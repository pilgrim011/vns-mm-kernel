/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : DhcpLog.h
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��9��30��
  ����޸�   :
  ��������   : DhcpLog.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��30��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DHCP_LOG__
#define __DHCP_LOG__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TTFComm.h"
#include "PsLogdef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define     DHCP_LOG_PARAM_MAX_NUM      (4)
#define     DHCP_LOG_RECORD_MAX_NUM     (10)
#define     ID_CTTF_DHCP_TRACE_LOG_MSG  (0xeeee)

#define     CTTF_DHCP_INIT_LOG_ENT()    DHCP_MNTN_InitLogEnt(&g_stDhcpLogEnt)

/* DHCP��־��� */
#define DHCP_INFO_LOG(String)                                                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_INFO_LOG1(String, Para1)                                           {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_INFO_LOG2(String, Para1, Para2)                                    {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_INFO_LOG3(String, Para1, Para2, Para3)                             {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_INFO_LOG4(String, Para1, Para2, Para3, Para4)                      {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}

#define DHCP_WARNING_LOG(String)                                                {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_WARNING_LOG1(String, Para1)                                        {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_WARNING_LOG2(String, Para1, Para2)                                 {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_WARNING_LOG3(String, Para1, Para2, Para3)                          {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_WARNING_LOG4(String, Para1, Para2, Para3, Para4)                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}

#define DHCP_ERROR_LOG(String)                                                  {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_ERROR_LOG1(String, Para1)                                          {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_ERROR_LOG2(String, Para1, Para2)                                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_ERROR_LOG3(String, Para1, Para2, Para3)                            {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_ERROR_LOG4(String, Para1, Para2, Para3, Para4)                     {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[DHCP_LOG_PARAM_MAX_NUM];
} DHCP_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                          ulCnt;                  /* ʵ�ʻ���Ĵ�ӡ��¼��Ŀ */
    DHCP_LOG_RECORD_STRU                astData[DHCP_LOG_RECORD_MAX_NUM];
} DHCP_LOG_ENT_STRU;

typedef struct
{
    VOS_MSG_HEADER                          /* _H2ASN_Skip */
    VOS_UINT16              usMsgType;      /* _H2ASN_Skip */
    VOS_UINT16              usTransId;
    DHCP_LOG_ENT_STRU       stLogMsgCont;   /* LOG_MSG���� */
} CTTF_DHCP_TRACE_LOG_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern DHCP_LOG_ENT_STRU            g_stDhcpLogEnt;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID DHCP_MNTN_InitLogEnt(DHCP_LOG_ENT_STRU *pstLogEnt);
VOS_VOID DHCP_MNTN_LogSave
(
    DHCP_LOG_ENT_STRU              *pstLogEnt,
    VOS_UINT32                      ulPid,
    LOG_LEVEL_EN                    enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
);
VOS_VOID DHCP_MNTN_LogOutput(DHCP_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid);


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


#endif /* end of DhcpLog.h */

