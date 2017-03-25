/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : VcProcNvim.c
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��3��3��
  ����޸�   :
  ��������   : VC����NV��Ķ�д�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :2012��3��3��
    ��    ��   : s62952
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "VcCtx.h"
#include "VcProcNvim.h"
#include "NVIM_Interface.h"
#include "VcComm.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

#include "VcMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_VC_PROC_NIVM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : APP_VC_ReadPcVoiceSupportNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_PCVOICE_Support_Flg������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  APP_VC_ReadPcVoiceSupportNvim( VOS_VOID )
{
    APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU                  stPcVoiceSupportFlag;
    APP_VC_MS_CFG_INFO_STRU                                *pstMsCfgInfo;
    VOS_UINT32                                              ulLength;

    pstMsCfgInfo                        = APP_VC_GetCustomCfgInfo();

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_PCVOICE_Support_Flg, &ulLength);
    if (ulLength > sizeof(stPcVoiceSupportFlag))
    {
        return;
    }
    stPcVoiceSupportFlag.usPcVoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;

    if (NV_OK != NV_Read(en_NV_Item_PCVOICE_Support_Flg, &stPcVoiceSupportFlag, ulLength))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
        VC_WARN_LOG("APP_VC_ReadAlsSupportNvim: NV Read en_NV_Item_PCVOICE_Support_Flg Fail" );
        return;
    }

    if ( (APP_VC_NV_ITEM_ACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag)
       &&(APP_VC_NV_ITEM_DEACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
    }
    else
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = stPcVoiceSupportFlag.usPcVoiceSupportFlag;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : APP_VC_ReadNvimInfo
 ��������  : ��NV�ж�ȡ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��18��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VC_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_PCVOICE_Support_Flg */
    APP_VC_ReadPcVoiceSupportNvim();
    return;
}

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



