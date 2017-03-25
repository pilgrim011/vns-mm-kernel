/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_loadmonitor_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-05-04 14:31:06
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��4��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_LOADMONITOR.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_LOADMONITOR_INTERFACE_H__
#define __SOC_LOADMONITOR_INTERFACE_H__

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
/* �Ĵ���˵����LOADMONITOR������ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION */
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_ADDR(base)    ((base) + (0x000))

/* �Ĵ���˵����LOADMONITOR���������ʱ�����üĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION */
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_ADDR(base)   ((base) + (0x004))

/* �Ĵ���˵����LOADMONITOR�����ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_ADDR(base)  ((base) + (0x008))

/* �Ĵ���˵����LOADMONITOR�����ȥʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_ADDR(base) ((base) + (0x00C))

/* �Ĵ���˵����LOADMONITOR�����ʹ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_ADDR(base) ((base) + (0x010))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD0_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD0_ADDR(base)      ((base) + (0x014))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD1_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD1_ADDR(base)      ((base) + (0x018))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD2_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD2_ADDR(base)      ((base) + (0x01C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD3_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD3_ADDR(base)      ((base) + (0x020))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD4_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD4_ADDR(base)      ((base) + (0x024))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD5_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD5_ADDR(base)      ((base) + (0x028))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD6_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD6_ADDR(base)      ((base) + (0x02C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD7_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD7_ADDR(base)      ((base) + (0x030))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD8_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD8_ADDR(base)      ((base) + (0x034))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD9_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD9_ADDR(base)      ((base) + (0x038))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD10_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD10_ADDR(base)     ((base) + (0x03C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD11_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD11_ADDR(base)     ((base) + (0x040))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD12_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD12_ADDR(base)     ((base) + (0x044))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD13_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD13_ADDR(base)     ((base) + (0x048))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD14_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD14_ADDR(base)     ((base) + (0x04C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD15_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD15_ADDR(base)     ((base) + (0x050))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD16_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD16_ADDR(base)     ((base) + (0x054))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD17_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD17_ADDR(base)     ((base) + (0x058))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD18_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD18_ADDR(base)     ((base) + (0x05C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD19_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD19_ADDR(base)     ((base) + (0x060))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD20_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD20_ADDR(base)     ((base) + (0x064))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD21_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD21_ADDR(base)     ((base) + (0x068))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD22_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD22_ADDR(base)     ((base) + (0x06C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD23_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD23_ADDR(base)     ((base) + (0x070))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD24_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD24_ADDR(base)     ((base) + (0x074))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD25_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD25_ADDR(base)     ((base) + (0x078))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD26_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD26_ADDR(base)     ((base) + (0x07C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD27_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD27_ADDR(base)     ((base) + (0x080))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD28_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD28_ADDR(base)     ((base) + (0x084))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD29_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD29_ADDR(base)     ((base) + (0x088))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD30_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD30_ADDR(base)     ((base) + (0x08C))

/* �Ĵ���˵����LOADMONITOR���ؼĴ���
   λ����UNION�ṹ:  SOC_LOADMONITOR_MONITOR_LOAD31_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD31_ADDR(base)     ((base) + (0x090))





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
 �ṹ��    : SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION
 �ṹ˵��  : MONITOR_CTRL_EN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR������ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_ctrl_en : 1;  /* bit[0]   : LOADMONITOR������ʹ�ܣ�
                                                          0����������ʹ�ܣ�
                                                          1��������ʹ�ܡ� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_monitor_ctrl_en_START  (0)
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_monitor_ctrl_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION
 �ṹ˵��  : MONITOR_CFG_TIME �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���������ʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cfg_time : 32; /* bit[0-31]: ���������ʱ�����üĴ�������������Ϊ60MHzʱ�� */
    } reg;
} SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_monitor_cfg_time_START  (0)
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_monitor_cfg_time_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION
 �ṹ˵��  : MONITOR_SENSOR_EN �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR�����ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_en  : 1;  /* bit[0] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor1_en  : 1;  /* bit[1] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor2_en  : 1;  /* bit[2] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor3_en  : 1;  /* bit[3] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor4_en  : 1;  /* bit[4] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor5_en  : 1;  /* bit[5] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor6_en  : 1;  /* bit[6] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor7_en  : 1;  /* bit[7] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor8_en  : 1;  /* bit[8] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor9_en  : 1;  /* bit[9] : LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor10_en : 1;  /* bit[10]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor11_en : 1;  /* bit[11]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor12_en : 1;  /* bit[12]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor13_en : 1;  /* bit[13]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor14_en : 1;  /* bit[14]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor15_en : 1;  /* bit[15]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor16_en : 1;  /* bit[16]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor17_en : 1;  /* bit[17]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor18_en : 1;  /* bit[18]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor19_en : 1;  /* bit[19]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor20_en : 1;  /* bit[20]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor21_en : 1;  /* bit[21]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor22_en : 1;  /* bit[22]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor23_en : 1;  /* bit[23]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor24_en : 1;  /* bit[24]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor25_en : 1;  /* bit[25]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor26_en : 1;  /* bit[26]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor27_en : 1;  /* bit[27]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor28_en : 1;  /* bit[28]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor29_en : 1;  /* bit[29]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor30_en : 1;  /* bit[30]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
        unsigned int  monitor_sensor31_en : 1;  /* bit[31]: LOADMONITOR�����ʹ�ܣ�
                                                            д0����Ч����
                                                            д1��ʹ�ܼ���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor0_en_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor0_en_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor1_en_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor1_en_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor2_en_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor2_en_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor3_en_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor3_en_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor4_en_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor4_en_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor5_en_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor5_en_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor6_en_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor6_en_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor7_en_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor7_en_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor8_en_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor8_en_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor9_en_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor9_en_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor10_en_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor10_en_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor11_en_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor11_en_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor12_en_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor12_en_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor13_en_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor13_en_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor14_en_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor14_en_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor15_en_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor15_en_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor16_en_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor16_en_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor17_en_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor17_en_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor18_en_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor18_en_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor19_en_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor19_en_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor20_en_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor20_en_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor21_en_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor21_en_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor22_en_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor22_en_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor23_en_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor23_en_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor24_en_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor24_en_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor25_en_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor25_en_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor26_en_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor26_en_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor27_en_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor27_en_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor28_en_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor28_en_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor29_en_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor29_en_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor30_en_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor30_en_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor31_en_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor31_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION
 �ṹ˵��  : MONITOR_SENSOR_DIS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR�����ȥʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_dis  : 1;  /* bit[0] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor1_dis  : 1;  /* bit[1] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor2_dis  : 1;  /* bit[2] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor3_dis  : 1;  /* bit[3] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor4_dis  : 1;  /* bit[4] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor5_dis  : 1;  /* bit[5] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor6_dis  : 1;  /* bit[6] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor7_dis  : 1;  /* bit[7] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor8_dis  : 1;  /* bit[8] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor9_dis  : 1;  /* bit[9] : LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor10_dis : 1;  /* bit[10]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor11_dis : 1;  /* bit[11]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor12_dis : 1;  /* bit[12]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor13_dis : 1;  /* bit[13]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor14_dis : 1;  /* bit[14]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor15_dis : 1;  /* bit[15]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor16_dis : 1;  /* bit[16]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor17_dis : 1;  /* bit[17]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor18_dis : 1;  /* bit[18]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor19_dis : 1;  /* bit[19]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor20_dis : 1;  /* bit[20]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor21_dis : 1;  /* bit[21]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor22_dis : 1;  /* bit[22]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor23_dis : 1;  /* bit[23]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor24_dis : 1;  /* bit[24]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor25_dis : 1;  /* bit[25]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor26_dis : 1;  /* bit[26]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor27_dis : 1;  /* bit[27]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor28_dis : 1;  /* bit[28]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor29_dis : 1;  /* bit[29]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor30_dis : 1;  /* bit[30]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
        unsigned int  monitor_sensor31_dis : 1;  /* bit[31]: LOADMONITOR�����ȥʹ�ܣ�
                                                             д0����Ч����
                                                             д1��ȥʹ�ܼ���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor0_dis_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor0_dis_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor1_dis_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor1_dis_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor2_dis_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor2_dis_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor3_dis_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor3_dis_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor4_dis_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor4_dis_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor5_dis_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor5_dis_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor6_dis_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor6_dis_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor7_dis_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor7_dis_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor8_dis_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor8_dis_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor9_dis_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor9_dis_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor10_dis_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor10_dis_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor11_dis_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor11_dis_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor12_dis_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor12_dis_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor13_dis_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor13_dis_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor14_dis_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor14_dis_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor15_dis_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor15_dis_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor16_dis_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor16_dis_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor17_dis_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor17_dis_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor18_dis_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor18_dis_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor19_dis_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor19_dis_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor20_dis_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor20_dis_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor21_dis_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor21_dis_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor22_dis_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor22_dis_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor23_dis_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor23_dis_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor24_dis_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor24_dis_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor25_dis_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor25_dis_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor26_dis_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor26_dis_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor27_dis_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor27_dis_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor28_dis_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor28_dis_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor29_dis_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor29_dis_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor30_dis_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor30_dis_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor31_dis_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor31_dis_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION
 �ṹ˵��  : MONITOR_SENSOR_STAT �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR�����ʹ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_stat  : 1;  /* bit[0] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor1_stat  : 1;  /* bit[1] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor2_stat  : 1;  /* bit[2] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor3_stat  : 1;  /* bit[3] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor4_stat  : 1;  /* bit[4] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor5_stat  : 1;  /* bit[5] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor6_stat  : 1;  /* bit[6] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor7_stat  : 1;  /* bit[7] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor8_stat  : 1;  /* bit[8] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor9_stat  : 1;  /* bit[9] : LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor10_stat : 1;  /* bit[10]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor11_stat : 1;  /* bit[11]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor12_stat : 1;  /* bit[12]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor13_stat : 1;  /* bit[13]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor14_stat : 1;  /* bit[14]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor15_stat : 1;  /* bit[15]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor16_stat : 1;  /* bit[16]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor17_stat : 1;  /* bit[17]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor18_stat : 1;  /* bit[18]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor19_stat : 1;  /* bit[19]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor20_stat : 1;  /* bit[20]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor21_stat : 1;  /* bit[21]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor22_stat : 1;  /* bit[22]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor23_stat : 1;  /* bit[23]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor24_stat : 1;  /* bit[24]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor25_stat : 1;  /* bit[25]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor26_stat : 1;  /* bit[26]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor27_stat : 1;  /* bit[27]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor28_stat : 1;  /* bit[28]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor29_stat : 1;  /* bit[29]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor30_stat : 1;  /* bit[30]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
        unsigned int  monitor_sensor31_stat : 1;  /* bit[31]: LOADMONITOR�����ʹ��״̬��
                                                              0����ʹ�ܣ�
                                                              1��ʹ�� */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor0_stat_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor0_stat_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor1_stat_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor1_stat_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor2_stat_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor2_stat_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor3_stat_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor3_stat_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor4_stat_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor4_stat_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor5_stat_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor5_stat_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor6_stat_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor6_stat_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor7_stat_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor7_stat_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor8_stat_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor8_stat_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor9_stat_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor9_stat_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor10_stat_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor10_stat_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor11_stat_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor11_stat_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor12_stat_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor12_stat_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor13_stat_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor13_stat_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor14_stat_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor14_stat_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor15_stat_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor15_stat_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor16_stat_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor16_stat_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor17_stat_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor17_stat_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor18_stat_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor18_stat_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor19_stat_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor19_stat_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor20_stat_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor20_stat_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor21_stat_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor21_stat_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor22_stat_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor22_stat_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor23_stat_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor23_stat_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor24_stat_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor24_stat_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor25_stat_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor25_stat_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor26_stat_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor26_stat_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor27_stat_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor27_stat_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor28_stat_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor28_stat_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor29_stat_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor29_stat_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor30_stat_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor30_stat_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor31_stat_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor31_stat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD0_UNION
 �ṹ˵��  : MONITOR_LOAD0 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load0 : 32; /* bit[0-31]: ��0·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD0_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD0_monitor_cnt_load0_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD0_monitor_cnt_load0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD1_UNION
 �ṹ˵��  : MONITOR_LOAD1 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load1 : 32; /* bit[0-31]: ��1·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD1_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD1_monitor_cnt_load1_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD1_monitor_cnt_load1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD2_UNION
 �ṹ˵��  : MONITOR_LOAD2 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load2 : 32; /* bit[0-31]: ��2·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD2_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD2_monitor_cnt_load2_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD2_monitor_cnt_load2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD3_UNION
 �ṹ˵��  : MONITOR_LOAD3 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load3 : 32; /* bit[0-31]: ��3·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD3_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD3_monitor_cnt_load3_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD3_monitor_cnt_load3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD4_UNION
 �ṹ˵��  : MONITOR_LOAD4 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load4 : 32; /* bit[0-31]: ��4·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD4_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD4_monitor_cnt_load4_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD4_monitor_cnt_load4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD5_UNION
 �ṹ˵��  : MONITOR_LOAD5 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load5 : 32; /* bit[0-31]: ��5·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD5_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD5_monitor_cnt_load5_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD5_monitor_cnt_load5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD6_UNION
 �ṹ˵��  : MONITOR_LOAD6 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load6 : 32; /* bit[0-31]: ��6·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD6_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD6_monitor_cnt_load6_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD6_monitor_cnt_load6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD7_UNION
 �ṹ˵��  : MONITOR_LOAD7 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load7 : 32; /* bit[0-31]: ��7·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD7_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD7_monitor_cnt_load7_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD7_monitor_cnt_load7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD8_UNION
 �ṹ˵��  : MONITOR_LOAD8 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load8 : 32; /* bit[0-31]: ��8·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD8_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD8_monitor_cnt_load8_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD8_monitor_cnt_load8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD9_UNION
 �ṹ˵��  : MONITOR_LOAD9 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load9 : 32; /* bit[0-31]: ��9·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD9_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD9_monitor_cnt_load9_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD9_monitor_cnt_load9_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD10_UNION
 �ṹ˵��  : MONITOR_LOAD10 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load10 : 32; /* bit[0-31]: ��10·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD10_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD10_monitor_cnt_load10_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD10_monitor_cnt_load10_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD11_UNION
 �ṹ˵��  : MONITOR_LOAD11 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load11 : 32; /* bit[0-31]: ��11·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD11_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD11_monitor_cnt_load11_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD11_monitor_cnt_load11_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD12_UNION
 �ṹ˵��  : MONITOR_LOAD12 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load12 : 32; /* bit[0-31]: ��12·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD12_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD12_monitor_cnt_load12_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD12_monitor_cnt_load12_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD13_UNION
 �ṹ˵��  : MONITOR_LOAD13 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load13 : 32; /* bit[0-31]: ��13·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD13_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD13_monitor_cnt_load13_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD13_monitor_cnt_load13_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD14_UNION
 �ṹ˵��  : MONITOR_LOAD14 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load14 : 32; /* bit[0-31]: ��14·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD14_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD14_monitor_cnt_load14_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD14_monitor_cnt_load14_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD15_UNION
 �ṹ˵��  : MONITOR_LOAD15 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load15 : 32; /* bit[0-31]: ��15·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD15_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD15_monitor_cnt_load15_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD15_monitor_cnt_load15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD16_UNION
 �ṹ˵��  : MONITOR_LOAD16 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load16 : 32; /* bit[0-31]: ��16·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD16_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD16_monitor_cnt_load16_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD16_monitor_cnt_load16_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD17_UNION
 �ṹ˵��  : MONITOR_LOAD17 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load17 : 32; /* bit[0-31]: ��17·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD17_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD17_monitor_cnt_load17_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD17_monitor_cnt_load17_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD18_UNION
 �ṹ˵��  : MONITOR_LOAD18 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load18 : 32; /* bit[0-31]: ��18·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD18_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD18_monitor_cnt_load18_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD18_monitor_cnt_load18_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD19_UNION
 �ṹ˵��  : MONITOR_LOAD19 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load19 : 32; /* bit[0-31]: ��19·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD19_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD19_monitor_cnt_load19_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD19_monitor_cnt_load19_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD20_UNION
 �ṹ˵��  : MONITOR_LOAD20 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load20 : 32; /* bit[0-31]: ��20·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD20_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD20_monitor_cnt_load20_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD20_monitor_cnt_load20_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD21_UNION
 �ṹ˵��  : MONITOR_LOAD21 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load21 : 32; /* bit[0-31]: ��21·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD21_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD21_monitor_cnt_load21_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD21_monitor_cnt_load21_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD22_UNION
 �ṹ˵��  : MONITOR_LOAD22 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load22 : 32; /* bit[0-31]: ��22·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD22_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD22_monitor_cnt_load22_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD22_monitor_cnt_load22_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD23_UNION
 �ṹ˵��  : MONITOR_LOAD23 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load23 : 32; /* bit[0-31]: ��23·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD23_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD23_monitor_cnt_load23_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD23_monitor_cnt_load23_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD24_UNION
 �ṹ˵��  : MONITOR_LOAD24 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load24 : 32; /* bit[0-31]: ��24·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD24_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD24_monitor_cnt_load24_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD24_monitor_cnt_load24_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD25_UNION
 �ṹ˵��  : MONITOR_LOAD25 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load25 : 32; /* bit[0-31]: ��25·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD25_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD25_monitor_cnt_load25_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD25_monitor_cnt_load25_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD26_UNION
 �ṹ˵��  : MONITOR_LOAD26 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load26 : 32; /* bit[0-31]: ��26·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD26_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD26_monitor_cnt_load26_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD26_monitor_cnt_load26_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD27_UNION
 �ṹ˵��  : MONITOR_LOAD27 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load27 : 32; /* bit[0-31]: ��27·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD27_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD27_monitor_cnt_load27_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD27_monitor_cnt_load27_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD28_UNION
 �ṹ˵��  : MONITOR_LOAD28 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load28 : 32; /* bit[0-31]: ��28·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD28_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD28_monitor_cnt_load28_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD28_monitor_cnt_load28_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD29_UNION
 �ṹ˵��  : MONITOR_LOAD29 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load29 : 32; /* bit[0-31]: ��29·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD29_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD29_monitor_cnt_load29_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD29_monitor_cnt_load29_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD30_UNION
 �ṹ˵��  : MONITOR_LOAD30 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load30 : 32; /* bit[0-31]: ��30·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD30_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD30_monitor_cnt_load30_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD30_monitor_cnt_load30_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LOADMONITOR_MONITOR_LOAD31_UNION
 �ṹ˵��  : MONITOR_LOAD31 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOADMONITOR���ؼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load31 : 32; /* bit[0-31]: ��31·���� */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD31_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD31_monitor_cnt_load31_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD31_monitor_cnt_load31_END    (31)






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

#endif /* end of soc_loadmonitor_interface.h */
