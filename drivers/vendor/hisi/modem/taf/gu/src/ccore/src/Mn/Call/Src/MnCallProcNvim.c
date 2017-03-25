/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallProcNvim.c
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��3��3��
  ����޸�   :
  ��������   : CALL����NV��Ķ�д�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :2012��3��3��
    ��    ��   : s62952
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"
#include "NVIM_Interface.h"
#include "MnCall.h"

#include "MnCallTimer.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_PROC_NIVM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadCustomizeServiceNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_CustomizeService������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  MN_CALL_ReadCustomizeServiceNvim( VOS_VOID )
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU               stCustomServ;
    VOS_UINT32                                    ulResult;


    stCustomServ.ulStatus           = VOS_FALSE;
    stCustomServ.ulCustomizeService = VOS_FALSE;

    /* ��ȡ��Ӧ�ļ���NV������浽ȫ�ֱ����� */
    ulResult = NV_Read(en_NV_Item_CustomizeService,
                       &stCustomServ,
                       sizeof(stCustomServ));

    /* PC����,�طŹ���,CCĬ�ϴ� */
#if (defined(__PS_WIN32_RECUR__))
        stCustomServ.ulStatus = VOS_TRUE;
        stCustomServ.ulCustomizeService = VOS_TRUE;
#endif
    /* Modified by z00234330 for PCLINT����, 2014-07-03, begin */
    if((ulResult == NV_OK)
    &&(VOS_TRUE == stCustomServ.ulStatus)
    &&(VOS_TRUE == (stCustomServ.ulCustomizeService&0x01)))
    {
       TAF_CALL_SetCallStatusControl(VOS_TRUE);
    }
    else
    {
        TAF_CALL_SetCallStatusControl(VOS_FALSE);
    }
    /* Modified by z00234330 for PCLINT����, 2014-07-03, end */
    return;
}

/*****************************************************************************
 �� �� ��  : MN_CAL_ReadMultiSimCallConfNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_MultiSimCallConf������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CAL_ReadMultiSimCallConfNvim( VOS_VOID )
{
    MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU         stMultiSimCallCon;
    VOS_UINT32                                    ulResult;


    stMultiSimCallCon.usMultiSimCallConf = VOS_FALSE;

    ulResult = NV_Read(en_NV_Item_MultiSimCallConf,
                      &stMultiSimCallCon,
                      sizeof(stMultiSimCallCon));

    /* Modified by z00234330 for PCLINT����, 2014-07-03, begin */
    if((ulResult == NV_OK)
    &&(VOS_TRUE == stMultiSimCallCon.usMultiSimCallConf))
    {
        TAF_CALL_SetMultiSimCallStatusControl(VOS_TRUE);
    }
    else
    {
        TAF_CALL_SetMultiSimCallStatusControl(VOS_FALSE);
    }
    /* Modified by z00234330 for PCLINT����, 2014-07-03, end */

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CAL_ReadVideoCallNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_VIDEO_CALL������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  MN_CAL_ReadVideoCallNvim( VOS_VOID )
{
    MN_CALL_NV_ITEM_VIDEO_CALL_STRU               stVideoCall;
    VOS_UINT32                                    ulResult;
    VOS_UINT32                                    ulLength;

    ulLength                 = 0;

    stVideoCall.ucStatus     = VOS_FALSE;
    stVideoCall.ucVpCfgState = MN_CALL_VP_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_VIDEO_CALL, &ulLength);

    ulResult = NV_Read(en_NV_Item_VIDEO_CALL,
                       &stVideoCall,
                       ulLength);

    /* PC����,�طŹ���,CCĬ�ϴ� */
#if (defined(__PS_WIN32_RECUR__))
        stVideoCall.ucStatus = VOS_TRUE;
        stVideoCall.ucVpCfgState = MN_CALL_VP_MO_MT_BOTH;
#endif
     if((ulResult == NV_OK)
     &&(VOS_TRUE == stVideoCall.ucStatus))
     {
        TAF_CALL_SetVpCfgState(stVideoCall.ucVpCfgState);
     }
     else
     {
        TAF_CALL_SetVpCfgState(MN_CALL_VP_MO_MT_BOTH);
     }

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CAL_ReadCcbsNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_NVIM_CCBS_SUPPORT_FLG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  MN_CAL_ReadCcbsNvim( VOS_VOID )
{
    NAS_NVIM_CCBS_SUPPORT_FLG_STRU                          stCcbsSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCcbsSupportFlg = VOS_NULL_PTR;


    stCcbsSupportFlg.ucCcbsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCcbsSupportFlg = MN_CALL_GetCustomCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_CCBS_SUPPORT_FLG,
                         &stCcbsSupportFlg, sizeof(NAS_NVIM_CCBS_SUPPORT_FLG_STRU)))
    {
        MN_WARN_LOG("MN_CAL_ReadCcbsNvim():WARNING: en_NV_Item_NVIM_CCBS_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg))
    {
        pstCcbsSupportFlg->ucCcbsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadCcbsNvim():WARNING: NV parameter Error");
        return;
    }

    pstCcbsSupportFlg->ucCcbsSupportFlg = stCcbsSupportFlg.ucCcbsSupportFlg;

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/*****************************************************************************
 �� �� ��  : MN_CAL_ReadCallDeflectionNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CAL_ReadCallDeflectionNvim( VOS_VOID )
{
    MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU           stCallDeflectionSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCallDeflectionSupportFlg = VOS_NULL_PTR;


    stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCallDeflectionSupportFlg = MN_CALL_GetCustomCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG,
                         &stCallDeflectionSupportFlg, sizeof(MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU)))
    {
        MN_WARN_LOG("MN_CAL_ReadCallDeflectionNvim():WARNING: en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg))
    {
        pstCallDeflectionSupportFlg->ucCallDeflectionSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadCallDeflectionNvim():WARNING: NV parameter Error");
        return;
    }

    pstCallDeflectionSupportFlg->ucCallDeflectionSupportFlg = stCallDeflectionSupportFlg.ucCallDeflectionSupportFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CAL_ReadAlsSupportNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_NVIM_ALS_SUPPORT_FLG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  MN_CAL_ReadAlsSupportNvim( VOS_VOID )
{
    MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU                       stAlsSupportFlg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength                        = 0;

    stAlsSupportFlg.ucAlsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_ALS_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_ALS_SUPPORT_FLG,
                         &stAlsSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_CAL_ReadAlsSupportNvim():WARNING: en_NV_Item_NVIM_ALS_SUPPORT_FLG Error");

        return;
    }


    if ((MN_CALL_NV_ITEM_ACTIVE != stAlsSupportFlg.ucAlsSupportFlg)
     && (MN_CALL_NV_ITEM_DEACTIVE != stAlsSupportFlg.ucAlsSupportFlg))
    {
        pstCustomCfg->ucAlsSupportFlg = MN_CALL_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_CAL_ReadAlsSupportNvim():WARNING: NV parameter Error");
        return;
    }

    pstCustomCfg->ucAlsSupportFlg = stAlsSupportFlg.ucAlsSupportFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CAL_ReadReportEccNumSupportNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_NVIM_ECC_NUM_REPORT_FLG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ�����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  MN_CALL_ReadReportEccNumSupportNvim( VOS_VOID )
{
    MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU            stCustomSetEcc;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;


    ulLength = 0;
    PS_MEM_SET(&stCustomSetEcc, 0x00, sizeof(stCustomSetEcc));

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadReportEccNumSupportNvim():WARNING: en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG length Error");
        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;

        return;
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG, &ulLength);
    if (ulLength > sizeof(MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU))
    {
        return;
    }

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG,
                         &stCustomSetEcc, ulLength))
    {
        MN_WARN_LOG("MN_CAL_ReadReportEccNumSupportNvim():WARNING: en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG Error");

        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;

        return;
    }

    /* NV���������������ϱ������־ΪVOS_TRUE */
    if (MN_CALL_NV_ITEM_ACTIVE == stCustomSetEcc.ucReportEccNumFlg)
    {
        pstCustomCfg->ucReportEccNumFlg = VOS_TRUE;
    }
    else
    {
        pstCustomCfg->ucReportEccNumFlg = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadCallRedialCfgNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_CS_Call_Redial_CFG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : ֧�ֺ����ؽ�����nv��
  2.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2012��1��4��
    ��    ��   : w00176964
    �޸�����   : DTS2013010403491:GCF���Կ�,CC�����ؽ��Ŀ�����Ҫ�ر�
  4.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿڵ���
  5.��    ��   : 2014��04��09��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
  6.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : NAS���������Ż�
*****************************************************************************/
VOS_VOID  MN_CALL_ReadCallRedialCfgNvim( VOS_VOID )
{
    MN_CALL_REDIAL_CFG_STRU             stCallRedialCfg;
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;


    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    /*��disconnect nv��ʼ��*/
    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialForDiscSupportFlg = VOS_FALSE;
    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialDiscCauseNum = 0;    

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    /* GCF����,�����ط�������Ҫ�ر� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;


        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                                    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                                    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);

        return;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CS_Call_Redial_CFG, &ulLength);

    PS_MEM_SET(&stCallRedialCfg, 0x0, sizeof(MN_CALL_REDIAL_CFG_STRU));

    if (ulLength > sizeof(MN_CALL_REDIAL_CFG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CS_Call_Redial_CFG length Error");
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
        return;
    }

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_CS_Call_Redial_CFG,
                         &stCallRedialCfg, sizeof(MN_CALL_REDIAL_CFG_STRU)))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CS_Call_Redial_CFG Error");
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
        MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
        return;
    }

    if (MN_CALL_NV_ITEM_ACTIVE == stCallRedialCfg.ucCallRedialSupportFlg)
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        /* nv�д��ʱ��Ϊ�룬��Ҫת��Ϊ���� */
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod
            = MN_CALL_ONE_THOUSAND_MILLISECOND * stCallRedialCfg.ulCallRedialPeriod;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval
            = MN_CALL_ONE_THOUSAND_MILLISECOND * stCallRedialCfg.ulCallRedialInterval;

    }
    else
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval   = 0;

    }

    /*ʶ�����һ�����ԣ�Ϊ�˵�ʱ��������FR�Ĳ���*/
    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod -= pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval;

    MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialPeriod);
    MN_CALL_UpdateTimerPeriod(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ulCallRedialInterval);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    /*����ܵ��ز����ش��ˣ���ô��ȡdisconnect�������õ�NV*/
    if (VOS_TRUE == pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.ucCallRedialSupportFlg)
    {
        MN_CALL_ReadCallRedialDiscCauseCfgNvim();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadCallRedialCmSrvRejCfgNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��24��
    ��    ��   : n00355355
    �޸�����   : ֧�ֺ����ؽ�����nv��
*****************************************************************************/

VOS_VOID  MN_CALL_ReadCallRedialCmSrvRejCfgNvim( VOS_VOID )
{
    TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU                     stCallRedialCmSrvRejCfg;
    VOS_UINT32                                              ulLength;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;


    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum = 0;

        return;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    if (ulLength > sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCfgNvim():WARNING: en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG length Error");

        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum = 0;

        return;
    }

    PS_MEM_SET(&stCallRedialCmSrvRejCfg, 0x0, sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU));

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG,
                         &stCallRedialCmSrvRejCfg, sizeof(TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU)))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCmSrvRejCfgNvim():WARNING: TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU Error");

        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum = 0;

        return;
    }

    if (stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum > TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum    = TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM;
    }

    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum
        = stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum;

    PS_MEM_CPY(pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialCmSrvRejCfg.aucCallRedialCmSrvRejCause,
                stCallRedialCmSrvRejCfg.aucCallRedialCmSrvRejCause,
                stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum);

   return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadCallRedialDiscCauseCfgNvim
 ��������  : ��ȡNVIM�е�MN_CALL_ReadCallRedialDiscCauseCfgNvim������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID  MN_CALL_ReadCallRedialDiscCauseCfgNvim( VOS_VOID )
{
    TAF_CALL_REDIAL_DISC_CFG_STRU       stCallRedialDiscCauseCfg;
    MN_CALL_CUSTOM_CFG_INFO_STRU                  *pstCustomCfg = VOS_NULL_PTR;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    PS_MEM_SET(&stCallRedialDiscCauseCfg, 0x0, sizeof(TAF_CALL_REDIAL_DISC_CFG_STRU));

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_CALL_REDIAL_DISC_CAUSE_CFG,
                         &stCallRedialDiscCauseCfg, sizeof(TAF_CALL_REDIAL_DISC_CFG_STRU)))
    {
        MN_WARN_LOG("MN_CALL_ReadCallRedialCmSrvRejCfgNvim():WARNING: en_NV_Item_CALL_REDIAL_DISC_CAUSE_CFG Error");
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialForDiscSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialDiscCauseNum = 0;

        return;
    }

    if (  MN_CALL_NV_ITEM_ACTIVE == stCallRedialDiscCauseCfg.ucCallRedialForDiscSupportFlg )
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialForDiscSupportFlg = VOS_TRUE;
    }
    else
    {
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialForDiscSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialDiscCauseNum = 0;

        return;
    }

    if (stCallRedialDiscCauseCfg.ucCallRedialDiscCauseNum > TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM)
    {
        stCallRedialDiscCauseCfg.ucCallRedialDiscCauseNum = TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM;
    }

    pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.ucCallRedialDiscCauseNum
        = stCallRedialDiscCauseCfg.ucCallRedialDiscCauseNum;

    PS_MEM_CPY(pstCustomCfg->stCallRedialCfgInfo.stCallRedialCfg.stCallRedialDiscCfg.aucCallRedialDiscCause,
                stCallRedialDiscCauseCfg.aucCallRedialDiscCause,
                stCallRedialDiscCauseCfg.ucCallRedialDiscCauseNum * sizeof(VOS_UINT8));

   return;
}



/*****************************************************************************
 �� �� ��  : TAF_CALL_ReadCallNotSupportedCause
 ��������  : ��ȡCALLģ����ն˲�֧��CALL���ظ�RELEASE COMPLETE��Ϣԭ����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��09��
    ��    ��   : f62575
    �޸�����   : DTS2013120411878���ն˲�֧��VOICE/VIDEO CALL���ظ�RELEASE
COMPLETE��Ϣԭ����ֵ
*****************************************************************************/
VOS_VOID TAF_CALL_ReadCallNotSupportedCause(VOS_VOID)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg = VOS_NULL_PTR;
    TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU             stVoiceCallNotSupportedCause;

    if (NV_OK != NV_Read(en_NV_Item_CALL_CallNotSupportedCause,
                         &stVoiceCallNotSupportedCause,
                         sizeof(stVoiceCallNotSupportedCause)))
    {
        stVoiceCallNotSupportedCause.ucVoiceCallNotSupportedCause = MN_CALL_USER_BUSY;
        stVoiceCallNotSupportedCause.ucVideoCallNotSupportedCause = MN_CALL_INCOMPATIBLE_DESTINATION;
    }

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    pstCustomCfg->ucVoiceCallNotSupportedCause =
                      stVoiceCallNotSupportedCause.ucVoiceCallNotSupportedCause;
    pstCustomCfg->ucVideoCallNotSupportedCause =
                      stVoiceCallNotSupportedCause.ucVideoCallNotSupportedCause;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_ReadAtaReportOkAsyncCfgNvim
 ��������  : ��ȡata �Ƿ��첽�ϱ�ok����nv��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_CALL_ReadAtaReportOkAsyncCfgNvim(VOS_VOID)
{
    TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU              stAtaReportOkAsyncCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Ata_Report_Ok_Async_Cfg, &ulLength);

    PS_MEM_SET(&stAtaReportOkAsyncCfg, 0x0, sizeof(stAtaReportOkAsyncCfg));

    /* ����Ĭ��ֵΪVOS_FALSE */
    TAF_CALL_SetAtaReportOkAsyncFlag(VOS_FALSE);

    if (ulLength > sizeof(TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU))
    {
       return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Ata_Report_Ok_Async_Cfg,
                         &stAtaReportOkAsyncCfg,
                         sizeof(stAtaReportOkAsyncCfg)))
    {
        return;
    }

    if (VOS_TRUE == stAtaReportOkAsyncCfg.ucAtaReportOkAsyncFlag)
    {
        TAF_CALL_SetAtaReportOkAsyncFlag(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_ReadCcwaCtrlModeNvim
 ��������  : ��ȡccwa����ģʽ��NV��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CALL_ReadCcwaCtrlModeNvim(VOS_VOID)
{
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU                       stCcwaCtrlMode;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Ccwa_Ctrl_Mode, &ulLength);

    PS_MEM_SET(&stCcwaCtrlMode, 0x0, sizeof(stCcwaCtrlMode));

    if (ulLength > sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU))
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Ccwa_Ctrl_Mode,
                         &stCcwaCtrlMode,
                         sizeof(stCcwaCtrlMode)))
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode read Error");
        return;
    }


    if (stCcwaCtrlMode.enCcwaCtrlMode >= TAF_CALL_CCWA_CTRL_MODE_BUTT)
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode enCcwaCtrlMode Error");
        return;
    }

    if (stCcwaCtrlMode.enCcwaiMode >= TAF_CALL_CCWAI_MODE_BUTT)
    {
        MN_ERR_LOG("TAF_CALL_ReadCcwaCtrlModeNvim():ERROR: en_NV_Item_Ccwa_Ctrl_Mode enCcwaiMode Error");
        return;
    }

    TAF_CALL_SetCcwaCtrlMode(stCcwaCtrlMode.enCcwaCtrlMode);

    TAF_CALL_SetCcwaiMode(stCcwaCtrlMode.enCcwaiMode);

    TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_CALL_ReadCcwaCtrlModeNvim ", stCcwaCtrlMode.enCcwaCtrlMode, stCcwaCtrlMode.enCcwaiMode);

    return;
}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_CALL_ReadEcallCfgNvim
 ��������  : ��ȡeCall�ز�ʱ�����ز�����¼�

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
  2.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : NAS���������Ż�
*****************************************************************************/
VOS_VOID TAF_CALL_ReadEcallCfgNvim(VOS_VOID)
{
    TAF_CALL_NVIM_ECALL_CFG_STRU        stEcallCfg;
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();

    PS_MEM_SET(&stEcallCfg, 0x0, sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_ECALL_CFG_INFO, &ulLength);

    if (ulLength > sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU))
    {
        MN_WARN_LOG("TAF_CALL_ReadEcallRedialCfgNvim():WARNING: en_NV_Item_ECALL_REDIAL_CFG_INFO length Error");
        /* NV���ȷǷ���Ĭ��eCall�ز�֧�֣���ʱ��ʱ��ʹ��hard code�е�ȱʡֵ */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH);

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH);

        return;
    }

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_ECALL_CFG_INFO,
                         &stEcallCfg, sizeof(TAF_CALL_NVIM_ECALL_CFG_STRU)))
    {
        MN_WARN_LOG("TAF_CALL_ReadEcallRedialCfgNvim():WARNING: en_NV_Item_ECALL_REDIAL_CFG_INFO Error");
        /* NV��ȡʧ�ܣ�Ĭ��eCall�ز�֧�֣���ʱ��ʱ��ʹ��hard code�е�ȱʡֵ */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH);

        MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH);

        return;
    }

    if (MN_CALL_NV_ITEM_ACTIVE == stEcallCfg.ucEcallRedialSupportFlg)
    {
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_TRUE;

        /* nv�д��ʱ��Ϊ�룬��Ҫת��Ϊ���� */
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod
            = (VOS_UINT32)(MN_CALL_ONE_THOUSAND_MILLISECOND * stEcallCfg.usEcallRedialPeriod);
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval
            = (VOS_UINT32)(MN_CALL_ONE_THOUSAND_MILLISECOND * stEcallCfg.usEcallRedialInterval);
    }
    else
    {
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ucCallRedialSupportFlg = VOS_FALSE;
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod     = 0;
        pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval   = 0;
    }

    /*ʶ�����һ�����ԣ�Ϊ�˵�ʱ��������FR�Ĳ���*/
    pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod -= pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval;

    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD,
                              pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialPeriod);
    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL,
                              pstCustomCfg->stCallRedialCfgInfo.stEcallRedialCfg.ulCallRedialInterval);

    /* ����T9ʱ��, �������1~12Сʱ��Χ�������£�ʹ��ȱʡֵ */
    if ((stEcallCfg.ucEcallT9Len < TAF_CALL_T9_MIN_TIMER_LENGTH)
     || (stEcallCfg.ucEcallT9Len > TAF_CALL_T9_MAX_TIMER_LENGTH))
    {
        return;
    }

    MN_CALL_UpdateTimerPeriod(TAF_CALL_TID_T9, (stEcallCfg.ucEcallT9Len*TAF_CALL_ONE_HOUR_TIMER_LENGTH));

    return;
}
#endif
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadNvimInfo
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
  2.��    ��   : 2012��6��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   : 2013��12��09��
    ��    ��   : f62575
    �޸�����   : DTS2013120411878���ն˲�֧��VOICE/VIDEO CALL���ظ�RELEASE COMPLETE��Ϣԭ����ֵ
  5.��    ��   : 2014��04��08��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
  6.��    ��   : 2014��6��24��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
*****************************************************************************/
VOS_VOID MN_CALL_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_CustomizeService */
    MN_CALL_ReadCustomizeServiceNvim();

    /* en_NV_Item_MultiSimCallConf */
    MN_CAL_ReadMultiSimCallConfNvim();

    /* en_NV_Item_VIDEO_CALL */
    MN_CAL_ReadVideoCallNvim();

    /* en_NV_Item_NVIM_CCBS_SUPPORT_FLG */
    MN_CAL_ReadCcbsNvim();

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    /* en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG */
    MN_CAL_ReadCallDeflectionNvim();

    /* en_NV_Item_NVIM_ALS_SUPPORT_FLG */
    MN_CAL_ReadAlsSupportNvim();

    /* en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG */
    MN_CALL_ReadReportEccNumSupportNvim();

    MN_CALL_ReadCallRedialCfgNvim();

    MN_CALL_ReadCallRedialCmSrvRejCfgNvim();

    TAF_CALL_ReadCallNotSupportedCause();

    TAF_CALL_ReadAtaReportOkAsyncCfgNvim();

    TAF_CALL_ReadCcwaCtrlModeNvim();

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* ��ȡeCall���ò��� */
    TAF_CALL_ReadEcallCfgNvim();
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */
    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



