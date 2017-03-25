/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_var.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Clientģ��Core����˽��ȫ�ֱ���������˵��
 *                      �����κεط������ٳ��ֶ�˽��ȫ�ֱ�����extern����
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2003-01-11      liuhui          Create file
 *  2005-09-15      t45114          Modify  
 *  2006-03-30      liai            Adjust for D00660
 *  2006/04/21      liai            Adjust for D00865
 *   
 ************************************************************************/

#ifndef  _POEC_VAR_H_
#define  _POEC_VAR_H_

#if __cplusplus
extern "C"{
#endif


/* ȫ��PPPoE Client CB˫������ͷ�ӵ� */
extern DLL_S  g_stPPPoEClientCB;

/* ȫ��PPPoE Session�������飬�±�Ϊdialer bundle���룬����Ϊ��Ӧ��Session���ƿ�ָ�� */
extern UINTPTR  g_ulPPPoESessionIndexArray[MAX_BUNDLENUMBER + 1];

/* ȫ��BundleNumber���� */
extern ULONG g_ulDialerBundleNumber[MAX_BUNDLENUMBER + 1];

/* ȫ��PPPoE Clientģ����Կ��� */
extern ULONG g_ulPoeClientDebugFlag;

/* POEC����ģʽ */
extern ULONG g_ulCurrentPOECGRState;

/* ȫ����̫���ܺ���ָ�� */
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  *g_pstEthernetComFunTable;

/* ȫ��PPP���ܺ���ָ�� */
extern struct IIF_COMP_PPP_ComIntFUNVtbl  *g_pstPoecPppComFunTable;

/* SAPRO module info & shell SSP API */
extern PPPOE_CLIENT_MOD_INFO_S        g_stPPPOEClientModInfo;
extern PPPOE_CLIENT_SHELL_CALLBACK_S  g_stPPPOEClientShellApi;

extern POEC_PHASE_NOTIFY g_pfPoecPhaseNotifyHook;

/* ����Dialer�ӿڵĵ��Կ��� */
extern ULONG g_aulPoecDialerDebugFlag[MAX_BUNDLENUMBER + 1];

#if __cplusplus
}
#endif

#endif 


