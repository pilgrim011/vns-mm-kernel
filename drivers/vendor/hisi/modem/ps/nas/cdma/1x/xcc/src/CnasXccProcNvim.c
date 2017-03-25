/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccProcNvim.c
  �� �� ��   : ����
  ��    ��   : c00299063
  ��������   : 2015��06��15��
  ��������   : XCC����NV�Ķ�ȡ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��06��15��
    ��    ��   : c00299063
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXccProcNvim.h"
#include  "CnasXccCtx.h"
#include  "NVIM_Interface.h"
#include  "CnasMntn.h"
#include  "NasNvInterface.h"
#include  "NasMntn.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_ReadCallCfgNvim
 ��������  : ��NV�л�ȡ���п�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��15��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��21��
   ��    ��   : y00245242
   �޸�����   : DTS2015120408853
*****************************************************************************/
VOS_VOID CNAS_XCC_ReadCallCfgNvim()
{
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_CALL_NVIM_CFG_STRU     stCallNvimCfg;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    NAS_MEM_SET_S(&stCallNvimCfg, sizeof(stCallNvimCfg), 0x0, sizeof(stCallNvimCfg));

    if (NV_OK != NV_Read(en_NV_Item_1X_CALL_CFG,
                         &stCallNvimCfg, sizeof(stCallNvimCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ReadCallCfgNvim:Read Nvim Failed");

        pstCallNvimCfg->ucIsL3ErrReOrigCount = VOS_FALSE;

        pstCallNvimCfg->ucPrivacyMode        = VOS_FALSE;
        return;
    }

    pstCallNvimCfg->ucIsL3ErrReOrigCount = stCallNvimCfg.ucIsL3ErrReOrigCount;

    pstCallNvimCfg->ucPrivacyMode        = stCallNvimCfg.ucPrivacyMode;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_WritePrivacyModeNvim
 ��������  : дprivacy mode��NV
 �������  : ucPrivacyMode -- privacy mode
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��21��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_WritePrivacyModeNvim(VOS_UINT8 ucPrivacyMode)
{
    CNAS_NVIM_1X_CALL_NVIM_CFG_STRU     stCallNvimCfg;

    NAS_MEM_SET_S(&stCallNvimCfg, sizeof(stCallNvimCfg), 0x0, sizeof(stCallNvimCfg));

    /* ����privacy mode */
    stCallNvimCfg.ucPrivacyMode = ucPrivacyMode;

    if (NV_OK != NV_Write(en_NV_Item_1X_CALL_CFG,
                          &stCallNvimCfg,
                          sizeof(stCallNvimCfg)))
    {
        NAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_WritePrivacyModeNvim: Write Nvim Failed");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_Read1xPagingRspSoCfg
 ��������  : ��ȡen_NV_Item_1X_PAGING_RSP_SO_CFG
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_Read1xPagingRspSoCfg(VOS_VOID)
{
    CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU                     *pstPagingRspSoCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU                     stNvPagingRspSoCfg;

    pstPagingRspSoCfg      = &(CNAS_XCC_GetCtxAddr()->stPagingRspSoCfg);

    NAS_MEM_SET_S(&stNvPagingRspSoCfg, sizeof(CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU), 0x0, sizeof(CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_PAGING_RSP_SO_CFG,
                         &stNvPagingRspSoCfg, sizeof(stNvPagingRspSoCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_Read1xPagingRspSoCfg:Read Nvim Failed");

        pstPagingRspSoCfg->ucNoDataSrvRspSo33Flg = VOS_FALSE;
        return;
    }

    pstPagingRspSoCfg->ucNoDataSrvRspSo33Flg = stNvPagingRspSoCfg.ucNoDataSrvRspSo33;

}


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : CNAS_XCC_ReadCallCfgNvim
 ��������  : ��NV�л�ȡ���������������ò����������������Լ���̬���ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��11��
   ��    ��   : l00359089
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ReadVoiceEncryptCapCfgPara(VOS_VOID)
{
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU        stNvimEccSrvCapInfo;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);
    NAS_MEM_SET_S(&stNvimEccSrvCapInfo, sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU), 0x00, sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO,
                         &stNvimEccSrvCapInfo,
                         sizeof(CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU)))
    {
        pstCallNvimCfg->ucEccSrvCap     = VOS_FALSE;
        pstCallNvimCfg->ucEccSrvStatus  = VOS_FALSE;

        CNAS_ERROR_LOG(UEPS_PID_XCC,
                       "CNAS_XCC_ReadVoiceEncryptCapCfgPara():Read en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO Error");
        return;
    }

    /* ����������ȡ��ֵ��� */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvCap)
    {
        stNvimEccSrvCapInfo.ucEccSrvCap     = VOS_TRUE;
    }

    /* ����״̬��ȡ��ֵ��� */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvStatus)
    {
        stNvimEccSrvCapInfo.ucEccSrvStatus  = VOS_TRUE;
    }

    pstCallNvimCfg->ucEccSrvCap         = stNvimEccSrvCapInfo.ucEccSrvCap;
    pstCallNvimCfg->ucEccSrvStatus      = stNvimEccSrvCapInfo.ucEccSrvStatus;
}
#endif

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




