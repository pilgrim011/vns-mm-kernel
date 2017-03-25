/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcUsim.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2014��11��17��
  ����޸�   :
  ��������   : ����USIM��Ϣ���ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcUsim.h"
#include "TafXCallCtx.h"
#include "Taf_Common.h"
#include "NasUsimmApi.h"
#include "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_USIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCardReadFileReq
 ��������  : ��ȡ�ļ�����
 �������  : enFileId -- �ļ�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID  TAF_XCALL_SndCardReadFileReq(
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId,
    VOS_UINT8                           ucRecordNum
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      (VOS_UINT16)enFileId,
                                      ucRecordNum);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* ��ӡ���ļ���ȡʧ�� */
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_SndCardReadFileReq: Get File Fail ", ulRet);
        return;
    }

    return;
}



#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




