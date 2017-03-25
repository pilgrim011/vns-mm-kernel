/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :Taf_Tafm_Db.c                                               */
/* Author        :zzy                                                         */
/* Description   :TAFͨ�Ų�������ģ��                                         */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 ����                                             */
/*               :2005-12-13 ���CS��ѯ����     �޸���:d49431                 */
/*               :2006-02-23 ���ⵥ:A32D02143   �޸���:L47619                 */
/*               :2006-02-23 ���ⵥ:A32D02147   �޸���:L47619                 */
/*               :2006-03-13 ���ⵥ:A32D02480   �޸���:H41410                 */
/*               :2006-03-13 ���ⵥ:A32D02493   �޸���:L47619                 */
/*               :2006-03-13 ���ⵥ:A32D02764   �޸���:D49431                 */
/*    1.��    �� : 2006-12-07
        ��    �� : ��³��
        �޸����� : A32D07824 ����CGEQNEG�Ĵ���
      2.��    �� : 2007��9��26��
        ��    �� : luojian id:107747
        �޸����� : ���ⵥ�ţ�A32D12931,��ѯAPI�ӿ����Ӵ������ϱ�
      3.��    ��   : 2008��08��25��
        ��    ��   : f62575
        �޸�����   : ���ⵥ�ţ�AT2D05096, AT��ѡ���TAF�·�������ģ��ʱ��������д����ȷ
******************************************************************************/
#include "Taf_Common.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */
#include "Taf_Aps.h"
#include "MmaAppLocal.h"
#include "MnComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_TAFM_DB_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*lint -save -e958 */

/**********************************************************/
/*         ���˱�TAF���õ�ͨ�Ų��������¼��ϱ��ӿ�API     */
/**********************************************************/
/**********************************************************
 Function:       Taf_ParaSetResult
 Description:    TAF��APP����ͨ�Ų������ý��
 Calls:          TAFM module
 Data Accessed:
 Data Updated:
 Input:          ClientId - �ͻ��˱�ʶ
                 OpId - ������ʶ
                 Result - �������ý��
 Output:
 Return:
 Others:
    1.2006-02-23 l47619     Modify ���ⵥ:A32D02143
    2.��    ��   : 2011��10��19��
      ��    ��   : f00179208
      �޸�����   : AT��ֲ��Ŀ,CallBack������
**********************************************************/
VOS_VOID  Taf_ParaSetResult (VOS_UINT16            ClientId,
                         VOS_UINT8                   OpId,
                         TAF_PARA_SET_RESULT      Result,
                         TAF_PARA_TYPE      QueryType,
                         VOS_VOID                     *pPara )
{

    MN_SETPARA_SendMsg(ClientId, OpId, Result, QueryType, pPara);

    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

