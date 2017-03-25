/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pap_type.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��PAP�ṹ�嶨��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_PAP == VRP_YES )

#ifndef      _PAPC_TYPE_H_
#define      _PAPC_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* PAP ���ƿ����ݽṹ����*/
typedef struct tagPppPapInfo
{
    PPPINFO_S *pstPppInfo;/* PPP ���ƿ�ָ��*/
    VOID* pstAAAAuthReqMsg;
    HTIMER ulServerTimeoutID;         /* Server ��ʱ��ʱ�� ID */
    HTIMER ulClientTimeoutID;	/* Client ��ʱ��ʱ�� ID*/

    VOS_UINT32 ulWaitReqTimeout;/* �ȴ��Զ���֤��ʱʱ�� */
    VOS_UINT32 ulWaitLnsAuthTimeOut;
    VOS_UINT32 ulSendReqTimeout;/* ��֤����ʱ�ش�ʱ�� */
    VOS_UINT32 ulMaxTransmits;/* ��֤��������ʹ��� */
    VOS_UINT32 ulWaitAuthRspTimeout;             /* �ȴ�AAA��Ȩ��Ӧ��ʱʱ�� */
    VOS_UINT32 ulAuthMaxTransmits;/* ��֤��������ʹ��� */

    VOS_UINT16 usAuthClientFailureTimes;	/* ������֤ʧ�ܴ���*/
    VOS_UINT16 usAuthServerFailureTimes;	/* Զ����֤ʧ�ܴ���*/
    UCHAR ucClientState;/* Client ״̬ */
    UCHAR ucServerState;/* Server ״̬ */
    UCHAR ucId;	/* ��ǰ������֤�������ID*/
    UCHAR ucAuthTransmits;	/* ������֤����Ĵ��� */




    UCHAR ucTransmits;	/* ������֤����Ĵ���*/
    UCHAR ucPeerId;/* ��ǰ�Զ���֤�����ID */
    UCHAR ucUsed;  /*pap���ƿ�ʹ�ñ�ǣ�1ʹ�ã�0δʹ��*/
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];/*�û���*/
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLEN + 2];/*�û�����*/
    UCHAR ucPppPapInfoRev;        /*�����ֶ�*/

}PPPPAPINFO_S;


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_PAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


