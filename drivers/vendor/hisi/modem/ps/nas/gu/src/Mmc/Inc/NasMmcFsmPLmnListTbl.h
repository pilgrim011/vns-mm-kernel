/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasFsmPlmnListTbl.h
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2011��07��04��
  ����޸�   :
  ��������   : plmn list״̬��״̬ת�Ʊ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��04��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _NAS_MMC_FSM_PLMN_LIST_TBL_H_
#define _NAS_MMC_FSM_PLMN_LIST_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/
extern NAS_STA_STRU                                     g_astNasMmcPlmnListStaTbl[];

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetPlmnListStaTbl()                     (g_astNasMmcPlmnListStaTbl)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_MMC_PLMN_LIST_STA_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �б�����״̬��״̬ö�ٶ���
*****************************************************************************/
enum NAS_MMC_PLMN_LIST_STA_ENUM
{
    /*Plmn List״̬����ʼ��״̬*/
    NAS_MMC_PLMN_LIST_STA_INIT                             =0,

    /*Plmn List״̬�� �ȴ�RRC��·�ͷ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND            =1,

    /*Plmn List״̬�� �ȴ�WAS��ϵͳ��Ϣ */
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND            =2,

    /*Plmn List״̬�� �ȴ�GAS��ϵͳ��Ϣ */
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND            =3,

    /*Plmn List״̬�� �ȴ�CS/SP��ע���� */
    NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND                =4,

    /*Plmn List״̬��,�ȴ�WAS�������*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF         =5,

    /*Plmn List״̬��,�ȴ�GAS�������*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF         =6,

    /*Plmn List״̬��,�ȴ�WAS����ظ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF             =7,

    /*Plmn List״̬��,�ȴ�GAS����ظ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF             =8,

    /*Plmn List״̬��,�ȴ�WASֹͣ�����ظ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF    =9,

    /*Plmn List״̬��,�ȴ�GASֹͣ�����ظ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF    =10,

#if (FEATURE_ON == FEATURE_LTE)

    /*Plmn List״̬�� �ȴ�EPS��·�ͷ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND            =11,

    /* plmn list״̬���ȴ�EPSע����*/
    NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND                 =12, 
    
    /*Plmn List״̬�� �ȴ�LMM������� */
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF         =13,

    /*Plmn List״̬�� �ȴ�LMM����ظ�*/
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_SUSPEND_CNF             =14,

    /*Plmn List״̬�� �ȴ�LMMֹͣ�����ظ� */
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF    =15,

#endif

#if (FEATURE_ON == FEATURE_CSG)
    /* CSG Plmn List״̬�����ȴ�LMM CSG �б������ظ� */
    NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF       =16,

    /* CSG Plmn List״̬�� �ȴ�LMMֹͣCSG List����ֹͣ�ظ� */
    NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF  =17,

    /* CSG Plmn List״̬��,�ȴ�WAS CSG LIST�������*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF       =18,

    /* CSG Plmn List״̬��,�ȴ�GAS CSG LIST�������*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF       =19,

    /* CSG Plmn List״̬��,�ȴ�WAS����ظ�*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_SUSPEND_CNF               =20,

    /* CSG Plmn List״̬��,�ȴ�GAS����ظ�*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_SUSPEND_CNF               =21,

    /* CSG Plmn List״̬��,�ȴ�WASֹͣCSG LIST�����ظ�*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF  =22,

    /* CSG Plmn List״̬��,�ȴ�GASֹͣCSG LIST�����ظ�*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF  =23,
#endif

   NAS_MMC_PLMN_LIST_STA_BUTT
};

typedef VOS_UINT32  NAS_MMC_PLMN_LIST_STA_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnListStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnListFsmDescAddr(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmcPlmnListFsmTbl.h */

