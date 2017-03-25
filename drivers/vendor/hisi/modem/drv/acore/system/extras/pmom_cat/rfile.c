/*************************************************************************
*   ��Ȩ����(C) 2008-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  rfile.c
*
*   ��    �� :  yuyangyang 00228784
*
*   ��    �� :  rfile ����������
*
*   �޸ļ�¼ : 2014��12��27��  v1.00  y00228784  ����
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "pmom_cat.h"

int rfile_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{

    if(typeid != 0)
    {
        printf("rfile_msg_parse Error Type ,%d\n",typeid);
        return 1;
    }
    if((len > 256)||((*out_ptr+len)>PMOM_PARSE_STR_BUFSIZ))
    {
        printf("rfile_msg_parse Error Len ,%d,%d\n",len,*out_ptr);
        return 2;
    }
    memcpy(&out_buf[*out_ptr],in_buf,len);
    *out_ptr += len;
    return PMOM_OK;
}

