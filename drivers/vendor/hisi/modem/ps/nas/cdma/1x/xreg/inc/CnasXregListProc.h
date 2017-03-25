/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregListProc.h
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��05��
    ��    ��   :
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _CNAS_XREG_LIST_PROC_H_
#define _CNAS_XREG_LIST_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "CnasXregProcess.h"
#include  "hi_list.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define CNAS_XREG_ZONE_NODE_MAX_NUM     (7)     /* Э��涨����Сֵ:N9m */
#define CNAX_XREG_SIDNID_NODE_MAX_NUM   (4)     /* Э��涨����Сֵ:N10m */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum CNAS_XREG_LIST_ENUM
{
    CNAS_XREG_ZONE_USED_LIST_ID = 0,
    CNAS_XREG_ZONE_FREE_LIST_ID,
    CNAS_XREG_SIDNID_USED_LIST_ID,
    CNAS_XREG_SIDNID_FREE_LIST_ID,
    CNAS_XREG_LIST_BUTT
};

typedef VOS_UINT8  CNAS_XREG_LIST_ID_ENUM_UINT8;

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
    HI_LIST_S                           stListNode;
    VOS_UINT32                          ulSecNum;
    VOS_UINT16                          usRegZone;
    VOS_UINT16                          usRsv;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usBandClass;
}CNAS_XREG_ZONE_NODE_STRU;

typedef struct
{
    HI_LIST_S                           stListNode;
    VOS_UINT32                          ulSecNum;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usBandClass;
}CNAS_XREG_SIDNID_NODE_STRU;

typedef struct
{
    VOS_UINT32                          ulNodeCount;
    HI_LIST_S                           stListHeader;
}CNAS_XREG_LIST_HEADER_STRU;

typedef struct
{
    VOS_UINT32                          ulPreSlice;     /* ��һ�ε�SLICEֵ����λΪ1/32768�� */
    VOS_UINT32                          ulSecNum;       /* �ӵ����ϵ��ʼʱ�䣬��λΪ�� */
}CNAS_XREG_TIME_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CNAS_XREG_MNTN_MSGID_ENUM_UINT32    enMsgId;
    VOS_UINT32                          ulCurSlice;
    CNAS_XREG_ZONE_NODE_STRU            astZoneNode[CNAS_XREG_ZONE_NODE_MAX_NUM];
}CNAS_XREG_ZONE_LIST_MNTN_STRU;

typedef struct
{
    VOS_MSG_HEADER
    CNAS_XREG_MNTN_MSGID_ENUM_UINT32    enMsgId;
    CNAS_XREG_TIME_INFO_STRU            stTimeInfo;
    CNAS_XREG_SIDNID_NODE_STRU          astSidNidNode[CNAX_XREG_SIDNID_NODE_MAX_NUM];
}CNAS_XREG_SIDNID_LIST_MNTN_STRU;

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
VOS_UINT8 CNAS_XREG_GetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_SetNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId, VOS_UINT32 ulNodeCount);

VOS_VOID CNAS_XREG_IncNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_DecNodeCount(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

HI_LIST_S* CNAS_XREG_GetListHeader(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

HI_LIST_S* CNAS_XREG_AllocListNode(CNAS_XREG_LIST_ID_ENUM_UINT8 enListId);

VOS_VOID CNAS_XREG_RelCurrZoneNode(VOS_VOID);

VOS_VOID CNAS_XREG_RelZoneListNode(HI_LIST_S *pstZoneNode);

VOS_VOID CNAS_XREG_RelCurrSidNidNode(VOS_VOID);

VOS_VOID CNAS_XREG_RelSidNidListNode(HI_LIST_S *pstSidNidNode);

VOS_VOID CNAS_XREG_InitList(VOS_VOID);

VOS_VOID CNAS_XREG_ClearList(VOS_VOID);

VOS_VOID CNAS_XREG_RestoreList(VOS_VOID);

VOS_VOID CNAS_XREG_SaveList(VOS_VOID);

VOS_VOID CNAS_XREG_AddZoneNode(CNAS_XREG_ZONE_NODE_STRU *pstZoneNode);

VOS_VOID CNAS_XREG_AddCurrZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                        VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_AddCurrSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid,
                                                    VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_AddSidNidNode(CNAS_XREG_SIDNID_NODE_STRU *pstSidNidNode);

VOS_VOID CNAS_XREG_RefreshLists(VOS_VOID);

VOS_VOID CNAS_XREG_TotalZones(VOS_UINT8 ucRegZoneNum);

VOS_VOID CNAS_XREG_DelNodesByBandBlkSys(XSD_XREG_SYS_INFO_STRU *pstSysInfo);

CNAS_XREG_ZONE_NODE_STRU *CNAS_XREG_FindZoneNode(VOS_UINT16 usSid, VOS_UINT16 usNid, VOS_UINT16 usRegZone);

CNAS_XREG_SIDNID_NODE_STRU *CNAS_XREG_FindSidNidNode(VOS_UINT16 usSid, VOS_UINT16 usNid);

VOS_VOID CNAS_XREG_UpdateZoneList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid, VOS_UINT16 usNid,
                                    VOS_UINT16 usRegZone, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_UpdateSidNidList(XSD_XREG_SYS_INFO_STRU *pstSysInfo, VOS_UINT16 usSid,
                                                VOS_UINT16 usNid, VOS_UINT8 ucZoneTimer);

VOS_VOID CNAS_XREG_DelMultSids(VOS_VOID);

VOS_VOID CNAS_XREG_DelMultNids(VOS_VOID);

VOS_UINT32 CNAS_XREG_SidNidListIsEmpty(VOS_VOID);
VOS_UINT32 CNAS_XREG_GetSlice(VOS_VOID);

VOS_VOID CNAS_XREG_SidNidListMntn(VOS_VOID);
VOS_VOID CNAS_XREG_ZoneListMntn(VOS_VOID);

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

