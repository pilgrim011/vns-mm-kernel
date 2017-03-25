/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_sh_var.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11  
 *        Author: liuhui
 *   Description: PPPoE Clientģ��Shell����ȫ�ֱ���������˵��
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE            NAME                DESCRIPTION
 *  2003-01-11      liuhui              Created file
 *  2005-09-15      t45114              Modify
 *  2006-03-30      liai                Adjust for D00660
 *  2006/04/21      liai                Adjust for D00865
 *  2006-05-13      l48923              Delete useless code
 *  
 ************************************************************************/

#ifndef  _POEC_SH_VAR_H_
#define  _POEC_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/*ȫ��PPPoE Client Discovery�׶ζ�ʱ��ID��������Session ��padi��padr����ʹ��*/
extern ULONG  g_ulPPPoEClientDisTimerID;

/*ȫ��IDLE Timer��ʱ��ʱ��ID */
extern ULONG  g_ulPPPoEClientIdleTimerID;

/*ȫ��PPPoE Clientģ��Session�ַ���*/
extern CHAR *g_PPPoESessionInfo[2];

/*ȫ��PPPoE Clientģ��Session ״̬�ַ���*/
extern CHAR *g_SessionState[]; 

extern CHAR g_cPppoeClientDebugBuf[];

extern CHAR *Inf_PPPOE_Client_En[];   /* Ӣ�İ�����Ϣ */

extern struct ComponentInfo m_PPPOE_CLIENT_CompInfo;  /* PPPOE�����Ϣ */

extern struct IIF_PPPOE_CLIENT_ComIntCFGVtbl   * g_pstPPPOEClientComCfgTable; /* PPPOE���ù����麯���� */
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl   * g_pstPPPOEClientComFunTable; /* PPPOE���ܺ������ */
extern struct IIF_PPPOE_CLIENT_ComIntSSAVtbl   * g_pstPPPOEClientComSsaTable; /* PPPOEϵͳ֧���麯���� */

extern APP_INIT_INFO_S g_stPPPoEClientAppInfo; 

#if __cplusplus
}
#endif

#endif

