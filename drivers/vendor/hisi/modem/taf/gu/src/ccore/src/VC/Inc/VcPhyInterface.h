/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : VcPhyInterface.h
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2009��7��05��
  ����޸�   : 2009��7��05��
  ��������   : VCģ���HPA֮��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��7��05��
    ��    ��   : h44270
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  VC_PHY_INTERFACE_H
#define  VC_PHY_INTERFACE_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "VcCallInterface.h"
#include "AppVcApi.h"
#include "VcCodecInterface.h"
#include "NasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#include "VcComm.h"

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
enum VC_GPHY_MSG_ID_ENUM
{
    /* VC->GDSP */
    ID_VC_GPHY_TEST_MODE_NOTIFY         = 0xE705,

    /* GDSP->VC */

    ID_VC_GPHY_MSG_BUTT
};
typedef VOS_UINT16 VC_GPHY_MSG_ID_ENUM_U16;

typedef struct
{
    VOS_INT16                           sTxVol[20];                             /* ����������dBֵ, -80~12 */
    VOS_INT16                           sRxVol[20];                             /* ����������dBֵ, -80~12 */
    VOS_UINT16                          usSlopeEnable;                          /* Ԥ�����˲�ʹ�� */
    VOS_INT16                           asSlopeCoeff[15];                       /* Ԥ�����˲�ϵ�� */
    VOS_UINT16                          usTxHpfEnable;                          /* ���и�ͨ�˲�ʹ�� */
    VOS_INT16                           asTxHpfCoeff[8];                        /* ���и�ͨ�˲�ϵ�� */
    VOS_UINT16                          usRxHpfEnable;                          /* ���и�ͨ�˲�ʹ�� */
    VOS_INT16                           asRxHpfCoeff[8];                        /* ���и�ͨ�˲�ϵ�� */
    VOS_INT16                           sDevTxGain;                             /* �豸������棨Codec�������棩 */
    VOS_INT16                           sDevRxGain;                             /* �豸�������棨Codec�������棩 */
    VOS_INT16                           sSideGain;                              /* �������� */
    VOS_UINT16                          usTxCompEnable;                         /* ���в���ʹ�� */
    VOS_INT16                           asTxCompCoeff[31];                      /* ���в����˲�ϵ�� */
    VOS_UINT16                          usRxCompEnable;                         /* ���в���ʹ�� */
    VOS_INT16                           asRxCompCoeff[31];                      /* ���в����˲�ϵ�� */
    VOS_UINT16                          usEcEnable;                             /* ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asEcParam[20];                          /* EC���� */
    VOS_UINT16                          usNsEnable;                             /* ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asNsParam[10];                          /* NS���� */
    VOS_UINT16                          usAgcEnable;                            /* �Զ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asAgcParam[6];                          /* AGC���� */
}VC_DEVICE_PARA_NV_STRU;


typedef struct
{
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode;                           /* �����豸��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ���� */
    VOS_INT16                           sTxVol;                                 /* ����������dBֵ, -80~12 */
    VOS_INT16                           sRxVol;                                 /* ����������dBֵ, -80~12 */
    VOS_UINT16                          usSlopeEnable;                          /* Ԥ�����˲�ʹ�� */
    VOS_INT16                           asSlopeCoeff[15];                       /* Ԥ�����˲�ϵ�� */
    VOS_UINT16                          usTxHpfEnable;                          /* ���и�ͨ�˲�ʹ�� */
    VOS_INT16                           asTxHpfCoeff[8];                        /* ���и�ͨ�˲�ϵ�� */
    VOS_UINT16                          usRxHpfEnable;                          /* ���и�ͨ�˲�ʹ�� */
    VOS_INT16                           asRxHpfCoeff[8];                        /* ���и�ͨ�˲�ϵ�� */
    VOS_INT16                           sDevTxGain;                             /* �豸������棨Codec�������棩 */
    VOS_INT16                           sDevRxGain;                             /* �豸�������棨Codec�������棩 */
    VOS_INT16                           sSideGain;                              /* �������� */
    VOS_UINT16                          usTxCompEnable;                         /* ���в���ʹ�� */
    VOS_INT16                           asTxCompCoeff[31];                      /* ���в����˲�ϵ�� */
    VOS_UINT16                          usRxCompEnable;                         /* ���в���ʹ�� */
    VOS_INT16                           asRxCompCoeff[31];                      /* ���в����˲�ϵ�� */
    VOS_UINT16                          usEcEnable;                             /* ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asEcParam[20];                          /* EC���� */
    VOS_UINT16                          usNsEnable;                             /* ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asNsParam[10];                          /* NS���� */
    VOS_UINT16                          usAgcEnable;                            /* �Զ��������ʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_INT16                           asAgcParam[6];                          /* AGC���� */
    VOS_UINT16                          usReserve2;                             /* ���� */
}VC_DEVICE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : VC_PHY_SET_DEVICE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ������������ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ԭ������ */
    VOS_UINT16                          usReserve;                              /* ���� */
    VC_DEVICE_PARA_STRU                 stDevPara;                              /* ���� */
}VC_PHY_SET_DEVICE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VC_PHY_TEST_MODE_NOTIFY_STRU
 �ṹ˵��  : ֪ͨ�����������ģʽ
 1.��    ��   : 2012��3��8��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ԭ������ */
    VOS_UINT8                           aucReserved[2];
}VC_PHY_TEST_MODE_NOTIFY_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/





/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-31, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-31, end */

/*****************************************************************************
�� �� ��  : APP_VC_SendStartReq
��������  : ������ϢID_VC_CODEC_START_REQ�������
�������  : pstChanInfo - �ŵ���Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��07��05��
    ��    ��   : h44270
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32  APP_VC_SendStartReq(
    CALL_VC_CHANNEL_INFO_STRU           *pstChanInfo,
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode
);

/*****************************************************************************
�� �� ��  : APP_VC_SendStopReq
��������  : ������ϢVC_PHY_STOP_REQ�������
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��07��05��
    ��    ��   : h44270
    �޸�����   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendStopReq(CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode);

VOS_UINT32  APP_VC_SendSetDeviceReq(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDeviceMode
);

/*****************************************************************************
�� �� ��  : APP_VC_SendSetVolumeReq
��������  : ������ϢVC_PHY_SET_VOLUME_REQ�������
�������  : pstChanInfo - �ŵ���Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��07��05��
    ��    ��   : h44270
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32  APP_VC_SendSetVolumeReq(
    VOS_UINT16                          usVolTarget,
    VOS_INT16                           sVolValue
);

/*****************************************************************************
�� �� ��  : APP_VC_SendSetCodecReq
��������  : ������ϢVC_PHY_SET_CODEC_REQ�������
�������  : pstChanInfo - �ŵ���Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��07��05��
    ��    ��   : h44270
    �޸�����   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetCodecReq(CALL_VC_CHANNEL_INFO_STRU *pstChanInfo);

/*****************************************************************************
�� �� ��  : APP_VC_SendEndCallReq
��������  : ���͹Ҷϵ绰��Ϣ��CALLģ��
�������  : pstChanInfo - �ŵ���Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��07��05��
    ��    ��   : h44270
    �޸�����   : Creat
2.  ��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID APP_VC_SendEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32  enCause
);


/*****************************************************************************
�� �� ��  : APP_VC_SendPhyTestModeNotify
��������  : ������ϢID_VC_GPHY_TEST_MODE_NOTIFY��DSP����ģʽ֪ͨ
�������  : enMode - ����ģʽ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��03��08��
    ��    ��   : h44270
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID APP_VC_SendPhyTestModeNotify(
    CALL_VC_RADIO_MODE_ENUM_U8              enMode
);


/*****************************************************************************
�� �� ��  : APP_VC_SendSetForeGroundReq
��������  : VC �·� CODEC ����ǰ��ģʽ��������
�������  : pstMsg - ��������Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendSetForeGroundReq(VOS_VOID);

/*****************************************************************************
�� �� ��  : APP_VC_SendSetBackGroundReq
��������  : VC �·� CODEC ���ú���ģʽ��������
�������  : pstMsg - ��������Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendSetBackGroundReq(VOS_VOID);

/*****************************************************************************
�� �� ��  : APP_VC_SendGroundQry
��������  : VC �·� CODEC ��ѯǰ��ģʽ��������
�������  : pstMsg - ��������Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 APP_VC_SendGroundQry(VOS_VOID);

/*****************************************************************************
�� �� ��  : APP_VC_SendSetForeGroundCnf
��������  : VC ���� AT ǰ��ģʽ���ûظ���Ϣ
�������  : clientId--AT Client ID,enExeRslt--��������������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetForeGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
�� �� ��  : APP_VC_SendSetBackGroundCnf
��������  : VC ���� AT ����ģʽ���ûظ���Ϣ
�������  : clientId--AT Client ID,enExeRslt--��������������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendSetBackGroundCnf(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
�� �� ��  : APP_VC_SendGroundRsp
��������  : VC ���� AT ��ѯǰ��ģʽ�ظ���Ϣ
�������  : clientId--AT Client ID,enState--��ѯ״̬��ucQryRslt--��ѯ�������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2012��12��28��
    ��    ��   : ����/00214637
    �޸�����   : Creat
*****************************************************************************/
VOS_VOID APP_VC_SendGroundRsp(
    MN_CLIENT_ID_T                      clientId,
    VCVOICE_GROUND_ENUM_UINT16          enState ,
    VOS_UINT8                           ucQryRslt
);

/*****************************************************************************
 �� �� ��  : APP_VC_SendSetModemLoopReq
 ��������  : VC����Codec������������ģʽ����Ϣ
 �������  : VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��5��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 APP_VC_SendSetModemLoopReq(VCVOICE_LOOP_ENUM_UINT16 enVoiceLoop);


/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-18, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID APP_VC_SendImsaExceptionNtf(
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enCause
);
#endif

VOS_VOID  APP_VC_LogEndCallReq(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
);

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-18, end */

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
/*****************************************************************************
�� �� ��  : APP_VC_SendAtSetCnf
��������  : VC�ظ�AT������Ϣ
�������  : usMsgName -- ��Ϣ����
            clientId--AT Client ID
            enExeRslt--���ò������
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SendAtSetCnf(
    VOS_UINT16                          usMsgName,
    MN_CLIENT_ID_T                      usClientId,
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

/*****************************************************************************
�� �� ��  : APP_VC_SendQryMsdCnf
��������  : VC�ظ�AT MSD ��ѯ���
�������  : clientId--AT Client ID
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :
�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SendQryMsdCnf(
    MN_CLIENT_ID_T                      usClientId
);

/*****************************************************************************
�� �� ��  : APP_VC_SendQryEcallCfgCnf
��������  : VC�ظ�AT eCall���ò�ѯ���
�������  : clientId--AT Client ID
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :
�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SendQryEcallCfgCnf(
    MN_CLIENT_ID_T                      usClientId
);


/*****************************************************************************
�� �� ��  : APP_VC_SendEcallCfgReq
��������  : ������ϢID_VC_VOICE_SET_ECALLCFG_REQ��MED
�������  :
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT32  APP_VC_SendEcallCfgReq(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enMode,
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16 enVocConfig
);

/*****************************************************************************
�� �� ��  : APP_VC_SendEcallTransStatusInd
��������  : ������ϢVC_CALL_ECALL_TRANS_STATUS_NTF��Callģ��
�������  : enEcallTransStatus  --����״̬
            enEcallTransFailCause -- ʧ��ԭ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SendEcallTransStatusInd(
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8      enEcallTransStatus,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enEcallTransFailCause
);


/*****************************************************************************
�� �� ��  : APP_VC_SendMsdReq
��������  : ����MSD���ݸ�MEDģ��
�������  : ��
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :
�޶���¼  :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SendMsdReq(VOS_VOID);
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

VOS_UINT32 APP_VC_SendDtmfInd(
    VOICEVC_DTMF_IND_STRU              *pstDtmfInd
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32  APP_VC_SendSoCtrlOrderInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    VOS_UINT8                       ucORDQ
);

VOS_UINT32  APP_VC_SendSoCtrlMsgInd(
    VCVOICE_TYPE_ENUM_UINT16        enCodecType,
    SO_CTRL_MSG_CODEC_STRU         *pstCodec
);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* VC_PHY_INTERFACE_H */

