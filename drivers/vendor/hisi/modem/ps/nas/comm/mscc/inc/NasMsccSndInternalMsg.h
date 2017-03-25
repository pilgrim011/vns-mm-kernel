

#ifndef __NAS_MSCC_SND_INTERNAL_MSG_H__
#define __NAS_MSCC_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasMsccCtx.h"
#include "NasMsccMntn.h"



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
/****************************************************************************
Enum name       :   NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16
Description     :   Contains the Internal Message types used in MSCC.
Modify History:
    1)  Date    :   2015-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-11-05
        Author  :   W00176964
        Modify content : DTS2015070910837;����CL intersys״̬���˳����
****************************************************************************/
enum NAS_MSCC_INTERNAL_MSG_TYPE_ENUM
{
    ID_NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF = ID_NAS_MSCC_MNTN_INTERNAL_MSG_BASE,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU*/
    ID_NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF                                     ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_SYS_ACQ_REQ                                            ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_ACQ_STRU*/
    ID_NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF                                       ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU */
    ID_NAS_MSCC_MSCC_ABORT_FSM_REQ                                          ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_ABORT_REQ_STRU*/

    ID_NAS_MSCC_MSCC_BSR_RSLT_CNF                                           ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF                                       ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF                                    ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_PIF_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16;



enum NAS_MSCC_SWITCH_ON_RESULT_ENUM
{
    NAS_MSCC_SWITCH_ON_RESULT_FAILURE   = 0x00000000,
    NAS_MSCC_SWITCH_ON_RESULT_SUCCESS   = 0x00000001,
    NAS_MSCC_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_SWITCH_ON_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM
 ö��˵��  : result of system acquire fsm
 1.��    ��   : 2015��04��03��
   ��    ��   : m00312079
   �޸�����   : Create
 2.��    ��   : 2015��08��25��
   ��    ��   : m00312079
   �޸�����   : DTS2015082004682:����L2C���
*****************************************************************************/
enum NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C                     = 0x00000003,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000004
};
typedef VOS_UINT32 NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;



enum NAS_MSCC_BSR_RESULT_ENUM
{
    NAS_MSCC_BSR_RESULT_SUCCESS,
    NAS_MSCC_BSR_RESULT_FAILURE,
    NAS_MSCC_BSR_RESULT_ABORT,
    NAS_MSCC_BSR_RESULT_L2C,
    NAS_MSCC_BSR_RESULT_BUTT
};
typedef VOS_UINT16 NAS_MSCC_BSR_RESULT_ENUM_UINT16;

/****************************************************************************
Enum name       :   NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8
Description     :   �Ƿ���Ҫ��������
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

enum NAS_MSCC_BSR_ACQ_SYS_ENUM
{
    NAS_MSCC_BSR_NEED_ACQ_SYS,           /* ��Ҫ���� */
    NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,       /* ����Ҫ���� */
    NAS_MSCC_BSR_ACQ_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8;

/****************************************************************************
Enum name       :   NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8
Description     :   �Ƿ���Ҫ����retry��ʱ��
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

enum NAS_MSCC_BSR_RETRY_TIMER_ENUM
{
    NAS_MSCC_BSR_NEED_START_RETRY_TIMER,          /* ������retry��ʱ�� */
    NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER,      /* ��������retry��ʱ�� */
    NAS_MSCC_BSR_RETRY_TIMER_BUTT
};
typedef VOS_UINT8 NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8;

/*****************************************************************************
 Name    : NAS_MSCC_POWEROFF_RSLT_ENUM
 Description  : Enum definition for Power Off result.
 History     :
  1.Date     : 2015-04-14
    Author   : w00176964
    Modify   : create
 2.��    ��   : 2016��1��6��
   ��    ��   : w00242748
   �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
enum NAS_MSCC_POWEROFF_RSLT_ENUM
{
    NAS_MSCC_POWEROFF_RSLT_POWER_OFF,
    NAS_MSCC_POWEROFF_RSLT_POWER_SAVE,
    NAS_MSCC_POWEROFF_RSLT_POWER_SAVE_HRPD_LTE,

    NAS_MSCC_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32;



enum NAS_MSCC_SYS_CFG_RESULT_ENUM
{
    NAS_MSCC_SYS_CFG_RESULT_SUCCESS   = 0x00000000,
    NAS_MSCC_SYS_CFG_RESULT_FAILURE   = 0x00000001,
    NAS_MSCC_SYS_CFG_RESULT_BUTT      = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32;


/****************************************************************************
Enum name       :   NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32
Description     :   CL��ϵͳ�˳����
Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :Create
****************************************************************************/
enum NAS_MSCC_CL_INTERSYS_RESULT_ENUM
{
    /* L��ѡ�����ض���C�ɹ�ʱ����
       C��ѡ��Lʱ���ɹ� */
    NAS_MSCC_CL_INTERSYS_RESULT_SUCC,

    /* L��ѡ�����ض���Cʧ���ֻ��˵�Lʱ����ϵͳ���Ϊʧ�ܣ�
       C��ѡ��Lʧ���ֻ��˵�Cʱ����ϵͳ���Ϊʧ�� */
    NAS_MSCC_CL_INTERSYS_RESULT_FAIL,

    /* ��ϵͳ�����ʱ���˳���ϵͳʱ���Ϊabort */
    NAS_MSCC_CL_INTERSYS_RESULT_ABORTED,

    NAS_MSCC_CL_INTERSYS_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32;


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
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32                      enRslt;
}NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU;


/****************************************************************************
Structure name  :   NAS_MSCC_MSCC_SYS_ACQ_STRU
Description     :   Contains the system acquire reqeust message structure.
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
    2)  Date    :   2015-12-30
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE������������
****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enLteSrchType;/* ����LTEָʾ���������� */
}NAS_MSCC_MSCC_SYS_ACQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
    VOS_UINT8                                               ucSearchHrpdFlag;
    VOS_UINT8                                               ucSearchLteFlag;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;                 /* _H2ASN_Skip */
    NAS_MSCC_BSR_RESULT_ENUM_UINT16                         enRslt;                  /* BSR ��� */
    NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8                         enIsNeedAcqSys;          /* �Ƿ���Ҫ���� */
    NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8                     enIsNeedStartRetryTimer; /* �Ƿ�Ҫ����retry��ʱ�� */
    VOS_UINT8                                               ucReserved[2];
}NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32                     enRslt;
}NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU;


/****************************************************************************
Structure name  :   NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU
Description     :   CL��ϵͳ״̬���˳����
Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :    Create
****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enRslt;
}NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU;



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
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_MSCC_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    NAS_MSCC_INTERNAL_MSG_DATA          stMsgData;
}NAS_MSCC_INTERNAL_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID NAS_MSCC_SndPowerOffRslt(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
);

VOS_VOID NAS_MSCC_SndSwitchOnRslt(
    VOS_UINT32                          ulResult
);

VOS_VOID NAS_MSCC_SndAbortFsmReq(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_SndInternalSysAcqReq(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enLteSrchType
);

VOS_VOID NAS_MSCC_SndInternalSysAcqRsltCnf(
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt,
    VOS_UINT8                                               ucSearchLteFlag,
    VOS_UINT8                                               ucSearchHrpdFlag
);

VOS_VOID NAS_MSCC_SndBsrResult(
    NAS_MSCC_BSR_RESULT_ENUM_UINT16     enBsrRslt,
    NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8     enIsNeedAcqSys,
    NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8 enIsNeedStartRetryTimer
);
#endif

VOS_VOID NAS_MSCC_SndSysCfgRslt(
    NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32      ulResult
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_SndCLInterSysRsltCnf(
    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt
);
#endif

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

#endif /* end of CnasXsdSndInternalMsg.h */

