/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mstp_api.h
*
*  Project Code: V100R007
*   Module Name:   
*  Date Created: 2008-10-22
*        Author: lianglong111779
*   Description: mstp cbb����ӿ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
#ifndef _MSTP_API_H_
#define _MSTP_API_H_


#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/mstp/include/mstp_cbb_api.h"

/*******************************************************************************
*    Func Name: MSTP_PPI_HookRegister
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: MSTP PPI����ע�ắ��
*        Input: MSTP_PPI_HOOK_FUNC pfMSTPPpiHook:����ָ��
*       Output: 
*       Return: �ɹ�����MSTP_OK���������ش����� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_HookRegister(MSTP_PPI_HOOK_FUNC pfMSTPPpiHook);

/*******************************************************************************
*    Func Name: MSTP_PPI_SetDebugSwitch
* Date Created: 2008-10-22
*       Author: zhangchi(00142640)
*  Description: ����MSTP PPI���Կ���
*        Input: ULONG ulSwitch:����,1��,0�ر�
*       Output: ��
*       Return: �ɹ�����MSTP_OK���������ش����� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi(00142640)         Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_SetDebugSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: MSTP_PPI_Count_Get
* Date Created: 2008-10-22
*       Author: zhangchi(00142640)
*  Description: ��ȡMSTP PPIͳ��
*        Input: MSTP_PPI_COUNT_S *pstCount:PPI�·�����ָ��
*       Output: 
*       Return: �ɹ�����MSTP_OK���������ش����� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi(00142640)        Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_Count_Get(MSTP_PPI_COUNT_S *pstCount);

/*******************************************************************************
*    Func Name: MSTP_PPI_ShowCount
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: ��ʾMSTP PPI�·�ͳ����Ϣ
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID MSTP_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: MSTP_PPI_Count_Reset
* Date Created: 2008-07-29
*       Author: wuhailan
*  Description: ���MSTP PPI�·�ͳ����Ϣ
*        Input: VOID
*       Output: ��
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_Count_Reset(VOID);

/*******************************************************************************
*    Func Name: MSTP_PPI_ComputeUpdateCost
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: ʹ�ܼ���MSTP PPI�·�ʱ�ӿ���
*        Input: ULONG ulSetYes:ʹ�ܿ���:1ʹ��,0ȥʹ��
*       Output: ��
*       Return: �ɹ�MSTP_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_ComputeUpdateCost(ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_PPI_ShowUpdateCost
* Date Created: 2008-12-10
*       Author: zhangchi(00142640)
*  Description: ��ʾPPI�·�ʱ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID MSTP_PPI_ShowUpdateCost(VOID);

#ifdef  __cplusplus
}
#endif

#endif

