


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_fun.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_PUB_C
/*lint +e767*/

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_AddressAllocateFailed
 ��������   : ����Ӧ��Ӧ��Ϣ��UE��Э����������
                            If no address is available, the server may choose to report the problem to
                            the system administrator. ��
                            �˴�Э��DHCPЭ��
                            ��RFC2131�й涨��Ҫ����ICMP ECHO��Ϣ��
                            ���ǵ��豸�Լ���֤��ַ�����������
                            ����Ҫ���ʹ���Ϣ����
                            ״̬��RequestIP -> IDEL��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateFailed(
          DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_Deactive
 ��������   : USM���͵�ȥ����Ϣ��
                           DHCPSģ��ɾ����ַ��Լ��Ϣ��
                           ÿ��ȥ���û�������DHCP��
                           ����֪ͨUSM��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_Deactive(  DHCPS_PRE_RESULT_S *pstPreResult,
                                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_USMTimerOut
 ��������   : ����Ӧ��Ӧ��Ϣ��UE��Э����������
                            If no address is available, the server may choose to report the problem
                            to the system administrator. ��
                            �˴�Э��DHCPЭ��
                            ��RFC2131�й涨��Ҫ����ICMP ECHO��Ϣ��
                            ���ǵ��豸�Լ���֤��ַ�����������
                            ����Ҫ���ʹ���Ϣ��
                            ״̬�л���idel��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_USMTimerOut(
          DHCPS_PRE_RESULT_S *pstPreResult,DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                        DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_Deactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ClientTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveInform(DHCPS_PRE_RESULT_S *pstPreResult,
                                       DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDeactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_LeaseTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_RELAY_ReceiveRelease
 ��������   :    �յ���UE������DHCP Release��Ϣ��
                 ת����PGW��
                 ͬʱ֪ͨUSM�ͷţ�
                 Ȼ��ɾ�����ƿ�
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveRelease(
              DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_RELAY_ReceiveDecline
 ��������   :    �յ���UE������DHCP Decline��Ϣ��
                 ת����PGW��
                 ͬʱ֪ͨUSM�ͷţ�
                 Ȼ��ɾ�����ƿ�
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��29��
    ��    ��       : zhangyang 00142225
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_RELAY_ReceiveRelease
 ��������   :    �յ�USM��ȥ����Ϣ��ɾ�����ƿ�
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveDeactive(
            DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_IDEL_ReceiveDiscover
 ��������   : ֪ͨUSM����IP��ַ����USM��ʱ��1���еȴ���
                            ͬʱ����Լ���ƿ�ı�־λ���ɹ���״̬��
                            IDLE����>REQUESTIP��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                     DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��        : DHCPS_FSM_IDEL_ReceiveRequest
 ��������        : ֪ͨUSM����IP��ַ����USM��ʱ��1���еȴ���
                            ͬʱ����Լ���ƿ�ı�־λ���ɹ���״̬��
                            IDLE����>REQUESTIP��
 �������        : ��
 �������        : ��
 �� �� ֵ        : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���        :
 ��������        :

 �޸���ʷ        :
  1.��    ��     : 2013��04��25��
    ��    ��     : guolixian 00171003
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_IDEL_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                    DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��      : DHCPS_FSM_IDEL_ReceiveDiscover
 ��������   : �����Լ��Ϣ���ͷ���Դ
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveRelease(
                                                                             DHCPS_PRE_RESULT_S *pstPreResult,
                                                                             DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_ReceiveRelease
 ��������   : �յ�Release��Ϣ(��˵��Ӧ���յ���)��
                            ����Ӧ��Ӧ��Ϣ��UE  ��
                            ״̬�л���IDEL��
                            REQUESTIP-->IDLE��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_AddressAllocateSuccess
 ��������   : ����OFFER��Ϣ��SGW��
                           �����ȴ�Request��Ϣ�Ķ�ʱ��2��
                           ״̬��REQUESTIP����>OFFERED��
                           ���ر����ַ��¼��Ϣ��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateSuccess(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*=======================================================================
 *  ��������:  ICMPv6_CheckSum
 *  �������:  2004/07/30
 *  ��    ��:    ����
 *  ��������:  ����ICMPv6���ĵ�У���
 *                           ptr����ָ��ı��Ļᱻ���ǣ���ע����Ҫ���ȱ���
 *  �������:
 *  �������:  ��
 *  ��������:
 *  ȫ�ֱ���:
 *  ����˵��:  ��
 *  ���ú���:
 *  ��������:   IPV6_TimerOutProc
 *=======================================================================*/
USHORT ICMPv6_CheckSum(UCHAR *ptr, const in6_addr src, const in6_addr des, const UCHAR *msg,
                                                    USHORT usLen, USHORT *pusCheckSum, UCHAR ucPro)
{
    return VOS_OK;
}

ULONG UGW_GtpEncap( PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return 0;
}

/*****************************************************************************
 �� �� ��        : UGW_GRE_Encap
 ��������        :

 �������        : ��
 �������        : ��
 �� �� ֵ        : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���        :
 ��������        :

 �޸���ʷ        :
  1.��    ��     : 2009��08��12��
    ��    ��     : zhangyang 00142225
    �޸�����     : �����ɺ���

*****************************************************************************/
ULONG UGW_GRE_Encap(PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_CtxApiGetApnInfo
 ��������  : ��ȡapn��Ϣ
 �������  : ULONG ulPdpIdx
 �������  : AM_CTX_APN_INFO_S *pstApnInfo
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG AM_CtxApiGetApnInfo( ULONG ulPdnIndex, AM_CTX_APN_INFO_S *pstApnInfo)
{
    return VOS_OK;
}

VOID UGW_OmAccessMsgTrc(UCHAR *pMsg,
                      E_TRACE_TYPE enTraceType,
                      ULONG  ulMsgClass,
                      ULONG  ulGtpMsgType,
                      ULONG  ulPeerIpAddr,
                      USHORT usMsgLen)
{
    return;
}

VOID GTPC_OmExternInterfaceTrcProcess(UCHAR *pMsg, E_TRACE_TYPE enTraceType, UGW_EXTERN_INTF_TRACE_S stTraceInfo)
{
    return;
}

/*****************************************************************************
 �� �� ��  : AM_CtxApiGetReqApnIndexByPdpContext
 ��������  : AM�ṩ������ģ��ʹ�ã����������Ļ�ȡ����Ӧ�������apnindex
 �������  : ULONG ulPdpindex
             USHORT *pusRequestIndex
             UCHAR *pucAliaApnFlag
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��29��
    ��    ��   : p00114481
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID AM_CtxApiGetReqApnIndexByPdpContext(SDB_GSPU_CONTEXT_S *pstContext,USHORT *pusRequestIndex,UCHAR *pucAliaApnFlag)
{
    return;
}

/*****************************************************************************
 �� �� ��   : IPV6_SrcAddrValidationCheck
 ��������   : ipv6��ns��rs��dhcp��ԭ��ַ�Ϸ��Լ��
 �������   : USHORT usApnIndex
 �������   :
 �� �� ֵ   :

 ���ú���   :
 ��������   :

 �޸���ʷ   :
 1.��    �� : 2012��02��01��
   ��    �� : zhangjinquan
   �޸����� : ��������  DTS2012011006447 ipv6ģ�����Դ��ַ���ͼ��
*****************************************************************************/
ULONG IPV6_SrcAddrValidationCheck(IPV6HDR_S *pstIpv6Hdr)
{
    return VOS_OK;
}

PF_ULONG fwd_get_ctrlhdr_pdpindex(FWD_TO_CTRL_HDR* pstCtrlHdr)
{
    return pstCtrlHdr->ulPdpIndex;
}

/*****************************************************************************
 �� �� ��  : LAP_SetPrefixLengthIp
 ��������  : ����ǰ׺��������ǰ׺������Ĳ���Ϊ0���������������У�飬�ɵ��ú�����֤
 �������  : ULONG aulOldIp[], UCHAR ucPrefixLength
 �������  : ULONG aulNewIp[], UCHAR *pucPos, UCHAR *pucMoveBitNum
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : LAP1_GetIpv6Prefix

 �޸���ʷ      :
  1.��    ��   : 2012-08-01
    ��    ��   : zhangjinquan 00175135
    �޸�����   : �����ɺ��� zhangjinquan 00175135 IPv6 Prefix Delegation���� 2012-08-01

*****************************************************************************/
VOID LAP_SetPrefixLengthIp(ULONG aulOldIp[], UCHAR ucPrefixLength, ULONG aulNewIp[],
                            UCHAR *pucPos, UCHAR *pucMoveBitNum)
{
    return;
}

/*****************************************************************************
 �� �� ��  : PTM_DebugBatchSProcDebugCmdRspMsg
 ��������  : ptm����ִ������������ദ��ͻ�����Ӧ��Ϣ
 �������  : UCHAR *pucMsg
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��11��
    ��    ��   : y00138047
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PTM_DebugBatchSProcDebugCmdRspMsg(UCHAR *pucMsg)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CLAP_TaskInit
 ��������  : CLAP��ʼ�������� ����CLAP��������PDP�����ĵĵ�ַ�˲�
 �������  : VOS_UINT64 ullCsi
             ULONG ulHandle
 �������  : ��
 �� �� ֵ  : extern VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : mengyuanhui 00221593
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CLAP_TaskInit(VOS_UINT64 ullCsi, ULONG ulHandle)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_PreMsgFromUSM
 ��������   : Ԥ�����USM�յ�����Ϣ������:�����ַ�ɹ���
                            �����ַʧ�ܣ�ȡ���û���
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��5��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
VOID DHCPS_FSM_PreMsgFromUSM(UCHAR *pucRspMsg)
{
    return;
}

/*****************************************************************************
 �� �� ��  : CLAP_TaskConfirm
 ��������  : ����CLAP����,��Ҫ��Դ���룬�ص�ע�ᡢ��ʱ���ȣ�����PDP�����ĵĵ�ַ�˲�
 �������  : ULONG ulTaskID
 �������  : ��
 �� �� ֵ  : extern ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : mengyuanhui 00221593
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG CLAP_TaskConfirm(ULONG ulTaskID)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CLAP_TaskProcess
 ��������  : CLAP����Ϣ������������PDP�����ĵĵ�ַ�˲�
 �������  : VOID
 �������  : ��
 �� �� ֵ  : extern VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : mengyuanhui 00221593
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID CLAP_TaskProcess()
{
    return;
}

/*****************************************************************************
 �� �� ��  : Path_GetVpn
 ��������  : ���ݵ�ַ��ȡ�߼��ӿڰ󶨵�vpn����
 �������  : SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : jixiaoming 00180244
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID Path_GetVpn(SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId)
{
    return;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


