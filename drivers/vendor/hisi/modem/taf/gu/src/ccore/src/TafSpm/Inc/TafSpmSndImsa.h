/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmSndImsa.h
  �� �� ��   : ����
  ��    ��   : s00217060
  ��������   : 2013��7��16��
  ����޸�   :
  ��������   : ����SPM���͸�IMSA��Ϣ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��16��
    ��    ��   : s00217060
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _TAF_SPM_SND_IMSA_H_
#define _TAF_SPM_SND_IMSA_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaCallOrigReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaSupsCmdReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCallInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg,
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8 enReqType
);

VOS_VOID TAF_SPM_SendImsaGetClprReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaStartDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaStopDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCdurReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaRegisterSsReq
 ��������  : ����REGISTER��Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaRegisterSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaEraseSsReq
 ��������  : ����ERASE��Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaEraseSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaActivateSsReq
 ��������  : ����ACTIVATE������Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaActivateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaDeactivateSsReq
 ��������  : ����DEACTIVATE������Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaDeactivateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaInterrogateSsReq
 ��������  : ����Interrogate������Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaInterrogateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaProcessUssSsReq
 ��������  : ����USSD DATA��Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaProcessUssSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendImsaReleaseSsReq
 ��������  : ����release������Ϣ��IMSA
 �������  : pstAppMsg ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaReleaseSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaCallInviteNewPtptReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallAnswerRemoteModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaEconfAddUsersReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaEconfDialReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaGetEconfInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_FillImsaEconfCallList(
    TAF_CALL_ECONF_CALL_LIST_STRU      *pstCallList
);


#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


