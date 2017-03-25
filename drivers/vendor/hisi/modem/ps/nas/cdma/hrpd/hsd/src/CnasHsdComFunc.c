/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdComFunc.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��14��
  ����޸�   :
  ��������   : HSDģ�鹫�ú�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "CnasTimerMgmt.h"
#include  "CnasHsdComFunc.h"
#include  "CnasMntn.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdAvoidStrategy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#ifdef DMT
VOS_UINT32                              g_ulHsdCurSlice         = 0;
VOS_UINT32                              g_ulHsdSliceNumOfOneSec = 1;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_StartTimer
 ��������  : HSDģ���װ��������ʱ������
 �������  : CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId,
             VOS_UINT32                          ulTimerLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_StartTimer(
    CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    /* ��ǰHSD�Ķ�ʱ����ulParam��ʱ�ò�����ȡֵΪ0��ulTimerPrecision����
       VOS_TIMER_NO_PRECISION�����������Ҫ����TimerId������ͬ�趨ʱ����
       ������صķ�װ���� */
    PS_MEM_SET(&stTimerInfo, 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = 0;
    stTimerInfo.ulTimerPrecision        = VOS_TIMER_PRECISION_0;

    CNAS_StartTimer(UEPS_PID_HSD, &stTimerInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_StopTimer
 ��������  : HSDģ���װ��ֹͣ��ʱ������
 �������  : CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_StopTimer(
    CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    /* HSDģ�鲻ҪulParam������ڵ���CNAS_StopTimer��ʱ��ulParamֵΪ0*/
    CNAS_StopTimer(UEPS_PID_HSD, enTimerId, 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_TransferCasStatusTypeToHsdFormat
 ��������  : ��CasStatus��CAS�����ö������תΪHSD�����ö������
 �������  : enCasStatus -- CAS�����ö������

 �������  : ��
 �� �� ֵ  : enHsdCasStatus -- HSD�����ö������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��15��
    ��    ��   : z00316370
    �޸�����   : CAS״̬ö��ֵ��CAS��ΪHSM

*****************************************************************************/
CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_TransferCasStatusTypeToHsdFormat(
    HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16                     enCasStatus
)
{
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdCasStatus;

    switch (enCasStatus)
    {
        case HSM_HSD_HRPD_CAS_STATUS_INIT:
            enHsdCasStatus = CNAS_HSD_AT_STATUS_ENUM_INIT;
            break;

        case HSM_HSD_HRPD_CAS_STATUS_IDLE:
            enHsdCasStatus = CNAS_HSD_AT_STATUS_ENUM_IDLE;
            break;

        case HSM_HSD_HRPD_CAS_STATUS_CONN:
            enHsdCasStatus = CNAS_HSD_AT_STATUS_ENUM_CONN;
            break;

        default:
            enHsdCasStatus = CNAS_HSD_AT_STATUS_ENUM_NONE;
            break;
    }

    return enHsdCasStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSystemSlice
 ��������  : ��ȡϵͳslice
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��ǰ��slice
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��06��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetSystemSlice(VOS_VOID)
{
#ifdef DMT
    return g_ulHsdCurSlice;
#else
    return VOS_GetSlice();
#endif
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSystemSliceNumOfOneSecond
 ��������  : ��ȡ1��slice�ĸ���
 �������  : ��

 �������  : ��
 �� �� ֵ  : 1����slice�ĸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��06��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetSystemSliceNumOfOneSecond(VOS_VOID)
{
    return VOS_GetSliceUnit();
}

/*lint -restore*/

/*****************************************************************************
 �� �� ��  : CNAS_HSD_CheckHybridMode
 ��������  : ͨ��MMA�·��Ľ��뼼���ж��ǻ�ϻ�ǻ��ģʽ
 �������  : aenRatMode:���뼼��
 �������  : ��
 �� �� ֵ  : ��ϻ�ǻ��ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��4��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_CheckHybridMode(
    VOS_UINT8               ucSuppNum,
    VOS_RATMODE_ENUM_UINT32 aenRatMode[VOS_RATMODE_BUTT]
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           uc1XExisted;
    VOS_UINT8                           ucHrpdExisted;

    uc1XExisted   = VOS_FALSE;
    ucHrpdExisted = VOS_FALSE;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(ucSuppNum, VOS_RATMODE_BUTT); i++)
    {
        /* ֻҪ���뼼������1X����Ϊ�ǻ��ģʽ�������Ƿ���EVDO */
        if (VOS_RATMODE_1X == aenRatMode[i])
        {
            uc1XExisted = VOS_TRUE;
        }

        if (VOS_RATMODE_HRPD == aenRatMode[i])
        {
            ucHrpdExisted = VOS_TRUE;
        }
    }

    if ((VOS_TRUE == uc1XExisted)
     && (VOS_TRUE == ucHrpdExisted))
    {
        return CNAS_HSD_SYS_MODE_HYBRID;
    }

    return CNAS_HSD_SYS_MODE_NONHYBRID;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_QRY_PrefSubnet
 ��������  : ��ѯ�����ѵ�HRPDϵͳ��������Ϣ
 �������  : pstReqMsg                  - ��������Ƶ����Ϣ����Ϣ����
             pucHrpdSysNum              - HRPDϵͳ����
             pstHrpdSysInfoList         - ���ظ���HRPDϵͳ�б�
             pfunc                      - ��ȡpri class�ĺ���ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��05��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_QRY_HrpdSysInfo(
    MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU *pstReqMsg,
    VOS_UINT8                           *pucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU         *pstHrpdSysInfoList,
    pCnasHsdGetPriClassFunc              pGetPriClassfunc
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucMatchPrio;
    VOS_UINT16                          usMatchedSysIndex;
    VOS_UINT8                           ucSysNum;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstTmpSysRecord;
    CNAS_PRL_HRPD_SYSTEM_STRU           stHrpdSys;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysList;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pst1xSysInfo;

    ucSysNum        = 0;
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();
    enModeType      = CNAS_HSD_GetModeType();
    pstHrpdSysList  = CNAS_HSD_GetSysRecListAddr();

    *pucHrpdSysNum = CNAS_MIN(pstReqMsg->ucHrpdSysNum, MSCC_HSD_BG_HRPD_MAX_SYS_NUM);

    /* ���ϵͳ�� */
    CNAS_HSD_InitSysRecList(CNAS_HSD_INIT_CTX_BUILD_FREQ, CNAS_HSD_GetSysRecListAddr());

    /* ����EVDO LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstHrpdSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_QRY_HrpdSysInfo: create hrpd list fail!");

        CNAS_HSD_Set_HrpdSysInfo_Invalid(pstHrpdSysInfoList, *pucHrpdSysNum);
        return;
    }

    /* ���avoid list�е��ڵ�Ƶ�㣬���ڵ���Ҫɾ�� */
    CNAS_HSD_CheckExpiredFreqFromAvoidList();

    for (i = 0; i < *pucHrpdSysNum; i++)
    {
        stHrpdSys.stFreq.enBandClass    =   pstReqMsg->astHrpdSysList[i].usBandClass;
        stHrpdSys.stFreq.usChannel      =   pstReqMsg->astHrpdSysList[i].usFreq;
        stHrpdSys.ucSubnetMask          =   CNAS_PRL_MAX_SUBNET_LEN_IN_BITS;

        PS_MEM_CPY(stHrpdSys.aucSubnet,
                   pstReqMsg->astHrpdSysList[i].aucSubnetId,
                   CNAS_PRL_BYTES_IN_SUBNET);

        if (VOS_TRUE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(&stHrpdSys, &ucMatchPrio, &usMatchedSysIndex))
        {
            pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(pstHrpdSysList->pstHrpdSysItem[usMatchedSysIndex].usSysIndex);

            if (VOS_NULL_PTR == pstTmpSysRecord)
            {
                /* ����Ϊ��Чֵ */
                CNAS_HSD_Set_HrpdSysInfo_Invalid(&pstHrpdSysInfoList[ucSysNum], 1);

                PS_MEM_CPY(&(pstHrpdSysInfoList[ucSysNum].stHrpdSysList),
                       &(pstReqMsg->astHrpdSysList[i]),
                       sizeof(MSCC_HSD_HRPD_SYS_STRU));

                ucSysNum++;
                if (ucSysNum >= MSCC_HSD_BG_HRPD_MAX_SYS_NUM)
                {
                    break;
                }

                continue;
            }

            pstHrpdSysInfoList[ucSysNum].enPrefNegSys       = pstTmpSysRecord->enPrefNegSys;
            pstHrpdSysInfoList[ucSysNum].enPriClass         = pGetPriClassfunc(&stHrpdSys);
            pstHrpdSysInfoList[ucSysNum].ucIsAvoided        = (VOS_UINT8)CNAS_HSD_IsCurFreqAvoided(&(stHrpdSys.stFreq));
            pstHrpdSysInfoList[ucSysNum].ucIsExistedInPrl   = VOS_TRUE;
            pstHrpdSysInfoList[ucSysNum].stHrpdSysItem.usAcqIndex   = pstTmpSysRecord->usAcqIndex;
            pstHrpdSysInfoList[ucSysNum].stHrpdSysItem.usSysIndex   = pstHrpdSysList->pstHrpdSysItem[usMatchedSysIndex].usSysIndex;
            pstHrpdSysInfoList[ucSysNum].stHrpdSysItem.ucPrioLevel  = ucMatchPrio;
            pstHrpdSysInfoList[ucSysNum].stHrpdSysItem.enPrefNegSys = pstTmpSysRecord->enPrefNegSys;

            PS_MEM_CPY(&(pstHrpdSysInfoList[ucSysNum].stHrpdSysList),
                       &(pstReqMsg->astHrpdSysList[i]),
                       sizeof(MSCC_HSD_HRPD_SYS_STRU));

            ucSysNum++;

            if (ucSysNum >= MSCC_HSD_BG_HRPD_MAX_SYS_NUM)
            {
                break;
            }

        }
        else
        {
            /* ����Ϊ��Чֵ */
            CNAS_HSD_Set_HrpdSysInfo_Invalid(&pstHrpdSysInfoList[ucSysNum], 1);

            PS_MEM_CPY(&(pstHrpdSysInfoList[ucSysNum].stHrpdSysList),
                       &(pstReqMsg->astHrpdSysList[i]),
                       sizeof(MSCC_HSD_HRPD_SYS_STRU));

            ucSysNum++;
            if (ucSysNum >= MSCC_HSD_BG_HRPD_MAX_SYS_NUM)
            {
                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Set_HrpdSysInfo_Invalid
 ��������  : ��HRPDϵͳ����Ϣ��Ϊ��Ч
 �������  : pstHrpdSysInfo                  - �����ϵͳ����
             ucSysNum                        - ϵͳ����

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��05��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_Set_HrpdSysInfo_Invalid(
    MSCC_HSD_HRPD_SYS_INFO_STRU        *pstHrpdSysInfo,
    VOS_UINT8                           ucSysNum
)
{
    VOS_UINT8                           i;

    /* ȫ����Ϊ��Чֵ */
    for (i = 0; i < ucSysNum; i++)
    {
        pstHrpdSysInfo[i].enPrefNegSys       = CNAS_PRL_PREF_NEG_SYS_NEG;
        pstHrpdSysInfo[i].enPriClass         = MSCC_HSD_PRI_CLASS_ENUM_BUTT;
        pstHrpdSysInfo[i].ucIsAvoided        = VOS_TRUE;
        pstHrpdSysInfo[i].ucIsExistedInPrl   = VOS_FALSE;
        pstHrpdSysInfo[i].stHrpdSysItem.usAcqIndex   = 0xFFFF;
        pstHrpdSysInfo[i].stHrpdSysItem.usSysIndex   = 0xFFFF;
        pstHrpdSysInfo[i].stHrpdSysItem.ucPrioLevel  = CNAS_PRL_PRIO_LEVEL_BUTT;
        pstHrpdSysInfo[i].stHrpdSysItem.enPrefNegSys = CNAS_PRL_PREF_NEG_SYS_NEG;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPriClassWithTypeAI
 ��������  : ϵͳ����ΪCDMA2000_AI������פ��Ƶ���PRI CLASS
 �������  : pstHrpdSys                 - פ����Ƶ��
 �������  : PRI CLASS
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
MSCC_HSD_PRI_CLASS_ENUM_UINT8 CNAS_HSD_GetPriClassWithTypeAI(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    VOS_UINT8                           ucMatchPrio;
    VOS_UINT16                          usMatchedSysIndex;
    MSCC_HSD_PRI_CLASS_ENUM_UINT8       enPriClass;

    enPriClass = MSCC_HSD_PRI_CLASS_ENUM_BUTT;

    if (VOS_TRUE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(pstHrpdSys, &ucMatchPrio, &usMatchedSysIndex))
    {
         /* �������ȼ�����Pri_class */
        CNAS_HSD_SetPriClass(ucMatchPrio,
                             CNAS_PRL_PRIO_LEVEL_1,
                             CNAS_PRL_PRIO_LEVEL_2,
                             &enPriClass);
    }

    return enPriClass;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPriClassWithTypeHRPD
 ��������  : ϵͳ����ΪCDMA2000_HRPD������פ��Ƶ���PRI CLASS
 �������  : pstHrpdSys                 - פ����Ƶ��
 �������  : PRI CLASS
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
MSCC_HSD_PRI_CLASS_ENUM_UINT8 CNAS_HSD_GetPriClassWithTypeHRPD(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    VOS_UINT8                           ucMatchPrio;
    VOS_UINT16                          usMatchedSysIndex;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstTmpSysRecord;
    VOS_INT16                           i;
    VOS_UINT16                          usFirstIndexInGeo;
    MSCC_HSD_PRI_CLASS_ENUM_UINT8       enPriClass;
    CNAS_HSD_QRY_HRPDSYSINFO_CTRL_STRU  stQryCtrl;
    VOS_UINT16                          usSysIndex;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysList;

    PS_MEM_SET(&stQryCtrl, 0, sizeof(CNAS_HSD_QRY_HRPDSYSINFO_CTRL_STRU));

    stQryCtrl.ucCurPrioLvl    = CNAS_PRL_PRIO_LEVEL_1;
    stQryCtrl.ucFirstPrioLvl  = CNAS_PRL_PRIO_LEVEL_1;
    stQryCtrl.ucSecondPrioLvl = CNAS_PRL_PRIO_LEVEL_2;

    usFirstIndexInGeo   = 0xFFFF;
    enPriClass          = MSCC_HSD_PRI_CLASS_ENUM_BUTT;
    pstHrpdSysList      = CNAS_HSD_GetSysRecListAddr();


    if (VOS_TRUE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(pstHrpdSys, &ucMatchPrio, &usMatchedSysIndex))
    {
        if (CNAS_PRL_PRIO_LEVEL_1 == ucMatchPrio)
        {
            return MSCC_HSD_PRI_CLASS_HOME;
        }

        usSysIndex = pstHrpdSysList->pstHrpdSysItem[usMatchedSysIndex].usSysIndex;

        /* �ҵ�GEO����ʼλ�� */
        for (i = (VOS_INT16)usSysIndex; i >= 0; i--)
        {
            pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord((VOS_UINT16)i);

            if (VOS_NULL_PTR == pstTmpSysRecord)
            {
                CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_Get_PriClass_HRPD: Get SysRecord is Null,i is", i);

                return MSCC_HSD_PRI_CLASS_ENUM_BUTT;
            }

            if (CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
            {
                usFirstIndexInGeo = (VOS_UINT16)i;
                break;
            }
        }

        /* ����most��second preferred�����ȼ� */
        for (; usFirstIndexInGeo <= usSysIndex; usFirstIndexInGeo++)
        {
            pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(usFirstIndexInGeo);

            if (VOS_NULL_PTR == pstTmpSysRecord)
            {
                CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_Get_PriClass_HRPD: Get SysRecord is Null,usFirstIndexInGeo is", usFirstIndexInGeo);

                return MSCC_HSD_PRI_CLASS_ENUM_BUTT;
            }

            /* �������ȼ���Ϣ */
            CNAS_HSD_UpdatePrioLvl(MSCC_HSD_SYS_TYPE_CDMA2000_HRPD,
                                   pstTmpSysRecord,
                                   &stQryCtrl);
        }

        /* �������ȼ�����Pri_class */
        CNAS_HSD_SetPriClass(ucMatchPrio,
                             stQryCtrl.ucFirstPrioLvl,
                             stQryCtrl.ucSecondPrioLvl,
                             &enPriClass);

    }

    return enPriClass;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetPriolvl
 ��������  : ����GEO��Ϣ����ϵͳ�����ȼ�
 �������  : enSysType                  - ��ǰ�����ϵͳ���ͣ�HPRD����AI
             enRecordType               - HRPDϵͳ���е����ͣ�HRPD����1x
             enPriInd                   - ���ȼ���more ���� same
 �������  : pstQryCtrl                 - �����PrioLvl
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��04��11��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdatePrioLvl(
    MSCC_HSD_SYS_TYPE_ENUM_UINT8                            enSysType,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord,
    CNAS_HSD_QRY_HRPDSYSINFO_CTRL_STRU                     *pstQryCtrl
)
{
    /* ���ȼ���ǰһ���� */
    if (VOS_TRUE == pstQryCtrl->ucPriMore)
    {
        pstQryCtrl->ucCurPrioLvl++;
        pstQryCtrl->ucPriMore = VOS_FALSE;
    }

    /* ����second preferred */
    if ((VOS_TRUE  == pstQryCtrl->ucFirstPriSetFlag)
     && (VOS_FALSE == pstQryCtrl->ucSecondPriSetFlag))
    {
        CNAS_HSD_SetPriorityWithCurrent(enSysType,
                                        pstSysRecord,
                                        pstQryCtrl->ucCurPrioLvl,
                                        &(pstQryCtrl->ucSecondPrioLvl),
                                        &(pstQryCtrl->ucSecondPriSetFlag));

    }

    /* ����most preferred */
    if (VOS_FALSE == pstQryCtrl->ucFirstPriSetFlag)
    {
         CNAS_HSD_SetPriorityWithCurrent(enSysType,
                                         pstSysRecord,
                                         pstQryCtrl->ucCurPrioLvl,
                                         &(pstQryCtrl->ucFirstPrioLvl),
                                         &(pstQryCtrl->ucFirstPriSetFlag));

    }

    if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
    {
        pstQryCtrl->ucPriMore = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetPriorityWithCurrent
 ��������  : ����ϵͳ�����ȼ�
 �������  : enSysType                  - ��ǰ�����ϵͳ���ͣ�HPRD����AI
             enRecordType               - HRPDϵͳ���е����ͣ�HRPD����1x
             ucCurPriolvl               - ��ǰ��Priority
 �������  : ucPriolvl                  - �����Priority
             ucPriolvlFlag              - ���ȼ����ñ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��04��11��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetPriorityWithCurrent(
    MSCC_HSD_SYS_TYPE_ENUM_UINT8        enSysType,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord,
    VOS_UINT8                           ucCurPriolvl,
    VOS_UINT8                          *ucPriolvl,
    VOS_UINT8                          *ucPriolvlFlag
)
{
    if (MSCC_HSD_SYS_TYPE_CDMA2000_AI == enSysType)
    {
       *ucPriolvl       = ucCurPriolvl;
       *ucPriolvlFlag   = VOS_TRUE;
    }
    else
    {
        if (VOS_TRUE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
        {
            *ucPriolvl       = ucCurPriolvl;
            *ucPriolvlFlag   = VOS_TRUE;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetPriolvl
 ��������  : ����ϵͳ��Pri_class
 �������  : ucCurPrioLvl               - ��ǰPrioLvl
             ucFirstPriolvl             - ������ȼ�
             ucSecondPriolvl            - �θ����ȼ�
 �������  : ucPriClass                 - �����PriClass
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      : ����
  1.��    ��   : 2015��04��11��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetPriClass(
    VOS_UINT8                           ucCurPrioLvl,
    VOS_UINT8                           ucFirstPriolvl,
    VOS_UINT8                           ucSecondPriolvl,
    MSCC_HSD_PRI_CLASS_ENUM_UINT8      *ucPriClass
)
{
    if (ucCurPrioLvl == ucFirstPriolvl)
    {
        *ucPriClass = MSCC_HSD_PRI_CLASS_HOME;
    }
    else if (ucCurPrioLvl == ucSecondPriolvl)
    {
        *ucPriClass = MSCC_HSD_PRI_CLASS_PREF;
    }
    else
    {
        *ucPriClass = MSCC_HSD_PRI_CLASS_ANY;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_BuildHrpdScanList_HighPriority
 ��������  : ������HRPD��CAS����Ƶ��ʱ�����������б�
 �������  : enSysAcqScene - ���񳡾�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��04��13��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildHrpdScanList_CasReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();

    /* ���ϵͳ��������� */
    CNAS_HSD_InitSysRecList(CNAS_HSD_INIT_CTX_BUILD_FREQ, CNAS_HSD_GetSysRecListAddr());
    CNAS_HSD_InitScanChanList(CNAS_HSD_INIT_CTX_BUILD_FREQ, CNAS_HSD_GetScanFreqListAddr());

    /* ��Ҫ���ǹ�����Ҳ�·�����˰��շǻ��ģʽ����EVOD LIST */
    if (VOS_FALSE == CNAS_HSD_CreateAllHrpdSysRecs(CNAS_PRL_NO_CHECK_ASSN_INCL, CNAS_PRL_SORT_NEEDED, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildHrpdScanList_CasReq: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* ����SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildHrpdScanList_CasReq: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ConvertLmmPlmnToGUNasPlmn
 ��������  : ��ָ��������LMM��PLMNת��ΪGUnas��ʽ��plmn
 �������  : VOS_UINT32                          ulLmmPlmnNum
              MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn
              MMC_PLMN_ID_STRU                   *pstGUNasPlmn
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��20��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    CNAS_CAS_HRPD_PLMN_STRU            *pstLmmPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstGUNasPlmn
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulLmmPlmnNum ; i++  )
    {
        CNAS_HSD_ConvertPlmnToNasPLMN( &(pstLmmPlmn[i]), &(pstGUNasPlmn[i]) );
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ConvertPlmnToNasPLMN
 ��������  : �������ѵõ���3�ֽڸ�ʽPLMNת��ΪMCC��MNC�ֿ��ĸ�ʽ
 �������  : aucEFplmn[3]
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_ID_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��20��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_HSD_ConvertPlmnToNasPLMN(
    CNAS_CAS_HRPD_PLMN_STRU             *pstLmmPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU           *pstNasPlmn
)
{
    VOS_UINT32                          ulTempData;
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmn;

    /*
       PLMN BCD ���� ��ʽ

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = CNAS_HSD_OCTET_LOW_FOUR_BITS & (pstLmmPlmn->aucPlmnId[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (CNAS_HSD_OCTET_HIGH_FOUR_BITS & (pstLmmPlmn->aucPlmnId[0])) >> CNAS_HSD_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << CNAS_HSD_OCTET_MOVE_EIGHT_BITS;

    ulTempData = CNAS_HSD_OCTET_LOW_FOUR_BITS & (pstLmmPlmn->aucPlmnId[1]);
    stPlmn.ulMcc |= ulTempData << CNAS_HSD_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (CNAS_HSD_OCTET_HIGH_FOUR_BITS & (pstLmmPlmn->aucPlmnId[1])) >> CNAS_HSD_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << CNAS_HSD_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = CNAS_HSD_OCTET_LOW_FOUR_BITS & (pstLmmPlmn->aucPlmnId[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (CNAS_HSD_OCTET_HIGH_FOUR_BITS & (pstLmmPlmn->aucPlmnId[2])) >> CNAS_HSD_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << CNAS_HSD_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;

    return ;
}


/*lint -restore*/

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ConvertPlmnToNasPLMN
 ��������  : ��HRPD�տ���Ϣ�е�MCC��ʽת����NAS��ʽ
             �й�����HRPD����MCC - 460���տڸ�ʽ - 0x1cc��ת��֮���ʽ - 0x00000604
             ����HRPD����MCC     - 311���տڸ�ʽ - 0x137��ת��֮���ʽ - 0x00010103
 �������  : usHrpdMcc - �տڸ�ʽ��MCC
 �������  : ��
 �� �� ֵ  : NAS��ʽ��MCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��04��
   ��    ��   : y00174758
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_HSD_ConvertHrpdMccToNasMcc(
    VOS_UINT16                          usHrpdMcc
)
{
    VOS_UINT32                          ulNasMcc;

    if (usHrpdMcc > CNAS_HSD_MAX_HRPD_OTA_MCC)
    {
        return CNAS_HSD_INVALID_MCC;
    }

    ulNasMcc  = (usHrpdMcc % 1000) / 100;

    ulNasMcc += (usHrpdMcc % 10) << 16;

    ulNasMcc += ((usHrpdMcc % 100) / 10) << 8;

    return ulNasMcc;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IsHrpdSysChange
 ��������  : �Ƚ��Ƿ���ͬ��HRPDϵͳ
 �������  : pstCurrHrpdSys        ��ǰ��HRPDϵͳ
             pstLastHrpdSys        �ϴε�HRPDϵͳ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsHrpdSysChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
)
{
    if ((pstCurrHrpdSys->stFreq.enBandClass != pstLastHrpdSys->stFreq.enBandClass)
     || (pstCurrHrpdSys->stFreq.usChannel   != pstLastHrpdSys->stFreq.usChannel))
    {
        return VOS_TRUE;
    }

    /* �ж�subnet change */
    return CNAS_HSD_IsSubnetIdChange(pstCurrHrpdSys, pstLastHrpdSys);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcessCTCCCustomize
 ��������  : �����й����Ŷ���(Ĭ��Ƶ������)
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��16��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_HSD_ProcessCTCCCustomize(VOS_VOID)
{
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;
    VOS_UINT8                           ucCTCCEnableFlg;

    enSsprPRev      = CNAS_PRL_GetPrlRevInfo();
    ucCTCCEnableFlg = CNAS_CCB_GetCTCCCustomizeFreqList()->ucEnableFlg;

    if ((CNAS_PRL_SSPR_P_REV_1 == enSsprPRev)
     && (VOS_TRUE == ucCTCCEnableFlg))
    {
        CNAS_HSD_SetSysModeType(CNAS_HSD_SYS_MODE_NONHYBRID);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IsMccInOperLockWhiteSidList
 ��������  : �ж�MCC�Ƿ��ڰ�������
 �������  : ulMcc
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ�ڰ�������
             VOS_FALSE  ��ʾ���ڰ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��31��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsMccInOperLockWhiteSidList(
    VOS_UINT16                          usMcc
)
{
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockWhiteSidList = VOS_NULL_PTR;
    CNAS_CCB_SYS_INFO_STRU                                 *pstSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;

    pstOperLockWhiteSidList = CNAS_CCB_GetOperLockSysWhiteList();

    enModeType              = CNAS_HSD_GetModeType();
    pst1xSysInfo            = CNAS_HSD_Get1xSystemInfo();

    /* ���ģʽ1x����ʱ������������ԣ�����Ҫ�жϰ����� */
    if ((CNAS_HSD_SYS_MODE_HYBRID     == enModeType)
     && (CNAS_HSD_1X_SYSTEM_AVAILABLE == pst1xSysInfo->enStatus))
    {
        return VOS_TRUE;
    }

    /* �����������disable��Ĭ��ϵͳ�ڰ������� */
    if (VOS_FALSE == pstOperLockWhiteSidList->ucEnable)
    {
        return VOS_TRUE;
    }

    for (i = 0; i < CNAS_MIN(pstOperLockWhiteSidList->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM); i++)
    {
        pstSysInfo = &(pstOperLockWhiteSidList->astSysInfo[i]);

        if (pstSysInfo->ulMcc == usMcc)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_Is1xNormalService
 ��������  : ��ȡ��ǰXSD����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ����������
             VOS_FALSE  ��ʾ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_Is1xNormalService(VOS_VOID)
{
    if (CNAS_CCB_SERVICE_STATUS_NORMAL_SERVICE == CNAS_CCB_GetCur1XSrvStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

