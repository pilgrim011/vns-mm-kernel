


#ifndef __NASLCSPUBLIC_H__
#define __NASLCSPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "PsCommonDef.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"
#include    "TafLcsInterface.h"
#include    "NasLcsTimerMsgProc.h"
#include    "PsCommonDef.h"
#include    "NasLcsDecode.h"
#include    "LmmLcsInterface.h"

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
  2 Macro
*****************************************************************************/
#define NAS_LCS_NULL                            0
#define NAS_LCS_NULL_PTR                        VOS_NULL_PTR
#define NAS_LCS_MAX_ENTITY_NUM                  (5)
#define NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN        (2)
#define NAS_LCS_MT_LR_ENTITY_INDEX_END          (4)
#define NAS_LCS_MO_LR_TAF_INDEX                 (1)
#define NAS_LCS_MO_LR_LPP_INDEX                 (0)
#define NAS_LCS_SUCC                            (0)
#define NAS_LCS_FAIL                            (1)
#define NAS_LCS_MAX_HANDLE_ID                   (255)
#define NAS_LCS_LEN_VOS_MSG_HEADER              (20)
#define NAS_LCS_MAX_LPP_MSG_LEN                 (235)
#define NAS_LCS_MAX_INVOKE_ID                   (255)
#define NAS_LCS_MAX_UPLINDK_LCS_MSG             (512)
#define NAS_LCS_MIN_SND_MSG_LEN                 (4)
#define NAS_LCS_MIN_MO_TI_VAULE                 (8)
#define NAS_LCS_MAX_MO_TI_VAULE                 (14)
#define NAS_LCS_TI_OFFSET                       (8)
#define NAS_LCS_TAF_MO_LR_TI                    (14)
#define NAS_LCS_LPP_MO_LR_TI                    (13)
#define NAS_LCS_UE_NW_CAP_LEN_INCLUDE_LCS       (5)
#define NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP         (4)
#define NAS_LCS_CLASSMARK2_LEN_INCLUDE_LCS      (3)
#define NAS_LCS_WAIT_NW_RSP_TIMER_DFT_LEN       (180)

#define NAS_LCS_MSG_HIGH_1_BIT                  (0x80)
#define NAS_LCS_MSG_HIGH_2_BIT                  (0xC0)
#define NAS_LCS_MSG_HIGH_3_BIT                  (0xE0)
#define NAS_LCS_MSG_HIGH_4_BIT                  (0xF0)
#define NAS_LCS_MSG_HIGH_5_BIT                  (0xF8)
#define NAS_LCS_MSG_HIGH_6_BIT                  (0xFC)
#define NAS_LCS_MSG_HIGH_7_BIT                  (0xFE)

#define NAS_LCS_MSG_LOW_BIT                     (0x0F)
#define NAS_LCS_MSG_HIGH_BIT                    (0xF0)
#define NAS_LCS_MSG_LOW_5_BIT                   (0x1F)
#define NAS_LCS_MSG_LOW_6_BIT                   (0x3F)
#define NAS_LCS_MSG_LOW_7_BIT                   (0x7F)
#define NAS_LCS_MSG_LOW_8_BIT                   (0xFF)
#define NAS_LCS_MSG_LOW_16_BIT                  (0xFFFF)

#define NAS_LCS_MSG_8_BIT                       (0x80)
#define NAS_LCS_MSG_7_BIT                       (0x40)
#define NAS_LCS_MSG_6_BIT                       (0x20)
#define NAS_LCS_MSG_5_BIT                       (0x10)
#define NAS_LCS_MSG_4_BIT                       (0x08)
#define NAS_LCS_MSG_3_BIT                       (0x04)
#define NAS_LCS_MSG_2_BIT                       (0x02)
#define NAS_LCS_MSG_1_BIT                       (0x01)

#define NAS_LCS_MOVEMENT_1_BITS                 (1)
#define NAS_LCS_MOVEMENT_2_BITS                 (2)
#define NAS_LCS_MOVEMENT_3_BITS                 (3)
#define NAS_LCS_MOVEMENT_4_BITS                 (4)
#define NAS_LCS_MOVEMENT_5_BITS                 (5)
#define NAS_LCS_MOVEMENT_6_BITS                 (6)
#define NAS_LCS_MOVEMENT_7_BITS                 (7)
#define NAS_LCS_MOVEMENT_8_BITS                 (8)
#define NAS_LCS_MOVEMENT_16_BITS                (16)
#define NAS_LCS_MOVEMENT_24_BITS                (24)


/*��װ��ӡLOG�ĺ�*/
#ifdef PS_ITT_PC_TEST
#define NAS_LCS_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LCS_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#define NAS_LCS_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LCS_ERR_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LCS_ERR_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_LCS_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_LCS_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_LCS_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LCS_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_LCS_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_LCS_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_LCS_ERR_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_LCS_ERR_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LCS_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif

#if (VOS_OS_VER == VOS_WIN32)

#define NAS_LCS_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
/*****************************************************************************
Function Name  : NAS_LCS_MEM_CPY_S
Discription    : LCS MEM CPY����, ����Ŀ���ڴ��С���追���ڴ��С����ͬʱ, Ŀ��
                 �ڴ��С��������追������, ���򷵻�ʧ��
Input          : pDestBuffer   :Ŀ���ڴ��ַ
                 ulMaxDest     :Ŀ���ڴ���󿽱�����
                 pSrcBuffer    :ԭ�ڴ��ַ
                 Count         :�����ڴ��ֽ���
Return         : EOK           :�����ɹ�
                 ����          :����ʧ��
*****************************************************************************/
#define NAS_LCS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)NAS_LCS_SecuMemCpy(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, (__LINE__), (THIS_FILE_ID) )

/*****************************************************************************
Function Name  : NAS_LCS_MEM_SET_S
Discription    : LCS MEM SET����, ����Ŀ���ڴ��С�����ʼ����С����ͬʱ, Ŀ��
                 �ڴ��С����������ʼ������, ���򷵻�ʧ��
Input          : pDestBuffer   :Ŀ���ڴ��ַ
                 ulMaxDest     :Ŀ���ڴ���󳤶�
                 ucData        :��ʼ��Ŀ��ֵ
                 Count         :��ʼ���ڴ����
Return         : EOK           :��ʼ���ɹ�
                 ����          :��ʼ��ʧ��
*****************************************************************************/
#define NAS_LCS_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength) \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_LCS_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#endif

#define NAS_LCS_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
    PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_LCS_MEM_FREE(pAddr) \
            {\
                if(VOS_OK != PS_MEM_FREE_ALL_CHECK((WUEPS_PID_LCS), (pAddr)))\
                {\
                    NAS_LCS_ERR_LOG("NAS_LCS_MEM_FREE  ERR!!");\
                }\
            }

#define NAS_LCS_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((WUEPS_PID_LCS), (ulSize))

#define NAS_LCS_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((WUEPS_PID_LCS),(ulLen))


/* ������Ϣ */
#define NAS_LCS_SND_MSG(pMsg)\
    {\
        NAS_LCS_PrintLcsSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_LCS_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((WUEPS_PID_LCS) , (pMsg)))\
            {\
                NAS_LCS_ERR_LOG("NAS_LCS_SND_MSG:Msg Snd Err!");\
            }\
    }

#define NAS_LCS_ReadNv( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)


#define NAS_LCS_WRITE_TAF_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_TAF;\
                    (pstMsg)->stMsgHeader.ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_LMM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_MM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_MM;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_LPP_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);

#define NAS_LCS_WRITE_OM_MSG_HEAD(pstMsg, MsgLenthNoHeader)\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_LCS;\
                    (pstMsg)->ulLength = (MsgLenthNoHeader);


/*��ʱ��ʱ��*/
#define TI_NAS_LCS_LPP_WAIT_NW_RSP_TIMER_LEN        (180*1000)      /* LPP������MO-LR���ȴ�������Ӧ��ʱ��ʱ�� */
#define TI_NAS_LCS_LPP_WAIT_USER_RSP_TIMER_LEN      (30*1000)       /* �ȴ��û���Ӧ��ʱ��ʱ�� */



#define NAS_LCS_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_LCS_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 �ṹ����: NAS_LCS_ENTITY_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ʵ������
*****************************************************************************/
enum NAS_LCS_ENTITY_TYPE_ENUM
{
    NAS_LCS_ENTITY_TYPE_MOLR       = 1,            /* ��ǰΪMOLRʵ�� */
    NAS_LCS_ENTITY_TYPE_MTLR       = 2,            /* ��ǰΪMTLRʵ�� */

    NAS_LCS_ENTITY_TYPE_BUTT
};
typedef VOS_UINT8  NAS_LCS_ENTITY_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_DOMAIN_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS������
*****************************************************************************/
enum NAS_LCS_DOMAIN_TYPE_ENUM
{
    NAS_LCS_DOMAIN_TYPE_EPC_LCS     = 0,
    NAS_LCS_DOMAIN_TYPE_CS_LCS      = 1,

    NAS_LCS_DOMAIN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_DOMAIN_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_CONN_STATE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:LCSʵ������״̬
*****************************************************************************/
enum NAS_LCS_CONN_STATE_ENUM
{
    NAS_LCS_CONN_STATE_IDLE         = 0, /* IDLE */
    NAS_LCS_CONN_STATE_ESTING       = 1, /* ESTING */
    NAS_LCS_CONN_STATE_CONN         = 2, /* CONNECTED */
    NAS_LCS_CONN_STATE_BUTT
};
typedef VOS_UINT8 NAS_LCS_CONN_STATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_ENTITY_USE_FLAG_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS����ʵ���¼�Ƿ�ʹ��
*****************************************************************************/
enum NAS_LCS_ENTITY_USE_FLAG_ENUM
{
    NAS_LCS_ENTITY_NOT_USED         = 0,                    /* ʵ��û��ʹ�� */
    NAS_LCS_ENTITY_USED             = 1,                    /* ʵ�屻ʹ�� */
    NAS_LCS_ENTITY_USE_FLAG_BUTT
};
typedef VOS_UINT8 NAS_LCS_ENTITY_USE_FLAG_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_NW_EPC_LCS_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����EPC_LCS����ö��
*****************************************************************************/
enum NAS_LCS_NW_EPC_LCS_ENUM
{
    NAS_LCS_NW_EPC_LCS_NOT_SUPPORT           = 0,           /* ���಻֧��EPC LCS */
    NAS_LCS_NW_EPC_LCS_SUPPORT               = 1,           /* ����֧��EPC LCS */

    NAS_LCS_NW_EPC_LCS_BUTT
};
typedef VOS_UINT32 NAS_LCS_NW_EPC_LCS_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: NAS_LCS_NW_CS_LCS_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����CS_LCS����ö��
*****************************************************************************/
enum NAS_LCS_NW_CS_LCS_ENUM
{
    NAS_LCS_NW_CS_LCS_NO_INFORMATION         = 0,           /* ������Ϣ��δЯ���Ƿ�֧��CS LCS */
    NAS_LCS_NW_CS_LCS_SUPPORT                = 1,           /* ����֧��CS_LCS */
    NAS_LCS_NW_CS_LCS_NOT_SUPPORT            = 2,           /* ���಻֧��LCS */
    NAS_LCS_NW_CS_LCS_RESERVED               = 3,           /* ���� */

    NAS_LCS_NW_CS_LCS_BUTT
};
typedef VOS_UINT32 NAS_LCS_NW_CS_LCS_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: NAS_LCS_START_SOURCE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS����Դö��
*****************************************************************************/
enum NAS_LCS_START_SOURCE_ENUM
{
    NAS_LCS_START_SOURCE_NW             = 0,
    NAS_LCS_START_SOURCE_LPP            = 1,
    NAS_LCS_START_SOURCE_TAF            = 2,

    NAS_LCS_START_SOURCE_BUTT
};
typedef VOS_UINT8 NAS_LCS_START_SOURCE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_ENTITY_STATE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCSʵ��״̬ö��
*****************************************************************************/
enum NAS_LCS_ENTITY_STATE_ENUM
{
    NAS_LCS_ENTITY_STATE_NULL               = 0,
    NAS_LCS_ENTITY_STATE_WAIT_NW_RSP        = 1,
    NAS_LCS_ENTITY_STATE_WAIT_USER_RSP      = 2,
    NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL    = 3,

    NAS_LCS_ENTITY_STATE_BUTT
};
typedef VOS_UINT8 NAS_LCS_ENTITY_STATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_CAP_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCSʵ��״̬ö��
*****************************************************************************/
enum NAS_LCS_CAP_ENUM
{
    NAS_LCS_CAP_NOT_SUPPORT             = 0,
    NAS_LCS_CAP_SUPPORT                 = 1,

    LMM_LCS_UE_LCS_BUTT
};
typedef VOS_UINT8 NAS_LCS_CAP_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_TIMER_RUN_STA_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS��ʱ��״̬ö��
*****************************************************************************/
enum    NAS_LCS_TIMER_RUN_STA_ENUM
{
    NAS_LCS_TIMER_RUNNING                = 0x00,
    NAS_LCS_TIMER_STOPED,
    NAS_LCS_TIMER_INVALID,

    NAS_LCS_TIMER_BUTT
};
typedef VOS_UINT32   NAS_LCS_TIMER_RUN_STA_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: NAS_LCS_NW_CAP_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����LCS����
*****************************************************************************/
typedef struct
{
    NAS_LCS_NW_EPC_LCS_ENUM_UINT32  enNwEpcLcs;
    NAS_LCS_NW_CS_LCS_ENUM_UINT32   enNwCsLcs;
}NAS_LCS_NW_CAP_INFO_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_UE_CAP_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: UE CS LCS����
*****************************************************************************/
typedef struct
{
    NAS_LCS_CAP_ENUM_UINT8              enPsLcsCap;                     /* �Ƿ�֧��PS-LCS */
    NAS_LCS_CAP_ENUM_UINT8              enCsLcsCap;                     /* �Ƿ�֧��CS-LCS */
    VOS_UINT8                           aucRsv[2];
}NAS_LCS_GU_LCS_CAP_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_LTE_LCS_CAP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: UE LTE LCS����
*****************************************************************************/
typedef struct
{
    NAS_LCS_CAP_ENUM_UINT8              enEpcLcsCap;                    /* �Ƿ�֧��EPC-LCS */
    NAS_LCS_CAP_ENUM_UINT8              enLppCap;                       /* �Ƿ�֧��LPP */
    VOS_UINT8                           aucRsv[2];
}NAS_LCS_LTE_LCS_CAP_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_UE_CAP_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: UE LCS����
*****************************************************************************/
typedef struct
{
    NAS_LCS_GU_LCS_CAP_STRU             stGuLcsCap;
    NAS_LCS_LTE_LCS_CAP_STRU            stLteLcsCap;
}NAS_LCS_UE_CAP_INFO_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_TAF_MSG_RECORD_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: TAF��Ϣ���ݼ�¼
*****************************************************************************/
typedef struct
{
    LCS_MOLR_PARA_STRU                  stMolrPara;                     /* TAF��LCS���͵�BeginReq��Ϣ���� */
}NAS_LCS_TAF_MSG_RECORD_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_NW_MSG_RECORD_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �տ���Ϣ���ݼ�¼
*****************************************************************************/
typedef struct
{
    LCS_NOTIFICATION_TYPE_ENUM_UINT8    enNotificationType;           /* MT-LR Notification���� */
    VOS_UINT8                           aucRsv[3];
}NAS_LCS_NW_MSG_RECORD_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_LPP_MSG_RECORD_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LPP��Ϣ���ݼ�¼������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLppMsgSize;       /* ���� */
    VOS_UINT8                           aucLppMsg[NAS_LCS_MAX_LPP_MSG_LEN];
}NAS_LCS_LPP_MSG_RECORD_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_COMM_NV_PARA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: NV���ñ��ش洢�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPeriodicRptTimes :1;               /* �Ƿ������������ϱ����� */
    VOS_UINT32                          bitOpSpare            :31;

    VOS_UINT8                           ucMaxRetryTimes;                        /* ������³��Դ��� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usRetryTimerLen;                        /* ���³��Զ�ʱ��ʱ��, ��ʱ������½��� */
    VOS_UINT16                          usPeriodicRptTimes;                     /* MO-LRΪ�����ϱ�ʱ,���������ϱ����� */
}NAS_LCS_COMM_NV_PARA_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_STATE_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS״̬��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTi;                               /* MO TIΪ8-14��MT TIΪ0-6��
                                                                            ��TI�����ǿտ��д����TIֵ����Ҫ����һ��ת����
                                                                            Ϊ������MM */
    VOS_UINT8                           ucHandleId;
    NAS_LCS_ENTITY_USE_FLAG_ENUM_UINT8  enUsedFlag;                         /* �жϸ�ʵ���Ƿ�ʹ�� */
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState;                        /* ��ǰ����״̬ */
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState;                      /* ʵ��״̬ */
    VOS_UINT8                           ucEstRetryTimes;                    /* ���Խ������� */
    VOS_UINT8                           ucPeriodRetryTimes;                 /* ���ڳ��Դ��� */
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enCurLcsDomain;                     /* ��ǰLCSѡ����� */
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource;                      /* ����LCSԴ,��Ҫ��������LPP��TAF������MOLR */
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           aucRsv[2];
    NAS_LCS_TIMER_INFO_STRU             stStateTimer;                       /* ״̬��ʱ�� */
    NAS_LCS_TIMER_INFO_STRU             stWaitResetTimer;                   /* WAIT RESET��ʱ�� */
    NAS_LCS_NW_MSG_RECORD_STRU          stLcsNwMsgRecord;                   /* ��¼���෢�͵Ŀտ���Ϣ */
}NAS_LCS_ENTITY_INFO_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_ENCODE_BUFFER_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����ά��BUFFER
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBufferLen;
    VOS_UINT8                           aucBuffer[NAS_LCS_MAX_UPLINDK_LCS_MSG];
}NAS_LCS_ENCODE_BUFFER_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_PUB_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS��Ϣ����ά���ṹ
*****************************************************************************/
typedef struct
{
    NAS_LCS_NW_CAP_INFO_STRU            stNwLcsCap;                             /* ����LCS���� */
    NAS_LCS_COMM_NV_PARA_STRU           stCommNvPara;                           /* LCS NV������ö����浽�ó�Ա�� */

    /* LCSʵ���¼,����¼5��,��һ��ʵ��洢LPP������MO-LR,�ڶ���ʵ��洢TAF������MO-LR,
        �������������ʵ��洢MT-LR */
    NAS_LCS_ENTITY_INFO_STRU            astLcsEntity[NAS_LCS_MAX_ENTITY_NUM];
    NAS_LCS_TAF_MSG_RECORD_STRU         stTafMsgRecord;                         /* ��¼TAF��LCS����Ϣ */
    NAS_LCS_LPP_MSG_RECORD_STRU         stLppMsgRecord;                         /* ��¼LPP��LCS����Ϣ */

    VOS_UINT8                           ucCurHandleId;
    VOS_UINT8                           ucCurInvokeId;
    VOS_UINT8                           aucRsv[2];

    NAS_LCS_ENCODE_BUFFER_STRU          stEncodeBuffer;
}NAS_LCS_PUB_INFO_STRU;


/*****************************************************************************
 �ṹ����: NAS_LCS_NV_PERIODIC_RPT_PARA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �������ϱ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPerRptTimesFlag;    /* usPerRptTimes�����Ƿ���Ч, 0:��ʾ��Ч, 1:��ʾ��Ч */
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usPerRptTimes;        /* �������ϱ��ϱ��������� */
}NAS_LCS_NV_PERIODIC_RPT_PARA_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_NV_RETRY_PARA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ���³������NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRetryTimerLen;      /* �ȴ��ؽ���ʱ��ʱ��,��λΪ�� */
    VOS_UINT8                           ucCsLcsRetryTimes;    /* Cs Lcs ���³��Դ��� */
    VOS_UINT8                           ucEpcLcsRetryTimes;   /* Epc Lcs ���³��Դ��� */
    VOS_UINT8                           ucRsv;
}NAS_LCS_NV_RETRY_PARA_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_NV_PARA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LCS NV ��������
*****************************************************************************/
typedef struct
{
    NAS_LCS_NV_RETRY_PARA_STRU          stRetryPara;          /* ���³���NV���� */
    NAS_LCS_NV_PERIODIC_RPT_PARA_STRU   stPerRptPara;         /* �������ϱ��������� */
}NAS_LCS_NV_PARA_STRU;

/*****************************************************************************
 �ṹ����: NAS_LCS_ENCODE_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �տڱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpCause      :1;
    VOS_UINT32                          bitLocNtfRsp    :1;
    VOS_UINT32                          bitOpInvokeId   :1;
    VOS_UINT32                          bitOpSpare      :29;

    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucInvokeId;
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource;
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperType;
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause;
}NAS_LCS_ENCODE_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_LCS_PUB_INFO_STRU                g_stLcsInfo;
extern NAS_LCS_PUB_INFO_STRU               *pg_stLcsInfo;

#define NAS_LCS_GetLcsInfo()                    (pg_stLcsInfo)
#define NAS_LCS_GetLcsEntity(ulIndex)           (&pg_stLcsInfo->astLcsEntity[ulIndex])
#define NAS_LCS_GetCurHandleId()                (pg_stLcsInfo->ucCurHandleId)
#define NAS_LCS_SetCurHandleId(ucHandleId)      (pg_stLcsInfo->ucCurHandleId = ucHandleId)
#define NAS_LCS_GetCurInvokeId()                (pg_stLcsInfo->ucCurInvokeId)
#define NAS_LCS_SetCurInvokeId(ucInvokeId)      (pg_stLcsInfo->ucCurInvokeId = ucInvokeId)
#define NAS_LCS_GetNwLcsCap()                   (&pg_stLcsInfo->stNwLcsCap)
#define NAS_LCS_GetEncodeBuffer()               (&pg_stLcsInfo->stEncodeBuffer)


/* ��ȡʵ����Ϣ */
#define NAS_LCS_GetEntityState(ulIndex)                     (pg_stLcsInfo->astLcsEntity[ulIndex].enEntityState)
#define NAS_LCS_GetEntityConnState(ulIndex)                 (pg_stLcsInfo->astLcsEntity[ulIndex].enConnState)
#define NAS_LCS_GetEntityLcsDomain(ulIndex)                 (pg_stLcsInfo->astLcsEntity[ulIndex].enCurLcsDomain)
#define NAS_LCS_SetEntityLcsDomain(ulIndex, enLcsDoamin)    (pg_stLcsInfo->astLcsEntity[ulIndex].enCurLcsDomain = (enLcsDoamin))
#define NAS_LCS_GetEntityEstRetryTimers(ulIndex)            (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes)
#define NAS_LCS_AddEntityEstRetryTimers(ulIndex)            (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes++)
#define NAS_LCS_ResetEntityEstRetryTimers(ulIndex)          (pg_stLcsInfo->astLcsEntity[ulIndex].ucEstRetryTimes = 0)
#define NAS_LCS_GetEntityPediodRetryTimers(ulIndex)         (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes)
#define NAS_LCS_AddEntityPediodRetryTimers(ulIndex)         (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes++)
#define NAS_LCS_ResetEntityPediodRetryTimers(ulIndex)       (pg_stLcsInfo->astLcsEntity[ulIndex].ucPeriodRetryTimes = 0)
#define NAS_LCS_GetEntityTi(ulIndex)                        (pg_stLcsInfo->astLcsEntity[ulIndex].ucTi)
#define NAS_LCS_GetEntityStrartSource(ulIndex)              (pg_stLcsInfo->astLcsEntity[ulIndex].enStartSource)
#define NAS_LCS_SetEntityTi(ulIndex, ucTmpTi)               (pg_stLcsInfo->astLcsEntity[ulIndex].ucTi = (ucTmpTi))
#define NAS_LCS_GetStateTimer(ulIndex)                      (&pg_stLcsInfo->astLcsEntity[ulIndex].stStateTimer)
#define NAS_LCS_GetWaitResetTimer(ulIndex)                  (&pg_stLcsInfo->astLcsEntity[ulIndex].stWaitResetTimer)
#define NAS_LCS_GetEntityHandleId(ulIndex)                  (pg_stLcsInfo->astLcsEntity[ulIndex].ucHandleId)
#define NAS_LCS_SetEntityHandleId(ulIndex, ucHandleId)      (pg_stLcsInfo->astLcsEntity[ulIndex].ucHandleId = (ucHandleId))
#define NAS_LCS_GetEntityNwMsgRecord(ulIndex)               (&pg_stLcsInfo->astLcsEntity[ulIndex].stLcsNwMsgRecord)
#define NAS_LCS_GetEntityNotificationType(ulIndex)          (pg_stLcsInfo->astLcsEntity[ulIndex].stLcsNwMsgRecord.enNotificationType)
#define NAS_LCS_GetEntityInvokeId(ulIndex)                  (pg_stLcsInfo->astLcsEntity[ulIndex].ucInvokeId)
#define NAS_LCS_SetEntityInvokeId(ulIndex,ucCurInvokeId)    (pg_stLcsInfo->astLcsEntity[ulIndex].ucInvokeId = (ucCurInvokeId))


/* ��ȡTAF��������Ϣ */
#define NAS_LCS_GetTafMolrRecord()              (&pg_stLcsInfo->stTafMsgRecord.stMolrPara)
#define NAS_LCS_GetMolrMode()                   (pg_stLcsInfo->stTafMsgRecord.stMolrPara.enRepMode)

/* ��ȡLPP��������Ϣ */
#define NAS_LCS_GetLppMolrRecord()              (&pg_stLcsInfo->stLppMsgRecord)


/* ��ȡNV�����Ϣ */
#define NAS_LCS_GetCommNvPara()                 (&pg_stLcsInfo->stCommNvPara)
#define NAS_LCS_GetNvMaxRetryTimes()            (pg_stLcsInfo->stCommNvPara.ucMaxRetryTimes)
#define NAS_LCS_GetNvMaxPeriodicRptTimes()      (pg_stLcsInfo->stCommNvPara.usPeriodicRptTimes)







/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_LCS_DOMAIN_TYPE_ENUM_UINT8 NAS_LCS_SelectMolrDomain( VOS_VOID );
extern VOS_VOID NAS_LCS_StartTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern VOS_VOID NAS_LCS_StopTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern VOS_UINT32 NAS_LCS_QueryMolrEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_LCS_IsLteSupportCsLcs( VOS_VOID );
extern VOS_VOID NAS_LCS_ClearResource ( VOS_VOID );
extern VOS_VOID NAS_LCS_SetEntityState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState
);
extern VOS_VOID NAS_LCS_SetEntityConnState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState
);
extern VOS_UINT32 NAS_LCS_IsMoLr
(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT32 NAS_LCS_CreateLcsEntity
(
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32  NAS_LCS_GetLcsEntityNum( VOS_VOID );
extern VOS_VOID NAS_LCS_ClearLcsEntityAndNotify
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_VOID  NAS_LCS_ProcMolrConnAbnormal
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
);
extern VOS_VOID NAS_LCS_ClearSingleLcsEntity
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_UINT32 NAS_LCS_QueryMtLrEntity
(
    VOS_UINT8                           ucHandleId,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID  NAS_LCS_ReadLcsNvCommonConfig( VOS_VOID);
extern VOS_VOID  NAS_LCS_ProcAirMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
);
extern VOS_UINT32 NAS_LCS_QueryLcsEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
);
extern NAS_LCS_TIMER_RUN_STA_ENUM_UINT32  NAS_LCS_IsTimerRunning
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmEstCnfCauseMap(const LMM_LCS_EST_RESULT_ENUM_UINT32 enCause);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmDataCnfCauseMap(const LMM_LCS_SEND_RSLT_ENUM_UINT32 enCause);
extern TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmRelCauseMap(const LMM_LCS_REL_CAUSE_ENUM_UINT32 enCause);
extern VOS_UINT8 NAS_LCS_CreateMoTi
(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT8 NAS_LCS_CreateInvokeId( VOS_VOID );
extern VOS_VOID  NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
);
extern VOS_VOID  NAS_LCS_TryToChangeDomain
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
);
extern VOS_VOID  NAS_LCS_SndTafBeginInd
(
    const NAS_LCS_LOC_NOTFICATION_STRU *pstLocNotication,
    VOS_UINT8                           ucHandleId
);
extern VOS_VOID NAS_LCS_SndRegister
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndFacility
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndReleaseComplte
(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_LCS_SndMtlrFailReleaseComplte
(
    VOS_UINT8                           ucDlAirTi,
    VOS_UINT8                           ucInvokeId,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType,
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause
);
extern VOS_VOID NAS_LCS_SndMtlrRspReleaseComplte
(
    VOS_UINT32                          ulIndex,
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp
);

extern VOS_INT32 NAS_LCS_SecuMemCpy
(
    VOS_VOID        * pDst,
    VOS_UINT32      ulMaxBuffer,
    const VOS_VOID  * pSrc,
    VOS_UINT32      ulLength,
    VOS_UINT32      ulLineNO,
    VOS_UINT32      ulFileID
);

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

#endif











































