/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregCtx.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��7��3��
  ����޸�   :
  ��������   : CnasXregCtx.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��3��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XREG_CTX_H__
#define __CNAS_XREG_CTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ״̬��ջ����� */
#define CNAS_XREG_MAX_FSM_STACK_DEPTH                       (4)

/* ��Ϣ����󳤶ȣ�����״̬������������Ϣ��CACHE��Ϣ */
#define CNAS_XREG_MAX_MSG_BUFFER_LEN                        (1600)

/* ������Ϣ���е������� */
#define CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM                   (8)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : CNAS_XREG_FSM_ID_ENUM
 ö��˵��  : ״̬��IDö�ٶ���
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XREG_FSM_ID_ENUM
{
    /***********************************************************************
     * XREG L1״̬����ʶ
     ***********************************************************************/
    /* L1 main״̬���ı�ʶ */
    CNAS_XREG_FSM_L1_MAIN                                   = 0x00,

    /***********************************************************************
     * XREG L2״̬���ı�ʶ
     ***********************************************************************/
    /* L2 ����״̬�� */
    CNAS_XREG_FSM_SWITCH_ON                                 = 0x01,

    /* L2 ע��״̬�� */
    CNAS_XREG_FSM_REGING                                    = 0x02,

    CNAS_XREG_FSM_BUTT
};
typedef VOS_UINT32 CNAS_XREG_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XREG_READ_CARD_FILES_CNF_ENUM
 �ṹ˵��  : ���ڱ�Ƕ�ȡ���ļ��Ļظ���Ϣ
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : ����

*****************************************************************************/
enum   CNAS_XREG_READ_CARD_FILES_CNF_ENUM
{
    CNAS_XREG_READ_CARD_FILE_FLG_NULL                       = 0x00,             /* ��ʼֵ */

    CNAS_XREG_READ_CARD_FILE_TERM_FLG                       = 0x01,             /* EFterm�ļ� */

    CNAS_XREG_READ_CARD_FILE_SSCI_FLG                       = 0x02,             /* EFssci�ļ� */

    CNAS_XREG_READ_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM
 �ṹ˵��  : ���ڱ�ǿ��ļ��ı�
 1.��    ��   : 2015��10��25��
   ��    ��   : d00212987
   �޸�����   : ����

*****************************************************************************/
enum   CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM
{
    CNAS_XREG_REFRESH_CARD_FILE_FLG_NULL                       = 0x00,             /* ��ʼֵ */

    CNAS_XREG_REFRESH_CARD_FILE_TERM_FLG                       = 0x01,             /* EFterm�ļ� */

    CNAS_XREG_REFRESH_CARD_FILE_SSCI_FLG                       = 0x02,             /* EFssci�ļ� */

    CNAS_XREG_REFRESH_CARD_FILE_SSCI_TERM_FLG                  = 0x03,             /* EFterm and EFssci�ļ� */

    CNAS_XREG_REFRESH_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM
 �ṹ˵��  : ���ڱ�ǿ��ļ��ı�
 1.��    ��   : 2015��10��25��
   ��    ��   : d00212987
   �޸�����   : ����

*****************************************************************************/
enum   CNAS_XREG_CARD_FILES_CHANGE_ENUM
{
    CNAS_XREG_CARD_FILE_CHANGE_FLG_NULL                       = 0x00,             /* ��ʼֵ */

    CNAS_XREG_CARD_FILE_TERM_CHANGE_FLG                       = 0x01,             /* EFterm�ļ� */

    CNAS_XREG_CARD_FILE_SSCI_CHANGE_FLG                       = 0x02,             /* EFssci�ļ� */

    CNAS_XREG_CARD_FILE_SSCI_TERM_CHANGE_FLG                  = 0x03,             /* EFterm and EFssci�ļ� */

    CNAS_XREG_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32;
/*****************************************************************************
 �ṹ��    : CNAS_XREG_CACHE_MSG_QUEUE_STRU
 �ṹ˵��  : �������Ϣ����
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32        enRefreshReadCard;               /* Refresh Card Ind ������Ϣ�ظ� */
    CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32             enCardFileChange;        /* ���ļ��仯 */
}CNAS_XREG_REFRESH_CARD_FILES_STATUS_STRU;


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
 �ṹ��    : CNAS_XREG_MSG_STRU
 �ṹ˵��  : XREG��Ϣ�ṹ��״̬������������Ϣ��CACHE��Ϣ��ʹ�ô˽ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_XREG_MAX_MSG_BUFFER_LEN];
}CNAS_XREG_MSG_STRU;

 /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
/*****************************************************************************
 �ṹ��    : CNAS_XREG_CACHE_MSG_QUEUE_STRU
 �ṹ˵��  : �������Ϣ����
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrIndex;                            /* ��¼��ǰ�������index */
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastCacheMsg[CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM]; /* XREG����Ϣ��������ָ�룬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}CNAS_XREG_CACHE_MSG_QUEUE_STRU;
 /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_REGISTER_CTX_STRU
 �ṹ˵��  : ���ע��״̬������������Ϣ
  1.��    ��   : 2014��07��07��
    ��    ��   : h00246512
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    CNAS_XREG_REFRESH_CARD_FILES_STATUS_STRU            stXregRefreshCardFileStatus;
}CNAS_XREG_PREPROC_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_REGISTER_CTX_STRU
 �ṹ˵��  : ���ע��״̬������������Ϣ
  1.��    ��   : 2014��07��07��
    ��    ��   : h00246512
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* ���ε������漰 */
    VOS_UINT8                           aucRsved[4];
}CNAS_XREG_FSM_REGISTER_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_L1_MAIN_CTX_STRU
 �ṹ˵��  : ���L1״̬������������Ϣ
  1.��    ��   : 2014��07��04��
    ��    ��   : y00245242
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* ���ε������漰 */
    VOS_UINT8                           aucRsved[4];
}CNAS_XREG_FSM_L1_MAIN_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_SWITCH_ON_CTX_STRU
 �ṹ˵��  : ��ſ���״̬������������Ϣ
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulXregReadCardFileFlg;                  /* ��ǿ��ļ��Ƿ��ȡ��� */
    VOS_UINT8                           aucReserved[4];
}CNAS_XREG_FSM_SWITCH_ON_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_EXTRA_CTX_UNION
 �ṹ˵��  : ״̬��״̬�����ṹ,״̬����������Ϣ
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef union
{
    CNAS_XREG_FSM_REGISTER_CTX_STRU     stRegisterCtx;

    CNAS_XREG_FSM_L1_MAIN_CTX_STRU      stL1MainCtx;

    CNAS_XREG_FSM_SWITCH_ON_CTX_STRU    stSwitchOnCtx;
}CNAS_XREG_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId;

    /* �ϲ�״̬����ʶ */
    CNAS_XREG_FSM_ID_ENUM_UINT32        enParentFsmId;

    /* �ϲ�״̬�������Ϣ���� */
    VOS_UINT32                          ulParentEventType;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;

    /* �����ϢMSGID������  */
    CNAS_XREG_MSG_STRU                  stEntryMsg;

    /* ״̬������ */
    CNAS_XREG_FSM_EXTRA_CTX_UNION       unFsmCtx;
}CNAS_XREG_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XREG_FSM_STACK_STRU
 �ṹ˵��  : ״̬��ջ�����ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */
    VOS_UINT16                          usStackPopFlg;                          /* ��ǰջpop��־ */
    CNAS_XREG_FSM_CTX_STRU              astFsmStack[CNAS_XREG_MAX_FSM_STACK_DEPTH];  /* ״̬��ջ����� */
}CNAS_XREG_FSM_STACK_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XREG_CTX_STRU
 �ṹ˵��  : XREG��������
 1.��    ��   : 2014��07��03��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* Ԥ���� */
    CNAS_XREG_PREPROC_CTX_STRU          stRegPreProcCtx;

    /**************************************************************************
                        CNAS XREG״̬��״̬����״̬ջ
     **************************************************************************/
    CNAS_XREG_FSM_CTX_STRU              stCurFsm;                               /* ״̬����ǰ��״̬������ */
    CNAS_XREG_FSM_STACK_STRU            stFsmStack;                             /* ״̬����״̬��ջ����   */

    /* CNAS XREG������Ϣ���� */
    CNAS_XREG_CACHE_MSG_QUEUE_STRU      stCacheMsgQueue;
}CNAS_XREG_CTX_STRU;


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

VOS_UINT32 CNAS_XREG_GetFsmTopState(VOS_VOID);

CNAS_XREG_CTX_STRU* CNAS_XREG_GetCtxAddr(VOS_VOID);
CNAS_XREG_FSM_CTX_STRU* CNAS_XREG_GetCurFsmAddr(VOS_VOID);
NAS_FSM_DESC_STRU* CNAS_XREG_GetCurFsmDesc(VOS_VOID);
CNAS_XREG_FSM_ID_ENUM_UINT32 CNAS_XREG_GetCurrFsmId(VOS_VOID);
CNAS_XREG_MSG_STRU* CNAS_XREG_GetCurrFsmEntryMsgAddr(VOS_VOID);
CNAS_XREG_FSM_STACK_STRU* CNAS_XREG_GetFsmStackAddr(VOS_VOID);
VOS_VOID CNAS_XREG_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT16  CNAS_XREG_GetFsmStackDepth(VOS_VOID);
VOS_UINT32  CNAS_XREG_GetNextCachedMsg(
    CNAS_XREG_MSG_STRU                 *pstEntryMsg
);
VOS_VOID  CNAS_XREG_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);
VOS_UINT16  CNAS_XREG_GetFsmStackPopFlg(VOS_VOID);
VOS_UINT32  CNAS_XREG_GetCacheMsgNum(VOS_VOID);
CNAS_XREG_CACHE_MSG_QUEUE_STRU* CNAS_XREG_GetCacheMsgAddr(VOS_VOID);

VOS_VOID CNAS_XREG_InitCtx(VOS_VOID);
VOS_VOID CNAS_XREG_InitFsmCtx_L1Main(VOS_VOID);

VOS_VOID CNAS_XREG_PushFsm(
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack,
    CNAS_XREG_FSM_CTX_STRU             *pstNewFsm
);

VOS_VOID CNAS_XREG_InitFsmL2(
    CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId
);

VOS_VOID CNAS_XREG_QuitFsmL2(VOS_VOID);

VOS_VOID CNAS_XREG_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

 /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
VOS_VOID  CNAS_XREG_SaveMsgToCache(
    VOS_UINT32                          ulEventType,
    VOS_UINT8                           *pucMsg
);
 /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */
 
VOS_VOID  CNAS_XREG_LoadSubFsm(
    CNAS_XREG_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XREG_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID CNAS_XREG_ClearCacheMsg(VOS_VOID);

VOS_VOID CNAS_XREG_InitFsmCtx_SwitchOn(VOS_VOID);

CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID);

VOS_VOID CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
);

VOS_VOID CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
);

CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32 CNAS_XREG_GetReadCardFilesIndFlg(VOS_VOID);

VOS_VOID CNAS_XREG_SetReadCardFilesIndFlg(
    CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32    enRefreshReadCard
);

VOS_VOID CNAS_XREG_ClearReadCardFilesIndFlg(
    VOS_UINT32                          ulEfId
);

CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32 CNAS_XREG_GetCardFilesChangeFlg(VOS_VOID);

VOS_VOID CNAS_XREG_SetCardFilesChangeFlg(
    CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32    enCardFileChange
);

VOS_VOID CNAS_XREG_ClearRefreshCardFilesCtx(VOS_VOID);

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

#endif /* end of CnasXregCtx.h */
