/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_cci500_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-22 13:56:36
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��22��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_CCI500.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CCI500_INTERFACE_H__
#define __SOC_CCI500_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) CCI500
 ****************************************************************************/
/* �Ĵ���˵�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_CTRL_OVR_UNION */
#define SOC_CCI500_CTRL_OVR_ADDR(base)                ((base) + (0x00000))

/* �Ĵ���˵������ȫ���ʼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_SECR_ACC_UNION */
#define SOC_CCI500_SECR_ACC_ADDR(base)                ((base) + (0x00008))

/* �Ĵ���˵����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_STATUS_UNION */
#define SOC_CCI500_STATUS_ADDR(base)                  ((base) + (0x0000C))

/* �Ĵ���˵������ȷ������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_IMPR_ERR_UNION */
#define SOC_CCI500_IMPR_ERR_ADDR(base)                ((base) + (0x00010))

/* �Ĵ���˵����QOS��ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_QOS_THRESHOLD_UNION */
#define SOC_CCI500_QOS_THRESHOLD_ADDR(base)           ((base) + (0x00014))

/* �Ĵ���˵�������ܼ�ؼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_PMU_CTRL_UNION */
#define SOC_CCI500_PMU_CTRL_ADDR(base)                ((base) + (0x00100))

/* �Ĵ���˵�����ӿڼ�ؿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_DEBUG_CTRL_UNION */
#define SOC_CCI500_DEBUG_CTRL_ADDR(base)              ((base) + (0x00104))

/* �Ĵ���˵��������ID�Ĵ���4��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID4_UNION */
#define SOC_CCI500_PERIPHERAL_ID4_ADDR(base)          ((base) + (0x00FD0))

/* �Ĵ���˵��������ID�Ĵ���5��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID5_UNION */
#define SOC_CCI500_PERIPHERAL_ID5_ADDR(base)          ((base) + (0x00FD4))

/* �Ĵ���˵��������ID�Ĵ���6��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID6_UNION */
#define SOC_CCI500_PERIPHERAL_ID6_ADDR(base)          ((base) + (0x00FD8))

/* �Ĵ���˵��������ID�Ĵ���7��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID7_UNION */
#define SOC_CCI500_PERIPHERAL_ID7_ADDR(base)          ((base) + (0x00FDC))

/* �Ĵ���˵��������ID�Ĵ���0��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID0_UNION */
#define SOC_CCI500_PERIPHERAL_ID0_ADDR(base)          ((base) + (0x00FE0))

/* �Ĵ���˵��������ID�Ĵ���1��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID1_UNION */
#define SOC_CCI500_PERIPHERAL_ID1_ADDR(base)          ((base) + (0x00FE4))

/* �Ĵ���˵��������ID�Ĵ���2��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID2_UNION */
#define SOC_CCI500_PERIPHERAL_ID2_ADDR(base)          ((base) + (0x00FE8))

/* �Ĵ���˵��������ID�Ĵ���3��
   λ����UNION�ṹ:  SOC_CCI500_PERIPHERAL_ID3_UNION */
#define SOC_CCI500_PERIPHERAL_ID3_ADDR(base)          ((base) + (0x00FEC))

/* �Ĵ���˵�������ID�Ĵ���0��
   λ����UNION�ṹ:  SOC_CCI500_COMPONENT_ID0_UNION */
#define SOC_CCI500_COMPONENT_ID0_ADDR(base)           ((base) + (0x00FF0))

/* �Ĵ���˵�������ID�Ĵ���1��
   λ����UNION�ṹ:  SOC_CCI500_COMPONENT_ID1_UNION */
#define SOC_CCI500_COMPONENT_ID1_ADDR(base)           ((base) + (0x00FF4))

/* �Ĵ���˵�������ID�Ĵ���2��
   λ����UNION�ṹ:  SOC_CCI500_COMPONENT_ID2_UNION */
#define SOC_CCI500_COMPONENT_ID2_ADDR(base)           ((base) + (0x00FF8))

/* �Ĵ���˵�������ID�Ĵ���3��
   λ����UNION�ṹ:  SOC_CCI500_COMPONENT_ID3_UNION */
#define SOC_CCI500_COMPONENT_ID3_ADDR(base)           ((base) + (0x00FFC))

/* �Ĵ���˵����S0 snoop���ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_SNOOP_CTRL_S0_UNION */
#define SOC_CCI500_SNOOP_CTRL_S0_ADDR(base)           ((base) + (0x01000))

/* �Ĵ���˵����S0 shareable override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_SHARE_OVR_S0_UNION */
#define SOC_CCI500_SHARE_OVR_S0_ADDR(base)            ((base) + (0x01004))

/* �Ĵ���˵����S0��ͨ��QoS override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ARQOS_OVR_S0_UNION */
#define SOC_CCI500_ARQOS_OVR_S0_ADDR(base)            ((base) + (0x01100))

/* �Ĵ���˵����S0дͨ��QoS override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_AWQOS_OVR_S0_UNION */
#define SOC_CCI500_AWQOS_OVR_S0_ADDR(base)            ((base) + (0x01104))

/* �Ĵ���˵����S0���OT�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_QOS_MAX_OT_S0_UNION */
#define SOC_CCI500_QOS_MAX_OT_S0_ADDR(base)           ((base) + (0x01110))

/* �Ĵ���˵����S1 snoop���ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_SNOOP_CTRL_S1_UNION */
#define SOC_CCI500_SNOOP_CTRL_S1_ADDR(base)           ((base) + (0x02000))

/* �Ĵ���˵����S1 shareable override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_SHARE_OVR_S1_UNION */
#define SOC_CCI500_SHARE_OVR_S1_ADDR(base)            ((base) + (0x02004))

/* �Ĵ���˵����S1��ͨ��QoS override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ARQOS_OVR_S1_UNION */
#define SOC_CCI500_ARQOS_OVR_S1_ADDR(base)            ((base) + (0x02100))

/* �Ĵ���˵����S1дͨ��QoS override�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_AWQOS_OVR_S1_UNION */
#define SOC_CCI500_AWQOS_OVR_S1_ADDR(base)            ((base) + (0x02104))

/* �Ĵ���˵����S1���OT�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_QOS_MAX_OT_31_UNION */
#define SOC_CCI500_QOS_MAX_OT_31_ADDR(base)           ((base) + (0x02110))

/* �Ĵ���˵����Performance counter 0�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_0_UNION */
#define SOC_CCI500_EVNT_SEL_0_ADDR(base)              ((base) + (0x10000))

/* �Ĵ���˵����Performance counter 0�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_0_UNION */
#define SOC_CCI500_ECNT_DATA_0_ADDR(base)             ((base) + (0x10004))

/* �Ĵ���˵����Performance counter 0�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_0_UNION */
#define SOC_CCI500_ECNT_CTRL_0_ADDR(base)             ((base) + (0x10008))

/* �Ĵ���˵����Performance counter 0�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_0_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_0_ADDR(base)         ((base) + (0x1000C))

/* �Ĵ���˵����Performance counter 1�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_1_UNION */
#define SOC_CCI500_EVNT_SEL_1_ADDR(base)              ((base) + (0x20000))

/* �Ĵ���˵����Performance counter 1�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_1_UNION */
#define SOC_CCI500_ECNT_DATA_1_ADDR(base)             ((base) + (0x20004))

/* �Ĵ���˵����Performance counter 1�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_1_UNION */
#define SOC_CCI500_ECNT_CTRL_1_ADDR(base)             ((base) + (0x20008))

/* �Ĵ���˵����Performance counter 1�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_1_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_1_ADDR(base)         ((base) + (0x2000C))

/* �Ĵ���˵����Performance counter 2�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_2_UNION */
#define SOC_CCI500_EVNT_SEL_2_ADDR(base)              ((base) + (0x30000))

/* �Ĵ���˵����Performance counter 2�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_2_UNION */
#define SOC_CCI500_ECNT_DATA_2_ADDR(base)             ((base) + (0x30004))

/* �Ĵ���˵����Performance counter 2�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_2_UNION */
#define SOC_CCI500_ECNT_CTRL_2_ADDR(base)             ((base) + (0x30008))

/* �Ĵ���˵����Performance counter 2�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_2_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_2_ADDR(base)         ((base) + (0x3000C))

/* �Ĵ���˵����Performance counter 3�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_3_UNION */
#define SOC_CCI500_EVNT_SEL_3_ADDR(base)              ((base) + (0x40000))

/* �Ĵ���˵����Performance counter 3�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_3_UNION */
#define SOC_CCI500_ECNT_DATA_3_ADDR(base)             ((base) + (0x40004))

/* �Ĵ���˵����Performance counter 3�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_3_UNION */
#define SOC_CCI500_ECNT_CTRL_3_ADDR(base)             ((base) + (0x40008))

/* �Ĵ���˵����Performance counter 3�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_3_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_3_ADDR(base)         ((base) + (0x4000C))

/* �Ĵ���˵����Performance counter 4�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_4_UNION */
#define SOC_CCI500_EVNT_SEL_4_ADDR(base)              ((base) + (0x50000))

/* �Ĵ���˵����Performance counter 4�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_4_UNION */
#define SOC_CCI500_ECNT_DATA_4_ADDR(base)             ((base) + (0x50004))

/* �Ĵ���˵����Performance counter 4�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_4_UNION */
#define SOC_CCI500_ECNT_CTRL_4_ADDR(base)             ((base) + (0x50008))

/* �Ĵ���˵����Performance counter 4�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_4_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_4_ADDR(base)         ((base) + (0x5000C))

/* �Ĵ���˵����Performance counter 5�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_5_UNION */
#define SOC_CCI500_EVNT_SEL_5_ADDR(base)              ((base) + (0x60000))

/* �Ĵ���˵����Performance counter 5�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_5_UNION */
#define SOC_CCI500_ECNT_DATA_5_ADDR(base)             ((base) + (0x60004))

/* �Ĵ���˵����Performance counter 5�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_5_UNION */
#define SOC_CCI500_ECNT_CTRL_5_ADDR(base)             ((base) + (0x60008))

/* �Ĵ���˵����Performance counter 5�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_5_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_5_ADDR(base)         ((base) + (0x6000C))

/* �Ĵ���˵����Performance counter 6�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_6_UNION */
#define SOC_CCI500_EVNT_SEL_6_ADDR(base)              ((base) + (0x70000))

/* �Ĵ���˵����Performance counter 6�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_6_UNION */
#define SOC_CCI500_ECNT_DATA_6_ADDR(base)             ((base) + (0x70004))

/* �Ĵ���˵����Performance counter 6�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_6_UNION */
#define SOC_CCI500_ECNT_CTRL_6_ADDR(base)             ((base) + (0x70008))

/* �Ĵ���˵����Performance counter 6�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_6_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_6_ADDR(base)         ((base) + (0x7000C))

/* �Ĵ���˵����Performance counter 7�¼�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_EVNT_SEL_7_UNION */
#define SOC_CCI500_EVNT_SEL_7_ADDR(base)              ((base) + (0x80000))

/* �Ĵ���˵����Performance counter 7�¼������Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_DATA_7_UNION */
#define SOC_CCI500_ECNT_DATA_7_ADDR(base)             ((base) + (0x80004))

/* �Ĵ���˵����Performance counter 7�������ƼĴ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CTRL_7_UNION */
#define SOC_CCI500_ECNT_CTRL_7_ADDR(base)             ((base) + (0x80008))

/* �Ĵ���˵����Performance counter 7�����־״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_ECNT_CLR_OVFL_7_UNION */
#define SOC_CCI500_ECNT_CLR_OVFL_7_ADDR(base)         ((base) + (0x8000C))

/* �Ĵ���˵����slave 0 debug�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_SLAVE_DEBUG_0_UNION */
#define SOC_CCI500_SLAVE_DEBUG_0_ADDR(base)           ((base) + (0x90000))

/* �Ĵ���˵����slave 1 debug�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_SLAVE_DEBUG_1_UNION */
#define SOC_CCI500_SLAVE_DEBUG_1_ADDR(base)           ((base) + (0x90004))

/* �Ĵ���˵����master 0 debug�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_MASTER_DEBUG_0_UNION */
#define SOC_CCI500_MASTER_DEBUG_0_ADDR(base)          ((base) + (0x90100))

/* �Ĵ���˵����master 1 debug�Ĵ�����
   λ����UNION�ṹ:  SOC_CCI500_MASTER_DEBUG_1_UNION */
#define SOC_CCI500_MASTER_DEBUG_1_ADDR(base)          ((base) + (0x90104))





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
                     (1/1) CCI500
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CCI500_CTRL_OVR_UNION
 �ṹ˵��  : CTRL_OVR �Ĵ����ṹ���塣��ַƫ����:0x00000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_disable        : 1;  /* bit[0]   : Snoop disable:
                                                               0:Send snoop requests according to the Snoop Control Registers.
                                                               1:Disable all snoops but not DVM messages. */
        unsigned int  dvm_message_disable  : 1;  /* bit[1]   : DVM message disable:
                                                               0:Send DVM messages according to the Snoop Control Registers. 
                                                               1:Disable propagation of all DVM messages. */
        unsigned int  disable_snoop_filter : 1;  /* bit[2]   : Disable the snoop filter:
                                                               0:Snoop filter operation is defined by the power state input, PSTATE.
                                                               1:Disable snoop filter operation. */
        unsigned int  disable_clock_gating : 1;  /* bit[3]   : Disable regional clock gating:
                                                               0:Regional clock gating operates in the CCI-500.
                                                               1:Disable regional clock gating in the CCI-500. */
        unsigned int  reserved             : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CCI500_CTRL_OVR_UNION;
#endif
#define SOC_CCI500_CTRL_OVR_snoop_disable_START         (0)
#define SOC_CCI500_CTRL_OVR_snoop_disable_END           (0)
#define SOC_CCI500_CTRL_OVR_dvm_message_disable_START   (1)
#define SOC_CCI500_CTRL_OVR_dvm_message_disable_END     (1)
#define SOC_CCI500_CTRL_OVR_disable_snoop_filter_START  (2)
#define SOC_CCI500_CTRL_OVR_disable_snoop_filter_END    (2)
#define SOC_CCI500_CTRL_OVR_disable_clock_gating_START  (3)
#define SOC_CCI500_CTRL_OVR_disable_clock_gating_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SECR_ACC_UNION
 �ṹ˵��  : SECR_ACC �Ĵ����ṹ���塣��ַƫ����:0x00008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ���ʼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  non_secure_register_access_override : 1;  /* bit[0]   : Non-secure register access override:
                                                                              0:Disable Non-secure access to the CCI-500 registers.
                                                                              1:Enable Non-secure access to the CCI-500 registers. */
        unsigned int  debug_monitor_security_override     : 1;  /* bit[1]   : Debug monitor security override:
                                                                              0:Enable Non-secure access to the PMU and Interface Monitor Registers.
                                                                              1:Disable Non-secure access to the PMU and Interface Monitor Registers, unless overridden by bit[0]. */
        unsigned int  reserved                            : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI500_SECR_ACC_UNION;
#endif
#define SOC_CCI500_SECR_ACC_non_secure_register_access_override_START  (0)
#define SOC_CCI500_SECR_ACC_non_secure_register_access_override_END    (0)
#define SOC_CCI500_SECR_ACC_debug_monitor_security_override_START      (1)
#define SOC_CCI500_SECR_ACC_debug_monitor_security_override_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_STATUS_UNION
 �ṹ˵��  : STATUS �Ĵ����ṹ���塣��ַƫ����:0x0000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  change_pending              : 1;  /* bit[0]   : Indicates whether any changes to the Snoop Control Registers or the Control Override Register are pending in the CCI-500:
                                                                      0:No changes are pending.
                                                                      1:Changes are pending. */
        unsigned int  sf_ram_initialization       : 1;  /* bit[1]   : Indicates when the snoop filter RAM is initialized. Shareable requests are not serviced during this period.
                                                                      0:Snoop filter RAM initialization is complete.
                                                                      1:Snoop filter RAM initialization is in progress. */
        unsigned int  sf_ram_state                : 3;  /* bit[2-4] : The snoop filter RAM power states are:
                                                                      0b000:Off.
                                                                      0b001:Static snoop filter RAM retention.
                                                                      0b010:Reserved.
                                                                      0b011:Dynamic snoop filter RAM retention.
                                                                      0b100:On.
                                                                      0b101:Reserved.
                                                                      0b110:Reserved.
                                                                      0b111:Reserved. */
        unsigned int  sf_ram_state_request        : 3;  /* bit[5-7] : This indicates the last requested power state of the snoop filter RAMs. The possible values of this field are the same as those of sf_ram_state.
                                                                      0b000:Off.
                                                                      0b001:Static snoop filter RAM retention.
                                                                      0b010:Reserved.
                                                                      0b011:Dynamic snoop filter RAM retention.
                                                                      0b100:On.
                                                                      0b101:Reserved.
                                                                      0b110:Reserved.
                                                                      0b111:Reserved. */
        unsigned int  sf_ram_state_change_pending : 1;  /* bit[8]   : Snoop filter RAM power state change pending. This bit reads back the PREQ input.
                                                                      0:No change pending, any previous requests have been accepted or denied.
                                                                      1:State change is pending and might be accepted or denied. */
        unsigned int  reserved                    : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_CCI500_STATUS_UNION;
#endif
#define SOC_CCI500_STATUS_change_pending_START               (0)
#define SOC_CCI500_STATUS_change_pending_END                 (0)
#define SOC_CCI500_STATUS_sf_ram_initialization_START        (1)
#define SOC_CCI500_STATUS_sf_ram_initialization_END          (1)
#define SOC_CCI500_STATUS_sf_ram_state_START                 (2)
#define SOC_CCI500_STATUS_sf_ram_state_END                   (4)
#define SOC_CCI500_STATUS_sf_ram_state_request_START         (5)
#define SOC_CCI500_STATUS_sf_ram_state_request_END           (7)
#define SOC_CCI500_STATUS_sf_ram_state_change_pending_START  (8)
#define SOC_CCI500_STATUS_sf_ram_state_change_pending_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_IMPR_ERR_UNION
 �ṹ˵��  : IMPR_ERR �Ĵ����ṹ���塣��ַƫ����:0x00010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȷ������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  imprecise_error_indicator_mi0 : 1;  /* bit[0]    : Imprecise error indicator for master interface 0.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_mi1 : 1;  /* bit[1]    : Imprecise error indicator for master interface 1.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_mi2 : 1;  /* bit[2]    : Imprecise error indicator for master interface 1.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_mi3 : 1;  /* bit[3]    : Imprecise error indicator for master interface 1.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_mi4 : 1;  /* bit[4]    : Imprecise error indicator for master interface 1.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_mi5 : 1;  /* bit[5]    : Imprecise error indicator for master interface 2.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  reserved_0                    : 10; /* bit[6-15] : Reserved */
        unsigned int  imprecise_error_indicator_si0 : 1;  /* bit[16]   : Imprecise error indicator for slave interface 0.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si1 : 1;  /* bit[17]   : Imprecise error indicator for slave interface 1.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si2 : 1;  /* bit[18]   : Imprecise error indicator for slave interface 2.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si3 : 1;  /* bit[19]   : Imprecise error indicator for slave interface 3.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si4 : 1;  /* bit[20]   : Imprecise error indicator for slave interface 4.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si5 : 1;  /* bit[21]   : Imprecise error indicator for slave interface 5.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  imprecise_error_indicator_si6 : 1;  /* bit[22]   : Imprecise error indicator for slave interface 6.
                                                                         0:No error from the time this bit was last reset.
                                                                         1:An error response has been received, but not signaled precisely. */
        unsigned int  reserved_1                    : 9;  /* bit[23-31]: Reserved */
    } reg;
} SOC_CCI500_IMPR_ERR_UNION;
#endif
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi0_START  (0)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi0_END    (0)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi1_START  (1)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi1_END    (1)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi2_START  (2)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi2_END    (2)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi3_START  (3)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi3_END    (3)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi4_START  (4)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi4_END    (4)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi5_START  (5)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_mi5_END    (5)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si0_START  (16)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si0_END    (16)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si1_START  (17)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si1_END    (17)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si2_START  (18)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si2_END    (18)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si3_START  (19)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si3_END    (19)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si4_START  (20)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si4_END    (20)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si5_START  (21)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si5_END    (21)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si6_START  (22)
#define SOC_CCI500_IMPR_ERR_imprecise_error_indicator_si6_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_QOS_THRESHOLD_UNION
 �ṹ˵��  : QOS_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x00014����ֵ:0x000000�����:32
 �Ĵ���˵��: QOS��ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_qv_thresh_high : 4;  /* bit[0-3]  : Read QoS threshold for high priority requests */
        unsigned int  reserved_0       : 12; /* bit[4-15] : reserved */
        unsigned int  w_qv_thresh_high : 4;  /* bit[16-19]: Write QoS threshold for high priority requests */
        unsigned int  reserved_1       : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_CCI500_QOS_THRESHOLD_UNION;
#endif
#define SOC_CCI500_QOS_THRESHOLD_r_qv_thresh_high_START  (0)
#define SOC_CCI500_QOS_THRESHOLD_r_qv_thresh_high_END    (3)
#define SOC_CCI500_QOS_THRESHOLD_w_qv_thresh_high_START  (16)
#define SOC_CCI500_QOS_THRESHOLD_w_qv_thresh_high_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PMU_CTRL_UNION
 �ṹ˵��  : PMU_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00100����ֵ:0x00004000�����:32
 �Ĵ���˵��: ���ܼ�ؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CEN                : 1;  /* bit[0]    : Enable bit:
                                                              0:Disable all event counters.
                                                              1:Enable all event counters. */
        unsigned int  RST                : 1;  /* bit[1]    : Performance counter reset:
                                                              0:No action.
                                                              1:Reset all performance counters to zero. */
        unsigned int  reserved_0         : 2;  /* bit[2-3]  : Reserved. */
        unsigned int  EX                 : 1;  /* bit[4]    : Enables export of the events to the event bus, EVNTBUS, to permit an external monitoring block to trace events:
                                                              0:Do not export EVNTBUS.
                                                              1:Export EVNTBUS. */
        unsigned int  reserved_1         : 6;  /* bit[5-10] : Reserved. */
        unsigned int  number_of_counters : 5;  /* bit[11-15]: Specifies the number of counters implemented. */
        unsigned int  reserved_2         : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_CCI500_PMU_CTRL_UNION;
#endif
#define SOC_CCI500_PMU_CTRL_CEN_START                 (0)
#define SOC_CCI500_PMU_CTRL_CEN_END                   (0)
#define SOC_CCI500_PMU_CTRL_RST_START                 (1)
#define SOC_CCI500_PMU_CTRL_RST_END                   (1)
#define SOC_CCI500_PMU_CTRL_EX_START                  (4)
#define SOC_CCI500_PMU_CTRL_EX_END                    (4)
#define SOC_CCI500_PMU_CTRL_number_of_counters_START  (11)
#define SOC_CCI500_PMU_CTRL_number_of_counters_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_DEBUG_CTRL_UNION
 �ṹ˵��  : DEBUG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00104����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ӿڼ�ؿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable_interface_monitors : 1;  /* bit[0]   : Enable bit:
                                                                    0:Interface Monitor counters and flags are set to 0.
                                                                    1:Enable all Interface Monitors. */
        unsigned int  reserved                  : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_DEBUG_CTRL_UNION;
#endif
#define SOC_CCI500_DEBUG_CTRL_enable_interface_monitors_START  (0)
#define SOC_CCI500_DEBUG_CTRL_enable_interface_monitors_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID4_UNION
 �ṹ˵��  : PERIPHERAL_ID4 �Ĵ����ṹ���塣��ַƫ����:0x00FD0����ֵ:0x00000084�����:32
 �Ĵ���˵��: ����ID�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id4_1 : 4;  /* bit[0-3] : JEP106 continuation code for ARM. */
        unsigned int  peri_id4_2 : 4;  /* bit[4-7] : 4KB region count. */
        unsigned int  reserved   : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID4_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID4_peri_id4_1_START  (0)
#define SOC_CCI500_PERIPHERAL_ID4_peri_id4_1_END    (3)
#define SOC_CCI500_PERIPHERAL_ID4_peri_id4_2_START  (4)
#define SOC_CCI500_PERIPHERAL_ID4_peri_id4_2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID5_UNION
 �ṹ˵��  : PERIPHERAL_ID5 �Ĵ����ṹ���塣��ַƫ����:0x00FD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id5 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID5_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID5_peri_id5_START  (0)
#define SOC_CCI500_PERIPHERAL_ID5_peri_id5_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID6_UNION
 �ṹ˵��  : PERIPHERAL_ID6 �Ĵ����ṹ���塣��ַƫ����:0x00FD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id6 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID6_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID6_peri_id6_START  (0)
#define SOC_CCI500_PERIPHERAL_ID6_peri_id6_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID7_UNION
 �ṹ˵��  : PERIPHERAL_ID7 �Ĵ����ṹ���塣��ַƫ����:0x00FDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id7 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID7_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID7_peri_id7_START  (0)
#define SOC_CCI500_PERIPHERAL_ID7_peri_id7_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID0_UNION
 �ṹ˵��  : PERIPHERAL_ID0 �Ĵ����ṹ���塣��ַƫ����:0x00FE0����ֵ:0x00000022�����:32
 �Ĵ���˵��: ����ID�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id0 : 8;  /* bit[0-7] : Part number[7:0]. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID0_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID0_peri_id0_START  (0)
#define SOC_CCI500_PERIPHERAL_ID0_peri_id0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID1_UNION
 �ṹ˵��  : PERIPHERAL_ID1 �Ĵ����ṹ���塣��ַƫ����:0x00FE4����ֵ:0x000000B4�����:32
 �Ĵ���˵��: ����ID�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id1_num : 4;  /* bit[0-3] : Part number[11:8]. */
        unsigned int  jep106_id_l  : 4;  /* bit[4-7] : JEP106 ID code[3:0] for ARM */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID1_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID1_peri_id1_num_START  (0)
#define SOC_CCI500_PERIPHERAL_ID1_peri_id1_num_END    (3)
#define SOC_CCI500_PERIPHERAL_ID1_jep106_id_l_START   (4)
#define SOC_CCI500_PERIPHERAL_ID1_jep106_id_l_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID2_UNION
 �ṹ˵��  : PERIPHERAL_ID2 �Ĵ����ṹ���塣��ַƫ����:0x00FE8����ֵ:0x0000001B�����:32
 �Ĵ���˵��: ����ID�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jep106_id_h  : 3;  /* bit[0-2] : JEP106 ID code[6:4] for ARM. */
        unsigned int  manu_id_code : 1;  /* bit[3]   : IC uses a manufacturer's identity code allocated by JEDEC according to the JEP106. */
        unsigned int  ccr_rev      : 4;  /* bit[4-7] : CCI-500 revision. */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID2_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID2_jep106_id_h_START   (0)
#define SOC_CCI500_PERIPHERAL_ID2_jep106_id_h_END     (2)
#define SOC_CCI500_PERIPHERAL_ID2_manu_id_code_START  (3)
#define SOC_CCI500_PERIPHERAL_ID2_manu_id_code_END    (3)
#define SOC_CCI500_PERIPHERAL_ID2_ccr_rev_START       (4)
#define SOC_CCI500_PERIPHERAL_ID2_ccr_rev_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_PERIPHERAL_ID3_UNION
 �ṹ˵��  : PERIPHERAL_ID3 �Ĵ����ṹ���塣��ַƫ����:0x00FEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_num  : 4;  /* bit[0-3] : Customer modification number */
        unsigned int  eco_num  : 4;  /* bit[4-7] : ARM approved ECO number. Use the ECOREVNUM inputs to modify this value. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_PERIPHERAL_ID3_UNION;
#endif
#define SOC_CCI500_PERIPHERAL_ID3_mod_num_START   (0)
#define SOC_CCI500_PERIPHERAL_ID3_mod_num_END     (3)
#define SOC_CCI500_PERIPHERAL_ID3_eco_num_START   (4)
#define SOC_CCI500_PERIPHERAL_ID3_eco_num_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_COMPONENT_ID0_UNION
 �ṹ˵��  : COMPONENT_ID0 �Ĵ����ṹ���塣��ַƫ����:0x00FF0����ֵ:0x0000000D�����:32
 �Ĵ���˵��: ���ID�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id0 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_COMPONENT_ID0_UNION;
#endif
#define SOC_CCI500_COMPONENT_ID0_component_id0_START  (0)
#define SOC_CCI500_COMPONENT_ID0_component_id0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_COMPONENT_ID1_UNION
 �ṹ˵��  : COMPONENT_ID1 �Ĵ����ṹ���塣��ַƫ����:0x00FF4����ֵ:0x000000F0�����:32
 �Ĵ���˵��: ���ID�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id1 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_COMPONENT_ID1_UNION;
#endif
#define SOC_CCI500_COMPONENT_ID1_component_id1_START  (0)
#define SOC_CCI500_COMPONENT_ID1_component_id1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_COMPONENT_ID2_UNION
 �ṹ˵��  : COMPONENT_ID2 �Ĵ����ṹ���塣��ַƫ����:0x00FF8����ֵ:0x00000005�����:32
 �Ĵ���˵��: ���ID�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id2 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_COMPONENT_ID2_UNION;
#endif
#define SOC_CCI500_COMPONENT_ID2_component_id2_START  (0)
#define SOC_CCI500_COMPONENT_ID2_component_id2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_COMPONENT_ID3_UNION
 �ṹ˵��  : COMPONENT_ID3 �Ĵ����ṹ���塣��ַƫ����:0x00FFC����ֵ:0x000000B1�����:32
 �Ĵ���˵��: ���ID�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id3 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI500_COMPONENT_ID3_UNION;
#endif
#define SOC_CCI500_COMPONENT_ID3_component_id3_START  (0)
#define SOC_CCI500_COMPONENT_ID3_component_id3_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SNOOP_CTRL_S0_UNION
 �ṹ˵��  : SNOOP_CTRL_S0 �Ĵ����ṹ���塣��ַƫ����:0x01000����ֵ:0xC0000000�����:32
 �Ĵ���˵��: S0 snoop���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : When the slave interface supports snoops, enables issuing of snoop requests from this slave interface:
                                                        0:Disable snoop requests.
                                                        1:Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : When the slave interface supports DVM messages, enables issuing of DVM message requests from this slave interface:
                                                        0:Disable DVM message requests.
                                                        1:Enable DVM message requests. */
        unsigned int  reserved      : 28; /* bit[2-29]: Reserved. */
        unsigned int  snoop_support : 1;  /* bit[30]  : Indicates whether the slave interface supports snoop requests.
                                                        0:The interface does not support snoops.
                                                        1:The interface supports snoops. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Indicates whether the slave interface supports DVM messages.
                                                        0:The interface does not support DVM messages.
                                                        1:The interface supports DVM messages. */
    } reg;
} SOC_CCI500_SNOOP_CTRL_S0_UNION;
#endif
#define SOC_CCI500_SNOOP_CTRL_S0_snoop_en_START       (0)
#define SOC_CCI500_SNOOP_CTRL_S0_snoop_en_END         (0)
#define SOC_CCI500_SNOOP_CTRL_S0_dvm_en_START         (1)
#define SOC_CCI500_SNOOP_CTRL_S0_dvm_en_END           (1)
#define SOC_CCI500_SNOOP_CTRL_S0_snoop_support_START  (30)
#define SOC_CCI500_SNOOP_CTRL_S0_snoop_support_END    (30)
#define SOC_CCI500_SNOOP_CTRL_S0_dvm_support_START    (31)
#define SOC_CCI500_SNOOP_CTRL_S0_dvm_support_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SHARE_OVR_S0_UNION
 �ṹ˵��  : SHARE_OVR_S0 �Ĵ����ṹ���塣��ַƫ����:0x01004����ֵ:0x00000000�����:32
 �Ĵ���˵��: S0 shareable override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shareable_override : 2;  /* bit[0-1] : Shareable override for slave interface:
                                                             0b00:Do not override AxDOMAIN inputs.
                                                             0b01:Do not override AxDOMAIN inputs.
                                                             0b10:Override AxDOMAIN inputs to 0b00, meaning that all
                                                             transactions are treated as Non-shareable.
                                                             0b11:Override AxDOMAIN inputs to 0b01, meaning that all Normal transactions are treated as Shareable. */
        unsigned int  reserved           : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI500_SHARE_OVR_S0_UNION;
#endif
#define SOC_CCI500_SHARE_OVR_S0_shareable_override_START  (0)
#define SOC_CCI500_SHARE_OVR_S0_shareable_override_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ARQOS_OVR_S0_UNION
 �ṹ˵��  : ARQOS_OVR_S0 �Ĵ����ṹ���塣��ַƫ����:0x01100����ֵ:0x00000000�����:32
 �Ĵ���˵��: S0��ͨ��QoS override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qv_max               : 4;  /* bit[0-3]  : Maximum value for ARQOS.
                                                                This value is the override value if QoS regulation is not enabled. */
        unsigned int  qv_min               : 4;  /* bit[4-7]  : Minimum value for ARQOS.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : Reserved */
        unsigned int  bandwidth_allocation : 4;  /* bit[16-19]: Bandwidth allocation in bytes per cycle.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_1           : 4;  /* bit[20-23]: Reserved */
        unsigned int  excess_bytes_per_qv  : 3;  /* bit[24-26]: Excess bytes permitted per QoS value.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_2           : 4;  /* bit[27-30]: Reserved */
        unsigned int  reg_enable           : 1;  /* bit[31]   : Enable dynamic QoS value override.
                                                                This bit is WI if the implementation does not include QoS regulators on the corresponding interface.
                                                                If this bit is not set, qv_max is used as the override value. */
    } reg;
} SOC_CCI500_ARQOS_OVR_S0_UNION;
#endif
#define SOC_CCI500_ARQOS_OVR_S0_qv_max_START                (0)
#define SOC_CCI500_ARQOS_OVR_S0_qv_max_END                  (3)
#define SOC_CCI500_ARQOS_OVR_S0_qv_min_START                (4)
#define SOC_CCI500_ARQOS_OVR_S0_qv_min_END                  (7)
#define SOC_CCI500_ARQOS_OVR_S0_bandwidth_allocation_START  (16)
#define SOC_CCI500_ARQOS_OVR_S0_bandwidth_allocation_END    (19)
#define SOC_CCI500_ARQOS_OVR_S0_excess_bytes_per_qv_START   (24)
#define SOC_CCI500_ARQOS_OVR_S0_excess_bytes_per_qv_END     (26)
#define SOC_CCI500_ARQOS_OVR_S0_reg_enable_START            (31)
#define SOC_CCI500_ARQOS_OVR_S0_reg_enable_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_AWQOS_OVR_S0_UNION
 �ṹ˵��  : AWQOS_OVR_S0 �Ĵ����ṹ���塣��ַƫ����:0x01104����ֵ:0x00000000�����:32
 �Ĵ���˵��: S0дͨ��QoS override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qv_max               : 4;  /* bit[0-3]  : Maximum value for AWQOS.
                                                                This value is the override value if QoS regulation is not enabled. */
        unsigned int  qv_min               : 4;  /* bit[4-7]  : Minimum value for AWQOS.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : Reserved */
        unsigned int  bandwidth_allocation : 4;  /* bit[16-19]: Bandwidth allocation in bytes per cycle.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_1           : 4;  /* bit[20-23]: Reserved */
        unsigned int  excess_bytes_per_qv  : 3;  /* bit[24-26]: Excess bytes permitted per QoS value.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_2           : 4;  /* bit[27-30]: Reserved */
        unsigned int  reg_enable           : 1;  /* bit[31]   : Enable dynamic QoS value override.
                                                                This bit is WI if the implementation does not include QoS regulators on the corresponding interface.
                                                                If this bit is not set, qv_max is used as the override value. */
    } reg;
} SOC_CCI500_AWQOS_OVR_S0_UNION;
#endif
#define SOC_CCI500_AWQOS_OVR_S0_qv_max_START                (0)
#define SOC_CCI500_AWQOS_OVR_S0_qv_max_END                  (3)
#define SOC_CCI500_AWQOS_OVR_S0_qv_min_START                (4)
#define SOC_CCI500_AWQOS_OVR_S0_qv_min_END                  (7)
#define SOC_CCI500_AWQOS_OVR_S0_bandwidth_allocation_START  (16)
#define SOC_CCI500_AWQOS_OVR_S0_bandwidth_allocation_END    (19)
#define SOC_CCI500_AWQOS_OVR_S0_excess_bytes_per_qv_START   (24)
#define SOC_CCI500_AWQOS_OVR_S0_excess_bytes_per_qv_END     (26)
#define SOC_CCI500_AWQOS_OVR_S0_reg_enable_START            (31)
#define SOC_CCI500_AWQOS_OVR_S0_reg_enable_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_QOS_MAX_OT_S0_UNION
 �ṹ˵��  : QOS_MAX_OT_S0 �Ĵ����ṹ���塣��ַƫ����:0x01110����ֵ:0x00000030�����:32
 �Ĵ���˵��: S0���OT�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_ot   : 8;  /* bit[0-7] : The maximum number of OTs for the interface. This is a combined issuing limit. It represents the maximum number of transactions that the upstream master can issue when the AR and AW channels are considered as one issuing source. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved. */
    } reg;
} SOC_CCI500_QOS_MAX_OT_S0_UNION;
#endif
#define SOC_CCI500_QOS_MAX_OT_S0_max_ot_START    (0)
#define SOC_CCI500_QOS_MAX_OT_S0_max_ot_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SNOOP_CTRL_S1_UNION
 �ṹ˵��  : SNOOP_CTRL_S1 �Ĵ����ṹ���塣��ַƫ����:0x02000����ֵ:0xC0000000�����:32
 �Ĵ���˵��: S1 snoop���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : When the slave interface supports snoops, enables issuing of snoop requests from this slave interface:
                                                        0:Disable snoop requests.
                                                        1:Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : When the slave interface supports DVM messages, enables issuing of DVM message requests from this slave interface:
                                                        0:Disable DVM message requests.
                                                        1:Enable DVM message requests. */
        unsigned int  reserved      : 28; /* bit[2-29]: Reserved */
        unsigned int  snoop_support : 1;  /* bit[30]  : Indicates whether the slave interface supports snoop requests.
                                                        0:The interface does not support snoops.
                                                        1:The interface supports snoops. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Indicates whether the slave interface supports DVM messages.
                                                        0:The interface does not support DVM messages.
                                                        1:The interface supports DVM messages. */
    } reg;
} SOC_CCI500_SNOOP_CTRL_S1_UNION;
#endif
#define SOC_CCI500_SNOOP_CTRL_S1_snoop_en_START       (0)
#define SOC_CCI500_SNOOP_CTRL_S1_snoop_en_END         (0)
#define SOC_CCI500_SNOOP_CTRL_S1_dvm_en_START         (1)
#define SOC_CCI500_SNOOP_CTRL_S1_dvm_en_END           (1)
#define SOC_CCI500_SNOOP_CTRL_S1_snoop_support_START  (30)
#define SOC_CCI500_SNOOP_CTRL_S1_snoop_support_END    (30)
#define SOC_CCI500_SNOOP_CTRL_S1_dvm_support_START    (31)
#define SOC_CCI500_SNOOP_CTRL_S1_dvm_support_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SHARE_OVR_S1_UNION
 �ṹ˵��  : SHARE_OVR_S1 �Ĵ����ṹ���塣��ַƫ����:0x02004����ֵ:0x00000000�����:32
 �Ĵ���˵��: S1 shareable override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shareable_override : 2;  /* bit[0-1] : Shareable override for slave interface:
                                                             0b00:Do not override AxDOMAIN inputs.
                                                             0b01:Do not override AxDOMAIN inputs.
                                                             0b10:Override AxDOMAIN inputs to 0b00, meaning that all
                                                             transactions are treated as Non-shareable.
                                                             0b11:Override AxDOMAIN inputs to 0b01, meaning that all Normal transactions are treated as Shareable. */
        unsigned int  reserved           : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI500_SHARE_OVR_S1_UNION;
#endif
#define SOC_CCI500_SHARE_OVR_S1_shareable_override_START  (0)
#define SOC_CCI500_SHARE_OVR_S1_shareable_override_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ARQOS_OVR_S1_UNION
 �ṹ˵��  : ARQOS_OVR_S1 �Ĵ����ṹ���塣��ַƫ����:0x02100����ֵ:0x00000000�����:32
 �Ĵ���˵��: S1��ͨ��QoS override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qv_max               : 4;  /* bit[0-3]  : Maximum value for ARQOS.
                                                                This value is the override value if QoS regulation is not enabled. */
        unsigned int  qv_min               : 4;  /* bit[4-7]  : Minimum value for ARQOS.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : Reserved */
        unsigned int  bandwidth_allocation : 4;  /* bit[16-19]: Bandwidth allocation in bytes per cycle.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_1           : 4;  /* bit[20-23]: Reserved */
        unsigned int  excess_bytes_per_qv  : 3;  /* bit[24-26]: Excess bytes permitted per QoS value.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_2           : 4;  /* bit[27-30]: Reserved */
        unsigned int  reg_enable           : 1;  /* bit[31]   : Enable dynamic QoS value override.
                                                                This bit is WI if the implementation does not include QoS regulators on the corresponding interface.
                                                                If this bit is not set, qv_max is used as the override value. */
    } reg;
} SOC_CCI500_ARQOS_OVR_S1_UNION;
#endif
#define SOC_CCI500_ARQOS_OVR_S1_qv_max_START                (0)
#define SOC_CCI500_ARQOS_OVR_S1_qv_max_END                  (3)
#define SOC_CCI500_ARQOS_OVR_S1_qv_min_START                (4)
#define SOC_CCI500_ARQOS_OVR_S1_qv_min_END                  (7)
#define SOC_CCI500_ARQOS_OVR_S1_bandwidth_allocation_START  (16)
#define SOC_CCI500_ARQOS_OVR_S1_bandwidth_allocation_END    (19)
#define SOC_CCI500_ARQOS_OVR_S1_excess_bytes_per_qv_START   (24)
#define SOC_CCI500_ARQOS_OVR_S1_excess_bytes_per_qv_END     (26)
#define SOC_CCI500_ARQOS_OVR_S1_reg_enable_START            (31)
#define SOC_CCI500_ARQOS_OVR_S1_reg_enable_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_AWQOS_OVR_S1_UNION
 �ṹ˵��  : AWQOS_OVR_S1 �Ĵ����ṹ���塣��ַƫ����:0x02104����ֵ:0x00000000�����:32
 �Ĵ���˵��: S1дͨ��QoS override�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qv_max               : 4;  /* bit[0-3]  : Maximum value for AWQOS.
                                                                This value is the override value if QoS regulation is not enabled. */
        unsigned int  qv_min               : 4;  /* bit[4-7]  : Minimum value for AWQOS.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : Reserved */
        unsigned int  bandwidth_allocation : 4;  /* bit[16-19]: Bandwidth allocation in bytes per cycle.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_1           : 4;  /* bit[20-23]: Reserved */
        unsigned int  excess_bytes_per_qv  : 3;  /* bit[24-26]: Excess bytes permitted per QoS value.
                                                                These bits are WI if the implementation does not include QoS regulators on the corresponding interface. */
        unsigned int  reserved_2           : 4;  /* bit[27-30]: Reserved */
        unsigned int  reg_enable           : 1;  /* bit[31]   : Enable dynamic QoS value override.
                                                                This bit is WI if the implementation does not include QoS regulators on the corresponding interface.
                                                                If this bit is not set, qv_max is used as the override value. */
    } reg;
} SOC_CCI500_AWQOS_OVR_S1_UNION;
#endif
#define SOC_CCI500_AWQOS_OVR_S1_qv_max_START                (0)
#define SOC_CCI500_AWQOS_OVR_S1_qv_max_END                  (3)
#define SOC_CCI500_AWQOS_OVR_S1_qv_min_START                (4)
#define SOC_CCI500_AWQOS_OVR_S1_qv_min_END                  (7)
#define SOC_CCI500_AWQOS_OVR_S1_bandwidth_allocation_START  (16)
#define SOC_CCI500_AWQOS_OVR_S1_bandwidth_allocation_END    (19)
#define SOC_CCI500_AWQOS_OVR_S1_excess_bytes_per_qv_START   (24)
#define SOC_CCI500_AWQOS_OVR_S1_excess_bytes_per_qv_END     (26)
#define SOC_CCI500_AWQOS_OVR_S1_reg_enable_START            (31)
#define SOC_CCI500_AWQOS_OVR_S1_reg_enable_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_QOS_MAX_OT_31_UNION
 �ṹ˵��  : QOS_MAX_OT_31 �Ĵ����ṹ���塣��ַƫ����:0x02110����ֵ:0x00000030�����:32
 �Ĵ���˵��: S1���OT�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_ot   : 8;  /* bit[0-7] : The maximum number of OTs for the interface. This is a combined issuing limit. It represents the maximum number of transactions that the upstream master can issue when the AR and AW channels are considered as one issuing source. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved. */
    } reg;
} SOC_CCI500_QOS_MAX_OT_31_UNION;
#endif
#define SOC_CCI500_QOS_MAX_OT_31_max_ot_START    (0)
#define SOC_CCI500_QOS_MAX_OT_31_max_ot_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_0_UNION
 �ṹ˵��  : EVNT_SEL_0 �Ĵ����ṹ���塣��ַƫ����:0x10000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 0�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_0_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_0_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_0_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_0_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_0_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_0_UNION
 �ṹ˵��  : ECNT_DATA_0 �Ĵ����ṹ���塣��ַƫ����:0x10004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 0�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_0_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_0_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_0_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_0_UNION
 �ṹ˵��  : ECNT_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x10008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 0�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_0_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_0_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_0_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_0_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_0 �Ĵ����ṹ���塣��ַƫ����:0x1000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 0�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_0_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_0_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_0_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_1_UNION
 �ṹ˵��  : EVNT_SEL_1 �Ĵ����ṹ���塣��ַƫ����:0x20000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 1�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_1_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_1_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_1_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_1_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_1_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_1_UNION
 �ṹ˵��  : ECNT_DATA_1 �Ĵ����ṹ���塣��ַƫ����:0x20004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 1�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_1_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_1_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_1_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_1_UNION
 �ṹ˵��  : ECNT_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x20008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 1�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_1_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_1_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_1_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_1_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_1 �Ĵ����ṹ���塣��ַƫ����:0x2000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 1�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_1_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_1_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_1_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_2_UNION
 �ṹ˵��  : EVNT_SEL_2 �Ĵ����ṹ���塣��ַƫ����:0x30000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 2�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_2_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_2_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_2_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_2_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_2_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_2_UNION
 �ṹ˵��  : ECNT_DATA_2 �Ĵ����ṹ���塣��ַƫ����:0x30004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 2�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_2_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_2_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_2_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_2_UNION
 �ṹ˵��  : ECNT_CTRL_2 �Ĵ����ṹ���塣��ַƫ����:0x30008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 2�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_2_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_2_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_2_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_2_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_2 �Ĵ����ṹ���塣��ַƫ����:0x3000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 2�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_2_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_2_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_2_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_3_UNION
 �ṹ˵��  : EVNT_SEL_3 �Ĵ����ṹ���塣��ַƫ����:0x40000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 3�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_3_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_3_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_3_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_3_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_3_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_3_UNION
 �ṹ˵��  : ECNT_DATA_3 �Ĵ����ṹ���塣��ַƫ����:0x40004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 3�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_3_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_3_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_3_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_3_UNION
 �ṹ˵��  : ECNT_CTRL_3 �Ĵ����ṹ���塣��ַƫ����:0x40008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 3�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_3_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_3_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_3_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_3_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_3 �Ĵ����ṹ���塣��ַƫ����:0x4000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 3�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_3_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_3_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_3_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_4_UNION
 �ṹ˵��  : EVNT_SEL_4 �Ĵ����ṹ���塣��ַƫ����:0x50000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 4�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_4_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_4_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_4_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_4_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_4_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_4_UNION
 �ṹ˵��  : ECNT_DATA_4 �Ĵ����ṹ���塣��ַƫ����:0x50004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 4�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_4_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_4_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_4_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_4_UNION
 �ṹ˵��  : ECNT_CTRL_4 �Ĵ����ṹ���塣��ַƫ����:0x50008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 4�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_4_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_4_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_4_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_4_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_4 �Ĵ����ṹ���塣��ַƫ����:0x5000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 4�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_4_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_4_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_4_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_5_UNION
 �ṹ˵��  : EVNT_SEL_5 �Ĵ����ṹ���塣��ַƫ����:0x60000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 5�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_5_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_5_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_5_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_5_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_5_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_5_UNION
 �ṹ˵��  : ECNT_DATA_5 �Ĵ����ṹ���塣��ַƫ����:0x60004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 5�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_5_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_5_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_5_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_5_UNION
 �ṹ˵��  : ECNT_CTRL_5 �Ĵ����ṹ���塣��ַƫ����:0x60008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 5�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_5_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_5_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_5_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_5_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_5 �Ĵ����ṹ���塣��ַƫ����:0x6000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 5�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_5_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_5_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_5_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_6_UNION
 �ṹ˵��  : EVNT_SEL_6 �Ĵ����ṹ���塣��ַƫ����:0x70000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 6�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_6_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_6_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_6_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_6_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_6_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_6_UNION
 �ṹ˵��  : ECNT_DATA_6 �Ĵ����ṹ���塣��ַƫ����:0x70004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 6�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_6_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_6_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_6_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_6_UNION
 �ṹ˵��  : ECNT_CTRL_6 �Ĵ����ṹ���塣��ַƫ����:0x70008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 6�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_6_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_6_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_6_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_6_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_6 �Ĵ����ṹ���塣��ַƫ����:0x7000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 6�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_6_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_6_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_6_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_EVNT_SEL_7_UNION
 �ṹ˵��  : EVNT_SEL_7 �Ĵ����ṹ���塣��ַƫ����:0x80000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 7�¼�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mon_evtx : 5;  /* bit[0-4] : Event code that defines the event to monitor. */
        unsigned int  mon_intx : 4;  /* bit[5-8] : Event code that defines the interface to monitor. */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved. */
    } reg;
} SOC_CCI500_EVNT_SEL_7_UNION;
#endif
#define SOC_CCI500_EVNT_SEL_7_mon_evtx_START  (0)
#define SOC_CCI500_EVNT_SEL_7_mon_evtx_END    (4)
#define SOC_CCI500_EVNT_SEL_7_mon_intx_START  (5)
#define SOC_CCI500_EVNT_SEL_7_mon_intx_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_DATA_7_UNION
 �ṹ˵��  : ECNT_DATA_7 �Ĵ����ṹ���塣��ַƫ����:0x80004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 7�¼������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter : 32; /* bit[0-31]: one for each of the eight corresponding event counters. */
    } reg;
} SOC_CCI500_ECNT_DATA_7_UNION;
#endif
#define SOC_CCI500_ECNT_DATA_7_counter_START  (0)
#define SOC_CCI500_ECNT_DATA_7_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CTRL_7_UNION
 �ṹ˵��  : ECNT_CTRL_7 �Ĵ����ṹ���塣��ַƫ����:0x80008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 7�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counter_enable : 1;  /* bit[0]   : Counter enable:
                                                         0:Counter disabled.
                                                         1:Counter enabled. */
        unsigned int  reserved       : 31; /* bit[1-31]: Reserved. */
    } reg;
} SOC_CCI500_ECNT_CTRL_7_UNION;
#endif
#define SOC_CCI500_ECNT_CTRL_7_counter_enable_START  (0)
#define SOC_CCI500_ECNT_CTRL_7_counter_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_ECNT_CLR_OVFL_7_UNION
 �ṹ˵��  : ECNT_CLR_OVFL_7 �Ĵ����ṹ���塣��ַƫ����:0x8000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Performance counter 7�����־״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_counter : 1;  /* bit[0]   : Event counter overflow flag:
                                                        0:The counter has not overflowed.
                                                        1:The counter has overflowed. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI500_ECNT_CLR_OVFL_7_UNION;
#endif
#define SOC_CCI500_ECNT_CLR_OVFL_7_event_counter_START  (0)
#define SOC_CCI500_ECNT_CLR_OVFL_7_event_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SLAVE_DEBUG_0_UNION
 �ṹ˵��  : SLAVE_DEBUG_0 �Ĵ����ṹ���塣��ַƫ����:0x90000����ֵ:0x00000000�����:32
 �Ĵ���˵��: slave 0 debug�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stalled_ar_channel : 1;  /* bit[0]    : When this bit is set to 1, a transfer is stalled on the AR channel, where both:
                                                              ? ARVALID is HIGH.
                                                              ? ARREADY is LOW. */
        unsigned int  stalled_r_channel  : 1;  /* bit[1]    : When this bit is set to 1, a transfer is stalled on the R channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_aw_channel : 1;  /* bit[2]    : When this bit is set to 1, a transfer is stalled on the AW channel, where both:
                                                              ? AWVALID is HIGH.
                                                              ? AWREADY is LOW. */
        unsigned int  stalled_w_channel  : 1;  /* bit[3]    : When this bit is set to 1, a transfer is stalled on the W channel, where both:
                                                              ? WVALID is HIGH.
                                                              ? WREADY is LOW. */
        unsigned int  stalled_b_channel  : 1;  /* bit[4]    : When this bit is set to 1, a transfer is stalled on the B channel, where both:
                                                              ? BVALID is HIGH.
                                                              ? BREADY is LOW. */
        unsigned int  stalled_ac_channel : 1;  /* bit[5]    : When this bit is set to 1, a transfer is stalled on the AC channel, where both:
                                                              ? ACVALID is HIGH.
                                                              ? ACREADY is LOW. */
        unsigned int  stalled_cr_channel : 1;  /* bit[6]    : When this bit is set to 1, a transfer is stalled on the CR channel, where both:
                                                              ? CRVALID is HIGH.
                                                              ? CRREADY is LOW. */
        unsigned int  stalled_cd_channel : 1;  /* bit[7]    : When this bit is set to 1, a transfer is stalled on the CD channel, where both:
                                                              ? CDVALID is HIGH.
                                                              ? CDREADY is LOW. */
        unsigned int  outstanding_reads  : 8;  /* bit[8-15] : Number of outstanding read transactions. From request
                                                              handshake to response for ACE-Lite interfaces, or RACK for ACE interfaces. */
        unsigned int  outstanding_writes : 8;  /* bit[16-23]: Number of outstanding write transactions. From request
                                                              handshake to response for ACE-Lite interfaces, or WACK for ACE interfaces. */
        unsigned int  outstanding_snoops : 8;  /* bit[24-31]: Number of outstanding snoop requests or DVM messages.
                                                              From request handshake to response or snoop data for a hit. */
    } reg;
} SOC_CCI500_SLAVE_DEBUG_0_UNION;
#endif
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_ar_channel_START  (0)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_ar_channel_END    (0)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_r_channel_START   (1)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_r_channel_END     (1)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_aw_channel_START  (2)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_aw_channel_END    (2)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_w_channel_START   (3)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_w_channel_END     (3)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_b_channel_START   (4)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_b_channel_END     (4)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_ac_channel_START  (5)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_ac_channel_END    (5)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_cr_channel_START  (6)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_cr_channel_END    (6)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_cd_channel_START  (7)
#define SOC_CCI500_SLAVE_DEBUG_0_stalled_cd_channel_END    (7)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_reads_START   (8)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_reads_END     (15)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_writes_START  (16)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_writes_END    (23)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_snoops_START  (24)
#define SOC_CCI500_SLAVE_DEBUG_0_outstanding_snoops_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_SLAVE_DEBUG_1_UNION
 �ṹ˵��  : SLAVE_DEBUG_1 �Ĵ����ṹ���塣��ַƫ����:0x90004����ֵ:0x00000000�����:32
 �Ĵ���˵��: slave 1 debug�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stalled_ar_channel : 1;  /* bit[0]    : When this bit is set to 1, a transfer is stalled on the AR channel, where both:
                                                              ? ARVALID is HIGH.
                                                              ? ARREADY is LOW. */
        unsigned int  stalled_r_channel  : 1;  /* bit[1]    : When this bit is set to 1, a transfer is stalled on the R channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_aw_channel : 1;  /* bit[2]    : When this bit is set to 1, a transfer is stalled on the AW channel, where both:
                                                              ? AWVALID is HIGH.
                                                              ? AWREADY is LOW. */
        unsigned int  stalled_w_channel  : 1;  /* bit[3]    : When this bit is set to 1, a transfer is stalled on the W channel, where both:
                                                              ? WVALID is HIGH.
                                                              ? WREADY is LOW. */
        unsigned int  stalled_b_channel  : 1;  /* bit[4]    : When this bit is set to 1, a transfer is stalled on the B channel, where both:
                                                              ? BVALID is HIGH.
                                                              ? BREADY is LOW. */
        unsigned int  stalled_ac_channel : 1;  /* bit[5]    : When this bit is set to 1, a transfer is stalled on the AC channel, where both:
                                                              ? ACVALID is HIGH.
                                                              ? ACREADY is LOW. */
        unsigned int  stalled_cr_channel : 1;  /* bit[6]    : When this bit is set to 1, a transfer is stalled on the CR channel, where both:
                                                              ? CRVALID is HIGH.
                                                              ? CRREADY is LOW. */
        unsigned int  stalled_cd_channel : 1;  /* bit[7]    : When this bit is set to 1, a transfer is stalled on the CD channel, where both:
                                                              ? CDVALID is HIGH.
                                                              ? CDREADY is LOW. */
        unsigned int  outstanding_reads  : 8;  /* bit[8-15] : Number of outstanding read transactions. From request
                                                              handshake to response for ACE-Lite interfaces, or RACK for ACE interfaces. */
        unsigned int  outstanding_writes : 8;  /* bit[16-23]: Number of outstanding write transactions. From request
                                                              handshake to response for ACE-Lite interfaces, or WACK for ACE interfaces. */
        unsigned int  outstanding_snoops : 8;  /* bit[24-31]: Number of outstanding snoop requests or DVM messages.
                                                              From request handshake to response or snoop data for a hit. */
    } reg;
} SOC_CCI500_SLAVE_DEBUG_1_UNION;
#endif
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_ar_channel_START  (0)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_ar_channel_END    (0)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_r_channel_START   (1)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_r_channel_END     (1)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_aw_channel_START  (2)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_aw_channel_END    (2)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_w_channel_START   (3)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_w_channel_END     (3)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_b_channel_START   (4)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_b_channel_END     (4)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_ac_channel_START  (5)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_ac_channel_END    (5)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_cr_channel_START  (6)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_cr_channel_END    (6)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_cd_channel_START  (7)
#define SOC_CCI500_SLAVE_DEBUG_1_stalled_cd_channel_END    (7)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_reads_START   (8)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_reads_END     (15)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_writes_START  (16)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_writes_END    (23)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_snoops_START  (24)
#define SOC_CCI500_SLAVE_DEBUG_1_outstanding_snoops_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_MASTER_DEBUG_0_UNION
 �ṹ˵��  : MASTER_DEBUG_0 �Ĵ����ṹ���塣��ַƫ����:0x90100����ֵ:0x00000000�����:32
 �Ĵ���˵��: master 0 debug�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stalled_ar_channel : 1;  /* bit[0]    : When this bit is set to 1, a transfer is stalled on the AR channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_r_channel  : 1;  /* bit[1]    : When this bit is set to 1, a transfer is stalled on the R channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_aw_channel : 1;  /* bit[2]    : When this bit is set to 1, a transfer is stalled on the AW channel, where both:
                                                              ? AWVALID is HIGH.
                                                              ? AWREADY is LOW. */
        unsigned int  stalled_w_channel  : 1;  /* bit[3]    : When this bit is set to 1, a transfer is stalled on the W channel, where both:
                                                              ? WVALID is HIGH.
                                                              ? WREADY is LOW. */
        unsigned int  stalled_b_channel  : 1;  /* bit[4]    : When this bit is set to 1, a transfer is stalled on the B channel, where:
                                                              ? BVALID is HIGH.
                                                              ? BREADY is LOW. */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : reserved */
        unsigned int  outstanding_reads  : 8;  /* bit[8-15] : Number of outstanding read transactions. From request
                                                              handshake to response. */
        unsigned int  outstanding_writes : 8;  /* bit[16-23]: Number of outstanding write transactions. From request
                                                              handshake to response. */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_CCI500_MASTER_DEBUG_0_UNION;
#endif
#define SOC_CCI500_MASTER_DEBUG_0_stalled_ar_channel_START  (0)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_ar_channel_END    (0)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_r_channel_START   (1)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_r_channel_END     (1)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_aw_channel_START  (2)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_aw_channel_END    (2)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_w_channel_START   (3)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_w_channel_END     (3)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_b_channel_START   (4)
#define SOC_CCI500_MASTER_DEBUG_0_stalled_b_channel_END     (4)
#define SOC_CCI500_MASTER_DEBUG_0_outstanding_reads_START   (8)
#define SOC_CCI500_MASTER_DEBUG_0_outstanding_reads_END     (15)
#define SOC_CCI500_MASTER_DEBUG_0_outstanding_writes_START  (16)
#define SOC_CCI500_MASTER_DEBUG_0_outstanding_writes_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_CCI500_MASTER_DEBUG_1_UNION
 �ṹ˵��  : MASTER_DEBUG_1 �Ĵ����ṹ���塣��ַƫ����:0x90104����ֵ:0x00000000�����:32
 �Ĵ���˵��: master 1 debug�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stalled_ar_channel : 1;  /* bit[0]    : When this bit is set to 1, a transfer is stalled on the AR channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_r_channel  : 1;  /* bit[1]    : When this bit is set to 1, a transfer is stalled on the R channel, where both:
                                                              ? RVALID is HIGH.
                                                              ? RREADY is LOW. */
        unsigned int  stalled_aw_channel : 1;  /* bit[2]    : When this bit is set to 1, a transfer is stalled on the AW channel, where both:
                                                              ? AWVALID is HIGH.
                                                              ? AWREADY is LOW. */
        unsigned int  stalled_w_channel  : 1;  /* bit[3]    : When this bit is set to 1, a transfer is stalled on the W channel, where both:
                                                              ? WVALID is HIGH.
                                                              ? WREADY is LOW. */
        unsigned int  stalled_b_channel  : 1;  /* bit[4]    : When this bit is set to 1, a transfer is stalled on the B channel, where:
                                                              ? BVALID is HIGH.
                                                              ? BREADY is LOW. */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : reserved */
        unsigned int  outstanding_reads  : 8;  /* bit[8-15] : Number of outstanding read transactions. From request
                                                              handshake to response. */
        unsigned int  outstanding_writes : 8;  /* bit[16-23]: Number of outstanding write transactions. From request
                                                              handshake to response. */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_CCI500_MASTER_DEBUG_1_UNION;
#endif
#define SOC_CCI500_MASTER_DEBUG_1_stalled_ar_channel_START  (0)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_ar_channel_END    (0)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_r_channel_START   (1)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_r_channel_END     (1)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_aw_channel_START  (2)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_aw_channel_END    (2)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_w_channel_START   (3)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_w_channel_END     (3)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_b_channel_START   (4)
#define SOC_CCI500_MASTER_DEBUG_1_stalled_b_channel_END     (4)
#define SOC_CCI500_MASTER_DEBUG_1_outstanding_reads_START   (8)
#define SOC_CCI500_MASTER_DEBUG_1_outstanding_reads_END     (15)
#define SOC_CCI500_MASTER_DEBUG_1_outstanding_writes_START  (16)
#define SOC_CCI500_MASTER_DEBUG_1_outstanding_writes_END    (23)






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

#endif /* end of soc_cci500_interface.h */
