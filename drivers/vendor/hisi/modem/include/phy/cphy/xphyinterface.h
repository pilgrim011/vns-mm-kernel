/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : xphyinterface.h
  �� �� ��   : ����
  ��    ��   : honghuiyong(164941)
  ��������   : 2015��6��13��
  ����޸�   :
  ��������   : �������䣬BBP����ַ�ȡ����ARM��TENSILICA����ͬһ���ط���������
            ��ַ��һ�����д�������Э��ջ��DSP��Ҫ����ͬһ���䣬�������ַ��
            ARM���TENSILCA�࿴���Ĳ���һ����ͨ�����ļ�����Ϊͬһ�ĺ꣬���ʹ��
            ��ͬ�����ּ��ɡ�

  �����б�   :
  �޸���ʷ   :
******************************************************************************/
#ifndef __XPHY_INTERFACE_H__
#define __XPHY_INTERFACE_H__

#include "uphy_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define SHARE_MAILBOX_SIZE                          (0x4800)
#define XPHY_MAILBOX_BASE_ADDR                      (g_aucMailboxBuf)

/* ���������С����*/
#define XPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002000UL)  /*8K�ֽڣ�PS���������С*/
#define XPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002000UL)  /*8k�ֽڣ�PS���������С*/
#define XPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k�ֽڣ�OM���������С*/


#define XPHY_MAILBOX_LHPA_UP_BASE_ADDR              (XPHY_MAILBOX_BASE_ADDR)
#define XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (XPHY_MAILBOX_LHPA_UP_BASE_ADDR + XPHY_MAILBOX_LHPA_UP_SIZE)
#define XPHY_MAILBOX_OM_DOWN_BASE_ADDR              (XPHY_MAILBOX_LHPA_DOWN_BASE_ADDR + XPHY_MAILBOX_LHPA_DOWN_SIZE)

extern UINT8 g_aucMailboxBuf[SHARE_MAILBOX_SIZE];
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* __MEM_MAP_BASE_H__ */
