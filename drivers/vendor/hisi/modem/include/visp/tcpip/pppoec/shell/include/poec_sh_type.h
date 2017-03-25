/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                          poec_sh_type.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Clientģ��Shell�������ݽṹ����
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME               DESCRIPTION
 *  2003-01-11      liuhui             Create file
 *  2005-09-15      t45114             Modify 
 *  2006-03-30      liai               Adjust for D00660
 *  2006/04/21      liai               Adjust for D00865
 *  2006-05-10   luyao(60000758)       Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
 *   
 ************************************************************************/

#ifndef  _POEC_SH_TYPE_H_
#define  _POEC_SH_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif



/*�Ȳ��ʱ�����·���ȫ������*/
typedef struct tagPoeClientHotInsertSlotMsg
{
    ULONG ulMsgType;        /*�Ȳ�ε���Ϣ����*/

}POE_CLIENT_HOT_INSERT_SLOT_MSG_S ; 


typedef struct tagPPPOE_CLIENT_RPC_RPL_DISPLAY
{
    UINTPTR  ulWaitListHandle;
    CHAR   szBuffer[PPPOE_CLIENT_DISPLAY_INFO_BLOCK_LEN + 1];  /* ����һ��'\0'������ */
    UCHAR  ucPadding[3]; 
}PPPOE_CLIENT_RPC_RPL_DISPLAY_S;

typedef PPPOE_CLIENT_RPC_RPL_DISPLAY_S PPPOE_CLIENT_DISPLAY_BLOCK_S;

typedef struct tagPPPOE_CLIENT_WAITLIST_PARAM
{
    UINTPTR ulHandle;            /* WAITLIST��� */
    UCHAR   ucGetNextType;        /* �������� */
    UCHAR   ucPadding[3];
    VOID    *pNode;                /* ������� */
}PPPOE_CLIENT_WAITLIST_PARAM_S;

typedef struct tagPPPOE_CLIENT_RPC_ENQ_DISPLAY
{
    UCHAR   ucRpcFunc;          /* RPC����ID */
    UCHAR   ucDisplayType;      /* Display���ͣ�PPPOE_CLIENT_DISPLAY_TYPE_EN */
    UCHAR   ucPadding[2]; 
    UINTPTR ulWaitListHandle;   /* WaitList��� */
    ULONG   ulBundleNumber;     /* �ӿ�IFNET���� */    
    ULONG   ulExecID;           /* EXEC�û�ID  */
    ULONG   ulLanguage;         /* ��ǰ���� */
}PPPOE_CLIENT_RPC_ENQ_DISPLAY_S;

typedef struct tagPPPOE_CLIENT_RPC_ENQ
{
    UCHAR   ucRpcFunc;          /* RPC����ID */
    UCHAR   ucPadding[3];
    ULONG   ulData;             /* �����ε�ʹ�������� */
}PPPOE_CLIENT_RPC_ENQ_S;


typedef struct tagPPPOE_CLIENT_RPC_RPL
{
    ULONG   ulData;             /* �û��Զ������� */
}PPPOE_CLIENT_RPC_RPL_S;

typedef enum tagPPPOE_CLIENT_RPC_FUNC
{
    PPPOE_CLIENT_RPC_GET_DISPLAY_INFO = 1,  /* ȡ��display��ʾ��Ϣ */
    PPPOE_CLIENT_RPC_USER_BREAK_NOTIFY,     /* �û��ж���ʾʱ֪ͨ�ӿڰ��ͷ�waitlist */
    PPPOE_CLIENT_RPC_HOT_PLUG_NOTIFY,       /* �Ȳ��ʱ֪ͨ�ӿڰ�ָ��������� */
    PPPOE_CLIENT_RPC_CLEAR_INFO
}PPPOE_CLIENT_RPC_FUNC_E;


#ifdef __cplusplus
}
#endif

#endif


