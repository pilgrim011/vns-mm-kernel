/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaDsDsPublic.c
  Description     : ��C�ļ�ʵ�ֹ����ĺ�������NV��д��USIM��
  History           :
     1.wangchen 00209181    2015-11-26  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaPublic.h"
#include "ImsaEntity.h"
#include "LNvCommon.h"
#include "LPsNvInterface.h"
#include "UsimPsInterface.h"
#include "ImsaNvInterface.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "ImsaImsInterface.h"
#include "ImsaImsAdaption.h"
#include "NasCommPrint.h"
#include "VcImsaInterface.h"
#include "ImsaCdsInterface.h"
#include "ImsaImsInterface.h"
#include "MsgImsaInterface.h"
#include "ImsaRegManagement.h"
#include "ScInterface.h"
#include "CallImsaInterface.h"
#include "NasNvInterface.h"
#include "LNasNvInterface.h"
#include "ImsaDsDsPublic.h"
#if (VOS_OS_VER != VOS_WIN32)
#include "TafNvInterface.h"
#include "SysNvId.h"
#endif

#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaProcOmMsg.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSAPUBLIC_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSAPUBLIC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
IMSA_DSDS_PUBLIC_INFO_STRU       g_stDsdsPubilcInfo;

IMSA_DSDS_TASKTYPE_INFO_STRU g_stImsaDsdsTaskTypeInfo[] =
{
    {RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_MO_SS,            IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_SS,            IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,           IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,           IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,         IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER,       IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
};

#define IMSA_DSDS_TASKTYPETBL_NUM  (sizeof(g_stImsaDsdsTaskTypeInfo)/sizeof(IMSA_DSDS_TASKTYPE_INFO_STRU))


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetTaskStatusByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
IMSA_TASKTYPE_STATUS_ENUM_UINT8 IMSA_DsdsGetTaskStatusByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskStatusByTaskType is entered!");

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus;
        }
    }

    return IMSA_TASKTYPE_STATUS_BUTT;
}
/*****************************************************************************
 �� �� ��  : IMSA_DsdsIsHasActiveResource
 ��������  : �Ƿ��д���ACTIVE״̬������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��23��
   ��    ��   : w00209181
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  IMSA_DsdsIsHasActiveResource
(
    VOS_VOID
)
{

    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 �� �� ��  : IMSA_Dsds_RRM_RfResourceIsShared
 ��������  : ��װRRM��ѯRF��Դ�Ƿ���ӿ�(DSDS�����Ƿ��)
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_RRM_RF_SHARED_ENUM_UINT8 IMSA_Dsds_RRM_RfResourceIsShared(VOS_VOID)
{
    PS_RRM_RF_SHARED_ENUM_UINT8 enRet = PS_RRM_RF_NOT_SHARED;
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager;
    #endif
    IMSA_INFO_LOG("IMSA_Dsds_RRM_RfResourceIsShared is entered!");
    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlManager = IMSA_GetControlManagerAddress();
    #endif

    #if (FEATURE_ON == FEATURE_DSDS)
    #if (VOS_OS_VER != VOS_WIN32)

    enRet = RRM_RfResourceIsShared(IMSA_DSDS_MODEM0,VOS_RATMODE_LTE);

    /*����DSDS���Ժ��Լ�RRM_RfResourceIsShared����Shared,����enActiveModemΪSingle����Ȼ��Ϊ���Բ���*/
    if (IMSA_FALSE == pstControlManager->ucDsdsNvCfgStatus)
    {
       enRet = PS_RRM_RF_NOT_SHARED;
    }
    #endif
    #endif

    return enRet;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsIsResourceStatusReady
 Description     : ������ģ����ã�������Դ���룬������ʱ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
IMSA_RESOURCE_STATUS_ENUM_UINT8  IMSA_DsdsGetResourceStatus
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        return IMSA_RESOURCE_STATUS_ACTIVE;
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_ACTIVE;
    }

    if (IMSA_TRUE == IMSA_DsdsIsHasActiveResource())
    {
        return IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF;
    }


    if (IMSA_TASKTYPE_STATUS_NULL == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_NULL;
    }

    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_APPLYING;
    }

    return IMSA_RESOURCE_STATUS_WAIT_STATUS_IND;

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetIndexByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_DsdsGetIndexByTaskType (RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetIndexByTaskType is entered!");

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return ulIndex;
        }
    }

    return ulIndex;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetTaskStatusByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsSetTaskStatusByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_TASKTYPE_STATUS_ENUM_UINT8         enTaskStatus,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsSetTaskStatusByTaskType is entered!");

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = enTaskStatus;

            g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;
            g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara      = ulPara;
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetTaskSrcByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsModifyTaskSrcByTaskType
(
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskSrcByTaskType is entered!");

    /* ����ע�����񣬹ػ�����������Դ�Ķ�ʱ��ʱ����һ�£������޸�Ϊ�ػ�ʱ����Ҫ��ԭ�ж�ʱ��
    ֹͣ�������ػ���ʱ�� */
    ulIndex = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_ABNORMAL_IDX == ulIndex)
    {
        return;
    }

    if ((IMSA_TASKTYPE_STATUS_APPLYING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) &&
        (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType) &&
        (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc))
    {
        IMSA_DsdsStopApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

        g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;

        IMSA_DsdsStartApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);
    }
    else
    {
        g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetTaskSrcByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 IMSA_DsdsGetTaskSrcByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskSrcByTaskType is entered!");

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc;
        }
    }

    return IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsGetTaskSrcByTaskType
 ��������  : TaskTypeά������ͨ��enTaskType���ҵ���Ӧ��ά����Index
             �ڲ����ú���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_DsdsGetTaskParaByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskParaByTaskType is entered!");

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsTaskTypeProcTaskApply
 ��������  : ����PS_RRM_RADIO_RESOURCE_APPLY_REQʱ����TaskTypeά����Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsTaskTypeProcByTaskApplyType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara,
    VOS_UINT8                               ucHasBuffer
)
{
    VOS_UINT32                          ulIndexOfTbl    = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndexOfTbl)
    {
        IMSA_ERR_LOG("IMSA_DsdsTaskTypeProcByTaskApplyType,ab index!");
        return;
    }

    if (IMSA_TRUE == IMSA_DsdsIsHasActiveResource())
    {
        g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enStatus = IMSA_TASKTYPE_STATUS_ACTIVE;
    }
    else
    {
        g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enStatus = IMSA_TASKTYPE_STATUS_APPLYING;
    }

    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enTrigerSrc  = enTrigerSrc;
    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].ulPara       = ulPara;
    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].ucHasBuffer  = ucHasBuffer;

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_ITFDSDS_SndSingleApplyReq
 ��������  : ��DSDS RRM���͵���������Դ��������Ϣ���ڲ�ʹ�ã�������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_DsdsSndSingleApplyReq(RRM_PS_TASK_TYPE_ENUM_UINT16  enTaskType)
{
    PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU  *pstApplyReq         = VOS_NULL_PTR;

    /*������Ϣ�ռ�*/
    pstApplyReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU));

    /* �������ռ��Ƿ�ɹ� */
    if (VOS_NULL_PTR == pstApplyReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndCdsSetImsBearerReqS:ERROR:Alloc Msg fail!");
        return IMSA_FALSE;
    }

    IMSA_WRITE_RRM_MSG_HEAD(pstApplyReq, ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ, sizeof(PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU));
    //IMSA_WRITE_RRM_MSG_HEAD(pstOccCnf, ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF);

    pstApplyReq->enModemId  = IMSA_DSDS_MODEM0;
    pstApplyReq->enRatType  = VOS_RATMODE_LTE;
    pstApplyReq->enTaskType = enTaskType;
    pstApplyReq->stMsgHeader.ulMsgName    = ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ;

    /* ��ӡ��Ϣ */
    IMSA_INFO_LOG1("IMSA_ITFDSDS_SndSingleApplyReq,send msg,enTaskType=",
                      pstApplyReq->enTaskType);
    /* ������Ϣ */
    IMSA_SND_MSG(pstApplyReq);

    return IMSA_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsTaskTypeProcApplyCnf
 ��������  : �յ�RRM_PS_RADIO_RESOURCE_APPLY_CNF����TaskTypeά����Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsTaskTypeProcByApplyCnf(RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType)
{
    IMSA_DSDS_TASKTYPE_INFO_STRU          *pstImsaTskTypeInfo = VOS_NULL_PTR;
    VOS_UINT32  ulLoop;

    for(ulLoop = 0; ulLoop < IMSA_DSDS_TASKTYPETBL_NUM; ulLoop++)
    {
        pstImsaTskTypeInfo = &g_stImsaDsdsTaskTypeInfo[ulLoop];

        /*ֻҪ��һ������������Applying�Ķ�תΪActive*/
        if (IMSA_TASKTYPE_STATUS_APPLYING == pstImsaTskTypeInfo->enStatus)
        {
            pstImsaTskTypeInfo->enStatus = IMSA_TASKTYPE_STATUS_ACTIVE;
        }

        /*��������´���Pending����һ���쳣*/
        if (IMSA_TASKTYPE_STATUS_PENDING == pstImsaTskTypeInfo->enStatus)
        {
            IMSA_ERR_LOG("IMSA_DsdsTaskTypeProcApplyCnf,ab index!");
        }
    }

    return;
}
/*****************************************************************************
 Function Name  : IMSA_ProcMsgRegResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgRegResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex = IMSA_FALSE;
    VOS_UINT32                          ulRst   = IMSA_TRUE;

    /* ���ô����� */
    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_ProcMsgRegResourceApplyCnf,ab index!");
        return;
    }

    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        ulRst = IMSA_RegFsmProcWaitRetryResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara);

        if (IMSA_FALSE == ulRst)
        {
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        ulRst = IMSA_SRV_ProcPeriodRegResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara);

        if (IMSA_FALSE == ulRst)
        {
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        IMSA_ProcStopResourceApplyCnf();
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        if (IMSA_FALSE == IMSA_SRV_ProcDeRegResourceApplyCnf())
        {
            /* �������Ҫ����ȥע�����̣��������ͷ���Դ */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else
    {
        if (IMSA_FALSE == IMSA_SRV_ProcGetNormSevResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara))
        {
            /* �������Ҫ����ȥע�����̣��������ͷ���Դ */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgDeRegResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgDeRegResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* ���ô����� */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER))
    {
        IMSA_ProcStopResourceApplyCnf();
    }
    else
    {
        if (IMSA_FALSE == IMSA_SRV_ProcDeRegResourceApplyCnf())
        {
            /* �������Ҫ����ȥע�����̣��������ͷ���Դ */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoCallResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoCallResourceApplyCnf
(
    VOS_UINT32              ulIndex
)
{
    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* ���ô����� */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_CALL == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        IMSA_CallProcMoCallResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stMoCall);
    }
    else
    {
        IMSA_CallProcEconfResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stEnhancedConferrence);
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoEmcCallResourceApplyCnf
(
    VOS_UINT32              ulIndex
)
{
    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);


    /* ����ǽ�������#380�ĳ��������ǲ����ڻ�����Ϣ�� */
    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* ���ô����� */
    IMSA_CallProcEmcResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stEmcCall);
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMtCallResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* ���ô����� */
    if (IMSA_FALSE == IMSA_CallProcMtResourceApplyCnf((VOS_UINT8)IMSA_DsdsGetTaskParaByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL)))
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoSmsResourceApplyCnf
(
    VOS_UINT32      ulIndex
)
{
    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMS == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        if ( VOS_NULL_PTR != g_stDsdsPubilcInfo.stBufferInfo.pstMoSms )
        {
            /* ���ô����� */
            IMSA_SMSProcMoResourceApplyCnf(g_stDsdsPubilcInfo.stBufferInfo.pstMoSms);

            /* ������ͷſռ� */
            IMSA_MEM_FREE(g_stDsdsPubilcInfo.stBufferInfo.pstMoSms);
            g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = VOS_NULL_PTR;
        }
    }
    else if(IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMMA == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_SMSProcSmmaResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stSmma);
    }
    else  /* �����SMMA�ش�*/
    {
        IMSA_SMSProcSmmaRetransResourceApplyCnf();
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMtSmsResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMtSmsResourceApplyCnf
(
    VOS_UINT32      ulIndex
)
{
    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    /* ֹͣ��ʱ�� */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* ���ô����� */
    IMSA_SMSProcMtResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stMtSms);
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgResourceApplyCnf
(
    const RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU *pstApplyCnf
)
{
    VOS_UINT32                          ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgResourceApplyCnf: ENTER");

    if (PS_RRM_RESULT_SUCCESS != pstApplyCnf->enResult)
    {
        /* ���ӱ��� */
        return;
    }

    ulIndex = IMSA_DsdsGetIndexByTaskType(pstApplyCnf->enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_ProcMsgResourceApplyCnf,ab index!");
        return;
    }

    /* �����ǰ״̬��NULL�����ָó�����REL IND��ACTIVE CNF�Գ�ĳ�����ֱ�Ӷ��� */
    /* �����ǰ״̬�Ѿ���ACTIVE����������task�Ѿ����뵽����Դ������Ҫ����Ӧ��ֱ�Ӷ��� */
    if ((IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) ||
        (IMSA_TASKTYPE_STATUS_NULL == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus))
    {
        return;
    }

    /*����TaskTypeά����*/
    IMSA_DsdsTaskTypeProcByApplyCnf(pstApplyCnf->enTaskType);

    /* �����ע�����͵ļ����ֱ�ӵ���SERVICEģ���ṩ��API�ӿ� */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_ProcMsgRegResourceApplyCnf();
    }

    /* �����������ļ������ö���ģ���ṩ��API�ӿ� */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_ProcMsgMoSmsResourceApplyCnf(ulIndex);
    }

    /* �����������ļ������ö���ģ���ṩ��API�ӿ� */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        IMSA_ProcMsgMtSmsResourceApplyCnf(ulIndex);
    }

    /* �����MO CALL������ú���ģ���ṩ��API�ӿ� */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        IMSA_ProcMsgMoCallResourceApplyCnf(ulIndex);
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_ProcMsgMoEmcCallResourceApplyCnf(ulIndex);
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
    {
        IMSA_ProcMsgMtCallResourceApplyCnf();
    }

    /* �����ȥע��������Դ�ɹ� */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER))
    {
        IMSA_ProcMsgDeRegResourceApplyCnf();
    }
    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_DsdsSndRrmReleaseInd
 ��������  : ���췢��rrm��release ind��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmReleaseInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16    enTaskType,
    PS_BOOL_ENUM_UINT8              enRelAllFlg,
    VOS_UINT32                      ulDelayTime
)
{
    PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU *pstRelReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_DsdsSndRrmReleaseInd is entered.");

    /*������Ϣ�ռ�*/
    pstRelReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    /* �������ռ��Ƿ�ɹ� */
    if (VOS_NULL_PTR == pstRelReq)
    {
        /* �������ʧ�ܣ��򷵻������ڴ�ʧ�� */
        return;
    }

    IMSA_MEM_SET_S( pstRelReq,
                    sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU),
                    0,
                    sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstRelReq, ID_PS_RRM_RADIO_RESOURCE_RELEASE_IND,sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    pstRelReq->enModemId    = IMSA_DSDS_MODEM0;
    pstRelReq->enRatType    = VOS_RATMODE_LTE;
    pstRelReq->enTaskType   = enTaskType;
    pstRelReq->enRelAllFlag = enRelAllFlg;
    pstRelReq->ulRelDelaytimer = ulDelayTime;


    /* ������Ϣ */
    IMSA_SND_MSG(pstRelReq);
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsSndRrmRegisterInd
 ��������  : ��RRM����ID_PS_RRM_REGISTER_IND��Ϣ
 �������  : enTaskType         :ע����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��21��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{
    /* ����ԭ������ָ�� */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_REGISTER_IND_STRU));

    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ����ʧ�� */
        return;
    }

    IMSA_MEM_SET_S( pstMsg,
                    sizeof(PS_RRM_REGISTER_IND_STRU),
                    0,
                    sizeof(PS_RRM_REGISTER_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstMsg, ID_PS_RRM_REGISTER_IND,sizeof(PS_RRM_REGISTER_IND_STRU));

    pstMsg->enModemId                       = IMSA_DSDS_MODEM0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*������Ϣ*/
    IMSA_SND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsSndRrmDeRegisterInd
 ��������  : ��RRM����ID_PS_RRM_DEREGISTER_IND��Ϣ
 �������  : enTaskType         :ע����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��21��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{
    /* ����ԭ������ָ�� */
    PS_RRM_DEREGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_DEREGISTER_IND_STRU));

    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ����ʧ�� */
        return;
    }

    IMSA_MEM_SET_S( pstMsg,
                    sizeof(PS_RRM_DEREGISTER_IND_STRU),
                    0,
                    sizeof(PS_RRM_DEREGISTER_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstMsg, ID_PS_RRM_DEREGISTER_IND, sizeof(PS_RRM_DEREGISTER_IND_STRU));

    pstMsg->enModemId                       = IMSA_DSDS_MODEM0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*������Ϣ*/
    IMSA_SND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_DsdsProcRrmPsStatusInd
 ��������  : �յ�RRM��PS STATUS IND��Ϣ��֪ͨRRM����ȥע��,ͬʱ������Դ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��23��
   ��    ��   : w00209181
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  IMSA_DsdsProcRrmPsStatusInd
(
    RRM_PS_STATUS_IND_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /* ���ͬʱ��RRMע������Դ��������ĳ���������뵽��Դ�������е����񶼸�RRMģ�鷢������ */
    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (IMSA_TASKTYPE_STATUS_PENDING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            IMSA_DsdsSndRrmDeRegisterInd(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);

            IMSA_DsdsSndSingleApplyReq(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);

            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_APPLYING;

            IMSA_DsdsStartApplyReqTimer(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);
        }
    }

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_DsdsSndRrmOccupyCnf
 ��������  : ��Ա�����ϢID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ���ظ�CNF
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��24��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmOccupyCnf(VOS_VOID)
{
    PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU  *pstOccCnf = VOS_NULL_PTR;

    if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        return;
    }

    pstOccCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstOccCnf)
    {
        /* ����ʧ�� */
        return;
    }

    IMSA_MEM_SET_S( pstOccCnf,
                    sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU),
                    0,
                    sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstOccCnf, ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF,sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    /*������Ϣ*/
    IMSA_SND_MSG(pstOccCnf);

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcOccupyReq
 Description     :   ������ռ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceOccupyCnf
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    if (VOS_FALSE == IMSA_IsTimerRunning(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer))
    {
        return;
    }
    IMSA_StopTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);
    IMSA_DsdsSndRrmOccupyCnf();

    IMSA_DsdsSetTaskStatusByTaskType(enTaskType,
                                     IMSA_TASKTYPE_STATUS_NULL,
                                     IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                     0);
}
/*****************************************************************************
 Function Name   : IMSA_DsdsProcOccupyReq
 Description     :   ������ռ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceOccupyReq
(
    RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU *pstOccupyReq
)
{
    /*����Ƿǽ�����ռ������һ��������ʱ��������������ռcnf*/
    if ((RRM_PS_URGENT_TYPE_NO_URGENT == pstOccupyReq->enUrgentType) ||
        (RRM_PS_URGENT_TYPE_SHORT_OCCUPY == pstOccupyReq->enUrgentType))
    {
        /* Ŀǰֻ�ж������̺�ȥע�����̻ᷢ����ռ  */
        /* �����ӳٴ�����ռ��Ϣ�Ķ�ʱ�� */
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);
    }
    else if (RRM_PS_URGENT_TYPE_URGENT == pstOccupyReq->enUrgentType)
    {
        /*����ǽ�����ռ�������ظ�cnf���ڲ��������� */
        IMSA_DsdsSndRrmOccupyCnf();

        if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            IMSA_SMSProcMoSmsRfOccupiedDelayTimerExp();

            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);


        }

        if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
        {
            IMSA_SMSProcMtSmsRfOccupiedDelayTimerExp();

            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);


        }
    }
    return;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsStartApplyReqTimer
 Description     : �����������ͣ�������ʱ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsStartApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
)
{
    if (RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMoCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMtCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitEmcCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMoSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMtSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType)
    {
        if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc)
        {
            IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitPowerOffRfTimer);
        }
        else
        {
            IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
        }
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitDeRegRFTimer);
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsStopApplyReqTimer
 Description     : �����������ͣ�������ʱ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsStopApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
)
{
    if (RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMoCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMtCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitEmcCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMoSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMtSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType)
    {
        if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc)
        {
            IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitPowerOffRfTimer);
        }
        else
        {
            IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
        }
        //IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitDeRegRFTimer);
    }
    else
    {
    }
    return;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsProcRegResourceApplyReq
 Description     : ������ģ����ã�������Դ���룬������ʱ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceApplyReq
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara,
    VOS_UINT8                               ucHasBuffer
)
{

    IMSA_DsdsSndSingleApplyReq(enTaskType);

    IMSA_DsdsTaskTypeProcByTaskApplyType(enTaskType, enTrigerSrc, ulPara, ucHasBuffer);

    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        IMSA_DsdsStartApplyReqTimer(enTaskType, enTrigerSrc);
        return;
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcResourceApplyReq
 Description     : ������ģ����ã�������Դ���룬������ʱ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_UINT32  IMSA_DsdsProcResourceRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara
)
{
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_TRUE;
    }

    /* ����������Ӧ�ò��������ֳ��� */
    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_FALSE;
    }

    if (IMSA_TASKTYPE_STATUS_PENDING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_FALSE;
    }

    if (IMSA_TASKTYPE_STATUS_NULL == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        IMSA_DsdsSndRrmRegisterInd(enTaskType);

        IMSA_DsdsSetTaskStatusByTaskType(enTaskType, IMSA_TASKTYPE_STATUS_PENDING ,enTrigerSrc, ulPara);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcRegResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcRegResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsProcRegResourceTimerExp: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_DsdsProcRegResourceTimerExp,ab index!");
        return;
    }

    if (IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* ��ע������֪ͨ��RRMģ�� */
        IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* ״̬�л� */
        //IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_TASKTYPE_STATUS_PENDING);
        g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;

        /* ��Ҫ֪ͨMMA VOICE ������ */
        IMSA_SRV_ProcGetNorServiceResourceApplyExp();

        return;
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_RegFsmProcWaitRetryResourceApplyExp();

        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* �޸Ĵ���ԴΪ��ȡ���� */
        IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* ��ע������֪ͨ��RRMģ�� */
        IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* ״̬�л� */
        g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* ���ú������� */
        if (IMSA_TRUE == IMSA_SRV_ProcPeriodRegResourceApplyExp())
        {
            /* ��ע������֪ͨ��RRMģ�� */
            IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* �޸Ĵ���ԴΪ��ȡ���� */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* ״̬�л� */
            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;
        }
        else
        {
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_ProcStopResourceApplyTimerExp();

        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        (VOS_VOID)IMSA_SRV_ProcDeRegResourceApplyTimerExp();

        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcMoCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMoCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        return;
    }

    /* ֪ͨRRMģ���ͷ���Դ */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL);

    /* ֪ͨSPM�ͷź��� */
    IMSA_CallProcMoOrEmcResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcEmcCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        return;
    }

    /* ֪ͨRRMģ���ͷ���Դ */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL);

    /* ֪ͨSPM�ͷź��� */
    IMSA_CallProcMoOrEmcResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMtCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
    {
        return;
    }

    IMSA_CallProcMtResourceApplyTimerExp((VOS_UINT8)IMSA_DsdsGetTaskParaByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL));

    /* ֪ͨRRMģ���ͷ���Դ */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMoSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMS== IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            return;
        }
        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

        IMSA_SMSProcMoResourceApplyTimerExp();

        /* ������Դ��ʱ����֮ǰ����Ŀռ�û���ͷţ��˴���Ҫ�ͷ� */
        if ( VOS_NULL_PTR != g_stDsdsPubilcInfo.stBufferInfo.pstMoSms )
        {
            IMSA_MEM_FREE(g_stDsdsPubilcInfo.stBufferInfo.pstMoSms);
            g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = VOS_NULL_PTR;
        }
    }
    else
    {
        if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            return;
        }

        /* ֪ͨRRMģ���ͷ���Դ */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        IMSA_SMSProcSmmaResourceApplyTimerExp();
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMtSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        return;
    }

    /* ֪ͨRRMģ���ͷ���Դ */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS);
    //IMSA_SMSProcMoResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : ����ע����Դ��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:����ֱ�ӷ�������
                   IMSA_FALSE:��RRM��Ӧ

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcOccupyDelayTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_StopTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);

        IMSA_SMSProcMoSmsRfOccupiedDelayTimerExp();
    }


    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);

        IMSA_SMSProcMtSmsRfOccupiedDelayTimerExp();
    }

    IMSA_DsdsSndRrmOccupyCnf();

    return;
}

/*****************************************************************************
 Function Name  : IMSA_DsdsClearResource()
 Description    : DSDSģ����Դ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_DsdsClearResource(VOS_VOID)
{
     VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /*ʹ�ñ�����������ֵ*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {


        if (IMSA_TASKTYPE_STATUS_PENDING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            IMSA_DsdsSndRrmDeRegisterInd(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);
        }

        if ((IMSA_TASKTYPE_STATUS_APPLYING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) ||
            (IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus))
        {
            /* ֹͣ��ʱ�� */
            IMSA_DsdsStopApplyReqTimer(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

            IMSA_DsdsProcResourceRelease(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);
        }

        /* ״̬�޸�ΪNULL */
        IMSA_DsdsSetTaskStatusByTaskType(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0);

        g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer = IMSA_FALSE;
    }

    if ( VOS_NULL_PTR != g_stDsdsPubilcInfo.stBufferInfo.pstMoSms )
    {
        IMSA_MEM_FREE(g_stDsdsPubilcInfo.stBufferInfo.pstMoSms);
        g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = VOS_NULL_PTR;
    }
}


VOS_VOID IMSA_DsdsSaveMoCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstMoCall
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stMoCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU),
                    pstMoCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveMoEmcCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstEmcCall
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stEmcCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU),
                    pstEmcCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveEconfCallMsg
(
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU       *pstEnhancedConferrence
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stEnhancedConferrence,
                    sizeof(SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU),
                    pstEnhancedConferrence,
                    sizeof(SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveMoSmsMsg
(
    const MSG_IMSA_RP_DATA_REQ_STRU               *pstMoSms
)
{
    VOS_UINT32                      ulLength;

    ulLength     = sizeof(MSG_IMSA_RP_DATA_REQ_STRU) - 4 + pstMoSms->ulDataLen + 1;

    TLPS_PRINT2LAYER_INFO(IMSA_DsdsSaveMoSmsMsg_ENUM,LNAS_ENTRY);

    /* ��ָ��ǿգ�˵���ϴ�����Ŀռ�û���ͷţ� */
    if ( VOS_NULL_PTR != g_stDsdsPubilcInfo.stBufferInfo.pstMoSms )
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DsdsSaveMoSmsMsg_ENUM,LNAS_FUNCTION_LABEL1);
        IMSA_MEM_FREE(g_stDsdsPubilcInfo.stBufferInfo.pstMoSms);
        g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = VOS_NULL_PTR;
    }

    /* ����ռ�, ���յ�����MO SMS��ԴCNF��ʱ���Լ��ػ�ʱ���ж��ͷŴ˴�����Ŀռ� */
    g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = IMSA_MEM_ALLOC(ulLength);

    if (VOS_NULL_PTR == g_stDsdsPubilcInfo.stBufferInfo.pstMoSms)
    {
        IMSA_ERR_LOG("IMSA_DsdsSaveMoSmsMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_DsdsSaveMoSmsMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_CPY_S( g_stDsdsPubilcInfo.stBufferInfo.pstMoSms, ulLength, pstMoSms, ulLength);

    TLPS_PRINT2LAYER_INFO(IMSA_DsdsSaveMoSmsMsg_ENUM, LNAS_LEAVE);
}

VOS_VOID IMSA_DsdsSaveMtSmsMsg
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU            *pstMtSms
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stMtSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU),
                    pstMtSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU));
}

VOS_VOID IMSA_DsdsSaveMoSmmaMsg
(
    const MSG_IMSA_SMMA_REQ_STRU    *pstSmma
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stSmma,
                    sizeof(MSG_IMSA_SMMA_REQ_STRU),
                    pstSmma,
                    sizeof(MSG_IMSA_SMMA_REQ_STRU));
}


VOS_VOID IMSA_DsdsProcResourceRelease
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        if (IMSA_TASKTYPE_STATUS_PENDING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
        {
            IMSA_DsdsSndRrmDeRegisterInd(enTaskType);
        }
        else if (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
        {
            IMSA_DsdsSndRrmReleaseInd(enTaskType,
                                      VOS_FALSE,
                                      VOS_FALSE);

            /* ֹͣ��ʱ�� */
            IMSA_DsdsStopApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

        }
        IMSA_DsdsSetTaskStatusByTaskType(enTaskType,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
    }
}


/*****************************************************************************
 Function Name  : IMSA_DsdsInit
 Description    : IMSA CONNģ��ĳ�ʼ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_DsdsInit( VOS_VOID )
{
    IMSA_DSDS_PUBLIC_INFO_STRU          *pstPublicInfo = &g_stDsdsPubilcInfo;

    pstPublicInfo->stWaitRegRFTimer.phTimer             = VOS_NULL_PTR;
    pstPublicInfo->stWaitRegRFTimer.ucMode              = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitRegRFTimer.usName              = TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitRegRFTimer.ulTimerLen          = TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitDeRegRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitDeRegRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitDeRegRFTimer.usName            = TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitDeRegRFTimer.ulTimerLen        = TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMoCallRFTimer.phTimer          = VOS_NULL_PTR;
    pstPublicInfo->stWaitMoCallRFTimer.ucMode           = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMoCallRFTimer.usName           = TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMoCallRFTimer.ulTimerLen       = TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMtCallRFTimer.phTimer          = VOS_NULL_PTR;
    pstPublicInfo->stWaitMtCallRFTimer.ucMode           = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMtCallRFTimer.usName           = TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMtCallRFTimer.ulTimerLen       = TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitEmcCallRFTimer.phTimer         = VOS_NULL_PTR;
    pstPublicInfo->stWaitEmcCallRFTimer.ucMode          = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitEmcCallRFTimer.usName          = TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitEmcCallRFTimer.ulTimerLen      = TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMoSmsRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitMoSmsRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMoSmsRFTimer.usName            = TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMoSmsRFTimer.ulTimerLen        = TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMtSmsRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitMtSmsRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMtSmsRFTimer.usName            = TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMtSmsRFTimer.ulTimerLen        = TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stDelayProcOccupiedTimer.phTimer     = VOS_NULL_PTR;
    pstPublicInfo->stDelayProcOccupiedTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stDelayProcOccupiedTimer.usName      = TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER;
    pstPublicInfo->stDelayProcOccupiedTimer.ulTimerLen  = TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER_LEN;

    pstPublicInfo->stWaitPowerOffRfTimer.phTimer        = VOS_NULL_PTR;
    pstPublicInfo->stWaitPowerOffRfTimer.ucMode         = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitPowerOffRfTimer.usName         = TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitPowerOffRfTimer.ulTimerLen     = TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER_LEN;

    g_stDsdsPubilcInfo.stBufferInfo.pstMoSms = VOS_NULL_PTR;

    IMSA_DsdsClearResource();

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_RrmMsgDistr()
 Description    : RRM��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RrmMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF:
            IMSA_ProcMsgResourceApplyCnf(pRcvMsg);
            break;

        case ID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ:
            IMSA_DsdsProcResourceOccupyReq((RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU*)pRcvMsg);
            break;

        case ID_RRM_PS_STATUS_IND:
            IMSA_DsdsProcRrmPsStatusInd((RRM_PS_STATUS_IND_STRU*)pRcvMsg);
            break;

        default:
            break;
    }
}


#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaPublic.c */



