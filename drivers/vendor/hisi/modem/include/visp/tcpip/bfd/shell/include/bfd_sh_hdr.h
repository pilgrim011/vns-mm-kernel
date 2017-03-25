/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_sh_hdr.h
*
*  Project Code: VISP V1R6C02
*   Module Name:   
*  Date Created: 2009-07-14
*        Author: mafeng(59090)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-14   zhangchi(00142640)/mafeng(59090)           Create
*
*******************************************************************************/

#ifndef _BFD_SH_HDR_H_
#define _BFD_SH_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* BFD�Ự������Ϣ */
typedef struct tagBFD_HEALTH_BASEINFO_S
{
    ULONG ulVrfIndex;         /* VRF����ֵ */
    ULONG ulSessionID;
    ULONG ulDstIPAddress;     /* �Ự��Ŀ�ĵ�ַ�������� */
    ULONG ulSrcIPAddress;     /* �Ự��Դ��ַ�������� */
    ULONG ulIfIndex;
    USHORT usActDetectMode;
    USHORT usSessionStatus;   /* �Ự״̬ */
    ULONG ulUpToDown;         /* �Ự�Դ���֮��״̬��Up��Down���ܴ��� */
    ULONG ulLastDownTime;     /* ���һ��Down��ʱ�� */
}BFD_HEALTH_BASEINFO_S;

/* BFD NP�·�ͳ����Ϣ */
typedef struct tagBFD_HEALTH_NPINFO_S
{
    /* BFD����֪ͨ�ܴ��� */
    ULONG ulBFDUpdateTotal; 
    /* BFD����֪ͨʧ�ܴ��� */
    ULONG ulBFDUpdateFailure;
}BFD_HEALTH_NPINFO_S;

extern VOID BFD_Health_BatchCheckup(VOID);
extern ULONG BFD_Health_SessionCheckup(VOID);
extern ULONG BFD_Health_NpCheckup(VOID);
extern ULONG BFD_LastWord_LastWordCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
    
#ifdef  __cplusplus
}
#endif
#endif


