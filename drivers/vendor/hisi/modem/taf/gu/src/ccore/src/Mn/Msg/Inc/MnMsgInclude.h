/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgInclude.h
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��15��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��15��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __MNMSGINCLUDE_H__
#define __MNMSGINCLUDE_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "Ps.h"
#include  "NasSms.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"
#include  "MnComm.h"
#include  "MnErrorCode.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

#include  "TafMmcInterface.h"
#include  "MnMsgExt.h"
#include  "MnMsgApi.h"
#include  "MnMsgSmCommProc.h"
#include  "MnMsgSendSms.h"
#include  "MnMsgTimerProc.h"
#include  "UsimPsInterface.h"
#include  "NVIM_Interface.h"
#include  "MnMsgUsimProc.h"
#include  "MnMsgTs.h"
#include  "MnMsgReport.h"
#include  "UsimPsApi.h"
#include  "NasComm.h"

#include  "TafCbsInterface.h"

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, begin */
#if (FEATURE_IMS == FEATURE_ON)
#include  "MsgImsaInterface.h"
#endif
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, end */

#endif /* __MNMSGINCLUDE_H__ */

