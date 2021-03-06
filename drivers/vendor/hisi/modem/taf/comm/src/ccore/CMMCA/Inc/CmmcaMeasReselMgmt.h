/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaProcMeasResel.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月8日
  最近修改   :
  功能描述   : CmmcaProcMeasResel.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月8日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCAPROCMEASRESEL_H__
#define __CMMCAPROCMEASRESEL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CmmcaParseCmd.h"
#include "LRrcCmmcaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId;
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32     enMsgId;
}CMMCA_CMDID_ERRC_MSGID_MAP_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID CMMCA_RcvCmmcMeasReselReq(VOS_VOID *pMsg);

VOS_VOID CMMCA_RcvCmmcSystemChgRsp(VOS_VOID *pMsg);

VOS_UINT32 CMMCA_GetCmdIdFromErrcMsgId(
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32     enMsgId,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16   *penCmdId
);


VOS_VOID CMMCA_RcvCmmcOtherRatInfoInd(VOS_VOID *pMsg);

VOS_VOID CMMCA_RcvCdmaConnStateInfoInd(VOS_VOID *pMsg);
VOS_VOID CMMCA_RcvCdmaMeasurementInfoInd(VOS_VOID *pMsg);
VOS_VOID CMMCA_RcvCdmaEventInfoInd(VOS_VOID *pMsg);
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

#endif /* end of CmmcaProcMeasResel.h */
