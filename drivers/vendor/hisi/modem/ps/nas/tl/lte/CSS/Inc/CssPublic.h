/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssPublic.h
    Description : CSSʵ��ͷ�ļ�
    History     :
      1.wangchen 00209181   2015-05-14  Draft Enact


******************************************************************************/

#ifndef __CSSPUBLIC_H__
#define __CSSPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "CssInterface.h"
#include    "CssLphyInterface.h"
#include    "CssNvInterface.h"
#include    "LmmCssInterface.h"
#include    "LNvCommon.h"
#include    "PsTypeDef.h"
#include    "LPsNvInterface.h"
#include    "PsCommonDef.h"
#include    "PsLogdef.h"
#include    "NasMmlCtx.h"
#include    "CssAtInterface.h"
#include "LPsOm.h"
#if (VOS_OS_VER != VOS_WIN32)
#include    "NasMntn.h"
#endif
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
#define INT16_MAX                       (0x7FFF)

#define CSS_NULL_PTR                    (VOS_NULL_PTR)
#define CSS_NULL                        (0)

#define CSS_SUCC                        (0)/* �������ܵķ���ֵbegin */
#define CSS_FAIL                        (1)
#define CSS_CAUSE_NULL_PTR              (2)/* �������ܵķ���ֵend */

#define CSS_OP_FALSE                    (0)
#define CSS_OP_TRUE                     (1)
#define CSS_TRUE                        (1)
#define CSS_FALSE                       (0)

#define CSS_COMM_BAND_DEFAULT_NUM       (9)

#define CSS_GSM_HIGH_THRESHOLD          (-85)
#define CSS_GSM_LOW_THRESHOLD           (-95)

#define CSS_WCDMA_HIGH_THRESHOLD        (-99)
#define CSS_WCDMA_LOW_THRESHOLD         (-100)

#define CSS_LTE_HIGH_THRESHOLD          (-90)
#define CSS_LTE_LOW_THRESHOLD           (-104)

#define CSS_RSSI_64DB                   (64)

#define CSS_FREQ_RANGE_999_100KHZ       (999)

#define CSS_MIN_OPID                    (1)
#define CSS_MAX_OPID                    (65535) /**/

#define CSS_GSM_SUPORT_OP               (0x01)
#define CSS_WCDMA_SUPORT_OP             (0x02)
#define CSS_LTE_SUPORT_OP               (0x04)


#define CSS_GSM_OP_OFFSET               (0x00)
#define CSS_WCDMA_OP_OFFSET             (0x01)
#define CSS_LTE_OP_OFFSET               (0x02)
#define CSS_TDS_OP_OFFSET               (0x03)


#define CSS_MAX_MEMORY_PERF_MCC_NUM     (CSS_MAX_PLMN_ID_NUM)
#define CSS_MAX_MEMORY_PERF_MNC_NUM     (50)
#define CSS_MAX_MEMORY_PERF_BAND_NUM    (30)
#define CSS_MAX_MEMORY_PERF_FREQ_NUM    (48)

#define CSS_MAX_UPDATE_MCC_NUM          (CSS_MAX_PLMN_ID_NUM)
#define CSS_MAX_PID_NUM                 (8)
#define CSS_MAX_NV_MCC_NUM              (3)

#define CSS_OCTET_LOW_4_BITS            (0x0f)                  /* ��ȡһ���ֽ��еĵ�4λ */
#define CSS_OCTET_HIGH_4_BITS           (0xf0)                  /* ��ȡһ���ֽ��еĸ�4λ */
#define CSS_DEC_DIGIT_9                 (9)                     /* ʮ������9 */

#define CSS_OCTET_MOVE_4_BITS           (0x04)
#define CSS_OCTET_MOVE_8_BITS           (0x08)
#define CSS_OCTET_MOVE_16_BITS          (0x10)

#define CSS_SIZEOF_AT_FREQ_RANGE_STRU   (9)

#define CSS_BEGIN_OF_AT_SEQ             (0x01)
#define CSS_END_OF_AT_SEQ               (0xFF)

#define CSS_NO_NETWORK_BAND_IND         (0)                    /* �ƶ��·����BANDIND����ʾû�в��� */


#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
#define CSS_CLOUD_MEM_TOTAL_LEN         (48000)               /* ��ͨ���ܹ�������ڴ��С */
#define CSS_CLOUD_BLOCK_HEAD_LEN        (4)                   /* ÿ����ͨ������ڵ�ʱ��CSS������ڴ��ͷ�Ĵ�С */
#define CSS_CLOUD_BLOCK_DATA_LEN        (20)                  /* ÿ����ͨ������ڵ�ʱ��CSS������ڴ��ʵ�����ݵĴ�С */
#define CSS_CLOUD_BLOCK_LEN             (CSS_CLOUD_BLOCK_HEAD_LEN+CSS_CLOUD_BLOCK_DATA_LEN)         /* ÿ����ͨ������ڵ�ʱ��CSS������ڴ��Ĵ�С */
extern VOS_CHAR g_acCssCloudFreqMemory[CSS_CLOUD_MEM_TOTAL_LEN];
#endif

#define CSS_PRINT_BUFF_LEN              (3096)              /* 1024ÿ�δ�ӡԤ�軺�� */
extern VOS_CHAR                         g_acCssPrintBuf[CSS_PRINT_BUFF_LEN];
#define CSS_GET_CSS_PRINT_BUF()         (g_acCssPrintBuf)

#ifdef PS_ITT_PC_TEST_NAS
#define TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN           (5000)
#define TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN             (5000)
#define TI_CSS_WAIT_FOR_SCAN_IND_LEN                        (10000)
#define TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN                   (5000)
#define TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN                     (2000)
#define TI_CSS_WAIT_START_BG_SEARCH_CNF_LEN                 (10000)

#else
#define TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN           (1000)
#define TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN             (1000)
#define TI_CSS_WAIT_FOR_SCAN_IND_LEN                        (1500)
#define TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN                   (1000)
#define TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN                     (1000)
#define TI_CSS_WAIT_START_BG_SEARCH_CNF_LEN                 (10000)

#endif

#define CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT           (12)
#define CSS_REBOOT_TYPE_STOP_SCAN_TIMEOUT                   (13)
#define CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL              (14)
#define CSS_REBOOT_TYPE_STOP_SCAN_FAIL                      (15)


typedef VOS_INT (*CSS_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
#ifdef PS_ITT_PC_TEST
#define CSS_INFO_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
     */
#define CSS_INFO_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
     */
#define CSS_INFO_LOG2(String, Para1, Para2) \
                     (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
     */
#define CSS_NORM_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
     */
#define CSS_NORM_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
     */
#define CSS_NORM_LOG2(String, Para1, Para2) \
                     (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
     */
#define CSS_WARN_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
     */
#define CSS_WARN_LOG1(String, Para1) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1 )
     */
#define CSS_WARN_LOG2(String, Para1, Para2) \
                             (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1, (long)Para2)
     */
#define CSS_ERR_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
     */
#define CSS_ERR_LOG1(String, Para1) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String, (long)Para1 )
     */

#else
/*�ɴ�ӡ�ر�ʱ*/
#if (!defined(_lint) && (PRINT_SWITCH == PRINT_OFF)&& (VOS_WIN32 != VOS_OS_VER))
#define CSS_INFO_LOG(String)
#define CSS_INFO_LOG1(String, Para1)
#define CSS_INFO_LOG2(String, Para1, Para2)
#define CSS_NORM_LOG(String)
#define CSS_NORM_LOG1(String, Para1)
#define CSS_NORM_LOG2(String, Para1, Para2)
#define CSS_WARN_LOG(String)
#define CSS_WARN_LOG1(String, Para1)
#define CSS_WARN_LOG2(String, Para1, Para2)
#define CSS_ERR_LOG(String)
#define CSS_ERR_LOG1(String, Para1)

#else
#define CSS_INFO_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String)
#define CSS_INFO_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define CSS_INFO_LOG2(String, Para1, Para2) \
                     (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define CSS_NORM_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define CSS_NORM_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define CSS_NORM_LOG2(String, Para1, Para2) \
                     (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define CSS_WARN_LOG(String) \
        {\
            (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String);\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(VOS_UINT8)VOS_NULL_PTR, \
                                        (VOS_UINT8)VOS_NULL_PTR, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_WARN_LOG1(String, Para1) \
        {\
            (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1 );\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(VOS_UINT8)Para1, \
                                        (VOS_UINT8)VOS_NULL_PTR, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_WARN_LOG2(String, Para1, Para2) \
        {\
            (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2);\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(VOS_UINT8)Para1, \
                                            (VOS_UINT8)Para2, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_ERR_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_ERROR, String)
#define CSS_ERR_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_ERROR, String, (long)Para1 )

#endif
#endif

#define CSS_MAX(a,b) (((a)>(b))?(a):(b))
#define CSS_MIN(a,b) (((a)<(b))?(a):(b))


/* �ڴ濽���궨�� */
#if (VOS_OS_VER == VOS_WIN32)

#define CSS_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define CSS_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define CSS_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define CSS_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)CSS_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define CSS_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_SET_S((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define CSS_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#endif


#define CSS_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define CSS_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_CSS) , (ulLen))

#define CSS_FREE_MSG(pMsg) \
            PS_FREE_MSG( PS_PID_CSS, pMsg )

extern VOS_VOID CSS_Send_Msg(VOS_VOID* pMsg);

/* ������Ϣ */
#define CSS_SND_MSG(pMsg)\
            CSS_Send_Msg(pMsg)


/*�ڴ��ͷ�*/
#define CSS_MEM_FREE(pAddr)  PS_MEM_FREE(PS_PID_CSS, pAddr)

/*�ڴ涯̬����*/
#define CSS_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_CSS) , (ulSize))


#define CSS_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)

#define CSS_NV_Write( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Write( ulId, pItemData, usItemDataLen)

#define CSS_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define CSS_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

#define CSS_GET_MSG_ENTITY_BY_NAME(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgName))

/*��װдCOMM��Ϣͷ�ĺ�*/
#define CSS_WRITE_COMM_MSG_HEAD(pstMsg, ulMsgID, ulInPid)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = (ulInPid);

/*��װдLPHY��Ϣͷ�ĺ�*/
#define CSS_WRITE_LPHY_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_HPA;

/*��װд�ڲ���Ϣͷ�ĺ�*/
#define CSS_WRITE_OM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_CSS;

/*��װдAT��Ϣͷ�ĺ�*/
#define CSS_WRITE_AT_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_AT;
/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    ö����    : CSS_TIMER_ID_ENUM
    ö��˵��  : ��ʱ��ID
*****************************************************************************/
enum CSS_TIMER_ID_ENUM
{
    TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF           = 0x0000,           /* �ȴ����ô�ģ��ʱ�� */
    TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF             = 0x0001,           /* �ȴ�������ģ��ʱ�� */

    TI_CSS_WAIT_FOR_SCAN_IND                        = 0x0002,           /* �ȴ�lphy�ϱ�ɨƵ��� */
    TI_CSS_WAIT_FOR_STOP_SCAN_CNF                   = 0x0003,           /* �ȴ�lphy�ϱ�ֹͣɨƵ��� */

    TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ               = 0x0004,           /* AP����ʱ�ȴ�MMC_SET_REQ */
    TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ        = 0x0005,           /* MMC��AS����ʱ�ȴ�MMC_SET_REQ */

    TI_CSS_WAIT_START_BG_SERACH_CNF                 = 0x0006,           /* �ȴ�LPHY�ظ�START_BG_SEARCH_CNF */

    CSS_TIMER_ID_BUTT
};
typedef VOS_UINT16 CSS_TIMER_ID_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : CSS_MAIN_STATE_ENUM
 �ṹ˵��  : CSS�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    CSS_MAIN_STATE_ENUM
{
    /*=================== CSS����״̬ ===================*/
    CSS_MS_IDLE                         = 0x0000,
    CSS_MS_SCAN                                 ,           /* ɨƵ�����е�״̬ */
    CSS_MS_STOP_SCAN                            ,           /* ֹͣɨƵ������״̬ */

    CSS_MAIN_STATE_BUTT
};
typedef VOS_UINT16 CSS_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : CSS_SUB_STATE_ENUM
 �ṹ˵��  : CSS�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    CSS_SUB_STATE_ENUM
{
    /*=================== CSS����״̬ ===================*/
    CSS_SS_WAIT_START_IND                   = 0x0000,           /* �ȴ�������״̬��ֻ��������Ϣ */
    CSS_SS_IDLE                                     ,
    CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF            ,           /* �ȴ�������ģ�ظ�״̬ */
    CSS_SS_WAIT_START_BG_SRCH_CNF                   ,           /* �ȴ���ʼ�����ѻظ�״̬ */
    CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF          ,           /* �ȴ����ô�ģ�ظ�״̬ */
    CSS_SS_WAIT_BAND_SCAN_IND                       ,           /* �ȴ�������ϱ�ɨƵ���״̬ */
    CSS_SS_WAIT_STOP_SCAN_CNF                       ,           /* �ȴ�������ϱ�ֹͣɨƵ���״̬ */

    CSS_SS_STATE_BUTT
};
typedef VOS_UINT16 CSS_SUB_STATE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : CSS_SCAN_TYPE_ENUM
 �ṹ˵��  : CSSɨƵģʽ��ö��
*****************************************************************************/
enum    CSS_SCAN_TYPE_ENUM
{
    CSS_SCAN_TYPE_MULTI_BAND_SCAN                  = 0x0000,           /* ����ǰ�Ļƽ�BANDɨƵ���� */
    CSS_SCAN_TYPE_AS_BAND_SCAN                             ,           /* ���������������ɨƵ���� */
};
typedef VOS_UINT8 CSS_SCAN_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : CSS_COMM_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���浱ǰ�����GUNAS/AS���͵���Ϣ
*****************************************************************************/
typedef struct
{
    /* ɨƵ������д洢 */
    VOS_UINT32                          bitOpSaveMsg : 1;
    VOS_UINT32                          bitOpHighRssi : 1; /* �洢ɨƵ�����Ƿ��Ǹ������ģ����ڴ洢REQ��Ϣʱ����ΪTRUE */
    VOS_UINT32                          bitOpMcc : 1;      /*�Ƿ�mccɨƵ*/
    VOS_UINT32                          bitOpRsv : 29;

    CSS_MSG_ID_ENUM_UINT32              enMsgId;                    /*��Ϣ����*/
    VOS_UINT32                          ulOpid;
    VOS_UINT32                          ulReceiverPid;

    CSS_BAND_SCAN_TYPE_ENUM_UINT32      enBandScanType;             /*ɨ������*/
    VOS_UINT8                           aucMcc[2];                  /* MCC����,MCC_BASED��������ʱ����ҪЯ�� */
    CSS_RAT_LIST                        stRatList;                  /* ����BAND��rat list */


    /* ɨƵ������д洢 */
}CSS_COMM_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CSS_AS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���浱ǰ�����TDS���͵���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                    ulIsSaveMsg;                  /* �Ƿ񱣴�����Ϣ */
    VOS_UINT32                                    ulReceiverPid;
    CSS_MSG_ID_ENUM_UINT32                        ulMsgId;                      /*��Ϣ����*/
    VOS_UINT32                                    ulOpid;                       /* op id */
    CSS_RAT_TYPE_ENUM_UINT8                       ucRatType;                    /* ��ʽ */
    VOS_UINT8                                     ucRsv[3];                     /* ���� */
    CSS_BAND_LIST                                 stBandList;                   /* ����BAND list */
}CSS_AS_MSG_STRU;


typedef struct
{

    HTIMER                              phTimer;            /* Timer��� */
    VOS_UINT16                          usName;             /* �� IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT16                          usPara;             /* �� IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    VOS_UINT8                           ucResv[3];
    VOS_UINT32                          ulTimerLen;         /* Timerʱ��(UNIT: ms) */
}CSS_TIMER_STRU;

typedef struct
{
    VOS_UINT8                                  bitOpLteSupport: 1;
    VOS_UINT8                                  bitOpWcdmaSupport: 1;
    VOS_UINT8                                  bitOpGsmSupport: 1;
    VOS_UINT8                                  bitOpTdsSupport: 1;
    VOS_UINT8                                  bitOpSpace: 4;

    VOS_UINT8                                  ucBandInd;
    VOS_UINT8                                  ucScanReqCount;
    VOS_UINT8                                  ucScanRsltArrayCount;

    CSS_LPHY_FREQ_RANGE_INFO_STRU             *pstScanReqArray;/* ��ʼ����һֱ���� */
    CSS_FREQ_RANGE_STRU                       *pstScanRsltArray;
} CSS_COMM_SCAN_BAND_INFO_STRU;

typedef struct tagCSS_COMM_SCAN_BAND_NODE_STRU
{
    CSS_COMM_SCAN_BAND_INFO_STRU                  stBandInfo;
    struct tagCSS_COMM_SCAN_BAND_NODE_STRU       *pstNext;
} CSS_COMM_SCAN_BAND_NODE_STRU;

typedef struct
{
    VOS_UINT8                           ucBandCount;
    VOS_UINT8                           ucCurFreqRangeIdx;/* ��ǰɨƵ��Ƶ������ */
    VOS_UINT8                           aucRsv[2];
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstCurr;/* ��ǰɨƵ��BAND���ָ�� */
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstHead;/* ָ��ͷ��� */
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstTail;/* ָ��β��㣬���ڲ��� */
} CSS_COMM_SCAN_BAND_LIST_STRU;

typedef CSS_NV_RAT_RSSI_THRESHOLD_STRU   CSS_RSSI_THRESHOLD_STRU;
typedef CSS_NV_COMM_BAND_CONFIG_STRU     CSS_COMM_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��     : CSS_PUB_PREF_FREQ_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �ڴ��б����Ԥ��Ƶ��Ľṹ
*****************************************************************************/
typedef struct tagCSS_PUB_PREF_FREQ_STRU
{
    VOS_UINT32                                    ulFreqBegin;
    VOS_UINT32                                    ulFreqEnd;
    VOS_UINT8                                     ucRatSupport;
    VOS_UINT8                                     aucRsv[3];
    struct tagCSS_PUB_PREF_FREQ_STRU             *pstNext;
}CSS_PUB_PREF_FREQ_STRU;

/*****************************************************************************
 �ṹ��     : CSS_PUB_PREF_BAND_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �ڴ��б����Ԥ��BAND�Ľṹ
*****************************************************************************/
typedef struct tagCSS_PUB_PREF_BAND_STRU
{
    VOS_UINT8                                     ucBandInd;
    VOS_UINT8                                     ucFreqNum;
    VOS_UINT8                                     ucRatSupport;
    VOS_UINT8                                     aucRsv[1];
    CSS_PUB_PREF_FREQ_STRU                       *pstFreqHead;
    CSS_PUB_PREF_FREQ_STRU                       *pstFreqTail;
    struct tagCSS_PUB_PREF_BAND_STRU             *pstNext;
}CSS_PUB_PREF_BAND_STRU;

/*****************************************************************************
 �ṹ��     : CSS_PUB_PREF_MNC_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �ڴ��б����Ԥ��MNC�Ľṹ
*****************************************************************************/
typedef struct tagCSS_PUB_PREF_MNC_STRU
{
    VOS_UINT8                                     aucMncId[2];
    VOS_UINT8                                     ucBandNum;
    VOS_UINT8                                     ucNoPrefBandFlg; /* �ƶ���ȷGSM/WCDMA/LTEû������Ҫ����GSM/WCDMA/LTE���� */
    CSS_PUB_PREF_BAND_STRU                       *pstBandHead;
    CSS_PUB_PREF_BAND_STRU                       *pstBandTail;
    struct tagCSS_PUB_PREF_MNC_STRU              *pstNext;
}CSS_PUB_PREF_MNC_STRU;

/*****************************************************************************
 �ṹ��     : CSS_PUB_PREF_MCC_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �ڴ��б����Ԥ��MCC�Ľṹ
*****************************************************************************/
typedef struct tagCSS_PUB_PREF_MCC_STRU
{
    VOS_UINT8                                     aucMccId[2];
    VOS_UINT8                                     ucMncNum;
    VOS_UINT8                                     aucRsv[1];
    CSS_PUB_PREF_MNC_STRU                        *pstMncHead;
    CSS_PUB_PREF_MNC_STRU                        *pstMncTail;
    struct tagCSS_PUB_PREF_MCC_STRU              *pstNext;
}CSS_PUB_PREF_MCC_STRU;

/*****************************************************************************
 �ṹ��     : CSS_PUB_PREF_FREQ_INFO_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �ڴ��б����Ԥ��Ƶ���BAND�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucMccNum;
    VOS_UINT8                                     aucRsv[3];
    CSS_PUB_PREF_MCC_STRU                        *pstHead;
    CSS_PUB_PREF_MCC_STRU                        *pstTail;
}CSS_PUB_PREF_FREQ_INFO_STRU;


/*****************************************************************************
 �ṹ��     : CSS_MMC_ID_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : MCC ID�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMccId[2];
    VOS_UINT8                           aucRsv[2];
}CSS_MCC_ID_STRU;

typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_UINT16                          usMccNum;                         /* ���ڸ��µ�MCC�ܸ��� */
    VOS_UINT8                           ucIsUpdating;
    VOS_UINT8                           aucUpdated[CSS_MAX_UPDATE_MCC_NUM];/* �Ƿ��Ѿ����� */
    CSS_MCC_ID_STRU                     astMcc[CSS_MAX_UPDATE_MCC_NUM];   /* ���ڸ��µ�MCC�б� */
    CSS_TIMER_STRU                      stTimer;
}CSS_MCC_UPDATE_STRU;



typedef struct
{
    VOS_UINT8                           ucCloudEnable;
    VOS_UINT8                           ucPrefFreqEnable;                 /*�Ƿ���ƶ˻�ȡƵ����Ϣ*/
    VOS_UINT8                           aucRsv[1];

    VOS_UINT8                           aucVersion[MCC_INFO_VERSION_LEN];
    VOS_UINT32                          ulMemUsedLen;
    CSS_MCC_ID_STRU                     astNvMcc[CSS_MAX_NV_MCC_NUM];
    CSS_MCC_UPDATE_STRU                 astMccUpdate[CSS_MAX_PID_NUM];
    CSS_MCC_UPDATE_STRU                 stApMccUpdate;
    CSS_PUB_PREF_FREQ_INFO_STRU         stPrefMccList;                    /* ��������Ԥ��Ƶ���Ƶ�� */
}CSS_CLOUD_PUB_CONTROL_STRU;


typedef struct
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState;               /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16           enSubState;                /* ��ǰ���ڵ���״̬ */

    CSS_COMM_MSG_STRU                   stCommMsg;

    VOS_UINT32                          ulCssLphyOpid;             /* CSSģ���LPHYģ����OPID */
    CSS_AS_MSG_STRU                     stAsMsg;                   /* ��������AS��CSS�·�����Ϣ���� */
    CSS_SCAN_TYPE_ENUM_UINT8            ucScanType;                /* ��������ģ����CSS������Ϣʱ����¼��ʲô���͵�����ɨƵ */
    VOS_UINT8                           ucBandScanRslt;            /* ��������Ҫ��MMC��AS���ص�ԭ��ֵ */
    VOS_UINT8                           ucRsv[2];

    CSS_TIMER_STRU                      stSetInactiveModeTimer;
    CSS_TIMER_STRU                      stSetactiveModeTimer;
    CSS_TIMER_STRU                      stBandScanIndTimer;
    CSS_TIMER_STRU                      stStopBandScanTimer;
    CSS_TIMER_STRU                      stStartBGSTimer;

    CSS_RSSI_THRESHOLD_STRU             stRssiThreshold;           /* ��������NV������ */
    CSS_COMM_BAND_INFO_STRU             stCommBandInfo;            /* ��������NV��COMM BAND */

    CSS_COMM_SCAN_BAND_LIST_STRU        stCommScanBandList;
    CSS_COMM_SCAN_BAND_LIST_STRU        stAsScanBandList;          /* ����TDS�����BAND��ɨƵ��Ľ�� */
    /* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� Begin */
    VOS_UINT8                           aucRatSupportFlag[CSS_MAX_BAND_NUM];       /* ��������API����и���BAND����ʽ֧����� */
    /* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� End */
}CSS_CONTROL_STRU;

/* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� Begin */
typedef struct
{
    VOS_UINT16                          ucBand1;
    VOS_UINT16                          ucBand2;
}CSS_OVERLAP_BAND_STRU;
/* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� End */

#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
/*****************************************************************************
 �ṹ��     : CSS_MEM_BLOCK_HEAD_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : CSS��ͨ������̶��ڴ��ͷ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsedFlag;
    VOS_UINT8                           ucRsv[3];
}CSS_MEM_BLOCK_HEAD_STRU;

/*****************************************************************************
 �ṹ��     : CSS_MEM_BLOCK_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : CSS��ͨ������̶��ڴ��ṹ
*****************************************************************************/
typedef struct
{
    CSS_MEM_BLOCK_HEAD_STRU             stMemHead;
    VOS_UINT8                           aucData[CSS_CLOUD_BLOCK_DATA_LEN];
}CSS_MEM_BLOCK_STRU;
#endif



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern CSS_LPHY_FREQ_RANGE_INFO_STRU                  g_ausCssLteBandFreq[];
/* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� Begin */
extern CSS_OVERLAP_BAND_STRU                          g_aucOverLapBand[];
extern const VOS_UINT32                               g_aucOverLapBandSize;
/* c00285307 add for ����ʽ���ص�Ƶ��BAND�Ż� End */


extern CSS_CONTROL_STRU                               g_stCssControl;
extern CSS_CONTROL_STRU                              *pgstCssControl;
extern CSS_CLOUD_PUB_CONTROL_STRU                     g_stCloudContrl;

#define CSS_GetCloudContrlAddr()                      (&g_stCloudContrl)


#define CSS_GetControlAddr()                          (&g_stCssControl)

#define CSS_GetCurMainStatus()                        (CSS_GetControlAddr()->enMainState)
#define CSS_GetCurSubStatus()                         (CSS_GetControlAddr()->enSubState)

#define CSS_GetLphyCurOpid()                          (CSS_GetControlAddr()->ulCssLphyOpid)
#define CSS_SetLphyCurOpid(ulOpid)                    (CSS_GetControlAddr()->ulCssLphyOpid = (ulOpid))



#define CSS_GetCommScanBandListAddr()                 (&(CSS_GetControlAddr()->stCommScanBandList))
#define CSS_GetCommScanBandListCurrNode()             (CSS_GetCommScanBandListAddr()->pstCurr)
#define CSS_GetCommScanBandListHeadNode()             (CSS_GetCommScanBandListAddr()->pstHead)
#define CSS_GetCommScanBandListTailNode()             (CSS_GetCommScanBandListAddr()->pstTail)
#define CSS_GetCommScanCurFreqRangeIdx()              (CSS_GetCommScanBandListAddr()->ucCurFreqRangeIdx)

#define CSS_GetAsScanBandListAddr()                   (&(CSS_GetControlAddr()->stAsScanBandList))
#define CSS_GetAsScanBandListCurrNode()               (CSS_GetAsScanBandListAddr()->pstCurr)
#define CSS_GetAsScanBandListHeadNode()               (CSS_GetAsScanBandListAddr()->pstHead)
#define CSS_GetAsScanBandListTailNode()               (CSS_GetAsScanBandListAddr()->pstTail)
#define CSS_GetAsScanCurFreqRangeIdx()                (CSS_GetAsScanBandListAddr()->ucCurFreqRangeIdx)

#define CSS_GetPrefMccListAddr()                      (&(CSS_GetCloudContrlAddr()->stPrefMccList))
#define CSS_GetPrefMccHeadNode()                      (CSS_GetPrefMccListAddr()->pstHead)
#define CSS_GetPrefMccTailNode()                      (CSS_GetPrefMccListAddr()->pstTail)
#define CSS_GetPrefMccNodeNum()                       (CSS_GetPrefMccListAddr()->ucMccNum)


#define CSS_IsCloudStrategyEnable()                   (CSS_GetCloudContrlAddr()->ucCloudEnable)
#define CSS_IsPrefFreqEnable()                        (CSS_GetCloudContrlAddr()->ucPrefFreqEnable)
#define CSS_IsApUpdating()                            (CSS_GetCloudContrlAddr()->stApMccUpdate.ucIsUpdating)




#define CSS_GetLteModeTypeByBandInd(ucBandInd)        ((CSS_LPHY_BAND_IND_33 <= ucBandInd) ? CSS_LPHY_LTE_MODE_TYPE_TDD:CSS_LPHY_LTE_MODE_TYPE_FDD)

#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
#define CSS_GetCloudMemAddr()                         (&(g_acCssCloudFreqMemory[0]))
#define CSS_GetCloudMemUsedLen()                      (CSS_GetCloudContrlAddr()->ulMemUsedLen)
#endif


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_UINT32  CSS_ReadNvCommBandConfig
(
    CSS_NV_COMM_BAND_CONFIG_STRU  *pstCssCommBandConfig
);

extern VOS_UINT32  CSS_ReadNvRssiThreshold
(
    CSS_NV_RAT_RSSI_THRESHOLD_STRU  *pstCssRssiTH
);
extern VOS_VOID  CSS_SendOmGetOnePlmnPrefFreqRslt
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnInNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    ulRslt,
    CSS_PREF_FREQ_INFO_STRU                      *pstPrefFreq
);
extern VOS_VOID  CSS_SendOmGetPrefBandRslt
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnInNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    aulResult[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    ulRslt,
    VOS_UINT32                                    ulPlmnOutNum,
    CSS_PREF_BAND_INFO_STRU                      *pstPrefBand
);

extern VOS_UINT32  CSS_ReadNvCloudStrategy(VOS_VOID);
extern VOS_VOID  CSS_ReadNvCloudPrefArfcn(VOS_VOID);
extern VOS_VOID CSS_PrintLocalPrefFreqInfo(VOS_VOID);
extern VOS_VOID CSS_SndOmPubCloudCtrlInd(VOS_VOID);

extern VOS_VOID CSS_FreeCommScanRsltMemory(VOS_VOID);
VOS_VOID CSS_FreeAsScanRsltMemory(VOS_VOID);

extern VOS_VOID CSS_StartTimer(CSS_TIMER_STRU *pstTimer);

extern VOS_VOID CSS_StopTimer(CSS_TIMER_STRU *pstTimer);

extern VOS_VOID CSS_PrintCssRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID CSS_ClearLocalResource(VOS_VOID);

extern VOS_VOID   CSS_FSMTranState
(
    CSS_MAIN_STATE_ENUM_UINT16  enMainState,
    CSS_SUB_STATE_ENUM_UINT16   enSubState
);
extern VOS_VOID  CSS_SendOmBandScanResultInfoInd
(
    CSS_COMM_SCAN_BAND_NODE_STRU       *pBandNode,
    VOS_UINT8                           ucInBandNum
);
extern VOS_VOID  CSS_SendOmCommBandInfoInd
(
    CSS_COMM_BAND_INFO_STRU  *pstCssCommBandConfig
);
extern VOS_VOID  CSS_SendOmRatThresholdInfoInd
(
    CSS_RSSI_THRESHOLD_STRU  *pstCssRatThresholdConfig
);
extern VOS_VOID  CSS_SendOmBandApiInfoInd
(
    CSS_RAT_COVERAGE_STRU                           *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                    *pstBandScanResult
);
extern VOS_VOID  CSS_SendOmMmlUeSupportBandInfoInd
(
    NAS_MML_MS_BAND_INFO_STRU   *pstUeSupportBand
);
extern VOS_VOID  CSS_SndOmBandScanAbnormalInfo
(
    VOS_UINT32 ulFileName,
    VOS_UINT32 ulLineNo,
    VOS_UINT8 enBandScanFailReason,
    VOS_UINT8 ucPara1,
    VOS_UINT8 ucPara2
);

extern VOS_INT32 CSS_SecuMemCpy
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

#endif /* end of CssMain.h */



