/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : kirin_partition.h
  �� �� ��   : ����
  ��        ��   : denghao 00221160
  ��������   : 2015��11��3��
  ����޸�   :
  ��������   : mmc_partition.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  ��    ��   : 2015��11��3��
  ��    ��   : denghao 00221160
  �޸�����   : �����ļ�

******************************************************************************/
#ifndef __KIRIN_PARTITION__
#define __KIRIN_PARTITION__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern int flash_find_ptn(const char* str, char* pblkname);
extern int get_cunrrent_total_ptn_num(void);
extern unsigned int flash_get_ptn_index(const char* pblkname);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

