
/*��ͷ�ļ�רΪTLdsp��Hifi�ṩ������ģ��Ӧ����drv_edma.h*/
#ifndef __DRV_EDMA_ENUM_H__
#define __DRV_EDMA_ENUM_H__

#define EDMA_CHANNEL_START  0
#define EDMA_CH16_NUM       16
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define EDMA_CH4_NUM        12
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM+EDMA_CH4_NUM)
#else
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM)
#endif


#define	EDMA_CH16_0	    0
#define	EDMA_CH16_1	    1
#define	EDMA_CH16_2	    2
#define	EDMA_CH16_3	    3
#define	EDMA_CH16_4	    4
#define	EDMA_CH16_5	    5
#define	EDMA_CH16_6	    6
#define	EDMA_CH16_7	    7
#define	EDMA_CH16_8	    8
#define	EDMA_CH16_9	    9
#define	EDMA_CH16_10	10
#define	EDMA_CH16_11	11
#define	EDMA_CH16_12	12
#define	EDMA_CH16_13	13
#define	EDMA_CH16_14	14
#define	EDMA_CH16_15	15

#define	EDMA_CH12_0	    16
#define	EDMA_CH12_1	    17
#define	EDMA_CH12_2	    18
#define	EDMA_CH12_3	    19
#define EDMA_CH12_4     20
#define EDMA_CH12_5     21
#define EDMA_CH12_6     22
#define EDMA_CH12_7     23
#define EDMA_CH12_8     24
#define EDMA_CH12_9     25
#define EDMA_CH12_10    26
#define EDMA_CH12_11    27
#define	EDMA_CH_END	    28


#define	EDMA_CH_LDSP_API_USED_0 EDMA_CH16_0
#define	EDMA_CH_LDSP_API_USED_1 EDMA_CH16_1
#define	EDMA_CH_LDSP_LCS_SDR    EDMA_CH16_2
#define	EDMA_CH_LDSP_CSU_SDR    EDMA_CH16_3
#define	EDMA_CH_LDSP_EMU_SDR    EDMA_CH16_4
#define	EDMA_CH_LDSP_NV_LOADING EDMA_CH16_5
/****arm��ldsp����****�͹��ı��ݻָ�  m2m */
#define	EDMA_CH_LOAD_LDSP_TCM  EDMA_CH_LDSP_API_USED_0
#define	EDMA_CH_LOAD_TDSP_TCM  EDMA_CH_LDSP_API_USED_1
/****gudsp��ldsp����****GU CQI���� �� LDSP LCS */
#define	EDMA_CH_GUDSP_MEMORY_3  EDMA_CH_LDSP_LCS_SDR

/*EDMA_CH_GUDSP_MEMORY_9  ==  BBP_GRIF_PHY��
GUDSPʵ��BBP����������У׼ ����GU BBP DEBUG��������
����ͨ����Ϊ M2M */
#define	EDMA_CH_GUDSP_MEMORY_9  EDMA_CH16_6
#define	EDMA_CH_GUDSP_MEMORY_7  EDMA_CH16_7
/****gudsp��gudsp����****GU DSP������ GU AHB���� */
#define	EDMA_CH_GUDSP_MEMORY_8  EDMA_CH_GUDSP_MEMORY_7


#define	EDMA_CH_GUDSP_MEMORY_1  EDMA_CH16_8
#define	EDMA_CH_GUDSP_MEMORY_2  EDMA_CH16_9
#define	EDMA_CH_GUDSP_MEMORY_4  EDMA_CH16_10
#define	EDMA_CH_GUDSP_MEMORY_6  EDMA_CH16_11

#define	EDMA_CH_GUDSP_MEMORY_10  EDMA_CH16_15

/* SIM��0 ���պͷ��� / SIM��1 ���պͷ��� */
#define	EDMA_CH_DRV_SIM_0       EDMA_CH16_12
#define	EDMA_CH_DRV_SIM_1       EDMA_CH16_13
/* ��������axi_monitor�Ĳɼ����� */
#define	EDMA_CH_DRV_AXIMON      EDMA_CH16_14



/* hi6250 ������ EDMA ����ַ: 0xE0204000 0xE0210000
   ��һ�� EDMA��ͨ���ż�Ϊ 0~15���ڶ��� EDMA��ͨ���ż�Ϊ 16~27
*/

#define EDMA_CH_G1_GTC EDMA_CH12_0
#define EDMA_CH_G2_GTC EDMA_CH12_1

/* C ps ר��ͨ�� */
#define EDMA_CH_CPS_M2M_0 EDMA_CH12_4      /* PS L2���а���  */
#define EDMA_CH_CPS_M2M_1 EDMA_CH12_5      /* PS L2���а���  */


/* CPHY��ר��ͨ���� 5 ��, 1����������/���� C dsp_tcm ����*/
/* ����ַ 0xE0210000 */

#define EDMA_CH_LOAD_CDSP_TCM   EDMA_CH12_6     /* ����������뱸�ݻָ� + cdsp�͹��ı��ݻָ� */
#define EDMA_CH_CPHY_M2M_2      EDMA_CH12_7     /* DDR��DDR         */
#define EDMA_CH_CPHY_1X_1       EDMA_CH12_8     /* �����ϱ� */
#define EDMA_CH_CPHY_1X_2       EDMA_CH12_9     /* �����ϱ� */
#define EDMA_CH_CPHY_1X_3       EDMA_CH12_10    /* �����ϱ� */
#define EDMA_CH_CPHY_1X_4       EDMA_CH12_11    /* �����·� */


/* CPHY 5 ������ EDMA ͨ�� (������ L ���ã������� GU ����) 
    (����ַ 0xE0204000) */
/* �����ϱ� * �����ϱ� * �����ϱ� * �����ϱ� * �����·� */
#define EDMA_CH_CPHY_EVDO_1 EDMA_CH_GUDSP_MEMORY_1
#define EDMA_CH_CPHY_EVDO_2 EDMA_CH_GUDSP_MEMORY_2
#define EDMA_CH_CPHY_EVDO_3 EDMA_CH_GUDSP_MEMORY_4
#define EDMA_CH_CPHY_EVDO_4 EDMA_CH_GUDSP_MEMORY_6
#define EDMA_CH_CPHY_EVDO_5 EDMA_CH_GUDSP_MEMORY_9


#endif

