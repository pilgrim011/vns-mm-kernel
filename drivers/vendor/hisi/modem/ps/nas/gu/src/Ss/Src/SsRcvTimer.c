/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvTimer.c
  Description  : ����Timer�����Ϣ�Ĵ���
  Function List:
      1.  Ss_T551Expiry         T551�����Ĵ���
      2.  Ss_RcvTimerOut        ����TIMER����ķַ������ú�����CC���ã�
  History:
      1.  ��־�� 2004.03.09   �°�����
      2.  ��    ��   : 2006��10��8��
          ��    ��   : luojian id:60022475
          �޸�����   : ���ⵥ��:A32D06583���޸�Ss_RcvTimerOut����
      3.  ��  �� 2006.11.07   ���ⵥA32D07063
*******************************************************************************/


#include "SsInclude.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*=>A32D07063*/
#if 0
/***********************************************************************
*  MODULE   : Ss_T551Expiry
*  FUNCTION : T551�����Ĵ���
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_T551Expiry(
                   VOS_UINT8 ucTi
                   )
{
    ST_SSP_MSG                      stSsMsg;

    SS_WARN_LOG( "\n SS TimerExpiry: T551\r" );
    if( SS_S_CONNECTED == g_SsEntity[ucTi].ucState )
    {                                                                           /* �ж��Ƿ��������                         */

        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* ����CR                                   */
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* ������Ϣѡ��                             */
        Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* ����Ϣ�ռ�����                           */
        SSA_DealMsgFromSS(&stSsMsg);

        Ss_SndRelCmpl( VOS_NULL_PTR, ucTi, SS_CAUSE_RECOVERY_TIMER_EXPIRY );            /* ����DR(RELEASE COMPLETE #102)            */
        Ss_SndMmssRelReq( ucTi );                                               /* ��MM����MMSS_REL_REQԭ��ͷ�MM����     */
        Ss_EntityClear( ucTi );                                                 /* �ͷŶ�Ӧ��SSʵ��                         */
    }
}
#endif
/*<=A32D07063*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVTIMER_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/***********************************************************************
*  MODULE   : Ss_RcvTimerOut
*  FUNCTION : ����TIMER����ķַ������ú�����CC���ã�
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��Ti
*             VOS_UINT8     ucTimerId   ��ʱ��id
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
      2.  ��    ��   : 2006��10��8��
          ��    ��   : luojian id:60022475
          �޸�����   : ���ⵥ��:A32D06583���޸�Ss_RcvTimerOut����
      3.��    ��   : 2012��02��24��
        ��    ��   : ��ӳ��/f62575
        �޸�����   : C50_IPC Project �����ȴ�USIM��FDN�������ʱ����
      4.��    ��   : 2013��04��08��
        ��    ��   : l65478
        �޸�����   : DTS2013032201710:�����²�ȥ
      5.��    ��   : 2013��05��17��
        ��    ��   : w00176964
        �޸�����   : SS FDN&Call Control��Ŀ:FDN���ɾ��
      6.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����   :DTS2013082903019:֧��ss�ط�����
      7.��    ��   : 2014��5��22��
        ��    ��   : z00161729
        �޸�����   : DTS2014050601476:L��绰�ض���g�����е绰�Ҷϣ�mm����cc abort��
                     g��ѯcsfb״̬�Ǵ��ڣ�lau������û����������FR���̵�L
************************************************************************/

VOS_VOID Ss_RcvTimerOut(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT8                           ucSsTi;


    if (TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER == ucTimerId)
    {
        ucSsTi = Ss_GetSsTi(ucTi);

        Ss_SndMmssAbortReq(ucSsTi);
    }


    TAF_SSA_RcvTimerExpired(ucTimerId, ucTi);




    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

