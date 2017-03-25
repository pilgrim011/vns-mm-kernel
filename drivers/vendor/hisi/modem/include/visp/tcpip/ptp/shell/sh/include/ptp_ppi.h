/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Ppi.h
  �� �� ��   : ����
  ��    ��   : ̷ǿ
  ��������   : 2008��5��6��
  ����޸�   :
  ��������   : PPI �ӿڶ����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   :

******************************************************************************/
#ifndef __ptp__ppi__h__
#define __ptp__ppi__h__

#ifdef __cplusplus
    extern "C" {
#endif

extern ULONG g_ulPtpPpiDebugSwitch;      /* PPI�·����Կ��� */
extern PTP_PPI_COUNT_S g_stPtpPpiCount;  /* PPI�·�ͳ�� */

/******************************************************************************
*Func Name   : PTP_PPI_LogMsg
*Description : PTP PPI��ν�ɲ��¼�ӿ�,������־/ͳ��/����
*Input       : ulDebugFlag:����PPI���Ա��,1-��,0-�ر�
*Output      : 
*Return      : .
*******************************************************************************/
extern VOID PTP_PPI_LogMsg(ULONG ulRet,USHORT usPtpPortNumber, ULONG ulPtpPpiCmd, PTP_PPI_S *pstPtpPpiInfo);

#ifdef __cplusplus
}
#endif

#endif


