/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppUpPublic.c
  Description     :
  History         :
     1.LIFUXIN       2015-7-30   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppPublic.h"
#include    "NasLppUpPublic.h"
#include    "NasLppOm.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPUPPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPUPPUBLIC_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)
NAS_LPP_UP_STATE_TIME_STRU g_astLppUpStateTime[LPP_UP_STATE_BUTT] =
{
    { LPP_UP_STATE_IDLE                      ,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}},
    { LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF    ,TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA,{0,0,0}},
    { LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF   ,TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF,  {0,0,0}},
    { LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF  ,TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF, {0,0,0}},
    { LPP_UP_STATE_WAIT_LRRC_MEAS_IND        ,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}}
};

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LPP_GetLppUpEntityCtx
 Description    : LPPģ����û���ʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_USER_PLANE_ENTITY_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_USER_PLANE_ENTITY_STRU*  NAS_LPP_GetLppUpEntityCtx( VOS_VOID )
{
    return (&g_stNasLppEntity.stUserPlaneEntity);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppUpOtdoaCtx
 Description    : LPPģ����û���OTDOAʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_UP_OTDOA_INFO_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_OTDOA_INFO_STRU*  NAS_LPP_GetLppUpOtdoaCtx( VOS_VOID )
{
    return &(NAS_LPP_GetLppUpEntityCtx()->stOtdoaUpEntity);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppUpMultiPosTechCtx
 Description    : LPPģ����û���ͬʱ����ECID&OTDOAʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU*  NAS_LPP_GetLppUpMultiPosTechCtx( VOS_VOID )
{
    return &(NAS_LPP_GetLppUpEntityCtx()->stMultiPosTechEntity);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppUpEcidCtx
 Description    : LPPģ����û���ECIDʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_UP_ECID_INFO_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_ECID_INFO_STRU*  NAS_LPP_GetLppUpEcidCtx( VOS_VOID )
{
    return &(NAS_LPP_GetLppUpEntityCtx()->stEcidUpEntity);
}

/*****************************************************************************
 Function Name  : NAS_LPP_LppUpEntityInit
 Description    : ��ʼ��LPP UP ʵ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangensheng 00324863 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_LppUpEntityInit( VOS_VOID )
{
    NAS_LPP_USER_PLANE_ENTITY_STRU     *pstLppUserPlane = NAS_LPP_NULL_PTR;

    pstLppUserPlane = NAS_LPP_GetLppUpEntityCtx();

    NAS_LPP_MEM_SET_S(  pstLppUserPlane,
                        sizeof(NAS_LPP_USER_PLANE_ENTITY_STRU),
                        0,
                        sizeof(NAS_LPP_USER_PLANE_ENTITY_STRU));

    pstLppUserPlane->stEcidUpEntity.enLppUpState  = LPP_UP_STATE_IDLE;
    pstLppUserPlane->stOtdoaUpEntity.enLppUpState = LPP_UP_STATE_IDLE;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtdoaPosType
 Description    : Get OTDOA��λ���������û��滹��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosType( VOS_VOID )
{
    return NAS_LPP_GetLppEntityCtx()->stUserPlaneEntity.stOtdoaUpEntity.enReqPosTechType;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtdoaAssistDataCtx
 Description    : Get OTDOA��λ���������û��滹��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_OTDOA_ASSIST_CFG_STRU*

 History        :
      1.wangensheng 00324863 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_OTDOA_ASSIST_CFG_STRU*  NAS_LPP_GetOtdoaAssistDataCtx( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stUserPlaneEntity.stOtdoaUpEntity.stOtdoaAssisCfg);
}

/*****************************************************************************
 Function Name  : NAS_LPP_SetOtdoaPosType
 Description    : Set OTDOA��λ���������û��滹��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetOtdoaPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enOtodaPosType
)
{
    NAS_LPP_GetLppEntityCtx()->stUserPlaneEntity.stOtdoaUpEntity.enReqPosTechType =  enOtodaPosType;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtdoaPosReqTechType
 Description    : Get OTDOA�Ķ�λ�����Ƿ�������
 Input          :
 Output         : VOS_VOID
 Return Value   : NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosReqTechType(VOS_VOID)
{
    return NAS_LPP_GetLppUpOtdoaCtx()->enReqPosTechType;
}

/*****************************************************************************
 Function Name  : NAS_LPP_SetEcidPosReqTechType
 Description    : Set ECID�Ķ�λ�����Ƿ�������
 Input          : enUpPosReqTech ��Ӧ�Ķ�λ����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetEcidPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
)
{
    NAS_LPP_GetLppUpEcidCtx()->enReqPosTechType = enUpPosReqTech;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidPosReqTechType
 Description    : Get ECID�Ķ�λ�����Ƿ�������
 Input          :
 Output         : VOS_VOID
 Return Value   : NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosReqTechType(VOS_VOID)
{
    return NAS_LPP_GetLppUpEcidCtx()->enReqPosTechType;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidAndOtdoaMeasFlag
 Description    : Get ECID�Լ�OTDOAͬʱ�����flag
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_BOOL  NAS_LPP_GetEcidAndOtdoaMeasFlag(VOS_VOID)
{
    return  NAS_LPP_GetLppUpMultiPosTechCtx()->bReqEcidAndOtdoaFlag;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtodaLrrcMeasFlag
 Description    : Get OTDOA�����Ƿ��ϱ�
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_BOOL  NAS_LPP_GetOtodaLrrcMeasFlag(VOS_VOID)
{
    return NAS_LPP_GetLppUpOtdoaCtx()->stOtdoaMeasRslt.bMeasRsltFlag;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtodaLrrcMeasAddr
 Description    : Get OTDOA������ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_OTDOA_MEAS_RESLT_STRU*  NAS_LPP_GetOtodaLrrcMeasAddr(VOS_VOID)
{
    return &(NAS_LPP_GetLppUpOtdoaCtx()->stOtdoaMeasRslt);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidLrrcMeasAddr
 Description    : Get ECID�����ϱ��ĵ�ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidLrrcMeasAddr(VOS_VOID)
{
    return &(NAS_LPP_GetLppUpEcidCtx()->stEcidMeasRslt);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidReqMeasType
 Description    : Get ECID�����ϱ�TYPE
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetEcidReqMeasType(VOS_VOID)
{
    return NAS_LPP_GetLppUpEcidCtx()->stRequestedMeasurements.ucRequestedMeas;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetNeighberMeasRsltElement
 Description    : �õ��տ�ecid�Ĳ�����ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-24  �¿���
*****************************************************************************/
LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetNeighberMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo,
    VOS_UINT32                               ulLoop
)
{
    return &(pstEcidSignalMeasInfo->stMeasResultList.astMeasResultsList[ulLoop]);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetPrimaryMeasRsltElement
 Description    : �õ��տ�ecid�Ĳ�����ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-24  �¿���
*****************************************************************************/
LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetPrimaryMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
)
{
    return &(pstEcidSignalMeasInfo->stPrimaryCellMeasResult);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidLrrcMeasFlag
 Description    : Get ECID�����Ƿ��ϱ�
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_BOOL  NAS_LPP_GetEcidLrrcMeasFlag(VOS_VOID)
{
    return NAS_LPP_GetLppUpEcidCtx()->stEcidMeasRslt.bHaveEcidMeasFlag;
}

/*****************************************************************************
 Function Name  : NAS_LPP_SetEcidAndOtdoaMeasFlag
 Description    : Set ECID�Լ�OTDOAͬʱ�����flag
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_BOOL

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetEcidAndOtdoaMeasFlag(VOS_BOOL bReqEcidAndOtdoaFlag)
{
    NAS_LPP_GetLppUpMultiPosTechCtx()->bReqEcidAndOtdoaFlag = bReqEcidAndOtdoaFlag;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_EcidReportTypeAddr
 Description    : Get Ecid�洢�ϱ���ʽ�ĵ�ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : NAS_LPP_REPORT_CRITERIA_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_EcidReportTypeAddr(VOS_VOID)
{
    return &(NAS_LPP_GetLppUpEcidCtx()->stReportCriteria);
}

/*****************************************************************************
 Function Name  : NAS_LPP_OtdoaReportTypeAddr
 Description    : Get OTDOA�洢�ϱ���ʽ�ĵ�ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : NAS_LPP_REPORT_CRITERIA_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_OtdoaReportTypeAddr(VOS_VOID)
{
    return &(NAS_LPP_GetLppUpOtdoaCtx()->stReportCriteria);
}

/*****************************************************************************
 Function Name  : NAS_LPP_MultiPosTechReportTypeAddr
 Description    : Get ECID&OTDOAͬʱ����洢�ϱ���ʽ�ĵ�ַ
 Input          :
 Output         : VOS_VOID
 Return Value   : NAS_LPP_REPORT_CRITERIA_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_MultiPosTechReportTypeAddr(VOS_VOID)
{
    return &(NAS_LPP_GetLppUpMultiPosTechCtx()->stReportCriteria);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidPosType
 Description    : Get ECID��λ���������û��滹��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosType( VOS_VOID )
{
    return NAS_LPP_GetLppEntityCtx()->stUserPlaneEntity.stEcidUpEntity.enReqPosTechType;
}

/*****************************************************************************
 Function Name  : NAS_LPP_SetEcidPosType
 Description    : Set ECID��λ���������û��滹��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetEcidPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enEcidPosType
)
{
    NAS_LPP_GetLppEntityCtx()->stUserPlaneEntity.stEcidUpEntity.enReqPosTechType =  enEcidPosType;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetOtdoaAssistDataFlag
 Description    : Get OTDOA���������Ƿ���ڵı�ʶ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
VOS_BOOL  NAS_LPP_GetOtdoaAssistDataFlag( VOS_VOID )
{
    return NAS_LPP_GetLppUpOtdoaCtx()->stOtdoaAssisCfg.bOtdoaAssistDataFlag;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpResponseTimer
 Description    : Get LPP�û����Response Timer
 Input          : enUpPosTechType ��ʾ����Ķ�λ��������
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpResponseTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU          *pstUpOtdoaInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU           *pstUpEcidInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU *pstMultiPosTechInfo = NAS_LPP_NULL_PTR;

    pstUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();
    pstUpEcidInfo = NAS_LPP_GetLppUpEcidCtx();
    pstMultiPosTechInfo = NAS_LPP_GetLppUpMultiPosTechCtx();

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == enUpPosTechType)
    {
        /*ECID��OTDOAͬʱ����ĳ���*/
        return &(pstMultiPosTechInfo->stReportCriteria.u.stReportOnce.stLppTimer);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enUpPosTechType)
    {
        return &(pstUpEcidInfo->stReportCriteria.u.stReportOnce.stLppTimer);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enUpPosTechType)
    {
        return &(pstUpOtdoaInfo->stReportCriteria.u.stReportOnce.stLppTimer);
    }
    else
    {
    }

    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpPeriodicalTimer
 Description    : Get LPP�û����periodical Timer
 Input          : enUpPosTechType ��ʾ����Ķ�λ��������
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpPeriodicalTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU          *pstUpOtdoaInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU           *pstUpEcidInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU *pstMultiPosTechInfo = NAS_LPP_NULL_PTR;

    pstUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();
    pstUpEcidInfo  = NAS_LPP_GetLppUpEcidCtx();
    pstMultiPosTechInfo = NAS_LPP_GetLppUpMultiPosTechCtx();

    if(PS_TRUE == NAS_LPP_GetEcidAndOtdoaMeasFlag())
    {
        /*ECID��OTDOAͬʱ����ĳ���*/
        return &(pstMultiPosTechInfo->stReportCriteria.u.stReportPeriod.stLppTimer);
    }

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enUpPosTechType)
    {
        return &(pstUpEcidInfo->stReportCriteria.u.stReportPeriod.stLppTimer);
    }

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enUpPosTechType)
    {
        return &(pstUpOtdoaInfo->stReportCriteria.u.stReportPeriod.stLppTimer);
    }

    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpDurationTimer
 Description    : Get LPP�û����Duration Timer
 Input          : enUpPosTechType ��ʾ����Ķ�λ��������
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpDurationTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
)
{
    NAS_LPP_UP_ECID_INFO_STRU           *pstUpEcidInfo  = NAS_LPP_NULL_PTR;

    pstUpEcidInfo  = NAS_LPP_GetLppUpEcidCtx();

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enUpPosTechType)
    {
        return &(pstUpEcidInfo->stReportCriteria.u.stReportTrigger.stLppTimer);
    }

    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpStateTimer
 Description    : Get LPP�û����״̬ Timer
 Input          : enUpPosTechType ��ʾ����Ķ�λ��������
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-11-24  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpStateTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU          *pstUpOtdoaInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU           *pstUpEcidInfo  = NAS_LPP_NULL_PTR;

    pstUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();
    pstUpEcidInfo  = NAS_LPP_GetLppUpEcidCtx();

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enUpPosTechType)
    {
        return &(pstUpEcidInfo->stLppUpStateTimer);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enUpPosTechType)
    {
        return &(pstUpOtdoaInfo->stLppUpStateTimer);
    }
    else
    {

    }

    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpPrtcTimeLen
 Description     : ��ȡ�û���Э�鶨ʱ���ĳ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin      2015-11-24  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetUpPrtcTimeLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
)
{
    VOS_UINT32                           ulLen       = 0;
    NAS_LPP_UP_OTDOA_INFO_STRU          *pstUpOtdoaInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU           *pstUpEcidInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU *pstMultiPosTech= NAS_LPP_NULL_PTR;

    pstUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();
    pstUpEcidInfo  = NAS_LPP_GetLppUpEcidCtx();
    pstMultiPosTech = NAS_LPP_GetLppUpMultiPosTechCtx();

    NAS_LPP_INFO_LOG("NAS_LPP_GetUpPrtcTimeLen is entered");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetUpPrtcTimeLen_ENUM, LNAS_LPP_enPosTechType, enPosTechType);

    switch (enTimeName)
    {
        case TI_NAS_LPP_UP_RESPONSE_TIMER :
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == enPosTechType)
            {
                ulLen = pstMultiPosTech->stReportCriteria.u.stReportOnce.ulResponseTime;
            }
            else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enPosTechType)
            {
                ulLen = pstUpEcidInfo->stReportCriteria.u.stReportOnce.ulResponseTime;
            }
            else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enPosTechType)
            {
                ulLen = pstUpOtdoaInfo->stReportCriteria.u.stReportOnce.ulResponseTime;
            }
            else
            {
            }
            break;

        case TI_NAS_LPP_UP_PERIODICAL_REPORT :
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == enPosTechType)
            {
                ulLen = pstMultiPosTech->stReportCriteria.u.stReportPeriod.ulReportIntraval;
            }
            else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enPosTechType)
            {
                ulLen = pstUpEcidInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval;
            }
            else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enPosTechType)
            {
                ulLen = pstUpOtdoaInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval;
            }
            else
            {
            }
            break;

        case TI_NAS_LPP_UP_REPORT_DURATION :
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enPosTechType)
            {
                ulLen = pstUpEcidInfo->stReportCriteria.u.stReportTrigger.ulReportDuration;
            }
            break;

        default:
            NAS_LPP_ERR_LOG("get error timer name");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetUpPrtcTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorTimerName);
            break;
    }

    return ulLen;
}

/*****************************************************************************
 Function Name  : NAS_LPP_UpTimerStart
 Discription    : �û���������ʱ��
 Input          : enPosTechType  ��ʾ��ǰ��ECID����OTDOA��λ����
                  enTimerType    ��ʾ��ǰ��ʱ��ID
 Output         : VOS_VOID
 Return         : None
 History:
    lifuxin 00253982 2015-11-24 �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_UpTimerStart
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = 0;
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                  ulTimerIndex = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartEnter);
    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(0, 0, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_WARN_LOG("NAS_LPP_UpTimerStart: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerNameInvalid);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LPP_GetTimer(0, 0, enPosTechType, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_UpTimerStart:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerInfoError);
        return;
    }

    /*timer indexֱ�Ӹ�ֵ�ɶ�Ӧ��λ�������ͣ�����OTDOA����ECID*/
    ulTimerIndex = enPosTechType;

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LPP_WARN_LOG("NAS_LPP_UpTimerStart:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimerFail);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG2("(TimerType) Timer not close!",pstTimerInfo->enTimerId, ulTimerIndex);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimer);
    }

    /*���ݶ�ʱ����ͬ���ͣ���ʱ����Ϣ��ͬ*/
    ulTimerLen = NAS_LPP_GetTimerLen(enTimerType, 0, 0, enPosTechType);
    if (0 == ulTimerLen)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_UpTimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerGetTimerLenFail);
        return;
    }

    /*�趨��ʱ��NAME,enTimerType�趨��ʱ��Para����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_LPP,\
                                ulTimerLen, (VOS_UINT32)enTimerType,\
                                 ulTimerIndex, VOS_RELTIMER_NOLOOP))
    {
          /*��ӡ�쳣��Ϣ*/
          NAS_LPP_WARN_LOG("NAS_LPP_UpTimerStart:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStart_ENUM, LNAS_LPP_TimerStartTimerSetTimerFail);
          return;
    }

    /*���¶�ʱ��������Ϣ�Ͷ�ʱ�����*/
    pstTimerInfo->enTimerId     = enTimerType;


    /*������ǰ�Ķ�ʱ����Ϣ */
    NAS_LPP_OmTimerStartInd(PS_NULL_UINT8, PS_NULL_UINT8, enTimerType, ulTimerLen);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_UpTimerStop
 Discription    : �û���ֹͣ��ʱ��
 Input          : enPosTechType  ��ʾ��ǰ��ECID����OTDOA��λ����
                  enTimerType    ��ʾ��ǰ��ʱ��ID
 Output         : VOS_VOID
 Return         : None
 History:
    lifuxin 00253982 2015-11-24 �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_UpTimerStop
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
)
{
    NAS_LPP_TIMER_STRU        *pstTimerInfo         = VOS_NULL_PTR;
    VOS_UINT32                 ulTimerRemainLen     = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpTimerStop_ENUM, LNAS_LPP_TimerStopEnter);
    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(0, 0, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_WARN_LOG("NAS_LPP_UpTimerStop: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStop_ENUM, LNAS_LPP_TimerStopTimerNameInvalid);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LPP_GetTimer(0, 0, enPosTechType, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_UpTimerStop:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStop_ENUM, LNAS_LPP_TimerStopTimerInfoError);
        return;
    }

    /*��ʱ�����ڴ�״̬����رգ����򣬺���*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LPP_WARN_LOG("NAS_LPP_UpTimerStop:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_UpTimerStop_ENUM, LNAS_LPP_TimerStopTimerFailToCloseTimer);
            return;
        }

        /*������ǰ�Ķ�ʱ����Ϣ */
        NAS_LPP_OmTimerStopInd(PS_NULL_UINT8, PS_NULL_UINT8, enTimerType, ulTimerRemainLen);
    }

    return;
}
/*****************************************************************************
 Function Name  : NAS_LPP_UP_SndLppLrrcEcidMeasReq
 Description    : LPP UP��LRRC����ECID��������
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      WANGENSHENG  2015-11-24  �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_UPSndEcidMeasReq
(
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_ECID_MEAS_REQ_STRU *pstEcidMeasReq;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLppLrrcEcidMeasReq enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppLrrcEcidMeasReq_ENUM, LNAS_LPP_Func_Enter);

    pstEcidMeasReq = (LPP_LRRC_ECID_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstEcidMeasReq)
    {
        NAS_LPP_ERR_LOG("lpp snd ecid meas req allocal msg null");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UP_SndLppLrrcEcidMeasReq_ENUM, LNAS_LPP_UP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstEcidMeasReq, sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU), 0, sizeof(LPP_LRRC_ECID_MEAS_REQ_STRU));

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstEcidMeasReq,ID_LPP_LRRC_ECID_MEAS_REQ);

    pstEcidMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;
    pstEcidMeasReq->ucRxTxTimeDiffMeasFlag = PS_TRUE;

    NAS_LPP_SND_MSG(pstEcidMeasReq);
}
/*****************************************************************************
 Function Name   : NAS_LPP_UP_SndOtdoaMeasReq
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangensheng      2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_UPSndOtdoaMeasReq
(
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
)
{
    LPP_LRRC_OTDOA_MEAS_REQ_STRU       *pstOtdoaMeasReq         = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstUpOtdoaInfo          = NAS_LPP_NULL_PTR;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU      *pstLppOtdoaAssistCfg    = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_UPSndOtdoaMeasReq enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UPSndOtdoaMeasReq_ENUM, LNAS_LPP_Func_Enter);

    pstLppOtdoaAssistCfg    = NAS_LPP_GetOtdoaAssistDataCtx();
    pstUpOtdoaInfo          = NAS_LPP_GetLppUpOtdoaCtx();

    pstOtdoaMeasReq         = (LPP_LRRC_OTDOA_MEAS_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstOtdoaMeasReq)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_UPSndOtdoaMeasReq:lpp snd otdoa meas req allocal msg null");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_UPSndOtdoaMeasReq_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstOtdoaMeasReq, sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU), 0, sizeof(LPP_LRRC_OTDOA_MEAS_REQ_STRU));

    NAS_LPP_WRITE_LRRC_MSG_HEAD(pstOtdoaMeasReq,ID_LPP_LRRC_OTDOA_MEAS_REQ);

    pstOtdoaMeasReq->ucLcsMeasCmd = ucLcsMeasCmd;

    if (LPP_LRRC_LCS_MEAS_CMD_SETUP == ucLcsMeasCmd)
    {
        pstOtdoaMeasReq->ucOtdoaMeasAssistanceDataFlag = LPP_LRRC_INFO_FLAG_VALID;

        if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD == pstUpOtdoaInfo->stReportCriteria.enType)
        {
            pstOtdoaMeasReq->enOtdoaRprtInterval =
                    pstUpOtdoaInfo->stReportCriteria.u.stReportPeriod.enOtdoaRprtInterval;
        }
        else
        {
            /*REPORT ONCEDE ,��lrrc�������е�ʱ�䳤��*/
            pstOtdoaMeasReq->enOtdoaRprtInterval = LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16;
        }

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaReferenceCellInfoFlag
            = pstLppOtdoaAssistCfg->ucOtdoaReferenceCellInfoFlag;

        pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.ucOtdoaNeighbourCellInfoFlag
            = pstLppOtdoaAssistCfg->ucOtdoaNeighbourCellInfoFlag;

        NAS_LPP_MEM_CPY_S(  &pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaReferenceCellInfo,
                            sizeof(LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU),
                            &pstLppOtdoaAssistCfg->stOtdoaReferenceCellInfo,
                            sizeof(LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU));

        NAS_LPP_MEM_CPY_S(  &pstOtdoaMeasReq->stLppLrrcOtdoaMeasAssistanceData.stOtdoaNeighbourCellInfo,
                            sizeof(LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU),
                            &pstLppOtdoaAssistCfg->stOtdoaNeighbourCellInfo,
                            sizeof(LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU));
        pstLppOtdoaAssistCfg->bOtdoaAssistDataFlag = PS_FALSE;
    }
    NAS_LPP_SND_MSG(pstOtdoaMeasReq);
}
/*****************************************************************************
 Function Name  : NAS_LPP_UPClrEcidCtx
 Description    : LPPģ����û���ECIDʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangensheng 00324863 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_UPClrEcidCtx(VOS_VOID)
{
    NAS_LPP_UP_ECID_INFO_STRU          *pstUpEcidInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_TIMER_STRU                 *pstTimerInfo    = NAS_LPP_NULL_PTR;

    pstUpEcidInfo                   = NAS_LPP_GetLppUpEcidCtx();

    pstTimerInfo = &pstUpEcidInfo->stLppUpStateTimer;

    /* �ر����̶�ʱ�� */
    NAS_LPP_UpTimerStop(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID, pstTimerInfo->enTimerId);

    /* ֹͣ�ϱ���ʽ��ʱ�� */
    NAS_LPP_StopReportTimer(&pstUpEcidInfo->stReportCriteria, NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);

    if ((LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF == pstUpEcidInfo->enLppUpState)
      ||(LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstUpEcidInfo->enLppUpState))
    {
        NAS_LPP_UPSndEcidMeasReq(LPP_LRRC_LCS_MEAS_CMD_REL);
    }

    pstUpEcidInfo->enLppUpState     = LPP_UP_STATE_IDLE;

    NAS_LPP_MEM_SET_S(  &pstUpEcidInfo->stEcidMeasRslt,
                        sizeof(NAS_LPP_ECID_MEAS_RESULT_STRU),
                        0,
                        sizeof(NAS_LPP_ECID_MEAS_RESULT_STRU));
    NAS_LPP_MEM_SET_S(  &pstUpEcidInfo->stReportCriteria,
                        sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU),
                        0,
                        sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU));
    NAS_LPP_MEM_SET_S(  &pstUpEcidInfo->stRequestedMeasurements,
                        sizeof(MTA_LPP_REQ_MEASUREMENT_STRU),
                        0,
                        sizeof(MTA_LPP_REQ_MEASUREMENT_STRU));
    pstUpEcidInfo->enReqPosTechType = NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL;
}

/*****************************************************************************
 Function Name  : NAS_LPP_UPClrOtdoaCtx
 Description    : ���LPPģ����û���OTDOAʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangensheng 00324863 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_UPClrOtdoaCtx( VOS_VOID )
{
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstLppUpOtdoaInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TIMER_STRU                 *pstTimerInfo    = NAS_LPP_NULL_PTR;

    pstLppUpOtdoaInfo                   = NAS_LPP_GetLppUpOtdoaCtx();
    pstTimerInfo = &pstLppUpOtdoaInfo->stLppUpStateTimer;

    /* �ر����̶�ʱ�� */
    NAS_LPP_UpTimerStop(pstLppUpOtdoaInfo->enReqPosTechType, pstTimerInfo->enTimerId);

    /* ֹͣ�ϱ���ʽ��ʱ�� */
    NAS_LPP_StopReportTimer(&pstLppUpOtdoaInfo->stReportCriteria, NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);

    if ((LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF == pstLppUpOtdoaInfo->enLppUpState)
      ||(LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstLppUpOtdoaInfo->enLppUpState))
    {
        NAS_LPP_UPSndOtdoaMeasReq(LPP_LRRC_LCS_MEAS_CMD_REL);
    }
    pstLppUpOtdoaInfo->enLppUpState     = LPP_UP_STATE_IDLE;

    NAS_LPP_MEM_SET_S(  &pstLppUpOtdoaInfo->stOtdoaAssisCfg,
                        sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU),
                        0,
                        sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));
    NAS_LPP_MEM_SET_S(  &pstLppUpOtdoaInfo->stOtdoaMeasRslt,
                        sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU),
                        0,
                        sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));
    NAS_LPP_MEM_SET_S(  &pstLppUpOtdoaInfo->stReportCriteria,
                        sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU),
                        0,
                        sizeof(NAS_LPP_UP_REPORT_CRITERIA_STRU));
    pstLppUpOtdoaInfo->enReqPosTechType = NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL;
}
/*****************************************************************************
 Function Name  : NAS_LPP_UPClrEntity
 Description    : ���LPPģ����û���ʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangensheng 00324863 2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_UPClrEntity( VOS_VOID )
{
    NAS_LPP_USER_PLANE_ENTITY_STRU     *pstLppUpEntity = NAS_LPP_NULL_PTR;

    pstLppUpEntity  = NAS_LPP_GetLppUpEntityCtx();

    if (NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == pstLppUpEntity->stEcidUpEntity.enReqPosTechType)
    {
        NAS_LPP_UPClrEcidCtx();
        pstLppUpEntity->stEcidUpEntity.enReqPosTechType  = NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL;
    }

    if (NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == pstLppUpEntity->stOtdoaUpEntity.enReqPosTechType)
    {
        NAS_LPP_UPClrOtdoaCtx();
        pstLppUpEntity->stOtdoaUpEntity.enReqPosTechType = NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL;
    }

    if (PS_TRUE == pstLppUpEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag)
    {
        pstLppUpEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag = PS_FALSE;
        NAS_LPP_StopReportTimer(&pstLppUpEntity->stMultiPosTechEntity.stReportCriteria,
                                 NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);

        NAS_LPP_MEM_SET_S(  &(pstLppUpEntity->stMultiPosTechEntity),
                            sizeof(NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU),
                            0,
                            sizeof(NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU));
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetTimeNameBySubState
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin      2015-11-23  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_PARA_ENUM_UINT8  NAS_LPP_UpGetTimeNameByState
(
    NAS_LPP_UP_STATE_ENUM_UINT32       enLppUpState
)
{
    if (enLppUpState >= LPP_UP_STATE_BUTT)
    {
        return TI_NAS_LPP_TIMER_PARA_BUTT;
    }

    return (g_astLppUpStateTime[enLppUpState].enTimeName);
}

/*****************************************************************************
 Function Name   : NAS_LPP_UpChangeTransFsmState
 Description     : LPP�û���ת״̬����
 Input           :

 Output          : None
 Return          : VOS_VOID
 History         :
    1.lifuxin      2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_UpChangeTransFsmState
(
    NAS_LPP_UP_STATE_ENUM_UINT32            enLppUpState,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
)
{
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    NAS_LPP_UP_OTDOA_INFO_STRU         *pstUpOtdoaInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU          *pstUpEcidInfo   = NAS_LPP_NULL_PTR;

    NAS_LPP_WARN_LOG("NAS_LPP_UpChangeTransFsmState!!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_UpChangeTransFsmState_ENUM, LNAS_LPP_Func_Enter);

    if (enLppUpState >= LPP_UP_STATE_BUTT)
    {
        NAS_LPP_ERR_LOG1("wrong main state and substate for change State",enLppUpState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_UpChangeTransFsmState_ENUM, LNAS_LPP_UP_STATE, enLppUpState);
        return;
    }

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enPosTechType)
    {
        pstUpEcidInfo = NAS_LPP_GetLppUpEcidCtx();

        /*��ȡ��ǰ״̬�Ķ�ʱ������*/
        enTimeName = NAS_LPP_UpGetTimeNameByState(pstUpEcidInfo->enLppUpState);

        /*ֹͣԭ��״̬��ʱ��*/
        NAS_LPP_UpTimerStop(enPosTechType, enTimeName);

        /*�����µ�״̬*/
        pstUpEcidInfo->enLppUpState = enLppUpState;

        /*��ȡ��״̬�Ķ�ʱ��*/
        enTimeName = NAS_LPP_UpGetTimeNameByState(pstUpEcidInfo->enLppUpState);

        /*������״̬�Ķ�ʱ��*/
        NAS_LPP_UpTimerStart(enPosTechType, enTimeName);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enPosTechType)
    {
        pstUpOtdoaInfo = NAS_LPP_GetLppUpOtdoaCtx();

        /*��ȡ��ǰ״̬�Ķ�ʱ������*/
        enTimeName = NAS_LPP_UpGetTimeNameByState(pstUpOtdoaInfo->enLppUpState);

        /*ֹͣԭ��״̬��ʱ��*/
        NAS_LPP_UpTimerStop(enPosTechType, enTimeName);

        /*�����µ�״̬*/
        pstUpOtdoaInfo->enLppUpState = enLppUpState;

        /*��ȡ��״̬�Ķ�ʱ��*/
        enTimeName = NAS_LPP_UpGetTimeNameByState(pstUpOtdoaInfo->enLppUpState);

        /*������״̬�Ķ�ʱ��*/
        NAS_LPP_UpTimerStart(enPosTechType, enTimeName);
    }
    else
    {
    }

    return;
}

#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

