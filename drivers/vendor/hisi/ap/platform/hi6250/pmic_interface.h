/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pmic_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-03 10:23:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��3��
    ��    ��   : l00279044
    �޸�����   : �ӡ�nManager_PMIC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PMIC_INTERFACE_H__
#define __PMIC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/5) PMU_CTRL
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ���0��
   λ����UNION�ṹ:  PMIC_VERSION0_UNION */
#define PMIC_VERSION0_ADDR(base)                  ((base) + (0x000))

/* �Ĵ���˵�����汾�Ĵ���1��
   λ����UNION�ṹ:  PMIC_VERSION1_UNION */
#define PMIC_VERSION1_ADDR(base)                  ((base) + (0x001))

/* �Ĵ���˵�����汾�Ĵ���2��
   λ����UNION�ṹ:  PMIC_VERSION2_UNION */
#define PMIC_VERSION2_ADDR(base)                  ((base) + (0x002))

/* �Ĵ���˵�����汾�Ĵ���3��
   λ����UNION�ṹ:  PMIC_VERSION3_UNION */
#define PMIC_VERSION3_ADDR(base)                  ((base) + (0x003))

/* �Ĵ���˵�����汾�Ĵ���4��
   λ����UNION�ṹ:  PMIC_VERSION4_UNION */
#define PMIC_VERSION4_ADDR(base)                  ((base) + (0x004))

/* �Ĵ���˵�����汾�Ĵ���5��
   λ����UNION�ṹ:  PMIC_VERSION5_UNION */
#define PMIC_VERSION5_ADDR(base)                  ((base) + (0x005))

/* �Ĵ���˵����״̬��־�Ĵ���0��
   λ����UNION�ṹ:  PMIC_STATUS0_UNION */
#define PMIC_STATUS0_ADDR(base)                   ((base) + (0x006))

/* �Ĵ���˵����״̬��־�Ĵ���1��
   λ����UNION�ṹ:  PMIC_STATUS1_UNION */
#define PMIC_STATUS1_ADDR(base)                   ((base) + (0x007))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���0��
   λ����UNION�ṹ:  PMIC_NP_D2A_RES0_UNION */
#define PMIC_NP_D2A_RES0_ADDR(base)               ((base) + (0x00A))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���1��
   λ����UNION�ṹ:  PMIC_NP_D2A_RES1_UNION */
#define PMIC_NP_D2A_RES1_ADDR(base)               ((base) + (0x00B))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���2��
   λ����UNION�ṹ:  PMIC_D2A_RES0_UNION */
#define PMIC_D2A_RES0_ADDR(base)                  ((base) + (0x00C))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���3��
   λ����UNION�ṹ:  PMIC_D2A_RES1_UNION */
#define PMIC_D2A_RES1_ADDR(base)                  ((base) + (0x00D))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���4��
   λ����UNION�ṹ:  PMIC_A2D_RES0_UNION */
#define PMIC_A2D_RES0_ADDR(base)                  ((base) + (0x00E))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���5��
   λ����UNION�ṹ:  PMIC_A2D_RES1_UNION */
#define PMIC_A2D_RES1_ADDR(base)                  ((base) + (0x00F))

/* �Ĵ���˵����BUCK0���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK0_ONOFF_ECO_UNION */
#define PMIC_BUCK0_ONOFF_ECO_ADDR(base)           ((base) + (0x010))

/* �Ĵ���˵����BUCK1���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK1_ONOFF_ECO_UNION */
#define PMIC_BUCK1_ONOFF_ECO_ADDR(base)           ((base) + (0x011))

/* �Ĵ���˵����BUCK2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK2_ONOFF_ECO_UNION */
#define PMIC_BUCK2_ONOFF_ECO_ADDR(base)           ((base) + (0x012))

/* �Ĵ���˵����BUCK3���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK3_ONOFF_ECO_UNION */
#define PMIC_BUCK3_ONOFF_ECO_ADDR(base)           ((base) + (0x013))

/* �Ĵ���˵����LDO0_1����ʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO0_1_ONOFF_UNION */
#define PMIC_LDO0_1_ONOFF_ADDR(base)              ((base) + (0x014))

/* �Ĵ���˵����LDO0_2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO0_2_ONOFF_ECO_UNION */
#define PMIC_LDO0_2_ONOFF_ECO_ADDR(base)          ((base) + (0x015))

/* �Ĵ���˵����LDO1���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO1_ONOFF_ECO_UNION */
#define PMIC_LDO1_ONOFF_ECO_ADDR(base)            ((base) + (0x016))

/* �Ĵ���˵����LDO2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO2_ONOFF_ECO_UNION */
#define PMIC_LDO2_ONOFF_ECO_ADDR(base)            ((base) + (0x017))

/* �Ĵ���˵����LDO3���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO3_ONOFF_ECO_UNION */
#define PMIC_LDO3_ONOFF_ECO_ADDR(base)            ((base) + (0x018))

/* �Ĵ���˵����LDO4���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO4_ONOFF_ECO_UNION */
#define PMIC_LDO4_ONOFF_ECO_ADDR(base)            ((base) + (0x019))

/* �Ĵ���˵����LDO5���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO5_ONOFF_ECO_UNION */
#define PMIC_LDO5_ONOFF_ECO_ADDR(base)            ((base) + (0x01A))

/* �Ĵ���˵����LDO7���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO7_ONOFF_ECO_UNION */
#define PMIC_LDO7_ONOFF_ECO_ADDR(base)            ((base) + (0x01B))

/* �Ĵ���˵����LDO8���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO8_ONOFF_ECO_UNION */
#define PMIC_LDO8_ONOFF_ECO_ADDR(base)            ((base) + (0x01C))

/* �Ĵ���˵����LDO9���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO9_ONOFF_ECO_UNION */
#define PMIC_LDO9_ONOFF_ECO_ADDR(base)            ((base) + (0x01D))

/* �Ĵ���˵����LDO10���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO10_ONOFF_ECO_UNION */
#define PMIC_LDO10_ONOFF_ECO_ADDR(base)           ((base) + (0x01E))

/* �Ĵ���˵����LDO11���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO11_ONOFF_ECO_UNION */
#define PMIC_LDO11_ONOFF_ECO_ADDR(base)           ((base) + (0x01F))

/* �Ĵ���˵����LDO12���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO12_ONOFF_ECO_UNION */
#define PMIC_LDO12_ONOFF_ECO_ADDR(base)           ((base) + (0x020))

/* �Ĵ���˵����LDO13���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO13_ONOFF_ECO_UNION */
#define PMIC_LDO13_ONOFF_ECO_ADDR(base)           ((base) + (0x021))

/* �Ĵ���˵����LDO14���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO14_ONOFF_ECO_UNION */
#define PMIC_LDO14_ONOFF_ECO_ADDR(base)           ((base) + (0x022))

/* �Ĵ���˵����LDO15���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO15_ONOFF_ECO_UNION */
#define PMIC_LDO15_ONOFF_ECO_ADDR(base)           ((base) + (0x023))

/* �Ĵ���˵����LDO16���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO16_ONOFF_ECO_UNION */
#define PMIC_LDO16_ONOFF_ECO_ADDR(base)           ((base) + (0x024))

/* �Ĵ���˵����LDO17���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO17_ONOFF_ECO_UNION */
#define PMIC_LDO17_ONOFF_ECO_ADDR(base)           ((base) + (0x025))

/* �Ĵ���˵����LDO19���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO19_ONOFF_ECO_UNION */
#define PMIC_LDO19_ONOFF_ECO_ADDR(base)           ((base) + (0x026))

/* �Ĵ���˵����LDO20���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO20_ONOFF_ECO_UNION */
#define PMIC_LDO20_ONOFF_ECO_ADDR(base)           ((base) + (0x027))

/* �Ĵ���˵����LDO21���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO21_ONOFF_ECO_UNION */
#define PMIC_LDO21_ONOFF_ECO_ADDR(base)           ((base) + (0x028))

/* �Ĵ���˵����LDO22���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_ONOFF_ECO_UNION */
#define PMIC_LDO22_ONOFF_ECO_ADDR(base)           ((base) + (0x029))

/* �Ĵ���˵����LDO23���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO23_ONOFF_ECO_UNION */
#define PMIC_LDO23_ONOFF_ECO_ADDR(base)           ((base) + (0x02A))

/* �Ĵ���˵����LDO24���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO24_ONOFF_ECO_UNION */
#define PMIC_LDO24_ONOFF_ECO_ADDR(base)           ((base) + (0x02B))

/* �Ĵ���˵����LDO25���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO25_ONOFF_ECO_UNION */
#define PMIC_LDO25_ONOFF_ECO_ADDR(base)           ((base) + (0x02C))

/* �Ĵ���˵����LDO26���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO26_ONOFF_ECO_UNION */
#define PMIC_LDO26_ONOFF_ECO_ADDR(base)           ((base) + (0x02D))

/* �Ĵ���˵����LDO27���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO27_ONOFF_ECO_UNION */
#define PMIC_LDO27_ONOFF_ECO_ADDR(base)           ((base) + (0x02E))

/* �Ĵ���˵����LDO28���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO28_ONOFF_ECO_UNION */
#define PMIC_LDO28_ONOFF_ECO_ADDR(base)           ((base) + (0x02F))

/* �Ĵ���˵����LDO29���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO29_ONOFF_ECO_UNION */
#define PMIC_LDO29_ONOFF_ECO_ADDR(base)           ((base) + (0x030))

/* �Ĵ���˵����LDO���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO31_ONOFF_ECO_UNION */
#define PMIC_LDO31_ONOFF_ECO_ADDR(base)           ((base) + (0x031))

/* �Ĵ���˵����LDO32���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO32_ONOFF_ECO_UNION */
#define PMIC_LDO32_ONOFF_ECO_ADDR(base)           ((base) + (0x032))

/* �Ĵ���˵����LDO���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO33_ONOFF_ECO_UNION */
#define PMIC_LDO33_ONOFF_ECO_ADDR(base)           ((base) + (0x033))

/* �Ĵ���˵����LDO���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO34_ONOFF_ECO_UNION */
#define PMIC_LDO34_ONOFF_ECO_ADDR(base)           ((base) + (0x034))

/* �Ĵ���˵����BUCK0��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK0_VSET_UNION */
#define PMIC_BUCK0_VSET_ADDR(base)                ((base) + (0x03A))

/* �Ĵ���˵����BUCK1��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK1_VSET_UNION */
#define PMIC_BUCK1_VSET_ADDR(base)                ((base) + (0x03B))

/* �Ĵ���˵����BUCK2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK2_VSET_UNION */
#define PMIC_BUCK2_VSET_ADDR(base)                ((base) + (0x03C))

/* �Ĵ���˵����BUCK3��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK3_VSET_UNION */
#define PMIC_BUCK3_VSET_ADDR(base)                ((base) + (0x03D))

/* �Ĵ���˵����LDO0_2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO0_2_VSET_UNION */
#define PMIC_LDO0_2_VSET_ADDR(base)               ((base) + (0x03E))

/* �Ĵ���˵����LDO1��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO1_VSET_UNION */
#define PMIC_LDO1_VSET_ADDR(base)                 ((base) + (0x03F))

/* �Ĵ���˵����LDO2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO2_VSET_UNION */
#define PMIC_LDO2_VSET_ADDR(base)                 ((base) + (0x040))

/* �Ĵ���˵����LDO3��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO3_VSET_UNION */
#define PMIC_LDO3_VSET_ADDR(base)                 ((base) + (0x041))

/* �Ĵ���˵����LDO4��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO4_VSET_UNION */
#define PMIC_LDO4_VSET_ADDR(base)                 ((base) + (0x042))

/* �Ĵ���˵����LDO5��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO5_VSET_UNION */
#define PMIC_LDO5_VSET_ADDR(base)                 ((base) + (0x043))

/* �Ĵ���˵����LDO7��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO7_VSET_UNION */
#define PMIC_LDO7_VSET_ADDR(base)                 ((base) + (0x044))

/* �Ĵ���˵����LDO8��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO8_VSET_UNION */
#define PMIC_LDO8_VSET_ADDR(base)                 ((base) + (0x045))

/* �Ĵ���˵����LDO9��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO9_VSET_UNION */
#define PMIC_LDO9_VSET_ADDR(base)                 ((base) + (0x046))

/* �Ĵ���˵����LDO10��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO10_VSET_UNION */
#define PMIC_LDO10_VSET_ADDR(base)                ((base) + (0x047))

/* �Ĵ���˵����LDO11��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO11_VSET_UNION */
#define PMIC_LDO11_VSET_ADDR(base)                ((base) + (0x048))

/* �Ĵ���˵����LDO12��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO12_VSET_UNION */
#define PMIC_LDO12_VSET_ADDR(base)                ((base) + (0x049))

/* �Ĵ���˵����LDO13��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO13_VSET_UNION */
#define PMIC_LDO13_VSET_ADDR(base)                ((base) + (0x04A))

/* �Ĵ���˵����LDO14��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO14_VSET_UNION */
#define PMIC_LDO14_VSET_ADDR(base)                ((base) + (0x04B))

/* �Ĵ���˵����LDO15��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO15_VSET_UNION */
#define PMIC_LDO15_VSET_ADDR(base)                ((base) + (0x04C))

/* �Ĵ���˵����LDO16��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO16_VSET_UNION */
#define PMIC_LDO16_VSET_ADDR(base)                ((base) + (0x04D))

/* �Ĵ���˵����LDO17��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO17_VSET_UNION */
#define PMIC_LDO17_VSET_ADDR(base)                ((base) + (0x04E))

/* �Ĵ���˵����LDO19��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO19_VSET1_UNION */
#define PMIC_LDO19_VSET1_ADDR(base)               ((base) + (0x04F))

/* �Ĵ���˵����LDO20��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO20_VSET_UNION */
#define PMIC_LDO20_VSET_ADDR(base)                ((base) + (0x050))

/* �Ĵ���˵����LDO21��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO21_VSET_UNION */
#define PMIC_LDO21_VSET_ADDR(base)                ((base) + (0x051))

/* �Ĵ���˵����LDO22��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO22_VSET_UNION */
#define PMIC_LDO22_VSET_ADDR(base)                ((base) + (0x052))

/* �Ĵ���˵����LDO23��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO23_VSET_UNION */
#define PMIC_LDO23_VSET_ADDR(base)                ((base) + (0x053))

/* �Ĵ���˵����LDO24��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO24_VSET_UNION */
#define PMIC_LDO24_VSET_ADDR(base)                ((base) + (0x054))

/* �Ĵ���˵����LDO25��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO25_VSET_UNION */
#define PMIC_LDO25_VSET_ADDR(base)                ((base) + (0x055))

/* �Ĵ���˵����LDO26��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO26_VSET_UNION */
#define PMIC_LDO26_VSET_ADDR(base)                ((base) + (0x056))

/* �Ĵ���˵����LDO27��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO27_VSET_UNION */
#define PMIC_LDO27_VSET_ADDR(base)                ((base) + (0x057))

/* �Ĵ���˵����LDO28��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO28_VSET_UNION */
#define PMIC_LDO28_VSET_ADDR(base)                ((base) + (0x058))

/* �Ĵ���˵����LDO29��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO29_VSET_UNION */
#define PMIC_LDO29_VSET_ADDR(base)                ((base) + (0x059))

/* �Ĵ���˵����LDO31��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO31_VSET_UNION */
#define PMIC_LDO31_VSET_ADDR(base)                ((base) + (0x05A))

/* �Ĵ���˵����LDO32��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO32_VSET_UNION */
#define PMIC_LDO32_VSET_ADDR(base)                ((base) + (0x05B))

/* �Ĵ���˵����LDO33��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO33_VSET_UNION */
#define PMIC_LDO33_VSET_ADDR(base)                ((base) + (0x05C))

/* �Ĵ���˵����LDO34��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO34_VSET_UNION */
#define PMIC_LDO34_VSET_ADDR(base)                ((base) + (0x05D))

/* �Ĵ���˵����BUCK0���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL0_UNION */
#define PMIC_BUCK0_CTRL0_ADDR(base)               ((base) + (0x064))

/* �Ĵ���˵����BUCK0���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL1_UNION */
#define PMIC_BUCK0_CTRL1_ADDR(base)               ((base) + (0x065))

/* �Ĵ���˵����BUCK0���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL2_UNION */
#define PMIC_BUCK0_CTRL2_ADDR(base)               ((base) + (0x066))

/* �Ĵ���˵����BUCK0���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL3_UNION */
#define PMIC_BUCK0_CTRL3_ADDR(base)               ((base) + (0x067))

/* �Ĵ���˵����BUCK0���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL4_UNION */
#define PMIC_BUCK0_CTRL4_ADDR(base)               ((base) + (0x068))

/* �Ĵ���˵����BUCK0���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL5_UNION */
#define PMIC_BUCK0_CTRL5_ADDR(base)               ((base) + (0x069))

/* �Ĵ���˵����BUCK0���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL6_UNION */
#define PMIC_BUCK0_CTRL6_ADDR(base)               ((base) + (0x06A))

/* �Ĵ���˵����BUCK0���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL7_UNION */
#define PMIC_BUCK0_CTRL7_ADDR(base)               ((base) + (0x06B))

/* �Ĵ���˵����BUCK0���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL8_UNION */
#define PMIC_BUCK0_CTRL8_ADDR(base)               ((base) + (0x06C))

/* �Ĵ���˵����BUCK1���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL0_UNION */
#define PMIC_BUCK1_CTRL0_ADDR(base)               ((base) + (0x06D))

/* �Ĵ���˵����BUCK1���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL1_UNION */
#define PMIC_BUCK1_CTRL1_ADDR(base)               ((base) + (0x06E))

/* �Ĵ���˵����BUCK1���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL2_UNION */
#define PMIC_BUCK1_CTRL2_ADDR(base)               ((base) + (0x06F))

/* �Ĵ���˵����BUCK1���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL3_UNION */
#define PMIC_BUCK1_CTRL3_ADDR(base)               ((base) + (0x070))

/* �Ĵ���˵����BUCK1���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL4_UNION */
#define PMIC_BUCK1_CTRL4_ADDR(base)               ((base) + (0x071))

/* �Ĵ���˵����BUCK1���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL5_UNION */
#define PMIC_BUCK1_CTRL5_ADDR(base)               ((base) + (0x072))

/* �Ĵ���˵����BUCK1���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL6_UNION */
#define PMIC_BUCK1_CTRL6_ADDR(base)               ((base) + (0x073))

/* �Ĵ���˵����BUCK1���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL7_UNION */
#define PMIC_BUCK1_CTRL7_ADDR(base)               ((base) + (0x074))

/* �Ĵ���˵����BUCK1���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL8_UNION */
#define PMIC_BUCK1_CTRL8_ADDR(base)               ((base) + (0x075))

/* �Ĵ���˵����BUCK2���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL0_UNION */
#define PMIC_BUCK2_CTRL0_ADDR(base)               ((base) + (0x076))

/* �Ĵ���˵����BUCK2���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL1_UNION */
#define PMIC_BUCK2_CTRL1_ADDR(base)               ((base) + (0x077))

/* �Ĵ���˵����BUCK2���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL2_UNION */
#define PMIC_BUCK2_CTRL2_ADDR(base)               ((base) + (0x078))

/* �Ĵ���˵����BUCK2���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL3_UNION */
#define PMIC_BUCK2_CTRL3_ADDR(base)               ((base) + (0x079))

/* �Ĵ���˵����BUCK2���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL4_UNION */
#define PMIC_BUCK2_CTRL4_ADDR(base)               ((base) + (0x07A))

/* �Ĵ���˵����BUCK2���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL5_UNION */
#define PMIC_BUCK2_CTRL5_ADDR(base)               ((base) + (0x07B))

/* �Ĵ���˵����BUCK2���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL6_UNION */
#define PMIC_BUCK2_CTRL6_ADDR(base)               ((base) + (0x07C))

/* �Ĵ���˵����BUCK2���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL7_UNION */
#define PMIC_BUCK2_CTRL7_ADDR(base)               ((base) + (0x07D))

/* �Ĵ���˵����BUCK2���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL8_UNION */
#define PMIC_BUCK2_CTRL8_ADDR(base)               ((base) + (0x07E))

/* �Ĵ���˵����BUCK3���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL0_UNION */
#define PMIC_BUCK3_CTRL0_ADDR(base)               ((base) + (0x07F))

/* �Ĵ���˵����BUCK3���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL1_UNION */
#define PMIC_BUCK3_CTRL1_ADDR(base)               ((base) + (0x080))

/* �Ĵ���˵����BUCK3���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL2_UNION */
#define PMIC_BUCK3_CTRL2_ADDR(base)               ((base) + (0x081))

/* �Ĵ���˵����BUCK3���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL3_UNION */
#define PMIC_BUCK3_CTRL3_ADDR(base)               ((base) + (0x082))

/* �Ĵ���˵����BUCK3���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL4_UNION */
#define PMIC_BUCK3_CTRL4_ADDR(base)               ((base) + (0x083))

/* �Ĵ���˵����BUCK3���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL5_UNION */
#define PMIC_BUCK3_CTRL5_ADDR(base)               ((base) + (0x084))

/* �Ĵ���˵����BUCK3���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL6_UNION */
#define PMIC_BUCK3_CTRL6_ADDR(base)               ((base) + (0x085))

/* �Ĵ���˵����BUCK3���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL7_UNION */
#define PMIC_BUCK3_CTRL7_ADDR(base)               ((base) + (0x086))

/* �Ĵ���˵����BUCK3���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL8_UNION */
#define PMIC_BUCK3_CTRL8_ADDR(base)               ((base) + (0x087))

/* �Ĵ���˵����BUCKԤ���Ĵ���
   λ����UNION�ṹ:  PMIC_BUCK_RESERVE0_UNION */
#define PMIC_BUCK_RESERVE0_ADDR(base)             ((base) + (0x088))

/* �Ĵ���˵����BUCKԤ���Ĵ���
   λ����UNION�ṹ:  PMIC_BUCK_RESERVE1_UNION */
#define PMIC_BUCK_RESERVE1_ADDR(base)             ((base) + (0x089))

/* �Ĵ���˵����LDO0_2/LDO1���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO_1_CTRL_UNION */
#define PMIC_LDO_1_CTRL_ADDR(base)                ((base) + (0x08A))

/* �Ĵ���˵����LDO1���ƼĴ���
   λ����UNION�ṹ:  PMIC_LDO1_CTRL_0_UNION */
#define PMIC_LDO1_CTRL_0_ADDR(base)               ((base) + (0x08B))

/* �Ĵ���˵����LDO1���ƼĴ���
   λ����UNION�ṹ:  PMIC_LDO1_CTRL_1_UNION */
#define PMIC_LDO1_CTRL_1_ADDR(base)               ((base) + (0x08C))

/* �Ĵ���˵����LDO2/LDO3���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO2_3_CTRL_UNION */
#define PMIC_LDO2_3_CTRL_ADDR(base)               ((base) + (0x08D))

/* �Ĵ���˵����LDO3���ƼĴ���
   λ����UNION�ṹ:  PMIC_LDO3_CTRL_UNION */
#define PMIC_LDO3_CTRL_ADDR(base)                 ((base) + (0x08E))

/* �Ĵ���˵����LDO4/LDO5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO4_5_CTRL_UNION */
#define PMIC_LDO4_5_CTRL_ADDR(base)               ((base) + (0x08F))

/* �Ĵ���˵����LDO7/LDO8���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO7_8_CTRL_UNION */
#define PMIC_LDO7_8_CTRL_ADDR(base)               ((base) + (0x090))

/* �Ĵ���˵����LDO9/LDO10���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO9_10_CTRL_UNION */
#define PMIC_LDO9_10_CTRL_ADDR(base)              ((base) + (0x091))

/* �Ĵ���˵����LDO11/LDO12���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LD11_12_CTRL_UNION */
#define PMIC_LD11_12_CTRL_ADDR(base)              ((base) + (0x092))

/* �Ĵ���˵����LDO13/LDO14���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO13_14_CTRL_UNION */
#define PMIC_LDO13_14_CTRL_ADDR(base)             ((base) + (0x093))

/* �Ĵ���˵����LDO15/LDO16���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO15_16_CTRL_UNION */
#define PMIC_LDO15_16_CTRL_ADDR(base)             ((base) + (0x094))

/* �Ĵ���˵����LDO17/LDO19���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO17_19_CTRL_UNION */
#define PMIC_LDO17_19_CTRL_ADDR(base)             ((base) + (0x095))

/* �Ĵ���˵����LDO20/LDO21���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO20_21_CTRL_UNION */
#define PMIC_LDO20_21_CTRL_ADDR(base)             ((base) + (0x096))

/* �Ĵ���˵����LDO22���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_CTRL0_UNION */
#define PMIC_LDO22_CTRL0_ADDR(base)               ((base) + (0x097))

/* �Ĵ���˵����LDO22���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_CTRL1_UNION */
#define PMIC_LDO22_CTRL1_ADDR(base)               ((base) + (0x098))

/* �Ĵ���˵����LDO22���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_CTRL2_UNION */
#define PMIC_LDO22_CTRL2_ADDR(base)               ((base) + (0x099))

/* �Ĵ���˵����LDO23���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO23_CTRL_UNION */
#define PMIC_LDO23_CTRL_ADDR(base)                ((base) + (0x09A))

/* �Ĵ���˵����LDO24/LDO25���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO24_25_CTRL_UNION */
#define PMIC_LDO24_25_CTRL_ADDR(base)             ((base) + (0x09B))

/* �Ĵ���˵����LDO26���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO26_CTRL_UNION */
#define PMIC_LDO26_CTRL_ADDR(base)                ((base) + (0x09C))

/* �Ĵ���˵����LDO27���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO27_CTRL_UNION */
#define PMIC_LDO27_CTRL_ADDR(base)                ((base) + (0x09D))

/* �Ĵ���˵����LDO28/LDO29���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO28_29_CTRL_UNION */
#define PMIC_LDO28_29_CTRL_ADDR(base)             ((base) + (0x09E))

/* �Ĵ���˵����LDO31/LDO32���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO31_32_CTRL_UNION */
#define PMIC_LDO31_32_CTRL_ADDR(base)             ((base) + (0x09F))

/* �Ĵ���˵����LDO33/LDO34���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO33_LDO34_CTRL_UNION */
#define PMIC_LDO33_LDO34_CTRL_ADDR(base)          ((base) + (0x0A0))

/* �Ĵ���˵����LDOԤ���Ĵ���
   λ����UNION�ṹ:  PMIC_LDO_RESERVE0_UNION */
#define PMIC_LDO_RESERVE0_ADDR(base)              ((base) + (0x0A1))

/* �Ĵ���˵����LDOԤ���Ĵ���
   λ����UNION�ṹ:  PMIC_LDO_RESERVE1_UNION */
#define PMIC_LDO_RESERVE1_ADDR(base)              ((base) + (0x0A2))

/* �Ĵ���˵����BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK0_3_OCP_CTRL_UNION */
#define PMIC_BUCK0_3_OCP_CTRL_ADDR(base)          ((base) + (0x100))

/* �Ĵ���˵����BUCK4/LDO0/1/2 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO0_3_OCP_CTRL_UNION */
#define PMIC_LDO0_3_OCP_CTRL_ADDR(base)           ((base) + (0x101))

/* �Ĵ���˵����LCO3/4/5/7 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO4_8_OCP_CTRL_UNION */
#define PMIC_LDO4_8_OCP_CTRL_ADDR(base)           ((base) + (0x102))

/* �Ĵ���˵����LDO8/9/10/11 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO9_12_OCP_CTRL_UNION */
#define PMIC_LDO9_12_OCP_CTRL_ADDR(base)          ((base) + (0x103))

/* �Ĵ���˵����LDO12/13/14/15 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO13_16_OCP_CTRL_UNION */
#define PMIC_LDO13_16_OCP_CTRL_ADDR(base)         ((base) + (0x104))

/* �Ĵ���˵����LDO16/17/19/20 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO17_21_OCP_CTRL_UNION */
#define PMIC_LDO17_21_OCP_CTRL_ADDR(base)         ((base) + (0x105))

/* �Ĵ���˵����LDO21/22/23/24 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_25_OCP_CTRL_UNION */
#define PMIC_LDO22_25_OCP_CTRL_ADDR(base)         ((base) + (0x106))

/* �Ĵ���˵����LDO25/26/27/28 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO26_29_OCP_CTRL_UNION */
#define PMIC_LDO26_29_OCP_CTRL_ADDR(base)         ((base) + (0x107))

/* �Ĵ���˵����LDO31/32/33/34 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO31_34_OCP_CTRL_UNION */
#define PMIC_LDO31_34_OCP_CTRL_ADDR(base)         ((base) + (0x108))

/* �Ĵ���˵����LDO_BUFF SCP/CLASS OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION */
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_ADDR(base)   ((base) + (0x109))

/* �Ĵ���˵����BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK0_3_SCP_CTRL_UNION */
#define PMIC_BUCK0_3_SCP_CTRL_ADDR(base)          ((base) + (0x10A))

/* �Ĵ���˵����LDO_PMUA ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO_PMUA_ECO_UNION */
#define PMIC_LDO_PMUA_ECO_ADDR(base)              ((base) + (0x10D))

/* �Ĵ���˵����LDO_PMUA��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO_PMUA_VSET_UNION */
#define PMIC_LDO_PMUA_VSET_ADDR(base)             ((base) + (0x10E))

/* �Ĵ���˵����ABBʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_ABB_EN_UNION */
#define PMIC_CLK_ABB_EN_ADDR(base)                ((base) + (0x10F))

/* �Ĵ���˵����WIFIʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_WIFI_EN_UNION */
#define PMIC_CLK_WIFI_EN_ADDR(base)               ((base) + (0x110))

/* �Ĵ���˵����RF0ʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_RF0_EN_UNION */
#define PMIC_CLK_RF0_EN_ADDR(base)                ((base) + (0x111))

/* �Ĵ���˵����RF1ʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_RF1_EN_UNION */
#define PMIC_CLK_RF1_EN_ADDR(base)                ((base) + (0x112))

/* �Ĵ���˵����SYSʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_SYS_EN_UNION */
#define PMIC_CLK_SYS_EN_ADDR(base)                ((base) + (0x113))

/* �Ĵ���˵����CODECʱ�ӿ��ؼĴ���
   λ����UNION�ṹ:  PMIC_CLK_CODEC_EN_UNION */
#define PMIC_CLK_CODEC_EN_ADDR(base)              ((base) + (0x114))

/* �Ĵ���˵����ABBʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_ABB_CTRL_UNION */
#define PMIC_CLK_ABB_CTRL_ADDR(base)              ((base) + (0x115))

/* �Ĵ���˵����WIFIʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_WIFI_CTRL_UNION */
#define PMIC_CLK_WIFI_CTRL_ADDR(base)             ((base) + (0x116))

/* �Ĵ���˵����RF0ʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_RF0_CTRL_UNION */
#define PMIC_CLK_RF0_CTRL_ADDR(base)              ((base) + (0x117))

/* �Ĵ���˵����RF1ʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_RF1_CTRL_UNION */
#define PMIC_CLK_RF1_CTRL_ADDR(base)              ((base) + (0x118))

/* �Ĵ���˵����SYSʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_SYS_CTRL_UNION */
#define PMIC_CLK_SYS_CTRL_ADDR(base)              ((base) + (0x119))

/* �Ĵ���˵����CODECʱ�����üĴ���
   λ����UNION�ṹ:  PMIC_CLK_CODEC_CTRL_UNION */
#define PMIC_CLK_CODEC_CTRL_ADDR(base)            ((base) + (0x11A))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL0_UNION */
#define PMIC_CLK_TOP_CTRL0_ADDR(base)             ((base) + (0x11B))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL1_UNION */
#define PMIC_CLK_TOP_CTRL1_ADDR(base)             ((base) + (0x11C))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���2��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL2_UNION */
#define PMIC_CLK_TOP_CTRL2_ADDR(base)             ((base) + (0x11D))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���3��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL3_UNION */
#define PMIC_CLK_TOP_CTRL3_ADDR(base)             ((base) + (0x11E))

/* �Ĵ���˵����256K RC���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLK_256K_CTRL0_UNION */
#define PMIC_CLK_256K_CTRL0_ADDR(base)            ((base) + (0x11F))

/* �Ĵ���˵����256K RC���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLK_256K_CTRL1_UNION */
#define PMIC_CLK_256K_CTRL1_ADDR(base)            ((base) + (0x120))

/* �Ĵ���˵����32kHzʱ�����ʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_OSC32K_ONOFF_CTRL_UNION */
#define PMIC_OSC32K_ONOFF_CTRL_ADDR(base)         ((base) + (0x121))

/* �Ĵ���˵����Ӳ�����ο��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_HARDWIRE_CTRL0_UNION */
#define PMIC_HARDWIRE_CTRL0_ADDR(base)            ((base) + (0x125))

/* �Ĵ���˵����Ӳ�����ο��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_HARDWIRE_CTRL1_UNION */
#define PMIC_HARDWIRE_CTRL1_ADDR(base)            ((base) + (0x126))

/* �Ĵ���˵����periӲ�߿��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_PERI_CTRL0_UNION */
#define PMIC_PERI_CTRL0_ADDR(base)                ((base) + (0x127))

/* �Ĵ���˵����periӲ�߿��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_PERI_CTRL1_UNION */
#define PMIC_PERI_CTRL1_ADDR(base)                ((base) + (0x128))

/* �Ĵ���˵����periӲ�߿��ƼĴ���2��
   λ����UNION�ṹ:  PMIC_PERI_CTRL2_UNION */
#define PMIC_PERI_CTRL2_ADDR(base)                ((base) + (0x129))

/* �Ĵ���˵����periӲ�߿��ƼĴ���3��
   λ����UNION�ṹ:  PMIC_PERI_CTRL3_UNION */
#define PMIC_PERI_CTRL3_ADDR(base)                ((base) + (0x12A))

/* �Ĵ���˵����periӲ�ߵ�ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_PERI_VSET_CTRL_UNION */
#define PMIC_PERI_VSET_CTRL_ADDR(base)            ((base) + (0x12B))

/* �Ĵ���˵����periӲ��ʱ�������ƼĴ�����
   λ����UNION�ṹ:  PMIC_PERI_TIME__CTRL_UNION */
#define PMIC_PERI_TIME__CTRL_ADDR(base)           ((base) + (0x12C))

/* �Ĵ���˵�������ؼ�ECOʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_COUL_ECO_MASK_UNION */
#define PMIC_COUL_ECO_MASK_ADDR(base)             ((base) + (0x12D))

/* �Ĵ���˵����IRQ_MASK0���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_0_UNION */
#define PMIC_IRQ_MASK_0_ADDR(base)                ((base) + (0x130))

/* �Ĵ���˵����IRQ_MASK1���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_1_UNION */
#define PMIC_IRQ_MASK_1_ADDR(base)                ((base) + (0x131))

/* �Ĵ���˵����IRQ_MASK3���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_2_UNION */
#define PMIC_IRQ_MASK_2_ADDR(base)                ((base) + (0x132))

/* �Ĵ���˵����IRQ_MASK4���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_3_UNION */
#define PMIC_IRQ_MASK_3_ADDR(base)                ((base) + (0x133))

/* �Ĵ���˵����IRQ_MASK5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_4_UNION */
#define PMIC_IRQ_MASK_4_ADDR(base)                ((base) + (0x134))

/* �Ĵ���˵����IRQ_MASK6���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_5_UNION */
#define PMIC_IRQ_MASK_5_ADDR(base)                ((base) + (0x135))

/* �Ĵ���˵����IRQ_MASK7���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_6_UNION */
#define PMIC_IRQ_MASK_6_ADDR(base)                ((base) + (0x136))

/* �Ĵ���˵����IRQ_MASK8���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_7_UNION */
#define PMIC_IRQ_MASK_7_ADDR(base)                ((base) + (0x137))

/* �Ĵ���˵����NOPWRT���ƼĴ�����
   λ����UNION�ṹ:  PMIC_BACKUP_CHG_UNION */
#define PMIC_BACKUP_CHG_ADDR(base)                ((base) + (0x13A))

/* �Ĵ���˵����classd���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL0_UNION */
#define PMIC_CLASSD_CTRL0_ADDR(base)              ((base) + (0x13B))

/* �Ĵ���˵����classd���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL1_UNION */
#define PMIC_CLASSD_CTRL1_ADDR(base)              ((base) + (0x13C))

/* �Ĵ���˵����classd���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL2_UNION */
#define PMIC_CLASSD_CTRL2_ADDR(base)              ((base) + (0x13D))

/* �Ĵ���˵����classd���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL3_UNION */
#define PMIC_CLASSD_CTRL3_ADDR(base)              ((base) + (0x13E))

/* �Ĵ���˵������ѹ�¶ȿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_TH_CTRL_UNION */
#define PMIC_TH_CTRL_ADDR(base)                   ((base) + (0x13F))

/* �Ĵ���˵����bg���ԼĴ�����
   λ����UNION�ṹ:  PMIC_BG_TEST_UNION */
#define PMIC_BG_TEST_ADDR(base)                   ((base) + (0x140))

/* �Ĵ���˵����DR345��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_EN_MODE_345_UNION */
#define PMIC_DR_EN_MODE_345_ADDR(base)            ((base) + (0x141))

/* �Ĵ���˵����DR12��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_EN_MODE_12_UNION */
#define PMIC_DR_EN_MODE_12_ADDR(base)             ((base) + (0x142))

/* �Ĵ���˵����DR12��˸ģʽ���ڵ���0�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_PERIOD_DR12_UNION */
#define PMIC_FLASH_PERIOD_DR12_ADDR(base)         ((base) + (0x143))

/* �Ĵ���˵����DR12��˸ģʽ����ʱ�����0�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_ON_DR12_UNION */
#define PMIC_FLASH_ON_DR12_ADDR(base)             ((base) + (0x144))

/* �Ĵ���˵����DR345��˸ģʽ���ڵ���1�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_PERIOD_DR345_UNION */
#define PMIC_FLASH_PERIOD_DR345_ADDR(base)        ((base) + (0x145))

/* �Ĵ���˵����DR345��˸ģʽ����ʱ�����1�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_ON_DR345_UNION */
#define PMIC_FLASH_ON_DR345_ADDR(base)            ((base) + (0x146))

/* �Ĵ���˵����DR��ģʽѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_MODE_SEL_UNION */
#define PMIC_DR_MODE_SEL_ADDR(base)               ((base) + (0x147))

/* �Ĵ���˵����DR1/2����ģʽ���ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_BRE_CTRL_UNION */
#define PMIC_DR_BRE_CTRL_ADDR(base)               ((base) + (0x148))

/* �Ĵ���˵����DR1��DR2��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR12_TIM_CONF0_UNION */
#define PMIC_DR12_TIM_CONF0_ADDR(base)            ((base) + (0x149))

/* �Ĵ���˵����DR1��DR2��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR12_TIM_CONF1_UNION */
#define PMIC_DR12_TIM_CONF1_ADDR(base)            ((base) + (0x14A))

/* �Ĵ���˵����DR1����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR1_ISET_UNION */
#define PMIC_DR1_ISET_ADDR(base)                  ((base) + (0x14B))

/* �Ĵ���˵����DR2����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR2_ISET_UNION */
#define PMIC_DR2_ISET_ADDR(base)                  ((base) + (0x14C))

/* �Ĵ���˵����DR3/4/5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_LED_CTRL_UNION */
#define PMIC_DR_LED_CTRL_ADDR(base)               ((base) + (0x14D))

/* �Ĵ���˵����DR3/4/5������ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_OUT_CTRL_UNION */
#define PMIC_DR_OUT_CTRL_ADDR(base)               ((base) + (0x14E))

/* �Ĵ���˵����DR3����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR3_ISET_UNION */
#define PMIC_DR3_ISET_ADDR(base)                  ((base) + (0x14F))

/* �Ĵ���˵����DR3������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR3_START_DEL_UNION */
#define PMIC_DR3_START_DEL_ADDR(base)             ((base) + (0x150))

/* �Ĵ���˵����DR4����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR4_ISET_UNION */
#define PMIC_DR4_ISET_ADDR(base)                  ((base) + (0x151))

/* �Ĵ���˵����DR4������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR4_START_DEL_UNION */
#define PMIC_DR4_START_DEL_ADDR(base)             ((base) + (0x152))

/* �Ĵ���˵����DR5����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR5_ISET_UNION */
#define PMIC_DR5_ISET_ADDR(base)                  ((base) + (0x153))

/* �Ĵ���˵����DR5������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR5_START_DEL_UNION */
#define PMIC_DR5_START_DEL_ADDR(base)             ((base) + (0x154))

/* �Ĵ���˵����DR345��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR334_TIM_CONF0_UNION */
#define PMIC_DR334_TIM_CONF0_ADDR(base)           ((base) + (0x155))

/* �Ĵ���˵����DR345��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR345_TIM_CONF1_UNION */
#define PMIC_DR345_TIM_CONF1_ADDR(base)           ((base) + (0x156))

/* �Ĵ���˵����IN�˵�ѹ��ֵ�����Ĵ�����
   λ����UNION�ṹ:  PMIC_VSYS_LOW_SET_UNION */
#define PMIC_VSYS_LOW_SET_ADDR(base)              ((base) + (0x157))

/* �Ĵ���˵����nfc_on���ƼĴ�����
   λ����UNION�ṹ:  PMIC_NFC_ON_CTRL_UNION */
#define PMIC_NFC_ON_CTRL_ADDR(base)               ((base) + (0x158))

/* �Ĵ���˵����ϵͳ����Ԥ���Ĵ�����
   λ����UNION�ṹ:  PMIC_SYS_CTRL_RESERVE_UNION */
#define PMIC_SYS_CTRL_RESERVE_ADDR(base)          ((base) + (0x159))

/* �Ĵ���˵�����ȸ�λ�µ���ƼĴ�����
   λ����UNION�ṹ:  PMIC_HRESET_PWRDOWN_CTRL_UNION */
#define PMIC_HRESET_PWRDOWN_CTRL_ADDR(base)       ((base) + (0x15A))

/* �Ĵ���˵����OCP��SPC�˲�ʱ����ƼĴ�����
   λ����UNION�ṹ:  PMIC_OCP_DEB_CTRL0_UNION */
#define PMIC_OCP_DEB_CTRL0_ADDR(base)             ((base) + (0x15B))

/* �Ĵ���˵����OCP��SPC�˲�ʱ����ƼĴ�����
   λ����UNION�ṹ:  PMIC_OCP_DEB_CTRL1_UNION */
#define PMIC_OCP_DEB_CTRL1_ADDR(base)             ((base) + (0x15C))

/* �Ĵ���˵����OCP��DOCP�˲����ؼĴ�����
   λ����UNION�ṹ:  PMIC_OCP_SCP_ONOFF_UNION */
#define PMIC_OCP_SCP_ONOFF_ADDR(base)             ((base) + (0x15D))

/* �Ĵ���˵����Ƿѹ�ػ��˲�ʱ��ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_PWROFF_DEB_CTRL_UNION */
#define PMIC_PWROFF_DEB_CTRL_ADDR(base)           ((base) + (0x15E))

/* �Ĵ���˵����ϵͳ���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_SYS_CTRL0_UNION */
#define PMIC_SYS_CTRL0_ADDR(base)                 ((base) + (0x15F))

/* �Ĵ���˵����SMPL���ƼĴ�����
   λ����UNION�ṹ:  PMIC_SMPL_CTRL_UNION */
#define PMIC_SMPL_CTRL_ADDR(base)                 ((base) + (0x160))

/* �Ĵ���˵����ϵͳ���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_SYS_CTRL1_UNION */
#define PMIC_SYS_CTRL1_ADDR(base)                 ((base) + (0x161))

/* �Ĵ���˵����SIM���ƼĴ�����
   λ����UNION�ṹ:  PMIC_SIM_CTRL_UNION */
#define PMIC_SIM_CTRL_ADDR(base)                  ((base) + (0x162))

/* �Ĵ���˵����SIM�˲����ƼĴ�����
   λ����UNION�ṹ:  PMIC_SIM_DEB_CTRL_UNION */
#define PMIC_SIM_DEB_CTRL_ADDR(base)              ((base) + (0x163))

/* �Ĵ���˵����DAC0 IBIAS���üĴ�����
   λ����UNION�ṹ:  PMIC_AUX0_IBIAS_CFG_UNION */
#define PMIC_AUX0_IBIAS_CFG_ADDR(base)            ((base) + (0x164))

/* �Ĵ���˵����DAC1 IBIAS���üĴ�����
   λ����UNION�ṹ:  PMIC_AUX1_IBIAS_CFG_UNION */
#define PMIC_AUX1_IBIAS_CFG_ADDR(base)            ((base) + (0x165))

/* �Ĵ���˵����OTP0�ض��Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP0_0_UNION */
#define PMIC_OTP0_0_ADDR(base)                    ((base) + (0x16A))

/* �Ĵ���˵����OTP0�ض��Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP0_1_UNION */
#define PMIC_OTP0_1_ADDR(base)                    ((base) + (0x16B))

/* �Ĵ���˵����OTP0�ض��Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP0_2_UNION */
#define PMIC_OTP0_2_ADDR(base)                    ((base) + (0x16C))

/* �Ĵ���˵����OTP0�ض��Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP0_3_UNION */
#define PMIC_OTP0_3_ADDR(base)                    ((base) + (0x16D))

/* �Ĵ���˵����OTP0���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_OTP0_CTRL_0_UNION */
#define PMIC_OTP0_CTRL_0_ADDR(base)               ((base) + (0x16E))

/* �Ĵ���˵����OTP0���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_OTP0_CTRL_1_UNION */
#define PMIC_OTP0_CTRL_1_ADDR(base)               ((base) + (0x16F))

/* �Ĵ���˵����OTP0д�������ݼĴ�����
   λ����UNION�ṹ:  PMIC_OTP0_WDATA_UNION */
#define PMIC_OTP0_WDATA_ADDR(base)                ((base) + (0x170))

/* �Ĵ���˵����OTP0������Ĵ���0
   λ����UNION�ṹ:  PMIC_OTP0_0_W_UNION */
#define PMIC_OTP0_0_W_ADDR(base)                  ((base) + (0x171))

/* �Ĵ���˵����OTP0������Ĵ���1
   λ����UNION�ṹ:  PMIC_OTP0_1_W_UNION */
#define PMIC_OTP0_1_W_ADDR(base)                  ((base) + (0x172))

/* �Ĵ���˵����OTP0������Ĵ���2
   λ����UNION�ṹ:  PMIC_OTP0_2_W_UNION */
#define PMIC_OTP0_2_W_ADDR(base)                  ((base) + (0x173))

/* �Ĵ���˵����OTP0������Ĵ���3
   λ����UNION�ṹ:  PMIC_OTP0_3_W_UNION */
#define PMIC_OTP0_3_W_ADDR(base)                  ((base) + (0x174))

/* �Ĵ���˵����OTP1�ض��Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP1_0_UNION */
#define PMIC_OTP1_0_ADDR(base)                    ((base) + (0x175))

/* �Ĵ���˵����OTP1�ض��Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP1_1_UNION */
#define PMIC_OTP1_1_ADDR(base)                    ((base) + (0x176))

/* �Ĵ���˵����OTP1�ض��Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP1_2_UNION */
#define PMIC_OTP1_2_ADDR(base)                    ((base) + (0x177))

/* �Ĵ���˵����OTP1�ض��Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP1_3_UNION */
#define PMIC_OTP1_3_ADDR(base)                    ((base) + (0x178))

/* �Ĵ���˵����OTP1���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_OTP1_CTRL_0_UNION */
#define PMIC_OTP1_CTRL_0_ADDR(base)               ((base) + (0x179))

/* �Ĵ���˵����OTP1���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_OTP1_CTRL_1_UNION */
#define PMIC_OTP1_CTRL_1_ADDR(base)               ((base) + (0x17A))

/* �Ĵ���˵����OTP1д�������ݼĴ�����
   λ����UNION�ṹ:  PMIC_OTP1_WDATA_UNION */
#define PMIC_OTP1_WDATA_ADDR(base)                ((base) + (0x17B))

/* �Ĵ���˵����OTP1������Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP1_0_W_UNION */
#define PMIC_OTP1_0_W_ADDR(base)                  ((base) + (0x17C))

/* �Ĵ���˵����OTP1������Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP1_1_W_UNION */
#define PMIC_OTP1_1_W_ADDR(base)                  ((base) + (0x17D))

/* �Ĵ���˵����OTP1������Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP1_2_W_UNION */
#define PMIC_OTP1_2_W_ADDR(base)                  ((base) + (0x17E))

/* �Ĵ���˵����OTP1������Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP1_3_W_UNION */
#define PMIC_OTP1_3_W_ADDR(base)                  ((base) + (0x17F))

/* �Ĵ���˵����OTP2�ض��Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP2_0_UNION */
#define PMIC_OTP2_0_ADDR(base)                    ((base) + (0x180))

/* �Ĵ���˵����OTP2�ض��Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP2_1_UNION */
#define PMIC_OTP2_1_ADDR(base)                    ((base) + (0x181))

/* �Ĵ���˵����OTP2�ض��Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP2_2_UNION */
#define PMIC_OTP2_2_ADDR(base)                    ((base) + (0x182))

/* �Ĵ���˵����OTP2�ض��Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP2_3_UNION */
#define PMIC_OTP2_3_ADDR(base)                    ((base) + (0x183))

/* �Ĵ���˵����OTP2���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_OTP2_CTRL_0_UNION */
#define PMIC_OTP2_CTRL_0_ADDR(base)               ((base) + (0x184))

/* �Ĵ���˵����OTP2���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_OTP2_CTRL_1_UNION */
#define PMIC_OTP2_CTRL_1_ADDR(base)               ((base) + (0x185))

/* �Ĵ���˵����OTP2д�������ݼĴ�����
   λ����UNION�ṹ:  PMIC_OTP2_WDATA_UNION */
#define PMIC_OTP2_WDATA_ADDR(base)                ((base) + (0x186))

/* �Ĵ���˵����OTP2������Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP2_0_W_UNION */
#define PMIC_OTP2_0_W_ADDR(base)                  ((base) + (0x187))

/* �Ĵ���˵����OTP2������Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP2_1_W_UNION */
#define PMIC_OTP2_1_W_ADDR(base)                  ((base) + (0x188))

/* �Ĵ���˵����OTP2������Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP2_2_W_UNION */
#define PMIC_OTP2_2_W_ADDR(base)                  ((base) + (0x189))

/* �Ĵ���˵����OTP2������Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP2_3_W_UNION */
#define PMIC_OTP2_3_W_ADDR(base)                  ((base) + (0x18A))

/* �Ĵ���˵�������Ԥ���Ĵ���0��
   λ����UNION�ṹ:  PMIC_HRST_REG0_UNION */
#define PMIC_HRST_REG0_ADDR(base)                 ((base) + (0x18B))

/* �Ĵ���˵�������Ԥ���Ĵ���1��
   λ����UNION�ṹ:  PMIC_HRST_REG1_UNION */
#define PMIC_HRST_REG1_ADDR(base)                 ((base) + (0x18C))

/* �Ĵ���˵�������Ԥ���Ĵ���2��
   λ����UNION�ṹ:  PMIC_HRST_REG2_UNION */
#define PMIC_HRST_REG2_ADDR(base)                 ((base) + (0x18D))

/* �Ĵ���˵�������Ԥ���Ĵ���3��
   λ����UNION�ṹ:  PMIC_HRST_REG3_UNION */
#define PMIC_HRST_REG3_ADDR(base)                 ((base) + (0x18E))

/* �Ĵ���˵�������Ԥ���Ĵ���4��
   λ����UNION�ṹ:  PMIC_HRST_REG4_UNION */
#define PMIC_HRST_REG4_ADDR(base)                 ((base) + (0x18F))

/* �Ĵ���˵�������Ԥ���Ĵ���5��
   λ����UNION�ṹ:  PMIC_HRST_REG5_UNION */
#define PMIC_HRST_REG5_ADDR(base)                 ((base) + (0x190))

/* �Ĵ���˵�������Ԥ���Ĵ���6��
   λ����UNION�ṹ:  PMIC_HRST_REG6_UNION */
#define PMIC_HRST_REG6_ADDR(base)                 ((base) + (0x191))

/* �Ĵ���˵�������Ԥ���Ĵ���7��
   λ����UNION�ṹ:  PMIC_HRST_REG7_UNION */
#define PMIC_HRST_REG7_ADDR(base)                 ((base) + (0x192))

/* �Ĵ���˵�������Ԥ���Ĵ���8��
   λ����UNION�ṹ:  PMIC_HRST_REG8_UNION */
#define PMIC_HRST_REG8_ADDR(base)                 ((base) + (0x193))

/* �Ĵ���˵�������Ԥ���Ĵ���9��
   λ����UNION�ṹ:  PMIC_HRST_REG9_UNION */
#define PMIC_HRST_REG9_ADDR(base)                 ((base) + (0x194))

/* �Ĵ���˵�������Ԥ���Ĵ���10��
   λ����UNION�ṹ:  PMIC_HRST_REG10_UNION */
#define PMIC_HRST_REG10_ADDR(base)                ((base) + (0x195))

/* �Ĵ���˵�������Ԥ���Ĵ���11��
   λ����UNION�ṹ:  PMIC_HRST_REG11_UNION */
#define PMIC_HRST_REG11_ADDR(base)                ((base) + (0x196))

/* �Ĵ���˵�������Ԥ���Ĵ���12��
   λ����UNION�ṹ:  PMIC_HRST_REG12_UNION */
#define PMIC_HRST_REG12_ADDR(base)                ((base) + (0x197))

/* �Ĵ���˵�������Ԥ���Ĵ���13��
   λ����UNION�ṹ:  PMIC_HRST_REG13_UNION */
#define PMIC_HRST_REG13_ADDR(base)                ((base) + (0x198))

/* �Ĵ���˵�������Ԥ���Ĵ���14��
   λ����UNION�ṹ:  PMIC_HRST_REG14_UNION */
#define PMIC_HRST_REG14_ADDR(base)                ((base) + (0x199))

/* �Ĵ���˵����DEBUG�Ĵ���
   λ����UNION�ṹ:  PMIC_DEBUG_CTRL_UNION */
#define PMIC_DEBUG_CTRL_ADDR(base)                ((base) + (0x19A))

/* �Ĵ���˵��������ϵͳdebugԤ���Ĵ���0��
   λ����UNION�ṹ:  PMIC_SYS_DEBUG0_UNION */
#define PMIC_SYS_DEBUG0_ADDR(base)                ((base) + (0x19B))

/* �Ĵ���˵��������ϵͳdebugԤ���Ĵ���1��
   λ����UNION�ṹ:  PMIC_SYS_DEBUG1_UNION */
#define PMIC_SYS_DEBUG1_ADDR(base)                ((base) + (0x19C))

/* �Ĵ���˵����debug�Ĵ���д���ο��ƼĴ�����
   λ����UNION�ṹ:  PMIC_DEBUG_LOCK_UNION */
#define PMIC_DEBUG_LOCK_ADDR(base)                ((base) + (0x19D))

/* �Ĵ���˵����DAC0 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC0_DIN_MSB_UNION */
#define PMIC_DAC0_DIN_MSB_ADDR(base)              ((base) + (0x19F))

/* �Ĵ���˵����DAC0 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC0_DIN_LSB_UNION */
#define PMIC_DAC0_DIN_LSB_ADDR(base)              ((base) + (0x1A0))

/* �Ĵ���˵����DAC1 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC1_DIN_MSB_UNION */
#define PMIC_DAC1_DIN_MSB_ADDR(base)              ((base) + (0x1A1))

/* �Ĵ���˵����DAC1 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC1_DIN_LSB_UNION */
#define PMIC_DAC1_DIN_LSB_ADDR(base)              ((base) + (0x1A2))



/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/* �Ĵ���˵�����жϼĴ���0��
   λ����UNION�ṹ:  PMIC_IRQ0_UNION */
#define PMIC_IRQ0_ADDR(base)                      ((base) + (0x1B0))

/* �Ĵ���˵�����жϼĴ���1��
   λ����UNION�ṹ:  PMIC_IRQ1_UNION */
#define PMIC_IRQ1_ADDR(base)                      ((base) + (0x1B1))

/* �Ĵ���˵����OCP�жϼĴ���0��
   λ����UNION�ṹ:  PMIC_OCP_IRQ0_UNION */
#define PMIC_OCP_IRQ0_ADDR(base)                  ((base) + (0x1B2))

/* �Ĵ���˵����OCP�жϼĴ���1��
   λ����UNION�ṹ:  PMIC_OCP_IRQ1_UNION */
#define PMIC_OCP_IRQ1_ADDR(base)                  ((base) + (0x1B3))

/* �Ĵ���˵����OCP�жϼĴ���3��
   λ����UNION�ṹ:  PMIC_OCP_IRQ2_UNION */
#define PMIC_OCP_IRQ2_ADDR(base)                  ((base) + (0x1B4))

/* �Ĵ���˵����OCP�жϼĴ���4��
   λ����UNION�ṹ:  PMIC_OCP_IRQ3_UNION */
#define PMIC_OCP_IRQ3_ADDR(base)                  ((base) + (0x1B5))

/* �Ĵ���˵����OCP�жϼĴ���5��
   λ����UNION�ṹ:  PMIC_OCP_IRQ4_UNION */
#define PMIC_OCP_IRQ4_ADDR(base)                  ((base) + (0x1B6))

/* �Ĵ���˵����OCP�жϼĴ���6��
   λ����UNION�ṹ:  PMIC_OCP_IRQ5_UNION */
#define PMIC_OCP_IRQ5_ADDR(base)                  ((base) + (0x1B7))

/* �Ĵ���˵����BUKC0-3��LDO0-3 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP0_UNION */
#define PMIC_NP_OCP0_ADDR(base)                   ((base) + (0x1B8))

/* �Ĵ���˵����LDO4-12 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP1_UNION */
#define PMIC_NP_OCP1_ADDR(base)                   ((base) + (0x1B9))

/* �Ĵ���˵����LDO12-20 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP2_UNION */
#define PMIC_NP_OCP2_ADDR(base)                   ((base) + (0x1BA))

/* �Ĵ���˵����LDO21-28 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP3_UNION */
#define PMIC_NP_OCP3_ADDR(base)                   ((base) + (0x1BB))

/* �Ĵ���˵����LDO31-34 CLASSD OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP4_UNION */
#define PMIC_NP_OCP4_ADDR(base)                   ((base) + (0x1BC))

/* �Ĵ���˵����BUCK0-3 SCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_SCP_UNION */
#define PMIC_NP_SCP_ADDR(base)                    ((base) + (0x1BD))

/* �Ĵ���˵�����¼���¼�Ĵ���0��
   λ����UNION�ṹ:  PMIC_NP_RECORD0_UNION */
#define PMIC_NP_RECORD0_ADDR(base)                ((base) + (0x1BE))

/* �Ĵ���˵�����¼���¼�Ĵ���1��
   λ����UNION�ṹ:  PMIC_NP_RECORD1_UNION */
#define PMIC_NP_RECORD1_ADDR(base)                ((base) + (0x1BF))

/* �Ĵ���˵�����¼���¼�Ĵ���2��
   λ����UNION�ṹ:  PMIC_NP_RECORD2_UNION */
#define PMIC_NP_RECORD2_ADDR(base)                ((base) + (0x1C0))

/* �Ĵ���˵�����¼���¼�Ĵ���3��
   λ����UNION�ṹ:  PMIC_NP_RECORD3_UNION */
#define PMIC_NP_RECORD3_ADDR(base)                ((base) + (0x1C1))



/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCDR0_UNION */
#define PMIC_RTCDR0_ADDR(base)                    ((base) + (0x1D0))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCDR1_UNION */
#define PMIC_RTCDR1_ADDR(base)                    ((base) + (0x1D1))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCDR2_UNION */
#define PMIC_RTCDR2_ADDR(base)                    ((base) + (0x1D2))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCDR3_UNION */
#define PMIC_RTCDR3_ADDR(base)                    ((base) + (0x1D3))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCMR0_UNION */
#define PMIC_RTCMR0_ADDR(base)                    ((base) + (0x1D4))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCMR1_UNION */
#define PMIC_RTCMR1_ADDR(base)                    ((base) + (0x1D5))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCMR2_UNION */
#define PMIC_RTCMR2_ADDR(base)                    ((base) + (0x1D6))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCMR3_UNION */
#define PMIC_RTCMR3_ADDR(base)                    ((base) + (0x1D7))

/* �Ĵ���˵����RTC���ؼĴ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCLR0_UNION */
#define PMIC_RTCLR0_ADDR(base)                    ((base) + (0x1D8))

/* �Ĵ���˵����RTC���ؼĴ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCLR1_UNION */
#define PMIC_RTCLR1_ADDR(base)                    ((base) + (0x1D9))

/* �Ĵ���˵����RTC���ؼĴ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCLR2_UNION */
#define PMIC_RTCLR2_ADDR(base)                    ((base) + (0x1DA))

/* �Ĵ���˵����RTC���ؼĴ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCLR3_UNION */
#define PMIC_RTCLR3_ADDR(base)                    ((base) + (0x1DB))

/* �Ĵ���˵����RTC���ƼĴ�����
   λ����UNION�ṹ:  PMIC_RTCCTRL_UNION */
#define PMIC_RTCCTRL_ADDR(base)                   ((base) + (0x1DC))

/* �Ĵ���˵����XO_THRESOLD[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_XO_THRESOLD0_UNION */
#define PMIC_XO_THRESOLD0_ADDR(base)              ((base) + (0x1DD))

/* �Ĵ���˵����XO_THRESOLD[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_XO_THRESOLD1_UNION */
#define PMIC_XO_THRESOLD1_ADDR(base)              ((base) + (0x1DE))

/* �Ĵ���˵����CRC_VALUE[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE0_UNION */
#define PMIC_CRC_VAULE0_ADDR(base)                ((base) + (0x1DF))

/* �Ĵ���˵����CRC_VALUE[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE1_UNION */
#define PMIC_CRC_VAULE1_ADDR(base)                ((base) + (0x1E0))

/* �Ĵ���˵����CRC_VALUE[20:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE2_UNION */
#define PMIC_CRC_VAULE2_ADDR(base)                ((base) + (0x1E1))

/* �Ĵ���˵����RTC�ϵ�����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER0_UNION */
#define PMIC_RTC_PWRUP_TIMER0_ADDR(base)          ((base) + (0x1E2))

/* �Ĵ���˵����RTC�ϵ�����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER1_UNION */
#define PMIC_RTC_PWRUP_TIMER1_ADDR(base)          ((base) + (0x1E3))

/* �Ĵ���˵����RTC�ϵ�����[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER2_UNION */
#define PMIC_RTC_PWRUP_TIMER2_ADDR(base)          ((base) + (0x1E4))

/* �Ĵ���˵����RTC�ϵ�����[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER3_UNION */
#define PMIC_RTC_PWRUP_TIMER3_ADDR(base)          ((base) + (0x1E5))

/* �Ĵ���˵����RTC�µ�����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER0_UNION */
#define PMIC_RTC_PWRDOWN_TIMER0_ADDR(base)        ((base) + (0x1E6))

/* �Ĵ���˵����RTC�µ�����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER1_UNION */
#define PMIC_RTC_PWRDOWN_TIMER1_ADDR(base)        ((base) + (0x1E7))

/* �Ĵ���˵����RTC�µ�����[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER2_UNION */
#define PMIC_RTC_PWRDOWN_TIMER2_ADDR(base)        ((base) + (0x1E8))

/* �Ĵ���˵����RTC�µ�����[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER3_UNION */
#define PMIC_RTC_PWRDOWN_TIMER3_ADDR(base)        ((base) + (0x1E9))



/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/* �Ĵ���˵�������ؼ��жϼĴ�����
   λ����UNION�ṹ:  PMIC_COUL_IRQ_UNION */
#define PMIC_COUL_IRQ_ADDR(base)                  ((base) + (0x1F0))

/* �Ĵ���˵�������ؼ��ж����μĴ�����
   λ����UNION�ṹ:  PMIC_COUL_IRQ_MASK_UNION */
#define PMIC_COUL_IRQ_MASK_ADDR(base)             ((base) + (0x1F1))

/* �Ĵ���˵������ǰ����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT_0_UNION */
#define PMIC_CURRENT_0_ADDR(base)                 ((base) + (0x1F2))

/* �Ĵ���˵������ǰ����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT_1_UNION */
#define PMIC_CURRENT_1_ADDR(base)                 ((base) + (0x1F3))

/* �Ĵ���˵������ǰ��ѹ[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT_0_UNION */
#define PMIC_V_OUT_0_ADDR(base)                   ((base) + (0x1F4))

/* �Ĵ���˵������ǰ��ѹ[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT_1_UNION */
#define PMIC_V_OUT_1_ADDR(base)                   ((base) + (0x1F5))

/* �Ĵ���˵�������ؼƿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_CLJ_CTRL_REG_UNION */
#define PMIC_CLJ_CTRL_REG_ADDR(base)              ((base) + (0x1F6))

/* �Ĵ���˵����ECO_REFLASH����ʱ��Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_REFALSH_TIME_UNION */
#define PMIC_ECO_REFALSH_TIME_ADDR(base)          ((base) + (0x1F7))

/* �Ĵ���˵����cl_out[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT0_UNION */
#define PMIC_CL_OUT0_ADDR(base)                   ((base) + (0x1F8))

/* �Ĵ���˵����cl_out[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT1_UNION */
#define PMIC_CL_OUT1_ADDR(base)                   ((base) + (0x1F9))

/* �Ĵ���˵����cl_out[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT2_UNION */
#define PMIC_CL_OUT2_ADDR(base)                   ((base) + (0x1FA))

/* �Ĵ���˵����cl_out[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT3_UNION */
#define PMIC_CL_OUT3_ADDR(base)                   ((base) + (0x1FB))

/* �Ĵ���˵����cl_in[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN0_UNION */
#define PMIC_CL_IN0_ADDR(base)                    ((base) + (0x1FC))

/* �Ĵ���˵����cl_in[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN1_UNION */
#define PMIC_CL_IN1_ADDR(base)                    ((base) + (0x1FD))

/* �Ĵ���˵����cl_in[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN2_UNION */
#define PMIC_CL_IN2_ADDR(base)                    ((base) + (0x1FE))

/* �Ĵ���˵����cl_in[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN3_UNION */
#define PMIC_CL_IN3_ADDR(base)                    ((base) + (0x1FF))

/* �Ĵ���˵����chg_timer[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER0_UNION */
#define PMIC_CHG_TIMER0_ADDR(base)                ((base) + (0x200))

/* �Ĵ���˵����chg_timer[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER1_UNION */
#define PMIC_CHG_TIMER1_ADDR(base)                ((base) + (0x201))

/* �Ĵ���˵����chg_timer[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER2_UNION */
#define PMIC_CHG_TIMER2_ADDR(base)                ((base) + (0x202))

/* �Ĵ���˵����chg_timer[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER3_UNION */
#define PMIC_CHG_TIMER3_ADDR(base)                ((base) + (0x203))

/* �Ĵ���˵����load_timer[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER0_UNION */
#define PMIC_LOAD_TIMER0_ADDR(base)               ((base) + (0x204))

/* �Ĵ���˵����load_timer[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER1_UNION */
#define PMIC_LOAD_TIMER1_ADDR(base)               ((base) + (0x205))

/* �Ĵ���˵����load_timer[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER2_UNION */
#define PMIC_LOAD_TIMER2_ADDR(base)               ((base) + (0x206))

/* �Ĵ���˵����load_timer[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER3_UNION */
#define PMIC_LOAD_TIMER3_ADDR(base)               ((base) + (0x207))

/* �Ĵ���˵����cl_int[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT0_UNION */
#define PMIC_CL_INT0_ADDR(base)                   ((base) + (0x208))

/* �Ĵ���˵����cl_int[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT1_UNION */
#define PMIC_CL_INT1_ADDR(base)                   ((base) + (0x209))

/* �Ĵ���˵����cl_int[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT2_UNION */
#define PMIC_CL_INT2_ADDR(base)                   ((base) + (0x20A))

/* �Ĵ���˵����cl_int[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT3_UNION */
#define PMIC_CL_INT3_ADDR(base)                   ((base) + (0x20B))

/* �Ĵ���˵����v_int[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_INT0_UNION */
#define PMIC_V_INT0_ADDR(base)                    ((base) + (0x20C))

/* �Ĵ���˵����v_int[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_INT1_UNION */
#define PMIC_V_INT1_ADDR(base)                    ((base) + (0x20D))

/* �Ĵ���˵����offset_current[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT0_UNION */
#define PMIC_OFFSET_CURRENT0_ADDR(base)           ((base) + (0x20E))

/* �Ĵ���˵����offset_current[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT1_UNION */
#define PMIC_OFFSET_CURRENT1_ADDR(base)           ((base) + (0x20F))

/* �Ĵ���˵����offset_voltage[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE0_UNION */
#define PMIC_OFFSET_VOLTAGE0_ADDR(base)           ((base) + (0x210))

/* �Ĵ���˵����offset_voltage[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE1_UNION */
#define PMIC_OFFSET_VOLTAGE1_ADDR(base)           ((base) + (0x211))

/* �Ĵ���˵����v_ocv_data[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_VOLTAGE0_UNION */
#define PMIC_OCV_VOLTAGE0_ADDR(base)              ((base) + (0x212))

/* �Ĵ���˵����v_ocv_data[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_VOLTAGE1_UNION */
#define PMIC_OCV_VOLTAGE1_ADDR(base)              ((base) + (0x213))

/* �Ĵ���˵����i_ocv_data[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_CURRENT0_UNION */
#define PMIC_OCV_CURRENT0_ADDR(base)              ((base) + (0x214))

/* �Ĵ���˵����i_ocv_data[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_CURRENT1_UNION */
#define PMIC_OCV_CURRENT1_ADDR(base)              ((base) + (0x215))

/* �Ĵ���˵����eco_out_clin[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_0_UNION */
#define PMIC_ECO_OUT_CLIN_0_ADDR(base)            ((base) + (0x216))

/* �Ĵ���˵����eco_out_clin[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_1_UNION */
#define PMIC_ECO_OUT_CLIN_1_ADDR(base)            ((base) + (0x217))

/* �Ĵ���˵����eco_out_clin[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_2_UNION */
#define PMIC_ECO_OUT_CLIN_2_ADDR(base)            ((base) + (0x218))

/* �Ĵ���˵����eco_out_clin[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_3_UNION */
#define PMIC_ECO_OUT_CLIN_3_ADDR(base)            ((base) + (0x219))

/* �Ĵ���˵����eco_out_clout[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_0_UNION */
#define PMIC_ECO_OUT_CLOUT_0_ADDR(base)           ((base) + (0x21A))

/* �Ĵ���˵����eco_out_clout[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_1_UNION */
#define PMIC_ECO_OUT_CLOUT_1_ADDR(base)           ((base) + (0x21B))

/* �Ĵ���˵����eco_out_clout[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_2_UNION */
#define PMIC_ECO_OUT_CLOUT_2_ADDR(base)           ((base) + (0x21C))

/* �Ĵ���˵����eco_out_clout[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_3_UNION */
#define PMIC_ECO_OUT_CLOUT_3_ADDR(base)           ((base) + (0x21D))

/* �Ĵ���˵����v_out_pre0[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE0_UNION */
#define PMIC_V_OUT0_PRE0_ADDR(base)               ((base) + (0x21E))

/* �Ĵ���˵����v_out_pre0[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE0_UNION */
#define PMIC_V_OUT1_PRE0_ADDR(base)               ((base) + (0x21F))

/* �Ĵ���˵����v_out_pre1[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE1_UNION */
#define PMIC_V_OUT0_PRE1_ADDR(base)               ((base) + (0x220))

/* �Ĵ���˵����v_out_pre1[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE1_UNION */
#define PMIC_V_OUT1_PRE1_ADDR(base)               ((base) + (0x221))

/* �Ĵ���˵����v_out_pre2[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE2_UNION */
#define PMIC_V_OUT0_PRE2_ADDR(base)               ((base) + (0x222))

/* �Ĵ���˵����v_out_pre2[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE2_UNION */
#define PMIC_V_OUT1_PRE2_ADDR(base)               ((base) + (0x223))

/* �Ĵ���˵����v_out_pre3[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE3_UNION */
#define PMIC_V_OUT0_PRE3_ADDR(base)               ((base) + (0x224))

/* �Ĵ���˵����v_out_pre3[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE3_UNION */
#define PMIC_V_OUT1_PRE3_ADDR(base)               ((base) + (0x225))

/* �Ĵ���˵����v_out_pre4[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE4_UNION */
#define PMIC_V_OUT0_PRE4_ADDR(base)               ((base) + (0x226))

/* �Ĵ���˵����v_out_pre4[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE4_UNION */
#define PMIC_V_OUT1_PRE4_ADDR(base)               ((base) + (0x227))

/* �Ĵ���˵����v_out_pre5[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE5_UNION */
#define PMIC_V_OUT0_PRE5_ADDR(base)               ((base) + (0x228))

/* �Ĵ���˵����v_out_pre5[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE5_UNION */
#define PMIC_V_OUT1_PRE5_ADDR(base)               ((base) + (0x229))

/* �Ĵ���˵����v_out_pre6[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE6_UNION */
#define PMIC_V_OUT0_PRE6_ADDR(base)               ((base) + (0x22A))

/* �Ĵ���˵����v_out_pre6[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE6_UNION */
#define PMIC_V_OUT1_PRE6_ADDR(base)               ((base) + (0x22B))

/* �Ĵ���˵����v_out_pre7[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE7_UNION */
#define PMIC_V_OUT0_PRE7_ADDR(base)               ((base) + (0x22C))

/* �Ĵ���˵����v_out_pre7[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE7_UNION */
#define PMIC_V_OUT1_PRE7_ADDR(base)               ((base) + (0x22D))

/* �Ĵ���˵����v_out_pre8[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE8_UNION */
#define PMIC_V_OUT0_PRE8_ADDR(base)               ((base) + (0x22E))

/* �Ĵ���˵����v_out_pre8[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE8_UNION */
#define PMIC_V_OUT1_PRE8_ADDR(base)               ((base) + (0x22F))

/* �Ĵ���˵����v_out_pre9[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE9_UNION */
#define PMIC_V_OUT0_PRE9_ADDR(base)               ((base) + (0x230))

/* �Ĵ���˵����v_out_pre9[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE9_UNION */
#define PMIC_V_OUT1_PRE9_ADDR(base)               ((base) + (0x231))

/* �Ĵ���˵����current_pre0[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE0_UNION */
#define PMIC_CURRENT0_PRE0_ADDR(base)             ((base) + (0x232))

/* �Ĵ���˵����current_pre0[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE0_UNION */
#define PMIC_CURRENT1_PRE0_ADDR(base)             ((base) + (0x233))

/* �Ĵ���˵����current_pre1[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE1_UNION */
#define PMIC_CURRENT0_PRE1_ADDR(base)             ((base) + (0x234))

/* �Ĵ���˵����current_pre1[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE1_UNION */
#define PMIC_CURRENT1_PRE1_ADDR(base)             ((base) + (0x235))

/* �Ĵ���˵����current_pre2[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE2_UNION */
#define PMIC_CURRENT0_PRE2_ADDR(base)             ((base) + (0x236))

/* �Ĵ���˵����current_pre2[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE2_UNION */
#define PMIC_CURRENT1_PRE2_ADDR(base)             ((base) + (0x237))

/* �Ĵ���˵����current_pre3[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE3_UNION */
#define PMIC_CURRENT0_PRE3_ADDR(base)             ((base) + (0x238))

/* �Ĵ���˵����current_pre3[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE3_UNION */
#define PMIC_CURRENT1_PRE3_ADDR(base)             ((base) + (0x239))

/* �Ĵ���˵����current_pre4[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE4_UNION */
#define PMIC_CURRENT0_PRE4_ADDR(base)             ((base) + (0x23A))

/* �Ĵ���˵����current_pre4[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE4_UNION */
#define PMIC_CURRENT1_PRE4_ADDR(base)             ((base) + (0x23B))

/* �Ĵ���˵����current_pre5[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE5_UNION */
#define PMIC_CURRENT0_PRE5_ADDR(base)             ((base) + (0x23C))

/* �Ĵ���˵����current_pre5[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE5_UNION */
#define PMIC_CURRENT1_PRE5_ADDR(base)             ((base) + (0x23D))

/* �Ĵ���˵����current_pre6[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE6_UNION */
#define PMIC_CURRENT0_PRE6_ADDR(base)             ((base) + (0x23E))

/* �Ĵ���˵����current_pre6[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE6_UNION */
#define PMIC_CURRENT1_PRE6_ADDR(base)             ((base) + (0x23F))

/* �Ĵ���˵����current_pre7[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE7_UNION */
#define PMIC_CURRENT0_PRE7_ADDR(base)             ((base) + (0x240))

/* �Ĵ���˵����current_pre7[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE7_UNION */
#define PMIC_CURRENT1_PRE7_ADDR(base)             ((base) + (0x241))

/* �Ĵ���˵����current_pre8[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE8_UNION */
#define PMIC_CURRENT0_PRE8_ADDR(base)             ((base) + (0x242))

/* �Ĵ���˵����current_pre8[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE8_UNION */
#define PMIC_CURRENT1_PRE8_ADDR(base)             ((base) + (0x243))

/* �Ĵ���˵����current_pre9[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE9_UNION */
#define PMIC_CURRENT0_PRE9_ADDR(base)             ((base) + (0x244))

/* �Ĵ���˵����current_pre9[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE9_UNION */
#define PMIC_CURRENT1_PRE9_ADDR(base)             ((base) + (0x245))

/* �Ĵ���˵��������ƫ�õ���[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT_MOD_0_UNION */
#define PMIC_OFFSET_CURRENT_MOD_0_ADDR(base)      ((base) + (0x246))

/* �Ĵ���˵��������ƫ�õ���[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT_MOD_1_UNION */
#define PMIC_OFFSET_CURRENT_MOD_1_ADDR(base)      ((base) + (0x247))

/* �Ĵ���˵������ѹƫ�õ���[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE_MOD_0_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_0_ADDR(base)      ((base) + (0x248))

/* �Ĵ���˵������ѹƫ�õ���[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE_MOD_1_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_1_ADDR(base)      ((base) + (0x249))

/* �Ĵ���˵�������ؼ�ģ�Ᵽ��0�Ĵ���
   λ����UNION�ṹ:  PMIC_COUL_RESERVE0_UNION */
#define PMIC_COUL_RESERVE0_ADDR(base)             ((base) + (0x24A))

/* �Ĵ���˵�������ؼƱ���0�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED0_UNION */
#define PMIC_CLJ_RESERVED0_ADDR(base)             ((base) + (0x24B))

/* �Ĵ���˵�������ؼƱ���1�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED1_UNION */
#define PMIC_CLJ_RESERVED1_ADDR(base)             ((base) + (0x24C))

/* �Ĵ���˵�������ؼƱ���2�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED2_UNION */
#define PMIC_CLJ_RESERVED2_ADDR(base)             ((base) + (0x24D))

/* �Ĵ���˵����PMU��λ�Ĵ�����
   λ����UNION�ṹ:  PMIC_PMU_SOFT_RST_UNION */
#define PMIC_PMU_SOFT_RST_ADDR(base)              ((base) + (0x24E))

/* �Ĵ���˵�������ؼ�DEBUGר��1�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_DEBUG_UNION */
#define PMIC_CLJ_DEBUG_ADDR(base)                 ((base) + (0x24F))

/* �Ĵ���˵�������ؼ�DEBUGר��2�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_DEBUG_2_UNION */
#define PMIC_CLJ_DEBUG_2_ADDR(base)               ((base) + (0x250))

/* �Ĵ���˵�������ؼ�DEBUGר��3�Ĵ�����
   λ����UNION�ṹ:  PMIC_STATE_TEST_UNION */
#define PMIC_STATE_TEST_ADDR(base)                ((base) + (0x251))

/* �Ĵ���˵�������ؼƿ��ƼĴ���2
   λ����UNION�ṹ:  PMIC_CLJ_CTRL_REGS2_UNION */
#define PMIC_CLJ_CTRL_REGS2_ADDR(base)            ((base) + (0x252))

/* �Ĵ���˵����DEBUG�Ĵ���д������
   λ����UNION�ṹ:  PMIC_DEBUG_WRITE_PRO_UNION */
#define PMIC_DEBUG_WRITE_PRO_ADDR(base)           ((base) + (0x253))



/****************************************************************************
                     (5/5) PMU_CODEC
 ****************************************************************************/
/* �Ĵ���˵����ʱ��ʹ�����üĴ�����
   λ����UNION�ṹ:  PMIC_CLK_EN_CFG_UNION */
#define PMIC_CLK_EN_CFG_ADDR(base)                ((base) + (0x260))

/* �Ĵ���˵������ģ�ӿ�ʱ����ѡ��
   λ����UNION�ṹ:  PMIC_CLK_EDGE_CFG_UNION */
#define PMIC_CLK_EDGE_CFG_ADDR(base)              ((base) + (0x261))

/* �Ĵ���˵�������ؿ��ơ�
   λ����UNION�ṹ:  PMIC_LOOPBACK_CFG_UNION */
#define PMIC_LOOPBACK_CFG_ADDR(base)              ((base) + (0x262))

/* �Ĵ���˵����ģ���ж�ԭʼ״̬�Ĵ�����
   λ����UNION�ṹ:  PMIC_ANA_IRQ_SIG_STAT_UNION */
#define PMIC_ANA_IRQ_SIG_STAT_ADDR(base)          ((base) + (0x263))

/* �Ĵ���˵����ANA_IRQ_REG�ж����μĴ�����
   λ����UNION�ṹ:  PMIC_ANA_IRQM_REG0_UNION */
#define PMIC_ANA_IRQM_REG0_ADDR(base)             ((base) + (0x264))

/* �Ĵ���˵����ģ���жϼĴ�����0��д1�壬���ϱ��ж���Ϣ��
   λ����UNION�ṹ:  PMIC_ANA_IRQ_REG0_UNION */
#define PMIC_ANA_IRQ_REG0_ADDR(base)              ((base) + (0x265))

/* �Ĵ���˵����hs_det_irqȥ�����á�
   λ����UNION�ṹ:  PMIC_DEB_CNT_HS_DET_CFG_UNION */
#define PMIC_DEB_CNT_HS_DET_CFG_ADDR(base)        ((base) + (0x266))

/* �Ĵ���˵����hs_mic_irqȥ�����á�
   λ����UNION�ṹ:  PMIC_DEB_CNT_HS_MIC_CFG_UNION */
#define PMIC_DEB_CNT_HS_MIC_CFG_ADDR(base)        ((base) + (0x267))

/* �Ĵ���˵����reserved��
   λ����UNION�ṹ:  PMIC_CODEC_DIG_RES02_UNION */
#define PMIC_CODEC_DIG_RES02_ADDR(base)           ((base) + (0x268))

/* �Ĵ���˵����reserved��
   λ����UNION�ṹ:  PMIC_CODEC_DIG_RES03_UNION */
#define PMIC_CODEC_DIG_RES03_ADDR(base)           ((base) + (0x269))

/* �Ĵ���˵����ADCͨ·PD�źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW01_UNION */
#define PMIC_CODEC_ANA_RW01_ADDR(base)            ((base) + (0x26A))

/* �Ĵ���˵����MICBIAS,MBHD�źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW02_UNION */
#define PMIC_CODEC_ANA_RW02_ADDR(base)            ((base) + (0x26B))

/* �Ĵ���˵����Headphone��MIXEROUT��PD�źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW03_UNION */
#define PMIC_CODEC_ANA_RW03_ADDR(base)            ((base) + (0x26C))

/* �Ĵ���˵����VREF����ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW04_UNION */
#define PMIC_CODEC_ANA_RW04_ADDR(base)            ((base) + (0x26D))

/* �Ĵ���˵����LINEPGALͨ·ѡ����������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW05_UNION */
#define PMIC_CODEC_ANA_RW05_ADDR(base)            ((base) + (0x26E))

/* �Ĵ���˵����LINEPGARͨ·ѡ��������ƿ����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW06_UNION */
#define PMIC_CODEC_ANA_RW06_ADDR(base)            ((base) + (0x26F))

/* �Ĵ���˵����AUXPGARͨ·ѡ��������ƿ����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW07_UNION */
#define PMIC_CODEC_ANA_RW07_ADDR(base)            ((base) + (0x270))

/* �Ĵ���˵����MAINPGARͨ·ѡ��������ƿ����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW08_UNION */
#define PMIC_CODEC_ANA_RW08_ADDR(base)            ((base) + (0x271))

/* �Ĵ���˵����ADCR_MIXINͨ·ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW09_UNION */
#define PMIC_CODEC_ANA_RW09_ADDR(base)            ((base) + (0x272))

/* �Ĵ���˵����ADCL_MIXINͨ·ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW10_UNION */
#define PMIC_CODEC_ANA_RW10_ADDR(base)            ((base) + (0x273))

/* �Ĵ���˵����ADCLʱ������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW11_UNION */
#define PMIC_CODEC_ANA_RW11_ADDR(base)            ((base) + (0x274))

/* �Ĵ���˵����ADCRʱ������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW12_UNION */
#define PMIC_CODEC_ANA_RW12_ADDR(base)            ((base) + (0x275))

/* �Ĵ���˵����MIXOUT_HSL��MIXOUT_HSRͨ·ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW13_UNION */
#define PMIC_CODEC_ANA_RW13_ADDR(base)            ((base) + (0x276))

/* �Ĵ���˵����MIXOUT_EARͨ·ѡ���źš�������ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW14_UNION */
#define PMIC_CODEC_ANA_RW14_ADDR(base)            ((base) + (0x277))

/* �Ĵ���˵����DACICELL���������źš���ChargePump����ʱ������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW15_UNION */
#define PMIC_CODEC_ANA_RW15_ADDR(base)            ((base) + (0x278))

/* �Ĵ���˵����Headphonesoftʹ���źš���ChargePump�����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW16_UNION */
#define PMIC_CODEC_ANA_RW16_ADDR(base)            ((base) + (0x279))

/* �Ĵ���˵����HeadphoneL��������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW17_UNION */
#define PMIC_CODEC_ANA_RW17_ADDR(base)            ((base) + (0x27A))

/* �Ĵ���˵����HeadphonR��������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW18_UNION */
#define PMIC_CODEC_ANA_RW18_ADDR(base)            ((base) + (0x27B))

/* �Ĵ���˵����Earphone��������źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW19_UNION */
#define PMIC_CODEC_ANA_RW19_ADDR(base)            ((base) + (0x27C))

/* �Ĵ���˵����POP����ʱ�����źš���ramp������·�����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW20_UNION */
#define PMIC_CODEC_ANA_RW20_ADDR(base)            ((base) + (0x27D))

/* �Ĵ���˵������POP��·�����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW21_UNION */
#define PMIC_CODEC_ANA_RW21_ADDR(base)            ((base) + (0x27E))

/* �Ĵ���˵����HSMICBIAS��MICBIAS1���ƫ�õ�ѹ�����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW22_UNION */
#define PMIC_CODEC_ANA_RW22_ADDR(base)            ((base) + (0x27F))

/* �Ĵ���˵����HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1�ŵ�ʹ���źš���MBHDʹ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW23_UNION */
#define PMIC_CODEC_ANA_RW23_ADDR(base)            ((base) + (0x280))

/* �Ĵ���˵����MBHD_VREF_CTRL[7:0]��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW24_UNION */
#define PMIC_CODEC_ANA_RW24_ADDR(base)            ((base) + (0x281))

/* �Ĵ���˵����CP_CLK_CTRL[7:0]��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW25_UNION */
#define PMIC_CODEC_ANA_RW25_ADDR(base)            ((base) + (0x282))

/* �Ĵ���˵����ADC��DACʱ����ѡ���źš���ADC��DACchopperʱ��ѡ���źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW26_UNION */
#define PMIC_CODEC_ANA_RW26_ADDR(base)            ((base) + (0x283))

/* �Ĵ���˵����RX��ADC_SDM,LINEIN,MICPGA,CTCM��chopperbaypass�źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW27_UNION */
#define PMIC_CODEC_ANA_RW27_ADDR(base)            ((base) + (0x284))

/* �Ĵ���˵����TX��DAC��MIXER_EAR,MIXER_HP��chopperbaypass�źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW28_UNION */
#define PMIC_CODEC_ANA_RW28_ADDR(base)            ((base) + (0x285))

/* �Ĵ���˵����CODEC_IBIAS_ADJ1��HeadphoneMIXER_HP���������źš���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW29_UNION */
#define PMIC_CODEC_ANA_RW29_ADDR(base)            ((base) + (0x286))

/* �Ĵ���˵����CODEC_IBIAS_ADJ2��DAC��ADC_OPA1���������źš���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW30_UNION */
#define PMIC_CODEC_ANA_RW30_ADDR(base)            ((base) + (0x287))

/* �Ĵ���˵����CODEC_IBIAS_ADJ3��ADC_OPA2��ADC_COMP���������źš���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW31_UNION */
#define PMIC_CODEC_ANA_RW31_ADDR(base)            ((base) + (0x288))

/* �Ĵ���˵����CODEC_IBIAS_ADJ4��LINEIN��MICBIAS���������źš���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW32_UNION */
#define PMIC_CODEC_ANA_RW32_ADDR(base)            ((base) + (0x289))

/* �Ĵ���˵����CODEC_IBIAS_ADJ5��reserved��AUXMIC���������źţ���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW33_UNION */
#define PMIC_CODEC_ANA_RW33_ADDR(base)            ((base) + (0x28A))

/* �Ĵ���˵����CODEC_IBIAS_ADJ6��MAINMIC��MIXER_EAR���������źš���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW34_UNION */
#define PMIC_CODEC_ANA_RW34_ADDR(base)            ((base) + (0x28B))

/* �Ĵ���˵����CODEC_IBIAS_ADJ7��EAR��CODECȫ�ֵ��������źţ���
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW35_UNION */
#define PMIC_CODEC_ANA_RW35_ADDR(base)            ((base) + (0x28C))

/* �Ĵ���˵����ADC_DACģ�⻷�ؿ����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW36_UNION */
#define PMIC_CODEC_ANA_RW36_ADDR(base)            ((base) + (0x28D))

/* �Ĵ���˵����HP_BIAS_PD ��CP_PD��CP_DET_PD�����źš�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW37_UNION */
#define PMIC_CODEC_ANA_RW37_ADDR(base)            ((base) + (0x28E))

/* �Ĵ���˵����DACL_PD��DACR_PD��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW38_UNION */
#define PMIC_CODEC_ANA_RW38_ADDR(base)            ((base) + (0x28F))

/* �Ĵ���˵����MIXOUT_EAR_PD��EAR_PD��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW39_UNION */
#define PMIC_CODEC_ANA_RW39_ADDR(base)            ((base) + (0x290))

/* �Ĵ���˵����CODEC_ANA_RW40��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW40_UNION */
#define PMIC_CODEC_ANA_RW40_ADDR(base)            ((base) + (0x291))

/* �Ĵ���˵����CODEC_ANA_RO01��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RO01_UNION */
#define PMIC_CODEC_ANA_RO01_ADDR(base)            ((base) + (0x292))

/* �Ĵ���˵����CODEC_ANA_RO02��
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RO02_UNION */
#define PMIC_CODEC_ANA_RO02_ADDR(base)            ((base) + (0x293))

/* �Ĵ���˵����OSC_BAK�����ź�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW41_UNION */
#define PMIC_CODEC_ANA_RW41_ADDR(base)            ((base) + (0x294))

/* �Ĵ���˵����FMģʽ��ʱ���л�ѡ���ź�
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW42_UNION */
#define PMIC_CODEC_ANA_RW42_ADDR(base)            ((base) + (0x295))

/* �Ĵ���˵����CODEC_ANA_RW43
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW43_UNION */
#define PMIC_CODEC_ANA_RW43_ADDR(base)            ((base) + (0x296))

/* �Ĵ���˵����CODEC_ANA_RW44
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW44_UNION */
#define PMIC_CODEC_ANA_RW44_ADDR(base)            ((base) + (0x297))

/* �Ĵ���˵����CODEC_ANA_RW45
   λ����UNION�ṹ:  PMIC_CODEC_ANA_RW45_UNION */
#define PMIC_CODEC_ANA_RW45_ADDR(base)            ((base) + (0x298))





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
                     (1/5) PMU_CTRL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_VERSION0_UNION
 �ṹ˵��  : VERSION0 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x36�����:8
 �Ĵ���˵��: �汾�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num0 : 8;  /* bit[0-7]: ASIC��36��ʾ��Ŀ���6�� */
    } reg;
} PMIC_VERSION0_UNION;
#endif
#define PMIC_VERSION0_project_num0_START  (0)
#define PMIC_VERSION0_project_num0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION1_UNION
 �ṹ˵��  : VERSION1 �Ĵ����ṹ���塣��ַƫ����:0x001����ֵ:0x35�����:8
 �Ĵ���˵��: �汾�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num1 : 8;  /* bit[0-7]: ASIC��35��ʾ��Ŀ���5�� */
    } reg;
} PMIC_VERSION1_UNION;
#endif
#define PMIC_VERSION1_project_num1_START  (0)
#define PMIC_VERSION1_project_num1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION2_UNION
 �ṹ˵��  : VERSION2 �Ĵ����ṹ���塣��ַƫ����:0x002����ֵ:0x35�����:8
 �Ĵ���˵��: �汾�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num2 : 8;  /* bit[0-7]: ASIC��35��ʾ��Ŀ���5�� */
    } reg;
} PMIC_VERSION2_UNION;
#endif
#define PMIC_VERSION2_project_num2_START  (0)
#define PMIC_VERSION2_project_num2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION3_UNION
 �ṹ˵��  : VERSION3 �Ĵ����ṹ���塣��ַƫ����:0x003����ֵ:0x35�����:8
 �Ĵ���˵��: �汾�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num3 : 8;  /* bit[0-7]: ASIC��35��ʾ��Ŀ���5�� */
    } reg;
} PMIC_VERSION3_UNION;
#endif
#define PMIC_VERSION3_project_num3_START  (0)
#define PMIC_VERSION3_project_num3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION4_UNION
 �ṹ˵��  : VERSION4 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x01�����:8
 �Ĵ���˵��: �汾�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  version : 8;  /* bit[0-7]: ��ʾ�汾ΪV100��1�� */
    } reg;
} PMIC_VERSION4_UNION;
#endif
#define PMIC_VERSION4_version_START  (0)
#define PMIC_VERSION4_version_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION5_UNION
 �ṹ˵��  : VERSION5 �Ĵ����ṹ���塣��ַƫ����:0x005����ֵ:0x00�����:8
 �Ĵ���˵��: �汾�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id : 8;  /* bit[0-7]: ��ʾ�汾ΪV100��00�� */
    } reg;
} PMIC_VERSION5_UNION;
#endif
#define PMIC_VERSION5_chip_id_START  (0)
#define PMIC_VERSION5_chip_id_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_STATUS0_UNION
 �ṹ˵��  : STATUS0 �Ĵ����ṹ���塣��ַƫ����:0x006����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  st_vsys_ov_d200ur        : 1;  /* bit[0]: ��ѹ״ָ̬ʾλ(������ȥ��200us)��
                                                                 0��VSYS��ѹС��6V��
                                                                 1��VSYS��ѹ����6V�� */
        unsigned char  st_vbus_det_insert_d20m  : 1;  /* bit[1]: USB״ָ̬ʾλ(˫��ȥ��20ms)��
                                                                 0��USB���ڰγ�״̬��
                                                                 1��USB���ڲ���״̬�� */
        unsigned char  st_vsys_pwroff_abs       : 1;  /* bit[2]: ���Թػ���ѹ״̬λָʾλ��û��ͬ������
                                                                 0��VSYS��ѹ����2.3V��
                                                                 1��VSYS��ѹС��2.3V�� */
        unsigned char  st_vsys_pwroff_deb_d80mr : 1;  /* bit[3]: ȥ���ػ���ѹ״ָ̬ʾλ��������ȥ��80ms��ʱ����䣩��
                                                                 0��VSYS����2.6V(�ɼĴ�������Ϊ3.0V)��
                                                                 1��VSYSС��2.6V(�ɼĴ�������Ϊ3.0V)��
                                                                 ���üĴ����ڷ��µ����� */
        unsigned char  st_vsys_pwron_d60ur      : 1;  /* bit[4]: ������ѹ״ָ̬ʾλ��������ȥ��60us����
                                                                 0��VSYS����2.8V(�ɼĴ�������Ϊ3.2V)��
                                                                 1��VSYSС��2.8V(�ɼĴ�������Ϊ3.2V)��
                                                                 ���üĴ����ڷ��µ����� */
        unsigned char  st_thsd_otmp140_d1mr     : 1;  /* bit[5]: ����״̬λ(������ȥ��1ms)��
                                                                 0���¶�С��140�棻
                                                                 1�� �¶ȴ���140�档 */
        unsigned char  st_thsd_otmp125_d1mr     : 1;  /* bit[6]: ����״ָ̬ʾλ(������ȥ��1ms)��
                                                                 0���¶�С������ֵ��
                                                                 1���¶ȴ�������ֵ(��140�ػ�����)��
                                                                 �¶�����ֵ�μ�TH_CTRL[thsd_tmp_set]��Ĭ��125�档 */
        unsigned char  st_pwron_d20m            : 1;  /* bit[7]: ����״ָ̬ʾλ(˫��ȥ��20ms)��
                                                                 0������δ�����£�
                                                                 1�����������¡� */
    } reg;
} PMIC_STATUS0_UNION;
#endif
#define PMIC_STATUS0_st_vsys_ov_d200ur_START         (0)
#define PMIC_STATUS0_st_vsys_ov_d200ur_END           (0)
#define PMIC_STATUS0_st_vbus_det_insert_d20m_START   (1)
#define PMIC_STATUS0_st_vbus_det_insert_d20m_END     (1)
#define PMIC_STATUS0_st_vsys_pwroff_abs_START        (2)
#define PMIC_STATUS0_st_vsys_pwroff_abs_END          (2)
#define PMIC_STATUS0_st_vsys_pwroff_deb_d80mr_START  (3)
#define PMIC_STATUS0_st_vsys_pwroff_deb_d80mr_END    (3)
#define PMIC_STATUS0_st_vsys_pwron_d60ur_START       (4)
#define PMIC_STATUS0_st_vsys_pwron_d60ur_END         (4)
#define PMIC_STATUS0_st_thsd_otmp140_d1mr_START      (5)
#define PMIC_STATUS0_st_thsd_otmp140_d1mr_END        (5)
#define PMIC_STATUS0_st_thsd_otmp125_d1mr_START      (6)
#define PMIC_STATUS0_st_thsd_otmp125_d1mr_END        (6)
#define PMIC_STATUS0_st_pwron_d20m_START             (7)
#define PMIC_STATUS0_st_pwron_d20m_END               (7)


/*****************************************************************************
 �ṹ��    : PMIC_STATUS1_UNION
 �ṹ˵��  : STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x007����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  st_dcxo_clk_sel       : 1;  /* bit[0]: DCXOģʽ��ǰ����ʱ��Դ��
                                                              0��32K RC��
                                                              1��19.2MHz 586��Ƶʱ�ӡ� */
        unsigned char  st_tcxo_clk_sel       : 1;  /* bit[1]: TCXOģʽ��ǰ����ʱ��Դ��
                                                              0��32K RC��
                                                              1��32K Crystal OSC�� */
        unsigned char  st_xo_32k_sel         : 1;  /* bit[2]: ģʽѡ��
                                                              0��DCXO��
                                                              1��TCXO�� */
        unsigned char  st_xo_19m2_sel        : 1;  /* bit[3]: XO 19.2M��Դ��
                                                              0��38.4M���壻
                                                              1��19.2M���� */
        unsigned char  st_buck1_vol_sel      : 1;  /* bit[4]: BUCK1�Ŀ�����ѹѡ���źš�
                                                              0��1.2V��
                                                              1��1.1V�� */
        unsigned char  st_sim0_hpd_d540u     : 1;  /* bit[5]: SIM0_HPD״ָ̬ʾλ(˫��ȥ��540us��ʱ�����)��
                                                              0��SIM0_HPD����͵�ƽ��
                                                              1��SIM0_HPD����ߵ�ƽ�� */
        unsigned char  st_sim1_hpd_d540u     : 1;  /* bit[6]: SIM1_HPD״ָ̬ʾλ(˫��ȥ��540us��ʱ�����)��
                                                              0��SIM1_HPD����͵�ƽ��
                                                              1��SIM1_HPD����ߵ�ƽ�� */
        unsigned char  st_avdd_osc_vld_d20nf : 1;  /* bit[7]: AVDD_OSC��Դ���״̬�Ĵ������½���ȥ��20ns����
                                                              0��AVDD_OSC��ѹ���ϸ�
                                                              1��AVDD_OSC��ѹ�ϸ� */
    } reg;
} PMIC_STATUS1_UNION;
#endif
#define PMIC_STATUS1_st_dcxo_clk_sel_START        (0)
#define PMIC_STATUS1_st_dcxo_clk_sel_END          (0)
#define PMIC_STATUS1_st_tcxo_clk_sel_START        (1)
#define PMIC_STATUS1_st_tcxo_clk_sel_END          (1)
#define PMIC_STATUS1_st_xo_32k_sel_START          (2)
#define PMIC_STATUS1_st_xo_32k_sel_END            (2)
#define PMIC_STATUS1_st_xo_19m2_sel_START         (3)
#define PMIC_STATUS1_st_xo_19m2_sel_END           (3)
#define PMIC_STATUS1_st_buck1_vol_sel_START       (4)
#define PMIC_STATUS1_st_buck1_vol_sel_END         (4)
#define PMIC_STATUS1_st_sim0_hpd_d540u_START      (5)
#define PMIC_STATUS1_st_sim0_hpd_d540u_END        (5)
#define PMIC_STATUS1_st_sim1_hpd_d540u_START      (6)
#define PMIC_STATUS1_st_sim1_hpd_d540u_END        (6)
#define PMIC_STATUS1_st_avdd_osc_vld_d20nf_START  (7)
#define PMIC_STATUS1_st_avdd_osc_vld_d20nf_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_D2A_RES0_UNION
 �ṹ˵��  : NP_D2A_RES0 �Ĵ����ṹ���塣��ַƫ����:0x00A����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_d2a_reserve0 : 8;  /* bit[0-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_NP_D2A_RES0_UNION;
#endif
#define PMIC_NP_D2A_RES0_np_d2a_reserve0_START  (0)
#define PMIC_NP_D2A_RES0_np_d2a_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_D2A_RES1_UNION
 �ṹ˵��  : NP_D2A_RES1 �Ĵ����ṹ���塣��ַƫ����:0x00B����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_d2a_reserve1 : 8;  /* bit[0-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_NP_D2A_RES1_UNION;
#endif
#define PMIC_NP_D2A_RES1_np_d2a_reserve1_START  (0)
#define PMIC_NP_D2A_RES1_np_d2a_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_D2A_RES0_UNION
 �ṹ˵��  : D2A_RES0 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  d2a_reserve0 : 8;  /* bit[0-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_D2A_RES0_UNION;
#endif
#define PMIC_D2A_RES0_d2a_reserve0_START  (0)
#define PMIC_D2A_RES0_d2a_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_D2A_RES1_UNION
 �ṹ˵��  : D2A_RES1 �Ĵ����ṹ���塣��ַƫ����:0x00D����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  d2a_reserve1 : 8;  /* bit[0-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_D2A_RES1_UNION;
#endif
#define PMIC_D2A_RES1_d2a_reserve1_START  (0)
#define PMIC_D2A_RES1_d2a_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_A2D_RES0_UNION
 �ṹ˵��  : A2D_RES0 �Ĵ����ṹ���塣��ַƫ����:0x00E����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  a2d_reserve0 : 8;  /* bit[0-7]: ģ�⵽���ֵı����źš� */
    } reg;
} PMIC_A2D_RES0_UNION;
#endif
#define PMIC_A2D_RES0_a2d_reserve0_START  (0)
#define PMIC_A2D_RES0_a2d_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_A2D_RES1_UNION
 �ṹ˵��  : A2D_RES1 �Ĵ����ṹ���塣��ַƫ����:0x00F����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  a2d_reserve1 : 8;  /* bit[0-7]: ģ�⵽���ֵı����źš� */
    } reg;
} PMIC_A2D_RES1_UNION;
#endif
#define PMIC_A2D_RES1_a2d_reserve1_START  (0)
#define PMIC_A2D_RES1_a2d_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK0_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK0���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck0_en     : 1;  /* bit[0]  : BUCK0ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  st_buck0_en      : 1;  /* bit[1]  : BUCK0����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_buck0_eco_en : 1;  /* bit[4]  : BUCK0 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK0_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_START      (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_END        (0)
#define PMIC_BUCK0_ONOFF_ECO_st_buck0_en_START       (1)
#define PMIC_BUCK0_ONOFF_ECO_st_buck0_en_END         (1)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_START  (4)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK1_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x011����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK1���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck1_en     : 1;  /* bit[0]  : BUCK1ʹ���źš�
                                                           0���رգ�
                                                           1��������
                                                           ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  st_buck1_en      : 1;  /* bit[1]  : BUCK1����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_buck1_eco_en : 1;  /* bit[4]  : BUCK1 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK1_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_START      (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_END        (0)
#define PMIC_BUCK1_ONOFF_ECO_st_buck1_en_START       (1)
#define PMIC_BUCK1_ONOFF_ECO_st_buck1_en_END         (1)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_START  (4)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x012����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck2_en     : 1;  /* bit[0]  : BUCK2ʹ���źš�
                                                           0���رգ�
                                                           1��������
                                                           ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  st_buck2_en      : 1;  /* bit[1]  : BUCK2����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_buck2_eco_en : 1;  /* bit[4]  : BUCK2 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK2_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_START      (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_END        (0)
#define PMIC_BUCK2_ONOFF_ECO_st_buck2_en_START       (1)
#define PMIC_BUCK2_ONOFF_ECO_st_buck2_en_END         (1)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_START  (4)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK3_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x013����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK3���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck3_en     : 1;  /* bit[0]  : BUCK3ʹ���źš�
                                                           0���رգ�
                                                           1��������
                                                           ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  st_buck3_en      : 1;  /* bit[1]  : BUCK3����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_buck3_eco_en : 1;  /* bit[4]  : BUCK3 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK3_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_START      (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_END        (0)
#define PMIC_BUCK3_ONOFF_ECO_st_buck3_en_START       (1)
#define PMIC_BUCK3_ONOFF_ECO_st_buck3_en_END         (1)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_START  (4)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_1_ONOFF_UNION
 �ṹ˵��  : LDO0_1_ONOFF �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00�����:8
 �Ĵ���˵��: LDO0_1����ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_1_en : 1;  /* bit[0]  : LDO0_1ʹ���źš�
                                                        0���رգ�
                                                        1��ʹ�ܡ� */
        unsigned char  st_ldo0_1_en  : 1;  /* bit[1]  : LDO0_1����״̬�Ĵ�����
                                                        0���رգ�
                                                        1�������� */
        unsigned char  reserved      : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO0_1_ONOFF_UNION;
#endif
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_START  (0)
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_END    (0)
#define PMIC_LDO0_1_ONOFF_st_ldo0_1_en_START   (1)
#define PMIC_LDO0_1_ONOFF_st_ldo0_1_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_2_ONOFF_ECO_UNION
 �ṹ˵��  : LDO0_2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x015����ֵ:0x01�����:8
 �Ĵ���˵��: LDO0_2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_2_en     : 1;  /* bit[0]  : LDO0_2ʹ���źš�
                                                            0���رգ�
                                                            1��ʹ�ܡ� */
        unsigned char  st_ldo0_2_en      : 1;  /* bit[1]  : LDO0_2����״̬�Ĵ�����
                                                            0���رգ�
                                                            1�������� */
        unsigned char  reserved_0        : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo0_2_eco_en : 1;  /* bit[4]  : LDO0_2����͹���ECOģʽ�����źš�
                                                            0��normalģʽ��
                                                            1��ECOģʽ�� */
        unsigned char  reserved_1        : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO0_2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_START      (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_END        (0)
#define PMIC_LDO0_2_ONOFF_ECO_st_ldo0_2_en_START       (1)
#define PMIC_LDO0_2_ONOFF_ECO_st_ldo0_2_en_END         (1)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_START  (4)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_ONOFF_ECO_UNION
 �ṹ˵��  : LDO1_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x016����ֵ:0x00�����:8
 �Ĵ���˵��: LDO1���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo1_en : 1;  /* bit[0]  : LDO1ʹ���źš�
                                                      0���رգ�
                                                      1��ʹ�ܡ� */
        unsigned char  st_ldo1_en  : 1;  /* bit[1]  : LDO1����״̬�Ĵ�����
                                                      0���رգ�
                                                      1�������� */
        unsigned char  reserved    : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO1_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_START  (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_END    (0)
#define PMIC_LDO1_ONOFF_ECO_st_ldo1_en_START   (1)
#define PMIC_LDO1_ONOFF_ECO_st_ldo1_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO2_ONOFF_ECO_UNION
 �ṹ˵��  : LDO2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x017����ֵ:0x01�����:8
 �Ĵ���˵��: LDO2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo2_en     : 1;  /* bit[0]  : LDO2ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  st_ldo2_en      : 1;  /* bit[1]  : LDO2����״̬�Ĵ�����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo2_eco_en : 1;  /* bit[4]  : LDO2����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_START      (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_END        (0)
#define PMIC_LDO2_ONOFF_ECO_st_ldo2_en_START       (1)
#define PMIC_LDO2_ONOFF_ECO_st_ldo2_en_END         (1)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_START  (4)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_ONOFF_ECO_UNION
 �ṹ˵��  : LDO3_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00�����:8
 �Ĵ���˵��: LDO3���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo3_en : 1;  /* bit[0]  : LDO3ʹ���źš�
                                                      0���رգ�
                                                      1��ʹ�ܡ� */
        unsigned char  st_ldo3_en  : 1;  /* bit[1]  : LDO3����״̬�Ĵ�����
                                                      0���رգ�
                                                      1�������� */
        unsigned char  reserved    : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO3_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_START  (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_END    (0)
#define PMIC_LDO3_ONOFF_ECO_st_ldo3_en_START   (1)
#define PMIC_LDO3_ONOFF_ECO_st_ldo3_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_ONOFF_ECO_UNION
 �ṹ˵��  : LDO4_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x019����ֵ:0x00�����:8
 �Ĵ���˵��: LDO4���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo4_en     : 1;  /* bit[0]  : LDO4ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  st_ldo4_en      : 1;  /* bit[1]  : LDO4����״̬�Ĵ�����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo4_eco_en : 1;  /* bit[4]  : LDO4����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO4_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_START      (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_END        (0)
#define PMIC_LDO4_ONOFF_ECO_st_ldo4_en_START       (1)
#define PMIC_LDO4_ONOFF_ECO_st_ldo4_en_END         (1)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_START  (4)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO5_ONOFF_ECO_UNION
 �ṹ˵��  : LDO5_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01A����ֵ:0x01�����:8
 �Ĵ���˵��: LDO5���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo5_en : 1;  /* bit[0]  : LDO5ʹ���źš�
                                                      0���رգ�
                                                      1��ʹ�ܡ� */
        unsigned char  st_ldo5_en  : 1;  /* bit[1]  : LDO5����״̬�Ĵ�����
                                                      0���رգ�
                                                      1�������� */
        unsigned char  reserved    : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO5_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_START  (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_END    (0)
#define PMIC_LDO5_ONOFF_ECO_st_ldo5_en_START   (1)
#define PMIC_LDO5_ONOFF_ECO_st_ldo5_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_ONOFF_ECO_UNION
 �ṹ˵��  : LDO7_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01B����ֵ:0x01�����:8
 �Ĵ���˵��: LDO7���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo7_en : 1;  /* bit[0]  : LDO7ʹ���źš�
                                                      0���رգ�
                                                      1��ʹ�ܡ� */
        unsigned char  st_ldo7_en  : 1;  /* bit[1]  : LDO7����״̬�Ĵ�����
                                                      0���رգ�
                                                      1�������� */
        unsigned char  reserved    : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO7_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_START  (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_END    (0)
#define PMIC_LDO7_ONOFF_ECO_st_ldo7_en_START   (1)
#define PMIC_LDO7_ONOFF_ECO_st_ldo7_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO8_ONOFF_ECO_UNION
 �ṹ˵��  : LDO8_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x01�����:8
 �Ĵ���˵��: LDO8���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo8_en     : 1;  /* bit[0]  : LDO8ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  st_ldo8_en      : 1;  /* bit[1]  : LDO8����״̬�Ĵ�����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo8_eco_en : 1;  /* bit[4]  : LDO8����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO8_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_START      (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_END        (0)
#define PMIC_LDO8_ONOFF_ECO_st_ldo8_en_START       (1)
#define PMIC_LDO8_ONOFF_ECO_st_ldo8_en_END         (1)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_START  (4)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_ONOFF_ECO_UNION
 �ṹ˵��  : LDO9_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO9���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo9_en     : 1;  /* bit[0]  : LDO9ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  st_ldo9_en      : 1;  /* bit[1]  : LDO9����״̬�Ĵ�����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo9_eco_en : 1;  /* bit[4]  : LDO9����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO9_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_START      (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_END        (0)
#define PMIC_LDO9_ONOFF_ECO_st_ldo9_en_START       (1)
#define PMIC_LDO9_ONOFF_ECO_st_ldo9_en_END         (1)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_START  (4)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO10_ONOFF_ECO_UNION
 �ṹ˵��  : LDO10_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01E����ֵ:0x01�����:8
 �Ĵ���˵��: LDO10���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo10_en     : 1;  /* bit[0]  : LDO10ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo10_en      : 1;  /* bit[1]  : LDO10����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo10_eco_en : 1;  /* bit[4]  : LDO10����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO10_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_START      (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_END        (0)
#define PMIC_LDO10_ONOFF_ECO_st_ldo10_en_START       (1)
#define PMIC_LDO10_ONOFF_ECO_st_ldo10_en_END         (1)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_START  (4)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO11_ONOFF_ECO_UNION
 �ṹ˵��  : LDO11_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x01F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO11���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo11_en     : 1;  /* bit[0]  : LDO11ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo11_en      : 1;  /* bit[1]  : LDO11����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo11_eco_en : 1;  /* bit[4]  : LDO11����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO11_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_START      (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_END        (0)
#define PMIC_LDO11_ONOFF_ECO_st_ldo11_en_START       (1)
#define PMIC_LDO11_ONOFF_ECO_st_ldo11_en_END         (1)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_START  (4)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO12_ONOFF_ECO_UNION
 �ṹ˵��  : LDO12_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo12_en     : 1;  /* bit[0]  : LDO12ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo12_en      : 1;  /* bit[1]  : LDO12����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo12_eco_en : 1;  /* bit[4]  : LDO12����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO12_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_START      (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_END        (0)
#define PMIC_LDO12_ONOFF_ECO_st_ldo12_en_START       (1)
#define PMIC_LDO12_ONOFF_ECO_st_ldo12_en_END         (1)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_START  (4)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_ONOFF_ECO_UNION
 �ṹ˵��  : LDO13_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x021����ֵ:0x00�����:8
 �Ĵ���˵��: LDO13���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo13_en : 1;  /* bit[0]  : LDO13ʹ���ź�(Ĭ�ϲ���������ͨ��OTP����Ĭ�Ͽ�����Ĭ��ֵΪ1��)��
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo13_en  : 1;  /* bit[1]  : LDO13����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO13_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_START  (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_END    (0)
#define PMIC_LDO13_ONOFF_ECO_st_ldo13_en_START   (1)
#define PMIC_LDO13_ONOFF_ECO_st_ldo13_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO14_ONOFF_ECO_UNION
 �ṹ˵��  : LDO14_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x022����ֵ:0x00�����:8
 �Ĵ���˵��: LDO14���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo14_en : 1;  /* bit[0]  : LDO14ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo14_en  : 1;  /* bit[1]  : LDO14����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO14_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_START  (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_END    (0)
#define PMIC_LDO14_ONOFF_ECO_st_ldo14_en_START   (1)
#define PMIC_LDO14_ONOFF_ECO_st_ldo14_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_ONOFF_ECO_UNION
 �ṹ˵��  : LDO15_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x023����ֵ:0x01�����:8
 �Ĵ���˵��: LDO15���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo15_en     : 1;  /* bit[0]  : LDO15ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo15_en      : 1;  /* bit[1]  : LDO15����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo15_eco_en : 1;  /* bit[4]  : LDO15����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO15_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_START      (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_END        (0)
#define PMIC_LDO15_ONOFF_ECO_st_ldo15_en_START       (1)
#define PMIC_LDO15_ONOFF_ECO_st_ldo15_en_END         (1)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_START  (4)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO16_ONOFF_ECO_UNION
 �ṹ˵��  : LDO16_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00�����:8
 �Ĵ���˵��: LDO16���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo16_en     : 1;  /* bit[0]  : LDO16ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo16_en      : 1;  /* bit[1]  : LDO16����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo16_eco_en : 1;  /* bit[4]  : LDO16����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO16_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_START      (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_END        (0)
#define PMIC_LDO16_ONOFF_ECO_st_ldo16_en_START       (1)
#define PMIC_LDO16_ONOFF_ECO_st_ldo16_en_END         (1)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_START  (4)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_ONOFF_ECO_UNION
 �ṹ˵��  : LDO17_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x025����ֵ:0x00�����:8
 �Ĵ���˵��: LDO17���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo17_en     : 1;  /* bit[0]  : LDO17ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo17_en      : 1;  /* bit[1]  : LDO17����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo17_eco_en : 1;  /* bit[4]  : LDO17����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO17_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_START      (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_END        (0)
#define PMIC_LDO17_ONOFF_ECO_st_ldo17_en_START       (1)
#define PMIC_LDO17_ONOFF_ECO_st_ldo17_en_END         (1)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_START  (4)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO19_ONOFF_ECO_UNION
 �ṹ˵��  : LDO19_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x026����ֵ:0x00�����:8
 �Ĵ���˵��: LDO19���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo19_en : 1;  /* bit[0]  : LDO19ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo19_en  : 1;  /* bit[1]  : LDO19����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO19_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_START  (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_END    (0)
#define PMIC_LDO19_ONOFF_ECO_st_ldo19_en_START   (1)
#define PMIC_LDO19_ONOFF_ECO_st_ldo19_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_ONOFF_ECO_UNION
 �ṹ˵��  : LDO20_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x027����ֵ:0x00�����:8
 �Ĵ���˵��: LDO20���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo20_en : 1;  /* bit[0]  : LDO20ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo20_en  : 1;  /* bit[1]  : LDO20����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO20_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_START  (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_END    (0)
#define PMIC_LDO20_ONOFF_ECO_st_ldo20_en_START   (1)
#define PMIC_LDO20_ONOFF_ECO_st_ldo20_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO21_ONOFF_ECO_UNION
 �ṹ˵��  : LDO21_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo21_en : 1;  /* bit[0]  : LDO21ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo21_en  : 1;  /* bit[1]  : LDO21����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO21_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_START  (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_END    (0)
#define PMIC_LDO21_ONOFF_ECO_st_ldo21_en_START   (1)
#define PMIC_LDO21_ONOFF_ECO_st_ldo21_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_ONOFF_ECO_UNION
 �ṹ˵��  : LDO22_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x029����ֵ:0x00�����:8
 �Ĵ���˵��: LDO22���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo22_en : 1;  /* bit[0]  : LDO22ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo22_en  : 1;  /* bit[1]  : LDO22����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO22_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_START  (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_END    (0)
#define PMIC_LDO22_ONOFF_ECO_st_ldo22_en_START   (1)
#define PMIC_LDO22_ONOFF_ECO_st_ldo22_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO23_ONOFF_ECO_UNION
 �ṹ˵��  : LDO23_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02A����ֵ:0x01�����:8
 �Ĵ���˵��: LDO23���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo23_en : 1;  /* bit[0]  : LDO23ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo23_en  : 1;  /* bit[1]  : LDO23����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO23_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_START  (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_END    (0)
#define PMIC_LDO23_ONOFF_ECO_st_ldo23_en_START   (1)
#define PMIC_LDO23_ONOFF_ECO_st_ldo23_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_ONOFF_ECO_UNION
 �ṹ˵��  : LDO24_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02B����ֵ:0x01�����:8
 �Ĵ���˵��: LDO24���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo24_en     : 1;  /* bit[0]  : LDO24ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo24_en      : 1;  /* bit[1]  : LDO24����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo24_eco_en : 1;  /* bit[4]  : LDO24����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO24_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_START      (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_END        (0)
#define PMIC_LDO24_ONOFF_ECO_st_ldo24_en_START       (1)
#define PMIC_LDO24_ONOFF_ECO_st_ldo24_en_END         (1)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_START  (4)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO25_ONOFF_ECO_UNION
 �ṹ˵��  : LDO25_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00�����:8
 �Ĵ���˵��: LDO25���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo25_en : 1;  /* bit[0]  : LDO25ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo25_en  : 1;  /* bit[1]  : LDO25����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO25_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_START  (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_END    (0)
#define PMIC_LDO25_ONOFF_ECO_st_ldo25_en_START   (1)
#define PMIC_LDO25_ONOFF_ECO_st_ldo25_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_ONOFF_ECO_UNION
 �ṹ˵��  : LDO26_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02D����ֵ:0x01�����:8
 �Ĵ���˵��: LDO26���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo26_en     : 1;  /* bit[0]  : LDO26ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo26_en      : 1;  /* bit[1]  : LDO26����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo26_eco_en : 1;  /* bit[4]  : LDO26����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO26_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_START      (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_END        (0)
#define PMIC_LDO26_ONOFF_ECO_st_ldo26_en_START       (1)
#define PMIC_LDO26_ONOFF_ECO_st_ldo26_en_END         (1)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_START  (4)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO27_ONOFF_ECO_UNION
 �ṹ˵��  : LDO27_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02E����ֵ:0x01�����:8
 �Ĵ���˵��: LDO27���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_en : 1;  /* bit[0]  : LDO27ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo27_en  : 1;  /* bit[1]  : LDO27����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO27_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_START  (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_END    (0)
#define PMIC_LDO27_ONOFF_ECO_st_ldo27_en_START   (1)
#define PMIC_LDO27_ONOFF_ECO_st_ldo27_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_ONOFF_ECO_UNION
 �ṹ˵��  : LDO28_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x02F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO28���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo28_en : 1;  /* bit[0]  : LDO28ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo28_en  : 1;  /* bit[1]  : LDO28����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO28_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_START  (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_END    (0)
#define PMIC_LDO28_ONOFF_ECO_st_ldo28_en_START   (1)
#define PMIC_LDO28_ONOFF_ECO_st_ldo28_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO29_ONOFF_ECO_UNION
 �ṹ˵��  : LDO29_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x01�����:8
 �Ĵ���˵��: LDO29���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo29_en     : 1;  /* bit[0]  : LDO29ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  st_ldo29_en      : 1;  /* bit[1]  : LDO29����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo29_eco_en : 1;  /* bit[4]  : LDO29����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO29_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_START      (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_END        (0)
#define PMIC_LDO29_ONOFF_ECO_st_ldo29_en_START       (1)
#define PMIC_LDO29_ONOFF_ECO_st_ldo29_en_END         (1)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_START  (4)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_ONOFF_ECO_UNION
 �ṹ˵��  : LDO31_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x031����ֵ:0x00�����:8
 �Ĵ���˵��: LDO���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo31_en : 1;  /* bit[0]  : LDO31ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo31_en  : 1;  /* bit[1]  : LDO31����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO31_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_START  (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_END    (0)
#define PMIC_LDO31_ONOFF_ECO_st_ldo31_en_START   (1)
#define PMIC_LDO31_ONOFF_ECO_st_ldo31_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO32_ONOFF_ECO_UNION
 �ṹ˵��  : LDO32_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x032����ֵ:0x00�����:8
 �Ĵ���˵��: LDO32���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo32_en : 1;  /* bit[0]  : LDO32ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo32_en  : 1;  /* bit[1]  : LDO32����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO32_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_START  (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_END    (0)
#define PMIC_LDO32_ONOFF_ECO_st_ldo32_en_START   (1)
#define PMIC_LDO32_ONOFF_ECO_st_ldo32_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO33_ONOFF_ECO_UNION
 �ṹ˵��  : LDO33_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x033����ֵ:0x00�����:8
 �Ĵ���˵��: LDO���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo33_en : 1;  /* bit[0]  : LDO33ʹ���źš�
                                                       0���رգ�
                                                       1��ʹ�ܡ� */
        unsigned char  st_ldo33_en  : 1;  /* bit[1]  : LDO33����״̬�Ĵ�����
                                                       0���رգ�
                                                       1�������� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO33_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO33_ONOFF_ECO_reg_ldo33_en_START  (0)
#define PMIC_LDO33_ONOFF_ECO_reg_ldo33_en_END    (0)
#define PMIC_LDO33_ONOFF_ECO_st_ldo33_en_START   (1)
#define PMIC_LDO33_ONOFF_ECO_st_ldo33_en_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO34_ONOFF_ECO_UNION
 �ṹ˵��  : LDO34_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x01�����:8
 �Ĵ���˵��: LDO���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo34_en     : 1;  /* bit[0]  : LDO34ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ�
                                                           ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  st_ldo34_en      : 1;  /* bit[1]  : LDO34����״̬�Ĵ�����
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_ldo34_eco_en : 1;  /* bit[4]  : LDO34����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO34_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_en_START      (0)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_en_END        (0)
#define PMIC_LDO34_ONOFF_ECO_st_ldo34_en_START       (1)
#define PMIC_LDO34_ONOFF_ECO_st_ldo34_en_END         (1)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_eco_en_START  (4)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_VSET_UNION
 �ṹ˵��  : BUCK0_VSET �Ĵ����ṹ���塣��ַƫ����:0x03A����ֵ:0x05�����:8
 �Ĵ���˵��: BUCK0��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_vset : 4;  /* bit[0-3]: BUCK0�����ѹ���ڡ�
                                                     0000��0.700V��
                                                     0001��0.725V��
                                                     0010��0.750V��
                                                     0011��0.775V��
                                                     0100��0.790V��
                                                     0101��0.800V��
                                                     0110��0.810V��
                                                     0111��0.825V��
                                                     1000��0.830V��
                                                     1001��0.850V��
                                                     1010��0.875V��
                                                     1011��0.900V��
                                                     1100��0.925V��
                                                     1101��0.950V��
                                                     1110��0.975V��
                                                     1111��1.000V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_BUCK0_VSET_UNION;
#endif
#define PMIC_BUCK0_VSET_buck0_vset_START  (0)
#define PMIC_BUCK0_VSET_buck0_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_VSET_UNION
 �ṹ˵��  : BUCK1_VSET �Ĵ����ṹ���塣��ַƫ����:0x03B����ֵ:0xCC�����:8
 �Ĵ���˵��: BUCK1��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_vset     : 4;  /* bit[0-3]: BUCK1�����ѹ���ڣ�Ĭ�Ͽ�����ѹ1.2V, buck1_vol_sel����Ĭ��ֵ��0��1.2V��1��1.12V��
                                                         0000��1.08V��
                                                         0001��1.09V��
                                                         0010��1.10V��
                                                         0011��1.11V��
                                                         0100��1.12V��
                                                         0101��1.13V��
                                                         0110��1.14V��
                                                         0111��1.15V��
                                                         1000��1.16V��
                                                         1001��1.17V��
                                                         1010��1.18V��
                                                         1011��1.19V��
                                                         1100��1.20V��
                                                         1101��1.21V��
                                                         1110��1.22V��
                                                         1111��1.23V�� */
        unsigned char  buck1_vset_adj : 4;  /* bit[4-7]: BUCK1�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ,buck1_vol_sel����Ĭ��ֵ��0��1.2V��1��1.12V��
                                                         0000��1.08V��
                                                         0001��1.09V��
                                                         0010��1.10V��
                                                         0011��1.11V��
                                                         0100��1.12V��
                                                         0101��1.13V��
                                                         0110��1.14V��
                                                         0111��1.15V��
                                                         1000��1.16V��
                                                         1001��1.17V��
                                                         1010��1.18V��
                                                         1011��1.19V��
                                                         1100��1.20V��
                                                         1101��1.21V��
                                                         1110��1.22V��
                                                         1111��1.23V�� */
    } reg;
} PMIC_BUCK1_VSET_UNION;
#endif
#define PMIC_BUCK1_VSET_buck1_vset_START      (0)
#define PMIC_BUCK1_VSET_buck1_vset_END        (3)
#define PMIC_BUCK1_VSET_buck1_vset_adj_START  (4)
#define PMIC_BUCK1_VSET_buck1_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_VSET_UNION
 �ṹ˵��  : BUCK2_VSET �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x44�����:8
 �Ĵ���˵��: BUCK2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_vset     : 4;  /* bit[0-3]: BUCK2�����ѹ���ڡ�
                                                         0000��1.250V��
                                                         0001��1.275V��
                                                         0010��1.300V��
                                                         0011��1.325V��
                                                         0100��1.350V��
                                                         0101��1.375V��
                                                         0110��1.400V��
                                                         0111��1.425V��
                                                         1000��1.450V��
                                                         1001��1.475V��
                                                         1010��1.500V��
                                                         1011��1.525V��
                                                         1100��1.550V��
                                                         1101��1.575V��
                                                         1110��1.600V��
                                                         1111��1.625V�� */
        unsigned char  buck2_vset_adj : 4;  /* bit[4-7]: BUCK2���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         0000��1.250V��
                                                         0001��1.275V��
                                                         0010��1.300V��
                                                         0011��1.325V��
                                                         0100��1.350V��
                                                         0101��1.375V��
                                                         0110��1.400V��
                                                         0111��1.425V��
                                                         1000��1.450V��
                                                         1001��1.475V��
                                                         1010��1.500V��
                                                         1011��1.525V��
                                                         1100��1.550V��
                                                         1101��1.575V��
                                                         1110��1.600V��
                                                         1111��1.625V�� */
    } reg;
} PMIC_BUCK2_VSET_UNION;
#endif
#define PMIC_BUCK2_VSET_buck2_vset_START      (0)
#define PMIC_BUCK2_VSET_buck2_vset_END        (3)
#define PMIC_BUCK2_VSET_buck2_vset_adj_START  (4)
#define PMIC_BUCK2_VSET_buck2_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_VSET_UNION
 �ṹ˵��  : BUCK3_VSET �Ĵ����ṹ���塣��ַƫ����:0x03D����ֵ:0x77�����:8
 �Ĵ���˵��: BUCK3��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_vset     : 4;  /* bit[0-3]: BUCK3�����ѹ���ڡ�
                                                         0000��1.720V��
                                                         0001��1.760V��
                                                         0010��1.800V��
                                                         0011��1.840V��
                                                         0100��1.880V��
                                                         0101��1.920V��
                                                         0110��1.960V��
                                                         0111��2.000V��
                                                         1000��2.040V��
                                                         1001��2.080V��
                                                         1010��2.120V��
                                                         1011��2.160V��
                                                         1100��2.200V��
                                                         1101��2.240V��
                                                         1110��2.280V��
                                                         1111��2.320V�� */
        unsigned char  buck3_vset_adj : 4;  /* bit[4-7]: BUCK3���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         0000��1.720V��
                                                         0001��1.760V��
                                                         0010��1.800V��
                                                         0011��1.840V��
                                                         0100��1.880V��
                                                         0101��1.920V��
                                                         0110��1.960V��
                                                         0111��2.000V��
                                                         1000��2.040V��
                                                         1001��2.080V��
                                                         1010��2.120V��
                                                         1011��2.160V��
                                                         1100��2.200V��
                                                         1101��2.240V��
                                                         1110��2.280V��
                                                         1111��2.320V�� */
    } reg;
} PMIC_BUCK3_VSET_UNION;
#endif
#define PMIC_BUCK3_VSET_buck3_vset_START      (0)
#define PMIC_BUCK3_VSET_buck3_vset_END        (3)
#define PMIC_BUCK3_VSET_buck3_vset_adj_START  (4)
#define PMIC_BUCK3_VSET_buck3_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_2_VSET_UNION
 �ṹ˵��  : LDO0_2_VSET �Ĵ����ṹ���塣��ַƫ����:0x03E����ֵ:0x55�����:8
 �Ĵ���˵��: LDO0_2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo0_2_vset     : 3;  /* bit[0-2]: LDO0_2�����ѹ���á�
                                                          000��0.600V��
                                                          001��0.650V��
                                                          010��0.700V��
                                                          011��0.750V��
                                                          100��0.775V��
                                                          101��0.800V��
                                                          110��0.825V��
                                                          111��0.850V�� */
        unsigned char  reserved_0      : 1;  /* bit[3]  : ���� */
        unsigned char  ldo0_2_vset_adj : 3;  /* bit[4-6]: LDO0_2�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ��
                                                          000��0.600V��
                                                          001��0.650V��
                                                          010��0.700V��
                                                          011��0.750V��
                                                          100��0.775V��
                                                          101��0.800V��
                                                          110��0.825V��
                                                          111��0.850V�� */
        unsigned char  reserved_1      : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO0_2_VSET_UNION;
#endif
#define PMIC_LDO0_2_VSET_ldo0_2_vset_START      (0)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_END        (2)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_START  (4)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_VSET_UNION
 �ṹ˵��  : LDO1_VSET �Ĵ����ṹ���塣��ַƫ����:0x03F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO1��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vset : 4;  /* bit[0-3]: LDO1�����ѹ���ã�Ĭ�ϵ�ѹ1.0V��
                                                    0000��1.20V��
                                                    0001��1.21V��
                                                    0010��1.22V��
                                                    0011��1.23V��
                                                    0100��1.24V��
                                                    0101��1.25V��
                                                    0110��1.26V��
                                                    0111��1.27V��
                                                    1000��1.28V��
                                                    1001��1.29V��
                                                    1010��1.30V��
                                                    1011��1.31V��
                                                    1100��1.32V��
                                                    1101��1.33V��
                                                    1110��1.34V��
                                                    1111��1.35V�� */
        unsigned char  reserved  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO1_VSET_UNION;
#endif
#define PMIC_LDO1_VSET_ldo1_vset_START  (0)
#define PMIC_LDO1_VSET_ldo1_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO2_VSET_UNION
 �ṹ˵��  : LDO2_VSET �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x33�����:8
 �Ĵ���˵��: LDO2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_vset     : 3;  /* bit[0-2]: LDO2�����ѹ���á�
                                                        000��1.700V��
                                                        001��1.750V��
                                                        010��1.775V��
                                                        011��1.800V��
                                                        100��1.825V��
                                                        101��1.850V��
                                                        110��1.875V��
                                                        111��1.900V�� */
        unsigned char  reserved_0    : 1;  /* bit[3]  : ������ */
        unsigned char  ldo2_vset_adj : 3;  /* bit[4-6]: LDO2�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ��
                                                        000��1.700V��
                                                        001��1.750V��
                                                        010��1.775V��
                                                        011��1.800V��
                                                        100��1.825V��
                                                        101��1.850V��
                                                        110��1.875V��
                                                        111��1.900V�� */
        unsigned char  reserved_1    : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO2_VSET_UNION;
#endif
#define PMIC_LDO2_VSET_ldo2_vset_START      (0)
#define PMIC_LDO2_VSET_ldo2_vset_END        (2)
#define PMIC_LDO2_VSET_ldo2_vset_adj_START  (4)
#define PMIC_LDO2_VSET_ldo2_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_VSET_UNION
 �ṹ˵��  : LDO3_VSET �Ĵ����ṹ���塣��ַƫ����:0x041����ֵ:0x00�����:8
 �Ĵ���˵��: LDO3��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vset : 4;  /* bit[0-3]: LDO3�����ѹ���á�
                                                    0000��1.83V��
                                                    0001��1.84V��
                                                    0010��1.85V��
                                                    0011��1.86V��
                                                    0100��1.87V��
                                                    0101��1.88V��
                                                    0110��1.89V��
                                                    0111��1.90V��
                                                    1000��1.91V��
                                                    1001��1.92V��
                                                    1010��1.93V��
                                                    1011��1.94V��
                                                    1100��1.95V��
                                                    1101��1.96V��
                                                    1110��1.97V��
                                                    1111��1.98V�� */
        unsigned char  reserved  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO3_VSET_UNION;
#endif
#define PMIC_LDO3_VSET_ldo3_vset_START  (0)
#define PMIC_LDO3_VSET_ldo3_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_VSET_UNION
 �ṹ˵��  : LDO4_VSET �Ĵ����ṹ���塣��ַƫ����:0x042����ֵ:0x00�����:8
 �Ĵ���˵��: LDO4��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo4_vset : 3;  /* bit[0-2]: LDO4�����ѹ���á�
                                                    000��1.700V��
                                                    001��1.750V��
                                                    010��1.775V��
                                                    011��1.800V��
                                                    100��1.825V��
                                                    101��1.850V��
                                                    110��1.875V��
                                                    111��1.900V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO4_VSET_UNION;
#endif
#define PMIC_LDO4_VSET_ldo4_vset_START  (0)
#define PMIC_LDO4_VSET_ldo4_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO5_VSET_UNION
 �ṹ˵��  : LDO5_VSET �Ĵ����ṹ���塣��ַƫ����:0x043����ֵ:0x03�����:8
 �Ĵ���˵��: LDO5��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vset : 3;  /* bit[0-2]: LDO5�����ѹ���á�
                                                    000��1.7V��
                                                    001��1.75V��
                                                    010��1.775V��
                                                    011��1.8V��
                                                    100��1.825V��
                                                    101��1.85V��
                                                    110��1.9V��
                                                    111��1.95V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO5_VSET_UNION;
#endif
#define PMIC_LDO5_VSET_ldo5_vset_START  (0)
#define PMIC_LDO5_VSET_ldo5_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_VSET_UNION
 �ṹ˵��  : LDO7_VSET �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x02�����:8
 �Ĵ���˵��: LDO7��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_vset : 3;  /* bit[0-2]: LDO7�����ѹ���á�
                                                    000��0.88V��
                                                    001��0.89V��
                                                    010��0.90V��
                                                    011��0.91V��
                                                    100��0.92V��
                                                    101��0.93V��
                                                    110��0.94V��
                                                    111��0.95V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO7_VSET_UNION;
#endif
#define PMIC_LDO7_VSET_ldo7_vset_START  (0)
#define PMIC_LDO7_VSET_ldo7_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO8_VSET_UNION
 �ṹ˵��  : LDO8_VSET �Ĵ����ṹ���塣��ַƫ����:0x045����ֵ:0x03�����:8
 �Ĵ���˵��: LDO8��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vset : 3;  /* bit[0-2]: LDO8�����ѹ���ã�ldo8_vset[3]��ʹ�á�
                                                    000��1.700V��
                                                    001��1.750V��
                                                    010��1.775V��
                                                    011��1.800V��
                                                    100��1.825V��
                                                    101��1.850V��
                                                    110��1.900V��
                                                    111��1.950V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO8_VSET_UNION;
#endif
#define PMIC_LDO8_VSET_ldo8_vset_START  (0)
#define PMIC_LDO8_VSET_ldo8_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_VSET_UNION
 �ṹ˵��  : LDO9_VSET �Ĵ����ṹ���塣��ַƫ����:0x046����ֵ:0x00�����:8
 �Ĵ���˵��: LDO9��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo9_vset : 3;  /* bit[0-2]: LDO9�����ѹ���á�
                                                    000��1.750V��
                                                    001��1.800V��
                                                    010��1.825V��
                                                    011��2.800V��
                                                    100��2.850V��
                                                    101��2.950V��
                                                    110��3.000V��
                                                    111��3.300V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO9_VSET_UNION;
#endif
#define PMIC_LDO9_VSET_ldo9_vset_START  (0)
#define PMIC_LDO9_VSET_ldo9_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO10_VSET_UNION
 �ṹ˵��  : LDO10_VSET �Ĵ����ṹ���塣��ַƫ����:0x047����ֵ:0x06�����:8
 �Ĵ���˵��: LDO10��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vset : 3;  /* bit[0-2]: LDO10�����ѹ���á�
                                                     000��2.6V��
                                                     001��2.7V��
                                                     010��2.8V��
                                                     011��2.9V��
                                                     100: 3.0V��
                                                     101: 3.1V��
                                                     110��3.2V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO10_VSET_UNION;
#endif
#define PMIC_LDO10_VSET_ldo10_vset_START  (0)
#define PMIC_LDO10_VSET_ldo10_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO11_VSET_UNION
 �ṹ˵��  : LDO11_VSET �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00�����:8
 �Ĵ���˵��: LDO11��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_vset : 3;  /* bit[0-2]: LDO11�����ѹ���á�
                                                     000��1.750V��
                                                     001��1.800V��
                                                     010��1.825V��
                                                     011��2.800V��
                                                     100��2.850V��
                                                     101��2.950V��
                                                     110��3.000V��
                                                     111��3.300V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO11_VSET_UNION;
#endif
#define PMIC_LDO11_VSET_ldo11_vset_START  (0)
#define PMIC_LDO11_VSET_ldo11_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO12_VSET_UNION
 �ṹ˵��  : LDO12_VSET �Ĵ����ṹ���塣��ַƫ����:0x049����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vset : 3;  /* bit[0-2]: LDO12�����ѹ���á�
                                                     000��1.750V��
                                                     001��1.800V��
                                                     010��1.825V��
                                                     011��2.800V��
                                                     100��2.850V��
                                                     101��2.950V��
                                                     110��3.000V��
                                                     111��3.300V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO12_VSET_UNION;
#endif
#define PMIC_LDO12_VSET_ldo12_vset_START  (0)
#define PMIC_LDO12_VSET_ldo12_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_VSET_UNION
 �ṹ˵��  : LDO13_VSET �Ĵ����ṹ���塣��ַƫ����:0x04A����ֵ:0x06�����:8
 �Ĵ���˵��: LDO13��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo13_vset : 3;  /* bit[0-2]: LDO13�����ѹ���á�
                                                     000��1.80V��
                                                     001��2.50V��
                                                     010��2.60V��
                                                     011��2.70V��
                                                     100��2.75V��
                                                     101��2.80V��
                                                     110��2.85V��
                                                     111��2.90V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO13_VSET_UNION;
#endif
#define PMIC_LDO13_VSET_ldo13_vset_START  (0)
#define PMIC_LDO13_VSET_ldo13_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO14_VSET_UNION
 �ṹ˵��  : LDO14_VSET �Ĵ����ṹ���塣��ַƫ����:0x04B����ֵ:0x00�����:8
 �Ĵ���˵��: LDO14��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vset : 3;  /* bit[0-2]: LDO14�����ѹ���á�
                                                     000��1.750V��
                                                     001��1.800V��
                                                     010��1.825V��
                                                     011��2.800V��
                                                     100��2.850V��
                                                     101��2.950V��
                                                     110��3.000V��
                                                     111��3.300V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO14_VSET_UNION;
#endif
#define PMIC_LDO14_VSET_ldo14_vset_START  (0)
#define PMIC_LDO14_VSET_ldo14_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_VSET_UNION
 �ṹ˵��  : LDO15_VSET �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x06�����:8
 �Ĵ���˵��: LDO15��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo15_vset : 3;  /* bit[0-2]: LDO15�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.80V��
                                                     010��2.40V��
                                                     011��2.60V��
                                                     100��2.70V��
                                                     101��2.85V��
                                                     110��2.95V��
                                                     111��3.00V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO15_VSET_UNION;
#endif
#define PMIC_LDO15_VSET_ldo15_vset_START  (0)
#define PMIC_LDO15_VSET_ldo15_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO16_VSET_UNION
 �ṹ˵��  : LDO16_VSET �Ĵ����ṹ���塣��ַƫ����:0x04D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO16��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vset : 3;  /* bit[0-2]: LDO16�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.80V��
                                                     010��2.40V��
                                                     011��2.60V��
                                                     100��2.70V��
                                                     101��2.85V��
                                                     110��2.95V��
                                                     111��3.00V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO16_VSET_UNION;
#endif
#define PMIC_LDO16_VSET_ldo16_vset_START  (0)
#define PMIC_LDO16_VSET_ldo16_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_VSET_UNION
 �ṹ˵��  : LDO17_VSET �Ĵ����ṹ���塣��ַƫ����:0x04E����ֵ:0x00�����:8
 �Ĵ���˵��: LDO17��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo17_vset : 3;  /* bit[0-2]: LDO17�����ѹ���á�
                                                     000��2.60V��
                                                     001��2.70V��
                                                     010��2.80V��
                                                     011��2.85V��
                                                     100��3.00V��
                                                     101��3.10V��
                                                     110��3.20V��
                                                     111��3.30V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO17_VSET_UNION;
#endif
#define PMIC_LDO17_VSET_ldo17_vset_START  (0)
#define PMIC_LDO17_VSET_ldo17_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO19_VSET1_UNION
 �ṹ˵��  : LDO19_VSET1 �Ĵ����ṹ���塣��ַƫ����:0x04F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO19��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vset : 3;  /* bit[0-2]: LDO19�����ѹ���á�
                                                     000��1.80V��
                                                     001��2.50V��
                                                     010��2.60V��
                                                     011��2.70V��
                                                     100��2.75V��
                                                     101��2.80V��
                                                     110��2.85V��
                                                     111��2.90V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO19_VSET1_UNION;
#endif
#define PMIC_LDO19_VSET1_ldo19_vset_START  (0)
#define PMIC_LDO19_VSET1_ldo19_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_VSET_UNION
 �ṹ˵��  : LDO20_VSET �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x02�����:8
 �Ĵ���˵��: LDO20��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_vset : 4;  /* bit[0-3]: LDO20�����ѹ���á�
                                                     0000��0.90V��
                                                     0001��0.95V��
                                                     0010��1.00V��
                                                     0011��1.05V��
                                                     0100��1.10V��
                                                     0101��1.20V��
                                                     0110��1.25V��
                                                     0111��1.26V��
                                                     1000��1.27V��
                                                     1001��1.28V��
                                                     1010��1.29V��
                                                     1011��1.30V��
                                                     1100��1.31V��
                                                     1101��1.32V��
                                                     ��������Ч�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO20_VSET_UNION;
#endif
#define PMIC_LDO20_VSET_ldo20_vset_START  (0)
#define PMIC_LDO20_VSET_ldo20_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO21_VSET_UNION
 �ṹ˵��  : LDO21_VSET �Ĵ����ṹ���塣��ַƫ����:0x051����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vset : 3;  /* bit[0-2]: LDO21�����ѹ���á�
                                                     000��1.700V��
                                                     001��1.750V��
                                                     010��1.775V��
                                                     011��1.800V��
                                                     100��1.825V��
                                                     101��1.850V��
                                                     110��1.875V��
                                                     111��1.900V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO21_VSET_UNION;
#endif
#define PMIC_LDO21_VSET_ldo21_vset_START  (0)
#define PMIC_LDO21_VSET_ldo21_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_VSET_UNION
 �ṹ˵��  : LDO22_VSET �Ĵ����ṹ���塣��ַƫ����:0x052����ֵ:0x00�����:8
 �Ĵ���˵��: LDO22��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vset : 4;  /* bit[0-3]: LDO22�����ѹ���á�
                                                     0000��1.20V��
                                                     0001��1.21V��
                                                     0010��1.22V��
                                                     0011��1.23V��
                                                     0100��1.24V��
                                                     0101��1.25V��
                                                     0110��1.26V��
                                                     0111��1.27V��
                                                     1000��1.28V��
                                                     1001��1.29V��
                                                     1010��1.30V��
                                                     1011��1.31V��
                                                     1100��1.32V��
                                                     1101��1.33V��
                                                     1110��1.34V��
                                                     1111��1.35V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO22_VSET_UNION;
#endif
#define PMIC_LDO22_VSET_ldo22_vset_START  (0)
#define PMIC_LDO22_VSET_ldo22_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO23_VSET_UNION
 �ṹ˵��  : LDO23_VSET �Ĵ����ṹ���塣��ַƫ����:0x053����ֵ:0x04�����:8
 �Ĵ���˵��: LDO23��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vset : 3;  /* bit[0-2]: LDO23�����ѹ���á�
                                                     000��1.90V��
                                                     001��1.95V��
                                                     010��2.00V��
                                                     011��2.05V��
                                                     100��2.10V��
                                                     101��2.15V��
                                                     110��2.20V��
                                                     111��2.25V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO23_VSET_UNION;
#endif
#define PMIC_LDO23_VSET_ldo23_vset_START  (0)
#define PMIC_LDO23_VSET_ldo23_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_VSET_UNION
 �ṹ˵��  : LDO24_VSET �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x02�����:8
 �Ĵ���˵��: LDO24��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_vset : 3;  /* bit[0-2]: LDO24�����ѹ���á�
                                                     000��2.60V��
                                                     001��2.70V��
                                                     010��2.80V��
                                                     011��2.85V��
                                                     100��3.00V��
                                                     101��3.10V��
                                                     110��3.20V��
                                                     111��3.30V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO24_VSET_UNION;
#endif
#define PMIC_LDO24_VSET_ldo24_vset_START  (0)
#define PMIC_LDO24_VSET_ldo24_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO25_VSET_UNION
 �ṹ˵��  : LDO25_VSET �Ĵ����ṹ���塣��ַƫ����:0x055����ֵ:0x00�����:8
 �Ĵ���˵��: LDO25��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vset : 3;  /* bit[0-2]: LDO25�����ѹ���á�
                                                     000��1.50V��
                                                     001��1.80V��
                                                     010��2.40V��
                                                     011��2.50V��
                                                     100��2.60V��
                                                     101��2.70V��
                                                     110��2.85V��
                                                     111��3.00V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO25_VSET_UNION;
#endif
#define PMIC_LDO25_VSET_ldo25_vset_START  (0)
#define PMIC_LDO25_VSET_ldo25_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_VSET_UNION
 �ṹ˵��  : LDO26_VSET �Ĵ����ṹ���塣��ַƫ����:0x056����ֵ:0x07�����:8
 �Ĵ���˵��: LDO26��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vset : 3;  /* bit[0-2]: LDO26�����ѹ���á�
                                                     000��1.20V��
                                                     001��1.25V��
                                                     010��1.30V��
                                                     011��1.35V��
                                                     100��1.40V��
                                                     101��1.50V��
                                                     110��1.60V��
                                                     111��1.70V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO26_VSET_UNION;
#endif
#define PMIC_LDO26_VSET_ldo26_vset_START  (0)
#define PMIC_LDO26_VSET_ldo26_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO27_VSET_UNION
 �ṹ˵��  : LDO27_VSET �Ĵ����ṹ���塣��ַƫ����:0x057����ֵ:0x05�����:8
 �Ĵ���˵��: LDO27��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vset : 4;  /* bit[0-3]: LDO27�����ѹ���á�
                                                     0000��2.200V��
                                                     0001��2.250V��
                                                     0010��2.300V��
                                                     0011��2.350V��
                                                     0100��2.375V��
                                                     0101��2.400V��
                                                     0110��2.425V��
                                                     0111��2.450V��
                                                     1000��2.475V��
                                                     1001��2.500V��
                                                     1010��2.550V��
                                                     1011��2.600V��
                                                     1100��2.650V��
                                                     1101��2.700V��
                                                     1110��2.800V��
                                                     1111��2.850V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO27_VSET_UNION;
#endif
#define PMIC_LDO27_VSET_ldo27_vset_START  (0)
#define PMIC_LDO27_VSET_ldo27_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_VSET_UNION
 �ṹ˵��  : LDO28_VSET �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00�����:8
 �Ĵ���˵��: LDO28��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo28_vset : 3;  /* bit[0-2]: LDO28�����ѹ���á�
                                                     000��1.700V��
                                                     001��1.750V��
                                                     010��1.775V��
                                                     011��1.800V��
                                                     100��1.825V��
                                                     101��1.850V��
                                                     110��1.875V��
                                                     111��1.900V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO28_VSET_UNION;
#endif
#define PMIC_LDO28_VSET_ldo28_vset_START  (0)
#define PMIC_LDO28_VSET_ldo28_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO29_VSET_UNION
 �ṹ˵��  : LDO29_VSET �Ĵ����ṹ���塣��ַƫ����:0x059����ֵ:0x33�����:8
 �Ĵ���˵��: LDO29��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vset     : 3;  /* bit[0-2]: LDO29�����ѹ���á�
                                                         000��1.000V��
                                                         001��1.050V��
                                                         010��1.100V��
                                                         011��1.200V��
                                                         100��1.225V��
                                                         101��1.250V��
                                                         110��1.275V��
                                                         111��1.300V�� */
        unsigned char  reserved_0     : 1;  /* bit[3]  : ������ */
        unsigned char  ldo29_vset_adj : 3;  /* bit[4-6]: LDO29���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         000��1.000V��
                                                         001��1.050V��
                                                         010��1.100V��
                                                         011��1.200V��
                                                         100��1.225V��
                                                         101��1.250V��
                                                         110��1.275V��
                                                         111��1.300V�� */
        unsigned char  reserved_1     : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO29_VSET_UNION;
#endif
#define PMIC_LDO29_VSET_ldo29_vset_START      (0)
#define PMIC_LDO29_VSET_ldo29_vset_END        (2)
#define PMIC_LDO29_VSET_ldo29_vset_adj_START  (4)
#define PMIC_LDO29_VSET_ldo29_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_VSET_UNION
 �ṹ˵��  : LDO31_VSET �Ĵ����ṹ���塣��ַƫ����:0x05A����ֵ:0x00�����:8
 �Ĵ���˵��: LDO31��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vset : 3;  /* bit[0-2]: LDO31�����ѹ���á�
                                                     000��2.5V��
                                                     001��2.6V��
                                                     010��2.7V��
                                                     011��2.8V��
                                                     100��2.9V��
                                                     101��3.0V��
                                                     110��3.1V��
                                                     111��3.2V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO31_VSET_UNION;
#endif
#define PMIC_LDO31_VSET_ldo31_vset_START  (0)
#define PMIC_LDO31_VSET_ldo31_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO32_VSET_UNION
 �ṹ˵��  : LDO32_VSET �Ĵ����ṹ���塣��ַƫ����:0x05B����ֵ:0x02�����:8
 �Ĵ���˵��: LDO32��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vset : 4;  /* bit[0-3]: LDO32�����ѹ���á�
                                                     0000��0.90V��
                                                     0001��0.95V��
                                                     0010��1.00V��
                                                     0011��1.05V��
                                                     0100��1.10V��
                                                     0101��1.20V��
                                                     0110��1.25V��
                                                     0111��1.26V��
                                                     1000��1.27V��
                                                     1001��1.28V��
                                                     1010��1.29V��
                                                     1011��1.30V��
                                                     1100��1.31V��
                                                     1101��1.32V��
                                                     ��������Ч�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO32_VSET_UNION;
#endif
#define PMIC_LDO32_VSET_ldo32_vset_START  (0)
#define PMIC_LDO32_VSET_ldo32_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO33_VSET_UNION
 �ṹ˵��  : LDO33_VSET �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00�����:8
 �Ĵ���˵��: LDO33��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo33_vset : 3;  /* bit[0-2]: LDO33�����ѹ���á�
                                                     000��1.700V��
                                                     001��1.750V��
                                                     010��1.775V��
                                                     011��1.800V��
                                                     100��1.825V��
                                                     101��1.850V��
                                                     110��1.875V��
                                                     111��1.900V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO33_VSET_UNION;
#endif
#define PMIC_LDO33_VSET_ldo33_vset_START  (0)
#define PMIC_LDO33_VSET_ldo33_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO34_VSET_UNION
 �ṹ˵��  : LDO34_VSET �Ĵ����ṹ���塣��ַƫ����:0x05D����ֵ:0x06�����:8
 �Ĵ���˵��: LDO34��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_vset : 3;  /* bit[0-2]: LDO34�����ѹ���á�
                                                     000��2.60V��
                                                     001��2.70V��
                                                     010��2.80V��
                                                     011��2.90V��
                                                     100��3.00V��
                                                     101��3.05V��
                                                     110��3.10V��
                                                     111��3.20V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO34_VSET_UNION;
#endif
#define PMIC_LDO34_VSET_ldo34_vset_START  (0)
#define PMIC_LDO34_VSET_ldo34_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL0_UNION
 �ṹ˵��  : BUCK0_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0xD4�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dbias   : 4;  /* bit[0-3]: buck0 <1:0>�Ƚ���ƫ�õ������ڣ�00~11����
                                                         buck0<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
        unsigned char  buck0_adj_rlx : 4;  /* bit[4-7]: BUCK0 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK0_CTRL0_UNION;
#endif
#define PMIC_BUCK0_CTRL0_buck0_dbias_START    (0)
#define PMIC_BUCK0_CTRL0_buck0_dbias_END      (3)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_START  (4)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL1_UNION
 �ṹ˵��  : BUCK0_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x065����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_dt_sel   : 1;  /* bit[0]  : BUCK0 P�ܵ�N������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck0_pg_dt_sel   : 1;  /* bit[1]  : BUCK0 N�ܵ�P������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck0_nmos_switch : 1;  /* bit[2]  : buck0 eco��normal�л�ʱNMOS�����л���ʽ��
                                                            0����dmdͬʱ�л���
                                                            1����dmd֮���л��� */
        unsigned char  reserved          : 1;  /* bit[3]  : ���� */
        unsigned char  buck0_dt_sel      : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                            0���������ӳ�5ns��
                                                            1�������ӳ�5ns�� */
        unsigned char  buck0_ocp_sel     : 2;  /* bit[6-7]: BUCK0 OCP�������
                                                            00��4.15A��
                                                            01��4.70A��
                                                            10��5.27A��
                                                            11��5.82A�� */
    } reg;
} PMIC_BUCK0_CTRL1_UNION;
#endif
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_START    (0)
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_END      (0)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_START    (1)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_END      (1)
#define PMIC_BUCK0_CTRL1_buck0_nmos_switch_START  (2)
#define PMIC_BUCK0_CTRL1_buck0_nmos_switch_END    (2)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_START       (4)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_END         (5)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_START      (6)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL2_UNION
 �ṹ˵��  : BUCK0_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x066����ֵ:0x99�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_n_sel : 2;  /* bit[0-1]: BUCK0 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck0_ng_p_sel : 2;  /* bit[2-3]: BUCK0 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck0_pg_n_sel : 2;  /* bit[4-5]: BUCK0 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck0_pg_p_sel : 2;  /* bit[6-7]: BUCK0 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK0_CTRL2_UNION;
#endif
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_START  (0)
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_END    (1)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_START  (2)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_END    (3)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_START  (4)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_END    (5)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_START  (6)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL3_UNION
 �ṹ˵��  : BUCK0_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x067����ֵ:0x61�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reg_r   : 2;  /* bit[0-1]: BUCK0�ڲ�regulator���裬���ڵ���regulator����
                                                        00��2.8kHz��
                                                        01��45kHz��
                                                        10��85kHz��
                                                        11��152kHz�� */
        unsigned char  reserved      : 2;  /* bit[2-3]: ������ */
        unsigned char  buck0_reg_en  : 1;  /* bit[4]  : BUCK0�ڲ����ȵ�����ʹ���źš�
                                                        0��ʹ�ܣ�
                                                        1����ʹ�ܡ� */
        unsigned char  buck0_adj_clx : 2;  /* bit[5-6]: buck0 LX�����˲����ݵ���
                                                        ��11������ȫ���룬00������ȫ�����룩 */
        unsigned char  buck0_ocp_dis : 1;  /* bit[7]  : BUCK0 �ڲ�OCP��·�����źš�
                                                        0�������Σ�
                                                        1�����Ρ� */
    } reg;
} PMIC_BUCK0_CTRL3_UNION;
#endif
#define PMIC_BUCK0_CTRL3_buck0_reg_r_START    (0)
#define PMIC_BUCK0_CTRL3_buck0_reg_r_END      (1)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_START   (4)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_END     (4)
#define PMIC_BUCK0_CTRL3_buck0_adj_clx_START  (5)
#define PMIC_BUCK0_CTRL3_buck0_adj_clx_END    (6)
#define PMIC_BUCK0_CTRL3_buck0_ocp_dis_START  (7)
#define PMIC_BUCK0_CTRL3_buck0_ocp_dis_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL4_UNION
 �ṹ˵��  : BUCK0_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x60�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_short_pdp  : 1;  /* bit[0]  : ��·�������μĴ�����
                                                           0��ʹ�ܶ�·������0.4V���ޣ�
                                                           1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck0_reg_ss     : 1;  /* bit[1]  : BUCK0������ʱ�ڲ�regulator״̬��
                                                           0������״̬��
                                                           1����λ���淴���� */
        unsigned char  buck0_regop_c    : 1;  /* bit[2]  : BUCK0�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                           0��slew-rate����
                                                           1��slew-rate�졣 */
        unsigned char  buck0_filter_ton : 2;  /* bit[3-4]: �Ƚ�����ë�̣�00~11���� */
        unsigned char  buck0_reg_dr     : 3;  /* bit[5-7]: BUCK0�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                           000��+/-6mV��
                                                           001��+/-12mV��
                                                           010��+/-18mV��
                                                           011��+/-24mV��
                                                           100��+/-30mV��
                                                           101��+/-36mV��
                                                           110��+/-42mV��
                                                           111��+/-48mV�� */
    } reg;
} PMIC_BUCK0_CTRL4_UNION;
#endif
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_START   (0)
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_END     (0)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_START      (1)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_END        (1)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_START     (2)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_END       (2)
#define PMIC_BUCK0_CTRL4_buck0_filter_ton_START  (3)
#define PMIC_BUCK0_CTRL4_buck0_filter_ton_END    (4)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_START      (5)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL5_UNION
 �ṹ˵��  : BUCK0_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x069����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ton      : 2;  /* bit[0-1]: BUCK0��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck0_eco_ng   : 1;  /* bit[2]  : BUCK0���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck0_reg_bias : 1;  /* bit[3]  : BUCK0�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0��0.5uA��
                                                         1��1uA�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK0_CTRL5_UNION;
#endif
#define PMIC_BUCK0_CTRL5_buck0_ton_START       (0)
#define PMIC_BUCK0_CTRL5_buck0_ton_END         (1)
#define PMIC_BUCK0_CTRL5_buck0_eco_ng_START    (2)
#define PMIC_BUCK0_CTRL5_buck0_eco_ng_END      (2)
#define PMIC_BUCK0_CTRL5_buck0_reg_bias_START  (3)
#define PMIC_BUCK0_CTRL5_buck0_reg_bias_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL6_UNION
 �ṹ˵��  : BUCK0_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x06A����ֵ:0x69�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dmd_ton  : 3;  /* bit[0-2]: buck0����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned char  buck0_ocp_toff : 2;  /* bit[3-4]: buck0����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned char  buck0_dmd_sel  : 3;  /* bit[5-7]: buck0 dmd��ѡ��000~111���� */
    } reg;
} PMIC_BUCK0_CTRL6_UNION;
#endif
#define PMIC_BUCK0_CTRL6_buck0_dmd_ton_START   (0)
#define PMIC_BUCK0_CTRL6_buck0_dmd_ton_END     (2)
#define PMIC_BUCK0_CTRL6_buck0_ocp_toff_START  (3)
#define PMIC_BUCK0_CTRL6_buck0_ocp_toff_END    (4)
#define PMIC_BUCK0_CTRL6_buck0_dmd_sel_START   (5)
#define PMIC_BUCK0_CTRL6_buck0_dmd_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL7_UNION
 �ṹ˵��  : BUCK0_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x06B����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ton_dmd     : 1;  /* bit[0]  : buck0����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
        unsigned char  buck0_eco_dmd     : 1;  /* bit[1]  : ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ƣ� */
        unsigned char  buck0_cmp_filter  : 1;  /* bit[2]  : �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned char  buck0_ocp_delay   : 1;  /* bit[3]  : ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned char  buck0_dmd_clamp   : 1;  /* bit[4]  : ��dmdǶλʹ���źţ�0�����ϣ�1�������ϣ� */
        unsigned char  buck0_regop_clamp : 1;  /* bit[5]  : regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܡ�0����ʹ�ܣ� */
        unsigned char  reserved          : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_BUCK0_CTRL7_UNION;
#endif
#define PMIC_BUCK0_CTRL7_buck0_ton_dmd_START      (0)
#define PMIC_BUCK0_CTRL7_buck0_ton_dmd_END        (0)
#define PMIC_BUCK0_CTRL7_buck0_eco_dmd_START      (1)
#define PMIC_BUCK0_CTRL7_buck0_eco_dmd_END        (1)
#define PMIC_BUCK0_CTRL7_buck0_cmp_filter_START   (2)
#define PMIC_BUCK0_CTRL7_buck0_cmp_filter_END     (2)
#define PMIC_BUCK0_CTRL7_buck0_ocp_delay_START    (3)
#define PMIC_BUCK0_CTRL7_buck0_ocp_delay_END      (3)
#define PMIC_BUCK0_CTRL7_buck0_dmd_clamp_START    (4)
#define PMIC_BUCK0_CTRL7_buck0_dmd_clamp_END      (4)
#define PMIC_BUCK0_CTRL7_buck0_regop_clamp_START  (5)
#define PMIC_BUCK0_CTRL7_buck0_regop_clamp_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL8_UNION
 �ṹ˵��  : BUCK0_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve : 8;  /* bit[0-7]: BUCK0���üĴ����� */
    } reg;
} PMIC_BUCK0_CTRL8_UNION;
#endif
#define PMIC_BUCK0_CTRL8_buck0_reserve_START  (0)
#define PMIC_BUCK0_CTRL8_buck0_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL0_UNION
 �ṹ˵��  : BUCK1_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x06D����ֵ:0xD5�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dbias   : 4;  /* bit[0-3]: buck1 <1:0>�Ƚ���ƫ�õ������ڣ�00~11����
                                                         buck1<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
        unsigned char  buck1_adj_rlx : 4;  /* bit[4-7]: BUCK1 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK1_CTRL0_UNION;
#endif
#define PMIC_BUCK1_CTRL0_buck1_dbias_START    (0)
#define PMIC_BUCK1_CTRL0_buck1_dbias_END      (3)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_START  (4)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL1_UNION
 �ṹ˵��  : BUCK1_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x06E����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_dt_sel   : 1;  /* bit[0]  : BUCK1 P�ܵ�N������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck1_pg_dt_sel   : 1;  /* bit[1]  : BUCK1 N�ܵ�P������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck1_nmos_switch : 1;  /* bit[2]  : buck1 eco��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned char  reserved          : 1;  /* bit[3]  : ������ */
        unsigned char  buck1_dt_sel      : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                            0���������ӳ�5ns��
                                                            1�������ӳ�5ns�� */
        unsigned char  buck1_ocp_sel     : 2;  /* bit[6-7]: BUCK1 OCP�������
                                                            00��2.627A��
                                                            01��3.198A��
                                                            10��3.753A��
                                                            11��4.318A�� */
    } reg;
} PMIC_BUCK1_CTRL1_UNION;
#endif
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_START    (0)
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_END      (0)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_START    (1)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_END      (1)
#define PMIC_BUCK1_CTRL1_buck1_nmos_switch_START  (2)
#define PMIC_BUCK1_CTRL1_buck1_nmos_switch_END    (2)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_START       (4)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_END         (5)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_START      (6)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL2_UNION
 �ṹ˵��  : BUCK1_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x06F����ֵ:0x99�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_n_sel : 2;  /* bit[0-1]: BUCK1 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck1_ng_p_sel : 2;  /* bit[2-3]: BUCK1 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck1_pg_n_sel : 2;  /* bit[4-5]: BUCK1 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck1_pg_p_sel : 2;  /* bit[6-7]: BUCK1 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK1_CTRL2_UNION;
#endif
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_START  (0)
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_END    (1)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_START  (2)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_END    (3)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_START  (4)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_END    (5)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_START  (6)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL3_UNION
 �ṹ˵��  : BUCK1_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x61�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reg_r   : 2;  /* bit[0-1]: BUCK1�ڲ�regulator���裬���ڵ���regulator����
                                                        00��2.8kHz��
                                                        01��45kHz��
                                                        10��85kHz��
                                                        11��152kHz�� */
        unsigned char  reserved      : 2;  /* bit[2-3]: ������ */
        unsigned char  buck1_reg_en  : 1;  /* bit[4]  : BUCK1�ڲ����ȵ�����ʹ���źš�
                                                        0��ʹ�ܣ�
                                                        1����ʹ�ܡ� */
        unsigned char  buck1_adj_clx : 2;  /* bit[5-6]: buck1 LX�����˲����ݵ���
                                                        ��11������ȫ���룬00������ȫ�����룩 */
        unsigned char  buck1_ocp_dis : 1;  /* bit[7]  : BUCK1 �ڲ�OCP��·�����źš�
                                                        0�������Σ�
                                                        1�����Ρ� */
    } reg;
} PMIC_BUCK1_CTRL3_UNION;
#endif
#define PMIC_BUCK1_CTRL3_buck1_reg_r_START    (0)
#define PMIC_BUCK1_CTRL3_buck1_reg_r_END      (1)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_START   (4)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_END     (4)
#define PMIC_BUCK1_CTRL3_buck1_adj_clx_START  (5)
#define PMIC_BUCK1_CTRL3_buck1_adj_clx_END    (6)
#define PMIC_BUCK1_CTRL3_buck1_ocp_dis_START  (7)
#define PMIC_BUCK1_CTRL3_buck1_ocp_dis_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL4_UNION
 �ṹ˵��  : BUCK1_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x071����ֵ:0x60�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_short_pdp  : 1;  /* bit[0]  : ��·�������μĴ�����
                                                           0��ʹ�ܶ�·������0.4V���ޣ�
                                                           1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck1_reg_ss     : 1;  /* bit[1]  : BUCK1������ʱ�ڲ�regulator״̬��
                                                           0������״̬��
                                                           1����λ���淴���� */
        unsigned char  buck1_regop_c    : 1;  /* bit[2]  : BUCK1�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                           0��slew-rate����
                                                           1��slew-rate�졣 */
        unsigned char  buck1_filter_ton : 2;  /* bit[3-4]: �Ƚ�����ë�̣�00~11���� */
        unsigned char  buck1_reg_dr     : 3;  /* bit[5-7]: BUCK1�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                           000��+/-6mV��
                                                           001��+/-12mV��
                                                           010��+/-18mV��
                                                           011��+/-24mV��
                                                           100��+/-30mV��
                                                           101��+/-36mV��
                                                           110��+/-42mV��
                                                           111��+/-48mV�� */
    } reg;
} PMIC_BUCK1_CTRL4_UNION;
#endif
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_START   (0)
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_END     (0)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_START      (1)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_END        (1)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_START     (2)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_END       (2)
#define PMIC_BUCK1_CTRL4_buck1_filter_ton_START  (3)
#define PMIC_BUCK1_CTRL4_buck1_filter_ton_END    (4)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_START      (5)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL5_UNION
 �ṹ˵��  : BUCK1_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x072����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ton      : 2;  /* bit[0-1]: BUCK1��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck1_eco_ng   : 1;  /* bit[2]  : BUCK1���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck1_reg_bias : 1;  /* bit[3]  : BUCK1�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0��0.5uA��
                                                         1��1uA�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK1_CTRL5_UNION;
#endif
#define PMIC_BUCK1_CTRL5_buck1_ton_START       (0)
#define PMIC_BUCK1_CTRL5_buck1_ton_END         (1)
#define PMIC_BUCK1_CTRL5_buck1_eco_ng_START    (2)
#define PMIC_BUCK1_CTRL5_buck1_eco_ng_END      (2)
#define PMIC_BUCK1_CTRL5_buck1_reg_bias_START  (3)
#define PMIC_BUCK1_CTRL5_buck1_reg_bias_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL6_UNION
 �ṹ˵��  : BUCK1_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x073����ֵ:0x6B�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dmd_ton  : 3;  /* bit[0-2]: buck1����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned char  buck1_ocp_toff : 2;  /* bit[3-4]: buck1����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned char  buck1_dmd_sel  : 3;  /* bit[5-7]: buck1 dmd��ѡ��000~111���� */
    } reg;
} PMIC_BUCK1_CTRL6_UNION;
#endif
#define PMIC_BUCK1_CTRL6_buck1_dmd_ton_START   (0)
#define PMIC_BUCK1_CTRL6_buck1_dmd_ton_END     (2)
#define PMIC_BUCK1_CTRL6_buck1_ocp_toff_START  (3)
#define PMIC_BUCK1_CTRL6_buck1_ocp_toff_END    (4)
#define PMIC_BUCK1_CTRL6_buck1_dmd_sel_START   (5)
#define PMIC_BUCK1_CTRL6_buck1_dmd_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL7_UNION
 �ṹ˵��  : BUCK1_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ton_dmd     : 1;  /* bit[0]  : buck1����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
        unsigned char  buck1_eco_dmd     : 1;  /* bit[1]  : ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ƣ� */
        unsigned char  buck1_cmp_filter  : 1;  /* bit[2]  : �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned char  buck1_ocp_delay   : 1;  /* bit[3]  : ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned char  buck1_dmd_clamp   : 1;  /* bit[4]  : ��dmdǶλʹ���źţ�0�����ϣ�1�������ϣ� */
        unsigned char  buck1_regop_clamp : 1;  /* bit[5]  : regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܡ�0����ʹ�ܣ� */
        unsigned char  reserved          : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_BUCK1_CTRL7_UNION;
#endif
#define PMIC_BUCK1_CTRL7_buck1_ton_dmd_START      (0)
#define PMIC_BUCK1_CTRL7_buck1_ton_dmd_END        (0)
#define PMIC_BUCK1_CTRL7_buck1_eco_dmd_START      (1)
#define PMIC_BUCK1_CTRL7_buck1_eco_dmd_END        (1)
#define PMIC_BUCK1_CTRL7_buck1_cmp_filter_START   (2)
#define PMIC_BUCK1_CTRL7_buck1_cmp_filter_END     (2)
#define PMIC_BUCK1_CTRL7_buck1_ocp_delay_START    (3)
#define PMIC_BUCK1_CTRL7_buck1_ocp_delay_END      (3)
#define PMIC_BUCK1_CTRL7_buck1_dmd_clamp_START    (4)
#define PMIC_BUCK1_CTRL7_buck1_dmd_clamp_END      (4)
#define PMIC_BUCK1_CTRL7_buck1_regop_clamp_START  (5)
#define PMIC_BUCK1_CTRL7_buck1_regop_clamp_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL8_UNION
 �ṹ˵��  : BUCK1_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x075����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve : 8;  /* bit[0-7]: BUCK1���üĴ����� */
    } reg;
} PMIC_BUCK1_CTRL8_UNION;
#endif
#define PMIC_BUCK1_CTRL8_buck1_reserve_START  (0)
#define PMIC_BUCK1_CTRL8_buck1_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL0_UNION
 �ṹ˵��  : BUCK2_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x076����ֵ:0xA5�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dbias   : 4;  /* bit[0-3]: buck2 <1:0>�Ƚ���ƫ�õ������ڣ�00~11����
                                                         buck2<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
        unsigned char  buck2_adj_rlx : 4;  /* bit[4-7]: BUCK2 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK2_CTRL0_UNION;
#endif
#define PMIC_BUCK2_CTRL0_buck2_dbias_START    (0)
#define PMIC_BUCK2_CTRL0_buck2_dbias_END      (3)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_START  (4)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL1_UNION
 �ṹ˵��  : BUCK2_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x077����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_dt_sel   : 1;  /* bit[0]  : BUCK2 P�ܵ�N������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck2_pg_dt_sel   : 1;  /* bit[1]  : BUCK2 N�ܵ�P������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck2_nmos_switch : 1;  /* bit[2]  : buck2 eco��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned char  reserved          : 1;  /* bit[3]  : ������ */
        unsigned char  buck2_dt_sel      : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                            0���������ӳ�5ns��
                                                            1�������ӳ�5ns�� */
        unsigned char  buck2_ocp_sel     : 2;  /* bit[6-7]: BUCK2 OCP�������
                                                            00��2.516A��
                                                            01��3.097A��
                                                            10��3.656A��
                                                            11��4.212A�� */
    } reg;
} PMIC_BUCK2_CTRL1_UNION;
#endif
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_START    (0)
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_END      (0)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_START    (1)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_END      (1)
#define PMIC_BUCK2_CTRL1_buck2_nmos_switch_START  (2)
#define PMIC_BUCK2_CTRL1_buck2_nmos_switch_END    (2)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_START       (4)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_END         (5)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_START      (6)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL2_UNION
 �ṹ˵��  : BUCK2_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x99�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_n_sel : 2;  /* bit[0-1]: BUCK2 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck2_ng_p_sel : 2;  /* bit[2-3]: BUCK2 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck2_pg_n_sel : 2;  /* bit[4-5]: BUCK2 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck2_pg_p_sel : 2;  /* bit[6-7]: BUCK2 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK2_CTRL2_UNION;
#endif
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_START  (0)
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_END    (1)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_START  (2)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_END    (3)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_START  (4)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_END    (5)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_START  (6)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL3_UNION
 �ṹ˵��  : BUCK2_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x079����ֵ:0x21�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reg_r   : 2;  /* bit[0-1]: BUCK2�ڲ�regulator���裬���ڵ���regulator����
                                                        00��2.8kHz��
                                                        01��45kHz��
                                                        10��85kHz��
                                                        11��152kHz�� */
        unsigned char  reserved      : 2;  /* bit[2-3]: ������ */
        unsigned char  buck2_reg_en  : 1;  /* bit[4]  : BUCK2�ڲ����ȵ�����ʹ���źš�
                                                        0��ʹ�ܣ�
                                                        1����ʹ�ܡ� */
        unsigned char  buck2_adj_clx : 2;  /* bit[5-6]: buck2 LX�����˲����ݵ���
                                                        ��11������ȫ���룬00������ȫ�����룩 */
        unsigned char  buck2_ocp_dis : 1;  /* bit[7]  : BUCK2 �ڲ�OCP��·�����źš�
                                                        0�������Σ�
                                                        1�����Ρ� */
    } reg;
} PMIC_BUCK2_CTRL3_UNION;
#endif
#define PMIC_BUCK2_CTRL3_buck2_reg_r_START    (0)
#define PMIC_BUCK2_CTRL3_buck2_reg_r_END      (1)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_START   (4)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_END     (4)
#define PMIC_BUCK2_CTRL3_buck2_adj_clx_START  (5)
#define PMIC_BUCK2_CTRL3_buck2_adj_clx_END    (6)
#define PMIC_BUCK2_CTRL3_buck2_ocp_dis_START  (7)
#define PMIC_BUCK2_CTRL3_buck2_ocp_dis_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL4_UNION
 �ṹ˵��  : BUCK2_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x07A����ֵ:0x60�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_short_pdp  : 1;  /* bit[0]  : ��·�������μĴ�����
                                                           0��ʹ�ܶ�·������0.4V���ޣ�
                                                           1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck2_reg_ss     : 1;  /* bit[1]  : BUCK2������ʱ�ڲ�regulator״̬��
                                                           0������״̬��
                                                           1����λ���淴���� */
        unsigned char  buck2_regop_c    : 1;  /* bit[2]  : BUCK2�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                           0��slew-rate����
                                                           1��slew-rate�졣 */
        unsigned char  buck2_filter_ton : 2;  /* bit[3-4]: �Ƚ�����ë�̣�00~11���� */
        unsigned char  buck2_reg_dr     : 3;  /* bit[5-7]: BUCK2�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                           000��+/-6mV��
                                                           001��+/-12mV��
                                                           010��+/-18mV��
                                                           011��+/-24mV��
                                                           100��+/-30mV��
                                                           101��+/-36mV��
                                                           110��+/-42mV��
                                                           111��+/-48mV�� */
    } reg;
} PMIC_BUCK2_CTRL4_UNION;
#endif
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_START   (0)
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_END     (0)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_START      (1)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_END        (1)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_START     (2)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_END       (2)
#define PMIC_BUCK2_CTRL4_buck2_filter_ton_START  (3)
#define PMIC_BUCK2_CTRL4_buck2_filter_ton_END    (4)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_START      (5)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL5_UNION
 �ṹ˵��  : BUCK2_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x07B����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ton      : 2;  /* bit[0-1]: BUCK2��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck2_eco_ng   : 1;  /* bit[2]  : BUCK2���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck2_reg_bias : 1;  /* bit[3]  : BUCK2�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0��0.5uA��
                                                         1��1uA�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK2_CTRL5_UNION;
#endif
#define PMIC_BUCK2_CTRL5_buck2_ton_START       (0)
#define PMIC_BUCK2_CTRL5_buck2_ton_END         (1)
#define PMIC_BUCK2_CTRL5_buck2_eco_ng_START    (2)
#define PMIC_BUCK2_CTRL5_buck2_eco_ng_END      (2)
#define PMIC_BUCK2_CTRL5_buck2_reg_bias_START  (3)
#define PMIC_BUCK2_CTRL5_buck2_reg_bias_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL6_UNION
 �ṹ˵��  : BUCK2_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x69�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dmd_ton  : 3;  /* bit[0-2]: buck2����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned char  buck2_ocp_toff : 2;  /* bit[3-4]: buck2����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned char  buck2_dmd_sel  : 3;  /* bit[5-7]: buck2 dmd��ѡ��000~111���� */
    } reg;
} PMIC_BUCK2_CTRL6_UNION;
#endif
#define PMIC_BUCK2_CTRL6_buck2_dmd_ton_START   (0)
#define PMIC_BUCK2_CTRL6_buck2_dmd_ton_END     (2)
#define PMIC_BUCK2_CTRL6_buck2_ocp_toff_START  (3)
#define PMIC_BUCK2_CTRL6_buck2_ocp_toff_END    (4)
#define PMIC_BUCK2_CTRL6_buck2_dmd_sel_START   (5)
#define PMIC_BUCK2_CTRL6_buck2_dmd_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL7_UNION
 �ṹ˵��  : BUCK2_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x07D����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ton_dmd     : 1;  /* bit[0]  : buck2����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
        unsigned char  buck2_eco_dmd     : 1;  /* bit[1]  : ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ƣ� */
        unsigned char  buck2_cmp_filter  : 1;  /* bit[2]  : �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned char  buck2_ocp_delay   : 1;  /* bit[3]  : ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned char  buck2_dmd_clamp   : 1;  /* bit[4]  : ��dmdǶλʹ���źţ�0�����ϣ�1�������ϣ� */
        unsigned char  buck2_regop_clamp : 1;  /* bit[5]  : regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܡ�0����ʹ�ܣ� */
        unsigned char  reserved          : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_BUCK2_CTRL7_UNION;
#endif
#define PMIC_BUCK2_CTRL7_buck2_ton_dmd_START      (0)
#define PMIC_BUCK2_CTRL7_buck2_ton_dmd_END        (0)
#define PMIC_BUCK2_CTRL7_buck2_eco_dmd_START      (1)
#define PMIC_BUCK2_CTRL7_buck2_eco_dmd_END        (1)
#define PMIC_BUCK2_CTRL7_buck2_cmp_filter_START   (2)
#define PMIC_BUCK2_CTRL7_buck2_cmp_filter_END     (2)
#define PMIC_BUCK2_CTRL7_buck2_ocp_delay_START    (3)
#define PMIC_BUCK2_CTRL7_buck2_ocp_delay_END      (3)
#define PMIC_BUCK2_CTRL7_buck2_dmd_clamp_START    (4)
#define PMIC_BUCK2_CTRL7_buck2_dmd_clamp_END      (4)
#define PMIC_BUCK2_CTRL7_buck2_regop_clamp_START  (5)
#define PMIC_BUCK2_CTRL7_buck2_regop_clamp_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL8_UNION
 �ṹ˵��  : BUCK2_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x07E����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve : 8;  /* bit[0-7]: BUCK2���üĴ����� */
    } reg;
} PMIC_BUCK2_CTRL8_UNION;
#endif
#define PMIC_BUCK2_CTRL8_buck2_reserve_START  (0)
#define PMIC_BUCK2_CTRL8_buck2_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL0_UNION
 �ṹ˵��  : BUCK3_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x07F����ֵ:0xA5�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dbias   : 4;  /* bit[0-3]: buck3 <1:0>�Ƚ���ƫ�õ������ڣ�00~11����
                                                         buck3<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
        unsigned char  buck3_adj_rlx : 4;  /* bit[4-7]: BUCK3 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK3_CTRL0_UNION;
#endif
#define PMIC_BUCK3_CTRL0_buck3_dbias_START    (0)
#define PMIC_BUCK3_CTRL0_buck3_dbias_END      (3)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_START  (4)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL1_UNION
 �ṹ˵��  : BUCK3_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_dt_sel   : 1;  /* bit[0]  : BUCK3 P�ܵ�N������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck3_pg_dt_sel   : 1;  /* bit[1]  : BUCK3 N�ܵ�P������ģʽѡ��
                                                            0������������������ģʽ��
                                                            1����������������ģʽ�� */
        unsigned char  buck3_nmos_switch : 1;  /* bit[2]  : buck3 eco��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned char  reserved          : 1;  /* bit[3]  : ������ */
        unsigned char  buck3_dt_sel      : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                            0���������ӳ�5ns��
                                                            1�������ӳ�5ns�� */
        unsigned char  buck3_ocp_sel     : 2;  /* bit[6-7]: BUCK3 OCP�������
                                                            00��2.489A��
                                                            01��3.070A��
                                                            10��3.629A��
                                                            11��4.190A�� */
    } reg;
} PMIC_BUCK3_CTRL1_UNION;
#endif
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_START    (0)
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_END      (0)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_START    (1)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_END      (1)
#define PMIC_BUCK3_CTRL1_buck3_nmos_switch_START  (2)
#define PMIC_BUCK3_CTRL1_buck3_nmos_switch_END    (2)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_START       (4)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_END         (5)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_START      (6)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL2_UNION
 �ṹ˵��  : BUCK3_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x081����ֵ:0x99�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_n_sel : 2;  /* bit[0-1]: BUCK3 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck3_ng_p_sel : 2;  /* bit[2-3]: BUCK3 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck3_pg_n_sel : 2;  /* bit[4-5]: BUCK3 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck3_pg_p_sel : 2;  /* bit[6-7]: BUCK3 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK3_CTRL2_UNION;
#endif
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_START  (0)
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_END    (1)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_START  (2)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_END    (3)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_START  (4)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_END    (5)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_START  (6)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL3_UNION
 �ṹ˵��  : BUCK3_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x082����ֵ:0x21�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reg_r   : 2;  /* bit[0-1]: BUCK3�ڲ�regulator���裬���ڵ���regulator����
                                                        00��2.8kHz��
                                                        01��45kHz��
                                                        10��85kHz��
                                                        11��152kHz�� */
        unsigned char  reserved      : 2;  /* bit[2-3]: ������ */
        unsigned char  buck3_reg_en  : 1;  /* bit[4]  : BUCK3�ڲ����ȵ�����ʹ���źš�
                                                        0��ʹ�ܣ�
                                                        1����ʹ�ܡ� */
        unsigned char  buck3_adj_clx : 2;  /* bit[5-6]: buck3 LX�����˲����ݵ���
                                                        ��11������ȫ���룬00������ȫ�����룩 */
        unsigned char  buck3_ocp_dis : 1;  /* bit[7]  : BUCK3 �ڲ�OCP��·�����źš�
                                                        0�������Σ�
                                                        1�����Ρ� */
    } reg;
} PMIC_BUCK3_CTRL3_UNION;
#endif
#define PMIC_BUCK3_CTRL3_buck3_reg_r_START    (0)
#define PMIC_BUCK3_CTRL3_buck3_reg_r_END      (1)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_START   (4)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_END     (4)
#define PMIC_BUCK3_CTRL3_buck3_adj_clx_START  (5)
#define PMIC_BUCK3_CTRL3_buck3_adj_clx_END    (6)
#define PMIC_BUCK3_CTRL3_buck3_ocp_dis_START  (7)
#define PMIC_BUCK3_CTRL3_buck3_ocp_dis_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL4_UNION
 �ṹ˵��  : BUCK3_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x083����ֵ:0x60�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_short_pdp  : 1;  /* bit[0]  : ��·�������μĴ�����
                                                           0��ʹ�ܶ�·������0.4V���ޣ�
                                                           1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck3_reg_ss     : 1;  /* bit[1]  : BUCK3������ʱ�ڲ�regulator״̬��
                                                           0������״̬��
                                                           1����λ���淴���� */
        unsigned char  buck3_regop_c    : 1;  /* bit[2]  : BUCK3�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                           0��slew-rate����
                                                           1��slew-rate�졣 */
        unsigned char  buck3_filter_ton : 2;  /* bit[3-4]: �Ƚ�����ë�̣�00~11���� */
        unsigned char  buck3_reg_dr     : 3;  /* bit[5-7]: BUCK3�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                           000��+/-6mV��
                                                           001��+/-12mV��
                                                           010��+/-18mV��
                                                           011��+/-24mV��
                                                           100��+/-30mV��
                                                           101��+/-36mV��
                                                           110��+/-42mV��
                                                           111��+/-48mV�� */
    } reg;
} PMIC_BUCK3_CTRL4_UNION;
#endif
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_START   (0)
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_END     (0)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_START      (1)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_END        (1)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_START     (2)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_END       (2)
#define PMIC_BUCK3_CTRL4_buck3_filter_ton_START  (3)
#define PMIC_BUCK3_CTRL4_buck3_filter_ton_END    (4)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_START      (5)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL5_UNION
 �ṹ˵��  : BUCK3_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ton      : 2;  /* bit[0-1]: BUCK3��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck3_eco_ng   : 1;  /* bit[2]  : BUCK3���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck3_reg_bias : 1;  /* bit[3]  : BUCK3�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK3_CTRL5_UNION;
#endif
#define PMIC_BUCK3_CTRL5_buck3_ton_START       (0)
#define PMIC_BUCK3_CTRL5_buck3_ton_END         (1)
#define PMIC_BUCK3_CTRL5_buck3_eco_ng_START    (2)
#define PMIC_BUCK3_CTRL5_buck3_eco_ng_END      (2)
#define PMIC_BUCK3_CTRL5_buck3_reg_bias_START  (3)
#define PMIC_BUCK3_CTRL5_buck3_reg_bias_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL6_UNION
 �ṹ˵��  : BUCK3_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x085����ֵ:0x69�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dmd_ton  : 3;  /* bit[0-2]: buck3����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned char  buck3_ocp_toff : 2;  /* bit[3-4]: buck3����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned char  buck3_dmd_sel  : 3;  /* bit[5-7]: buck3 dmd��ѡ��000~111���� */
    } reg;
} PMIC_BUCK3_CTRL6_UNION;
#endif
#define PMIC_BUCK3_CTRL6_buck3_dmd_ton_START   (0)
#define PMIC_BUCK3_CTRL6_buck3_dmd_ton_END     (2)
#define PMIC_BUCK3_CTRL6_buck3_ocp_toff_START  (3)
#define PMIC_BUCK3_CTRL6_buck3_ocp_toff_END    (4)
#define PMIC_BUCK3_CTRL6_buck3_dmd_sel_START   (5)
#define PMIC_BUCK3_CTRL6_buck3_dmd_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL7_UNION
 �ṹ˵��  : BUCK3_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x086����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ton_dmd     : 1;  /* bit[0]  : buck3����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
        unsigned char  buck3_eco_dmd     : 1;  /* bit[1]  : ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ƣ� */
        unsigned char  buck3_cmp_filter  : 1;  /* bit[2]  : �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned char  buck3_ocp_delay   : 1;  /* bit[3]  : ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned char  buck3_dmd_clamp   : 1;  /* bit[4]  : ��dmdǶλʹ���źţ�0�����ϣ�1�������ϣ� */
        unsigned char  buck3_regop_clamp : 1;  /* bit[5]  : regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܡ�0����ʹ�ܣ� */
        unsigned char  reserved          : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_BUCK3_CTRL7_UNION;
#endif
#define PMIC_BUCK3_CTRL7_buck3_ton_dmd_START      (0)
#define PMIC_BUCK3_CTRL7_buck3_ton_dmd_END        (0)
#define PMIC_BUCK3_CTRL7_buck3_eco_dmd_START      (1)
#define PMIC_BUCK3_CTRL7_buck3_eco_dmd_END        (1)
#define PMIC_BUCK3_CTRL7_buck3_cmp_filter_START   (2)
#define PMIC_BUCK3_CTRL7_buck3_cmp_filter_END     (2)
#define PMIC_BUCK3_CTRL7_buck3_ocp_delay_START    (3)
#define PMIC_BUCK3_CTRL7_buck3_ocp_delay_END      (3)
#define PMIC_BUCK3_CTRL7_buck3_dmd_clamp_START    (4)
#define PMIC_BUCK3_CTRL7_buck3_dmd_clamp_END      (4)
#define PMIC_BUCK3_CTRL7_buck3_regop_clamp_START  (5)
#define PMIC_BUCK3_CTRL7_buck3_regop_clamp_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL8_UNION
 �ṹ˵��  : BUCK3_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x087����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve : 8;  /* bit[0-7]: BUCK3���üĴ����� */
    } reg;
} PMIC_BUCK3_CTRL8_UNION;
#endif
#define PMIC_BUCK3_CTRL8_buck3_reserve_START  (0)
#define PMIC_BUCK3_CTRL8_buck3_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK_RESERVE0_UNION
 �ṹ˵��  : BUCK_RESERVE0 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0 : 8;  /* bit[0-7]: BUCK���üĴ��� */
    } reg;
} PMIC_BUCK_RESERVE0_UNION;
#endif
#define PMIC_BUCK_RESERVE0_buck_reserve0_START  (0)
#define PMIC_BUCK_RESERVE0_buck_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK_RESERVE1_UNION
 �ṹ˵��  : BUCK_RESERVE1 �Ĵ����ṹ���塣��ַƫ����:0x089����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1 : 8;  /* bit[0-7]: BUCK���üĴ��� */
    } reg;
} PMIC_BUCK_RESERVE1_UNION;
#endif
#define PMIC_BUCK_RESERVE1_buck_reserve1_START  (0)
#define PMIC_BUCK_RESERVE1_buck_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_1_CTRL_UNION
 �ṹ˵��  : LDO_1_CTRL �Ĵ����ṹ���塣��ַƫ����:0x08A����ֵ:0x11�����:8
 �Ĵ���˵��: LDO0_2/LDO1���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vrset     : 3;  /* bit[0-2]: LDO1���ص����ʲ���������
                                                         000����������
                                                         001������5mV��
                                                         010������10mV��
                                                         011������15mV��
                                                         100������20mV��
                                                         101������25mV��
                                                         110������30mV��
                                                         111������35mV�� */
        unsigned char  ldo1_ocp_enn   : 1;  /* bit[3]  : LDO1����ģʽѡ���źš�
                                                         0����ʾ�澯������
                                                         1����ʾ�澯�������� */
        unsigned char  ldo0_2_vrset   : 3;  /* bit[4-6]: LDO0���ص����ʲ���������
                                                         000����������
                                                         001������5mV��
                                                         010������10mV��
                                                         011������15mV��
                                                         100������20mV��
                                                         101������25mV��
                                                         110������30mV��
                                                         111������35mV�� */
        unsigned char  ldo0_2_ocp_enn : 1;  /* bit[7]  : LDO0����ģʽѡ���źš�
                                                         0����ʾ�澯������
                                                         1����ʾ�澯�������� */
    } reg;
} PMIC_LDO_1_CTRL_UNION;
#endif
#define PMIC_LDO_1_CTRL_ldo1_vrset_START      (0)
#define PMIC_LDO_1_CTRL_ldo1_vrset_END        (2)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_START    (3)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_END      (3)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_START    (4)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_END      (6)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_START  (7)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_CTRL_0_UNION
 �ṹ˵��  : LDO1_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x08B����ֵ:0x60�����:8
 �Ĵ���˵��: LDO1���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_ref_buf_bypass : 1;  /* bit[0]  : LDO1��REF�Ƿ������˷ţ�ֱ��ͨ��PIN�������
                                                              0���������˷ţ�
                                                              1�������˷š� */
        unsigned char  ldo1_psrr2_set      : 3;  /* bit[1-3]: LDO1 PSRR ������·2�ĵ�λ���ڣ�000��ʾ���������ܣ�������λӰ���������� */
        unsigned char  ldo1_psrr1_set      : 3;  /* bit[4-6]: LDO1 PSRR ������·1�ĵ�λ���ڣ�000��ʾ���������ܣ�������λӰ���������� */
        unsigned char  ldo1_psrr_en        : 1;  /* bit[7]  : LDO1 PSRR ������·ʹ���źš�
                                                              0������رգ�
                                                              1������ʹ�ܡ� */
    } reg;
} PMIC_LDO1_CTRL_0_UNION;
#endif
#define PMIC_LDO1_CTRL_0_ldo1_ref_buf_bypass_START  (0)
#define PMIC_LDO1_CTRL_0_ldo1_ref_buf_bypass_END    (0)
#define PMIC_LDO1_CTRL_0_ldo1_psrr2_set_START       (1)
#define PMIC_LDO1_CTRL_0_ldo1_psrr2_set_END         (3)
#define PMIC_LDO1_CTRL_0_ldo1_psrr1_set_START       (4)
#define PMIC_LDO1_CTRL_0_ldo1_psrr1_set_END         (6)
#define PMIC_LDO1_CTRL_0_ldo1_psrr_en_START         (7)
#define PMIC_LDO1_CTRL_0_ldo1_psrr_en_END           (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_CTRL_1_UNION
 �ṹ˵��  : LDO1_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x58�����:8
 �Ĵ���˵��: LDO1���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_ocps_en      : 1;  /* bit[0]  : LDO1��S-clamp OCP��·������ʹ���źš�0���رգ�
                                                            1��ʹ�ܡ�  */
        unsigned char  ldo1_bw_en        : 1;  /* bit[1]  : LDO1 buffer��·�����ĵ���ʹ�ܡ�
                                                            0����ʾ�渺�ر仯��
                                                            1����ʾ���渺�ر仯�� */
        unsigned char  ldo1_vgpr_en      : 1;  /* bit[2]  : LDO1�� POWER��gate��ѹ������
                                                            0���رգ�
                                                            1�������� */
        unsigned char  ldo1_ref_buf_rset : 2;  /* bit[3-4]: LDO1��REF�˷ź�����˲�����ѡ��(00:��С; 11���) */
        unsigned char  ldo1_comp         : 3;  /* bit[5-7]: LDO1�Ĳ������� */
    } reg;
} PMIC_LDO1_CTRL_1_UNION;
#endif
#define PMIC_LDO1_CTRL_1_ldo1_ocps_en_START       (0)
#define PMIC_LDO1_CTRL_1_ldo1_ocps_en_END         (0)
#define PMIC_LDO1_CTRL_1_ldo1_bw_en_START         (1)
#define PMIC_LDO1_CTRL_1_ldo1_bw_en_END           (1)
#define PMIC_LDO1_CTRL_1_ldo1_vgpr_en_START       (2)
#define PMIC_LDO1_CTRL_1_ldo1_vgpr_en_END         (2)
#define PMIC_LDO1_CTRL_1_ldo1_ref_buf_rset_START  (3)
#define PMIC_LDO1_CTRL_1_ldo1_ref_buf_rset_END    (4)
#define PMIC_LDO1_CTRL_1_ldo1_comp_START          (5)
#define PMIC_LDO1_CTRL_1_ldo1_comp_END            (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO2_3_CTRL_UNION
 �ṹ˵��  : LDO2_3_CTRL �Ĵ����ṹ���塣��ַƫ����:0x08D����ֵ:0x11�����:8
 �Ĵ���˵��: LDO2/LDO3���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vrset   : 3;  /* bit[0-2]: LDO3���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo3_ocp_enn : 1;  /* bit[3]  : LDO3����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo2_vrset   : 3;  /* bit[4-6]: LDO2���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo2_ocp_enn : 1;  /* bit[7]  : LDO2����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LDO2_3_CTRL_UNION;
#endif
#define PMIC_LDO2_3_CTRL_ldo3_vrset_START    (0)
#define PMIC_LDO2_3_CTRL_ldo3_vrset_END      (2)
#define PMIC_LDO2_3_CTRL_ldo3_ocp_enn_START  (3)
#define PMIC_LDO2_3_CTRL_ldo3_ocp_enn_END    (3)
#define PMIC_LDO2_3_CTRL_ldo2_vrset_START    (4)
#define PMIC_LDO2_3_CTRL_ldo2_vrset_END      (6)
#define PMIC_LDO2_3_CTRL_ldo2_ocp_enn_START  (7)
#define PMIC_LDO2_3_CTRL_ldo2_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_CTRL_UNION
 �ṹ˵��  : LDO3_CTRL �Ĵ����ṹ���塣��ַƫ����:0x08E����ֵ:0x88�����:8
 �Ĵ���˵��: LDO3���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_i_sst     : 1;  /* bit[0]  : ldo3�Ļ�������������
                                                         0����ʾ��������ΪĬ��ֵ��
                                                         1����ʾ������������ */
        unsigned char  ldo3_psrr2_set : 3;  /* bit[1-3]: ldo3 PSRR ������·1�ĵ�λ���ڣ���λӰ���������� */
        unsigned char  ldo3_psrr1_set : 3;  /* bit[4-6]: ldo3 PSRR ������·1�ĵ�λ���ڣ���λӰ���������� */
        unsigned char  ldo3_psrr_en   : 1;  /* bit[7]  : ldo3 PSRR ������·ʹ�� */
    } reg;
} PMIC_LDO3_CTRL_UNION;
#endif
#define PMIC_LDO3_CTRL_ldo3_i_sst_START      (0)
#define PMIC_LDO3_CTRL_ldo3_i_sst_END        (0)
#define PMIC_LDO3_CTRL_ldo3_psrr2_set_START  (1)
#define PMIC_LDO3_CTRL_ldo3_psrr2_set_END    (3)
#define PMIC_LDO3_CTRL_ldo3_psrr1_set_START  (4)
#define PMIC_LDO3_CTRL_ldo3_psrr1_set_END    (6)
#define PMIC_LDO3_CTRL_ldo3_psrr_en_START    (7)
#define PMIC_LDO3_CTRL_ldo3_psrr_en_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_5_CTRL_UNION
 �ṹ˵��  : LDO4_5_CTRL �Ĵ����ṹ���塣��ַƫ����:0x08F����ֵ:0x11�����:8
 �Ĵ���˵��: LDO4/LDO5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vrset   : 3;  /* bit[0-2]: LDO5���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo5_ocp_enn : 1;  /* bit[3]  : LDO5����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo4_vrset   : 3;  /* bit[4-6]: LDO4���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo4_ocp_enn : 1;  /* bit[7]  : LDO4����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LDO4_5_CTRL_UNION;
#endif
#define PMIC_LDO4_5_CTRL_ldo5_vrset_START    (0)
#define PMIC_LDO4_5_CTRL_ldo5_vrset_END      (2)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_START  (3)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_END    (3)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_START    (4)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_END      (6)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_START  (7)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_8_CTRL_UNION
 �ṹ˵��  : LDO7_8_CTRL �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x11�����:8
 �Ĵ���˵��: LDO7/LDO8���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vrset   : 3;  /* bit[0-2]: LDO8���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo8_ocp_enn : 1;  /* bit[3]  : LDO8����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo7_vrset   : 3;  /* bit[4-6]: LDO7���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo7_ocp_enn : 1;  /* bit[7]  : LDO7����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LDO7_8_CTRL_UNION;
#endif
#define PMIC_LDO7_8_CTRL_ldo8_vrset_START    (0)
#define PMIC_LDO7_8_CTRL_ldo8_vrset_END      (2)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_START  (3)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_END    (3)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_START    (4)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_END      (6)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_START  (7)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_10_CTRL_UNION
 �ṹ˵��  : LDO9_10_CTRL �Ĵ����ṹ���塣��ַƫ����:0x091����ֵ:0x11�����:8
 �Ĵ���˵��: LDO9/LDO10���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vrset   : 3;  /* bit[0-2]: LDO10���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo10_ocp_enn : 1;  /* bit[3]  : LDO10����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo9_vrset    : 3;  /* bit[4-6]: LDO9���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo9_ocp_enn  : 1;  /* bit[7]  : LDO9����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO9_10_CTRL_UNION;
#endif
#define PMIC_LDO9_10_CTRL_ldo10_vrset_START    (0)
#define PMIC_LDO9_10_CTRL_ldo10_vrset_END      (2)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_START  (3)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_END    (3)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_START     (4)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_END       (6)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_START   (7)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_LD11_12_CTRL_UNION
 �ṹ˵��  : LD11_12_CTRL �Ĵ����ṹ���塣��ַƫ����:0x092����ֵ:0x11�����:8
 �Ĵ���˵��: LDO11/LDO12���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vrset   : 3;  /* bit[0-2]: LDO12���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo12_ocp_enn : 1;  /* bit[3]  : LDO12����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo11_vrset   : 3;  /* bit[4-6]: LDO11���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo11_ocp_enn : 1;  /* bit[7]  : LDO11����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LD11_12_CTRL_UNION;
#endif
#define PMIC_LD11_12_CTRL_ldo12_vrset_START    (0)
#define PMIC_LD11_12_CTRL_ldo12_vrset_END      (2)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_START  (3)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_END    (3)
#define PMIC_LD11_12_CTRL_ldo11_vrset_START    (4)
#define PMIC_LD11_12_CTRL_ldo11_vrset_END      (6)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_START  (7)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_14_CTRL_UNION
 �ṹ˵��  : LDO13_14_CTRL �Ĵ����ṹ���塣��ַƫ����:0x093����ֵ:0x11�����:8
 �Ĵ���˵��: LDO13/LDO14���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vrset   : 3;  /* bit[0-2]: LDO14���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo14_ocp_enn : 1;  /* bit[3]  : LDO14����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo13_vrset   : 3;  /* bit[4-6]: LDO13���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo13_ocp_enn : 1;  /* bit[7]  : LDO13����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO13_14_CTRL_UNION;
#endif
#define PMIC_LDO13_14_CTRL_ldo14_vrset_START    (0)
#define PMIC_LDO13_14_CTRL_ldo14_vrset_END      (2)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_START  (3)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_END    (3)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_START    (4)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_END      (6)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_START  (7)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_16_CTRL_UNION
 �ṹ˵��  : LDO15_16_CTRL �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x11�����:8
 �Ĵ���˵��: LDO15/LDO16���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vrset   : 3;  /* bit[0-2]: LDO16���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo16_ocp_enn : 1;  /* bit[3]  : LDO16����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo15_vrset   : 3;  /* bit[4-6]: LDO15���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo15_ocp_enn : 1;  /* bit[7]  : LDO15����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO15_16_CTRL_UNION;
#endif
#define PMIC_LDO15_16_CTRL_ldo16_vrset_START    (0)
#define PMIC_LDO15_16_CTRL_ldo16_vrset_END      (2)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_START  (3)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_END    (3)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_START    (4)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_END      (6)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_START  (7)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_19_CTRL_UNION
 �ṹ˵��  : LDO17_19_CTRL �Ĵ����ṹ���塣��ַƫ����:0x095����ֵ:0x11�����:8
 �Ĵ���˵��: LDO17/LDO19���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vrset   : 3;  /* bit[0-2]: LDO19���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo19_ocp_enn : 1;  /* bit[3]  : LDO19����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo17_vrset   : 3;  /* bit[4-6]: LDO17���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo17_ocp_enn : 1;  /* bit[7]  : LDO17����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO17_19_CTRL_UNION;
#endif
#define PMIC_LDO17_19_CTRL_ldo19_vrset_START    (0)
#define PMIC_LDO17_19_CTRL_ldo19_vrset_END      (2)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_START  (3)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_END    (3)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_START    (4)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_END      (6)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_START  (7)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_21_CTRL_UNION
 �ṹ˵��  : LDO20_21_CTRL �Ĵ����ṹ���塣��ַƫ����:0x096����ֵ:0x11�����:8
 �Ĵ���˵��: LDO20/LDO21���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vrset   : 3;  /* bit[0-2]: LDO21���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo21_ocp_enn : 1;  /* bit[3]  : LDO21����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo20_vrset   : 3;  /* bit[4-6]: LDO20���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo20_ocp_enn : 1;  /* bit[7]  : LDO20����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO20_21_CTRL_UNION;
#endif
#define PMIC_LDO20_21_CTRL_ldo21_vrset_START    (0)
#define PMIC_LDO20_21_CTRL_ldo21_vrset_END      (2)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_START  (3)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_END    (3)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_START    (4)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_END      (6)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_START  (7)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_CTRL0_UNION
 �ṹ˵��  : LDO22_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x097����ֵ:0x01�����:8
 �Ĵ���˵��: LDO22���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vrset   : 3;  /* bit[0-2]: LDO22���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo22_ocp_enn : 1;  /* bit[3]  : LDO22����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_LDO22_CTRL0_UNION;
#endif
#define PMIC_LDO22_CTRL0_ldo22_vrset_START    (0)
#define PMIC_LDO22_CTRL0_ldo22_vrset_END      (2)
#define PMIC_LDO22_CTRL0_ldo22_ocp_enn_START  (3)
#define PMIC_LDO22_CTRL0_ldo22_ocp_enn_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_CTRL1_UNION
 �ṹ˵��  : LDO22_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x60�����:8
 �Ĵ���˵��: LDO22���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_ref_buf_bypass : 1;  /* bit[0]  : ldo22��REF�Ƿ������˷ţ�ֱ��ͨ��PIN�������
                                                               0���������˷ţ�
                                                               1�������˷š� */
        unsigned char  ldo22_psrr2_set      : 3;  /* bit[1-3]: ldo22 PSRR ������·2�ĵ�λ���ڣ�000��ʾ���������ܣ�������λӰ���������� */
        unsigned char  ldo22_psrr1_set      : 3;  /* bit[4-6]: ldo22 PSRR ������·1�ĵ�λ���ڣ�000��ʾ���������ܣ�������λӰ���������� */
        unsigned char  ldo22_psrr_en        : 1;  /* bit[7]  : ldo22 PSRR ������·ʹ���źš�
                                                               0������رգ�
                                                               1������ʹ�ܡ� */
    } reg;
} PMIC_LDO22_CTRL1_UNION;
#endif
#define PMIC_LDO22_CTRL1_ldo22_ref_buf_bypass_START  (0)
#define PMIC_LDO22_CTRL1_ldo22_ref_buf_bypass_END    (0)
#define PMIC_LDO22_CTRL1_ldo22_psrr2_set_START       (1)
#define PMIC_LDO22_CTRL1_ldo22_psrr2_set_END         (3)
#define PMIC_LDO22_CTRL1_ldo22_psrr1_set_START       (4)
#define PMIC_LDO22_CTRL1_ldo22_psrr1_set_END         (6)
#define PMIC_LDO22_CTRL1_ldo22_psrr_en_START         (7)
#define PMIC_LDO22_CTRL1_ldo22_psrr_en_END           (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_CTRL2_UNION
 �ṹ˵��  : LDO22_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x099����ֵ:0x58�����:8
 �Ĵ���˵��: LDO22���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_ocps_en      : 1;  /* bit[0]  : ldo22��S-clamp OCP��·������ʹ���źš�0���رգ�
                                                             1��ʹ�ܡ�  */
        unsigned char  ldo22_bw_en        : 1;  /* bit[1]  : ldo22 buffer��·�����ĵ���ʹ�ܡ�
                                                             0����ʾ�渺�ر仯��
                                                             1����ʾ���渺�ر仯�� */
        unsigned char  ldo22_vgpr_en      : 1;  /* bit[2]  : ldo22�� POWER��gate��ѹ������
                                                             0���رգ�
                                                             1�������� */
        unsigned char  ldo22_ref_buf_rset : 2;  /* bit[3-4]: ldo22��REF�˷ź�����˲�����ѡ��(00:��С; 11���) */
        unsigned char  ldo22_comp         : 3;  /* bit[5-7]: ldo22�Ĳ������� */
    } reg;
} PMIC_LDO22_CTRL2_UNION;
#endif
#define PMIC_LDO22_CTRL2_ldo22_ocps_en_START       (0)
#define PMIC_LDO22_CTRL2_ldo22_ocps_en_END         (0)
#define PMIC_LDO22_CTRL2_ldo22_bw_en_START         (1)
#define PMIC_LDO22_CTRL2_ldo22_bw_en_END           (1)
#define PMIC_LDO22_CTRL2_ldo22_vgpr_en_START       (2)
#define PMIC_LDO22_CTRL2_ldo22_vgpr_en_END         (2)
#define PMIC_LDO22_CTRL2_ldo22_ref_buf_rset_START  (3)
#define PMIC_LDO22_CTRL2_ldo22_ref_buf_rset_END    (4)
#define PMIC_LDO22_CTRL2_ldo22_comp_START          (5)
#define PMIC_LDO22_CTRL2_ldo22_comp_END            (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO23_CTRL_UNION
 �ṹ˵��  : LDO23_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09A����ֵ:0x01�����:8
 �Ĵ���˵��: LDO23���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vrset   : 3;  /* bit[0-2]: LDO23���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo23_ocp_enn : 1;  /* bit[3]  : LDO23����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_LDO23_CTRL_UNION;
#endif
#define PMIC_LDO23_CTRL_ldo23_vrset_START    (0)
#define PMIC_LDO23_CTRL_ldo23_vrset_END      (2)
#define PMIC_LDO23_CTRL_ldo23_ocp_enn_START  (3)
#define PMIC_LDO23_CTRL_ldo23_ocp_enn_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_25_CTRL_UNION
 �ṹ˵��  : LDO24_25_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09B����ֵ:0x11�����:8
 �Ĵ���˵��: LDO24/LDO25���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vrset   : 3;  /* bit[0-2]: LDO25���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo25_ocp_enn : 1;  /* bit[3]  : LDO25����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo24_vrset   : 3;  /* bit[4-6]: LDO24���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo24_ocp_enn : 1;  /* bit[7]  : LDO24����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO24_25_CTRL_UNION;
#endif
#define PMIC_LDO24_25_CTRL_ldo25_vrset_START    (0)
#define PMIC_LDO24_25_CTRL_ldo25_vrset_END      (2)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_START  (3)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_END    (3)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_START    (4)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_END      (6)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_START  (7)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_CTRL_UNION
 �ṹ˵��  : LDO26_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x01�����:8
 �Ĵ���˵��: LDO26���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vrset   : 3;  /* bit[0-2]: LDO26���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo26_ocp_enn : 1;  /* bit[3]  : LDO26����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo26_i_sst   : 1;  /* bit[4]  : LDO26�Ļ�������������
                                                        0����ʾ��������ΪĬ��ֵ��
                                                        1����ʾ������������ */
        unsigned char  reserved      : 3;  /* bit[5-7]: ���� */
    } reg;
} PMIC_LDO26_CTRL_UNION;
#endif
#define PMIC_LDO26_CTRL_ldo26_vrset_START    (0)
#define PMIC_LDO26_CTRL_ldo26_vrset_END      (2)
#define PMIC_LDO26_CTRL_ldo26_ocp_enn_START  (3)
#define PMIC_LDO26_CTRL_ldo26_ocp_enn_END    (3)
#define PMIC_LDO26_CTRL_ldo26_i_sst_START    (4)
#define PMIC_LDO26_CTRL_ldo26_i_sst_END      (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO27_CTRL_UNION
 �ṹ˵��  : LDO27_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09D����ֵ:0x01�����:8
 �Ĵ���˵��: LDO27���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vrset   : 3;  /* bit[0-2]: LDO27���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo27_ocp_enn : 1;  /* bit[3]  : LDO27����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_LDO27_CTRL_UNION;
#endif
#define PMIC_LDO27_CTRL_ldo27_vrset_START    (0)
#define PMIC_LDO27_CTRL_ldo27_vrset_END      (2)
#define PMIC_LDO27_CTRL_ldo27_ocp_enn_START  (3)
#define PMIC_LDO27_CTRL_ldo27_ocp_enn_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_29_CTRL_UNION
 �ṹ˵��  : LDO28_29_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09E����ֵ:0x11�����:8
 �Ĵ���˵��: LDO28/LDO29���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vrset   : 3;  /* bit[0-2]: LDO29���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo29_ocp_enn : 1;  /* bit[3]  : LDO29����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo28_vrset   : 3;  /* bit[4-6]: LDO28���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo28_ocp_enn : 1;  /* bit[7]  : LDO28����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO28_29_CTRL_UNION;
#endif
#define PMIC_LDO28_29_CTRL_ldo29_vrset_START    (0)
#define PMIC_LDO28_29_CTRL_ldo29_vrset_END      (2)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_START  (3)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_END    (3)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_START    (4)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_END      (6)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_START  (7)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_32_CTRL_UNION
 �ṹ˵��  : LDO31_32_CTRL �Ĵ����ṹ���塣��ַƫ����:0x09F����ֵ:0x11�����:8
 �Ĵ���˵��: LDO31/LDO32���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vrset   : 3;  /* bit[0-2]: LDO32���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo32_ocp_enn : 1;  /* bit[3]  : LDO32����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo31_vrset   : 3;  /* bit[4-6]: LDO31���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo31_ocp_enn : 1;  /* bit[7]  : LDO31����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO31_32_CTRL_UNION;
#endif
#define PMIC_LDO31_32_CTRL_ldo32_vrset_START    (0)
#define PMIC_LDO31_32_CTRL_ldo32_vrset_END      (2)
#define PMIC_LDO31_32_CTRL_ldo32_ocp_enn_START  (3)
#define PMIC_LDO31_32_CTRL_ldo32_ocp_enn_END    (3)
#define PMIC_LDO31_32_CTRL_ldo31_vrset_START    (4)
#define PMIC_LDO31_32_CTRL_ldo31_vrset_END      (6)
#define PMIC_LDO31_32_CTRL_ldo31_ocp_enn_START  (7)
#define PMIC_LDO31_32_CTRL_ldo31_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO33_LDO34_CTRL_UNION
 �ṹ˵��  : LDO33_LDO34_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x11�����:8
 �Ĵ���˵��: LDO33/LDO34���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_vrset   : 3;  /* bit[0-2]: LDO34���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo34_ocp_enn : 1;  /* bit[3]  : LDO34����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo33_vrset   : 3;  /* bit[4-6]: LDO33���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo33_ocp_enn : 1;  /* bit[7]  : LDO33����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO33_LDO34_CTRL_UNION;
#endif
#define PMIC_LDO33_LDO34_CTRL_ldo34_vrset_START    (0)
#define PMIC_LDO33_LDO34_CTRL_ldo34_vrset_END      (2)
#define PMIC_LDO33_LDO34_CTRL_ldo34_ocp_enn_START  (3)
#define PMIC_LDO33_LDO34_CTRL_ldo34_ocp_enn_END    (3)
#define PMIC_LDO33_LDO34_CTRL_ldo33_vrset_START    (4)
#define PMIC_LDO33_LDO34_CTRL_ldo33_vrset_END      (6)
#define PMIC_LDO33_LDO34_CTRL_ldo33_ocp_enn_START  (7)
#define PMIC_LDO33_LDO34_CTRL_ldo33_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_RESERVE0_UNION
 �ṹ˵��  : LDO_RESERVE0 �Ĵ����ṹ���塣��ַƫ����:0x0A1����ֵ:0x00�����:8
 �Ĵ���˵��: LDOԤ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo_reserve0 : 8;  /* bit[0-7]: ldoԤ���Ĵ��� */
    } reg;
} PMIC_LDO_RESERVE0_UNION;
#endif
#define PMIC_LDO_RESERVE0_ldo_reserve0_START  (0)
#define PMIC_LDO_RESERVE0_ldo_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_RESERVE1_UNION
 �ṹ˵��  : LDO_RESERVE1 �Ĵ����ṹ���塣��ַƫ����:0x0A2����ֵ:0x00�����:8
 �Ĵ���˵��: LDOԤ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo_reserve1 : 8;  /* bit[0-7]: ldoԤ���Ĵ��� */
    } reg;
} PMIC_LDO_RESERVE1_UNION;
#endif
#define PMIC_LDO_RESERVE1_ldo_reserve1_START  (0)
#define PMIC_LDO_RESERVE1_ldo_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_3_OCP_CTRL_UNION
 �ṹ˵��  : BUCK0_3_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0xFF�����:8
 �Ĵ���˵��: BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ocp_auto_stop : 2;  /* bit[0-1]: BUCK3�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck2_ocp_auto_stop : 2;  /* bit[2-3]: BUCK2�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck1_ocp_auto_stop : 2;  /* bit[4-5]: BUCK1�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck0_ocp_auto_stop : 2;  /* bit[6-7]: BUCK0�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_BUCK0_3_OCP_CTRL_UNION;
#endif
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_START  (0)
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_END    (1)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_START  (2)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_END    (3)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_START  (4)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_END    (5)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_START  (6)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_3_OCP_CTRL_UNION
 �ṹ˵��  : LDO0_3_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x101����ֵ:0xDD�����:8
 �Ĵ���˵��: BUCK4/LDO0/1/2 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_ocp_auto_stop : 2;  /* bit[0-1]: LDO3�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo2_ocp_auto_stop : 2;  /* bit[2-3]: LDO2�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo1_ocp_auto_stop : 2;  /* bit[4-5]: LDO1�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo0_ocp_auto_stop : 2;  /* bit[6-7]: LDO0�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO0_3_OCP_CTRL_UNION;
#endif
#define PMIC_LDO0_3_OCP_CTRL_ldo3_ocp_auto_stop_START  (0)
#define PMIC_LDO0_3_OCP_CTRL_ldo3_ocp_auto_stop_END    (1)
#define PMIC_LDO0_3_OCP_CTRL_ldo2_ocp_auto_stop_START  (2)
#define PMIC_LDO0_3_OCP_CTRL_ldo2_ocp_auto_stop_END    (3)
#define PMIC_LDO0_3_OCP_CTRL_ldo1_ocp_auto_stop_START  (4)
#define PMIC_LDO0_3_OCP_CTRL_ldo1_ocp_auto_stop_END    (5)
#define PMIC_LDO0_3_OCP_CTRL_ldo0_ocp_auto_stop_START  (6)
#define PMIC_LDO0_3_OCP_CTRL_ldo0_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_8_OCP_CTRL_UNION
 �ṹ˵��  : LDO4_8_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x102����ֵ:0x77�����:8
 �Ĵ���˵��: LCO3/4/5/7 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_ocp_auto_stop : 2;  /* bit[0-1]: LDO8�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo7_ocp_auto_stop : 2;  /* bit[2-3]: LDO7�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo5_ocp_auto_stop : 2;  /* bit[4-5]: LDO5�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo4_ocp_auto_stop : 2;  /* bit[6-7]: LDO4�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO4_8_OCP_CTRL_UNION;
#endif
#define PMIC_LDO4_8_OCP_CTRL_ldo8_ocp_auto_stop_START  (0)
#define PMIC_LDO4_8_OCP_CTRL_ldo8_ocp_auto_stop_END    (1)
#define PMIC_LDO4_8_OCP_CTRL_ldo7_ocp_auto_stop_START  (2)
#define PMIC_LDO4_8_OCP_CTRL_ldo7_ocp_auto_stop_END    (3)
#define PMIC_LDO4_8_OCP_CTRL_ldo5_ocp_auto_stop_START  (4)
#define PMIC_LDO4_8_OCP_CTRL_ldo5_ocp_auto_stop_END    (5)
#define PMIC_LDO4_8_OCP_CTRL_ldo4_ocp_auto_stop_START  (6)
#define PMIC_LDO4_8_OCP_CTRL_ldo4_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_12_OCP_CTRL_UNION
 �ṹ˵��  : LDO9_12_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x103����ֵ:0x75�����:8
 �Ĵ���˵��: LDO8/9/10/11 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_ocp_auto_stop : 2;  /* bit[0-1]: LDO12�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo11_ocp_auto_stop : 2;  /* bit[2-3]: LDO11�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo10_ocp_auto_stop : 2;  /* bit[4-5]: LDO10�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo9_ocp_auto_stop  : 2;  /* bit[6-7]: LDO9�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO9_12_OCP_CTRL_UNION;
#endif
#define PMIC_LDO9_12_OCP_CTRL_ldo12_ocp_auto_stop_START  (0)
#define PMIC_LDO9_12_OCP_CTRL_ldo12_ocp_auto_stop_END    (1)
#define PMIC_LDO9_12_OCP_CTRL_ldo11_ocp_auto_stop_START  (2)
#define PMIC_LDO9_12_OCP_CTRL_ldo11_ocp_auto_stop_END    (3)
#define PMIC_LDO9_12_OCP_CTRL_ldo10_ocp_auto_stop_START  (4)
#define PMIC_LDO9_12_OCP_CTRL_ldo10_ocp_auto_stop_END    (5)
#define PMIC_LDO9_12_OCP_CTRL_ldo9_ocp_auto_stop_START   (6)
#define PMIC_LDO9_12_OCP_CTRL_ldo9_ocp_auto_stop_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_16_OCP_CTRL_UNION
 �ṹ˵��  : LDO13_16_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x5D�����:8
 �Ĵ���˵��: LDO12/13/14/15 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_ocp_auto_stop : 2;  /* bit[0-1]: LDO16�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo15_ocp_auto_stop : 2;  /* bit[2-3]: LDO15�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo14_ocp_auto_stop : 2;  /* bit[4-5]: LDO14�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo13_ocp_auto_stop : 2;  /* bit[6-7]: LDO13�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO13_16_OCP_CTRL_UNION;
#endif
#define PMIC_LDO13_16_OCP_CTRL_ldo16_ocp_auto_stop_START  (0)
#define PMIC_LDO13_16_OCP_CTRL_ldo16_ocp_auto_stop_END    (1)
#define PMIC_LDO13_16_OCP_CTRL_ldo15_ocp_auto_stop_START  (2)
#define PMIC_LDO13_16_OCP_CTRL_ldo15_ocp_auto_stop_END    (3)
#define PMIC_LDO13_16_OCP_CTRL_ldo14_ocp_auto_stop_START  (4)
#define PMIC_LDO13_16_OCP_CTRL_ldo14_ocp_auto_stop_END    (5)
#define PMIC_LDO13_16_OCP_CTRL_ldo13_ocp_auto_stop_START  (6)
#define PMIC_LDO13_16_OCP_CTRL_ldo13_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_21_OCP_CTRL_UNION
 �ṹ˵��  : LDO17_21_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x105����ֵ:0x55�����:8
 �Ĵ���˵��: LDO16/17/19/20 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_ocp_auto_stop : 2;  /* bit[0-1]: LDO21�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo20_ocp_auto_stop : 2;  /* bit[2-3]: LDO20�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo19_ocp_auto_stop : 2;  /* bit[4-5]: LDO19�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo17_ocp_auto_stop : 2;  /* bit[6-7]: LDO17�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO17_21_OCP_CTRL_UNION;
#endif
#define PMIC_LDO17_21_OCP_CTRL_ldo21_ocp_auto_stop_START  (0)
#define PMIC_LDO17_21_OCP_CTRL_ldo21_ocp_auto_stop_END    (1)
#define PMIC_LDO17_21_OCP_CTRL_ldo20_ocp_auto_stop_START  (2)
#define PMIC_LDO17_21_OCP_CTRL_ldo20_ocp_auto_stop_END    (3)
#define PMIC_LDO17_21_OCP_CTRL_ldo19_ocp_auto_stop_START  (4)
#define PMIC_LDO17_21_OCP_CTRL_ldo19_ocp_auto_stop_END    (5)
#define PMIC_LDO17_21_OCP_CTRL_ldo17_ocp_auto_stop_START  (6)
#define PMIC_LDO17_21_OCP_CTRL_ldo17_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_25_OCP_CTRL_UNION
 �ṹ˵��  : LDO22_25_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x106����ֵ:0x7D�����:8
 �Ĵ���˵��: LDO21/22/23/24 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_ocp_auto_stop : 2;  /* bit[0-1]: LDO25�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo24_ocp_auto_stop : 2;  /* bit[2-3]: LDO24�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo23_ocp_auto_stop : 2;  /* bit[4-5]: LDO23�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo22_ocp_auto_stop : 2;  /* bit[6-7]: LDO22�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO22_25_OCP_CTRL_UNION;
#endif
#define PMIC_LDO22_25_OCP_CTRL_ldo25_ocp_auto_stop_START  (0)
#define PMIC_LDO22_25_OCP_CTRL_ldo25_ocp_auto_stop_END    (1)
#define PMIC_LDO22_25_OCP_CTRL_ldo24_ocp_auto_stop_START  (2)
#define PMIC_LDO22_25_OCP_CTRL_ldo24_ocp_auto_stop_END    (3)
#define PMIC_LDO22_25_OCP_CTRL_ldo23_ocp_auto_stop_START  (4)
#define PMIC_LDO22_25_OCP_CTRL_ldo23_ocp_auto_stop_END    (5)
#define PMIC_LDO22_25_OCP_CTRL_ldo22_ocp_auto_stop_START  (6)
#define PMIC_LDO22_25_OCP_CTRL_ldo22_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_29_OCP_CTRL_UNION
 �ṹ˵��  : LDO26_29_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x107����ֵ:0xF7�����:8
 �Ĵ���˵��: LDO25/26/27/28 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_ocp_auto_stop : 2;  /* bit[0-1]: LDO29�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo28_ocp_auto_stop : 2;  /* bit[2-3]: LDO28�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo27_ocp_auto_stop : 2;  /* bit[4-5]: LDO27�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo26_ocp_auto_stop : 2;  /* bit[6-7]: LDO26�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO26_29_OCP_CTRL_UNION;
#endif
#define PMIC_LDO26_29_OCP_CTRL_ldo29_ocp_auto_stop_START  (0)
#define PMIC_LDO26_29_OCP_CTRL_ldo29_ocp_auto_stop_END    (1)
#define PMIC_LDO26_29_OCP_CTRL_ldo28_ocp_auto_stop_START  (2)
#define PMIC_LDO26_29_OCP_CTRL_ldo28_ocp_auto_stop_END    (3)
#define PMIC_LDO26_29_OCP_CTRL_ldo27_ocp_auto_stop_START  (4)
#define PMIC_LDO26_29_OCP_CTRL_ldo27_ocp_auto_stop_END    (5)
#define PMIC_LDO26_29_OCP_CTRL_ldo26_ocp_auto_stop_START  (6)
#define PMIC_LDO26_29_OCP_CTRL_ldo26_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_34_OCP_CTRL_UNION
 �ṹ˵��  : LDO31_34_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x57�����:8
 �Ĵ���˵��: LDO31/32/33/34 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_ocp_auto_stop : 2;  /* bit[0-1]: LDO34�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo33_ocp_auto_stop : 2;  /* bit[2-3]: LDO33�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo32_ocp_auto_stop : 2;  /* bit[4-5]: LDO32�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo31_ocp_auto_stop : 2;  /* bit[6-7]: LDO31�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO31_34_OCP_CTRL_UNION;
#endif
#define PMIC_LDO31_34_OCP_CTRL_ldo34_ocp_auto_stop_START  (0)
#define PMIC_LDO31_34_OCP_CTRL_ldo34_ocp_auto_stop_END    (1)
#define PMIC_LDO31_34_OCP_CTRL_ldo33_ocp_auto_stop_START  (2)
#define PMIC_LDO31_34_OCP_CTRL_ldo33_ocp_auto_stop_END    (3)
#define PMIC_LDO31_34_OCP_CTRL_ldo32_ocp_auto_stop_START  (4)
#define PMIC_LDO31_34_OCP_CTRL_ldo32_ocp_auto_stop_END    (5)
#define PMIC_LDO31_34_OCP_CTRL_ldo31_ocp_auto_stop_START  (6)
#define PMIC_LDO31_34_OCP_CTRL_ldo31_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION
 �ṹ˵��  : LDO_BUFF_CLASS_SCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x109����ֵ:0x0D�����:8
 �Ĵ���˵��: LDO_BUFF SCP/CLASS OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_ocp_auto_stop      : 2;  /* bit[0-1]: class�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                                    X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                                    01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                                    11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  xo_ldo_buff_scp_auto_stop : 2;  /* bit[2-3]: xo_ldo_buff�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                                    X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                                    01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                                    11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  reserved                  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION;
#endif
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_classd_ocp_auto_stop_START       (0)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_classd_ocp_auto_stop_END         (1)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_xo_ldo_buff_scp_auto_stop_START  (2)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_xo_ldo_buff_scp_auto_stop_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_3_SCP_CTRL_UNION
 �ṹ˵��  : BUCK0_3_SCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x10A����ֵ:0xFF�����:8
 �Ĵ���˵��: BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_scp_auto_stop : 2;  /* bit[0-1]: BUCK3�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck2_scp_auto_stop : 2;  /* bit[2-3]: BUCK2�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck1_scp_auto_stop : 2;  /* bit[4-5]: BUCK1�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck0_scp_auto_stop : 2;  /* bit[6-7]: BUCK0�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_BUCK0_3_SCP_CTRL_UNION;
#endif
#define PMIC_BUCK0_3_SCP_CTRL_buck3_scp_auto_stop_START  (0)
#define PMIC_BUCK0_3_SCP_CTRL_buck3_scp_auto_stop_END    (1)
#define PMIC_BUCK0_3_SCP_CTRL_buck2_scp_auto_stop_START  (2)
#define PMIC_BUCK0_3_SCP_CTRL_buck2_scp_auto_stop_END    (3)
#define PMIC_BUCK0_3_SCP_CTRL_buck1_scp_auto_stop_START  (4)
#define PMIC_BUCK0_3_SCP_CTRL_buck1_scp_auto_stop_END    (5)
#define PMIC_BUCK0_3_SCP_CTRL_buck0_scp_auto_stop_START  (6)
#define PMIC_BUCK0_3_SCP_CTRL_buck0_scp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_PMUA_ECO_UNION
 �ṹ˵��  : LDO_PMUA_ECO �Ĵ����ṹ���塣��ַƫ����:0x10D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO_PMUA ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  st_pmua_en      : 1;  /* bit[0]  : PMUA��ģ�ӿ�״̬�Ĵ�����
                                                          0����ʾ�ر�PMUA��
                                                          1����ʾ��PMUA�� */
        unsigned char  reserved_0      : 3;  /* bit[1-3]:  */
        unsigned char  reg_pmua_eco_en : 1;  /* bit[4]  : PMUA����ECOģʽ�����źš�
                                                          0��0����normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO_PMUA_ECO_UNION;
#endif
#define PMIC_LDO_PMUA_ECO_st_pmua_en_START       (0)
#define PMIC_LDO_PMUA_ECO_st_pmua_en_END         (0)
#define PMIC_LDO_PMUA_ECO_reg_pmua_eco_en_START  (4)
#define PMIC_LDO_PMUA_ECO_reg_pmua_eco_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_PMUA_VSET_UNION
 �ṹ˵��  : LDO_PMUA_VSET �Ĵ����ṹ���塣��ַƫ����:0x10E����ֵ:0x01�����:8
 �Ĵ���˵��: LDO_PMUA��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_vset : 3;  /* bit[0-2]: LDO_PMUA�����ѹ���á�
                                                    000��1.70��
                                                    001��1.80��
                                                    010��1.90��
                                                    011��2.00��
                                                    ��������Ч�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO_PMUA_VSET_UNION;
#endif
#define PMIC_LDO_PMUA_VSET_pmua_vset_START  (0)
#define PMIC_LDO_PMUA_VSET_pmua_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_ABB_EN_UNION
 �ṹ˵��  : CLK_ABB_EN �Ĵ����ṹ���塣��ַƫ����:0x10F����ֵ:0x01�����:8
 �Ĵ���˵��: ABBʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_abb_en : 1;  /* bit[0]  : clk_abbʹ���źţ�ע��ABB buf����
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned char  reserved      : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_ABB_EN_UNION;
#endif
#define PMIC_CLK_ABB_EN_reg_xo_abb_en_START  (0)
#define PMIC_CLK_ABB_EN_reg_xo_abb_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_WIFI_EN_UNION
 �ṹ˵��  : CLK_WIFI_EN �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00�����:8
 �Ĵ���˵��: WIFIʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_wifi_en : 1;  /* bit[0]  : clk_wifiʹ���źţ�ע��WIFI buf����
                                                         0����ʹ�ܣ�
                                                         1��ʹ�ܡ� */
        unsigned char  reserved       : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_WIFI_EN_UNION;
#endif
#define PMIC_CLK_WIFI_EN_reg_xo_wifi_en_START  (0)
#define PMIC_CLK_WIFI_EN_reg_xo_wifi_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_RF0_EN_UNION
 �ṹ˵��  : CLK_RF0_EN �Ĵ����ṹ���塣��ַƫ����:0x111����ֵ:0x00�����:8
 �Ĵ���˵��: RF0ʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf0_en : 1;  /* bit[0]  : clk_rf0ʹ���źţ�ע��RF0 buf����
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned char  reserved  : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_RF0_EN_UNION;
#endif
#define PMIC_CLK_RF0_EN_xo_rf0_en_START  (0)
#define PMIC_CLK_RF0_EN_xo_rf0_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_RF1_EN_UNION
 �ṹ˵��  : CLK_RF1_EN �Ĵ����ṹ���塣��ַƫ����:0x112����ֵ:0x00�����:8
 �Ĵ���˵��: RF1ʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf1_en : 1;  /* bit[0]  : clk_rf1ʹ���źţ�ע��RF1 buf����
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned char  reserved  : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_RF1_EN_UNION;
#endif
#define PMIC_CLK_RF1_EN_xo_rf1_en_START  (0)
#define PMIC_CLK_RF1_EN_xo_rf1_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_SYS_EN_UNION
 �ṹ˵��  : CLK_SYS_EN �Ĵ����ṹ���塣��ַƫ����:0x113����ֵ:0x01�����:8
 �Ĵ���˵��: SYSʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_sys_en : 1;  /* bit[0]  : clk_sysʹ���źţ�ע:Vsys buf����
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned char  reserved      : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_SYS_EN_UNION;
#endif
#define PMIC_CLK_SYS_EN_reg_xo_sys_en_START  (0)
#define PMIC_CLK_SYS_EN_reg_xo_sys_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_CODEC_EN_UNION
 �ṹ˵��  : CLK_CODEC_EN �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00�����:8
 �Ĵ���˵��: CODECʱ�ӿ��ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_codec_en : 1;  /* bit[0]  : clk_codecʹ���ź�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CLK_CODEC_EN_UNION;
#endif
#define PMIC_CLK_CODEC_EN_reg_xo_codec_en_START  (0)
#define PMIC_CLK_CODEC_EN_reg_xo_codec_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_ABB_CTRL_UNION
 �ṹ˵��  : CLK_ABB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x115����ֵ:0x03�����:8
 �Ĵ���˵��: ABBʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_abb_drv : 2;  /* bit[0-1]: clk_abb�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  reserved   : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_CLK_ABB_CTRL_UNION;
#endif
#define PMIC_CLK_ABB_CTRL_xo_abb_drv_START  (0)
#define PMIC_CLK_ABB_CTRL_xo_abb_drv_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_WIFI_CTRL_UNION
 �ṹ˵��  : CLK_WIFI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x116����ֵ:0x05�����:8
 �Ĵ���˵��: WIFIʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_wifi_drv        : 2;  /* bit[0-1]: clk_wifi�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  np_xo_dig_wifi_sel : 1;  /* bit[2]  : 0����Ӧ������
                                                             1����Ӧ���ҡ� */
        unsigned char  reserved           : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_CLK_WIFI_CTRL_UNION;
#endif
#define PMIC_CLK_WIFI_CTRL_xo_wifi_drv_START         (0)
#define PMIC_CLK_WIFI_CTRL_xo_wifi_drv_END           (1)
#define PMIC_CLK_WIFI_CTRL_np_xo_dig_wifi_sel_START  (2)
#define PMIC_CLK_WIFI_CTRL_np_xo_dig_wifi_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_RF0_CTRL_UNION
 �ṹ˵��  : CLK_RF0_CTRL �Ĵ����ṹ���塣��ַƫ����:0x117����ֵ:0x05�����:8
 �Ĵ���˵��: RF0ʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf0_drv        : 2;  /* bit[0-1]: clk_rf0�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  np_xo_dig_rf0_sel : 1;  /* bit[2]  : 0����Ӧ������
                                                            1����Ӧ���ҡ� */
        unsigned char  reserved          : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_CLK_RF0_CTRL_UNION;
#endif
#define PMIC_CLK_RF0_CTRL_xo_rf0_drv_START         (0)
#define PMIC_CLK_RF0_CTRL_xo_rf0_drv_END           (1)
#define PMIC_CLK_RF0_CTRL_np_xo_dig_rf0_sel_START  (2)
#define PMIC_CLK_RF0_CTRL_np_xo_dig_rf0_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_RF1_CTRL_UNION
 �ṹ˵��  : CLK_RF1_CTRL �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x05�����:8
 �Ĵ���˵��: RF1ʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf1_drv        : 2;  /* bit[0-1]: clk_rf1�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  np_xo_dig_rf1_sel : 1;  /* bit[2]  : 0����Ӧ������
                                                            1����Ӧ���ҡ� */
        unsigned char  reserved          : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_CLK_RF1_CTRL_UNION;
#endif
#define PMIC_CLK_RF1_CTRL_xo_rf1_drv_START         (0)
#define PMIC_CLK_RF1_CTRL_xo_rf1_drv_END           (1)
#define PMIC_CLK_RF1_CTRL_np_xo_dig_rf1_sel_START  (2)
#define PMIC_CLK_RF1_CTRL_np_xo_dig_rf1_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_SYS_CTRL_UNION
 �ṹ˵��  : CLK_SYS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x119����ֵ:0x03�����:8
 �Ĵ���˵��: SYSʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_sys_drv : 2;  /* bit[0-1]: clk_sys�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  reserved   : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_CLK_SYS_CTRL_UNION;
#endif
#define PMIC_CLK_SYS_CTRL_xo_sys_drv_START  (0)
#define PMIC_CLK_SYS_CTRL_xo_sys_drv_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_CODEC_CTRL_UNION
 �ṹ˵��  : CLK_CODEC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x11A����ֵ:0x01�����:8
 �Ĵ���˵��: CODECʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_codec_drv : 2;  /* bit[0-1]: clk_codec�����������ƣ�00��ʾ����Ϊ3pF//100K,11��ʾ����30pF//100K */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_CLK_CODEC_CTRL_UNION;
#endif
#define PMIC_CLK_CODEC_CTRL_xo_codec_drv_START  (0)
#define PMIC_CLK_CODEC_CTRL_xo_codec_drv_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL0_UNION
 �ṹ˵��  : CLK_TOP_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x11B����ֵ:0x50�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_ldo_buff_curr : 2;  /* bit[0-1]: �ڲ�LDOƫ�õ����ơ� */
        unsigned char  reserved         : 2;  /* bit[2-3]: ������ */
        unsigned char  np_xo_trim_c2fix : 4;  /* bit[4-7]: ʱ��Ƶ�ʾ���trim�Ĵ���2����CLK_TOP_CTRL1[np_xo_c1fix]һ��ʹ�ã��� */
    } reg;
} PMIC_CLK_TOP_CTRL0_UNION;
#endif
#define PMIC_CLK_TOP_CTRL0_xo_ldo_buff_curr_START  (0)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_buff_curr_END    (1)
#define PMIC_CLK_TOP_CTRL0_np_xo_trim_c2fix_START  (4)
#define PMIC_CLK_TOP_CTRL0_np_xo_trim_c2fix_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL1_UNION
 �ṹ˵��  : CLK_TOP_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x50�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_trim_c1fix : 8;  /* bit[0-7]: ʱ��Ƶ�ʾ���trim�Ĵ���1����CLK_TOP_CTRL0[np_xo_c2fix]һ��ʹ�ã��� */
    } reg;
} PMIC_CLK_TOP_CTRL1_UNION;
#endif
#define PMIC_CLK_TOP_CTRL1_np_xo_trim_c1fix_START  (0)
#define PMIC_CLK_TOP_CTRL1_np_xo_trim_c1fix_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL2_UNION
 �ṹ˵��  : CLK_TOP_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x11D����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_delay_sel : 2;  /* bit[0-1]: ʱ�������Delayʱ��Ŀ���ѡ���ź� */
        unsigned char  xo_tri_cap   : 1;  /* bit[2]  : ʱ�ӵ����ǲ���·�ĵ��ݿ��� */
        unsigned char  reserved     : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_CLK_TOP_CTRL2_UNION;
#endif
#define PMIC_CLK_TOP_CTRL2_xo_delay_sel_START  (0)
#define PMIC_CLK_TOP_CTRL2_xo_delay_sel_END    (1)
#define PMIC_CLK_TOP_CTRL2_xo_tri_cap_START    (2)
#define PMIC_CLK_TOP_CTRL2_xo_tri_cap_END      (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL3_UNION
 �ṹ˵��  : CLK_TOP_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x11E����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve : 8;  /* bit[0-7]: xoԤ���Ĵ����� */
    } reg;
} PMIC_CLK_TOP_CTRL3_UNION;
#endif
#define PMIC_CLK_TOP_CTRL3_xo_reserve_START  (0)
#define PMIC_CLK_TOP_CTRL3_xo_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_256K_CTRL0_UNION
 �ṹ˵��  : CLK_256K_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x11F����ֵ:0x00�����:8
 �Ĵ���˵��: 256K RC���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_256k_en0 : 8;  /* bit[0-7]: RC256K�رտ��ơ�
                                                          0x5A���ر�256Kʱ�ӣ�ͬʱreg_256k_en1Ϊ0xF0����
                                                          ������������ */
    } reg;
} PMIC_CLK_256K_CTRL0_UNION;
#endif
#define PMIC_CLK_256K_CTRL0_np_reg_256k_en0_START  (0)
#define PMIC_CLK_256K_CTRL0_np_reg_256k_en0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_256K_CTRL1_UNION
 �ṹ˵��  : CLK_256K_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00�����:8
 �Ĵ���˵��: 256K RC���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_256k_en1 : 8;  /* bit[0-7]: RC256K�رտ��ơ�
                                                          0xF0���ر�256Kʱ�ӣ�ͬʱreg_256k_en0Ϊ0x5A����
                                                          ������������ */
    } reg;
} PMIC_CLK_256K_CTRL1_UNION;
#endif
#define PMIC_CLK_256K_CTRL1_np_reg_256k_en1_START  (0)
#define PMIC_CLK_256K_CTRL1_np_reg_256k_en1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OSC32K_ONOFF_CTRL_UNION
 �ṹ˵��  : OSC32K_ONOFF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x121����ֵ:0x01�����:8
 �Ĵ���˵��: 32kHzʱ�����ʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_32k_sys : 1;  /* bit[0]  : CLK32_SYS ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  en_32k_bt  : 1;  /* bit[1]  : CLK32_BT ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  en_32k_gps : 1;  /* bit[2]  : CLK32_GPS ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_OSC32K_ONOFF_CTRL_UNION;
#endif
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_START  (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_END    (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_START   (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_END     (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_START  (2)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_HARDWIRE_CTRL0_UNION
 �ṹ˵��  : HARDWIRE_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x125����ֵ:0x1F�����:8
 �Ĵ���˵��: Ӳ�����ο��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_hd_mask      : 1;  /* bit[0]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���eco_in_n������/���߿������á�
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned char  reg_xo_ldo_buff_hd_mask : 1;  /* bit[1]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���xo_ldo_buff_n������/���߿������á�
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned char  reg_sys_clk_hd_mask     : 1;  /* bit[2]  : �Ƿ�����Ӳ��SYS_CLK_EN��sys_clk�Ŀ�/�ؿ������á�
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned char  reg_abb_clk_hd_mask     : 1;  /* bit[3]  : �Ƿ�����Ӳ��SYS_CLK_EN��abb_clk�Ŀ�/�ؿ������á�
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned char  reg_wifi_clk_hd_mask    : 1;  /* bit[4]  : �Ƿ�����Ӳ��WIFIBT_CLK_EN��wifibt_clk�Ŀ�/�ؿ������á�
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned char  reserved                : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_HARDWIRE_CTRL0_UNION;
#endif
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_START       (0)
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_END         (0)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_buff_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_buff_hd_mask_END    (1)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_START      (2)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_END        (2)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_START      (3)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_END        (3)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_START     (4)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_END       (4)


/*****************************************************************************
 �ṹ��    : PMIC_HARDWIRE_CTRL1_UNION
 �ṹ˵��  : HARDWIRE_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x126����ֵ:0x0F�����:8
 �Ĵ���˵��: Ӳ�����ο��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_hd_mask : 1;  /* bit[0]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ldo27�Ŀ�/�ؿ������á�
                                                            0�������Σ�
                                                            1�����Ρ� */
        unsigned char  reg_ldo26_hd_mask : 2;  /* bit[1-2]: �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ld26�Ŀ�/�ؼ���/��eco�������á�
                                                            00��������
                                                            01����������߼���ldo26�Ŀ�/�ؿ��ƣ�����������߼���LDO26�Ľ�/��eco���ƣ����������£�ldo26��ʹ�ܼĴ�������Ϊ1��ldo26��ecoʹ�ܼĴ�������Ϊ0��ldo26�ſ����ܿ�������߼�����/��ecoģʽ����
                                                            10������������߼���LDO26�Ŀ�/�ؿ��ƣ���������߼���ldo26�Ľ�/��eco���ƣ����������£�ldo26��ʹ�ܼĴ�������Ϊ0��ldo26���п����ܿ�������߼�����/�أ���
                                                            11����������߼���ldo26�Ŀ�/�غͽ�/��eco���ƣ����������£�ldo26�Ŀ�/��ֻ�ܿ�������ʹ�ܼĴ�����ldo26�Ľ�/��eco����ֻ�ܿ��������ecoʹ�ܼĴ�������Ȼ��ʹ�ܼĴ�������Ϊ1���п�����������ecoģʽ���� */
        unsigned char  reg_ldo13_hd_mask : 1;  /* bit[3]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ldo13�Ŀ�/�ؿ������á�
                                                            0�������Σ�
                                                            1�����Ρ� */
        unsigned char  reserved          : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_HARDWIRE_CTRL1_UNION;
#endif
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_START  (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_END    (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_END    (2)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_START  (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL0_UNION
 �ṹ˵��  : PERI_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x127����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo23_on : 1;  /* bit[0]  : LDO23�ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ��������µ���ƿ�/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo10_on : 1;  /* bit[1]  : LDO10�ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ��������µ���ƿ�/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo7_on  : 1;  /* bit[2]  : LDO7�ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ��������µ���ƿ�/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo5_on  : 1;  /* bit[3]  : LDO5�ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ��������µ���ƿ�/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_buck0_on : 1;  /* bit[4]  : BUCK0�ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ��������µ���ƿ�/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  reserved         : 3;  /* bit[5-7]: ���� */
    } reg;
} PMIC_PERI_CTRL0_UNION;
#endif
#define PMIC_PERI_CTRL0_peri_en_ldo23_on_START  (0)
#define PMIC_PERI_CTRL0_peri_en_ldo23_on_END    (0)
#define PMIC_PERI_CTRL0_peri_en_ldo10_on_START  (1)
#define PMIC_PERI_CTRL0_peri_en_ldo10_on_END    (1)
#define PMIC_PERI_CTRL0_peri_en_ldo7_on_START   (2)
#define PMIC_PERI_CTRL0_peri_en_ldo7_on_END     (2)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_START   (3)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_END     (3)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_START  (4)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL1_UNION
 �ṹ˵��  : PERI_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo8_eco   : 1;  /* bit[0]: LDO8�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo4_eco   : 1;  /* bit[1]: LDO4�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo2_eco   : 1;  /* bit[2]: LDO2�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo0_2_eco : 1;  /* bit[3]: LDO0_2�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck3_eco  : 1;  /* bit[4]: BUCK3�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck2_eco  : 1;  /* bit[5]: BUCK2�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck1_eco  : 1;  /* bit[6]: BUCK1�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck0_eco  : 1;  /* bit[7]: BUCK0�͹����ܿ�Դѡ��Ĵ�����
                                                           0���ܼĴ������ƿ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
    } reg;
} PMIC_PERI_CTRL1_UNION;
#endif
#define PMIC_PERI_CTRL1_peri_en_ldo8_eco_START    (0)
#define PMIC_PERI_CTRL1_peri_en_ldo8_eco_END      (0)
#define PMIC_PERI_CTRL1_peri_en_ldo4_eco_START    (1)
#define PMIC_PERI_CTRL1_peri_en_ldo4_eco_END      (1)
#define PMIC_PERI_CTRL1_peri_en_ldo2_eco_START    (2)
#define PMIC_PERI_CTRL1_peri_en_ldo2_eco_END      (2)
#define PMIC_PERI_CTRL1_peri_en_ldo0_2_eco_START  (3)
#define PMIC_PERI_CTRL1_peri_en_ldo0_2_eco_END    (3)
#define PMIC_PERI_CTRL1_peri_en_buck3_eco_START   (4)
#define PMIC_PERI_CTRL1_peri_en_buck3_eco_END     (4)
#define PMIC_PERI_CTRL1_peri_en_buck2_eco_START   (5)
#define PMIC_PERI_CTRL1_peri_en_buck2_eco_END     (5)
#define PMIC_PERI_CTRL1_peri_en_buck1_eco_START   (6)
#define PMIC_PERI_CTRL1_peri_en_buck1_eco_END     (6)
#define PMIC_PERI_CTRL1_peri_en_buck0_eco_START   (7)
#define PMIC_PERI_CTRL1_peri_en_buck0_eco_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL2_UNION
 �ṹ˵��  : PERI_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x129����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo24_eco : 1;  /* bit[0]: LDO24�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo17_eco : 1;  /* bit[1]: LDO17�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo16_eco : 1;  /* bit[2]: LDO16�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo15_eco : 1;  /* bit[3]: LDO15�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo12_eco : 1;  /* bit[4]: LDO12�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo11_eco : 1;  /* bit[5]: LDO11�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo10_eco : 1;  /* bit[6]: LDO10�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo9_eco  : 1;  /* bit[7]: LDO9�͹����ܿ�Դѡ��Ĵ�����
                                                          0���ܼĴ������ƿ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
    } reg;
} PMIC_PERI_CTRL2_UNION;
#endif
#define PMIC_PERI_CTRL2_peri_en_ldo24_eco_START  (0)
#define PMIC_PERI_CTRL2_peri_en_ldo24_eco_END    (0)
#define PMIC_PERI_CTRL2_peri_en_ldo17_eco_START  (1)
#define PMIC_PERI_CTRL2_peri_en_ldo17_eco_END    (1)
#define PMIC_PERI_CTRL2_peri_en_ldo16_eco_START  (2)
#define PMIC_PERI_CTRL2_peri_en_ldo16_eco_END    (2)
#define PMIC_PERI_CTRL2_peri_en_ldo15_eco_START  (3)
#define PMIC_PERI_CTRL2_peri_en_ldo15_eco_END    (3)
#define PMIC_PERI_CTRL2_peri_en_ldo12_eco_START  (4)
#define PMIC_PERI_CTRL2_peri_en_ldo12_eco_END    (4)
#define PMIC_PERI_CTRL2_peri_en_ldo11_eco_START  (5)
#define PMIC_PERI_CTRL2_peri_en_ldo11_eco_END    (5)
#define PMIC_PERI_CTRL2_peri_en_ldo10_eco_START  (6)
#define PMIC_PERI_CTRL2_peri_en_ldo10_eco_END    (6)
#define PMIC_PERI_CTRL2_peri_en_ldo9_eco_START   (7)
#define PMIC_PERI_CTRL2_peri_en_ldo9_eco_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL3_UNION
 �ṹ˵��  : PERI_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x12A����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_thsd_eco  : 1;  /* bit[0]  : THSD�͹����ܿ�Դѡ��Ĵ�����
                                                            0���ܼĴ������ƿ���/��ECO��
                                                            1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_pmua_eco  : 1;  /* bit[1]  : PMUA�͹����ܿ�Դѡ��Ĵ�����
                                                            0���ܼĴ������ƿ���/��ECO��
                                                            1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo34_eco : 1;  /* bit[2]  : LDO34�͹����ܿ�Դѡ��Ĵ�����
                                                            0���ܼĴ������ƿ���/��ECO��
                                                            1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo29_eco : 1;  /* bit[3]  : LDO29�͹����ܿ�Դѡ��Ĵ�����
                                                            0���ܼĴ������ƿ���/��ECO��
                                                            1����peri_en���ƶ���/��ECO�� */
        unsigned char  reserved          : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_PERI_CTRL3_UNION;
#endif
#define PMIC_PERI_CTRL3_peri_en_thsd_eco_START   (0)
#define PMIC_PERI_CTRL3_peri_en_thsd_eco_END     (0)
#define PMIC_PERI_CTRL3_peri_en_pmua_eco_START   (1)
#define PMIC_PERI_CTRL3_peri_en_pmua_eco_END     (1)
#define PMIC_PERI_CTRL3_peri_en_ldo34_eco_START  (2)
#define PMIC_PERI_CTRL3_peri_en_ldo34_eco_END    (2)
#define PMIC_PERI_CTRL3_peri_en_ldo29_eco_START  (3)
#define PMIC_PERI_CTRL3_peri_en_ldo29_eco_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_VSET_CTRL_UNION
 �ṹ˵��  : PERI_VSET_CTRL �Ĵ����ṹ���塣��ַƫ����:0x12B����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�ߵ�ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_buck3_vset  : 1;  /* bit[0]  : BUCK3��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_buck2_vset  : 1;  /* bit[1]  : BUCK2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_buck1_vset  : 1;  /* bit[2]  : BUCK1��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo29_vset  : 1;  /* bit[3]  : LDO29��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo2_vset   : 1;  /* bit[4]  : LDO2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo0_2_vset : 1;  /* bit[5]  : LDO0_2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  reserved            : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_PERI_VSET_CTRL_UNION;
#endif
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_START   (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_END     (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_START   (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_END     (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_START   (2)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_END     (2)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_START   (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_END     (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_START    (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_END      (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_START  (5)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_TIME__CTRL_UNION
 �ṹ˵��  : PERI_TIME__CTRL �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ��ʱ�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_time_sel : 1;  /* bit[0]  : PERI_EN�����ϵ�������λ��
                                                        0��peri_en����ʱLDO�ϵ���Ϊ120us��BUCK�ϵ���Ϊ240us��
                                                        1��peri_en����ʱLDO5��LDO8�ϵ���Ϊ60us��BUCK�ϵ���Ϊ120us�� */
        unsigned char  reserved      : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_PERI_TIME__CTRL_UNION;
#endif
#define PMIC_PERI_TIME__CTRL_peri_time_sel_START  (0)
#define PMIC_PERI_TIME__CTRL_peri_time_sel_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_ECO_MASK_UNION
 �ṹ˵��  : COUL_ECO_MASK �Ĵ����ṹ���塣��ַƫ����:0x12D����ֵ:0x07�����:8
 �Ĵ���˵��: ���ؼ�ECOʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_codec_clk_en_mask : 1;  /* bit[0]  : CODEC_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  coul_wifi_clk_en_mask  : 1;  /* bit[1]  : WIFI_BT_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  coul_sys_clk_en_mask   : 1;  /* bit[2]  : SYS_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  reserved               : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_COUL_ECO_MASK_UNION;
#endif
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_START  (0)
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_END    (0)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_START   (1)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_END     (1)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_START    (2)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_END      (2)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_0_UNION
 �ṹ˵��  : IRQ_MASK_0 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK0���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_0 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]�����������ж����Σ�
                                                     bit[6]�������ͷ��ж����Σ�
                                                     bit[5]������1s�ж����Σ�
                                                     bit[4]������6s�ж����Σ�
                                                     bit[3]�������ж����Σ�
                                                     bit[2]��vbus�γ��ж����Σ�
                                                     bit[1]��vbus�����ж����Σ�
                                                     bit[0]������125���ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_0_UNION;
#endif
#define PMIC_IRQ_MASK_0_irq_mask_0_START  (0)
#define PMIC_IRQ_MASK_0_irq_mask_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_1_UNION
 �ṹ˵��  : IRQ_MASK_1 �Ĵ����ṹ���塣��ַƫ����:0x131����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK1���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_1 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7:6]������ʹ�ã��ɶ�д��
                                                     bit[5]��sim_hpd1�½����ж����Σ�
                                                     bit[4]��sim_hpd1�������ж����Σ�
                                                     bit[3]��sim_hpd0�½����ж����Σ�
                                                     bit[2]��sim_hpd0�������ж����Σ�
                                                     bit[1]�����ؼ��ж������Σ�
                                                     bit[0]��OCP�ж������Ρ� */
    } reg;
} PMIC_IRQ_MASK_1_UNION;
#endif
#define PMIC_IRQ_MASK_1_irq_mask_1_START  (0)
#define PMIC_IRQ_MASK_1_irq_mask_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_2_UNION
 �ṹ˵��  : IRQ_MASK_2 �Ĵ����ṹ���塣��ַƫ����:0x132����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK3���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_2 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��BUCK0��������ж����Σ�
                                                     bit[6]��BUCK1��������ж����Σ�
                                                     bit[5]��BUCK2��������ж����Σ�
                                                     bit[4]��BUCK3��������ж����Σ�
                                                     bit[3]��LDO0_2��������ж����Σ�
                                                     bit[2]��LDO1��������ж����Σ�
                                                     bit[1]��LDO2��������ж�����;
                                                     bit[0]��LDO3��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_2_UNION;
#endif
#define PMIC_IRQ_MASK_2_irq_mask_2_START  (0)
#define PMIC_IRQ_MASK_2_irq_mask_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_3_UNION
 �ṹ˵��  : IRQ_MASK_3 �Ĵ����ṹ���塣��ַƫ����:0x133����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK4���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_3 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO4��������ж����Σ�
                                                     bit[6]��LDO5��������ж����Σ�
                                                     bit[5]��LDO7��������ж����Σ�
                                                     bit[4]��LDO8��������ж����Σ�
                                                     bit[3]��LDO9��������ж����Σ�
                                                     bit[2]��LDO10��������ж����Σ�
                                                     bit[1]��LDO11��������ж�����;
                                                     bit[0]��LDO12��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_3_UNION;
#endif
#define PMIC_IRQ_MASK_3_irq_mask_3_START  (0)
#define PMIC_IRQ_MASK_3_irq_mask_3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_4_UNION
 �ṹ˵��  : IRQ_MASK_4 �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_4 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO13��������ж����Σ�
                                                     bit[6]��LDO14��������ж����Σ�
                                                     bit[5]��LDO15��������ж����Σ�
                                                     bit[4]��LDO16��������ж����Σ�
                                                     bit[3]��LDO17��������ж����Σ�
                                                     bit[2]��LDO19��������ж����Σ�
                                                     bit[1]��LDO20��������ж����Σ�
                                                     bit[0]��LDO21��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_4_UNION;
#endif
#define PMIC_IRQ_MASK_4_irq_mask_4_START  (0)
#define PMIC_IRQ_MASK_4_irq_mask_4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_5_UNION
 �ṹ˵��  : IRQ_MASK_5 �Ĵ����ṹ���塣��ַƫ����:0x135����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK6���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_5 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO22��������ж����Σ�
                                                     bit[6]��LDO23��������ж����Σ�
                                                     bit[5]��LDO24��������ж����Σ�
                                                     bit[4]��LDO25��������ж����Σ�
                                                     bit[3]��LDO26��������ж����Σ�
                                                     bit[2]��LDO27��������ж����Σ�
                                                     bit[1]��LDO28��������ж����Σ�
                                                     bit[0]��LDO29��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_5_UNION;
#endif
#define PMIC_IRQ_MASK_5_irq_mask_5_START  (0)
#define PMIC_IRQ_MASK_5_irq_mask_5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_6_UNION
 �ṹ˵��  : IRQ_MASK_6 �Ĵ����ṹ���塣��ַƫ����:0x136����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK7���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_6 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7:5]������ʹ�ã��ɶ�д��
                                                     bit[4]��LDO31��������ж����Σ�
                                                     bit[3]��LDO32��������ж����Σ�
                                                     bit[2]��LDO33��������ж����Σ�
                                                     bit[1]��LDO34��������ж����Σ�
                                                     bit[0]��class��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_6_UNION;
#endif
#define PMIC_IRQ_MASK_6_irq_mask_6_START  (0)
#define PMIC_IRQ_MASK_6_irq_mask_6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_7_UNION
 �ṹ˵��  : IRQ_MASK_7 �Ĵ����ṹ���塣��ַƫ����:0x137����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK8���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_7 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7��5]������ʹ�ã��ɶ�д��
                                                     bit[4]��xo_ldo_buff�����·�ж�����
                                                     bit[3]��BUCK0�����·�ж����Σ�
                                                     bit[2]��BUCK1�����·�ж����Σ�
                                                     bit[1]��BUCK2�����·�ж����Σ�
                                                     bit[0]��BUCK3�����·�ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_7_UNION;
#endif
#define PMIC_IRQ_MASK_7_irq_mask_7_START  (0)
#define PMIC_IRQ_MASK_7_irq_mask_7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BACKUP_CHG_UNION
 �ṹ˵��  : BACKUP_CHG �Ĵ����ṹ���塣��ַƫ����:0x13A����ֵ:0x09�����:8
 �Ĵ���˵��: NOPWRT���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_chg_en     : 1;  /* bit[0]  : ���õ�س��ʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned char  np_chg_bypass : 1;  /* bit[1]  : ���õ��ֱͨģʽ���ơ�
                                                        0����ֱͨ��
                                                        1��ֱͨ��  */
        unsigned char  np_chg_vset   : 2;  /* bit[2-3]: ���õ�س���ѹѡ��
                                                        00��2.5V��
                                                        01��3.0V��
                                                        1X��3.3V�� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BACKUP_CHG_UNION;
#endif
#define PMIC_BACKUP_CHG_np_chg_en_START      (0)
#define PMIC_BACKUP_CHG_np_chg_en_END        (0)
#define PMIC_BACKUP_CHG_np_chg_bypass_START  (1)
#define PMIC_BACKUP_CHG_np_chg_bypass_END    (1)
#define PMIC_BACKUP_CHG_np_chg_vset_START    (2)
#define PMIC_BACKUP_CHG_np_chg_vset_END      (3)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL0_UNION
 �ṹ˵��  : CLASSD_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x13B����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_classd_en   : 1;  /* bit[0]  : classDʹ�ܿ��ơ�
                                                          1��������
                                                          0���رա� */
        unsigned char  classd_mute     : 1;  /* bit[1]  : classd_mute���ơ� 
                                                          0������������
                                                          1��Mute�� */
        unsigned char  classd_mute_sel : 1;  /* bit[2]  : classd_mute_sel���ơ� 
                                                          0����ʱmuteģʽ��muteʱ����mute,���muteʱ����ʱ8ms,�����������ٽ������ 
                                                          1������muteģʽ����8ms��ʱ���� */
        unsigned char  classd_drv_en   : 1;  /* bit[3]  : ������·ʹ�ܡ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  classd_i_ocp    : 2;  /* bit[4-5]: classD������ֵ���ڡ�
                                                          00��1.5A��
                                                          01��2.0A��
                                                          10��2.5A��
                                                          11��3.0A�� */
        unsigned char  classd_gain     : 2;  /* bit[6-7]: classD������ơ� 
                                                          00��12db��
                                                          01��15db��
                                                          10��18db��
                                                          11��21db�� */
    } reg;
} PMIC_CLASSD_CTRL0_UNION;
#endif
#define PMIC_CLASSD_CTRL0_reg_classd_en_START    (0)
#define PMIC_CLASSD_CTRL0_reg_classd_en_END      (0)
#define PMIC_CLASSD_CTRL0_classd_mute_START      (1)
#define PMIC_CLASSD_CTRL0_classd_mute_END        (1)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_START  (2)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_END    (2)
#define PMIC_CLASSD_CTRL0_classd_drv_en_START    (3)
#define PMIC_CLASSD_CTRL0_classd_drv_en_END      (3)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_START     (4)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_END       (5)
#define PMIC_CLASSD_CTRL0_classd_gain_START      (6)
#define PMIC_CLASSD_CTRL0_classd_gain_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL1_UNION
 �ṹ˵��  : CLASSD_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_i_pump : 2;  /* bit[0-1]: Ramp���У�pump�������ơ�
                                                        00��6��A��
                                                        01��7��A��
                                                        10��7��A��
                                                        11��8��A�� */
        unsigned char  classd_p_sel  : 2;  /* bit[2-3]: ������pmos���ơ�
                                                        00����һ·pmos��
                                                        01������·pmos��
                                                        10������·pmos��
                                                        11������·pmos�� */
        unsigned char  classd_n_sel  : 2;  /* bit[4-5]: ������nmos���ơ�
                                                        00����һ·nmos��
                                                        01������·nmos��
                                                        10������·nmos��
                                                        11������·nmos�� */
        unsigned char  reserved      : 2;  /* bit[6-7]: ���� */
    } reg;
} PMIC_CLASSD_CTRL1_UNION;
#endif
#define PMIC_CLASSD_CTRL1_classd_i_pump_START  (0)
#define PMIC_CLASSD_CTRL1_classd_i_pump_END    (1)
#define PMIC_CLASSD_CTRL1_classd_p_sel_START   (2)
#define PMIC_CLASSD_CTRL1_classd_p_sel_END     (3)
#define PMIC_CLASSD_CTRL1_classd_n_sel_START   (4)
#define PMIC_CLASSD_CTRL1_classd_n_sel_END     (5)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL2_UNION
 �ṹ˵��  : CLASSD_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x13D����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_pls_byp  : 1;  /* bit[0]  : ��С�������ޡ�
                                                          0������������
                                                          1��bypass��С�������ơ� */
        unsigned char  classd_dt_sel   : 1;  /* bit[1]  : dead time���ơ�
                                                          0��2ns��
                                                          1��7ns�� */
        unsigned char  classd_ocp_bps  : 1;  /* bit[2]  : �����������ơ�
                                                          0����������������
                                                          1��bypass����������·��OCP�źŲ��ϱ����� */
        unsigned char  reserved        : 1;  /* bit[3]  : ���� */
        unsigned char  classd_reserve0 : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLASSD_CTRL2_UNION;
#endif
#define PMIC_CLASSD_CTRL2_classd_pls_byp_START   (0)
#define PMIC_CLASSD_CTRL2_classd_pls_byp_END     (0)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_START    (1)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_END      (1)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_START   (2)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_END     (2)
#define PMIC_CLASSD_CTRL2_classd_reserve0_START  (4)
#define PMIC_CLASSD_CTRL2_classd_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL3_UNION
 �ṹ˵��  : CLASSD_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x13E����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_reserve1 : 8;  /* bit[0-7]: ������ */
    } reg;
} PMIC_CLASSD_CTRL3_UNION;
#endif
#define PMIC_CLASSD_CTRL3_classd_reserve1_START  (0)
#define PMIC_CLASSD_CTRL3_classd_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_TH_CTRL_UNION
 �ṹ˵��  : TH_CTRL �Ĵ����ṹ���塣��ַƫ����:0x13F����ֵ:0xD1�����:8
 �Ĵ���˵��: ��ѹ�¶ȿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_res_sel_int   : 1;  /* bit[0]  : ��׼VREF�ܽ��˲�����ѡ�� �� */
        unsigned char  ref_ibias_trim_en : 2;  /* bit[1-2]: ��׼����Trimʹ���ź� */
        unsigned char  reserved          : 1;  /* bit[3]  : ���� */
        unsigned char  reg_thsd_en       : 1;  /* bit[4]  : THSD���±���ģ��ر�/���ؿ���λ��
                                                            0���ر�THSD���±���ģ�飻
                                                            1������THSD���±���ģ�顣 */
        unsigned char  reg_thsd_eco_en   : 1;  /* bit[5]  : THSD���±���ģ��ECO����λ��
                                                            0���˳��͹���ģʽ��
                                                            1������͹���ģʽ���ߵ�ƽΪ10ms������Ϊ1s�������źš� */
        unsigned char  thsd_tmp_set      : 2;  /* bit[6-7]: �¶ȱ���ģ�鱨���¶����á�
                                                            00��95�棻
                                                            01��105�棻
                                                            10��115�棻
                                                            11��125�档 */
    } reg;
} PMIC_TH_CTRL_UNION;
#endif
#define PMIC_TH_CTRL_ref_res_sel_int_START    (0)
#define PMIC_TH_CTRL_ref_res_sel_int_END      (0)
#define PMIC_TH_CTRL_ref_ibias_trim_en_START  (1)
#define PMIC_TH_CTRL_ref_ibias_trim_en_END    (2)
#define PMIC_TH_CTRL_reg_thsd_en_START        (4)
#define PMIC_TH_CTRL_reg_thsd_en_END          (4)
#define PMIC_TH_CTRL_reg_thsd_eco_en_START    (5)
#define PMIC_TH_CTRL_reg_thsd_eco_en_END      (5)
#define PMIC_TH_CTRL_thsd_tmp_set_START       (6)
#define PMIC_TH_CTRL_thsd_tmp_set_END         (7)


/*****************************************************************************
 �ṹ��    : PMIC_BG_TEST_UNION
 �ṹ˵��  : BG_TEST �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00�����:8
 �Ĵ���˵��: bg���ԼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_reserve : 8;  /* bit[0-7]: ��׼����ģʽԤ���� */
    } reg;
} PMIC_BG_TEST_UNION;
#endif
#define PMIC_BG_TEST_ref_reserve_START  (0)
#define PMIC_BG_TEST_ref_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR_EN_MODE_345_UNION
 �ṹ˵��  : DR_EN_MODE_345 �Ĵ����ṹ���塣��ַƫ����:0x141����ֵ:0x00�����:8
 �Ĵ���˵��: DR345��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr3_int : 1;  /* bit[0]  : DR3��������˸ģʽ�£�dr3_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR3��
                                                     1������DR3��  */
        unsigned char  dr3_mode   : 1;  /* bit[1]  : DR3����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR3����ģʽ��  */
        unsigned char  en_dr4_int : 1;  /* bit[2]  : DR4��������˸ģʽ�£�dr4_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR4��
                                                     1������DR4��  */
        unsigned char  dr4_mode   : 1;  /* bit[3]  : DR4����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR4����ģʽ��  */
        unsigned char  en_dr5_int : 1;  /* bit[4]  : DR5��������˸ģʽ�£�dr5_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR5��
                                                     1������DR5��  */
        unsigned char  dr5_mode   : 1;  /* bit[5]  : DR5����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR5����ģʽ��  */
        unsigned char  reserved   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_EN_MODE_345_UNION;
#endif
#define PMIC_DR_EN_MODE_345_en_dr3_int_START  (0)
#define PMIC_DR_EN_MODE_345_en_dr3_int_END    (0)
#define PMIC_DR_EN_MODE_345_dr3_mode_START    (1)
#define PMIC_DR_EN_MODE_345_dr3_mode_END      (1)
#define PMIC_DR_EN_MODE_345_en_dr4_int_START  (2)
#define PMIC_DR_EN_MODE_345_en_dr4_int_END    (2)
#define PMIC_DR_EN_MODE_345_dr4_mode_START    (3)
#define PMIC_DR_EN_MODE_345_dr4_mode_END      (3)
#define PMIC_DR_EN_MODE_345_en_dr5_int_START  (4)
#define PMIC_DR_EN_MODE_345_en_dr5_int_END    (4)
#define PMIC_DR_EN_MODE_345_dr5_mode_START    (5)
#define PMIC_DR_EN_MODE_345_dr5_mode_END      (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR_EN_MODE_12_UNION
 �ṹ˵��  : DR_EN_MODE_12 �Ĵ����ṹ���塣��ַƫ����:0x142����ֵ:0x00�����:8
 �Ĵ���˵��: DR12��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr1_int : 1;  /* bit[0]  : DR1��������˸ģʽ�£�dr1_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR1��
                                                     1������DR1 ��  */
        unsigned char  dr1_mode   : 1;  /* bit[1]  : DR1����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR1����ģʽ��  */
        unsigned char  en_dr2_int : 1;  /* bit[2]  : DR2��������˸ģʽ�£�dr2_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR2��
                                                     1������DR2��  */
        unsigned char  dr2_mode   : 1;  /* bit[3]  : DR2����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR2����ģʽ��  */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_DR_EN_MODE_12_UNION;
#endif
#define PMIC_DR_EN_MODE_12_en_dr1_int_START  (0)
#define PMIC_DR_EN_MODE_12_en_dr1_int_END    (0)
#define PMIC_DR_EN_MODE_12_dr1_mode_START    (1)
#define PMIC_DR_EN_MODE_12_dr1_mode_END      (1)
#define PMIC_DR_EN_MODE_12_en_dr2_int_START  (2)
#define PMIC_DR_EN_MODE_12_en_dr2_int_END    (2)
#define PMIC_DR_EN_MODE_12_dr2_mode_START    (3)
#define PMIC_DR_EN_MODE_12_dr2_mode_END      (3)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_PERIOD_DR12_UNION
 �ṹ˵��  : FLASH_PERIOD_DR12 �Ĵ����ṹ���塣��ַƫ����:0x143����ֵ:0x3F�����:8
 �Ĵ���˵��: DR12��˸ģʽ���ڵ���0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr12 : 8;  /* bit[0-7]: ��˸����T = ����ֵ *31.25ms�� */
    } reg;
} PMIC_FLASH_PERIOD_DR12_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_START  (0)
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_ON_DR12_UNION
 �ṹ˵��  : FLASH_ON_DR12 �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x1F�����:8
 �Ĵ���˵��: DR12��˸ģʽ����ʱ�����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr12 : 8;  /* bit[0-7]: ����ʱ��t =����ֵ *7.8125ms�� */
    } reg;
} PMIC_FLASH_ON_DR12_UNION;
#endif
#define PMIC_FLASH_ON_DR12_flash_on_dr12_START  (0)
#define PMIC_FLASH_ON_DR12_flash_on_dr12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_PERIOD_DR345_UNION
 �ṹ˵��  : FLASH_PERIOD_DR345 �Ĵ����ṹ���塣��ַƫ����:0x145����ֵ:0x3F�����:8
 �Ĵ���˵��: DR345��˸ģʽ���ڵ���1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr345 : 8;  /* bit[0-7]: ��˸����T = ����ֵ *31.25ms�� */
    } reg;
} PMIC_FLASH_PERIOD_DR345_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_START  (0)
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_ON_DR345_UNION
 �ṹ˵��  : FLASH_ON_DR345 �Ĵ����ṹ���塣��ַƫ����:0x146����ֵ:0x1F�����:8
 �Ĵ���˵��: DR345��˸ģʽ����ʱ�����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr345 : 8;  /* bit[0-7]: ����ʱ��t =����ֵ *7.8125ms�� */
    } reg;
} PMIC_FLASH_ON_DR345_UNION;
#endif
#define PMIC_FLASH_ON_DR345_flash_on_dr345_START  (0)
#define PMIC_FLASH_ON_DR345_flash_on_dr345_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR_MODE_SEL_UNION
 �ṹ˵��  : DR_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x147����ֵ:0x00�����:8
 �Ĵ���˵��: DR��ģʽѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_mode_sel : 1;  /* bit[0]  : DR1����ģʽѡ��
                                                       0�� DR1�����ں�������ģʽ��
                                                       1��DR1��������˸ģʽ�� */
        unsigned char  dr2_mode_sel : 1;  /* bit[1]  : DR2����ģʽѡ��
                                                       0�� DR2�����ں�������ģʽ��
                                                       1��DR2��������˸ģʽ�� */
        unsigned char  dr3_mode_sel : 1;  /* bit[2]  : DR3����ģʽѡ��
                                                       0�� DR3�����ں�������ģʽ��
                                                       1��DR3��������˸ģʽ�� */
        unsigned char  dr4_mode_sel : 1;  /* bit[3]  : DR4����ģʽѡ��
                                                       0�� DR4�����ں�������ģʽ��
                                                       1��DR4��������˸ģʽ�� */
        unsigned char  dr5_mode_sel : 1;  /* bit[4]  : DR5����ģʽѡ��
                                                       0�� DR5�����ں�������ģʽ��
                                                       1��DR5��������˸ģʽ�� */
        unsigned char  reserved     : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_DR_MODE_SEL_UNION;
#endif
#define PMIC_DR_MODE_SEL_dr1_mode_sel_START  (0)
#define PMIC_DR_MODE_SEL_dr1_mode_sel_END    (0)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_START  (1)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_END    (1)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_START  (2)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_END    (2)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_START  (3)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_END    (3)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_START  (4)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_DR_BRE_CTRL_UNION
 �ṹ˵��  : DR_BRE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00�����:8
 �Ĵ���˵��: DR1/2����ģʽ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr1_en   : 1;  /* bit[0]  : DR1�����ں�����dr1_mode_sel=0��ģʽʹ�ܡ�
                                                       0��dr1�ر� �� 
                                                       1��dr1ʹ�ܡ�
                                                       dr1_flash_en = 1,���� ��
                                                       dr1_flash_en = 0,���� �� */
        unsigned char  dr1_flash_en : 1;  /* bit[1]  : DR1����ʹ�ܡ�
                                                       0����ʹ��dr1����ģʽ��
                                                       1��ʹ��dr1����ģʽ�� */
        unsigned char  reserved_0   : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_dr2_en   : 1;  /* bit[4]  : DR2�����ں�����dr2_mode_sel=0��ģʽʹ�ܡ�
                                                       0��dr2�ر� �� 
                                                       1��dr2ʹ�ܡ�
                                                       dr2_flash_en = 1,���� ��
                                                       dr2_flash_en = 0,���� �� */
        unsigned char  dr2_flash_en : 1;  /* bit[5]  : DR2����ʹ�ܡ�
                                                       0����ʹ��dr2����ģʽ��
                                                       1��ʹ��dr2����ģʽ�� */
        unsigned char  reserved_1   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_BRE_CTRL_UNION;
#endif
#define PMIC_DR_BRE_CTRL_reg_dr1_en_START    (0)
#define PMIC_DR_BRE_CTRL_reg_dr1_en_END      (0)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_START  (1)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_END    (1)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_START    (4)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_END      (4)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_START  (5)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR12_TIM_CONF0_UNION
 �ṹ˵��  : DR12_TIM_CONF0 �Ĵ����ṹ���塣��ַƫ����:0x149����ֵ:0x33�����:8
 �Ĵ���˵��: DR1��DR2��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_off : 3;  /* bit[0-2]: DR12����ģʽ�³���ʱ�䡣
                                                     000��1ms��
                                                     001��0.25s��
                                                     010��0.5s��
                                                     011��1s��
                                                     100��2s��
                                                     101��4s��
                                                     110��4s��
                                                     111�������� */
        unsigned char  reserved_0 : 1;  /* bit[3]  : ������ */
        unsigned char  dr12_t_on  : 3;  /* bit[4-6]: DR12����ģʽ�³���ʱ�����á�
                                                     000��1ms��
                                                     001��0.25s��
                                                     010��0.5s��
                                                     011��1s��
                                                     100��2s��
                                                     101��4s��
                                                     110��4s��
                                                     111�������� */
        unsigned char  reserved_1 : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR12_TIM_CONF0_UNION;
#endif
#define PMIC_DR12_TIM_CONF0_dr12_t_off_START  (0)
#define PMIC_DR12_TIM_CONF0_dr12_t_off_END    (2)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_START   (4)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_DR12_TIM_CONF1_UNION
 �ṹ˵��  : DR12_TIM_CONF1 �Ĵ����ṹ���塣��ַƫ����:0x14A����ֵ:0x33�����:8
 �Ĵ���˵��: DR1��DR2��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_rise : 3;  /* bit[0-2]: DR12����ģʽ�½���ʱ�䡣
                                                      000��0s��
                                                      001��0.25s��
                                                      010��0.5s��
                                                      011��1s��
                                                      100��2s��
                                                      101��2.5s��
                                                      110��3s��
                                                      111��4s�� */
        unsigned char  reserved_0  : 1;  /* bit[3]  : ������ */
        unsigned char  dr12_t_fall : 3;  /* bit[4-6]: DR12����ģʽ�½���ʱ�䡣
                                                      000��0s��
                                                      001��0.25s��
                                                      010��0.5s��
                                                      011��1s��
                                                      100��2s��
                                                      101��2.5s��
                                                      110��3s��
                                                      111��4s�� */
        unsigned char  reserved_1  : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR12_TIM_CONF1_UNION;
#endif
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_START  (0)
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_END    (2)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_START  (4)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_DR1_ISET_UNION
 �ṹ˵��  : DR1_ISET �Ĵ����ṹ���塣��ַƫ����:0x14B����ֵ:0x00�����:8
 �Ĵ���˵��: DR1����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_iset : 3;  /* bit[0-2]: DR1�������ڡ� 000��1 mA��
                                                   001��3 mA��
                                                   010��5 mA��
                                                   011��7 mA��
                                                   100��9 mA��
                                                   101��11 mA��
                                                   110��13 mA��
                                                   111��15 mA�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR1_ISET_UNION;
#endif
#define PMIC_DR1_ISET_dr1_iset_START  (0)
#define PMIC_DR1_ISET_dr1_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR2_ISET_UNION
 �ṹ˵��  : DR2_ISET �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x00�����:8
 �Ĵ���˵��: DR2����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr2_iset : 3;  /* bit[0-2]: DR2�������ڡ� 000��1 mA��
                                                   001��3 mA��
                                                   010��5 mA��
                                                   011��7 mA��
                                                   100��9 mA��
                                                   101��11 mA��
                                                   110��13 mA��
                                                   111��15 mA�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR2_ISET_UNION;
#endif
#define PMIC_DR2_ISET_dr2_iset_START  (0)
#define PMIC_DR2_ISET_dr2_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR_LED_CTRL_UNION
 �ṹ˵��  : DR_LED_CTRL �Ĵ����ṹ���塣��ַƫ����:0x14D����ֵ:0x00�����:8
 �Ĵ���˵��: DR3/4/5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr3_en : 1;  /* bit[0]  : ����ģʽ��DR3ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reg_dr4_en : 1;  /* bit[1]  : ����ģʽ��DR4ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reg_dr5_en : 1;  /* bit[2]  : ����ģʽ��DR5ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR_LED_CTRL_UNION;
#endif
#define PMIC_DR_LED_CTRL_reg_dr3_en_START  (0)
#define PMIC_DR_LED_CTRL_reg_dr3_en_END    (0)
#define PMIC_DR_LED_CTRL_reg_dr4_en_START  (1)
#define PMIC_DR_LED_CTRL_reg_dr4_en_END    (1)
#define PMIC_DR_LED_CTRL_reg_dr5_en_START  (2)
#define PMIC_DR_LED_CTRL_reg_dr5_en_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR_OUT_CTRL_UNION
 �ṹ˵��  : DR_OUT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x14E����ֵ:0x00�����:8
 �Ĵ���˵��: DR3/4/5������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_out_ctrl : 2;  /* bit[0-1]: DR3������ơ�
                                                       00��DR3�������������DR3�ܽţ�
                                                       01��DR3��DR4����������������DR3�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR3�ܽţ�
                                                       11��DR4��DR5����������������DR3�ܽš� */
        unsigned char  dr4_out_ctrl : 2;  /* bit[2-3]: DR4������ơ�
                                                       00��DR4�������������DR4�ܽţ�
                                                       01��DR3��DR4����������������DR4�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR4�ܽţ�
                                                       11��DR4��DR5����������������DR4�ܽš� */
        unsigned char  dr5_out_ctrl : 2;  /* bit[4-5]: DR5������ơ�
                                                       00��DR5�������������DR5�ܽţ�
                                                       01��DR3��DR4����������������DR5�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR5�ܽţ�
                                                       11��DR4��DR5����������������DR5�ܽš� */
        unsigned char  reserved     : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_OUT_CTRL_UNION;
#endif
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_START  (0)
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_END    (1)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_START  (2)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_END    (3)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_START  (4)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR3_ISET_UNION
 �ṹ˵��  : DR3_ISET �Ĵ����ṹ���塣��ַƫ����:0x14F����ֵ:0x00�����:8
 �Ĵ���˵��: DR3����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_iset : 3;  /* bit[0-2]: DR3����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR3_ISET_UNION;
#endif
#define PMIC_DR3_ISET_dr3_iset_START  (0)
#define PMIC_DR3_ISET_dr3_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR3_START_DEL_UNION
 �ṹ˵��  : DR3_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x10�����:8
 �Ĵ���˵��: DR3������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_start_delay : 8;  /* bit[0-7]: DR3������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR3_START_DEL_UNION;
#endif
#define PMIC_DR3_START_DEL_dr3_start_delay_START  (0)
#define PMIC_DR3_START_DEL_dr3_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR4_ISET_UNION
 �ṹ˵��  : DR4_ISET �Ĵ����ṹ���塣��ַƫ����:0x151����ֵ:0x00�����:8
 �Ĵ���˵��: DR4����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_iset : 3;  /* bit[0-2]: DR4����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR4_ISET_UNION;
#endif
#define PMIC_DR4_ISET_dr4_iset_START  (0)
#define PMIC_DR4_ISET_dr4_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR4_START_DEL_UNION
 �ṹ˵��  : DR4_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x152����ֵ:0x10�����:8
 �Ĵ���˵��: DR4������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_start_delay : 8;  /* bit[0-7]: DR4������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR4_START_DEL_UNION;
#endif
#define PMIC_DR4_START_DEL_dr4_start_delay_START  (0)
#define PMIC_DR4_START_DEL_dr4_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR5_ISET_UNION
 �ṹ˵��  : DR5_ISET �Ĵ����ṹ���塣��ַƫ����:0x153����ֵ:0x00�����:8
 �Ĵ���˵��: DR5����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_iset : 3;  /* bit[0-2]: DR5����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR5_ISET_UNION;
#endif
#define PMIC_DR5_ISET_dr5_iset_START  (0)
#define PMIC_DR5_ISET_dr5_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR5_START_DEL_UNION
 �ṹ˵��  : DR5_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x10�����:8
 �Ĵ���˵��: DR5������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_start_delay : 8;  /* bit[0-7]: DR5������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR5_START_DEL_UNION;
#endif
#define PMIC_DR5_START_DEL_dr5_start_delay_START  (0)
#define PMIC_DR5_START_DEL_dr5_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR334_TIM_CONF0_UNION
 �ṹ˵��  : DR334_TIM_CONF0 �Ĵ����ṹ���塣��ַƫ����:0x155����ֵ:0x44�����:8
 �Ĵ���˵��: DR345��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_off : 4;  /* bit[0-3]: DR345����ʱ�����á�
                                                      000��0s��
                                                      001��0.5s��
                                                      010��1s��
                                                      011��2s��
                                                      100��4s��
                                                      101��6s��
                                                      110��8s��
                                                      111��12s��
                                                      1000��14��
                                                      1001��16��
                                                      ������������ */
        unsigned char  dr345_t_on  : 4;  /* bit[4-7]: DR345����ʱ�����á�
                                                      0000��0s��
                                                      0001��0.5s��
                                                      0010��1s��
                                                      0011��2s��
                                                      0100��4s��
                                                      0101��6s��
                                                      0110��8s��
                                                      0111��12s��
                                                      1000��14��
                                                      1001��16��
                                                      ������������ */
    } reg;
} PMIC_DR334_TIM_CONF0_UNION;
#endif
#define PMIC_DR334_TIM_CONF0_dr345_t_off_START  (0)
#define PMIC_DR334_TIM_CONF0_dr345_t_off_END    (3)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_START   (4)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR345_TIM_CONF1_UNION
 �ṹ˵��  : DR345_TIM_CONF1 �Ĵ����ṹ���塣��ַƫ����:0x156����ֵ:0x33�����:8
 �Ĵ���˵��: DR345��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_rise : 3;  /* bit[0-2]: DR345����ʱ�����á�
                                                       000��0s��
                                                       001��0.25s��
                                                       010��0.5s��
                                                       011��1s��
                                                       100��2s��
                                                       101��2.5s��
                                                       110��3s��
                                                       111��4s�� */
        unsigned char  reserved_0   : 1;  /* bit[3]  : ������ */
        unsigned char  dr345_t_fall : 3;  /* bit[4-6]: DR345����ʱ�����á�
                                                       000��0s��
                                                       001��0.25s��
                                                       010��0.5s��
                                                       011��1s��
                                                       100��2s��
                                                       101��2.5s��
                                                       110��3s��
                                                       111��4s�� */
        unsigned char  reserved_1   : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR345_TIM_CONF1_UNION;
#endif
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_START  (0)
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_END    (2)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_START  (4)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_VSYS_LOW_SET_UNION
 �ṹ˵��  : VSYS_LOW_SET �Ĵ����ṹ���塣��ַƫ����:0x157����ֵ:0x21�����:8
 �Ĵ���˵��: IN�˵�ѹ��ֵ�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_vsys_pwroff_deb_set : 3;  /* bit[0-2]: �ػ���ѹ��ֵ���ڣ����ڴ˵�ѹPMU�ػ���
                                                                 000��2.5V��
                                                                 001��2.6V��
                                                                 010��2.7V��
                                                                 011��2.8V��
                                                                 100��2.9V��
                                                                 101��3.0V��
                                                                 110��3.1V��
                                                                 111��3.2V�� */
        unsigned char  np_vsys_pwroff_abs_set : 1;  /* bit[3]  : vsys�˵͵�ѹ�ж���ֵ��ѹ���������ڴ˵�ѹ���̹ػ������˲���
                                                                 0��2.3V��
                                                                 1��2.4V�� */
        unsigned char  np_vsys_pwron_set      : 3;  /* bit[4-6]: ������ѹ��ֵ���ڣ����ڴ˵�ѹPMU������
                                                                 000��2.6V��
                                                                 001��2.7V��
                                                                 010��2.8V��
                                                                 011��2.9V��
                                                                 100��3.0V��
                                                                 101��3.1V��
                                                                 110��3.2V��
                                                                 111��3.3V�� */
        unsigned char  reserved               : 1;  /* bit[7]  : ���� */
    } reg;
} PMIC_VSYS_LOW_SET_UNION;
#endif
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_deb_set_START  (0)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_deb_set_END    (2)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_abs_set_START  (3)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_abs_set_END    (3)
#define PMIC_VSYS_LOW_SET_np_vsys_pwron_set_START       (4)
#define PMIC_VSYS_LOW_SET_np_vsys_pwron_set_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_NFC_ON_CTRL_UNION
 �ṹ˵��  : NFC_ON_CTRL �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00�����:8
 �Ĵ���˵��: nfc_on���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_nfc_on_d2a : 1;  /* bit[0]  : NFC_ON����ܽţ��ǵ���Ĵ���������PMUD�����档
                                                        0��NFC_ON�ܽ����0��ƽ��
                                                        1��NFC_ON�ܽ����1.8V�� */
        unsigned char  reserved      : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_NFC_ON_CTRL_UNION;
#endif
#define PMIC_NFC_ON_CTRL_np_nfc_on_d2a_START  (0)
#define PMIC_NFC_ON_CTRL_np_nfc_on_d2a_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL_RESERVE_UNION
 �ṹ˵��  : SYS_CTRL_RESERVE �Ĵ����ṹ���塣��ַƫ����:0x159����ֵ:0x00�����:8
 �Ĵ���˵��: ϵͳ����Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_ctrl_reserve : 8;  /* bit[0-7]: ϵͳ����ģ��Ԥ���Ĵ����� */
    } reg;
} PMIC_SYS_CTRL_RESERVE_UNION;
#endif
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_START  (0)
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRESET_PWRDOWN_CTRL_UNION
 �ṹ˵��  : HRESET_PWRDOWN_CTRL �Ĵ����ṹ���塣��ַƫ����:0x15A����ֵ:0x01�����:8
 �Ĵ���˵��: �ȸ�λ�µ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hreset_mode : 1;  /* bit[0]  : HRESET_N����ģʽѡ��λ��
                                                         0��hreset�µ�������
                                                         1��hreset�ȸ�λ������ */
        unsigned char  reserved       : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_HRESET_PWRDOWN_CTRL_UNION;
#endif
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_START  (0)
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_DEB_CTRL0_UNION
 �ṹ˵��  : OCP_DEB_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x15B����ֵ:0x04�����:8
 �Ĵ���˵��: OCP��SPC�˲�ʱ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_ocp_deb_sel : 2;  /* bit[0-1]: LDO31��OCP�˲�ʱ�䡣
                                                            000��1ms��
                                                            001��2ms��
                                                            010��4ms��
                                                            011��8ms�� */
        unsigned char  ldo_ocp_deb_sel   : 2;  /* bit[2-3]: LDO��OCP�˲�ʱ�䣨����LDO31����
                                                            000��0.5ms
                                                            001��1ms��
                                                            010��2ms��
                                                            011��4ms�� */
        unsigned char  buck_scp_deb_sel  : 2;  /* bit[4-5]: BUCK��SCP���˲�ʱ��ѡ��
                                                            00��60us���Ǿ���60us��������90us��120us�Ƚ�Сֵ����
                                                            01��0.5ms��
                                                            10��1ms��
                                                            11��2ms�� */
        unsigned char  buck_ocp_deb_sel  : 2;  /* bit[6-7]: BUCK��OCP���˲�ʱ��ѡ��
                                                            00��60us���Ǿ���60us��������90us��120us�Ƚ�Сֵ����
                                                            01��0.5ms��
                                                            10��1ms��
                                                            11��2ms�� */
    } reg;
} PMIC_OCP_DEB_CTRL0_UNION;
#endif
#define PMIC_OCP_DEB_CTRL0_ldo31_ocp_deb_sel_START  (0)
#define PMIC_OCP_DEB_CTRL0_ldo31_ocp_deb_sel_END    (1)
#define PMIC_OCP_DEB_CTRL0_ldo_ocp_deb_sel_START    (2)
#define PMIC_OCP_DEB_CTRL0_ldo_ocp_deb_sel_END      (3)
#define PMIC_OCP_DEB_CTRL0_buck_scp_deb_sel_START   (4)
#define PMIC_OCP_DEB_CTRL0_buck_scp_deb_sel_END     (5)
#define PMIC_OCP_DEB_CTRL0_buck_ocp_deb_sel_START   (6)
#define PMIC_OCP_DEB_CTRL0_buck_ocp_deb_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_DEB_CTRL1_UNION
 �ṹ˵��  : OCP_DEB_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0xC5�����:8
 �Ĵ���˵��: OCP��SPC�˲�ʱ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vin_ldoh_deb_sel        : 2;  /* bit[0-1]: vin_ldoh���˲�ʱ�䡣
                                                                  000��0.5ms
                                                                  001��1ms��
                                                                  010��2ms��
                                                                  011��4ms�� */
        unsigned char  xo_ldo_buff_scp_deb_sel : 2;  /* bit[2-3]: xo_ldo_buff��SCP�˲�ʱ�䡣
                                                                  000��0.5ms
                                                                  001��1ms��
                                                                  010��2ms��
                                                                  011��4ms�� */
        unsigned char  classd_ocp_deb_sel      : 2;  /* bit[4-5]: classd��OCP���˲�ʱ��ѡ��
                                                                  00��60us���Ǿ���60us��������90us��120us�Ƚ�Сֵ����
                                                                  01��0.5ms��
                                                                  10��1ms��
                                                                  11��2ms�� */
        unsigned char  ldo27_ocp_deb_sel       : 2;  /* bit[6-7]: LDO31��OCP�˲�ʱ�䡣
                                                                  000��0.5ms
                                                                  001��1ms��
                                                                  010��2ms��
                                                                  011��4ms�� */
    } reg;
} PMIC_OCP_DEB_CTRL1_UNION;
#endif
#define PMIC_OCP_DEB_CTRL1_vin_ldoh_deb_sel_START         (0)
#define PMIC_OCP_DEB_CTRL1_vin_ldoh_deb_sel_END           (1)
#define PMIC_OCP_DEB_CTRL1_xo_ldo_buff_scp_deb_sel_START  (2)
#define PMIC_OCP_DEB_CTRL1_xo_ldo_buff_scp_deb_sel_END    (3)
#define PMIC_OCP_DEB_CTRL1_classd_ocp_deb_sel_START       (4)
#define PMIC_OCP_DEB_CTRL1_classd_ocp_deb_sel_END         (5)
#define PMIC_OCP_DEB_CTRL1_ldo27_ocp_deb_sel_START        (6)
#define PMIC_OCP_DEB_CTRL1_ldo27_ocp_deb_sel_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_SCP_ONOFF_UNION
 �ṹ˵��  : OCP_SCP_ONOFF �Ĵ����ṹ���塣��ַƫ����:0x15D����ֵ:0xFF�����:8
 �Ĵ���˵��: OCP��DOCP�˲����ؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_vin_ldoh_deb        : 1;  /* bit[0]: vin_ldoh�˲�����ʹ��λ��
                                                               0��vin_ldoh �˲���ʹ�ܣ�
                                                               1��vin_ldoh �˲�ʹ�ܡ� */
        unsigned char  en_xo_ldo_buff_scp_deb : 1;  /* bit[1]: xo_ldo_buff SCP�˲�����ʹ��λ��
                                                               0��xo_ldo_buff �˲���ʹ�ܣ�
                                                               1��xo_ldo_buff �˲�ʹ�ܡ� */
        unsigned char  en_classd_ocp_deb      : 1;  /* bit[2]: CLASSD OCP�˲�����ʹ��λ��
                                                               0��CLASSD OCP �˲���ʹ�ܣ�
                                                               1��CLASSD OCP �˲�ʹ�ܡ� */
        unsigned char  en_ldo31_ocp_deb       : 1;  /* bit[3]: LDO31 OCP�˲�����ʹ��λ��
                                                               0��LDO31 OCP �˲���ʹ�ܣ�
                                                               1��LDO31 OCP �˲�ʹ�ܡ� */
        unsigned char  en_ldo_ocp_deb         : 1;  /* bit[4]: LDO OCP������LDO31���˲�����ʹ��λ��
                                                               0��LDO OCP �˲���ʹ�ܣ�
                                                               1��LDO OCP �˲�ʹ�ܡ� */
        unsigned char  en_buck_scp_deb        : 1;  /* bit[5]: BUCK scp�˲�����ʹ��λ��
                                                               0��BUCK scp �˲���ʹ�ܣ�
                                                               1��BUCK scp �˲�ʹ�ܡ� */
        unsigned char  en_buck_ocp_deb        : 1;  /* bit[6]: BUCK OCP�˲�����ʹ��λ��
                                                               0��BUCK OCP �˲���ʹ�ܣ�
                                                               1��BUCK OCP �˲�ʹ�ܡ� */
        unsigned char  en_ldo27_ocp_deb       : 1;  /* bit[7]: LDO27 OCP�˲�����ʹ��λ��
                                                               0��LDO27 OCP �˲���ʹ�ܣ�
                                                               1��LDO27 OCP �˲�ʹ�ܡ� */
    } reg;
} PMIC_OCP_SCP_ONOFF_UNION;
#endif
#define PMIC_OCP_SCP_ONOFF_en_vin_ldoh_deb_START         (0)
#define PMIC_OCP_SCP_ONOFF_en_vin_ldoh_deb_END           (0)
#define PMIC_OCP_SCP_ONOFF_en_xo_ldo_buff_scp_deb_START  (1)
#define PMIC_OCP_SCP_ONOFF_en_xo_ldo_buff_scp_deb_END    (1)
#define PMIC_OCP_SCP_ONOFF_en_classd_ocp_deb_START       (2)
#define PMIC_OCP_SCP_ONOFF_en_classd_ocp_deb_END         (2)
#define PMIC_OCP_SCP_ONOFF_en_ldo31_ocp_deb_START        (3)
#define PMIC_OCP_SCP_ONOFF_en_ldo31_ocp_deb_END          (3)
#define PMIC_OCP_SCP_ONOFF_en_ldo_ocp_deb_START          (4)
#define PMIC_OCP_SCP_ONOFF_en_ldo_ocp_deb_END            (4)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_START         (5)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_END           (5)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_START         (6)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_END           (6)
#define PMIC_OCP_SCP_ONOFF_en_ldo27_ocp_deb_START        (7)
#define PMIC_OCP_SCP_ONOFF_en_ldo27_ocp_deb_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_PWROFF_DEB_CTRL_UNION
 �ṹ˵��  : PWROFF_DEB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x15E����ֵ:0x07�����:8
 �Ĵ���˵��: Ƿѹ�ػ��˲�ʱ��ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_deb_sel : 3;  /* bit[0-2]: vsysС��2.6Vָʾ�ź�ȥ��ʱ�䡣
                                                              000��0ms���Ǿ���0������30us��60us�Ƚ�Сֵ����
                                                              001��0.45ms��
                                                              010��0.9ms��
                                                              011��1.8ms��
                                                              100��3.6ms��
                                                              101��20ms��
                                                              110��40ms��
                                                              111��80ms�� */
        unsigned char  reserved            : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_PWROFF_DEB_CTRL_UNION;
#endif
#define PMIC_PWROFF_DEB_CTRL_vsys_pwroff_deb_sel_START  (0)
#define PMIC_PWROFF_DEB_CTRL_vsys_pwroff_deb_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL0_UNION
 �ṹ˵��  : SYS_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x15F����ֵ:0x00�����:8
 �Ĵ���˵��: ϵͳ���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_abs_pd_mask : 1;  /* bit[0]  : vsysС��2.3vʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ�(����2.3vʱ�䳬��35us���ϲ��ܱ�֤�ػ��ɹ�)��
                                                                  1�����Զ��ػ���
                                                                  ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  vsys_pwroff_deb_pd_mask : 1;  /* bit[1]  : vsysС��2.6vʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ���
                                                                  ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  thsd_otmp140_pd_mask    : 1;  /* bit[2]  : �¶ȳ���140��ʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ���
                                                                  ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  vsys_ov_pd_mask         : 1;  /* bit[3]  : vsys��ѹʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ���
                                                                  ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  vin_ldoh_vld_pd_mask    : 1;  /* bit[4]  : VIN_LDOH��Դ���ϸ�ʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ���
                                                                  ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reserved                : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_SYS_CTRL0_UNION;
#endif
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_START  (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_END    (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_START  (1)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_END    (1)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_START     (2)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_END       (2)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_START          (3)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_END            (3)
#define PMIC_SYS_CTRL0_vin_ldoh_vld_pd_mask_START     (4)
#define PMIC_SYS_CTRL0_vin_ldoh_vld_pd_mask_END       (4)


/*****************************************************************************
 �ṹ��    : PMIC_SMPL_CTRL_UNION
 �ṹ˵��  : SMPL_CTRL �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00�����:8
 �Ĵ���˵��: SMPL���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_smpl_open_en  : 1;  /* bit[0]  : SMPL����ʹ��λ��
                                                           0����֧�ֵ�ص�����������
                                                           1��֧�ֵ�ص����������� */
        unsigned char  np_smpl_time_sel : 2;  /* bit[1-2]: ��ص����ٲ���������ʱ��ѡ��
                                                           00��0.5s��
                                                           01��1s��
                                                           10��1.5s��
                                                           11��2s�� */
        unsigned char  reserved         : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_SMPL_CTRL_UNION;
#endif
#define PMIC_SMPL_CTRL_np_smpl_open_en_START   (0)
#define PMIC_SMPL_CTRL_np_smpl_open_en_END     (0)
#define PMIC_SMPL_CTRL_np_smpl_time_sel_START  (1)
#define PMIC_SMPL_CTRL_np_smpl_time_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL1_UNION
 �ṹ˵��  : SYS_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x161����ֵ:0x02�����:8
 �Ĵ���˵��: ϵͳ���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pwron_8s_sel   : 1;  /* bit[0]  : ����״̬�°���pwron_n����8s�ػ���������ѡ��
                                                            0��������������
                                                            1���������ػ��� */
        unsigned char  np_pwron_time_sel : 2;  /* bit[1-2]: ��������Чʱ�����üĴ�����
                                                            00:7s��
                                                            01:8s��
                                                            10:9s��
                                                            11:10s�� */
        unsigned char  reserved          : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_SYS_CTRL1_UNION;
#endif
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_START    (0)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_END      (0)
#define PMIC_SYS_CTRL1_np_pwron_time_sel_START  (1)
#define PMIC_SYS_CTRL1_np_pwron_time_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_SIM_CTRL_UNION
 �ṹ˵��  : SIM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x162����ֵ:0x00�����:8
 �Ĵ���˵��: SIM���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r_pd_en : 1;  /* bit[0]  : ����sim0_hpd�������ж�ʱ�Ƿ�ر�LDO11����λ��
                                                           0�����ر�LDO11��
                                                           1���ر�LDO11�� */
        unsigned char  sim0_hpd_f_pd_en : 1;  /* bit[1]  : ����sim0_hpd�½����ж�ʱ�Ƿ�ر�LDO11����λ��
                                                           0�����ر�LDO11��
                                                           1���ر�LDO11�� */
        unsigned char  sim1_hpd_r_pd_en : 1;  /* bit[2]  : ����sim1_hpd�������ж�ʱ�Ƿ�ر�LDO12����λ��
                                                           0�����ر�LDO12��
                                                           1���ر�LDO12�� */
        unsigned char  sim1_hpd_f_pd_en : 1;  /* bit[3]  : ����sim1_hpd�½����ж�ʱ�Ƿ�ر�LDO12����λ��
                                                           0�����ر�LDO12��
                                                           1���ر�LDO12�� */
        unsigned char  reserved         : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_SIM_CTRL_UNION;
#endif
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_START  (0)
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_END    (0)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_START  (1)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_END    (1)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_START  (2)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_END    (2)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_START  (3)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_SIM_DEB_CTRL_UNION
 �ṹ˵��  : SIM_DEB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x163����ֵ:0x27�����:8
 �Ĵ���˵��: SIM�˲����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim_hpd_deb_sel : 5;  /* bit[0-4]: sim_hpd�����ط�����ʵ�ʲ��������жϵ�ʱ��������������ټ�90us����
                                                          0x0 �� 120us��0x1 ��180us��
                                                          0x2 ��240us��0x3 �� 300us��
                                                          0x4 �� 360us��0x5 �� 420us��
                                                          0x6 �� 480us��0x7 �� 540us��
                                                          0x8 �� 600us��0x9 �� 740us��
                                                          0xa �� 1ms��0xb �� 1.25ms��
                                                          0xc �� 1.5ms��0xd �� 1.75ms��
                                                          0xe �� 2ms��0xf �� 2.25ms��
                                                          0x10�� 2.5ms��0x11�� 2.75ms��
                                                          0x12�� 3ms��0x13�� 4ms��
                                                          0x14�� 5ms��0x15�� 6ms��
                                                          0x16�� 7ms��0x17�� 8ms��
                                                          0x18�� 9ms��0x19�� 10ms��
                                                          0x1a�� 11ms��0x1b�� 12ms��
                                                          0x1c�� 13ms��0x1d�� 14ms��
                                                          0x1e�� 15ms��0x1f�� 16ms��
                                                          ��0x0-0x8����60us���ҵ�ƫ�0x9-0x12����250us���ҵ�ƫ�0x13-0x1f����2ms���ҵ�ƫ� */
        unsigned char  sim_del_sel     : 3;  /* bit[5-7]: SIM0/1_HPD�����жϵ��Զ��رյ�Դ�ӳ�ʱ��ѡ��
                                                          000��60us��
                                                          001��120us��
                                                          010��180us��
                                                          011��240us��
                                                          100��360us��
                                                          101��480us��
                                                          110��540us��
                                                          111��600us�� */
    } reg;
} PMIC_SIM_DEB_CTRL_UNION;
#endif
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_START  (0)
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_END    (4)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_START      (5)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_AUX0_IBIAS_CFG_UNION
 �ṹ˵��  : AUX0_IBIAS_CFG �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x0A�����:8
 �Ĵ���˵��: DAC0 IBIAS���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux0_offset_cfg : 2;  /* bit[0-1]: AUXDAC0 OFFSET���ڡ�
                                                          00��+7.5mV��
                                                          01��0mV��
                                                          10��0mV��
                                                          11��-7.5mV�� */
        unsigned char  aux0_ibias_cfg  : 2;  /* bit[2-3]: AUXDAC0ƫ�õ������ڡ�
                                                          00��2.5uA��
                                                          01��5.0uA��
                                                          10��5.0uA��
                                                          11��7.5uA�� */
        unsigned char  reserved        : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_AUX0_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX0_IBIAS_CFG_aux0_offset_cfg_START  (0)
#define PMIC_AUX0_IBIAS_CFG_aux0_offset_cfg_END    (1)
#define PMIC_AUX0_IBIAS_CFG_aux0_ibias_cfg_START   (2)
#define PMIC_AUX0_IBIAS_CFG_aux0_ibias_cfg_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_AUX1_IBIAS_CFG_UNION
 �ṹ˵��  : AUX1_IBIAS_CFG �Ĵ����ṹ���塣��ַƫ����:0x165����ֵ:0x0A�����:8
 �Ĵ���˵��: DAC1 IBIAS���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux1_offset_cfg : 2;  /* bit[0-1]: AUXDAC1 OFFSET���ڡ�
                                                          00��+7.5mV��
                                                          01��0mV��
                                                          10��0mV��
                                                          11��-7.5mV�� */
        unsigned char  aux1_ibias_cfg  : 2;  /* bit[2-3]: AUXDAC1ƫ�õ������ڡ�
                                                          00��2.5uA��
                                                          01��5.0uA��
                                                          10��5.0uA��
                                                          11��7.5uA�� */
        unsigned char  reserved        : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_AUX1_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX1_IBIAS_CFG_aux1_offset_cfg_START  (0)
#define PMIC_AUX1_IBIAS_CFG_aux1_offset_cfg_END    (1)
#define PMIC_AUX1_IBIAS_CFG_aux1_ibias_cfg_START   (2)
#define PMIC_AUX1_IBIAS_CFG_aux1_ibias_cfg_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_0_UNION
 �ṹ˵��  : OTP0_0 �Ĵ����ṹ���塣��ַƫ����:0x16A����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[7:0]�� */
    } reg;
} PMIC_OTP0_0_UNION;
#endif
#define PMIC_OTP0_0_otp0_pdob0_START  (0)
#define PMIC_OTP0_0_otp0_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_1_UNION
 �ṹ˵��  : OTP0_1 �Ĵ����ṹ���塣��ַƫ����:0x16B����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[15:8]�� */
    } reg;
} PMIC_OTP0_1_UNION;
#endif
#define PMIC_OTP0_1_otp0_pdob1_START  (0)
#define PMIC_OTP0_1_otp0_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_2_UNION
 �ṹ˵��  : OTP0_2 �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[23:16]�� */
    } reg;
} PMIC_OTP0_2_UNION;
#endif
#define PMIC_OTP0_2_otp0_pdob2_START  (0)
#define PMIC_OTP0_2_otp0_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_3_UNION
 �ṹ˵��  : OTP0_3 �Ĵ����ṹ���塣��ַƫ����:0x16D����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[31:24]�� */
    } reg;
} PMIC_OTP0_3_UNION;
#endif
#define PMIC_OTP0_3_otp0_pdob3_START  (0)
#define PMIC_OTP0_3_otp0_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_CTRL_0_UNION
 �ṹ˵��  : OTP0_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x16E����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pwe_int   : 1;  /* bit[0]  : OTP0д�����źš�
                                                         0������otp_pwe������д������
                                                         1������otp_pwe������д������
                                                         �豣֤otp_pwe�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp0_pwe_pulse : 1;  /* bit[1]  : OTP0д������ơ�
                                                         0�����������壻
                                                         1������һ��310us�ĸߵ�ƽ���塣 */
        unsigned char  otp0_por_int   : 1;  /* bit[2]  : OTP0�������źš�
                                                         0������otp_por��������������
                                                         1������otp_por�������������
                                                         �豣֤otp_por�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp0_por_pulse : 1;  /* bit[3]  : OTP0��ʼ�������źš�
                                                         0�� ���������壻
                                                         1������һ��30us��por�ߵ�ƽ���塣 */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP0_CTRL_0_UNION;
#endif
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_START    (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_END      (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_START  (1)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_END    (1)
#define PMIC_OTP0_CTRL_0_otp0_por_int_START    (2)
#define PMIC_OTP0_CTRL_0_otp0_por_int_END      (2)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_START  (3)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_CTRL_1_UNION
 �ṹ˵��  : OTP0_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x16F����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pa      : 2;  /* bit[0-1]: OTP0�ĵ�ַ�źš�
                                                       00��ѡ��otp0������bit[7:0]���ж�/д������
                                                       01��ѡ��otp0������bit[15:8]���ж�/д������
                                                       10��ѡ��otp0������bit[23:16]���ж�/д������
                                                       11��ѡ��otp0������bit[31:24]���ж�/д������ */
        unsigned char  otp0_ptm     : 2;  /* bit[2-3]: OTP0����ģʽʹ���źš�
                                                       00���û�ģʽ��
                                                       01��margin-2��ģʽ��
                                                       10��margin-1��ģʽ��
                                                       11��δ���塣 */
        unsigned char  otp012_pprog : 1;  /* bit[4]  : OTP012���ģʽʹ���źš�
                                                       0���ر�otp��̣�
                                                       1��ʹ��otp��̡� */
        unsigned char  reserved     : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_OTP0_CTRL_1_UNION;
#endif
#define PMIC_OTP0_CTRL_1_otp0_pa_START       (0)
#define PMIC_OTP0_CTRL_1_otp0_pa_END         (1)
#define PMIC_OTP0_CTRL_1_otp0_ptm_START      (2)
#define PMIC_OTP0_CTRL_1_otp0_ptm_END        (3)
#define PMIC_OTP0_CTRL_1_otp012_pprog_START  (4)
#define PMIC_OTP0_CTRL_1_otp012_pprog_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_WDATA_UNION
 �ṹ˵��  : OTP0_WDATA �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0д�������ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdin : 8;  /* bit[0-7]: OTP0������ֵ�Ĵ����� */
    } reg;
} PMIC_OTP0_WDATA_UNION;
#endif
#define PMIC_OTP0_WDATA_otp0_pdin_START  (0)
#define PMIC_OTP0_WDATA_otp0_pdin_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_0_W_UNION
 �ṹ˵��  : OTP0_0_W �Ĵ����ṹ���塣��ַƫ����:0x171����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0_w : 8;  /* bit[0-7]: ��OTP0_0�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_0_W_UNION;
#endif
#define PMIC_OTP0_0_W_otp0_pdob0_w_START  (0)
#define PMIC_OTP0_0_W_otp0_pdob0_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_1_W_UNION
 �ṹ˵��  : OTP0_1_W �Ĵ����ṹ���塣��ַƫ����:0x172����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1_w : 8;  /* bit[0-7]: ��OTP0_1�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_1_W_UNION;
#endif
#define PMIC_OTP0_1_W_otp0_pdob1_w_START  (0)
#define PMIC_OTP0_1_W_otp0_pdob1_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_2_W_UNION
 �ṹ˵��  : OTP0_2_W �Ĵ����ṹ���塣��ַƫ����:0x173����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2_w : 8;  /* bit[0-7]: ��OTP0_2�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_2_W_UNION;
#endif
#define PMIC_OTP0_2_W_otp0_pdob2_w_START  (0)
#define PMIC_OTP0_2_W_otp0_pdob2_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_3_W_UNION
 �ṹ˵��  : OTP0_3_W �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3_w : 8;  /* bit[0-7]: ��OTP0_3�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_3_W_UNION;
#endif
#define PMIC_OTP0_3_W_otp0_pdob3_w_START  (0)
#define PMIC_OTP0_3_W_otp0_pdob3_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_0_UNION
 �ṹ˵��  : OTP1_0 �Ĵ����ṹ���塣��ַƫ����:0x175����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[7:0]�� */
    } reg;
} PMIC_OTP1_0_UNION;
#endif
#define PMIC_OTP1_0_otp1_pdob0_START  (0)
#define PMIC_OTP1_0_otp1_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_1_UNION
 �ṹ˵��  : OTP1_1 �Ĵ����ṹ���塣��ַƫ����:0x176����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[15:8]�� */
    } reg;
} PMIC_OTP1_1_UNION;
#endif
#define PMIC_OTP1_1_otp1_pdob1_START  (0)
#define PMIC_OTP1_1_otp1_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_2_UNION
 �ṹ˵��  : OTP1_2 �Ĵ����ṹ���塣��ַƫ����:0x177����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[23:16]�� */
    } reg;
} PMIC_OTP1_2_UNION;
#endif
#define PMIC_OTP1_2_otp1_pdob2_START  (0)
#define PMIC_OTP1_2_otp1_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_3_UNION
 �ṹ˵��  : OTP1_3 �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[31:24]�� */
    } reg;
} PMIC_OTP1_3_UNION;
#endif
#define PMIC_OTP1_3_otp1_pdob3_START  (0)
#define PMIC_OTP1_3_otp1_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_CTRL_0_UNION
 �ṹ˵��  : OTP1_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x179����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pwe_int   : 1;  /* bit[0]  : OTP1д�����źš�
                                                         0������otp_pwe������д������
                                                         1������otp_pwe������д������
                                                         �豣֤otp_pwe�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp1_pwe_pulse : 1;  /* bit[1]  : OTP1д������ơ�
                                                         0�����������壻
                                                         1������һ��310us�ĸߵ�ƽ���塣 */
        unsigned char  otp1_por_int   : 1;  /* bit[2]  : OTP1�������źš�
                                                         0������otp_por��������������
                                                         1������otp_por�������������
                                                         �豣֤otp_por�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp1_por_pulse : 1;  /* bit[3]  : OTP1��ʼ�������źš�
                                                         0�� ���������壻
                                                         1������һ��30us��por�ߵ�ƽ���塣 */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP1_CTRL_0_UNION;
#endif
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_START    (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_END      (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_START  (1)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_END    (1)
#define PMIC_OTP1_CTRL_0_otp1_por_int_START    (2)
#define PMIC_OTP1_CTRL_0_otp1_por_int_END      (2)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_START  (3)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_CTRL_1_UNION
 �ṹ˵��  : OTP1_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x17A����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pa  : 2;  /* bit[0-1]: OTP1�ĵ�ַ�źš�
                                                   00��ѡ��otp1������bit[7��0]���ж�/д������
                                                   01��ѡ��otp1������bit[15��8]���ж�/д������
                                                   10��ѡ��otp1������bit[23��16]���ж�/д������
                                                   11��ѡ��otp1������bit[31��24]���ж�/д������ */
        unsigned char  otp1_ptm : 2;  /* bit[2-3]: OTP1����ģʽʹ���źš�
                                                   00���û�ģʽ��
                                                   01��margin-2��ģʽ��
                                                   10��margin-1��ģʽ��
                                                   11��δ���塣 */
        unsigned char  reserved : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP1_CTRL_1_UNION;
#endif
#define PMIC_OTP1_CTRL_1_otp1_pa_START   (0)
#define PMIC_OTP1_CTRL_1_otp1_pa_END     (1)
#define PMIC_OTP1_CTRL_1_otp1_ptm_START  (2)
#define PMIC_OTP1_CTRL_1_otp1_ptm_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_WDATA_UNION
 �ṹ˵��  : OTP1_WDATA �Ĵ����ṹ���塣��ַƫ����:0x17B����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1д�������ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdin : 8;  /* bit[0-7]: OTP1������ֵ�Ĵ����� */
    } reg;
} PMIC_OTP1_WDATA_UNION;
#endif
#define PMIC_OTP1_WDATA_otp1_pdin_START  (0)
#define PMIC_OTP1_WDATA_otp1_pdin_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_0_W_UNION
 �ṹ˵��  : OTP1_0_W �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0_w : 8;  /* bit[0-7]: ��OTP1_0�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_0_W_UNION;
#endif
#define PMIC_OTP1_0_W_otp1_pdob0_w_START  (0)
#define PMIC_OTP1_0_W_otp1_pdob0_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_1_W_UNION
 �ṹ˵��  : OTP1_1_W �Ĵ����ṹ���塣��ַƫ����:0x17D����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1_w : 8;  /* bit[0-7]: ��OTP1_1�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_1_W_UNION;
#endif
#define PMIC_OTP1_1_W_otp1_pdob1_w_START  (0)
#define PMIC_OTP1_1_W_otp1_pdob1_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_2_W_UNION
 �ṹ˵��  : OTP1_2_W �Ĵ����ṹ���塣��ַƫ����:0x17E����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2_w : 8;  /* bit[0-7]: ��OTP1_2�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_2_W_UNION;
#endif
#define PMIC_OTP1_2_W_otp1_pdob2_w_START  (0)
#define PMIC_OTP1_2_W_otp1_pdob2_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_3_W_UNION
 �ṹ˵��  : OTP1_3_W �Ĵ����ṹ���塣��ַƫ����:0x17F����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3_w : 8;  /* bit[0-7]: ��OTP1_3�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_3_W_UNION;
#endif
#define PMIC_OTP1_3_W_otp1_pdob3_w_START  (0)
#define PMIC_OTP1_3_W_otp1_pdob3_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_0_UNION
 �ṹ˵��  : OTP2_0 �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2�ض��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob0 : 8;  /* bit[0-7]: OTP2�ض�ֵbit[7:0]�� */
    } reg;
} PMIC_OTP2_0_UNION;
#endif
#define PMIC_OTP2_0_otp2_pdob0_START  (0)
#define PMIC_OTP2_0_otp2_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_1_UNION
 �ṹ˵��  : OTP2_1 �Ĵ����ṹ���塣��ַƫ����:0x181����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2�ض��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob1 : 8;  /* bit[0-7]: OTP2�ض�ֵbit[15:8]�� */
    } reg;
} PMIC_OTP2_1_UNION;
#endif
#define PMIC_OTP2_1_otp2_pdob1_START  (0)
#define PMIC_OTP2_1_otp2_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_2_UNION
 �ṹ˵��  : OTP2_2 �Ĵ����ṹ���塣��ַƫ����:0x182����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2�ض��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob2 : 8;  /* bit[0-7]: OTP2�ض�ֵbit[23:16]�� */
    } reg;
} PMIC_OTP2_2_UNION;
#endif
#define PMIC_OTP2_2_otp2_pdob2_START  (0)
#define PMIC_OTP2_2_otp2_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_3_UNION
 �ṹ˵��  : OTP2_3 �Ĵ����ṹ���塣��ַƫ����:0x183����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2�ض��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob3 : 8;  /* bit[0-7]: OTP2�ض�ֵbit[31:24]�� */
    } reg;
} PMIC_OTP2_3_UNION;
#endif
#define PMIC_OTP2_3_otp2_pdob3_START  (0)
#define PMIC_OTP2_3_otp2_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_CTRL_0_UNION
 �ṹ˵��  : OTP2_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pwe_int   : 1;  /* bit[0]  : OTP2д�����źš�
                                                         0������otp_pwe������д������
                                                         1������otp_pwe������д������
                                                         �豣֤otp_pwe�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp2_pwe_pulse : 1;  /* bit[1]  : OTP2д������ơ�
                                                         0�����������壻
                                                         1������һ��310us�ĸߵ�ƽ���塣 */
        unsigned char  otp2_por_int   : 1;  /* bit[2]  : OTP2�������źš�
                                                         0������otp_por��������������
                                                         1������otp_por�������������
                                                         �豣֤otp_por�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp2_por_pulse : 1;  /* bit[3]  : OTP2��ʼ�������źš�
                                                         0�� ���������壻
                                                         1������һ��30us��por�ߵ�ƽ���塣 */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP2_CTRL_0_UNION;
#endif
#define PMIC_OTP2_CTRL_0_otp2_pwe_int_START    (0)
#define PMIC_OTP2_CTRL_0_otp2_pwe_int_END      (0)
#define PMIC_OTP2_CTRL_0_otp2_pwe_pulse_START  (1)
#define PMIC_OTP2_CTRL_0_otp2_pwe_pulse_END    (1)
#define PMIC_OTP2_CTRL_0_otp2_por_int_START    (2)
#define PMIC_OTP2_CTRL_0_otp2_por_int_END      (2)
#define PMIC_OTP2_CTRL_0_otp2_por_pulse_START  (3)
#define PMIC_OTP2_CTRL_0_otp2_por_pulse_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_CTRL_1_UNION
 �ṹ˵��  : OTP2_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x185����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pa  : 2;  /* bit[0-1]: OTP2�ĵ�ַ�źš�
                                                   00��ѡ��otp1������bit[7��0]���ж�/д������
                                                   01��ѡ��otp1������bit[15��8]���ж�/д������
                                                   10��ѡ��otp1������bit[23��16]���ж�/д������
                                                   11��ѡ��otp1������bit[31��24]���ж�/д������ */
        unsigned char  otp2_ptm : 2;  /* bit[2-3]: OTP2����ģʽʹ���źš�
                                                   00���û�ģʽ��
                                                   01��margin-2��ģʽ��
                                                   10��margin-1��ģʽ��
                                                   11��δ���塣 */
        unsigned char  reserved : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP2_CTRL_1_UNION;
#endif
#define PMIC_OTP2_CTRL_1_otp2_pa_START   (0)
#define PMIC_OTP2_CTRL_1_otp2_pa_END     (1)
#define PMIC_OTP2_CTRL_1_otp2_ptm_START  (2)
#define PMIC_OTP2_CTRL_1_otp2_ptm_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_WDATA_UNION
 �ṹ˵��  : OTP2_WDATA �Ĵ����ṹ���塣��ַƫ����:0x186����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2д�������ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdin : 8;  /* bit[0-7]: OTP2������ֵ�Ĵ����� */
    } reg;
} PMIC_OTP2_WDATA_UNION;
#endif
#define PMIC_OTP2_WDATA_otp2_pdin_START  (0)
#define PMIC_OTP2_WDATA_otp2_pdin_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_0_W_UNION
 �ṹ˵��  : OTP2_0_W �Ĵ����ṹ���塣��ַƫ����:0x187����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2������Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob0_w : 8;  /* bit[0-7]: ��OTP2_0�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP2_0_W_UNION;
#endif
#define PMIC_OTP2_0_W_otp2_pdob0_w_START  (0)
#define PMIC_OTP2_0_W_otp2_pdob0_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_1_W_UNION
 �ṹ˵��  : OTP2_1_W �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2������Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob1_w : 8;  /* bit[0-7]: ��OTP2_1�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP2_1_W_UNION;
#endif
#define PMIC_OTP2_1_W_otp2_pdob1_w_START  (0)
#define PMIC_OTP2_1_W_otp2_pdob1_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_2_W_UNION
 �ṹ˵��  : OTP2_2_W �Ĵ����ṹ���塣��ַƫ����:0x189����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2������Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob2_w : 8;  /* bit[0-7]: ��OTP2_2�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP2_2_W_UNION;
#endif
#define PMIC_OTP2_2_W_otp2_pdob2_w_START  (0)
#define PMIC_OTP2_2_W_otp2_pdob2_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP2_3_W_UNION
 �ṹ˵��  : OTP2_3_W �Ĵ����ṹ���塣��ַƫ����:0x18A����ֵ:0x00�����:8
 �Ĵ���˵��: OTP2������Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob3_w : 8;  /* bit[0-7]: ��OTP2_3�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP2_3_W_UNION;
#endif
#define PMIC_OTP2_3_W_otp2_pdob3_w_START  (0)
#define PMIC_OTP2_3_W_otp2_pdob3_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG0_UNION
 �ṹ˵��  : HRST_REG0 �Ĵ����ṹ���塣��ַƫ����:0x18B����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg0 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG0_UNION;
#endif
#define PMIC_HRST_REG0_np_hrst_reg0_START  (0)
#define PMIC_HRST_REG0_np_hrst_reg0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG1_UNION
 �ṹ˵��  : HRST_REG1 �Ĵ����ṹ���塣��ַƫ����:0x18C����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg1 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG1_UNION;
#endif
#define PMIC_HRST_REG1_np_hrst_reg1_START  (0)
#define PMIC_HRST_REG1_np_hrst_reg1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG2_UNION
 �ṹ˵��  : HRST_REG2 �Ĵ����ṹ���塣��ַƫ����:0x18D����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg2 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG2_UNION;
#endif
#define PMIC_HRST_REG2_np_hrst_reg2_START  (0)
#define PMIC_HRST_REG2_np_hrst_reg2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG3_UNION
 �ṹ˵��  : HRST_REG3 �Ĵ����ṹ���塣��ַƫ����:0x18E����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg3 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG3_UNION;
#endif
#define PMIC_HRST_REG3_np_hrst_reg3_START  (0)
#define PMIC_HRST_REG3_np_hrst_reg3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG4_UNION
 �ṹ˵��  : HRST_REG4 �Ĵ����ṹ���塣��ַƫ����:0x18F����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg4 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG4_UNION;
#endif
#define PMIC_HRST_REG4_np_hrst_reg4_START  (0)
#define PMIC_HRST_REG4_np_hrst_reg4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG5_UNION
 �ṹ˵��  : HRST_REG5 �Ĵ����ṹ���塣��ַƫ����:0x190����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg5 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG5_UNION;
#endif
#define PMIC_HRST_REG5_np_hrst_reg5_START  (0)
#define PMIC_HRST_REG5_np_hrst_reg5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG6_UNION
 �ṹ˵��  : HRST_REG6 �Ĵ����ṹ���塣��ַƫ����:0x191����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg6 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG6_UNION;
#endif
#define PMIC_HRST_REG6_np_hrst_reg6_START  (0)
#define PMIC_HRST_REG6_np_hrst_reg6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG7_UNION
 �ṹ˵��  : HRST_REG7 �Ĵ����ṹ���塣��ַƫ����:0x192����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg7 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG7_UNION;
#endif
#define PMIC_HRST_REG7_np_hrst_reg7_START  (0)
#define PMIC_HRST_REG7_np_hrst_reg7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG8_UNION
 �ṹ˵��  : HRST_REG8 �Ĵ����ṹ���塣��ַƫ����:0x193����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg8 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG8_UNION;
#endif
#define PMIC_HRST_REG8_np_hrst_reg8_START  (0)
#define PMIC_HRST_REG8_np_hrst_reg8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG9_UNION
 �ṹ˵��  : HRST_REG9 �Ĵ����ṹ���塣��ַƫ����:0x194����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg9 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG9_UNION;
#endif
#define PMIC_HRST_REG9_np_hrst_reg9_START  (0)
#define PMIC_HRST_REG9_np_hrst_reg9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG10_UNION
 �ṹ˵��  : HRST_REG10 �Ĵ����ṹ���塣��ַƫ����:0x195����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg10 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG10_UNION;
#endif
#define PMIC_HRST_REG10_np_hrst_reg10_START  (0)
#define PMIC_HRST_REG10_np_hrst_reg10_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG11_UNION
 �ṹ˵��  : HRST_REG11 �Ĵ����ṹ���塣��ַƫ����:0x196����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg11 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG11_UNION;
#endif
#define PMIC_HRST_REG11_np_hrst_reg11_START  (0)
#define PMIC_HRST_REG11_np_hrst_reg11_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG12_UNION
 �ṹ˵��  : HRST_REG12 �Ĵ����ṹ���塣��ַƫ����:0x197����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���12��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg12 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG12_UNION;
#endif
#define PMIC_HRST_REG12_np_hrst_reg12_START  (0)
#define PMIC_HRST_REG12_np_hrst_reg12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG13_UNION
 �ṹ˵��  : HRST_REG13 �Ĵ����ṹ���塣��ַƫ����:0x198����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���13��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg13 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG13_UNION;
#endif
#define PMIC_HRST_REG13_np_hrst_reg13_START  (0)
#define PMIC_HRST_REG13_np_hrst_reg13_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG14_UNION
 �ṹ˵��  : HRST_REG14 �Ĵ����ṹ���塣��ַƫ����:0x199����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���14��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg14 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG14_UNION;
#endif
#define PMIC_HRST_REG14_np_hrst_reg14_START  (0)
#define PMIC_HRST_REG14_np_hrst_reg14_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DEBUG_CTRL_UNION
 �ṹ˵��  : DEBUG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x19A����ֵ:0x00�����:8
 �Ĵ���˵��: DEBUG�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_rc_debug : 1;  /* bit[0]  : RCʱ��debugʹ���źš�
                                                          0������ʹ�ã�
                                                          1����256Kʱ��������
                                                          ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reserved        : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_DEBUG_CTRL_UNION;
#endif
#define PMIC_DEBUG_CTRL_np_reg_rc_debug_START  (0)
#define PMIC_DEBUG_CTRL_np_reg_rc_debug_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_DEBUG0_UNION
 �ṹ˵��  : SYS_DEBUG0 �Ĵ����ṹ���塣��ַƫ����:0x19B����ֵ:0x00�����:8
 �Ĵ���˵��: ����ϵͳdebugԤ���Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug0 : 8;  /* bit[0-7]: ����ϵͳdebugԤ���Ĵ�����
                                                     ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
    } reg;
} PMIC_SYS_DEBUG0_UNION;
#endif
#define PMIC_SYS_DEBUG0_sys_debug0_START  (0)
#define PMIC_SYS_DEBUG0_sys_debug0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_DEBUG1_UNION
 �ṹ˵��  : SYS_DEBUG1 �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00�����:8
 �Ĵ���˵��: ����ϵͳdebugԤ���Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug1 : 8;  /* bit[0-7]: ����ϵͳdebugԤ���Ĵ�����
                                                     ע���Ĵ�����Ҫ���Ĵ���DEBUG_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
    } reg;
} PMIC_SYS_DEBUG1_UNION;
#endif
#define PMIC_SYS_DEBUG1_sys_debug1_START  (0)
#define PMIC_SYS_DEBUG1_sys_debug1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DEBUG_LOCK_UNION
 �ṹ˵��  : DEBUG_LOCK �Ĵ����ṹ���塣��ַƫ����:0x19D����ֵ:0x00�����:8
 �Ĵ���˵��: debug�Ĵ���д���ο��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  debug_lock : 8;  /* bit[0-7]: Ϊ��ֹ�����дSYS_CTRL0��DEBUG_CTRL��SYS_DEBUG0/1������ϵͳ����ֻ�е�debug_lockдΪ8'h6C��ʱ������3���Ĵ���������һֱд�롣 */
    } reg;
} PMIC_DEBUG_LOCK_UNION;
#endif
#define PMIC_DEBUG_LOCK_debug_lock_START  (0)
#define PMIC_DEBUG_LOCK_debug_lock_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DAC0_DIN_MSB_UNION
 �ṹ˵��  : DAC0_DIN_MSB �Ĵ����ṹ���塣��ַƫ����:0x19F����ֵ:0x00�����:8
 �Ĵ���˵��: DAC0 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_msb : 2;  /* bit[0-1]: dac0 din[9��8]ӳ��Ĵ����� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_DAC0_DIN_MSB_UNION;
#endif
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_START  (0)
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_DAC0_DIN_LSB_UNION
 �ṹ˵��  : DAC0_DIN_LSB �Ĵ����ṹ���塣��ַƫ����:0x1A0����ֵ:0x00�����:8
 �Ĵ���˵��: DAC0 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_lsb : 8;  /* bit[0-7]: dac0 din[7:0]ӳ��Ĵ����� */
    } reg;
} PMIC_DAC0_DIN_LSB_UNION;
#endif
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_START  (0)
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DAC1_DIN_MSB_UNION
 �ṹ˵��  : DAC1_DIN_MSB �Ĵ����ṹ���塣��ַƫ����:0x1A1����ֵ:0x00�����:8
 �Ĵ���˵��: DAC1 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_msb : 2;  /* bit[0-1]: dac1 din[9��8]ӳ��Ĵ����� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_DAC1_DIN_MSB_UNION;
#endif
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_START  (0)
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_DAC1_DIN_LSB_UNION
 �ṹ˵��  : DAC1_DIN_LSB �Ĵ����ṹ���塣��ַƫ����:0x1A2����ֵ:0x00�����:8
 �Ĵ���˵��: DAC1 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_lsb : 8;  /* bit[0-7]: dac1 din[7:0]ӳ��Ĵ����� */
    } reg;
} PMIC_DAC1_DIN_LSB_UNION;
#endif
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_START  (0)
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_END    (7)




/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_IRQ0_UNION
 �ṹ˵��  : IRQ0 �Ĵ����ṹ���塣��ַƫ����:0x1B0����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[0]: ���£�оƬ�¶ȳ����趨�ı����¶ȣ��¼��ж�(������ȥ��1ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vbus_det_insert_d20mr : 1;  /* bit[1]: ����״̬�£�����������ж�(������ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vbus_det_insert_d20mf : 1;  /* bit[2]: ����״̬�£�������γ��ж�(�½���ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  alarmon_r             : 1;  /* bit[3]: ����״̬�£������жϡ�
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d6sf           : 1;  /* bit[4]: ����״̬�£��������³���6s�¼��ж�(�½���ȥ��6s)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d1sf           : 1;  /* bit[5]: ����״̬�£��������³���1s�¼��ж�(�½���ȥ��1s)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d20mr          : 1;  /* bit[6]: ����״̬�£������ͷ��¼��ж�(������ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d20mf          : 1;  /* bit[7]: ����״̬�£����������¼��ж�(�½���ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
    } reg;
} PMIC_IRQ0_UNION;
#endif
#define PMIC_IRQ0_thsd_otmp125_d1mr_START      (0)
#define PMIC_IRQ0_thsd_otmp125_d1mr_END        (0)
#define PMIC_IRQ0_vbus_det_insert_d20mr_START  (1)
#define PMIC_IRQ0_vbus_det_insert_d20mr_END    (1)
#define PMIC_IRQ0_vbus_det_insert_d20mf_START  (2)
#define PMIC_IRQ0_vbus_det_insert_d20mf_END    (2)
#define PMIC_IRQ0_alarmon_r_START              (3)
#define PMIC_IRQ0_alarmon_r_END                (3)
#define PMIC_IRQ0_pwronn_d6sf_START            (4)
#define PMIC_IRQ0_pwronn_d6sf_END              (4)
#define PMIC_IRQ0_pwronn_d1sf_START            (5)
#define PMIC_IRQ0_pwronn_d1sf_END              (5)
#define PMIC_IRQ0_pwronn_d20mr_START           (6)
#define PMIC_IRQ0_pwronn_d20mr_END             (6)
#define PMIC_IRQ0_pwronn_d20mf_START           (7)
#define PMIC_IRQ0_pwronn_d20mf_END             (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ1_UNION
 �ṹ˵��  : IRQ1 �Ĵ����ṹ���塣��ַƫ����:0x1B1����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocp_scp_r  : 1;  /* bit[0]  : OCP/SCP���ж�
                                                     0:�޴��жϣ�
                                                     1:��ʾ������һ��BUCK���������������߶�·����������CLASSD/LDO��������������CPU��ѯ����Ҫȥ�鿴����Ĺ�������Ĵ����鿴����һ������������������д1����ж������� */
        unsigned char  coul_r     : 1;  /* bit[1]  : ���ؼ��¼��жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ�PMU�ӵ��Ժ�Ҫȥ�鿴����Ŀ��ؼ��жϼĴ���ȷ������һ���жϡ� */
        unsigned char  sim0_hpd_r : 1;  /* bit[2]  : sim0_hpd�������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  sim0_hpd_f : 1;  /* bit[3]  : sim0_hpd�½����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  sim1_hpd_r : 1;  /* bit[4]  : sim1_hpd�������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  sim1_hpd_f : 1;  /* bit[5]  : sim1_hpd�½����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  reserved   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_IRQ1_UNION;
#endif
#define PMIC_IRQ1_ocp_scp_r_START   (0)
#define PMIC_IRQ1_ocp_scp_r_END     (0)
#define PMIC_IRQ1_coul_r_START      (1)
#define PMIC_IRQ1_coul_r_END        (1)
#define PMIC_IRQ1_sim0_hpd_r_START  (2)
#define PMIC_IRQ1_sim0_hpd_r_END    (2)
#define PMIC_IRQ1_sim0_hpd_f_START  (3)
#define PMIC_IRQ1_sim0_hpd_f_END    (3)
#define PMIC_IRQ1_sim1_hpd_r_START  (4)
#define PMIC_IRQ1_sim1_hpd_r_END    (4)
#define PMIC_IRQ1_sim1_hpd_f_START  (5)
#define PMIC_IRQ1_sim1_hpd_f_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ0_UNION
 �ṹ˵��  : OCP_IRQ0 �Ĵ����ṹ���塣��ַƫ����:0x1B2����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo3   : 1;  /* bit[0]: LDO3��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpldo2   : 1;  /* bit[1]: LDO2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpldo1   : 1;  /* bit[2]: LDO1��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpldo0_2 : 1;  /* bit[3]: LDO0_2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck3  : 1;  /* bit[4]: BUCK3��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck2  : 1;  /* bit[5]: BUCK2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck1  : 1;  /* bit[6]: BUCK1��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck0  : 1;  /* bit[7]: BUCK0��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ0_UNION;
#endif
#define PMIC_OCP_IRQ0_ocpldo3_START    (0)
#define PMIC_OCP_IRQ0_ocpldo3_END      (0)
#define PMIC_OCP_IRQ0_ocpldo2_START    (1)
#define PMIC_OCP_IRQ0_ocpldo2_END      (1)
#define PMIC_OCP_IRQ0_ocpldo1_START    (2)
#define PMIC_OCP_IRQ0_ocpldo1_END      (2)
#define PMIC_OCP_IRQ0_ocpldo0_2_START  (3)
#define PMIC_OCP_IRQ0_ocpldo0_2_END    (3)
#define PMIC_OCP_IRQ0_ocpbuck3_START   (4)
#define PMIC_OCP_IRQ0_ocpbuck3_END     (4)
#define PMIC_OCP_IRQ0_ocpbuck2_START   (5)
#define PMIC_OCP_IRQ0_ocpbuck2_END     (5)
#define PMIC_OCP_IRQ0_ocpbuck1_START   (6)
#define PMIC_OCP_IRQ0_ocpbuck1_END     (6)
#define PMIC_OCP_IRQ0_ocpbuck0_START   (7)
#define PMIC_OCP_IRQ0_ocpbuck0_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ1_UNION
 �ṹ˵��  : OCP_IRQ1 �Ĵ����ṹ���塣��ַƫ����:0x1B3����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo12 : 1;  /* bit[0]: LDO12��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo11 : 1;  /* bit[1]: LDO11��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo10 : 1;  /* bit[2]: LDO10��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo9  : 1;  /* bit[3]: LDO9��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo8  : 1;  /* bit[4]: LDO8��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo7  : 1;  /* bit[5]: LDO7��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo5  : 1;  /* bit[6]: LDO5��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo4  : 1;  /* bit[7]: LDO4��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ1_UNION;
#endif
#define PMIC_OCP_IRQ1_ocpldo12_START  (0)
#define PMIC_OCP_IRQ1_ocpldo12_END    (0)
#define PMIC_OCP_IRQ1_ocpldo11_START  (1)
#define PMIC_OCP_IRQ1_ocpldo11_END    (1)
#define PMIC_OCP_IRQ1_ocpldo10_START  (2)
#define PMIC_OCP_IRQ1_ocpldo10_END    (2)
#define PMIC_OCP_IRQ1_ocpldo9_START   (3)
#define PMIC_OCP_IRQ1_ocpldo9_END     (3)
#define PMIC_OCP_IRQ1_ocpldo8_START   (4)
#define PMIC_OCP_IRQ1_ocpldo8_END     (4)
#define PMIC_OCP_IRQ1_ocpldo7_START   (5)
#define PMIC_OCP_IRQ1_ocpldo7_END     (5)
#define PMIC_OCP_IRQ1_ocpldo5_START   (6)
#define PMIC_OCP_IRQ1_ocpldo5_END     (6)
#define PMIC_OCP_IRQ1_ocpldo4_START   (7)
#define PMIC_OCP_IRQ1_ocpldo4_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ2_UNION
 �ṹ˵��  : OCP_IRQ2 �Ĵ����ṹ���塣��ַƫ����:0x1B4����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo21 : 1;  /* bit[0]: LDO21��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo20 : 1;  /* bit[1]: LDO20��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo19 : 1;  /* bit[2]: LDO19��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo17 : 1;  /* bit[3]: LDO17��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo16 : 1;  /* bit[4]: LDO16��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo15 : 1;  /* bit[5]: LDO15��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo14 : 1;  /* bit[6]: LDO14��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo13 : 1;  /* bit[7]: LDO13��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ2_UNION;
#endif
#define PMIC_OCP_IRQ2_ocpldo21_START  (0)
#define PMIC_OCP_IRQ2_ocpldo21_END    (0)
#define PMIC_OCP_IRQ2_ocpldo20_START  (1)
#define PMIC_OCP_IRQ2_ocpldo20_END    (1)
#define PMIC_OCP_IRQ2_ocpldo19_START  (2)
#define PMIC_OCP_IRQ2_ocpldo19_END    (2)
#define PMIC_OCP_IRQ2_ocpldo17_START  (3)
#define PMIC_OCP_IRQ2_ocpldo17_END    (3)
#define PMIC_OCP_IRQ2_ocpldo16_START  (4)
#define PMIC_OCP_IRQ2_ocpldo16_END    (4)
#define PMIC_OCP_IRQ2_ocpldo15_START  (5)
#define PMIC_OCP_IRQ2_ocpldo15_END    (5)
#define PMIC_OCP_IRQ2_ocpldo14_START  (6)
#define PMIC_OCP_IRQ2_ocpldo14_END    (6)
#define PMIC_OCP_IRQ2_ocpldo13_START  (7)
#define PMIC_OCP_IRQ2_ocpldo13_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ3_UNION
 �ṹ˵��  : OCP_IRQ3 �Ĵ����ṹ���塣��ַƫ����:0x1B5����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo29 : 1;  /* bit[0]: LDO29��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo28 : 1;  /* bit[1]: LDO28��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo27 : 1;  /* bit[2]: LDO27��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo26 : 1;  /* bit[3]: LDO26��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo25 : 1;  /* bit[4]: LDO25��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo24 : 1;  /* bit[5]: LDO24��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo23 : 1;  /* bit[6]: LDO23��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo22 : 1;  /* bit[7]: LDO22��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ3_UNION;
#endif
#define PMIC_OCP_IRQ3_ocpldo29_START  (0)
#define PMIC_OCP_IRQ3_ocpldo29_END    (0)
#define PMIC_OCP_IRQ3_ocpldo28_START  (1)
#define PMIC_OCP_IRQ3_ocpldo28_END    (1)
#define PMIC_OCP_IRQ3_ocpldo27_START  (2)
#define PMIC_OCP_IRQ3_ocpldo27_END    (2)
#define PMIC_OCP_IRQ3_ocpldo26_START  (3)
#define PMIC_OCP_IRQ3_ocpldo26_END    (3)
#define PMIC_OCP_IRQ3_ocpldo25_START  (4)
#define PMIC_OCP_IRQ3_ocpldo25_END    (4)
#define PMIC_OCP_IRQ3_ocpldo24_START  (5)
#define PMIC_OCP_IRQ3_ocpldo24_END    (5)
#define PMIC_OCP_IRQ3_ocpldo23_START  (6)
#define PMIC_OCP_IRQ3_ocpldo23_END    (6)
#define PMIC_OCP_IRQ3_ocpldo22_START  (7)
#define PMIC_OCP_IRQ3_ocpldo22_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ4_UNION
 �ṹ˵��  : OCP_IRQ4 �Ĵ����ṹ���塣��ַƫ����:0x1B6����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_ocp : 1;  /* bit[0]  : classd��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo34   : 1;  /* bit[1]  : LDO34��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo33   : 1;  /* bit[2]  : LDO33��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo32   : 1;  /* bit[3]  : LDO32��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo31   : 1;  /* bit[4]  : LDO31��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  reserved   : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_OCP_IRQ4_UNION;
#endif
#define PMIC_OCP_IRQ4_classd_ocp_START  (0)
#define PMIC_OCP_IRQ4_classd_ocp_END    (0)
#define PMIC_OCP_IRQ4_ocpldo34_START    (1)
#define PMIC_OCP_IRQ4_ocpldo34_END      (1)
#define PMIC_OCP_IRQ4_ocpldo33_START    (2)
#define PMIC_OCP_IRQ4_ocpldo33_END      (2)
#define PMIC_OCP_IRQ4_ocpldo32_START    (3)
#define PMIC_OCP_IRQ4_ocpldo32_END      (3)
#define PMIC_OCP_IRQ4_ocpldo31_START    (4)
#define PMIC_OCP_IRQ4_ocpldo31_END      (4)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ5_UNION
 �ṹ˵��  : OCP_IRQ5 �Ĵ����ṹ���塣��ַƫ����:0x1B7����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_scp       : 1;  /* bit[0]  : BUCK3�����·�жϡ�
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned char  buck2_scp       : 1;  /* bit[1]  : BUCK2�����·�жϡ�
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned char  buck1_scp       : 1;  /* bit[2]  : BUCK1�����·�жϡ�
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned char  buck0_scp       : 1;  /* bit[3]  : BUCK0�����·�жϡ�
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned char  xo_ldo_buff_scp : 1;  /* bit[4]  : xo_ldo_buff�����·�жϡ�
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned char  reserved        : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_OCP_IRQ5_UNION;
#endif
#define PMIC_OCP_IRQ5_buck3_scp_START        (0)
#define PMIC_OCP_IRQ5_buck3_scp_END          (0)
#define PMIC_OCP_IRQ5_buck2_scp_START        (1)
#define PMIC_OCP_IRQ5_buck2_scp_END          (1)
#define PMIC_OCP_IRQ5_buck1_scp_START        (2)
#define PMIC_OCP_IRQ5_buck1_scp_END          (2)
#define PMIC_OCP_IRQ5_buck0_scp_START        (3)
#define PMIC_OCP_IRQ5_buck0_scp_END          (3)
#define PMIC_OCP_IRQ5_xo_ldo_buff_scp_START  (4)
#define PMIC_OCP_IRQ5_xo_ldo_buff_scp_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP0_UNION
 �ṹ˵��  : NP_OCP0 �Ĵ����ṹ���塣��ַƫ����:0x1B8����ֵ:0x00�����:8
 �Ĵ���˵��: BUKC0-3��LDO0-3 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo3   : 1;  /* bit[0]: LDO3��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpldo2   : 1;  /* bit[1]: LDO2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpldo1   : 1;  /* bit[2]: LDO1��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpldo0_2 : 1;  /* bit[3]: LDO0_2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck3  : 1;  /* bit[4]: BUCK3��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck2  : 1;  /* bit[5]: BUCK2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck1  : 1;  /* bit[6]: BUCK1��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck0  : 1;  /* bit[7]: BUCK0��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
    } reg;
} PMIC_NP_OCP0_UNION;
#endif
#define PMIC_NP_OCP0_np_ocpldo3_START    (0)
#define PMIC_NP_OCP0_np_ocpldo3_END      (0)
#define PMIC_NP_OCP0_np_ocpldo2_START    (1)
#define PMIC_NP_OCP0_np_ocpldo2_END      (1)
#define PMIC_NP_OCP0_np_ocpldo1_START    (2)
#define PMIC_NP_OCP0_np_ocpldo1_END      (2)
#define PMIC_NP_OCP0_np_ocpldo0_2_START  (3)
#define PMIC_NP_OCP0_np_ocpldo0_2_END    (3)
#define PMIC_NP_OCP0_np_ocpbuck3_START   (4)
#define PMIC_NP_OCP0_np_ocpbuck3_END     (4)
#define PMIC_NP_OCP0_np_ocpbuck2_START   (5)
#define PMIC_NP_OCP0_np_ocpbuck2_END     (5)
#define PMIC_NP_OCP0_np_ocpbuck1_START   (6)
#define PMIC_NP_OCP0_np_ocpbuck1_END     (6)
#define PMIC_NP_OCP0_np_ocpbuck0_START   (7)
#define PMIC_NP_OCP0_np_ocpbuck0_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP1_UNION
 �ṹ˵��  : NP_OCP1 �Ĵ����ṹ���塣��ַƫ����:0x1B9����ֵ:0x00�����:8
 �Ĵ���˵��: LDO4-12 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo12 : 1;  /* bit[0]: LDO12��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo11 : 1;  /* bit[1]: LDO11��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo10 : 1;  /* bit[2]: LDO10��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo9  : 1;  /* bit[3]: LDO9��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo8  : 1;  /* bit[4]: LDO8��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo7  : 1;  /* bit[5]: LDO7��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo5  : 1;  /* bit[6]: LDO5��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo4  : 1;  /* bit[7]: LDO3��������¼���¼�Ĵ�����
                                                    0�����жϣ�
                                                    1�����жϡ� */
    } reg;
} PMIC_NP_OCP1_UNION;
#endif
#define PMIC_NP_OCP1_np_ocpldo12_START  (0)
#define PMIC_NP_OCP1_np_ocpldo12_END    (0)
#define PMIC_NP_OCP1_np_ocpldo11_START  (1)
#define PMIC_NP_OCP1_np_ocpldo11_END    (1)
#define PMIC_NP_OCP1_np_ocpldo10_START  (2)
#define PMIC_NP_OCP1_np_ocpldo10_END    (2)
#define PMIC_NP_OCP1_np_ocpldo9_START   (3)
#define PMIC_NP_OCP1_np_ocpldo9_END     (3)
#define PMIC_NP_OCP1_np_ocpldo8_START   (4)
#define PMIC_NP_OCP1_np_ocpldo8_END     (4)
#define PMIC_NP_OCP1_np_ocpldo7_START   (5)
#define PMIC_NP_OCP1_np_ocpldo7_END     (5)
#define PMIC_NP_OCP1_np_ocpldo5_START   (6)
#define PMIC_NP_OCP1_np_ocpldo5_END     (6)
#define PMIC_NP_OCP1_np_ocpldo4_START   (7)
#define PMIC_NP_OCP1_np_ocpldo4_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP2_UNION
 �ṹ˵��  : NP_OCP2 �Ĵ����ṹ���塣��ַƫ����:0x1BA����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12-20 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo21 : 1;  /* bit[0]: LDO21��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo20 : 1;  /* bit[1]: LDO20��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo19 : 1;  /* bit[2]: LDO19��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo17 : 1;  /* bit[3]: LDO17��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo16 : 1;  /* bit[4]: LDO16��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo15 : 1;  /* bit[5]: LDO15��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo14 : 1;  /* bit[6]: LDO14��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo13 : 1;  /* bit[7]: LDO13��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
    } reg;
} PMIC_NP_OCP2_UNION;
#endif
#define PMIC_NP_OCP2_np_ocpldo21_START  (0)
#define PMIC_NP_OCP2_np_ocpldo21_END    (0)
#define PMIC_NP_OCP2_np_ocpldo20_START  (1)
#define PMIC_NP_OCP2_np_ocpldo20_END    (1)
#define PMIC_NP_OCP2_np_ocpldo19_START  (2)
#define PMIC_NP_OCP2_np_ocpldo19_END    (2)
#define PMIC_NP_OCP2_np_ocpldo17_START  (3)
#define PMIC_NP_OCP2_np_ocpldo17_END    (3)
#define PMIC_NP_OCP2_np_ocpldo16_START  (4)
#define PMIC_NP_OCP2_np_ocpldo16_END    (4)
#define PMIC_NP_OCP2_np_ocpldo15_START  (5)
#define PMIC_NP_OCP2_np_ocpldo15_END    (5)
#define PMIC_NP_OCP2_np_ocpldo14_START  (6)
#define PMIC_NP_OCP2_np_ocpldo14_END    (6)
#define PMIC_NP_OCP2_np_ocpldo13_START  (7)
#define PMIC_NP_OCP2_np_ocpldo13_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP3_UNION
 �ṹ˵��  : NP_OCP3 �Ĵ����ṹ���塣��ַƫ����:0x1BB����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21-28 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo29 : 1;  /* bit[0]: LDO29��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo28 : 1;  /* bit[1]: LDO28��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo27 : 1;  /* bit[2]: LDO27��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo26 : 1;  /* bit[3]: LDO26��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo25 : 1;  /* bit[4]: LDO25��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo24 : 1;  /* bit[5]: LDO24��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo23 : 1;  /* bit[6]: LDO23��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo22 : 1;  /* bit[7]: LDO22��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
    } reg;
} PMIC_NP_OCP3_UNION;
#endif
#define PMIC_NP_OCP3_np_ocpldo29_START  (0)
#define PMIC_NP_OCP3_np_ocpldo29_END    (0)
#define PMIC_NP_OCP3_np_ocpldo28_START  (1)
#define PMIC_NP_OCP3_np_ocpldo28_END    (1)
#define PMIC_NP_OCP3_np_ocpldo27_START  (2)
#define PMIC_NP_OCP3_np_ocpldo27_END    (2)
#define PMIC_NP_OCP3_np_ocpldo26_START  (3)
#define PMIC_NP_OCP3_np_ocpldo26_END    (3)
#define PMIC_NP_OCP3_np_ocpldo25_START  (4)
#define PMIC_NP_OCP3_np_ocpldo25_END    (4)
#define PMIC_NP_OCP3_np_ocpldo24_START  (5)
#define PMIC_NP_OCP3_np_ocpldo24_END    (5)
#define PMIC_NP_OCP3_np_ocpldo23_START  (6)
#define PMIC_NP_OCP3_np_ocpldo23_END    (6)
#define PMIC_NP_OCP3_np_ocpldo22_START  (7)
#define PMIC_NP_OCP3_np_ocpldo22_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP4_UNION
 �ṹ˵��  : NP_OCP4 �Ĵ����ṹ���塣��ַƫ����:0x1BC����ֵ:0x00�����:8
 �Ĵ���˵��: LDO31-34 CLASSD OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_classd_ocp : 1;  /* bit[0]  : classd��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo34   : 1;  /* bit[1]  : LDO34��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo33   : 1;  /* bit[2]  : LDO33��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo32   : 1;  /* bit[3]  : LDO32��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo31   : 1;  /* bit[4]  : LDO31��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_NP_OCP4_UNION;
#endif
#define PMIC_NP_OCP4_np_classd_ocp_START  (0)
#define PMIC_NP_OCP4_np_classd_ocp_END    (0)
#define PMIC_NP_OCP4_np_ocpldo34_START    (1)
#define PMIC_NP_OCP4_np_ocpldo34_END      (1)
#define PMIC_NP_OCP4_np_ocpldo33_START    (2)
#define PMIC_NP_OCP4_np_ocpldo33_END      (2)
#define PMIC_NP_OCP4_np_ocpldo32_START    (3)
#define PMIC_NP_OCP4_np_ocpldo32_END      (3)
#define PMIC_NP_OCP4_np_ocpldo31_START    (4)
#define PMIC_NP_OCP4_np_ocpldo31_END      (4)


/*****************************************************************************
 �ṹ��    : PMIC_NP_SCP_UNION
 �ṹ˵��  : NP_SCP �Ĵ����ṹ���塣��ַƫ����:0x1BD����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0-3 SCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_buck3_scp       : 1;  /* bit[0]  : BUCK3�����·�¼���¼�Ĵ�����
                                                             0��û�з��������¼���
                                                             1�����������¼��� */
        unsigned char  np_buck2_scp       : 1;  /* bit[1]  : BUCK2�����·�¼���¼�Ĵ�����
                                                             0��û�з��������¼���
                                                             1�����������¼��� */
        unsigned char  np_buck1_scp       : 1;  /* bit[2]  : BUCK1�����·�¼���¼�Ĵ�����
                                                             0��û�з��������¼���
                                                             1�����������¼��� */
        unsigned char  np_buck0_scp       : 1;  /* bit[3]  : BUCK0�����·�¼���¼�Ĵ�����
                                                             0��û�з��������¼���
                                                             1�����������¼��� */
        unsigned char  np_xo_ldo_buff_scp : 1;  /* bit[4]  : xo_ldo_buff�����·�¼���¼�Ĵ�����
                                                             0��û�з��������¼���
                                                             1�����������¼��� */
        unsigned char  reserved           : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_NP_SCP_UNION;
#endif
#define PMIC_NP_SCP_np_buck3_scp_START        (0)
#define PMIC_NP_SCP_np_buck3_scp_END          (0)
#define PMIC_NP_SCP_np_buck2_scp_START        (1)
#define PMIC_NP_SCP_np_buck2_scp_END          (1)
#define PMIC_NP_SCP_np_buck1_scp_START        (2)
#define PMIC_NP_SCP_np_buck1_scp_END          (2)
#define PMIC_NP_SCP_np_buck0_scp_START        (3)
#define PMIC_NP_SCP_np_buck0_scp_END          (3)
#define PMIC_NP_SCP_np_xo_ldo_buff_scp_START  (4)
#define PMIC_NP_SCP_np_xo_ldo_buff_scp_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD0_UNION
 �ṹ˵��  : NP_RECORD0 �Ĵ����ṹ���塣��ַƫ����:0x1BE����ֵ:0x00�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_vsys_ov_d200ur        : 1;  /* bit[0]: ��ѹ�¼�(������ȥ��200us)��
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_vsys_pwroff_abs_2d    : 1;  /* bit[1]: ����Ƿѹ�¼���
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_vsys_pwroff_deb_d80mr : 1;  /* bit[2]: ȥ��Ƿѹ�¼�(������ȥ��80ms��ʱ�����)��
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_thsd_otmp140_d1mr     : 1;  /* bit[3]: ����140���¼�(������ȥ��1ms)��
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_thsd_otmp125_d1mr     : 1;  /* bit[4]: ����125���µ��¼�(������ȥ��1ms)��
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_hresetn_d90uf         : 1;  /* bit[5]: �ȸ�λ�¼��������µ�ͷ��µ��ȸ�λ����
                                                                 0�����ȸ�λ�¼���
                                                                 1�����ȸ�λ�¼��� */
        unsigned char  np_avdd_osc_vld_d20nf    : 1;  /* bit[6]: AVDD_OSC��Դ�쳣�¼����½���ȥ��20ns����
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
        unsigned char  np_19m2_dis              : 1;  /* bit[7]: 19.2Mʱ���쳣��ʧ�¼���
                                                                 0��û�з��������¼���
                                                                 1�����������¼��� */
    } reg;
} PMIC_NP_RECORD0_UNION;
#endif
#define PMIC_NP_RECORD0_np_vsys_ov_d200ur_START         (0)
#define PMIC_NP_RECORD0_np_vsys_ov_d200ur_END           (0)
#define PMIC_NP_RECORD0_np_vsys_pwroff_abs_2d_START     (1)
#define PMIC_NP_RECORD0_np_vsys_pwroff_abs_2d_END       (1)
#define PMIC_NP_RECORD0_np_vsys_pwroff_deb_d80mr_START  (2)
#define PMIC_NP_RECORD0_np_vsys_pwroff_deb_d80mr_END    (2)
#define PMIC_NP_RECORD0_np_thsd_otmp140_d1mr_START      (3)
#define PMIC_NP_RECORD0_np_thsd_otmp140_d1mr_END        (3)
#define PMIC_NP_RECORD0_np_thsd_otmp125_d1mr_START      (4)
#define PMIC_NP_RECORD0_np_thsd_otmp125_d1mr_END        (4)
#define PMIC_NP_RECORD0_np_hresetn_d90uf_START          (5)
#define PMIC_NP_RECORD0_np_hresetn_d90uf_END            (5)
#define PMIC_NP_RECORD0_np_avdd_osc_vld_d20nf_START     (6)
#define PMIC_NP_RECORD0_np_avdd_osc_vld_d20nf_END       (6)
#define PMIC_NP_RECORD0_np_19m2_dis_START               (7)
#define PMIC_NP_RECORD0_np_19m2_dis_END                 (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD1_UNION
 �ṹ˵��  : NP_RECORD1 �Ĵ����ṹ���塣��ַƫ����:0x1BF����ֵ:0x00�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pwronn_restart   : 1;  /* bit[0]: ����״̬�°�������8s����������
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_pwrhold_shutdown : 1;  /* bit[1]: pwr_hold���ʹ����ػ���
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_pwronn_shutdown  : 1;  /* bit[2]: ����״̬�°�������8s�����ػ���
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_pwrhold_pwrup    : 1;  /* bit[3]: pwr_hold����������
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_alarmon_pwrup    : 1;  /* bit[4]: �ػ�״̬�����Ӵ�������(����״̬�µ�alarm_on����¼)��
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_vbus_pwrup       : 1;  /* bit[5]: �ػ�״̬�³��������200ms���������� 
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_pwronn_pwrup     : 1;  /* bit[6]: �ػ�״̬�°�������500ms����������
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_fast_pwrup       : 1;  /* bit[7]: ���߿��ٿ�����
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
    } reg;
} PMIC_NP_RECORD1_UNION;
#endif
#define PMIC_NP_RECORD1_np_pwronn_restart_START    (0)
#define PMIC_NP_RECORD1_np_pwronn_restart_END      (0)
#define PMIC_NP_RECORD1_np_pwrhold_shutdown_START  (1)
#define PMIC_NP_RECORD1_np_pwrhold_shutdown_END    (1)
#define PMIC_NP_RECORD1_np_pwronn_shutdown_START   (2)
#define PMIC_NP_RECORD1_np_pwronn_shutdown_END     (2)
#define PMIC_NP_RECORD1_np_pwrhold_pwrup_START     (3)
#define PMIC_NP_RECORD1_np_pwrhold_pwrup_END       (3)
#define PMIC_NP_RECORD1_np_alarmon_pwrup_START     (4)
#define PMIC_NP_RECORD1_np_alarmon_pwrup_END       (4)
#define PMIC_NP_RECORD1_np_vbus_pwrup_START        (5)
#define PMIC_NP_RECORD1_np_vbus_pwrup_END          (5)
#define PMIC_NP_RECORD1_np_pwronn_pwrup_START      (6)
#define PMIC_NP_RECORD1_np_pwronn_pwrup_END        (6)
#define PMIC_NP_RECORD1_np_fast_pwrup_START        (7)
#define PMIC_NP_RECORD1_np_fast_pwrup_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD2_UNION
 �ṹ˵��  : NP_RECORD2 �Ĵ����ṹ���塣��ַƫ����:0x1C0����ֵ:0x10�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_tcxo_clk_sel_r : 1;  /* bit[0]: 32K RC�л���32K Crystal OSC ʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_tcxo_clk_sel_f : 1;  /* bit[1]: 32K Crystal OSC�л���32K RC ʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_dcxo_clk_sel_r : 1;  /* bit[2]: 32K RC �л��� 19.2MHz/586 ʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_dcxo_clk_sel_f : 1;  /* bit[3]: 19.2MHz/586 �л��� 32K RCʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_vsys_vcoin_sel : 1;  /* bit[4]: VSYS��VCION�л��źš�
                                                          0��û�з��������¼���
                                                          1�����������¼��� */
        unsigned char  np_smpl           : 1;  /* bit[5]: SMPL������¼
                                                          0��û�з���SMPL��
                                                          1������SMPL�� */
        unsigned char  np_core_io_vld_f  : 1;  /* bit[6]: core_io_vld�쳣�µ��¼���¼��VDD_IO�Ƿ����ͣ���
                                                          0��û�з��������¼���
                                                          1���з��������¼��� */
        unsigned char  np_pwrhold_1s     : 1;  /* bit[7]: SYS_RST_N���ߺ�1sʱ�̣�VBUS����λ������pwr_holdΪ�ʹ����ػ���
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
    } reg;
} PMIC_NP_RECORD2_UNION;
#endif
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_r_START  (0)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_r_END    (0)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_f_START  (1)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_f_END    (1)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_r_START  (2)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_r_END    (2)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_f_START  (3)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_f_END    (3)
#define PMIC_NP_RECORD2_np_vsys_vcoin_sel_START  (4)
#define PMIC_NP_RECORD2_np_vsys_vcoin_sel_END    (4)
#define PMIC_NP_RECORD2_np_smpl_START            (5)
#define PMIC_NP_RECORD2_np_smpl_END              (5)
#define PMIC_NP_RECORD2_np_core_io_vld_f_START   (6)
#define PMIC_NP_RECORD2_np_core_io_vld_f_END     (6)
#define PMIC_NP_RECORD2_np_pwrhold_1s_START      (7)
#define PMIC_NP_RECORD2_np_pwrhold_1s_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD3_UNION
 �ṹ˵��  : NP_RECORD3 �Ĵ����ṹ���塣��ַƫ����:0x1C1����ֵ:0x00�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pmua_short_f      : 1;  /* bit[0]  : pmua��������¼���¼�Ĵ�����
                                                               0��û�з��������¼���
                                                               1�����������¼��� */
        unsigned char  np_ldo34_short_f     : 1;  /* bit[1]  : LDO34��������¼���¼�Ĵ�����
                                                               0��û�з��������¼���
                                                               1�����������¼��� */
        unsigned char  np_vin_ldoh_shutdown : 1;  /* bit[2]  : vin_ldo�쳣�¼���¼�Ĵ�����
                                                               0��û�з��������¼���
                                                               1�����������¼���  */
        unsigned char  reserved             : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_NP_RECORD3_UNION;
#endif
#define PMIC_NP_RECORD3_np_pmua_short_f_START       (0)
#define PMIC_NP_RECORD3_np_pmua_short_f_END         (0)
#define PMIC_NP_RECORD3_np_ldo34_short_f_START      (1)
#define PMIC_NP_RECORD3_np_ldo34_short_f_END        (1)
#define PMIC_NP_RECORD3_np_vin_ldoh_shutdown_START  (2)
#define PMIC_NP_RECORD3_np_vin_ldoh_shutdown_END    (2)




/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_RTCDR0_UNION
 �ṹ˵��  : RTCDR0 �Ĵ����ṹ���塣��ַƫ����:0x1D0����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr0 : 8;  /* bit[0-7]: 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } reg;
} PMIC_RTCDR0_UNION;
#endif
#define PMIC_RTCDR0_rtcdr0_START  (0)
#define PMIC_RTCDR0_rtcdr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR1_UNION
 �ṹ˵��  : RTCDR1 �Ĵ����ṹ���塣��ַƫ����:0x1D1����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR1_UNION;
#endif
#define PMIC_RTCDR1_rtcdr1_START  (0)
#define PMIC_RTCDR1_rtcdr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR2_UNION
 �ṹ˵��  : RTCDR2 �Ĵ����ṹ���塣��ַƫ����:0x1D2����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR2_UNION;
#endif
#define PMIC_RTCDR2_rtcdr2_START  (0)
#define PMIC_RTCDR2_rtcdr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR3_UNION
 �ṹ˵��  : RTCDR3 �Ĵ����ṹ���塣��ַƫ����:0x1D3����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR3_UNION;
#endif
#define PMIC_RTCDR3_rtcdr3_START  (0)
#define PMIC_RTCDR3_rtcdr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR0_UNION
 �ṹ˵��  : RTCMR0 �Ĵ����ṹ���塣��ַƫ����:0x1D4����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr0 : 8;  /* bit[0-7]: 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ��������˳��Ҫ�������õ�λ������������λ����û��Ҫ��˳��д�����һ��Ĵ�����Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
    } reg;
} PMIC_RTCMR0_UNION;
#endif
#define PMIC_RTCMR0_rtcmr0_START  (0)
#define PMIC_RTCMR0_rtcmr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR1_UNION
 �ṹ˵��  : RTCMR1 �Ĵ����ṹ���塣��ַƫ����:0x1D5����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR1_UNION;
#endif
#define PMIC_RTCMR1_rtcmr1_START  (0)
#define PMIC_RTCMR1_rtcmr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR2_UNION
 �ṹ˵��  : RTCMR2 �Ĵ����ṹ���塣��ַƫ����:0x1D6����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR2_UNION;
#endif
#define PMIC_RTCMR2_rtcmr2_START  (0)
#define PMIC_RTCMR2_rtcmr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR3_UNION
 �ṹ˵��  : RTCMR3 �Ĵ����ṹ���塣��ַƫ����:0x1D7����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR3_UNION;
#endif
#define PMIC_RTCMR3_rtcmr3_START  (0)
#define PMIC_RTCMR3_rtcmr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR0_UNION
 �ṹ˵��  : RTCLR0 �Ĵ����ṹ���塣��ַƫ����:0x1D8����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr0 : 8;  /* bit[0-7]: 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ��������˳��Ҫ�������õ�λ������������λ����û��Ҫ��˳��д�����һ��Ĵ�����Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
    } reg;
} PMIC_RTCLR0_UNION;
#endif
#define PMIC_RTCLR0_rtcclr0_START  (0)
#define PMIC_RTCLR0_rtcclr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR1_UNION
 �ṹ˵��  : RTCLR1 �Ĵ����ṹ���塣��ַƫ����:0x1D9����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR1_UNION;
#endif
#define PMIC_RTCLR1_rtcclr1_START  (0)
#define PMIC_RTCLR1_rtcclr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR2_UNION
 �ṹ˵��  : RTCLR2 �Ĵ����ṹ���塣��ַƫ����:0x1DA����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR2_UNION;
#endif
#define PMIC_RTCLR2_rtcclr2_START  (0)
#define PMIC_RTCLR2_rtcclr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR3_UNION
 �ṹ˵��  : RTCLR3 �Ĵ����ṹ���塣��ַƫ����:0x1DB����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR3_UNION;
#endif
#define PMIC_RTCLR3_rtcclr3_START  (0)
#define PMIC_RTCLR3_rtcclr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCCTRL_UNION
 �ṹ˵��  : RTCCTRL �Ĵ����ṹ���塣��ַƫ����:0x1DC����ֵ:0x01�����:8
 �Ĵ���˵��: RTC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtccr    : 1;  /* bit[0]  : ��RTC����λ��
                                                   0����RTC��ǰֵ������ֵȫ��Ϊ0��
                                                   1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ��
                                                   ���˼Ĵ���д���Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
        unsigned char  reserved : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_RTCCTRL_UNION;
#endif
#define PMIC_RTCCTRL_rtccr_START     (0)
#define PMIC_RTCCTRL_rtccr_END       (0)


/*****************************************************************************
 �ṹ��    : PMIC_XO_THRESOLD0_UNION
 �ṹ˵��  : XO_THRESOLD0 �Ĵ����ṹ���塣��ַƫ����:0x1DD����ֵ:0xFF�����:8
 �Ĵ���˵��: XO_THRESOLD[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_low : 8;  /* bit[0-7]: У׼ƫ����ֵ���üĴ������Ƽ�ֵ0xB8��300ppm���� */
    } reg;
} PMIC_XO_THRESOLD0_UNION;
#endif
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_START  (0)
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_XO_THRESOLD1_UNION
 �ṹ˵��  : XO_THRESOLD1 �Ĵ����ṹ���塣��ַƫ����:0x1DE����ֵ:0xFF�����:8
 �Ĵ���˵��: XO_THRESOLD[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold1_high : 8;  /* bit[0-7]: У׼ƫ����ֵ���üĴ����� */
    } reg;
} PMIC_XO_THRESOLD1_UNION;
#endif
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_START  (0)
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE0_UNION
 �ṹ˵��  : CRC_VAULE0 �Ĵ����ṹ���塣��ַƫ����:0x1DF����ֵ:0xC0�����:8
 �Ĵ���˵��: CRC_VALUE[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value0 : 8;  /* bit[0-7]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[7:0]�� */
    } reg;
} PMIC_CRC_VAULE0_UNION;
#endif
#define PMIC_CRC_VAULE0_crc_value0_START  (0)
#define PMIC_CRC_VAULE0_crc_value0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE1_UNION
 �ṹ˵��  : CRC_VAULE1 �Ĵ����ṹ���塣��ַƫ����:0x1E0����ֵ:0x27�����:8
 �Ĵ���˵��: CRC_VALUE[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value1 : 8;  /* bit[0-7]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[15:8]�� */
    } reg;
} PMIC_CRC_VAULE1_UNION;
#endif
#define PMIC_CRC_VAULE1_crc_value1_START  (0)
#define PMIC_CRC_VAULE1_crc_value1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE2_UNION
 �ṹ˵��  : CRC_VAULE2 �Ĵ����ṹ���塣��ַƫ����:0x1E1����ֵ:0x09�����:8
 �Ĵ���˵��: CRC_VALUE[20:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value2 : 5;  /* bit[0-4]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[20:16]�� */
        unsigned char  reserved   : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_CRC_VAULE2_UNION;
#endif
#define PMIC_CRC_VAULE2_crc_value2_START  (0)
#define PMIC_CRC_VAULE2_crc_value2_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER0_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x1E2����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer0 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[7:0]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_START  (0)
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER1_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x1E3����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer1 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[15:8]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_START  (0)
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER2_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x1E4����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer2 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[23:16]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_START  (0)
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER3_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x1E5����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer3 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[31:24]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_START  (0)
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER0_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x1E6����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer0 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[7:0]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER1_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x1E7����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer1 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[15:8]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER2_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x1E8����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer2 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[23:16]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER3_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x1E9����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer3 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[31:24]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_END    (7)




/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_COUL_IRQ_UNION
 �ṹ˵��  : COUL_IRQ �Ĵ����ṹ���塣��ַƫ����:0x1F0����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ��жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_gate_int : 1;  /* bit[0]  : cl_out>cl_intʱ�ϱ��жϡ�
                                                      0���޴��жϣ�
                                                      1���ϱ��жϡ� */
        unsigned char  cl_out_int  : 1;  /* bit[1]  : cl_out������81%�ϱ��жϡ�
                                                      0���޴��жϣ�
                                                      1���ϱ��жϡ� */
        unsigned char  cl_in_int   : 1;  /* bit[2]  : cl_in������81%�ϱ��жϡ�
                                                      0���޴��жϣ�
                                                      1���ϱ��жϡ� */
        unsigned char  v_gate_int  : 1;  /* bit[3]  : vbat��ѹ<�趨��v_intֵ��
                                                      0���޴��жϣ�
                                                      1���ϱ��жϡ� */
        unsigned char  reserved    : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_COUL_IRQ_UNION;
#endif
#define PMIC_COUL_IRQ_cl_gate_int_START  (0)
#define PMIC_COUL_IRQ_cl_gate_int_END    (0)
#define PMIC_COUL_IRQ_cl_out_int_START   (1)
#define PMIC_COUL_IRQ_cl_out_int_END     (1)
#define PMIC_COUL_IRQ_cl_in_int_START    (2)
#define PMIC_COUL_IRQ_cl_in_int_END      (2)
#define PMIC_COUL_IRQ_v_gate_int_START   (3)
#define PMIC_COUL_IRQ_v_gate_int_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_IRQ_MASK_UNION
 �ṹ˵��  : COUL_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x1F1����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ��ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_gate_int_mk : 1;  /* bit[0]  : cl_gate_int�ж�����λ��
                                                         0�������Σ�
                                                         1��cl_int_i�ж����Ρ� */
        unsigned char  cl_out_int_mk  : 1;  /* bit[1]  : cl_out_int�ж�����λ��
                                                         0�������Σ�
                                                         1��cl_out_i�ж����Ρ� */
        unsigned char  cl_in_int_mk   : 1;  /* bit[2]  : cl_in_int�ж�����λ��
                                                         0�������Σ�
                                                         1��cl_in_i�ж����Ρ� */
        unsigned char  v_gate_int_mk  : 1;  /* bit[3]  : v_gate_int�ж�����λ��
                                                         0�������Σ�
                                                         1��vbat_int_i�ж����Ρ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_COUL_IRQ_MASK_UNION;
#endif
#define PMIC_COUL_IRQ_MASK_cl_gate_int_mk_START  (0)
#define PMIC_COUL_IRQ_MASK_cl_gate_int_mk_END    (0)
#define PMIC_COUL_IRQ_MASK_cl_out_int_mk_START   (1)
#define PMIC_COUL_IRQ_MASK_cl_out_int_mk_END     (1)
#define PMIC_COUL_IRQ_MASK_cl_in_int_mk_START    (2)
#define PMIC_COUL_IRQ_MASK_cl_in_int_mk_END      (2)
#define PMIC_COUL_IRQ_MASK_v_gate_int_mk_START   (3)
#define PMIC_COUL_IRQ_MASK_v_gate_int_mk_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT_0_UNION
 �ṹ˵��  : CURRENT_0 �Ĵ����ṹ���塣��ַƫ����:0x1F2����ֵ:0x00�����:8
 �Ĵ���˵��: ��ǰ����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_s0 : 8;  /* bit[0-7]: ��ǰ����ֵ����ֵ�Ǿ���У׼���ֵ��
                                                     ��������������Ĵ����洢�����ݣ������ȡʱ�����ȶ���8bit������������λ��ȡ������ȡ���8bit�����ζ�ȡ֮��û��ʱ��Լ�����������ж���8bit�ļĴ����Ķ�д��ʽ��Ҫ���մ˲������� */
    } reg;
} PMIC_CURRENT_0_UNION;
#endif
#define PMIC_CURRENT_0_current_s0_START  (0)
#define PMIC_CURRENT_0_current_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT_1_UNION
 �ṹ˵��  : CURRENT_1 �Ĵ����ṹ���塣��ַƫ����:0x1F3����ֵ:0x00�����:8
 �Ĵ���˵��: ��ǰ����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT_1_UNION;
#endif
#define PMIC_CURRENT_1_current_s1_START  (0)
#define PMIC_CURRENT_1_current_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT_0_UNION
 �ṹ˵��  : V_OUT_0 �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0xFF�����:8
 �Ĵ���˵��: ��ǰ��ѹ[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_s0 : 8;  /* bit[0-7]: ��ǰ��ѹֵ����ֵ�Ǿ���У׼���ֵ�� */
    } reg;
} PMIC_V_OUT_0_UNION;
#endif
#define PMIC_V_OUT_0_v_out_s0_START  (0)
#define PMIC_V_OUT_0_v_out_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT_1_UNION
 �ṹ˵��  : V_OUT_1 �Ĵ����ṹ���塣��ַƫ����:0x1F5����ֵ:0xFF�����:8
 �Ĵ���˵��: ��ǰ��ѹ[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT_1_UNION;
#endif
#define PMIC_V_OUT_1_v_out_s1_START  (0)
#define PMIC_V_OUT_1_v_out_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_CTRL_REG_UNION
 �ṹ˵��  : CLJ_CTRL_REG �Ĵ����ṹ���塣��ַƫ����:0x1F6����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_ctrl           : 3;  /* bit[0-2]: bit[2]���Ƿ�ǿ�ƽ���ECOģʽ���ơ�
                                                             0����ǿ�ƽ���ECOģʽ��
                                                             1��ǿ�ƽ���ECOģʽ��
                                                             
                                                             bit[1]�����ؼ��Ƿ����PMU����ECOģʽ���ơ�
                                                             0�����ؼƲ�����PMU����ECOģʽ��
                                                             1�����ؼƸ���PMU����ECOģʽ��
                                                             ��������bit[2] == 0 ʱ��Ч����Ҫ�����PMU��ͬʱ��Ҫ��0x12D[COUL_ECO_MASK]�Ĵ������㣩
                                                             
                                                             bit[0]������ECOģʽʱ��ʹ���ź��Ƿ�ȥ�����ơ�
                                                             0������ECOģʽʹ���źŲ�ȥ����
                                                             1������ECOģʽʹ���ź�ȥ����
                                                             ��������bit[1] ==1 ʱ��Ч��
                                                             ע��eco_ctrl�üĴ����ȸ�λ�����㡣 */
        unsigned char  reflash_value_ctrl : 1;  /* bit[3]  : ���ؼƸ������ݷ�ʽѡ��
                                                             0������״̬���������ݣ�
                                                             1����ECOģʽ�������ݡ� */
        unsigned char  eco_filter_time    : 3;  /* bit[4-6]: ���ؼ��˳�ECOģʽʹ���ź�ȥ��ʱ��ѡ��
                                                             000��50ms��
                                                             001��100ms��
                                                             010��150ms��
                                                             011��200ms��
                                                             100: 250ms��
                                                             101: 300ms��
                                                             110: 350ms��
                                                             111: 400ms��
                                                             ��������en_eco_modeȥ��ʱ����Ĭ��Ϊ000�� */
        unsigned char  calibration_ctrl   : 1;  /* bit[7]  : ���ؼ�ǿ��У׼����λ��
                                                             0����У׼��
                                                             1��ǿ�ƽ���У׼״̬�� */
    } reg;
} PMIC_CLJ_CTRL_REG_UNION;
#endif
#define PMIC_CLJ_CTRL_REG_eco_ctrl_START            (0)
#define PMIC_CLJ_CTRL_REG_eco_ctrl_END              (2)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_START  (3)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_END    (3)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_START     (4)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_END       (6)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_START    (7)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_REFALSH_TIME_UNION
 �ṹ˵��  : ECO_REFALSH_TIME �Ĵ����ṹ���塣��ַƫ����:0x1F7����ֵ:0x01�����:8
 �Ĵ���˵��: ECO_REFLASH����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_reflash_time : 8;  /* bit[0-7]: �˹���ʱ����һ����λ����110ms��ΪECO_REFLASHʱ�䣻��Ч����ֵΪ1~255������ֵ����255ʱ��Ӳ��ֱ�ӱ��͵�255��Ĭ��Ϊ1��
                                                           ������ÿ��ؼƽ���ECOģʽ��ֻ���ò�1�ģ�ͣ9�ģ��ȴ�1�ĵĳ���ģʽ��������FLASH���ڵ�ģʽ����Ӧ�ã������������֤���ǡ� */
    } reg;
} PMIC_ECO_REFALSH_TIME_UNION;
#endif
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_START  (0)
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT0_UNION
 �ṹ˵��  : CL_OUT0 �Ĵ����ṹ���塣��ַƫ����:0x1F8����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s0 : 8;  /* bit[0-7]: ��������������[31:0]��
                                                    ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_OUT0_UNION;
#endif
#define PMIC_CL_OUT0_cl_out_s0_START  (0)
#define PMIC_CL_OUT0_cl_out_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT1_UNION
 �ṹ˵��  : CL_OUT1 �Ĵ����ṹ���塣��ַƫ����:0x1F9����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT1_UNION;
#endif
#define PMIC_CL_OUT1_cl_out_s1_START  (0)
#define PMIC_CL_OUT1_cl_out_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT2_UNION
 �ṹ˵��  : CL_OUT2 �Ĵ����ṹ���塣��ַƫ����:0x1FA����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT2_UNION;
#endif
#define PMIC_CL_OUT2_cl_out_s2_START  (0)
#define PMIC_CL_OUT2_cl_out_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT3_UNION
 �ṹ˵��  : CL_OUT3 �Ĵ����ṹ���塣��ַƫ����:0x1FB����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT3_UNION;
#endif
#define PMIC_CL_OUT3_cl_out_s3_START  (0)
#define PMIC_CL_OUT3_cl_out_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN0_UNION
 �ṹ˵��  : CL_IN0 �Ĵ����ṹ���塣��ַƫ����:0x1FC����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s0 : 8;  /* bit[0-7]: �������������[31:0]��
                                                   ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_IN0_UNION;
#endif
#define PMIC_CL_IN0_cl_in_s0_START  (0)
#define PMIC_CL_IN0_cl_in_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN1_UNION
 �ṹ˵��  : CL_IN1 �Ĵ����ṹ���塣��ַƫ����:0x1FD����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN1_UNION;
#endif
#define PMIC_CL_IN1_cl_in_s1_START  (0)
#define PMIC_CL_IN1_cl_in_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN2_UNION
 �ṹ˵��  : CL_IN2 �Ĵ����ṹ���塣��ַƫ����:0x1FE����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN2_UNION;
#endif
#define PMIC_CL_IN2_cl_in_s2_START  (0)
#define PMIC_CL_IN2_cl_in_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN3_UNION
 �ṹ˵��  : CL_IN3 �Ĵ����ṹ���塣��ַƫ����:0x1FF����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN3_UNION;
#endif
#define PMIC_CL_IN3_cl_in_s3_START  (0)
#define PMIC_CL_IN3_cl_in_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER0_UNION
 �ṹ˵��  : CHG_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s0 : 8;  /* bit[0-7]: ���ʱ�������[31:0]��
                                                       ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CHG_TIMER0_UNION;
#endif
#define PMIC_CHG_TIMER0_chg_timer_s0_START  (0)
#define PMIC_CHG_TIMER0_chg_timer_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER1_UNION
 �ṹ˵��  : CHG_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x201����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER1_UNION;
#endif
#define PMIC_CHG_TIMER1_chg_timer_s1_START  (0)
#define PMIC_CHG_TIMER1_chg_timer_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER2_UNION
 �ṹ˵��  : CHG_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x202����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER2_UNION;
#endif
#define PMIC_CHG_TIMER2_chg_timer_s2_START  (0)
#define PMIC_CHG_TIMER2_chg_timer_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER3_UNION
 �ṹ˵��  : CHG_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x203����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER3_UNION;
#endif
#define PMIC_CHG_TIMER3_chg_timer_s3_START  (0)
#define PMIC_CHG_TIMER3_chg_timer_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER0_UNION
 �ṹ˵��  : LOAD_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s0 : 8;  /* bit[0-7]: �ŵ�ʱ�������[31:0]��
                                                        ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_LOAD_TIMER0_UNION;
#endif
#define PMIC_LOAD_TIMER0_load_timer_s0_START  (0)
#define PMIC_LOAD_TIMER0_load_timer_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER1_UNION
 �ṹ˵��  : LOAD_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x205����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER1_UNION;
#endif
#define PMIC_LOAD_TIMER1_load_timer_s1_START  (0)
#define PMIC_LOAD_TIMER1_load_timer_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER2_UNION
 �ṹ˵��  : LOAD_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x206����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER2_UNION;
#endif
#define PMIC_LOAD_TIMER2_load_timer_s2_START  (0)
#define PMIC_LOAD_TIMER2_load_timer_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER3_UNION
 �ṹ˵��  : LOAD_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x207����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER3_UNION;
#endif
#define PMIC_LOAD_TIMER3_load_timer_s3_START  (0)
#define PMIC_LOAD_TIMER3_load_timer_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT0_UNION
 �ṹ˵��  : CL_INT0 �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s0 : 8;  /* bit[0-7]: ���������жϱȽϼĴ���[31:0]��
                                                    ��cl_inout>cl_intʱ�ϱ��жϡ�
                                                    ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_INT0_UNION;
#endif
#define PMIC_CL_INT0_cl_int_s0_START  (0)
#define PMIC_CL_INT0_cl_int_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT1_UNION
 �ṹ˵��  : CL_INT1 �Ĵ����ṹ���塣��ַƫ����:0x209����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT1_UNION;
#endif
#define PMIC_CL_INT1_cl_int_s1_START  (0)
#define PMIC_CL_INT1_cl_int_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT2_UNION
 �ṹ˵��  : CL_INT2 �Ĵ����ṹ���塣��ַƫ����:0x20A����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT2_UNION;
#endif
#define PMIC_CL_INT2_cl_int_s2_START  (0)
#define PMIC_CL_INT2_cl_int_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT3_UNION
 �ṹ˵��  : CL_INT3 �Ĵ����ṹ���塣��ַƫ����:0x20B����ֵ:0x80�����:8
 �Ĵ���˵��: cl_int[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT3_UNION;
#endif
#define PMIC_CL_INT3_cl_int_s3_START  (0)
#define PMIC_CL_INT3_cl_int_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_INT0_UNION
 �ṹ˵��  : V_INT0 �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00�����:8
 �Ĵ���˵��: v_int[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int_s0 : 8;  /* bit[0-7]: ��ѹ�жϱȽ�ֵ�Ĵ���[15:0]��
                                                   ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_V_INT0_UNION;
#endif
#define PMIC_V_INT0_v_int_s0_START  (0)
#define PMIC_V_INT0_v_int_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_INT1_UNION
 �ṹ˵��  : V_INT1 �Ĵ����ṹ���塣��ַƫ����:0x20D����ֵ:0x00�����:8
 �Ĵ���˵��: v_int[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_INT1_UNION;
#endif
#define PMIC_V_INT1_v_int_s1_START  (0)
#define PMIC_V_INT1_v_int_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT0_UNION
 �ṹ˵��  : OFFSET_CURRENT0 �Ĵ����ṹ���塣��ַƫ����:0x20E����ֵ:0x00�����:8
 �Ĵ���˵��: offset_current[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_s0 : 8;  /* bit[0-7]: ����У׼ֵ[15:0]�� */
    } reg;
} PMIC_OFFSET_CURRENT0_UNION;
#endif
#define PMIC_OFFSET_CURRENT0_offset_current_s0_START  (0)
#define PMIC_OFFSET_CURRENT0_offset_current_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT1_UNION
 �ṹ˵��  : OFFSET_CURRENT1 �Ĵ����ṹ���塣��ַƫ����:0x20F����ֵ:0x00�����:8
 �Ĵ���˵��: offset_current[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT1_UNION;
#endif
#define PMIC_OFFSET_CURRENT1_offset_current_s1_START  (0)
#define PMIC_OFFSET_CURRENT1_offset_current_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE0_UNION
 �ṹ˵��  : OFFSET_VOLTAGE0 �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x00�����:8
 �Ĵ���˵��: offset_voltage[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_s0 : 8;  /* bit[0-7]: ��ѹУ׼ֵ[15:0]�� */
    } reg;
} PMIC_OFFSET_VOLTAGE0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE0_offset_voltage_s0_START  (0)
#define PMIC_OFFSET_VOLTAGE0_offset_voltage_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE1_UNION
 �ṹ˵��  : OFFSET_VOLTAGE1 �Ĵ����ṹ���塣��ַƫ����:0x211����ֵ:0x00�����:8
 �Ĵ���˵��: offset_voltage[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE1_offset_voltage_s1_START  (0)
#define PMIC_OFFSET_VOLTAGE1_offset_voltage_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_VOLTAGE0_UNION
 �ṹ˵��  : OCV_VOLTAGE0 �Ĵ����ṹ���塣��ַƫ����:0x212����ֵ:0x00�����:8
 �Ĵ���˵��: v_ocv_data[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data_s0 : 8;  /* bit[0-7]: ����ʱOCV��ѹ����ֵ[15:0]����ֵ��ԭʼֵ��δ����У׼�� */
    } reg;
} PMIC_OCV_VOLTAGE0_UNION;
#endif
#define PMIC_OCV_VOLTAGE0_v_ocv_data_s0_START  (0)
#define PMIC_OCV_VOLTAGE0_v_ocv_data_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_VOLTAGE1_UNION
 �ṹ˵��  : OCV_VOLTAGE1 �Ĵ����ṹ���塣��ַƫ����:0x213����ֵ:0x00�����:8
 �Ĵ���˵��: v_ocv_data[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_VOLTAGE1_UNION;
#endif
#define PMIC_OCV_VOLTAGE1_v_ocv_data_s1_START  (0)
#define PMIC_OCV_VOLTAGE1_v_ocv_data_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_CURRENT0_UNION
 �ṹ˵��  : OCV_CURRENT0 �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x00�����:8
 �Ĵ���˵��: i_ocv_data[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data_s0 : 8;  /* bit[0-7]: ����ʱOCV��������ֵ[15:0]����ֵ��ԭʼֵ��δ����У׼�� */
    } reg;
} PMIC_OCV_CURRENT0_UNION;
#endif
#define PMIC_OCV_CURRENT0_i_ocv_data_s0_START  (0)
#define PMIC_OCV_CURRENT0_i_ocv_data_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_CURRENT1_UNION
 �ṹ˵��  : OCV_CURRENT1 �Ĵ����ṹ���塣��ַƫ����:0x215����ֵ:0x00�����:8
 �Ĵ���˵��: i_ocv_data[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_CURRENT1_UNION;
#endif
#define PMIC_OCV_CURRENT1_i_ocv_data_s1_START  (0)
#define PMIC_OCV_CURRENT1_i_ocv_data_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_0_UNION
 �ṹ˵��  : ECO_OUT_CLIN_0 �Ĵ����ṹ���塣��ַƫ����:0x216����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s0 : 8;  /* bit[0-7]: �˳�ECOģʽ�������������[13:0]��ÿ���˳�ECOģʽ�Զ���¼��ǰ�������������ʱ�̱��֡� */
    } reg;
} PMIC_ECO_OUT_CLIN_0_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin_s0_START  (0)
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_1_UNION
 �ṹ˵��  : ECO_OUT_CLIN_1 �Ĵ����ṹ���塣��ַƫ����:0x217����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_1_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin_s1_START  (0)
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_2_UNION
 �ṹ˵��  : ECO_OUT_CLIN_2 �Ĵ����ṹ���塣��ַƫ����:0x218����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_2_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin_s2_START  (0)
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_3_UNION
 �ṹ˵��  : ECO_OUT_CLIN_3 �Ĵ����ṹ���塣��ַƫ����:0x219����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_3_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin_s3_START  (0)
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_0_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_0 �Ĵ����ṹ���塣��ַƫ����:0x21A����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s0 : 8;  /* bit[0-7]: �˳�ECOģʽ��������������[31:0]��ÿ���˳�ECOģʽ�Զ���¼��ǰ��������������ʱ�̱��֡� */
    } reg;
} PMIC_ECO_OUT_CLOUT_0_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout_s0_START  (0)
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_1_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_1 �Ĵ����ṹ���塣��ַƫ����:0x21B����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_1_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout_s1_START  (0)
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_2_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_2 �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_2_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout_s2_START  (0)
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout_s2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_3_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_3 �Ĵ����ṹ���塣��ַƫ����:0x21D����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_3_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout_s3_START  (0)
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout_s3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE0_UNION
 �ṹ˵��  : V_OUT0_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x21E����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre0[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre0_s0 : 8;  /* bit[0-7]: ��ǰ��ص�ѹָʾ[15:0]�����λ�������λ�� */
    } reg;
} PMIC_V_OUT0_PRE0_UNION;
#endif
#define PMIC_V_OUT0_PRE0_v_out_pre0_s0_START  (0)
#define PMIC_V_OUT0_PRE0_v_out_pre0_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE0_UNION
 �ṹ˵��  : V_OUT1_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x21F����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre0[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre0_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE0_UNION;
#endif
#define PMIC_V_OUT1_PRE0_v_out_pre0_s1_START  (0)
#define PMIC_V_OUT1_PRE0_v_out_pre0_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE1_UNION
 �ṹ˵��  : V_OUT0_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre1[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre1_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰһ��ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE1_UNION;
#endif
#define PMIC_V_OUT0_PRE1_v_out_pre1_s0_START  (0)
#define PMIC_V_OUT0_PRE1_v_out_pre1_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE1_UNION
 �ṹ˵��  : V_OUT1_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x221����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre1[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre1_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE1_UNION;
#endif
#define PMIC_V_OUT1_PRE1_v_out_pre1_s1_START  (0)
#define PMIC_V_OUT1_PRE1_v_out_pre1_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE2_UNION
 �ṹ˵��  : V_OUT0_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x222����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre2[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre2_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE2_UNION;
#endif
#define PMIC_V_OUT0_PRE2_v_out_pre2_s0_START  (0)
#define PMIC_V_OUT0_PRE2_v_out_pre2_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE2_UNION
 �ṹ˵��  : V_OUT1_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x223����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre2[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre2_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE2_UNION;
#endif
#define PMIC_V_OUT1_PRE2_v_out_pre2_s1_START  (0)
#define PMIC_V_OUT1_PRE2_v_out_pre2_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE3_UNION
 �ṹ˵��  : V_OUT0_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x224����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre3[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre3_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE3_UNION;
#endif
#define PMIC_V_OUT0_PRE3_v_out_pre3_s0_START  (0)
#define PMIC_V_OUT0_PRE3_v_out_pre3_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE3_UNION
 �ṹ˵��  : V_OUT1_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x225����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre3[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre3_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE3_UNION;
#endif
#define PMIC_V_OUT1_PRE3_v_out_pre3_s1_START  (0)
#define PMIC_V_OUT1_PRE3_v_out_pre3_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE4_UNION
 �ṹ˵��  : V_OUT0_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x226����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre4[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre4_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�Ĵ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE4_UNION;
#endif
#define PMIC_V_OUT0_PRE4_v_out_pre4_s0_START  (0)
#define PMIC_V_OUT0_PRE4_v_out_pre4_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE4_UNION
 �ṹ˵��  : V_OUT1_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x227����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre4[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre4_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE4_UNION;
#endif
#define PMIC_V_OUT1_PRE4_v_out_pre4_s1_START  (0)
#define PMIC_V_OUT1_PRE4_v_out_pre4_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE5_UNION
 �ṹ˵��  : V_OUT0_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre5[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre5_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ���ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE5_UNION;
#endif
#define PMIC_V_OUT0_PRE5_v_out_pre5_s0_START  (0)
#define PMIC_V_OUT0_PRE5_v_out_pre5_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE5_UNION
 �ṹ˵��  : V_OUT1_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x229����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre5[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre5_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE5_UNION;
#endif
#define PMIC_V_OUT1_PRE5_v_out_pre5_s1_START  (0)
#define PMIC_V_OUT1_PRE5_v_out_pre5_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE6_UNION
 �ṹ˵��  : V_OUT0_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x22A����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre6[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre6_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE6_UNION;
#endif
#define PMIC_V_OUT0_PRE6_v_out_pre6_s0_START  (0)
#define PMIC_V_OUT0_PRE6_v_out_pre6_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE6_UNION
 �ṹ˵��  : V_OUT1_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x22B����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre6[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre6_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE6_UNION;
#endif
#define PMIC_V_OUT1_PRE6_v_out_pre6_s1_START  (0)
#define PMIC_V_OUT1_PRE6_v_out_pre6_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE7_UNION
 �ṹ˵��  : V_OUT0_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre7[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre7_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�ߴ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE7_UNION;
#endif
#define PMIC_V_OUT0_PRE7_v_out_pre7_s0_START  (0)
#define PMIC_V_OUT0_PRE7_v_out_pre7_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE7_UNION
 �ṹ˵��  : V_OUT1_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x22D����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre7[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre7_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE7_UNION;
#endif
#define PMIC_V_OUT1_PRE7_v_out_pre7_s1_START  (0)
#define PMIC_V_OUT1_PRE7_v_out_pre7_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE8_UNION
 �ṹ˵��  : V_OUT0_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x22E����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre8[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre8_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�˴�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE8_UNION;
#endif
#define PMIC_V_OUT0_PRE8_v_out_pre8_s0_START  (0)
#define PMIC_V_OUT0_PRE8_v_out_pre8_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE8_UNION
 �ṹ˵��  : V_OUT1_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x22F����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre8[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre8_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE8_UNION;
#endif
#define PMIC_V_OUT1_PRE8_v_out_pre8_s1_START  (0)
#define PMIC_V_OUT1_PRE8_v_out_pre8_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE9_UNION
 �ṹ˵��  : V_OUT0_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre9[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre9_s0 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�Ŵ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE9_UNION;
#endif
#define PMIC_V_OUT0_PRE9_v_out_pre9_s0_START  (0)
#define PMIC_V_OUT0_PRE9_v_out_pre9_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE9_UNION
 �ṹ˵��  : V_OUT1_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x231����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre9[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre9_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE9_UNION;
#endif
#define PMIC_V_OUT1_PRE9_v_out_pre9_s1_START  (0)
#define PMIC_V_OUT1_PRE9_v_out_pre9_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE0_UNION
 �ṹ˵��  : CURRENT0_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x232����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre0[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre0_s0 : 8;  /* bit[0-7]: ��ǰ����ָʾ[15:0]�����λ�������λ�� */
    } reg;
} PMIC_CURRENT0_PRE0_UNION;
#endif
#define PMIC_CURRENT0_PRE0_current_pre0_s0_START  (0)
#define PMIC_CURRENT0_PRE0_current_pre0_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE0_UNION
 �ṹ˵��  : CURRENT1_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x233����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre0[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre0_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE0_UNION;
#endif
#define PMIC_CURRENT1_PRE0_current_pre0_s1_START  (0)
#define PMIC_CURRENT1_PRE0_current_pre0_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE1_UNION
 �ṹ˵��  : CURRENT0_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre1[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre1_s0 : 8;  /* bit[0-7]: ��ǰ����ǰһ��ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE1_UNION;
#endif
#define PMIC_CURRENT0_PRE1_current_pre1_s0_START  (0)
#define PMIC_CURRENT0_PRE1_current_pre1_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE1_UNION
 �ṹ˵��  : CURRENT1_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x235����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre1[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre1_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE1_UNION;
#endif
#define PMIC_CURRENT1_PRE1_current_pre1_s1_START  (0)
#define PMIC_CURRENT1_PRE1_current_pre1_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE2_UNION
 �ṹ˵��  : CURRENT0_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x236����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre2[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre2_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE2_UNION;
#endif
#define PMIC_CURRENT0_PRE2_current_pre2_s0_START  (0)
#define PMIC_CURRENT0_PRE2_current_pre2_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE2_UNION
 �ṹ˵��  : CURRENT1_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x237����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre2[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre2_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE2_UNION;
#endif
#define PMIC_CURRENT1_PRE2_current_pre2_s1_START  (0)
#define PMIC_CURRENT1_PRE2_current_pre2_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE3_UNION
 �ṹ˵��  : CURRENT0_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre3[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre3_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE3_UNION;
#endif
#define PMIC_CURRENT0_PRE3_current_pre3_s0_START  (0)
#define PMIC_CURRENT0_PRE3_current_pre3_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE3_UNION
 �ṹ˵��  : CURRENT1_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x239����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre3[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre3_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE3_UNION;
#endif
#define PMIC_CURRENT1_PRE3_current_pre3_s1_START  (0)
#define PMIC_CURRENT1_PRE3_current_pre3_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE4_UNION
 �ṹ˵��  : CURRENT0_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x23A����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre4[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre4_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ�Ĵ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE4_UNION;
#endif
#define PMIC_CURRENT0_PRE4_current_pre4_s0_START  (0)
#define PMIC_CURRENT0_PRE4_current_pre4_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE4_UNION
 �ṹ˵��  : CURRENT1_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x23B����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre4[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre4_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE4_UNION;
#endif
#define PMIC_CURRENT1_PRE4_current_pre4_s1_START  (0)
#define PMIC_CURRENT1_PRE4_current_pre4_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE5_UNION
 �ṹ˵��  : CURRENT0_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x23C����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre5[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre5_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ���ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE5_UNION;
#endif
#define PMIC_CURRENT0_PRE5_current_pre5_s0_START  (0)
#define PMIC_CURRENT0_PRE5_current_pre5_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE5_UNION
 �ṹ˵��  : CURRENT1_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x23D����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre5[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre5_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE5_UNION;
#endif
#define PMIC_CURRENT1_PRE5_current_pre5_s1_START  (0)
#define PMIC_CURRENT1_PRE5_current_pre5_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE6_UNION
 �ṹ˵��  : CURRENT0_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x23E����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre6[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre6_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE6_UNION;
#endif
#define PMIC_CURRENT0_PRE6_current_pre6_s0_START  (0)
#define PMIC_CURRENT0_PRE6_current_pre6_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE6_UNION
 �ṹ˵��  : CURRENT1_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x23F����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre6[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre6_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE6_UNION;
#endif
#define PMIC_CURRENT1_PRE6_current_pre6_s1_START  (0)
#define PMIC_CURRENT1_PRE6_current_pre6_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE7_UNION
 �ṹ˵��  : CURRENT0_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre7[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre7_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ�ߴ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE7_UNION;
#endif
#define PMIC_CURRENT0_PRE7_current_pre7_s0_START  (0)
#define PMIC_CURRENT0_PRE7_current_pre7_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE7_UNION
 �ṹ˵��  : CURRENT1_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x241����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre7[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre7_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE7_UNION;
#endif
#define PMIC_CURRENT1_PRE7_current_pre7_s1_START  (0)
#define PMIC_CURRENT1_PRE7_current_pre7_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE8_UNION
 �ṹ˵��  : CURRENT0_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x242����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre8[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre8_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ�˴�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE8_UNION;
#endif
#define PMIC_CURRENT0_PRE8_current_pre8_s0_START  (0)
#define PMIC_CURRENT0_PRE8_current_pre8_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE8_UNION
 �ṹ˵��  : CURRENT1_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x243����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre8[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre8_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE8_UNION;
#endif
#define PMIC_CURRENT1_PRE8_current_pre8_s1_START  (0)
#define PMIC_CURRENT1_PRE8_current_pre8_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE9_UNION
 �ṹ˵��  : CURRENT0_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre9[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre9_s0 : 8;  /* bit[0-7]: ��ǰ����ǰ�Ŵ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE9_UNION;
#endif
#define PMIC_CURRENT0_PRE9_current_pre9_s0_START  (0)
#define PMIC_CURRENT0_PRE9_current_pre9_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE9_UNION
 �ṹ˵��  : CURRENT1_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x245����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre9[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre9_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE9_UNION;
#endif
#define PMIC_CURRENT1_PRE9_current_pre9_s1_START  (0)
#define PMIC_CURRENT1_PRE9_current_pre9_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT_MOD_0_UNION
 �ṹ˵��  : OFFSET_CURRENT_MOD_0 �Ĵ����ṹ���塣��ַƫ����:0x246����ֵ:0x00�����:8
 �Ĵ���˵��: ����ƫ�õ���[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_s0 : 8;  /* bit[0-7]: ����ƫ�õ�����
                                                                ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_0_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_s0_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT_MOD_1_UNION
 �ṹ˵��  : OFFSET_CURRENT_MOD_1 �Ĵ����ṹ���塣��ַƫ����:0x247����ֵ:0x00�����:8
 �Ĵ���˵��: ����ƫ�õ���[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_1_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_s1_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE_MOD_0_UNION
 �ṹ˵��  : OFFSET_VOLTAGE_MOD_0 �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹƫ�õ���[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_s0 : 8;  /* bit[0-7]: ��ѹƫ�õ�����
                                                                ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_s0_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_s0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE_MOD_1_UNION
 �ṹ˵��  : OFFSET_VOLTAGE_MOD_1 �Ĵ����ṹ���塣��ַƫ����:0x249����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹƫ�õ���[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_s1_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_s1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_RESERVE0_UNION
 �ṹ˵��  : COUL_RESERVE0 �Ĵ����ṹ���塣��ַƫ����:0x24A����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�ģ�Ᵽ��0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_reserve0 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ������������������ռ�ã� */
    } reg;
} PMIC_COUL_RESERVE0_UNION;
#endif
#define PMIC_COUL_RESERVE0_coul_reserve0_START  (0)
#define PMIC_COUL_RESERVE0_coul_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED0_UNION
 �ṹ˵��  : CLJ_RESERVED0 �Ĵ����ṹ���塣��ַƫ����:0x24B����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_1 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED0_UNION;
#endif
#define PMIC_CLJ_RESERVED0_i_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED0_i_reserve_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED1_UNION
 �ṹ˵��  : CLJ_RESERVED1 �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_2 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED1_UNION;
#endif
#define PMIC_CLJ_RESERVED1_i_reserve_2_START  (0)
#define PMIC_CLJ_RESERVED1_i_reserve_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED2_UNION
 �ṹ˵��  : CLJ_RESERVED2 �Ĵ����ṹ���塣��ַƫ����:0x24D����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_reserve_1 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED2_UNION;
#endif
#define PMIC_CLJ_RESERVED2_v_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED2_v_reserve_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_PMU_SOFT_RST_UNION
 �ṹ˵��  : PMU_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x24E����ֵ:0x00�����:8
 �Ĵ���˵��: PMU��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_n : 8;  /* bit[0-7]: ���ؼ���λ��
                                                     0x11:��λ���ؼ�ģ�飻
                                                     0x1F:������ؼ�ģ�鸴λ��
                                                     д��������Ч��
                                                     
                                                     CODECģ����λ��
                                                     0x22:��λCODECģ�飻
                                                     0x2F:���CODECģ�鸴λ��
                                                     д��������Ч�� */
    } reg;
} PMIC_PMU_SOFT_RST_UNION;
#endif
#define PMIC_PMU_SOFT_RST_soft_rst_n_START  (0)
#define PMIC_PMU_SOFT_RST_soft_rst_n_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_DEBUG_UNION
 �ṹ˵��  : CLJ_DEBUG �Ĵ����ṹ���塣��ַƫ����:0x24F����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_debug_0     : 1;  /* bit[0]: ���ƿ��ؼƵ����˲���·��һ��ȡ��ʱ�ӡ�
                                                        0����Ч��
                                                        1����Ч�� */
        unsigned char  clj_debug_1     : 1;  /* bit[1]: ���ƿ��ؼƵ�ѹ�˲���·��һ��ȡ��ʱ�ӡ�
                                                        0����Ч��
                                                        1����Ч�� */
        unsigned char  clj_debug_2     : 1;  /* bit[2]: ����CK32_BT�ܽţ���ѹADCģ������� */
        unsigned char  clj_debug_3     : 1;  /* bit[3]: ����CK32_GPS�ܽţ�����ADCģ������� */
        unsigned char  cali_en_i       : 1;  /* bit[4]: ��������Ƿ�У׼ѡ��
                                                        0������������
                                                        1������ʼ�ղ����м��У׼�� */
        unsigned char  cali_en_i_force : 1;  /* bit[5]: ����У׼ѡ��
                                                        0��������ǿ��У׼��
                                                        1������ǿ��У׼��
                                                        ���Ϲ��ܾ���clj_debug[4]=0ʱ�����á� */
        unsigned char  cali_en_v_force : 1;  /* bit[6]: ��ѹУ׼ѡ��
                                                        0����ѹ��ǿ��У׼��
                                                        1����ѹǿ��У׼��
                                                        ���Ϲ��ܾ���clj_debug[7]=0ʱ�����á� */
        unsigned char  cali_en_v       : 1;  /* bit[7]: ��ѹ����Ƿ�У׼ѡ��
                                                        0������������
                                                        1����ѹ���ʼ�ղ�����У׼�� */
    } reg;
} PMIC_CLJ_DEBUG_UNION;
#endif
#define PMIC_CLJ_DEBUG_clj_debug_0_START      (0)
#define PMIC_CLJ_DEBUG_clj_debug_0_END        (0)
#define PMIC_CLJ_DEBUG_clj_debug_1_START      (1)
#define PMIC_CLJ_DEBUG_clj_debug_1_END        (1)
#define PMIC_CLJ_DEBUG_clj_debug_2_START      (2)
#define PMIC_CLJ_DEBUG_clj_debug_2_END        (2)
#define PMIC_CLJ_DEBUG_clj_debug_3_START      (3)
#define PMIC_CLJ_DEBUG_clj_debug_3_END        (3)
#define PMIC_CLJ_DEBUG_cali_en_i_START        (4)
#define PMIC_CLJ_DEBUG_cali_en_i_END          (4)
#define PMIC_CLJ_DEBUG_cali_en_i_force_START  (5)
#define PMIC_CLJ_DEBUG_cali_en_i_force_END    (5)
#define PMIC_CLJ_DEBUG_cali_en_v_force_START  (6)
#define PMIC_CLJ_DEBUG_cali_en_v_force_END    (6)
#define PMIC_CLJ_DEBUG_cali_en_v_START        (7)
#define PMIC_CLJ_DEBUG_cali_en_v_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_DEBUG_2_UNION
 �ṹ˵��  : CLJ_DEBUG_2 �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_coul_always_off : 1;  /* bit[0]  : �����Ƴ��ؿ��ƣ�
                                                                  0���������ܣ�
                                                                  1�������Ƴ��ء�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  voltage_coul_always_off : 1;  /* bit[1]  : ��ѹ�Ƴ��ؿ��ƣ�
                                                                  0���������ܣ�
                                                                  1����ѹ�Ƴ��ء�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  clj_debug_2_2           : 1;  /* bit[2]  : ���ؼ��ſ�ʱ��ʹ�ܣ�
                                                                  0�������ſ�ʹ�ܣ�
                                                                  1���ر��ſ�ʹ�ܡ�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  reserved                : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_CLJ_DEBUG_2_UNION;
#endif
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_START  (0)
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_END    (0)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_START  (1)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_END    (1)
#define PMIC_CLJ_DEBUG_2_clj_debug_2_2_START            (2)
#define PMIC_CLJ_DEBUG_2_clj_debug_2_2_END              (2)


/*****************************************************************************
 �ṹ��    : PMIC_STATE_TEST_UNION
 �ṹ˵��  : STATE_TEST �Ĵ����ṹ���塣��ַƫ����:0x251����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mstate   : 3;  /* bit[0-2]: bit[2:0]��ʾ��ѹ������ת״̬��
                                                   000��CLJ_OFF(���ؼƹر�״̬)��
                                                   001��CLJ_ON(���ؼƿ���״̬)��
                                                   010��OCV_DETE(���ؼ�ocv��ѹ����״̬)��
                                                   011��CALIBRATION(���ؼ��Զ�У׼״̬)��
                                                   100��NORMAL_FUNC(���ؼ���������״̬)��
                                                   101��ECO_REFLASH(���ؼƽ���͹���ǰһ��״̬)��
                                                   110��ECO_POWER_OFF(���ؼƽ���͹���״̬)��
                                                   111��WAITTING(���ؼ��˳��͹��ĺ�һ��״̬)���� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_STATE_TEST_UNION;
#endif
#define PMIC_STATE_TEST_mstate_START    (0)
#define PMIC_STATE_TEST_mstate_END      (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_CTRL_REGS2_UNION
 �ṹ˵��  : CLJ_CTRL_REGS2 �Ĵ����ṹ���塣��ַƫ����:0x252����ֵ:0x01�����:8
 �Ĵ���˵��: ���ؼƿ��ƼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_ctrl_onoff_reg  : 1;  /* bit[0]  : ���ؼƿ��ؿ��ƼĴ�����
                                                               0�����ؼƹرգ�
                                                               1�����ؼƿ����� */
        unsigned char  reg_data_clr         : 1;  /* bit[1]  : 10��Ĵ�������������ѹ�����ֵ�ָ���ʼֵ���ã�
                                                               0�����ָ���ʼֵ��
                                                               1���ָ���ʼֵ�� */
        unsigned char  cali_auto_time       : 3;  /* bit[2-4]: ���ؼ�Ӳ��У׼���ڿ��䣺
                                                               000��15s��
                                                               001��30s��
                                                               010��60s��
                                                               011��2min��
                                                               100��4min��
                                                               101��8min��
                                                               110��16min��
                                                               111��32min */
        unsigned char  cali_auto_onoff_ctrl : 1;  /* bit[5]  : ���ؼ�Ӳ����ʱУ׼����λ��
                                                               0����У׼��
                                                               1������У׼״̬�� */
        unsigned char  reserved             : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_CLJ_CTRL_REGS2_UNION;
#endif
#define PMIC_CLJ_CTRL_REGS2_coul_ctrl_onoff_reg_START   (0)
#define PMIC_CLJ_CTRL_REGS2_coul_ctrl_onoff_reg_END     (0)
#define PMIC_CLJ_CTRL_REGS2_reg_data_clr_START          (1)
#define PMIC_CLJ_CTRL_REGS2_reg_data_clr_END            (1)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_time_START        (2)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_time_END          (4)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_onoff_ctrl_START  (5)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_onoff_ctrl_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DEBUG_WRITE_PRO_UNION
 �ṹ˵��  : DEBUG_WRITE_PRO �Ĵ����ṹ���塣��ַƫ����:0x253����ֵ:0x56�����:8
 �Ĵ���˵��: DEBUG�Ĵ���д������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  debug_write_pro : 8;  /* bit[0-7]: CLJ_DEBUG��CLJ_DEBUG_2�Ĵ���д�������ܣ�
                                                          0x56������DEBUG�Ĵ�����
                                                          0xa9���Ᵽ��DEBUG�Ĵ�����
                                                          (����ֵ������ԭ��״̬����������) */
    } reg;
} PMIC_DEBUG_WRITE_PRO_UNION;
#endif
#define PMIC_DEBUG_WRITE_PRO_debug_write_pro_START  (0)
#define PMIC_DEBUG_WRITE_PRO_debug_write_pro_END    (7)




/****************************************************************************
                     (5/5) PMU_CODEC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_CLK_EN_CFG_UNION
 �ṹ˵��  : CLK_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ��ʹ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacl_en  : 1;  /* bit[0]  : DACLʱ��ʹ�ܣ�
                                                   0���ر�ʱ�ӣ�
                                                   1����ʱ�ӡ� */
        unsigned char  dacr_en  : 1;  /* bit[1]  : DACRʱ��ʹ�ܣ�
                                                   0���ر�ʱ�ӣ�
                                                   1����ʱ�ӡ� */
        unsigned char  adcl_en  : 1;  /* bit[2]  : ADCLʱ��ʹ�ܣ�
                                                   0���ر�ʱ�ӣ�
                                                   1����ʱ�ӡ� */
        unsigned char  adcr_en  : 1;  /* bit[3]  : ADCRʱ��ʹ�ܣ�
                                                   0���ر�ʱ�ӣ�
                                                   1����ʱ�ӡ� */
        unsigned char  sif_en   : 1;  /* bit[4]  : SIFʱ��ʹ�ܣ�
                                                   0���ر�ʱ�ӣ�
                                                   1����ʱ�ӡ� */
        unsigned char  reserved : 3;  /* bit[5-7]: reserved */
    } reg;
} PMIC_CLK_EN_CFG_UNION;
#endif
#define PMIC_CLK_EN_CFG_dacl_en_START   (0)
#define PMIC_CLK_EN_CFG_dacl_en_END     (0)
#define PMIC_CLK_EN_CFG_dacr_en_START   (1)
#define PMIC_CLK_EN_CFG_dacr_en_END     (1)
#define PMIC_CLK_EN_CFG_adcl_en_START   (2)
#define PMIC_CLK_EN_CFG_adcl_en_END     (2)
#define PMIC_CLK_EN_CFG_adcr_en_START   (3)
#define PMIC_CLK_EN_CFG_adcr_en_END     (3)
#define PMIC_CLK_EN_CFG_sif_en_START    (4)
#define PMIC_CLK_EN_CFG_sif_en_END      (4)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_EDGE_CFG_UNION
 �ṹ˵��  : CLK_EDGE_CFG �Ĵ����ṹ���塣��ַƫ����:0x261����ֵ:0x0F�����:8
 �Ĵ���˵��: ��ģ�ӿ�ʱ����ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacl_clk_edge_sel : 1;  /* bit[0]  : DACLʱ����ѡ��
                                                            0�����أ�
                                                            1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
        unsigned char  dacr_clk_edge_sel : 1;  /* bit[1]  : DACRʱ����ѡ��
                                                            0�����أ�
                                                            1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
        unsigned char  adcl_clk_edge_sel : 1;  /* bit[2]  : ADCLʱ����ѡ��
                                                            0�����أ�
                                                            1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
        unsigned char  adcr_clk_edge_sel : 1;  /* bit[3]  : ADCRʱ����ѡ��
                                                            0�����أ�
                                                            1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
        unsigned char  reserved          : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CLK_EDGE_CFG_UNION;
#endif
#define PMIC_CLK_EDGE_CFG_dacl_clk_edge_sel_START  (0)
#define PMIC_CLK_EDGE_CFG_dacl_clk_edge_sel_END    (0)
#define PMIC_CLK_EDGE_CFG_dacr_clk_edge_sel_START  (1)
#define PMIC_CLK_EDGE_CFG_dacr_clk_edge_sel_END    (1)
#define PMIC_CLK_EDGE_CFG_adcl_clk_edge_sel_START  (2)
#define PMIC_CLK_EDGE_CFG_adcl_clk_edge_sel_END    (2)
#define PMIC_CLK_EDGE_CFG_adcr_clk_edge_sel_START  (3)
#define PMIC_CLK_EDGE_CFG_adcr_clk_edge_sel_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LOOPBACK_CFG_UNION
 �ṹ˵��  : LOOPBACK_CFG �Ĵ����ṹ���塣��ַƫ����:0x262����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؿ��ơ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac_loopback     : 1;  /* bit[0]  : DACͨ�����ݻ��ؿ��ƣ�
                                                           1'b0�����������ڴ��нӿڣ�
                                                           1'b1��DACL��������������ģ��ADCL�������룬DACR��������������ģ��ADCR�������� */
        unsigned char  adc_loopback     : 1;  /* bit[1]  : ADCͨ�����ݻ��ؿ��ƣ�
                                                           1'b0��adc��������������ģ�Ⲣ�����룻
                                                           1'b1��adc��������������dac�Ĳ������ */
        unsigned char  sif_s2p_loopback : 1;  /* bit[2]  : SIF����������ݻ���ʹ�ܣ�
                                                           1��ADC����������ص�DAC��������
                                                           0�������� */
        unsigned char  dac_dem_din_sel  : 1;  /* bit[3]  : DACͨ����������ѡ��
                                                           1'b1: ѡ���4���������룻
                                                           1'b0: ѡ��ԭ�������룻 */
        unsigned char  reserved         : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_LOOPBACK_CFG_UNION;
#endif
#define PMIC_LOOPBACK_CFG_dac_loopback_START      (0)
#define PMIC_LOOPBACK_CFG_dac_loopback_END        (0)
#define PMIC_LOOPBACK_CFG_adc_loopback_START      (1)
#define PMIC_LOOPBACK_CFG_adc_loopback_END        (1)
#define PMIC_LOOPBACK_CFG_sif_s2p_loopback_START  (2)
#define PMIC_LOOPBACK_CFG_sif_s2p_loopback_END    (2)
#define PMIC_LOOPBACK_CFG_dac_dem_din_sel_START   (3)
#define PMIC_LOOPBACK_CFG_dac_dem_din_sel_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_ANA_IRQ_SIG_STAT_UNION
 �ṹ˵��  : ANA_IRQ_SIG_STAT �Ĵ����ṹ���塣��ַƫ����:0x263����ֵ:0x00�����:8
 �Ĵ���˵��: ģ���ж�ԭʼ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_mic_nor1_irq : 1;  /* bit[0]  : ����ģʽ�£�COMP_H�Ƚ����жϣ�����������½��ؾ���Ч��
                                                          1��COMP_H�Ƚ�������ߣ�DETECT��ƽ<0.85Vmicbias��Ĭ��ֵ����
                                                          0��COMP_H�Ƚ�������ͣ�DETECT��ƽ>0.85Vmicbias��Ĭ��ֵ���� */
        unsigned char  hs_mic_nor2_irq : 1;  /* bit[1]  : ����ģʽ�£�COMP_L�Ƚ����жϣ�����������½��ؾ���Ч��
                                                          1��COMP_L�Ƚ�������ߣ�DETECT��ƽ>600mV��Ĭ��ֵ����
                                                          0��COMP_L�Ƚ�������ͣ�DETECT��ƽ<600mV��Ĭ��ֵ���� */
        unsigned char  hs_mic_eco_irq  : 1;  /* bit[2]  : ECOģʽ�£�COMP_ECO�Ƚ����жϣ�����������½��ؾ���Ч��
                                                          1��COMP_ECO�Ƚ�������ߣ�ECOģʽ�°���δ���£�DETECT��ƽ>100mV��Ĭ��ֵ����
                                                          0��COMP_ECO�Ƚ�������ͣ�ECOģʽ�°������£�DETECT��ƽ<100mV��Ĭ��ֵ���� */
        unsigned char  hs_det_irq      : 1;  /* bit[3]  : �����������жϣ�����������½��ؾ���Ч��
                                                          1����������غ��Ҷ�ֵΪ��1��ʱ����ʾ�ж������룻
                                                          0������½��غ��Ҷ�ֵΪ��0��ʱ����ʾ�����γ��� */
        unsigned char  reserved        : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_ANA_IRQ_SIG_STAT_UNION;
#endif
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor1_irq_START  (0)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor1_irq_END    (0)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor2_irq_START  (1)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor2_irq_END    (1)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_eco_irq_START   (2)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_eco_irq_END     (2)
#define PMIC_ANA_IRQ_SIG_STAT_hs_det_irq_START       (3)
#define PMIC_ANA_IRQ_SIG_STAT_hs_det_irq_END         (3)


/*****************************************************************************
 �ṹ��    : PMIC_ANA_IRQM_REG0_UNION
 �ṹ˵��  : ANA_IRQM_REG0 �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x00�����:8
 �Ĵ���˵��: ANA_IRQ_REG�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ana_irq_mask : 8;  /* bit[0-7]: [7]:�����γ�����ж�����λ�� 
                                                       [6]:�����������ж�����λ��
                                                       [5]:COMP_ECO�Ƚ�������ɸߵ����ж�����λ��
                                                       [4]:COMP_ECO�Ƚ�������ɵ͵����ж�����λ��
                                                       [3]:COMP_L�Ƚ�������ɸߵ����ж�����λ��
                                                       [2]:COMP_L�Ƚ�������ɵ͵����ж�����λ��
                                                       [1]:COMP_H�Ƚ�������ɸߵ����ж�����λ��
                                                       [0]:COMP_H�Ƚ�������ɵ͵����ж�����λ��
                                                       1�������жϣ�
                                                       0����������жϡ� */
    } reg;
} PMIC_ANA_IRQM_REG0_UNION;
#endif
#define PMIC_ANA_IRQM_REG0_ana_irq_mask_START  (0)
#define PMIC_ANA_IRQM_REG0_ana_irq_mask_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ANA_IRQ_REG0_UNION
 �ṹ˵��  : ANA_IRQ_REG0 �Ĵ����ṹ���塣��ַƫ����:0x265����ֵ:0x00�����:8
 �Ĵ���˵��: ģ���жϼĴ�����0��д1�壬���ϱ��ж���Ϣ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_mic_nor1_irq_pos : 1;  /* bit[0]: COMP_H�Ƚ�������ɵ͵����жϣ����ߵ�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_mic_nor1_irq_neg : 1;  /* bit[1]: COMP_H�Ƚ�������ɸߵ����жϣ����͵�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_mic_nor2_irq_pos : 1;  /* bit[2]: COMP_L�Ƚ�������ɵ͵����жϣ����ߵ�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_mic_nor2_irq_neg : 1;  /* bit[3]: COMP_L�Ƚ�������ɸߵ����жϣ����͵�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_mic_eco_irq_pos  : 1;  /* bit[4]: COMP_ECO�Ƚ�������ɵ͵����жϣ����ߵ�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_mic_eco_irq_neg  : 1;  /* bit[5]: COMP_ECO�Ƚ�������ɸߵ����жϣ����͵�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_det_irq_pos      : 1;  /* bit[6]: �����������жϣ����ߵ�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
        unsigned char  hs_det_irq_neg      : 1;  /* bit[7]: �����γ�����жϣ����͵�ƽ��Ч��
                                                            1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
                                                            0����ѯʱ��ʾ�ж���Ч�� */
    } reg;
} PMIC_ANA_IRQ_REG0_UNION;
#endif
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_pos_START  (0)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_pos_END    (0)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_neg_START  (1)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_neg_END    (1)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_pos_START  (2)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_pos_END    (2)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_neg_START  (3)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_neg_END    (3)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_pos_START   (4)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_pos_END     (4)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_neg_START   (5)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_neg_END     (5)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_pos_START       (6)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_pos_END         (6)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_neg_START       (7)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_neg_END         (7)


/*****************************************************************************
 �ṹ��    : PMIC_DEB_CNT_HS_DET_CFG_UNION
 �ṹ˵��  : DEB_CNT_HS_DET_CFG �Ĵ����ṹ���塣��ַƫ����:0x266����ֵ:0x14�����:8
 �Ĵ���˵��: hs_det_irqȥ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  deb_cnt_hs_det_irq    : 5;  /* bit[0-4]: ȥ�������ڼ���������32kʱ�Ӽ���
                                                                ����Ϊ1ms*����ֵ��
                                                                Ĭ������Ϊ20*1ms = 20ms
                                                                ��ʱ��Χ��0~32ms */
        unsigned char  bypass_deb_hs_det_irq : 1;  /* bit[5]  : ��·hs_det_irq�ж�ȥ�������ܡ�
                                                                0��ȥ����������Ч��
                                                                1��ȥ����������Ч�� */
        unsigned char  reserved              : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_DEB_CNT_HS_DET_CFG_UNION;
#endif
#define PMIC_DEB_CNT_HS_DET_CFG_deb_cnt_hs_det_irq_START     (0)
#define PMIC_DEB_CNT_HS_DET_CFG_deb_cnt_hs_det_irq_END       (4)
#define PMIC_DEB_CNT_HS_DET_CFG_bypass_deb_hs_det_irq_START  (5)
#define PMIC_DEB_CNT_HS_DET_CFG_bypass_deb_hs_det_irq_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DEB_CNT_HS_MIC_CFG_UNION
 �ṹ˵��  : DEB_CNT_HS_MIC_CFG �Ĵ����ṹ���塣��ַƫ����:0x267����ֵ:0x0A�����:8
 �Ĵ���˵��: hs_mic_irqȥ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  deb_cnt_hs_mic_irq    : 5;  /* bit[0-4]: ȥ�������ڼ���������32kʱ�Ӽ���
                                                                ����Ϊ1ms*����ֵ��
                                                                Ĭ������Ϊ10*1ms = 10ms
                                                                ��ʱ��Χ��0~32ms */
        unsigned char  bypass_deb_hs_mic_irq : 1;  /* bit[5]  : ��·hs_mic_irq�ж�ȥ�������ܡ�
                                                                0��ȥ����������Ч��
                                                                1��ȥ����������Ч�� */
        unsigned char  reserved              : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_DEB_CNT_HS_MIC_CFG_UNION;
#endif
#define PMIC_DEB_CNT_HS_MIC_CFG_deb_cnt_hs_mic_irq_START     (0)
#define PMIC_DEB_CNT_HS_MIC_CFG_deb_cnt_hs_mic_irq_END       (4)
#define PMIC_DEB_CNT_HS_MIC_CFG_bypass_deb_hs_mic_irq_START  (5)
#define PMIC_DEB_CNT_HS_MIC_CFG_bypass_deb_hs_mic_irq_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_DIG_RES02_UNION
 �ṹ˵��  : CODEC_DIG_RES02 �Ĵ����ṹ���塣��ַƫ����:0x268����ֵ:0x00�����:8
 �Ĵ���˵��: reserved��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_DIG_RES02_UNION;
#endif


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_DIG_RES03_UNION
 �ṹ˵��  : CODEC_DIG_RES03 �Ĵ����ṹ���塣��ַƫ����:0x269����ֵ:0x00�����:8
 �Ĵ���˵��: reserved��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_DIG_RES03_UNION;
#endif


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW01_UNION
 �ṹ˵��  : CODEC_ANA_RW01 �Ĵ����ṹ���塣��ַƫ����:0x26A����ֵ:0x3F�����:8
 �Ĵ���˵��: ADCͨ·PD�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgar_pd : 1;  /* bit[0]  : LINEPGAR_PD�����ź�(LINEPGAR_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  linepgal_pd : 1;  /* bit[1]  : LINEPGAL_PD�����ź�(LINEPGAL_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  auxpga_pd   : 1;  /* bit[2]  : AUXPGA_PD�����ź�(AUXPGAR_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  mainpga_pd  : 1;  /* bit[3]  : MAINPGA_PD�����ź�(MAINPGAR_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  adcr_pd     : 1;  /* bit[4]  : ADCR PD�����ź�(ADCR_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  adcl_pd     : 1;  /* bit[5]  : ADCL PD�����ź�(ADCL_PD):
                                                      0������������
                                                      1��PD */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW01_UNION;
#endif
#define PMIC_CODEC_ANA_RW01_linepgar_pd_START  (0)
#define PMIC_CODEC_ANA_RW01_linepgar_pd_END    (0)
#define PMIC_CODEC_ANA_RW01_linepgal_pd_START  (1)
#define PMIC_CODEC_ANA_RW01_linepgal_pd_END    (1)
#define PMIC_CODEC_ANA_RW01_auxpga_pd_START    (2)
#define PMIC_CODEC_ANA_RW01_auxpga_pd_END      (2)
#define PMIC_CODEC_ANA_RW01_mainpga_pd_START   (3)
#define PMIC_CODEC_ANA_RW01_mainpga_pd_END     (3)
#define PMIC_CODEC_ANA_RW01_adcr_pd_START      (4)
#define PMIC_CODEC_ANA_RW01_adcr_pd_END        (4)
#define PMIC_CODEC_ANA_RW01_adcl_pd_START      (5)
#define PMIC_CODEC_ANA_RW01_adcl_pd_END        (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW02_UNION
 �ṹ˵��  : CODEC_ANA_RW02 �Ĵ����ṹ���塣��ַƫ����:0x26B����ֵ:0xFF�����:8
 �Ĵ���˵��: MICBIAS,MBHD�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ibias_pd     : 1;  /* bit[0]: ����оƬ��Ibias���ϵ�����ź�(IBIAS_PD)��
                                                     0������������
                                                     1��PD�� */
        unsigned char  reserved_0   : 1;  /* bit[1]: reserved */
        unsigned char  reserved_1   : 1;  /* bit[2]: reserved */
        unsigned char  reserved_2   : 1;  /* bit[3]: reserved */
        unsigned char  mbhd_buff_pd : 1;  /* bit[4]: MBHD buff�ϵ�����ź�(MBHD_BUFF_PD)��
                                                     0������������
                                                     1��PD */
        unsigned char  mbhd_comp_pd : 1;  /* bit[5]: MBHD comp�ϵ�����ź�(MBHD_COMP_PD)��
                                                     0������������
                                                     1��PD */
        unsigned char  hsmicb_pd    : 1;  /* bit[6]: ����MICBIAS�ϵ�����ź�(HSMICB_PD)��
                                                     0������������
                                                     1��PD */
        unsigned char  micb1_pd     : 1;  /* bit[7]: MICBIAS1�ϵ�����ź�(MICB1_PD)��
                                                     0������������
                                                     1��PD */
    } reg;
} PMIC_CODEC_ANA_RW02_UNION;
#endif
#define PMIC_CODEC_ANA_RW02_ibias_pd_START      (0)
#define PMIC_CODEC_ANA_RW02_ibias_pd_END        (0)
#define PMIC_CODEC_ANA_RW02_mbhd_buff_pd_START  (4)
#define PMIC_CODEC_ANA_RW02_mbhd_buff_pd_END    (4)
#define PMIC_CODEC_ANA_RW02_mbhd_comp_pd_START  (5)
#define PMIC_CODEC_ANA_RW02_mbhd_comp_pd_END    (5)
#define PMIC_CODEC_ANA_RW02_hsmicb_pd_START     (6)
#define PMIC_CODEC_ANA_RW02_hsmicb_pd_END       (6)
#define PMIC_CODEC_ANA_RW02_micb1_pd_START      (7)
#define PMIC_CODEC_ANA_RW02_micb1_pd_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW03_UNION
 �ṹ˵��  : CODEC_ANA_RW03 �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0xFF�����:8
 �Ĵ���˵��: Headphone��MIXEROUT��PD�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0    : 1;  /* bit[0]: reserved */
        unsigned char  hsr_pd        : 1;  /* bit[1]: HeadphoneR�ϵ�����ź�(HSR_PD)��
                                                      0������������
                                                      1��PD */
        unsigned char  hsl_pd        : 1;  /* bit[2]: HeadphoneL�ϵ�����ź�(HSL_PD)��
                                                      0������������
                                                      1��PD */
        unsigned char  reserved_1    : 1;  /* bit[3]: reserved */
        unsigned char  mixout_hsr_pd : 1;  /* bit[4]: MIXOUT_HSR�ϵ�����ź�(MIXOUT_HSR_PD)��
                                                      0������������
                                                      1��PD */
        unsigned char  mixout_hsl_pd : 1;  /* bit[5]: MIXOUT_HSL�ϵ�����ź�(MIXOUT_HSL_PD)��
                                                      0������������
                                                      1��PD */
        unsigned char  reserved_2    : 1;  /* bit[6]: reserved */
        unsigned char  reserved_3    : 1;  /* bit[7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW03_UNION;
#endif
#define PMIC_CODEC_ANA_RW03_hsr_pd_START         (1)
#define PMIC_CODEC_ANA_RW03_hsr_pd_END           (1)
#define PMIC_CODEC_ANA_RW03_hsl_pd_START         (2)
#define PMIC_CODEC_ANA_RW03_hsl_pd_END           (2)
#define PMIC_CODEC_ANA_RW03_mixout_hsr_pd_START  (4)
#define PMIC_CODEC_ANA_RW03_mixout_hsr_pd_END    (4)
#define PMIC_CODEC_ANA_RW03_mixout_hsl_pd_START  (5)
#define PMIC_CODEC_ANA_RW03_mixout_hsl_pd_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW04_UNION
 �ṹ˵��  : CODEC_ANA_RW04 �Ĵ����ṹ���塣��ַƫ����:0x26D����ֵ:0x00�����:8
 �Ĵ���˵��: VREF����ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vrefsel     : 2;  /* bit[0-1]: VREF ����ѡ���źţ�VREFSEL<1:0>��;
                                                      00:��Ч��
                                                      01: 100kohm ��ѹ����
                                                      10: 500kohm ��ѹ����
                                                      11: 1kohm ��ѹ���� */
        unsigned char  analog_loop : 1;  /* bit[2]  : CODECģ��ADC_DAC���ؿ����ź�(ANALOG_LOOP):
                                                      0:�����أ�
                                                      1:���أ�(ADCL_DACL,ADCR_DACR) */
        unsigned char  reserved    : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW04_UNION;
#endif
#define PMIC_CODEC_ANA_RW04_vrefsel_START      (0)
#define PMIC_CODEC_ANA_RW04_vrefsel_END        (1)
#define PMIC_CODEC_ANA_RW04_analog_loop_START  (2)
#define PMIC_CODEC_ANA_RW04_analog_loop_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW05_UNION
 �ṹ˵��  : CODEC_ANA_RW05 �Ĵ����ṹ���塣��ַƫ����:0x26E����ֵ:0x0F�����:8
 �Ĵ���˵��: LINEPGALͨ·ѡ����������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgal_mute : 1;  /* bit[0]  : LINEPGAL��ͨ·MUTE�ź�(LINEPGAL_MUTE)��
                                                        0:ͨ·����������
                                                        1��ͨ·MUTE; */
        unsigned char  linepgal_gain : 4;  /* bit[1-4]: LINEPGAL��ͨ·�����ź�(LINEPGAL_GAIN<3:0>)��
                                                        0000:-26dB��
                                                        0001:-24dB��
                                                        0010:-22dB��
                                                        0011:-20dB;
                                                        0100:-18dB;
                                                        0101:-15dB��
                                                        0110:-12dB��
                                                        0111:-9dB��
                                                        1000:-6dB��
                                                        1001:-3dB��
                                                        1010:0dB��
                                                        1011:-3dB;
                                                        1100:6dB;
                                                        1101:10dB��
                                                        1110:14dB��
                                                        1111:18dB�� */
        unsigned char  linepgal_sel  : 2;  /* bit[5-6]: LINEPGAL��ͨ·ѡ���ź�(LINEPGAL_SEL<1:0>)��
                                                        01:LINEINL��LINEINR��ɲ�����룻
                                                        10:LINEINL��VCM��ɵ������룻
                                                        other����Ч��MUTE; */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW05_UNION;
#endif
#define PMIC_CODEC_ANA_RW05_linepgal_mute_START  (0)
#define PMIC_CODEC_ANA_RW05_linepgal_mute_END    (0)
#define PMIC_CODEC_ANA_RW05_linepgal_gain_START  (1)
#define PMIC_CODEC_ANA_RW05_linepgal_gain_END    (4)
#define PMIC_CODEC_ANA_RW05_linepgal_sel_START   (5)
#define PMIC_CODEC_ANA_RW05_linepgal_sel_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW06_UNION
 �ṹ˵��  : CODEC_ANA_RW06 �Ĵ����ṹ���塣��ַƫ����:0x26F����ֵ:0x0F�����:8
 �Ĵ���˵��: LINEPGARͨ·ѡ��������ƿ����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgar_mute : 1;  /* bit[0]  : LINEPGAR��ͨ·MUTE�ź�(LINEPGAR_MUTE)��
                                                        0:ͨ·����������
                                                        1��ͨ·MUTE; */
        unsigned char  linepgar_gain : 4;  /* bit[1-4]: LINEPGAR��ͨ·�����ź�(LINEPGAR_GAIN<3:0>)��
                                                        0000:-26dB��
                                                        0001:-24dB��
                                                        0010:-22dB��
                                                        0011:-20dB;
                                                        0100:-18dB;
                                                        0101:-15dB��
                                                        0110:-12dB��
                                                        0111:-9dB��
                                                        1000:-6dB��
                                                        1001:-3dB��
                                                        1010:0dB��
                                                        1011:-3dB;
                                                        1100:6dB;
                                                        1101:10dB��
                                                        1110:14dB��
                                                        1111:18dB�� */
        unsigned char  linepgar_sel  : 2;  /* bit[5-6]: LINEPGAR��ͨ·ѡ���ź�(LINEPGAR_SEL<1:0>)��
                                                        01:LINEINR��LINEINL��ɲ�����룻
                                                        10:LINEINR��VCM��ɵ������룻
                                                        other����Ч��MUTE; */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW06_UNION;
#endif
#define PMIC_CODEC_ANA_RW06_linepgar_mute_START  (0)
#define PMIC_CODEC_ANA_RW06_linepgar_mute_END    (0)
#define PMIC_CODEC_ANA_RW06_linepgar_gain_START  (1)
#define PMIC_CODEC_ANA_RW06_linepgar_gain_END    (4)
#define PMIC_CODEC_ANA_RW06_linepgar_sel_START   (5)
#define PMIC_CODEC_ANA_RW06_linepgar_sel_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW07_UNION
 �ṹ˵��  : CODEC_ANA_RW07 �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x05�����:8
 �Ĵ���˵��: AUXPGARͨ·ѡ��������ƿ����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  auxpga_sel        : 2;  /* bit[0-1]: AUXPGA��ͨ·ѡ���ź�(AUXPGA_SEL<1:0>)��
                                                            00:PD��Ч
                                                            01:AUXMIC����
                                                            10:ѡ��VCM���룻
                                                            11����Ч��MUTE�� */
        unsigned char  auxpga_mute       : 1;  /* bit[2]  : AUXPGA��ͨ·MUTE�ź�(AUXPGA_MUTE)��
                                                            0:ͨ·����������
                                                            1��ͨ·MUTE; */
        unsigned char  auxpga_gain       : 3;  /* bit[3-5]: AUXPGA��ͨ·�����ź�(AUXPGA_GAIN<2:0>)��
                                                            000: 0dB��
                                                            001: 2dB��
                                                            010: 4dB��
                                                            011: 6dB��
                                                            100: 8dB��
                                                            101: 10dB��
                                                            110: 12dB��
                                                            111: 14dB�� */
        unsigned char  auxpga_boost      : 1;  /* bit[6]  : AUXPGA��BOOST�����ź�(AUXPGA_BOOST)��
                                                            0:�������棻
                                                            1:26dB���棻 */
        unsigned char  micpga_unlock_bps : 1;  /* bit[7]  : MICPGA�����������źţ�MICPGA_UNLOCK_BPS����
                                                            0:��������Ч��
                                                            1:��������Ч�� */
    } reg;
} PMIC_CODEC_ANA_RW07_UNION;
#endif
#define PMIC_CODEC_ANA_RW07_auxpga_sel_START         (0)
#define PMIC_CODEC_ANA_RW07_auxpga_sel_END           (1)
#define PMIC_CODEC_ANA_RW07_auxpga_mute_START        (2)
#define PMIC_CODEC_ANA_RW07_auxpga_mute_END          (2)
#define PMIC_CODEC_ANA_RW07_auxpga_gain_START        (3)
#define PMIC_CODEC_ANA_RW07_auxpga_gain_END          (5)
#define PMIC_CODEC_ANA_RW07_auxpga_boost_START       (6)
#define PMIC_CODEC_ANA_RW07_auxpga_boost_END         (6)
#define PMIC_CODEC_ANA_RW07_micpga_unlock_bps_START  (7)
#define PMIC_CODEC_ANA_RW07_micpga_unlock_bps_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW08_UNION
 �ṹ˵��  : CODEC_ANA_RW08 �Ĵ����ṹ���塣��ַƫ����:0x271����ֵ:0x01�����:8
 �Ĵ���˵��: MAINPGARͨ·ѡ��������ƿ����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mainpga_mute  : 1;  /* bit[0]  : MAINPGA��ͨ·MUTE�ź�(MAINPGA_MUTE)��
                                                        0:ͨ·����������
                                                        1��ͨ·MUTE; */
        unsigned char  mainpga_gain  : 3;  /* bit[1-3]: MAINPGA��ͨ·�����ź�(MAINPGA_GAIN<2:0>)��
                                                        000: 0dB��
                                                        001: 2dB��
                                                        010: 4dB��
                                                        011: 6dB��
                                                        100: 8dB��
                                                        101: 10dB��
                                                        110: 12dB��
                                                        111: 14dB�� */
        unsigned char  mainpga_boost : 1;  /* bit[4]  : MAINPGA��BOOST�����ź�(MAINPGA_BOOST)��
                                                        0:�������棻
                                                        1:26dB���棻 */
        unsigned char  mainpga_sel   : 2;  /* bit[5-6]: MAINPGA��ͨ·ѡ���ź�(MAINPGA_SEL<1:0>)��
                                                        01��ѡ���ֻ�MIC���룻
                                                        10:ѡ�����MIC���룻
                                                        others����Ч��MUTE�� */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW08_UNION;
#endif
#define PMIC_CODEC_ANA_RW08_mainpga_mute_START   (0)
#define PMIC_CODEC_ANA_RW08_mainpga_mute_END     (0)
#define PMIC_CODEC_ANA_RW08_mainpga_gain_START   (1)
#define PMIC_CODEC_ANA_RW08_mainpga_gain_END     (3)
#define PMIC_CODEC_ANA_RW08_mainpga_boost_START  (4)
#define PMIC_CODEC_ANA_RW08_mainpga_boost_END    (4)
#define PMIC_CODEC_ANA_RW08_mainpga_sel_START    (5)
#define PMIC_CODEC_ANA_RW08_mainpga_sel_END      (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW09_UNION
 �ṹ˵��  : CODEC_ANA_RW09 �Ĵ����ṹ���塣��ַƫ����:0x272����ֵ:0x00�����:8
 �Ĵ���˵��: ADCR_MIXINͨ·ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcr_mixin : 6;  /* bit[0-5]: ADCR_MIXIN�������ź�ͨ·ѡ������ź�(ADCR_MIXIN<5:0>):
                                                     XXXXX1:AUXPGA������źţ�
                                                     XXXX1X:MAINPGA������źţ�
                                                     XXX1XX:LINEINR������źţ�
                                                     XX1XXX:LINEINL������źţ�
                                                     X1XXXX:DACR������źţ�
                                                     1XXXXX:DACL������źţ� */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW09_UNION;
#endif
#define PMIC_CODEC_ANA_RW09_adcr_mixin_START  (0)
#define PMIC_CODEC_ANA_RW09_adcr_mixin_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW10_UNION
 �ṹ˵��  : CODEC_ANA_RW10 �Ĵ����ṹ���塣��ַƫ����:0x273����ֵ:0x00�����:8
 �Ĵ���˵��: ADCL_MIXINͨ·ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcl_mixin : 6;  /* bit[0-5]: ADCL_MIXIN�������ź�ͨ·ѡ������ź�(ADCL_MIXIN<5:0>):
                                                     XXXXX1:AUXPGA������źţ�
                                                     XXXX1X:MAINPGA������źţ�
                                                     XXX1XX:LINEINR������źţ�
                                                     XX1XXX:LINEINL������źţ�
                                                     X1XXXX:DACR������źţ�
                                                     1XXXXX:DACL������źţ� */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW10_UNION;
#endif
#define PMIC_CODEC_ANA_RW10_adcl_mixin_START  (0)
#define PMIC_CODEC_ANA_RW10_adcl_mixin_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW11_UNION
 �ṹ˵��  : CODEC_ANA_RW11 �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x12�����:8
 �Ĵ���˵��: ADCLʱ������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcl_dwa_bps     : 1;  /* bit[0]  : ADCLͨ·DWA Baypass�����ź�(ADCL_DWA_BPS):
                                                           0:��DWA��
                                                           1:Baypass DWA���ܣ� */
        unsigned char  adcl_flstn       : 2;  /* bit[1-2]: ADCL��FlashADC�Ĳο���ѹѡ���ź�(ADCL_FLSTN<1:0>):
                                                           00:�ο���ѹΪ1.05����
                                                           01:�ο���ѹΪ1����
                                                           10:�ο���ѹΪ0.95����
                                                           11:�ο���ѹΪ0.9���� */
        unsigned char  adcl_dac_bias    : 2;  /* bit[3-4]: ADCL�ķ���DAC��ƫ��ѡ���ź�(ADCL_DAC_BIAS<1:0>):
                                                           00:ƫ�õ�ѹΪ0.9����
                                                           01:ƫ�õ�ѹΪ0.95����
                                                           10:ƫ�õ�ѹΪ1����
                                                           11:ƫ�õ�ѹΪ1.1���� */
        unsigned char  adcl_clk_delay_0 : 1;  /* bit[5]  : ADCL_CLK_DELAY<0>:ADCL�ڲ�CLKʱ��(CLK_TIMING_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
        unsigned char  adcl_clk_delay_1 : 1;  /* bit[6]  : ADCL_CLK_DELAY<1>:ADCL�ڲ�CLK��ʱ(CLK_DELAY_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
        unsigned char  adcl_clk_delay_2 : 1;  /* bit[7]  : ADCL_CLK_DELAY<2>:ADCL��������ݵ�ʱ(DOUT_TIMING_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
    } reg;
} PMIC_CODEC_ANA_RW11_UNION;
#endif
#define PMIC_CODEC_ANA_RW11_adcl_dwa_bps_START      (0)
#define PMIC_CODEC_ANA_RW11_adcl_dwa_bps_END        (0)
#define PMIC_CODEC_ANA_RW11_adcl_flstn_START        (1)
#define PMIC_CODEC_ANA_RW11_adcl_flstn_END          (2)
#define PMIC_CODEC_ANA_RW11_adcl_dac_bias_START     (3)
#define PMIC_CODEC_ANA_RW11_adcl_dac_bias_END       (4)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_0_START  (5)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_0_END    (5)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_1_START  (6)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_1_END    (6)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_2_START  (7)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW12_UNION
 �ṹ˵��  : CODEC_ANA_RW12 �Ĵ����ṹ���塣��ַƫ����:0x275����ֵ:0x12�����:8
 �Ĵ���˵��: ADCRʱ������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcr_dwa_bps     : 1;  /* bit[0]  : ADCRͨ·DWA Baypass�����ź�(ADCR_DWA_BPS):
                                                           0:��DWA��
                                                           1:Baypass DWA���ܣ� */
        unsigned char  adcr_flstn       : 2;  /* bit[1-2]: ADCR��FlashADC�Ĳο���ѹѡ���ź�(ADCR_FLSTN<1:0>):
                                                           00:�ο���ѹΪ1.05����
                                                           01:�ο���ѹΪ1����
                                                           10:�ο���ѹΪ0.95����
                                                           11:�ο���ѹΪ0.9���� */
        unsigned char  adcr_dac_bias    : 2;  /* bit[3-4]: ADCR�ķ���DAC��ƫ��ѡ���ź�(ADCR_DAC_BIAS<1:0>):
                                                           00:ƫ�õ�ѹΪ0.9����
                                                           01:ƫ�õ�ѹΪ0.95����
                                                           10:ƫ�õ�ѹΪ1����
                                                           11:ƫ�õ�ѹΪ1.1���� */
        unsigned char  adcr_clk_delay_0 : 1;  /* bit[5]  : ADCR_CLK_DELAY<0>:ADCR�ڲ�CLKʱ��(CLK_TIMING_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
        unsigned char  adcr_clk_delay_1 : 1;  /* bit[6]  : ADCR_CLK_DELAY<1>:ADCR�ڲ�CLK��ʱ(CLK_DELAY_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
        unsigned char  adcr_clk_delay_2 : 1;  /* bit[7]  : 
                                                           ADCR_CLK_DELAY<2>:ADCR��������ݵ�ʱ��(DOUT_TIMING_SEL)��
                                                           0: Ĭ����ʱ
                                                           1: ������ʱ */
    } reg;
} PMIC_CODEC_ANA_RW12_UNION;
#endif
#define PMIC_CODEC_ANA_RW12_adcr_dwa_bps_START      (0)
#define PMIC_CODEC_ANA_RW12_adcr_dwa_bps_END        (0)
#define PMIC_CODEC_ANA_RW12_adcr_flstn_START        (1)
#define PMIC_CODEC_ANA_RW12_adcr_flstn_END          (2)
#define PMIC_CODEC_ANA_RW12_adcr_dac_bias_START     (3)
#define PMIC_CODEC_ANA_RW12_adcr_dac_bias_END       (4)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_0_START  (5)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_0_END    (5)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_1_START  (6)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_1_END    (6)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_2_START  (7)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW13_UNION
 �ṹ˵��  : CODEC_ANA_RW13 �Ĵ����ṹ���塣��ַƫ����:0x276����ֵ:0x12�����:8
 �Ĵ���˵��: MIXOUT_HSL��MIXOUT_HSRͨ·ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mixout_hsr : 4;  /* bit[0-3]: MIXOUT_HSR�������ź�ͨ·ѡ������ź�(MIXOUT_HSR<3:0>):
                                                     XXX1:LINEINR������źţ�
                                                     XX1X:LINEINL������źţ�
                                                     X1XX:DACR������źţ�
                                                     1XXX:DACL������źţ� */
        unsigned char  mixout_hsl : 4;  /* bit[4-7]: MIXOUT_HSL�������ź�ͨ·ѡ������ź�(MIXOUT_HSL<3:0>):
                                                     XXX1:LINEINR������źţ�
                                                     XX1X:LINEINL������źţ�
                                                     X1XX:DACR������źţ�
                                                     1XXX:DACL������źţ� */
    } reg;
} PMIC_CODEC_ANA_RW13_UNION;
#endif
#define PMIC_CODEC_ANA_RW13_mixout_hsr_START  (0)
#define PMIC_CODEC_ANA_RW13_mixout_hsr_END    (3)
#define PMIC_CODEC_ANA_RW13_mixout_hsl_START  (4)
#define PMIC_CODEC_ANA_RW13_mixout_hsl_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW14_UNION
 �ṹ˵��  : CODEC_ANA_RW14 �Ĵ����ṹ���塣��ַƫ����:0x277����ֵ:0x13�����:8
 �Ĵ���˵��: MIXOUT_EARͨ·ѡ���źš�������ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cr_mixf    : 4;  /* bit[0-3]: MIXOUT_EAR��0dB,-6dBѡ������ź�(CR_MIXF<3:0>):
                                                     XXX1:LINEINR֧·0dB��XXX0:LINEINR֧·-6dB
                                                     XX1X:LINEINL֧·0dB��XX0X:LINEINL֧·-6dB
                                                     X1XX:DACR֧·0dB��X0XX:DACR֧·-6dB
                                                     1XXX:DACL֧·0dB��0XXX:DACL֧·-6dB�� */
        unsigned char  mixout_ear : 4;  /* bit[4-7]: MIXOUT_EAR�������ź�ͨ·ѡ������ź�(MIXOUT_EAR<3:0>):
                                                     XXX1:LINEINR������źţ�
                                                     XX1X:LINEINL������źţ�
                                                     X1XX:DACR������źţ�
                                                     1XXX:DACL������źţ� */
    } reg;
} PMIC_CODEC_ANA_RW14_UNION;
#endif
#define PMIC_CODEC_ANA_RW14_cr_mixf_START     (0)
#define PMIC_CODEC_ANA_RW14_cr_mixf_END       (3)
#define PMIC_CODEC_ANA_RW14_mixout_ear_START  (4)
#define PMIC_CODEC_ANA_RW14_mixout_ear_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW15_UNION
 �ṹ˵��  : CODEC_ANA_RW15 �Ĵ����ṹ���塣��ַƫ����:0x278����ֵ:0x50�����:8
 �Ĵ���˵��: DACICELL���������źš���ChargePump����ʱ������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_dtc_3   : 2;  /* bit[0-1]: Charge Pump����ʱ������ʱ������źţ�CP_DTC_3<1:0>)��
                                                     00:10ns��Ĭ�ϣ�
                                                     01:20ns
                                                     10:30ns
                                                     11:50ns */
        unsigned char  cp_dtc_2   : 2;  /* bit[2-3]: Charge Pump����ʱ������ʱ������źţ�CP_DTC_2<1:0>)��
                                                     00:10ns��Ĭ�ϣ�
                                                     01:20ns
                                                     10:30ns
                                                     11:50ns */
        unsigned char  dacr_ictrl : 2;  /* bit[4-5]: DACR ICELLS�ĵ��������ź�(DACR_ICTRL<1:0>):
                                                     00:������Ϊ0.9����
                                                     01:����������
                                                     10:������Ϊ1.1����
                                                     11:������Ϊ1.2���� */
        unsigned char  dacl_ictrl : 2;  /* bit[6-7]: DACL ICELLS�ĵ��������ź�(DACL_ICTRL<1:0>):
                                                     00:������Ϊ0.9����
                                                     01:����������
                                                     10:������Ϊ1.1����
                                                     11:������Ϊ1.2���� */
    } reg;
} PMIC_CODEC_ANA_RW15_UNION;
#endif
#define PMIC_CODEC_ANA_RW15_cp_dtc_3_START    (0)
#define PMIC_CODEC_ANA_RW15_cp_dtc_3_END      (1)
#define PMIC_CODEC_ANA_RW15_cp_dtc_2_START    (2)
#define PMIC_CODEC_ANA_RW15_cp_dtc_2_END      (3)
#define PMIC_CODEC_ANA_RW15_dacr_ictrl_START  (4)
#define PMIC_CODEC_ANA_RW15_dacr_ictrl_END    (5)
#define PMIC_CODEC_ANA_RW15_dacl_ictrl_START  (6)
#define PMIC_CODEC_ANA_RW15_dacl_ictrl_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW16_UNION
 �ṹ˵��  : CODEC_ANA_RW16 �Ĵ����ṹ���塣��ַƫ����:0x279����ֵ:0x80�����:8
 �Ĵ���˵��: Headphonesoftʹ���źš���ChargePump�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_dr_ctrl : 2;  /* bit[0-1]: Change Pump ��ͨ������������ѡ��CP_DR_CTRL<1:0>);
                                                     00: ��С������Ĭ�ϣ�
                                                     01: ��С����
                                                     10: �ϴ�����
                                                     11:������� */
        unsigned char  classg_ref : 2;  /* bit[2-3]: CLASSGģʽ��������ȵĲο�ѡ���ź�(CLASSG_REF<1:0>):
                                                     00: VREFΪ200mV��
                                                     01: VREFΪ400mV��
                                                     10: VREFΪ300mV��
                                                     11: VREFΪ500mV�� */
        unsigned char  cp_mode    : 2;  /* bit[4-5]: Charge Pump�������ѹ��ģʽ�����ź�(CP_MODE<1:0>):
                                                     00:�̶��������1.8V�ĵ�Դ��
                                                     01:�̶��������0.9V�ĵ�Դ��
                                                     10:CLASSGģʽ�������ѹ�������źſɵ���
                                                     11:CLASSGģʽ�������ѹ�������źſɵ��� */
        unsigned char  en_cp_mode : 1;  /* bit[6]  : Headphone����ģʽ��CLASSGģʽƫ�ùܵ����źţ�EN_CP_MODE��:
                                                     0: ƫ�ùܱ�׼ģʽ��
                                                     1: ƫ�ùܵ���ģʽ�� */
        unsigned char  hp_soft_en : 1;  /* bit[7]  : Headphone softʹ�ܿ����ź�(HP_SOFT_EN):
                                                     0: ����ʹ�ܣ�
                                                     1: softʹ�ܣ� */
    } reg;
} PMIC_CODEC_ANA_RW16_UNION;
#endif
#define PMIC_CODEC_ANA_RW16_cp_dr_ctrl_START  (0)
#define PMIC_CODEC_ANA_RW16_cp_dr_ctrl_END    (1)
#define PMIC_CODEC_ANA_RW16_classg_ref_START  (2)
#define PMIC_CODEC_ANA_RW16_classg_ref_END    (3)
#define PMIC_CODEC_ANA_RW16_cp_mode_START     (4)
#define PMIC_CODEC_ANA_RW16_cp_mode_END       (5)
#define PMIC_CODEC_ANA_RW16_en_cp_mode_START  (6)
#define PMIC_CODEC_ANA_RW16_en_cp_mode_END    (6)
#define PMIC_CODEC_ANA_RW16_hp_soft_en_START  (7)
#define PMIC_CODEC_ANA_RW16_hp_soft_en_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW17_UNION
 �ṹ˵��  : CODEC_ANA_RW17 �Ĵ����ṹ���塣��ַƫ����:0x27A����ֵ:0x20�����:8
 �Ĵ���˵��: HeadphoneL��������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hsl_min_gain : 1;  /* bit[0]  : HeadphoneL��ͨ·��С����ѡ���ź�(HSL_MIN_GAIN)��
                                                       0:��С����(-26dB)��Ч��
                                                       1����С����(-26dB)��Ч; */
        unsigned char  hsl_gain     : 4;  /* bit[1-4]: HeadphoneL��ͨ·�����ź�(HSL_GAIN<3:0>)��
                                                       0000:-20dB��
                                                       0001:-18dB��
                                                       0010��-16.5dB��
                                                       0011: -15dB;
                                                       0100:-13.5dB;
                                                       0101:-12dB;
                                                       0110:-10.5dB;
                                                       0111:-9.5dB;
                                                       1000:-8.5dB;
                                                       1001:-7.5dB;
                                                       1010:-6.5dB;
                                                       1011:-5.5dB;
                                                       1100:-4.5dB;
                                                       1101:-3dB;
                                                       1110: -1.5dB;
                                                       1111:0dB; */
        unsigned char  hsl_mute     : 1;  /* bit[5]  : HeadphoneL��ͨ·MUTE�ź�(HSL_MUTE)��
                                                       0:ͨ·����������
                                                       1��ͨ·MUTE; */
        unsigned char  HS_LIT_LP_L  : 1;  /* bit[6]  : HeadphoneL��POPС��·MUTE�ź�(HS_LIT_LP_L)��
                                                       0��С��·MUTE��ʹ�� ����ʱС��·��mute��hsl_mute���ƣ�
                                                       1��С��·MUTEʹ��; */
        unsigned char  reserved     : 1;  /* bit[7]  : 
                                                       reserved */
    } reg;
} PMIC_CODEC_ANA_RW17_UNION;
#endif
#define PMIC_CODEC_ANA_RW17_hsl_min_gain_START  (0)
#define PMIC_CODEC_ANA_RW17_hsl_min_gain_END    (0)
#define PMIC_CODEC_ANA_RW17_hsl_gain_START      (1)
#define PMIC_CODEC_ANA_RW17_hsl_gain_END        (4)
#define PMIC_CODEC_ANA_RW17_hsl_mute_START      (5)
#define PMIC_CODEC_ANA_RW17_hsl_mute_END        (5)
#define PMIC_CODEC_ANA_RW17_HS_LIT_LP_L_START   (6)
#define PMIC_CODEC_ANA_RW17_HS_LIT_LP_L_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW18_UNION
 �ṹ˵��  : CODEC_ANA_RW18 �Ĵ����ṹ���塣��ַƫ����:0x27B����ֵ:0x20�����:8
 �Ĵ���˵��: HeadphonR��������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hsr_min_gain : 1;  /* bit[0]  : HeadphoneR��ͨ·��С����ѡ���ź�(HSR_MIN_GAIN)��
                                                       0:��С����(-26dB)��Ч��
                                                       1����С����(-26dB)��Ч; */
        unsigned char  hsr_gain     : 4;  /* bit[1-4]: HeadphoneR��ͨ·�����ź�(HSR_GAIN<3:0>)��
                                                       0000:-20dB��
                                                       0001:-18dB��
                                                       0010��-16.5dB��
                                                       0011: -15dB;
                                                       0100:-13.5dB;
                                                       0101:-12dB;
                                                       0110:-10.5dB;
                                                       0111:-9.5dB;
                                                       1000:-8.5dB;
                                                       1001:-7.5dB;
                                                       1010:-6.5dB;
                                                       1011:-5.5dB;
                                                       1100:-4.5dB;
                                                       1101:-3dB;
                                                       1110: -1.5dB;
                                                       1111:0dB; */
        unsigned char  hsr_mute     : 1;  /* bit[5]  : HeadphoneR��ͨ·MUTE�ź�(HSR_MUTE)��
                                                       0:ͨ·����������
                                                       1��ͨ·MUTE; */
        unsigned char  HS_LIT_LP_R  : 1;  /* bit[6]  : HeadphoneR��POPС��·MUTE�ź�(HS_LIT_LP_R)��
                                                       0��С��·MUTE��ʹ�� ����ʱС��·��mute��hsl_mute���ƣ�
                                                       1��С��·MUTEʹ��; */
        unsigned char  reserved     : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW18_UNION;
#endif
#define PMIC_CODEC_ANA_RW18_hsr_min_gain_START  (0)
#define PMIC_CODEC_ANA_RW18_hsr_min_gain_END    (0)
#define PMIC_CODEC_ANA_RW18_hsr_gain_START      (1)
#define PMIC_CODEC_ANA_RW18_hsr_gain_END        (4)
#define PMIC_CODEC_ANA_RW18_hsr_mute_START      (5)
#define PMIC_CODEC_ANA_RW18_hsr_mute_END        (5)
#define PMIC_CODEC_ANA_RW18_HS_LIT_LP_R_START   (6)
#define PMIC_CODEC_ANA_RW18_HS_LIT_LP_R_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW19_UNION
 �ṹ˵��  : CODEC_ANA_RW19 �Ĵ����ṹ���塣��ַƫ����:0x27C����ֵ:0x21�����:8
 �Ĵ���˵��: Earphone��������źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ear_cm_ctrl : 1;  /* bit[0]  : EAR�Ĺ�ģ�����ź�(EAR_CM_CTRL):
                                                      0:�������500ŷķ���赽VCM��
                                                      1:�������30Kŷķ���赽VCM�� */
        unsigned char  ear_gain    : 4;  /* bit[1-4]: EAR��ͨ·�����ź�(EAR_GAIN<5:0>)��
                                                      0000:-20dB��
                                                      0001:-18dB��
                                                      0010��-16dB��
                                                      0011: -14dB;
                                                      0100:-12dB;
                                                      0101:-10dB;
                                                      0110:-8dB;
                                                      0111:-6dB;
                                                      1000:-4dB;
                                                      1001:-2dB;
                                                      1010:-0dB;
                                                      1011:2dB;
                                                      1100:4dB;
                                                      1101:5dB;
                                                      1110:6dB;
                                                      1111:7dB�� */
        unsigned char  ear_mute    : 1;  /* bit[5]  : EAR��ͨ·MUTE�ź�(EAR_MUTE)��
                                                      0:ͨ·����������
                                                      1��ͨ·MUTE; */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW19_UNION;
#endif
#define PMIC_CODEC_ANA_RW19_ear_cm_ctrl_START  (0)
#define PMIC_CODEC_ANA_RW19_ear_cm_ctrl_END    (0)
#define PMIC_CODEC_ANA_RW19_ear_gain_START     (1)
#define PMIC_CODEC_ANA_RW19_ear_gain_END       (4)
#define PMIC_CODEC_ANA_RW19_ear_mute_START     (5)
#define PMIC_CODEC_ANA_RW19_ear_mute_END       (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW20_UNION
 �ṹ˵��  : CODEC_ANA_RW20 �Ĵ����ṹ���塣��ַƫ����:0x27D����ֵ:0x40�����:8
 �Ĵ���˵��: POP����ʱ�����źš���ramp������·�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pop_ramp_ct_2_0 : 3;  /* bit[0-2]: ramp������·,����clkѡ��(POP_RAMP_CT<2:0>��
                                                          000��48k
                                                          001��48k/2
                                                          010��48k/4
                                                          011��48k/8
                                                          1*0��48k/16
                                                          1*1��48k/32 */
        unsigned char  pop_ramp_ct_3   : 1;  /* bit[3]  : ramp������·,�������(POP_RAMP_CT<3>)��
                                                          0��normal��������ʹ�ã�
                                                          1��mormal*1.5 */
        unsigned char  pop_ramp_ct_4   : 1;  /* bit[4]  : ramp������·,capѡ��(POP_RAMP_CT<4>)��
                                                          0��normal��������ʹ�ã�
                                                          1��mormal*1.5 */
        unsigned char  clk_dl          : 3;  /* bit[5-7]: POP���ϵ���ʱ����(CLK_DL)��(clk_sel=0��������Ϊclk_sel=1)
                                                          
                                                          000��7.98m (15.96m )
                                                          001��13.34m (26.68m)
                                                          010��18.68m (37.36m)
                                                          011��23.98m (47.96m)
                                                          100��29.28m (58.56m)
                                                          101��34.58m (69.16m)
                                                          110��39.88m (79.96m)
                                                          111��45.18m (90.36m) */
    } reg;
} PMIC_CODEC_ANA_RW20_UNION;
#endif
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_2_0_START  (0)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_2_0_END    (2)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_3_START    (3)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_3_END      (3)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_4_START    (4)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_4_END      (4)
#define PMIC_CODEC_ANA_RW20_clk_dl_START           (5)
#define PMIC_CODEC_ANA_RW20_clk_dl_END             (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW21_UNION
 �ṹ˵��  : CODEC_ANA_RW21 �Ĵ����ṹ���塣��ַƫ����:0x27E����ֵ:0x10�����:8
 �Ĵ���˵��: ��POP��·�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rst_n_r        : 1;  /* bit[0]  : RST HP��ͨ· POP������ģ��(RST_N_R)��
                                                         0��RST ��Ч
                                                         1��Normal�� */
        unsigned char  rst_n_l        : 1;  /* bit[1]  : RST HP��ͨ· POP������ģ��(RST_N_L)��
                                                         0��RST ��Ч
                                                         1��Normal�� */
        unsigned char  pop_dis        : 1;  /* bit[2]  : POP������ģ��byassѡ��(POP_DIS)��
                                                         0��enable POP�����Ƶ�·��
                                                         1��bypass POP�����Ƶ�·�� */
        unsigned char  clk_sel        : 1;  /* bit[3]  : POP����ʱ���Ƶ�·,clkѡ��(CLK_SEL)������1E7<7:5>���ʹ�ã�
                                                         0:188Hz��
                                                         1:94Hz�� */
        unsigned char  pdd_en         : 1;  /* bit[4]  : HP PD�ź�delay ����(PDD_EN)��
                                                         0��PD�ź�ֱ�������HPģ�飻
                                                         1��PD�źž���delay�����HPģ�飻������ģʽ�� */
        unsigned char  pop_new_bypass : 1;  /* bit[5]  : ��POP�����������BYPASS�źţ�
                                                         0���·���ʹ�ܣ�
                                                         1���·�����ʹ�ܣ� */
        unsigned char  reserved       : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW21_UNION;
#endif
#define PMIC_CODEC_ANA_RW21_rst_n_r_START         (0)
#define PMIC_CODEC_ANA_RW21_rst_n_r_END           (0)
#define PMIC_CODEC_ANA_RW21_rst_n_l_START         (1)
#define PMIC_CODEC_ANA_RW21_rst_n_l_END           (1)
#define PMIC_CODEC_ANA_RW21_pop_dis_START         (2)
#define PMIC_CODEC_ANA_RW21_pop_dis_END           (2)
#define PMIC_CODEC_ANA_RW21_clk_sel_START         (3)
#define PMIC_CODEC_ANA_RW21_clk_sel_END           (3)
#define PMIC_CODEC_ANA_RW21_pdd_en_START          (4)
#define PMIC_CODEC_ANA_RW21_pdd_en_END            (4)
#define PMIC_CODEC_ANA_RW21_pop_new_bypass_START  (5)
#define PMIC_CODEC_ANA_RW21_pop_new_bypass_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW22_UNION
 �ṹ˵��  : CODEC_ANA_RW22 �Ĵ����ṹ���塣��ַƫ����:0x27F����ֵ:0x00�����:8
 �Ĵ���˵��: HSMICBIAS��MICBIAS1���ƫ�õ�ѹ�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  micb1_adj  : 3;  /* bit[0-2]: MICBIAS1���ƫ�õ�ѹ�����ź�(MICB1_ADJ<2:0>):
                                                     000: 2.1V��
                                                     001: 2.2V��
                                                     010: 2.3V��
                                                     011: 2.4V��
                                                     100: 2.5V��
                                                     101: 2.6V��
                                                     110: 2.7V��
                                                     111: 2.8V�� */
        unsigned char  hsmicb_adj : 3;  /* bit[3-5]: HSMICBIAS���ƫ�õ�ѹ�����ź�(HSMICB_ADJ<2:0>):
                                                     000: 2.1V��
                                                     001: 2.2V��
                                                     010: 2.3V��
                                                     011: 2.4V��
                                                     100: 2.5V��
                                                     101: 2.6V��
                                                     110: 2.7V��
                                                     111: 2.8V�� */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW22_UNION;
#endif
#define PMIC_CODEC_ANA_RW22_micb1_adj_START   (0)
#define PMIC_CODEC_ANA_RW22_micb1_adj_END     (2)
#define PMIC_CODEC_ANA_RW22_hsmicb_adj_START  (3)
#define PMIC_CODEC_ANA_RW22_hsmicb_adj_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW23_UNION
 �ṹ˵��  : CODEC_ANA_RW23 �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x08�����:8
 �Ĵ���˵��: HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1�ŵ�ʹ���źš���MBHDʹ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mbhd_eco_en  : 1;  /* bit[0]  : ECOģʽ�£�MBHDʹ���ź�(MBHD_ECO_EN):
                                                       0:��ʹ�ܣ�
                                                       1:ʹ�ܣ� */
        unsigned char  micb1_dschg  : 1;  /* bit[1]  : MICBIAS1�ŵ�ʹ���ź�(MICB1_DSCHG):
                                                       0:��ʹ�ܣ�
                                                       1:ʹ�ܣ� */
        unsigned char  hsmicb_dschg : 1;  /* bit[2]  : HSMICBIAS�ŵ�ʹ���ź�(HSMICB_DSCHG):
                                                       0:��ʹ�ܣ�
                                                       1:ʹ�ܣ� */
        unsigned char  hsd_ctrl_0   : 1;  /* bit[3]  : HSD EN ����(HSD_CTRL<0>)��
                                                       0: HS ģ�鲻ʹ�ܣ�
                                                       1��HS ģ��ʹ�ܣ�������ģʽ�� */
        unsigned char  hsd_ctrl_1   : 1;  /* bit[4]  : HSD INV ����(HSD_CTRL<1>)��
                                                       0: HS ������򣻣�����ģʽ��
                                                       1��HS ��������� */
        unsigned char  hsd_ctrl_2   : 1;  /* bit[5]  : HSD POLLDOWN ���ƣ�HSD_CTRL<2>)��
                                                       0: Headset ģ������������������ģʽ��
                                                       1��HSD ���������� */
        unsigned char  reserved     : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW23_UNION;
#endif
#define PMIC_CODEC_ANA_RW23_mbhd_eco_en_START   (0)
#define PMIC_CODEC_ANA_RW23_mbhd_eco_en_END     (0)
#define PMIC_CODEC_ANA_RW23_micb1_dschg_START   (1)
#define PMIC_CODEC_ANA_RW23_micb1_dschg_END     (1)
#define PMIC_CODEC_ANA_RW23_hsmicb_dschg_START  (2)
#define PMIC_CODEC_ANA_RW23_hsmicb_dschg_END    (2)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_0_START    (3)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_0_END      (3)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_1_START    (4)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_1_END      (4)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_2_START    (5)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_2_END      (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW24_UNION
 �ṹ˵��  : CODEC_ANA_RW24 �Ĵ����ṹ���塣��ַƫ����:0x281����ֵ:0x84�����:8
 �Ĵ���˵��: MBHD_VREF_CTRL[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mbhd_vref_ctrl_1_0 : 2;  /* bit[0-1]: Normalģʽ�£�COMPL�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<1:0>��
                                                             00: 600mV
                                                             01: 700mV
                                                             10: 800mV
                                                             11: 900mV */
        unsigned char  mbhd_vref_ctrl_3_2 : 2;  /* bit[2-3]: Normalģʽ�£�COMPH�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<3:2>)��
                                                             00:80%*Vmicbias;
                                                             01:85%*Vmicbias;
                                                             10:90%Vmicbias;
                                                             11:95%*Vmicbias */
        unsigned char  mbhd_vref_ctrl_6_4 : 3;  /* bit[4-6]: ECOģʽ�£�ECO_COMP�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<6:4>)��
                                                             000��100mV
                                                             001��125mV
                                                             010: 150mV
                                                             011: 175mV
                                                             100: 200mV
                                                             101: 225mV
                                                             110: 250mV
                                                             111��275mV */
        unsigned char  mbhd_vref_pd       : 1;  /* bit[7]  : �������ģ��Ƚ�����ѹ����PD�ź�(mbhd_vref_pd)��
                                                             0��VREF���Ƚ�������������
                                                             1��VREF���Ƚ���PD�������޶�����λ״̬�£�����PD=1�� */
    } reg;
} PMIC_CODEC_ANA_RW24_UNION;
#endif
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_1_0_START  (0)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_1_0_END    (1)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_3_2_START  (2)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_3_2_END    (3)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_6_4_START  (4)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_6_4_END    (6)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_pd_START        (7)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_pd_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW25_UNION
 �ṹ˵��  : CODEC_ANA_RW25 �Ĵ����ṹ���塣��ַƫ����:0x282����ֵ:0x30�����:8
 �Ĵ���˵��: CP_CLK_CTRL[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_det_sel    : 2;  /* bit[0-1]: ChargePump�����Դ���л���ʱ�����ź�(CP_DET_SEL<1:0>):
                                                        00: 375Hz��
                                                        01: 187.5Hz��
                                                        10: 94Hz��
                                                        11: 47Hz�� */
        unsigned char  cp_det_clk_pd : 1;  /* bit[2]  : ChargePump�����Դ���л���ʱ�����ź�PD��CP_DET_CLK_PD��:
                                                        0���������ʱ�ӣ�
                                                        1��PD */
        unsigned char  cp_clk_pd     : 1;  /* bit[3]  : ChargePump����ʱ�ӿ����źţ�CP_CLK_PD��:
                                                        0���������ʱ�ӣ�
                                                        1��PD */
        unsigned char  cp_sel        : 3;  /* bit[4-6]: ChargePump����Ƶ��ѡ���ź�(CP_SEL<2:0>):
                                                        000: 6.144MHz��
                                                        001: 3.072MHz��
                                                        010: 1.536MHz��
                                                        011: 768KHz��
                                                        100: 384KHz��
                                                        101: 192KHz��
                                                        110: 96KHz��
                                                        111: 48KHz�� */
        unsigned char  hs_sys_clk_pd : 1;  /* bit[7]  : Headphone ϵͳʱ��PD�źţ�HS_SYS_CLK_PD��
                                                        0���������ʱ�ӣ�
                                                        1��PD */
    } reg;
} PMIC_CODEC_ANA_RW25_UNION;
#endif
#define PMIC_CODEC_ANA_RW25_cp_det_sel_START     (0)
#define PMIC_CODEC_ANA_RW25_cp_det_sel_END       (1)
#define PMIC_CODEC_ANA_RW25_cp_det_clk_pd_START  (2)
#define PMIC_CODEC_ANA_RW25_cp_det_clk_pd_END    (2)
#define PMIC_CODEC_ANA_RW25_cp_clk_pd_START      (3)
#define PMIC_CODEC_ANA_RW25_cp_clk_pd_END        (3)
#define PMIC_CODEC_ANA_RW25_cp_sel_START         (4)
#define PMIC_CODEC_ANA_RW25_cp_sel_END           (6)
#define PMIC_CODEC_ANA_RW25_hs_sys_clk_pd_START  (7)
#define PMIC_CODEC_ANA_RW25_hs_sys_clk_pd_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW26_UNION
 �ṹ˵��  : CODEC_ANA_RW26 �Ĵ����ṹ���塣��ַƫ����:0x283����ֵ:0x09�����:8
 �Ĵ���˵��: ADC��DACʱ����ѡ���źš���ADC��DACchopperʱ��ѡ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac_chop_clk_sel   : 2;  /* bit[0-1]: DAC��chopperʱ��ѡ���ź�(DAC_CHOP_CLK_SEL<1:0>):
                                                             00: 3MHz��
                                                             01: 1.5MHz��
                                                             10: 750KHz��
                                                             11: 375KHz�� */
        unsigned char  adc_chop_clk_sel   : 2;  /* bit[2-3]: ADC��chopperʱ��ѡ���ź�(ADC_CHOP_CLK_SEL<1:0>):
                                                             00: 384KHz��
                                                             01: 192KHz��
                                                             10: 96KHz��
                                                             11: 48KHz�� */
        unsigned char  dac_clk_sys_edge_0 : 1;  /* bit[4]  : DACʱ����λѡ���ź�(DAC_CLK_SYS_EDG_0):
                                                             0:DACʱ��ѡ�����Ƶ��ͬ��ʱ��
                                                             1:DACʱ��ѡ�����Ƶ����ʱ�� */
        unsigned char  dac_clk_sys_edge_1 : 1;  /* bit[5]  : DACʱ����ѡ���ź�(DAC_CLK_SYS_EDG_1):
                                                             0:DACʱ����ͬ����12.288MHzʱ���ط��أ�
                                                             1:DACʱ����ͬ����12.288MHzʱ����ͬ�أ� */
        unsigned char  adc_clk_sys_edge_0 : 1;  /* bit[6]  : ADCʱ����λѡ���ź�(ADC_CLK_SYS_EDG_0):
                                                             0:ADCʱ��ѡ�����Ƶ��ͬ��ʱ��
                                                             1:ADCʱ��ѡ�����Ƶ����ʱ�� */
        unsigned char  adc_clk_sys_edge_1 : 1;  /* bit[7]  : ADCʱ����ѡ���ź�(ADC_CLK_SYS_EDG_1):
                                                             0:ADCʱ����ͬ����12.288MHzʱ���ط��أ�
                                                             1:ADCʱ����ͬ����12.288MHzʱ����ͬ�أ� */
    } reg;
} PMIC_CODEC_ANA_RW26_UNION;
#endif
#define PMIC_CODEC_ANA_RW26_dac_chop_clk_sel_START    (0)
#define PMIC_CODEC_ANA_RW26_dac_chop_clk_sel_END      (1)
#define PMIC_CODEC_ANA_RW26_adc_chop_clk_sel_START    (2)
#define PMIC_CODEC_ANA_RW26_adc_chop_clk_sel_END      (3)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_0_START  (4)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_0_END    (4)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_1_START  (5)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_1_END    (5)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_0_START  (6)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_0_END    (6)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_1_START  (7)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW27_UNION
 �ṹ˵��  : CODEC_ANA_RW27 �Ĵ����ṹ���塣��ַƫ����:0x284����ֵ:0x00�����:8
 �Ĵ���˵��: RX��ADC_SDM,LINEIN,MICPGA,CTCM��chopperbaypass�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ctcm_chop_bps    : 1;  /* bit[0]  : CTCM Chopper Baypass�����ź�(CTCM_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  micpga_chop_bps  : 1;  /* bit[1]  : MICPGA Chopper Baypass�����ź�(MICPGA_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  linein_chop_bps  : 1;  /* bit[2]  : LINEIN Chopper Baypass�����ź�(LINEIN_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  adc_sdm_chop_bps : 1;  /* bit[3]  : ADC_SDM Chopper Baypass�����ź�(ADC_SDM_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  rx_chop_bps      : 1;  /* bit[4]  : RX Chopper Baypass�����ź�(RX_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  reserved         : 3;  /* bit[5-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW27_UNION;
#endif
#define PMIC_CODEC_ANA_RW27_ctcm_chop_bps_START     (0)
#define PMIC_CODEC_ANA_RW27_ctcm_chop_bps_END       (0)
#define PMIC_CODEC_ANA_RW27_micpga_chop_bps_START   (1)
#define PMIC_CODEC_ANA_RW27_micpga_chop_bps_END     (1)
#define PMIC_CODEC_ANA_RW27_linein_chop_bps_START   (2)
#define PMIC_CODEC_ANA_RW27_linein_chop_bps_END     (2)
#define PMIC_CODEC_ANA_RW27_adc_sdm_chop_bps_START  (3)
#define PMIC_CODEC_ANA_RW27_adc_sdm_chop_bps_END    (3)
#define PMIC_CODEC_ANA_RW27_rx_chop_bps_START       (4)
#define PMIC_CODEC_ANA_RW27_rx_chop_bps_END         (4)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW28_UNION
 �ṹ˵��  : CODEC_ANA_RW28 �Ĵ����ṹ���塣��ַƫ����:0x285����ֵ:0x00�����:8
 �Ĵ���˵��: TX��DAC��MIXER_EAR,MIXER_HP��chopperbaypass�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_chop_bps      : 1;  /* bit[0]  : MIXER FOR Headphone Chopper Baypass�����ź�(HS_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  ear_cld_chop_bps : 1;  /* bit[1]  : MIXER FOR Earphone and Classd Chopper Baypass�����ź�(EAR_CLD_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  dac_chop_bps     : 1;  /* bit[2]  : DAC Chopper Baypass�����ź�(DAC_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  tx_chop_bps      : 1;  /* bit[3]  : TX Chopper Baypass�����ź�(TX_CHOP_BPS):
                                                           0:��Chopper���ܣ�
                                                           1:Baypass Chopper���ܣ� */
        unsigned char  reserved         : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW28_UNION;
#endif
#define PMIC_CODEC_ANA_RW28_hs_chop_bps_START       (0)
#define PMIC_CODEC_ANA_RW28_hs_chop_bps_END         (0)
#define PMIC_CODEC_ANA_RW28_ear_cld_chop_bps_START  (1)
#define PMIC_CODEC_ANA_RW28_ear_cld_chop_bps_END    (1)
#define PMIC_CODEC_ANA_RW28_dac_chop_bps_START      (2)
#define PMIC_CODEC_ANA_RW28_dac_chop_bps_END        (2)
#define PMIC_CODEC_ANA_RW28_tx_chop_bps_START       (3)
#define PMIC_CODEC_ANA_RW28_tx_chop_bps_END         (3)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW29_UNION
 �ṹ˵��  : CODEC_ANA_RW29 �Ĵ����ṹ���塣��ַƫ����:0x286����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ1��HeadphoneMIXER_HP���������źš���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_mixer_hp : 3;  /* bit[0-2]: MIXER_HP�ĵ��������ź�:
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  ib05_hp       : 3;  /* bit[3-5]: Headphone_amp�ĵ��������ź�:
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW29_UNION;
#endif
#define PMIC_CODEC_ANA_RW29_ib05_mixer_hp_START  (0)
#define PMIC_CODEC_ANA_RW29_ib05_mixer_hp_END    (2)
#define PMIC_CODEC_ANA_RW29_ib05_hp_START        (3)
#define PMIC_CODEC_ANA_RW29_ib05_hp_END          (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW30_UNION
 �ṹ˵��  : CODEC_ANA_RW30 �Ĵ����ṹ���塣��ַƫ����:0x287����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ2��DAC��ADC_OPA1���������źš���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_adc_opa1 : 3;  /* bit[0-2]: IB05_ADC_OPA1�ĵ��������ź�(IB05_ADC_OPA1):
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  ib05_dac      : 3;  /* bit[3-5]: DAC�ĵ��������ź�(IB05_DAC):
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW30_UNION;
#endif
#define PMIC_CODEC_ANA_RW30_ib05_adc_opa1_START  (0)
#define PMIC_CODEC_ANA_RW30_ib05_adc_opa1_END    (2)
#define PMIC_CODEC_ANA_RW30_ib05_dac_START       (3)
#define PMIC_CODEC_ANA_RW30_ib05_dac_END         (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW31_UNION
 �ṹ˵��  : CODEC_ANA_RW31 �Ĵ����ṹ���塣��ַƫ����:0x288����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ3��ADC_OPA2��ADC_COMP���������źš���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_adc_comp : 3;  /* bit[0-2]: IB05_ADC_COMP�ĵ��������ź�(IB05_ADC_COMP):
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  ib05_adc_opa2 : 3;  /* bit[3-5]: IB05_ADC_OPA2�ĵ��������ź�(IB05_ADC_OPA2):
                                                        000: 2.5uA��
                                                        001: 3uA��
                                                        010: 3.5uA��
                                                        011: 4uA��
                                                        100: 4.5uA��
                                                        101: 5uA��
                                                        110: 7uA��
                                                        111: 9uA�� */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW31_UNION;
#endif
#define PMIC_CODEC_ANA_RW31_ib05_adc_comp_START  (0)
#define PMIC_CODEC_ANA_RW31_ib05_adc_comp_END    (2)
#define PMIC_CODEC_ANA_RW31_ib05_adc_opa2_START  (3)
#define PMIC_CODEC_ANA_RW31_ib05_adc_opa2_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW32_UNION
 �ṹ˵��  : CODEC_ANA_RW32 �Ĵ����ṹ���塣��ַƫ����:0x289����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ4��LINEIN��MICBIAS���������źš���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_micbias    : 3;  /* bit[0-2]: IB05_MICBIAS�ĵ��������ź�(IB05_MICBIAS):
                                                          000: 2.5uA��
                                                          001: 3uA��
                                                          010: 3.5uA��
                                                          011: 4uA��
                                                          100: 4.5uA��
                                                          101: 5uA��
                                                          110: 7uA��
                                                          111: 9uA�� */
        unsigned char  ib05_adc_linein : 3;  /* bit[3-5]: IB05_ADC_LINEIN�ĵ��������ź�(IB05_ADC_LINEIN):
                                                          000: 2.5uA��
                                                          001: 3uA��
                                                          010: 3.5uA��
                                                          011: 4uA��
                                                          100: 4.5uA��
                                                          101: 5uA��
                                                          110: 7uA��
                                                          111: 9uA�� */
        unsigned char  reserved        : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW32_UNION;
#endif
#define PMIC_CODEC_ANA_RW32_ib05_micbias_START     (0)
#define PMIC_CODEC_ANA_RW32_ib05_micbias_END       (2)
#define PMIC_CODEC_ANA_RW32_ib05_adc_linein_START  (3)
#define PMIC_CODEC_ANA_RW32_ib05_adc_linein_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW33_UNION
 �ṹ˵��  : CODEC_ANA_RW33 �Ĵ����ṹ���塣��ַƫ����:0x28A����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ5��reserved��AUXMIC���������źţ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_auxmic : 3;  /* bit[0-2]: IB05_AUXMIC�ĵ��������ź�(IB05_AUXMIC):
                                                      000: 2.5uA��
                                                      001: 3uA��
                                                      010: 3.5uA��
                                                      011: 4uA��
                                                      100: 4.5uA��
                                                      101: 5uA��
                                                      110: 7uA��
                                                      111: 9uA�� */
        unsigned char  ib05_rev    : 3;  /* bit[3-5]: IB05_CTCM�ĵ��������ź�(IB05_CTCM):
                                                      000: 2.5uA��
                                                      001: 3uA��
                                                      010: 3.5uA��
                                                      011: 4uA��
                                                      100: 4.5uA��
                                                      101: 5uA��
                                                      110: 7uA��
                                                      111: 9uA�� */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW33_UNION;
#endif
#define PMIC_CODEC_ANA_RW33_ib05_auxmic_START  (0)
#define PMIC_CODEC_ANA_RW33_ib05_auxmic_END    (2)
#define PMIC_CODEC_ANA_RW33_ib05_rev_START     (3)
#define PMIC_CODEC_ANA_RW33_ib05_rev_END       (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW34_UNION
 �ṹ˵��  : CODEC_ANA_RW34 �Ĵ����ṹ���塣��ַƫ����:0x28B����ֵ:0x2D�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ6��MAINMIC��MIXER_EAR���������źš���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_mixer_ear : 3;  /* bit[0-2]: IB05_MIXER_EAR�ĵ��������ź�(IB05_MIXER_EAR):
                                                         000: 2.5uA��
                                                         001: 3uA��
                                                         010: 3.5uA��
                                                         011: 4uA��
                                                         100: 4.5uA��
                                                         101: 5uA��
                                                         110: 7uA��
                                                         111: 9uA�� */
        unsigned char  ib05_mainmic   : 3;  /* bit[3-5]: IB05_MAINMIC�ĵ��������ź�(IB05_MAINMIC):
                                                         000: 2.5uA��
                                                         001: 3uA��
                                                         010: 3.5uA��
                                                         011: 4uA��
                                                         100: 4.5uA��
                                                         101: 5uA��
                                                         110: 7uA��
                                                         111: 9uA�� */
        unsigned char  reserved       : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW34_UNION;
#endif
#define PMIC_CODEC_ANA_RW34_ib05_mixer_ear_START  (0)
#define PMIC_CODEC_ANA_RW34_ib05_mixer_ear_END    (2)
#define PMIC_CODEC_ANA_RW34_ib05_mainmic_START    (3)
#define PMIC_CODEC_ANA_RW34_ib05_mainmic_END      (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW35_UNION
 �ṹ˵��  : CODEC_ANA_RW35 �Ĵ����ṹ���塣��ַƫ����:0x28C����ֵ:0x0A�����:8
 �Ĵ���˵��: CODEC_IBIAS_ADJ7��EAR��CODECȫ�ֵ��������źţ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_bias_adj : 1;  /* bit[0]  : CODEC��ȫ�ֵ��������ź�(CODEC_IBIAS_ADJ):
                                                         0:5uA��
                                                         1:7.5uA�� */
        unsigned char  ib05_ear       : 3;  /* bit[1-3]: IB05_EAR�ĵ��������ź�(IB05_EAR):
                                                         000: 2.5uA��
                                                         001: 3uA��
                                                         010: 3.5uA��
                                                         011: 4uA��
                                                         100: 4.5uA��
                                                         101: 5uA��
                                                         110: 7uA��
                                                         111: 9uA�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW35_UNION;
#endif
#define PMIC_CODEC_ANA_RW35_codec_bias_adj_START  (0)
#define PMIC_CODEC_ANA_RW35_codec_bias_adj_END    (0)
#define PMIC_CODEC_ANA_RW35_ib05_ear_START        (1)
#define PMIC_CODEC_ANA_RW35_ib05_ear_END          (3)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW36_UNION
 �ṹ˵��  : CODEC_ANA_RW36 �Ĵ����ṹ���塣��ַƫ����:0x28D����ֵ:0x00�����:8
 �Ĵ���˵��: ADC_DACģ�⻷�ؿ����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hpl_pop_res_c : 2;  /* bit[0-1]: HeadphoneL ��POP��ǿ������ܼ������ֵѡ������ź�HPL_POP_RES_C<1:0>��
                                                        00��1.5K��
                                                        01��3K��
                                                        10��4.5K��
                                                        11��6K�� */
        unsigned char  reserved      : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW36_UNION;
#endif
#define PMIC_CODEC_ANA_RW36_hpl_pop_res_c_START  (0)
#define PMIC_CODEC_ANA_RW36_hpl_pop_res_c_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW37_UNION
 �ṹ˵��  : CODEC_ANA_RW37 �Ĵ����ṹ���塣��ַƫ����:0x28E����ֵ:0x00�����:8
 �Ĵ���˵��: HP_BIAS_PD ��CP_PD��CP_DET_PD�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_det_pd  : 1;  /* bit[0]  : ChargePump Detect�ϵ�����ź�(CP_DET_PD)��
                                                     0��PD��
                                                     1����������; */
        unsigned char  cp_pd      : 1;  /* bit[1]  : ChargePump�ϵ�����ź�(CP_PD)��
                                                     0��PD��
                                                     1����������; */
        unsigned char  hp_bias_pd : 1;  /* bit[2]  : Headphone ibias�ϵ�����źţ�HP_BIAS_PD��
                                                     0��PD��
                                                     1����������; */
        unsigned char  reserved   : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW37_UNION;
#endif
#define PMIC_CODEC_ANA_RW37_cp_det_pd_START   (0)
#define PMIC_CODEC_ANA_RW37_cp_det_pd_END     (0)
#define PMIC_CODEC_ANA_RW37_cp_pd_START       (1)
#define PMIC_CODEC_ANA_RW37_cp_pd_END         (1)
#define PMIC_CODEC_ANA_RW37_hp_bias_pd_START  (2)
#define PMIC_CODEC_ANA_RW37_hp_bias_pd_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW38_UNION
 �ṹ˵��  : CODEC_ANA_RW38 �Ĵ����ṹ���塣��ַƫ����:0x28F����ֵ:0x00�����:8
 �Ĵ���˵��: DACL_PD��DACR_PD��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacr_pd  : 1;  /* bit[0]  : DACR�ϵ�����ź�(DACR_PD)��
                                                   0��PD��
                                                   1����������; */
        unsigned char  dacl_pd  : 1;  /* bit[1]  : DACL�ϵ�����ź�(DACL_PD)��
                                                   0��PD��
                                                   1����������; */
        unsigned char  reserved : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW38_UNION;
#endif
#define PMIC_CODEC_ANA_RW38_dacr_pd_START   (0)
#define PMIC_CODEC_ANA_RW38_dacr_pd_END     (0)
#define PMIC_CODEC_ANA_RW38_dacl_pd_START   (1)
#define PMIC_CODEC_ANA_RW38_dacl_pd_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW39_UNION
 �ṹ˵��  : CODEC_ANA_RW39 �Ĵ����ṹ���塣��ַƫ����:0x290����ֵ:0x00�����:8
 �Ĵ���˵��: MIXOUT_EAR_PD��EAR_PD��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ear_pd        : 1;  /* bit[0]  : EAR�ϵ�����ź�(EAR_PD)��
                                                        0��PD��
                                                        1����������; */
        unsigned char  mixout_ear_pd : 1;  /* bit[1]  : MIXOUT_EAR�ϵ�����ź�(MIXOUT_EAR_PD)��
                                                        0��PD��
                                                        1����������; */
        unsigned char  ear_vref_en   : 1;  /* bit[2]  : EAR_VREF�ϵ�����ź�(EAR_VREF_EN)��
                                                        0��PD��
                                                        1����������; */
        unsigned char  reserved      : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW39_UNION;
#endif
#define PMIC_CODEC_ANA_RW39_ear_pd_START         (0)
#define PMIC_CODEC_ANA_RW39_ear_pd_END           (0)
#define PMIC_CODEC_ANA_RW39_mixout_ear_pd_START  (1)
#define PMIC_CODEC_ANA_RW39_mixout_ear_pd_END    (1)
#define PMIC_CODEC_ANA_RW39_ear_vref_en_START    (2)
#define PMIC_CODEC_ANA_RW39_ear_vref_en_END      (2)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW40_UNION
 �ṹ˵��  : CODEC_ANA_RW40 �Ĵ����ṹ���塣��ַƫ����:0x291����ֵ:0x00�����:8
 �Ĵ���˵��: CODEC_ANA_RW40��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hpr_pop_res_c : 2;  /* bit[0-1]: HeadphoneR ��POP��ǿ������ܼ������ֵѡ������ź�HPR_POP_RES_C<1:0>��
                                                        00��1.5K��
                                                        01��3K��
                                                        10��4.5K��
                                                        11��6K�� */
        unsigned char  reserved      : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW40_UNION;
#endif
#define PMIC_CODEC_ANA_RW40_hpr_pop_res_c_START  (0)
#define PMIC_CODEC_ANA_RW40_hpr_pop_res_c_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RO01_UNION
 �ṹ˵��  : CODEC_ANA_RO01 �Ĵ����ṹ���塣��ַƫ����:0x292����ֵ:0x00�����:8
 �Ĵ���˵��: CODEC_ANA_RO01��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_ana_ro01 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CODEC_ANA_RO01_UNION;
#endif
#define PMIC_CODEC_ANA_RO01_codec_ana_ro01_START  (0)
#define PMIC_CODEC_ANA_RO01_codec_ana_ro01_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RO02_UNION
 �ṹ˵��  : CODEC_ANA_RO02 �Ĵ����ṹ���塣��ַƫ����:0x293����ֵ:0x00�����:8
 �Ĵ���˵��: CODEC_ANA_RO02��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_ana_ro02 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CODEC_ANA_RO02_UNION;
#endif
#define PMIC_CODEC_ANA_RO02_codec_ana_ro02_START  (0)
#define PMIC_CODEC_ANA_RO02_codec_ana_ro02_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW41_UNION
 �ṹ˵��  : CODEC_ANA_RW41 �Ĵ����ṹ���塣��ַƫ����:0x294����ֵ:0x27�����:8
 �Ĵ���˵��: OSC_BAK�����ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  osc_bak_adj     : 4;  /* bit[0-3]: FMģʽ�±���ʱ�ӵ����ź�(OSC_BAK_ADJ<3:0>)��
                                                          TT condition
                                                          0000��NO CLK����ֹ
                                                          0001��0.517MHz��
                                                          0010��0.992MHz��
                                                          0011��1.445MHz��
                                                          0100��1.872MHz��
                                                          0101��2.296MHz��
                                                          0110��2.705MHz��
                                                          0111��3.115MHz��
                                                          1000��3.490MHz��
                                                          1001��3.889MHz��
                                                          1010��4.275MHz��
                                                          1011��4.669MHz��
                                                          1100��5.033MHz��
                                                          1101��5.421MHz��
                                                          1110��5.795MHz��
                                                          1111��6.18MHz�� */
        unsigned char  osc_bak_ins_sel : 1;  /* bit[4]  : FMģʽ�±���ʱ�Ӵ���ԭʱ��λ��ѡ���ź�(OSC_BAK_INS_SEL)
                                                          0������ʱ����PLLʱ�ӷ�Ƶ����3M������PLLʱ�ӣ������OSC_BAK_ADJ=7ʱʹ�ã�
                                                          1������ʱ����PLLʱ�ӷ�Ƶ����6M������PLLʱ�ӣ������OSC_BAK_ADJ=15ʱʹ�ã� */
        unsigned char  osc_bak_pd      : 1;  /* bit[5]  : ����ʱ��PD�ź�(OSC_BAK_PD)
                                                          0������������
                                                          1��PD�� */
        unsigned char  reserved        : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW41_UNION;
#endif
#define PMIC_CODEC_ANA_RW41_osc_bak_adj_START      (0)
#define PMIC_CODEC_ANA_RW41_osc_bak_adj_END        (3)
#define PMIC_CODEC_ANA_RW41_osc_bak_ins_sel_START  (4)
#define PMIC_CODEC_ANA_RW41_osc_bak_ins_sel_END    (4)
#define PMIC_CODEC_ANA_RW41_osc_bak_pd_START       (5)
#define PMIC_CODEC_ANA_RW41_osc_bak_pd_END         (5)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW42_UNION
 �ṹ˵��  : CODEC_ANA_RW42 �Ĵ����ṹ���塣��ַƫ����:0x295����ֵ:0x00�����:8
 �Ĵ���˵��: FMģʽ��ʱ���л�ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clk_cp_src_sel     : 1;  /* bit[0]  : Chargepumpʱ��Դѡ���ź�(CLK_CP_SRC_SEL)
                                                             CLK_CP/CLK_CP_DET/CLK_POP_48K
                                                             0��ѡ��PLLʱ�ӣ�
                                                             1��ѡ��OSC_BAKʱ�ӣ� */
        unsigned char  clk_txchop_src_sel : 1;  /* bit[1]  : RXͨ·CHOPʱ��Դѡ���ź�(CLK_TXCHOP_SRC_SEL)
                                                             CLK_DAC_CHOP/CLK_ERA_CLKD_CHOP/CLK_HS_CHOP
                                                             0��ѡ��PLLʱ�ӣ�
                                                             1��ѡ��OSC_BAKʱ�ӣ� */
        unsigned char  clk_rxchop_src_sel : 1;  /* bit[2]  : RXͨ·CHOPʱ��Դѡ���ź�(CLK_RXCHOP_SRC_SEL)
                                                             CLK_LINEIN_CHOP/CLK_MICPGA_CHOP/CLK_ADC_SDM_CHOP/CLK_CTCM_CHOP
                                                             0��ѡ��PLLʱ�ӣ�
                                                             1��ѡ��OSC_BAKʱ�ӣ� */
        unsigned char  reserved           : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW42_UNION;
#endif
#define PMIC_CODEC_ANA_RW42_clk_cp_src_sel_START      (0)
#define PMIC_CODEC_ANA_RW42_clk_cp_src_sel_END        (0)
#define PMIC_CODEC_ANA_RW42_clk_txchop_src_sel_START  (1)
#define PMIC_CODEC_ANA_RW42_clk_txchop_src_sel_END    (1)
#define PMIC_CODEC_ANA_RW42_clk_rxchop_src_sel_START  (2)
#define PMIC_CODEC_ANA_RW42_clk_rxchop_src_sel_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW43_UNION
 �ṹ˵��  : CODEC_ANA_RW43 �Ĵ����ṹ���塣��ַƫ����:0x296����ֵ:0x74�����:8
 �Ĵ���˵��: CODEC_ANA_RW43
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  push_adj_n : 3;  /* bit[0-2]: Headphone ��POP��HP N���������ؿ����ź�PUSH_ADJ_N<2:0>
                                                     000��8/15��
                                                     001��9/15��
                                                     010��10/15��
                                                     011��11/15��
                                                     100��12/15��Ĭ�ϣ���
                                                     101��13/15��
                                                     110��14/15��
                                                     111��full�ߴ磻 */
        unsigned char  reserved_0 : 1;  /* bit[3]  : reserved */
        unsigned char  push_adj_p : 3;  /* bit[4-6]: Headphone ��POP��HP P���������ؿ����ź�PUSH_ADJ_P<2:0>
                                                     000��8/15��
                                                     001��9/15��
                                                     010��10/15��
                                                     011��11/15��
                                                     100��12/15��
                                                     101��13/15��
                                                     110��14/15��
                                                     111��full�ߴ磨Ĭ�ϣ��� */
        unsigned char  reserved_1 : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW43_UNION;
#endif
#define PMIC_CODEC_ANA_RW43_push_adj_n_START  (0)
#define PMIC_CODEC_ANA_RW43_push_adj_n_END    (2)
#define PMIC_CODEC_ANA_RW43_push_adj_p_START  (4)
#define PMIC_CODEC_ANA_RW43_push_adj_p_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW44_UNION
 �ṹ˵��  : CODEC_ANA_RW44 �Ĵ����ṹ���塣��ַƫ����:0x297����ֵ:0x00�����:8
 �Ĵ���˵��: CODEC_ANA_RW44
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW44_UNION;
#endif


/*****************************************************************************
 �ṹ��    : PMIC_CODEC_ANA_RW45_UNION
 �ṹ˵��  : CODEC_ANA_RW45 �Ĵ����ṹ���塣��ַƫ����:0x298����ֵ:0x00�����:8
 �Ĵ���˵��: CODEC_ANA_RW45
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW45_UNION;
#endif






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

#endif /* end of soc_pmic_interface.h */
