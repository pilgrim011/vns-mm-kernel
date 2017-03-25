


#ifndef __NASLPPPUBLIC_H__
#define __NASLPPPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppAirMsg.h"
#include    "PsCommonDef.h"
#include    "EmmLppInterface.h"
#include    "NasLppEncodeDecodePublic.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"



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
#define NAS_LPP_NULL_PTR                VOS_NULL_PTR
/*��װ��ӡLOG�ĺ�*/
#ifdef PS_ITT_PC_TEST
#define NAS_LPP_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LPP_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#define NAS_LPP_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_ERR_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LPP_ERR_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_LPP_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_LPP_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_LPP_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LPP_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_LPP_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_LPP_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_LPP_ERR_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_LPP_ERR_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif

/* LPP���ڴ濽���궨�� */
//#define __LINE__    0
#define NAS_LPP_LOG_ERR(String)   vos_printf(" %s\r\n",String)


#if (VOS_OS_VER == VOS_WIN32)

#define NAS_LPP_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else

#define NAS_LPP_MEM_CPY_S(pDestBuffer, DestCount, pSrcBuffer, SrcCount) \
        (VOS_VOID)NAS_LPP_SecuMemCpy(pDestBuffer, DestCount, pSrcBuffer, SrcCount, (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength) \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength )  \
        (VOS_VOID)TLPS_MEM_MOVE_S((pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#endif

#define NAS_LPP_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
    PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_LPP_MEM_FREE(pAddr) \
            {\
                if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_LPP), (pAddr)))\
                {\
                    NAS_LPP_LOG_ERR("NAS_LMM_MEM_FREE  ERR!!");\
                }\
            }
#define NAS_LPP_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((PS_PID_LPP), (ulSize))

#define NAS_LPP_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_LPP),(ulLen))


/*Memset MSG*/
#define NAS_LPP_MEM_SET_MSG(pMsgBuffer, ulMaxMsgSize, ucData, MsgSize) \
        (VOS_VOID)TLPS_MEM_SET_S((((NAS_LPP_MSG*)pMsgBuffer)->ucRsv), ulMaxMsgSize - NAS_LPP_MSG_HEADER_LENGTH, ucData, MsgSize - NAS_LPP_MSG_HEADER_LENGTH, __LINE__, THIS_FILE_ID)

/* ������Ϣ */
#define NAS_LPP_SND_MSG(pMsg)\
    {\
        NAS_LPP_PrintLppSendMsg((const PS_MSG_HEADER_STRU *)pMsg, NAS_COMM_GET_LPP_PRINT_BUF());\
        NAS_LPP_NORM_LOG("====================IN MSG CONTENT is : ============");\
        NAS_COMM_PrintArray(             NAS_COMM_GET_LPP_PRINT_BUF(),\
                                         (VOS_UINT8 *)pMsg,\
                                         (pMsg->ulLength + NAS_LPP_MSG_HEADER_LENGTH));\
        NAS_LPP_NORM_LOG("====================================================");\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_LPP) , (pMsg)))\
            {\
                NAS_LPP_ERR_LOG("NAS_LPP_SND_MSG:Msg Snd Err!");\
            }\
    }

#define LPP_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)


#define NAS_LPP_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

#define NAS_LPP_INTER_WRITE_EMM_MSG_HEAD(pstMsg, ulLppInterMsgID)\
                    (pstMsg)->ulMsgId   = (ulLppInterMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;


#define NAS_LPP_WRITE_LRRC_MSG_HEAD(pstMsg, ulLrrcLppMsgID)\
                    (pstMsg)->enMsgId   = (ulLrrcLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ERRC;

#define NAS_LPP_WRITE_INTRA_MSG_HEAD(pstMsg, ulIntraLppMsgID)\
                    (pstMsg)->enMsgId   = (ulIntraLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;

#define NAS_LPP_WRITE_MTA_MSG_HEAD(pstMsg, ulMtaLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulMtaLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_MTA;

#define NAS_LPP_WRITE_LCS_MSG_HEAD(pstMsg, ulLcsLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulLcsLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid =   PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_LCS;

#define NAS_LPP_COMP_STATE(enLppMainState,enLppSubState)  ((((VOS_UINT32)enLppMainState)<<16)|(((VOS_UINT32)enLppSubState)&0xFFFF))
#define NAS_LPP_STATE_TBL_SIZE(astStateTbl)  ( sizeof(astStateTbl)/sizeof(NAS_LPP_FSM_ACT_STRU) )


typedef VOS_INT32 (*NAS_LPP_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);
typedef VOS_UINT32 (*NAS_LPP_ACTION_FUN)
(
    VOS_UINT32, /* ��ϢID   */
    VOS_VOID *  /* ��Ϣָ�� */
);

typedef VOS_VOID (*NAS_LPP_TIMER_PROC_FUNC)(VOS_UINT8, VOS_UINT8, VOS_UINT8, VOS_VOID*);

#define NAS_LPP_MAX_SESSION_COUNT       (3) /*���������session�ĸ���*/
#define NAS_LPP_MAX_TRANS_COUNT         (4) /*����session��ͬʱ���������transaction�ĸ���*/
#define NAS_LPP_MAX_TRANS_POOL_COUNT    (8) /*transactionʵ��صĸ���*/
#define NAS_LPP_MAX_BUFF_MSG_COUNT      (8) /*���������Ի����LPP��Ϣ����*/
#define NAS_LPP_MAX_BUFF_MSG_LEN        (1024)  /*���Ի���ĵ���LPP��Ϣ����󳤶�??*/
#define NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN        (235)  /*���Ի����lcs�����������buff����󳤶�*/
#define NAS_LPP_MAX_RETRANS_COUNT       (3)
#define NAS_LPP_MAX_UP_MSG_PER_TRANSACTION  3
#define NAS_LPP_MAX_FSM_MSG_BUFF_POOL_COUNT         (4) /*״̬����Ϣ����صĸ���*/
#define NAS_LPP_MAX_FSM_MSG_BUFF_LEN                (500) /*״̬����Ϣ����ĳ���*/
#define NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM           2
#define NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM            2


#define LPP_MAX_MSG_CONTAINER_CNTNTS_LEN            (2048)
#define NAS_LPP_TRANS_END                           (1)
#define NAS_LPP_TRANS_NOT_END                       (0)
#define NAS_LPP_SEQUENCE_NUM_INVALID                (0xFFFE)
#define NAS_LMM_LPP_OPID_NOT_VAILID                 (0xFFFFFFFF)
#define NAS_LPP_TIMER_INVAILD_PARA                  (0xFF)
#define NAS_LPP_MAX_POS_TECH                        (3)
#define NAS_LPP_MIN_SND_MSG_LEN                     (4)
#define NAS_LPP_MSG_HEADER_LENGTH                   (20)
#define NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN             (5000)
#define NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN     (600000)

/*��ʱ��ʱ��*/
#ifdef PS_ITT_PC_TEST_NAS
#define TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN     (1000)      /*���пտ���Ϣ�ش���ʱ��ʱ��*/
#define TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    (5000)
#define TI_NAS_LPP_LOCATION_INVALID_TIMER_LEN       (NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN)
#define TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN     (500)
#define TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN           (5000)
#define TI_NAS_LPP_WAIT_RE_EST_TIMER_LEN            (2000)
#define TI_NAS_LPP_RESPONSE_TIMER_TIMER_LEN         (0)
#define TI_NAS_LPP_PERIODICAL_REPORT_TIMER_LEN      (0)
#define TI_NAS_LPP_REPORT_DURATION_TIMER_LEN        (0)
#define TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN          (NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN)/* added by wangensheng */
#define TI_NAS_LPP_SEQUENCE_NUMBER_INVALID_LEN      (10*60*1000)
#else
#define TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN     (1000)      /*���пտ���Ϣ�ش���ʱ��ʱ��*/
#define TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    (5000)
#define TI_NAS_LPP_LOCATION_INVALID_TIMER_LEN       (NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN)
#define TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN     (500)
#define TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN           (5000)
#define TI_NAS_LPP_WAIT_RE_EST_TIMER_LEN            (2000)
#define TI_NAS_LPP_RESPONSE_TIMER_TIMER_LEN         (0)
#define TI_NAS_LPP_PERIODICAL_REPORT_TIMER_LEN      (0)
#define TI_NAS_LPP_REPORT_DURATION_TIMER_LEN        (0)
#define TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN          (NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN)/* added by wangensheng */
#define TI_NAS_LPP_SEQUENCE_NUMBER_INVALID_LEN      (10*60*1000)
#endif


#define NAS_LPP_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_LPP_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))
#define NAS_LPP_GET_GNSS_CAP_MAX            (3)
#define NAS_LPP_OTDOA_CELL_MIN_NUM          (3)
#define NAS_LPP_IsReportInfinity(ucReportAmount)  ( (0 == ucReportAmount) ? PS_TRUE : PS_FALSE  )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*******************************************************************************
 ö����    : NAS_LPP_ERROR_CODE_ENUM
 ö��˵��  : LPP�Ĵ���ԭ��֮
 1.��    ��   : 2015��07��06��
   ��    ��   :
   �޸�����   :
*******************************************************************************/
enum NAS_LPP_ERROR_CODE_ENUM
{
    NAS_LPP_SUCCESS                     = 0,         /*LPP ģ�麯�����سɹ�*/
    NAS_LPP_FAILURE                        ,         /*LPP ģ�麯������ʧ��*/
    NAS_LPP_MSG_DUPLICATE                  ,         /*��Ϣ �ظ�*/
    NAS_LPP_CONN_MANAGE_FAIL               ,         /*EMM��������LPP��Ϣʱ�����������������ʧ�ܡ�������Ϣ����ʧ�ܣ�lpp�����ӹ���ģ���lpp��Ϣ��resultȡ��ֵ*/
    NAS_LPP_FSM_NOT_MATCH                  ,         /*��Ϣ��״̬��״̬��ƥ��*/
    NAS_LPP_MSG_PROCESS_CMPL               ,         /*lpp��Ϣ������ɣ��������*/
    NAS_LPP_MSG_VERIFY_SUCC                ,
    NAS_LPP_MSG_VERIFY_FAIL                ,
    NAS_LPP_MSG_VERIFY_HEAD_FAIL           ,
    NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR,
    NAS_LPP_FSM_MSG_BUFF_EMPTY,
    NAS_LPP_ASSIST_DATA_CONFLICT,
};
typedef VOS_UINT32  NAS_LPP_ERROR_CODE_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_UPLINK_MSG_TYPE_ENUM
 ö��˵��  : LPP������Ϣ����
 1.��    ��   : 2015��07��06��
   ��    ��   :
   �޸�����   :
*******************************************************************************/
enum NAS_LPP_UPLINK_MSG_TYPE_ENUM
{
    NAS_LPP_UPLINK_MSG_TYPE_ACK             = 0,         /*������Ϣ��ACK��Ϣ*/
    NAS_LPP_UPLINK_MSG_TYPE_PROCESS         = 1,         /*LPP������Ϣ*/

    NAS_LPP_UPLINK_MSG_TYPE_BUTT,
};
typedef VOS_UINT32  NAS_LPP_UPLINK_MSG_TYPE_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_MAIN_STATE_ENUM
 ö��˵��  : LPP����״̬
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum    NAS_LPP_MAIN_STATE_ENUM
{
    /*=================== EMM����״̬ ===================*/
    LPP_MS_IDLE                         = 0, /*��ǰû���κ�LPP����*/
    LPP_MS_CAPABILITY                   = 1, /*������������*/
    LPP_MS_ASSISTDATA                   = 2, /*������������*/
    LPP_MS_LOCATION                     = 3, /*λ����Ϣ��������*/

    LPP_MS_BUTT
};
typedef VOS_UINT32  NAS_LPP_MAIN_STATE_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_SUB_STATE_ENUM
 ö��˵��  : LPP����״̬

     ע��:  g_astLppSubStateTime��g_astNasLppFsm�������ĵ�Ԫ�������״̬�Ķ����Ⱥ�˳��
            ǿ��أ���Ҫ�����޸���״̬��˳�򡢻���������״̬�м���붨������״̬(������������µ���״̬����)��
            ������м�����¶�������״̬����Ҫ�����޸����ϵ�������

 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum    NAS_LPP_SUB_STATE_ENUM
{

    /*===================LPP_MS_IDLE��״̬===================*/
    LPP_SS_IDLE                             = 0, /*��ʾ��ǰû���κ�LPP����*/

    /*==================LPP_MS_CAPABILITY��״̬==============*/
    LPP_SS_CAP_REQ_WAIT_CNF                 = 1, /*��ʾ�������������е�GNSS�ظ�����*/
    LPP_SS_CAP_PRIVIDE_WAIT_CN_ACK          = 2, /*��ʾ�ṩ����������������ACK*/
    LPP_SS_CAP_WAIT_ABORT_CN_ACK            = 3, /*��ʾ����transaction abort֮�������ظ�ack*/

    /*==================LPP_MS_ASSISTDATA��״̬==============*/
    LPP_SS_ASSISTDATA_REQ_WAIT_CN_ACK       = 4, /*��ʾ�������ศ�����ݵ�����ACK*/
    LPP_SS_ASSISTDATA_WAIT_CN_CNF           = 5, /*��ʾ�����ศ�����ݻظ�*/
    LPP_SS_ASSISTDATA_WAIT_ABORT_CN_ACK     = 6, /*��ʾ�������ݹ��̵������abort�ظ�ACK*/

    /*==================LPP_MS_LOCATION��״̬================*/
    LPP_SS_WAIT_ASSISTDATA_RCV_CMP          = 7, /*��ʾ�ȴ����ո����������,��ʾ��ǰ�����ڽ����еĸ�����������*/
    LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP  = 8, /*��ʾ�ȴ��������������������,��ʾ��ǰû�и������ݣ���Ҫ����һ���µ�transaction���븨������*/
    LPP_SS_WAIT_LRRC_MEAS_CNF               = 9, /*��ʾ�ȴ�LRRC�����ظ�*/
    LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF       = 10,
    LPP_SS_WAIT_LOCATION_CN_ACK             = 11,/*��ʾ�ȴ�λ���ṩ��Ϣ��ACK�ظ�*/
    LPP_SS_WAIT_LOCATION_ABORT_CN_ACK       = 12,/*��ʾ�ȴ�λ����������abort��������ACK�ظ�*/

    LPP_SS_WAIT_INTRA_DATA_CNF              = 13, /*����data req�󣬵ȴ�LPP �����ӹ���ģ��ظ�DATA CNF����Ϣ*/
    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK= 14, /*����LPP ACK��data req�󣬵ȴ�LPP �����ӹ���ģ��ظ�DATA CNF����Ϣ*/
    LPP_SS_WAIT_MEAS_IND                    = 15, /*��ʾ��ǰ�ȴ�LRRC��GNSS�Ĳ����ظ�*/


    LPP_SS_BUTT
};
typedef VOS_UINT32  NAS_LPP_SUB_STATE_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_UP_STATE_STATE_ENUM
 ö��˵��  : LPP��״̬
 1.��    ��   : 2015��11��24��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum  NAS_LPP_UP_STATE_STATE_ENUM
{
    LPP_UP_STATE_IDLE                             = 0, /*��ʾ��ǰû���κ�LPP����*/
    LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF           = 1, /*��ʾ��MTA OTDOA�������ݻظ�*/
    LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF          = 2, /*��ʾ�ȴ�LRRC ECID�Ĳ����ظ�*/
    LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF         = 3, /*��ʾ�ȴ�LRRC OTDOA�Ĳ����ظ�*/
    LPP_UP_STATE_WAIT_LRRC_MEAS_IND               = 4, /*��ʾ��ǰ�ȴ�LRRC�Ĳ����ظ�*/

    LPP_UP_STATE_BUTT
};
typedef VOS_UINT32  NAS_LPP_UP_STATE_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_SUB_STATE_ENUM
 ö��˵��  : LPP����״̬
 1.��    ��   : 2015��07��06��
   ��    ��   :
   �޸�����   :
*******************************************************************************/
enum    NAS_LPP_AIR_MSG_ENUM
{
    /*���е�*/
    NAS_LPP_AIR_MSG_PROVIDE_CAP  = 0,
    NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA,
    NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO,
    NAS_LPP_AIR_MSG_UP_ERR,
    NAS_LPP_AIR_MSG_UP_ABORT,
    NAS_LPP_AIR_MSG_UP_LPP_ACK,

    /*���е�*/
    NAS_LPP_AIR_MSG_REQUEST_CAP,
    NAS_LPP_AIR_MSG_PROVIDE_ASSIST_DATA,
    NAS_LPP_AIR_MSG_REQUEST_LOCATION_INFO,
    NAS_LPP_AIR_MSG_DOWN_ERR,
    NAS_LPP_AIR_MSG_DOWN_ABORT,

    NAS_LPP_AIR_MSG_BUTT
};
typedef VOS_UINT32  NAS_LPP_AIR_MSG_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_SUB_STATE_ENUM
 ö��˵��  : LPP����ʹ�õĶ�ʱ��
             �ϱ����ȼ����������ϱ�>ֻ�ϱ�һ��>����������ʽ�������������λ��
             ��Ϣ��ʱ�򣬷������������ϱ���ʽ�������ֻ���3��ͬʱ��������������
             ��ôUE��Ҫ�������ȼ��͵��ϱ���ʽ

   ע��: �������Ķ�����g_astLppSubStateTime��g_afNasLppStateTimerFun/g_afNasLppNoneStateTimerFun��ǿ��ء��¶����������������ӣ�
   ��Ҫ���м���������µĶ�ʱ�����֡��޸ĺ󣬲�Ҫ�����޸�������������

 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum NAS_LPP_TIMER_PARA_ENUM
{
/*------------------------------------------״̬����Ӧ�Ķ�ʱ��--------------------------------------*/
    /*-------״̬��ʱ����������transaction��----------------------*/
    TI_NAS_LPP_MSG_TIMER_NULL           = 0,
    TI_NAS_LPP_UPLINK_MSG_RETRANS       = 1,    /*LPP���͵����пտڵ��ش���ʱ��*/
    TI_NAS_LPP_WAIT_CN_ASSIST_DATA      = 2,    /*��������·��������ݶ�ʱ��*/
    TI_NAS_LPP_WAIT_LRRC_MEAS_CNF       = 3,    /*�ȴ�LRRC �����ظ�*/

    TI_NAS_LPP_WAIT_GNSS_CAP_CNF        = 4,    /*�ȴ�gnss�ظ�����*/
    TI_NAS_LPP_WAIT_INTRA_DATE_CNF      = 5,    /*�ȴ��ڲ�DataCnf��Ϣ*/


    /*-------���ӹ���ά���Ķ�ʱ�����������LPP��entity��------------*/
    TI_NAS_LPP_WAIT_EST_CNF             = 6,   /*�ȴ�LMM����·�ظ�*/
    TI_NAS_LPP_WAIT_RE_EST              = 7,   /*�ؽ�����ʱ��*/
    TI_NAS_LPP_SEQUENCE_NUMBER_INVALID  = 8,   /*sequence Number�Ƿ���Ч��ʱ��*/

    /* ������״̬��ʱ�����ӵ����TI_NAS_LPP_STATE_TIMER_MAX_NUM֮ǰ */
    TI_NAS_LPP_UP_STATE_TIMER_START_NUM,
    TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA   = TI_NAS_LPP_UP_STATE_TIMER_START_NUM,    /*�û����������·��������ݶ�ʱ��*/
    TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF  ,    /*�ȴ�LRRC ECID�����ظ�*/
    TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF ,    /*�ȴ�LRRC OTDOA�����ظ�*/

    TI_NAS_LPP_STATE_TIMER_MAX_NUM         ,
/*------------------------------------------��״̬����Ӧ�Ķ�ʱ��--------------------------------------*/
    /*-------�ϱ�λ����Ϣ��Э�鶨ʱ����������session��------------*/
    TI_NAS_LPP_RESPONSE_TIMER = TI_NAS_LPP_STATE_TIMER_MAX_NUM ,    /*���ֻ��һ�ε���Ӧʱ��*/
    TI_NAS_LPP_PERIODICAL_REPORT           ,    /*�������ϱ���ʱ����*/
    TI_NAS_LPP_REPORT_DURATION             ,    /*�����ϱ��ϱ����������ʱ��*/

    /*-------GPSλ����Ϣ�Ƿ���Ч�Ķ�ʱ��---------------------------*/
    TI_NAS_LPP_LOCATION_INVALID            ,    /*λ����Ϣ��Ч��ʱ��*/

    TI_NAS_LPP_PTC_TIMER_MAX_NUM         ,      /*Э�鶨ʱ�����ı߽�ֵ*/
    /*-------�û��涨λ����ʹ�õ��˶�ʱ��--------------------------*/
    TI_NAS_LPP_UP_RESPONSE_TIMER = TI_NAS_LPP_PTC_TIMER_MAX_NUM,  /*�û������ֻ��һ�ε���Ӧʱ��*/
    TI_NAS_LPP_UP_PERIODICAL_REPORT           ,    /*�û����������ϱ���ʱ����*/
    TI_NAS_LPP_UP_REPORT_DURATION             ,    /*�û��������ϱ��ϱ����������ʱ��*/

    TI_NAS_LPP_TIMER_PARA_BUTT
};
typedef VOS_UINT8   NAS_LPP_TIMER_PARA_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_LPP_CONN_STATUS_ENUM
 ö��˵��  : LPP������״̬
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum NAS_LPP_CONN_STATUS_ENUM
{
    NAS_LPP_CONN_STATUS_IDLE            = 0,    /*LPP��ǰ���ڿ���̬*/
    NAS_LPP_CONN_STATUS_CONNECT         = 1,    /*LPP��ǰ��������̬*/
    NAS_LPP_CONN_STATUS_ESTING          = 2,    /*LPP��ǰ���ڽ���������*/

    NAS_LPP_CONN_STATUS_BUTT
};
typedef VOS_UINT32   NAS_LPP_CONN_STATUS_ENUM_UINT32;

/*******************************************************************************
 ö����    : NAS_LPP_REPORT_LOCATION_TYPE_ENUM
 ö��˵��  : LPP�ϱ�λ����Ϣ�ķ�ʽ
 1.��    ��   : 2015��07��06��
   ��    ��   : lifuxin 00253982
   �޸�����   : Added for LPP
*******************************************************************************/

enum NAS_LPP_REPORT_LOCATION_TYPE_ENUM
{
    NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER            = 0,/*���������ϱ�*/
    NAS_LPP_REPORT_LOCATION_TYPE_PERIOD             = 1,/*�������ϱ�*/
    NAS_LPP_REPORT_LOCATION_TYPE_ONCE               = 2,/*�ϱ�һ��*/

    NAS_LPP_REPORT_LOCATION_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_LPP_POSITION_TECH_ENUM
 ö��˵��  : LPP��λ����ö��
 1.��    ��   : 2015��07��06��
   ��    ��   : lifuxin 00253982
   �޸�����   : Added for LPP
*******************************************************************************/

enum NAS_LPP_POSITION_TECH_ENUM
{
    NAS_LPP_POSITION_TECH_NULL                      = 0,/*��ǰ�ṹû�б�ռ��*/
    NAS_LPP_POSITION_TECH_ECID                      = 1,/*ECID���ϱ�����*/
    NAS_LPP_POSITION_TECH_OTDOA                     = 2,/*OTDOA�Ķ�λ����*/
    NAS_LPP_POSITION_TECH_GNSS                      = 3,/*GNSS�Ķ�λ����*/

    NAS_LPP_POSITION_TECH_BUTT
};
typedef VOS_UINT8 NAS_LPP_POSITION_TECH_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_LPP_POSITION_TECH_ENUM
 ö��˵��  : LPP��λ����ö��
 1.��    ��   : 2015��07��06��
   ��    ��   : lifuxin 00253982
   �޸�����   : Added for LPP
*******************************************************************************/

enum NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM
{
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_LOW,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_BUTT
};
typedef VOS_UINT8 NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_LPP_POSITION_PROCESS_TYPE_ENUM
 ö��˵��  : ��¼��ǰ��λ�������û��滹�ǿ�����
 1.��    ��   : 2015��11��20��
   ��    ��   : lifuxin 00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum NAS_LPP_POSITION_PROCESS_TYPE_ENUM
{
    NAS_LPP_POSITION_PROCESS_TYPE_NULL,
    NAS_LPP_POSITION_PROCESS_TYPE_CONTROL_PLANE,
    NAS_LPP_POSITION_PROCESS_TYPE_USER_PLANE,
    NAS_LPP_POSITION_PROCESS_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM
 ö��˵��  : ��¼�û��浱ǰ���������һ�ֶ�λ����
 1.��    ��   : 2015��11��20��
   ��    ��   : lifuxin 00253982
   �޸�����   : Added for LPP
*******************************************************************************/
enum NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*******************************************************************************
 �ṹ��    : NAS_LPP_FSM_ACT_STRU
 �ṹ˵��  : NAS_LPP_FSM_ACT_STRU
 1.��    ��   : 2015��07��06��
   ��    ��   :Xiaojun
*******************************************************************************/

typedef struct
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgId;
#if 0
    NAS_LPP_ACTION_FUN                  pfActionFun;   /* �������� */
#endif
}NAS_LPP_FSM_ACT_STRU;

/*******************************************************************************
 �ṹ��    :
 �ṹ˵��  : NAS_LPP_FSM_STRU
 1.��    ��   : 2015��07��06��
   ��    ��   :Xiaojun
*******************************************************************************/

typedef struct
{
    VOS_UINT32                          ulState;
    VOS_UINT32                          ulSize;     /*NAS_LPP_FSM_ACT_STRU�ĸ���*/
    NAS_LPP_FSM_ACT_STRU               *pfFsmActTbl;
}NAS_LPP_FSM_STRU;

/*******************************************************************************
 �ṹ��    :
 �ṹ˵��  : LPP-TransactionID
 1.��    ��   : 2015��07��06��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[3];
}NAS_LPP_SUB_STATE_TIME_STRU;


/*******************************************************************************
 �ṹ��    :
 �ṹ˵��  : LPP-TransactionID
 1.��    ��   : 2015��07��06��
   ��    ��   :
*******************************************************************************/
typedef struct
{
    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRes[2];
}NAS_LPP_TRANS_ID_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_MSG_IDENTITY_STRU
 �ṹ˵��  : Ψһʶ��һ��LPP��Ϣ�Ľṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionId;        /*�ỰID���������generic��Ϣ��Ҫʹ��*/
    VOS_UINT16                          usSequnceNum;       /*��ǰ�Ự����ʹ�����е���Ϣ����Ϣ����*/
    VOS_UINT8                           aucRsv[2];
    NAS_LPP_TRANS_ID_STRU               stTransId;          /*Transaction�ı�ʶ*/
    NAS_LPP_UPLINK_MSG_TYPE_UINT32      enUplinkMsgType;    /*������Ϣ����*/
    VOS_BOOL                            bIsProvideLocFalg;   /*��ʾ�����洢��Ϣ�Ƿ���provideLocation��Ϣ*/
}NAS_LPP_MSG_IDENTITY_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_TIMER_STRU
 �ṹ˵��  : LPP����transaction���еĶ�ʱ��
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    HTIMER                                  hTimer;             /* vos�����Timer Id */
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerId;          /* Timer����*/
    VOS_UINT8                               aucReserve1[3];     /* ���ֽڶ��룬���� */
    VOS_UINT32                              ulPara;             /* ��ʱ����Ҫ����Ĳ���*/
}NAS_LPP_TIMER_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_CAP_REQ_STRU
 �ṹ˵��  : LPP�����������󻺴�
 1.��    ��   : 2015��08��04��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpAgnssCapReq    :1;
    VOS_UINT32                              bitOpOtdoaCapReq    :1;
    VOS_UINT32                              bitOpEcidCapReq     :1;
    VOS_UINT32                              bitOpSpare          :29;

    LPP_AGNSS_REQ_CAP_STRU                  stGnssReqCap;
}NAS_LPP_CAP_REQ_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_FSM_MSG_BUFF_POOL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��07��06��
   ��    ��   : xiaojun
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulSenderPid;
    VOS_UINT32                              ulMsgId;
    VOS_VOID                               *pMsg;
}NAS_LPP_FSM_MSG_BUFF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_FSM_MSG_BUFF_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��08��04��
   ��    ��   :
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucHighNum;
    VOS_UINT8                               aucRsv[3];
    NAS_LPP_FSM_MSG_BUFF_STRU               astHighMsg[NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM];

    VOS_UINT8                               ucLowNum;
    VOS_UINT8                               aucRsv1[3];
    NAS_LPP_FSM_MSG_BUFF_STRU               astLowMsg[NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM];
}NAS_LPP_FSM_BUFF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_TRANSACTION_ELEMENT_ENTIYT_STRU
 �ṹ˵��  : LPP����transaction��ʵ��ṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpWaitEcidMeasCnf    :1;
    VOS_UINT32                              bitOpWaitOtdoaMeasCnf   :1;
    VOS_UINT32                              bitOpOtdoaAssistReq     :1;
    VOS_UINT32                              bitOpSpare:29;

    NAS_LPP_TRANS_ID_STRU                   stTransId;              /*transaction ID*/
    NAS_LPP_MAIN_STATE_ENUM_UINT32          enLppMainState;         /*��ʾ��ǰtransaction����״̬*/
    NAS_LPP_SUB_STATE_ENUM_UINT32           enLppSubState;          /*��ʾ��ǰtransaction����״̬*/
    NAS_LPP_TIMER_STRU                      stLppTimer;             /*����transaction running�Ķ�ʱ��*/
    NAS_LPP_AIR_MSG_ENUM_UINT32             enLastUpMsgId;          /*���͵����µ�����LPP��Ϣ*/
    VOS_UINT8                               ucRetranNum;            /*�ش�����*/
    VOS_UINT8                               ucTransEndFlag;         /*��ʾ��transaction�Ƿ����*/
    VOS_UINT8                               ucCommCfgIndex;         /*��ʾ�洢�ı�transactioλ��������ص�������Ϣ������*/
    VOS_UINT8                               aucRsv[1];

    /*����Ŀտ�request capability info�� �Ĳ���,����provide capabilities informationʹ��*/
    NAS_LPP_CAP_REQ_STRU                    stCapReq;

    NAS_LPP_FSM_BUFF_STRU                   stFsmBuff;
}NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_MSG_HEAD_STRU
 �ṹ˵��  : LPP��Ϣͷ�ṹ
 1.��    ��   : 2015��08��04��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLppTransactionId:1;
    VOS_UINT32                              bitOpSequenceNumber:1;
    VOS_UINT32                              bitOpAcknowledgement:1;
    VOS_UINT32                              bitOpLppMessageBody:1;
    VOS_UINT32                              bitOpSpare:28;

    LPP_TRANSACTION_ID_STRU                 stTransactionId;
    VOS_BOOL                                bEndTransaction;
    LPP_SEQUENCE_NUMBER_STRU                stSequenceNumber;
    LPP_ACKNOWLEDGEMENT_STRU                stAcknowledgement;
}NAS_LPP_MSG_HEAD_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 �ṹ˵��  : LPP�Ự��transaction��ʵ��ṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucTransIdCount;         /*��ʾ��ǰ�Ự��running��transaction������*/
    VOS_UINT8                                   aucRsv[3];

    /*��ʾtransactionʵ����transaction element entity pool�������*/
    VOS_UINT8                                   aucTransElementIdx[NAS_LPP_MAX_TRANS_COUNT];
}NAS_LPP_TRANSACTION_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 �ṹ˵��  : LPP�Ự��transaction��ʵ��ṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    /*��Ӧbit 1:��Ӧ��transactionʵ�屻ʹ�ã� ��Ӧbit 0:��Ӧ��transactionʵ��δʹ��*/
    VOS_UINT32                                  ulTransBitmap;

    /*��ʾ��һtransactionʵ��*/
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU     astTransElementEntity[NAS_LPP_MAX_TRANS_POOL_COUNT];
}NAS_LPP_TRANSACTION_ENTITY_POOL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU
 �ṹ˵��  : ���������ϱ���ʽά����ȫ����Ϣ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{

    VOS_UINT32                                  ulReportDuration;   /*�ϱ�������ʱ��*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*�ϱ�����ʱ�䶨ʱ��*/
}NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU
 �ṹ˵��  : �������ϱ���ʽά����ȫ����Ϣ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucReportAmount;     /*Ҫ���ϱ����ܵļ���*/
    VOS_UINT8                                   ucReportingAmount;  /*�Ѿ��ϱ��ĵļ���*/
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16    enOtdoaRprtInterval;/*�ϱ���ʱ������ֻ������LRRCʱʹ��*/
    VOS_UINT32                                  ulReportIntraval;   /*�ϱ���ʱ����*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*�������ϱ���ʱ��*/
}NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU
 �ṹ˵��  : �ϱ�һ��ά����ȫ����Ϣ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulResponseTime;     /*response timeʱ��*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*�ϱ�һ�ζ�ʱ��*/
}NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_REPORT_CRITERIA_STRU
 �ṹ˵��  : lpp�ϱ�λ����Ϣ�ķ�ʽ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enType;
    VOS_UINT8                                   ucSessionIndex;
    VOS_UINT8                                   ucSessionTransIndex;
    VOS_UINT8                                   ucRsv;

    union
    {
        NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU   stReportTrigger;
        NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU    stReportPeriod;
        NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU      stReportOnce;
    }u;
}NAS_LPP_REPORT_CRITERIA_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 �ṹ˵��  : LPP�����Ự��ʵ��ṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSessionId;            /*��ǰ�Ự��ID*/
    PS_BOOL_ENUM_UINT8                              enRcvedDownMsg;
    VOS_UINT8                                       ucLastDownSequenceNum;  /*��ǰ�Ự�յ������µ�����LPP��Ϣ��sequence number*/
    VOS_UINT8                                       aucRsv[2];
    NAS_LPP_TIMER_STRU                              stSequenceNumInvalid;   /*��ʾ��session�ɼ��Ķ�ʱ����Ŀǰ����sequenceNumber�Ƿ���Чά��ʹ��*/

    NAS_LPP_TRANSACTION_STRU                        stLppTrans;             /*һ���Ự�е�����transactionʵ��*/
}NAS_LPP_SESSION_ENTITY_ELEMENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_SESSION_ENTITY_STRU
 �ṹ˵��  : LPP�Ựʵ��Ľṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSessionActiveBitmap;  /*��ǰSESSION��״̬:��ӦbitΪ1����Ӧ��sessionʵ�屻ʹ�ã���ӦbitΪ0����Ӧ��ʵ��δ��ʹ��*/
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU             astLppSessionEntity[NAS_LPP_MAX_SESSION_COUNT]; /*��һ�Ựʵ��*/
    /*ά��һ����ʶȥ��ʶ��ǰ��û�и��ֶ�λ�����ĸ�����Ϣ*/

}NAS_LPP_SESSION_ENTITY_POOL_STRU;

/*****************************************************************************
 �ṹ��    : LPP_UPLINK_MSG_BUF_STRU
 �ṹ˵��  : LPP_UPLINK_MSG_BUF_STRU���ݽṹ
 ����      : lifuxin 00253982 2015-07-02 �¿���
 ���ܵ�����: ���л���buffer�洢�����ݽṹ��ÿһ��buffer����LPP��Ϣ��IDENTIY��
             �Լ������ֱ����Ϣʵ�壬��������ĺô��ǲ���ÿһ��buffer��ʱ��
             ��֪������һ��session����һ��transaction����һ���տ���Ϣ������
             �Ϳ��Զ�̬��ά��ָ����buffer��
*****************************************************************************/
typedef struct
{
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;    /*һ��LPP��Ϣ��Ψһ�����ʶ��*/
    VOS_BOOL                            bSendBufFlag;        /*��ʾ��buffer�Ļ�����Ϣ�Ƿ��Ѿ����ͳɹ��������࣬��ACK*/

    union
    {
        LPP_LMM_DATA_REQ_STRU           stLppDataReq;       /*LPP����LMM��ֱ����Ϣ*/
        VOS_UINT8                       aucLppMsg[NAS_LPP_MAX_BUFF_MSG_LEN];
    } u;
}LPP_UPLINK_MSG_BUF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_CONN_MANAGE_STRU
 �ṹ˵��  : LPP���ӹ������ݽṹ
 ���ܵ�����: �����пտ�Ҫ���������ǰΪIDLE�� ���LMM������������ͬʱ������Ӧ
             ����LMM��ֱ����Ϣ�ŵ������б���ȥ�������ֽ����һ�ǽ����ɹ���������
             ȡ�������е�ֱ����Ϣ����DATA REQ��LMM�����ǽ���ʧ�ܣ��������ؽ�����
             ʱ������ʱ����ʱ�������·��������ֽ׶���ʱ�ؽ���һ�μ��ɣ����
             ����ʧ�ܣ������θ��ݻ�����sessionID��transactionID�ҵ���Ӧtransaction��
             ����Ӧ����Դ��գ���ֹ��λ���̡�

             ֱ���������ط����õ�:
             1. �����ɹ�֮������ȥ�����ͻ����б�������ȥȡ��Ӧ����Ϣ���͸�LMM
             2. ��ǰ��·���ڣ�ֱ�����ֱ����Ϣ�����͸�LMM��ͬʱ����������ϢҲ�ŵ�����
             ������ȥ
             �������������ֻҪ���ͳɹ�֮���򽫶�Ӧbuffer��ָ�����ó�NULL�� ���ҷ�
             ��һ���ڲ���Ϣ��transaction��֪ͨ��Ҫ�����ش���ʱ�����������ʧ�ܣ���
             �����ؽ�����ʱ������ʱ����ʱ֮���ٴη��������ص����潨�����߼���ȥ��

 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP

*******************************************************************************/
typedef struct
{
    NAS_LPP_CONN_STATUS_ENUM_UINT32         enConectStatus;                                 /*��ʾ��ǰ������״̬*/
    VOS_UINT32                              ulEstOrDataCnt;                                 /*��������ֱ�����Դ���������ʵ���������ʧ�ܣ����ش�һ��*/
    NAS_LPP_TIMER_STRU                      stLppTimer;                                     /*���ӹ���������running�Ķ�ʱ��*/
}NAS_LPP_CONN_MANAGE_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU
 �ṹ˵��  : ����buffer���ڴ���ѵĽ��
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNum;
    VOS_UINT8                               aucIndex[NAS_LPP_MAX_UP_MSG_PER_TRANSACTION];
}NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_MSG_SEQUENCE_STRU
 �ṹ˵��  : ����buffer�İ��Ⱥ�˳��洢�����ṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8               ucUsedFlag;         /*�Ƿ�ռ��flag*/
    VOS_UINT8               ucUpLinkBuffIndex;  /*���л���buffer������*/
}NAS_LPP_UP_MSG_SEQUENCE_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_MSG_BUFF_POOL_STRU
 �ṹ˵��  : ����buffer���ڴ��
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_MSG_SEQUENCE_STRU            astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT];
    VOS_UINT32                              ulBitMap;
    LPP_UPLINK_MSG_BUF_STRU                 astLppUpMsg[NAS_LPP_MAX_BUFF_MSG_COUNT];
}NAS_LPP_UP_MSG_BUFF_POOL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_LOC_TECH_MAP_STRU
 �ṹ˵��  : ��λ������session���ӳ���ϵ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech;     /*��λ����*/
    VOS_UINT8                               ucSessionIndx;      /*����running�Ķ�λ������Ӧ��sessionIndx*/
    VOS_UINT8                               ucSessionTranIndx;  /*����running�Ķ�λ������Ӧ�������±�*/
    VOS_UINT8                               ucTransIndx;        /*����running�Ķ�λ������Ӧ��transaction�ڴ���е�����*/
}NAS_LPP_LOC_TECH_MAP_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_LOC_TECH_RUNING_STRU
 �ṹ˵��  : ��¼��ǰ����λ���������̵�session transactionID�ȣ�����
             LRRC�ظ�����IND֮����֪������һ��ʵ�巢�������
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNum;
    VOS_UINT8                               aucRsv[3];
    NAS_LPP_LOC_TECH_MAP_STRU               astLocTechMap[NAS_LPP_MAX_POS_TECH];
}NAS_LPP_LOC_TECH_RUNING_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_ECID_MEAS_RESULT_STRU
 �ṹ˵��  : ���ڱ���ECID�Ĳ�����Ϣ
 1.��    ��   : 2015��07��28��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                    bHaveEcidMeasFlag;
    LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU         stLrrcLppEcidMeasResultList;   /*�����ϱ��Ĳ�����Ϣ����*/
    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU           stLastGlobalIdInfo;     /*�ϴβ���ind��Ӧ��GLOID��Ϣ*/
    VOS_UINT16                                  usLastPhyCellId;        /*�ϴβ���ind��Ӧ������С��ID*/
}NAS_LPP_ECID_MEAS_RESULT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OTDOA_MEAS_RESLT_STRU
 �ṹ˵��  : ���ڱ���otdoa�Ĳ�����Ϣ
 1.��    ��   : 2015��07��28��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                        bMeasRsltFlag;

    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:����OTDOA-MeasQuality������Ч��1:����OTDOA-MeasQuality������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasqualityFlag;

    VOS_UINT16                                      usSfn;

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellIdRef;
    VOS_UINT8                                       aucRsv[2];

    VOS_UINT32                                      ulEarfcn;

    VOS_UINT32                                      ulNghbrRptNum;  /*�Ѿ���provide location infor���ϱ���С������*/

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stReferenceMeasQuality;

    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU         stNeighbourMeasurementList;
}NAS_LPP_OTDOA_MEAS_RESLT_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_GNSS_MEAS_RESLT_STRU
 �ṹ˵��  : ���ڱ���GNSS�Ĳ�����Ϣ
 1.��    ��   : 2015��07��28��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitCommonInfo:1;
    VOS_UINT32                                      bitAgnssInfo:1;
    VOS_UINT32                                      bitSpare:30;

    VOS_BOOL                                        bHaveGnssMeasFlag;      /*�Ƿ���GNSS�Ĳ�����Ϣ*/
    MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU        stGnssReqLocationInfo;  /*GNSS�Ĳ�����Ϣ*/
    MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU   stCommonProvideLocInfo; /*��γ�ȹ�����Ϣ*/
}NAS_LPP_GNSS_MEAS_RESLT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_MEAS_RESULT_STRU
 �ṹ˵��  : ���ڱ���ECID��OTDOA��GNSS�Ĳ�����Ϣ
 1.��    ��   : 2015��07��28��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_ECID_MEAS_RESULT_STRU           stEcidMeasRslt;     /*ECID�Ĳ������*/
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           stOtdoaMeasRslt;    /*OTDOA�Ĳ������*/
    NAS_LPP_GNSS_MEAS_RESLT_STRU            stGnssMeasRslt;     /*GNSS�Ĳ������*/
}NAS_LPP_MEAS_RESULT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_MEAS_RESULT_STRU
 �ṹ˵��  : ���ڱ���ECID��OTDOA��GNSS�Ĳ�����Ϣ
 1.��    ��   : 2015��08��03��
   ��    ��   : w00324863
   �޸�����   : Added for LPP
*******************************************************************************/

typedef struct
{

    /* 0:����֧�֣�1:����֧��*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaUeAssistFlag;

    /* 0:����֧�֣�1:����֧�� */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucInterFreqRSTDMeasFlag;

    /* 0:����֧�֣�1:����֧�� */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAddOtdoaNeighbourCellInfoListFlag;

    /*
    usBandNum ȡֵ��Χ[1,256]
    ulBandInd,ÿ��BIT��1:����֧�֣�0����֧�֣�ulBandInd[0]�е�һ��BIT����BAND1,��������;
    */

    VOS_UINT32                                      ulBandNum;
    VOS_UINT32                                      aulBandInd[LRRC_LPP_MAX_BAND_IND_ARRAY_NUM];

}LRRC_CAPABILITY_STRU;
/*******************************************************************************
 �ṹ��    :NAS_LPP_TRANS_INDEX_STRU
 �ṹ˵��  :  һ��transactionʵ���Ӧ��ָ���Լ���Ӧ�ڴ���е��������Լ�
              ��Ӧ�Ĵ洢����ֵ��transaction�������±�
 1.��    ��   : 2015��07��06��
   ��    ��   :
*******************************************************************************/
typedef struct
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    VOS_UINT8                                ucTransIndx;
    VOS_UINT8                                ucSessionTransIndx;
    VOS_UINT8                                aucRsv[2];
}NAS_LPP_TRANS_INDEX_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_MEAS_RESULT_STRU
 �ṹ˵��  : ���ڱ���ECID��OTDOA��GNSS�Ĳ�����Ϣ
 1.��    ��   : 2015��08��03��
   ��    ��   : w00324863
   �޸�����   : Added for LPP
*******************************************************************************/

typedef struct
{

    /*����������Ч���յ�RRC��Ϣʱ��ΪTRUE*/
    VOS_BOOL                        bRrcCapbilityFlag;
    LRRC_CAPABILITY_STRU            stRrcCapbility;
}LRRC_SUPPORT_CAPABILITY_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_ENTITY_STRU
 �ṹ˵��  : LPPʵ������ݽṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP

*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usReTransTimerLen;/*resend msg timer len*/
    VOS_UINT16                          usAttempeTransCnt;/*���ӹ����Լ���*/
    VOS_UINT8                           ucLppLayerSwitch;/*LPP��ά�ɲ��ܿ���*/
    VOS_UINT8                           ucLppLayerNorm;/*LPP��ά�ɲ�normal��Ϣ����*/
    VOS_UINT8                           ucLppLayerInfo;/*LPP��ά�ɲ�info��Ϣ����*/
    VOS_UINT8                           ucLppLayerWarn;/*LPP��ά�ɲ�warn��Ϣ����*/
    VOS_UINT8                           ucLppLayerErr;/*LPP��ά�ɲ�error��Ϣ����*/
    VOS_UINT8                           aucRsv[3];
}NAS_LPP_NV_CONFIG_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OTDOA_ASSIST_CFG_STRU
 �ṹ˵��  : LPP���и��������ṩ����
 1.��    ��   : 2015��08��04��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                        bOtdoaAssistDataFlag;

    /* 0:otdoa ReferenceCellInfo ��Ч��1: otdoa ReferenceCellInfo ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaReferenceCellInfoFlag;

    /* 0:otdoa NeighbourCellInfo ��Ч��1: otdoa NeighbourCellInfo ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaNeighbourCellInfoFlag;

    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU         stOtdoaReferenceCellInfo;

    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU    stOtdoaNeighbourCellInfo;
}NAS_LPP_OTDOA_ASSIST_CFG_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_LOCATION_REQ_STRU
 �ṹ˵��  : LPP����λ����Ϣ����
 1.��    ��   : 2015��08��04��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitOpAgnssLocReq    :1;
    VOS_UINT32                                      bitOpOtdoaLocReq    :1;
    VOS_UINT32                                      bitOpEcidLocReq     :1;
    VOS_UINT32                                      bitOpSpare          :29;

    LPP_AGNSS_REQ_LOCATION_INFO_STRU                stAGNSSReqLocationInfo;
    LPP_OTDOA_REQ_LOCATION_INFO_STRU                stOtdoaReqLocationInfo;
    LPP_ECID_REQ_LOCATION_INFO_STRU                 stEcidReqLocationInfo;
}NAS_LPP_LOCATION_REQ_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_COMM_CONFIG_INFO_STRU
 �ṹ˵��  :request location information�Ĺ������ò���
 1.��    ��   : 2015��08��04��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
   VOS_UINT32                                   bitOpQos                        :1;
   VOS_UINT32                                   bitOpLocationCoordinateType     :1;
   VOS_UINT32                                   bitOPVelocityTypes              :1;
   VOS_UINT32                                   bitOpSpare                      :29;

    /*��Ӧ��session��transaction�Ķ�Ӧ��ϵ*/
    VOS_UINT8                                   ucSessionIndex;
    VOS_UINT8                                   ucSessionTransIndex;

    /*�ϱ�location information��*/
    LPP_LOCATION_INFO_TYPE_ENUM_UINT8           enLocationInformationType;

    /*�Ƿ��ϱ�addtional*/
    LPP_ADDITON_REPORT_ENUM_UNIT8               enAdditonInfo;

    /* �������� */
    LPP_ENVIRONMENT_ENUM_UINT8                  enEnvironment;

    VOS_UINT8                                   ascRsv[3];

    /*�ϱ�׼��*/
    NAS_LPP_REPORT_CRITERIA_STRU                stReportCriteria;

    /* Qos: �����stResponseTime�����Ѿ���report criteria������洢������ֻ�Ǵ�һ�£���ʹ�á�*/
    LPP_MTA_COMMON_QOS_STRU                     stQos;

    /* ֻ��GNSS�� */
    LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU stLocationCoordinateType;

    /* ֻ��GNSS�� */
    LPP_MTA_COMMON_VELOCITY_TYPE_STRU           stVeloctytype;
}NAS_LPP_COMM_CONFIG_INFO_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_ENTITY_STRU
 �ṹ˵��  : LPPʵ������ݽṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitmap;
    NAS_LPP_COMM_CONFIG_INFO_STRU       astLppCommCfgInfo[NAS_LPP_MAX_POS_TECH];
}NAS_LPP_COMM_CONFIG_INFO_POOL_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_SERVING_CELL_STRU
 �ṹ˵��  : LPPʵ������ݽṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitCELLIDChng:1;/* ��¼CELL ID CHANGE */
    VOS_UINT32                          bitOpspare:31;
    VOS_UINT32                          ulEarfcn;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulCellIdentity;

     /* PLMN ID��տڱ���һ�� */
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;

}NAS_LPP_SERVING_CELL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_CONFIG_PARA_STRU
 �ṹ˵��  : LPP���ò������ݽṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : xiaojun
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOtdoaAssisChng   :1;
    VOS_UINT32                          bitGnssAssisChng    :1;
    VOS_UINT32                          bitEcidReq          :1; /*��¼��ǰ��Location request���Ƿ�Я����ecid ������*/
    VOS_UINT32                          bitOtdoaReq         :1; /*��¼��ǰ��Location request���Ƿ�Я����otdoa ������*/
    VOS_UINT32                          bitGnssReq          :1; /*��¼��ǰ��Location request���Ƿ�Я����gnss ������*/
    VOS_UINT32                          bitSpare            :27;

    /*REQUEST LOCATION INFOR��Я����common���ò����������ܶ�Ӧ3��request location information�·���*/
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  stCommCfgInfoPool;

    /*OTDOA�ĸ������ݲ���*/
    NAS_LPP_OTDOA_ASSIST_CFG_STRU       stOtdoaAssisCfg;

    /*GNSS�ĸ������ݲ���*/
    /*NAS_LPP_GNSS_ASSIS_DATA_STRU        stGnssAssisData;*/

    /*REQUEST LOCATION INFOR ������ݲ���*/
    NAS_LPP_LOCATION_REQ_STRU           stLocationReq;

    NAS_LPP_SERVING_CELL_STRU           stServingCell;
}NAS_LPP_CONFIG_PARA_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_GNSS_TIMER_STRU
 �ṹ˵��  : LPP gnss timer struct
 1.��    ��   : 2015��10��22��
   ��    ��   : w00324863
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    /* ��ȡGNSS CAP���� */
    VOS_UINT8                               ucSendMtaGnssCapCnt;
    VOS_UINT8                               aucRsv[3];
    /* GNSS CAP ��ȡ�ɹ���־λ */
    VOS_BOOL                                bGnssCapbilityFlag;
    /* GNSS������Ϣ */
    MTA_LPP_AGNSS_PROVIDE_CAP_STRU          stMtaLppGnssCap;
    /* �ȴ�GNSS CAP CNF ��ʱ�� */
    NAS_LPP_TIMER_STRU                      stLppWaitForGnssCapCnfTimer;    /* �ȴ�MTA�ظ�GNSS CAP�Ķ�ʱ�� */
    NAS_LPP_TIMER_STRU                      stLppGnssLocInfoInvalidTimer;    /* λ����Ϣ��Ч��ʱ�� */
}NAS_LPP_GNSS_DATA_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_REPORT_CRITERIA_STRU
 �ṹ˵��  : lpp�ϱ�λ����Ϣ�ķ�ʽ
 1.��    ��   : 2015��07��06��
   ��    ��   : W00324863
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enType;
    VOS_UINT8                                   ucRsv[3];

    union
    {
        NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU   stReportTrigger;
        NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU    stReportPeriod;
        NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU      stReportOnce;
    }u;
}NAS_LPP_UP_REPORT_CRITERIA_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_ECID_INFO_STRU
 �ṹ˵��  : LPP �û���ECID��ʵ��ṹ
 1.��    ��   : 2015��11��18��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqPosTechType;   /*��ʾMTA������嶨λ��������*/
    VOS_UINT8                                   aucRsv[3];
    NAS_LPP_ECID_MEAS_RESULT_STRU               stEcidMeasRslt;      /*ECID�Ĳ������*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU             stReportCriteria;    /*�ϱ�׼��*/
    NAS_LPP_TIMER_STRU                          stLppUpStateTimer;   /*ECID������ʹ�õ���״̬��ʱ��*/
    NAS_LPP_UP_STATE_ENUM_UINT32                enLppUpState;        /*��ʾECID�ĵ�ǰ״̬*/
    MTA_LPP_REQ_MEASUREMENT_STRU                stRequestedMeasurements; /*��ʾ����ECID�Ĳ���������*/
}NAS_LPP_UP_ECID_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_UP_OTDOA_INFO_STRU
 �ṹ˵��  : LPP �û���OTDOA�����ݽṹ
 1.��    ��   : 2015��11��18��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqPosTechType;   /*��ʾMTA������嶨λ��������*/
    VOS_UINT8                                   aucRsv[3];
    NAS_LPP_OTDOA_MEAS_RESLT_STRU               stOtdoaMeasRslt;     /*OTDOA�Ĳ������*/
    NAS_LPP_OTDOA_ASSIST_CFG_STRU               stOtdoaAssisCfg;     /*OTDOA�ĸ������ݲ���*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU             stReportCriteria;    /*�ϱ�׼��*/
    NAS_LPP_TIMER_STRU                          stLppUpStateTimer;   /*OTDOA������ʹ�õ���״̬��ʱ��*/
    NAS_LPP_UP_STATE_ENUM_UINT32                enLppUpState;        /*��ʾOTDOA�ĵ�ǰ״̬*/
}NAS_LPP_UP_OTDOA_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_USER_PLANE_ENTITY_STRU
 �ṹ˵��  : LPP �û����ʵ����Ϣ
 1.��    ��   : 2015��11��18��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                bReqEcidAndOtdoaFlag; /*��ʶͬʱ������ECID&OTDOA�Ĳ�������*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU         stReportCriteria;     /*ͬʱ����ECID&OTDOAά�����ϱ�׼��*/
}NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_USER_PLANE_ENTITY_STRU
 �ṹ˵��  : LPP �û����ʵ����Ϣ
 1.��    ��   : 2015��11��18��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU     stMultiPosTechEntity; /*ͬʱ����ECID&OTDOA��˽����Ϣ*/
    NAS_LPP_UP_ECID_INFO_STRU               stEcidUpEntity;     /*�û���ECID��ʵ����Ϣ*/
    NAS_LPP_UP_OTDOA_INFO_STRU              stOtdoaUpEntity;    /*�û���OTDOA��ʵ����Ϣ*/
}NAS_LPP_USER_PLANE_ENTITY_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_ENTITY_STRU
 �ṹ˵��  : LPPʵ������ݽṹ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                ucTransNum;             /*��ǰʹ�õ���UE������transaction��transaction Number�����ֵ������෢���transaction��SMLCά��*/
    VOS_UINT8                                ucUpSequenceNumMax;     /*��ǰʹ������LPP��ϢsequenceNum�����ֵ�� ����LPP��ϢsequenceNum��SMLCά��*/
    VOS_UINT8                                aucRsv[2];

    VOS_UINT32                               ulInvalidLen;
    NAS_LPP_SESSION_ENTITY_POOL_STRU         stSessionEntityPool;    /*LPP�ĻỰʵ��*/
    NAS_LPP_NV_CONFIG_STRU                   stLppNvConfig;          /*LPP�漰����NV��*/
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU     stTransEntityPool;      /*TRANSACTIONʵ�����Դ�أ����е�sessionʵ�����������transaction��Ԫ*/
    LRRC_SUPPORT_CAPABILITY_STRU             stLrrcSupCapability;    /*����LRRC�ϱ���LCS��λ���������*/
    NAS_LPP_LOC_TECH_RUNING_STRU             stRuningLocTech;        /*���ڼ�¼��ǰ����running�Ķ�λ��������һ��ʵ�������У�����LRRC�ظ�����cnf������IND֮���ʵ������*/
    NAS_LPP_MEAS_RESULT_STRU                 stMeasResult;           /*�������ind��Ϣ*/
    NAS_LPP_CONN_MANAGE_STRU                 stLppConnManage;        /*LPP���ӹ���ģ������Ҫ��������Ϣ*/
    NAS_LPP_UP_MSG_BUFF_POOL_STRU            stUpMsgBuffPool;        /*������Ϣ�Ĺ����ڴ��*/
    NAS_LPP_CONFIG_PARA_STRU                 stLppConfig;            /*�洢���ò���:request location information��assistant data����*/
    NAS_LPP_GNSS_DATA_STRU                   stStructDataForGnss;    /*gnss data */
    NAS_LPP_USER_PLANE_ENTITY_STRU           stUserPlaneEntity;      /*�û���ʵ��*/
} NAS_LPP_ENTITY_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_MSG
 �ṹ˵��  : LPP��Ϣ
 1.��    ��   : 2015��07��06��
   ��    ��   : l00253982
   �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/

    VOS_UINT8                           ucRsv[4];
}NAS_LPP_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_LPP_ENTITY_STRU     g_stNasLppEntity;
extern NAS_LPP_SUB_STATE_TIME_STRU g_astLppSubStateTime[LPP_SS_BUTT];
extern NAS_LPP_FSM_STRU  g_astNasLppFsm[];
extern LPP_MESSAGE_STRU        stLppMsgBuff;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_INT32   NAS_COMM_PrinLrrcLppMsg
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                               usOffset,
           const PS_MSG_HEADER_STRU                *pstMsg
       );
extern VOS_INT32   NAS_COMM_PrintMmLppMsg
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                               usOffset,
           const PS_MSG_HEADER_STRU                *pstMsg
       );
extern VOS_VOID  NAS_LPP_AddRunningPositionTech
       (
           NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech,
           VOS_UINT8                               ucSessionIndx,
           VOS_UINT8                               ucSessionTransIndx,
           VOS_UINT8                               ucTransIndx
       );
extern VOS_UINT32 NAS_LPP_AddTransEntityToSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity ,VOS_UINT8 ucIndex,VOS_UINT8 *pucSessionTransIndex);
extern VOS_UINT8 NAS_LPP_ApplyTransNum( VOS_VOID );
extern VOS_VOID  NAS_LPP_BuffFsmMsg
       (
           PS_MSG_HEADER_STRU                         *pstMsg,
           VOS_UINT32                                  ulSize,
           VOS_UINT8                                   ucTransIndex,
           NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority
       );
extern VOS_VOID NAS_LPP_ChangeTransFsmState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndx,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enLppMainState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
       );
extern VOS_UINT8  NAS_LPP_GetLppLayerSwitchFlag(VOS_VOID);
extern VOS_VOID  NAS_LPP_ClearLppMsgBuff( VOS_VOID );
extern VOS_VOID  NAS_LPP_ClearLppTransCnt(VOS_VOID);
extern VOS_VOID  NAS_LPP_DeleteRunningPositionTech(  NAS_LPP_POSITION_TECH_ENUM_UINT8 enPositionTech );
extern VOS_VOID  NAS_LPP_DelTransEntityFromSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity, VOS_UINT8 ucSessionTransIndx );
extern LPP_UPLINK_MSG_BUF_STRU* NAS_LPP_FindUpLinkBuffer
       (
           VOS_UINT8                           ucSequenceNum,
           VOS_UINT32                          ulSessionId
       );
extern NAS_LPP_FSM_STRU * NAS_LPP_FsmFind(NAS_LPP_MAIN_STATE_ENUM_UINT32 enLppMainState, NAS_LPP_SUB_STATE_ENUM_UINT32 enLppSubState);
extern VOS_VOID NAS_LPP_FsmInit( VOS_VOID );
extern VOS_INT32 NAS_LPP_FsmStaCompare( const VOS_VOID *arg1, const VOS_VOID *arg2 );
extern NAS_LPP_CONFIG_PARA_STRU *NAS_LPP_GetCfgPara( VOS_VOID );
extern NAS_LPP_COMM_CONFIG_INFO_STRU *NAS_LPP_GetCommCfgInfoElementByIndex( VOS_UINT8 ucIndex);
extern NAS_LPP_COMM_CONFIG_INFO_POOL_STRU *NAS_LPP_GetCommCfgInfoPool( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetConnManageTimer( VOS_VOID );
extern LPP_REQUEST_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetDownLinkCapReqIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern LPP_REQ_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetDownLinkLocationReqIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern VOS_UINT16 NAS_LPP_GetDownLinkMsgSequenceNum
       (
           VOS_UINT8               ucSessionIndx
       );
extern VOS_UINT32 NAS_LPP_GetDownlinkMsgType
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetDurationTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidMeasRsltAddr( VOS_VOID );
extern NAS_LPP_MEAS_RESULT_STRU*  NAS_LPP_GetMeasRsltAddr( VOS_VOID );
extern VOS_UINT8  NAS_LPP_GetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx );
extern LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU*  NAS_LPP_GetLastTriggerCellGloId( VOS_VOID );
extern NAS_LPP_LOCATION_REQ_STRU  *NAS_LPP_GetLocationReqBuff( VOS_VOID );
extern NAS_LPP_CONN_STATUS_ENUM_UINT32  NAS_LPP_GetLppConnStatus( VOS_VOID );
extern NAS_LPP_ENTITY_STRU*  NAS_LPP_GetLppEntityCtx( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetLppIntraDataCnfTimerLen(VOS_VOID);
extern VOS_UINT32  NAS_LPP_GetLppMainState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndx
       );
extern LPP_MESSAGE_STRU*  NAS_LPP_GetLppMsgBuff( VOS_VOID );
extern NAS_LPP_NV_CONFIG_STRU*  NAS_LPP_GetLppNvParaConfig(VOS_VOID);
extern NAS_LPP_SESSION_ENTITY_POOL_STRU* NAS_LPP_GetLppSessionEntityPool( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetLppSubState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetLppTransAttepCnt(VOS_VOID);
extern NAS_LPP_TRANSACTION_ENTITY_POOL_STRU * NAS_LPP_GetLppTransEntityPool( VOS_VOID );
extern NAS_LPP_UP_MSG_BUFF_POOL_STRU * NAS_LPP_GetLppUpMsgBuffPool( VOS_VOID );
extern LRRC_SUPPORT_CAPABILITY_STRU *NAS_LPP_GetLrrcCap( VOS_VOID );
extern VOS_UINT8  NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag(VOS_VOID);
extern NAS_LPP_OTDOA_ASSIST_CFG_STRU *NAS_LPP_GetOtdoaAssisCfg( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetPeriodTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern VOS_UINT32  NAS_LPP_GetPositionTechEcid(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPositionTechGnss(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPositionTechOtdoa(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPrtclTimeLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetResPonseTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern NAS_LPP_LOC_TECH_RUNING_STRU  *NAS_LPP_GetRuningLocTech( VOS_VOID );
extern NAS_LPP_SERVING_CELL_STRU *NAS_LPP_GetServingCell( VOS_VOID );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * NAS_LPP_GetSessionElementByIndex(VOS_UINT8 ucIndex);
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_GetSessionEntity
       (
           VOS_UINT32                          ulSessionIndex
       );
extern VOS_UINT8  NAS_LPP_GetSessionEntityReportType
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetSessionIdBySessionIndx
       (
           VOS_UINT8                           ucSessionIndx
       );
extern NAS_LPP_TIMER_PARA_ENUM_UINT8  NAS_LPP_GetTimeNameBySubState
       (
           NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetTimer
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndx,
           NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_LPP_GetTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
       );
extern NAS_LPP_TIMER_PROC_FUNC  NAS_LPP_GetTimerProcFun( NAS_LPP_TIMER_PARA_ENUM_UINT8 enTimeName );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetTransactionTimer
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndx
       );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_GetTransElementByIndex(VOS_UINT8 ucIndex);
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU  *NAS_LPP_GetTransEntity
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndex
       );
extern VOS_UINT8  NAS_LPP_GetTransIdIndex
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetTransLppMsgCnt( VOS_VOID );
extern NAS_LPP_MSG_IDENTITY_STRU* NAS_LPP_GetUpLinkMsgIndetity
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern LPP_PROVIDE_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideCapIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideLocIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkSequenceNumber
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkSessionId
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkTransactionNumber
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT8 NAS_LPP_GetUpMsgSequenceNum( VOS_VOID );
extern NAS_LPP_SUB_STATE_ENUM_UINT32  NAS_LPP_GetWaitAckSubState
       (
           NAS_LPP_AIR_MSG_ENUM_UINT32         ulUpLppMsgId,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enMainState
       );
extern VOS_VOID NAS_LPP_InitRunningLocTech( VOS_VOID );
extern VOS_UINT32  NAS_LPP_IsTimerNameValid
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ucSessionTransIndx,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_LPP_LppCtxInit( VOS_VOID );
extern VOS_VOID  NAS_LPP_LppPlmn2NasPlmn
       (
           LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId,
           VOS_UINT8                           *pucNasPlmnId
       );
extern VOS_UINT8  NAS_LPP_MallocCommCfgInfoElementIndex( VOS_UINT8 ucTransIndex );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU* NAS_LPP_MallocSessionEntity( VOS_UINT32  ulSessionId );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_MallocTransEntity
       (
           LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
       );
extern VOS_UINT8 NAS_LPP_MallocTransEntityIndx
       (
           LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
       );
LPP_UPLINK_MSG_BUF_STRU  *NAS_LPP_MallocUpMsgBuffer(VOS_UINT8 *pucUplinkBuffIndx);
extern VOS_VOID  NAS_LPP_ModifyPrtclTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           VOS_UINT32                          ulTimerLen
       );
extern VOS_VOID  NAS_LPP_ModifyTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           VOS_UINT32                          ulTimerLen
       );
extern VOS_UINT32 NAS_LPP_MsgDuplicateDetect( VOS_UINT32 ulSessionId, VOS_UINT8 ucNewMsgSequenecNum );
extern VOS_VOID  NAS_LPP_NasPlmn2LppPlmn
       (
           VOS_UINT8                           *pucNasPlmnId,
           LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId
       );
extern VOS_UINT32  NAS_LPP_PopFsmMsg
       (
           VOS_UINT8                                   ucTransIndex,
           NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority );
extern VOS_VOID NAS_LPP_PrintLppRevMsg
       (
           const PS_MSG_HEADER_STRU           *pstMsg,
           VOS_CHAR                           *pcBuff
       );
extern VOS_VOID NAS_LPP_PrintLppSendMsg
       (
           const PS_MSG_HEADER_STRU           *pstMsg,
           VOS_CHAR                           *pcBuff
       );
extern VOS_VOID  NAS_LPP_ReadLppNvConfig( VOS_VOID);
extern VOS_VOID NAS_LPP_ReInitTransEntity
       (
           VOS_UINT8       ucTransIndex,
           VOS_UINT8       ucSessionIndx,
           VOS_UINT8       ucSessionTransIndx
       );
extern VOS_VOID  NAS_LPP_RelAllTransEntity( VOS_VOID );
extern VOS_VOID  NAS_LPP_ReleaseAllSession( VOS_VOID );
extern VOS_VOID  NAS_LPP_ReleaseCommCfgInfoElementByIndex( VOS_UINT8 ucTransIndex, VOS_UINT8 ucIndex);
extern VOS_VOID  NAS_LPP_ReleasePosTechMeas
(
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPosTech
);
extern VOS_VOID NAS_LPP_ReleaseSessionEntity(VOS_UINT32 ulSessionId);
extern VOS_VOID  NAS_LPP_ReleaseSessionEntityByIndex( VOS_UINT8 ucSessionIndx );
extern VOS_VOID  NAS_LPP_ReleaseTransEntity( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID  NAS_LPP_ReleaseTransEntityAction
       (
           VOS_UINT8                               ucSessionIndx,
           VOS_UINT8                               ucSessionTransIndx
       );
extern VOS_VOID  NAS_LPP_ReleaseTransEntityByIndx(VOS_UINT8 ucSessionIndx ,VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID NAS_LPP_ReleaseTransEntityElementOnly( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID NAS_LPP_RelUpMsgBuffer( LPP_UPLINK_MSG_BUF_STRU **ppstLppUpMsgBuf );
extern VOS_VOID NAS_LPP_RelUpMsgBufferByIndex( VOS_UINT8 ucIndex );
extern VOS_VOID  NAS_LPP_ReturnTransEntityToPool( VOS_UINT8 ucTransIndex );
extern NAS_LPP_LOC_TECH_MAP_STRU*  NAS_LPP_SearchRunningPositionTech
       (
           NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechByIndx2
       (
           VOS_UINT8 ucSessionIndx,
           VOS_UINT8 ucSessionTranIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechBySessionIndx
       (
           VOS_UINT8 ucSessionIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechByTransIndx
       (
           VOS_UINT8 ucTransIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_SearchSessionElement( VOS_UINT32 ulSessionId );
extern VOS_UINT8 NAS_LPP_SearchSessionIndx( VOS_UINT32 ulSessionId );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU * NAS_LPP_SearchTransEntity
       (
           VOS_UINT32                          ulSessionId,
           NAS_LPP_TRANS_ID_STRU               *pstTransId,
           VOS_UINT8                           *pucSessionTransIndx
       );
extern VOS_VOID NAS_LPP_SearchTransEntityIndx(
           VOS_UINT8                       ucSessionIndx,
           NAS_LPP_TRANS_ID_STRU          *pstTransId,
           VOS_UINT8                      *pucTransIndx,
           VOS_UINT8                      *pucSessionTransIndx );
extern LPP_UPLINK_MSG_BUF_STRU*   NAS_LPP_SearchUpMsgBuff
       (
           VOS_UINT32             ulSessionId,
           NAS_LPP_TRANS_ID_STRU *pstTransId
       );
extern VOS_VOID NAS_LPP_SearchUpMsgBuffByTrnasId
       (
           NAS_LPP_TRANS_ID_STRU                *pstTransId,
           NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU *pstSearchRslt
       );
extern VOS_VOID  NAS_LPP_SessionEntityReInit( VOS_UINT8 ucSessionIndx );
extern VOS_VOID NAS_LPP_SetDownLinkMsgSequenceNum
       (
           VOS_UINT8               ucSessionIndx,
           VOS_UINT8               ucSequenceNumber
       );
extern VOS_VOID  NAS_LPP_SetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,PS_BOOL_ENUM_UINT8 enTransEndFlg);
extern VOS_VOID  NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ENUM_UINT32 enConnStatus);
extern VOS_VOID  NAS_LPP_TimerReg
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           NAS_LPP_TIMER_PROC_FUNC             fFun,
           VOS_UINT32                          ulTimerLen

       );
extern VOS_VOID NAS_LPP_TimerStart
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ucSessionTransIndx,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_LPP_TimerStop
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_LPP_TransFsmCheck
(
    NAS_LPP_MAIN_STATE_ENUM_UINT32  enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32   enLppSubState,
    PS_MSG_HEADER_STRU             *pstMsg
);
extern VOS_VOID  NAS_LPP_TransLppMsgAddCnt(VOS_VOID);
extern VOS_VOID  NAS_LPP_CreatNewTrans
(
    VOS_UINT8       ucSessionIndx ,
    VOS_UINT8      *pucSessionTransIndx,
    VOS_UINT8      *pucTransIndex
);
extern NAS_LPP_GNSS_DATA_STRU *NAS_LPP_GetGnssData( VOS_VOID );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInCapState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInAssistState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInLocState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_VOID  NAS_LPP_SetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech,
    VOS_UINT32                          ulFlag
);
extern VOS_UINT32  NAS_LPP_GetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
);
extern VOS_BOOL NAS_LPP_IsThereOtherTransactionRunningInSession
(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
);
extern VOS_UINT16  NAS_LPP_GetLastTriggerLastPhyCellId( VOS_VOID );
extern VOS_VOID  NAS_LPP_SetLastTriggerLastPhyCellId(VOS_UINT16 usPhyCellId);
extern VOS_BOOL  NAS_LPP_IsOtdoaAssistDataChng( VOS_VOID );
extern VOS_BOOL  NAS_LPP_IsGnssAssistDataChng( VOS_VOID );
extern VOS_VOID  NAS_LPP_AbortAndErrorProcess
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_TRANS_ID_STRU              *pstTransId
);
extern VOS_VOID  NAS_LPP_StopTechLocForLackOfAssistData( VOS_VOID );
extern NAS_LPP_GNSS_MEAS_RESLT_STRU*  NAS_LPP_GetGnssMeasRsltAddr( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpResponseTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpPeriodicalTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpDurationTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpStateTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern VOS_UINT32  NAS_LPP_GetUpPrtcTimeLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern VOS_VOID   NAS_LPP_RcvMtaLppUpCapReq
(
    MTA_LPP_UP_CAPABILITY_REQ_STRU          *pstMtaLppUpCapREq
);
extern VOS_VOID  NAS_LPP_UPClrOtdoaCtx( VOS_VOID );
extern VOS_VOID  NAS_LPP_UPClrEcidCtx(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetEcidLrrcMeasFlag(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetOtodaLrrcMeasFlag(VOS_VOID);
extern VOS_VOID  NAS_LPP_UPClrEntity( VOS_VOID );
extern VOS_VOID NAS_LPP_UpTimerStart
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern VOS_UINT32  NAS_LPP_GetEcidPeriodReportCnt( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetEcidPeriodReportingCnt( VOS_VOID );
extern VOS_VOID  NAS_LPP_EcidPeriodReportingCntAddOne( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetOtodaPeriodReportCnt( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetOtodaPeriodReportingCnt( VOS_VOID );
extern VOS_VOID  NAS_LPP_LppUpEntityInit( VOS_VOID );
extern VOS_VOID  NAS_LPP_OmMtaLocInfoReq
(
    LPP_MTA_MSG_TYPE_ENUM_UINT32        enGnssAssistData
);
extern VOS_VOID  NAS_LPP_OmMtaAssistData
(
    LPP_MTA_MSG_TYPE_ENUM_UINT32        enGnssAssistData
);
extern VOS_VOID NAS_LPP_UpTimerStop
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern NAS_LPP_UP_OTDOA_INFO_STRU*  NAS_LPP_GetLppUpOtdoaCtx( VOS_VOID );
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosReqTechType(VOS_VOID);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosReqTechType(VOS_VOID);
extern VOS_VOID NAS_LPP_UpChangeTransFsmState
(
    NAS_LPP_UP_STATE_ENUM_UINT32            enLppUpState,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern NAS_LPP_UP_ECID_INFO_STRU*  NAS_LPP_GetLppUpEcidCtx( VOS_VOID );
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_EcidReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_OtdoaReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_MultiPosTechReportTypeAddr(VOS_VOID);
extern VOS_VOID  NAS_LPP_SetEcidAndOtdoaMeasFlag(VOS_BOOL bReqEcidAndOtdoaFlag);
extern VOS_VOID  NAS_LPP_SetEcidPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enEcidPosType
);
extern VOS_VOID  NAS_LPP_SetOtdoaPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enOtodaPosType
);
extern VOS_VOID  NAS_LPP_SetEcidPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_VOID  NAS_LPP_SetOtdoaPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_BOOL  NAS_LPP_GetEcidAndOtdoaMeasFlag(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetOtdoaAssistDataFlag( VOS_VOID );
extern VOS_VOID  NAS_LPP_SaveSlotNumOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID   NAS_LPP_SaveOtdoaNghbrCell
(
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosType( VOS_VOID );
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosType( VOS_VOID );
extern VOS_VOID NAS_LPP_PrePareGloIdPara
(
    LPP_MEAS_RESULT_ELEMENT_STRU            *pstMeasRsltEle,
    LRRC_LPP_ECID_MEAS_RESULT_STRU          *pstLrrcLppMeasRslt
);
extern NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidLrrcMeasAddr(VOS_VOID);
extern VOS_UINT8  NAS_LPP_GetEcidReqMeasType(VOS_VOID);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetNeighberMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo,
    VOS_UINT32                               ulLoop
);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetPrimaryMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
);
extern LRRC_LPP_ECID_MEAS_RESULT_STRU* NAS_LPP_GetLrrcEcidMeasRslt
(
    NAS_LPP_ECID_MEAS_RESULT_STRU         *pstEcidMeasRslt,
    VOS_UINT32                             ulLoop
);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetPrimaryMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
);
extern NAS_LPP_OTDOA_MEAS_RESLT_STRU*  NAS_LPP_GetOtodaLrrcMeasAddr(VOS_VOID);
extern VOS_VOID  NAS_LPP_PrePareOtdoaSignalMeasInfo
(
    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU         *pstOtdoaSignalMeasInfo,
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           *pstOtdoaMeasRslt
);
extern VOS_VOID   NAS_LPP_RcvMtaLppUpMeasNotify
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
);
extern VOS_VOID   NAS_LPP_UpRcvMtaOtdoaAssistData
(
    MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY_STRU                  *pstMtaLppUpOtdoaAssistData
);
extern VOS_VOID NAS_LPP_RcvMtaLppUpAbortMeas
(
    MTA_LPP_UP_MEAS_ABORT_NTY_STRU     *pstLppUpMeasAbort
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32 enEcidErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaOtdoaMeasmentInd
(
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaMeasInd
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqTechType

);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasAndOtodaErrInd
(
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause
);
extern VOS_VOID NAS_LPP_LppInitExceptCap( VOS_VOID );
extern NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU*  NAS_LPP_GetLppUpMultiPosTechCtx( VOS_VOID );

extern VOS_INT32 NAS_LPP_SecuMemCpy
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











































