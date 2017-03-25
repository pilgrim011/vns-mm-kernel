/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib_sh_ha.h
*
*  Project Code:    VISPV1R6
*   Module Name:  SFIB Module   
*  Date Created:   2006-12-06
*        Author:        j51916
*   Description:      SFIB high availability function implement
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE                  NAME                     DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-06      j51916                  Creat the first version.
*
*
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _SFIB_SH_HA_H
#define _SFIB_SH_HA_H

#define SFIB_ADD_STATIC_BAK                1    /* ���Ӿ�̬·�ɵ� */
#define SFIB_BATCH_ITEM_BAK                2    /* ��������·���� */
#define SFIB_DEL_STATIC_BAK                3    /* ɾ����̬·����Ϣ */
#define SFIB_DISABLE_BY_NEXTHOP_BAK        4    /* ������һ��ȥʹ�ܽӿ�·�� */
#define SFIB_ENABLE_BY_NEXTHOP_BAK         5    /* ������һ��ʹ�ܽӿ�·�� */
#define SFIB_DISABEL_RT_BAK                6    /* ��ֹRIB���� */
#define SFIB_ENABLE_RT_BAK                 7    /* ʹ��RIB���� */
#define SFIB_ROUTE_POLICY_BAK              8    /* ·�ɲ��Եı��� */

/* ȫ�ֵ��Կ��� */
extern ULONG g_ulFibBakDbg;

/* ʵʱ·�ɱ�����Ϣ */
typedef struct tagSFIB_REAL_HEAD_BAK
{
    USHORT usType;              /* ������Ϣ������ */
    USHORT usLen;               /* ������Ϣ����ܳ��� */
    ULONG ulIpAddress;          /* ���õĵ�ַ */
    ULONG ulMaskLen;            /* ���볤�� */
    ULONG ulGateway;            /* ���ص�ַ */
    ULONG ulIfIndex;            /* ���ӿ����� */
    ULONG ulRt_Flags;           /* ·����Ч��� */
    ULONG ulRTPri;              /* ·�����ȼ� */
    ULONG ulPmtu;
} SFIB_REAL_HEAD_BAK_S;

/* ʵʱ��Ϣ������Ϣ */
typedef struct tagSFIB_HEAD_BAK
{
    USHORT usType;              /* ������Ϣ������ */
    USHORT usLen;               /* ������Ϣ����ܳ��� */
    ULONG ulExtend;             /* ��չ�ֶΣ�����·�ɲ���������ֶ� */
} SFIB_HEAD_BAK_S;

ULONG SFIB4_HA_BatchBackup();
ULONG SFIB4_HA_BuildOnePacket(USHORT usType, UCHAR * pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG SFIB4_HA_BatchBackupSendPacket(UCHAR * pucData, USHORT usDataLen, ULONG ulCount);
ULONG SFIB4_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG SFIB4_HA_BuildSendOnePacket(USHORT usType, UCHAR * pucData, USHORT usInBufLen);
USHORT SFIB4_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG SFIB4_HA_Smooth();
ULONG TCPIP_HA_SetSfibDbg(ULONG ulDbg);
ULONG SFIB4_HA_GetSfibDbg (ULONG *pulDbg);
VOID SFIB4_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG SFIB4_HA_SetSfib4VerboseDbg(ULONG ulDbg);
ULONG SFIB4_HA_GetSfib4VerboseDbg (ULONG *pulDbg);
extern void *VOS_Mem_Cpy( void *Dest, const void *Src, ULONG Count );
ULONG SFIB4_HA_Clean(VOID);

#ifdef  __cplusplus
}
#endif

#endif
