/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

******************************************************************************
    File name   : ImsaLrrcInterface.h
    Description : Imsa��Lrrc ͷ�ļ�
    History     :
      1.leili 00132387   2013-10-11  Draft Enact


******************************************************************************/

#ifndef __IMSALRRCINTERFACE_H__
#define __IMSALRRCINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "LPSCommon.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define  IMSA_LRRC_MSG_HDR   (PS_MSG_ID_IMSA_TO_ERRC_BASE)





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
 ö����    : IMSA_LRRC_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IMSA��LRRC֮�����Ϣ�ӿ�
 1.��    ��   : 2014��7��26��
   ��    ��   : c00134407
   �޸�����   : �½�
*****************************************************************************/
enum    IMSA_LRRC_MSG_ID_ENUM
{
    ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY     = (IMSA_LRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU */
    ID_IMSA_LRRC_END_SESSION_NOTIFY       = (IMSA_LRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice IMSA_LRRC_END_SESSION_NOTIFY_STRU */

    ID_IMSA_LRRC_HIFI_SYNC_SWITCH_IND     = (IMSA_LRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU */

    ID_IMSA_LRRC_VOLTE_STATUS_NOTIFY      = (IMSA_LRRC_MSG_HDR + 0x03),    /* _H2ASN_MsgChoice IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU */

    ID_IMSA_LRRC_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32   IMSA_LRRC_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : IMSA_LRRC_SESSION_TYPE_ENUM_UINT8
 ö��˵��  : SESSION����
 1.��    ��   : 2014��5��22��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum IMSA_LRRC_SESSION_TYPE_ENUM
{
    IMSA_LRRC_SESSION_TYPE_MO_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_MT_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_EMERGENCY_CALL,
    IMSA_LRRC_SESSION_TYPE_MO_SS,
    IMSA_LRRC_SESSION_TYPE_MT_SS,
    IMSA_LRRC_SESSION_TYPE_MO_SMS,
    IMSA_LRRC_SESSION_TYPE_MT_SMS,
    IMSA_LRRC_SESSION_TYPE_REGISTER,
    IMSA_LRRC_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_LRRC_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����   : IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8
 ö��˵��  : LMM֪ͨLRRC VOLTE����������
 1.��    ��   : 2015��11��30��
   ��    ��   : l00195322
   �޸�����   : �½�
*****************************************************************************/
enum IMSA_LRRC_VOLTE_STATUS_ENUM
{
    IMSA_LRRC_VOLTE_STATUS_INIT,
    IMSA_LRRC_VOLTE_STATUS_START,
    IMSA_LRRC_VOLTE_STATUS_END,

    IMSA_LRRC_VOLTE_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
�ṹ��    : IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU
�ṹ˵��  : SESSION��ʼָʾ
1.��    ��   : 2014��5��22��
  ��    ��   : h00246512
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_LRRC_END_SESSION_NOTIFY_STRU
 �ṹ˵��  : SESSION��ָֹʾ
 1.��    ��   : 2014��5��22��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU
 �ṹ˵��  : ֪ͨLRRC HIFIͬ������ָʾ
 1.��    ��   : 2014��11��14��
   ��    ��   : l00150010
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                                       ucHifiSyncEnabled;    /* 0��ʾ�رգ�1��ʾ�� */
    VOS_UINT8                                       ucPowerState;         /* Modem1���ػ�״̬��0��ʾ�ر�;1��ʾ�� */
    VOS_UINT8                                       aucReserved[2];
}IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU;


/*****************************************************************************
 ��������: IMSA_LRRC_GetSsacInfo
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucBarFactorForVoice;   /*ȡֵ��Χ:0~15ö��ֵ*/
    VOS_UINT8    ucBarTimeForVoice;     /*ȡֵ��Χ:0~7ö��ֵ,��λ:s*/
    VOS_UINT8    ucBarFactorForVideo;   /*ȡֵ��Χ:0~15ö��ֵ*/
    VOS_UINT8    ucBarTimeForVideo;     /*ȡֵ��Χ:0~7ö��ֵ,��λ:s*/
}IMSA_LRRC_SSAC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU
 �ṹ˵��  : IMSA֪ͨLRRC VOLTE���������Լ�����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /*_H2ASN_Skip*/
    IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8               enVolteStatus;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_VOLTE_STATUS_NOTIFY_STRU;


/*****************************************************************************
 ��������: IMSA_LRRC_GetSsacInfo
 Э����:
 ASN.1 ����:
 ����˵��:LRRC�ṩ��IMSA SSAC�����Ϣ
*****************************************************************************/
extern VOS_UINT32  IMSA_LRRC_GetSSACInfo
(
    IMSA_LRRC_SSAC_INFO_STRU *pstSsacInfo
);

/*****************************************************************************
 Function Name   : IMSA_LRRC_JudgeCurrCellSingalQuality
 Description     : LRRC�ṩ��IMSA�ӿڣ�����������ǰ�ź�����
 Input           : None
 Output          : None
 Return          : 0,�ź������ã�LTE���ܷ���VOLTE�绰
                   1,�ź��������ã��ź������ֱ��ȥGU��CS�绰

 History         :

    1.l00195322     2015-12-3
*****************************************************************************/

extern VOS_UINT32 IMSA_LRRC_JudgeCurrCellSingalQuality(VOS_VOID);
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/





/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaLrrcInterface.h */








