/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name:          SmrRam.c
  Description:        sms��ȫ�ֱ�������
  Function List: 
               1.  
  History: 
      1.   ��־��      2004.03.09   �¹�����
      2.Data :2007-08-20
        Author:z40661
        Modify:A32D12705
*******************************************************************************/
#include "smsinclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


SMC_ENTITY_STRU     g_SmcPsEnt;                                                 /* sms ps���ʵ�嶨��                       */
SMC_ENTITY_STRU     g_SmcCsEnt;                                                 /* sms cs���ʵ�嶨��                       */
VOS_UINT8               g_ucPsServiceStatus = SMS_FALSE;                        /* GMM��PS���Ƿ�ע���־                    */
VOS_UINT8               g_ucCsRegFlg = SMS_FALSE;                                                 /* MM��CS���Ƿ�ע���־                    */

SMR_ENTITY_STRU     g_SmrEnt;                                                   /* smr��ʵ�嶨��                            */

/*
SMR_SMC_IMPORTED_FUNC_LIST_STRU   g_SmrSmcApiFunc;                              / * api����ʵ�嶨��                          * /
*/
VOS_UINT8               g_ucSmsMR;                                                     /* SMR��ά���Ķ���Ϣ��ʶ0��255              */
/* ����ȫ������ʾ�ϲ�ָ���Ĵ����� */
VOS_UINT8                g_SndDomain;                                               /* ������ */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

