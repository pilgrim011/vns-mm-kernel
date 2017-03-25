/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : cosa.c
  �� �� ��   : ����
  ��    ��   : s00207770
  ��������   : 2015��3��21��
  ����޸�   :
  ��������   : cosa PM��Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��21��
    ��    ��   : s00207770
    �޸�����   : �����ļ�

******************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "cosa.h"

/*****************************************************************************
 �� �� ��  : pm_cosa_main_parse
 ��������  : COSA PM��Ϣ���������
 �������  : char *in_buf
             unsigned int len
 �������  : char *out_buf
             unsigned int *out_ptr
 �� �� ֵ  : int PMOM_OK
                 PMOM_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��21��
    ��    ��   : s00207770
    �޸�����   : �����ɺ���

*****************************************************************************/
int pm_cosa_main_parse( char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr )
{
    PM_LOG_COSA_PAM_ENUM_UINT32         enModuleType;
    unsigned int                        ulData_len = 0;
    PM_LOG_RTC_TIMER                   *stInfo;

    if ( 0 == in_buf || 0 == out_buf || 0 == out_ptr)
    {
        return PMOM_ERR;
    }

    enModuleType    = *((PM_LOG_COSA_PAM_ENUM_UINT32 *)in_buf);

    /* �Ƴ�Main type���� */
    in_buf  += sizeof(PM_LOG_COSA_PAM_ENUM_UINT32);
    len     -= sizeof(PM_LOG_COSA_PAM_ENUM_UINT32);

    switch(enModuleType)
    {
        case PM_LOG_COSA_PAM_TIMER:
            stInfo  = (PM_LOG_RTC_TIMER *)in_buf;

            ulData_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
                "Pid is %d, Timer Id is %x\r\n", stInfo->ulPid, stInfo->ulTimerId);

            *out_ptr = *out_ptr + ulData_len;
            break;

        default:
            break;
    }

    return PMOM_OK;
}
