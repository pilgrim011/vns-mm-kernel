/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ppp_task.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : ppp_task.c��ͷ�ļ�
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef _PPP_TASK_H_H_H_
#define _PPP_TASK_H_H_H_


extern VOS_UINT32 PPP_QueueInit(VOS_VOID);
extern VOS_UINT32 PPP_TaskInit(VOS_VOID);
extern VOS_UINT32 PPP_TaskEntry(VOS_VOID);







extern VOID L2TP_AttachQueue(VOS_VOID);
extern VOS_UINT32 PPP_CompInit1(VOS_VOID);
extern VOS_UINT32 PPP_CompInit3(VOS_VOID);
extern VOS_UINT32 PPP_CompInit2(VOS_VOID);
VOS_VOID PPP_SubBoardInit(VOS_VOID);




#ifdef __WIN32_PLATFORM__
#define DVM_WaitForSysCanRun() 1

#endif


#endif /* _PPP_TASK_H_H_H_ */
