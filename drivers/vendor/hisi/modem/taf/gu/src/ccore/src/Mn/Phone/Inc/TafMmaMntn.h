/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaMntn.h
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2013��7��23��
  ����޸�   :
  ��������   : TafMmaMntn.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��23��
    ��    ��   : W00176964
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_MMA_MNTN_H__
#define __TAF_MMA_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMmaCtx.h"
#include "mdrv.h"
#include "msp_diag_comm.h"
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
 ö����    : TAF_MMA_MNTN_MSG_ID_ENUM
 �ṹ˵��  : MSCC���͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2013��7��23��
    ��    ��   : w00176964
    �޸�����   : MMA�Ŀ�ά�ɲ���ϢIDö��

  2.��    ��   : 2014��2��18��
    ��    ��   : w00167002
    �޸�����   : CL������������ά�ɲ�
*****************************************************************************/
enum TAF_MMA_MNTN_MSG_ID_ENUM
{
    TAF_MMA_LOG_FSM_INFO_IND                                , /*_H2ASN_MsgChoice TAF_MMA_LOG_FSM_INFO_STRU */
    TAF_MMA_LOG_BUFFER_MSG_INFO_IND                         , /*_H2ASN_MsgChoice TAF_MMA_LOG_BUffER_MSG_INFO_STRU */
    TAF_MMA_LOG_INTER_MSG_INFO_IND                          , /*_H2ASN_MsgChoice TAF_MMA_LOG_INTER_MSG_INFO_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_UNLOCK            , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK              , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */

    /* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
    TAF_MMA_LOG_OPER_CTX_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_OPER_CTX_INFO_STRU */
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */

    TAF_MMA_LOG_COPS_RLT_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_COPS_RLT_INFO_STRU */

    TAF_MMA_LOG_NETWORK_APPNETWORK_CTX_INFO_IND             , /*_H2ASN_MsgChoice TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU */

    TAF_MMA_LOG_READ_NV_INFO_IND                            , /*_H2ASN_MsgChoice TAF_MMA_LOG_READ_NV_INFO_IND_STRU */

    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND         , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU */

    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_ENTER_IND   , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU */
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_EXIT_IND    , /*_H2ASN_MsgChoice TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU */
    TAF_MMA_LOG_BUT
};
typedef VOS_UINT32 TAF_MMA_MNTN_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8
 �ṹ˵��  : ��Ӫ����������
 1.��    ��   : 2015��4��8��
   ��    ��   : c00318887
   �޸�����   : ����
*****************************************************************************/
enum TAF_SDC_LOG_OPER_NAME_TYPE_ENUM
{
    TAF_SDC_LOG_OPER_NAME_TYPE_PNN = 1,
    TAF_SDC_LOG_OPER_NAME_TYPE_CPHS,
    TAF_SDC_LOG_OPER_NAME_TYPE_SPN,
    TAF_SDC_LOG_OPER_NAME_TYPE_MMINFO,
    TAF_SDC_LOG_OPER_NAME_TYPE_NV,
    TAF_SDC_LOG_OPER_NAME_TYPE_TABLE,
    TAF_SDC_LOG_OPER_NAME_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8;


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
 �ṹ��    : TAF_MMA_LOG_FSM_INFO_STRU
 �ṹ˵��  : MMA״̬����ά�ɲ���Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��07��23��
   ��    ��   : W00176964
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulState;
}TAF_MMA_LOG_FSM_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_BUffER_MSG_INFO_STRU
 �ṹ˵��  : MMA�Ļ�����Ϣ��ν�ɲ�

 �޸ļ�¼  :
 1.��    ��   : 2013��07��23��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    TAF_MMA_MSG_QUEUE_STRU              stMsgQueue;
}TAF_MMA_LOG_BUffER_MSG_INFO_STRU;

/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_OPER_CTX_INFO_STRU
 �ṹ˵��  : MMA��OPER_CTX��Ϣ��ά�ɲ�

 �޸ļ�¼  :
  1.��    ��   : 2014��2��18��
    ��    ��   : w00167002
    �޸�����   : ����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];
}TAF_MMA_LOG_OPER_CTX_INFO_STRU;
/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */


/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_INTER_MSG_INFO_STRU
 �ṹ˵��  : �ڲ���Ϣ��������֪ͨ
 1.��    ��   : 2013��7��24��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    VOS_UINT8                           ucFullFlg;
    VOS_UINT8                           ucMsgLenValidFlg;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_LOG_INTER_MSG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEP_VOTE_UNLOCK_STRU
 �ṹ˵��  : ����TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��08��12��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;            /* _H2ASN_Skip*/
    PWC_CLIENT_ID_E                     enClientId;
    VOS_UINT32                          ulRslt;
}TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU;


/*****************************************************************************
 �ṹ��    : TAF_SDC_LOG_ENHANCED_OPERATOR_NAME_INFO
 �ṹ˵��  : ��¼��Ӫ�����������Ϣ
 1.��    ��   : 2015��4��8��
   ��    ��   : c00318887
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU         stOperNameTypePrio;   /* cops��^eonsucs2��ѯ��PNN��SPN��CPHS��NITZ��ȡ�Ⱥ�˳�����ȼ�*/
    TAF_SDC_SPN_FILE_INFO_STRU               stUsimSpnFileInfo;    /* Usim�е�SPN�ļ�0x6f46��Ϣ */
    TAF_SDC_SPN_FILE_INFO_STRU               stSimSpnFileInfo;     /* Sim�е�SPN�ļ�0x6f46��Ϣ */
    TAF_SDC_MM_INFO_STRU                     stMmInfo;             /* ��¼MM/GMM/EMM info��Ϣ�е���Ϣ*/
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8      enCopsFormatType;
    VOS_CHAR                                 cWildCard;             /* ͨ���,ȡֵa-f,�ɴ���0-9�������� */
    VOS_UINT8                                aucReserved[2];
}TAF_SDC_LOG_EONS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_COPS_RLT_INFO_STRU
 �ṹ˵��  : MMA��COPS�����Ϣ��ά�ɲ�

 �޸ļ�¼  :
  1.��    ��   : 2015��4��8��
    ��    ��   : c00318887
    �޸�����   : ����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32         enMsgId;        /* _H2ASN_Skip*/
    TAF_PH_OPERATOR_NAME_STRU               stName;
    TAF_PH_NETWORKNAME_FORMAT               stNameFormat;         /*������Ӫ�����ָ�ʽ*/
    TAF_PH_RA_MODE                          ucRaMode;            /*���߽���ģʽ,3G/2G*/
    TAF_PH_PLMN_SEL_MODE                    ucPlmnSelMode;       /*PLMN selection mode*/
    TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8   enType;
    TAF_SDC_LOG_EONS_INFO_STRU              stEonsInfo;
}TAF_MMA_LOG_COPS_RLT_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32         enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];                       /* NV���� */

}TAF_MMA_LOG_READ_NV_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM
 �ṹ˵��  : AT������ʱ�ϱ�����ʱ��AT��������

 �޸ļ�¼  :
  1.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
enum TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM
{
    TAF_MMA_LOG_DELAY_RPT_SRVST = 0,
    TAF_MMA_LOG_DELAY_RPT_CREG,
    TAF_MMA_LOG_DELAY_RPT_CGREG,
    TAF_MMA_LOG_DELAY_RPT_EGREG,
    TAF_MMA_LOG_DELAY_RPT_SID,
    TAF_MMA_LOG_DELAY_RPT_CDMACSQ,
    TAF_MMA_LOG_DELAY_RPT_HDRCSQ,
    TAF_MMA_LOG_DELAY_RPT_BUTT
};
typedef VOS_UINT8  TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : AT������ʱ�ϱ��ǣ������ṹ��

 �޸ļ�¼  :
  1.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32              enMsgId;
    TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8     enDelayRptType;
    VOS_UINT8                                    aucReserved[3];
}TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_DELAY_REPORT_CTX_TYPE_ENUM
 �ṹ˵��  : CL����״̬��Ϣ��ʱ�ϱ���������

 �޸ļ�¼  :
  1.��    ��   : 2016��01��15��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
enum TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM
{
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER = 0,        /* ������ڹ�����Ϣ */
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT,             /* �������ڹ�����Ϣ */
};
typedef VOS_UINT8  TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_1X_SYS_INFO_STRU
 �ṹ˵��  : 1X��ϵͳ��Ϣ�������ͷ���״̬ע��״̬�������Ϣ

 �޸ļ�¼  :
  1.��    ��   : 2016��01��15��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
    VOS_UINT32                          ulMcc;            /**<  Mobile country code */
    VOS_UINT16                          usMnc;            /**<  Mobile network code */
    VOS_UINT16                          usImsi11_12;      /**<  11th and 12th digits of the IMSI */
    VOS_UINT8                           uc1xRfAvailFlg;
    VOS_UINT8                           ucRoamingInd;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_LOG_CL_DELAY_REPORT_1X_SYS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_NETWORK_SYS_INFO_STRU
 �ṹ˵��  : ϵͳ��Ϣ����������NetWorkInfo�е�ϵͳ��Ϣ��ע��״̬������״̬��������
             ��AppNetWorkInfo�е�ϵͳ��Ϣ��ע��״̬������״̬��������

 �޸ļ�¼  :
  1.��    ��   : 2016��01��15��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_LOG_CL_DELAY_REPORT_1X_SYS_INFO_STRU            st1xSysInfo;         /* ������1x����Ϣ */
    TAF_SDC_SERVICED_PLMN_INFO_STRU                         st3GppServPlmnInfo;  /* ������lte����Ϣ */
    TAF_SDC_CS_DOMAIN_INFO_STRU                             stCsDomainInfo;      /*��ǰCS����Ϣ*/
    TAF_SDC_PS_DOMAIN_INFO_STRU                             stPsDomainInfo;      /*��ǰPS����Ϣ*/
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSysSubMode;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8                        enReportSrvsta;    /* UE�ķ���״̬ ^srvst�ϱ��ķ���״̬*/
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8                       enServiceDomain;   /* UE�ķ�����sysinfo ��ѯʱ�ϱ��ķ�����*/
}TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU
 �ṹ˵��  : ϵͳ��Ϣ����������NetWorkInfo�е�ϵͳ��Ϣ��ע��״̬������״̬��������
             ��AppNetWorkInfo�е�ϵͳ��Ϣ��ע��״̬������״̬��������

 �޸ļ�¼  :
  1.��    ��   : 2016��01��15��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32                         enMsgId;
    TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU               stNetWorkInfo;              /* ʵʱϵͳ��Ϣ����g_stTafSdcCtx�е�stNetworkInfo�л�ȡ */
    TAF_MMA_LOG_CL_DELAY_REPORT_SYS_INFO_STRU               stAppNetWorkInfo;           /* ��ʱϵͳ��Ϣ����g_stTafSdcCtx�е�stAppNetworkInfo�л�ȡ */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enCsDelayReportTimerStatus; /* CS����ʱ�ϱ���ʱ��״̬ */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enPsDelayReportTimerStatus; /* PS����ʱ�ϱ���ʱ��״̬ */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enDelayRptApsClNoSrvTimerStatue;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enDelayRptApsDoNoSrvTimerStatue;
}TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_DATA                 stMsgData;
}TafMmaMntn_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* Deleted by wx270776 for OM�ں�, 2015-7-24, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-24, end */

VOS_VOID  TAF_MMA_LogFsmInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
VOS_VOID TAF_MMA_LogOperCtxInfo(VOS_VOID);
/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */

VOS_VOID  TAF_MMA_LogNetworkInfoAndAppNetworkInfo(VOS_VOID);

VOS_VOID  TAF_MMA_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
);

VOS_VOID TAF_MMA_ShowPhoneModeCtrlInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
VOS_VOID TAF_MMA_ShowCLConfigInfo(VOS_VOID);
/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */

VOS_VOID TAF_MMA_LogCopsRltInfo(
        TAF_PH_NETWORKNAME_STRU                   *pstOperatorName,
        TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8      enType
);

VOS_VOID TAF_MMA_ModelPihSndUsimStatusInd(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeOne,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceOne,
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeTwo,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceTwo
);
VOS_VOID TAF_MMA_ModelUphySndInitStatusInd(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16               enInitStatus
);
VOS_VOID TAF_MMA_ModelUsimStatusIndTimeOut(VOS_VOID);
VOS_VOID TAF_MMA_SndTestInterPowerInitReq(VOS_VOID);
VOS_VOID TAF_MMA_TestSetGeoIno(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
);

VOS_VOID TAF_MMA_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_MMA_LogDelayReportInfo(
    TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8    enDelayRptType
);

#endif

VOS_VOID TAF_MMA_LogCLDelayRptSrvStatusCtx(
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM_UINT8         enMmaLogDelayRptCtxType
);

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

#endif /* end of TafMmaMntn.h */


