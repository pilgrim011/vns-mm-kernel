

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CSD_UL_STATUS_INFO_STRU                 g_stCsdStatusInfo = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CSD_ShowULStatus
 ��������  : ��ʾCSD����ͳ����Ϣ
 �������  : vos_void
 �������  : ��
 �� �� ֵ  : vos_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��29��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CSD_ShowULStatus(VOS_VOID)
{
    (VOS_VOID)vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulULRecvPktNum);
    (VOS_VOID)vos_printf("CSD���л��������ݰ��ĸ���                         %d\n",g_stCsdStatusInfo.ulULSaveBuffPktNum);
    (VOS_VOID)vos_printf("CSD�������ʧ�ܵĴ���                             %d\n",g_stCsdStatusInfo.ulULEnQueFail);
    (VOS_VOID)vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulULSendPktNum);
    (VOS_VOID)vos_printf("CSD������������ʱ�Ӷ����л�ȡ����ָ�����Ŀ       %d\n",g_stCsdStatusInfo.ulULQueNullNum);
    (VOS_VOID)vos_printf("CSD������������sk_bufferͷת����IMMͷʧ�ܵİ���Ŀ %d\n",g_stCsdStatusInfo.ulULZcToImmFailNum);
    (VOS_VOID)vos_printf("CSD�����������ݲ���DICCͨ��ʧ�ܵİ���Ŀ           %d\n",g_stCsdStatusInfo.ulULInsertDiccFailNum);
    (VOS_VOID)vos_printf("\r\n");

    return;
}
/*****************************************************************************
 �� �� ��  : CSD_ShowDLStatus
 ��������  : ��ʾCSD����ͳ����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��29��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CSD_ShowDLStatus(VOS_VOID)
{
    (VOS_VOID)vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulDLRecvPktNum);
    (VOS_VOID)vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulDLSendPktNum);
    (VOS_VOID)vos_printf("CSD���з���ʧ�ܰ�����Ŀ                           %d\n",g_stCsdStatusInfo.ulDLSendFailNum);
    (VOS_VOID)vos_printf("\r\n");

    return;
}
/*****************************************************************************
 �� �� ��  : CSD_Help
 ��������  : CSD��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��29��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CSD_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************CSD�����Ϣ************************\n");
    (VOS_VOID)vos_printf("CSD_ShowULStatus                         ��ʾCSD����ͳ����Ϣ\n");
    (VOS_VOID)vos_printf("CSD_ShowDLStatus                         ��ʾCSD����ͳ����Ϣ\n");

    return;
}









#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
