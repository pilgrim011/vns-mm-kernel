/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSdcCtx.c
  �� �� ��   : ����
  ��    ��   : s46746
  ��������   : 2012��12��25��

  ��������   : TAF�㹲���������ģ�����ȫ�ֱ��������Լ������ṩAPI�ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��25��
    ��    ��   : s46746
    �޸�����   : �����ļ�

****************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafSdcCtx.h"
#include "TafLog.h"

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, begin */

#include "TafNvInterface.h"
#include  "NasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-25, begin */
#if (FEATURE_IMS == FEATURE_ON)
#include  "ImsaNvInterface.h"
#endif

#include  "LNvCommon.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-25, end */


#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
#include  "LNasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */
#if (FEATURE_ON == FEATURE_BASTET)
#include  "TtfNvInterface.h"
#endif

#include  "NasUtranCtrlInterface.h"

#include  "MmaAppLocal.h"
#include "TafStdlib.h"

#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/

/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID PS_FILE_ID_TAFSDC_CTX_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
/* ����TAF�㹲�õ�CTX */
TAF_SDC_CTX_STRU                        g_stTafSdcCtx;

/*Ĭ�������ʹ�õ�GSM 7bit to ASCII��ת����*/
LOCAL VOS_UINT8 g_aucTafSdcDef7BitToAsciiTbl[] =
{
 '@', 0xA3, '$', 0xA5, 0xE8, 0xE9, 0xF9, 0xEC, 0xF2, 0xC7,0x0A, 0xD8, 0xF8,0x0D, 0xC5, 0xE5,
 '?', '_', '?', '?', '?', '?', '?', '?', '?', '?', '?',' ', 0xC6, 0xE6, 0xDF, 0xC9,
 ' ', '!',0x22, '#', 0x2A, '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xA1, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0xC4, 0xD6, 0xD1, 0xDC, 0xA7,
 0xBF, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0xE4, 0xF6, 0xF1, 0xFC, 0xE0
};


/*TME����ʹ�õ�GSM 7bit to ASCII��ת����*/
LOCAL VOS_UINT8 g_aucTafSdcTme7BitToAsciiTbl[] =
{
 '@', 0x9C, '$', 0x9D, 0x8A, 0x82, 0x97, 0x8D, 0x95, 0x80,0x0A, '?', '?',0x0D, 0x8F, 0x86,
 '?', '_', 0xE8, 0xE2, '?', 0xEA, 0xE3, '?',0xE4, 0xE9, '?','?', 0x92, 0x91, 0xE1, 0x90,
 ' ', '!',0x22, '#', '?', '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xAD, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0x8E, 0x99, 0xA5, 0x9A, '?',
 0xA8, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x84, 0x94, 0xA4, 0x81, 0x85
};

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */

LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsNoUsim[TAF_SDC_NUMOF_EMER_NUMS_NO_USIM] =
{
"112", "911", "000", "08", "110", "118", "119", "999"
};

LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsWithUsim[TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM] =
{"112", "911"};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
LOCAL VOS_CHAR *g_acTafSdcCdmaCallEmcNums[TAF_SDC_NUMOF_CDMA_PRESET_EMC_NUM] =
{
    "110", "112", "911", "999", "119", "120"
};
#endif
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSdcCtx
 ��������  : ��ȡ��ǰSDC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰSDC��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CTX_STRU*  TAF_SDC_GetSdcCtx( VOS_VOID )
{
    return &(g_stTafSdcCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetMsCapInfo
 ��������  : ��ȡMS��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMS������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���

*****************************************************************************/
TAF_SDC_MS_CAP_INFO_STRU*  TAF_SDC_GetMsCapInfo( VOS_VOID )
{
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, end */
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-16, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRoamFlag
 ��������  : ��ȡ��ǰ���α��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰϵͳģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRoamFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetRoamFlag
 ��������  : ���õ�ǰ���α��
 �������  : ��ǰפ������������α��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetRoamFlag(VOS_UINT8 ucRoamFlag)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag = ucRoamFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCampOnFlag
 ��������  : ��ȡ��ǰ�Ƿ�פ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰפ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCampOnFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCampOnFlag
 ��������  : ���õ�ǰ�Ƿ�פ�����
 �������  : ��ǰ�Ƿ�פ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCampOnFlag(VOS_UINT8 ucCampOnFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg = ucCampOnFlg;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-16, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_Set3GppRfAvailFlag
 ��������  : ���õ�ǰ�Ƿ�NO RF���
 �������  : ��ǰ�Ƿ�NO RF���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��05��29��
   ��    ��   : l00301449
   �޸�����   : CDMA Iteration 15
*****************************************************************************/
VOS_VOID TAF_SDC_Set3GppRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get3GppRfAvailFlag
 ��������  : ��ȡ��ǰ�Ƿ�NO RF���
 �������  : ��
 �������  : VOS_TRUE:  ��ǰNO RF
             VOS_FALSE: ��ǰ��NO RF
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��05��29��
   ��    ��   : l00301449
   �޸�����   : CDMA Iteration 15

*****************************************************************************/
VOS_UINT8 TAF_SDC_Get3GppRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Set1xRfAvailFlag
 ��������  : ���õ�ǰ1X��RF��־
 �������  : VOS_UINT8                           ucRfAvailFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_Set1xRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xRfAvailFlag
 ��������  : ��ȡ��ǰ1X��RF��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetHrpdRfAvailFlag
 ��������  : ���õ�ǰHRPD��RF��־
 �������  : VOS_UINT8                           ucRfAvailFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetHrpdRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg = ucRfAvailFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetHrpdRfAvailFlag
 ��������  : ��ȡ��ǰHRPD��RF��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetHrpdRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg);
}




/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSysMode
 ��������  : ��ȡ��ǰϵͳģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰϵͳģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSysMode
 ��������  : ���õ�ǰϵͳģʽ
 �������  : ��ǰϵͳģʽ���뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode = enSysMode;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSysSubMode
 ��������  : ��ȡ��ǰϵͳ��ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰϵͳ��ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode);
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSysSubMode
 ��������  : ���õ�ǰϵͳ��ģʽ
 �������  : ��ǰϵͳ��ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode = enSysSubMode;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get3gppSysInfo
 ��������  : ��ȡ����С��ϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����С��ϵͳ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_3GPP_SYS_INFO_STRU* TAF_SDC_Get3gppSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get3gppSysInfo
 ��������  : ��ȡ����С��ϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����С��ϵͳ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SYS_INFO_STRU* TAF_SDC_GetSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo);
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurrCampPlmnId
 ��������  : ���õ�ǰפ��plmn��Ϣ
 �������  : pstPlmnId - plmn id��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampPlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId = *pstPlmnId;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrCampPlmnId
 ��������  : ��ȡ��ǰפ��plmn id��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : plmn id��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetCurrCampPlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrCampLac
 ��������  : ��ȡ��ǰפ��lac��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : lac��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_SDC_GetCurrCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurrCampLac
 ��������  : ���õ�ǰפ��lac��Ϣ
 �������  : usLac - lac��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac = usLac;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrCampRac
 ��������  : ��ȡ��ǰפ��rac��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : rac��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCurrCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurrCampRac
 ��������  : ���õ�ǰפ��rac��Ϣ
 �������  : ucRac - rac��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac = ucRac;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrCampCellId
 ��������  : ��ȡ��ǰפ��cell id��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : cell id��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetCurrCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurrCampCellId
 ��������  : ���õ�ǰפ��cell id��Ϣ
 �������  : ulCellId - cell id��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrCampCellId(VOS_UINT32 ulCellId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId = ulCellId;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrLmmAccessType
 ��������  : ��ȡ��ǰפ����LTEС����TDD����FDD,פ��GUС��ʱ��ֵ��Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : enAccessType:EUTRAN_TDD/FDD
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 TAF_SDC_GetCurrLmmAccessType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurrLmmAccessType
 ��������  : ���õ�ǰפ����LTEС����TDD����FDD,פ��GUС��ʱ��ֵ��Ч
 �������  : enAccessType - EUTRAN_TDD/FDD
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCurrLmmAccessType(TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 enLmmAccessType)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType  = enLmmAccessType;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsServiceStatus
 ��������  : ��ȡcs�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : cs�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsServiceStatus
 ��������  : ����cs�����״̬
 �������  : cs�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsServiceStatus
 ��������  : ��ȡps�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ps�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsServiceStatus
 ��������  : ����ps�����״̬
 �������  : ps�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsAttachAllowFlg
 ��������  : ����ps�Ƿ�����ע���ʶ
 �������  : ucPsAttachAllowFlg - ps�Ƿ�����ע���ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsAttachAllowFlg(VOS_UINT8 ucPsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg = ucPsAttachAllowFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsAttachAllowFlg
 ��������  : ��ȡps�Ƿ�����ע���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ps�Ƿ�����ע���ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetServiceStatus
 ��������  : ����UE�ܷ���״̬
 �������  : enReportSrvsta - ����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetServiceStatus
 ��������  : ��ȡUE�ܷ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��4��3��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppServiceStatus
 ��������  : ����AppNetwork�е�UE�ܷ���״̬
 �������  : enReportSrvsta - ����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :

  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServiceStatus(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppServiceStatus
 ��������  : ��ȡAppNetwork�е�UE�ܷ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetAppServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetServiceDomain
 ��������  : ��ȡ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetServiceDomain
 ��������  : ���÷�����
 �������  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppServiceDomain
 ��������  : ��ȡAppNetwork�з�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII

*****************************************************************************/
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetAppServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppServiceDomain
 ��������  : ����AppNetwork�з�����
 �������  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServiceDomain(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsRegStatus
 ��������  : ��ȡcsע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : csע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsRegStatus
 ��������  : ����csע��״̬
 �������  : csע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCsRegStatus
 ��������  : ��ȡAppNetworkInfo csע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : csע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCsRegStatus
 ��������  : ����AppNetworkInfo csע��״̬
 �������  : csע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsRegStatus
 ��������  : ��ȡpsע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : psע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsRegStatus
 ��������  : ����psע��״̬
 �������  : psע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppPsRegStatus
 ��������  : ��ȡAppNetworkInfo psע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : psע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppPsRegStatus
 ��������  : ����AppNetworkInfo psע��״̬
 �������  : psע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppPsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimCsRegStatus
 ��������  : ��ȡSIM����csע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : SIM����csע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSimCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSimCsRegStatus
 ��������  : ����SIM����csע��״̬
 �������  : SIM����csע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimCsRegStatus(
    VOS_UINT8       ucSimCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus = ucSimCsRegStatus;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimPsRegStatus
 ��������  : ��ȡSIM����psע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : SIM����psע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSimPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSimPsRegStatus
 ��������  : ����SIM����psע��״̬
 �������  : SIM����psע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimPsRegStatus(
    VOS_UINT8       ucSimPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus= ucSimPsRegStatus;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsAcRestriction
 ��������  : ����cs�����ֹ��Ϣ
 �������  : pstCsAcRetriction - cs�����ֹ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstCsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction = *pstCsAcRetriction;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsAcRestriction
 ��������  : ��ȡcs�����ֹ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : cs�����ֹ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetCsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction));
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsAcRestriction
 ��������  : ��ȡps�����ֹ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ps�����ֹ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetPsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction));
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsAcRestriction
 ��������  : ����ps�����ֹ��Ϣ
 �������  : pstPsAcRetriction - ps�����ֹ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstPsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction = *pstPsAcRetriction;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimImsi
 ��������  : ��ȡimsi��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : imsi��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetSimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsimImsi
 ��������  : ��ȡCsim Imsi��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : imsi��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��11��2��
    ��    ��   : h00313353
    �޸�����   : Iteration 19

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetCsimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stMsIdentity.aucImsi);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSimImsi
 ��������  : ����imsi��Ϣ
 �������  : imsi��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi, pstImsi, sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucImsi));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLastSimImsi
 ��������  : ��ȡLast imsi��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : imsi��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��4��26��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_UINT8* TAF_SDC_GetLastSimImsi(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLastSimImsi
 ��������  : ����Last imsi��Ϣ
 �������  : imsi��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��4��26��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetLastSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi, pstImsi,
                sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimStatus
 ��������  : ��ȡ��״̬,0��sim��״̬��Ч; 1��sim��״̬��Ч 2��sim����cs����Ч
             3��sim����ps����Ч; 4��sim����ps+cs�¾���Ч; 255��sim��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetSimStatus(
    VOS_VOID
)
{
    /* �ۺ�Usim��Csim��CardService��ȡ��״̬ */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus;

    enUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    enCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == enUsimStatus)
    {
        return enUsimStatus;
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != enUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return enUsimStatus;
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return TAF_SDC_USIM_STATUS_NO_PRESENT;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUsimStatus
 ��������  : ����Usimm��״̬
 �������  : ��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetUsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus = enSimStatus;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimStatus
 ��������  : ��ȡUsimm��״̬
 �������  :
 �������  : ��
 �� �� ֵ  : TAF_SDC_USIM_STATUS_ENUM_UINT8: ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetUsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsimStatus
 ��������  : ��ȡCsimm��״̬
 �������  :
 �������  : ��
 �� �� ֵ  : TAF_SDC_USIM_STATUS_ENUM_UINT8: ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetCsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsimStatus
 ��������  : ����Csimm��״̬
 �������  : ��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetCsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus = enSimStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetIccIdInfo
 ��������  : ����IccId��Ϣ
 �������  : TAF_SDC_ICCID_INFO_STRU: IccId��Ϣ,���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetIccIdInfo(
    VOS_UINT8                   ucLen,
    VOS_UINT8                  *pucIccId
)
{
    TAF_SDC_ICCID_INFO_STRU    *pstIccIdInfo    = VOS_NULL_PTR;

    pstIccIdInfo                = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    PS_MEM_CPY(pstIccIdInfo->aucIccId, pucIccId, ucLen);

    pstIccIdInfo->ucLen         = ucLen;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetIccIdInfo
 ��������  : ��ȡIccId��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : IccId��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
TAF_SDC_ICCID_INFO_STRU *TAF_SDC_GetIccIdInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stSimInfo.stIccIdInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsimType
 ��������  : ����Csimm������
 �������  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetCsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType = enCsimType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUsimType
 ��������  : ����Csimm������
 �������  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_VOID TAF_SDC_SetUsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enUsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType = enUsimType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimType
 ��������  : ��ȡSDC Usimm��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SIM_TYPE_ENUM_UINT8: Usim������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetUsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsimType
 ��������  : ��ȡSDC Csimm��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SIM_TYPE_ENUM_UINT8: Csim������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetCsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
}

/* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-30, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimType
 ��������  : ��ȡ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetSimType(VOS_VOID)
{
    /* ��ȡ�ۺϵĿ����ͣ��¸��������ĳ�GetCardType */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstCsimStatus;

    pstUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    pstCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == pstUsimStatus)
    {
        return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return TAF_SDC_SIM_TYPE_BUTT;
        }
    }
}
/* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-30, end */

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-26, end */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPlatformRatCap
 ��������  : ��ȡƽ̨���뼼��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƽ̨���뼼��������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
TAF_SDC_PLATFORM_RAT_CAP_STRU*  TAF_SDC_GetPlatformRatCap( VOS_VOID )
{
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stPlatformRatCap);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, end */
}
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurcRptCtrl
 ��������  : ��ȡCURC���������ϱ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰCURC���������ϱ���ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��1��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CURC_RPT_CTRL_STRU*  TAF_SDC_GetCurcRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stCurcRptCtrl);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUnsolicitedRptCtrl
 ��������  : ��ȡ����������������ϱ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����������������ϱ���ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��1��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_UNSOLICITED_RPT_CTRL_STRU*  TAF_SDC_GetUnsolicitedRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stUnsolicitedRptCtrl);
}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetGuNwCapInfo
 ��������  : get GU network capability infomation
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ر����������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetGuNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLteNwCapInfo
 ��������  : get LTE network capability infomation
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ر����������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetLteNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetGuNwCapInfo
 ��������  : set GU network capability infomation
 �������  : pstNwCapInfo ����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetGuNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLteNwCapInfo
 ��������  : set LTE network capability infomation
 �������  : pstNwCapInfo ����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsAttachAllowFlg
 ��������  : ����cs�Ƿ�����ע���ʶ
 �������  : ucCsAttachAllowFlg - cs�Ƿ�����ע���ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsAttachAllowFlg(VOS_UINT8 ucCsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg = ucCsAttachAllowFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsAttachAllowFlg
 ��������  : ��ȡcs�Ƿ�����ע���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : cs�Ƿ�����ע���ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg;
}




/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrNetworkInfo
 ��������  : ��ȡstNetworkInfo�е���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_NETWORK_INFO_STRU:������Ϣ������פ����Ϣ���ź�ǿ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetCurrNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppRssiValue
 ��������  : ����stAppNetworkInfo ����ת��Ϊ�ȼ���ʾ���ź�ǿ��
 �������  : ucRssiValue - cs��ת��Ϊ�ȼ���ʾ���ź�ǿ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
     �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppRssiValue(VOS_UINT8 ucRssiValue)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue = ucRssiValue;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppRssiValue
 ��������  : ��ȡstAppNetworkInfo ����ת��Ϊ�ȼ���ʾ���ź�ǿ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfo ����ת��Ϊ�ȼ���ʾ���ź�ǿ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppRssiValue(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCellUlFreq
 ��������  : ��ȡstAppNetworkInfo��С������Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfo��С������Ƶ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��14��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCellUlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellUlFreq;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCellDlFreq
 ��������  : ��ȡstAppNetworkInfo��С������Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfo��С������Ƶ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��14��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCellDlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellDlFreq;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppLteArfcn
 ��������  : ��ȡLTEפ��Ƶ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : LTEפ��Ƶ����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetAppLteArfcn(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppLteArfcn
 ��������  : ����LTEפ��Ƶ����Ϣ
 �������  : LTEפ��Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��14��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppLteArfcn(VOS_UINT32 ulLteArfcn)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn = ulLteArfcn;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCampPlmnId
 ��������  : ����stAppNetworkInfo ��פ��plmn��Ϣ
 �������  : pstPlmnId - plmn id��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppServicePlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId = *pstPlmnId;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCampPlmnId
 ��������  : ��ȡ stAppNetworkInfo ��פ��plmn��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfo �� plmn id��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetAppServicePlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId);
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppSysMode
 ��������  : ���� stAppNetworkInfo ��ϵͳģʽ
 �������  : stAppNetworkInfo ��ϵͳģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode = enSysMode;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppSysMode
 ��������  : ��ȡstAppNetworkInfoϵͳģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfoϵͳģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetAppSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppSysSubMode
 ��������  : ����stAppNetworkInfoϵͳ��ģʽ
 �������  :stAppNetworkInfoϵͳ��ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode = enSysSubMode;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppSysSubMode
 ��������  : ��ȡstAppNetworkInfoϵͳ��ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfoϵͳ��ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetAppSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCampLac
 ��������  : ����stAppNetworkInfo lac��Ϣ
 �������  : usLac - lac��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac = usLac;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCampLac
 ��������  : ��ȡ��ǰstAppNetworkInfo lac��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : lac��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCampRac
 ��������  : ����stAppNetworkInfo rac��Ϣ
 �������  : ucRac - rac��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac = ucRac;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCampRac
 ��������  : ��ȡstAppNetworkInfo rac��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : stAppNetworkInfo rac��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCampCellId
 ��������  : ����stAppNetworkInfo cell id��Ϣ
 �������  : ulCellId - cell id��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCampCellId(VOS_UINT32 ulServiceCellId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId = ulServiceCellId;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCampCellId
 ��������  : ��ȡstAppNetworkInfo cell id��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : cell id��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetAppCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppRoamFlg
 ��������  : ����stAppNetworkInfo ������Ϣ
 �������  : ucServiceRoamFlg - ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppRoamFlg(VOS_UINT8 ucServiceRoamFlg)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg = ucServiceRoamFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCampCellId
 ��������  : ��ȡstAppNetworkInfo ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucServiceRoamFlg - ������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppRoamFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppNetworkInfo
 ��������  : ��ȡstAppNetworkInfo�е���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_APPNETWORK_INFO:פ����Ϣ���ź�ǿ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppUtranMode
 ��������  : ����stAppNetworkInfo utran mode��Ϣ
 �������  : ucServiceUtranMode - utran mode
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_SDC_SetAppUtranMode(VOS_UINT8 ucServiceUtranMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode = ucServiceUtranMode;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppUtranMode
 ��������  : ��ȡstAppNetworkInfo utran mode��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucServiceUtranMode - utran mode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
   ��    ��   : l00305157
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetAppUtranMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCsServiceStatus
 ��������  : ��ȡcs�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : cs�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCsServiceStatus
 ��������  : ����cs�����״̬
 �������  : cs�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppPsServiceStatus
 ��������  : ��ȡps�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ps�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppPsServiceStatus
 ��������  : ����ps�����״̬
 �������  : ps�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��2��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppPsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitSvlteSupportFlag
 ��������  : ��ʼ��SVLTE֧�ֱ�־
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitSvlteSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                                  ulLength;
    SVLTE_SUPPORT_FLAG_STRU                     stSvlteFlag;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* ��ʼ��Ϊ��֧��SVLTE */
    pstMsCapInfo->ucSvlteSupportFlag = VOS_FALSE;

    /* SVLTEֻ����FEATURE_MULTI_MODEM��ʱ�����п�������Ϊ���� */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SVLTE_FLAG, &ulLength);

    if (ulLength > sizeof(SVLTE_SUPPORT_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: en_NV_Item_SVLTE length Error");

        return;
    }

    /* ��NV��en_NV_Item_SVLTE_FLAG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: read en_NV_Item_SVLTE Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    pstMsCapInfo->ucSvlteSupportFlag = stSvlteFlag.ucSvlteSupportFlag;
#endif

    return;
}


/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitImsRatSupport
 ��������  : ��ʼ��IMS֧����Ϣ
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��25��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsRatSupport(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU                stImsSupport;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS��ر�ʱ��Ĭ�ϳ�ʼ��Ϊ��֧��IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsRatSupport), 0, sizeof(TAF_SDC_IMS_RAT_SUPPORT_STRU));
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* IMS����ֻ����FEATURE_IMS��ʱ�����п�������Ϊ���� */
#if (FEATURE_ON == FEATURE_IMS)

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* ��NV��EN_NV_ID_IMS_RAT_SUPPORT��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = stImsSupport.ucUtranImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = stImsSupport.ucLteImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = stImsSupport.ucUtranEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = stImsSupport.ucLteEmsSupportFlag;
#endif

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-25, end */

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitImsCapability
 ��������  : ��ʼ��IMS֧�ֶ���/��������
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsCapability(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMS_NV_IMS_CAP_STRU                         stImsCapa;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS��ر�ʱ��Ĭ�ϳ�ʼ��Ϊ��֧��IMS VOICE��IMS SMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsCapability), 0, sizeof(TAF_SDC_IMS_CAPABILITY_STRU));
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = VOS_FALSE;

    /* IMS����ֻ����FEATURE_IMS��ʱ�����п�������Ϊ���� */
#if (FEATURE_ON == FEATURE_IMS)

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_CAPABILITY, &ulLength);

    if (ulLength > sizeof(IMS_NV_IMS_CAP_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: EN_NV_ID_IMS_CAPABILITY length Error");

        return;
    }

    /* ��NV��EN_NV_ID_IMS_CAPABILITY��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCapa, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = stImsCapa.ucVoiceCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = stImsCapa.ucVideoCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = stImsCapa.ucSmsOnImsSupportFlag;
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitVoiceDomain
 ��������  : ��ʼ��������ѡ��
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��07��04��
   ��    ��   : s00217060
   �޸�����   : DTS2014070301192:IMS���ʱ��NVĬ��ֵΪcs only;IMS��ر�ʱ��NVĬ��ֵΪps preferred

*****************************************************************************/
VOS_VOID TAF_SDC_InitVoiceDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU               stVoiceDomain;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* NV�ر�ʱ��Ĭ�ϳ�ʼ��ΪCS ONLY */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_CS_ONLY;

#if (FEATURE_ON == FEATURE_IMS)

    /* NV��ʱ��Ĭ�ϳ�ʼ��Ϊps preferred */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: EN_NV_ID_UE_VOICE_DOMAIN length Error");

        return;
    }

    /* ��NV��EN_NV_ID_UE_VOICE_DOMAIN��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: read EN_NV_ID_UE_VOICE_DOMAIN Error");

        return;
    }

    /* NV������ȡֵ�Ϸ�ʱ����ֵ��ȫ�ֱ����� */
    if ( (NV_ITEM_ACTIVE == stVoiceDomain.bitOpVoicDomain)
      && (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stVoiceDomain.enVoicDomain) )
    {
        pstMsCapInfo->stImsConfigPara.enVoiceDomain = stVoiceDomain.enVoicDomain;
    }
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitSmsDomain
 ��������  : ��ʼ��������ѡ��
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitSmsDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NVIM_SMS_DOMAIN_STRU                    stSmsDomain;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* Ĭ�ϳ�ʼ��Ϊnot use sms over ip */
    pstMsCapInfo->stImsConfigPara.enSmsDomain   = TAF_SDC_SMS_DOMAIN_NOT_USE_SMS_OVER_IP;

#if (FEATURE_ON == FEATURE_IMS)
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_DOMAIN, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_SMS_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: en_NV_Item_SMS_DOMAIN length Error");

        return;
    }

    /* ��NV��en_NV_Item_SMS_DOMAIN��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_SMS_DOMAIN,
                         &stSmsDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: read en_NV_Item_SMS_DOMAIN Error");

        return;
    }

    /* NV������ȡֵ�Ϸ�ʱ����ֵ��ȫ�ֱ����� */
    if (TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP >= stSmsDomain.ucSmsDomain)
    {
        pstMsCapInfo->stImsConfigPara.enSmsDomain = stSmsDomain.ucSmsDomain;
    }
#endif

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitLteCsServiceCfg
 ��������  : ��NV�л�ȡL֧�ֵ�csҵ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��24��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitLteCsServiceCfg(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    NAS_NVIM_LTE_CS_SERVICE_CFG_STRU                        stLteCsServiceCfg;
    VOS_UINT32                                              ulLength;

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    ulLength        = 0;
    PS_MEM_SET(&stLteCsServiceCfg, 0x00, sizeof(NAS_NVIM_LTE_CS_SERVICE_CFG_STRU));

    /* Ĭ�ϳ�ʼ��ΪTAF_SDC_LTE_SUPPORT_BUTT����MMC��ʼֵ����һ�� */
    pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = TAF_SDC_LTE_SUPPORT_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Cs_Service_Config, &ulLength);

    if (ulLength > sizeof(stLteCsServiceCfg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg():WARNING: en_NV_Item_Lte_Cs_Service_Config length Error");
        return;
    }
    if ( NV_OK != NV_Read(en_NV_Item_Lte_Cs_Service_Config,
                          &stLteCsServiceCfg,
                          ulLength ))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg(): en_NV_Item_Lte_Cs_Service_Config Error");
        return;
    }

    /* ���NV����ֵ��Ч�������ȫ�ֱ��� */
    if ((NV_ITEM_ACTIVE == stLteCsServiceCfg.ucNvimActiveFlg)
     && (stLteCsServiceCfg.ucLteCsServiceCfg < TAF_SDC_LTE_SUPPORT_BUTT))
    {
        pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = stLteCsServiceCfg.ucLteCsServiceCfg;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitRedialConfig
 ��������  : ��ʼ���ز�����
 �������  : enInitType   ������ʼ������
             pstMsCapInfo ���� ��������ָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
VOS_VOID TAF_SDC_InitRedialCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU  stRedialImsToCs;

    PS_MEM_SET(&stRedialImsToCs, 0, sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* Ĭ�ϳ�ʼ��ΪFALSE */
    /* IMS to CS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs),
               0,
               sizeof(TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));

    /* CS to IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialCsToIms),
               0,
               sizeof(TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU));

#if (FEATURE_ON == FEATURE_IMS)
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG length Error");

        return;
    }

    /* ��NV��en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG,
                         &stRedialImsToCs, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: read en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG Error");

        return;
    }

    /* NV�������ز����� */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucCallRedial = stRedialImsToCs.ucCallRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSmsRedial  = stRedialImsToCs.ucSmsRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSsRedial   = stRedialImsToCs.ucSsRedial;

    /* IMS REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum  = TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum <= TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum;
    }



    /* IMSA REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum <= TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum;
    }



    /* IMS REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum)*sizeof(VOS_UINT16));



    /* IMSA REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum)*sizeof(VOS_UINT16));

    /* CS to IMS����Ļ����ز�δ���������� */
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitImsRoamingCfgInfo
 ��������  : ��ʼ���ز�����
 �������  : enInitType   ������ʼ������
             pstMsCapInfo ���� ��������ָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitImsRoamingCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_ROAMING_SUPPORT_STRU             stRoamingFlg;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* Ĭ�ϳ�ʼ��ΪFALSE */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_ROAMING_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_ROAMING_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: en_NV_Item_IMS_ROAMING_SUPPORT_FLG length Error");

        return;
    }

    /* ��NV��en_NV_Item_IMS_ROAMING_SUPPORT_FLG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_IMS_ROAMING_SUPPORT_FLG,
                         &stRoamingFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: read en_NV_Item_IMS_ROAMING_SUPPORT_FLG Error");

        return;
    }

    /* NV������ims����֧��������Ϣ */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = stRoamingFlg.ucImsRoamingFlg;
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitImsUssdCfgInfo
 ��������  : ��ʼ���ز�����
 �������  : enInitType   ������ʼ������
             pstMsCapInfo ���� ��������ָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��04��01��
    ��    ��   : y00245242
    �޸�����   : ΪDTS2014040203732�޸ģ�����NV����USSDҵ����ѡ��USSDҵ��NV�򿪣�
                 ����������ѡ�񣬷���ѡ��CS��
*****************************************************************************/
VOS_VOID TAF_SDC_InitImsUssdCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_USSD_SUPPORT_STRU                stUssdFlg;
#endif

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* Ĭ�ϳ�ʼ��ΪFALSE */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_USSD_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_USSD_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: en_NV_Item_IMS_USSD_SUPPORT_FLG length Error");

        return;
    }

    /* ��NV��en_NV_Item_IMS_USSD_SUPPORT_FLG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_IMS_USSD_SUPPORT_FLG,
                         &stUssdFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: read en_NV_Item_IMS_USSD_SUPPORT_FLG Error");

        return;
    }

    /* NV������USSD֧��������Ϣ */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = stUssdFlg.ucUssdOnImsSupportFlag;
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitImsConfigPara
 ��������  : ��ʼ��IMS������Ϣ
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : ���ӻ����ز������ο��ƹ���
 3.��    ��   : 2014��04��01��
   ��    ��   : y00245242
   �޸�����   : ΪDTS2014040203732�޸ģ�����NV����USSDҵ����ѡ��USSDҵ��NV�򿪣�
                ����������ѡ�񣬷���ѡ��CS��
*****************************************************************************/
VOS_VOID TAF_SDC_InitImsConfigPara(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    /* EN_NV_ID_IMS_RAT_SUPPORT */
    TAF_SDC_InitImsRatSupport(enInitType, pstMsCapInfo);

    /* EN_NV_ID_IMS_CAPABILITY */
    TAF_SDC_InitImsCapability(enInitType, pstMsCapInfo);

    /* EN_NV_ID_UE_VOICE_DOMAIN */
    TAF_SDC_InitVoiceDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_SMS_DOMAIN */
    TAF_SDC_InitSmsDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_Lte_Cs_Service_Config */
    TAF_SDC_InitLteCsServiceCfg(enInitType, pstMsCapInfo);

    TAF_SDC_InitRedialCfgInfo(enInitType, pstMsCapInfo);

    TAF_SDC_InitImsRoamingCfgInfo(enInitType, pstMsCapInfo);


    TAF_SDC_InitImsUssdCfgInfo(enInitType, pstMsCapInfo);
}
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-15, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitLcConfigPara
 ��������  : ��ʼ��LC������Ϣ
 �������  : enInitType:INIT����
             pstLcConfigPara:LC����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��15��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitLcConfigPara(
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigPara
)
{
    pstLcConfigPara->ucLCEnableFlg  = VOS_FALSE;
    pstLcConfigPara->enRatCombined  = TAF_NVIM_LC_RAT_COMBINED_BUTT;
    pstLcConfigPara->enLCWorkCfg    = TAF_NVIM_LC_WORK_CFG_BUTT;
    pstLcConfigPara->aucReserved[0] = 0;

    return;
}
/* Added by w00167002 for L-C��������Ŀ, 2014-2-15, end */
#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitBastetSupportFlag
 ��������  : ��NV�л�ȡBastet������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��22��
    ��    ��   : z00128442
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitBastetSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    VOS_UINT32                                  ulLength;
    BASTET_SUPPORT_FLG_STRU                     stBastetFlag;

    /* �����ϵ��ʼ��ʱ���г�ʼ���������������޸� */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* ��ʼ��Ϊ��֧��bastet*/
    pstMsCapInfo->ucBastetSupportFlag = VOS_FALSE;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Bastet_CONFIG, &ulLength);

    if (ulLength > sizeof(BASTET_SUPPORT_FLG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: en_NV_Item_Bastet_CONFIG length Error");

        return;
    }

    /* en_NV_Item_Bastet_CONFIG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Bastet_CONFIG,
                         &stBastetFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: read en_NV_Item_Bastet_CONFIG Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    pstMsCapInfo->ucBastetSupportFlag = stBastetFlag.ucActiveFlg;

    return;
}

/*lint -restore */

#endif
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitMsCapInfo
 ��������  : ��ʼ��MS������Ϣ
 �������  : enInitType:INIT����
             pstMsCapInfo:MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��06��04��
   ��    ��   : s00217060
   �޸�����   : for V9R1_SVLTE:SVLTEĬ�Ϲر�
 3.��    ��   : 2013��07��25��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseI��Ŀ
 4.��    ��   : 2013��09��22��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ����ȡEN_NV_ID_IMS_CAPABILITY��EN_NV_ID_UE_VOICE_DOMAIN
 5.��    ��   : 2014��2��14��
   ��    ��   : w00167002
   �޸�����   : L-C��������Ŀ:LC�������ó�ʼ��
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsCapInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CAP_INFO_STRU            *pstMsCapInfo
)
{
    TAF_SDC_InitSvlteSupportFlag(enInitType, pstMsCapInfo);

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
    TAF_SDC_InitImsConfigPara(enInitType, pstMsCapInfo);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

    /* Added by w00167002 for L-C��������Ŀ, 2014-2-15, begin */
    TAF_SDC_InitLcConfigPara(&(pstMsCapInfo->stLcConfigPara));
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-15, end */
#if (FEATURE_ON == FEATURE_BASTET)
    TAF_SDC_InitBastetSupportFlag(enInitType, pstMsCapInfo);
#endif
}

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitRptCtrlInfo
 ��������  : ��ʼ�������ϱ�����ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitRptCtrlInfo(VOS_VOID)
{
    /* ��ʼ��ȫ�ֱ��� */
    TAF_SDC_InitCurcRptCtrlInfo();

    /* ��ʼ���������������ϱ���ʶ */
    TAF_SDC_InitUnsolicitedRptCtrlInfo();
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitUssdCfgInfo
 ��������  : ��ʼ��USSD��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitUssdCfgInfo(VOS_VOID)
{
    TAF_SDC_ReadUssdTransModeNvim();

    TAF_SDC_ReadUssdTransTableNvim();

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadUssdTransModeNvim
 ��������  : ����NV��(en_NV_Item_CUST_USSD_MODE,����ʼUSSD�Ĵ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_ReadUssdTransModeNvim(VOS_VOID)
{
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stUssdTranMode, 0x00, sizeof(TAF_USSD_NVIM_TRANS_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_CUST_USSD_MODE, &ulLength);

    /* ��ȡUSSD�Ƿ�͸������ */
    if (NV_OK == NV_Read(en_NV_Item_CUST_USSD_MODE,
                          &stUssdTranMode,
                          ulLength))
    {
        if (VOS_TRUE != stUssdTranMode.ucStatus)
        {
            stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
        }
    }
    else
    {
        stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
    }

    TAF_SDC_SetUssdTransMode(stUssdTranMode.ucUssdTransMode);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadUssdTransTableNvim
 ��������  : ����NV��(en_NV_Item_USSD_Apha_To_Ascii,����ʼUSSD��ת��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_ReadUssdTransTableNvim(VOS_VOID)
{
    SSA_NV_ITEM_ALPHA_to_ASCII_STRU               stUSSDApha;
    VOS_UINT32                                    ulResult;
    VOS_UINT32                                    ulLength;

    ulLength = 0;
    stUSSDApha.ucStatus         = VOS_FALSE;
    stUSSDApha.ucAlphaTransMode = TAF_SDC_USSD_TRAN_MODE_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_USSD_Apha_To_Ascii, &ulLength);

    ulResult = NV_Read(en_NV_Item_USSD_Apha_To_Ascii,
                       &stUSSDApha,
                       ulLength);

    if ((ulResult == NV_OK)
     && (VOS_TRUE == stUSSDApha.ucStatus)
     && (VOS_TRUE == (stUSSDApha.ucAlphaTransMode & 0x01)))
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME);
    }
    else
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_DEF);
    }

    return;
}


/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-05, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppCfgSupportType
 ��������  : ��NV�л�ȡ�Խӵ�Ӧ�����ͣ�����¼��SDCȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��05��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ����
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppCfgSupportType(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT16                          usAppCfgType;

    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;
    ulLength                          = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

    if (ulLength > sizeof(stSysAppConfig))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);

        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType )
    {
        usAppCfgType    = SYSTEM_APP_MP;
    }
    else
    {
        usAppCfgType    = stSysAppConfig.usSysAppConfigType ;
    }

    TAF_SDC_SetAppCfgSupportType(usAppCfgType);

    return;
}
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-05, end */


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitPlmnExactlyCompareFlg
 ��������  : ��ȡen_NV_Item_PLMN_EXACTLY_COMPARE_FLG nv������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��26��
    ��    ��   : c00318887
    �޸�����   : AT&T phaseII����
*****************************************************************************/
VOS_VOID TAF_SDC_InitPlmnExactlyCompareFlg(VOS_VOID)
{
    NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU             stPlmnExactlyCompara;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stPlmnExactlyCompara, 0x00, sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU));

    ulLength = 0;
    TAF_SDC_SetPlmnExactlyCompareFlg(VOS_FALSE);

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg():WARNING: en_NV_Item_PLMN_EXACTLY_COMPARE_FLG length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read (en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &stPlmnExactlyCompara, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg(): en_NV_Item_PLMN_EXACTLY_COMPARE_FLG Error");
        return;
    }

    /* NV��Ч�Լ�� */
    if (VOS_TRUE == stPlmnExactlyCompara.ucPlmnExactlyCompareFlag)
    {
        /* ��ֵ��ȫ�ֱ��� */
        TAF_SDC_SetPlmnExactlyCompareFlg(stPlmnExactlyCompara.ucPlmnExactlyCompareFlag);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitRefreshAllFileRestartFlag
 ��������  : ��ȡen_NV_Item_REFRESH_ALL_FILE_RESTART_CFG nv������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��26��
    ��    ��   : z00161729
    �޸�����   : AT&T phaseII����
*****************************************************************************/
VOS_VOID TAF_SDC_InitRefreshAllFileRestartFlag(VOS_VOID)
{
    TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU              stRefreshAllFileRestartFlag;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stRefreshAllFileRestartFlag, 0x00, sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU));

    ulLength = 0;
    TAF_SDC_SetRefreshAllFileRestartFlag(VOS_FALSE);

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag():WARNING: en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read (en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &stRefreshAllFileRestartFlag, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag(): en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG Error");
        return;
    }

    /* NV��Ч�Լ�� */
    if (VOS_TRUE == stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag)
    {
        /* ��ֵ��ȫ�ֱ��� */
        TAF_SDC_SetRefreshAllFileRestartFlag(stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag);
    }

    return;
}


/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-10-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitUeUsageSetting
 ��������  : ��NV�л�ȡ��Ӧ��UEʹ�����ã�����¼��SDCȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��11��
    ��    ��   : y00245242
    �޸�����   : VoLTE_PhaseII��Ŀ����
*****************************************************************************/
VOS_VOID TAF_SDC_InitUeUsageSetting(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_UE_CENTER_STRU          stUeCentric;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_CENTER, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_UE_CENTER_STRU))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(EMM_SETTING_DATA_CENTRIC);

        return;
    }

    stUeCentric.enUeCenter = EMM_USAGE_SETTING_BUTT;

    if (NV_OK != NV_Read(EN_NV_ID_UE_CENTER,
                         &stUeCentric, ulLength))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(TAF_SDC_UE_USAGE_DATA_CENTRIC);

        return;
    }

    TAF_SDC_SetUeUsageSetting((TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8)(stUeCentric.enUeCenter));

    return;
}
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-10-11, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitMsSysCfgInfo
 ��������  : ��ʼ��ϵͳ������Ϣ
 �������  : pstMsSysCfgInfo - ϵͳ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : SS FDN&Call Control��Ŀ:����USSD����ģʽ��ʼ��
 3.��    ��   : 2013��08��05��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseI��Ŀ
 4.��    ��   : 2013��10��15��
   ��    ��   : y00245242
   �޸�����   : VoLTE_PhaseII��Ŀ

 5.��    ��   : 2013��11��14��
   ��    ��   : z00161729
   �޸�����   : DTS2013111507527:gcf 31.9.2.1����������ussd notify��ϢӦ�ù㲥�ϱ����յ�����release completeӦ���ϱ�cusd:2������0
 6.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
 7.��    ��   : 2015��2��26��
   ��    ��   : c00318887
   �޸�����   : AT&T phaseII ���Ӿ�ȷ�Ƚ�PLMN��ʾ�Ĵ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsSysCfgInfo(TAF_SDC_MS_SYS_CFG_INFO_STRU *pstMsSysCfgInfo)
{
    TAF_SDC_InitRptCtrlInfo();

    TAF_SDC_InitUssdCfgInfo();

    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-05, begin */
    TAF_SDC_InitAppCfgSupportType();
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-05, end */

    TAF_SDC_InitPlmnExactlyCompareFlg();
    TAF_SDC_InitRefreshAllFileRestartFlag();

    TAF_SDC_InitDsdaPlmnSearchEnhancedCfg();

    /* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-10-11, begin */
    TAF_SDC_InitUeUsageSetting();
    /* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-10-11, end */

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
#if (FEATURE_ON == FEATURE_LTE)
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_LTE;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[2]= TAF_SDC_SYS_MODE_GSM;
#else
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_GSM;
#endif
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    pstMsSysCfgInfo->stNonnormalRegStatusMergeCfg.ucMergeFlg = VOS_TRUE;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitMsCfgInfo
 ��������  : ��ʼ��MS������Ϣ
 �������  : enInitType   - INIT����
             pstMsCapInfo - MS������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitMsCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CFG_INFO_STRU            *pstMsCfgInfo
)
{
    TAF_SDC_InitMsCapInfo(enInitType, &(pstMsCfgInfo->stMsCapInfo));

    TAF_SDC_InitMsSysCfgInfo(&pstMsCfgInfo->stMsSysCfgInfo);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Init3gppSysInfo
 ��������  : ��ʼ��פ��plmn��Ϣ
 �������  : pstCampPlmnInfo - פ��plmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��8��14��
   ��    ��   : s00217060
   �޸�����   : DTS2014080700822:��ʼ��accesstype

*****************************************************************************/
VOS_VOID TAF_SDC_Init3gppSysInfo(TAF_SDC_3GPP_SYS_INFO_STRU *pst3gppSysInfo)
{
    pst3gppSysInfo->stPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pst3gppSysInfo->stPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pst3gppSysInfo->ucRac          = TAF_SDC_RAC_INVALID;
    pst3gppSysInfo->usLac          = TAF_SDC_LAC_INVALID;
    pst3gppSysInfo->ulCellId       = TAF_SDC_CELLID_INVALID;
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-16, begin */
    pst3gppSysInfo->ucRoamFlag     = VOS_FALSE;
    pst3gppSysInfo->ucCampOnFlg    = VOS_FALSE;
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-16, end */

    TAF_SDC_Set3GppRfAvailFlag(VOS_TRUE);

    pst3gppSysInfo->enLmmAccessType   = TAF_SDC_LMM_ACCESS_TYPE_BUTT;

}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Init1xSysInfo
 ��������  : ��ʼ��1Xģʽ�µ�ϵͳ��Ϣ������
 �������  : TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��4��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��23��
    ��    ��   : w00242748
    �޸�����   : DTS2015031307387:�������SID/NID�����0ʱ����ʱSID/NID�㲻��
                 �����ϱ���
  3.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_VOID TAF_SDC_Init1xSysInfo(
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
)
{
    PS_MEM_SET(pst1xSysInfo, 0x0, sizeof(TAF_SDC_1X_SYS_INFO_STRU));

    pst1xSysInfo->lSid                = MMA_INVALID_SID;
    pst1xSysInfo->lNid                = MMA_INVALID_NID;

    pst1xSysInfo->uc1xRfAvailFlg      = VOS_TRUE;

    /* ��Ҫ��һЩ���ԵĲ��������ó���Чֵ */
    pst1xSysInfo->stServiceInfo.ulMcc = (VOS_UINT32)MMA_INVALID_MCC;
    pst1xSysInfo->stServiceInfo.usMnc = (VOS_UINT16)MMA_INVALID_MNC;
    pst1xSysInfo->ucRoamingInd        = TAF_SDC_SYS_ROAMING_STATUS_OFF;

    pst1xSysInfo->ulIsInEmcCallBack   = VOS_FALSE;
    pst1xSysInfo->ucIsEmcCallExistFlg = VOS_FALSE;

    pst1xSysInfo->enRegInfoIncl         = PS_FALSE;
    pst1xSysInfo->enBaseStationInfoIncl = PS_FALSE;
    pst1xSysInfo->enServiceInfoIncl     = PS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitHrpdSysInfo
 ��������  : ��ʼ��HRPDģʽ�µ�ϵͳ��Ϣ������
 �������  : TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitHrpdSysInfo(
    TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
)
{
    PS_MEM_SET(pstHrpdSysInfo, 0x0, sizeof(TAF_SDC_HRPD_SYS_INFO_STRU));

    pstHrpdSysInfo->ucHrpdRfAvailFlg = VOS_TRUE;


    pstHrpdSysInfo->ucSessionStatus  = HRPD_SESSION_STATUS_CLOSE;

    pstHrpdSysInfo->ulMcc            = (VOS_UINT32)MMA_INVALID_MCC;

}



/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCsDomainInfo
 ��������  : ��ʼ��cs����Ϣ
 �������  : pstCsDomainInfo - cs����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��06��3��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ��ע��״̬��ʼ��Ϊ0
 3.��    ��   : 2014��1��23��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0��1
*****************************************************************************/
VOS_VOID TAF_SDC_InitCsDomainInfo(TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* С����������Ĭ����Ҫ����Ϊ������,��������ΪBUTTʱRIL����Ϊ���� */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitPsDomainInfo
 ��������  : ��ʼ��ps����Ϣ
 �������  : pstPsDomainInfo - ps����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��06��3��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ��ע��״̬��ʼ��Ϊ0
 3.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�

*****************************************************************************/
VOS_VOID TAF_SDC_InitPsDomainInfo(TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* С����������Ĭ����Ҫ����Ϊ������,��������ΪBUTTʱRIL����Ϊ���� */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitGuNwCapInfo
 ��������  : ��ʼ��GU���������������Ϣ
 �������  : pstGuNwCapInfo - GU���������������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��29��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitGuNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstGuNwCapInfo
)
{
    /* ��ʼ�������������Ϣ */
    PS_MEM_SET(pstGuNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstGuNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstGuNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstGuNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitLteNwCapInfo
 ��������  : ��ʼ��LTE���������������Ϣ
 �������  : pstLteNwCapInfo - LTE���������������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��29��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitLteNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstLteNwCapInfo
)
{
    /* ��ʼ�������������Ϣ */
    PS_MEM_SET(pstLteNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstLteNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstLteNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstLteNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitNetWorkInfo
 ��������  : ��ʼ��פ��������Ϣ
 �������  : pstNetworkInfo - פ��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��11��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseI��Ŀ
 3.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
 4.��    ��   : 2015��01��28��
   ��    ��   : y00245242
   �޸�����   : iteration 9����������IMSA�ӿڵ�MSCCģ��

*****************************************************************************/
VOS_VOID TAF_SDC_InitNetWorkInfo(TAF_SDC_NETWORK_INFO_STRU *pstNetworkInfo)
{
    pstNetworkInfo->stSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
    pstNetworkInfo->stSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
    pstNetworkInfo->stSysInfo.en1xCallState  = CDMA_1X_CALL_STATE_BUTT;

    TAF_SDC_Init3gppSysInfo(&pstNetworkInfo->stSysInfo.st3gppSysInfo);

    TAF_SDC_Init1xSysInfo(&pstNetworkInfo->stSysInfo.st1xSysInfo);

    TAF_SDC_InitHrpdSysInfo(&pstNetworkInfo->stSysInfo.stHrpdSysInfo);

    TAF_SDC_InitCsDomainInfo(&pstNetworkInfo->stCsDomainInfo);

    TAF_SDC_InitPsDomainInfo(&pstNetworkInfo->stPsDomainInfo);

    pstNetworkInfo->enServiceDomain = TAF_SDC_SERVICE_DOMAIN_BUTT;

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-13, begin */
    pstNetworkInfo->enReportSrvsta  = TAF_SDC_REPORT_SRVSTA_BUTT;

    TAF_SDC_InitGuNwCapInfo(&pstNetworkInfo->stGuNwCapInfo);
    TAF_SDC_InitLteNwCapInfo(&pstNetworkInfo->stLteNwCapInfo);

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-13, end */

    PS_MEM_SET(pstNetworkInfo->aucReserved, 0, sizeof(pstNetworkInfo->aucReserved));

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    TAF_SDC_SetImsNormalRegStatus(TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG);
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    TAF_SDC_InitNetworkRssiValue(&pstNetworkInfo->stSigQuaInfo);

    pstNetworkInfo->lSid = MMA_INVALID_SID;
    return;
}
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCsInfo
 ��������  : ��ʼ��פ��������Ϣ
 �������  : pstCsInfo - CS����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID TAF_SDC_InitCsInfo(TAF_SDC_CS_INFO_STRU *pstCsInfo)
{

    PS_MEM_SET(pstCsInfo->aucReserved, 0, sizeof(pstCsInfo->aucReserved));
    pstCsInfo->ucCsServiceConnStatusFlag    = VOS_FALSE;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitPsInfo
 ��������  : ��ʼ��פ��������Ϣ
 �������  : pstPsInfo - PS����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID TAF_SDC_InitPsInfo(TAF_SDC_PS_INFO_STRU *pstPsInfo)
{

    PS_MEM_SET(pstPsInfo->aucReserved, 0, sizeof(pstPsInfo->aucReserved));
    pstPsInfo->ucPsServiceConnStatusFlag    = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitEpsInfo
 ��������  : ��ʼ��פ��������Ϣ
 �������  : pstEpsInfo - EPS����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID TAF_SDC_InitEpsInfo(TAF_SDC_EPS_INFO_STRU *pstEpsInfo)
{

    PS_MEM_SET(pstEpsInfo->aucReserved, 0, sizeof(pstEpsInfo->aucReserved));
    pstEpsInfo->ucEpsServiceConnStatusFlag    = VOS_FALSE;

    return;
}
#endif
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitServiceInfo
 ��������  : ��ʼ��ҵ����Ϣ
 �������  : pstServiceInfo - ҵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : ����SMS��SSҵ����Ϣ�ĳ�ʼ��
 3.��    ��   : 2013��09��22��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ
 4.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
 5.��    ��   : 2014��6��30��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
 6.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID TAF_SDC_InitServiceInfo(
    TAF_SDC_SERVICE_INFO_STRU          *pstServiceInfo
)
{
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    pstServiceInfo->stSmsInfo.ucCsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucPsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucImsSmsSrvExistFlg   = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucCsSsSrvExistFlg      = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucImsSsSrvExistFlg     = VOS_FALSE;
    PS_MEM_SET(pstServiceInfo->stSmsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSmsInfo.aucReserved));
    PS_MEM_SET(pstServiceInfo->stSsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSsInfo.aucReserved));

    TAF_SDC_InitCallInfo(&(pstServiceInfo->stCallInfo));
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

    PS_MEM_SET(&pstServiceInfo->stTrigPlmnSrcSrvType, 0, sizeof(pstServiceInfo->stTrigPlmnSrcSrvType));

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
    TAF_SDC_InitCsInfo(&(pstServiceInfo->stCsInfo));
    TAF_SDC_InitPsInfo(&(pstServiceInfo->stPsInfo));
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_InitEpsInfo(&(pstServiceInfo->stEpsInfo));
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

    return;
}


/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitECallNumber
 ��������  : ��ʼ��ecall test number��recfg number��Ϣ
 �������  : pstECallNumber - ecall number��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitECallNumber(
    TAF_SDC_ECALL_NUM_STRU             *pstECallNumber
)
{
    PS_MEM_SET(pstECallNumber, 0, sizeof(TAF_SDC_ECALL_NUM_STRU));

    pstECallNumber->ucNumType = 0x81;

    return;
}

#endif
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCallInfo
 ��������  : ��ʼ�����������Ϣ
 �������  : pstCallInfo - ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��23��
   ��    ��   : y00245242
   �޸�����   : ����SRVCC���洦��
 3.��    ��   : 2014��02��28��
   ��    ��   : z00161729
   �޸�����   : DTS2014022800234:����mm�յ�paging������csҵ���������Ӵ��ڣ�
                ����ѯ^usersrvstateʱ������csҵ��syscfgex����ʧ�ܻظ�����csҵ�񣬲�һ��
 4.��    ��   : 2014-04-15
   ��    ��   : y00245242
   �޸�����   : V3R3C60_eCall��Ŀ����
 5.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������
 6.��    ��   : 2014��11��17��
   ��    ��   : w00176964
   �޸�����   : CDMA 1x��Ŀ����5�޸�
*****************************************************************************/
VOS_VOID TAF_SDC_InitCallInfo(
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo
)
{
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-17, begin */

    /* ��ʼ��CALL��ر�־ */
    pstCallInfo->ucCsCallExistFlg                       = VOS_FALSE;
    pstCallInfo->ucImsCallExistFlg                      = VOS_FALSE;

    /* SRVCC��־�����Ƶ���CALLģ��*/

    /* ��ʼ��MM��ؽ����������б� */
    PS_MEM_SET(&(pstCallInfo->stMmCallEmerNumList), 0, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));
    pstCallInfo->stMmCallEmerNumList.ulMcc              = TAF_SDC_INVALID_MCC;
    pstCallInfo->stMmCallEmerNumList.ucEmergencyNumber  = 0;

    /* ����NV��en_NV_Item_CUSTOM_ECC_NUM_LIST����ʼ��APP���ƽ����������б� */
    PS_MEM_SET(&(pstCallInfo->stCustomCallEccNumCtx), 0, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));
    TAF_SDC_ReadCustomEccNumListNvim();
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-17, end */

    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitPhoneInfo
 ��������  : ��ʼ���Ϳ��ػ���صĿ�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��03��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_VOID TAF_SDC_InitPhoneInfo(
    TAF_SDC_PHONE_INFO_STRU            *pstPhInfo
)
{
    PS_MEM_SET(pstPhInfo, 0, sizeof(TAF_SDC_PHONE_INFO_STRU));

    pstPhInfo->enPhMode = TAF_SDC_PHONE_MODE_MINI;

    pstPhInfo->enImsSwitchState = TAF_SDC_IMS_SWITCH_STATE_OFF;

    PS_MEM_SET(pstPhInfo->stHardWareInfo.aucMeId, 0xFF, sizeof(VOS_UINT8) * NAS_OM_MMA_MEID_OCTET_NUM);
    pstPhInfo->stHardWareInfo.ulEsn          = 0xFFFFFFFF;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitRegReportStatus
 ��������  : ��ʼ����ע��״̬�ϱ���صĿ�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitRegReportStatus(
    TAF_SDC_REG_REPORT_STATUS_STRU     *pstRegReportStatus
)
{
    PS_MEM_SET(pstRegReportStatus, 0, sizeof(TAF_SDC_REG_REPORT_STATUS_STRU));

    pstRegReportStatus->enCregType  = TAF_SDC_CREG_TYPE_BUTT;
    pstRegReportStatus->enCgregType = TAF_SDC_CGREG_TYPE_BUTT;
    pstRegReportStatus->enCeregType = TAF_SDC_CEREG_TYPE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadCustomEccNumListNvim
 ��������  : ��ȡNV�б����APP���ƽ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��������
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCustomEccNumListNvim(VOS_VOID)
{
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stCustomEccNumList;
    VOS_UINT8                               i;
    TAF_SDC_CALL_INFO_STRU                 *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();


    PS_MEM_SET(&stCustomEccNumList, 0x00, sizeof(stCustomEccNumList));

    /* ��ȡAPP���ƽ������б�NV */
    if (NV_OK != NV_Read(en_NV_Item_CUSTOM_ECC_NUM_LIST,
                         &stCustomEccNumList,
                         sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU)))
    {
        return;
    }

    /* ����б��б���ĸ���Ϊ��Чֵ */
    if ( stCustomEccNumList.ucEccNumCount > TAF_SDC_MAX_CUSTOM_ECC_NUM)
    {
        return;
    }


    /* ����NV���ֵ��ֵ��ȫ�ֱ����� */
    pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.ucEccNumCount
        = stCustomEccNumList.ucEccNumCount;

    /* ��NV��ȡ�����ݱ�����ȫ�ֱ����� */
    for (i = 0; i < stCustomEccNumList.ucEccNumCount; i++)
    {
        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucCategory
            = stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
            = stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ulMcc
            = stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
            = stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */



/*****************************************************************************
 �� �� ��  : TAF_SDC_InitMsIdentity
 ��������  : ��ʼ��sim��ص�ms identity��Ϣ
 �������  : pstMsIdentity - sim���ms identity��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��222��
   ��    ��   : j00177245
   �޸�����   : ����Coverity
 3.��    ��   : 2014��04��28��
   ��    ��   : s00246516
   �޸�����   : ˫IMSI�л�ʱ,MMA���ʲ������ػ��Ϳ�������
*****************************************************************************/
VOS_VOID TAF_SDC_InitMsIdentity(TAF_SDC_SIM_MS_IDENTITY_STRU *pstMsIdentity)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstMsIdentity, 0, sizeof(TAF_SDC_SIM_MS_IDENTITY_STRU));

    for ( i = 0 ; i < TAF_SDC_MAX_IMSI_LEN; i++ )
    {
        pstMsIdentity->aucImsi[i]      = TAF_SDC_IMSI_INVALID;

		pstMsIdentity->aucLastImsi[i]  = TAF_SDC_IMSI_INVALID;
	}

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitSimStatus
 ��������  : ��ʼ��sim status��Ϣ
 �������  : pstSimStatus - sim status��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitSimStatus(TAF_SDC_SIM_STATUS_STRU *pstSimStatus)
{
    PS_MEM_SET(pstSimStatus, 0, sizeof(TAF_SDC_SIM_STATUS_STRU));

    pstSimStatus->enSimStatus = TAF_SDC_USIM_STATUS_BUTT;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitSimInfo
 ��������  : ��ʼ��sim��Ϣ
 �������  : pstSimInfo - sim��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��7��30��
   ��    ��   : w00176964
   �޸�����   : ����SIM�����͵ĳ�ʼ��
 3.��    ��   : 2014��4��29��
   ��    ��   : w00176964
   �޸�����   : V3R3C60_eCall��Ŀ:���Ӻ���ģʽ��ʼ��

*****************************************************************************/
VOS_VOID TAF_SDC_InitSimInfo(TAF_SDC_USIM_INFO_STRU *pstSimInfo)
{
    TAF_SDC_InitSimStatus(&pstSimInfo->stUsimStatus);

    TAF_SDC_InitMsIdentity(&pstSimInfo->stMsIdentity);

    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-30, begin */
    pstSimInfo->enUsimType = TAF_SDC_SIM_TYPE_BUTT;
    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-30, end */

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    TAF_SDC_SetCurCallMode(TAF_SDC_CALL_MODE_BUTT);
#endif
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCsimInfo
 ��������  : ��ʼ��Csim��Ϣ
 �������  : TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo - Csim��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : h00313353
    �޸�����   : Iteration 19

*****************************************************************************/
VOS_VOID TAF_SDC_InitCsimInfo(
    TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo
)
{
    TAF_SDC_InitSimStatus(&pstCsimInfo->stCsimStatus);

    TAF_SDC_InitMsIdentity(&pstCsimInfo->stMsIdentity);

    pstCsimInfo->enCsimType = TAF_SDC_SIM_TYPE_BUTT;

    PS_MEM_SET(pstCsimInfo->aucRuimid, 0xff, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);

    return;
}

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, end */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCtx
 ��������  : ��ʼ��SDC_CTX
 �������  : enInitType:INIT����
             pstSdcCtx:SDC��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��29��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
 3.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : SS FDN&Call Control��Ŀ:����ҵ����Ϣ��ʼ��
 4.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : ErrLog&FTM��Ŀ
 5.��    ��   : 2014��08��18��
   ��    ��   : w00242748
   �޸�����   : DTS2014082204531:CREG=1��CGREG=1����֮��CREG�����ϱ���CGREG�����ϱ�
                �����ϱ���
 6.��    ��   : 2015��2��25��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_VOID TAF_SDC_InitCtx(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_CTX_STRU                    *pstSdcCtx
)
{
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    TAF_SDC_InitMsCfgInfo(enInitType, &pstSdcCtx->stMsCfgInfo);

    TAF_SDC_InitNetWorkInfo(&pstSdcCtx->stNetworkInfo);

    TAF_SDC_InitSimInfo(&pstSdcCtx->stSimInfo.stUsimInfo);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, end */

    TAF_SDC_InitCsimInfo(&(pstSdcCtx->stSimInfo.stCsimInfo));

    TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_InitErrLogInfo(&pstSdcCtx->stErrlogInfo);
#endif

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */
    TAF_SDC_InitPhoneInfo(&pstSdcCtx->stPhoneInfo);
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */

    TAF_SDC_InitRegReportStatus(&pstSdcCtx->stRegReportStatus);

    TAF_SDC_InitAppNetwork_Info(&pstSdcCtx->stAppNetworkInfo);

    TAF_SDC_InitEnhancedOperatorNameInfo(enInitType, &pstSdcCtx->stEnhancedOperatorNameInfo);

    return;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_InitCurcRptCtrlInfo
 ��������  : ����NV��en_NV_Item_PRIVATE_CMD_STATUS_RPT����ʼ�������ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��4��4��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID TAF_SDC_InitCurcRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl = VOS_NULL_PTR;
    NVIM_PRIVATE_CMD_STATUS_RPT_STRU        stNvimCmdRptCtrl;
    VOS_UINT32                              ulLength;

    ulLength = 0;

    /* ��ȡ^CURC�����Ӧ��NV�ȫ�ֱ��� */
    stNvimCmdRptCtrl.ucStatus                     = VOS_FALSE;
    stNvimCmdRptCtrl.ucStatusRptGeneralControl    = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;

    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();
    (VOS_VOID)NV_GetLength(en_NV_Item_PRIVATE_CMD_STATUS_RPT, &ulLength);

    if(NV_OK != NV_Read(en_NV_Item_PRIVATE_CMD_STATUS_RPT,
                          &stNvimCmdRptCtrl,
                          ulLength))
    {
        pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
        PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
    }
    else
    {
        if( (VOS_TRUE == stNvimCmdRptCtrl.ucStatus)
         && (VOS_FALSE == stNvimCmdRptCtrl.ucStatusRptGeneralControl) )
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_NO_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0x00, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
        else
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitUnsolicitedRptCtrlInfo
 ��������  : ��ʼ���������������ϱ�����ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��3��29��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��11��26��
   ��    ��   : h00360002
   �޸�����   : CTZR����CTZE�ϱ�

*****************************************************************************/
VOS_VOID TAF_SDC_InitUnsolicitedRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* Ĭ��Ϊ�����ϱ�ȫ�� */
    PS_MEM_SET(pstUnsolicitedRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);

    /* CREG/CGREG/CEREG�ر� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CGREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CEREG, VOS_FALSE);

    /* CTZR�ر� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZV, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_FALSE);

    /* CUSD�ر� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_FALSE);

    /* CUUS1�ر� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, VOS_FALSE);

    /* CSSN�ر� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, VOS_FALSE);

    /* �����ϱ���ʼֵͨ����NV en_NV_Item_DSFLOW_REPORT��ȡ */

    /* CERSSI�ϱ���ʼֵͨ����en_NV_Item_CELL_SIGN_REPORT_CFG��ȡ */
    TAF_SDC_ReadCellSignReportCfgNV();
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadEnhancedOperNameServiceCfgNvim
 ��������  : ��NV�л�ȡEONS�������������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��13��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_VOID TAF_SDC_ReadEnhancedOperNameServiceCfgNvim( VOS_VOID )
{
    TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU            stOperNameCfg;
    VOS_UINT32                                              ulLength;
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU                       *pstOperNamePrio = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucOperNamePrioNum;
    VOS_CHAR                                                cWildCard;

    pstOperNamePrio   = TAF_SDC_GetOperNamePrio();
    PS_MEM_SET(&stOperNameCfg, 0x00, sizeof(stOperNameCfg));
    ulLength          = 0;
    ucOperNamePrioNum = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG len failed");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG,
                         &stOperNameCfg, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG failed");
        return;
    }

    pstOperNamePrio->ucOperNamePrioNum = stOperNameCfg.ucOperNameServicePrioNum;

    if (pstOperNamePrio->ucOperNamePrioNum > TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM)
    {
        pstOperNamePrio->ucOperNamePrioNum = TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM;
    }

    for (ucIndex = 0; ucIndex < pstOperNamePrio->ucOperNamePrioNum; ucIndex++)
    {
        if (stOperNameCfg.aucOperNameSerivcePrio[ucIndex] >= TAF_SDC_OPER_NAME_TYPE_BUTT)
        {
            continue;
        }

        pstOperNamePrio->aucOperNameTypePrio[ucOperNamePrioNum] = stOperNameCfg.aucOperNameSerivcePrio[ucIndex];
        ucOperNamePrioNum++;
    }

    pstOperNamePrio->ucOperNamePrioNum = ucOperNamePrioNum;

    /* plmn�Ƚ�֧��ͨ�����ͨ���Ϊa-f,�����ȫ�ֱ��� */
    if (VOS_FALSE == stOperNameCfg.ucPlmnCompareSupportWildCardFlag)
    {
        return;
    }

    /* ���ֲ�����Ϊͨ��� */
    if (stOperNameCfg.ucWildCard <= 0x09)
    {
        return;
    }

    /* nv������0xA�����ַ�'A',0xA�����ַ�'B',0xC�����ַ�'C',0xD�����ַ�'D',
       0xE�����ַ�'E',0xF�����ַ�'F',����ֵ��Ϊ�Ƿ� */
    if ((0x0A == stOperNameCfg.ucWildCard)
     || (0x0B == stOperNameCfg.ucWildCard)
     || (0x0C == stOperNameCfg.ucWildCard)
     || (0x0D == stOperNameCfg.ucWildCard)
     || (0x0E == stOperNameCfg.ucWildCard)
     || (0x0F == stOperNameCfg.ucWildCard))
    {
        cWildCard = (VOS_CHAR)(stOperNameCfg.ucWildCard + 0x37);
        TAF_SDC_SetPlmnCompareWildCard(cWildCard);
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadCustomOperNameInfoNvim
 ��������  : ��ȡ50024 nv��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCustomOperNameInfoNvim(VOS_VOID)
{
    VOS_UINT16                          usIndex;
    NAS_MMA_NVIM_OPERATOR_NAME_STRU     stNvCustomOperName;
    VOS_UINT32                          ulNvLen;
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU *pstCustomOperNameInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucNvDataIndex = VOS_NULL_PTR;

    pstCustomOperNameInfo = TAF_SDC_GetCustomOperNameInfo();
    ulNvLen               = 0;
    PS_MEM_SET(&stNvCustomOperName, 0x00, sizeof(stNvCustomOperName));

    (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED, &ulNvLen);

    if ( ulNvLen > sizeof(NAS_MMA_NVIM_OPERATOR_NAME_STRU))
    {
        return;
    }

    if (NV_OK !=  NV_Read(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED,(VOS_VOID *)(&stNvCustomOperName),  ulNvLen))
    {
        return;
    }

    if( NV_ITEM_DEACTIVE == stNvCustomOperName.aucRcvData[0])
    {
        return;
    }

    pucNvDataIndex = stNvCustomOperName.aucRcvData + 4;

    for ( usIndex = 0; usIndex < TAF_NVIM_STORED_OPER_NAME_NUM; usIndex++ )
    {
        PS_MEM_CPY(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId,
                   pucNvDataIndex, NV_ITEM_PLMN_ID_LEN);

        TAF_SDC_ConvertPlmnId2NasStyle(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId);
        pucNvDataIndex += NV_ITEM_PLMN_ID_LEN;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameShort.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_SHORT);

        pucNvDataIndex += NV_ITEM_OPER_NAME_SHORT;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameLong.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_LONG);

        pucNvDataIndex += NV_ITEM_OPER_NAME_LONG;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadCellSignReportCfgNV
 ��������  : ��NV�ж�ȡ�ź������ϱ����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��06��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID TAF_SDC_ReadCellSignReportCfgNV( VOS_VOID )
{
    TAF_SDC_CELL_SIGN_REPORT_CFG_STRU   stCellSignReportCfg;
    VOS_UINT32                          ulCerssiRptFlg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stCellSignReportCfg, 0x0, sizeof(stCellSignReportCfg));
    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
    if (ulLength > sizeof(stCellSignReportCfg))
    {
        return;
    }
    if(NV_OK != NV_Read(en_NV_Item_CELL_SIGN_REPORT_CFG,
                          &stCellSignReportCfg,
                          ulLength))
    {
         TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadCellSignReportCfgNV:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
         return;
    }

    ulCerssiRptFlg  = VOS_TRUE;

    /* ����ֵΪ��Чֵ�����ϱ� */
    if (TAF_SDC_MAX_SIGN_THRESHOLD < stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    /* ����ֵΪ0�����ϱ� */
    if (0 == stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulCerssiRptFlg);

    return;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetXsmsCallExistFlg
 ��������  : ���õ�ǰ�Ƿ���xsms CALL��
 �������  : ucIsXsmsCallExistFlg - ��ǰ�Ƿ���xsms CALL��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��07��
   ��    ��   : c00299064
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetXsmsCallExistFlg(
    VOS_UINT8                           ucIsXsmsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg = ucIsXsmsCallExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetXsmsCallExistFlg
 ��������  : ��ǰ�Ƿ���xsms CALL��
 �������  :
 �������  : ��
 �� �� ֵ  : XSMS CALL STATUS
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��07��
   ��    ��   : c00299064
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetXsmsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsCallExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS CALL��
 �������  : ucCsCallExistFlg - ��ǰ�Ƿ���CS CALL��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsCallExistFlg(
    VOS_UINT8                           ucCsCallExistFlg
)
{
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg = ucCsCallExistFlg;
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsEccExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS ��������
 �������  : ucCsEccExistFlg - ��ǰ�Ƿ���CS ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsEccExistFlg(
    VOS_UINT8                           ucCsEccExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg = ucCsEccExistFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsEccExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���CS ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�Ƿ���CS ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsEccExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsServiceConnStatusFlag
 ��������  : ����csҵ���������ӱ�ʶ�Ƿ����
 �������  : ucCsServiceConnStatusFlag - csҵ���������ӱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��28��
   ��    ��   : z00161729
   �޸�����   : DTS2014022800234:����mm�յ�paging������csҵ���������Ӵ��ڣ�
                ����ѯ^usersrvstateʱ������csҵ��syscfgex����ʧ�ܻظ�����csҵ�񣬲�һ��

*****************************************************************************/
VOS_VOID TAF_SDC_SetCsServiceConnStatusFlag(
    VOS_UINT8                           ucCsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag = ucCsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetTrigPlmnSearchSrvType
 ��������  : ��ȡҵ�񴥷�����ҵ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ҵ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :

*****************************************************************************/
TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION *TAF_SDC_GetTrigPlmnSearchSrvType(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stTrigPlmnSrcSrvType);
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsServiceConnStatusFlag
 ��������  : ��ȡcsҵ�����������Ƿ���ڱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : csҵ���������ӱ�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��28��
   ��    ��   : z00161729
   �޸�����   : DTS2014022800234:����mm�յ�paging������csҵ���������Ӵ��ڣ�
                ����ѯ^usersrvstateʱ������csҵ��syscfgex����ʧ�ܻظ�����csҵ�񣬲�һ��

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsCallExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���CS������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���CS������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID)
{
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg;
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetImsCallExistFlg
 ��������  : ���õ�ǰ�Ƿ���IMS CALL��
 �������  : ucImsCallExistFlg - ��ǰ�Ƿ���IMS CALL��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ����

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsCallExistFlg(
    VOS_UINT8                           ucImsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg = ucImsCallExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetImsCallExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���IMS������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���IMS������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 2.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ����

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetImsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg;
}
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */

/* SRVCC�Ƶ�CALLģ���Լ�ά������*/

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCallInfo
 ��������  : ��ȡ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_CALL_INFO_STRU:������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 2.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
TAF_SDC_CALL_INFO_STRU* TAF_SDC_GetCallInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetMmCallEmerNumList
 ��������  : ����MM��ؽ������б�
 �������  : stMmCallEmerNumList - MM��ؽ������б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
VOS_VOID TAF_SDC_SetMmCallEmerNumList(
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stMmCallEmerNumList), pstMmCallEmerNumList, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetMmCallEmerNumList
 ��������  : ��ȡMM��ؽ������б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : MM��ؽ������б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
TAF_SDC_MM_EMERGENCY_LIST_STRU* TAF_SDC_GetMmCallEmerNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stMmCallEmerNumList);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCustomCallEccNumCtx
 ��������  : ������Ӫ�̶�����ؽ������б�
 �������  : stCustomCallEccNumCtx - ��Ӫ�̶�����ؽ������б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
VOS_VOID TAF_SDC_SetCustomCallEccNumCtx(
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEccNumCtx
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stCustomCallEccNumCtx), pstCustomCallEccNumCtx, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCustomCallEccNumCtx
 ��������  : ��ȡ��Ӫ�̶�����ؽ������б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��Ӫ�̶�����ؽ������б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
TAF_SDC_CUSTOM_ECC_CTX_STRU* TAF_SDC_GetCustomCallEccNumCtx(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stCustomCallEccNumCtx);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCallEmerNumsNoUsimTblAddr
 ��������  : ��ȡ�޿�ʱ�Ľ������б��׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �޿�ʱ�Ľ������б��׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCallEmerNumsNoUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsNoUsim;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCallEmerNumsNoUsimTblAddr
 ��������  : ��ȡ�п�ʱ�Ľ������б��׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �п�ʱ�Ľ������б��׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��16��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCallEmerNumsWithUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsWithUsim;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCdmaCallEmcNumsAddr
 ��������  : ��ȡ�й�����Ԥ�õĽ������к����б��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �й�����Ԥ�õĽ������к����б��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��02��04��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_CHAR** TAF_SDC_GetCdmaCallEmcNumsAddr(VOS_VOID)
{
    return g_acTafSdcCdmaCallEmcNums;
}
#endif
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUtranSkipWPlmnSearchFlag
 ��������  : ����UTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ���£��Ƿ���Ҫ����w�����ı�ʶ
 �������  : ucUtranSkipWPlmnSearchFlag - UTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ�����Ƿ���Ҫ����w�����ı�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8  ucUtranSkipWPlmnSearchFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUtranSkipWPlmnSearchFlag
 ��������  : ��ȡUTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ���£��Ƿ���Ҫ����w�����ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : UTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ�����Ƿ���Ҫ����w�����ı�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  TAF_SDC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitDsdaPlmnSearchEnhancedCfg
 ��������  : ����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ���ǰ֧�ֵĲ���Ϊ��
             ͨ����һModem��PLMN��Ϣ,����FDD�����Ƿ������Ĳ��ԡ�
             ����GUTL+G�İ汾���������Ѿ�פ���ڹ���G����ʱ������������������FDD�����������ƶ�����ֻ��Ҫ֧��TDDģʽ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitDsdaPlmnSearchEnhancedCfg(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU                   stDsdaPlmnSearchEnhancedCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDsdaPlmnSearchEnhancedCfg, 0x00, sizeof(stDsdaPlmnSearchEnhancedCfg));

    TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG, &ulLength);

    if (ulLength > sizeof(NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU))
    {
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG,
                         &stDsdaPlmnSearchEnhancedCfg, ulLength))
    {
        return;
    }

    if (VOS_TRUE == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & 0x0001))
    {
         TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_TRUE);
    }
#endif

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUssdTransMode
 ��������  : ���õ�ǰUSSD�Ĵ���ģʽ
 �������  : ucTransMode - ��ǰUSSD�Ĵ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetUssdTransMode(
    VOS_UINT8                           ucTransMode
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode = ucTransMode;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUssdTransMode
 ��������  : ��ȡ��ǰUSSD�Ĵ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰUSSD�Ĵ���ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetUssdTransMode(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Set7BitToAssicTableType
 ��������  : ���õ�ǰussd��ת��������
 �������  : ucType - ussd��ת��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_Set7BitToAssicTableType(
    VOS_UINT8                           ucType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode = ucType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get7BitToAssicTableType
 ��������  : ��ȡ��ǰussd��ת��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰussd��ת��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_Get7BitToAssicTableType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurr7BitToAsciiTableAddr
 ��������  : ��ȡ��ǰ��7BIT��ASCII��ת����ָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��7BIT��ASCII��ת����ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8*   TAF_SDC_GetCurr7BitToAsciiTableAddr(VOS_VOID)
{
    if (TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME == TAF_SDC_Get7BitToAssicTableType())
    {
        return g_aucTafSdcTme7BitToAsciiTbl;
    }
    else
    {
        return g_aucTafSdcDef7BitToAsciiTbl;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_Get3GppCurrentLai
 ��������  : ��ȡ3GPP����С����Ϣ������
 �������  : VOS_UINT8                          *aucLai     ����С����Ϣ
             VOS_UINT32                         *pulLaiLen  ����С����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
  6.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��
                 MN_GetLaiForMoCtrl->TAF_SDC_GetCurrentLai
*****************************************************************************/
VOS_VOID TAF_SDC_Get3GppCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    VOS_UINT32                          ulPos;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo = VOS_NULL_PTR;
    TAF_SDC_SYS_INFO_STRU              *pstSysInfo = VOS_NULL_PTR;

    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();
    pstSysInfo     = TAF_SDC_GetSysInfo();

    ulPos = 0;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMcc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMcc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMcc) >> 16);
    aucLai[ulPos] |= (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMnc) >> 12);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMnc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMnc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((pst3gppSysInfo->usLac & 0xff00) >> 8);
    ulPos++;
    aucLai[ulPos]  = (VOS_UINT8)(pst3gppSysInfo->usLac & 0x00ff);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 8) & 0xff);
    ulPos++;
    aucLai[ulPos] = (VOS_UINT8)(pst3gppSysInfo->ulCellId & 0xff);
    ulPos++;

    if (TAF_SDC_SYS_MODE_GSM != pstSysInfo->enSysMode)
    {
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 24) & 0xff);
        ulPos++;
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 16) & 0xff);
        ulPos++;
    }

    *pulLaiLen = ulPos;

    /*��ȡMM��ע��״̬*/
    enCsRegStatus = TAF_SDC_GetCsRegStatus();
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK != enCsRegStatus)
     && (TAF_SDC_REG_REGISTERED_ROAM != enCsRegStatus))
    {
        PS_MEM_SET(aucLai, (VOS_CHAR)0xff, ulPos);
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_SDC_Get3Gpp2CurrentLai
 ��������  : ��ȡ3GPP2����С����Ϣ������
 �������  : VOS_UINT8                          *aucLai
             VOS_UINT32                         *pulLaiLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_Get3Gpp2CurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    /***********************************************************************
     Description                      Length(Byte)
     MCC                              2
     IMSI_11_12                       1
     SID                              2
     NID                              2
     BASE_ID                          2
     BASE_LAT                         3
     BASE_LONG                        3
     ************************************************************************/
    VOS_UINT32                          ulPos;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucImsi_11_12;

    ulPos = 0;
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();

    /* MCC */
    ulMcc = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);
    aucLai[ulPos]  = TAF_SDC_GET_STK_MCC(ulMcc) & 0x00FF;
    ulPos++;

    aucLai[ulPos]  = (TAF_SDC_GET_STK_MCC(ulMcc) & 0xFF00) >> 8;
    ulPos++;

    /* IMSI_11_12*/
    ucImsi_11_12 = TAF_STD_TransformBcdImsi1112ToDeciDigit(pstSdc1xSysInfo->stServiceInfo.usImsi11_12);
    aucLai[ulPos]  = (VOS_UINT8)TAF_SDC_GET_STK_MNC(ucImsi_11_12);
    ulPos++;

    /* SID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lSid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lSid) >> 8);
    ulPos++;

    /* NID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lNid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lNid) >> 8);
    ulPos++;

    /* BASE_ID */
    aucLai[ulPos] = (VOS_UINT8)(0x00FF & pstSdc1xSysInfo->stBaseStationInfo.usBaseId);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0xFF00 & pstSdc1xSysInfo->stBaseStationInfo.usBaseId) >> 8);
    ulPos++;

    /* BASE_LAI */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 16);
    ulPos++;

    /* BASE_LONG */
    aucLai[ulPos]  = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 16);
    ulPos++;

    *pulLaiLen = ulPos;

}
#endif

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurrentLai
 ��������  : ��ȡ����С����Ϣ������
 �������  : VOS_UINT8                          *aucLai
             VOS_UINT32                         *pulLaiLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_GetCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside�����ҵ�ǰ��CLģʽ */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_SDC_Get3Gpp2CurrentLai(aucLai, pulLaiLen);
    }
    else
    {
        TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
    }
#else
    TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
#endif
}




/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSvlteFlg
 ��������  : �����Ƿ�֧��SVLTE
 �������  : ulSvlteFlg - SVLTE��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��3��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetSvlteSupportFlag(
    VOS_UINT8                          ucSvlteSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag = ucSvlteSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSvlteFlg
 ��������  : ��ȡ�Ƿ�֧��SVLTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��SVLTE
             VOS_FALSE:��֧��SVLTE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��3��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetSvlteSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsSmsSrvExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS��Ķ���ҵ��
 �������  : ucCsSmsSrvExistFlg - ��ǰ�Ƿ���CS��Ķ���ҵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsSmsSrvExistFlg(
    VOS_UINT8                           ucCsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg = ucCsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsSmsSrvExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���CS��Ķ���ҵ��ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���CS��Ķ���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsSmsSrvExistFlg
 ��������  : ���õ�ǰ�Ƿ���PS��Ķ���ҵ��
 �������  : ucPsSmsSrvExistFlg - ��ǰ�Ƿ���PS��Ķ���ҵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsSmsSrvExistFlg(
    VOS_UINT8                           ucPsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg = ucPsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsSmsSrvExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���PS��Ķ���ҵ��ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���PS��Ķ���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetImsSmsSrvExistFlg
 ��������  : ���õ�ǰ�Ƿ���IMS��Ķ���ҵ��
 �������  : ucImsSmsSrvExistFlg - ��ǰ�Ƿ���IMS��Ķ���ҵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��23��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetImsSmsSrvExistFlg(
    VOS_UINT8                           ucImsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg = ucImsSmsSrvExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetImsSmsSrvExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���IMS��Ķ���ҵ��ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���IMS��Ķ���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetImsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCsSsSrvExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS��Ĳ���ҵ��
 �������  : ucCsSsSrvExistFlg - ��ǰ�Ƿ���CS��Ĳ���ҵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetCsSsSrvExistFlg(
    VOS_UINT8                           ucCsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg = ucCsSsSrvExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCsSsSrvExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���CS��Ĳ���ҵ��ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���CS��Ĳ���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetCsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg;
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetImsSsSrvExistFlg
 ��������  : ���õ�ǰ�Ƿ���IMS��Ĳ���ҵ��
 �������  : ucImsSsSrvExistFlg - ��ǰ�Ƿ���IMS��Ĳ���ҵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��23��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsSsSrvExistFlg(
    VOS_UINT8                           ucImsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg = ucImsSsSrvExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetImsSsSrvExistFlg
 ��������  : ��ȡ��ǰ�Ƿ���IMS��Ĳ���ҵ��ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���IMS��Ĳ���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��23��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetImsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg;
}/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */


/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetGsmImsSupportFlag
 ��������  : �����Ƿ�֧��GSM�µ�IMS
 �������  : ucGsmImsSupportFlag - Gsm�µ�IMS��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetGsmImsSupportFlag(
    VOS_UINT8                          ucGsmImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag = ucGsmImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetGsmImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��GSM�µ�IMS��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��GSM�µ�IMS
             VOS_FALSE:��֧��GSM�µ�IMS
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetGsmImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUtranImsSupportFlag
 ��������  : �����Ƿ�֧��Utran�µ�IMS
 �������  : ucUtranImsSupportFlag - Utran�µ�IMS��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetUtranImsSupportFlag(
    VOS_UINT8                          ucUtranImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = ucUtranImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUtranImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��Utran�µ�IMS��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��Utran�µ�IMS
             VOS_FALSE:��֧��Utran�µ�IMS
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetUtranImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLteImsSupportFlag
 ��������  : �����Ƿ�֧��LTE�µ�IMS
 �������  : ucLteImsSupportFlag - LTE�µ�IMS��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteImsSupportFlag(
    VOS_UINT8                          ucLteImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag = ucLteImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLteImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��LTE�µ�IMS��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��LTE�µ�IMS
             VOS_FALSE:��֧��LTE�µ�IMS
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLteImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetAppCfgSupportType
 ��������  : ���öԽӵ�Ӧ������
 �������  : usAppCfgSupportType - �Խӵ�Ӧ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetAppCfgSupportType(
    VOS_UINT16                          usAppCfgSupportType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType = usAppCfgSupportType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppCfgSupportType
 ��������  : ��ȡ�Խӵ�Ӧ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : usAppCfgSupportType:�Խӵ�Ӧ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��7��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_SDC_GetAppCfgSupportType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SaveCsimCardType
 ��������  : ����Csim������
 �������  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: Csim������
 �������  : ��
 �� �� ֵ  : TRUE -- change
             FALSE-- not change
 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SaveCsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
        VOS_UINT8                           ucSimType;

        switch (enCardType)
        {
            case USIMM_CARD_UIM:
                ucSimType = TAF_SDC_SIM_TYPE_UIM;
                break;

            case USIMM_CARD_CSIM:
                ucSimType = TAF_SDC_SIM_TYPE_CSIM;
                break;

            case USIMM_CARD_NOCARD:
            case USIMM_CARD_ISIM:
            default:

                ucSimType = TAF_SDC_SIM_TYPE_BUTT;
                break;
        }

        TAF_SDC_SetCsimType(ucSimType);

        return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SaveUsimCardType
 ��������  : ����Usim������
 �������  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: Usimm������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SaveUsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
    VOS_UINT8                           ucSimType;

    switch (enCardType)
    {
        case USIMM_CARD_SIM:

            ucSimType = TAF_SDC_SIM_TYPE_SIM;
            break;

        case USIMM_CARD_USIM:

            ucSimType = TAF_SDC_SIM_TYPE_USIM;
            break;

        case USIMM_CARD_ROM_SIM:
            ucSimType = TAF_SDC_SIM_TYPE_ROM_SIM;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = TAF_SDC_SIM_TYPE_BUTT;
            break;
    }

    TAF_SDC_SetUsimType(ucSimType);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SaveUsimCardStatus
 ��������  : change MMA USIM status
 �������  : VOS_UINT32  ulUsimSta
 �������  : ��
 �� �� ֵ  : VOS_VOID
 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
)
{
    switch ( enUsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* �쳣���� */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* �����������Ϊ��״̬��Ч */
            TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SaveCsimCardStatus
 ��������  : ����Csim��״̬
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
)
{
    switch ( enCsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* �쳣���� */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* �����������Ϊ��״̬��Ч */
            TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-11, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogRingBufAddr
 ��������  : ��ȡTAF��RING BUFFER�ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF��RING BUFFER�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
OM_RING_ID TAF_SDC_GetErrLogRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogRingBufAddr
 ��������  : ����TAF��RING BUFFER�ĵ�ַ
 �������  : RING BUFFER�ĵ�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogCtrlFlag
 ��������  : ��ȡERRLOG�򿪺͹رյı�ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERRLOG�򿪺͹رյı�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogCtrlFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogCtrlFlag
 ��������  : ����ERRLOG�򿪺͹رյı�ʶ
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogAlmLevel
 ��������  : ��ȡERRLOG�򿪺͹رյı�ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERRLOG�򿪺͹رյı�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 TAF_SDC_GetErrlogAlmLevel(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogAlmLevel
 ��������  : ����ERRLOG�򿪺͹رյı�ʶ
 �������  : usAlmLevel
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��23��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogOverflowCnt
 ��������  : ��ȡRingbuf����Ĵ���
 �������  : VOS_UINT32
 �������  : ��
 �� �� ֵ  : Ringbuf����Ĵ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��09��19��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogOverflowCnt(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogOverflowCnt
 ��������  : ����Ringbuf����Ĵ���
 �������  : Ringbuf����Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��09��19��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogCsOosReportToAppFlag
 ��������  : ��ȡCS���Ƿ��ϱ����޷�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ��ϱ����޷�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogCsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogCsOosReportToAppFlag
 ��������  : ����CS���Ƿ��ϱ����޷�����
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag = ucFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogPsOosReportToAppFlag
 ��������  : ��ȡPS���Ƿ��ϱ����޷�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ��ϱ����޷�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogPsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogPsOosReportToAppFlag
 ��������  : ����PS���Ƿ��ϱ����޷�����
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag = ucFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogReportPowerOnBeginFlag
 ��������  : ��ȡ�Ƿ��ϱ�������CHR
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ��ϱ�������CHR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��30��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOnBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogReportPowerOnBeginFlag
 ��������  : �����Ƿ��ϱ�������CHR
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��30��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag = ucFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogReportPowerOffBeginFlag
 ��������  : ��ȡ�Ƿ��ϱ����ػ�CHR
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ��ϱ����ػ�CHR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��30��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOffBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogReportPowerOffBeginFlag
 ��������  : �����Ƿ��ϱ����ػ�CHR
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��30��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag = ucFlag;

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogImsCallFailFlag
 ��������  : ��ȡims call fail flag
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��5��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogImsCallFailFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ucImsCallFailFlag;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogImsCallFailFlag
 ��������  : ����ims call fail flag
 �������  : VOS_UINT8 ucImsCallFailFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��5��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogImsCallFailFlag(
    VOS_UINT8                           ucImsCallFailFlag
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ucImsCallFailFlag = ucImsCallFailFlag;

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogImsCallFailCause
 ��������  : ��ȡims call fail cause
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��5��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrLogImsCallFailCause(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ulImsCallFailCause;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogImsCallFailCause
 ��������  : ����ims call fail cause
 �������  : VOS_UINT32 ulImsCallFailCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��5��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogImsCallFailCause(
    VOS_UINT32                          ulImsCallFailCause
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ulImsCallFailCause = ulImsCallFailCause;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitErrLogImsCallFailInfo
 ��������  : ��ʼ��IMS CALL FAIL INFO
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��8��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitErrLogImsCallFailInfo(VOS_VOID)
{
    PS_MEM_SET(&(TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo),
               0,
               sizeof(NAS_ERR_LOG_IMS_CALL_FAIL_INFO_STRU));

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogActiveRptFlag
 ��������  : ��ȡNV���õ������ϱ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogActiveRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogActiveRptFlag
 ��������  : ��ȡNV���õ������ϱ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogActiveRptFlag(VOS_UINT8 ucActiveRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag = (ucActiveRptFlag & 0x01);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogRatSwitchRptFlag
 ��������  : ��ȡNV���õ������ϱ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrlogRatSwitchRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogRatSwitchRptFlag
 ��������  : ��ȡNV���õ������ϱ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_UINT8 ucRatSwitchRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag = (ucRatSwitchRptFlag & 0x01);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogRatSwitchStatisticTime
 ��������  : ��ȡNV���õ�RAT�л���ͳ��ʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticTime(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogRatSwitchStatisticTime
 ��������  : ����NV���õ�RAT�л���ͳ��ʱ��
 �������  : VOS_INT32                  ulStatisticTime
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticTime(
    VOS_UINT32                           ulStatisticTime
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime = ulStatisticTime;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrlogRatSwitchStatisticNum
 ��������  : ��ȡNV���õ�RAT�л���ͳ�ƴ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticNum(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrlogRatSwitchStatisticNum
 ��������  : ����NV���õ�RAT�л��Ĵ���
 �������  : VOS_INT32                  ulSwitchNum
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : n00269697
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticNum(
    VOS_UINT32                           ulSwitchNum
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum = ulSwitchNum;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogOldRatType
 ��������  : ��ȡ���һ��ģʽ�л�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��ȡ���һ��ģʽ�л�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetErrLogOldRatType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetErrLogOldRatType
 ��������  : �������һ��ģʽ�л�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetErrLogOldRatType(VOS_UINT8 ucRatType)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType = ucRatType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRatSwitchRingBufAddr
 ��������  : ��ȡƵ���л�RING BUFFER�ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : Ƶ���л�RING BUFFER�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �����ɺ���
*****************************************************************************/
OM_RING_ID TAF_SDC_GetRatSwitchRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetRatSwitchRingBufAddr
 ��������  : ����Ƶ���л�RING BUFFER�ĵ�ַ
 �������  : RING BUFFER�ĵ�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetRatSwitchRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer = pRingBuffer;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim
 ��������  : ��gutlƵ���л�CHR�ϱ�NV�����ñ��浽ȫ�ֱ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : n00269697
    �޸�����   : CHR�Ż���������
*****************************************************************************/
VOS_VOID TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim(VOS_VOID)
{
    VOS_UINT32                                           ulResult;
    VOS_UINT32                                           ulLength;
    TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU        stRatFrequentlySwitchChrRptCfg;

    ulLength = 0;
    PS_MEM_SET(&stRatFrequentlySwitchChrRptCfg,
               0x00, sizeof(TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg, &ulLength);

    ulResult = NV_Read(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg,
                       &stRatFrequentlySwitchChrRptCfg,
                       ulLength);

    if (NV_OK != ulResult)
    {
        TAF_SDC_SetErrlogRatSwitchStatisticTime(0);
        TAF_SDC_SetErrlogRatSwitchStatisticNum(0);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim: read en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg failed");

        return;
    }


    /* ��NV��ȡ��Ƶ���л��޶�ʱ����ڹ涨�����ֵ */
    if (stRatFrequentlySwitchChrRptCfg.ulStatisticTime > NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME)
    {
        stRatFrequentlySwitchChrRptCfg.ulStatisticTime = NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticTime(stRatFrequentlySwitchChrRptCfg.ulStatisticTime);

    /* ��NV��ȡ��Ƶ���л��޶��������ڹ涨�����ֵ */
    if (stRatFrequentlySwitchChrRptCfg.ulSwitchNum > NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN)
    {
        stRatFrequentlySwitchChrRptCfg.ulSwitchNum = NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticNum(stRatFrequentlySwitchChrRptCfg.ulSwitchNum);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadErrlogCtrlInfoNvim
 ��������  : ����NV:en_NV_Item_ErrLogCtrlInfo��ʼ��ErrlogInfo
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
  1.��    ��   : 2015��4��14��
    ��    ��   : n00269697
    �޸�����   : CHR �Ż���Ŀ
*****************************************************************************/
VOS_VOID TAF_SDC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT8                           ucActiveRptFlag;
    VOS_UINT8                           ucRatSwitchRptFlag;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        TAF_SDC_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        TAF_SDC_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);

        ucActiveRptFlag    = (stErrorLogCtrlInfo.aucReportBitMap[0] >> NAS_ERR_LOG_ACTIVE_RPT_FLAG_OFFSET) & 0x01;
        ucRatSwitchRptFlag = (stErrorLogCtrlInfo.aucReportBitMap[1] >> NAS_ERR_LOG_RAT_SWITCH_RPT_FLAG_OFFSET) & 0x01;

        TAF_SDC_SetErrlogActiveRptFlag(ucActiveRptFlag);
        TAF_SDC_SetErrlogRatSwitchRptFlag(ucRatSwitchRptFlag);
    }
    else
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);

        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadErrlogCtrlInfoNvim:read en_NV_Item_ErrLogCtrlInfo failed");
    }

    /* ���Կ����򲻿����ù��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);
    }

    return;
}

/*lint -e593 -e830*/

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitErrLogInfo
 ��������  : ����RING BUFFER
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
*****************************************************************************/
VOS_VOID TAF_SDC_InitErrLogInfo(
    TAF_SDC_ERRLOG_INFO_STRU           *pstErrLogInfo
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRingbuffer;
#endif

    TAF_SDC_ReadErrlogCtrlInfoNvim();

    TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim();

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_CreatRatSwitchRingBuf();
#endif

    TAF_SDC_SetErrLogOldRatType(TAF_PH_INFO_NONE_RAT);

    PS_MEM_SET(&pstErrLogInfo->stOosInfo,
               0x0,
               sizeof(TAF_SDC_ERRLOG_OOS_INFO_STRU));

    TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);

    TAF_SDC_InitErrLogImsCallFailInfo();

#if (FEATURE_ON == FEATURE_PTM)
    /* ����cache�Ķ�̬�ڴ� , ���ȼ�1����Ϊ����дָ��֮����д��ʱ�����һ���ֽ� */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        pstErrLogInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitErrLogInfo: alloc fail");
        return;
    }

    /* ����OM�Ľӿڣ�������Ķ�̬�ڴ洴��ΪRING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    /* ����ringbufferָ�� */
    pstErrLogInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrLogInfo->stBuffInfo.ulOverflowCnt = 0;
#endif

    return;

}
/*lint +e593 +e830*/

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : TAF_SDC_PutRatSwitchRingBuf
 ��������  : RING BUFFERд����
 �������  : pbuffer:��Ҫд�������
             lbytes :д�����ݵĳ���
 �������  : ��
 �� �� ֵ  : ʵ��д��Ĵ�С�����BUFFER�ռ䲻���򷵻�0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_PutRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    OM_RING_ID                          pTafRingBuffer;
    VOS_UINT32                          ulRatRingbufferLength;
    VOS_UINT32                          ulNvSwitchNum;
    VOS_UINT32                          ulLength;

    pTafRingBuffer = TAF_SDC_GetRatSwitchRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    ulNvSwitchNum         = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulRatRingbufferLength = ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU);

    /* ���д���RING BUFFER������д�� */
    if ((ulbytes > ulRatRingbufferLength)
     || (ulbytes != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        return 0;
    }

    /* ��ȡRING BUFFERʣ��ռ��С */
    ulFreeSize = TAF_SDC_GetRatSwitchRingBufferFreeBytes();

    /* ��������Ѿ����ˣ������ͷ����¼���� */
    if (0 == ulFreeSize)
    {
        ulLength = TAF_SDC_RatSwitchRingBufRemoveRecord(sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

        if (ulLength != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU))
        {
            return 0;
        }
    }

    /* д��RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_RatSwitchRingBufRemoveRecord
 ��������  : RING BUFFERɾ������
 �������  : ulbytes: ɾ�����ֽ���
 �������  : ��
 �� �� ֵ  : ʵ��ɾ�����ֽ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_RatSwitchRingBufRemoveRecord(
    VOS_UINT32                          ulbytes
)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferRemove(TAF_SDC_GetRatSwitchRingBufAddr(), (VOS_INT)ulbytes);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRecordFromRatSwitchRingBuf
 ��������  : RING BUFFER����������
 �������  : pbuffer: ��������ŵĿռ�
             ulbytes: ��ȡ�����ֵ
 �������  : ��
 �� �� ֵ  : ʵ�ʶ�ȡ�Ĵ�С�����RINGBUFFERΪ�գ��򷵻�0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetRecordFromRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGetReserve(TAF_SDC_GetRatSwitchRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRatSwitchRingBufferFreeBytes
 ��������  : RING BUFFER����δʹ�ÿռ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ʵ��RING BUFFER��δʹ�ÿռ��С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetRatSwitchRingBufferFreeBytes(VOS_VOID)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferFreeBytes(TAF_SDC_GetRatSwitchRingBufAddr());
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_CleanRatSwitchRingBuf
 ��������  : ���RINGBUFFER�е�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_CleanRatSwitchRingBuf(VOS_VOID)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetRatSwitchRingBufAddr());

    return;
}

/*lint -e830 -e593*/
/*****************************************************************************
 �� �� ��  : TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim
 ��������  : ��gutlƵ���л�CHR�ϱ�NV�����ñ��浽ȫ�ֱ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : n00269697
    �޸�����   : CHR�Ż���������
*****************************************************************************/
VOS_VOID TAF_SDC_CreatRatSwitchRingBuf(VOS_VOID)
{
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRatRingbuffer;
    VOS_UINT32                          ulNvSwitchNum;                          /* NV���õ�gutl�л���ͳ�ƴ��� */
    VOS_INT32                           lRatRingbufferLength;

    ulNvSwitchNum = TAF_SDC_GetErrlogRatSwitchStatisticNum();

    if (0 == ulNvSwitchNum)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);

        return;
    }

    lRatRingbufferLength = (VOS_INT32)ulNvSwitchNum * (VOS_INT32)sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU) + 1;

    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, (VOS_UINT32)lRatRingbufferLength);
    if (VOS_NULL_PTR == pbuffer)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);
        return;
    }

    PS_MEM_SET(pbuffer, 0, (VOS_UINT32)lRatRingbufferLength);

    /* ����OM�Ľӿڣ�������Ķ�̬�ڴ洴��ΪRING BUFFER */
    pRatRingbuffer = OM_RingBufferCreateEx(pbuffer, lRatRingbufferLength);
    if (VOS_NULL_PTR == pRatRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    TAF_SDC_SetRatSwitchRingBufAddr(pRatRingbuffer);

    return;
}
/*lint +e830 +e593*/

/*****************************************************************************
 �� �� ��  : TAF_SDC_PutErrLogRingBuf
 ��������  : RING BUFFERд����
 �������  : pbuffer:��Ҫд�������
             lbytes :д�����ݵĳ���
 �������  : ��
 �� �� ֵ  : ʵ��д��Ĵ�С�����BUFFER�ռ䲻���򷵻�0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
*****************************************************************************/
VOS_UINT32 TAF_SDC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = TAF_SDC_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* ���д���RING BUFFER������д�� */
    if (ulbytes > TAF_SDC_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* ��ȡRING BUFFERʣ��ռ��С */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = TAF_SDC_GetErrlogOverflowCnt();
    /* ���ʣ��ռ䲻��д��Ĵ�С�������RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        TAF_SDC_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* д��RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogRingBufContent
 ��������  : RING BUFFER����������
 �������  : pbuffer: ��������ŵĿռ�
             ulbytes: ��ȡ�����ֵ
 �������  : ��
 �� �� ֵ  : ʵ�ʶ�ȡ�Ĵ�С�����RINGBUFFERΪ�գ��򷵻�0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(TAF_SDC_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetErrLogRingBufferUseBytes
 ��������  : RING BUFFER���ж�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ʵ��RING BUFFER�����ݴ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
*****************************************************************************/
VOS_UINT32 TAF_SDC_GetErrLogRingBufferUseBytes(VOS_VOID)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(TAF_SDC_GetErrLogRingBufAddr());
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_CleanErrLogRingBuf
 ��������  : ���RINGBUFFER�е�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������
*****************************************************************************/
VOS_VOID TAF_SDC_CleanErrLogRingBuf(VOS_VOID)
{
    /* �����쳣���� */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetErrLogRingBufAddr());

    return;
}

#endif

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetVoiceCallOnImsSupportFlag
 ��������  : �����Ƿ�֧��IMS�������б�־
 �������  : ucVoiceCallOnImsSupportFlag - IMS���������Ƿ�֧��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                          ucVoiceCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag = ucVoiceCallOnImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetVoiceCallOnImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��IMS�������б�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��IMS��������
             VOS_FALSE:��֧��IMS��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetVoiceCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSmsOnImsSupportFlag
 ��������  : �����Ƿ�֧��IMS���ű�־
 �������  : SmsOnImsSupportFlag - IMS�����Ƿ�֧��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsOnImsSupportFlag(
    VOS_UINT8                          ucSmsOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag = ucSmsOnImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSmsOnImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��IMS���ű�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��IMS����
             VOS_FALSE:��֧��IMS����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSmsOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetVideoCallOnImsSupportFlag
 ��������  : �����Ƿ�֧��IMS��VIDEO CALL��־
 �������  : VideoCallOnImsSupportFlag - IMS��VIDEO CALL�Ƿ�֧��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                          ucVideoCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag = ucVideoCallOnImsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetVideoCallOnImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��IMS��VIDEO CALL��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��IMS��VIDEO CALL
             VOS_FALSE:��֧��IMS��VIDEO CALL
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetVideoCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetVoiceDomain
 ��������  : ��������������ѡ��
 �������  : enVoiceDomain - ����������ѡ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain = enVoiceDomain;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetVoiceDomain
 ��������  : ��ȡ����������ѡ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_VOICE_DOMAIN_ENUM_UINT32:����������ѡ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_VOICE_DOMAIN_ENUM_UINT32 TAF_SDC_GetVoiceDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSmsDomain
 ��������  : ���ö�����ѡ��
 �������  : enSmsDomain - ������ѡ����ѡ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsDomain(
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8      enSmsDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain = enSmsDomain;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSmsDomain
 ��������  : ��ȡ������ѡ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SMS_DOMAIN_ENUM_UINT32:������ѡ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SMS_DOMAIN_ENUM_UINT8 TAF_SDC_GetSmsDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLteEmsSupportFlag
 ��������  : ����LTE EMS֧��flag
 �������  : LTE EMS֧��flag:VOS_TRUE -- LTE EMS֧�� VOS_FALSE -- LTE EMS��֧��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��24��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteEmsSupportFlag(
    VOS_UINT8                           ucLteEmsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag = ucLteEmsSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLteEmsSupportFlag
 ��������  : ��ȡLTE EMS֧��flag
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- LTE EMS֧��
             VOS_FALSE -- LTE EMS��֧��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��24��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLteEmsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLteCsServiceCap
 ��������  : ����UE֧��LTE CSҵ������
 �������  : enLteCsServiceCap - UE֧��LTE CSҵ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��10��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetLteCsSeviceCap(
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCap
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg = enLteCsServiceCap;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLteCsSeviceCap
 ��������  : ��ȡUE֧��LTE CSҵ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
             TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS -- ֧��cs fallback��sms over sgs
             TAF_SDC_LTE_SUPPORT_SMS_OVER_SGS_ONLY     -- ֧��sms over sgs only
             TAF_SDC_LTE_SUPPORT_1XCSFB                -- ֧��1XCSFB
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��10��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8 TAF_SDC_GetLteCsSeviceCap(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUeUsageSetting
 ��������  : ��ȡUEʹ���趨
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����UE��ʹ���趨
             VOICE_CENTRIC ���� ��������
             DATA_CENTRIC  ���� ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��10��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 TAF_SDC_GetUeUsageSetting(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUeUsageSetting
 ��������  : ����UEʹ���趨
 �������  : enUeUsageSetting - UEʹ���趨
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��10��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetUeUsageSetting(
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8   enUeUsageSetting
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting = enUeUsageSetting;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCampSysMode
 ��������  : ��ȡ��ǰפ��ʱ��ϵͳģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰפ��ʱ��ϵͳģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetCampSysMode( VOS_VOID )
{
    if (VOS_TRUE == TAF_SDC_GetCampOnFlag())
    {
        return TAF_SDC_GetSysMode();
    }

    return TAF_SDC_SYS_MODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetMsPrioRatList
 ��������  : ��ȡSDC�б��浱ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : SDC�б��浱ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��20��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_RAT_PRIO_STRU* TAF_SDC_GetMsPrioRatList( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetMsPrioRatList
 ��������  : ����SDC�б���SYSCFG�Ľ������ȼ��б���Ϣ
 �������  : pstPrioRatList -SYSCFG�Ľ������ȼ��б���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��20��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID TAF_SDC_SetMsPrioRatList(
    TAF_SDC_RAT_PRIO_STRU              *pstPrioRatList
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList = *pstPrioRatList;
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

/* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCallRedailFromImsToCsSupportFlag
 ��������  : ��ȡ���д�IMS��CS��Ļ����ز�Flag
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  �ز�֧��
             VOS_FALSE -- �ز���֧��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCallRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial                    \
        .stRedialImsToCs.ucCallRedial;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCallRedailFromImsToCsSupportFlag
 ��������  : ���ú��д�IMS��CS��Ļ����ز�Flag
 �������  : ucCallRedialFromImsToCs -- ֧��IMS��CS�����ز���־
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCallRedailFromImsToCsSupportFlag(VOS_UINT8 ucCallRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucCallRedial = ucCallRedialFromImsToCs;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSmsRedailFromImsToCsSupportFlag
 ��������  : ��ȡ���Ŵ�IMS��CS��Ļ����ز�Flag
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  �ز�֧��
             VOS_FALSE -- �ز���֧��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetSmsRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs    \
        .ucSmsRedial;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetSmsRedailFromImsToCsSupportFlag
 ��������  : ���ö��Ŵ�IMS��CS��Ļ����ز�Flag
 �������  : ucCallRedialFromImsToCs -- ֧��IMS��CS�����ز���־
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetSmsRedailFromImsToCsSupportFlag(VOS_UINT8 ucSmsRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucSmsRedial = ucSmsRedialFromImsToCs;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRoamingSupportFlag
 ��������  : ��ȡ���γ�����IMSҵ��֧�ֱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ����֧��
             VOS_FALSE -- ���β�֧��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRoamingSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetRoamingSupportFlag
 ��������  : ��������֧�ֱ��
 �������  : ucRoamingSupport ���� ����֧�ֱ�־
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetRoamingSupportFlag(VOS_UINT8 ucRoamingSupport)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport = ucRoamingSupport;
}
/* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetImsNormalRegStatus
 ��������  : ���õ�ǰIMS������ע��״̬
 �������  : enRegStatus - IMS��ע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��14��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
VOS_VOID    TAF_SDC_SetImsNormalRegStatus(
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta = enRegStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetImsNormalRegStatus
 ��������  : ��ȡ��ǰIMS������ע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰIMS������ע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��09��23��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ����

*****************************************************************************/
TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   TAF_SDC_GetImsNormalRegStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurPhoneMode
 ��������  : ���õ�ǰ���ֻ�ģʽ
 �������  : enPhoneMode-��ǰ���ֻ�ģʽ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode) = enPhoneMode;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurPhoneMode
 ��������  : ��ȡ��ǰ���ֻ�ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_PHONE_MODE_ENUM_UINT8  TAF_SDC_GetCurPhoneMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode);
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurImsSwitchState
 ��������  : ���õ�ǰ��IMSЭ��ջ���ػ�״̬
 �������  : enState - ��ǰ��IMSЭ��ջ���ػ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurImsSwitchState(
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8       enState
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState) = enState;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurImsSwitchState
 ��������  : ��ȡIMSЭ��ջ���ػ�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8  TAF_SDC_GetCurImsSwitchState(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCregType
 ��������  : ��ȡ��ǰ���õ�Creg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CREG_TYPE_ENUM_UINT8  TAF_SDC_GetCregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCregType
 ��������  : ���õ�ǰ���õ�Creg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCregType(TAF_SDC_CREG_TYPE_ENUM_UINT8 enCregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType = enCregType;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCgregType
 ��������  : ��ȡ��ǰ���õ�Cgreg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CGREG_TYPE_ENUM_UINT8  TAF_SDC_GetCgregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCregType
 ��������  : ���õ�ǰ���õ�Creg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCgregType(TAF_SDC_CGREG_TYPE_ENUM_UINT8 enCgregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType = enCgregType;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCeregType
 ��������  : ��ȡ��ǰ���õ�Cgreg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CEREG_TYPE_ENUM_UINT8  TAF_SDC_GetCeregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCregType
 ��������  : ���õ�ǰ���õ�Creg����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCeregType(TAF_SDC_CEREG_TYPE_ENUM_UINT8 enCeregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType = enCeregType;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUssdOnImsSupportFlag
 ��������  : ��ȡ�Ƿ�֧��IMS USSD��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��IMS USSD
             VOS_FALSE:��֧��IMS USSD
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��04��01��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetUssdOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetUssdOnImsSupportFlag
 ��������  : ����IMS USSD��־
 �������  : ucUssdOnImsSupportFlag �� IMS USSD��־�Ƿ�֧��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��04��01��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetUssdOnImsSupportFlag(VOS_UINT8 ucUssdOnImsSupportFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = ucUssdOnImsSupportFlag;
}

#if (FEATURE_ON == FEATURE_ECALL)
/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetEcallTestNumber
 ��������  : ��ȡTestNumber
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_ECALL_NUM_STRU---��ǰUSIM���ļ��е�test����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallTestNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallTestNumber));
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetEcallRecfgNumber
 ��������  : ��ȡRecfgNumber
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_ECALL_NUM_STRU---��ǰUSIM���ļ��е�recfg����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallRecfgNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallRecfgNumber));
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCurCallMode
 ��������  : ��ȡ��ǰ�ĺ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_CALL_MODE_ENUM_UINT8---��ǰ����ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CALL_MODE_ENUM_UINT8            TAF_SDC_GetCurCallMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCurCallMode
 ��������  : ���õ�ǰ�ĺ���ģʽ
 �������  : enCallMode---��ǰ����ģʽ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetCurCallMode(
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode = enCallMode;
    return;
}

/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, end */
#endif

/* Added by s00261364 for L-C��������Ŀ, 2014-2-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLCEnableFlg
 ��������  : ����L-Cģʽʹ�ܱ�־
 �������  : ucLCEnableFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��02��10��
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetLCEnableFlg(
    VOS_UINT8                           ucLCEnableFlg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg = ucLCEnableFlg;
}
/* Added by s00261364 for L-C��������Ŀ, 2014-2-11, end */


/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLCEnableFlg
 ��������  : ��ȡL-Cģʽʹ�ܱ�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : L-Cģʽʹ�ܱ�־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��01��23��
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCEnableFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg;
}
/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, end */


/* Added by s00261364 for L-C��������Ŀ, 2014-2-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetLCWorkCfg
 ��������  : ����L-Cģʽ��ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��02��10��
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_SetLCWorkCfg(
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8     enLCWorkCfg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg = enLCWorkCfg;
}
/* Added by s00261364 for L-C��������Ŀ, 2014-2-11, end */


/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLCWorkCfg
 ��������  : ��ȡL-Cģʽ��ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : L-Cģʽ��ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��01��23��
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCWorkCfg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg;
}
/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, end */

/* Added by m00217266 for L-C��������Ŀ, 2014-2-12, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLCWorkCfg
 ��������  : ��ȡL-C�½��뼼�����ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : L-C�½��뼼�����ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��02��12��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetLCRatCombined(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enRatCombined;
}
/* Added by m00217266 for L-C��������Ŀ, 2014-2-12, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetLcConfigPara
 ��������  : ��ȡL-C�½��뼼�����ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : L-C�½��뼼�����ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��02��12��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SDC_LC_CONFIG_PARA_STRU* TAF_SDC_GetLcConfigPara(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara);
}
/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */

/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPsServiceConnStatusFlag
 ��������  : ����psҵ���������ӱ�ʶ�Ƿ����
 �������  : ucPsServiceConnStatusFlag - psҵ���������ӱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������

*****************************************************************************/
VOS_VOID TAF_SDC_SetPsServiceConnStatusFlag(
    VOS_UINT8                           ucPsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag = ucPsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPsServiceConnStatusFlag
 ��������  : ��ȡpsҵ�����������Ƿ���ڱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : psҵ���������ӱ�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_SDC_SetEpsServiceConnStatusFlag
 ��������  : ����epsҵ���������ӱ�ʶ�Ƿ����
 �������  : ucEpsServiceConnStatusFlag - psҵ���������ӱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������

*****************************************************************************/
VOS_VOID TAF_SDC_SetEpsServiceConnStatusFlag(
    VOS_UINT8                           ucEpsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag = ucEpsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetEpsServiceConnStatusFlag
 ��������  : ��ȡepsҵ�����������Ƿ���ڱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : epsҵ���������ӱ�ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : s00217060
   �޸�����   : K3V3 ��ģ����������

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetEpsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppSysMode
 ��������  : ��ʼ��APP��ϵͳģʽ��ϵͳ��ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppSysMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppSysSubMode
 ��������  : ��ʼ��APP��ϵͳ��ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppSysSubMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppNetworkPlmnInfo
 ��������  : ��ʼ�������plmn��Ϣ
 �������  : pstCampPlmnInfo - �����plmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���    Service_State_Optimize_PhaseI��Ŀ�޸�

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppNetworkPlmnInfo(TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstServPlmnInfo)
{
    pstServPlmnInfo->stServicePlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstServPlmnInfo->stServicePlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pstServPlmnInfo->ucServiceUtranMode    = NAS_UTRANCTRL_UTRAN_MODE_BUTT;
    pstServPlmnInfo->ucServiceRac          = TAF_SDC_RAC_INVALID;
    pstServPlmnInfo->usServiceLac          = TAF_SDC_LAC_INVALID;
    pstServPlmnInfo->ulServiceCellId       = TAF_SDC_CELLID_INVALID;
    pstServPlmnInfo->ucServiceRoamFlg      = TAF_PH_INFO_ROAM_UNKNOW;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetEnhancedOperatorNameInfo
 ��������  : ��ȡEONS�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU *TAF_SDC_GetEnhancedOperatorNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimOplFileInfo
 ��������  : ��ȡUSIM��OPL�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_OPL_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetUsimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimOplFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetOperNamePrio
 ��������  : ��ȡ��Ӫ��������ʾ���ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_OPER_NAME_TYPE_PRIO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_OPER_NAME_TYPE_PRIO_STRU* TAF_SDC_GetOperNamePrio(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stOperNameTypePrio);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCopsFormatType
 ��������  : ��ȡcops���õ���Ӫ��������ʾ��ʽ�����������������ָ�ʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 TAF_SDC_GetCopsFormatType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitEonsRelatedSimFileInfo
 ��������  : ��ʼ��EONS���ļ������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��29��
   ��    ��   : z00359541
   �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_SDC_InitEonsRelatedSimFileInfo(VOS_VOID)
{
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    pstEnhancedOperatorNameInfo = &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCphsFileInfo), 0, sizeof(TAF_SDC_CPHS_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitEnhancedOperatorNameInfo
 ��������  : ��ʼ��EONS��Ϣ
 �������  : pstEnhancedOperatorNameInfo - EONS��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��25��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��EONS�����޸�
 2.��    ��   : 2015��12��29��
   ��    ��   : z00359541
   �޸�����   : DTS2015120305849:���ӳ�ʼ��ԭ��ֵΪ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitEnhancedOperatorNameInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8                        enInitType,
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo
)
{
    VOS_UINT32                                              ulIndex;

    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SDC_InitEnhancedOperatorNameInfo: Start up scena, init EONS related SIM file info");
        TAF_SDC_InitEonsRelatedSimFileInfo();
    }

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stOperNameTypePrio), 0, sizeof(TAF_SDC_OPER_NAME_TYPE_PRIO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stMmInfo), 0, sizeof(TAF_SDC_MM_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    pstEnhancedOperatorNameInfo->cWildCard = 0;

    pstEnhancedOperatorNameInfo->enCopsFormatType = TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH;

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_OPER_NAME_PRIO_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex] = TAF_SDC_OPER_NAME_TYPE_BUTT;
    }

    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;

    for (ulIndex = 0; ulIndex < TAF_NVIM_STORED_OPER_NAME_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    }

    TAF_SDC_ReadEnhancedOperNameServiceCfgNvim();
    TAF_SDC_ReadCustomOperNameInfoNvim();
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCopsFormatType
 ��������  : ����cops���õ���Ӫ��������ʾ��ʽ�����������������ָ�ʽ
 �������  : enCopsFormatType - ��Ӫ��������ʾ��ʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCopsFormatType(
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType = enCopsFormatType;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimOplFileInfo
 ��������  : ��ȡSIM��OPL�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_OPL_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetSimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimOplFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimPnnFileInfo
 ��������  : ��ȡusim PNN�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_PNN_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetUsimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimPnnFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimPnnFileInfo
 ��������  : ��ȡsim PNN�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_PNN_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetSimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimPnnFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimSpnFileInfo
 ��������  : ��ȡusim SPN�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SPN_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetUsimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpnFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimSpnFileInfo
 ��������  : ��ȡsim SPN�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SPN_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetSimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpnFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetChpsFileInfo
 ��������  : ��ȡCHPS�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_CPHS_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CPHS_FILE_INFO_STRU* TAF_SDC_GetChpsFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCphsFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetUsimSpdiFileInfo
 ��������  : ��ȡusim SPDI�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SPDI_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetUsimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpdiFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetSimSpdiFileInfo
 ��������  : ��ȡsim SPDI�ļ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_SPDI_FILE_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpdiFileInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetMmInfo
 ��������  : ��ȡmm/gmm/emm information��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_MM_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_MM_INFO_STRU* TAF_SDC_GetMmInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stMmInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCustomOperNameInfo
 ��������  : ��ȡ50024 nv����Ӫ�̶�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU* TAF_SDC_GetCustomOperNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCustomOperNameInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPlmnExactlyCompareFlg
 ��������  : ��ȡTAF �б����ucPlmnExactlyCompareFlg ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetPlmnExactlyCompareFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPlmnExactlyCompareFlg
 ��������  : ����TAF �б���ľ�ȷ�Ƚϱ��ucPlmnExactlyCompareFlg
 �������  : ucPlmnExactlyComparaFlag :Mnc��ȷ�Ƚϱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��26��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetPlmnExactlyCompareFlg(VOS_UINT8  ucPlmnExactlyComparaFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag = ucPlmnExactlyComparaFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetRefreshAllFileRestartFlag
 ��������  : ��ȡrefresh all fileʱ�Ƿ���Ҫ����modem��ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetRefreshAllFileRestartFlag(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetRefreshAllFileRestartFlag
 ��������  : ����refresh all fileʱ�Ƿ���Ҫ����modem��ʶ
 �������  : ucRefreshAllFileRestartFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetRefreshAllFileRestartFlag(
    VOS_UINT8                           ucRefreshAllFileRestartFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag = ucRefreshAllFileRestartFlag;
    return;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_SetPlmnCompareWildCard
 ��������  : ����plmn�Ƚ�ʱ��ͨ���
 �������  : cWildCard - ͨ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SDC_SetPlmnCompareWildCard(
    VOS_CHAR                            cWildCard
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard = cWildCard;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetPlmnCompareWildCard
 ��������  : ��ȡplmn�Ƚ�ʱ��ͨ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_CHAR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��26��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_CHAR  TAF_SDC_GetPlmnCompareWildCard(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard;
}



/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppNetworkRssiValue
 ��������  : ��ʼ�� TAF_SDC_APP_NETWORK_INFO  stAppNetworkInfo��Rssiֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID  TAF_SDC_InitNetworkRssiValue(TAF_SDC_SIG_QUALITY_INFO_STRU *pstSigQuaInfo)
{
    /* 3PGG�����ʽ���ź�ǿ��  */
    pstSigQuaInfo->st3GppRssiInfo.sUeRfPower                            = TAF_SDC_UE_RFPOWER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucChannalQual                         = TAF_SDC_BLER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucRssiValue                           = TAF_SDC_RSSI_VALUE_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellDlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellUlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRssi              = TAF_SDC_RSSI_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsd               = 0;   /*���ֵ*/
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrp              = TAF_SDC_RSRP_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrq              = TAF_SDC_RSRQ_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.lSINR              = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI         = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[1]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1]    = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 3GPP2�����ʽ���ź�ǿ�ȣ�Ŀǰֻ��1x�� */
    TAF_SDC_Init1xSigQualityRptValue();

    TAF_SDC_InitHrpdSigQualityRptValue();
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppCsDomainInfo
 ��������  : ��ʼ��cs����Ϣ
 �������  : pstCsDomainInfo - cs����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppCsDomainInfo(
    TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo
)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* С����������Ĭ����Ҫ����Ϊ������,��������ΪBUTTʱRIL����Ϊ���� */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;
    pstCsDomainInfo->ucCsAttachAllowFlg                    = VOS_FALSE;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppPsDomainInfo
 ��������  : ��ʼ��ps����Ϣ
 �������  : pstPsDomainInfo - ps����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��11��
   ��    ��   : w00281933
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SDC_InitAppPsDomainInfo(
    TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo
)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* С����������Ĭ����Ҫ����Ϊ������,��������ΪBUTTʱRIL����Ϊ���� */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;
    pstPsDomainInfo->ucPsAttachAllowFlg                    = VOS_FALSE;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitAppNetwork_Info
 ��������  : ��ʼ�� TAF_SDC_APP_NETWORK_INFO  stAppNetworkInfo
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
  2.��    ��   : 2015��02��11��
    ��    ��   : w00281933
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  3.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�

*****************************************************************************/
VOS_VOID TAF_SDC_InitAppNetwork_Info(
    TAF_SDC_APPNETWORK_INFO *pstAppNetworkInfo
)
{
    TAF_SDC_InitAppSysMode();
    TAF_SDC_InitAppSysSubMode();

    TAF_SDC_InitAppNetworkPlmnInfo(&pstAppNetworkInfo->stAppSysInfo.stServPlmnInfo);

    TAF_SDC_Init1xSysInfo(&pstAppNetworkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);

    TAF_SDC_InitNetworkRssiValue(&pstAppNetworkInfo->stAppSigQuaInfo);

    TAF_SDC_InitAppCsDomainInfo(&pstAppNetworkInfo->stCsDomainInfo);
    TAF_SDC_InitAppPsDomainInfo(&pstAppNetworkInfo->stPsDomainInfo);

    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_BUTT);
    TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_BUTT);

}
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

/*lint -restore */
#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetBastetSupportFlag
 ��������  : ��ȡ�Ƿ�֧��Bastet
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��Bastet
             VOS_FALSE:��֧��Bastet
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��22��
   ��    ��   : z00128442
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   TAF_SDC_GetBastetSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucBastetSupportFlag;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_SDC_Set1xCallUcimEmccNumList
 ��������  : ����1X����UIM��CSIM���еĽ������б�
 �������  : pstUcimEccNumList - UIM��CSIM�е���ؽ������б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : w00176964
   �޸�����   : 1x��Ŀ����

*****************************************************************************/
VOS_VOID TAF_SDC_Set1xCallUcimEmccNumList(
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->st1xCallUcimEccNumList), pstUcimEccNumList, sizeof(TAF_SDC_UCIM_ECC_NUM_LIST_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xCallUcimEmccNumList
 ��������  : ��ȡ1X����UIM��CSIM���еĽ������б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1X����UIM��CSIM���еĽ������б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : w00176964
   �޸�����   : 1x��Ŀ����

*****************************************************************************/
TAF_SDC_UCIM_ECC_NUM_LIST_STRU* TAF_SDC_Get1xCallUcimEmccNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.st1xCallUcimEccNumList);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xBaseId
 ��������  : ��ȡBaseId��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��07��10��
    ��    ��   : d00212987
    �޸�����   : AGPS����0����
*****************************************************************************/
VOS_UINT16 TAF_SDC_Get1xBaseId(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.stBaseStationInfo.usBaseId;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xSid
 ��������  : ��ȡSid��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : g00261581
   �޸�����   : 1x��Ŀ����
 2.��    ��   : 2015��3��23��
   ��    ��   : w00242748
   �޸�����   : DTS2015031307387:�������SID/NID�����0ʱ����ʱSID/NID�㲻��
                �����ϱ���
*****************************************************************************/
VOS_INT32 TAF_SDC_Get1xSid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lSid;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xNid
 ��������  : ��ȡNid��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : g00261581
   �޸�����   : 1x��Ŀ����
 2.��    ��   : 2015��3��23��
   ��    ��   : w00242748
   �޸�����   : DTS2015031307387:�������SID/NID�����0ʱ����ʱSID/NID�㲻��
               �����ϱ���
*****************************************************************************/
VOS_INT32 TAF_SDC_Get1xNid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lNid;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xRoamingFlag
 ��������  : ��ȡ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : g00261581
   �޸�����   : 1x��Ŀ����
*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xRoamingFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucRoamingInd;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Set1xSysInfo
 ��������  : MMA����ϵͳ��Ϣ
 �������  : MMA_MSCC_SYS_SRV_INFO_STRU         *pSysInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : g00261581
   �޸�����   : 1x��Ŀ����
 2.��    ��   : 2015��3��23��
   ��    ��   : w00242748
   �޸�����   : DTS2015031307387:�������SID/NID�����0ʱ����ʱSID/NID�㲻��
                �����ϱ���
*****************************************************************************/
VOS_VOID TAF_SDC_Set1xSysInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pSysInfo
)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pSdc1xSysInfo;

    pSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    pSdc1xSysInfo->usBandClass      = pSysInfo->usBandClass;
    pSdc1xSysInfo->ucRoamingInd     = pSysInfo->ucRoamingInd;
    pSdc1xSysInfo->ucPacketZoneId   = pSysInfo->ucPzid;
    pSdc1xSysInfo->lSid             = (0x00000000 | pSysInfo->usSid);
    pSdc1xSysInfo->lNid             = (0x00000000 | pSysInfo->usNid);
    pSdc1xSysInfo->ucPrevInUse      = pSysInfo->ucPrevInUse;
    pSdc1xSysInfo->usFreq           = pSysInfo->usFreq;

    pSdc1xSysInfo->enRegInfoIncl         = pSysInfo->enRegInfoIncl;
    pSdc1xSysInfo->enBaseStationInfoIncl = pSysInfo->enBaseStationInfoIncl;
    pSdc1xSysInfo->enServiceInfoIncl     = pSysInfo->enServiceInfoIncl;

    if (PS_TRUE == pSysInfo->enRegInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stRegInfo), &(pSysInfo->stRegInfo), sizeof(NAS_MSCC_PIF_OHM_REG_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enBaseStationInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stBaseStationInfo), &(pSysInfo->stBaseStationInfo), sizeof(NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enServiceInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stServiceInfo), &(pSysInfo->stServiceInfo), sizeof(NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU));
    }
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GethrpdSysInfo
 ��������  : ��ȡϵͳ��Ϣ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ϵͳ��Ϣ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : y00322978
   �޸�����   : iterating 17����
*****************************************************************************/
TAF_SDC_HRPD_SYS_INFO_STRU* TAF_SDC_GethrpdSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xSysInfo
 ��������  : ��ȡϵͳ��Ϣ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ϵͳ��Ϣ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��25��
   ��    ��   : g00261581
   �޸�����   : 1x��Ŀ����
*****************************************************************************/
TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_Get1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xSigQualityInfo
 ��������  : ��ȡ1x�ź�������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : 1x�ź�������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��01��14��
   ��    ��   : m00312079
   �޸�����   : 1x��Ŀ����
2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_Get1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetHrpdSigQualityInfo
 ��������  : ��ȡHrpd�ź�������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : HRPD�ź�������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��20��
   ��    ��   : C00299064
   �޸�����   : ����
*****************************************************************************/
TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU* TAF_SDC_GetHrpdSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.stHrpdSigQualityRptInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitHrpdSigQualityRptValue;
 ��������  : ��ʼ��SDC��HDR SigQualityRpt��ֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00299064
    �޸�����   :
*****************************************************************************/
VOS_VOID TAF_SDC_InitHrpdSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU         *pstSdcHrpdSigQualityInfo;

    pstSdcHrpdSigQualityInfo                     = TAF_SDC_GetHrpdSigQualityInfo();

    pstSdcHrpdSigQualityInfo->enMode             = TAF_SDC_HDR_CSQ_MODE_ENABLE;
    pstSdcHrpdSigQualityInfo->ucTimeInterval     = 0;
    pstSdcHrpdSigQualityInfo->ucRssiThreshold    = 3;
    pstSdcHrpdSigQualityInfo->ucSnrThreshold     = 3;
    pstSdcHrpdSigQualityInfo->ucEcioThreshold    = 10;
    pstSdcHrpdSigQualityInfo->sHdrRssi           = TAF_SDC_HRPD_INVALID_RSSI_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrSnr            = TAF_SDC_HRPD_INVALID_SNR_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrEcio           = TAF_SDC_HRPD_INVALID_ECIO_VALUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_InitSigQualityRptValue;
 ��������  : ��ʼ��SDC��SigQualityRpt��ֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��27��
    ��    ��   : m00312079
    �޸�����   : �½�

  2.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����

*****************************************************************************/
VOS_VOID TAF_SDC_Init1xSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU            *pstSdc1xSigQualityInfo;

    pstSdc1xSigQualityInfo                          = TAF_SDC_Get1xSigQualityInfo();

    pstSdc1xSigQualityInfo->enMode                  = TAF_SDC_CDMACSQ_MODE_ENABLE;
    pstSdc1xSigQualityInfo->ucTimeInterval          = 3;
    pstSdc1xSigQualityInfo->ucRssiRptThreshold      = 3;
    pstSdc1xSigQualityInfo->ucEcIoRptThreshold      = 3;
    pstSdc1xSigQualityInfo->sCdmaRssi               = TAF_SDC_CDMA_INVALID_RSSI_VALUE;
    pstSdc1xSigQualityInfo->sCdmaEcIo               = TAF_SDC_CDMA_INVALID_ECIO_VALUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xPrevInUse
 ��������  : ��ȡ��ǰʹ�õ�Э��汾��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��16��
   ��    ��   : z00316370
   �޸�����   : ����
*****************************************************************************/
VOS_UINT8 TAF_SDC_Get1xPrevInUse(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucPrevInUse;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_Get1xChan
 ��������  : ��ȡ��ǰʹ�õ�channel
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��16��
   ��    ��   : z00316370
   �޸�����   : ����
*****************************************************************************/
VOS_UINT16 TAF_SDC_Get1xChan(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.usFreq;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetXCaLLState
 ��������  : ���õ�ǰXCALL״̬
 �������  : enXCallState xcall ״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetXCaLLState(
    NAS_OM_1X_CALL_STATE_ENUM_UINT8        enXCallState
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState = enXCallState;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetXCallState
 ��������  : ��ȡxcall״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_OM_1X_CALL_STATE_ENUM_UINT8 TAF_SDC_GetXCallState(
    VOS_VOID
)
{
    return   TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState;

}
/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCdmaStatusReportPeriod
 ��������  : ��ȡcdma��Ϣ�����ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_SDC_GetCdmaStatusReportPeriod(
    VOS_VOID
)
{
    return TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCdmaStatusReportPeriod
 ��������  : ����cdma״̬��Ϣ�����ϱ�����
 �������  : VOS_UINT32               ulRptPeriod
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCdmaStatusReportPeriod(
    VOS_UINT32                          ulRptPeriod
)
{
    TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod = ulRptPeriod;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_SetCdmaCurUeState
 ��������  : ����cdma��ǰUE״̬
 �������  : TAF_SDC_1X_UE_STATUS_ENUM_UINT8    enCasState
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��11��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SDC_SetCdmaCurUeState(
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8    enCasState
)
{
    TAF_SDC_GetSdcCtx()->enCasState = enCasState;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetCdmaCurUeState
 ��������  : ��ȡcdma��ǰUE״̬
 �������  :
 �������  : ��
 �� �� ֵ  : enCasState
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��11��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SDC_GetCdmaCurUeState(
    VOS_VOID
)
{
    return  TAF_SDC_GetSdcCtx()->enCasState;
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetApp1xSigQualityInfo
 ��������  : ��ȡstAppNetworkInfo�е�1x�ź�������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : 1x�ź�������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 ����
*****************************************************************************/
TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_GetApp1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetApp1xSysInfo
 ��������  : ��ȡstAppNetworkInfo�е�ϵͳ��Ϣ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ϵͳ��Ϣ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 ����
*****************************************************************************/
TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_GetApp1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetApp1xRoamingFlag
 ��������  : ��ȡstAppNetworkInfo������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��30��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 18 ����
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetApp1xRoamingFlag(VOS_VOID)
{
   return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.ucRoamingInd;
}


#endif



/*****************************************************************************
 �� �� ��  : TAF_SDC_GetImsToCsRedialCauseConfig
 ��������  : ��ȡIMS��CS���ز������õ�ԭ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��13��
   ��    ��   : l00289540
   �޸�����   : ����
*****************************************************************************/

TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU * TAF_SDC_GetImsToCsRedialCauseConfig(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg);

}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetNonnormalRegStatusMergeCfg
 ��������  : ��ȡ�������������Ƿ��ϱ�ע�����״̬�仯������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : �������������Ƿ��ϱ�ע�����״̬�仯������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��27��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU* TAF_SDC_GetNonnormalRegStatusMergeCfg(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetNonnormalRegStatusMergeFlg
 ��������  : ��ȡ�������������Ƿ��ϱ�ע�����״̬�仯������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : �������������Ƿ��ϱ�ע�����״̬�仯������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��27��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SDC_GetNonnormalRegStatusMergeFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg.ucMergeFlg);
}


/*****************************************************************************
 �� �� ��  : TAF_SDC_GetNetWorkInfoAddr
 ��������  : ��ȡNetWorkInfo�ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_SDC_NETWORK_INFO_STRU*     NetWorkInfo��ȫ�ֱ����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��01��15��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_GetAppNetWorkInfoAddr
 ��������  : ��ȡAppNetWorkInfo�ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_SDC_APPNETWORK_INFO*     AppNetWorkInfo��ȫ�ֱ����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��01��15��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

