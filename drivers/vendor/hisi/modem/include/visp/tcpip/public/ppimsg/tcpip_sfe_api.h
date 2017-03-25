/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_api.h
*
*  Project Code: VISPV100R008C02
*   Module Name: 
*  Date Created: 2009-8-20
*        Author: zhangchunyu(62474)
*   Description: �����浽������API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-20  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _TCPIP_SFE_API_H_
#define _TCPIP_SFE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/ppimsg/tcpip_sfe_share_api.h"
#include "tcpip/bfd/include/bfd_cbb_api.h"

typedef UINT32 (*g_pfSendMsgToSFE)(VOID * pMsg, UINT32 u32Len);
typedef UINT32 (*g_pfRecvMsgFromSFE)(VOID *pMsgBuf, UINT32 *u32Len);
typedef VOID * (*g_pfAllocMsg)(UINT32 ulLength);
typedef UINT32 (*g_pfFreeMsg)(VOID *pMsg);

typedef UINT32 (*PF_FILTER_ROUTE4)(PPI_RTMSG4_S *pstPpiRoute);

/*******************************************************************************
*    Func Name: TCPIP_RegRecvMsgFromSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ��Ʒע�������������������ݽӿ�
*        Input: g_pfRecvMsgFromSFE *pfFunc:  ע�ắ�� 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegRecvMsgFromSFE(g_pfRecvMsgFromSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegSendMsgToSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ��Ʒע������浽�����淢�ͽӿ�
*        Input: g_pfSendMsgToSFE *pfFunc: ע�ắ�� 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegSendMsgToSFE(g_pfSendMsgToSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegFreeMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: �ͷ�������������ڴ�
*        Input: g_pfFreeMsg pfFunc: �ص�����
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFreeMsg(g_pfFreeMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegAllocMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ע�����������浽�������ڴ�
*        Input: g_pfAllocMsg pfFunc: 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegAllocMsg(g_pfAllocMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFilterFib4
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: ·�ɹ��˻ص��ӿ�
*        Input: PF_FILTER_ROUTE4 pfFunc: ע��ص�����
*       Output: pfFunc�������ؽ��:1��ʾ���·�,0��ʾ�·�
*       Return: TCPIP_RT_SUCCESS:�ɹ� ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFilterFib4(PF_FILTER_ROUTE4 pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RecvEvent
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: �����������������Ϣ�ַ�����
*        Input: VOID *pMsg: ��Ϣ
*               UINT32 u32MsgLen:��Ϣ���� 
*       Output: 
*       Return: �ɹ�:TCPIP_SFE_COM_SUCCESS ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RecvEvent(VOID *pMsg, UINT32 u32MsgLen);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperARP
* Date Created: 2009-8-20
*       Author: w60786
*  Description: ARP�����������Ӧ�Ŀ�����
*        Input: UINT32 u32OperType: ARP��������
*               TCPIP_SFE_ARP_S *pstArp: ARP���ò���
*       Output: 
*       Return: 
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20  w60786         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperARP(UINT32 u32OperType, TCPIP_SFE_ARP_S *pstArp);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperFIB4
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: �û����ò���·�ɽӿ�
*        Input: ULONG ulOperType: ��������
*               TCPIP_SFE_ROUTE_S *pstRtMsg: ·����Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_RT_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperFIB4(UINT32 u32OperType, TCPIP_SFE_ROUTE_S *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperIf
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: ����API��ͳһ�ɲ�Ʒ���ã����нӿڵ����ø��µȲ���
*        Input: UINT32 u32OperType:������,�μ�tcpip_pub_api.h�ļ���tagPPIOprType
*               TCPIP_SFE_INTF_S *pstIntfInfo: �ӿ���Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperIf(UINT32 u32OperType,TCPIP_SFE_INTF_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_FIB4_Update
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ������PPI�·��ӿ�
*        Input: UINT32 ulOprType: PPI����
*               PPI_RTMSG4_S *pstPpiRoute:��Ϣ�ṹ 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_RT_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_FIB4_Update(UINT32 u32OprType, PPI_RTMSG4_S *pstPpiRoute);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_ARP_Update
* Date Created: 2009-8-21
*       Author: w60786
*  Description: ARPģ�鴦�������PPI�·������ֵĺ���
*        Input: UINT32 u32OperType: ARP��������
*               PPI_ARP_S *pstArpMsg: ARP ������PPI�·�����
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_ARP_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-21    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32  TCPIP_SFE_PPI_ARP_Update(UINT32 u32OperType, PPI_ARP_S *pstArpMsg);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_IF_Update
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: IFNET��PPIע��ӿ�,�������ʼ��ǰ�����TCPIP_PPI_HookRegister�ӿڽ���ע��
*        Input: UINT32 u32IfIndex:�ӿ�����
*               UINT32 u32Cmd:PPI����
*               VOID *pData:
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_IF_Update(UINT32 u32IfIndex, UINT32 u32Cmd, VOID *pData);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_VRF_Update
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: Vrf��PPIע��ӿ�,�������ʼ��ǰ�����TCPIP_PPI_HookRegister�ӿڽ���ע��
*        Input: UINT32 u32Cmd:������
*               VRF_PPI_S *pstVrfPpi:Vrf��Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_VRF_Update(UINT32 u32Cmd, VRF_PPI_S *pstVrfPpi);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_BFD4_Update
* Date Created: 2009-9-3
*       Author: w60786
*  Description: BFDģ�鴦�������PPI�·������ֵĺ���
*        Input: UINT32 u32OperType: PPI ������
*               UINT32 u32SessionID: �ỰID
*               BFD_PPI_S *pstBfdPpiInfo: IPV4 BFD�Ự��Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_BFD_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-3     w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_BFD4_Update(UINT32 u32OperType, UINT32 u32SessionID, BFD_PPI_S *pstBfdPpiInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFIBInfo
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: ��ȡָ��VRF��ָ��IP��Ӧ��·�ɱ�����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32IpAddr: ��ַ(������)
*               TCPIP_SFE_ROUTE_S *pstRouteInfo: ��ȡ��·����Ϣ
*       Output: *pstRouteInfo: ��ȡ��·����Ϣ
*       Return: TCPIP_SFE_COM_SUCCESS:�ɹ� ����:ʧ��
*      Caution: �ú�����������ֻ�ܻ�ȡһ��·����Ϣ,�����ƽ��·��,�������ȡһ��ƽ��·��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFIBInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ROUTE_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetArpInfo
* Date Created: 2009-8-28
*       Author: w60786
*  Description: ��ȡָ��VRF��ָ��IP��Ӧ��ARP������Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32IpAddr: ��ַ(������)
*               TCPIP_SFE_ARP_S *pstArp: ��ȡ��ARP��Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_ARP_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-28    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetArpInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ARP_S *pstArp);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetIfInfoByID
* Date Created: 2009-8-28
*       Author: w60786
*  Description: ��ȡָ���ӿ�ID����Ϣ
*        Input: TCPIP_SFE_IFID *pstIntfID: �ӿ�ID
*               TCPIP_SFE_INTF_S *pstIntfInfo: �ӿ���Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-28    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetIfInfoByID(TCPIP_SFE_IFID *pstIntfID,TCPIP_SFE_INTF_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetBfdSessionInfo
* Date Created: 2009-9-15
*       Author: w60786/h00121208
*  Description: ��ȡָ��VRF��ָ���ỰID��Ӧ��BFD�Ự��Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: BFD�ỰID
*       Output: TCPIP_SFE_BFD_SESS_INFO_S *pstBfdSessInfo: ��ȡ��BFD�Ự��Ϣ
*       Return: �ɹ�: TCPIP_SFE_BFD_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-15    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetBfdSessionInfo(UINT32 u32VrfIndex, UINT32 u32SessionId,
                                                    TCPIP_SFE_BFD_SESS_INFO_S *pstBfdSessInfo);
                                             
/*******************************************************************************
*    Func Name: TCPIP_SFE_OpenTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: ��ָ�������ݱ�
*        Input: UINT32  u32TableType: ���ݱ�, ȡֵ��enumTableType
*               UINT32  u32VrfIndex:  VRFʵ����
*       Output: UINT32 *pu32Handle:   ���ݱ�������, ����get��close
*       Return: TCPIP_SFE_TABLE_SUCCESS �ɹ� / ���� ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OpenTable(UINT32 u32TableType, UINT32 u32VrfIndex, UINT32 *pu32Handle);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetTableData
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: 
*        Input: UINT32  u32Handle:  ���ݱ�������, openʱ���
*               UINT32 *pu32GetNum: �����ȡ�ı������
*               UINT32 *pu32BufLen: ���������� 
*       Output: 
*               UINT32 *pu32GetNum: ʵ�ʻ�ȡ�ı������
*               UINT8  *pu8Buf:     ��������ַ
*               UINT32 *pu32BufLen: ʵ�ʿ����ĳ��� 
*       Return: TCPIP_SFE_TABLE_SUCCESS: �ɹ�
*               TCPIP_SFE_TABLE_GET_OVER: ��ȡ�������
*               ����: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetTableData(UINT32  u32Handle,
                              UINT32 *pu32GetNum,
                              UINT8  *pu8Buf,
                              UINT32 *pu32BufLen);

/*******************************************************************************
*    Func Name: TCPIP_SFE_CloseTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: �ر�ָ�������ݱ�
*        Input: UINT32 u32Handle: ���ݱ�������, openʱ���
*       Output: 
*       Return: TCPIP_SFE_TABLE_SUCCESS �ɹ� / ���� ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_CloseTable(UINT32 u32Handle);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetSendIcmpErrSwitch
* Date Created: 2009-08-21
*       Author: z62474/z62531
*  Description: ���÷���ICMP����ĵĿ���
*        Input: u32Switch:���Կ���
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_ICMP_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   z62474/z62531           Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetSendIcmpErrSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetSendIcmpErrSwitch
* Date Created: 2009-9-12
*       Author: z62474/z62531
*  Description: ��ȡICMP���Կ���
*        Input: UINT32 *pu32Switch: �������,��ȡֵ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_ICMP_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-12    z62474/z62531     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetSendIcmpErrSwitch(UINT32 *pu32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_IF_SetEthArpMissSwitch
* Date Created: 2009-9-16
*       Author: w60786/h00121208
*  Description: ������̫�ӿ��Ƿ���Ҫ����ARP MISS������
*        Input: TCPIP_SFE_IFID *pstIfId: ��̫�ӿ�ID
*               UINT32 u32Switch: ARP MISS������ֵ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-16    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_IF_SetEthArpMissSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_IF_SetReduceTTLSwitch
* Date Created: 2009-9-16
*       Author: w60786/h00121208
*  Description: ���ýӿ��Ƿ���Ҫ�ݼ�TTL����
*        Input: TCPIP_SFE_IFID *pstIfId: �ӿ�ID
*               UINT32 u32Switch: TTL�Ƿ�ݼ�����ֵ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_IF_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-16    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_IF_SetReduceTTLSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetSrcIpAddr
* Date Created: 2009-10-16
*       Author: z62474/z62531
*  Description: �ڿ��������������淢�ͱ���ʱ������Ҫ��ԴIP
*        Input: u32VrfIndex:ʵ����
*               u32SrcIpAddr:IP Addr,������
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_ICMP_OK
*               ʧ��: ������
*      Caution: Ŀǰ������ӿ�û��ά����ַ,�ڷ��ͱ��ĵ�ʱ��,
*               �����û�����VRF�µ�IP��䱨�ĵ�ԴIP
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62474/z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetSrcIpAddr(UINT32 u32VrfIndex, UINT32 u32SrcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetSrcIpAddr
* Date Created: 2009-10-16
*       Author: z62474/z62531
*  Description: �ڿ������ȡԴIP
*        Input: u32VrfIndex:ʵ����
*       Output: pu32SrcIpAddr:�������, ��ȡ����Src IP
*       Return: �ɹ�: TCPIP_SFE_IP_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62474/z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetSrcIpAddr(UINT32 u32VrfIndex, UINT32 *pu32SrcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_BFD_SetDebugSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: ����BFD�Ự���õ��Կ���
*        Input: UINT32 u32VrfIndex:VRF����
*               UINT32 u32SessionId:�ỰID
*               UINT32 u32IsDebug:�Ƿ���ԣ�1�򿪵��Կ���,0�رյ��Կ���
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_BFD_OK
*               ʧ��: ������
*      Caution: �ỰIDΪ0ʱ��ʾ�����лỰ�ĵ��Կ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531                   Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_BFD_SetDebugSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 u32IsDebug);

/*******************************************************************************
*    Func Name: TCPIP_SFE_BFD_GetDebugSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: ����BFD�Ự��ȡ���Կ���
*        Input: UINT32 u32VrfIndex:VRF����
*               UINT32 u32SessionId:�ỰID
*       Output: UINT32 *pu32IsDebug:�Ƿ���ԣ�1�򿪵��Կ���,0�رյ��Կ���
*       Return: �ɹ�: TCPIP_SFE_BFD_OK
*               ʧ��: ������
*      Caution: �ỰIDΪ0ʱ��ʾ��ȡ�Ƿ������BFD�Ự�ĵ��Կ���,1Ϊ��,0Ϊ�ر�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531                   Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_BFD_GetDebugSwitch(UINT32 u32VrfIndex, 
                                                UINT32 u32SessionId, UINT32 *pu32IsDebug);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetDebugTypeSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: ���õ������Ϳ���
*        Input: UINT32 u32DebugTypeSwitch: λ�������Ϳ���ֵ
*       Output: pu32SrcIpAddr:�������, ��ȡ����Src IP
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: ��������:,��ǰ��֧��SFE_DEBUG_TYPE_PROC
*               #define SFE_DEBUG_TYPE_ERROR        0x0001
*               #define SFE_DEBUG_TYPE_INOUT        0x0002  
*               #define SFE_DEBUG_TYPE_PROC         0x0004
*               #define SFE_DEBUG_TYPE_VERBOSE      0x0008
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugTypeSwitch(UINT32 u32DebugTypeSwitch);

/*******************************************************************************
*    Func Name: SFE_SetDebugVcpuSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ���õ���VCPU����
*        Input: UINT32 u32DebugVcpuSwitch: λ����VCPU����ֵ
*       Output: 
*       Return: �ɹ�: SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                        Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetDebugModuleSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ���õ���ģ�鿪��
*        Input: UINT32 u32DebugModuleSwitch: λ����ģ�鿪��ֵ
*               SFE_DEBUG_MODULE_IPFWD     0x00000001
*               SFE_DEBUG_MODULE_ICMP      0x00000002
*               SFE_DEBUG_MODULE_BFD       0x00000004
*               SFE_DEBUG_MODULE_ALL       (SFE_DEBUG_MODULE_IPFWD | SFE_DEBUG_MODULE_ICMP | SFE_DEBUG_MODULE_BFD)
*       Output: 
*       Return: �ɹ�: SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: Ϊ������չ,���޶�u32DebugModuleSwitch�Ĵ�С
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                        Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetDebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ��ȡ���ֵ��Կ���
*        Input: 
*       Output: UINT32* pu32DebugTypeSwitch: �������Ϳ���
*               UINT32* pu32DebugVcpuSwitch: ����VPU����
*               UINT32* pu32DebugModuleSwitch: ����ģ�鿪��
*       Return: �ɹ�: SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                       Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
                                                UINT32* pu32DebugVcpuSwitch, 
                                                UINT32* pu32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowDebugSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ��������ֵ��Կ�����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowDebugSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ������������Ϣ���¼����Կ���,1Ϊ��,0Ϊ�ر�
*        Input: UINT32 u32DebugSwitch:���Կ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetMsgOrEvent_DebugSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: SFE_GetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ��ȡ��Ϣ���¼����Կ���,1Ϊ��,0Ϊ�ر�
*        Input: 
*       Output: UINT32 *pu32CtlDbgSwitch:������ĵ��Կ���
*               UINT32 *pu32SfeDbgSwitch:ת����ĵ��Կ���
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetMsgOrEvent_DebugSwitch(UINT32 *pu32CtlDbgSwitch,
                                           UINT32 *pu32SfeDbgSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ������ϸ���Ա��ĵĴ����ͳ���
*        Input: UINT32 u32PktNum:���Ĵ���
*               UINT32 u32Length:���Ա��ĵĳ���
*       Output: 
*       Return: VOID
*      Caution: u32PktNumΪ0��ʾ����ӡ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetVerboseDebug_CntAndLen(UINT32 u32PktNum, UINT32 u32Length);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*  Description: ��ȡ��ϸ���Ա��ĵĴ����ͳ���
*        Input: 
*       Output: UINT32 *pu32PktNum:���Ĵ���
*               UINT32 *pu32Length:���Ա��ĵĳ���
*       Return: VOID
*      Caution: u32PktNumΪ0ʱ��ʾ�����Ƶ��Ա��ĵĸ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetVerboseDebug_CntAndLen(UINT32 *pu32PktNum, UINT32 *pu32Length);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetAllStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ȡ������ȫ��ͳ����Ϣ
*        Input: 
*       Output: SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo: ȫ���ֶ�ͳ����Ϣ(��VCPUͳ��֮��),
*                   �û��ṩ�ռ�.
*               UINT32 pu32StaisticAutoInfo[SFE_STAT_IPFWD_MAX]: ȫ���Զ�ͳ����Ϣ,�û��ṩ�ռ�,
*               �û����뱣֤�ÿռ��㹻��,������SFE_STAT_IPFWD_MAX*sizeof(UINT32)�ֽڴ�.
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: �û����뱣֤�ṩ�Ĵ洢�ռ��㹻��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetAllStatistic(SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo,
                                        UINT32 pu32StaisticAutoInfo[SFE_STAT_IPFWD_MAX]);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetManualStatisticByVcpu
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ȡ������ָ��VCPU��ȫ���ֶ�ͳ����Ϣ
*        Input: UINT32 u32VcpuId: VCPU ID,ȡֵ��Χ[0, SFE_VCPU_MAX_NUM-1]
*       Output: SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo: ָ��VCPU��ȫ���ֶ�ͳ����Ϣ,�û��ṩ�ռ�
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: �û����뱣֤�ṩ�Ĵ洢�ռ��㹻��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetManualStatisticByVcpu(UINT32 u32VcpuId, SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾȫ��ͳ����Ϣ(ȫ���ֶ���VCPUͳ��֮��,�Լ�ȫ���Զ�ͳ����Ϣ)
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAutoStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾȫ���Զ�ͳ����Ϣ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAutoStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowManualStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾȫ���ֶ�ͳ����Ϣ(��VCPUͳ����Ϣ֮��)
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowManualStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowManualStatisticByVCPU
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾָ��VCPU��ȫ���ֶ�ͳ����Ϣ
*        Input: UINT32 u32VCPUID: 
*               ID���[0,SFE_VCPU_MAX_NUM��1]:��ʾ��ʾָ��VCPU��ŵ��ֶ�ͳ����Ϣ
*               SFE_VCPU_MAX_NUM(32):��ʾѭ����ʾ��VCPU���ֶ�ͳ����Ϣ
*               SFE_SHOW_TOTAL_MANUAL_STATISTIC(0xffffffff):��ʾ��ʾ��VCPU�ֶ�ͳ��ֵ֮��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowManualStatisticByVCPU(UINT32 u32VCPUID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ������������ͳ�ƿ���
*        Input: UINT32 u32FlowStatSwitch: ��ͳ�ƿ���ֵ
*               `   SFE_FLOWSTAT_SWITCH_ON:����ͳ�ƹ���
*                   SFE_FLOWSTAT_SWITCH_OFF:�ر���ͳ�ƹ���
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetFlowStatisticSwitch(UINT32 u32FlowStatSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ��ȡ��������ͳ�ƿ���
*        Input: 
*       Output: UINT32 *pu32FlowStatSwitch: ��ͳ�ƿ���,
*               `   SFE_FLOWSTAT_SWITCH_ON:��
*                   SFE_FLOWSTAT_SWITCH_OFF:�ر�
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticSwitch(UINT32 *pu32FlowStatSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ��ʾ��������ͳ�ƿ���
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ConfigFlowStatisticRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: �������������ͳ�ƹ���
*        Input: UINT32 u32OperType: ���ò�������,ȡֵ��μ�SFE_FLOWSTATISTIC_RULE_OPER_TYPE_E����
*               TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: ��ͳ�ƹ�����Ϣ,
*                   �����ò�������ΪSFE_FLOWSTATISTIC_DELALLʱ,�ò�����Ч,�ɴ���NULLָ��.
*                   �����������ò����ò��������NULL.
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ConfigFlowStatisticRule(UINT32 u32OperType, TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticRuleNum
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ��ȡ�����浱ǰ����ͳ�ƹ�����
*        Input: 
*       Output: UINT32 *pu32FlowStatisticRuleNum: ��ͳ�ƹ�����ָ��
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: �ɹ�ʱ�����Ϣ����Ч,�û��������жϷ���ֵ,��ʹ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticRuleNum(UINT32 *pu32FlowStatisticRuleNum);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ָ��������Ŀ��ȡ��ͳ�ƹ���
*        Input: pu32FlowRuleNum: ָ���û���Ҫ��ȡ����������,
*       Output: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: ��Ż�ȡ����ͳ�ƹ���
*                   �û�����Ŀռ��СҪ�㹻��,����������pstFlowRuleNum����ֵ����
*                   TCPIP_SFE_FLOWSTATISTIC_RULE_S�ṹ��С�Ŀռ䡣
*               UINT32 *pstFlowRuleNum: ����ʱ,ָ���û���Ҫ��ȡ����������,
*                   ���ʱ,��ʾʵ�ʻ�ȡ����ͳ�ƹ�����,��ֵҲ����Ϊ0,��ʾ�����ڹ���û�л�ȡ��.
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: �ɹ�ʱ�����Ϣ����Ч,�û��������жϷ���ֵ,��ʹ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786                  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                               UINT32 *pu32FlowRuleNum);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticInfoByRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: ������ͳ�ƹ����ȡ��Ӧ��ͳ����Ϣ
*        Input: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: ��ͳ�ƹ���
*                  �����Э���TCP��UDP,�����ԴĿ�Ķ˿ںŲ���Ч,������Ч.
*                  ��ͳ��ID�ֶ���Ϊ�������.
*       Output: SFE_IPSFE_FLOWSTATISTIC_S *pstFlowStatisticManualInfo: ��Ӧ�����ֶ�ͳ����Ϣ
*               UINT32 pu32FlowStaisticAutoInfo[SFE_STAT_IPFWD_MAX]: ��Ӧ�����Զ�ͳ����Ϣ
*                     �û����뱣֤�ÿռ��㹻��,������SFE_STAT_IPFWD_MAX*sizeof(UINT32)�ֽڴ�.
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: pu32FlowStaisticAutoInfo������һ����СΪSFE_STAT_IPFWD_MAX��UINT32���͵�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786                  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticInfoByRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                                       SFE_IPSFE_FLOWSTATISTIC_S *pstFlowStatisticManualInfo,
                                                       UINT32 pu32FlowStaisticAutoInfo[SFE_STAT_IPFWD_MAX]);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFlowStatisticRule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ���������е���ͳ�ƹ���
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFlowStatisticRule(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticRuleByFlowId
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ָ����ID����ͳ�ƹ���
*        Input: UINT32 u32FlowId: ��IDֵ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticRuleByFlowId(UINT32 u32FlowId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFlowStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ���������е���ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFlowStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticByFlowRule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ָ�����������ͳ����Ϣ
*        Input: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: ָ������������Ϣ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticByFlowRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticByFlowId
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ָ����ID����ͳ����Ϣ
*        Input: UINT32 u32FlowId:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticByFlowId(UINT32 u32FlowId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetLogLevel
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ������������־���𿪹�
*        Input: UINT32 u32LogLevel: ��־����,ȡֵ��μ�SFE_LOG_LEVEL_Eö�ٶ���
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetLogLevel(UINT32 u32LogLevel);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetLogType
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ������־��¼���Ϳ���
*        Input: UINT32 ul32WarningLogEnable: �澯��־��¼����,ȡֵ:0:�ر� 1:��
*               UINT32 u32CfgLogEnable: ������־��¼����,ȡֵ:0:�ر� 1:��
*               UINT32 u32RunLogEnable: ������־��¼����,ȡֵ:0:�ر� 1:��
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetLogType(UINT32 ul32WarningLogEnable, UINT32 u32CfgLogEnable, UINT32 u32RunLogEnable);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowLogSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ��������־������Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowLogSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowVersion
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������汾����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_PreConfigPara
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������Ԥ������Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_PreConfigPara(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_ShareMemoryID
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ʹ�õĸ����͹����ڴ�ID
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_ShareMemoryID(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_StubDeleteModule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ģ��ü����
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_StubDeleteModule(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ����ACL�����Ƿ���Ҫ��������м����鿪����֧�־�ȷƥ�书��
*        Input: UINT32 u32Switch: ����,
*               ȡֵ: SFE_ACL_NEED_FAKEREASS_SWITCH_ON: ACL������Ҫ��������м����鴦��
*                     SFE_ACL_NEED_FAKEREASS_SWITCH_OFF: ACL������Ҫ��������м����鴦��
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_PUB_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetAclNeedFakeReassSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ȡACL�����Ƿ���Ҫ��������м����鿪����֧�־�ȷƥ�书��
*        Input: 
*       Output: UINT32 *pu32Switch: ����ֵ,ȡֵ������μ�TCPIP_SFE_SetAclNeedFakeReassSwitch�ӿ�˵��
*       Return: �ɹ�: TCPIP_SFE_PUB_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetAclNeedFakeReassSwitch(UINT32 *pu32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾACL�����Ƿ���Ҫ��������м����鿪����֧�־�ȷƥ�书��
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAclNeedFakeReassSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_Show_MsgSeq
* Date Created: 2009-10-26
*       Author: maqinggao(00116466)
*  Description: ��ʾ������ͨ����Ϣ���к�
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-26   maqinggao(00116466)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_Show_MsgSeq(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_MsgSeq
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ��ʾ������ͨ����Ϣ���к�
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_MsgSeq(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OutputToCOMSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: ������ά����Ϣcom���������,�ýӿڲ��Ƕ���API�ӿ�,ֻ������ά�����
*        Input: UINT32 u32Switch: ����,ȡֵ��μ�SFE_OUTPUT_FIX_LOG�Ⱥ궨��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_OutputToCOMSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearAllStatistic
* Date Created: 2009-11-6
*       Author: w60786
*  Description: �������������ȫ��ͳ����Ϣ(�ýӿڲ��Ƕ���API�ӿ�,ֻ�����ڲ�ά�����,
*               ����ͳ����Ϣ�Ƕ�˲���,���Ըýӿڲ������ܲ�̫׼ȷ),
*        Input: VOID
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-6    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearAllStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearAllFlowStatistic
* Date Created: 2009-11-6
*       Author: w60786
*  Description: ���������������ͳ����Ϣ(�ýӿڲ��Ƕ���API�ӿ�,ֻ�����ڲ�ά�����,
*               ����ͳ����Ϣ�Ƕ�˲���,���Ըýӿڲ������ܲ�̫׼ȷ),
*        Input: VOID
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_DEBUG_OK
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-6    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearAllFlowStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllArpInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾ����ARP����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllArpInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowArpInfoByVrf
* Date Created: 2009-8-6
*       Author: m00116466
*  Description: ��ʾָ��VRF�µ�����ARP����
*        Input: UINT32 u32VrfIndex: VRF����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-11     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowArpInfoByVrf(UINT32 u32VrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowOneArpInfo
* Date Created: 2009-8-6
*       Author: m00116466
*  Description: ��ʾָ����ĳ��ARP����
*        Input: UINT32 u32VrfIndex: VRF����
*               CHAR *pcIpAddr: ���ʮ������ʽ�ĵ�ַ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-6     w60786/luowentong         Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowOneArpInfo(UINT32 u32VrfIndex, CHAR *pcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllIfInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾ���нӿ���Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466               Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllIfInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowIfInfoByID
* Date Created: 2009-12-01
*       Author: maqinggao(00116466)
*  Description: ���ݽӿ�ID��ʾ�ӿ���Ϣ
*        Input: TCPIP_SFE_IFID *pstIfID:�ӿ�ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-01   maqinggao(00116466)  Create
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowIfInfoByID(TCPIP_SFE_IFID *pstIfID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllBfdInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾ����VRF�µ�BFD�Ự��Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllBfdInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdInfoByVrf
* Date Created: 2009-12-01
*       Author: m00116466
*  Description: ��ʾָ��VRF�µ�BFD�Ự��Ϣ 
*        Input: UINT32 u32VrfIndex: VRF����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-01     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdInfoByVrf(UINT32 u32VrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdInfoByID
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾָ��VRF SessionID�ĻỰ��Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*        Input: UINT32 u32SessionId:BFD�ỰID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdInfoByID(UINT32 u32VrfIndex, UINT32 u32SessionId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFibInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾ����·����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466               Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFibInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFibInfoByIP
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: ��ʾָ��VRF ĳ��IP��·����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*        Input: CHAR  *pi8IpAddr:  ���ʮ������ʽ�ĵ�ַ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFibInfoByIP(UINT32 u32VrfIndex, CHAR *pi8IpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��ȡָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*               SFE_BFD_SESS_STATISTIC_S *pstStat:�������, ͳ����Ϣ
*       Output: 
*       Return: �ɹ� TCPIP_SFE_COM_SUCCESS
*               ʧ�� ����������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId, SFE_BFD_SESS_STATISTIC_S *pstStat);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��0ָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*       Output: 
*       Return: �ɹ� TCPIP_SFE_COM_SUCCESS
*               ʧ�� ����������
*      Caution: �������Ƕ��,���ڶ��ͬʱ��д����ֶ�,��������0��,��������ֶο��ܲ���0�ĸ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��ʾָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*       Output: ��ʾ�Ự��Ϣ
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


#ifdef  __cplusplus
}
#endif
#endif

