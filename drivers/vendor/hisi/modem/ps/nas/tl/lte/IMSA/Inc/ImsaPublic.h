/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaPublic.h
    Description : ImsaPublic.cͷ�ļ�
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAPUBLIC_H__
#define __IMSAPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "PsCommonDef.h"
#include "LPSCommon.h"
#include "ImsaEntity.h"
#include "LPsOm.h"
#include "ImsaImsEvent.h"
#include "ImsParm.h"
#include "ImsaLrrcInterface.h"
#include "NasFileId.h"
#include "UsimPsInterface.h"


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
#define IMSA_NULL                       (0)
#define IMSA_SUCC                       (0)
#define IMSA_FAIL                       (1)
#define IMSA_OP_FALSE                   (0)
#define IMSA_OP_TRUE                    (1)
#define IMSA_TRUE                       (1)
#define IMSA_FALSE                      (0)
#define IMSA_CLIENT_ID                  (0x66)

#define IMSA_PRINT_BUFF_LEN             (3096)              /* 1024ÿ�δ�ӡԤ�軺�� */
extern VOS_CHAR                         g_acImsaPrintBuf[IMSA_PRINT_BUFF_LEN];
#define IMSA_GET_IMSA_PRINT_BUF()       (g_acImsaPrintBuf)

#define IMSA_Min(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX2) : (ulX1))
#define IMSA_Max(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX1) : (ulX2))

#define IMSA_MOVEMENT_8                 (8)
#define IMSA_MOVEMENT_16                (16)
#define IMSA_MOVEMENT_24                (24)

#define IMSA_MSG_NOT_PROC               (0)
#define IMSA_MSG_PROCED                 (1)
#define IMSA_NV_INFO_LEN                (4)

#define IMSA_TIMER_1_TICK_10_MS         (10)            /* 1 tickΪ10ms */

#define IMSA_AUTH_TYPE_AKA               (0)
#define IMSA_AUTH_TYPE_DIGIST            (1)
#define IMSA_AUTH_TYPE_AKA_IPSEC         (2)

#define IMSA_USIM_MAX_OPID              (0x7F)

#define IMSA_HANDLED                    (0)
#define IMSA_NOT_HANDLED                (1)

#define IMSA_CONN_TIMER_THRESHOLD       (200)   /* ��λms */
#define IMSA_REG_TIMER_THRESHOLD        (1500)  /* ��λms */

#ifdef PS_ITT_PC_TEST
#define IMSA_INFO_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define IMSA_INFO_LOG1(String, Para1) \
                 (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define IMSA_NORM_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define IMSA_NORM_LOG1(String, Para1) \
                 (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#define IMSA_WARN_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define IMSA_WARN_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1 )
 */
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1, (long)Para2)
 */
#define IMSA_ERR_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define IMSA_ERR_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String, (long)Para1 )
 */

#else
/*��ӡת����*/
#if (!defined(_lint) && (PRINT_SWITCH == PRINT_OFF) && (VOS_WIN32 != VOS_OS_VER))
#define IMSA_INFO_LOG(String)
#define IMSA_INFO_LOG1(String, Para1)
#define IMSA_INFO_LOG2(String, Para1, Para2)
#define IMSA_NORM_LOG(String)
#define IMSA_NORM_LOG1(String, Para1)
#define IMSA_NORM_LOG2(String, Para1, Para2)
#define IMSA_WARN_LOG(String)
#define IMSA_WARN_LOG1(String, Para1)
#define IMSA_WARN_LOG2(String, Para1, Para2)
#define IMSA_ERR_LOG(String)
#define IMSA_ERR_LOG1(String, Para1)
#else
#define IMSA_INFO_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String)
#define IMSA_INFO_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define IMSA_NORM_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define IMSA_NORM_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define IMSA_WARN_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String)
#define IMSA_WARN_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1 )
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2)
#define IMSA_ERR_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String)
#define IMSA_ERR_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String, (long)Para1 )

#endif
#endif

/* �ڴ濽���궨�� */

#if (VOS_OS_VER == VOS_WIN32)

#define IMSA_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
	NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define IMSA_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
	NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define IMSA_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
	NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define IMSA_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)IMSA_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define IMSA_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_SET_S((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define IMSA_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))
#endif


#define IMSA_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define IMSA_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_IMSA) , (ulLen))

#define IMSA_FREE_MSG(pMsg) \
            PS_FREE_MSG( PS_PID_IMSA, pMsg )

extern VOS_VOID IMSA_Send_Msg(VOS_VOID* pMsg);

/* ������Ϣ */
#define IMSA_SND_MSG(pMsg)\
            IMSA_Send_Msg(pMsg)

extern VOS_VOID IMSA_Send_Msg_Normally(VOS_VOID* pMsg);

#define IMSA_SND_MSG_NORMALLY(pMsg)\
            IMSA_Send_Msg_Normally(pMsg)


extern VOS_VOID IMSA_Send_Intra_Msg(VOS_VOID* pIntraMsg);

#define IMSA_SEND_INTRA_MSG(pIntraMsg)\
            IMSA_Send_Intra_Msg(pIntraMsg)

/*�ڴ��ͷ�*/
#define IMSA_MEM_FREE(pAddr)  PS_MEM_FREE(PS_PID_IMSA, pAddr)

/*�ڴ涯̬����*/
#define IMSA_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_IMSA) , (ulSize))


#define IMSA_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)

#define IMSA_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define IMSA_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

#define IMSA_GET_MSG_ENTITY_BY_NAME(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgName))

/*��װдSPM��Ϣͷ�ĺ�*/
#define IMSA_WRITE_SPM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

/*��װдMMA��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MSCC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_MSCC;

/*��װдIMSA�ڲ���Ϣͷ�ĺ�*/
#define IMSA_WRITE_INTRA_MSG_HEAD(pstMsg, ulMsgID, ulLen)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;\
                    (pstMsg)->ulLength          = (ulLen - VOS_MSG_HEAD_LENGTH);

/*��װдCDS��Ϣͷ�ĺ�*/
#define IMSA_WRITE_CDS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_CDS;

/* ��װдRRM��Ϣͷ�ĺ� */
#define IMSA_WRITE_RRM_MSG_HEAD(pstMsg, ulMsgID,ulLen)\
                    (pstMsg)->stMsgHeader.ulMsgName         = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid     = UEPS_PID_RRM;\
                    (pstMsg)->stMsgHeader.ulLength          = (ulLen - VOS_MSG_HEAD_LENGTH);


/*��װдVC��Ϣͷ�ĺ�*/
#define IMSA_WRITE_VC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_VC;

/*��װдIMS��Ϣͷ�ĺ�*/
#define IMSA_WRITE_IMS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSVA;

/*��װD2дIMSA��Ϣͷ�ĺ�*/
#define IMSA_WRITE_IMSA_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSVA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;

/*��װдMSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_TAF;

/*��װдAT MSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_AT_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_AT;

/*��װдSPM��Ϣͷ�ĺ�*/
#define IMSA_WRITE_CALL_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

#define IMSA_WRITE_RNIC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ACPU_PID_RNIC;


/*��װдLRRC��Ϣͷ�ĺ�*/
#define IMSA_WRITE_LRRC_MSG_HEAD(pstMsg, ulMsgID,ulLen)\
                    (pstMsg)->stMsgHeader.ulMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid = PS_PID_ERRC;\
                    (pstMsg)->stMsgHeader.ulLength      = (ulLen - VOS_MSG_HEAD_LENGTH);


/*��װдMTC MSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MTC_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_MTC;
#define IMSA_WRITE_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
                    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_IMSA; \
                    (pstHeader)->usModemId         = ModemId; \
                    (pstHeader)->usAlmId           = AlmId; \
                    (pstHeader)->usAlmLevel        = AlmLevel; \
                    (pstHeader)->usAlmType         = IMSA_ERR_LOG_ALARM_TYPE_COMMUNICATION; \
                    (pstHeader)->usAlmLowSlice     = ulSlice; \
                    (pstHeader)->usAlmHighSlice    = 0; \
                    (pstHeader)->ulAlmLength       = ulLength;

#define IMSA_WRITE_OM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
/*��װдUSIM��Ϣͷ�ĺ�*/
/*USIM����Ϣͷ����ͳһ��װ����MsgHeader��*/
#define IMSA_WRITE_USIM_MSG_HEAD(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
    ö����    : IMSA_TIMER_ID_ENUM
    ö��˵��  : ��ʱ��ID
*****************************************************************************/
enum IMSA_TIMER_ID_ENUM
{
    TI_IMSA_START_OR_STOP               = 0x0000,           /* ���ػ���ʱ�� */
    TI_IMSA_PERIOD_TRY_IMS_SRV          = 0x0001,           /* �����Գ���IMS����ʱ�� */
    TI_IMSA_TEMP_FORBIDDEN_TIMER        = 0x0002,           /* ��ʱ��ֹ��ʱ���������ڼ䣬��������IMS PDN���� */

    /* delete PeriodImsEmcSrvTryTimer */

    TI_IMSA_SIP_SIGAL_PDP_ORIG          = 0x0100,           /* SIP������ز��Ŷ�ʱ�� */
    TI_IMSA_SIP_SIGAL_PDP_END           = 0x0101,           /* SIP�������ȥ���Ŷ�ʱ�� */
    TI_IMSA_WAIT_IPV6_INFO              = 0x0102,           /* �ȴ�IPV6��Ϣ��ʱ�� */

    TI_IMSA_REG_PROTECT                 = 0x0200,           /* ע��ģ��ı�����ʱ�� */
    TI_IMSA_REG_RETRY                   = 0x0201,           /* ע��ģ������Զ�ʱ�� */
    TI_IMSA_REG_PERIOD_TRY              = 0x0202,           /* ע��ģ������ڳ���IMSע�ᶨʱ�� */
    TI_IMSA_CALL_PROTECT                = 0x0300,           /* ����ģ��ı�����ʱ�� */
    TI_IMSA_CALL_RES_READY              = 0x0301,           /* ����ģ��ȴ���ԴԤ�������ʱ�� */
    TI_IMSA_CALL_DTMF_DURATION          = 0x0302,           /* ����ģ��dtmf����ʱ����ʱ�� */
    TI_IMSA_CALL_DTMF_PROTECT           = 0x0303,           /* ����ģ��dtmf������ʱ�� */
    TI_IMSA_CALL_REDIAL_MAX_TIME        = 0x0304,           /* ����ģ���ز����ʱ����ʱ�� */
    TI_IMSA_CALL_REDIAL_INTERVEL        = 0x0305,           /* ����ģ���ز������ʱ�� */
    TI_IMSA_CALL_NORMAL_TCALL           = 0x0306,           /* NORMAL Tcall��ʱ��*/
    TI_IMSA_CALL_EMC_TCALL              = 0x0307,           /* EMC Tcall��ʱ�� */
    TI_IMSA_CALL_NORM_MEDIA_LOST_REL_CALL   = 0x0308,           /* ý������ͷź������Ҷϵ绰�Ķ�ʱ�� */
    TI_IMSA_CALL_EMC_MEDIA_LOST_REL_CALL    = 0x0309,           /* ý������ͷź������Ҷϵ绰�Ķ�ʱ�� */

    TI_IMSA_SMS_TR1M                    = 0x0400,           /* ����TR1M��ʱ�� */
    TI_IMSA_SMS_TR2M                    = 0x0401,           /* ����TR2M��ʱ�� */
    TI_IMSA_SMS_TRAM                    = 0x0402,           /* ����TRAM��ʱ�� */

    TI_IMSA_BACK_OFF_TX                 = 0x0500,           /* SSAC*/
    TI_IMSA_BACK_OFF_TY                 = 0x0501,           /**/

    TI_IMSA_USSD_WAIT_NET_RSP           = 0x0600,           /*USSD�ȴ�������Ӧ��ʱ��*/
    TI_IMSA_USSD_WAIT_APP_RSP           = 0x0601,           /*USSD�ȴ��ϲ���Ӧ��ʱ��*/

    TI_IMSA_HIFI_ACK_PROTECT            = 0x0701,           /*HIFI���ݰ���ִ������ʱ��*/
    TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER  = 0x0800,           /* ��ȡIMS����ȴ�RF��Դ��ʱ�� */
    TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER        = 0x0801,           /* �ر�IMS����ȴ�RF��Դ��ʱ�� */
    TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER      = 0x0802,           /* MO���еȴ�RF��Դ��ʱ�� */
    TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER      = 0x0803,           /* MT���еȴ�RF��Դ��ʱ�� */
    TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER     = 0x0804,           /* MT���еȴ�RF��Դ��ʱ�� */
    TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER       = 0x0805,           /* MO���ŵȴ�RF��Դ��ʱ�� */
    TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER       = 0x0806,           /* MT���ŵȴ�RF��Դ��ʱ�� */
    TI_IMSA_GET_SERVICE_PROTECT_TIMER           = 0x0807,           /* ��ȡIMS������ʱ��������ʱ�� */
    TI_IMSA_DEREG_SERVICE_PROTECT_TIMER         = 0x0808,           /* ȥע��IMS������ʱ��������ʱ�� */
    TI_IMSA_MO_CALL_PROTECT_TIMER               = 0x0809,           /* ����MO CALL��ʱ��������ʱ�� */
    TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER        = 0x080A,           /* RF�ǽ�����ʱ�ӳٴ���ʱ�� */
    TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER    = 0x080B,           /* RF�ǽ�����ʱ�ӳٴ���ʱ�� */

    IMSA_TIMER_ID_BUTT
};
typedef VOS_UINT16 IMSA_TIMER_ID_ENUM_UINT16;




/*****************************************************************************
    ö����    : IMSA_SIP_NW_ERROR_CAUSE_ENUM
    ö��˵��  : SIP�տھܾ�ԭ��ֵ
*****************************************************************************/
enum IMSA_SIP_NW_ERROR_CAUSE_ENUM
{
    IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY               = 305,
    IMSA_SIP_NW_ERROR_CAUSE_ALTERNATIVE_SERVICE     = 380,
    IMSA_SIP_NW_ERROR_CAUSE_UNAUTHORIZED            = 401,
    IMSA_SIP_NW_ERROR_CAUSE_FORBIDDEN               = 403,
    IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT         = 408,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR   = 500,
    IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE     = 503,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT          = 504,
    IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE         = 600,

    IMSA_SIP_NW_ERROR_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_SIP_NW_ERROR_CAUSE_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_OM_MSG_ENUM
    ö��˵��  : IMSA��ά�ɲ���ϢIDö��
*****************************************************************************/
enum IMSA_OM_MSG_ENUM
{
    ID_IMSA_OM_TIMER_MSG_MAX            = PS_MSG_ID_IMSA_TO_IMSA_OM_BASE + 0xCFFF,  /* �ڴ�֮ǰΪ��ʱ��Ԥ����ά�ɲ�ID */
    ID_IMSA_OM_PDN_REJ_FORB_NV_INFO     = ID_IMSA_OM_TIMER_MSG_MAX + 0x01,          /* PDN REJ����NV���ÿ�ά�ɲ� */
    ID_IMSA_OM_CONN_FORB_INFO           = ID_IMSA_OM_TIMER_MSG_MAX + 0x02,          /* ������ؽ���������ά�ɲ� */
    ID_IMSA_OM_MSG_BUTT
};
typedef VOS_UINT32 IMSA_OM_MSG_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
#if (FEATURE_ON == FEATURE_PTM)
/*******************************************************************************
 �ṹ��    : IMSA_ERR_LOG_ALM_LEVEL_STRU
 �ṹ˵��  : Alm ID��log�����Ӧ�Ľṹ��
 1.��    ��   : 2015��01��06��
   ��    ��   : W00209181
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    IMSA_ERR_LOG_ALM_ID_ENUM_UINT16         enAlmID;        /* �쳣ģ��ID */
    VOS_UINT16                              usLogLevel;     /* �ϱ�log�ȼ� */
}IMSA_ERR_LOG_ALM_LEVEL_STRU;
#endif

typedef struct
{
    VOS_UINT8            *pData;      /*����*/
    VOS_UINT16          usDataLen;   /*����*/
}IMSA_ISIM_DATA_STRU;

typedef VOS_UINT32 ( * IMSA_ISIM_ACTION_FUN )
(
    const IMSA_ISIM_DATA_STRU *    /*����ָ��*/
);


typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimFileId;        /* ISIMЭ���ļ�ID*/
    IMSA_ISIM_ACTION_FUN                pfDecodeActionFun;   /* �������� */
    IMSA_ISIM_ACTION_FUN                pfEncodeActionFun;   /* �������� */
}IMSA_ISIM_ACT_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32   g_ulImsaNotifyRrcVoLteCallStartFlag;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_VOID IMSA_ReadImsaNV(VOS_VOID);

extern VOS_VOID IMSA_StartTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_StopTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_UINT32 IMSA_IsTimerRunning(const IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_GetRemainTimeLen
(
    IMSA_TIMER_STRU                    *pstTimer,
    VOS_UINT32                         *pulRemainTimeLen
);
extern VOS_UINT32 IMSA_AllocImsOpId(VOS_VOID);
extern VOS_VOID   IMSA_ResetImsOpId(VOS_VOID);
extern VOS_UINT32 IMSA_GetImsOpId(VOS_VOID);
extern VOS_VOID IMSA_SaveRcvImsNormOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsNormOpid(VOS_VOID);

extern VOS_VOID IMSA_SaveRcvImsEmcOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsEmcOpid(VOS_VOID);
extern VOS_UINT8 IMSA_AllocUsimOpId(VOS_VOID);
extern VOS_VOID IMSA_ResetUsimOpId(VOS_VOID);
extern VOS_UINT8 IMSA_GetUsimOpId(VOS_VOID);

extern VOS_VOID IMSA_ProcIsimStatusInd(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimRefreshInd(const VOS_VOID *pRcvMsg);

extern VOS_UINT32 IMSA_ProcReadIsimFileResult(VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimAuthRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ReadIsimFile(VOS_VOID);
extern VOS_UINT32  IMSA_UtilBcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
);
extern VOS_UINT32  IMSA_UtilAsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
);


extern VOS_VOID IMSA_UtilStrNCpy(VOS_CHAR *pDst, const VOS_CHAR *pSrc, VOS_UINT32 ulLen);
extern VOS_VOID IMSA_PrintImsaSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);
extern VOS_INT32  IMSA_PrintSpmImsaCallSupsCmdReq
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaSpmCallMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintCallImsaSrvccStatusNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  IMSA_PrintImsaImsOutputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_VOID IMSA_PrintImsaRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID IMSA_ConfigCgi2Ims( VOS_VOID );
extern VOS_CHAR IMSA_ConverterDigit2Chacter
(
    VOS_UINT8                           ucDigit
);
extern VOS_VOID IMSA_ConfigImei2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigTimerLength2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigUeCapabilityInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigNetCapInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigAccoutInfo2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
extern VOS_UINT32  IMSA_AsciiToDtmfKeyEnum
(
    VOS_CHAR                            cAsciiCode,
    IMSA_IMS_DTMF_KEY_ENUM_UINT8       *penDtmfKey
);
extern VOS_VOID IMSA_ConfigSipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigVoipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigCodeInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSsConfInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSecurityInfo2Ims( VOS_VOID );

extern VOS_VOID IMSA_ConfigMediaParmInfo2Ims( VOS_VOID );


extern VOS_VOID IMSA_ConfigNvUeCapabilityInfo2Ims( VOS_VOID );

extern VOS_VOID IMSA_ConfigSipPort2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConverterSipPort2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
);
extern VOS_UINT32 IMSA_SetCurrentPara
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);
extern VOS_UINT32 IMSA_IsRegParaAvailable
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);

extern VOS_VOID IMSA_SndMtcSrvConnStatusNotify(VOS_UINT8 ucIsImsExist);
extern VOS_UINT32 IMSA_IsImsExist(VOS_VOID);
extern VOS_VOID IMSA_WhenImsSrvConnStatusChangeNotifyMtc(VOS_VOID);

extern VOS_UINT32 IMSA_IsCurrentAccessTypeSupportIms(VOS_VOID);
extern VOS_VOID IMSA_SndUsimAuthenticationReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType,
    VOS_UINT8                       ulOpId,
    USIMM_AUTH_DATA_UNION          *puAuth
);
extern VOS_VOID IMSA_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
);
#if (FEATURE_ON == FEATURE_PTM)

extern VOS_VOID IMSA_InitErrLogInfo(VOS_VOID);
extern IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8 IMSA_CallImsaState2ErrlogState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState);
extern VOS_UINT16 IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_ID_ENUM_UINT16 enAlmId);

extern VOS_UINT32 IMSA_IsErrLogNeedRecord(VOS_UINT16 usLevel);

extern VOS_UINT32 IMSA_GetErrLogRingBufContent
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 IMSA_GetErrLogRingBufferUseBytes(VOS_VOID);
extern VOS_VOID IMSA_CleanErrLogRingBuf(VOS_VOID);
extern VOS_UINT32 IMSA_PutErrLogRingBuf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8 IMSA_PsSerStates2ErrlogPsStates
(
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8 enImsaPsStates
);
extern IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8 IMSA_ConnState2ErrlogConnState(IMSA_CONN_STATUS_ENUM_UINT8 enImsaConnState);
extern IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8 IMSA_VoPsState2ErrlogVoPsState(IMSA_IMS_VOPS_STATUS_ENUM_UINT8 enImsaImsVoPsStatus);
extern IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8 IMSA_CallImsaMpty2ErrlogMpty(MN_CALL_MPTY_STATE_ENUM_UINT8 enImsaMpty);
extern IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8 IMSA_RegState2ErrlogState(IMSA_REG_STAUTS_ENUM_UINT8 enImsaRegState);
extern IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8 IMSA_RegAddrType2ErrlogRegReason(IMSA_REG_ADDR_PARAM_ENUM_UINT32 enImsaRegAddr);
extern VOS_VOID IMSA_SndAcpuOmFaultErrLogInd
(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    IMSA_ERR_LOG_ALM_ID_ENUM_UINT16     usAlmId
);
extern VOS_VOID IMSA_RegFailEventReport
(
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enRegFailReason,
    VOS_UINT16                                      usSipStatusCode,
    VOS_UINT8                                       ucPermForbFlag,
    VOS_UINT8                                       ucTermForbFlag
);

#endif

extern VOS_VOID IMSA_ProcMtcMsgModem1InfoInd
(
    const VOS_VOID                     *pRcvMsg
);

extern VOS_VOID IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_ENUM_UINT8  enVolteStatus);

extern VOS_VOID IMSA_SndOmPdnRejForbNvInfo(VOS_VOID);
extern VOS_VOID IMSA_SndOmConnForbiddenInfo(IMSA_OM_CONN_FORBIDDEN_CAUSE_ENUM_UINT32 enCause);
extern VOS_VOID IMSA_ProcLmmAttachBeginInd(const MsgBlock * pMsg);
extern VOS_UINT32 IMSA_GetTempForbFetureCtrlFlag(VOS_VOID);
extern VOS_UINT32 IMSA_GetPermForbFetureCtrlFlag(VOS_VOID);
extern VOS_UINT32 IMSA_IsCauseInPdnTempRejCauseList(TAF_PS_CAUSE_ENUM_UINT32 enCause);
extern VOS_UINT32 IMSA_IsCauseInPdnPermRejCauseList(TAF_PS_CAUSE_ENUM_UINT32 enCause);

extern VOS_INT32 IMSA_SecuMemCpy
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

#endif /* end of ImsaPublic.h */




