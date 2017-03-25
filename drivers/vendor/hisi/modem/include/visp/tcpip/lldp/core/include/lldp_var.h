/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_var.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: ��������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_VAR_H_
#define _LLDP_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern LLDP_LOCAL_SYS_INFO_S    g_stLldpLocalSystemData;    /*�����豸ϵͳ��Ϣ*/
extern LLDP_LOCAL_SYS_STAT_S g_stLldpLocalSysStat;     /*ϵͳͳ����Ϣ*/
extern LLDP_LOCAL_PORT_S **g_stLldpLocalPortArray;       /*���ض˿ڱ�������LLDP_LOCAL_PORT_S*/
extern ULONG g_ulLldpLocalPortNum;      /*���ض˿�����*/
extern BOOL_T g_bLLDP_ShellInit;   /*LLDP�Ƿ��ʼ���ɹ�*/

/*Added by guo00178934, ϵͳ����ھ���, 2011/11/8   ���ⵥ��:DTS2011110104340 */
extern ULONG  g_ulLldpRemmTotal;             /*ϵͳ�ھ�����*/
/* End of Added by guo00178934, 2011/11/8   ���ⵥ��:DTS2011110104340 */


/* Global semaphore for LLDP */
extern ULONG g_ulSemForLldp ;

/*LLDPRUN���������ID����Ϣ����ID*/
extern ULONG ulLLDPTaskID;


extern ULONG txFastInit;
extern ULONG reinitDelay;
extern ULONG msgTxInterval;

extern ULONG g_ulLLDPControlQueID;
extern ULONG g_ulLLDPTimerQueID;
extern ULONG g_ulLLDPRcvQueID;
extern ULONG g_ulLLDPTransmitTimerQueID;

extern ULONG g_ulLLDPDebugSwitch;
extern ULONG g_ulLLDPDebugIfIndexFilter;
extern ULONG g_ulLLDPDebugMACTypeFilter;
extern ULONG g_ulLLDPRemIndex;

extern ULONG g_ulLLDPSendPktFilter;
extern ULONG g_ulLLDPReceivePktFilter;

/*Added by limin00188004, ���ӱ��ķ���ʱѡ��802.1��802.3Э��涨��Link Aggregation TLV, 2011/11/4   ���ⵥ��:DTS2011110806987 */
extern ULONG g_ulLLDPLinkAggrTlvSwitch;    /*ֵΪ0, ѡ����802.1�еĹ涨; ֵ����0��ѡ����802.3�еĹ涨��*/
/* End of Added by limin00188004, 2011/11/4   ���ⵥ��:DTS2011110806987 */

/*Added by zhangliangzhi00187023, �����ӷ������⡿��Ҫ֧���·��鲥��ַ���˹���, 2012/8/29   ���ⵥ��:DTS2012082907401 */
extern UCHAR g_lldp_szEthDMA[LLDP_MAX_MACTYPE_SIZE][LLDP_MAC_ADDR_LEN] ;
/* End of Added by zhangliangzhi00187023, 2012/8/29   ���ⵥ��:DTS2012082907401 */

/*Added by luogaowei, �ϱ��澯Я�����ھ���Ϣ, 2013/3/30, DTS2013040700481 */
extern LLDP_REM_INFO_S  *g_pstLLDPWarningRemInfo;

/*added by w00217009,LLDP�˿���ӷ�ʽ��Ĭ��0��visp�����ӿ�ʱ������ӣ�Ϊ1���ɲ�Ʒ����api�������,DTS2013060608306*/
extern ULONG g_ulLLDPAddPortMode;

extern LLDP_GETEXTTLV_HOOK_FUNC g_stLLDPGetExtTlv;

extern LLDP_INPUT_HOOK_FUNC g_stLLDPInputHook;

/* Global value for storing LLDP maximum supported interface*/
extern ULONG g_ulLldpMaxLocalPortNum;

/* Global value for storing LLDP maximum neighbour interface*/
extern ULONG g_ulLldpMaxNbrNum;

#ifdef  __cplusplus
}
#endif

#endif
