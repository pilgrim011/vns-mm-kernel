/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCall.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��22��
  ����޸�   : 2007��8��22��
  ��������   : CCAģ����ⲿ�ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

  2.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
******************************************************************************/
#ifndef  MN_CALL_H
#define  MN_CALL_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "TafMmcInterface.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "TafLog.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "TafMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/

/* Max number of supported codecs in BC*/
#define MN_CALL_BC_MAX_SPH_VER_NUM          (6)





/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulStatus;                                       /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                  ulCustomizeService;                             /*�ն�˵������1��byte��Ϊ��û�пն��������4byte����3byte����*/
}MN_CALL_NV_ITEM_CUSTOMIZE_SERV_STRU;







/*****************************************************************************
 �ṹ��    : TAF_CALL_FDN_INFO_STRU
 �ṹ˵��  : CALLҵ��ģ��FDNҵ�����Բ����ṹ
             ulFdnStatus        (U)SIM��FDNҵ��ʹ��״̬
             stFdnConfig        ME��FDNҵ��NV����
1.��    ��   : 2012��02��23��
  ��    ��   : f62575
  �޸�����   : ����
2.��    ��   : 2013��6��5��
  ��    ��   : z00161729
  �޸�����   : SVLTE ��usim�ӿڵ����޸�
*****************************************************************************/
typedef struct
{
    TAF_FDN_CONFIG_STRU                   stFdnConfig;
}TAF_CALL_FDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CALL_BC_STRU
 �ṹ˵��  : CALLģ��BC�������ݽṹ�����ã��ο�Э��24008 10.5.4.5

  1.��    ��   : 2012��09��18��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;

    NAS_CC_IE_BC_OCTET3_STRU            Octet3;
    NAS_CC_IE_BC_OCTET3A_STRU           Octet3a;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3b;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3c;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3d;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3e;
    NAS_CC_IE_BC_OCTET4_STRU            Octet4;
    NAS_CC_IE_BC_OCTET5_STRU            Octet5;
    NAS_CC_IE_BC_OCTET5A_STRU           Octet5a;
    NAS_CC_IE_BC_OCTET5B_STRU           Octet5b;
    NAS_CC_IE_BC_OCTET6_STRU            Octet6;
    NAS_CC_IE_BC_OCTET6A_STRU           Octet6a;
    NAS_CC_IE_BC_OCTET6B_STRU           Octet6b;
    NAS_CC_IE_BC_OCTET6C_STRU           Octet6c;
    NAS_CC_IE_BC_OCTET6D_STRU           Octet6d;
    NAS_CC_IE_BC_OCTET6E_STRU           Octet6e;
    NAS_CC_IE_BC_OCTET6F_STRU           Octet6f;
    NAS_CC_IE_BC_OCTET6G_STRU           Octet6g;
    NAS_CC_IE_BC_OCTET7_STRU            Octet7;
}TAF_CALL_BC_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CS_ERR_CODE_MAP_STRU
 �ṹ˵��  : TAF������ԭ��ֵ�Ķ�Ӧ�ṹ

  1.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ����
*****************************************************************************/
typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    MN_CALL_CC_CAUSE_ENUM_U8            enCcCause;

} TAF_CS_ERR_CODE_MAP_STRU;
/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_CALL_Init
 ��������  : ִ��CCAģ��ĳ�ʼ�����������к���״̬�ĸ�λ��ȫ����Դ�ĳ�ʼ��
             TAFӦ����ϵͳ����ʱ��Resetʱ���øýӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_Init(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcAppReqMsg
 ��������  : ��������Ӧ�ò��������Ϣ
             �ú���������������ͽ���Ϣ�ַ�����Ӧ����������ȥ����
 �������  : pstMsg - Ӧ�ò����TAF APIʱ��API���������������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcAppReqMsg(
    const VOS_VOID                      *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccPrimMsg
 ��������  : ��������CC��MNCCԭ����Ϣ
             �ú�������ԭ��������Ϣ�ַ�����Ӧ��MNCCԭ�ﴦ����ȥ����
 �������  : pstMsg - ����CC��MNCCԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccPrimMsg(
    const VOS_VOID                      *pMsg
);

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
/* ɾ���ú��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcVCMsg
 ��������  : ��������VCģ�����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcVCMsg (VOS_VOID * pstMsg);

/*****************************************************************************
 �� �� ��  : MN_CALL_LineInfo
 ��������  : �յ�����λ��Ϣ���NVIM�л�ȡ��ǰѡ�����·
 �������  : enUsimStatus:��ǰ���Ƿ���λ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��25��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_LineInfo(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
);

VOS_VOID MN_CALL_ProcOmMsg(
    VOS_VOID                            *pstMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcCstCcPrimitive
 ��������  : ����CSTģ�鷢������Ϣԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstCallPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcRabmCallPrimitive
 ��������  : ��������Rabm����Ϣ��
 �������  : pMsg  - ��ʱ����ʱ��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_DispatchUsimMsg
 ��������  : �����USIM��������Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_DispatchUsimMsg(struct MsgCB * pstMsg);

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 �� �� ��  : MN_CALL_ProcUsimFdnInd(UT����ʹ��)
 ��������  : USIM������FDN״̬�ϱ���Ϣ���±���FDN״̬
 �������  : pstFdnStatusInd - �յ���USIM������FDN״̬�ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_VOID MN_CALL_ProcUsimFdnInd(struct MsgCB * pstMsg);
#endif


/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, end */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */


/*****************************************************************************
 �� �� ��  : MN_CALL_SupportMoCallType
 ��������  : ��ȡUE��ָ���������͵�֧��״̬
 �������  : MN_CALL_TYPE_ENUM_U8                enCallType  ��������
 �������  : VOS_BOOL                           *pSupported  UE�Ƿ�֧��ָ���ĺ�������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_BOOL                           *pSupported
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID MN_CALL_CsCallErrRecord(
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);


VOS_VOID MN_CALL_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen
);
VOS_VOID MN_CALL_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
);

VOS_VOID MN_CALL_CsCallDiscInfoRecord(
    MN_CALL_ID_T                            ucCallId,
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
);

#endif

extern VOS_VOID MN_CALL_ReadNvimInfo(VOS_VOID);

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
VOS_VOID TAF_CALL_ProcTafMsg (
    const VOS_VOID                      *pMsg
);

VOS_VOID TAF_CALL_ProcMmaMsg (
    const VOS_VOID                      *pMsg
);
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

TAF_VC_TTYMODE_ENUM_UINT8 TAF_CALL_GetTTYMode(VOS_VOID);
VOS_BOOL TAF_CALL_IsSupportTTYMode(VOID);

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

#endif /* MN_CALL_H */


