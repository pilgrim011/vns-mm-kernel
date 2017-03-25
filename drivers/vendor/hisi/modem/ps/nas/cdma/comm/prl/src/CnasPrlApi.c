/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasPrlApi.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��08����
  ��������   : NAS 1X&EVDO �ṩ����PRL API����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��06��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "CnasPrlMem.h"
#include "CnasPrlApi.h"
#include "CnasCcb.h"
#include "CnasXsdCtx.h"

#include "NasMntn.h"
#include "CnasPrlMntn.h"
#include  "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_API_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/******************************************************************************
    =============== ROAMING LIST ===============
    Roaming List Type:    IS-683C
    Preferred Only:   FALSE
    Default Roaming Indicator:  2
    Preferred List ID:    1

    =============== Acquisition Table Record ===============
    INDEX ACQ_TYPE  CH1 CH2 CH3 CH4 CH5 CH6 CH7 - - CH31
    0 1 B
    1 1 A
    2 2 B Both
    3 2 A Both
    4 10  0 283 0 691 0 384 0 777 0 779 0 738 0 486 0 568 0 40  0 1022 10 50 10 100 10 150 10 250 10 300 10 350 10 450 10 500 10 550 10 650 10 670 10 770 10 820 10 870
    5 10  1 25  1 50  1 75  1 100 1 125 1 150 1 175 1 200 1 225 1 250 1 275 1 325 1 350 1 375 1 425 1 450 1 475 1 500 1 525 1 550 1 575 1 600 1 625 1 650 1 675 1 725 1 750 1 775 1 825 1 850 1 875 1 925
    6 10  1 950 1 975 1 1000  1 1025  1 1050  1 1075  1 1100  1 1125  1 1150  1 1175
    7 10  15  25  15  50  15  75  15  100 15  125 15  150 15  175 15  225 15  250 15  275 15  300 15  325 15  350 15  375 15  425 15  450 15  475 15  525 15  550 15  575 15  625 15  650 15  675 15  725 15  750 15  775 15  800 15  825 15  850 15  875
    8 10  18  45  18  70  18  95  18  145 18  170 18  195
    9 10  19  23  19  48  19  73  19  98  19  143 19  168 19  193 19  218 19  263 19  288 19  313 19  338
    10  5 Any

    =============== System Table Record ===============
    INDEX SYS_TYPE  NEG/PREF  GEO PRI ACQ_IND ROAM_IND  ASSN INC  ASSN TAG  PN ASSN DATA ASSN SID, NID / MCC, IMSI_11_12 / SUBNETID / PLMN TYPE, PLMN, LAC
    0 0 Pref  New Same  4 0 No  0 65535
    1 0 Pref  Same  Same  5 0 No  0 65535
    2 0 Pref  Same  Same  6 0 No  0 65535
    3 0 Pref  Same  Same  7 0 No  0 65535
    4 0 Pref  Same  Same  8 0 No  0 65535
    5 0 Pref  Same  Same  9 0 No  0 65535
    6 0 Pref  Same  Same  10  2 No  0 65535
    7 0 Pref  Same  Same  2 0 No  0 65535
    8 0 Pref  Same  More  3 2 No  0 65535
    9 0 Pref  Same  Same  0 0 No  0 65535
    10  0 Pref  Same  Same  1 2 No  0 65535

******************************************************************************/
VOS_UINT8                               g_aucDefaultPrlBuffer[] =
{ 0x01, 0x4E, 0x00, 0x01, 0x03, 0x01, 0x02, 0xC0,
  0x00, 0x05, 0x80, 0x01, 0x01, 0x40, 0x01, 0x01,
  0x00, 0x02, 0x01, 0x70, 0x02, 0x01, 0x30, 0x0A,
  0x30, 0x01, 0x1B, 0x02, 0xB3, 0x01, 0x80, 0x03,
  0x09, 0x03, 0x0B, 0x02, 0xE2, 0x01, 0xE6, 0x02,
  0x38, 0x00, 0x28, 0x03, 0xFE, 0x50, 0x32, 0x50,
  0x64, 0x50, 0x96, 0x50, 0xFA, 0x51, 0x2C, 0x51,
  0x5E, 0x51, 0xC2, 0x51, 0xF4, 0x52, 0x26, 0x52,
  0x8A, 0x52, 0x9E, 0x53, 0x02, 0x53, 0x34, 0x53,
  0x66, 0x0A, 0x40, 0x08, 0x19, 0x08, 0x32, 0x08,
  0x4B, 0x08, 0x64, 0x08, 0x7D, 0x08, 0x96, 0x08,
  0xAF, 0x08, 0xC8, 0x08, 0xE1, 0x08, 0xFA, 0x09,
  0x13, 0x09, 0x45, 0x09, 0x5E, 0x09, 0x77, 0x09,
  0xA9, 0x09, 0xC2, 0x09, 0xDB, 0x09, 0xF4, 0x0A,
  0x0D, 0x0A, 0x26, 0x0A, 0x3F, 0x0A, 0x58, 0x0A,
  0x71, 0x0A, 0x8A, 0x0A, 0xA3, 0x0A, 0xD5, 0x0A,
  0xEE, 0x0B, 0x07, 0x0B, 0x39, 0x0B, 0x52, 0x0B,
  0x6B, 0x0B, 0x9D, 0x0A, 0x14, 0x0B, 0xB6, 0x0B,
  0xCF, 0x0B, 0xE8, 0x0C, 0x01, 0x0C, 0x1A, 0x0C,
  0x33, 0x0C, 0x4C, 0x0C, 0x65, 0x0C, 0x7E, 0x0C,
  0x97, 0x0A, 0x3C, 0x78, 0x19, 0x78, 0x32, 0x78,
  0x4B, 0x78, 0x64, 0x78, 0x7D, 0x78, 0x96, 0x78,
  0xAF, 0x78, 0xE1, 0x78, 0xFA, 0x79, 0x13, 0x79,
  0x2C, 0x79, 0x45, 0x79, 0x5E, 0x79, 0x77, 0x79,
  0xA9, 0x79, 0xC2, 0x79, 0xDB, 0x7A, 0x0D, 0x7A,
  0x26, 0x7A, 0x3F, 0x7A, 0x71, 0x7A, 0x8A, 0x7A,
  0xA3, 0x7A, 0xD5, 0x7A, 0xEE, 0x7B, 0x07, 0x7B,
  0x20, 0x7B, 0x39, 0x7B, 0x52, 0x7B, 0x6B, 0x0A,
  0x0C, 0x90, 0x2D, 0x90, 0x46, 0x90, 0x5F, 0x90,
  0x91, 0x90, 0xAA, 0x90, 0xC3, 0x0A, 0x18, 0x98,
  0x17, 0x98, 0x30, 0x98, 0x49, 0x98, 0x62, 0x98,
  0x8F, 0x98, 0xA8, 0x98, 0xC1, 0x98, 0xDA, 0x99,
  0x07, 0x99, 0x20, 0x99, 0x39, 0x99, 0x52, 0x05,
  0x01, 0x3C, 0x30, 0x40, 0x20, 0x00, 0x00, 0x00,
  0x30, 0x60, 0x28, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x30, 0x00, 0x00, 0x00, 0x30, 0x60, 0x38, 0x00,
  0x00, 0x00, 0x30, 0x60, 0x40, 0x00, 0x00, 0x00,
  0x30, 0x60, 0x48, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x50, 0x00, 0x00, 0x04, 0x30, 0x60, 0x10, 0x00,
  0x00, 0x00, 0x30, 0x70, 0x18, 0x00, 0x00, 0x04,
  0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x08, 0x00, 0x00, 0x04, 0x69, 0xC7};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 1 (spread rate 1)
 ****************************************************************************/
/* PCS block A prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockATab[]={
    25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275
};

/* PCS block B prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockBTab[]={
    425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675
};

/* PCS block C prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockCTab[]={
    925, 950, 975, 1000, 1025, 1050, 1075, 1100, 1125, 1150, 1175
};

/* PCS block D prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockDTab[]={
    325, 350, 375
};

/* PCS block E prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockETab[]={
    725, 750, 775
};

/* PCS block F prefered channels */
VOS_UINT16 const g_ausCnasPrlPcsBlockFTab[]={
    825, 850, 875
};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 0 (spread rate 1)
 ****************************************************************************/
CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU const g_astCnasPrlBand0Tab[] = {
    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 779, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 738, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_B, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 486, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_SYS_SEL_TYPE_B, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 568, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 40, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 1022, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN, 0, 1273, 0},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_SYS_SEL_TYPE_A, CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN, 0, 40, 0}
};

/****************************************************************************
 * CDMA Preferred Set of Frequency Assignments for Band Class 10 (spread rate 1)
 ****************************************************************************/
CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const g_astCnasPrlBand10Tab[] = {
    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 50},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 100},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_0, CNAS_PRL_BAND10_SYS_SEL_TYPE_A, 150},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 250},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 300},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_1, CNAS_PRL_BAND10_SYS_SEL_TYPE_B, 350},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 450},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 500},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_2, CNAS_PRL_BAND10_SYS_SEL_TYPE_C, 550},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_BAND10_SYS_SEL_TYPE_D, 650},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_3, CNAS_PRL_BAND10_SYS_SEL_TYPE_D, 670},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 770},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 820},

    {CNAS_PRL_BAND_SUBCLASS_TYPE_4, CNAS_PRL_BAND10_SYS_SEL_TYPE_E, 870}
};


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : CNAS_PRL_InitPrlCtx
 ��������  : ��ʼ��PRL��������Ϣ
 �������  : ulTaskInitFlag - task��ʼ����־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_InitPrlCtx(VOS_UINT32 ulTaskInitFlag)
{
    if (VOS_TRUE == ulTaskInitFlag)
    {
        /* ��ʼ��PRL������ */
        CNAS_PRL_InitMemBuff();
    }
    else
    {
        CNAS_PRL_MemFreeBuff();
    }

    /* ��ʼ��PRL�洢��Ϣ */
    CNAS_PRL_InitPrlInfo(ulTaskInitFlag);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlHeaderInfoAddr
 ��������  : ��ȡ��ǰPRL header��Ϣ�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL header��Ϣ�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_HEADER_INFO_STRU* CNAS_PRL_GetPrlHeaderInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlInfoValidFlag
 ��������  : ��ȡ��ǰPRL��Ϣ��Ч��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL��Ϣ�Ƿ���Ч��־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_GetPrlInfoValidFlag(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->ulIsPrlValid);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetDdefaultPrl
 ��������  : ��ȡdefault PRL
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����default PRL����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 *CNAS_PRL_GetDefaultPrl(VOS_VOID)
{
    return &(g_aucDefaultPrlBuffer[0]);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetDefaultPrlSize
 ��������  : ��ȡdefault PRL size
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����default PRL size
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_PRL_GetDefaultPrlSize(VOS_VOID)
{
    return sizeof(g_aucDefaultPrlBuffer);
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlAcqInfoAddr
 ��������  : ��ȡ��ǰPRL�����¼��Ϣ�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL�����¼�׵�ַ
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_ACQ_RECORD_INFO_STRU* CNAS_PRL_GetPrlAcqInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlSysInfoAddr
 ��������  : ��ȡ��ǰPRLϵͳ��Ϣ�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRLϵͳ��Ϣ�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_SYS_RECORD_INFO_STRU* CNAS_PRL_GetPrlSysInfoAddr(VOS_VOID)
{
    return &(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlAcqRecordNum
 ��������  : ��ȡ��ǰPRL�����¼��Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL�����¼��Ŀ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_PRL_GetPrlAcqRecordNum(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.usAcqRecordNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlRevInfo
 ��������  : ��ȡ��ǰPRL�汾��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL header��Ϣ�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_SSPR_P_REV_ENUM_UINT8 CNAS_PRL_GetPrlRevInfo(VOS_VOID)
{
    return (CNAS_PRL_GetPrlHeaderInfoAddr()->enSsprPRev);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_SetPrlRevInfo
 ��������  : ���õ�ǰPRL�汾��Ϣ
 �������  : enSsprPRev -- PRL�汾
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��21��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_SetPrlRevInfo(
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev
)
{
    CNAS_PRL_GetPrlHeaderInfoAddr()->enSsprPRev = enSsprPRev;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetSpecifiedPrlAcqRecord
 ��������  : ��ȡָ��PRL�����¼��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ��PRL�����¼��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlAcqRecord(VOS_UINT16 usIndex)
{
    if ((usIndex < CNAS_PRL_GetPrlAcqRecordNum()) && (usIndex < CNAS_PRL_ACQ_RECORD_MAX_NUM))
    {
        return (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.pastPrlAcqRecord[usIndex]);

    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlSysRecordNum
 ��������  : ��ȡ��ǰPRLϵͳ��¼��Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRLϵͳ��¼��Ŀ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_PRL_GetPrlSysRecordNum(VOS_VOID)
{
    return (CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.usSysRecordNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetSpecifiedPrlSysRecord
 ��������  : ��ȡָ��PRLϵͳ��¼��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ��PRLϵͳ��¼��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlSysRecord(VOS_UINT16 usIndex)
{
    /* ������� */
    if ((usIndex < CNAS_PRL_GetPrlSysRecordNum()) && (usIndex < CNAS_PRL_SYS_RECORD_MAX_NUM))
    {
        /* ��ת��ָ��������ϵͳ��¼��ַ */
        return (CNAS_PRL_EXT_SYS_RECORD_STRU *)(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.pstSysRecord + usIndex);
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_InitPrlHeaderInfo
 ��������  : ��ʼ��PRLͷ��Ϣ
 �������  : pstPrlHeader -- ָ��PRLͷ��ַ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_InitPrlHeaderInfo(
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeader
)
{
    /* ��ʼ��PRL ͷ��Ϣ */
    NAS_MEM_SET_S(pstPrlHeader, sizeof(CNAS_PRL_HEADER_INFO_STRU), 0, sizeof(CNAS_PRL_HEADER_INFO_STRU));

    pstPrlHeader->enDefRoamInd = CNAS_PRL_SYS_ROAMING_STATUS_RESERVED;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_InitPrlAcqInfo
 ��������  : ��ʼ��PRL�����¼��Ϣ
 �������  : pstPrlAcqInfo -- ָ��PRL�����¼�׵�ַ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_InitPrlAcqInfo(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstPrlAcqInfo
)
{
    VOS_UINT16                          i;

    /* ��ʼ��PRL�����¼��Ϣ */
    NAS_MEM_SET_S(pstPrlAcqInfo, sizeof(CNAS_PRL_ACQ_RECORD_INFO_STRU), 0, sizeof(CNAS_PRL_ACQ_RECORD_INFO_STRU));

    for (i = 0; i < CNAS_PRL_ACQ_RECORD_MAX_NUM; i++)
    {
        pstPrlAcqInfo->pastPrlAcqRecord[i] = VOS_NULL_PTR;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_FreeMccRec
 ��������  : �ͷ�PRLϵͳ����MCC-MNC��¼���ڴ�
 �������  : pstPrlSysInfo -- ָ��PRLϵͳ��¼�׵�ַ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��18��
   ��    ��   : x00306642
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_FreeMccRec(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo
)
{
    VOS_UINT32                          ulIndex;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    for (ulIndex = 0; ulIndex < pstPrlSysInfo->usSysRecordNum; ulIndex++)
    {
        pstSysRecord = &(pstPrlSysInfo->pstSysRecord[ulIndex]);

        if ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED      == pstSysRecord->enRecordType)
         && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType))
        {
            if (VOS_NULL_PTR != pstSysRecord->u.stMccMncId.u.pstSubnetId)
            {
                PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord->u.stMccMncId.u.pstSubnetId);
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_InitPrlSysInfo
 ��������  : ��ʼ��PRL��ȡ��¼��Ϣ
 �������  : pstPrlSysInfo -- ָ��PRLϵͳ��¼�׵�ַ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_InitPrlSysInfo(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo,
    VOS_UINT32                          ulTaskInitFlag
)
{
    if ((VOS_FALSE    == ulTaskInitFlag)
     && (VOS_NULL_PTR != pstPrlSysInfo->pstSysRecord))
    {
        CNAS_PRL_FreeMccRec(pstPrlSysInfo);

        PS_MEM_FREE(UEPS_PID_XSD, pstPrlSysInfo->pstSysRecord);
    }

    /* ��ʼ��PRLϵͳ��¼��Ϣ */
    NAS_MEM_SET_S(pstPrlSysInfo, sizeof(CNAS_PRL_SYS_RECORD_INFO_STRU), 0, sizeof(CNAS_PRL_SYS_RECORD_INFO_STRU));

    pstPrlSysInfo->pstSysRecord = VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_InitPrlInfo
 ��������  : ��ʼ��PRL
 �������  : ulTaskInitFlag - task��ʼ����־
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_InitPrlInfo(VOS_UINT32 ulTaskInitFlag)
{
    CNAS_PRL_INFO_STRU                  *pstPrlInfo = VOS_NULL_PTR;

    pstPrlInfo = CNAS_PRL_GetPrlInfoAddr();

    pstPrlInfo->ulIsPrlValid = VOS_FALSE;

    CNAS_PRL_InitPrlHeaderInfo(&(pstPrlInfo->stPrlHeader));

    CNAS_PRL_InitPrlAcqInfo(&(pstPrlInfo->stPrlAcqInfo));

    CNAS_PRL_InitPrlSysInfo(&(pstPrlInfo->stPrlSysInfo), ulTaskInitFlag);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ProcPrlInfo
 ��������  : ����PRL������Ϣ
 �������  : pucSrc   -- prlԭʼ���ݵ�ַ
             usSrcLen -- ���ݳ���
             enPrlRev -- �汾

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- PRL�����ɹ�
             VOS_FALSE -- PRL����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ProcPrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    VOS_UINT32                          ulRslt;

    if ((CNAS_PRL_SSPR_P_REV_3 != enPrlRev)
     && (CNAS_PRL_SSPR_P_REV_1 != enPrlRev))
    {
        /* PRL���ݳ����뷵�ص��ļ����Ȳ�ƥ�� */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: enPrlRev is not supported!");

        return VOS_FALSE;
    }

    /* ����PRL��Ҫʹ�õ��ڴ� */
    CNAS_PRL_MallocMemBuff();

    if (CNAS_PRL_SSPR_P_REV_3 == enPrlRev)
    {
        ulRslt = CNAS_PRL_ParseEprlBitStream(pucSrc, usSrcLen);
    }
    else
    {
        ulRslt = CNAS_PRL_ParsePrlBitStream(pucSrc, usSrcLen);
    }

    /* �������ʧ�ܣ��ͷ��ϴη�����ڴ� */
    if (VOS_FALSE == ulRslt)
    {
        CNAS_PRL_InitPrlCtx(VOS_FALSE);
    }

    return ulRslt;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapStandardBand0SubClassToChannel
 ��������  : ����C.S0057,��Band0�е�SYS A/Bת���ɶ�Ӧ��channel
 �������  : enBandSubClass - Band SubClass
             enSysSelType   - System Designator
             enStandChanSelType - primary����secondary
 �������  : pusChannel - ��Ӧ��Ƶ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��14��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_PRL_MapStandardBand0SubClassToChannel(
    CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8                  enBandSubClass,
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType,
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enStandChanSelType,
    VOS_UINT16                                             *pusChannel
)
{
    VOS_UINT16                                              i;
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan = VOS_NULL_PTR;

    if (CNAS_PRL_BAND_SUBCLASS_TYPE_0 == enBandSubClass)
    {
        pstCdmaStandardChan = CNAS_CCB_GetCdmaStandardChannels();

        if (CNAS_PRL_SYS_SEL_TYPE_A == enSysSelType)
        {
            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usPrimaryA;

                return;
            }

            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usSecondaryA;

                return;
            }
        }

        if (CNAS_PRL_SYS_SEL_TYPE_B == enSysSelType)
        {
            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usPrimaryB;

                return;
            }

            if (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enStandChanSelType)
            {
                *pusChannel = pstCdmaStandardChan->usSecondaryB;

                return;
            }
        }

        return;
    }

    /* ����g_aucCnasPrlBand0Tab���е���Ϣ�����ض�Ӧ��Ƶ����Ϣ */
    for (i = 0; i<(sizeof(g_astCnasPrlBand0Tab)/sizeof(CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU)); i++)
    {
        if ((enBandSubClass == g_astCnasPrlBand0Tab[i].enSubclass)
         && (enSysSelType == g_astCnasPrlBand0Tab[i].enSysType)
         && (enStandChanSelType == g_astCnasPrlBand0Tab[i].enChanType))
        {
            *pusChannel = g_astCnasPrlBand0Tab[i].usChan;
        }
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel
 ��������  : ��Cellular CDMA (Standard Channels) Acquisition Record��Sys A��
             ��Ϣ��ת����band��channel number
 �������  : pstCellularStandardSys - Cellular CDMA (Standard Channels)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_2,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_3,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;
    }

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_2,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_3,
                                                   CNAS_PRL_SYS_SEL_TYPE_A,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;
    }


}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel
 ��������  : ��Cellular CDMA (Standard Channels) Acquisition Record��SYS B��
             ��Ϣ��ת����band��channel number
 �������  : pstCellularStandardSys - Cellular CDMA (Standard Channels)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

    }

    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN == enChanSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN == enChanSelType))
    {
        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_0,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

        pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        CNAS_PRL_MapStandardBand0SubClassToChannel(CNAS_PRL_BAND_SUBCLASS_TYPE_1,
                                                   CNAS_PRL_SYS_SEL_TYPE_B,
                                                   CNAS_PRL_STANDARD_CHAN_SEL_TYPE_SEC_CDMA_CHAN,
                                                   &pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum].usChannel);
        pstFreqInfo->ulNum++;

    }


}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCellularCdmaStandardToBandChannel
 ��������  : ��Cellular CDMA (Standard Channels) Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstCellularStandardSys - Cellular CDMA (Standard Channels)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapCellularCdmaStandardToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU    *pstCellularStandardSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    /*
      For band class 0 only, the actual CDMA channels come from NV-RAM1 and,
      as may have already been deduced from the tables above, there are four
      such channels, namely, primary-A, primary-B, secondary-A, and secondary-B.
      These channels are programmed into NV by the operator (or specified by the
      operator to the manufacturer in the Product Release Information (PRI)).
      Band            Standard Channel        Channel Number
      A               Primary                 283
                      Secondary               691
      B               Primary                 384
                      Secondary               777
     */

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 0�ĳ��������band������д��band 0*/
    pstFreqInfo->ulNum = 0;

    /* ��������쳣������SYS A/Bϵͳ��ֱ�ӷ��أ���ʱ����Ϊ0 */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstCellularStandardSys->enSysSelType)
      ||(pstCellularStandardSys->enSysSelType > CNAS_PRL_SYS_SEL_TYPE_A_OR_B))
    {
        return;
    }

    /* ��������쳣������Primary��Secondary��ֱ�ӷ��أ���ʱ����Ϊ0 */
    if ((CNAS_PRL_STANDARD_CHAN_SEL_TYPE_RESERVED == pstCellularStandardSys->enChanSelType)
      ||(pstCellularStandardSys->enChanSelType > CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN))
    {
        return;
    }

    /* ת��SYS A��band��channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_A == pstCellularStandardSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularStandardSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(pstCellularStandardSys->enChanSelType,
                                                          pstFreqInfo);
    }

    /* ת��SYS B��band��channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_B == pstCellularStandardSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularStandardSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(pstCellularStandardSys->enChanSelType,
                                                          pstFreqInfo);
    }

}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCellularCdmaCustomToBandChannel
 ��������  : ��Cellular CDMA (Custom Channels) Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstCelluarCustomSys - Cellular CDMA (Custom Channels)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapCellularCdmaCustomToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU      *pstCelluarCustomSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT32                          i;

    /*
    This acquisition record is used to search for CDMA service in band class 0
    (800 MHz cellular frequency band) on a list (up to 32) of specific channels.
    */

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 0�ĳ�����band������д��band 0��channelֱ����д */

    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstCelluarCustomSys->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_0;
        pstFreqInfo->astFreqInfo[i].usChannel = pstCelluarCustomSys->ausChan[i];
    }
    pstFreqInfo->ulNum = pstCelluarCustomSys->ucNumOfChans;

}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCellularCdmaPreferToBandChannel
 ��������  : ��Cellular CDMA Preferred Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstCellularPreSys - Cellular CDMA Preferred��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapCellularCdmaPreferToBandChannel(
    CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU    *pstCellularPreSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    /*
    This record is used to instruct the mobile device to search, in band
    class 0, for CDMA service first (on the standard channels in a particular
    band); and, if no CDMA service is found, to look for AMPS Cellular service
    in the same band.

    This channel editor field is known in the standards as the 'PRI_SEC 'field
    and can take one of three legal values.
    (���ﰴ��Primary��Secondary��֧��������)

    Band            Standard Channel        Channel Number
    A               Primary                 283
                    Secondary               691
    B               Primary                 384
                    Secondary               777
    */

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 0�ĳ��������band������д��band 0*/

    pstFreqInfo->ulNum = 0;

    /* ��������쳣������SYS A/Bϵͳ��ֱ�ӷ��أ���ʱ����Ϊ0 */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstCellularPreSys->enSysSelType)
      ||(pstCellularPreSys->enSysSelType > CNAS_PRL_SYS_SEL_TYPE_A_OR_B))
    {
        return;
    }


    /* ת��SYS A��band��channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_A == pstCellularPreSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularPreSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN,
                                                          pstFreqInfo);
    }

    /* ת��SYS B��band��channel */
    if ((CNAS_PRL_SYS_SEL_TYPE_B == pstCellularPreSys->enSysSelType)
     || (CNAS_PRL_SYS_SEL_TYPE_A_OR_B == pstCellularPreSys->enSysSelType))
    {
        CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(CNAS_PRL_STANDARD_CHAN_SEL_TYPE_PRI_OR_SEC_CDMA_CHAN,
                                                          pstFreqInfo);
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockAToBandChannel
 ��������  : ��PCS CDMA Block A�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockAToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockATab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockATab[i];
        }
        pstFreqInfo->ulNum = i;

    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockBToBandChannel
 ��������  : ��PCS CDMA Block B�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockBToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockBTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockBTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockCToBandChannel
 ��������  : ��PCS CDMA Block C�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockCToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockCTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockCTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockDToBandChannel
 ��������  : ��PCS CDMA Block D�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockDToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockDTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockDTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockEToBandChannel
 ��������  : ��PCS CDMA Block E�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockEToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockETab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockETab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockFToBandChannel
 ��������  : ��PCS CDMA Block F�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockFToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ��ǰֻ֧��CNAS_SPREADING_RATE_1��ĿǰоƬ������㶼����֧��CNAS_SPREADING_RATE_3 */

    pstFreqInfo->ulNum = 0;
    if (CNAS_SPREADING_RATE_1 == enSpreadingRate)
    {
        for (i = 0; i < (sizeof(g_ausCnasPrlPcsBlockFTab)/sizeof(VOS_UINT16)); i++)
        {
            pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
            pstFreqInfo->astFreqInfo[i].usChannel = g_ausCnasPrlPcsBlockFTab[i];
        }
        pstFreqInfo->ulNum = i;

    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsBlockAnyToBandChannel
 ��������  : ��PCS CDMA Block Any�е���Ϣ��ת����band��channel number
 �������  : enSpreadingRate - Spreading Rate����
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsBlockAnyToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stTmpFreqInfo;

    pstFreqInfo->ulNum = 0;

    CNAS_PRL_MapPcsBlockAToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockBToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockCToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockDToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockEToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;

    CNAS_PRL_MapPcsBlockFToBandChannel(enSpreadingRate, &stTmpFreqInfo);
    NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                  stTmpFreqInfo.astFreqInfo,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
    pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;



}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_TransBlockTypeToBlockTypeFlag
 ��������  : ��PCS CDMA (Using Blocks) Acquisition Record�е�
             Block Type��Ϣ��ת���ɶ�Ӧ��Block Type Flag
 �������  : pstPcsBlocksSys - PCS CDMA (Using Blocks)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32 CNAS_PRL_TransBlockTypeToBlockTypeFlag(
    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8           enBlockType
)
{
    switch (enBlockType)
    {
        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_A:
            return CNAS_PRL_MAP_PCS_BLOCK_A_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_B:
            return CNAS_PRL_MAP_PCS_BLOCK_B_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_C:
            return CNAS_PRL_MAP_PCS_BLOCK_C_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_D:
            return CNAS_PRL_MAP_PCS_BLOCK_D_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_E:
            return CNAS_PRL_MAP_PCS_BLOCK_E_FLG;

        case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_F:
            return CNAS_PRL_MAP_PCS_BLOCK_F_FLG;

        default:
            return CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;
    }
}
/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsCdmaBlockToBandChannel
 ��������  : ��PCS CDMA (Using Blocks) Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstPcsBlocksSys - PCS CDMA (Using Blocks)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsCdmaBlockToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU           *pstPcsBlocksSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stTmpFreqInfo;
    CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32                  enMapPcsBlockFlg;
    CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32                  enTmpMapPcsBlockFlg;

    /*
     This record is used to instruct the mobile device to look for CDMA service
     on the channels listed in band class 1 (1900 MHz PCS frequencies).
     */

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 1�ĳ�����band������д��band 1��channel ����PCS�Ķ���ת������д */

    pstFreqInfo->ulNum      = 0;
    stTmpFreqInfo.ulNum     = 0;
    enMapPcsBlockFlg        = CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;
    enTmpMapPcsBlockFlg     = CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG;


    for (i = 0; i < pstPcsBlocksSys->ucNumOfBlocks; i++)
    {
        /* Ϊ��ֹAcq Record�����ظ�ת��������ظ����ֵ�block������ת�����ŵ�Ƶ���� */
        enTmpMapPcsBlockFlg = CNAS_PRL_TransBlockTypeToBlockTypeFlag(pstPcsBlocksSys->aenBlock[i]);
        {
            /* ����Ѿ����������ֱ��continue */
            if ((enTmpMapPcsBlockFlg != CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG)
             && (enTmpMapPcsBlockFlg == (enTmpMapPcsBlockFlg & enMapPcsBlockFlg)))
            {
                continue;
            }
        }

        switch (pstPcsBlocksSys->aenBlock[i])
        {
            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_A:
                CNAS_PRL_MapPcsBlockAToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_A_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_B:
                CNAS_PRL_MapPcsBlockBToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_B_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_C:
                CNAS_PRL_MapPcsBlockCToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_C_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_D:
                CNAS_PRL_MapPcsBlockDToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_D_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_E:
                CNAS_PRL_MapPcsBlockEToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_E_FLG;
                break;

            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_F:
                CNAS_PRL_MapPcsBlockFToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_F_FLG;
                break;

            /* Ϊ�������Ա����������ʱ��any ���ͣ���ǰ���Ѿ���д��������block����ɾ����֮ǰ�ĸ�ֵ�����¸�ֵ */
            case CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ANY_BLOCK:
                pstFreqInfo->ulNum = 0;
                CNAS_PRL_MapPcsBlockAnyToBandChannel(CNAS_SPREADING_RATE_1, &stTmpFreqInfo);
                enMapPcsBlockFlg |= CNAS_PRL_MAP_PCS_BLOCK_ANY_FLG;
                break;

            default:
                CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_MapPcsCdmaBlockToBandChannel():Wrong  block Type");
                break;
        }

        if (0 != stTmpFreqInfo.ulNum)
        {
            NAS_MEM_CPY_S(&pstFreqInfo->astFreqInfo[pstFreqInfo->ulNum],
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM - pstFreqInfo->ulNum),
                          stTmpFreqInfo.astFreqInfo,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)*stTmpFreqInfo.ulNum);
            pstFreqInfo->ulNum += stTmpFreqInfo.ulNum;
        }
        stTmpFreqInfo.ulNum = 0;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapPcsCdmaChannelToBandChannel
 ��������  : ��PCS CDMA (Using Channels) Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstPcsChannelsSys - PCS CDMA (Using Channels)��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_MapPcsCdmaChannelToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU                *pstPcsChannelsSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /*
     This record is used to instruct the mobile device to look for CDMA service
     on the channels listed in band class 1 (1900 MHz PCS frequencies).
     */

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 1�ĳ�����band������д��band 1��channelֱ����д */

    pstFreqInfo->ulNum = pstPcsChannelsSys->ucNumOfChans;
    for (i = 0; i < CNAS_MIN(pstPcsChannelsSys->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = CNAS_PRL_BAND_CLASS_TYPE_1;
        pstFreqInfo->astFreqInfo[i].usChannel   = pstPcsChannelsSys->ausChan[i];
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_MapCdmaGenericToBandChannel
 ��������  : ��CDMA Generic��Acquisition Record�е�
             ��Ϣ��ת����band��channel number
 �������  : pstGenericAcq - cdma generic��Ϣ
 �������  : pstFreqInfo - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_PRL_MapCdmaGenericToBandChannel(
    CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_STRU              *pstGenericAcq,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    VOS_UINT16                          i;

    /* ���ݴ������Ϣ����дƵ�κ�channel number������CDG130�Ķ��壬��ʱ����
       Band 1�ĳ�����band������д��band 1��channelֱ����д */

    pstFreqInfo->ulNum = pstGenericAcq->ucNumOfChans;
    for (i = 0; i < CNAS_MIN(pstGenericAcq->ucNumOfChans, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        pstFreqInfo->astFreqInfo[i].enBandClass = pstGenericAcq->astFreq[i].enBandClass;
        pstFreqInfo->astFreqInfo[i].usChannel   = pstGenericAcq->astFreq[i].usChannel;
    }
}



/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlAcqRecFreqListInfo
 ��������  : ͨ��PRL��ָ����ϵͳ��¼��ȡƵ���б���Ϣ
 �������  : pstPrlAcqRec - ָ���Ļ�ȡ���¼
 �������  : pstFreqInfo  - ת�����Ƶ����Ϣ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_GetPrlAcqRecFreqListInfo(
    CNAS_PRL_ACQ_RECORD_STRU                               *pstPrlAcqRec,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
)
{
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8            enAcqType;

    /* �����ָ���ǰ��Acq record����Ч�ģ���ֱ�ӷ��ظ���Ϊ0 */
    if ((VOS_NULL_PTR == pstPrlAcqRec)
     || (VOS_FALSE    == pstPrlAcqRec->ucAcqValid))
    {
        pstFreqInfo->ulNum = 0;
        return;
    }

    enAcqType = pstPrlAcqRec->enAcqType;
    switch (enAcqType)
    {
        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS:
            CNAS_PRL_MapCellularCdmaStandardToBandChannel(&pstPrlAcqRec->u.stCellularStandardSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS:
            CNAS_PRL_MapCellularCdmaCustomToBandChannel(&pstPrlAcqRec->u.stCelluarCustomSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED:
            CNAS_PRL_MapCellularCdmaPreferToBandChannel(&pstPrlAcqRec->u.stCellularPreSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS:
            CNAS_PRL_MapPcsCdmaBlockToBandChannel(&pstPrlAcqRec->u.stPcsBlocksSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS:
            CNAS_PRL_MapPcsCdmaChannelToBandChannel(&pstPrlAcqRec->u.stPcsChannelsSys, pstFreqInfo);
            break;

        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95:
            CNAS_PRL_MapCdmaGenericToBandChannel(&pstPrlAcqRec->u.st1xAndIs95Sys, pstFreqInfo);
            break;

        /* ��֧�ֵ�ACQ TYPE�����ظ���Ϊ0 */
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS:
        case CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS:
            pstFreqInfo->ulNum = 0;
            break;
        /* �޸ĸ�������sizeof */
        case CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD:
            pstFreqInfo->ulNum = pstPrlAcqRec->u.stHrpdSys.ucNumOfChans;
            NAS_MEM_CPY_S(pstFreqInfo->astFreqInfo,
                          CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstPrlAcqRec->u.stHrpdSys.astFreq,
                          pstFreqInfo->ulNum * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
            break;

        default:
            pstFreqInfo->ulNum = 0;
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_GetPrlAcqRecFreqListInfo():Wrong  AcqType");
            break;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_CalcPrlAcqRecTotalFreqNum
 ��������  : ����PRL��ȡ�����ܵ�Ƶ�����
 �������  : ��
 �������  : ��

 �� �� ֵ  : ��ȡ�����ܵ�Ƶ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_PRL_CalcPrlAcqRecTotalFreqNum(VOS_VOID)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usAcqRecNum;
    VOS_UINT16                          usTotalNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;

    usAcqRecNum = CNAS_PRL_GetPrlAcqRecordNum();
    usTotalNum  = 0;

    /* ��ǰ�����Ƶ��������ظ���Ŀǰ���������������ظ�����ʱ��Ϊ����ظ��������ر�Ķ� */
    for (i = 0; i < usAcqRecNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* ��ָ����б�����ֱ������ */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /*�������Ч��Acq Rec�� ֱ������*/
        if (VOS_FALSE == pstPrlAcqRec->ucAcqValid)
        {
            continue;
        }
        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

        usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
    }

    return usTotalNum;
}



/*****************************************************************************
 �� �� ��  : CNAS_PRL_CalcPrlSysRecListTotalFreqNum
 ��������  : ����PRLϵͳ��¼�б���ܵ�Ƶ�����
 �������  : usSysRecNum-----------ϵͳ��¼�ܸ���
             pstSysRecord----------ϵͳ��¼�б�
 �������  : ��

 �� �� ֵ  : ��ȡ�����ܵ�Ƶ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_PRL_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usTotalNum;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;

    usTotalNum  = 0;
    usAcqIndex  = 0;

    /* ��ǰ�����Ƶ��������ظ���Ŀǰ���������������ظ�����ʱ��Ϊ����ظ��������ر�Ķ� */
    for (i = 0; i < usSysRecNum; i++)
    {

        if (VOS_FALSE == pstSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        usAcqIndex = pstSysRecord[i].usAcqIndex;

        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

        /* ��ָ����б��� */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

        usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
    }

    return usTotalNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetSidNidWildCard_1XIS95
 ��������  : ��ǰ��SID��NID�Ƿ�ƥ��(���Ƚ�SID��NID),ƥ���򷵻�VOS_TRUE�����򷵻�
             VOS_FALSE��ͬʱ���ص�ǰSID/NID��ͨ������
 �������  : pstSysInfo - ��Ҫ�Ƚϵ�SID/NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : pstWildCard  - ��ȡͨ�������
 �� �� ֵ  : VOS_TRUE:��ǰƥ�䣬ͨ��������Ч, VOS_FALSE:��ǰ��ƥ�䣬ͨ��������Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsSidNidMatch_1XIS95(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          usTmpNid;

    if ((pstSysRecord->u.st1xAndIs95Id.usSid != pstSysInfo->usSid)
     && (pstSysRecord->u.st1xAndIs95Id.usSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if (CNAS_PRL_NID_INCL == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        usTmpNid = pstSysRecord->u.st1xAndIs95Id.usNid;
    }
    else
    {
        /* Ĭ����ΪNIDΪͨ��� */
        if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = CNAS_PRL_WILDCARD_NID;
        }
        else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = CNAS_PRL_PUBLIC_NETWORK_NID;
        }
        else
        {
            usTmpNid = CNAS_PRL_WILDCARD_NID;
        }
    }

    if ((usTmpNid != pstSysInfo->usNid)
     && (usTmpNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrl1xIs95SysRecordWildCardType
 ��������  : �鿴sys record�е�sid��nid���Ƿ���ͨ���
 �������  : pstSysInfo - ��Ҫ�Ƚϵ�SID/NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : SID��NID��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrl1xIs95SysRecordWildCardType(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;
    VOS_UINT16                          usTmpNid;

    enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;

    /* �ȿ�SID��ͨ������� */
    if (pstSysRecord->u.st1xAndIs95Id.usSid == CNAS_PRL_WILDCARD_SID)
    {
        enWildCardType = CNAS_PRL_WILDCARD_TYPE_SID;
    }

    /* �ٿ�NID��ͨ������� */
    else
    {
        if (CNAS_PRL_NID_INCL == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
        {
            usTmpNid = pstSysRecord->u.st1xAndIs95Id.usNid;
        }
        else
        {
            if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
            {
                usTmpNid = CNAS_PRL_WILDCARD_NID;
            }
            else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstSysRecord->u.st1xAndIs95Id.enNidIncl)
            {
                usTmpNid = CNAS_PRL_PUBLIC_NETWORK_NID;
            }
            else
            {
                usTmpNid = CNAS_PRL_WILDCARD_NID;
            }
        }

        if( usTmpNid == CNAS_PRL_WILDCARD_NID )
        {
          enWildCardType = CNAS_PRL_WILDCARD_TYPE_NID;
        }
        else
        {
          enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;
        }
    }
    return enWildCardType;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrl1xMccMncSysRecordWileCardType
 ��������  : �鿴MCC/MNC���͵�sys record�е�sid��nid���Ƿ���ͨ���
 �������  : pstSysInfo - ��Ҫ�Ƚϵ�SID/NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : SID��NID��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrl1xMccMncSysRecordWileCardType(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_SYS_TYPE_SID_NID_STRU                         *pstSidNid = VOS_NULL_PTR;
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU                      *pstMccMncId = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstSidNid      = &(pstSysRecord->u.stMccMncId.u.stSidNid);
    pstMccMncId    = &(pstSysRecord->u.stMccMncId);
    enWildCardType = CNAS_PRL_WILDCARD_TYPE_BUTT;

    if (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstMccMncId->enMccMncSubType)
    {
        return CNAS_PRL_WILDCARD_TYPE_SID;
    }

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSidNid->ucSidNidNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM);i++)
    {
        /* ���SID���ҵ���˵��SID��ȷƥ�䣬NIDͨ�� */
        if (CNAS_PRL_WILDCARD_SID == pstSidNid->asSid[i])
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_SID;
            break;
        }
        else if (CNAS_PRL_WILDCARD_NID == pstSidNid->asNid[i])
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_NID;
            break;
        }
        else
        {
            enWildCardType = CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD;
        }
    }

    return enWildCardType;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlSysRecordWildCardType
 ��������  : �鿴sys record�е�ͨ�������
 �������  : pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : ͨ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrlSysRecordWildCardType(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    switch( pstSysRecord->enRecordType )
    {
        case CNAS_PRL_SYS_RECORD_TYPE_1X_IS95:
            return CNAS_PRL_GetPrl1xIs95SysRecordWildCardType(pstSysRecord);

        case CNAS_PRL_SYS_RECORD_TYPE_HRPD:
            break;

        case CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED:
            return CNAS_PRL_GetPrl1xMccMncSysRecordWileCardType(pstSysInfo, pstSysRecord);

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_GetPrlSysRecordWildCardType():Wrong  Sys Rec Type");
            break;
    }

    return CNAS_PRL_WILDCARD_TYPE_UNKNOWN;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetMatchLvl_OnlySidNidMatch
 ��������  : �ڽ�SID/NIDƥ�������£���Ӧ��sys record��ƥ�伶��
 �������  : pstSysRecord - ϵͳ��¼������
 �������  : ��

 �� �� ֵ  : sys reord��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;

    /* ��ǰ������������������͵�SID������Ϊ��ƥ�� */
    if ((CNAS_PRL_SID_OPER_0 != pstSysInfo->usSid)
     && (CNAS_PRL_SID_OPER_1 != pstSysInfo->usSid))
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    /* �����ǰSYS RECORD�в���ͨ�������˵���϶���SID/NID��ƥ�� */
    if (CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD == enWildCardType)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;
    }

    /* ֻ��NIDͨ�����ʱ�򣬷���NIDͨ�� */
    if (CNAS_PRL_WILDCARD_TYPE_NID == enWildCardType)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;
    }

    return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch
 ��������  : ��Bandƥ�������£���Ӧ��sys record��ƥ�伶��
 �������  : pstSysRecord - ϵͳ��¼������
 �������  : ��

 �� �� ֵ  : sys reord��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{

    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstOhmFreq = VOS_NULL_PTR;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_SID:
            {
                pstOhmFreq = CNAS_CCB_GetCdmaOhmFreq();

                /* �����ǰϵͳƵ����overheader��Ϣ��Ƶ�㣬��������Ҫ��hashƵ���ϵͳmatch�����⴦�� */
                if ((pstSysInfo->stFreq.enBandClass == pstOhmFreq->enBandClass)
                 && (pstSysInfo->stFreq.usChannel   == pstOhmFreq->usChannel))
                {
                    enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID;
                }
                else
                {
                    enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
                }
            }
            break;

        case CNAS_PRL_WILDCARD_TYPE_UNKNOWN:
        default:
            enMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
            break;
    }

    return enMatchLvl;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch
 ��������  : ��channel��ƥ�������£���Ӧ��sys record��ƥ�伶��
 �������  : pstSysRecord - ϵͳ��¼������
 �������  : ��

 �� �� ֵ  : sys reord��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8   enWildCardType;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_SID:
            return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            return CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID;

        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            return CNAS_PRL_SID_NID_MATCH_LVL_SID_NID;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_GetSysRecordChannelMatchLvl():Wrong Sys wildcard Type");
            break;
    }

    return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysMatchSysRecordLvl
 ��������  : ��ǰ��1Xϵͳ�Ƿ��ϵͳ��¼��ƥ��
 �������  : usSrcSid - ��Ҫ�Ƚϵ�SID�� usSrcNid - ��Ҫ�Ƚϵ�NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : SID��NID��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

 2.��    ��   : 2014��12��30��
   ��    ��   : y00245242
   �޸�����   : match GEO�޸�

*****************************************************************************/
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordLvl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord;
    VOS_UINT32                                              ulIsSidNidMatched;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    ulIsSidNidMatched      = VOS_FALSE;

     /* ϵͳ��¼��Ч�������� */
    if (VOS_FALSE == pstSysRecord->ucSysRecValid)
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_1XIS95(pstSysInfo, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_MccMncBased(pstSysInfo, pstSysRecord);
    }
    else
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    /* ���SID��NID����ƥ�䣬��ʱ��ǰϵͳ�϶���ϵͳ��¼��ƥ�� */
    if ( VOS_FALSE == ulIsSidNidMatched )
    {
        return CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    }

    pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

    /* ��ָ�뱣�� */
    if (VOS_NULL_PTR == pstAcqRecord)
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);
    }

    enBandChannelMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);
    /* ���band��û��ƥ�䣬˵����ʱ����ƥ����SID��NID */
    if ( CNAS_PRL_BAND_CHANNEL_NOT_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);
    }

    /* ���CHANNELû��ƥ�䣬˵����ʱ����ƥ����SID��NID��BAND */
    if ( CNAS_PRL_BAND_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch(pstSysInfo, pstSysRecord);
    }

    /* ������˵����SID��NID��BAND��CHANNEL��ƥ�䣬����channelƥ������µ�ƥ��ȼ� */
    return CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(pstSysInfo, pstSysRecord);

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysGeoList
 ��������  : �жϵ�ǰ��1xϵͳ�Ƿ���PRL�д���
 �������  : usSid - �����ҵ�sid
             usNid - �����ҵ�nid
 �������  : pstGeoListInfo - ��������GEO�б���Ϣ�������PRL�в����ڣ��򷵻صĸ���Ϊ0

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified
*****************************************************************************/
VOS_VOID CNAS_PRL_Get1xSysGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstPrlSysInfo;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT32                                              ulIsMatched;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTmpMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;
    VOS_UINT16                                              usMostMatchedIndex;

    pstPrlSysInfo               = CNAS_PRL_GetPrlSysInfoAddr();
    ulIsMatched                 = VOS_FALSE;
    usGeoFirstSysRecIndex       = 0;
    enMatchLvl                  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    pstTmpSysRecord             = pstPrlSysInfo->pstSysRecord;

    /* ��ʼ��������� */
    pstGeoListInfo->ucGeoNum    = 0;
    pstGeoListInfo->usSid       = pstSysInfo->usSid;
    pstGeoListInfo->usNid       = pstSysInfo->usNid;

    usMostMatchedIndex          = 0;

    for (i = 0; i < pstPrlSysInfo->usSysRecordNum; i++,pstTmpSysRecord++)
    {

        /* ÿ�ν��µ�GEO(�ǵ�һ��GEO)���ߵ���ϵͳ�б�����һ����ʱ���ж�֮ǰ������ʱ���Ƿ����matach�ļ�¼ */
        if (((CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
            &&(i != 0))
          ||(i == (pstPrlSysInfo->usSysRecordNum -1)))
        {
            if (VOS_TRUE == ulIsMatched)
            {
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].enMatchLvl             = enMatchLvl;
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoFirstSysRecIndex  = usGeoFirstSysRecIndex;
                pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usMostMatchedIndex     = usMostMatchedIndex;

                if ((i                            == (pstPrlSysInfo->usSysRecordNum -1))
                 && (CNAS_PRL_GEO_REGION_IND_SAME == pstTmpSysRecord->enGeoInd))
                {
                    pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum     = i - usGeoFirstSysRecIndex + 1;
                    pstGeoListInfo->ucGeoNum++;

                    return;
                }
                else
                {
                    pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum     = i - usGeoFirstSysRecIndex;
                    pstGeoListInfo->ucGeoNum++;
                }

                ulIsMatched        = VOS_FALSE;
                enMatchLvl         = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
                usMostMatchedIndex = 0;
            }
        }

        /* �жϴ����ϵͳ��Ϣ���Ƿ��ϵͳ��¼�е���ƥ�� */
        enTmpMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo,
                                                           pstTmpSysRecord);
        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enTmpMatchLvl)
        {
            ulIsMatched = VOS_TRUE;

            /* ���ƥ��̶�����ߣ������ƥ��̶� */
            if (enMatchLvl < enTmpMatchLvl)
            {
                enMatchLvl         = enTmpMatchLvl;
                usMostMatchedIndex = i;
            }
        }

        /* ��¼��GEO�еĵ�һ����¼��λ�� */
        if (CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
        {
            usGeoFirstSysRecIndex = i;
        }

        /* ����һ��ֻ��һ����¼����ƥ���������� */
        if ((pstPrlSysInfo->usSysRecordNum == (i+1))
         && (VOS_TRUE == ulIsMatched))
        {
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].enMatchLvl             = enMatchLvl;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoFirstSysRecIndex  = usGeoFirstSysRecIndex;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usGeoSysRecNum         = i - usGeoFirstSysRecIndex + 1;
            pstGeoListInfo->astGeoInfoList[pstGeoListInfo->ucGeoNum].usMostMatchedIndex     = usMostMatchedIndex;
            pstGeoListInfo->ucGeoNum++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_BuildGeoSysRecList
 ��������  : ����GEO�е�ϵͳ��¼�б�����ڶ��GEO�У�������ƥ���SID��NID��ʱ����Ҫ�ܹ�ƴ��
 �������  : pstGeoListInfo - ��ǰ�Ѿ��ҵ���GEO��Ϣ
             ucIgnoreNegSys - �Ƿ����negativeϵͳ,Ĭ�϶��Ǻ���negativeϵͳ��,���������ǲ�����negativeϵͳ,��Ϊ
                              �������п�����negativeϵͳ���ṩ����
 �������  : pusSysRecNum -- ϵͳ��¼��
             pstSysRecord -- ϵͳ��¼ָ��ĵ�ַ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��9��
    ��    ��   : w00176964
    �޸�����   : DTS2015030405482:����ϵͳ�����ʱ,GEO��ϵͳ����Ϊ1ʱ,��Ҫ����negativeϵͳ

*****************************************************************************/
VOS_VOID CNAS_PRL_BuildGeoSysRecList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT8                                               ucIgnoreNegSys,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usMostMatchGeoNum;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchLvl;
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstPrlSysInfo;
    VOS_UINT16                                              usGeoFirstSysRecIndex;

    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMostMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMatchLevel;

    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;

    enMostMatchLvl              = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    usMostMatchGeoNum           = 0;

    pstPrlSysInfo = CNAS_PRL_GetPrlSysInfoAddr();



    /* �ҵ���ƥ���GEO�������Ӧ��ϵͳ��¼�б� */
    for (i = 0; i < CNAS_MIN(pstGeoListInfo->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        /* �����Ҫ����negativeϵͳ������ƥ���GEO��ϵͳ��¼�ܸ���Ϊ1�����������ƥ���ϵͳ
           ��negativeϵͳ,��������GEO����������һ��GEO */
        if ((VOS_TRUE  == ucIgnoreNegSys)
         && (1         == pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum))
        {
            pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex);

            if (VOS_NULL_PTR == pstTmpSysRecord)
            {
                continue;
            }

            if (CNAS_PRL_PREF_NEG_SYS_NEG == pstTmpSysRecord->enPrefNegSys)
            {
                continue;
            }
        }

        if (enMostMatchLvl < pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {

            enMostMatchLvl      = pstGeoListInfo->astGeoInfoList[i].enMatchLvl;
            usMostMatchGeoNum   = i;
        }
        else if ((enMostMatchLvl                       == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
              && (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != pstGeoListInfo->astGeoInfoList[i].enMatchLvl))
        {
            enBandChanMostMatchLevel = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum]));
            enBandChanMatchLevel     = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[i]));

            if (enBandChanMostMatchLevel < enBandChanMatchLevel)
            {
                usMostMatchGeoNum   = i;
            }
        }
        else
        {}
    }

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enMostMatchLvl)
    {
        *pusSysRecNum = 0;
        return;
    }

    usGeoFirstSysRecIndex = pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum].usGeoFirstSysRecIndex;
    *pusSysRecNum = pstGeoListInfo->astGeoInfoList[usMostMatchGeoNum].usGeoSysRecNum;

    NAS_MEM_CPY_S(pstSysRecord,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum),
                  pstPrlSysInfo->pstSysRecord + usGeoFirstSysRecIndex,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsSysRecordVaild
 ��������  : �ж�ϵͳ��¼�Ƿ����
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
VOS_UINT8 CNAS_PRL_IsSysRecordVaild(
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSysRecord
)
{
    if ((VOS_NULL_PTR                     == pstSysRecord)
     || (VOS_FALSE                        == pstSysRecord->ucSysRecValid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysNegative_BandChanAmbiguousMatch
 ��������  : �ж�geo��ϵͳ��neg�ķ�ʽband channelģ��ƥ�䣬ƥ�䷽ʽΪ:���һ��geo��ͬʱ����ƥ���prefϵͳneg
             ϵͳ���Ƚ�ƥ��ȼ��������ȣ����ٱȽ�band channel�ȼ���ֱ����prefϵͳ
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo
             CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��28��
    ��    ��   : c00299063
    �޸�����   : DTS2015072703850
*****************************************************************************/
VOS_UINT8 CNAS_PRL_Is1xSysNegative_BandChanAmbiguousMatch(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;

    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchNegSysLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMostMatchPrefSysLvl;

    enMostMatchNegSysLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enMostMatchPrefSysLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

    for (i = 0; i < pstMatchedGeoInfo->usGeoSysRecNum; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMatchedGeoInfo->usGeoFirstSysRecIndex + i);

        if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
        {
            continue;
        }

        enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

        /*���һ��geo��ͬʱ����ƥ���prefϵͳnegϵͳ���Ƚ�ƥ��ȼ��������ȣ����ٱȽ�band channel�ȼ���ֱ����prefϵͳ */
        if (CNAS_PRL_PREF_NEG_SYS_PREF  == pstSysRecord->enPrefNegSys)
        {
            if (enSysMatchLvl > enMostMatchPrefSysLvl)
            {
                enMostMatchPrefSysLvl = enSysMatchLvl;
            }
        }
        else
        {
            if (enSysMatchLvl > enMostMatchNegSysLvl)
            {
                enMostMatchNegSysLvl = enSysMatchLvl;
            }
        }

    }

    if (enMostMatchNegSysLvl > enMostMatchPrefSysLvl)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}
/*****************************************************************************
 �� �� ��  : CNAS_PRL_CmpIncludeRelationOfTwoAcqRecord
 ��������  : �Ƚ����������¼��������Ƶ���໥֮��İ�����ϵ
 �������  : CNAS_PRL_ACQ_RECORD_STRU                               *pstFirAcqRecord,
             CNAS_PRL_ACQ_RECORD_STRU                               *pstSecAcqRecord
 �������  :
 �� �� ֵ  :  CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8 CNAS_PRL_CmpIncludeRelationOfTwoAcqRecord(
    CNAS_PRL_ACQ_RECORD_STRU                               *pstFirAcqRecord,
    CNAS_PRL_ACQ_RECORD_STRU                               *pstSecAcqRecord
)
{

    VOS_UINT8                                               i;
    VOS_UINT8                                               j;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stFirAcqRecFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stSecAcqRecFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstMoreChanAcqRecFreqInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstLessChanAcqRecFreqInfo = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stFirAcqRecFreqInfo, sizeof(stFirAcqRecFreqInfo), 0x0, sizeof(stFirAcqRecFreqInfo));
    NAS_MEM_SET_S(&stSecAcqRecFreqInfo, sizeof(stSecAcqRecFreqInfo), 0x0, sizeof(stSecAcqRecFreqInfo));

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstFirAcqRecord, &stFirAcqRecFreqInfo);
    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstSecAcqRecord, &stSecAcqRecFreqInfo);

    if (stFirAcqRecFreqInfo.ulNum > stSecAcqRecFreqInfo.ulNum)
    {
        pstMoreChanAcqRecFreqInfo = &stFirAcqRecFreqInfo;
        pstLessChanAcqRecFreqInfo = &stSecAcqRecFreqInfo;
    }
    else
    {
        pstMoreChanAcqRecFreqInfo = &stSecAcqRecFreqInfo;
        pstLessChanAcqRecFreqInfo = &stFirAcqRecFreqInfo;
    }

    /*������ڰ�����ϵ����Ƶ�������ٵĲ����¼�У�ÿһ��Ƶ�㶼����Ƶ�����϶�Ĳ����¼�д��� */
    for (i = 0; i < pstLessChanAcqRecFreqInfo->ulNum; i++)
    {
        for (j = 0; j < pstMoreChanAcqRecFreqInfo->ulNum; j++)
        {
            if ((pstLessChanAcqRecFreqInfo->astFreqInfo[i].enBandClass == pstMoreChanAcqRecFreqInfo->astFreqInfo[j].enBandClass)
             && (pstLessChanAcqRecFreqInfo->astFreqInfo[i].usChannel   == pstMoreChanAcqRecFreqInfo->astFreqInfo[j].usChannel))
            {
                break;
            }

            if (pstMoreChanAcqRecFreqInfo->ulNum - 1 == j)
            {
                return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_NOT_INCLUDE;
            }

        }
    }

    /*������ڰ�����ϵ����Ƶ�������ٵ�Ϊ��������Ƶ������ͬ���ʾ2�������¼����Ӧ��Ƶ����ȫһ�� */
    if (stFirAcqRecFreqInfo.ulNum > stSecAcqRecFreqInfo.ulNum)
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_FIR_INCLUDE_SEC;
    }
    else if (stFirAcqRecFreqInfo.ulNum < stSecAcqRecFreqInfo.ulNum)
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SEC_INCLUDE_FIR;
    }
    else
    {
        return CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SAME;
    }

}




/*****************************************************************************
 �� �� ��  : CNAS_PRL_CmpBandChanMatchLvlOfTwoAcqRecord
 ��������  : �Ƚ����������¼��band channel ƥ��̶�
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
             CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstFirSysRecord,
             CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSecSysRecord
 �������  :
 �� �� ֵ  :  CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM_UINT8 CNAS_PRL_CmpSysBandChanMatchLvlInTwoSysRecord(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstFirSysRecord,
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSecSysRecord
)
{
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enFirSysBandChanMatchLvl;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enSecSysBandChanMatchLvl;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstFirAcqRecord   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstSecAcqRecord   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8         enIncludeRelation;

    enFirSysBandChanMatchLvl = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    enSecSysBandChanMatchLvl = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    /* ����ϵͳ��¼��ȡ��Ӧ�Ĳ����¼ */
    pstFirAcqRecord   = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstFirSysRecord->usAcqIndex);

    if (VOS_NULL_PTR != pstFirAcqRecord)
    {
        enFirSysBandChanMatchLvl = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstFirAcqRecord);
    }

    pstSecAcqRecord   = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSecSysRecord->usAcqIndex);

    if (VOS_NULL_PTR != pstSecAcqRecord)
    {
        enSecSysBandChanMatchLvl = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstSecAcqRecord);
    }


    /* �Ƚϲ����¼�У�ϵͳ��band channel��ƥ��̶� */
    if (enFirSysBandChanMatchLvl > enSecSysBandChanMatchLvl)
    {
        return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH;
    }
    else if (enFirSysBandChanMatchLvl < enSecSysBandChanMatchLvl)
    {
        return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_SEC_RECORD_HIGH;
    }
    else
    {
        /*�Ƚ����������¼����Ӧ��Ƶ��֮ǰ�Ƿ���ڰ�����ϵ�����ڱ�������ϵ�Ĳ����¼ƥ��̶ȸ��� */
        enIncludeRelation = CNAS_PRL_CmpIncludeRelationOfTwoAcqRecord(pstFirAcqRecord, pstSecAcqRecord);

        switch(enIncludeRelation)
        {
            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_FIR_INCLUDE_SEC:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_SEC_RECORD_HIGH;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SEC_INCLUDE_FIR:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SAME:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_TWO_RECORD_SAME;

            case CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_NOT_INCLUDE:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_UNKNOWN;

            default:
                return CNAS_PRL_BAND_CHANNEL_MATCH_CMP_BUTT;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysNegative_CmpPrefAndNegSysPrioInGeo
 ��������  : �ж�ϵͳΪnegϵͳ�ķ�ʽΪ �Ƚ�geo��prefϵͳ��negϵͳ�����ȼ�
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
             CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_UINT8 CNAS_PRL_Is1xSysNegative_BandChanAccurateMatch(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrefSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrefSysMostMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enNegSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enNegSysMostMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord         = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostPrefSysRecord = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostNegSysRecord  = VOS_NULL_PTR;

    enPrefSysMostMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enNegSysMostMatchLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enPrefSysMatchLvl     = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enNegSysMatchLvl      = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;

    for (i = 0; i < pstMatchedGeoInfo->usGeoSysRecNum; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMatchedGeoInfo->usGeoFirstSysRecIndex + i);

        if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
        {
            continue;
        }

        /* ����cdg143 5.8.3.1, ���negativeϵͳע���������ֳ���:
        Consider a system table with two entries in the same GEO of:
        0001: SID=00004; NID=05001; PREF=PREFERRED; ACQ_INDEX = 1
        0002: SID=00004; NID=65535; PREF=NEGATIVE; ACQ_INDEX=1

        Example: Consider a system table with two entries in the same GEO of:
        0001: SID=00004; NID=65535; PREF=PREFERRED; ACQ_INDEX = [PCS CHAN 25]
        0002: SID=00004; NID=65535; PREF=NEGATIVE; ACQ_INDEX  = [PCS BLOCK ANY]
        */

        if (CNAS_PRL_PREF_NEG_SYS_PREF  == pstSysRecord->enPrefNegSys)
        {
            /*��¼��ƥ���prefϵͳ�ĵȼ������� */
            enPrefSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            if (enPrefSysMatchLvl > enPrefSysMostMatchLvl)
            {
                enPrefSysMostMatchLvl = enPrefSysMatchLvl;
                pstMostPrefSysRecord  = pstSysRecord;
            }
        }
        else
        {
            /*��¼��ƥ���Negϵͳ�ĵȼ������� */
            enNegSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            if (enNegSysMatchLvl > enNegSysMostMatchLvl)
            {
                enNegSysMostMatchLvl = enNegSysMatchLvl;
                pstMostNegSysRecord  = pstSysRecord;
            }
        }
    }

    /* �Ƚ�prefϵͳ��negϵͳ��ƥ��̶� */
    if (enPrefSysMostMatchLvl > enNegSysMostMatchLvl)
    {
        return VOS_FALSE;
    }
    else if (enPrefSysMostMatchLvl < enNegSysMostMatchLvl)
    {
        return VOS_TRUE;
    }
    else
    {
        if (VOS_NULL_PTR == pstMostNegSysRecord)
        {
            return VOS_FALSE;
        }

        if (VOS_NULL_PTR == pstMostPrefSysRecord)
        {
            return VOS_TRUE;
        }

        /* ��� prefϵͳ�� negϵͳ��sid nidƥ��̶���ͬ����Ƚ�band channelƥ��ȼ���ֻҪ����neg�ı���̶ȸ��ߣ����ж�Ϊperfϵͳ��*/
        if (CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH == CNAS_PRL_CmpSysBandChanMatchLvlInTwoSysRecord(pstSysInfo,
                                                                                                             pstMostNegSysRecord,
                                                                                                             pstMostPrefSysRecord))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysNegativeInCurGeo
 ��������  : �ж�ϵͳ�ڵ�ǰGEO���Ƿ���negϵͳ
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
             CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_PRL_Is1xSysNegativeInCurGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                 *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          *pstMatchedGeoInfo
)
{
    /* ͨ��NV���е�ֵ�жϲ�����һ���жϷ�ʽ*/
    if (CNAS_XSD_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH == CNAS_XSD_GetNegPrefSysCmpType())
    {
        return CNAS_PRL_Is1xSysNegative_BandChanAmbiguousMatch(pstSysInfo, pstMatchedGeoInfo);

    }
    else
    {
        return CNAS_PRL_Is1xSysNegative_BandChanAccurateMatch(pstSysInfo, pstMatchedGeoInfo);
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysNegative
 ��������  : �жϵ�ǰ��SID��NID��PRL���Ƿ���Negative��
 �������  : pstSysInfo -- �����ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Negative��  VOS_FALSE: ����Negative��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��12��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��8��12��
    ��    ��   : y00245242
    �޸�����   : �޸�GEOƥ��ԭ��
  3.��    ��   : 2015��7��2��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
VOS_UINT32 CNAS_PRL_Is1xSysNegativeInPrl(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;

    /* ���±����������쳣 */
    if (0 == pstGeoListInfo->ucGeoNum)
    {
        return VOS_FALSE;
    }

    /* cdg143 7.1.2.6:
       The placement of negative systems in the system table can vary. In some cases, a
       policy can dictate that all negative systems are placed in their own GEO or a combined
       GEO. In other cases, policy may dictate that negative systems are located in the same
       GEO as the preferred systems of the same market. Maintainability is increased if
       negative systems appear at the bottom of their appropriate GEO and it ensures that the
       frequencies of preferred systems of the GEO are immediately scanned.

       negativeϵͳ��PRL�з��ù�������:
       1. һ�ֳ�����negativeϵͳͨ���Զ�����GEO���֣�
       2. ���⣬negativeϵͳҲ������preferredϵͳ����ͬһ��GEO����ά������˵��negativeϵͳͨ��
          �������GEO�еײ���
    */

    /* ��GEO list���ҳ���ƥ���GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo);

    /* ����ƥ���GEO�л�ȡPRL������ƥ���ϵͳ��¼���� */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
    {
        return CNAS_PRL_Is1xSysNegativeInCurGeo(pstSysInfo, pstMostMatchGeoInfo);

    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrefOnlyFlg
 ��������  : ��ȡpref only��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8 ����Pref only���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_PRL_GetPrefOnlyFlg(VOS_VOID)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;

    pstPrlHeaderInfo = CNAS_PRL_GetPrlHeaderInfoAddr();

    return pstPrlHeaderInfo->ucPreferOnly;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsMostPref1xSysInGeo
 ��������  : �鿴��ǰ��1xϵͳ�ǲ��ǵ�ǰGEO�����ȼ���ߵ�ϵͳ
 �������  : pstCurSysInfo -- ��ǰ�ѵ���ϵͳ��Ϣ
             pstSysAcqList -- ���ɵĲ����б���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����ȼ���ߵ�   VOS_FALSE: �������ȼ���ߵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��12��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��30��
    ��    ��   : y00245242
    �޸�����   : �޸�GEO matchԭ��

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsMostPref1xSysInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsMostPref;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord        = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIs1xSysRecordExist;

    VOS_UINT8                                               ucIsExistWildcardSid;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enCurSysMatchLvl;

    ucIsExistWildcardSid  = VOS_FALSE;

    ulIs1xSysRecordExist  = VOS_FALSE;

    ulIsMostPref          = VOS_FALSE;
    /* �����ǰ����GEO�˵���϶�����������ϵͳ */
    if (0 == pstGeoListInfo->ucGeoNum)
    {
        return ulIsMostPref;
    }

    /* ��GEO list���ҳ���ƥ���GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo ,pstGeoListInfo);

    /* ����ƥ���GEO�л�ȡPRL������ƥ���ϵͳ��¼���� */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
    {
        for (i = 0; i < pstMostMatchGeoInfo->usGeoSysRecNum; i++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(pstMostMatchGeoInfo->usGeoFirstSysRecIndex + i);

            if (VOS_FALSE == CNAS_PRL_IsSysRecordVaild(pstSysRecord))
            {
                continue;
            }

            if (VOS_TRUE == CNAS_PRL_Is1xSysRecord(pstSysRecord))
            {
                ulIs1xSysRecordExist = VOS_TRUE;
            }

            enCurSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstCurSysInfo, pstSysRecord);

            /* ��ȡGEO��ƥ��ȼ���ߵ�ϵͳ��¼ */
            if (enSysMatchLvl == enCurSysMatchLvl)
            {
                pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

                /* �����GEO��ƥ��ȼ���ߵ�ϵͳ�У���ǰϵͳ��band��channelƥ��, ����TRUE */
                if (CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID == enSysMatchLvl)
                {
                    if (CNAS_PRL_BAND_CHANNEL_MATCH == CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstCurSysInfo->stFreq), pstAcqRecord))
                    {
                        ulIsMostPref = VOS_TRUE;
                        break;
                    }
                }
                else
                {
                    ulIsMostPref = VOS_TRUE;
                    break;
                }
            }


            /* ��¼geo���Ƿ����sidͨ��ƥ����Ϊpref��ϵͳ*/
            if ((CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID == enCurSysMatchLvl)
             && (CNAS_PRL_PREF_NEG_SYS_PREF              == pstSysRecord->enPrefNegSys))
            {
                ucIsExistWildcardSid = VOS_TRUE;
            }


            if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
            {
                /* �������ȼ�Ϊmore�ļ�¼����֮ǰ����SIDͨ��ƥ�䣬�Ҹ�ϵͳ��geo��prefϵͳ����Ϊ����ϵͳ */
                if (VOS_TRUE  == ucIsExistWildcardSid)
                {
                    ulIsMostPref = VOS_TRUE;
                }

                /* �ñ������ڹ������³���: �ȵ�ǰϵͳ���ŵ�ϵͳ��ȫ��HRPDϵͳ */
                if (VOS_TRUE == ulIs1xSysRecordExist)
                {
                    break;
                }
            }
        }
    }

    return ulIsMostPref;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysIdMatched
 ��������  : �ж�1X��ϵͳID(sid+nid)�Ƿ�ƥ��
 �������  : usSrcSid/usSrcNid - ��Ҫ�Ƚϵ�ϵͳID
             usDstSid/usDstNid - ���Ƚϵ�ϵͳID
 �������  : ��

 �� �� ֵ  : VOS_TRUE:��ǰƥ��, VOS_FALSE:��ǰ��ƥ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_Is1xSysIdMatched(
    VOS_UINT16                          usSrcSid,
    VOS_UINT16                          usSrcNid,
    VOS_UINT16                          usDstSid,
    VOS_UINT16                          usDstNid
)
{
    if ((usDstSid != usSrcSid)
     && (usDstSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if ((usDstNid != usSrcNid)
     && (usDstNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysIdInSysIdList
 ��������  : �ж�1X��ϵͳID(sid+nid)�Ƿ���SYS ID�б���
 �������  : pstSrcSysId - ��Ҫ�Ƚϵ�ϵͳID
             usDtsSysIdNum   -- ���Ƚϵ�ϵͳID�б����
             pstDstSysIdInfo --- ���Ƚϵ�ϵͳID�б�
 �������  : ��

 �� �� ֵ  : VOS_TRUE:��Ŀ��SYSID�б���, VOS_FALSE:����Ŀ��SYSID�б���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_Is1xSysIdInSysIdList(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSrcSysId,
    VOS_UINT16                          usDtsSysIdNum,
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstDstSysIdInfo
)
{
    VOS_UINT16                          i;

    for (i = 0; i < usDtsSysIdNum; i++)
    {
        if (VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(pstSrcSysId->usSid, pstSrcSysId->usNid,
                                                  pstDstSysIdInfo[i].usSid,pstDstSysIdInfo[i].usNid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysMatched
 ��������  : �ж�1X��ϵͳID(sid+nid)��Ƶ���Ƿ�ƥ��
 �������  : pstSrcSysId - ��Ҫ�Ƚϵ�ϵͳ
             pstDtsSysId - ���Ƚϵ�ϵͳ
 �������  : ��

 �� �� ֵ  : VOS_TRUE:��ǰƥ��, VOS_FALSE:��ǰ��ƥ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_Is1xSysMatched(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSrcSys,
    CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
)
{
    if ((pstDstSys->usSid != pstSrcSys->usSid)
     && (pstDstSys->usSid != CNAS_PRL_WILDCARD_SID))
    {
        return VOS_FALSE;
    }

    if ((pstDstSys->usNid != pstSrcSys->usNid)
     && (pstDstSys->usNid != CNAS_PRL_WILDCARD_NID))
    {
        return VOS_FALSE;
    }

    if (pstDstSys->stFreq.enBandClass != pstSrcSys->stFreq.enBandClass)
    {
        return VOS_FALSE;
    }

    if (pstDstSys->stFreq.usChannel != pstSrcSys->stFreq.usChannel)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo
 ��������  : get the most matched system record index in GEO
 �������  : pstMatchedGeoInfo -- matched GEO information pointer

 �������  : pusIndex   -- return system record index in GEO
 �� �� ֵ  : enMatchLvl -- match level
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 12/2/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeoInfo,
    VOS_UINT16                         *pusIndex
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecordAddr = VOS_NULL_PTR;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTempMatchLvl;
    VOS_UINT16                                              usGeoEndIndex;
    VOS_UINT16                                              i;

    enMatchLvl     = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enTempMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    *pusIndex      = 0;

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    usGeoEndIndex    = pstMatchedGeoInfo->usGeoFirstSysRecIndex + pstMatchedGeoInfo->usGeoSysRecNum;

    for (i = pstMatchedGeoInfo->usGeoFirstSysRecIndex; i < usGeoEndIndex; i++)
    {
        /* get matched index of current system in GEO */
        enTempMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo,
                                                           (pstSysRecordAddr->pstSysRecord + i));

        /* update matche level */
        if (enMatchLvl < enTempMatchLvl)
        {
            enMatchLvl = enTempMatchLvl;
            *pusIndex  = i;
        }
    }

    return enMatchLvl;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo
 ��������  : compare the priority of two system records in the same GEO list
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
             CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
             CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstSysGeoListInfo,
 �������  : CNAS_PRL_SYS_PRI_CMP_ENUM_UINT8                        *penSysPriCmp
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 11/27/2014
    ��    ��   : c00299063
    �޸�����   : create new function
  2.��    ��   : 2015/03/31
    ��    ��   : w00242748
    �޸�����   : DTS2015032802406:�Ƚ�����ϵͳ�����ȼ�

*****************************************************************************/
CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32  CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
)
{
    VOS_UINT16                                              usOrigSysIndex;
    VOS_UINT16                                              usCurSysIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enOrigSysMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enCurSysMatchLvl;
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enOrigSysPri;
    CNAS_PRL_PREF_NEG_SYS_ENUM_UINT8                        enCurSysPri;
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enCurSysRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enOrigSysRoamingInd;
    VOS_UINT8                                               ucIsCurSysHome;
    VOS_UINT8                                               ucIsOrigSysHome;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstOrigSysRecord = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstCurSysRecord  = VOS_NULL_PTR;

    /* get current system matched index in GEO */
    enCurSysMatchLvl  = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo,
                                                                  pstMatchedGeoInfo,
                                                                  &usCurSysIndex);

    /* get orignal system matched index in GEO */
    enOrigSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstOrigSysInfo,
                                                                  pstMatchedGeoInfo,
                                                                  &usOrigSysIndex);

    if ((CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enCurSysMatchLvl)
     || (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enOrigSysMatchLvl))
    {
        /* In theory, it should not happen. */
        CNAS_ERROR_LOG(UEPS_PID_XSD,
                       "CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo: somewhere is error!");

        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }

    if (usCurSysIndex == usOrigSysIndex)
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    pstOrigSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(usOrigSysIndex);
    if (VOS_NULL_PTR == pstOrigSysRecord)
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }
    enOrigSysPri = pstOrigSysRecord->enPrefNegSys;

    pstCurSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(usCurSysIndex);
    if (VOS_NULL_PTR == pstCurSysRecord)
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }
    enCurSysPri  = pstCurSysRecord->enPrefNegSys;

    ucIsOrigSysHome = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstOrigSysInfo);
    ucIsCurSysHome  = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

    enOrigSysPri    = (VOS_TRUE == ucIsOrigSysHome) ? CNAS_PRL_PREF_NEG_SYS_PREF : enOrigSysPri;
    enCurSysPri     = (VOS_TRUE == ucIsCurSysHome) ? CNAS_PRL_PREF_NEG_SYS_PREF : enCurSysPri;


    if ((CNAS_PRL_PREF_NEG_SYS_NEG == enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG == enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if ((CNAS_PRL_PREF_NEG_SYS_NEG != enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG == enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if ((CNAS_PRL_PREF_NEG_SYS_NEG == enCurSysPri)
     && (CNAS_PRL_PREF_NEG_SYS_NEG != enOrigSysPri))
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    for (i = CNAS_MIN(usCurSysIndex, usOrigSysIndex); i < (CNAS_MAX(usCurSysIndex, usOrigSysIndex) + 1); i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);
        if (VOS_NULL_PTR == pstSysRecord)
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            break;
        }
    }

    /* last system record is MORE or no MORE is met, two system priority is same */
    if (i >= CNAS_MAX(usCurSysIndex, usOrigSysIndex))
    {
        /* reference from chapter 2.11 in CDG 143:
           3. If the roaming indicator of one system is more favorable than the other (as defined in
           Req. 2.6.2), select the more favorable one.
        */
        enOrigSysRoamingInd = (VOS_TRUE == ucIsOrigSysHome) ? CNAS_PRL_SYS_ROAMING_STATUS_OFF : pstOrigSysRecord->enRoamingInd;
        enCurSysRoamingInd  = (VOS_TRUE == ucIsCurSysHome) ? CNAS_PRL_SYS_ROAMING_STATUS_OFF : pstCurSysRecord->enRoamingInd;

        /*****************************************************************
        *
        * 1��enOrigRoamingInd�����Σ�enCurRoamingInd���Σ�����CNAS_PRL_SYS_PRI_LOW
        * 2��enOrigRoamingInd���Σ�enCurRoamingInd�����Σ�����CNAS_PRL_SYS_PRI_HIGH
        * 3�����ೡ������CNAS_PRL_SYS_PRI_SAME
        *
        ******************************************************************/
        return (CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32)((enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF) ? ( (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF)
                                                                                                                ? CNAS_PRL_SYS_PRI_SAME : CNAS_PRL_SYS_PRI_LOW)
                                                                                                            : ( (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_OFF)
                                                                                                                ? CNAS_PRL_SYS_PRI_HIGH : CNAS_PRL_SYS_PRI_SAME));
    }

    if (usCurSysIndex < usOrigSysIndex)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetRoamingIndInMatchedGeolist
 ��������  : get the roam indicator vlaue of system record in geo list
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo
             CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
 �������  : CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                    *enRoamingInd
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 11/27/2014
    ��    ��   : c00299063
    �޸�����   : create new function
  �޸���ʷ      :
  2.��    ��   : 2015/11/17
    ��    ��   : y00245242
    �޸�����   : iteration 19
*****************************************************************************/
CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_PRL_GetRoamingIndInMatchedGeolist(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    VOS_UINT8                                               i;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stMostMatchGeoListInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enTempRoamingInd;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stMostMatchGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* ��GEO list��ȡ�ȼ���ߵ�GEO�б� */
    CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo, &stMostMatchGeoListInfo);

    enRoamingInd = CNAS_PRL_SYS_ROAMING_STATUS_RESERVED;

    for (i = 0; i < stMostMatchGeoListInfo.ucGeoNum; i++)
    {
        enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstSysInfo,
                                                                  &stMostMatchGeoListInfo.astGeoInfoList[i],
                                                                  &ucMostMatchIndex);


        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enSysMatchLvl)
        {
            pstSysRecord  = CNAS_PRL_GetSpecifiedPrlSysRecord(ucMostMatchIndex);

            if (VOS_NULL_PTR != pstSysRecord)
            {
                enTempRoamingInd = pstSysRecord->enRoamingInd;

                if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == enTempRoamingInd)
                {
                    return CNAS_PRL_SYS_ROAMING_STATUS_OFF;
                }

                /* ����cdg130 5.3.9.3.2�½�Э��:
                  typically ��roaming indicator off�� would be preferred over ��roaming
                  indicator on�� or ��roaming indicator flashing��; and, ��roaming indicator on�� would be
                  preferred over ��roaming indicator flashing��.

                  ���ﷵ������ֵ��Сϵͳ��¼��roamingָʾֵ�����Է�Э�����ᵽ��������ָʾֵ�����ﰴ����ֵ
                  ��С�����ȼ���ߴ���roaming indicator off���⣻
                 */
                if (enTempRoamingInd < enRoamingInd)
                {
                    enRoamingInd = enTempRoamingInd;
                }
            }
        }
    }

    return enRoamingInd;

}



#if 0
/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetAcqRecIndexAccordingToSysRecIndex
 ��������  : Get acquisition record index according to system record index
 �������  : usSysRecIndex -- system record index in PRL system table
 �������  : none

 �� �� ֵ  : return acquisition record index in PRL acquisition Table
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
VOS_UINT16 CNAS_PRL_GetAcqRecIndexAccordingToSysRecIndex(
    VOS_UINT16                          usSysRecIndex
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecordAddr = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstCurSysRecord  = VOS_NULL_PTR;

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    pstCurSysRecord = (pstSysRecordAddr->pstSysRecord + usSysRecIndex);

    return pstCurSysRecord->usAcqIndex;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsCurrentSystemHomeRoamingIndicator
 ��������  : check current system is home roaming indicator

 �������  : pstSysInfo     -- the current system information
             pstCurSysInfo  -- the current system synchronized.

 �������  : penRoamingInd  -- return roaming indicator

 �� �� ֵ  : VOS_TRUE  -- home roaming system
             VOS_FALSE -- non-roaming system

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create
  2.��    ��   : 2015/04/02
    ��    ��   : w00242748
    �޸�����   : DTS2015032802406:�Ƚ�����ϵͳ���ȼ�ʱ�������жϸ�ϵͳ�Ƿ���HOME
                 SID/NID��

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                    *penRoamingInd
)
{
    if (0 != pstGeoListInfo->ucGeoNum)
    {
        if (VOS_TRUE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstSysInfo))
        {
            return VOS_TRUE;
        }

        *penRoamingInd = CNAS_PRL_GetRoamingIndInMatchedGeolist(pstSysInfo,pstGeoListInfo);

        /* is home roaming indicator? */
        if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == *penRoamingInd)
        {
            return VOS_TRUE;
        }
    }

    /* TO DO: implement home group and roam mask (reference from chapter 2.6.2 in cdg143 and
        chapter 5.3.9.1 in cdg130)
    ) */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems
 ��������  : comparing two systems, which system roaming indicator is more
             preferred
             1) if current system is more preferred than old system, return
                MORE;
             2) if current system is the same preferred than old system,
                return SAME;
             3) if current system is the less preferred than old system,
                return LESS;

             NOTE: It implements function from chapter 2.6.2 in CDG 143


 �������  : pstCurSysGeoListInfo  -- the current system GEO list information
             pstOrigSysGeoListInfo -- the orignal system GEO list information
 �������  : none
 �� �� ֵ  : MORE -- more preferred
             SAME -- same preferred
             LESS -- less preferred
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
)
{
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enOrigSysRoamingInd;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enCurSysRoamingInd;
    VOS_UINT32                                              ulIsOrigSysHomeRoaming;
    VOS_UINT32                                              ulIsCurSysHomeRoaming;

    enOrigSysRoamingInd = 0xFF;
    enCurSysRoamingInd  = 0xFF;

    /* reference from chapter 5.3.9.3.2 in cdg130
      Where both systems are listed in different GEOs and the roaming indicators are
      different then typically ��roaming indicator off�� would be preferred over ��roaming
      indicator on�� or ��roaming indicator flashing��; and, ��roaming indicator on�� would be
      preferred over ��roaming indicator flashing��
     */
    ulIsOrigSysHomeRoaming = CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstOrigSysInfo,
                                                                          pstOrigSysGeoListInfo,
                                                                          &enOrigSysRoamingInd);

    ulIsCurSysHomeRoaming = CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstCurSysInfo,
                                                                         pstCurSysGeoListInfo,
                                                                         &enCurSysRoamingInd);

    if ((VOS_TRUE == ulIsOrigSysHomeRoaming)
     && (VOS_TRUE == ulIsCurSysHomeRoaming))
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if (VOS_TRUE == ulIsOrigSysHomeRoaming)
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    if (VOS_TRUE == ulIsCurSysHomeRoaming)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if (enCurSysRoamingInd == enOrigSysRoamingInd)
    {
        return CNAS_PRL_SYS_PRI_SAME;
    }

    if ((enCurSysRoamingInd < enOrigSysRoamingInd)
     && ((enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_ON)
      || (enCurSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_FLASHING)))
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if ((enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_ON)
     || (enOrigSysRoamingInd == CNAS_PRL_SYS_ROAMING_STATUS_FLASHING))
    {
        return CNAS_PRL_SYS_PRI_LOW;
    }

    return CNAS_PRL_SYS_PRI_UNKNOWN;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CompareChannelIndexOfTwoSystems
 ��������  : comparing two systems, which system channel is more
             preferred
             1) if current system index is LESS than old system, return
                MORE;
             2) if current system index is the same as old system,
                return SAME;
             3) if current system index is MORE than old system,
                return LESS;


 �������  : usCurSysAcqIndex   -- the current system index in PRL acquisition table;
             ucCurSysFreqIndex  -- the current system freqency index in acquisiton record;
             usOrigSysAcqIndex  -- the current system index in PRL acquisition table;
             ucOrigSysFreqIndex -- the current system freqency index in acquisiton record;

 �������  : none
 �� �� ֵ  : MORE -- more preferred
             SAME -- same preferred
             LESS -- less preferred
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareChannelIndexOfTwoSystems(
    VOS_UINT16                          usCurSysAcqIndex,
    VOS_UINT8                           ucCurSysFreqIndex,
    VOS_UINT16                          usOrigSysAcqIndex,
    VOS_UINT8                           usOrigSysFreqIndex
)
{
    if (usCurSysAcqIndex == usOrigSysAcqIndex)
    {
        if (ucCurSysFreqIndex == usOrigSysFreqIndex)
        {
            return CNAS_PRL_SYS_PRI_SAME;
        }

        if (ucCurSysFreqIndex < usOrigSysFreqIndex)
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        return CNAS_PRL_SYS_PRI_LOW;
    }

    if (usCurSysAcqIndex < usOrigSysAcqIndex)
    {
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CompareChannelPreferenceOfTwoSystems
 ��������  : comparing two systems, which system channel is more
             preferred
             1) if current system is more preferred than old system, return
                MORE;
             2) if current system is the same preferred than old system,
                return SAME;
             3) if current system is the less preferred than old system,
                return LESS;

             NOTE: It implements function from chapter 2.6.2 in CDG 143.


 �������  : pstCurSysInfo  -- the current system information
             pstOrigSysInfo -- the orignal system information
 �������  : none
 �� �� ֵ  : MORE -- more preferred
             SAME -- same preferred
             LESS -- less preferred
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareChannelPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
)
{
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqInfoAddr = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec   = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT8                           j;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    VOS_UINT16                          usCurSysAcqIndex;
    VOS_UINT16                          usOrigSysAcqIndex;
    VOS_UINT8                           ucCurSysFreqIndex;
    VOS_UINT8                           usOrigSysFreqIndex;
    VOS_UINT8                           ucOrigSysSearchEnd;
    VOS_UINT8                           ucCurSysSearchEnd;
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32   enSysPri;

    ucOrigSysSearchEnd = VOS_FALSE;
    ucCurSysSearchEnd  = VOS_FALSE;
    usCurSysAcqIndex   = 0;
    usOrigSysAcqIndex  = 0;
    ucCurSysFreqIndex  = 0;
    usOrigSysFreqIndex = 0;

    pstAcqInfoAddr = CNAS_PRL_GetPrlAcqInfoAddr();

    for (i = 0; i < pstAcqInfoAddr->usAcqRecordNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        for (j = 0; j < (VOS_UINT8)CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); j++)
        {
            if ((ucCurSysSearchEnd                           == VOS_FALSE)
             && (stAcqRecFreqInfo.astFreqInfo[j].enBandClass == pstCurSysInfo->stFreq.enBandClass)
             && (stAcqRecFreqInfo.astFreqInfo[j].usChannel   == pstCurSysInfo->stFreq.usChannel))
            {
                usCurSysAcqIndex  = i;
                ucCurSysFreqIndex = j;
                ucCurSysSearchEnd = VOS_TRUE;
            }

            if ((ucOrigSysSearchEnd                          == VOS_FALSE)
             && (stAcqRecFreqInfo.astFreqInfo[j].enBandClass == pstOrigSysInfo->stFreq.enBandClass)
             && (stAcqRecFreqInfo.astFreqInfo[j].usChannel   == pstOrigSysInfo->stFreq.usChannel))
            {
                usOrigSysAcqIndex  = i;
                usOrigSysFreqIndex = j;
                ucOrigSysSearchEnd = VOS_TRUE;
            }
        }

        if ((VOS_TRUE == ucCurSysSearchEnd)
         && (VOS_TRUE == ucOrigSysSearchEnd))
        {
            break;
        }
    }

    if ((VOS_FALSE == ucCurSysSearchEnd)
     && (VOS_FALSE == ucOrigSysSearchEnd))
    {
        return CNAS_PRL_SYS_PRI_UNKNOWN;
    }

    if (VOS_TRUE == ucCurSysSearchEnd)
    {
        if (VOS_FALSE == ucOrigSysSearchEnd)
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        enSysPri = CNAS_PRL_CompareChannelIndexOfTwoSystems(usCurSysAcqIndex,
                                                            ucCurSysFreqIndex,
                                                            usOrigSysAcqIndex,
                                                            usOrigSysFreqIndex);
        return enSysPri;
    }

    return CNAS_PRL_SYS_PRI_LOW;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList
 ��������  : Comparing GEO list of both systems,  get the first same GEO in both
             lists

 �������  : pstCurSysGeoListInfo   -- the current system GEO list information
             pstOrigSysGeoListInfo  -- the orignal system GEO list information.

 �������  : none

 �� �� ֵ  : CNAS_PRL_MATCHED_GEO_INFO_STRU* -- return the same GEO information

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 28/11/2014
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    for (i = 0; i < pstCurSysGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstOrigSysGeoListInfo->ucGeoNum; j++)
        {
            if (pstCurSysGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex ==
                pstOrigSysGeoListInfo->astGeoInfoList[j].usGeoFirstSysRecIndex)
            {
                return &(pstCurSysGeoListInfo->astGeoInfoList[i]);
            }
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CompareSystemPreference
 ��������  : compare two systems, return the preferred result.
             1) if current system is more preferred than old system, return
                MORE;
             2) if current system is the same preferred than old system,
                return SAME;
             3) if current system is the less preferred than old system,
                return LESS

             NOTE: It implements function from chapter 2.11 in CDG 143:
                   When comparing two systems (that are available OTA),
                   MS shall step in order through the criteria listed in
                   the Remarks column to determine and select the more preferred
                   one. Once a criterion is met, MS shall use it and stop
                   going through the list.

 �������  : pstCurSysInfo  -- the current system synchronized.
             pstOrigSysInfo -- the previous camped system.
 �������  : none
 �� �� ֵ  : MORE -- more preferred
             SAME -- same preferred
             LESS -- less preferred
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareSystemPreference(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stOrigSysGeoListInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stCurSysGeoListInfo;
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32                       enSysPref;
    VOS_UINT32                                              ulCurMostPrefer;
    VOS_UINT32                                              ulOrigMostPrefer;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo = VOS_NULL_PTR;

    enSysPref = CNAS_PRL_SYS_PRI_UNKNOWN;

    /* Get the GEO list informaion of the orignal system */
    NAS_MEM_SET_S(&stOrigSysGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstOrigSysInfo, &stOrigSysGeoListInfo);

    /* Get the GEO list informaion of the synchronized system */
    NAS_MEM_SET_S(&stCurSysGeoListInfo, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stCurSysGeoListInfo);

    if ((0 != stOrigSysGeoListInfo.ucGeoNum)
     && (0 != stCurSysGeoListInfo.ucGeoNum))
    {
        pstMatchedGeoInfo = CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList(&stCurSysGeoListInfo,
                                                                   &stOrigSysGeoListInfo);
        if (VOS_NULL_PTR != pstMatchedGeoInfo)
        {
            /* reference from chapter 2.11 in CDG 143:
            1. If there is a GEO in the PRL that lists both systems, select the one that is listed as
               the more preferred in this GEO.
             - If both systems are listed in more than one GEO, only look in the first GEO (from top
               to bottom of the PRL system table) that lists both systems to determine the priority.
             - If both systems are listed at the same preference, select/stay on the original system
               (to avoid ping-pong effect).
            */

            enSysPref = CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo(pstCurSysInfo,
                                                                     pstOrigSysInfo,
                                                                     pstMatchedGeoInfo);

            return enSysPref;
        }

        /* reference from chapter 2.11 in CDG 143:
           3. If the roaming indicator of one system is more favorable than the other (as defined in
           Req. 2.6.2), select the more favorable one.
        */
        enSysPref = CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems(pstCurSysInfo,
                                                                           pstOrigSysInfo,
                                                                           &stCurSysGeoListInfo,
                                                                           &stOrigSysGeoListInfo);
        if ((CNAS_PRL_SYS_PRI_HIGH == enSysPref)
         || (CNAS_PRL_SYS_PRI_LOW  == enSysPref))
        {
            return enSysPref;
        }

        /* reference from chapter 2.11 in CDG 143:
           4. If one system is listed as most preferred system in its GEO, select that system.
        */
        ulCurMostPrefer  = CNAS_PRL_IsMostPref1xSysInGeo(pstCurSysInfo, &stCurSysGeoListInfo);
        ulOrigMostPrefer = CNAS_PRL_IsMostPref1xSysInGeo(pstOrigSysInfo, &stOrigSysGeoListInfo);

        if ((VOS_TRUE  == ulCurMostPrefer)
         && (VOS_FALSE == ulOrigMostPrefer))
        {
            return CNAS_PRL_SYS_PRI_HIGH;
        }

        if ((VOS_FALSE  == ulCurMostPrefer)
         && (VOS_TRUE   == ulOrigMostPrefer))
        {
            return CNAS_PRL_SYS_PRI_LOW;
        }

        /* reference from chapter 2.11 in CDG 143:
            5. If the position of channels in the PRL acquisition table is different, select the system
               for which its channel is listed first. The position of the channel is determined by the
               first appearance of that channel in the acquisition table when traversed from top to bottom.
        */
        enSysPref = CNAS_PRL_CompareChannelPreferenceOfTwoSystems(pstCurSysInfo, pstOrigSysInfo);

        return enSysPref;
    }

    /* reference from chapter 2.11 in CDG 143:
       2. If only one system is listed in the PRL system table (as a preferred system), select
          the one that is listed in the PRL.
    */
    if (0 != stCurSysGeoListInfo.ucGeoNum)
    {
        /* current system is in PRL */
        return CNAS_PRL_SYS_PRI_HIGH;
    }

    if (0 != stOrigSysGeoListInfo.ucGeoNum)
    {
        /* orignal system is in PRL */
        return CNAS_PRL_SYS_PRI_LOW;
    }

    /* could not determine the preference while both systems are not in PRL */
    return CNAS_PRL_SYS_PRI_UNKNOWN;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_CalcMatchedGeoListTotalFreqNum
 ��������  : calculate the totoal frequency number of the matched GEO list
 �������  : pstGeoListInfo----matched geo list info
 �������  : NONE

 �� �� ֵ  : the totoal number of the geo list channel
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 3/1/2015
    ��    ��   : w00176964
    �޸�����   : Create

*****************************************************************************/
VOS_UINT16 CNAS_PRL_CalcMatchedGeoListTotalFreqNum(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord  = VOS_NULL_PTR;
    VOS_UINT16                          usSysRecordNum;
    VOS_UINT16                          i;
    VOS_UINT16                          usMaxGeoChanNum;
    VOS_UINT16                          usGeoSysRecordNum;

    usMaxGeoChanNum     = 0;
    usSysRecordNum      = 0;
    usGeoSysRecordNum   = 0;

    /* calculate the system record numbers */
    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstGeoListInfo->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        usGeoSysRecordNum += pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum;
    }

    pstSysRecord = PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * usGeoSysRecordNum);

    /* alloc memory fail,return */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        return usMaxGeoChanNum;
    }

    CNAS_PRL_BuildGeoSysRecList(pstSysInfo, pstGeoListInfo, VOS_TRUE, &usSysRecordNum, pstSysRecord);

    /* calculate max size of the channuel number */
    usMaxGeoChanNum                 = CNAS_PRL_CalcPrlSysRecListTotalFreqNum(usSysRecordNum, pstSysRecord);

    /* free the memory of pstSysRecord */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);

    return usMaxGeoChanNum;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetBandChanMatchInfoOfGeoSys
 ��������  : ��ȡGEO��Band��Channel��ƥ��ȼ�
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
             CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstGeoInfo
 �������  : ��
 �� �� ֵ  : CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetBandChanMatchInfoOfGeoSys(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstGeoInfo
)
{
    VOS_UINT16                                              usFirstSysRecIndex;
    VOS_UINT16                                              usGeoSysRecNum;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMostMatch;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord          = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMostMatchSysRecord = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord          = VOS_NULL_PTR;
    VOS_UINT16                                              usIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrlSidNidMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enPrlSidNidMostMatchLvl;

    usFirstSysRecIndex      = pstGeoInfo->usGeoFirstSysRecIndex;
    usGeoSysRecNum          = pstGeoInfo->usGeoSysRecNum;
    enPrlSidNidMostMatchLvl = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    enBandChannelMostMatch  = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    for (usIndex = usFirstSysRecIndex; usIndex < (usFirstSysRecIndex + usGeoSysRecNum); usIndex++)
    {
        /* ���λ�ȡϵͳ��¼��������Ӧ��ϵͳ��¼��Ϣ */
        pstSysRecord  = CNAS_PRL_GetSpecifiedPrlSysRecord(usIndex);

        if (VOS_NULL_PTR !=  pstSysRecord)
        {
            /*  ��ȡSID NIDƥ��ȼ���*/
            enPrlSidNidMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstSysRecord);

            /* ��ȡϵͳ��¼�л�ȡ��¼��������Ӧ�Ļ�ȡ��¼��Ϣ*/
            pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

            if (VOS_NULL_PTR != pstAcqRecord)
            {
                /*  ��ȡband channelƥ��ȼ���*/
                enBandChannelMatch  = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

                if (enPrlSidNidMatchLvl > enPrlSidNidMostMatchLvl)
                {
                    enPrlSidNidMostMatchLvl  = enPrlSidNidMatchLvl;
                    pstMostMatchSysRecord    = pstSysRecord;
                    enBandChannelMostMatch   = enBandChannelMatch;
                }
                else if (enPrlSidNidMatchLvl == enPrlSidNidMostMatchLvl)
                {
                    /*SID NIDƥ�����ȼ���ͬ�������Ƚ�band channelƥ�����ȼ��ȼ� */
                    if (enBandChannelMatch > enBandChannelMostMatch)
                    {
                        enBandChannelMostMatch = enBandChannelMatch;
                        pstMostMatchSysRecord  = pstSysRecord;
                    }
                }
                else
                {}
            }
        }
    }

    if (VOS_NULL_PTR != pstMostMatchSysRecord)
    {
         /* ��ȡϵͳ��¼�л�ȡ��¼��������Ӧ�Ļ�ȡ��¼��Ϣ*/
        pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstMostMatchSysRecord->usAcqIndex);

        if (VOS_NULL_PTR != pstAcqRecord)
        {
            /* ��ȡBandChannel ƥ��ȼ�*/
            enBandChannelMostMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

            return enBandChannelMostMatch;
        }

    }

    return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList
 ��������  : ��GEO list�л�ȡ��ƥ���GEO ��Ϣ
 �������  : pstGeoListInfo -- ƥ���GEO List

 �������  : pstGeoInfo -- ������match��GEO��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    VOS_UINT8                                               i;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;

    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMostMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChanMatchLevel;

    /* ��ʼ���׸�GEOΪ��match GEO */
    pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[0]);

    for (i = 1; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstMostMatchGeoInfo->enMatchLvl < pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[i]);
        }
        else if (pstMostMatchGeoInfo->enMatchLvl == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            enBandChanMostMatchLevel = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, pstMostMatchGeoInfo);
            enBandChanMatchLevel     = CNAS_PRL_GetBandChanMatchInfoOfGeoSys(pstSysInfo, &(pstGeoListInfo->astGeoInfoList[i]));

            if (enBandChanMostMatchLevel < enBandChanMatchLevel)
            {
                pstMostMatchGeoInfo = &(pstGeoListInfo->astGeoInfoList[i]);
            }

        }
        else
        {}
    }

    return pstMostMatchGeoInfo;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList
 ��������  : ��GEO list�л�ȡ������ƥ���GEO��Ϣ
 �������  : pstGeoListInfo          -- ƥ���GEO List
             pstMostMatchGeoListInfo -- ƥ��ȼ����GEO list��Ϣ

 �������  : ��
 �� �� ֵ  : ����������ƥ���GEO
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
)
{
    VOS_UINT8                                               i;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;

    /* ��GEO list���ҳ���ƥ���GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstSysInfo, pstGeoListInfo);

    /* ��������GEO������ƥ���GEO�ȼ���ͬ��GEO, ���������match GEO list�� */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstMostMatchGeoInfo->enMatchLvl == pstGeoListInfo->astGeoInfoList[i].enMatchLvl)
        {
            NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[pstMostMatchGeoListInfo->ucGeoNum]),
                          sizeof(CNAS_PRL_MATCHED_GEO_INFO_STRU),
                          &(pstGeoListInfo->astGeoInfoList[i]),
                          sizeof(CNAS_PRL_MATCHED_GEO_INFO_STRU));

            pstMostMatchGeoListInfo->ucGeoNum++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord
 ��������  : ��GEO list�л�ȡ������ƥ���GEO��Ϣ
 �������  : pstFreq      -- Ƶ����Ϣ
             pstAcqRecord -- ������¼��Ϣ

 �������  : ��
 �� �� ֵ  : ����������ƥ���GEO
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord
)
{
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stFreqInfo;
    VOS_UINT8                                               i;

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstAcqRecord, &stFreqInfo);

    enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;

    for (i = 0; i < CNAS_MIN(stFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++ )
    {
        if (pstFreq->enBandClass == stFreqInfo.astFreqInfo[i].enBandClass)
        {
            enBandChannelMatch = CNAS_PRL_BAND_MATCH;

            if (pstFreq->usChannel == stFreqInfo.astFreqInfo[i].usChannel)
            {
                enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_MATCH;
                break;
            }
        }
    }

    return enBandChannelMatch;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsCurrentSystemInHomeSidNidList
 ��������  : ��鵱ǰϵͳ�Ƿ���Home SID/NID List��
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_PRL_IsCurrentSystemInHomeSidNidList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    VOS_UINT8                           i;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList = VOS_NULL_PTR;

    pstHomeSidNidList = CNAS_CCB_GetHomeSidNidList();

    for (i = 0; i < CNAS_MIN(pstHomeSidNidList->ucSysNum, CNAS_CCB_MAX_HOME_SID_NID_LIST); i++)
    {
        /* 3gpp2 CS0005 2.6.5.3�½�:
           The mobile station may use the special NID value 65535 to indicate that
           the mobile station considers all NIDs within a SID to be non-roaming */

        /* ����Э���˵��NID������ͨ���������SIDΪͨ����������������� */
        if ((CNAS_PRL_WILDCARD_SID != pstHomeSidNidList->astHomeSidNid[i].usSid)
         && (pstCurSysInfo->usSid  == pstHomeSidNidList->astHomeSidNid[i].usSid))
        {
            /* NID��Ȼ���ͨ��� */
            if ((pstCurSysInfo->usNid  == pstHomeSidNidList->astHomeSidNid[i].usNid)
             || (CNAS_PRL_WILDCARD_NID == pstHomeSidNidList->astHomeSidNid[i].usNid))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetSpecifiedPrlValidAcqRecord
 ��������  : ��ȡָ����ЧPRL�����¼��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ��PRL�����¼��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��29��
   ��    ��   : d00212987
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidAcqRecord(VOS_UINT16 usIndex)
{
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRecord;

    if ((usIndex < CNAS_PRL_GetPrlAcqRecordNum()) && (usIndex < CNAS_PRL_ACQ_RECORD_MAX_NUM))
    {
        pstPrlAcqRecord = (CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo.pastPrlAcqRecord[usIndex]);

        if (VOS_FALSE == pstPrlAcqRecord->ucAcqValid)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_PRL_GetSpecifiedPrlValidAcqRecord: AcqRecValid is False,index is", usIndex);
            return VOS_NULL_PTR;
        }

        return pstPrlAcqRecord;
    }

    return VOS_NULL_PTR;
}
/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetSpecifiedPrlValidSysRecord
 ��������  : ��ȡָ������ЧPRLϵͳ��¼��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ��PRLϵͳ��¼��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��29��
   ��    ��   : d00212987
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidSysRecord(VOS_UINT16 usIndex)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    /* ������� */
    if ((usIndex < CNAS_PRL_GetPrlSysRecordNum()) && (usIndex < CNAS_PRL_SYS_RECORD_MAX_NUM))
    {
        /* ��ת��ָ��������ϵͳ��¼��ַ */
        pstSysRecord = (CNAS_PRL_EXT_SYS_RECORD_STRU *)(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.pstSysRecord + usIndex);

        /* �жϼ�¼���� */
        if (VOS_FALSE == pstSysRecord->ucSysRecValid)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecNum: SysRecValid is False,index is", usIndex);
            return VOS_NULL_PTR;
        }

        return pstSysRecord;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CmpFreqValue
 ��������  : �Ƚ�����Ƶ���Ƿ����
 �������  : pstSrcFreq  - ԴƵ��
             pstDstFreq  - ���Ƚ�Ƶ��

 �������  : ��

 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT32 CNAS_PRL_CmpFreqValue(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSrcFreq,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstFreq
)
{
    if ((VOS_NULL_PTR == pstSrcFreq) || (VOS_NULL_PTR == pstDstFreq))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_CmpFreqValue: para is NULL!");

        return VOS_FALSE;
    }

    if ((pstSrcFreq->enBandClass == pstDstFreq->enBandClass)
         && (pstSrcFreq->usChannel   == pstDstFreq->usChannel))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CmpSubnetValue
 ��������  : �Ƚ�����Subnet�Ƿ����
 �������  : pucSrcSubnet  - ԴSubnet
             pucDstSubnet  - ���Ƚ�Subnet
             ulCmpLen      - ���Ƚϳ���

 �������  : ��

 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT32 CNAS_PRL_CmpSubnetValue(
    VOS_UINT8                          *pucSrcSubnet,
    VOS_UINT8                          *pucDstSubnet,
    VOS_UINT32                          ulCmpLen
)
{
    if ((VOS_NULL_PTR == pucSrcSubnet) || (VOS_NULL_PTR == pucDstSubnet))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_CmpSubnetValue: para is NULL!");

        return VOS_FALSE;
    }

    if (VOS_OK == PS_MEM_CMP(pucSrcSubnet, pucDstSubnet, ulCmpLen))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsHrpdSubnetMatched
 ��������  : �ж�SubnetId�Ƿ�ƥ��
 �������  : pucOTASubnetid           - �տ�����Subnet Id
             ucOTASubnetidBitSize     - �տ�����Subnet Id bit����(��λ:bit)
             pucSysRecSubnetid        - SYS RECORD��ŵ�Subnet Id
             ucSysRecSubnetidBitSize  - SYS RECORD��ŵ�Subnet Id bit����(��λ:bit)

 �������  : ��

 �� �� ֵ  : CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_IsHrpdSubnetMatched(
    VOS_UINT8                          *pucOTASubnetid,
    VOS_UINT8                           ucOTASubnetidBitSize,
    VOS_UINT8                          *pucSysRecSubnetid,
    VOS_UINT8                           ucSysRecSubnetidBitSize
)
{
    VOS_UINT8                           ucSrcSubnetid;
    VOS_UINT8                           ucDstSubnetid;
    VOS_UINT8                           ucSubnetTempLen;
    VOS_UINT8                           ucSubnetBitTempLen;   /* ���Subneʣ��bit���� */

    if ((VOS_NULL_PTR == pucOTASubnetid) || (VOS_NULL_PTR == pucSysRecSubnetid))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_IsHrpdSubnetMatched: para is NULL!");
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* OTA����С��PRL Subnet���� */
    if (ucOTASubnetidBitSize < ucSysRecSubnetidBitSize)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_IsHrpdSubnetMatched: OTA TOO Small!");

        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* �Ƿ���ͨ�� */
    if (0 == ucSysRecSubnetidBitSize)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;
    }

    ucSubnetTempLen = (ucSysRecSubnetidBitSize / CNAS_PRL_BIT_LEN_8_BIT);

    /* SYS RECORD subnet����bit�������ȱȽ����ֽ� */
    if (VOS_TRUE != CNAS_PRL_CmpSubnetValue(pucOTASubnetid, pucSysRecSubnetid, ucSubnetTempLen))
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* �ٱȽ�ʣ��bit */
    ucSubnetBitTempLen = (ucSysRecSubnetidBitSize % CNAS_PRL_BIT_LEN_8_BIT);
    if (0 < ucSubnetBitTempLen)
    {
        ucSrcSubnetid = CNAS_PRL_ExtractBitStringToOctet(&pucOTASubnetid[ucSubnetTempLen], 0, ucSubnetBitTempLen);
        ucDstSubnetid = CNAS_PRL_ExtractBitStringToOctet(&pucSysRecSubnetid[ucSubnetTempLen], 0, ucSubnetBitTempLen);
        if (ucSrcSubnetid != ucDstSubnetid)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
        }
    }

    return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsHrpdFreqMatched
 ��������  : �ж�Hrpd ��Ƶ���Ƿ�ƥ��
 �������  : usAcqIndex  - Acq������
             pstFreq     - Ƶ��

 �������  : ��

 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0
*****************************************************************************/
CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_IsHrpdFreqMatched(
    VOS_UINT16                          usAcqIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstPrlAcqRecord;
    CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU                     *pstHrpdSys;
    VOS_UINT32                                              i;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    pstPrlAcqRecord = CNAS_PRL_GetSpecifiedPrlValidAcqRecord(usAcqIndex);

    /* ������� */
    if (VOS_NULL_PTR == pstPrlAcqRecord)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_IsHrpdFreqMatched: usAcqIndex out of range", usAcqIndex);
        return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    }

    /* �Ƿ�ΪHRPD ACQ */
    if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD != pstPrlAcqRecord->enAcqType)
    {
        return CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    }

    enBandChannelMatch  = CNAS_PRL_BAND_CHANNEL_NOT_MATCH;
    pstHrpdSys          = &(pstPrlAcqRecord->u.stHrpdSys);

    for (i = 0; i < pstHrpdSys->ucNumOfChans; i++ )
    {
        if (pstFreq->enBandClass == pstHrpdSys->astFreq[i].enBandClass)
        {
            enBandChannelMatch = CNAS_PRL_BAND_MATCH;

            if (pstFreq->usChannel == pstHrpdSys->astFreq[i].usChannel)
            {
                enBandChannelMatch = CNAS_PRL_BAND_CHANNEL_MATCH;
                break;
            }
        }
    }

    return enBandChannelMatch;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetHrpdSysRecByIndex
 ��������  : ��ȡIndex ��Ӧ�� Hrpd SYS RECORD��¼
 �������  : Index    - Hrpd SYS RECORD Index

 �������  : NA

 �� �� ֵ  : ��ȡ����Hrpd SYS RECORD
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
CNAS_PRL_EXT_SYS_RECORD_STRU* CNAS_PRL_GetHrpdSysRecByIndex(VOS_UINT16 usIndex)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord;

    pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(usIndex);

    /* ������� */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_GetHrpdSysRecByIndex: usIndex out of range", usIndex);
        return VOS_NULL_PTR;
    }

    /* ��HRPD */
    if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_PRL_GetHrpdSysRecByIndex: is not Hrpd");
        return VOS_NULL_PTR;
    }

    return pstSysRecord;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetHrpdSysRecMatchLvl
 ��������  : ��ǰ��HRPDϵͳ�Ƿ��ϵͳ��¼��ƥ��
 �������  : pstHrpdSystem - ��Ҫ�Ƚ�HRPDϵͳ
             pstSysRecord  - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0
  2.��    ��   : 2015��07��17��
    ��    ��   : x00306642
    �޸�����   : ����MMC-MNC�Ĵ���

*****************************************************************************/
CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16     enMatchLevel;

    /* ��HRPD */
    if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    /* �ж�Subnetƥ��ȼ� */
    if ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType))
    {
        enMatchLevel = CNAS_PRL_GetHrpdSysRecMatchLvl_MccMncBased(pstHrpdSystem, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_HRPD == pstSysRecord->enRecordType)
    {
        enMatchLevel = CNAS_PRL_GetHrpdSysRecMatchLvl_IS856(pstHrpdSystem, pstSysRecord);
    }
    else
    {
        enMatchLevel = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    }

    return enMatchLevel;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_RecordMostMatchLvlGeoIndex
 ��������  : ������MATCH LEVEL Index
 �������  : pst1xGeoInfoEx     - �����Ƶ�����
             penMatchLvl        - ��������GEO�б���Ϣ�������PRL�в����ڣ��򷵻صĸ���Ϊ0
             enGet1xSysMatchLvl - ���MATCH LEVEL
             usSysRecIndex      - SYS RECORD Index

 �������  : penMatchLvl - ��ȡ�������MATCH LEVEL

 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_VOID CNAS_PRL_RecordMostMatchLvlGeoIndex(
    CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU                   *pst1xGeoInfoEx,
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                 *penMatchLvl,
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enGet1xSysMatchLvl,
    VOS_UINT16                                              usSysRecIndex
)
{
    if ((*penMatchLvl                             == enGet1xSysMatchLvl) &&
        (CNAS_HSD_MAX_MATCH_LVL_SYS_REC_INDEX_NUM > pst1xGeoInfoEx->us1xSysIndexNum))
    {
        /* ���index */
        pst1xGeoInfoEx->aus1xSysIndex[pst1xGeoInfoEx->us1xSysIndexNum] = usSysRecIndex;
        pst1xGeoInfoEx->us1xSysIndexNum++;
    }

    /* ���ƥ��̶�����ߣ������ƥ��̶� */
    if (*penMatchLvl < enGet1xSysMatchLvl)
    {
        *penMatchLvl  = enGet1xSysMatchLvl;

        /* ���֮ǰ��ŵ�index */
        pst1xGeoInfoEx->us1xSysIndexNum = 0;

        /* ��ŵ�ǰindex */
        pst1xGeoInfoEx->aus1xSysIndex[pst1xGeoInfoEx->us1xSysIndexNum] = usSysRecIndex;
        pst1xGeoInfoEx->us1xSysIndexNum++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysGeoListEx
 ��������  : ��SYS RECORD�л�ȡGeo�б�
 �������  : pstSysInfo     - �����Ƶ�����
             pst1xGeoListEx - ��������GEO�б���Ϣ�������PRL�в����ڣ��򷵻صĸ���Ϊ0

 �������  : pst1xGeoListEx - ��ȡ����GEO�б���Ϣ

 �� �� ֵ  : ��ȡ����GEO�б����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_VOID CNAS_PRL_Get1xSysGeoListEx(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_1X_GEO_LIST_INFO_EX_STRU              *pst1xGeoListEx
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstTmpSysRecord;
    CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU                   *pstTmp1xGeoInfoEx;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enTmpMatchLvl;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT32                                              ulIsMatched;
    VOS_UINT16                                              i;

    enMatchLvl                   = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
    ulIsMatched                  = VOS_FALSE;
    usGeoFirstSysRecIndex        = 0;
    pstTmp1xGeoInfoEx            = VOS_NULL_PTR;

    /* ��ʼ��������� */
    pst1xGeoListEx->ucGeoNum    = 0;
    pst1xGeoListEx->usSid       = pstSysInfo->usSid;
    pst1xGeoListEx->usNid       = pstSysInfo->usNid;

    for (i = 0; i < CNAS_PRL_GetPrlSysRecordNum(); i++)
    {
        pstTmpSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstTmpSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_PRL_Get1xSysGeoListEx: Get SysRecord is Null,i is", i);
            continue;
        }

        /* ÿ�ν��µ�GEO���ж�֮ǰ������ʱ���Ƿ����matach�ļ�¼ */
        if (CNAS_PRL_GEO_REGION_IND_NEW == pstTmpSysRecord->enGeoInd)
        {
            if (VOS_TRUE == ulIsMatched)
            {
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].enMatchLvl            = enMatchLvl;
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
                pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoSysRecNum        = i - usGeoFirstSysRecIndex;
                pst1xGeoListEx->ucGeoNum++;

                /* �ж�GEO NUM�Ƿ�Ϸ� */
                if (CNAS_PRL_MAX_MATCHING_GEO_NUM <= pst1xGeoListEx->ucGeoNum)
                {
                    CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_PRL_Get1xSysGeoListEx: GeoNum is", pst1xGeoListEx->ucGeoNum);
                    return;
                }

                ulIsMatched = VOS_FALSE;
                enMatchLvl  = CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH;
            }

            usGeoFirstSysRecIndex = i;
        }

        /* �Ƿ�����1X */
        if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 != pstTmpSysRecord->enRecordType)
        {
            continue;
        }

        /* �Ƿ���NEG */
        if (CNAS_PRL_PREF_NEG_SYS_NEG == pstTmpSysRecord->enPrefNegSys)
        {
            continue;
        }

        /* �жϴ����ϵͳ��Ϣ���Ƿ��ϵͳ��¼�е���ƥ�� */
        enTmpMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordLvl(pstSysInfo, pstTmpSysRecord);

        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH != enTmpMatchLvl)
        {
            ulIsMatched = VOS_TRUE;

            pstTmp1xGeoInfoEx = &(pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum]);

            /* ��¼���MATCH LEVEL Index��������ĸ� */
            CNAS_PRL_RecordMostMatchLvlGeoIndex(pstTmp1xGeoInfoEx, &enMatchLvl, enTmpMatchLvl, i);
        }
    }

    if (VOS_TRUE == ulIsMatched)
    {
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].enMatchLvl            = enMatchLvl;
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
        pst1xGeoListEx->ast1xGeoInfoListEx[pst1xGeoListEx->ucGeoNum].usGeoSysRecNum        = i - usGeoFirstSysRecIndex;

        pst1xGeoListEx->ucGeoNum++;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetMatchLvl_MccMncBased_SubTypeMulSid
 ��������  : ��ȡMCC-MNC���ͣ�������Ϊ��SID�ļ�¼ƥ��ȼ�
 �������  : pstSysInfo   - ��ǰϵͳ��Ϣ
             pstSysRecord - ϵͳ��¼������

 �������  : ��

 �� �� ֵ  : sys reord��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsSidNidMatch_MccMncBased(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_TYPE_SID_NID_STRU                         *pstSidNid = VOS_NULL_PTR;
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU                      *pstMccMncId = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstSidNid   = &(pstSysRecord->u.stMccMncId.u.stSidNid);
    pstMccMncId = &(pstSysRecord->u.stMccMncId);

    if ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID != pstMccMncId->enMccMncSubType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID != pstMccMncId->enMccMncSubType) )
    {
        return VOS_FALSE;
    }

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSidNid->ucSidNidNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM);i++)
    {
        /* ���SID���ҵ���˵��SID��ȷƥ�䣬NIDͨ�� */
        if ( ( (pstSysInfo->usSid == pstSidNid->asSid[i])
            || (CNAS_PRL_WILDCARD_SID == pstSidNid->asSid[i]) )
          && ( (pstSysInfo->usNid == pstSidNid->asNid[i])
            || (CNAS_PRL_WILDCARD_NID == pstSidNid->asNid[i]) ) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetBand0PrefChanTab
 ��������  : ��ȡBand0�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU
             ����BAND0��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand0PrefChanTab(VOS_VOID)
{
    return g_astCnasPrlBand0Tab;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetBand0PrefChanTabSize
 ��������  : ��ȡBand0�б��С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             ����BAND0���ݴ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_GetBand0PrefChanTabSize(VOS_VOID)
{
    return (sizeof(g_astCnasPrlBand0Tab)/sizeof(CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetBand10PrefChanTabSize
 ��������  : ��ȡBand10�����ݴ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             ����BAND10�������ݱ��С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_GetBand10PrefChanTabSize(VOS_VOID)
{
    return (sizeof(g_astCnasPrlBand10Tab)/sizeof(CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetBand10PrefChanTab
 ��������  : ��ȡBand10�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU
             ����BAND10��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand10PrefChanTab(VOS_VOID)
{
    return g_astCnasPrlBand10Tab;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Is1xSysRecord
 ��������  : �ж�ϵͳ��¼�Ƿ����
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��4��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

  2.��    ��   : 2015��8��20��
    ��    ��   : w00242748
    �޸�����   : DTS2015081904804

*****************************************************************************/
VOS_UINT8 CNAS_PRL_Is1xSysRecord(
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSysRecord
)
{
    if ((VOS_NULL_PTR                     == pstSysRecord)
     || (VOS_FALSE                        == pstSysRecord->ucSysRecValid))
    {
        return VOS_FALSE;
    }

    if ( (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
      || ( (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
        && ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstSysRecord->u.stMccMncId.enMccMncSubType)
          || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord->u.stMccMncId.enMccMncSubType) ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsHrpdSysRec
 ��������  : �ж�ϵͳ��¼�Ƿ�ΪHRPD���͵�
 �������  : pstSysRecord     - ϵͳ��¼

 �������  : ��

 �� �� ֵ  : �жϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��16��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsHrpdSysRec(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    if ((CNAS_PRL_SYS_RECORD_TYPE_HRPD == pstSysRecord->enRecordType)
     || ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID == pstSysRecord->u.stMccMncId.enMccMncSubType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetHrpdSysRecMatchLvl_IS856
 ��������  : ��ǰ��HRPDϵͳ�Ƿ��ϵͳ��¼�е�IS856ϵͳ��ƥ��
 �������  : pstHrpdSystem  - ��ƥ���ϵͳ
             pstSysRecord   - HRPDϵͳ��

 �������  : ��

 �� �� ֵ  : ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��16��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��30��
    ��    ��   : z00316370
    �޸�����   : ����ͨ�������ƥ��ȼ�
*****************************************************************************/
CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_IS856(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMatchLevel;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;

    enMatchLevel = CNAS_PRL_IsHrpdSubnetMatched(pstHrpdSystem->aucSubnet,
                                                pstHrpdSystem->ucSubnetMask,
                                                pstSysRecord->u.stIs856Id.aucSubnet,
                                                pstSysRecord->u.stIs856Id.ucSubnetBitLen);

    if (CNAS_PRL_SUBNET_MATCH_LVL_SUBNET == enMatchLevel)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
    }

    if (CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD == enMatchLevel)
    {
        /* �ж�Freq �Ƿ�ƥ�� */
        enBandChannelMatch = CNAS_PRL_IsHrpdFreqMatched(pstSysRecord->usAcqIndex,
                                                        &(pstHrpdSystem->stFreq));
        if (CNAS_PRL_BAND_CHANNEL_MATCH == enBandChannelMatch)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND_CHANNEL;
        }
        else if (CNAS_PRL_BAND_MATCH == enBandChannelMatch)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND;
        }
        else
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;
        }
    }

    return CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetHrpdSysRecMatchLvl_IS856
 ��������  : ��ǰ��HRPDϵͳ�Ƿ��ϵͳ��¼�е�IS856ϵͳ��ƥ��
 �������  : pstHrpdSystem  - ��ƥ���ϵͳ
             pstSysRecord   - HRPDϵͳ��

 �������  : ��

 �� �� ֵ  : ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��16��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��30��
    ��    ��   : z00316370
    �޸�����   : ����ͨ�������ƥ��ȼ�

*****************************************************************************/
CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_MccMncBased(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU                       *pstSubnetId;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enSubnetMatchLevel;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMatchLevel;
    VOS_UINT16                                              i;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enMostFreqMatch;

    enMatchLevel            = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    enMostFreqMatch         = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;

    pstSubnetId             = pstSysRecord->u.stMccMncId.u.pstSubnetId;

    for (i = 0; i < CNAS_MIN((VOS_UINT32)pstSubnetId->ucSubnetNum, CNAS_PRL_MCC_MNC_SID_MAX_NUM); i++)
    {
        enSubnetMatchLevel = CNAS_PRL_IsHrpdSubnetMatched(pstHrpdSystem->aucSubnet,
                                                          pstHrpdSystem->ucSubnetMask,
                                                          pstSubnetId->aucSubnetID[i],
                                                          pstSubnetId->aucSubnetLen[i]);

        if (CNAS_PRL_SUBNET_MATCH_LVL_SUBNET == enSubnetMatchLevel)
        {
            return CNAS_PRL_SUBNET_MATCH_LVL_SUBNET;
        }

        if (CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD == enSubnetMatchLevel)
        {
            enMatchLevel       =   CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD;

            enBandChannelMatch = CNAS_PRL_IsHrpdFreqMatched(pstSysRecord->usAcqIndex,
                                                        &(pstHrpdSystem->stFreq));

            if (enBandChannelMatch > enMostFreqMatch)
            {
                enMostFreqMatch = enBandChannelMatch;
            }
        }
    }

    if (CNAS_PRL_BAND_CHANNEL_MATCH == enMostFreqMatch)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND_CHANNEL;
    }
    else if (CNAS_PRL_BAND_MATCH == enMostFreqMatch)
    {
        return CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND;
    }
    else
    {
        return enMatchLevel;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysMatchSysRecordCustomLvl
 ��������  : ��ǰ��1Xϵͳ�Ƿ��ϵͳ��¼��ƥ��
 �������  : usSrcSid - ��Ҫ�Ƚϵ�SID�� usSrcNid - ��Ҫ�Ƚϵ�NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : SID��NID��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_ConvertStandardMatchLvlToCustom(
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enStandardMatchLvl
)
{
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enCustomMatchLvl;

    enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_BUTT;

    switch ( enStandardMatchLvl )
    {
        case CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_NID;
            break;
        case CNAS_PRL_SID_NID_MATCH_LVL_SID_NID :
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_SID_NID;
            break;
        default:
            enCustomMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_BUTT;
            break;
    }

    return enCustomMatchLvl;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetCustomMatchLvl_OnlySidNidBandMatch
 ��������  : ��Bandƥ�������£���Ӧ��sys record��ƥ�伶��
 �������  : pstSysRecord - ϵͳ��¼������
 �������  : ��

 �� �� ֵ  : sys reord��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetCustomMatchLvl_OnlySidNidBandMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{

    CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8                       enWildCardType;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enMatchLvl;

    enWildCardType = CNAS_PRL_GetPrlSysRecordWildCardType(pstSysInfo, pstSysRecord);

    switch (enWildCardType)
    {
        case CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_SID_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_NID:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_NID;
            break;

        case CNAS_PRL_WILDCARD_TYPE_SID:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID_EXCEPT_CHANNEL;
            break;

        case CNAS_PRL_WILDCARD_TYPE_UNKNOWN:
        default:
            enMatchLvl = CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
            break;
    }

    return enMatchLvl;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_Get1xSysMatchSysRecordCustomLvl
 ��������  : ��ǰ��1Xϵͳ�Ƿ��ϵͳ��¼��ƥ��
 �������  : usSrcSid - ��Ҫ�Ƚϵ�SID�� usSrcNid - ��Ҫ�Ƚϵ�NID
             pstSysRecord - ���Ƚϵ�ϵͳ��¼
 �������  : ��

 �� �� ֵ  : SID��NID��ƥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord;
    VOS_UINT32                                              ulIsSidNidMatched;
    CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8             enBandChannelMatch;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enStandardMatchLvl;

    ulIsSidNidMatched      = VOS_FALSE;

     /* ϵͳ��¼��Ч�������� */
    if (VOS_FALSE == pstSysRecord->ucSysRecValid)
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_1XIS95(pstSysInfo, pstSysRecord);
    }
    else if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
    {
        ulIsSidNidMatched = CNAS_PRL_IsSidNidMatch_MccMncBased(pstSysInfo, pstSysRecord);
    }
    else
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    /* ���SID��NID����ƥ�䣬��ʱ��ǰϵͳ�϶���ϵͳ��¼��ƥ�� */
    if ( VOS_FALSE == ulIsSidNidMatched )
    {
        return CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH;
    }

    pstAcqRecord  = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);

    /* ��ָ�뱣�� */
    if (VOS_NULL_PTR == pstAcqRecord)
    {
        enStandardMatchLvl = CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);

        return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
    }

    enBandChannelMatch = CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(&(pstSysInfo->stFreq), pstAcqRecord);

    /* ���band��û��ƥ�䣬˵����ʱ����ƥ����SID��NID */
    if ( CNAS_PRL_BAND_CHANNEL_NOT_MATCH == enBandChannelMatch )
    {
        enStandardMatchLvl = CNAS_PRL_GetMatchLvl_OnlySidNidMatch(pstSysInfo, pstSysRecord);

        return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
    }

    /* ���CHANNELû��ƥ�䣬˵����ʱ����ƥ����SID��NID��BAND */
    if ( CNAS_PRL_BAND_MATCH == enBandChannelMatch )
    {
        return CNAS_PRL_GetCustomMatchLvl_OnlySidNidBandMatch(pstSysInfo, pstSysRecord);
    }

    /* ������˵����SID��NID��BAND��CHANNEL��ƥ�䣬����channelƥ������µ�ƥ��ȼ� */
    enStandardMatchLvl = CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(pstSysInfo, pstSysRecord);

    return CNAS_PRL_ConvertStandardMatchLvlToCustom(enStandardMatchLvl);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_BuildGeoListBasedOnSysRecord
 ��������  : ����ϵͳ��¼��Ϣ��ȡ��Ӧ��GEO
 �������  : pstCurSysInfo - ��ǰϵͳ
 �������  : pstGeoList - GEO�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_GetMostMultiMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMostMatchGeoListInfo
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecordAddr  = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord   = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                    stGeoInfo;
    VOS_UINT8                                               ucGeoNum;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enMatchLvl;
    VOS_UINT16                                              usGeoFirstSysRecIndex;
    VOS_UINT16                                              usMatchedIndexNum;


    NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));

    pstSysRecordAddr = CNAS_PRL_GetPrlSysInfoAddr();

    ucGeoNum = 0;

    /* ϵͳ��¼���һ����¼�����⴦�� */
    pstSysRecord      = pstSysRecordAddr->pstSysRecord;

    enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(pstCurSysInfo, pstSysRecord);

    NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));
    stGeoInfo.usGeoFirstSysRecIndex = 0;
    stGeoInfo.enGeoMostMatchLvl     = enMatchLvl;
    usGeoFirstSysRecIndex           = 0;

    if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != enMatchLvl)
    {
        stGeoInfo.astIndexList[enMatchLvl].ausMostMatchedIndex[0] = 0;
        stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum++;
    }

    for (i = 1; i < pstSysRecordAddr->usSysRecordNum; i++)
    {
        /* �õ���i����¼ */
        pstSysRecord      = pstSysRecordAddr->pstSysRecord + i;

        if (CNAS_PRL_GEO_REGION_IND_NEW == pstSysRecord->enGeoInd)
        {
            /* ��дGEO��ϵͳ��¼���� */
            stGeoInfo.usGeoSysRecNum        = i - usGeoFirstSysRecIndex;

            /* ������GEO���뵽GEO�б� */
            if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != stGeoInfo.enGeoMostMatchLvl)
            {
                CNAS_PRL_LogMultiMatchedGeoInfo(&stGeoInfo);

                ucGeoNum = pstMostMatchGeoListInfo->ucGeoNum;
                NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[ucGeoNum]), sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU), &stGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU));
                pstMostMatchGeoListInfo->ucGeoNum++;
            }

            /* ���GEO */
            NAS_MEM_SET_S(&stGeoInfo, sizeof(stGeoInfo), 0x00, sizeof(stGeoInfo));
            usGeoFirstSysRecIndex           = i;
            stGeoInfo.usGeoFirstSysRecIndex = usGeoFirstSysRecIndex;
        }

        enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordCustomLvl(pstCurSysInfo, pstSysRecord);

        if (stGeoInfo.enGeoMostMatchLvl < enMatchLvl)
        {
            stGeoInfo.enGeoMostMatchLvl = enMatchLvl;
        }

        if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != enMatchLvl)
        {
            usMatchedIndexNum = stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum;

            if (usMatchedIndexNum < CNAS_PRL_MAX_MATCHED_SYSTEM_NUM)
            {
                stGeoInfo.astIndexList[enMatchLvl].ausMostMatchedIndex[usMatchedIndexNum] = i;
                stGeoInfo.astIndexList[enMatchLvl].usMatchedIndexNum++;
            }
            else
            {
                NAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_GetMostMultiMatched1xGeoList MatchedIndexNum > CNAS_PRL_MAX_MATCHED_SYSTEM_NUM!");
            }
        }
    }

    /* ���һ��GEO�����⴦�� */
    stGeoInfo.usGeoSysRecNum = pstSysRecordAddr->usSysRecordNum - usGeoFirstSysRecIndex;

    if (CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH != stGeoInfo.enGeoMostMatchLvl)
    {
        CNAS_PRL_LogMultiMatchedGeoInfo(&stGeoInfo);

        ucGeoNum = pstMostMatchGeoListInfo->ucGeoNum;
        NAS_MEM_CPY_S(&(pstMostMatchGeoListInfo->astGeoInfoList[ucGeoNum]), sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU), &stGeoInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU));
        pstMostMatchGeoListInfo->ucGeoNum++;
    }

    pstMostMatchGeoListInfo->usSid = pstCurSysInfo->usSid;
    pstMostMatchGeoListInfo->usNid = pstCurSysInfo->usNid;

    CNAS_PRL_LogMultiMatchedGeoListInfo(pstMostMatchGeoListInfo);

    return;
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



