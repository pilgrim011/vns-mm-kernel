/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregMain.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��27��
  ��������   : 1X REG(register)�����ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregCtx.h"
#include  "CnasXregMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXregProcess.h"
#include  "CnasXregTimer.h"
#include  "CnasXregListProc.h"
#include  "csn1clib.h"
#include  "CnasXregSndCas.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "UserDefinedDataTypes_cs0005.h"
#endif
#include  "NVIM_Interface.h"

/* Added by wx270776 for OM�ں�, 2015-7-25, begin */
#include "NasNvInterface.h"
/* Added by wx270776 for OM�ں�, 2015-7-25, end */

#include "CnasXregMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_PROCESS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CNAS_XREG_REGSTATE_STRU                 g_stCnasXregStateInfo;

CNAS_XREG_SYS_MSG_CONTENT_STRU          g_stCnasXregSysMsgCont;

CNAS_XREG_HOME_INFO_STRU                g_stCnasXregHomeInfo;

NAS_OM_REPORT_ACTION_ENUM_UINT8         g_enCnasXregRptAction = NAS_OM_REPORT_STOP;

/* 57 = 85-29+1 */
VOS_UINT32  g_aulCnasXregCountMax[] =
{
    152, 181, 215, 256, 304, 362, 430, 512,
    608, 724, 861, 1024, 1217, 1448, 1722, 2048,
    2435, 2896, 3444, 4096, 4870, 5792, 6888, 8192,
    9741, 11585, 13777, 16384, 19483, 23170, 27554, 32768,
    38967, 46340, 55108, 65536, 77935, 92681, 110217, 131072,
    155871, 185363, 220435, 262144, 311743, 370727, 440871, 524288,
    623487, 741455, 881743, 1048576, 1246974, 1482910, 1763487, 2097152,
    2493948
};

CNAS_XREG_DBG_STAT_STRU                 g_stCnasXregDbgStat = {0};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetRegStateAddr
 ��������  : ��ȡע��״̬ȫ�ֱ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XREG_REGSTATE_STRU* CNAS_XREG_GetRegStateAddr(VOS_VOID)
{
    return &g_stCnasXregStateInfo;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetSysMsgAddr
 ��������  : ϵͳ��Ϣ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XREG_SYS_MSG_CONTENT_STRU* CNAS_XREG_GetSysMsgAddr(VOS_VOID)
{
    return &g_stCnasXregSysMsgCont;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SquareRoot
 ��������  : ����ƽ�����ĺ�����Դ��Quack 3�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 CNAS_XREG_SquareRoot(VOS_UINT32 ulNumber)
{
    VOS_UINT32      i;
    float           x;
    float           y;
    float           f;
    VOS_UINT32      ulResult;

    f   = 1.5F;

    x   = ulNumber * 0.5F;

    y   = ulNumber;

    i   = * ( VOS_UINT32 * ) &y;

    i   = 0x5f375a86 - ( i >> 1 );         /*ħ����*/

    y   = * ( float * ) &i;

    y   = y * ( f - ( x * y * y ) );        /*����1    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*����2    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*����3    1/sqrt(number)  */

    ulResult = (VOS_UINT32)(ulNumber * y);

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_CalcDistance
 ��������  : �������ĺ���
 �������  : ulOldLat: Old value of lat
             ulNewLat: New value of lat
             ulOldLong: Old value of long
             ulNewLong: new value of long
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_CalcDistance(
    VOS_INT32                           lOldLat,
    VOS_INT32                           lOldLong,
    VOS_INT32                           lNewLat,
    VOS_INT32                           lNewLong
)
{
    VOS_UINT32                          ulDeltaLat;
    VOS_UINT32                          ulDist;
    VOS_UINT32                          ulDeltaLong;
    VOS_DOUBLE                          dDeltaLong;

    if (lNewLat > lOldLat)
    {
        ulDeltaLat = (VOS_UINT32)(lNewLat - lOldLat);
    }
    else
    {
        ulDeltaLat = (VOS_UINT32)(lOldLat - lNewLat);
    }

    if ( ulDeltaLat > CNAS_XREG_DELTAVALUE_MAX )    /*�ж����ֵ��������Χ������*/
    {
        return CNAS_XREG_DELTADIST_MAX;
    }

    if (lNewLong > lOldLong)
    {
        ulDeltaLong = (VOS_UINT32)(lNewLong - lOldLong);
    }
    else
    {
        ulDeltaLong = (VOS_UINT32)(lOldLong - lNewLong);
    }

    if (( ulDeltaLong > CNAS_XREG_180DEGREE )&&( ulDeltaLong < CNAS_XREG_360DEGREE ))
    {
        ulDeltaLong = CNAS_XREG_360DEGREE - ulDeltaLong;
    }
    else if (ulDeltaLong > CNAS_XREG_360DEGREE)
    {
        ulDeltaLong = ulDeltaLong - CNAS_XREG_360DEGREE;
    }
    else
    {
        ulDeltaLong = ulDeltaLong;
    }

    dDeltaLong = (VOS_DOUBLE)ulDeltaLong * cos((VOS_DOUBLE)(((3.14F)/180*lOldLat)/14400));

    ulDeltaLong = (VOS_UINT32)dDeltaLong;

    if ( ulDeltaLong > CNAS_XREG_DELTAVALUE_MAX )    /*�ж����ֵ��������Χ������*/
    {
        return CNAS_XREG_DELTADIST_MAX;
    }

    ulDist =  CNAS_XREG_SquareRoot(( ulDeltaLat * ulDeltaLat ) + ( ulDeltaLong * ulDeltaLong ));

    ulDist = ulDist >> 4;

    return ulDist;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_StartTime
 ��������  : ��XREGģ��ʹ�õĶ�ʱ��
 �������  : ulTimerId:��ʱ��ID
             ulTimerLen: ��ʱ��ʱ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_StartTime(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    stTimerInfo.ulParam             = VOS_NULL;
    stTimerInfo.ulTimerId           = ulTimerId;
    stTimerInfo.ulTimerLen          = ulTimerLen;
    stTimerInfo.ulTimerPrecision    = VOS_TIMER_PRECISION_0;

    CNAS_RestartTimer(UEPS_PID_XREG, &stTimerInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SetRegEnabled
 ��������  : �ж�����״̬�Լ���ע���Ƿ�ʹ��
 �������  : usSid         -- system id
             usNid         -- network id
             ucHomeReg     -- Homeע��ָʾ
             ucSidRoamReg  -- SidHomeע��ָʾ
             ucNidRoamReg  -- NidHomeע��ָʾ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_SetRegEnabled(VOS_UINT16 usSid,
                                              VOS_UINT16 usNid,
                                              VOS_UINT8  ucHomeReg,
                                              VOS_UINT8  ucSidRoamReg,
                                              VOS_UINT8  ucNidRoamReg)
{
    CNAS_XREG_ROAMING_STATE_UINT8       enRoamingState;
    VOS_UINT32                          ulIndex;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNids;

    g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_NO;

    enRoamingState = CNAS_XREG_SID_ROAMING;

    pstHomeSidNids = CNAS_CCB_GetHomeSidNidList();

    for (ulIndex = 0; ulIndex < pstHomeSidNids->ucSysNum; ulIndex++)
    {
        /* �ҵ���ͬ��SIDֵ */
        if (usSid == pstHomeSidNids->astHomeSidNid[ulIndex].usSid)
        {
            enRoamingState = CNAS_XREG_NID_ROAMING;

            /* �ҵ���ͬ��NIDֵ */
            if ((usNid == pstHomeSidNids->astHomeSidNid[ulIndex].usNid)
                || (CNAS_XREG_HOME_NID == pstHomeSidNids->astHomeSidNid[ulIndex].usNid))
            {
                enRoamingState = CNAS_XREG_NO_ROAMING;

                break;
            }
        }
    }

    /* The mobile station is not roaming, and both HOME_REGs and MOB_TERM_HOMEp are equal to '1'*/
    if (CNAS_XREG_NO_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermHome);

        if ((VOS_TRUE == ucHomeReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermHome))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }

        return;
    }

    /* The mobile station is a foreign SID roamer and both FOR_SID_REGs and
       MOB_TERM_FOR_SIDp are equal to '1'; otherwise the mobile station shall set REG_ENABLEDs to NO. */
    if (CNAS_XREG_SID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForSid);

        if ((VOS_TRUE == ucSidRoamReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermForSid))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }

        return;
    }

    /* The mobile station is a foreign NID roamer and both FOR_NID_REGs and MOB_TERM_FOR_NIDp are equal to '1' */
    if (CNAS_XREG_NID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForNid);

        if ((VOS_TRUE == ucNidRoamReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermForNid))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegSuccProc
 ��������  : ע��ɹ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RegSuccProc(VOS_VOID)
{


    VOS_UINT32                          ulTimerLen;
    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    /* ���翪����ʱ��������������ֹͣ */
    if (CNAS_XREG_TIMER_RUNNING == g_stCnasXregStateInfo.enT57MState)
    {
        CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_T57M, 0);

        g_stCnasXregStateInfo.enT57MState = CNAS_XREG_TIMER_EXPIRED;    /*���ճ�ʱ���������ػ��ᷢ��ע��*/
    }

    /* ����ʼCOUNTֵ��0 */
    g_stCnasXregStateInfo.ulRegInitCount = 0;

    ulTimerLen = (g_stCnasXregStateInfo.ulRegCountMax - g_stCnasXregStateInfo.ulRegInitCount)
                            *CNAS_XREG_MS_PER_COUNT;

    if ((VOS_NULL != ulTimerLen) && (CNAS_XREG_TIMER_NULL != g_stCnasXregStateInfo.enRegTimerState))
    {
        if (CNAS_XREG_TIMER_MAX_LEN < ulTimerLen)
        {
            g_stCnasXregStateInfo.ulRemainderTimerLen = ulTimerLen - CNAS_XREG_TIMER_MAX_LEN;

            /* ��������ע�ᶨʱ�� */
            CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
        }
        else
        {
            g_stCnasXregStateInfo.ulRemainderTimerLen = 0;

            /* ��������ע�ᶨʱ�� */
            CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, ulTimerLen);
        }

        g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_RUNNING;
    }

    /* ָʾ�Ѿ��ɹ�ע���� */
    g_stCnasXregStateInfo.enRegisterFlag = CNAS_XREG_VAR_YES;

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegSuccProc: SysMsg is not current.");
    }

    /* ��ȡ��ǰ�����ϵͳ��Ϣ */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    /* ɾ����ʱ�ڵ� */
    CNAS_XREG_RefreshLists();

    /* ɾ��LIST��BandClass or BlockSystem��ͬ�Ľڵ� */
    CNAS_XREG_DelNodesByBandBlkSys(pstSysInfo);

    /* ����ZONE_LIST�б��SID_NID_LIST�б� */
    CNAS_XREG_UpdateZoneList(pstSysInfo, pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.usRegZone, pstSysInfo->stRegInfo.ucZoneTimer);
    CNAS_XREG_UpdateSidNidList(pstSysInfo, pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.ucZoneTimer);

    /* ����ϵͳ��Ϣ�е�ucRegZoneNum����ZONE_LIST�еĶ�����ɾ�� */
    CNAS_XREG_TotalZones(pstSysInfo->stRegInfo.ucRegZoneNum);

    /* ����ucMultiSidFlgΪ0 */
    if (0 == pstSysInfo->stRegInfo.ucMultiSidFlg)
    {
        CNAS_XREG_DelMultSids();
    }

    /* ����ucMultiNidFlgΪ0 */
    if (0 == pstSysInfo->stRegInfo.ucMultiNidFlg)
    {
        CNAS_XREG_DelMultNids();
    }

    /* ����λ�ò��� */
    g_stCnasXregStateInfo.stDistInfo.lBaseLast = pstSysInfo->stBaseStationInfo.lBaseLatitude;
    g_stCnasXregStateInfo.stDistInfo.lBaseLong = pstSysInfo->stBaseStationInfo.lBaseLongitude;
    g_stCnasXregStateInfo.stDistInfo.ulDistThrd = pstSysInfo->stRegInfo.usRegDistance;
    g_stCnasXregStateInfo.enDistRegFlag = CNAS_XREG_VAR_NO;

    /* ����BandClass��BlockOrSys */
    g_stCnasXregStateInfo.enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);
    g_stCnasXregStateInfo.usBandClass = pstSysInfo->usBandClass;

    /* ע��ɹ��󽫰汾�仯������ */
    g_stCnasXregStateInfo.enIsVerChange  = CNAS_XREG_VAR_NO;

    /* ע��ɹ���TCH̬�л������� */
    g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;

    /* ע��ɹ�����±����UE���� */
    (VOS_VOID)CNAS_XREG_SciParaCheck();
    (VOS_VOID)CNAS_XREG_TermParaCheck();

    /* ����ǰ��SIDNIDLIST��ZONELIST��ά�ɲ���� */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegFailProc
 ��������  : ע��ʧ�ܴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : g002563031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RegFailProc(VOS_VOID)
{
    

    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegFailProc: SysMsg is not current.");
    }

    /* ��ȡ��ǰ�����ϵͳ��Ϣ */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    CNAS_XREG_RefreshLists();

    /* ɾ��LIST��BandClass or BlockSystem��ͬ�Ľڵ� */
    CNAS_XREG_DelNodesByBandBlkSys(pstSysInfo);

    /* ����ǰZONE�ڵ����ZONE_LIST�� */
    CNAS_XREG_AddCurrZoneNode(pstSysInfo->usSid, pstSysInfo->usNid,
                                pstSysInfo->stRegInfo.usRegZone, pstSysInfo->stRegInfo.ucZoneTimer);

    /* ����ǰSIDNID�ڵ����SIDNID_LIST�� */
    CNAS_XREG_AddCurrSidNidNode(pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.ucZoneTimer);

    /* ����ǰ��SIDNIDLIST��ZONELIST��ά�ɲ���� */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_MobTermSet
 ��������  : ����(MOB_TERMs)ָʾ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_MobTermSet(VOS_UINT16 usSid, VOS_UINT16 usNid)
{
    CNAS_XREG_ROAMING_STATE_UINT8       enRoamingState;
    VOS_UINT32                          ulIndex;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNids;

    enRoamingState = CNAS_XREG_SID_ROAMING;

    pstHomeSidNids = CNAS_CCB_GetHomeSidNidList();

    for (ulIndex = 0; ulIndex < pstHomeSidNids->ucSysNum; ulIndex++)
    {
        if (usSid == pstHomeSidNids->astHomeSidNid[ulIndex].usSid)
        {
            enRoamingState = CNAS_XREG_NID_ROAMING;

            if ((usNid == pstHomeSidNids->astHomeSidNid[ulIndex].usNid)
                || (CNAS_XREG_HOME_NID == pstHomeSidNids->astHomeSidNid[ulIndex].usNid))
            {
                enRoamingState = CNAS_XREG_NO_ROAMING;

                break;
            }
        }
    }

    if (CNAS_XREG_NO_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermHome);

        return;
    }

    if (CNAS_XREG_SID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForSid);

        return;
    }

    if (CNAS_XREG_NID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForNid);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_MSRMProc
 ��������  : ����CAS��Ϣ�еĻ�վλ����Ϣ������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_MSRMProc(CNAS_XREG_MSRM_STRU *pstMsrm)
{
/*
The mobile station shall perform the following actions:
   1��If the mobile station supports the 800 MHz analog mode, set the First-Idle ID status to enabled (see [6]).
   2��Set DIGITAL_REGs-p to '00000001'.
   3��Add REG_ZONEs, SIDs, and NIDs to ZONE_LISTs if not already in the list. If required,
      include the band class identifier and block identifier for the current band and frequency block as specified in 2.6.5.1.5.
   4��Delete all entries from ZONE_LISTs belonging to a different band class (see 2.1.1.1 of [2]) than CDMABANDs.
   5��Disable the zone list entry timer for the entry of ZONE_LISTs containing REG_ZONEs, SIDs, and NIDs. For any other entry of ZONE_LISTs whose entry timer
      is not active, enable the entry timer with the duration specified by ZONE_TIMERs (see 2.6.5.1.5).
   6��If ZONE_LISTs contains more than TOTAL_ZONESs entries, delete the excess entries according to the rules specified in 2.6.5.1.5.
   7��Delete all entries from SID_NID_LISTs belonging to a different band class (see [2]) than CDMABANDs.
   8��Add SIDs and NIDs to 1 SID_NID_LISTs if not already in the list. If required, include the band class identifier
      and block identifier for the current band and frequency block as specified in 2.6.5.1.5.
   9��Disable the SID/NID list entry timer for the entry of SID_NID_LISTs containing SIDs, and NIDs.
      For any other entry of SID_NID_LISTs whose entry timer is not active, enable the entry timer with the duration specified in 2.6.5.1.5.
  10��If SID_NID_LISTs contains more than N10m entries, delete the excess entries according to the rules specified in 2.6.5.1.5.
  11��If MULT_SIDSs is equal to '0' and SID_NID_LIST contains entries with different SIDs, delete the excess entries according to the rules specified in 2.6.5.1.5.
  12��If MULT_NIDSs is equal to '0' and SID_NID_LIST contains more than one entry for any SID, delete the excess entries according to the rules specified in 2.6.5.1.5.
  13��Set the stored location of last registration (BASE_LAT_REGs-p and BASE_LONG-_REGs-p) to the base station��s location (BASE_LATs and BASE_LONGs).
      Set thestored registration distance (REG_DIST_REGs-p) to the base station��s registration distance (REG_DISTs).
  14��Update its roaming status and set MOB_TERMs as specified in 2.6.5.3. The mobile station should indicate to the user whether the mobile station is roaming.

*/
    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    /* ��¼ע���� */
    CNAS_XREG_RecordRegRslt(CAS_CNAS_1X_REGISTRATION_TYPE_BUTT, VOS_OK);

    /* ˢ��ZONE&SIDNID�б� */
    CNAS_XREG_RefreshLists();

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegSuccProc: SysMsg is not current.");
    }

    /* ��ȡ��ǰ�����ϵͳ��Ϣ */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    /* ����ZONE_LIST�б��SID_NID_LIST�б� */
    CNAS_XREG_UpdateZoneList(pstSysInfo, pstMsrm->usSid, pstMsrm->usNid, pstMsrm->usRegZone, pstMsrm->ucZoneTimer);
    CNAS_XREG_UpdateSidNidList(pstSysInfo, pstMsrm->usSid, pstMsrm->usNid, pstMsrm->ucZoneTimer);

    /* ����ZONE�б�������� */
    CNAS_XREG_TotalZones(pstMsrm->ucTotalZones);

    /* ����ucMultSidsΪ0 */
    if (0 == pstMsrm->ucMultSids)
    {
        CNAS_XREG_DelMultSids();
    }

    /* ����ucMultNidsΪ0 */
    if (0 == pstMsrm->ucMultNids)
    {
        CNAS_XREG_DelMultNids();
    }

    /* ����λ�ò��� */
    g_stCnasXregStateInfo.stDistInfo.lBaseLast  = pstMsrm->lBaseLat;
    g_stCnasXregStateInfo.stDistInfo.lBaseLong  = pstMsrm->lBaseLong;
    g_stCnasXregStateInfo.stDistInfo.ulDistThrd = pstMsrm->usRegDist;
    g_stCnasXregStateInfo.enDistRegFlag = CNAS_XREG_VAR_NO;

    /* ����BandClass��BlockOrSys */
    g_stCnasXregStateInfo.enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);
    g_stCnasXregStateInfo.usBandClass = pstSysInfo->usBandClass;

    /* ����MOB_TERMs */
    CNAS_XREG_MobTermSet(pstMsrm->usSid, pstMsrm->usNid);

    /* ע��ɹ��󽫰汾�仯������ */
    g_stCnasXregStateInfo.enIsVerChange  = CNAS_XREG_VAR_NO;

    /* ע��ɹ���TCH̬�л������� */
    g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;

    /* ������ϱ���ά�ɲ�ע������ */
    CNAS_XREG_GetRegStateAddr()->enRegTypeMntn = NAS_OM_CDMA_TRAFFIC_CHANNEL_REGISTRATION;
    CNAS_XREG_SndOmRegTypeReportInd(NAS_OM_CDMA_TRAFFIC_CHANNEL_REGISTRATION);

    /* ����ǰ��SIDNIDLIST��ZONELIST��ά�ɲ���� */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ORDMCheck
 ��������  : �ж�CAS��Ϣ�в���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_ORDMCheck(CNAS_XREG_ORDM_STRU *pstOrdm)
{
    /* Registration Request Order */
    if ((CNAS_XREG_REG_ORD == pstOrdm->ucOrder) && (CNAS_XREG_REG_REQ == pstOrdm->ucOrdq))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetCountMax
 ��������  : ��ȡ���ڶ�ʱ�������ʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetCountMax(VOS_UINT8 ucRegPeriod)
{
    if ((CNAS_XREG_MIN_REG_PRD <= ucRegPeriod) && (CNAS_XREG_MAX_REG_PRD >= ucRegPeriod))
    {
        return g_aulCnasXregCountMax[ucRegPeriod - CNAS_XREG_MIN_REG_PRD];
    }

    return 0;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegTimerStart
 ��������  : ����������ע�ᶨʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RegTimerStart(XSD_XREG_SYS_INFO_STRU *pstSysInfo,
                                             CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    VOS_UINT32                          ulCountMax;
    VOS_UINT32                          ulTimerLen;

    /* ��ʱ���Ѿ��������˳� */
    if ((CNAS_XREG_TIMER_NULL != pstSysState->enRegTimerState)
        || (CNAS_XREG_VAR_NO == pstSysState->enRegEnabledFlag))
    {
        return;
    }

    ulCountMax = CNAS_XREG_GetCountMax(pstSysInfo->stRegInfo.ucRegPeriod);

    /* ��������ȷ */
    if (0 == ulCountMax)
    {
        return;
    }

    pstSysState->ulRegCountMax = ulCountMax;

    /* ȡ���ֵ */
    pstSysState->ulRegInitCount = VOS_Rand(ulCountMax - 1);

    ulTimerLen = (pstSysState->ulRegCountMax - pstSysState->ulRegInitCount)*CNAS_XREG_MS_PER_COUNT;

    if (CNAS_XREG_TIMER_MAX_LEN < ulTimerLen)
    {
        pstSysState->ulRemainderTimerLen = ulTimerLen - CNAS_XREG_TIMER_MAX_LEN;

        /* ����ע�ᶨʱ�� */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
    }
    else
    {
        pstSysState->ulRemainderTimerLen = 0;

        /* ����ע�ᶨʱ�� */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, ulTimerLen);
    }

    pstSysState->enRegTimerState = CNAS_XREG_TIMER_RUNNING;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegTimerStop
 ��������  : ����ע�ᶨʱ��ֹͣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RegTimerStop(VOS_VOID)
{
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

    g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_NULL;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegTimerRefresh
 ��������  : ����ע�ᶨʱ��ʱ��ˢ��
 �������  : ucRegPeriod -- ϵͳ��Ϣ�е�PEG_PRDs
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RegTimerRefresh(VOS_UINT8 ucRegPeriod)
{
    VOS_UINT32                          ulCountMax;
    VOS_UINT32                          ulRemainLen;
    VOS_INT32                           lTimerLen;

    /* ����ֵΪ0��ر�ע�ᶨʱ�� */
    if (0 == ucRegPeriod)
    {
        CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

        g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_NULL;

        return;
    }

    /* ����MAXֵ */
    ulCountMax = CNAS_XREG_GetCountMax(ucRegPeriod);

    if ((0 != ulCountMax) && (ulCountMax != g_stCnasXregStateInfo.ulRegCountMax))
    {
        /* �ж϶�ʱ��ע�Ṧ���Ƿ����� */
        if (CNAS_XREG_TIMER_NULL == g_stCnasXregStateInfo.enRegTimerState)
        {
            g_stCnasXregStateInfo.ulRegCountMax = ulCountMax;

            return;
        }

        /* ��ö�ʱ��ʣ�೤�� */
        ulRemainLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

        ulRemainLen += g_stCnasXregStateInfo.ulRemainderTimerLen;

        if (0 != ulRemainLen)
        {
            lTimerLen = (VOS_INT32)(ulRemainLen + (ulCountMax - g_stCnasXregStateInfo.ulRegCountMax)*CNAS_XREG_MS_PER_COUNT);

            if (0 < lTimerLen)
            {
                if (CNAS_XREG_TIMER_MAX_LEN < lTimerLen)
                {
                    g_stCnasXregStateInfo.ulRemainderTimerLen = (VOS_UINT32)(lTimerLen - CNAS_XREG_TIMER_MAX_LEN);

                    /* ����ע�ᶨʱ�� */
                    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
                }
                else
                {
                    g_stCnasXregStateInfo.ulRemainderTimerLen = 0;

                    /* ����ע�ᶨʱ�� */
                    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, (VOS_UINT32)lTimerLen);
                }

                g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_RUNNING;
            }
            else
            {
                CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

                /* ��ʱ���Ѿ���ʱ */
                g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_EXPIRED;
            }
        }

        g_stCnasXregStateInfo.ulRegCountMax = ulCountMax;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PowerUpCheck
 ��������  : �ɷ���п���ע��ļ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ף�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_PowerUpCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /* POWER_UP_REG  is equal to 1; and
       REGISTERED  is equal to NO, and
       REG_ENABLED  is equal to YES. */
    if ((VOS_TRUE               == pstSysInfoSave->stSysInfo.stRegInfo.ucPowerUpReg)
        &&(CNAS_XREG_VAR_NO     == pstSysState->enRegisterFlag)
        &&(CNAS_XREG_VAR_YES    == pstSysState->enRegEnabledFlag))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PowerUpParaCheck
 ��������  : �Ƿ����ڲ����ı����𿪻�ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ף�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_PowerUpParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                    CNAS_XREG_REGSTATE_STRU          *pstSysState)
{
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;

    enBlkSys = CNAS_XREG_BandFreqToBlkSys(pstSysInfoSave->stSysInfo.usBandClass, pstSysInfoSave->stSysInfo.usFreq);

    if ((VOS_TRUE                    == pstSysInfoSave->stSysInfo.stRegInfo.ucPowerUpReg)
        &&(CNAS_XREG_VAR_YES         == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_VAR_YES         == pstSysState->enRegisterFlag)
        &&((pstSysState->usBandClass != pstSysInfoSave->stSysInfo.usBandClass)
            || (enBlkSys != pstSysState->enBlkSys)))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_TimerBaseCheck
 ��������  : �Ƿ���Խ�������ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ף�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_TimerBaseCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    /*PARAMETER_REG  is equal to 1; and
       There is no entry of SID_NID_LIST  whose SID and NID fields match the stored SID and NID . */
    if ((CNAS_XREG_VAR_YES            == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_TIMER_EXPIRED      == pstSysState->enRegTimerState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PowerDownCheck
 ��������  : �ػ�ע����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ף�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_PowerDownCheck(VOS_VOID)
{

    /*REG_ENABLED  equals YES; and

    POWER_DOWN_REG  equals 1; and

    There is an entry of SID_NID_LIST  for which the SID and NID fields are equal to SID  and NID ; and

    The power-up/initialization timer (see 2.6.5.1.1) is disabled or has expired. */
    if ((VOS_NULL_PTR != CNAS_XREG_FindSidNidNode(g_stCnasXregSysMsgCont.stSysInfo.usSid, g_stCnasXregSysMsgCont.stSysInfo.usNid))
        &&(VOS_TRUE == g_stCnasXregSysMsgCont.stSysInfo.stRegInfo.ucPowerDownReg)
        &&(CAS_CNAS_1X_CAS_IDLE_STATE == g_stCnasXregStateInfo.enCasState)
        &&(CNAS_XREG_VAR_YES        == g_stCnasXregStateInfo.enRegEnabledFlag)
        &&(CNAS_XREG_TIMER_EXPIRED  == g_stCnasXregStateInfo.enT57MState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_DistanceCheck
 ��������  : �Ƿ񳬳���վ������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_DistanceCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                            CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /*REG_DIST  is not equal to zero; and
      REG_ENABLED  is equal to YES; and
      The current base station distance from the base station in which the mobile
      station last registered (see 2.6.5.1.4) is greater than or equal to REG_DIST_REGs-p*/

    if ((0 != pstSysInfoSave->stSysInfo.stRegInfo.usRegDistance)
        &&(CNAS_XREG_VAR_YES == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_VAR_YES == pstSysState->enDistRegFlag))
    {
        pstSysState->enDistRegFlag = CNAS_XREG_VAR_NO;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ZoneCheck
 ��������  : ����ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_ZoneCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                        CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /*TOTAL_ZONES  is not equal to zero; and
      REG_ENABLED  is equal to YES; and
      There is no entry of ZONE_LIST  whose SID, NID and REG_ZONE fields match the stored SID , NID  and REG_ZONE .*/

    if ((CNAS_XREG_VAR_YES == pstSysState->enRegEnabledFlag)
        && (0 != pstSysInfoSave->stSysInfo.stRegInfo.ucRegZoneNum))
    {
        if (VOS_NULL_PTR == CNAS_XREG_FindZoneNode(pstSysInfoSave->stSysInfo.usSid,
                                                   pstSysInfoSave->stSysInfo.usNid,
                                                   pstSysInfoSave->stSysInfo.stRegInfo.usRegZone))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SciParaCheck
 ��������  : SCI�������ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_SciParaCheck(VOS_VOID)
{
    VOS_UINT8                               ucCardSci;

    ucCardSci = CNAS_XREG_GetCardSciValue();

    if (ucCardSci != CNAS_XREG_GetLastSciValue())
    {
        CNAS_XREG_SetLastSciValue(ucCardSci);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_TermParaCheck
 ��������  : TERM�������ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_TermParaCheck(VOS_VOID)
{
    CNAS_NVIM_1X_MOB_TERM_STRU          stTermNv;

    /* ��NV���ж�����ֵ�Ϳ��е���Ƚϣ������ͬ����ע����� */
    if (NV_OK != NV_Read(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_TermParaCheck:NV_Read Failed");

        return VOS_FALSE;
    }

    if ((g_stCnasXregHomeInfo.ucMobTermForNid != stTermNv.ucMobTermForNid)
     || (g_stCnasXregHomeInfo.ucMobTermForSid != stTermNv.ucMobTermForSid)
     || (g_stCnasXregHomeInfo.ucMobTermHome   != stTermNv.ucMobTermHome))
    {
        stTermNv.ucMobTermForNid = g_stCnasXregHomeInfo.ucMobTermForNid;
        stTermNv.ucMobTermForSid = g_stCnasXregHomeInfo.ucMobTermForSid;
        stTermNv.ucMobTermHome   = g_stCnasXregHomeInfo.ucMobTermHome;

        (VOS_VOID)NV_Write(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv));

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ParaCheck
 ��������  : �������ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_ParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                        CNAS_XREG_REGSTATE_STRU          *pstSysState)
{
    /*PARAMETER_REG  is equal to 1!��; and
      There is no entry of SID_NID_LIST  whose SID and NID fields match the stored SID  and NID.*/

    if (VOS_FALSE == pstSysInfoSave->stSysInfo.stRegInfo.ucParameterReg)
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(pstSysInfoSave->stSysInfo.usSid, pstSysInfoSave->stSysInfo.usNid))
    {
        return VOS_TRUE;
    }

    /* �жϿ��е�SCIֵ�Ƿ��б仯 */
    if (VOS_TRUE == CNAS_XREG_SciParaCheck())
    {
        return VOS_TRUE;
    }


    if (VOS_TRUE == CNAS_XREG_TermParaCheck())
    {
        return VOS_TRUE;
    }

    /* Э��汾�����仯 */
    if (CNAS_XREG_VAR_YES == g_stCnasXregStateInfo.enIsVerChange)
    {
        return VOS_TRUE;
    }

    /* TCH������л���û��ע�����С�� */
    if (CNAS_XREG_VAR_YES == g_stCnasXregStateInfo.enIsTchHandoff)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_UserZoneCheck
 ��������  : �û�����ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_UserZoneCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    return VOS_FALSE;   /*���ص�����ʵ��*/
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_EncryptCheck
 ��������  : ���������仯ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL CNAS_XREG_EncryptCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    return VOS_FALSE;   /*���ص�����ʵ��*/
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_IdleRegCheck
 ��������  : ϵͳ�Զ�ע�����ͼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ף�
    �޸�����   : �����ɺ���
*****************************************************************************/
CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 CNAS_XREG_IdleRegCheck(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if ((CNAS_XREG_SYSMSG_CURRENT != g_stCnasXregSysMsgCont.enAvailable)
        ||(CNAS_XREG_TIMER_EXPIRED  != g_stCnasXregStateInfo.enT57MState)
        ||(CAS_CNAS_1X_CAS_IDLE_STATE  != g_stCnasXregStateInfo.enCasState))
    {
        return CAS_CNAS_1X_REGISTRATION_TYPE_BUTT;
    }

    /* ����������ע�ᶨʱ�� */
    CNAS_XREG_RegTimerStart(&g_stCnasXregSysMsgCont.stSysInfo, &g_stCnasXregStateInfo);

    /* ˢ�³�ʱ����ڵ� */
    CNAS_XREG_RefreshLists();

    ulResult = CNAS_XREG_PowerUpCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_POWER_UP_REGISTRATION;
    }

    ulResult = CNAS_XREG_PowerUpParaCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_POWER_UP_REGISTRATION;
    }

    ulResult = CNAS_XREG_ParaCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_PARAMETER_CHANGED_REGISTRATION;
    }

    ulResult = CNAS_XREG_TimerBaseCheck(&g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_TIMER_BASED_REGISTRATION;
    }

    ulResult = CNAS_XREG_DistanceCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_DISTANCE_BASED_REGISTRATION;
    }

    ulResult = CNAS_XREG_ZoneCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_ZONE_BASED_REGISTRATION;
    }

    return CAS_CNAS_1X_REGISTRATION_TYPE_BUTT;
}

/*****************************************************************************
 �� �� ��  : CAS_XREG_GetTrueCodeByComplementCode
 ��������  : ����ת����ԭ��
 �������  : VOS_UINT32 ulCompCode,VOS_UINT8 ucCompLende
 �������  : ��
 �� �� ֵ  : VOS_INT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��18��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CAS_XREG_GetTrueCodeByComplementCode(
    VOS_INT32                          *plTrueCode,
    VOS_UINT32                          ulCompCode,
    VOS_UINT8                           ucCompLen
)
{
    VOS_UINT32                           ulTemp;
    VOS_UINT32                           ulLoop;

    if ((ucCompLen > 32)
     || (ucCompLen < 2))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CAS_XREG_GetTrueCodeByComplementCode: ucCompLen invalid");

        return ;
    }

    /* �жϴ���Ĳ����Ƿ�Ϊ������false��ʾ������true��ʾ���� */
    if (0 == (((VOS_UINT32)1 << (ucCompLen - 1)) & ulCompCode))
    {
        *plTrueCode                     = (VOS_INT32)ulCompCode;
    }
    else
    {
        ulTemp                          = ulCompCode;
        for (ulLoop = ucCompLen;ulLoop < 32;ulLoop++)
        {
            ulTemp                      |= (VOS_UINT32)1 << ulLoop;
        }

        *plTrueCode                     = (VOS_INT32)ulTemp;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_DSCHDataTrans
 ��������  : CAS���͵�DSCH����ת��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_DSCHDataTrans(CAS_CNAS_1X_DSCH_DATA_IND_STRU *pstDschData)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stDecodeData;
    VOS_INT                             lDecodeRslt;
    CNAS_XREG_MSRM_STRU                 stMsrm;

    CNAS_XREG_SetCS0005EDetailPara(&stCS0005Detail, pstDschData->enDschMsgType, CNAS_CCB_GetPRevInUse(), 0);

    /* ��ʼ���ڴ� */
    PS_MEM_SET(&stDecodeData, 0, sizeof(stDecodeData));

    /* ���� SYNC ��Ϣ */
    lDecodeRslt = DECODE_c_f_dsch((char *)(pstDschData->aucMsgData),
                                              0,
                                              &stDecodeData,
                                              pstDschData->usMsgDataLen, /* ��bit�������� */
                                              &stCS0005Detail);

    /* ����ʧ��, �ͷ��ڴ�, ���� */
    if ((lDecodeRslt < 0)
     || (U_c_f_dsch_MSRM != stDecodeData.Present))
    {
        if (VOS_NULL_PTR != stDecodeData.u.MSRM)
        {
            FREE_c_f_dsch(&stDecodeData);
        }

        return VOS_ERR;
    }

    CAS_XREG_GetTrueCodeByComplementCode(&(stMsrm.lBaseLat), stDecodeData.u.MSRM->BASE_LAT, 22);
    CAS_XREG_GetTrueCodeByComplementCode(&(stMsrm.lBaseLong), stDecodeData.u.MSRM->BASE_LONG, 23);

    stMsrm.usNid        = (VOS_UINT16)stDecodeData.u.MSRM->NID;
    stMsrm.usRegDist    = (VOS_UINT16)stDecodeData.u.MSRM->REG_DIST;
    stMsrm.usRegZone    = (VOS_UINT16)stDecodeData.u.MSRM->REG_ZONE;
    stMsrm.usSid        = (VOS_UINT16)stDecodeData.u.MSRM->SID;
    stMsrm.ucMultNids   = stDecodeData.u.MSRM->MULT_NIDS;
    stMsrm.ucMultSids   = stDecodeData.u.MSRM->MULT_SIDS;
    stMsrm.ucTotalZones = stDecodeData.u.MSRM->TOTAL_ZONES;
    stMsrm.ucZoneTimer  = stDecodeData.u.MSRM->ZONE_TIMER;

    CNAS_XREG_MSRMProc(&stMsrm);

    FREE_c_f_dsch(&stDecodeData);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_CSCHDataTrans
 ��������  : CAS���͵�cSCH����ת��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_CSCHDataTrans(CAS_CNAS_1X_CSCH_DATA_IND_STRU *pstCschData)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_csch_mini6                      stDecodeData;
    VOS_INT                             lDecodeRslt;
    CNAS_XREG_ORDM_STRU                 stOrdm;

    CNAS_XREG_SetCS0005EDetailPara(&stCS0005Detail, pstCschData->enCschMsgType, CNAS_CCB_GetPRevInUse(), 0);

    /* ��ʼ���ڴ� */
    PS_MEM_SET(&stDecodeData, 0, sizeof(stDecodeData));

    /* ���� SYNC ��Ϣ */
    lDecodeRslt = DECODE_c_f_csch_mini6((char *)(pstCschData->aucMsgData),
                                              0,
                                              &stDecodeData,
                                              pstCschData->usMsgDataLen, /* ��bit�������� */
                                              &stCS0005Detail);

    /* ����ʧ��, �ͷ��ڴ�, ���� */
    if ((lDecodeRslt < 0)
     || (U_c_f_csch_mini6_ORDM != stDecodeData.Present)
     || (VOS_NULL_PTR == stDecodeData.u.ORDM->order.parameters.u.p_R_Generic_Order))
    {
        if (VOS_NULL_PTR != stDecodeData.u.ORDM)
        {
            FREE_c_f_csch_mini6(&stDecodeData);
        }

        return VOS_ERR;
    }

    stOrdm.ucOrder = stDecodeData.u.ORDM->order.ORDER;
    stOrdm.ucOrdq  = stDecodeData.u.ORDM->order.parameters.u.p_R_Generic_Order->ORDQ;

    /* �жϵ�ǰOrder��Ϣ�Ƿ�ΪRegistation Requset Order */
    if (VOS_OK != CNAS_XREG_ORDMCheck(&stOrdm))
    {
        FREE_c_f_csch_mini6(&stDecodeData);

        return VOS_ERR;
    }

    FREE_c_f_csch_mini6(&stDecodeData);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ClearGlobal
 ��������  : ȫ�ֱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_ClearGlobal(VOS_VOID)
{
    VOS_MemSet(&g_stCnasXregStateInfo, 0, sizeof(g_stCnasXregStateInfo));

    g_stCnasXregStateInfo.enRegTypeMntn = NAS_OM_CDMA_REG_MODE_BUTT;

    VOS_MemSet(&g_stCnasXregSysMsgCont, 0, sizeof(g_stCnasXregSysMsgCont));

    g_stCnasXregSysMsgCont.enAvailable = CNAS_XREG_SYSMSG_STATE_BUTT;

    VOS_MemSet(&g_stCnasXregHomeInfo, 0, sizeof(g_stCnasXregHomeInfo));

    /* Ĭ��ֵ */
    CNAS_XREG_SetCardSciValue(CNAS_XREG_SCI_DEF_VALUE);

    (VOS_VOID)CNAS_XREG_IsSetMobTerm(VOS_TRUE, VOS_TRUE, VOS_TRUE);

    CNAS_XREG_RestoreList();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GlobalMntn
 ��������  : ȫ�ֱ�����ά�ɲ���Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_GlobalMntn(VOS_UINT32 ulMsgID,VOS_UINT32 ulEvent)
{
    CNAS_XREG_MNTN_MSG_STRU     *pstMsg;

    pstMsg = (CNAS_XREG_MNTN_MSG_STRU*)VOS_AllocMsg(UEPS_PID_XREG, sizeof(CNAS_XREG_MNTN_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid   = UEPS_PID_XREG;
    pstMsg->enMsgId         = ulMsgID;
    pstMsg->ulEventID       = ulEvent;
    pstMsg->enCurState      = CNAS_XREG_GetCurrFsmId();

    VOS_MemCpy(&(pstMsg->stCnasXregStateInfo),  &g_stCnasXregStateInfo,  sizeof(g_stCnasXregStateInfo));
    VOS_MemCpy(&(pstMsg->stCnasXregSysMsgCont), &g_stCnasXregSysMsgCont, sizeof(g_stCnasXregSysMsgCont));
    VOS_MemCpy(&(pstMsg->stCnasXregHomeInfo),   &g_stCnasXregHomeInfo,   sizeof(g_stCnasXregHomeInfo));

    DIAG_TraceReport((VOS_VOID *)(pstMsg));

    VOS_FreeMsg(UEPS_PID_XREG, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_BandFreqToBlkSys
 ��������  : Ƶ�β���ת��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XREG_BLKSYS_ENUM_UINT8 CNAS_XREG_BandFreqToBlkSys(VOS_UINT16 usBandClass, VOS_UINT16 usFreq)
{
    if (0 == usBandClass)
    {
        if (CNAS_XREG_NUM_RANGE(1, 333, usFreq)
            || CNAS_XREG_NUM_RANGE(667, 716, usFreq)
            || CNAS_XREG_NUM_RANGE(991, 1023, usFreq))
        {
            return CNAS_XREG_BLKSYS_CELL_A;
        }

        if (CNAS_XREG_NUM_RANGE(334, 666, usFreq)
            || CNAS_XREG_NUM_RANGE(717, 799, usFreq))
        {
            return CNAS_XREG_BLKSYS_CELL_B;
        }
    }

    if (1 == usBandClass)
    {
        if (299 >= usFreq)
        {
            return CNAS_XREG_BLKSYS_PCS_A;
        }

        if (CNAS_XREG_NUM_RANGE(300, 399, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_D;
        }

        if (CNAS_XREG_NUM_RANGE(400, 699, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_B;
        }

        if (CNAS_XREG_NUM_RANGE(700, 799, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_E;
        }

        if (CNAS_XREG_NUM_RANGE(800, 899, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_F;
        }

        if (CNAS_XREG_NUM_RANGE(900, 1199, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_C;
        }
    }

    return CNAS_XREG_BLKSYS_BUTT;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RecordRegRslt
 ��������  : ��¼ע����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RecordRegRslt(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType,
                                            CAS_CNAS_1X_EST_RSLT_ENUM_UINT8 enEstRslt)
{
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].enRegType = enRegType;
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].enEstRslt = enEstRslt;
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].ulSlice   = VOS_GetSlice();

    g_stCnasXregDbgStat.ulIndex++;

    if (CNAS_XREG_MAX_ITEM_NUM == g_stCnasXregDbgStat.ulIndex)
    {
        g_stCnasXregDbgStat.ulIndex = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RecordShow
 ��������  : ��ӡע���¼��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_RecordShow(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = g_stCnasXregDbgStat.ulIndex; ulIndex < CNAS_XREG_MAX_ITEM_NUM; ulIndex++)
    {
        if (0 != g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice)
        {
            vos_printf("enRegType: %d, enEstRslt: %d, ulSlice: 0x%x.\r\n ",
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].enRegType,
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].enEstRslt,
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice);
        }
    }

    for (ulIndex = 0; ulIndex < g_stCnasXregDbgStat.ulIndex; ulIndex++)
    {
        vos_printf("enRegType: %d, enEstRslt: %d, ulSlice: 0x%x.\r\n ",
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].enRegType,
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].enEstRslt,
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SetPowerOffDeregFlg
 ��������  : ���ùػ�ȥע����
 �������  : ucPowerOffDeregFlg------------------�ػ�ȥע����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_SetPowerOffDeregFlg(
    VOS_UINT8                           ucPowerOffDeregFlg
)
{
    g_stCnasXregStateInfo.ucPowerOffDeregFlg = ucPowerOffDeregFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetPowerOffDeregFlg
 ��������  : ��ȡ�ػ�ȥע����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XREG_GetPowerOffDeregFlg(VOS_VOID)
{
    return g_stCnasXregStateInfo.ucPowerOffDeregFlg;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_IsSetMobTerm
 ��������  : ���汻��ģʽʹ�ܱ��
 �������  : VOS_UINT8                           ucMobTermForNid
             VOS_UINT8                           ucMobTermForSid
             VOS_UINT8                           ucMobTermHome
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL CNAS_XREG_IsSetMobTerm(
    VOS_UINT8                           ucMobTermForNid,
    VOS_UINT8                           ucMobTermForSid,
    VOS_UINT8                           ucMobTermHome
)
{
    VOS_BOOL                            bIsValueChange = VOS_FALSE;

    if (ucMobTermForNid != g_stCnasXregHomeInfo.ucMobTermForNid)
    {
        g_stCnasXregHomeInfo.ucMobTermForNid = ucMobTermForNid;

        bIsValueChange = VOS_TRUE;
    }

    if (ucMobTermForSid != g_stCnasXregHomeInfo.ucMobTermForSid)
    {
        g_stCnasXregHomeInfo.ucMobTermForSid = ucMobTermForSid;

        bIsValueChange = VOS_TRUE;
    }

    if (ucMobTermHome != g_stCnasXregHomeInfo.ucMobTermHome)
    {
        g_stCnasXregHomeInfo.ucMobTermHome = ucMobTermHome;

        bIsValueChange = VOS_TRUE;
    }

    return bIsValueChange;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SetCardSciValue
 ��������  : ���濨�е�SICֵ
 �������  : VOS_UINT8                           ucSciValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_SetCardSciValue(
    VOS_UINT8                           ucSciValue
)
{
    g_stCnasXregHomeInfo.ucCardSci = ucSciValue;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetCardSciValue
 ��������  : ��ȡ���е�SICֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8                           ucSciValue
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XREG_GetCardSciValue(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucCardSci;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SetLastSciValue
 ��������  : �����ϴ�ʹ�õ�SICֵ
 �������  : VOS_UINT8                           ucSciValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_SetLastSciValue(
    VOS_UINT8                           ucSciValue
)
{
    g_stCnasXregHomeInfo.ucLastSci = ucSciValue;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetLastSciValue
 ��������  : ��ȡ�ϴ�ʹ�õ�SCIֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XREG_GetLastSciValue(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucLastSci;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_CalcSciValue
 ��������  : ����SCIֵ�����͸������
 �������  : VOS_UINT8                           ucSciValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_CalcSciValue(VOS_VOID)
{
    VOS_UINT8                           ucSciValue;
    VOS_UINT8                           ucCardSci;

    /* �жϵ�ǰϵͳ��Ϣ�Ƿ�Ϊ���� */
    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_CalcSciValue: SysMsg is not current.");

        return;
    }

    ucCardSci  = CNAS_XREG_GetCardSciValue();

    /* ��ǰ����û��ע��� */
    if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(g_stCnasXregSysMsgCont.stSysInfo.usSid,
                                                 g_stCnasXregSysMsgCont.stSysInfo.usNid))
    {
        ucSciValue = CNAS_MIN(1, g_stCnasXregSysMsgCont.stSysInfo.ucMaxSlotCycleIndex);

        /* ���ǰһ���쳣�ػ��󿪻������໹����ԭ����SCI�·�Ѱ�������� */
        ucSciValue = CNAS_MIN(ucCardSci, ucSciValue);
    }
    else /* ��ǰ������ע��� */
    {
        ucSciValue = CNAS_MIN(ucCardSci, g_stCnasXregSysMsgCont.stSysInfo.ucMaxSlotCycleIndex);
    }

    g_stCnasXregHomeInfo.ucCurrSci = ucSciValue;

    CNAS_XREG_SndCASSciReq(ucSciValue);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_BlkSysChange
 ��������  : �ж�ϵͳ�Ƿ����仯
 �������  : pstNewSysInfo
             pstOldSysInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��3��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��13��
   ��    ��   : m00312079
   �޸�����   : DTS2015063003186���returnCauseֵ��ά���߼�

*****************************************************************************/
VOS_VOID CNAS_XREG_BlkSysChange(
    XSD_XREG_SYS_INFO_STRU             *pstNewSysInfo,
    XSD_XREG_SYS_INFO_STRU             *pstOldSysInfo
)
{
    CNAS_XREG_BLKSYS_ENUM_UINT8         enNewBlkSys;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enOldBlkSys;

    enNewBlkSys = CNAS_XREG_BandFreqToBlkSys(pstNewSysInfo->usBandClass, pstNewSysInfo->usFreq);
    enOldBlkSys = CNAS_XREG_BandFreqToBlkSys(pstOldSysInfo->usBandClass, pstOldSysInfo->usFreq);

    if (enNewBlkSys != enOldBlkSys)
    {
        /* Set timer-based registation enable status (COUNTER_ENABLEDs) to NO. */
        CNAS_XREG_RegTimerStop();

        /* Set autonomous registation enable status (REG_ENABLEDs) to NO.. */
        g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_NO;

        /* Set the registerd flag (REGISTEREDs) to NO.*/
        g_stCnasXregStateInfo.enRegisterFlag = CNAS_XREG_VAR_NO;
        /* Set the returnCasue (RETURN_CAUSEs) to 0x00 (NORMAL_ACCESS).*/
        CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
    }

    /* �ж�Э��汾�Ƿ�仯 */
    if (pstNewSysInfo->ucPRevInUse != pstOldSysInfo->ucPRevInUse)
    {
        g_stCnasXregStateInfo.enIsVerChange = CNAS_XREG_VAR_YES;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_EnableNoCardMode
 ��������  : ʹ���޿�ע��ģʽ
 �������  : VOS_UINT8                           ucSciValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_EnableNoCardMode(VOS_VOID)
{
    g_stCnasXregHomeInfo.ucNoCardMode = VOS_TRUE;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetNoCardMode
 ��������  : ��ȡ��ע����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8                           ucNoCardMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XREG_GetNoCardMode(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucNoCardMode;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SetOmReportFlag
 ��������  : ���������������ȡ���ļ��ظ����
 �������  : ���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_XREG_SetOmRegReportFlag(
    NAS_OM_REPORT_ACTION_ENUM_UINT8     enRptAction
)
{
    g_enCnasXregRptAction = enRptAction;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetOmReportFlag
 ��������  : ���������������ȡ���ļ��ظ����
 �������  : ���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_OM_REPORT_ACTION_ENUM_UINT8  CNAS_XREG_GetOmRegReportFlag(VOS_VOID)
{
    return g_enCnasXregRptAction;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcCardReadFileCnf_EF_TERM
 ��������  : ��EFterm�ļ����ݱ��浽ȫ�ֱ�����
 �������  : struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��3��7��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_ProcCardReadFileCnf_EF_TERM(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    CNAS_NVIM_1X_MOB_TERM_STRU          stTermNv;

    ucMobTermForNid = VOS_FALSE;
    ucMobTermForSid = VOS_FALSE;
    ucMobTermHome   = VOS_FALSE;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    /* �����ж� */
    if ((VOS_OK != pstFile->stCmdResult.ulResult) || (0 == pstFile->usEfLen))
    {
        CNAS_WARNING_LOG2(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf_EF_TERM:ERROR: Read Error:",
                          pstFile->stCmdResult.ulResult, pstFile->usEfLen);

        return;
    }

    /* NID */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_NID_MASK))
    {
        ucMobTermForNid = VOS_TRUE;
    }

    /* SID */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_SID_MASK))
    {
        ucMobTermForSid = VOS_TRUE;
    }

    /* HOME */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_HOME_MASK))
    {
        ucMobTermHome   = VOS_TRUE;
    }

    /* ���浽ȫ�ֱ����� */
    if (VOS_TRUE == CNAS_XREG_IsSetMobTerm(ucMobTermForNid, ucMobTermForSid, ucMobTermHome))
    {
        CNAS_XREG_SetCardFilesChangeFlg(CNAS_XREG_REFRESH_CARD_FILE_TERM_FLG);
    }

    /* ����NV��δ�����򽫿��е�ֵд��NV�� */
    stTermNv.ucMobTermForNid = ucMobTermForNid;
    stTermNv.ucMobTermForSid = ucMobTermForSid;
    stTermNv.ucMobTermHome   = ucMobTermHome;
    stTermNv.ucRsv           = 0;

    (VOS_VOID)NV_Write(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcCardReadFileCnf_EF_SSCI
 ��������  : ��EFssci�ļ����ݱ��浽ȫ�ֱ�����.
 �������  : struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��3��7��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_ProcCardReadFileCnf_EF_SSCI(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT8                           ucSci;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if ((VOS_OK != pstFile->stCmdResult.ulResult) || (0 == pstFile->usEfLen))
    {
        CNAS_WARNING_LOG2(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf_EF_SSCI:ERROR: Read Error:",
                          pstFile->stCmdResult.ulResult, pstFile->usEfLen);

        return;
    }

    ucSci = pstFile->aucEf[0] & CNAS_XREG_SSCI_VALUE_MASK;

    /* ����ļ������ˢ�»��� */
    if (ucSci != CNAS_XREG_GetCardSciValue())
    {
        /* ���浽ȫ�ֱ����� */
        CNAS_XREG_SetCardSciValue(ucSci);

        CNAS_XREG_SetCardFilesChangeFlg(CNAS_XREG_REFRESH_CARD_FILE_SSCI_FLG);
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��3��7��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch (enEfId)
    {
        case USIMM_CDMA_EFTERM_ID:
        case USIMM_CSIM_EFTERM_ID:
            CNAS_XREG_ProcCardReadFileCnf_EF_TERM(pstMsg);
            break;

        case USIMM_CDMA_EFSSCI_ID:
        case USIMM_CSIM_EFSSCI_ID:
            CNAS_XREG_ProcCardReadFileCnf_EF_SSCI(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_TchHandoffProc
 ��������  : �ж�TCH̬��Handoff��ϵͳ�Ƿ���ע���
 �������  : pstSysInfoMsg------------------��ǰ��ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��1��30��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_TchHandoffProc(
    XSD_XREG_SYS_INFO_IND_STRU         *pstSysInfoMsg
)
{
    /* ��TCH̬�����л���û��ע�����С�����˳�TCH̬����Ҫ����ע����� */
    if (CNAS_CCB_1X_CAS_TCH_STATE == CNAS_CCB_GetCasState())
    {
        if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(pstSysInfoMsg->stSysInfo.usSid,
                                                     pstSysInfoMsg->stSysInfo.usNid))
        {
            /* ��Ҫע�� */
            g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_YES;
        }
        else
        {
            /* ����Ҫע�� */
            g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;
        }
    }

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




