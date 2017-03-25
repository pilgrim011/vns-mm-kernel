/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCsCallCommFunc.c
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��12��22��
  ��������   : TAF CS CALL �����ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��22��
    ��    ��   : l00359089
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafCsCallCommDef.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_COMM_FUNC_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

VC_TO_TAFCS_CAUSE_STRU                    g_astVcCauseToTafCsCause[] =
{
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED         ,   TAF_CS_CAUSE_VC_ERR_STARTED         },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL   ,   TAF_CS_CAUSE_VC_ERR_PORT_CFG_FAIL   },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_DEVICE_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL  ,   TAF_CS_CAUSE_VC_ERR_SET_START_FAIL  },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_VOLUME_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL,   TAF_CS_CAUSE_VC_ERR_SAMPLE_RATE_FAIL},
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED,   TAF_CS_CAUSE_VC_ERR_TI_START_EXPIRED},
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_CALL_ConvertVcCauseToTafCsCause
 ��������  : VC��ԭ��ֵת��ΪTafCsCause
 �������  : enCause   - VCʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : TAF��ʧ��ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :2015��12��22��
    ��    ��   :l00359089
    �޸�����   :�½�
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_ConvertVcCauseToTafCsCause(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32 enVcCause
)
{
    TAF_CS_CAUSE_ENUM_UINT32            enTafCause;
    VOS_UINT32                          i;

    enTafCause  = TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;

    for (i = 0; i < (sizeof(g_astVcCauseToTafCsCause) / sizeof(g_astVcCauseToTafCsCause[0])); i++)
    {
        if (enVcCause == g_astVcCauseToTafCsCause[i].enVcCause)
        {
            enTafCause = g_astVcCauseToTafCsCause[i].enTafCsCasue;
            break;
        }
    }

    return enTafCause;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


