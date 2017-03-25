/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : chap_typ.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ�鶨��ChapЭ��ṹ��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/



#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES )

#ifndef      _CHAP_TYPE_H_
#define      _CHAP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* CHAP ���ƿ����ݽṹ���� */
typedef struct tagPppChapInfo 
{
    PPPINFO_S *pstPppInfo ;         /*PPP���ƿ�ָ��*/    
    VOID *pstAAAAuthReqMsg;    
    HTIMER ulRespTimeoutID;            /* ����Response��ʱ��ʱ��*/    
    HTIMER ulChalTimeoutID;            /* ����Challenge��ʱ��ʱ��*/

    VOS_UINT32 ulWaitAuthRspTimeout;             /* �ȴ�AAA��Ȩ��Ӧ��ʱʱ�� */
    VOS_UINT32 ulAuthMaxTransmits;				/* ��֤��������ʹ��� */    
    VOS_UINT32 ulRespTransmits;	        /* �Ѵ���Response���� */
    VOS_UINT32 ulChalTransmits;	        /* �Ѵ���Challenge ���� */
    VOS_UINT32 ulChalInterval;		        /* �ٴ���֤�Զ˵�ʱ���� */
    VOS_UINT32 ulTimeOutTime;		        /* ��ʱʱ�� */
    VOS_UINT32 ulMaxTransmits;		        /* ����ʹ��� */
    VOS_UINT32 ulWaitLnsAuthTimeOut;

    VOS_UINT16 usAuthClientFailureTimes;/* Client����֤ʧ�ܼ�����*/
    VOS_UINT16 usAuthServerFailureTimes;/* Server����֤ʧ�ܶ�ʱ��*/    
    UCHAR ucClientState;		    /* Client ״̬*/
    UCHAR ucRespLen;		        /* Response ���� */
    UCHAR ucRespId;			        /* Response ID*/
    UCHAR ucRespType;		        /* ����Response �Ĺ�ϣ�㷨����*/

    
    UCHAR ucServerState;		    /* Server ״̬ */
    UCHAR ucChalLen;			    /* Challenge ����*/
    UCHAR ucChalId;			        /* Challenge ID*/
    UCHAR ucChalType;		        /* ����Challenge�Ĺ�ϣ�㷨���� */
    UCHAR ucUsed;                   /*CHAP���ƿ�ʹ�ñ��*/
    UCHAR ucAuthTransmits;					/* ������֤����Ĵ��� */    
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2];
                                        /* ������*/

    UCHAR szChallenge[CHAP_MAX_CHALLENGE_LENGTH]; 
    UCHAR szHostPwd[PPP_MAXUSERPWDLEN + 2];
                                    /*����*/
    UCHAR szResponse[CHAP_MAX_RESPONSE_LENGTH + 2];  
                                    /* �ͳ���Response �ַ���*/
    UCHAR ucPppChapInfoRev[4];     /*�����ֶ�*/


} PPPCHAPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _CHAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

