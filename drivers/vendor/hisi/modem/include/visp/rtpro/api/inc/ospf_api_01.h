/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_01.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2013-09-13
*        Author: guojianjun178934
*   Description: ���ļ�����OSPFͨ��I3֪ͨ��Ʒ��صĶ���ṹ�嶨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-13   guojianjun178934        Create
*
*******************************************************************************/
#ifndef _OSPF_API_01_H_
#define _OSPF_API_01_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define OSPF_CLASH_ROUTER_MAX   5   /* 2-LSA��ͻ�����·������(����·��������)*/

#define OSPF_ROUTE_CALCULATE_SUCCESS   1    /*·�ɼ���ɹ�*/
#define OSPF_ROUTE_CALCULATE_FAILURE    2    /*·�ɼ���ʧ��*/

typedef struct tagOSPF_NETWORK_LSA_CLASH_WARNING_S
{
    ULONG ulProcessID;
    ULONG ulAreaID;
    ULONG ulClashIPAddr;
    ULONG ulClashRouterCount;
    ULONG szClashRouterID[OSPF_CLASH_ROUTER_MAX];
}OSPF_NETWORK_LSA_CLASH_WARNING_S;

/*Added by guojianjun178934, ��DOPRA IP V3R2C10-ͬ�����ⵥ-DTS2014081600138����OSPF�ɿ�������ר�ͬһ������Router-ID�������ഥ��·�ɼ������ޣ�����·������ʧ�� , 2014/9/25   ���ⵥ��:DTS2014092408371  */
/*Added by guojianjun178934, �����ӷ������⡿����������������Ʒά��ר��_OSPF�ɿ�������ר��, 2014/6/30   ���ⵥ��:DTS2014062803093 */
/*·�ɼ�������֪ͨ*/
typedef struct tagOSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY
{
    ULONG ulProcessID;                   /* ����ID */
    ULONG ulCalcResult;                 /*·�ɼ�����*/
    ULONG ulAreaID;                     /* ����ID */
    ULONG ulRouterLSACount;             /*��ǰ����Router LSA����*/
    ULONG ulNetworkLSACount;           /* ��ǰ����Network LSA����*/
}OSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY;
/* End of Added by guojianjun178934, 2014/6/30   ���ⵥ��:DTS2014062803093 */
/* End of Added by guojianjun178934, 2014/9/25   ���ⵥ��:DTS2014092408371  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
