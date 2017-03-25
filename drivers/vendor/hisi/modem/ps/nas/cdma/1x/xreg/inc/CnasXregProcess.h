/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregProcess.h
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��08��
    ��    ��   :
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _CNAS_XREG_PROCESS_H_
#define _CNAS_XREG_PROCESS_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include  "cas_1x_idlectrl_proc_nas_pif.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "cas_1x_access_ctrl_proc_nas_pif.h"
#include  "xsd_xreg_pif.h"
#include  "CnasXregFsmMainTbl.h"
#include  "NasOmTrans.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_XREG_T57M_LEN              (20*1000)   /*20s*/
#define CNAS_XREG_ZONE_MAX              (7)         /*N9M*/
#define CNAS_XREG_SID_NID_MAX           (4)         /*N10M*/

#define CNAS_XREG_MS_PER_COUNT          (80)        /* COUNTֵ��λΪ80ms */

#define CNAS_XREG_TIMER_MAX_LEN         (43200000)  /* ����OSA֧�ֵ����ʱ��ΪVOS_TIMER_MAX_LENGTH(18Сʱ) */

#define CNAS_XREG_HOME_SID_NID_NUM      (20)        /* �ж��Ƿ�����ʹ�� */
#define CNAS_XREG_HOME_NID              (0xffff)

#define CNAS_XREG_REG_ORD               (0x1b)      /* ����ָ��ע����ʹ�� */
#define CNAS_XREG_REG_REQ               (0x01)

#define CNAS_XREG_MIN_REG_PRD           (29)        /* PRD_REGs��Χֵ */
#define CNAS_XREG_MAX_REG_PRD           (85)

#define CNAS_XREG_180DEGREE             (0x278D00)
#define CNAS_XREG_360DEGREE             (0x4F1A00)

#define CNAS_XREG_DELTAVALUE_MAX        (0xFFFF)
#define CNAS_XREG_DELTADIST_MAX         (0xFFFFFFFF)

#define CNAS_XREG_SCI_NULL_VALUE        (0x7f)      /* ��Ч��SCIֵ */
#define CNAS_XREG_SCI_DEF_VALUE         (2)         /* Ĭ�ϵ�SCIֵ */
#define CNAS_XREG_SCI_MIN_VALUE         (0)         /* ��С��SCIֵ */
#define CNAS_XREG_SCI_MAX_VALUE         (7)         /* ����SCIֵ */

#define CNAS_XREG_MOB_TERM_NID_MASK     (0x1)       /* ����EFterm�ļ���NID�Ƿ�ʹ�ܵ�����λ */
#define CNAS_XREG_MOB_TERM_SID_MASK     (0x2)       /* ����EFterm�ļ���SID�Ƿ�ʹ�ܵ�����λ */
#define CNAS_XREG_MOB_TERM_HOME_MASK    (0x4)       /* ����EFterm�ļ���HOME�Ƿ�ʹ�ܵ�����λ */

#define CNAS_XREG_SSCI_VALUE_MASK       (0x7)       /* ����EFssci�ļ���Suggested Slot Cycle Index������λ */

/* ���� CS0005E_Details ��Ա */
#define CNAS_XREG_SetCS0005EDetailPara(pstCS0005Detail,usMsgTag,usPRevInUse,usAuthMode)\
    {\
        PS_MEM_SET((pstCS0005Detail),0,sizeof(CS0005E_Details));\
        (pstCS0005Detail)->n_MSG_TAG          = (usMsgTag);\
        (pstCS0005Detail)->n_P_REV_IN_USEs    = (usPRevInUse);\
        (pstCS0005Detail)->n_AUTH_MODE        = (usAuthMode);\
    }

#define CNAS_XREG_NUM_RANGE(min, max, value) ((value >= min)&&(value <= max))

#define CNAS_XREG_MAX_ITEM_NUM          (20)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum CNAS_XREG_VAR_VALUE_ENUM
{
    CNAS_XREG_VAR_NO        = 0,
    CNAS_XREG_VAR_YES       = 0x5a,
    CNAS_XREG_VAR_VALUE_BUTT
};
typedef VOS_UINT8 CNAS_XREG_VAR_VALUE_ENUM_UINT8;

enum CNAS_XREG_SYSMSG_STATE_ENUM
{
    CNAS_XREG_SYSMSG_NOT_CURRENT    = 0,
    CNAS_XREG_SYSMSG_CURRENT        = 0x5a,
    CNAS_XREG_SYSMSG_STATE_BUTT
};
typedef VOS_UINT8 CNAS_XREG_SYSMSG_STATE_ENUM_UINT8;

enum CNAS_XREG_TIMER_STATE_ENUM
{
     CNAS_XREG_TIMER_NULL           = 0,
     CNAS_XREG_TIMER_RUNNING        = 0xa5,
     CNAS_XREG_TIMER_EXPIRED        = 0x5a,
     CNAS_XREG_TIMER_STATE_BUTT
};
typedef VOS_UINT8 CNAS_XREG_TIMER_STATE_ENUM_UINT8;

enum CNAS_XREG_ROAMING_STATE_ENUM
{
     CNAS_XREG_NO_ROAMING = 0,
     CNAS_XREG_SID_ROAMING,
     CNAS_XREG_NID_ROAMING,
     CNAS_XREG_ROAMING_BUTT
};
typedef VOS_UINT8 CNAS_XREG_ROAMING_STATE_UINT8;

enum CNAS_XREG_MNTN_MSGID_ENUM
{
    CNAS_XREG_MNTN_GLOBALIN         = 0x0000FF01,
    CNAS_XREG_MNTN_GLOBALOUT        = 0x0000FF02,
    CNAS_XREG_MNTN_SIDNID_LIST      = 0x0000FF03,
    CNAS_XREG_MNTN_ZONE_LIST        = 0x0000FF04,
    CNAS_XREG_MNTN_MSGID_BUTT
};
typedef VOS_UINT32 CNAS_XREG_MNTN_MSGID_ENUM_UINT32;

enum CNAS_XREG_BLKSYS_ENUM
{
    CNAS_XREG_BLKSYS_PCS_A = 0,
    CNAS_XREG_BLKSYS_PCS_B,
    CNAS_XREG_BLKSYS_PCS_C,
    CNAS_XREG_BLKSYS_PCS_D,
    CNAS_XREG_BLKSYS_PCS_E,
    CNAS_XREG_BLKSYS_PCS_F,
    CNAS_XREG_BLKSYS_CELL_A,
    CNAS_XREG_BLKSYS_CELL_B,
    CNAS_XREG_BLKSYS_BUTT
};
typedef VOS_UINT8 CNAS_XREG_BLKSYS_ENUM_UINT8;

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
typedef struct
{
    VOS_INT32                           lBaseLast;
    VOS_INT32                           lBaseLong;
    VOS_UINT32                          ulDistThrd;
}CNAS_XREG_DISTINFO_STRU;

typedef struct
{
    /*Protocol variable*/
    CNAS_XREG_VAR_VALUE_ENUM_UINT8      enRegEnabledFlag;       /*REG_ENABLED*/
    CNAS_XREG_VAR_VALUE_ENUM_UINT8      enDistRegFlag;          /*REG_DIST*/
    CNAS_XREG_VAR_VALUE_ENUM_UINT8      enRegisterFlag;         /*REGISTERED*/

    /*Private vairable*/
    CNAS_XREG_VAR_VALUE_ENUM_UINT8      enIsVerChange;          /* Version change flag */
    CNAS_XREG_VAR_VALUE_ENUM_UINT8      enIsTchHandoff;         /* Handoff to unreg system during TCH */
    VOS_UINT8                           aucRsv[3];
    CNAS_XREG_TIMER_STATE_ENUM_UINT8    enT57MState;            /*Power Up Timer State*/
    CNAS_XREG_TIMER_STATE_ENUM_UINT8    enRegTimerState;        /*Time Base's Timer State*/
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8    enCurRegType;
    VOS_UINT8                           ucPowerOffDeregFlg;     /* power offf dereg flg */

    /*System massage info*/
    CAS_CNAS_1X_CAS_STATE_ENUM_UINT8    enCasState;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    VOS_UINT16                          usBandClass;
    VOS_UINT32                          ulRegInitCount;         /*Timer Base begin*/
    VOS_UINT32                          ulRegCountMax;          /*Timer Base end*/
    VOS_UINT32                          ulRemainderTimerLen;    /* Remainder Timer Length */
    CNAS_XREG_DISTINFO_STRU             stDistInfo;             /*Distance info*/

    /* ��ά�ɲ�ʹ�� */
    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32    enRegTypeMntn;
}CNAS_XREG_REGSTATE_STRU;

typedef struct
{
    CNAS_XREG_SYSMSG_STATE_ENUM_UINT8   enAvailable;
    VOS_UINT8                           aucRsv[3];
    XSD_XREG_SYS_INFO_STRU              stSysInfo;
}CNAS_XREG_SYS_MSG_CONTENT_STRU;

typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
}CNAS_XREG_SID_NID_STRU;

typedef struct
{
    VOS_UINT8                           ucMobTermHome;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucCardSci;          /* �����ڿ��е�SCIֵ */
    VOS_UINT8                           ucLastSci;          /* �����ϴε�SCIֵ */
    VOS_UINT8                           ucCurrSci;          /* ���浱ǰ��SCIֵ */
    VOS_UINT8                           ucNoCardMode;       /* �޿�ǿ��ע���� */
    VOS_UINT8                           aucRsv[1];
}CNAS_XREG_HOME_INFO_STRU; /* Reserved in nv */

typedef struct
{
    VOS_INT32                           lBaseLat;
    VOS_INT32                           lBaseLong;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usRegDist;
    VOS_UINT16                          usRegZone;
    VOS_UINT16                          usSid;
    VOS_UINT8                           ucMultNids;
    VOS_UINT8                           ucMultSids;
    VOS_UINT8                           ucTotalZones;
    VOS_UINT8                           ucZoneTimer;
}CNAS_XREG_MSRM_STRU;   /* Mobile Station Registered Message, ����:c_f_dsch_MSRM */

typedef struct
{
    VOS_UINT32                          ulOrderDesc;
    VOS_UINT32                          ulNnnn;
    VOS_UINT8                           ucOrder;
    VOS_UINT8                           ucOrdq;
    VOS_UINT8                           ucNnnnPresent;
    VOS_UINT8                           ucRfu;
}CNAS_XREG_ORDM_STRU;            /* ����: c_F_Orders */

typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */
    CNAS_XREG_MNTN_MSGID_ENUM_UINT32        enMsgId;                /* _H2ASN_Skip */
    VOS_UINT32                              ulEventID;
    CNAS_XREG_L1_STA_ENUM_UINT32            enCurState;
    CNAS_XREG_REGSTATE_STRU                 stCnasXregStateInfo;
    CNAS_XREG_SYS_MSG_CONTENT_STRU          stCnasXregSysMsgCont;
    CNAS_XREG_HOME_INFO_STRU                stCnasXregHomeInfo;
}CNAS_XREG_MNTN_MSG_STRU;


typedef struct
{
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8    enRegType;
    CAS_CNAS_1X_EST_RSLT_ENUM_UINT8             enEstRslt;
    VOS_UINT16                                  usRsv;
    VOS_UINT32                                  ulSlice;
}CNAS_XREG_RECORD_ITEM_STRU;

typedef struct
{
    VOS_UINT32                          ulIndex;
    CNAS_XREG_RECORD_ITEM_STRU          stRecordItem[CNAS_XREG_MAX_ITEM_NUM];
}CNAS_XREG_DBG_STAT_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern CNAS_XREG_REGSTATE_STRU* CNAS_XREG_GetRegStateAddr(VOS_VOID);

extern CNAS_XREG_SYS_MSG_CONTENT_STRU* CNAS_XREG_GetSysMsgAddr(VOS_VOID);

extern VOS_VOID CNAS_XREG_StartTime(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen);

extern VOS_VOID CNAS_XREG_SetRegEnabled(VOS_UINT16 usSid, VOS_UINT16 usNid, VOS_UINT8  ucHomeReg, VOS_UINT8  ucSidRoamReg, VOS_UINT8  ucNidRoamReg);

extern VOS_VOID CNAS_XREG_RegSuccProc(VOS_VOID);

extern VOS_VOID CNAS_XREG_RegFailProc(VOS_VOID);

extern VOS_VOID CNAS_XREG_MobTermSet(VOS_UINT16 usSid, VOS_UINT16 usNid);

extern VOS_VOID CNAS_XREG_MSRMProc(CNAS_XREG_MSRM_STRU *pstMsrm);

extern VOS_UINT32 CNAS_XREG_ORDMCheck(CNAS_XREG_ORDM_STRU *pstOrdm);

extern VOS_UINT32 CNAS_XREG_GetCountMax(VOS_UINT8 ucRegPeriod);

extern VOS_VOID CNAS_XREG_RegTimerStart(XSD_XREG_SYS_INFO_STRU *pstSysInfo, CNAS_XREG_REGSTATE_STRU  *pstSysState);

extern VOS_VOID CNAS_XREG_RegTimerStop(VOS_VOID);

extern VOS_VOID CNAS_XREG_RegTimerRefresh(VOS_UINT8 ucRegPeriod);

extern VOS_BOOL CNAS_XREG_PowerUpCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU *pstSysInfoSave, CNAS_XREG_REGSTATE_STRU *pstSysState);

extern VOS_BOOL CNAS_XREG_PowerUpParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU *pstSysInfoSave, CNAS_XREG_REGSTATE_STRU *pstSysState);

extern VOS_BOOL CNAS_XREG_TimerBaseCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState);

extern VOS_BOOL CNAS_XREG_PowerDownCheck(VOS_VOID);

extern VOS_BOOL CNAS_XREG_DistanceCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                    CNAS_XREG_REGSTATE_STRU          *pstSysState);
extern VOS_BOOL CNAS_XREG_ZoneCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                               CNAS_XREG_REGSTATE_STRU         *pstSysState);

extern VOS_BOOL CNAS_XREG_SciParaCheck(VOS_VOID);

extern VOS_BOOL CNAS_XREG_TermParaCheck(VOS_VOID);

extern VOS_BOOL CNAS_XREG_ParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                CNAS_XREG_REGSTATE_STRU          *pstSysState);

extern VOS_BOOL CNAS_XREG_UserZoneCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState);

extern VOS_BOOL CNAS_XREG_EncryptCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState);

extern CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 CNAS_XREG_IdleRegCheck(VOS_VOID);

extern VOS_UINT32 CNAS_XREG_DSCHDataTrans(CAS_CNAS_1X_DSCH_DATA_IND_STRU *pstDschData);

extern VOS_UINT32 CNAS_XREG_CSCHDataTrans(CAS_CNAS_1X_CSCH_DATA_IND_STRU *pstCschData);

extern VOS_VOID CNAS_XREG_ClearGlobal(VOS_VOID);

extern VOS_VOID CNAS_XREG_GlobalMntn(VOS_UINT32 ulMsgID,VOS_UINT32 ulEvent);

extern CNAS_XREG_BLKSYS_ENUM_UINT8 CNAS_XREG_BandFreqToBlkSys(VOS_UINT16 usBandClass, VOS_UINT16 usFreq);

extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

extern VOS_UINT32 CNAS_XREG_SquareRoot(VOS_UINT32 ulNumber);

extern VOS_UINT32 CNAS_XREG_CalcDistance(
    VOS_INT32                           lOldLat,
    VOS_INT32                           lOldLong,
    VOS_INT32                           lNewLat,
    VOS_INT32                           lNewLong
);


#if (VOS_RTOSCK == VOS_OS_VER)
extern double cos(double angle);
#endif  /*(VOS_RTOSCK == VOS_OS_VER)*/

extern VOS_VOID CNAS_XREG_RecordRegRslt(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType,
                                            CAS_CNAS_1X_EST_RSLT_ENUM_UINT8 enEstRslt);

extern VOS_VOID CNAS_XREG_RecordShow(VOS_VOID);

extern VOS_VOID CNAS_XREG_SetPowerOffDeregFlg(
    VOS_UINT8                           ucPowerOffDeregFlg
);

extern VOS_UINT8 CNAS_XREG_GetPowerOffDeregFlg(VOS_VOID);

extern VOS_BOOL CNAS_XREG_IsSetMobTerm(
    VOS_UINT8                           ucMobTermForNid,
    VOS_UINT8                           ucMobTermForSid,
    VOS_UINT8                           ucMobTermHome
);

extern VOS_VOID CNAS_XREG_SetCardSciValue(
    VOS_UINT8                           ucSciValue
);

extern VOS_UINT8 CNAS_XREG_GetCardSciValue(VOS_VOID);

extern VOS_VOID CNAS_XREG_SetLastSciValue(
    VOS_UINT8                           ucSciValue
);

extern VOS_UINT8 CNAS_XREG_GetLastSciValue(VOS_VOID);

extern VOS_VOID CNAS_XREG_CalcSciValue(VOS_VOID);


extern VOS_VOID CNAS_XREG_BlkSysChange(
    XSD_XREG_SYS_INFO_STRU             *pstNewSysInfo,
    XSD_XREG_SYS_INFO_STRU             *pstOldSysInfo
);

extern VOS_VOID CNAS_XREG_EnableNoCardMode(VOS_VOID);
extern VOS_UINT8 CNAS_XREG_GetNoCardMode(VOS_VOID);

extern VOS_VOID  CNAS_XREG_SetOmRegReportFlag(
    NAS_OM_REPORT_ACTION_ENUM_UINT8     enRptAction
);

extern NAS_OM_REPORT_ACTION_ENUM_UINT8  CNAS_XREG_GetOmRegReportFlag(VOS_VOID);

VOS_VOID    CNAS_XREG_ProcCardReadFileCnf_EF_TERM(
    struct MsgCB                       *pstMsg
);

VOS_VOID    CNAS_XREG_ProcCardReadFileCnf_EF_SSCI(
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XREG_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
);
VOS_VOID CAS_XREG_GetTrueCodeByComplementCode(
                VOS_INT32              *plTrueCode,
                VOS_UINT32              ulCompCode,
                VOS_UINT8               ucCompLen
);

VOS_VOID CNAS_XREG_TchHandoffProc(
    XSD_XREG_SYS_INFO_IND_STRU         *pstSysInfoMsg
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

