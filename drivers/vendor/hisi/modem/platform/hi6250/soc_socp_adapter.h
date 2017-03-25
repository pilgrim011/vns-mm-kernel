/******************************************************************************

                 ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_socp_adapter.h
  �� �� ��   : ����
  ��    ��   : �޾�ǿ
  ��������   : 2015-11-12 
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��12��
    ��    ��   : c00326366
    �޸�����   : ��ƽ̨����SOCP����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SOCP_ADAPTER_H__
#define __SOC_SOCP_ADAPTER_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SOC_SOCP_CODER_SRC_CHAN                 0x00

#define SOC_SOCP_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*����Դͨ��IDö�ٶ���*/
enum SOCP_CODER_SRC_ENUM
{
    SOCP_CODER_SRC_LOM_CNF1     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,0),  /* OM������Ӧ(A��) */
    SOCP_CODER_SRC_BSP_ACORE    = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,1),  /* BSP OMͨ��(A��) */
    SOCP_CODER_SRC_LOM_IND1     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,2),  /* OM�����Ϣ(A��,�����ȼ�) */
    SOCP_CODER_SRC_LOM_IND4     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,3),  /* OM�����Ϣ(A��,�����ȼ�) */
    SOCP_CODER_SRC_LOM_IND2     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,4),  /* OM�����Ϣ(C��,�����ȼ�) */
    SOCP_CODER_SRC_LOM_IND3     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,5),  /* OM�����Ϣ(C��,�����ȼ�) */
    SOCP_CODER_SRC_LOM_CNF2     = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,6),  /* OM������Ӧ(C��) */
    SOCP_CODER_SRC_RSV1         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,7),  /* ���� */
    SOCP_CODER_SRC_BSP_CCORE    = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,8),  /* BSP OMͨ��(C��) */
    SOCP_CODER_SRC_HIFI         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,9),  /* GU HIFI�����Ϣ */
    SOCP_CODER_SRC_RSV2         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,10), /* ���� */
    SOCP_CODER_SRC_AXI_MONITOR  = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,11), /* AXI monitor */
    SOCP_CODER_SRC_MCU1         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,12), /* MCU�����Ϣ */
    SOCP_CODER_SRC_RSV3         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,13), /* ���� */
    SOCP_CODER_SRC_LDSP1        = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,14), /* LDSP�����Ϣ */
    SOCP_CODER_SRC_LDSP2        = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,15), /* LDSP�����Ϣ */
    SOCP_CODER_SRC_BBP_LOG      = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,16), /* LBBP LOG��Ϣ(ͨ����Ӳ���󶨲��ܵ���) */
    SOCP_CODER_SRC_BBP_BUS      = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,17), /* LBBP BUS��Ϣ(ͨ����Ӳ���󶨲��ܵ���) */
    SOCP_CODER_SRC_CPROC        = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,18), /* CPROC�����Ϣ */
    SOCP_CODER_SRC_AP_BSP       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,19), /* AP_BSP�����Ϣ */
    SOCP_CODER_SRC_AP_APP       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,20), /* AP_APP�����Ϣ */
    SOCP_CODER_SRC_AP_DDR       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,21), /* AP_DDR�����Ϣ */
    SOCP_CODER_SRC_ISP          = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,22), /* ISP�����Ϣ */
    SOCP_CODER_SRC_XDSP         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,23), /* XDSP�����Ϣ */
    SOCP_CODER_SRC_BBP_DS       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,24), /* LBBP������Ϣ */
    SOCP_CODER_SRC_GUBBP1       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,25), /* GUBBP�����Ϣ */
    SOCP_CODER_SRC_GUBBP2       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,26), /* GUBBP�����Ϣ */
    SOCP_CODER_SRC_GUDSP1       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,27), /* GUDSP�����Ϣ */
    SOCP_CODER_SRC_GUDSP2       = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,28), /* GUDSP�����Ϣ */
    SOCP_CODER_SRC_RSV4         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,29), /* ���� */
    SOCP_CODER_SRC_RSV5         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,30), /* ���� */
    SOCP_CODER_SRC_RSV6         = SOC_SOCP_CHAN_DEF(SOC_SOCP_CODER_SRC_CHAN,31), /* ���� */
    SOCP_CODER_SRC_BUTT
};


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

#endif /* end of bbp_cdma_on_interface.h */
