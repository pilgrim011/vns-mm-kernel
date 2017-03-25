/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsProcUsim.c
  �� �� ��   : ����
  ��    ��   : y00322978
  ��������   : 2015��11��30��
  ����޸�   :
  ��������   : TAF APS����usim��д�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��30��
    ��    ��   : y00322978
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsProcUsim.h"
#include  "NasUsimmApi.h"
#include  "TafSdcCtx.h"
#include  "TafApsComFunc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PROC_USIM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_GetWaitSimFilesCnfFlg
 ��������  : ���������л�ȡ��ȡSIM���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡSIM���ļ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_APS_GetWaitSimFilesCnfFlg(VOS_VOID)
{
    return TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ClearWaitSimFilesCnfFlg
 ��������  : ���������������ȡSIM���ļ��ظ����
 �������  : enSimFileCnfFlg - SIM���ļ��ظ����
             ulAppType       - APP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : Y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
)
{
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enRead3GpdFileFlag;

    enRead3GpdFileFlag = TAF_APS_Map3GpdFileIdAndFlag(usEfId);

    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg &= ~enRead3GpdFileFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetWaitSimFilesCnfFlg
 ��������  : ��������������SIM���ļ��ظ����
 �������  : enSimFileCnfFlg - SIM���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : Y00322978
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    TAF_APS_SetWaitSimFilesCnfFlg(
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
)
{
    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg |= enSimFileCnfFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SendUsimFileReq
 ��������  : ����������Ϣȥ��ȡUSIM���ļ�
 �������  : USIMM_APP_TYPE_ENUM_UINT32          enAppType
             VOS_UINT16                          usEfId
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��3��
   ��    ��   : Y00322978
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                    enAppType,
                    usEfId,
                    0);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_Read3GdpFile
 ��������  : ������3Gpd�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : y00322978
    �޸�����   : DTS2015111309776
*****************************************************************************/
VOS_VOID TAF_APS_Read3GdpFile( VOS_VOID )
{
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    enCsimType                          = TAF_SDC_GetCsimType();

    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        return;
    }

    if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG);
    }

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG);

    }

    return;
}

#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
