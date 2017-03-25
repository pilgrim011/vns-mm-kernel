/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcSndInternalmsg.h
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2011��5��9��
  ����޸�   :
  ��������   : �����ڲ���Ϣ���ʹ���ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _NAS_MMC_SND_INTERNAL_MSG_H_
#define _NAS_MMC_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasMmcCtx.h"
#include  "NasCommDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_MMLAYER_INTERNAL_MSG_ID_ENUM
 �ṹ˵��  : �ڲ���ϢID
 1.��    ��   : 2011��5��9��
   ��    ��   : zhoujun 40661
   �޸�����   : MMC�ڲ���ϢIDö��
 2.��    ��   : 2011��7��19��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
*****************************************************************************/
enum NAS_MMC_INTERNAL_MSG_ID_ENUM
{
    /* MMC�յ����ڲ���ϢID,MMC�ڲ��յ�����ϢID��0x000��0x199 */
    MMCMMC_ABORT_FSM_REQ                       = 0,
    MMCMMC_INTER_PLMN_SEARCH_REQ               = 1,                                  /* �ڲ��������� ,���³�ʼ���������������� */
    MMCMMC_INTER_ANYCELL_SEARCH_REQ            = 2,                                  /* �ڲ��������� ,���³�ʼ���������������� */
    MMCMMC_INTER_PLMN_LIST_REQ                 = 3,

    MMCMMC_SWITCH_ON_RSLT_CNF                  = 4,
    MMCMMC_POWER_OFF_RSLT_CNF                  = 5,
    MMCMMC_SUSPEND_RSLT_CNF                    = 6,
    MMCMMC_PLMN_LIST_RSLT_CNF                  = 7,

    MMCMMC_PLMN_SELECTION_RSLT_CNF             = 8,

    MMCMMC_ANYCELL_SEARCH_RSLT_CNF             = 9,

    MMCMMC_SYSCFG_RSLT_CNF                     = 10,

    MMCMMC_BG_PLMN_SEARCH_RSLT_CNF             = 11,

    MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND        = 12,

    MMCMMC_INTER_SKIP_SEARCH_W_IND             = 13,

    MMCMMC_INTER_SKIP_SEARCH_TDS_IND           = 14,
    MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ = 15,
    MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF = 16,

    MMCMMC_GET_GEO_RSLT_CNF                    = 17,
    MMCMMC_INTER_DPLMN_SET_REQ                 = 18,

    MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND = 19,

    MMCMMC_INTERNAL_MSG_ID_BUTT
};
typedef VOS_UINT32 NAS_MMC_INTERNAL_MSG_ID_ENUM_U32;


/*****************************************************************************
ö����    : NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM
�ṹ˵��  : Anycell ����״̬�������Ľ��
1.��    ��   : 2011��7��11��
  ��    ��   : l00130025
  �޸�����   : ����
2.��    ��   : 2014��4��24��
  ��    ��   : w00242748
  �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ

*****************************************************************************/
enum NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM
{
    NAS_MMC_ANYCELL_SEARCH_SUCC         = 0,
    NAS_MMC_ANYCELL_SEARCH_FAIL         = 1,
    NAS_MMC_ANYCELL_SEARCH_ABORTED      = 2,
    NAS_MMC_ANYCELL_SEARCH_REJECT       = 3,
    NAS_MMC_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32;

/*****************************************************************************
ö����    : NAS_MMC_PLMN_SELECTION_RESULT_ENUM
�ṹ˵��  : plmnSelection״̬�������Ľ��
1.��    ��   : 2011��7��11��
  ��    ��   : l00130025
  �޸�����   : ����
2.��    ��   : 2014��1��27��
  ��    ��   : s00246516
  �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
enum NAS_MMC_PLMN_SELECTION_RESULT_ENUM
{
    NAS_MMC_PLMN_SELECTION_SUCC            = 0,                                    /*����������פ��*/
    NAS_MMC_PLMN_SELECTION_FAIL            = 1,                                    /*�������ע�ᵼ�¿���Ч*/
    NAS_MMC_PLMN_SELECTION_ABORTED         = 2,                                    /* PlmnSelection״̬�������*/
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD  = 3,                                 /* ������������ѡ��HRPD */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */
    NAS_MMC_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MMC_SUSPEND_RSLT_ENUM_UINT32
 �ṹ˵��  : ��ѡ/HO/CCO״̬�������Ľ��
 1.��    ��   : 2011��7��18��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
enum NAS_MMC_SUSPEND_RSLT_ENUM
{
    NAS_MMC_SUSPEND_SUCCESS            = 0,
    NAS_MMC_SUSPEND_FAIL               = 1,
    NAS_MMC_SUSPEND_ABORTED            = 2,
    NAS_MMC_SUSPEND_BUTT
};
typedef VOS_UINT32 NAS_MMC_SUSPEND_RSLT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MMC_GET_GEO_RSLT_ENUM_UINT32
 �ṹ˵��  : GET GEO״̬�������Ľ��
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : ����
*****************************************************************************/
enum NAS_MMC_GET_GEO_RSLT_ENUM
{
    NAS_MMC_GET_GEO_SUCCESS             = 0,
    NAS_MMC_GET_GEO_FAIL                = 1,
    NAS_MMC_GET_GEO_ABORTED             = 2,
    NAS_MMC_GET_GEO_ABNORMAL            = 3,                /* ״̬�����쳣��ֹ */
    NAS_MMC_GET_GEO_NO_RF               = 4,                /* GET GEO���ؽ��ΪNO_RF */
    NAS_MMC_GET_GEO_BUTT
};
typedef VOS_UINT32 NAS_MMC_GET_GEO_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM
 �ṹ˵��  : InterSys״̬��ʧ��ԭ��, ��ǰInterSys״̬���˳����ΪNAS_MMC_SUSPEND_FAILʱ�������Ч
 1.��    ��   : 2011��9��29��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
enum NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM
{
    NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST        = 0,
    NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8;

/*****************************************************************************
ö����    : NAS_MMC_PLMN_LIST_RESULT_ENUM
�ṹ˵��  : LIST����״̬�������Ľ��
1.��    ��   : 2011��9��05��
  ��    ��   : w00176964
  �޸�����   : ����
2.��    ��   : 2014��5��15��
  ��    ��   : w00167002
  �޸�����   : DTS2014051501018:DSDS��MODEM����绰����MODEM����ʧ������AVAILABLE
               ��ʱ�����û������б��ѣ����б��ѹ����У�����������ʱ����ʱ���б���
               ������MMCû����������������ʱ����
               �޸�Ϊ:���б���NO RF�󣬶�����AVAILABLE��ʱ������AVAILABLE��ʱ��
               ��ʱ�����������ǰ����#12����������ǰACCESS BAR��������
*****************************************************************************/
enum NAS_MMC_PLMN_LIST_RESULT_ENUM
{
    NAS_MMC_PLMN_LIST_SUCC         = 0,
    NAS_MMC_PLMN_LIST_FAIL         = 1,
    NAS_MMC_PLMN_LIST_ABORTED      = 2,

    NAS_MMC_PLMN_LIST_NO_RF_FAIL    = 3,

    NAS_MMC_PLMN_LIST_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32;

/*****************************************************************************
ö����    : NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM
�ṹ˵��  : BgPlmnSearch״̬���˳����
1.��    ��   : 2011��9��20��
  ��    ��   : s46746
  �޸�����   : ����
2.��    ��   : 2014��1��27��
  ��    ��   : s00246516
  �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
enum NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM
{
    NAS_MMC_BG_PLMN_SEARCH_SUCC         = 0,                                    /* BG�����ɹ���� */
    NAS_MMC_BG_PLMN_SEARCH_FAIL         = 1,                                    /* BG����δ��� */
    NAS_MMC_BG_PLMN_SEARCH_ABORTED      = 2,                                    /* BG������Abort */

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD  = 3,                                 /* BG������������ѡ��HRPD */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    NAS_MMC_BG_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32;


/*****************************************************************************
ö����    : NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM
�ṹ˵��  : HighPrioPlmnSearch״̬���˳����
1.��    ��   : 2011��9��20��
  ��    ��   : w00167002
  �޸�����   : ����
*****************************************************************************/
enum NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM
{
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_SUCC         = 0,                             /* �����ȼ������ɹ���� */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_FAIL         = 1,                             /* �����ȼ�����δ��� */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_ABORTED      = 2,                             /* �����ȼ�������Abort */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM_UINT8
 �ṹ˵��  : LIST����״̬���˳������б������������
 1.��    ��   : 2015��9��18��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
enum NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM
{
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_NOT_CSG_LIST = 0,  /* list�����������ͨ�û��б��������ڲ��б��������� */
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_CSG_LIST     = 1,  /* list���������CSG LIST�������� */
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM_UINT8;

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
ö����    : NAS_MMC_POWEROFF_RSLT_ENUM
�ṹ˵��  : POWEROFF״̬���˳����
1.��    ��   : 2014��1��28��
  ��    ��   : s00246516
  �޸�����   : ����
*****************************************************************************/
enum NAS_MMC_POWEROFF_RSLT_ENUM
{
    NAS_MMC_POWEROFF_RSLT_POWER_OFF            = 0,
    NAS_MMC_POWEROFF_RSLT_POWER_SAVE           = 1,
    NAS_MMC_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MMC_POWEROFF_RSLT_ENUM_UINT32;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

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
 �ṹ��    : NAS_MMC_ABORT_FSM_STRU
 �ṹ˵��  : MMC������ֹ״̬����Ϣ�Ľṹ
 1.��    ��   : 2011��7��12��
   ��    ��   : zhoujun 40661
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ

 2.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : DTS2011112301233:���Ӵ���¼�ID��״̬������֪����ʲô�¼�
                ����Լ��ġ�
                �޸�ԭ��:�û��·��ػ�����󣬵�ǰ�����ڵ�ע���������ڵ�����
                �ͷţ�������Ҫ�ȽϾõ�ʱ����ܴ���ػ����ͨ�����Ӵ���¼���
                ��鵱ǰ�ڵ�ע�������ߵ������ͷ�״̬�����յ��ػ������ֱ��
                �˳���ǰ״̬���������û��Ĺػ����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgID;                                /* ��ϢID */

    VOS_UINT32                          ulEventType;                            /* ����¼�ID */

    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType;
    VOS_UINT8                           aucReserved[3];
}NAS_MMC_ABORT_FSM_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU
 �ṹ˵��:  MMC->MMC,�ڲ�Anycell�������ͱ�ʶ

  1.��    ��   : 2011��7��19��
    ��    ��   : l00130025
    �޸�����   : �ڲ�������Ϣ�Ľṹ
  2.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;                   /* ��ǰҪ�����Ľ��뼼���б� */

    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8  enAnycellSearchScene;
    VOS_UINT8                            aucReserved[3];
}NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU;


/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU
 �ṹ˵��: MMC->MMC,�ڲ�������Ϣ�Ľṹ
 1.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;            /* ��Ϣͷ */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enPlmnSearchScene;      /* �������� */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    astInterPlmnSearchInfo[NAS_MML_MAX_RAT_NUM]; /* Я��������Ϣ */
}NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_PLMN_LIST_REQ_STRU
 �ṹ˵��: MMC->MMC,�ڲ�LIST������Ϣ�Ľṹ
 1.��    ��   : 2011��9��19��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* ��Ϣͷ */
}NAS_MMC_INTER_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_DPLMN_SET_REQ_STRU
 �ṹ˵��: MMC->MMC,�ڲ�DPLMN SET REQ��Ϣ�Ľṹ
  1.��    ��   : 2015��11��9��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                                        /* ��Ϣͷ */
    VOS_UINT8                           aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];        /* �汾�ţ��̶�Ϊxx.xx.xxx */
    VOS_UINT8                           ucEhPlmnNum;                                        /* EHPLMN�ĸ���*/
    VOS_UINT8                           aucReserve[2];
    NAS_MML_PLMN_ID_STRU                astEhPlmnInfo[NAS_MML_MAX_EHPLMN_NUM + 1];          /* EHPLMN ID�б� */
}NAS_MMC_INTER_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_GET_GEO_RSLT_STRU
 �ṹ˵��: MMC->MMC,�ڲ���ȡ������Ϣ�����Ϣ�Ľṹ
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;  /* ��Ϣͷ */

    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32              enGetGeoRslt; /* ��ȡ������Ϣ��� */
    NAS_MML_PLMN_ID_STRU                          stGetGeoPlmn; /* ��ȡ������Ϣ�ɹ�ʱ��Ч����ȡ����PLMN */
}NAS_MMCMMC_GET_GEO_RSLT_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_SWITCHON_RLST_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMC->MMC,�������

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : ������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;
    VOS_UINT32                                 ulResult;
} NAS_MMC_SWITCHON_RLST_STRU;


/*****************************************************************************
 �ṹ����: NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU
 �ṹ˵��:  MMC->MMC,Anycell�������

  1.��    ��   : 2011��7��11��
    ��    ��   : l00130025
    �޸�����   : Anycell�������
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32   enResult;
} NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU
 �ṹ˵��:  MMC->MMC,PlmnSelection�������

  1.��    ��   : 2011��7��11��
    ��    ��   : l00130025
    �޸�����   : ѡ������ڲ���Ϣ���
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                              /*��Ϣͷ*/
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32   enResult;                               /*ѡ�����*/
    VOS_UINT32                                  ulCampFlg;                              /*��ǰ�Ƿ�פ����־,VOS_TRUE:��פ��,VOS_FALSE:δפ��*/
    VOS_UINT32                                  ulRatNum;                               /*�и��ǵĽ��뼼������*/
    NAS_MMC_RAT_SEARCH_INFO_STRU                astSearchRatInfo[NAS_MML_MAX_RAT_NUM];  /*���治ͬ���뼼����������Ϣ*/
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32       ulPlmnSearchScene;                      /* �������� */
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, end */
} NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU
 �ṹ˵��:  MMC->MMC,֪ͨUTRANCTRL������W���

  1.��    ��   : 2014��2��11��
    ��    ��   : w00167002
    �޸�����   : ֪ͨUTRANCTRL��������W���.
                 ע:SVLTE�����ߣ���W������NO RF����G�������ɹ�����פ���ɹ���
                 �����ٷ�������ʱ������WAS,����G�ᶪ��������UTRANCTRL״̬��ʱ��
                 ��NO RFʱ��ǰ��FDDģʽ�ģ����MMC�ٷ�������ʱ�򣬻��ȸ�WAS���ͣ�
                 UTRAN����SKIP W��Ϣ����UTRANCTRL״̬������TDD.
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU
 �ṹ˵��:  MMC->MMC,֪ͨUTRANCTRL������tds���

  1.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU;

/*****************************************************************************
 �ṹ����: MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU
 �ṹ˵��:  MMC->MMC,֪ͨUTRANCTRLֹͣ��������utran ctrl mode��Ϣ

  1.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ����: MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU
 �ṹ˵��:  MMC->MMC,utran ctrl �ظ�mmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ

  1.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU;



/*****************************************************************************
 �ṹ����: NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU
 �ṹ˵��: MMC->MMC,֪ͨUTRANCTRL�ѱ�ABORT

  1.��    ��   : 2015��12��17��
    ��    ��   : w00167002
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU;


/*****************************************************************************
 �ṹ����: NAS_MMCMMC_SUSPEND_RSLT_STRU
 �ṹ˵��:  MMC->MMC,��ѡ,HO,CCO״̬�����

  1.��    ��   : 2011��7��18��
    ��    ��   : w00176964
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;

    /* �������� */
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause;

    /* ״̬��ʧ��ԭ�� */
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enFailCause;

    VOS_UINT8                                               ucReserve[2];

    /*״̬����ɵĽ�� */
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enRslt;


    /* ������ϱ��������б� */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnSearchInfo[NAS_MML_MAX_RAT_NUM];
}NAS_MMCMMC_SUSPEND_RSLT_STRU;


/*****************************************************************************
 �ṹ����: NAS_MMCMMC_PLMN_LIST_RSLT_STRU
 �ṹ˵��:  MMC->MMC,user list����״̬�����
 1.��    ��   : 2011��8��30��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2012��5��8��
   ��    ��   : t00212959
   �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;

    /* ״̬����ɵĽ�� */
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt;

    /* �Ƿ���Ҫ���� */
    VOS_UINT8                                               ucNeedPlmnSearch;

    /* ��ǰ����CS��ע�����ĸ��Ӵ��� */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;

    /* ��ǰ����PS��ע�����ĸ��Ӵ��� */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsRegAdditionalAction;

    VOS_UINT8                                               aucReserve[1];

    /* plmn list����״̬���Ľ�� */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnSearchInfo[NAS_MML_MAX_RAT_NUM];

    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;            /* Я����������*/
    VOS_UINT8                                               aucReserved[3];

}NAS_MMCMMC_PLMN_LIST_RSLT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt;
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */
}NAS_MMCMMC_POWEROFF_RSLT_STRU;


/*****************************************************************************
 �ṹ����:  NAS_MMCMMC_SysCfg_RSLT_STRU
 �ṹ˵��:  MMC->MMC,SYSCFG״̬����ɽ����Ϣ

 1.��    ��   : 2011��7��18��
   ��    ��   : w00167002
   �޸�����   : �����ṹ
 2.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE.
                 ���޸�Ϊ��SYSCFG��,�����Ҫ���������б��Ƿ�ATTACH PS��Ҫ��ENABLE LTE��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */
    VOS_UINT32                          ulRslt;             /* SYSCFG״̬����ɽ��:VOS_TRUE:SYSCFG���óɹ���VOS_FALSE:SYSCFG����ʧ�� */
    VOS_UINT32                          ulNeedPlmnSrch;     /* SYSCFG״̬������Ƿ���Ҫ����:VOS_TRUE:SYSCFG���óɹ�����Ҫ������VOS_FALSE:YSCFG���óɹ�����Ҫ���� */

    VOS_UINT32                          ulIsNeedAttachPs;

    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;   /* ��syscfg״̬��ǰ�Ľ��뼼�������ȼ� */


} NAS_MMCMMC_SysCfg_RSLT_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU
 �ṹ˵��:  MMC->MMC,BgPlmnSearch״̬���˳����
 1.��    ��   : 2011��9��20��
   ��    ��   : s46746
   �޸�����   : �����ṹ
 2.��    ��   : 2012��5��8��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL BG�����޸�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32     enRslt;                         /* BG������� */
    VOS_UINT32                                  ulNeedPlmnSearch;               /* �Ƿ���Ҫ������־,VOS_TRUE:��Ҫ����,VOS_FALSE:����Ҫ���� */
    VOS_UINT32                                  ulSearchCompleted;              /* �Ƿ���ɸ����ȼ�������־,VOS_TRUE::���ָ����ȼ�����������VOS_FALSE:���ָ����ȼ�����δ���� */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU        stSearchedPlmnListInfo;         /* Я��������Ϣ */

    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8     enBgPlmnSearchScene;            /* Я����������*/
    VOS_UINT8                                   aucReserved[3];
} NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* ��Ϣͷ */
}NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_UPDATE_UPLMN_NTF_STRU
 �ṹ˵��: MMC->MMC,����UPLMN��Ϣ�Ľṹ
 1.��    ��   : 2015��02��09��
   ��    ��   : y00307564
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* ��Ϣͷ */
}NAS_MMC_INTER_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_MMC_SndAbortFsmMsg(
    VOS_UINT32                          ulEventType,
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType
);
VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult);

VOS_VOID  NAS_MMC_SndSuspendRsltMsg(
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause,
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enSuspendRslt,
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enSuspendFailCause,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
);


/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, begin */
VOS_VOID  NAS_MMC_SndPlmnSelectionRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt,
    VOS_UINT32                                              ulCampFlg,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    VOS_UINT32                                              ulRatNum,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   ulPlmnSearchScene
);
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, end */

VOS_VOID  NAS_MMC_SndInterSkipSearchWIndMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterSkipSearchTdsIndMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg(VOS_VOID);



VOS_VOID NAS_MMC_SndAnycellSearchRslt(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
);

VOS_VOID  NAS_MMC_SndBgPlmnSearchRslt(
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enPlmnSelectionRslt,
    VOS_UINT32                                              ulNeedPlmnSearch,
    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8                 enBgPlmnSearchScene,
    VOS_UINT32                                              ulBgSearchCompleted,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);



VOS_VOID  NAS_MMC_SndSysCfgRslt(
    VOS_UINT32                          ulSysCfgRslt,
    VOS_UINT32                          ulNeedPlmnSrch,
    VOS_UINT32                          ulIsNeedAttachPs,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
);

VOS_VOID NAS_MMC_SndInterPlmnSearchReq(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo,
    VOS_UINT8                                ucRatNum
);

VOS_VOID NAS_MMC_SndInterPlmnListReq(VOS_VOID);

VOS_VOID NAS_MMC_SndInterAnyCellSearchReq(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstAnycellSrchRatList,
    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8                 enAnycellSearchScene
);


VOS_VOID NAS_MMC_BulidInterPlmnSearchReqMsg(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstIntraPlmnSrchInfo,
    VOS_UINT8                                               ucRatNum,
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstMsg
);

VOS_VOID NAS_MMC_BuildInterDplmnSetReqMsg(
    VOS_UINT8                                              *pucVersion,
    VOS_UINT8                                               ucEhPlmnNum,
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstEhPlmnInfo,
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU                       *pstMsg
);
/* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
VOS_VOID NAS_MMC_SndPowerOffRslt(
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt
);
/* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

VOS_VOID NAS_MMC_SndPlmnListRslt(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ulNeedPlmnSearch,
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                    *pstRegRsltInfo
);

VOS_VOID NAS_MMC_SndInterNvimOPlmnRefreshInd(VOS_VOID);

VOS_VOID  NAS_MMC_SndGetGeoRsltMsg(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGetGeoPlmn
);

VOS_VOID NAS_MMC_SndInterUpdateUplmnNtf(VOS_VOID);

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

#endif

