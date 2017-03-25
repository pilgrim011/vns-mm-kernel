/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmaMmcInterface.h
  Description : TAF��MMC�ӿ�ͷ�ļ�
  History     :
      1.  ��־��   2003.11.26   �°�����
      2.  ���r     2005.11.20   ����3����Ϣ�ṹ��RSSI��SPECIALIZE PLMN REQ,
                                SPECIALIZE PLMN CNF, �޸�TAF SERVICE STATUS IND

      3.��    ��   : 2006��8��4��
        ��    ��   : liuyang id:48197
        �޸�����   : �������ⵥ�ţ�A32D05223
      4.��    ��   : 2007��5��22��
        ��    ��   : Li Jilin 60827
        �޸�����   : A32D11131
      5.��    ��   : 2007��7��20��
        ��    ��   : Li Jilin 60827
        �޸�����   : A32D12536
      6.��    ��   : 2007��09��30��
        ��    ��   : luojian id:107747
        �޸�����   : A32D12980
      7.��    ��   : 2008��3��17��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D02570,NAS B005�汾�����������
      8.��    ��   : 2008��4��22��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D02941,С����Bar�󣬽���GMM Attachû����Ӧ
      9.��    ��   : 2008��06��20��
        ��    ��   : l00107747
        �޸�����   : ���ⵥ��:AT2D03832,�޸�MMC��TAF��״̬�ϱ��ӿ�
     10.��    ��   : 2009��07��07��
        ��    ��   : h44270
        �޸�����   : ���ⵥ�ţ�AT2D12792��������ʾEGPRSС����Ϣ
     11.��    ��   : 2009��11��28��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�AT2D15677,�Ĵ��������ζ��ƺ���
     12.��    ��   : 2011��04��23��
        ��    ��   : L00171473
        �޸�����   : for V7R1 porting, ȥ��ö�ٳ�Ա���Ķ��ţ��������WARNING
*******************************************************************************/

#ifndef _TAF_MMC_INTERFACE_H_
#define _TAF_MMC_INTERFACE_H_

#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "TafAppMma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-8, begin */
#define TAFMMC_CBS_NO_NETWORK_IND       (1)
#define TAFMMC_CBS_CURR_NET_MODE_IND    (2)

#define TAFMMC_APS_SERVICE_STATE_IND    (3)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
}TAFMMC_CBS_NO_NETWORK_IND_STRU;


/* MMC���͸�MSGģ��ĵ�ǰ����ģʽ��Ϣ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucCurNetWork;                           /* ��ǰ����ģʽ */
    VOS_UINT8                           aucReserve[3];
}TAFMMC_CBS_CURR_NET_MODE_IND_STRU;
/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-8, end */


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
