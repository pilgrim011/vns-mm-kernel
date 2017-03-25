/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasEhsmMsgPrioCompare.h
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2015��5��27��
  ����޸�   :
  ��������   : CnasEhsmMsgPrioCompare.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��27��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasEhsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_UNIVERAL_MSG_ID                (0xFFFFFFFF)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_EHSM_ABORT_FSM_TYPE_UINT8
 �ṹ˵��  : Abort����
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : ����
*****************************************************************************/
enum CNAS_EHSM_ABORT_FSM_TYPE
{
    CNAS_EHSM_ABORT_FSM_IMMEDIATELY           = 0,
    CNAS_EHSM_ABORT_FSM_DELAY                 = 1,
    CNAS_EHSM_ABORT_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_ABORT_FSM_TYPE_UINT8;

/*****************************************************************************
 ö����    : CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM
 �ṹ˵��  : EHSM��Ϣ���ȼ��ȽϵĽ��
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM
{
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT              ,                        /* �����ȼ���Ϣ�жϵ�ǰ���� */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE              ,                        /* ��Ҫ�������Ϣ */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM            ,                        /* ����״̬���д��� */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD            ,                        /* ֱ�Ӷ�������Ϣ */

    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_BUTT
};
typedef VOS_UINT32 CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32;

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
 �ṹ��    : CNAS_EHSM_MSG_COMPARE_FUNC
 �ṹ˵��  : ���ȼ��Ƚϴ����������Ͷ���
 1.��    ��   : 2013��7��22��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef VOS_UINT32 (*CNAS_EHSM_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

/*****************************************************************************
 �ṹ��    : CNAS_EHSM_MSG_COMPARE_STRU
 �ṹ˵��  : �ȽϺ����ṹ
 1.��    ��   : 2013��7��22��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* ��Ƚϵ���Ϣ */
    CNAS_EHSM_MSG_COMPARE_FUNC          pfCompareFun;           /* �ȽϺ��� */
}  CNAS_EHSM_MSG_COMPARE_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_EHSM_MSG_COMPARE_STRU
 �ṹ˵��  : �ȽϺ����ṹ
 1.��    ��   : 2013��7��22��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId;                /* ��ǰ���е�FSM ID */
    VOS_UINT32                          ulSize;                 /* ������Ĵ�С�ֽ�������ACT�ṹ�Ĵ�С */
    CNAS_EHSM_MSG_COMPARE_STRU         *pfCompareTbl;           /* �ȽϺ����� */
}  CNAS_EHSM_FSM_MSG_COMPARE_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 CNAS_EHSM_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);


/*****************************************************************************
 �ṹ��    : CNAS_EHSM_COMPARE_TBL_ITEM
 �ṹ˵��  : ÿ������״̬���ȽϺ�����ṹ
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : ����
*****************************************************************************/
#define CNAS_EHSM_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}

/*****************************************************************************
 �ṹ��    : CNAS_EHSM_FSM_COMPARE_TBL_ITEM
 �ṹ˵��  : �ȽϺ�����ṹ
 1.��    ��   : 2013��7��22��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
#define CNAS_EHSM_FSM_COMPARE_TBL_ITEM(enFsmId, astFsmCompareTbl)\
{\
    ( enFsmId),\
    ((sizeof(astFsmCompareTbl))/sizeof(CNAS_EHSM_MSG_COMPARE_STRU)),\
    (astFsmCompareTbl)\
}

VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

CNAS_EHSM_MSG_COMPARE_FUNC  CNAS_EHSM_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
);

VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnReconnReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
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


