/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_Com.c
  Description  : MM��������
  Function List:
                1.  Mm_TimerStart
                2.  Mm_TimerStop
                3.  Mm_TimerPause
                4.  Mm_TimerResume
                5.  Mm_SendMsg
                6.  Mm_SendMsgNoWait
                7.  Mm_ComNasInfoSav
                8.  NAS_MML_IsCsLaiChanged
                9.  Mm_ComRandJudge
                10. Mm_ComT3212
                11. Mm_ComSvcStaJudge
                12. Mm_ComRelAllMmConn
                13. Mm_ComRejectCause11
                14. Mm_ComRejectCause12
                15. Mm_ComRejectCause13
                16. Mm_ComRejectCause15
                17. Mm_ComAuthenRcvAuthenRej
                18. Mm_ComTmsiReloc
                19. Mm_ComInfo
                20. Mm_ComIdentity
                21. Mm_ComAbortCause6
                22. Mm_ComAbortCause17
                23. Mm_ComT3214orT3216Expired
                24. Mm_ComDelRandRes
                25. Mm_ComT3218Expired
                26. Mm_ComAuthenNoAutn
                27. Mm_ComAuthenRcvAuthenReq
                28. Mm_ComAuthenRcvUsimCnfSuccess
                29. Mm_ComAuthenRcvUsimCnfFail
                30. Mm_ComAuthenRcvUsimCnf
                31. Mm_ComRejectCause4
                32. Mm_ComRejectCause6
                33. Mm_T3240Expire
                34. Mm_T3230Expire
                35. Mm_ComCheckDelayMmConn
                36. Mm_ComLuOnly
                37. Mm_ComInit
                38. Mm_ComStart
                39. NasMmLock
                40. NasMmUnLock
                41. Mm_ComToU2Handle
                42. Mm_ComLuCauseHandle
                43. Mm_ComGmmAttachCauseHandle
                44. Mm_ComGmmRauCauseHandle
                45. Mm_ComGmmSrCauseHandle
                46. Mm_ComNetDetachCauseHandle
                47. Mm_ComCauseHandleAllProc
                48. Mm_ComToNoImsiHandle
                49. Mm_ComRcvSysHandle
                50. Mm_ComMmConnExist
                51. Mm_ComJudgeProcForMmConn
                52. Mm_ComSaveProcAndCauseVal
                53. Mm_ComJudgeLimitSvc
                54. Mm_ComFillInCMSncReq
                55. Mm_ComFollowOnProc
                56. Mm_ComChkAttDelay
                57. Mm_ComProcCauseProcess
                58. Mm_ComDelLai
                59. Mm_ComProcCauseClear
                60. Mm_ComProcCauseClear
                61. MM_Com_RacChgChk


  History:
      1.  ��־��    2003-12-8  �°�����
      2.  s46746 2006-02-09 �������ⵥA32D01864�޸�
      3.  s46746 2006-02-28 �������ⵥA32D03324�޸�
      4.  s46746 2006-02-28 �������ⵥA32D02503�޸�
      5.  s46746 2006-03-29  �������ⵥA32D02486�޸�
      6. s46746 2006-03-31  �������ⵥA32D02790�޸�
      7.��    ��   : 2006��4��14��
        ��    ��   : liuyang id:48197
        �޸�����   : ���ⵥ�ţ�A32D03031
      8.  s46746 2006-04-19 �������ⵥA32D03273�޸�
      9.  x51137 2006/5/30 A32D04051
      10. s46746 2006-06-21  �������ⵥA32D04355�޸�
     11.  s46746  2006-06-24  �������ⵥA32D04439�޸�
     12.  s46746  2006-07-25  �������ⵥA32D05058�޸�
     13.  s46746  2006.08.02  �������ⵥA32D03686�޸�
     14.  ��    ��   : 2006��9��6��
          ��    ��   : sunxibo id:46746
          �޸�����   : ���ⵥ�ţ�A32D05604
     15.��    ��   : 2006��10��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D05960
     16.x51137 2006/11/3 A32D06511
     17.x51137 2006/11/3 A32D06821
     18.��    ��   : 2006��11��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D06442
     19. ��    ��   : 2006��11��22��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ�ţ�A32D07582
     20. ��    ��   : 2006��11��22��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ�ţ�A32D07583
     21.��    ��   : 2006��12��5��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D07740
     22.��    ��   : 2007��01��03��
        ��    ��   : x51137
        �޸�����   : ���ⵥ��:A32D08115
     23.��    ��   : 2007��3��5��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D09094
     24.��    ��   : 2007��3��10��
        ��    ��   : x51137
        �޸�����   : �������ⵥ�ţ�A32D09201
     25.��    ��   : 2007��04��13��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10663
     26.��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
     27.��    ��   : 2007��06��01��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥA32D10964�޸�
     28.��    ��   : 2007��07��10��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥA32D11966
     29.��    ��   : 2007��07��31��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D12640,MM CONNECTION ACTIVE״̬
                     ���ü�¼���ӽ���ǰ״̬
     30.��    ��   : 2007��9��27��
        ��    ��   : s46746
        �޸�����   : ������Ч��Ϣ��RRMM_NAS_INFO_CHANGE��Ϣ���õ�
     31.��    ��   : 2007��10��06��
        ��    ��   : l65478
        �޸�����   : �������ⵥ�ţ�A32D12977
     32.��    ��   : 2007��11��26��
        ��    ��   : luojian id:107747
        �޸�����   : ���ⵥ�ţ�A32D13605,����Чʱ��Ҫ���¿�״̬
     33.��    ��   : 2007��12��12��
        ��    ��   : l00107747
        �޸�����   : �������ⵥ�ţ�A32D13861
     34.��    ��   : 2007��12��15��
        ��    ��   : l00107747
        �޸�����   : ���ⵥ��:A32D13897,SIM����W�½���CS ע��ʱ��
                     �����ǰLAI��Ч����CKSNҲ��Ϊ��Ч
     35.��    ��   : 2007��12��21��
        ��    ��   : l00107747
        �޸�����   : ���ⵥ��:A32D13951
     36.��    ��   : 2008��5��27��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D03209,�����б�����ʱ��ӦѰ������
     37.��    ��   : 2008��7��23��
        ��    ��   : luojian id:107747
        �޸�����   : �������ⵥ��AT2D04627/AT2D04237,
                     ATTEMPT TO UPDATE/ATTACH ״̬��CM������
     38.��    ��   : 2008��7��28��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D03915,�޸�����RAU����,CS����Ѿ�����LAU�ɹ�����Ҫ
                     ����with IMSI Attach��RAU
     39.��    ��   : 2008��08��1��
        ��    ��   : luojian id:00107747
        �޸�����   : �������ⵥAT2D04486/AT2D04822,�޸�CM��������ܾ�ԭ��ֵΪ#4,
                     RR�����ͷź���,���� 24.008 4.5.1.1,4.2.2.3
     40.��    ��   : 2008��8��13��
        ��    ��   : l0010747
        �޸�����   : ���ⵥ��:AT2D04996/AT2D05037,IDLE ATTEMPT TO UPDATE״ֻ̬����Normal LAU.
     41.��    ��   : 2008��8��23��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
     42.��    ��   : 2008��9��5��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D05514,MM֪ͨ����Ϣ״̬�ı�
     43.��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mm״̬�޸�
     44.��    ��   : 2008��12��22��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��:AT2D07757,MM�������ػ�ԭС����������LU
     45.��    ��   : 2009��01��15��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
     46.��    ��   : 2009��02��24��
        ��    ��   : x00115505
        �޸�����   : ���ⵥ��:AT2D09321,MM��WRR�·���NAS_INFO_CHANGE_REQ TMSI��
                     �� plmnȫ F��ʹWAS����ʧ�ܣ�RRC���ӽ���ʧ�ܡ�
     47.��    ��   : 2009��02��28��
        ��    ��   : s46746
        �޸�����   : �������ⵥAT2D09542,WCDMA��ģ�£�A5/1��������Ϊ��֧��
     49.��    ��   : 2009��03��12��
        ��    ��   : ouyangfei id:00132663
        �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
     50.��    ��   : 2009��04��21��
        ��    ��   : h44270
        �޸�����   : ���ⵥ�ţ�AT2D10800/AT2D11202
     51.��    ��   : 2009��04��29��
        ��    ��   : x00115505
        �޸�����   : AT2D11365,2G��MM�����������ӱ�����ʱ���ĳ��ȹ�������190s�޸�Ϊ15s��
     52.��    ��   : 2009��05��11��
        ��    ��   : h44270
        �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
     53.��    ��   : 2009��07��18��
        ��    ��   : s46746
        �޸�����   : AT2D12943��CS Detach�󣬲�ѯע��״̬��ȻΪע����������
     54.��    ��   : 2009��07��22��
        ��    ��   : s46746
        �޸�����   : AT2D12764��˫ģW��ע��ʱ��MM����GSM������ȡ��ǰƵ�Σ�����GSM�쳣��ӡ
     55.��    ��   : 2009��07��24��
        ��    ��   : z40661
        �޸�����   : ��ϵͳ��ѡ�󣬽������в��ܽ�ͨ
     56.��    ��   : 2009��07��31��
        ��    ��   : x00115505
        �޸�����   : AT2D13428,2G������ע���ȥע��PS��֮�����������У�����ظ�Cm Service Reject��#4��������ʧ�ܡ�
     57. ��    ��   : 2009��08��11��
         ��    ��   : z40661
         �޸�����   : ���ⵥ�ţ�AT2D13689������ʱ������������У�����ظ�ԭ��ֵ4ʱ���ҵ�ǰPLMN����ֹʱ����һ�η���Cm Service Req��ԭ��ΪMM����δ�����
     58.��    ��   : 2009��09��23��
        ��    ��   : x00115505
        �޸�����   : AT2D14632,����ע��ʧ�ܣ���ѯCREG���� 1
     59.��    ��   : 2010��3��2��
        ��    ��   : o00132663
        �޸�����   : NAS R7Э��������������·�ͷ���ǿ���������
*******************************************************************************/
#include        "MM_Inc.h"
#include        "stdlib.h"
#include        "GmmMmInterface.h"
#include        "NasMmSndOm.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#include "NasMmEcall.h"
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

#include "MmCmInterface.h"
#include "MmCcInterface.h"
#include "MmSsInterface.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

extern MM_SUSPEND_MSG_BUF_ST gstMmSuspendMsgQue;
extern MM_TIMER_ST  gstMmTimerSuspend;

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_COM_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*****************************************************************************
   2 ��������
*****************************************************************************/
RRC_TO_MMCC_REL_CAUSE_STRU g_astRrcToMmCcRelCause[] =
{
    {RRC_REL_CAUSE_RR_NORM_EVENT             ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_EVENT},
    {RRC_REL_CAUSE_RR_UNSPEC                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_RR_PRE_EMPT_REL           ,  NAS_MMCM_REL_CAUSE_RR_REL_PREEMPTIVE_RELEASE},
    {RRC_REL_CAUSE_RR_CONGEST                ,  NAS_MMCM_REL_CAUSE_RR_REL_CONGESTION},
    {RRC_REL_CAUSE_RR_RE_EST_REJ             ,  NAS_MMCM_REL_CAUSE_RR_REL_REEST_REJ},
    {RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST   ,  NAS_MMCM_REL_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST},
    {RRC_REL_CAUSE_RR_USER_INACT             ,  NAS_MMCM_REL_CAUSE_RR_REL_USER_INACTIVE},
    {RRC_REL_CAUSE_UTRAN_RELEASE             ,  NAS_MMCM_REL_CAUSE_RR_REL_UTRAN_RELEASE},
    {RRC_REL_CAUSE_NAS_REL_SUCCESS           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_REL_ABSENT            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_ABORT                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_STOP_SETUP            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_CONN_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_CONN_FAIL},
    {RRC_REL_CAUSE_NAS_DATA_ABSENT           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_DATA_ABSENT},
    {RRC_REL_CAUSE_RRC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RRC_ERROR},
    {RRC_REL_CAUSE_RL_FAILURE                ,  NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE},
    {RRC_REL_CAUSE_GAS_TIMEOUT               ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_OTHER_REASON              ,  NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON},
    {RRC_REL_CAUSE_NO_RF                     ,  NAS_MMCM_REL_CAUSE_RR_REL_NO_RF},
    {RRC_REL_CAUSE_RLC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RLC_ERR_OR},
    {RRC_REL_CAUSE_CELL_UPDATE_FAIL          ,  NAS_MMCM_REL_CAUSE_RR_REL_CELL_UP_DATE_FAIL},
    {RRC_REL_CAUSE_T314_EXPIRED              ,  NAS_MMCM_REL_CAUSE_RR_REL_T314_EXPIRED},
    {RRC_REL_CAUSE_W_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_W_RL_FAIL},

    {RRC_REL_CAUSE_G_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_G_RL_FAIL},
};

EST_RSLT_TO_MMCC_REL_CAUSE_STRU g_astEstRsltToMmCcRelCause[] =
{
    {RRC_EST_SUCCESS                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_PRESENT                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_ESTING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_DELING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CONGESTION},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UNSPECIFIED},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RF},
    {RRC_EST_RJ_SNW                             ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_VALID_INFO},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_TIME_OUT},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO},
};


NAS_MM_LAU_EST_CNF_TO_T3212_START_SCENE_STRU g_astLauEstCnfRsltToT3212StartScene[] =
{
    {RRC_EST_SUCCESS                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_PRESENT                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_ESTING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_DELING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_SNW                             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
};

NAS_MM_T3212_START_SCENE_CFG_TBL_STRU g_astNasMmT3212StartSceneCfgTbl[] =
{
    /* ��ǰBITλ,    ���ÿ��Ƴ��� */
    {0,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},            /* BIT0����: LAU����ʱ��ʧ������T3212���� */
    {1,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS},            /* BIT1����: LAU����ʱ��REL����T3212���� */
};
#if (FEATURE_ON == FEATURE_LTE)
CSFB_RSLT_TO_MMCC_REL_CAUSE_STRU g_astCsfbRsltToMmCcRelCause[] =
{
    {MM_LMM_CSFB_SERVICE_RSLT_FAILURE                           ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL},
    {MM_LMM_CSFB_SERVICE_RSLT_AUTH_REJ                          ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_AUTH_REJ},
    {MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT                 ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT},
    {MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL                   ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL                    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_EMM_STATE    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_SMS_ONLY       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_SMS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_PS_ONLY        ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_PS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL},
};
#endif
/*lint -save -e958 */

/*******************************************************************************
  Module:   Mm_ComNasInfoSav
  Function: MM ��ʼ��
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��      2003.12.16   �°�����
  2.��־��   2004.10.25   ���ݴ洢�ṹ�����Ӧ
  3.��    ��   : 2006��9��6��
    ��    ��   : sunxibo id:46746
    �޸�����   : ���ⵥ�ţ�A32D05604
  4.��    ��   : 2007��11��26��
    ��    ��   : luojian id:107747
    �޸�����   : ���ⵥ�ţ�A32D13605
  5.��    ��   : 2009��04��21��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D10800/AT2D11202
  6.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2012��02��29��
    ��    ��   : l00130025
    �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
  8.��    ��   : 2012��03��20��
    ��    ��   : l00130025
    �޸�����   : DTS2012030105247,NASֻ������ʵ�ʷ����Ȩʱ,֪ͨW SecurityKey�������������WAS���ö�Ӧ�ӿڻ�ȡ
*******************************************************************************/
VOS_VOID Mm_ComNasInfoSav (
                       VOS_UINT8    ucAttachState,
                       VOS_UINT8    ucCksnFlg
                       )
{
    /* ����CSע��״̬ */
    if ( g_MmSubLyrShare.MmShare.ucCsAttachState != ucAttachState )
    {
        g_MmSubLyrShare.MmShare.ucCsAttachState = ucAttachState;
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_ATTACH_FLG);
        if ((g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {
            Mm_SndSmsRegStsInd( g_MmSubLyrShare.MmShare.ucCsAttachState );
        }
    }
    else
    {
        if ((g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {

            Mm_SndSmsRegStsInd(MM_STATUS_ATTACHED);
        }
    }


    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);
    }


    /* ����CS��ȫ���� */
    if ( NAS_MML_GetSimCsSecurityCksn() != ucCksnFlg )
    {
        NAS_MML_SetSimCsSecurityCksn(ucCksnFlg);
        if ( MM_CKSN_INVALID == NAS_MML_GetSimCsSecurityCksn() )
        {
            NAS_MML_InitCsSecurityUmtsCkInvalid();
            NAS_MML_InitCsSecurityUmtsIkInvalid();

            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_DEL_KEY_FLG);
        }
        else
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }
        }
    }
    return;                                                                     /* ����                                     */
}

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

/*******************************************************************************
  Module:   Mm_ComRandJudge
  Function: �ж�RAND�Ƿ�仯
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   MM_TRUE     RAND�仯
            MM_FALSE    RAND���仯
  History:
      1.  ��־��     2003.12.10  �°�����
*******************************************************************************/

VOS_UINT8 Mm_ComRandJudge()
{
    VOS_UINT8                       i;
    VOS_UINT8                   ucRet = MM_FALSE;

    for ( i = 0; i < 16; i++ )
    {
        if ( g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] !=
            g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] )
        {
            ucRet = MM_TRUE;
            break;
        }
    }
    return ucRet;

}

/*******************************************************************************
  Module:   Mm_ComUpdateUsimFileReq
  Function: ���¿��ļ�
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:
  History:
      1.  hezhijun     2015.02.17  �°�����
*******************************************************************************/
VOS_VOID Mm_ComUpdateUsimFileReq(
    VOS_VOID
)
{
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
    }

    return;
}


/*******************************************************************************
  Module:   Mm_ComSvcStaJudge
  Function: �жϷ���״̬�Ƿ�ı�
  Input:    VOS_UINT8 ucSvcStatus
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.16  �°�����
*******************************************************************************/

VOS_VOID Mm_ComSvcStaJudge(VOS_UINT8 ucSvcStatus)
{
    if ( ucSvcStatus != g_MmGlobalInfo.ucMmServiceState )
    {
        g_MmGlobalInfo.ucMmServiceState = ucSvcStatus;
    }
}

/*******************************************************************************
  Module:   Mm_ComRelAllMmConn
  Function: �ͷ�����MM����,���ڽ���MM����
  Input:    enMmccRelCause - �ͷ�ԭ��ֵ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.16  �°�����
      2.  s46746     2006.08.09  �������ⵥA32D05269�޸�

      3.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬

      4.��    ��   : 2012��2��24��
        ��    ��   : w00167002
        �޸�����   : CSFB&PPAC&ETWS&ISR ����:���CSFB���ڱ�־
      5.��    ��   : 2012��5��26��
        ��    ��   : w00176964
        �޸�����   : GUL BG��Ŀ����:֧��CSFBʱ�Ȳ����CC SS�Ļ���,���յ�LMM��ע�������
      6.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      7.��    ��   : 2013��01��23��
        ��    ��   : s00217060
        �޸�����   : ���ⵥ: DTS2013012106172,����������ı�־
      8.��    ��   : 2013��3��30��
        ��    ��   : l00167671
        �޸�����   : �����ϱ�AT�������������C��
      9.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����   :DTS2013082903019:֧��ss�ط�����
      10.��    ��   :2013��10��18��
         ��    ��   :z00161729
         �޸�����   :DTS2013101900866:mm��wait for mm connection״̬�յ�gas������Ϣû�и�cc�ظ�rel ind���º���T303��ʱ����ʧ��
      11.��    ��   :2013��10��20��
         ��    ��   :z00234330
         �޸�����   :DTS2013111903821:MM�ظ���ti����ȷ,�����ϲ�ҵ��û�д����ط�������
      12.��    ��   : 2014��6��13��
         ��    ��   : w00242748
         �޸�����   : DSDS ������
      13.��    ��   :2014��7��22��
         ��    ��   :s00217060
         �޸�����   :K3V3 ��ģ����������:CSҵ�������ͷ�ʱ,֪ͨMMC
      14.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRelAllMmConn(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8                                               i;

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
    VOS_UINT8                                               ucCsSrvFlg;

    ucCsSrvFlg  = VOS_FALSE;
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */


    for ( i = 0; i < 7; i++ )
    {
        /*lint -e701*/
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����CC������MM����                       */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����CC������MM����                       */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����CC�ؽ�����MM����                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����CC�ؽ�����MM����                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {

            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����SS������MM����                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����SS������MM����                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����SMS������MM����                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause );
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

            /* ����SMS������MM����                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause );
        }

        /*lint +e701*/
    }


    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {

        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }



    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    /* ��MM���Ӵ��ڱ�־���ó�û�� */
    g_MmGlobalInfo.ucMMConnEstingPD  = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI      = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]   = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]   = 0;

    NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    /* CSFB���� */

    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
#endif

    NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
    /* ֮ǰ��CSҵ����ڣ��ͷ�����ʱ֪ͨMMC */
    if (VOS_TRUE == ucCsSrvFlg)
    {
        Mm_SndMmcCmSvcInd(VOS_FALSE);
    }
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

}
/*******************************************************************************
  Module:   Mm_ComRelAllMmConnExcEmergencyCall
  Function: �ͷų��˽�����֮������MM����,���ڽ���MM����
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.
      2.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      3.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����   :DTS2013082903019:֧��ss�ط�����
      4.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_ComRelAllMmConnExcEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8               i;

    /*lint -e701*/
    for (i = 0; i < 7; i++)
    {
        /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
           �������ж���һ�������ǽ����� */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* ����CC�ؽ�����MM���� */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
           �������ж���һ�������ǽ����� */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* ����CC������MM���Ӳ��Ҳ��ǽ�����         */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
           �������ж���һ�������ǽ����� */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* ����CC�ؽ�����MM����                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
           �������ж���һ�������ǽ����� */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* ����CC�ؽ�����MM����                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* ����SS������MM����                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* ����SS������MM����                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* ����SMS������MM����                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* ����SMS������MM����                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause);
        }
    }

    /*lint +e701*/

    /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
       �������ж���һ�������ǽ����� */
    if ((NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg))
    {
        /* ���ڽ���MM�����Ҳ��ǽ�������MM����       */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       ucMMConnEstingTI,
                       enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       ucMMConnEstingTI, enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI,
                        enMmCcRelCause);
    }
    /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
       �������ж���һ�������ǽ����� */
    if ((MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType))
    {
        /* �л����MM���ӽ�������                   */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);                       /* ָʾ�����MM���ӽ���ʧ��                 */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* ��������־                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {                                                                           /* �л����MM���ӽ�������                   */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);                        /* ָʾ�����MM���ӽ���ʧ��                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* ��������־                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {                                                                           /* �л����MM���ӽ�������                   */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       RcvXXEstReq.ulTransactionId, enMmCcRelCause);

        /* ָʾ�����MM���ӽ���ʧ��                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* ��������־                             */
    }


    /* �����жϽ����ֻ֧��һ��CC���е��������֧�ֶ��CC���й���ʱ��
       �������ж���һ�������ǽ����� */
    if (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg)
    {
        g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] = 0;
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] = 0;

    if ( ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MM_RelAllExistSsConn
 ��������  : �ͷ����д��ڵ�ssҵ���Ӧ��MM����
 �������  : NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��7��2��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RelAllExistSsConn(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < 7; i++ )
    {
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] & ((VOS_UINT32)0x01 << i) ))
        {
            Mm_SndSsRelInd(i, enMmCcRelCause);

            NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_RelAllExistSsConn: exist mt ss conn, i", i);
        }

        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] & ((VOS_UINT32)0x01 << i) ))
        {
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);

            NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_RelAllExistSsConn: exist mo ss conn, i", i);
        }
    }

    /* ��ssҵ���Ӧ��MM���Ӵ��ڱ�־���ó�û�� */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] = 0;

    return;
}



/*******************************************************************************
  Module:   Mm_ComRejectCause11
  Function: �յ�ԭ��ֵΪ#11�Ĵ���
  Input:    VOS_UINT8 ucType
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.09  �°�����
  2. ��    ��   : 2008��8��21��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/

VOS_VOID Mm_ComRejectCause11(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        /* ע�ᱻ12�ܾ����ó��Ժ����ط� */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
    }

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* ���÷���״̬                             */
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* ���ø���״̬                             */

    switch(ucType)
    {
    case MM_ATTACH:
    case MM_RAU:
    case MM_NET_DETACH:
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause11:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                                       /* ��RRC����RRMM_REL_REQ(CS��)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* �����ͷ�RR����ʱ������״̬             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}



/*******************************************************************************
  Module:   Mm_ComRejectCause13
  Function: �յ�ԭ��ֵΪ#13�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.16  �°�����
  2. ��    ��   : 2008��8��21��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��9��12��
    ��    ��   : z00161729
    �޸�����   : DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause13(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* ���÷���״̬                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause13:INFO: MmServiceState is MM_LIMITED_SERVICE");
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* ���ø���״̬                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause13:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* �����ͷ�RR����ʱ������״̬             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}

/*******************************************************************************
  Module:   Mm_ComRejectCause15
  Function: �յ�ԭ��ֵΪ#15�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.16  �°�����
  2. ��    ��   : 2008��8��21��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��9��12��
    ��    ��   : z00161729
    �޸�����   : DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause15(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* ���÷���״̬                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause15:INFO: MmServiceState is MM_LIMITED_SERVICE");
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* ���ø���״̬                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* ����SIM������״̬                        */
        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* ����SIM������״̬                        */
        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause15:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* �����ͷ�RR����ʱ������״̬             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is  MM_IDLE_LIMITED_SERVICE");
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvAuthenRej
  Function: ��Ȩʧ�ܵĴ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.09  �°�����
  2. ��    ��   : 2007��06��01��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥA32D10964�޸�
  3.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mm״̬�޸�
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  6.��    ��   : 2012��12��29��
    ��    ��   : w00167002
    �޸�����   : DTS2012122900619:DCM MM-18-01-22 �ַ�Ҫ�����CS:4F20�ļ���PS����
                 4F52�ļ�;balong������PSû�и���CS��
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2013��06��5��
    ��    ��   : w00242748
    �޸�����   : svlte��usim�ӿڵ���
  9.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 10.��    ��   : 2013��7��29��
    ��    ��   : y00245242
    �޸�����   : �����µ�USIM�ӿ�
 11.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvAuthenRej()
{
    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ);

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAuthenRcvAuthenRej:INFO: MmServiceState is MM_NO_IMSI");
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* ���ø���״̬                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* ����SIM������״̬                        */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);                     /* ����SIM������״̬                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);                     /* ����SIM������״̬                        */

        /* DCM MM-18-01-22 Ҫ�����CS:4F20�ļ���PS����4F52�ļ� */
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        /* A32D10964 ==> */
        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S0_E23(VOS_NULL_PTR);
        }
        /* <== A32D10964 */
    }
}


/*******************************************************************************
  Module:   Mm_ComTmsiReloc
  Function: TMSI RELOC���̵Ĺ�������
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.��    ��   : 2010��9��30��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �������ⵥ��DTS2010092902368,TMSIֻ�ڵ�ЧPLMN����Ч
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��3��24��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����,BBIT�����޸�
  5.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  6.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/

VOS_VOID Mm_ComTmsiReloc()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    pstCurrCampLai = NAS_MML_GetCurrCampLai();
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    pstCsSuccLai->stPlmnId.ulMcc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMnc;
    pstCsSuccLai->aucLac[0] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
    pstCsSuccLai->aucLac[1] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac) & (0x00FF);

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_MS_ID_IMSI_PRESENT ==
        ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                    MM_MS_ID_IMSI_PRESENT ) )
    {
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* ����TMSI��Ч                             */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMSI_PRESENT;    /* ����IMSI��Ч                             */

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

    }
    else
    {
        if ( MM_MS_ID_TMSI_PRESENT ==

                    ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                MM_MS_ID_TMSI_PRESENT ) )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }

        }

    }
    Mm_ComMsgTmsiRelocCpltSnd();                                                /* ����TMSI REALLOCATION COMPLETE           */
}

/*******************************************************************************
  Module:   Mm_ComInfo
  Function: MM INFO���̵Ĺ�������
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.  s46746  2005.10.20  �޸�
      3.  x51137 2006/5/30 A32D04051

      4.��    ��   : 2011��7��13��
        ��    ��   : zhoujun 40661
        �޸�����   : SIM�����ݸ��µ�MML��
*******************************************************************************/

VOS_VOID Mm_ComInfo()
{

    Mm_SndMmcInfoInd();
}

/*******************************************************************************
  Module:   Mm_ComIdentity
  Function: IDENTITY���̵Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
*******************************************************************************/

VOS_VOID Mm_ComIdentity()
{
    MM_MSG_ID_RSP_STRU    Msg;

    NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

    switch( g_MmMsgIdReq.MmIeIdType.ucIDType )
    {
    case MM_IE_MI_ID_TYPE_IMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_IMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    case MM_IE_MI_ID_TYPE_IMEI:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEI_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_IMEISV:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEISV_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_TMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_TMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_TMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    default:
        break;
    }
    Mm_ComMsgIdRspSnd(&Msg);                                                    /* IDENTITY RESPONSE��Ϣ                    */

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_IDResInfoRecord(g_MmMsgIdReq.MmIeIdType.ucIDType);
#endif

}

/*******************************************************************************
  Module:   Mm_ComAbortCause6
  Function: ABORT���̵Ĵ���,#6
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  ��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��9��12��
    ��    ��   : z00161729
    �޸�����   : DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  9.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/

VOS_VOID Mm_ComAbortCause6()
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);        /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAbortCause6:INFO: MmServiceState is MM_NO_IMSI");
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* ���ø���״̬                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* �����ͷ�RR����ʱ������״̬             */
    Mm_TimerStart(MM_TIMER_T3240);
    /* Mm_SndMmcCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME); */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComAbortCause17
  Function: ABORT���̵Ĵ���,#17
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComAbortCause17()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NETWORK_FAILURE);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);   /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;            /* �����ͷ�RR����ʱ������״̬             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause17:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComT3214orT3216Expired
  Function: T3214����T3216����Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.12  �°�����
******************************************************************************/

VOS_VOID Mm_ComT3214orT3216Expired()
{
    Mm_ComAuthMsRej();
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

}

/*******************************************************************************
  Module:   Mm_ComDelRandRes
  Function: ɾ��RAND��RES�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��  ��   2004.01.07   �°�����
      2.  ��־��   2004.10.25   ���ݴ洢�ṹ�����Ӧ
*******************************************************************************/

VOS_VOID Mm_ComDelRandRes()
{
    VOS_UINT8                   i;

    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg = MM_AUTHEN_RES_ABSENT;

    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_ABSENT;

    /* Modified by ��־�� 2004.10.25 begin */
    /* g_MmGlobalInfo.AuthenCtrlInfo.ulRes = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 0, 4);
    /* Modified by ��־�� 2004.10.25 end */
    g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;
    /* Modified by ��־�� 2004.10.25 begin */
    /* g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 0, 12);
    /* Modified by ��־�� 2004.10.25 end */
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;
    for ( i = 0; i < 16; i ++ )
    {
        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] = 0;
        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] = 0;
    }
}

/*******************************************************************************
  Module:   Mm_ComT3218Expired
  Function: T3218����Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.12  �°�����
*******************************************************************************/

VOS_VOID Mm_ComT3218Expired()
{
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

}

/*******************************************************************************
  Module:   Mm_ComAuthenNoAutn
  Function: ��Ϣ�в���AUTN�ĳ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.��    ��   : 2013��1��30��
        ��    ��   : w00176964
        �޸�����   : DTS2013012906743:����3�μ�Ȩʧ�ܲ���Ϊ��Ȩʧ��
      3.��    ��  : 2013��11��15��
        ��    ��  : m00217266
        �޸�����  : sim����Ȩʧ��ԭ���ϱ�
*******************************************************************************/

VOS_VOID Mm_ComAuthenNoAutn()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE;

    Mm_ComMsgAuthFailSnd(&Msg);                                                 /* ����AUTHENTICATION FAILURE��Ϣ           */
    NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt++;

    /* R6�汾�Ժ��������μ�Ȩʧ��UE������Ϊ��Ȩʧ�� */
    if ((PS_PTL_VER_R6  <= cVersion)
     && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    /* �˴�ʵ��ԭ���ο�R5Э���������μ�Ȩʧ��UE������Ϊ��Ȩʧ�� */
    if ((PS_PTL_VER_R5  >= cVersion)
     && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
      || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    if (VOS_TRUE == ucAuthFailFlg)
    {
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        Mm_ComAuthMsRej();

    }
    else
    {
        g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;       /* ������һ�εĴ�����Ϣ                     */
        Mm_TimerStart(MM_TIMER_T3214);
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvAuthenReq
  Function: �յ�AUTHEN REQ�Ĵ���
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��  ��  2003.12.10  �°�����
  2.  ��־��  2004.10.25  ���ݴ洢�ṹ�����Ӧ
  3.  ��־��     2005.01.27  007037 for MM
  4.  s46746  2005.09.05  for HSS4100 V200R001
  5.��    ��   : 2006��12��5��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07740
  6.��    ��   : 2010��11��19��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:DTS2010111604811,��Ȩ�����н��յ���ͬ��Ȩ��Ϣ����
  7.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  8.��    ��   : 2014��10��20��
    ��    ��   : w00167002
    �޸�����   : DTS2014102000868:�ڼ�Ȩ�ɹ���Ÿ���CKSN
  9.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvAuthenReq()
{
    VOS_UINT8                           i;
    MM_MSG_AUTHENTICATION_RSP_STRU      Msg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType   = NAS_MML_GetCurrNetRatType();

    /* ���� SIM ����Ȩ�� USIM ���� GSM �¼�Ȩ */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus()) /* �������� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "Mm_ComAuthenRcvAuthenReq: WARNING: Sim is invalid!");

        /* ������Ϣ������, ��������ֱ�ӷ��� */
        return;
    }
    /* Ϊ SIM �������� USIM ���� GSM ���е� GSM ��Ȩ */
    else if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
          || ((MM_IE_AUTN_ABSENT == g_MmMsgAuthReq.ucAutnFlg)
          && (NAS_MML_NET_RAT_TYPE_GSM == enRatType)))
    {

        MM_GsmAuthProc();

        return;
    }
    else
    {

    }
    /* USIM ���� UMTS ���м�Ȩ���� USIM ���� GSM ���е� UMTS ��Ȩ��������д��� */


    if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
    {                                                                           /* MS��֧��UMTS ALGO                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthenRcvAuthenReq:WARNING: Not support UMTS ALGO");
        return;
    }
    PS_MEM_SET(&Msg,0,sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                g_MmMsgAuthReq.MmIeRAND.aucRandValue,
                16 * sizeof(VOS_UINT8)
                );

    /* ��3G��Ȩ�����2G��Ȩ��� */
    NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);

    if ( MM_IE_AUTN_PRESENT == g_MmMsgAuthReq.ucAutnFlg )
    {                                                                           /* AUTN���ڵĳ���                           */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen
            = g_MmMsgAuthReq.MmIeAUTN.ucAutnLen;
        for ( i = 0; i < g_MmMsgAuthReq.MmIeAUTN.ucAutnLen; i++ )
        {
            g_MmGlobalInfo.AuthenCtrlInfo.aucAutn[i]
                = g_MmMsgAuthReq.MmIeAUTN.aucAutn[i];
        }
        if ( MM_AUTHEN_RAND_ABSENT ==  g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg )
        {
            PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_PRESENT;   /* ����RAND���ڱ�ʶ                         */
            /*A32D07740==>*/
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
            /*<==A32D07740*/
            Mm_SndAgentUsimAuthenReq();                                         /* ����AGENT_USIM_AUTHENTICATION_REQ        */
            Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                              /* ��������TIMER                            */
            /* Mm_TimerStart(MM_TIMER_PROTECT); */
        }
        else
        {
            if ( ( MM_FALSE == Mm_ComRandJudge() ) )
            {                                                                   /* RAND��ͬ                                 */
                /* ǰ���� RAND �Ƿ���ͬ */
                if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
                {
                    /* ���� RAND ���ϴ���ͬ */
                    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat = MM_AUTHEN_RAND_REPEAT;

                    Mm_SndAgentUsimAuthenReq();                                 /* ����AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* ��������TIMER                            */
                }
                /* ǰ���� RAND ��ͬ���� RES ���ڣ����μ�Ȩ�������ϴ���ͬ */
                else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg)
                    && (AUTHENTICATION_REQ_UMTS_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
                /* if ( MM_AUTHEN_RES_PRESENT ==
                                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg ) */
                {                                                               /* RES���ڵĳ���                            */

                    /* Modified by ��־�� 2004.10.25 begin */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =  */
                    /*    (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] = */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 )    */
                    /*                                                & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 )   */
                    /*                                                 & 0xFF); */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 )   */
                    /*                                                 & 0xFF); */
                    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
                    /* Modified by ��־�� 2004.10.25 end */
                    if ( MM_CONST_NUM_0 !=
                            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
                    {
                        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
                        Msg.MmIeAuthRspParaExt.ucLength =
                        (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
                        /* Modified by ��־�� 2004.10.25 begin */
                        /* for ( i = 0; i < 4; i ++ )                    */
                        /* {                                              */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 8] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);   */
                        /* }                                                  */
                        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                                  g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
                        /* Modified by ��־�� 2004.10.25 end */
                    }

                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenReq: Send Auth Rsp");
                    NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);
                    
                    Mm_ComMsgAuthRspSnd(&Msg);                                  /* ����AUTHENTICATION RESPONSE(RES)         */
                }
                else
                {                                                               /* RES�����ڵĳ���                          */
                    /* Res �Ƿ���ڵı�־�����ڼ�Ȩ�ɹ������� */
                    /*g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg =
                                                        MM_AUTHEN_RES_PRESENT;*/  /* ����RES���ڵı�ʶ                        */

                    Mm_SndAgentUsimAuthenReq();                                 /* ����AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* ��������TIMER                            */
                    /* Mm_TimerStart(MM_TIMER_PROTECT); */
                }
            }
            else
            {                                                                   /* RAND����ͬ�ĳ���                         */
                PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );

                /* ���� RAND ���ϴβ�ͬ����Ҫ���RES���ڱ�־ */
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg       = MM_AUTHEN_RES_ABSENT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg      = MM_AUTHEN_RES_ABSENT;

                Mm_SndAgentUsimAuthenReq();
                Mm_TimerStart(MM_TIMER_PROTECT_AGENT);
            }
        }
    }
    else
    {
        Mm_ComAuthenNoAutn();
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnfSuccess
  Function: �յ�USIM������AGENT_USIM_AUTHENTICATION_CNF(SUCCESS)�Ĵ���
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��  ��  2003.12.12  �°�����
  2.  ��־��  2004.10.25  ���ݴ洢�ṹ�����Ӧ
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

  4.��    ��   : 2012��12��29��
    ��    ��   : w00167002
    �޸�����   : DTS2012122900619:DCM MM-18-01-22 �ַ�Ҫ�����CS:4F20�ļ���PS����
                 4F52�ļ�;balong������PSû�и���CS��
  5.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : svlte��usim�ӿ��޸�
  6.��    ��   : 2013��7��29��
    ��    ��   : y00245242
    �޸�����   : �����µ�USIM�ӿ�
  7.��    ��   : 2014��4��175��
    ��    ��   : s00246516
    �޸�����   : DTS2014041700472:ʹ��2G SIM����PAD��̬�ϳ��ּ�Ȩ������ܾ�
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnfSuccess()
{
    /* Deleted by ��־�� 2004.10.25 begin */
    /* VOS_UINT8                               i;*/
    /* Deleted by ��־�� 2004.10.25 end */
    MM_MSG_AUTHENTICATION_RSP_STRU    Msg;

    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    if ( ( WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState ) ||
        ( WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION ==
                                            g_MmGlobalInfo.ucState ) )
    {                                                                           /* ΪT3230���е�״̬�ĳ���                  */
        Mm_TimerStart(MM_TIMER_T3230);                                          /* ����T3230                                */
    }
    if ( LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3210);                                          /* ����T3210                                */
    }
    if ( IMSI_DETACH_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3220);                                          /* ����T3220                                */
    }
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;


    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* ���ú��� Mm_SndAgentUsimUpdateFileReq ���� KC��CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);
    }
    else /* USIM �� */
    {
        /* ���� USIM �� CK IK CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);

        /* DCM MM-18-01-22 Ҫ�����CS:4F20�ļ���PS����4F52�ļ� */
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    /* �� AS ����RRMM_NAS_INFO_CHANGE_REQ */
    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);

    /* �������� RAND ��ͬ��Ҫ��ʱ������ Res��RAND ��Ч�� */
    if (MM_AUTHEN_RAND_REPEAT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
    {
        Mm_TimerStop(MM_TIMER_T3218);                                           /* ֹͣT3218                                */
        Mm_TimerStart(MM_TIMER_T3218);                                          /* ����T3218                                */
    }


    /*if ( MM_AUTHEN_RES_ABSENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg )*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* ����SIM��CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);   */                           /* ��RRC����RRMM_NAS_INFO_CHANGE_REQ        */
    /*}*/
    /*else*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);  */                   /* ����SIM��CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);  */                            /* ��RRC����RRMM_NAS_INFO_CHANGE_REQ        */
    /*     */
    /*    Mm_TimerStop(MM_TIMER_T3218);  */                                         /* ֹͣT3218                                */
    /*    Mm_TimerStart(MM_TIMER_T3218);  */                                        /* ����T3218                                */
    /*}                                                                                                                       */

    /* Modified by ��־�� 2004.10.25 begin */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =   */
    /*     (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 ) & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 ) & 0x000000FF); */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] = */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 ) & 0x000000FF); */

    PS_MEM_SET(&Msg, 0x0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
    /* Modified by ��־�� 2004.10.25 end */
    if ( MM_CONST_NUM_0 != g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
    {
        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
        Msg.MmIeAuthRspParaExt.ucLength =
            (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
        /* Modified by ��־�� 2004.10.25 begin */
        /* for ( i = 0; i < 4; i ++ )   */
        /* {              */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =   */
        /*     (VOS_UINT8)( (g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>   */
        /*                                             ( i * 8 ) ) & 0x000000FF); */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /*    Msg.MmIeAuthRspParaExt.aucRES[i + 8] =   */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /* }        */
        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
        /* Modified by ��־�� 2004.10.25 end */
    }
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvUsimCnfSuccess: Return Auth Succ");
    Mm_ComMsgAuthRspSnd(&Msg);                                                  /* ����AUTHENTICATION RESPONSE(RES)         */

}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnfFail
  Function: �յ�USIM������AGENT_USIM_AUTHENTICATION_CNF(FAILURE)�Ĵ���
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��  ��  2003.12.12  �°�����
      2. ��־��  2004.10.23  AGENT�ӿڱ����Ӧ
      3.��    ��   : 2013��1��30��
        ��    ��   : w00176964
        �޸�����   : DTS2013012906743:����3�μ�Ȩʧ�ܲ���Ϊ��Ȩʧ��
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnfFail()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Mm_TimerStop(MM_TIMER_T3230);                                               /* ֹͣT3230                                */
    Mm_TimerStop(MM_TIMER_T3220);                                               /* ֹͣT3220                                */
    Mm_TimerStop(MM_TIMER_T3210);                                               /* ֹͣT3210                                */
    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    if ( AGENT_AUTH_FAIL_MAC_CODE == g_AgentUsimAuthCnf.ucFailureCause )
    {                                                                           /* ʧ�ܵ�����ΪMAC CODE FAIL�ĳ���          */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE;
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* ����AUTHENTICATION FAILURE               */

        /* 3GPP.24008 The MS shall deem that the network has failed the authentication check and behave
        as described in subclause 4.3.2.6.1, if any of the following occurs:
        -the timer T3216 expires;
        -the MS detects any combination of the authentication failures: "MAC failure", "invalid SQN",
        and "GSM authentication unacceptable", during three consecutive authentication challenges.
        The authentication challenges shall be considered as consecutive only, if the authentication
        challenges causing the second and third authentication failure are received by the MS, while
        the timer T3214 or T3216 started after the previous authentication failure is running. */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6�汾�Ժ��������μ�Ȩʧ��UE������Ϊ��Ȩʧ�� */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        /* �˴�ʵ��ԭ���ο�R5Э���������μ�Ȩʧ��UE������Ϊ��Ȩʧ�� */
        if ((PS_PTL_VER_R5  >= cVersion)
         && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;
            Mm_TimerStart(MM_TIMER_T3214);
        }
    }
    /* else */
    else if (AGENT_AUTH_FAIL_SQN == g_AgentUsimAuthCnf.ucFailureCause)
    {
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE;
        Msg.MmIeAuthFailPara.ucLength =
             g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength;
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        PS_MEM_CPY(Msg.MmIeAuthFailPara.aucAuthFailPara,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucFailPara, 14);
        /* Modified by ��־�� 2004.10.23 end */
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* ����AUTHENTICATION FAILURE               */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6�汾�Ժ��������μ�Ȩʧ��UE������Ϊ��Ȩʧ�� */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if ((PS_PTL_VER_R5          >= cVersion)
         && ((MM_CONST_NUM_3        == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_SQN_FAIL           == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_SQN_FAIL;
            Mm_TimerStart(MM_TIMER_T3216);
        }
    }
    else
    {
        /* �쳣���� */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;
        Mm_ComMsgAuthFailSnd(&Msg);

        MM_WARN_LOG(
                   " \nMM:UMTS AUTH RESULT IS NOT EXPECTED!\r " );

    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              Msg.MmIeRejCause.ucRejCause);

}


/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnf
  Function: �յ�USIM������AGENT_USIM_AUTHENTICATION_CNF�Ĵ���
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.  ��־��     2005.01.27  007037 for MM
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnf()
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);                                       /* ֹͣ����TIMER                            */
    /* Mm_TimerStop(MM_TIMER_PROTECT); */
    if ( AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst )
    {                                                                           /* USIM�Ľ���Ƿ�ɹ�                       */
        Mm_ComAuthenRcvUsimCnfSuccess();
    }
    else
    {
        Mm_ComAuthenRcvUsimCnfFail();
    }
}

/*******************************************************************************
  Module:   Mm_ComRejectCause4
  Function: �յ�ԭ��ֵΪ#4�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.12  �°�����
  2.  ��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 201112��16��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2011111403722,����ģʽI CSע��ʧ��#4ʱ,û�з���ע��,����CSҵ�񲻿���
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_ComRejectCause4()
{
    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                  /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause4:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* �����־λ                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    Mm_ComUpdateUsimFileReq();


    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_ATTEMPTING_TO_UPDATE;      /* �����ͷ�RR����ʱ������״̬             */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR
                             );                                                 /* ��¼���̺�ԭ��ֵ                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause4:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComRejectCause6
  Function: �յ�ԭ��ֵΪ#4�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.12  �°�����
  2.  ��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause6()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause6:INFO: MmServiceState is MM_NO_IMSI");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* ���ø���״̬                             */

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* �����־λ                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);

    Mm_ComUpdateUsimFileReq();

    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* �����ͷ�RR����ʱ������״̬             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME
                             );                                                 /* ��¼���̺�ԭ��ֵ                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/***********************************************************************
 *  MODULE   : Mm_T3240Expire
 *  FUNCTION : T3240���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-11      �°�����
       2.  s46746     05-11-24      �޸�
 ************************************************************************/
VOS_VOID Mm_T3240Expire(
                        VOS_VOID
                    )
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3240);
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* ��¼Ǩ��֮ǰ��״̬                       */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /*Mm_SndRrAbortReq(RRC_ABORT_CS_SIGN_CONN); */                                  /* ��RRC����RRMM_ABORT_REQ(CS��)            */

    /* if ( MM_LU_PROC != g_MmGlobalInfo.ucProc ) */
    /* {                            */                                          /* �������LU����                           */
    /*     Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
    /* } */
    Mm_TimerStart(MM_TIMER_T3240);
    return;
}

/***********************************************************************
 *  MODULE   : Mm_T3230Expire
 *  FUNCTION : T3230���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��      03-12-11  �°�����

       2.��    ��   : 2011��7��14��
         ��    ��   : zhoujun 40661
         �޸�����   : ����MML_CTX�е�ҵ�����״̬
       3.��    ��   : 2012��10��29��
         ��    ��   : z00161729
         �޸�����   : DTS2012083102536:֧��cc�����ؽ�
       4.��    ��   :2013��9��12��
         ��    ��   :z00161729
         �޸�����   :DTS2013082903019:֧��ss�ط�����
       5.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_T3230Expire(
                        VOS_VOID
                    )
 {
    VOS_UINT8   i = 0;                                                              /* ѭ����������                             */

    Mm_TimerStop(MM_TIMER_T3230);

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF != g_MmGlobalInfo.ucState )
    {                                                                           /* �����ؽ�����                             */
        switch ( g_MmGlobalInfo.ucMMConnEstingPD )
        {                                                                       /* ȷ�����ĸ�PD������MM����                 */
        case MM_IE_PD_CALL_CONTROL:

            /* CCҪ������MM����                       */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);            /* ֪ͨCC,MM���ӽ���ʧ��                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* ������ڽ���MM���ӵı�־                 */
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                      /* SSҪ������MM����                       */
            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* ������ڽ���MM���ӵı�־                 */
            break;
        case MM_IE_PD_SMS_MSG:                                                  /* SMSҪ������MM����                      */
            Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);              /* ֪ͨSMS,MM���ӽ���ʧ��                   */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* ������ڽ���MM���ӵı�־                 */
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_T3230Expire:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
            break;
        }
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* ����û�����ڽ���������                   */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;                                                      /* ������ڽ�����MM���ӵı�־               */
    if ( ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
    {                                                                           /* û��MM���Ӵ���                           */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* ��¼Ҫ�����״̬                         */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* ��¼���̺�ԭ��ֵ                         */

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* ����TIMER3240                            */
    }
    else if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF ==
        g_MmGlobalInfo.ucState )
    {                                                                           /* �ؽ�����                                 */
        for ( i = 0; i < MM_CONST_NUM_7; i++ )
        {                                                                       /* �ؽ���MM����                             */
            /*lint -e701*/
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & ( 0x01 << i ) ) )
            {
                /* ��TI��MM����ʧЧ                         */
                Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);           /* ֪ͨCC,MM���ӽ���ʧ��                    */
            }
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & ( 0x01 << i ) ) )
            {
                /* ��TI��MM����ʧЧ                         */
                Mm_SndCcRelInd( ( i + 8 ),
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);                          /* ֪ͨCC,MM���ӽ���ʧ��                    */
            }
            /*lint +e701*/
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;    /* �����־λ                               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;    /* �����־λ                               */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* WAIT_FOR_NETWORK_COMMAND֮������״̬   */
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* ����TIMER3240                            */
    }
    else
    {                                                                           /* �����ؽ����Ҳ��ǽ�����һ��MM����         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );                                     /* ����Ƿ��б�������Ҫ������MM����         */
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_IDLE_NORMAL_SERVICE ״̬�£�CC ESTREQ FLAG ΪTRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2010��09��02��
   ��    ��   : w00167002
   �޸�����   : ���ⵥ�ţ�DTS2010090101612,�ض���G�󣬵��������ǽ������Ǻõ�
 3.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                          /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */
    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* ���ú�������                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* ���ú���TI                               */
    if ( MMCC_MO_NORMAL_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulCallType )
    {                                                               /* ��������                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* ���CM SERVICE REQUEST�ṹ��             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_FALSE;                             /* ��������                                 */
    }
    else
    {                                                               /* ��������                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* ���CM SERVICE REQUEST�ṹ��             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_TRUE;                              /* ��������                                 */
    }
    pucCmSvcReq =
        Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );       /* ���CM SERVICE REQUEST ��Ϣ              */
    if ( VOS_NULL_PTR == pucCmSvcReq )
    {                                                               /* ��Ϣ����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                     /* ����                                     */
    }
    else
    {                                                               /* ��Ϣ�����ɹ�                             */
        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {                                                           /* ��������                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL,
                MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* ������Ϣ                                 */
        }
        else
        {                                                           /* ��������                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* ������Ϣ                                 */
        }
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );             /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
        if ( MM_TRUE == ucLUFlg )
        {
            /* ��LU����øú���                         */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                            /* ��¼���ڽ�����MM����                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* ��¼���ڽ�����MM���ӵ�PD                 */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* ��������TIMER                            */
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_IDLE_NORMAL_SERVICE ״̬�£�SS ESTREQ FLAG ΪTRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 4.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                          /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI���Ϸ�                                 */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE,
            &CmSvcReq);                                             /* ���CM SERVICE REQUEST�ṹ��             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* ���CM SERVICE REQUEST ��Ϣ              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* ��Ϣ����ʧ��                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* ����                                     */
        }
        else
        {                                                           /* ��Ϣ�����ɹ�                             */
            Mm_SndRrEstReq(
                RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                MM_FALSE, usMsgSize, pucCmSvcReq );                 /* ������Ϣ                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );         /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            RcvXXEstReq.ulTransactionId;                            /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD =
            MM_IE_PD_NON_CALL_RLT_SS_MSG;                           /* ��¼���ڽ�����MM���ӵ�PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* ��������TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_IDLE_NORMAL_SERVICE ״̬�£�SMS ESTREQ FLAG ΪTRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                          /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI���Ϸ�                                 */
        Mm_SndSmsRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* ֪ͨSMS����ʧ��                          */
    }
    else
    {                                                               /* TI�Ϸ�                                   */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE,
            &CmSvcReq);                                             /* ���CM SERVICE REQUEST�ṹ��             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* ���CM SERVICE REQUEST ��Ϣ              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* ��Ϣ����ʧ��                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, ":WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* ����                                     */
        }
        else
        {                                                           /* ��Ϣ�����ɹ�                             */
            Mm_SndRrEstReq(
               RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
               MM_FALSE,
               usMsgSize, pucCmSvcReq );                            /* ������Ϣ                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );          /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            RcvXXEstReq.ulTransactionId;                            /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* ��¼���ڽ�����MM���ӵ�PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* ��������TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_IDLE_NORMAL_SERVICE ״̬����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   : 2012��09��01��
   ��    ��   : s46746
   �޸�����   : DTS2012090405619:DCM�ⳡ����,����RAU��������ӦѰ��������abort
 4.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 5.��    ��   : 2013��9��12��
   ��    ��   : w00242748
   �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                G��ԭС��ʱ��LAU
 6.��    ��   : 2015��3��20��
   ��    ��   : w00167002
   �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                ���з�װ��
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* �еȴ���CC��������Ҫ������MM����         */
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* û�еȴ���CCҪ������MM����             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_IDLE_ATTEMPTING_TO_UPDATE ״̬����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 4.��    ��   : 2013��07��05��
   ��    ��   : l65478
   �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ
 5.��    ��   : 2013��9��12��
   ��    ��   : w00242748
   �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                G��ԭС��ʱ��LAU
  6.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  8.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU   CmSvcReq;                                              /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16               usMsgSize = 0;                                         /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8               *pucCmSvcReq = 0;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

    RRMM_PAGING_IND_STRU     stWPagingMsg;
    GRRMM_PAGING_IND_ST      stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* �ɵȴ���CC��������Ҫ������MM����         */
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulCallType )
        {                                                               /* �ǽ�������                               */
            g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* ���ú�������                             */
            g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
                ulTransactionId;                                        /* ���ú���TI                               */
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* ��¼�յ���������ʱ��״̬                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                   /* ���CM SERVICE REQUEST�ṹ��             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                              /* ��������                                 */
            pucCmSvcReq =
                Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* ���CM SERVICE REQUEST ��Ϣ              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                           /* ��Ϣ����ʧ��                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                 /* ����                                     */
            }
            else
            {                                                           /* ��Ϣ�����ɹ�                             */
                if ( MM_TRUE == ucLUFlg )
                {                                                       /* ��LU����øú���                         */
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
                }
                Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                    usMsgSize, pucCmSvcReq );                           /* ������Ϣ                                 */
                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* ��������TIMER                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucMMConnEstingTI =
                    (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId;                        /* ��¼���ڽ�����MM����                     */
                g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* ��¼���ڽ�����MM���ӵ�PD                 */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            }
        }
        else
        {
            /* ����������                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                      /* ֪ͨCCָ��������MM���ӽ���ʧ��           */

            if ( MM_FALSE == ucLUFlg )
            {
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                        /* ֪ͨSMS����ʧ��                          */
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* û�еȴ���CCҪ������MM����             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_CONNECTION_ACTIVE CC EST FLAGΪ TRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   : 2014��5��28��
       ��    ��   : z00234330
       �޸�����   : covertity�޸�
     5.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(&CmSvcReq, 0x00, sizeof(CmSvcReq));
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */

    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* ���ú�������                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* ���ú���TI                               */
    /*lint -e701*/
    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        aucMMConnExtFlg[1] & ( 0x01 <<
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId - 8 ) ) ) )
        )
    {
        /* Ҫ������MM�����Ѿ����ڻ����޷���״̬   */
        Mm_SndCcRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* ֪ͨCCָ��������MM���ӽ���ʧ��           */
    }
    /*lint +e701*/
    else
    {                                                               /* Ҫ������MM���Ӳ�����                   */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
                                                                    /* ��¼�յ���������ʱ��״̬                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* ������������                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* ���CM SERVICE REQUEST�ṹ��             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_FALSE;                         /* ��������                                 */
        }
        else if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* ���н�������                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* ���CM SERVICE REQUEST�ṹ��             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg = MM_TRUE;                      /* ��������                                 */
        }
        else
        {
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                            /* �����෢�ͽ���MM���ӵ�����               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI = (VOS_UINT8)g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq
            .ulTransactionId;                                       /* ��¼���ڽ�����MM����                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* ��¼���ڽ�����MM���ӵ�PD                 */
        Mm_TimerStart(MM_TIMER_T3230);                              /* ����TIMER3230                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_CONNECTION_ACTIVE SS EST FLAGΪ TRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI���Ϸ������޷���״̬   */

        /* ֪ͨSSָ��������MM���ӽ���ʧ��           */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* Ҫ������MM�����Ѿ�����                 */

        /* ��¼�յ���������ʱ��״̬                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* ��MM���ӽ����ɹ�                         */
        Mm_SndSsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId,MMSS_EST_SUCCESS);
    }
    else
    {
        /* ���CM SERVICE REQUEST�ṹ��             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);
        /* �����෢�ͽ���MM���ӵ�����               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId);
        /* ��¼���ڽ�����MM���ӵ�PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
        /* ����TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* ��¼Ǩ��֮ǰ��״̬                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* ״̬Ǩ��                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_CONNECTION_ACTIVE SMS EST FLAGΪ TRUE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
    2.��    ��   :2013��9��12��
      ��    ��   :z00161729
      �޸�����   :DTS2013082903019:֧��ss�ط�����
    3.��    ��   :2014��9��24��
      ��    ��   :s00217060
      �޸�����   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI���Ϸ������޷���״̬   */

        /* ֪ͨSMSָ��������MM���ӽ���ʧ��           */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* Ҫ������MM�����Ѿ�����                 */

        /* ��¼�յ���������ʱ��״̬                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* ��MM���ӽ����ɹ�                         */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
    }
    else
    {
        /* ���CM SERVICE REQUEST�ṹ��             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);
        /* �����෢�ͽ���MM���ӵ�����               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
        /* ��¼���ڽ�����MM���ӵ�PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;
        /* ����TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* ��¼Ǩ��֮ǰ��״̬                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* ״̬Ǩ��                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�: MM_CONNECTION_ACTIVE ״̬����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE(VOS_VOID)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* �еȴ���CC��������Ҫ������MM����         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        /* �еȴ���SS��������Ҫ������MM����         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        /* �еȴ���SMS��������Ҫ������MM����         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_ComCheckDelayMmConn_OtherStateHandling_CC
 ��������  : �ɵȴ���CC��������Ҫ������MM����
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_CC(
    VOS_UINT8                           ucLUFlg
)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                                  /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

    if ( MMCC_EMERGENCY_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType )
    {                                                               /* �ǽ�������                               */
        g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* ���ú�������                             */
        g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId;                                        /* ���ú���TI                               */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* ��¼�յ���������ʱ��״̬                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* ���CM SERVICE REQUEST�ṹ��             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                          /* ��������                                 */
        pucCmSvcReq =
            Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* ���CM SERVICE REQUEST ��Ϣ              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* ��Ϣ����ʧ��                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* ����                                     */
        }
        else
        {                                                           /* ��Ϣ�����ɹ�                             */
            if ( MM_TRUE == ucLUFlg )
            {                                                       /* ��LU����øú���                         */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            }
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* ������Ϣ                                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* ��������TIMER                            */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId;                        /* ��¼���ڽ�����MM����                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* ��¼���ڽ�����MM���ӵ�PD                 */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
    }
    else
    {
        if ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
        {
            /* ����������                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                      /* ֪ͨCCָ��������MM���ӽ���ʧ��           */
        }
        else if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
              && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
        {
            /* �������ڱ���ԭ��ֵ12��������Ʒ���״̬���Գ��Ժ����ط�*/
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
        }
        else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
        }
        else
        {
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                      NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                      /* ֪ͨCCָ��������MM���ӽ���ʧ��           */
        }

        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }
}

/*****************************************************************************
 �� �� ��  : Mm_ComCheckDelayMmConn_OtherStateHandling_SS
 ��������  : �ɵȴ���SS��������Ҫ������MM����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* �������ڱ���ԭ��ֵ12��������Ʒ���״̬���Գ���ss�ط� */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}

/*****************************************************************************
 �� �� ��  : Mm_ComCheckDelayMmConn_OtherStateHandling_SMS
 ��������  : �ɵȴ���SS��������Ҫ������MM����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SMS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* �������ڱ���ԭ��ֵ12��������Ʒ���״̬���Գ���ss�ط� */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_Other_State_Handling
 *  FUNCTION : Mm_ComCheckDelayMmConn���������Ӷ�:
                      MM_IDLE_LIMITED_SERVICE,
                      MM_IDLE_LOCATION_UPDATE_NEEDED,
                      MM_IDLE_NO_IMSI״̬����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   : 2012��09��01��
   ��    ��   : s46746
   �޸�����  : DTS2012090405619:DCM�ⳡ����,����RAU��������ӦѰ��������abort
 4.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 5.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 6.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_Other_State_Handling(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU        stWPagingMsg;
    GRRMM_PAGING_IND_ST         stGPagingMsg;

    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_CC(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SS();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SMS();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* û�еȴ���CCҪ������MM����             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn
 *  FUNCTION : �ڽ�����̬ʱ����Ƿ��б�������Ҫ������MM����
 *  INPUT    : VOS_UINT8   ucLUFlg          �Ƿ���LU��������õĸú���
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��        03-12-11    �°�����
 *     2.  x51137        07-03-10    A32D09201
       3.��    ��   : 2007��04��13��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ��:A32D10663
       4.��    ��   : 2007��07��31��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ��:A32D12640
       5.��    ��   : 2008��8��13��
         ��    ��   : l0010747
         �޸�����   : ���ⵥ��:AT2D04996/AT2D05037
       3.��    ��   : 2012��3��07��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
       4.��    ��   : 2012��09��01��
         ��    ��   : s46746
         �޸�����  : DTS2012090405619:DCM�ⳡ����,����RAU��������ӦѰ��������abort
       5.��    ��   : 2012��10��29��
         ��    ��   : z00161729
         �޸�����   : DTS2012083102536:֧��cc�����ؽ�
       6.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����  :DTS2013082903019:֧��ss�ط�����
       7.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
 ************************************************************************/

VOS_VOID Mm_ComCheckDelayMmConn(
                            VOS_UINT8   ucLUFlg                                     /* �Ƿ���LU��������õĸú���               */
                    )
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId ) ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId )) && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {
        /* TI���Ϸ�                                 */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);        /* ֪ͨCC����ʧ��                           */
    }
    else
    {                                                                           /* TI�Ϸ�                                   */
        switch ( g_MmGlobalInfo.ucState )
        {                                                                       /* ��ǰ״̬                                 */
        case MM_IDLE_NORMAL_SERVICE:
            Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            break;
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
            Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(ucLUFlg);
            break;
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_NO_IMSI:
            Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            break;
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
            if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
            {
                Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            }
            else
            {
                Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            }
            break;
        case MM_CONNECTION_ACTIVE:
            Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: g_MmGlobalInfo.ucState Abnormal");
            break;
        }
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    return;
}
/***********************************************************************
 *  MODULE   : Mm_ComRrConnRelChk
 *  FUNCTION : �ж��Ƿ���Ҫ֪ͨMMC���������ͷ�
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��        2005.01.31    �°�����
       2.��    ��   : 2013��2��4��
         ��    ��   : w00176964
         �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 ************************************************************************/
VOS_UINT8 Mm_ComRrConnRelChk()
{
    if ( ( ( MM_MM_CONN_PROC != g_MmGlobalInfo.ucProc ) ||
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR !=
        g_MmGlobalInfo.usCauseVal ) )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
    {                                                                           /* ԭ��ֵ����4�������̲���MM����û�л���    */
        return MM_TRUE;
    }
    else
    {
        if (( MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc ) &&
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR ==  g_MmGlobalInfo.usCauseVal )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
        {                                                                       /* û�л���                                 */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
            if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
            {                                                                   /* �ж��Ƿ�ΪA+Iģʽ                        */
                return MM_TRUE;
            }
        }
    }
    return MM_FALSE;
}
/***********************************************************************
 *  MODULE   : Mm_ComTiChk
 *  FUNCTION : TI�ĺϷ��Լ��
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��     2005.01.31  �°�����
       2.  ��־��  2005.03.09  MM_Review_HW_BUG_027��Ӧ
 ************************************************************************/
VOS_UINT8 Mm_ComTiChk()
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId )
        ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId ))
        && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {                                                                           /* TI���Ϸ�                                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                                                                    = MM_FALSE;

        NAS_MM_UpdateCsServiceBufferStatusFlg();
        return MM_FALSE;
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI���Ϸ�                                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                      .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI���Ϸ�                                 */
            /*return MM_FALSE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                       .RcvXXEstReq.ucFlg = MM_FALSE; */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}
/***********************************************************************
 *  MODULE   : Mm_ComSigRelForDelayMmConnRej
 *  FUNCTION : MM�ܾ��ϲ������֪ͨMMC���������ͷ�
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��        2005.01.31    �°�����
       2.  ��    ��   :  2007��10��06��
           ��    ��   :  l65478
           �޸�����   :  ���ⵥ�ţ�A32D12977
************************************************************************/
VOS_VOID Mm_ComSigRelForDelayMmConnRej()
{
    switch ( g_MmGlobalInfo.ucState )
    {                                                                           /* ��ǰ״̬                                 */
    case MM_IDLE_NORMAL_SERVICE:
        break;
    case MM_CONNECTION_ACTIVE:
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_LOCATION_UPDATE_NEEDED:
    case MM_IDLE_NO_IMSI:
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* �ɵȴ���CC��������Ҫ������MM����         */
            if ( MMCC_EMERGENCY_CALL ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType )
            {                                                                   /* �ǽ�������                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {                                                                   /* ����������                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {

        }
        break;
    default:
        break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_FillMobileID
 ��������  : ����MM��ȫ�ֱ���ȡֵ�����MobileID��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_FillMobileID(
    MM_MOBILE_ID_STRU                  *pstMobileID
)
{
    VOS_UINT8                          *pucIMSI;

    pstMobileID->ucMsIdFlg = g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg;

    PS_MEM_CPY(pstMobileID->aucImei,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImei,
               sizeof(pstMobileID->aucImei));

    PS_MEM_CPY(pstMobileID->aucImeisv,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv,
               sizeof(pstMobileID->aucImeisv));

    PS_MEM_CPY(pstMobileID->aucTmsi,
               NAS_MML_GetUeIdTmsi(),
               sizeof(pstMobileID->aucTmsi));

    pucIMSI = NAS_MML_GetSimImsi();

    pstMobileID->Imsi.ucLength = pucIMSI[0];

    PS_MEM_CPY(pstMobileID->Imsi.aucImsi,
               pucIMSI + 1,
               sizeof(pstMobileID->Imsi.aucImsi));


    return;
}

/*******************************************************************************
  Module:   Mm_ComLuOnly
  Function: A+IIģʽ����Bģʽ�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.16  �°�����
  2.  ��־��     2005.01.27  007037 for MM
  3.��    ��   : 2006��11��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D06442
  4.��    ��   : 2007��05��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D10713
  5.��    ��   : 2007��12��15��
    ��    ��   : l00107747
    �޸�����   : ���ⵥ��:A32D13897
  6.��    ��   : 2007��12��21��
    ��    ��   : l00107747
    �޸�����   : ���ⵥ��:A32D13951
  7.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  8.��    ��   : 2008��11��22��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D06900,mmע��״̬�޸�
  9.��    ��   : 2009��05��11��
    ��    ��   : h44270
    �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
  10.��    ��   : 2011��07��14��
     ��    ��   : z00161729
     �޸�����   : V7R1 phase IIȫ�ֱ��������޸�
  11.��    ��   : 2011��7��22��
     ��    ��   : h44270
     �޸�����   : V7R1 PhaseII�׶ε�����ע������
  12.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  13.��    ��   : 2011��7��26��
     ��    ��   : l00130025
     �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
  14.��    ��   : 2011��04��23��
     ��    ��   : f00179208
     �޸�����   : ���ⵥ�ţ�DTS2011032903294,[�����������������翨�����������ٻ�ԭС����UEֻ��������T3212������û�з���LAU
  15.��    ��   : 2011��12��17��
     ��    ��   : w00166186
     �޸�����   : dts2011120603107����һ����������С����ѡ��һ����֧��GPRS��С������ͣ����LAU
  16.��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
  17.��    ��   : 2012��2��15��
     ��    ��   : w00167002
     �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������CSFB��pagingʱ����LAU��Ҳ��Ҫ
                   Я��FOLLOW ON ��־��
                   TS24008 4.5.1.3.4 Paging response for CS fallback
                   NOTE: For the race condition when the mobile station has a CM
                   application request pending, the mobile station also indicates
                   that it has a follow-on request pending.
  18.��    ��   : 2012��9��24��
     ��    ��   : s46746
     �޸�����   : ���ⵥ��DTS2012090801459������λ�ø���ʱֹͣT3212
  19.��    ��   : 2012��10��29��
     ��    ��   : z00161729
     �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  20.��    ��   : 2012��12��22��
     ��    ��   : l65478
     �޸�����   : DTS2012122103936 �����������ʱMM״̬Ǩ�ƴ���
  21.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  22.��    ��   : 2013��7��25��
     ��    ��   : w00242748
     �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                  �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                  rau req�д�follow on��־,����ȷЭ������
  23.��    ��   : 2013��9��12��
     ��    ��   : z00161729
     �޸�����   : DTS2013082903019:֧��ss�ط�����
  24.��    ��   : 2014��4��2��
     ��    ��   : w00176964
     �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  25.��    ��   : 2014��5��21��
     ��    ��   : w00167002
     �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                MMɾ����SOR�����⴦��
  26.��    ��   : 2014��6��4��
     ��    ��   : w00167002
     �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
  27.��    ��   : 2014��6��13��
     ��    ��   : w00242748
     �޸�����   : DSDS ������
  28.��    ��   :2014��9��24��
     ��    ��   :s00217060
     �޸�����   :for cs_err_log
  29.��    ��   : 2014��11��26��
     ��    ��   : w00167002
     �޸�����   : DTS2014092806342:��L�±���CSFB��GSM�󣬽���ʧ�ܣ�����ѡ���µ�λ����
                  ����LAUʱ��û��Я��CSMT��־���ڻ�Ϊ�����ϣ�������·�SETUP������
                  �ɹ����ڷǻ�Ϊ�����ϣ�����δ�·�SETUP���޸�ΪЯ��CSMT��־��
  30.��    ��   : 2015��1��26��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  31.��    ��   : 2015��6��30��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
  32.��    ��   : 2015��8��13��
     ��    ��   : l00289540
     �޸�����   : User_Exp_Improve�޸�
  33.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*******************************************************************************/

VOS_VOID Mm_ComLuOnly()
{
    MM_MSG_LU_REQ_STRU     Msg;

    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    VOS_UINT32                          ulCsLastSucLac;

    VOS_UINT32                          ulUsimDoneGsmCsAuthFlg;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo   = NAS_MML_GetRplmnCfg();

    ulCsLastSucLac = NAS_MML_GetCsLastSuccLac();
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstMsCapability = NAS_MML_GetMsCapability();
    ucSimType       = NAS_MML_GetSimType();

    ulUsimDoneGsmCsAuthFlg              = NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth();


    /* ����LAUǰ������Ա�־λ */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return;
    }
    if ( VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        if (VOS_TRUE == NAS_MM_IsNeedDeactiveIsrLauInit())
        {
            /* ȥ����ISR,����TINֵΪP-TMSI */
            NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
            NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
        }

        Mm_TimerStop(MM_TIMER_T3211);
        Mm_TimerStop(MM_TIMER_T3213);

        /* 4.4.4.1 Location updating initiation by the mobile station
           Any timer used for triggering the location updating procedure
           (e.g. T3211, T3212) is stopped if running. */
        Mm_TimerStop(MM_TIMER_T3212);



        Msg.MmIeLuType.ucLUT =
            g_MmGlobalInfo.LuInfo.ucLuType & MM_IE_LU_TYPE_LUT_MASK;            /* ����LU TYPE                              */
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* �б�����MM����                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI�Ϸ�                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* ����FOR                                  */
            }
            else
            {
                /* TI���Ϸ�, ֪ͨCC����ʧ�� */
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* ����û�л����MM����                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* ����FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {                                                                       /* �б�����MM����                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI�Ϸ�                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* ����FOR                                  */
            }
            else
            {                                                                   /* TI���Ϸ�                                 */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* ����û�л����MM����                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* ����FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {                                                                       /* �б�����MM����                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI�Ϸ�                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* ����FOR                                  */
            }
            else
            {                                                                   /* TI���Ϸ�                                 */
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                            /* ֪ͨCC����ʧ��                           */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                    ucFlg = MM_FALSE;                                           /* ����û�л����MM����                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* ����FOR                                  */
            }
        }
        else
        {                                                                       /* û�б�����MM����                         */
            Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                              /* ����FOR                                  */
        }

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        /* SIM����W�½���CS ע��ʱ�������ǰLAI��Ч����CKSNҲ��Ϊ��Ч */
        if ( ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
           && (NAS_MML_SIM_TYPE_SIM       == ucSimType)
           && ((MM_INVALID_LAI            == ulCsLastSucLac)
            || (0x0                       == ulCsLastSucLac)))
          || (VOS_TRUE                    == ulUsimDoneGsmCsAuthFlg) )
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        Msg.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();             /* ����CKSN                                 */
        Msg.MmIeLAI.IeLai.PlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
        Msg.MmIeLAI.IeLai.PlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        Msg.MmIeLAI.IeLai.ulLac        = NAS_MML_GetCsLastSuccLac();
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

        if ( MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0] )
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_TRUE;                                  /* ����ClassMark For UMTS����               */
            MM_Fill_IE_ClassMark2(Msg.MmIeMsClsMskFrUMTS.aucClassmark2);
        }
        else
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_FALSE;                                 /* ����ClassMark For UMTS������             */
        }


        /* ����LAUʱ�����ATTEMPT UPDATE LAI��Ϣ */
        NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

        g_MmMsgLuRjct.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_NULL;

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;

        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING);

        Mm_ComMsgLuReqSndOfEstReq(&Msg);                                        /* ������Ϣ                                 */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuOnly:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

        NAS_EventReport(WUEPS_PID_MM,NAS_OM_EVENT_LOCATION_UPDATE_REQ,
                        &g_MmGlobalInfo.LuInfo.ucLuType,NAS_OM_EVENT_LAU_REQ_LEN);
    }
}

/*******************************************************************************
  Module:   Mm_ComInit
  Function: MM ��ʼ��
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��      2003.12.23   �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3.  s46746     2005.09.05   for HSS4100 V200R001
  4.  h44270     2009.01.22   ���ⵥ�ţ�AT2D08559
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2011��12��29��
    ��    ��   : l00130025
    �޸�����   : DTS2011082201679/DTS2011121504358,�л�ģʽ�����˺�W/G��ע��״̬û����NASͬ��
  7.��    ��   : 2012��2��14��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 ֧��CSFB�����޸�
  7.��    ��   : 2012��05��21��
    ��    ��   :  z40661
    �޸�����  :  DTS2012052308001:��L��ѡ��G�󷴸�����LAU
  8.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  9.��    ��   : 2012��09��21��
    ��    ��   : z00161729
    �޸�����  : DTS2012090706407 :����lau accept��Я����ϵͳ��Ϣ�в�ͬ��non broadcast laiʱ��Ҫ����lau
 10.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 11.��    ��   : 2012��12��22��
    ��    ��   : l65478
    �޸�����   : DTS2012122103936 �����������ʱMM״̬Ǩ�ƴ���
 12.��    ��   : 2013��05��21��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

 13.��    ��   : 2013��7��4��
    ��    ��   : w00167002
    �޸�����   : SVLTE BBIT��CS detach������ʱ������Ϊ��ѭ����ʱ��

 14.��    ��   : 2013��9��4��
    ��    ��   : w00167002
    �޸�����   : DTS2013090403562:NAS��ʱ��������Ҫ����32K��ʱ������MM/MMA/SMS
                 ģ���ѭ����ʱ���޸�Ϊ��ѭ����ʱ����
 15.��    ��   : 2013��7��25��
   ��    ��   : w00242748
   �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                rau req�д�follow on��־,����ȷЭ������
 16.��    ��   : 2013��11��01��
    ��    ��   : l65478
    �޸�����   : DTS2013103107433:��������CSFB HO��GU���յ�ϵͳ��Ϣǰ�ȷ�����ҵ��
 17.��    ��   : 2013��9��25��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseII ��Ŀ�޸�:����SRVCC���̱�ǳ�ʼ��
 18.��    ��   : 2014��4��175��
    ��    ��   : s00246516
    �޸�����   : DTS2014041700472:ʹ��2G SIM����PAD��̬�ϳ��ּ�Ȩ������ܾ�
 19.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
  20.��    ��   : 2014��8��14��
     ��    ��   : z00161729
     �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau
  21.��    ��   : 2015��5��5��
    ��    ��   : w00167002
    �޸�����   : csmt�޸�
  22.��    ��   : 2015��6��15��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
  23.��    ��   : 2015��8��13��
     ��    ��   : l00289540
     �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Mm_ComInit ()
{

    VOS_UINT8                           i;
    VOS_UINT32                          ulHoWaitSysinfoTimeLen;
    ulHoWaitSysinfoTimeLen = NAS_MML_GetHoWaitSysinfoTimerLen();

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    PS_MEM_SET( &gstMmTimer[0], 0, ( MM_TIMER_MAX * sizeof( MM_TIMER_STRU ) ) );/* ��ʼ��                                   */
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    PS_MEM_SET( &g_MmGlobalInfo, 0, sizeof( MM_GLOBAL_CTRL_STRU ) );           /* ��ʼ��                                   */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    PS_MEM_SET(&gstMmSuspendMsgQue, 0, sizeof(MM_SUSPEND_MSG_BUF_ST));        /* ��ʼ��                                   */
    PS_MEM_SET(&gstMmTimerSuspend, 0, sizeof(MM_TIMER_ST));                   /* ��ʼ��                                   */

    g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = 0;

    gstMmTimerSuspend.ulTimerLength     = MM_TIMER_PROTECT_SUSPEND_VALUE;

    PS_MEM_SET(&g_MmMsgLuAccpt, 0, sizeof(MM_MSG_LU_ACCPT_STRU));
    PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

    PS_MEM_SET(&g_AgentUsimAuthCnf, 0, sizeof(MM_USIM_AUTHENTICATION_CNF_STRU));

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

    g_MmGlobalInfo.ucSysInfoFlg =  MM_FALSE;

    g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucFollowOnFlg         = MM_NO_FOLLOW_ON;
    g_MmGlobalInfo.ucCsSigConnFlg        = MM_CS_SIG_CONN_ABSENT;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComInit:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_ABSENT");
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* û�����ڽ�����MM����                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* û�����ڽ�����MM����                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI  =
        NO_MM_CONN_ESTING;                                                      /* û�����ڽ�����MM����                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg =
        MM_FALSE;
    g_MmGlobalInfo.ucMMConnEstingPD                                 =
        NO_MM_CONN_ESTING;

    g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc = MM_WasRrEstReq;
    g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc = As_RrRelReq;
    g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc = MM_WasRrDataReq;

    g_NasMmImportFunc.ucFuncEnvironment             = NAS_MML_NET_RAT_TYPE_WCDMA;
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    g_MmGlobalInfo.ucLikeB = MM_FALSE;
    g_MmGlobalInfo.ucAttDelay = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_NOPRESENT;
    g_MmSubLyrShare.MmShare.ucCsSpecificFlg = MM_SPECIFIC_OFF;

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    {
        gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

        /* ����ʱ���޸�Ϊ��ѭ����ʱ�� */
        gstMmTimer[i].ucMode        = VOS_RELTIMER_NOLOOP;
    }

    /* ��ʼ��TIMER��ʱ�� */
    gstMmTimer[MM_TIMER_T3210].ulTimerLen = MM_TIMER_T3210_VALUE;
    gstMmTimer[MM_TIMER_T3211].ulTimerLen = MM_TIMER_T3211_VALUE;
    gstMmTimer[MM_TIMER_T3213].ulTimerLen = MM_TIMER_T3213_VALUE;
    gstMmTimer[MM_TIMER_T3214].ulTimerLen = MM_TIMER_T3214_VALUE;
    gstMmTimer[MM_TIMER_T3216].ulTimerLen = MM_TIMER_T3216_VALUE;
    gstMmTimer[MM_TIMER_T3218].ulTimerLen = MM_TIMER_T3218_VALUE;
    gstMmTimer[MM_TIMER_T3220].ulTimerLen = MM_TIMER_T3220_VALUE;

    gstMmTimer[MM_TIMER_T3230].ulTimerLen = MM_TIMER_T3230_VALUE;

    gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_AGENT].ulTimerLen =
                                    MM_TIMER_PROTECT_AGENT_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_DETACH].ulTimerLen =
                                    MM_TIMER_PROTECT_DETACH_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen
                                     = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;

    gstMmTimer[MM_TIMER_PROTECT_CC].ulTimerLen = MM_TIMER_PROTECT_CC_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_CCBS].ulTimerLen = MM_TIMER_PROTECT_CCBS_VALUE;
    gstMmTimer[MM_TIMER_DELAY_LU_GSM].ulTimerLen = MM_TIMER_DELAY_LU_GSM_VALUE;
    gstMmTimer[MM_TIMER_DELAY_CS_SERVICE_GSM].ulTimerLen = MM_TIMER_DELAY_CS_SERVICE_GSM_VALUE;

    gstMmTimer[MM_TIMER_WAIT_CONNECT_REL].ulTimerLen = MM_TIMER_WAIT_CONNECT_REL_VALUE;

    gstMmTimer[MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_CS_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;


    gstMmTimer[MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT].ulTimerLen = NAS_MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT_LEN_VALUE;

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-11, begin */
    gstMmTimer[MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerLen = MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_LEN_VALUE;
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-11, end */

    gstMmTimer[MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE].ulTimerLen = (VOS_UINT32)(NAS_MML_GetProtectMtCsfbPagingProcedureLen() * 1000);

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    gstMmTimer[MM_TIMER_T3242].ulTimerLen = MM_TIMER_T3242_VALUE;
    gstMmTimer[MM_TIMER_T3243].ulTimerLen = MM_TIMER_T3243_VALUE;
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;


    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat              = MM_AUTHEN_RAND_DIFFER;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType            = MM_CONST_NUM_2;

    g_T3211Flag = 0;
    g_MmGlobalInfo.ucMmServiceState = MMC_MM_NO_SERVICE;

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect        = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;


    g_MmSubLyrShare.MmShare.MmSuspendEvent              = MM_EVENT_ID_INVALID;


    /* ��ʼ��Ϊ���ӳٵ�LAU��־ */
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    g_MmGlobalInfo.enPreRatType                         = NAS_MML_NET_RAT_TYPE_BUTT;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg  = VOS_FALSE;

    NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
    NAS_MM_SetSrvccFlg(VOS_FALSE);

    NAS_MM_SetRcvSrvccCallInfoFlg(VOS_FALSE);
#endif
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, end */

    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

    NAS_MML_InitOldCampLai(NAS_MM_GetAllocT3212ValueLaiInfo());
    NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BUTT);

    NAS_MM_InitT3212Counter();

    g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246    = VOS_FALSE;

    return;                                                                     /* ����                                     */
}


VOS_VOID    Mm_Nop(VOS_VOID* pMsg)
{
}

/***********************************************************************
 *  MODULE   : Mm_ComStart
 *  FUNCTION : �յ�MMCMM_START_REQ�Ĺ�������
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.��־��      04-02-06  �°�����
       2.��    ��   : 2008��12��22��
         ��    ��   : o00132663
         �޸�����   : ���ⵥ��:AT2D07757,MM�������ػ�ԭС����������LU
       3.��    ��   : 2010��9��30��
         ��    ��   : ŷ���� 00132663
         �޸�����   : �������ⵥ��DTS2010092902368,TMSIֻ�ڵ�ЧPLMN����Ч

       4.��    ��   : 2011��7��13��
         ��    ��   : zhoujun 40661
         �޸�����   : SIM�����ݸ��µ�MML��
       5.��    ��   : 2012��2��22��
         ��    ��   : w00199382
         �޸�����   : B060��Ŀ��ֲ������
       6.��    ��   : 2014��4��2��
         ��    ��   : w00176964
         �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
************************************************************************/
VOS_VOID Mm_ComStart(
                 VOS_VOID
                 )
{

    VOS_UINT8                           i;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    VOS_UINT8                           ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsi;

    /*���ݿ�״̬��Ϣ������CS��Sim��״̬*/
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MML_SetSimCsRegStatus(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* SIM��Ч                                  */
        /* IMSI */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
           |= MM_MS_ID_IMSI_PRESENT;                                            /* ��Mobile ID���ڱ�־                      */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        /* ���ݵ�ǰ�洢��TMSI�Ƿ���Ч���趨�Ƿ����TMSI */
        ulInvalidCnt = 0;
        pucTmpTmsi = NAS_MML_GetUeIdTmsi();
        for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
        {
            if (NAS_MML_TMSI_INVALID == pucTmpTmsi[i])
            {
                ulInvalidCnt++;
            }
        }

        if ( ulInvalidCnt < NAS_MML_MAX_PTMSI_LEN )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
                |= MM_MS_ID_TMSI_PRESENT;

        }


        /* ������䵱ǰTMSI������ID */
        if ( MM_MS_ID_TMSI_PRESENT ==
              (MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg) )
        {
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        }
    }

    /* IMEI(SV) */
    pstMsCapability = NAS_MML_GetMsCapability();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEI_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0]
       = (VOS_UINT8)((pstMsCapability->aucImeisv[0] << 4) | 0x0f);

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEISV_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[0]
       = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0];

    for (i = MM_CONST_NUM_1; i < MM_CONST_NUM_8; i++ )
    {                                                                           /* �洢IMEI                                 */
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i]
           = (VOS_UINT8)((pstMsCapability->aucImeisv[2*i]<<4)
                       | pstMsCapability->aucImeisv[(2*i)-1]);
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[i]
           = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i];
    }
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[7] &= 0x0f;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8]
       = (VOS_UINT8)( pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1]
                   & 0x0f);
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8] |= 0xf0;




    /* Ϊ�˷�ֹʹ�ò��ԺŶαܹ�IMSI�ļ�飬ʹ���ܹ�ʹ��TMSI����ע�ᣬ��Ҫ
       ���з��������ж�����NV��������£�����Ŷ�TMSI��Ϊ��Ч
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    }


    Mm_SndMmcStartCnf();
}


/***********************************************************************
 *  MODULE   : Mm_ComToU2Handle
 *  FUNCTION : MM��U2�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-09  �°�����,�������
    2.  ��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
    3. ��    ��   : 2010��12��24��
       ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
    4.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    5.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
************************************************************************/

VOS_VOID Mm_ComToU2Handle()
{
    /* g_MmSubLyrShare.MmShare.ucUpdateSts = MM_UPDATE_STATUS_NOT_UPDATED; */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );                                                          /* ����MM��Ϣ                               */
    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* ����SIM������״̬                        */
    Mm_ComUpdateUsimFileReq();


    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE\r " );                     */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComToU2Handle:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
}


/***********************************************************************
 *  MODULE   : Mm_ComLuCauseHandle
 *  FUNCTION : MM��LU����ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucCause                  ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-09  �°�����,�������
    2.  s46746  2006-07-25  �������ⵥA32D05058�޸�
    3.��    ��   : 2006��11��22��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ�ţ�A32D07583
    4.��    ��   : 2007��05��11��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D10713
    5.��    ��   : 2007��06��01��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D1964
    6.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    7.��    ��   : 2011��7��28��
      ��    ��   : sunxibo 46746
      �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
    8.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    9.��    ��   :2013��9��12��
      ��    ��   :z00161729
      �޸�����  :DTS2013082903019:֧��ss�ط�����
    10.��    ��   : 2014��5��21��
       ��    ��   : w00167002
       �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                MMɾ����SOR�����⴦��
    11.��    ��   : 2014��6��4��
       ��    ��   : w00167002
       �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                    �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                    ������LAU.
                    ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                    DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                    �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                    ������LAU.
    12.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
 ************************************************************************/

VOS_VOID Mm_ComLuCauseHandle(VOS_UINT16 usCause)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.usCauseVal   = usCause;                            /* ��¼ԭ��ֵ                               */
    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:

        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* ���ø���״̬                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;
        Mm_ComUpdateUsimFileReq();


        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* ����LU COUNTERΪ0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* ���ø���״̬                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;   /* ����TMIS������                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* ����LU COUNTERΪ0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* ���ø���״̬                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }


        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* �ж�LU Counter�Ƿ�С��4                  */
            enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();
            if ( ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* �ж�LAI�Ƿ�δ�ı�,�Ҹ���״̬ΪU1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");

                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
            }
            else
            {
                if ( ( usCause >=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                    ( usCause <=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
                {                                                               /* �ж�ԭ��ֵ�Ƿ���retry��Χ��              */
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                 /* ����ucRetryFlgΪMM_TRUE                  */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                /* ����ucRetryFlgΪMM_FALSE                 */
                }

                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComToU2Handle();
                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
            }
        }
        else
        {
            if ( ( usCause >
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                ( usCause <
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
            {                                                                   /* �ж�ԭ��ֵ�Ƿ���retry��Χ��              */
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                     /* ����ucRetryFlgΪMM_TRUE                  */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                    /* ����ucRetryFlgΪMM_FALSE                 */
            }
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            Mm_ComToU2Handle();



            /* SOR������MMC����MM����LAU */
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);



            /*A32D10964==>*/
            if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
            {
                Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
                g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
                Mm_Cell_S0_E23(VOS_NULL_PTR);
            }
            /*<==A32D10964*/
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_FALSE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}

/***********************************************************************
 *  MODULE   : Mm_ComGmmAttachCauseHandle
 *  FUNCTION : MM��GMM ATTACH����ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucCause                  ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-09  �°�����,�������
    2. ��    ��   : 2007��3��5��
       ��    ��   : liurui id:40632
       �޸�����   : �������ⵥ�ţ�A32D09094
    3. ��    ��   : 2008��09��03��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
    4.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    5.��    ��   : 2011��07��21��
      ��    ��   : h44270
      �޸�����   : ���ⵥ�ţ�DTS2011071901850,PLMN NOT ALLOWʱͣT3212��ʱ��
    6.��    ��   : 2011��11��22��
      ��    ��   : W00166186
      �޸�����   : DTS2011122107833,PS 11�ܾ���CS ok��ЧPLMNû��ɾ��
    7.��    ��   : 2013��03��14��
      ��    ��   : l65478
      �޸�����   : DTS2013031309016,PS REJ#3ʱ��û�а�CS����Ϊ��Ч
    8.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    9.��    ��   : 2014��4��2��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
    10.��    ��   : 2015��2��6��
       ��    ��   : h00313353
       �޸�����   : USIMM���ӿڵ���
 ************************************************************************/

VOS_VOID Mm_ComGmmAttachCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* �ο�24.008��
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_NO_IMSI \r " );                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* ���ø���״̬                             */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* ���ø���״̬                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* ����TMIS������                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                /* Modified by h44270 for DTS2011071901850�� 2011-07-21 Begin */
                Mm_TimerStop(MM_TIMER_T3212);
                /* Modified by h44270 for DTS2011071901850�� 2011-07-21 end */
            }
        }
        break;
    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComGmmRauCauseHandle
 *  FUNCTION : MM��GMM RAU����ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucCause                  ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-10  �°�����,�������
    2.  ��    ��   : 2007��1��26��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D08577
    3.  ��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
    4.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    5.��    ��   : 2011��07��21��
      ��    ��   : h44270
      �޸�����   : ���ⵥ�ţ�DTS2011071901850,PLMN NOT ALLOWʱͣT3212��ʱ��
    6.��    ��   : 2011��11��22��
      ��    ��   : W00166186
      �޸�����   : DTS2011111400747,RAU��3�Ż�6��ԭ��ֵ�ܾ��󣬺����ַ�����LAU
    7.��    ��   : 2011��11��22��
      ��    ��   : W00166186
      �޸�����   : DTS2011122107833,PS 11�ܾ���CS ok��ЧPLMNû��ɾ��
    8.��    ��   : 2012��04��19��
      ��    ��   : W00166186
      �޸�����   : DTS2012041804101,һ���򱻾�13#,û��ɾ��EPLMN
    9.��    ��   : 2013��03��14��
      ��    ��   : l65478
      �޸�����   : DTS2013031309016,PS REJ#3ʱ��û�а�CS����Ϊ��Ч
   10.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   11.��    ��   : 2014��4��2��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
 ************************************************************************/

VOS_VOID Mm_ComGmmRauCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* �ο�24.008��
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.usCauseVal   = usCause;                                /* ��¼ԭ��ֵ                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NO_IMSI \r " );                       */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* ���ø���״̬                             */

            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* ����TMIS������                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                /* Modified by h44270 for DTS2011071901850�� 2011-07-21 Begin */
                Mm_TimerStop(MM_TIMER_T3212);
                /* Modified by h44270 for DTS2011071901850�� 2011-07-21 end */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* ����MM��Ϣ                               */


            NAS_MM_UpdateEquPlmnInfo(usCause);

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcGmmSeriveRejCause3
 ��������  : MM����gmm������service����ԭ��ֵ#3/#6/#8
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��11��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MM_ProcGmmSeriveRejCause3(VOS_UINT16 usCause)
{
    g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
    g_MmGlobalInfo.usCauseVal   = usCause;
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* ���ø���״̬                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(
                     MM_STATUS_DETACHED,
                     MM_CKSN_INVALID
                     );                                                     /* ��RRC����RRMM_NAS_INFO_CHANGE_REQ        */
    Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                        ~MM_MS_ID_TMSI_PRESENT;             /* ����TMSI������                           */

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;         /* ����IMSI������                           */

    Mm_ComUpdateUsimFileReq();

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
    Mm_ComProcCauseClear();

    return;

}

/***********************************************************************
 *  MODULE   : Mm_ComGmmSrCauseHandle
 *  FUNCTION : MM��GMM SR����ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucCause                  ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.��־��    04-03-10  �°�����,�������
    2.��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
    3.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    4.��    ��   : 2011��07��21��
      ��    ��   : h44270
      �޸�����   : ���ⵥ�ţ�DTS2011071901850,PLMN NOT ALLOWʱͣT3212��ʱ��

    5.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
    6.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    7.��    ��   : 2013��9��12��
      ��    ��   : w00242748
      �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                   ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                   G��ԭС��ʱ��LAU
    8.��    ��   : 2014��4��2��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
    9.��    ��   : 2015��3��20��
      ��    ��   : w00167002
      �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                   ���з�װ��
    10.��    ��   : 2015��6��11��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
************************************************************************/

VOS_VOID Mm_ComGmmSrCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
    /*24008_CR2297R2_(Rel-11)_C1-124967 24008 4.7.13.4��������:
    #8 - The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED (and
    shall store it according to subclause 4.1.3.2) and shall delete any P-TMSI,
    P-TMSI signature, RAI and GPRS ciphering key sequence number. The new GMM state
    is GMM-DEREGISTERED.
    The MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI
    and ciphering key sequence number. If the MS is operating in MS operation mode A and an RR
    connection exists, the MS shall abort the RR connection, unless an emergency call is ongoing.
    The SIM/USIM shall be considered as invalid for GPRS and non-GPRS services until switching off
    or the SIM/USIM is removed. */
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;


    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+Iģʽ                            */
            if ( (MM_FALSE == g_MmGlobalInfo.ucLikeB)
             && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                   && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))

            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ��������Bģʽ                            */
                /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* ���ø���״̬                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* ����TMIS������                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();

        /* Modified by h44270 for DTS2011071901850�� 2011-07-21 Begin */
        Mm_TimerStop(MM_TIMER_T3212);
        /* Modified by h44270 for DTS2011071901850�� 2011-07-21 end */

        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* ����TMIS������                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* ����MM��Ϣ                               */


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedStartT3212RcvGmmDetachInd
 ��������  : �ж�MM�յ�gmm��detach ind��Ϣ�Ƿ���Ҫ����T3212
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����T3212
             VOS_FALSE - ����Ҫ����T3212
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedStartT3212RcvGmmDetachInd( VOS_VOID )
{
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
       || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
        && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/***********************************************************************
 *  MODULE   : Mm_ComNetDetachCauseHandle
 *  FUNCTION : MM��NET DETACH����ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucCause                  ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-10  �°�����,�������
    2.  ��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
    3.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    4.��    ��   : 2011��07��05��
      ��    ��   : c00173809
      �޸�����   : DTS2011070100651,BVT����6.2.7ʧ�ܣ���HOME PLMN�ϣ�GMM�յ�����DETACH��
           ԭ��ΪPLMN NOT ALLOW����ѡ��LAI��С����û�з���LAU��

    5.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
    6.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    7.��    ��   : 2013��9��12��
      ��    ��   : w00242748
      �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                   ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                   G��ԭС��ʱ��LAU
    8.��    ��   : 2014��4��2��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
    9.��    ��   : 2015��3��20��
      ��    ��   : w00167002
      �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                   ���з�װ��
    10.��    ��   : 2015��6��8��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
************************************************************************/

VOS_VOID Mm_ComNetDetachCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* ���ø���״̬                             */

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         MM_CKSN_INVALID
                         );                                                     /* ��RRC����RRMM_NAS_INFO_CHANGE_REQ        */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* ����TMSI������                           */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;         /* ����IMSI������                           */

        Mm_ComUpdateUsimFileReq();

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;

        /*24008_CR2243R2_(Rel-11)_C1-124176 24008  4.7.4.2.2�½���������:
        If the MS is attached for GPRS and non-GPRS services and the network operates in network operation mode I,
        then if in the MS the timer T3212 is not already running, the timer T3212 shall be
        set to its initial value and restarted if:
        -   the detach type IE indicates "re-attach required";
        -   the detach type IE indicates "re-attach not required" and no cause code is included; or
        -   the detach type IE indicates "re-attach not required" and the cause code is #7 "GPRS services not allowed"
            or #14 "GPRS services not allowed in this PLMN". */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        if (VOS_TRUE == NAS_MM_IsNeedStartT3212RcvGmmDetachInd())
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ                          */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmLikeB is MM_TRUE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        /* g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;    */
        /* g_MmGlobalInfo.usCauseVal   = ucCause;               */
        /* g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE; */              /* ���÷���״̬                             */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* ���ø���״̬                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* ����MM��Ϣ                               */
        Mm_ComDelLai();                                                         /* ɾ��LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* ����TMIS������                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();
        /* Modified by c00173809 for DTS2011070100651�� 2011-07-05 Begin */
        Mm_TimerStop(MM_TIMER_T3212);
        /* Modified by c00173809 for DTS2011070100651�� 2011-07-05 End */
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* ����LU COUNTERΪ0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* ����TMIS������                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;



    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComCauseHandleAllProc
 *  FUNCTION : MM��ԭ��ֵ�Ĵ���
 *  INPUT    : VOS_UINT8   ucProcType                ��ǰ���̵�����
 *             VOS_UINT8   ucCause                   �����յ���ԭ��ֵ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  ��־��    04-03-10  �°�����,�������
 *     2.
 ************************************************************************/

VOS_VOID Mm_ComCauseHandleAllProc(
                              VOS_UINT8   ucProcType,
                              VOS_UINT16  usCause
                              )
{
    switch(ucProcType)
    {
    case MM_LU_PROC:
        Mm_ComLuCauseHandle(usCause);
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComGmmAttachCauseHandle(usCause);
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComGmmRauCauseHandle(usCause);
        break;
    case MM_GMM_SR_PROC:
        Mm_ComGmmSrCauseHandle(usCause);
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComNetDetachCauseHandle(usCause);
        break;
    default:
        break;
    }
}
/*****************************************************************************
 �� �� ��  : NAS_MM_DelLaiTmsiCK
 ��������  : ɾ��LAI��TMSI��CK����KC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��3��14��
   ��    ��   : luokaihui / 00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��3��14��
   ��    ��   : w00167002
   �޸�����   : ɾ����CS������Ϊ��Ч�Ĵ���: NAS_MML_SetSimCsRegStatus(VOS_FALSE);
                ԭ��:L��ע�ᱻ��ԭ��ֵ#11������GU��ע�ᣬCS������Ϊ����Ч
 3.��    ��   : 2011��10��31��
   ��    ��   : s46746
   �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
*****************************************************************************/
VOS_VOID NAS_MM_DelLaiTmsiCK(VOS_VOID)
{
    /* ɾ��ȫ�ֱ����е�LAI */
    Mm_ComDelLai();

    /* ɾ��ȫ�ֱ����е�TMSI */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg              &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();

    /* ɾ��SIM���е�LAI��IMSI */
    NAS_MM_WriteLocaInCard();

    NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

    /* ����SIM�����;�����ǰ��Ҫɾ��KC����CKIK*/
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        NAS_MM_WriteKCInCard();
    }
    else
    {
        NAS_MM_WriteCkIkInCard();
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComToNoImsiHandle
 *  FUNCTION : MM����NO SIM�Ĺ�������
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-11  �°�����,�������
    2. ��    ��   : 2007��12��12��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13861
    3.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
************************************************************************/

VOS_VOID Mm_ComToNoImsiHandle()
{
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* ���ø���״̬                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* ɾ��LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();

}

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1
 ��������  : ����ģʽI�յ�ϵͳ��Ϣָʾcs��bar��ps bar��λ����δ�ı�,mm update״̬
             ��U1̬��location update neededʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1(VOS_VOID)
{
    /* ���LAI����,����״̬ΪU1                 */
    if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
    {
        Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );

        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }

            NAS_MM_NotifyAsInfoChgReq();

            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                 NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else
    {
        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(MM_FALSE, MM_IE_LUT_IMSI_ATTACH);
        }
        else
        {
            Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* ���÷���״̬                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}



/***********************************************************************
 *  MODULE   : Mm_ComSysInfoHandleWithLaiNoChange
 *  FUNCTION : ��λ�������ı�ʱ�Ĺ�������
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-11  �°�����,�������
    2. ��    ��   : 2009��8��23��
       ��    ��   : l65478
       �޸�����   : ���ⵥ�ţ�AT2D13980,��LUʧ�ܺ󣬸ı�С���󣬴˺��ٲ��ᷢ��LU,��Ϊ���յ�ϵͳ��Ϣʱ����T3211ֹͣ��
    3. ��    ��   : 2010��10��5��
       ��    ��   : ŷ����
       �޸�����   : DTS2010100500028, LAU 4��ʧ�ܺ󴥷�MMC�����б���������Ȼפ
                    ��ԭС�����˺󱳾��Ѷ�ʱ����ʱ��δ���𱳾���
    4. ��    ��   : 2010��9��29��
       ��    ��   : w00167002
       �޸�����   : ���ⵥ�ţ�DTS2010091903182,ע��ʧ�ܺ�û�з�������
    5.��    ��   : 2011��7��14��
      ��    ��   : h44270
      �޸�����   : V7R1 PhaseII�׶ε�����ע������
    6.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    7.��    ��   : 2011��12��23��
      ��    ��   : w00167002
      �޸�����   : DTS2011111901055:�������ϱ�ԭ��ֵ��NAS_MML_REG_FAIL_CAUSE_NULL
                   �޸�ΪNAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                   �޸�ԭ��:��ON PLMN״̬���յ��˼�������Ϣ����ԭ��ֵС��
                   NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE������ܷ���������
    8.��    ��   : 2012��02��23��
      ��    ��   : l65478
      �޸�����  : DTS2012020402238,GCF���ԣ�LU���ʹ���
    9.��    ��   : 2012��02��07��
      ��    ��   : l65478
      �޸�����   : DTS2012012902539:��G->L->G��ѡʱ����L��CSע��ʧ��,�ص�G��MMû�з���ע��
   10.��    ��   : 2012��03��20��
      ��    ��   : l00130025
      �޸�����   : DTS2012030105247,NASֻ������ʵ�ʷ����Ȩʱ,֪ͨW SecurityKey�������������WAS���ö�Ӧ�ӿڻ�ȡ
   11.��    ��   : 2012��9��24��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��DTS2012090801459������λ�ø���ʱֹͣT3212
   12.��    ��   : 2012��12��25��
      ��    ��   : l00167671
      �޸�����   : ���ⵥ��DTSl00167671��L�������������ʱ��W���ѵ����ϴ�ע����ͬ��С��
                   �ȷ�����LU
   13.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   14.��    ��   : 2013��06��09��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��DTS2013060407637��T3212��������Ϊ0,��ǰ����ֻ����һ�����粢��ע��ܾ�ʱÿ��PLMN����������MM���̷���ע��
   15.��    ��   : 2014��5��21��
      ��    ��   : w00167002
      �޸�����   : DTS2014051602857:��SOR��ʱ���û�ָ������ʱ�������ATTEMPT
                   COUNTER��
   16.��    ��   : 2014��8��14��
      ��    ��   : z00161729
      �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau
   17.��    ��   : 2015��3��20��
      ��    ��   : w00167002
      �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                   ���з�װ��
 ************************************************************************/
VOS_VOID    Mm_ComSysInfoHandleWithLaiNoChange(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        /* ���LAI����,����״̬ΪU1                 */
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            else
            {
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                {
                    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                    {
                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
                    }

                    NAS_MM_NotifyAsInfoChgReq();

                    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
        else
        {
            if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);
            }
            else if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            /* ���ڷ���LAU��ʱ��ֹͣ��T3212��������T3212û�����У���ʾǰ���Ѿ������ */
            else if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* ���÷���״̬                             */

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��MMC����MMCMM_LU_RESULT_IND             */


                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
    else if ( (1 == ucUserSpecificSearchFlg)                        /* �û������ָ���������ҵ�ǰ����U1����ʹλ�������䣬Ҳ����ע�� */
            ||(MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))             /* �տ�����λ�������䣬Ҳ����ע�� */
    {
        /* ����״̬�����ֶ�����ʱ�������ATTMPTCNT */
        if ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
    }
    else
    {   /* MM ״̬Ǩ�ص�����ǰ��״̬ */
        /* �ڷ�U1״̬��������ע�ᶨʱ��û������ʱ,Ҫ����һ��LU���� */
        if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
         && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
        {
            /* ��NOT UPDATED״̬��MMӦ�÷������NORMAL LU */
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
           NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
        else if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            /* ���T3212��������T3211�������У���֪ͨMMC��ǰT3212������,��������ȴ�T3211��ʱע�ᴦ�� */
            if ( (MM_TIMER_STOP     == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
              && (MM_TIMER_RUNNING  == gstMmTimer[MM_TIMER_T3212].ucTimerStatus) )
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING);
            }
            else
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);/* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */

            }

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);              /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
        }
        else
        {

        }
    }
}


/***********************************************************************
 *  MODULE   : Mm_ComRcvSysHandle
 *  FUNCTION : MM��NO CELL��PLMN SEARCH�յ�ϵͳ��Ϣ�Ĺ�������
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  ��־��    04-03-11  �°�����,�������
    2.  s46746    06-06-21  �������ⵥA32D04355�޸�
    3. s46746  2006-07-27 �������ⵥA32D03975�޸�
    4.��    ��   : 2006��11��22��
      ��    ��   : luojian   id:60022475
      �޸�����   : ���ⵥ�ţ�A32D07582
    5.��    ��   : 2008��8��21��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
    6.��    ��   : 2008��12��22��
      ��    ��   : o00132663
      �޸�����   : ���ⵥ��:AT2D07757,MM�������ػ�ԭС����������LU
    7.��    ��   : 2009��01��05��
      ��    ��   : l65478
      �޸�����   : �������ⵥ:AT2D07749,�޸���������ʱ��,���ؽ�������ʱ�����LAI���ı䣬��Ӧ�ý���LU
    8.��    ��   : 2011��7��14��
      ��    ��   : h44270
      �޸�����   : V7R1 PhaseII�׶ε�����ע������
    9.��    ��   : 2011��10��27��
      ��    ��   : s46746
      �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
   10.��    ��   : 2012��03��17��
      ��    ��   : s46746
      �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
    11.��    ��  : 2012��2��15��
       ��    ��  : z00161729
       �޸�����  : V7R1C50 ֧��CSFB�����޸ģ�����CSFB��־ʱ������LAU
    12.��    ��  : 2012��3��21��
       ��    ��  : w00166186
       �޸�����  : V7R1C50 L��ϵͳ��Gʱ����ͣ��LAU
   13.��    ��   : 2012��11��07��
      ��    ��   : t00212959
      �޸�����   : DTS2011110100336,�������Ⱥ��к���LAU
   14.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   15.��    ��   : 2013��10��15��
      ��    ��   : l65478
      �޸�����   : DTS2013102501008���յ�����ģʽ���ó��Զ�����ģʽ��û�з���ע��
   16.��    ��   : 2013��12��5��
      ��    ��   : w00167002
      �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                   PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                   �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
   17.��    ��   : 2014��04��1��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż��Լ�ȫ�ֱ����滻
  18.��    ��   : 2014��6��4��
      ��    ��   : w00167002
      �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                 �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                 ������LAU.
                 ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                 DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                 �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                 ������LAU.
************************************************************************/

VOS_VOID Mm_ComRcvSysHandle(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    MM_LAI_STRU                         stCurLai;
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
    {
        return;
    }
#endif

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);

    /* ��ǰ״̬��attempt tO updateʱ,����һ��פ����LAI��Ƚ�;
       ��ǰ״̬��limit serviceʱ,���ϴγɹ�פ����LAI��Ƚ� */
    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(),
                                                   &stCurLai))

            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else if (MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucNotCampONPreState)
        {
            if (VOS_TRUE == ulLaiChangeFlag)
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else
        {
        }
    }

    if ( g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod )
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
            {
                Mm_TimerStop(MM_TIMER_T3213);
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
             /* �����NOT UPDATEʱ�򣬵�ǰLAI����ATTEMPT LAI�У�����LAU */
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(), &stCurLai))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            {
                /* ����LU REQ */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                /* LA û�����ı� */
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        else
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
    }
    else
    {
        Mm_ComNetModeChange();
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
}


/*******************************************************************************
  MODULE   : Mm_ComMmConnExist
  FUNCTION : �ж��Ƿ���MM���Ӵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         �Ƿ���MM���Ӵ��ڵĽ��
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMmConnExist(
                        VOS_VOID
                    )
{
    VOS_UINT8           ucResult = MM_FALSE;                                        /* �Ƿ���MM���Ӵ��ڵĽ��                   */
    VOS_UINT8           i        = 0;                                               /* ѭ������                                 */

    for ( i = 0; i < MM_CONN_CM_ENTITY_NUM; i++)
    {                                                                           /* ����CMʵ�����                           */
        if ( ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[0] )
            || ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[1] ) )
        {                                                                       /* �д��ڵ�MM����                           */
            ucResult = MM_TRUE;                                                 /* ����ֵ���ó���MM���Ӵ���                 */
        }
    }

    return ucResult;
}


/*******************************************************************************
  MODULE   : Mm_ComSaveProcAndCauseVal
  FUNCTION : �洢���̺�ԭ��ֵ
  INPUT    : VOS_UINT8             ucProc          ����
             VOS_UINT8             ucCauseVal      ԭ��ֵ
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15  �°�����
*******************************************************************************/
VOS_VOID Mm_ComSaveProcAndCauseVal(
                                VOS_UINT8             ucProc,
                                VOS_UINT16            usCauseVal
                                )
{
    if ( ( MM_NULL_PROC == g_MmGlobalInfo.ucProc )
        && ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal ) )
    {
        g_MmGlobalInfo.usCauseVal   = usCauseVal;
        g_MmGlobalInfo.ucProc       = ucProc;
    }
    else
    {
        if ( ( MM_NULL_PROC != ucProc )
            && ( NAS_MML_REG_FAIL_CAUSE_NULL != usCauseVal ) )
        {
            g_MmGlobalInfo.usCauseVal   = usCauseVal;
            g_MmGlobalInfo.ucProc       = ucProc;
        }
        else
        {
            if ( MM_AUTH_FAIL_PROC == ucProc )
            {
                g_MmGlobalInfo.usCauseVal   = usCauseVal;
                g_MmGlobalInfo.ucProc       = ucProc;
            }
        }
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_ComJudgeLimitSvc
  FUNCTION : �ж��Ƿ������޷���״̬
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         �Ƿ������޷���
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15  �°�����
     2.
*******************************************************************************/
VOS_UINT8 Mm_ComJudgeLimitSvc(
                         VOS_VOID
                         )
{
    VOS_UINT8             ucResult = MM_FALSE;                                      /* �Ƿ������޷���                           */
    if ( ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState ) )
    {                                                                           /* �����޷���                               */
        ucResult = MM_TRUE;                                                     /* ���������޷���                           */
    }

    return ucResult;                                                            /* ����                                     */
}

/*******************************************************************************
  MODULE   : Mm_ComFillInCMSncReq
  FUNCTION : �����Ϣ����
  INPUT    : VOS_UINT8                      ucCMSvcType          CM��������
             VOS_UINT8                      ucPrioLeveFlg        ���ȼ�
             MM_MSG_CM_SVC_REQ_STRU     *CmSvcReq            ��Ϣ���ݽṹ��ָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15  �°�����

  2.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*******************************************************************************/
VOS_VOID Mm_ComFillInCMSncReq(
                            VOS_UINT8                       ucCMSvcType,
                            VOS_UINT8                       ucPrioLeveFlg,
                            MM_MSG_CM_SVC_REQ_STRU      *CmSvcReq
                            )
{
    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    CmSvcReq->MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();           /* �洢CKSN                                 */
    CmSvcReq->MmIeCmSvcType.ucCMSvcType = ucCMSvcType;                          /* Supplementary service activation         */
    NAS_MM_FillMobileID(&(CmSvcReq->MmIeMobileId.MobileID));
    CmSvcReq->ucPrioLeveFlg = ucPrioLeveFlg;                                    /* û�����ȼ�                               */

    return;
}
/*******************************************************************************
  MODULE   : Mm_ComFollowOnProc
  FUNCTION : �������FollowOn�����
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15    �°�����
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�

  2.��    ��   : 2013��4��15��
    ��    ��   : w00167002
    �޸�����   : DTS2013041108015:�û�ͨ��HISC2ͨ����L�·���SMSҵ��SMSҵ��
                  ʧ�ܣ��û���HISC1ͨ��������ͨ�绰ҵ����GU��LAU�ɹ���
                  ָʾFOLLOW ON��ʶ���绰ҵ����SMSҵ��ͬʱ�����յ�CM SERVICE RSLT
                  ʱ��MM�޷��б��յ�ʱ��һ��CMҵ��Ľ����
                  �޸�ΪMMֻ����һ��CM SERVICE REQ,SMSҵ�񱻻��棬����MM���յ�
                  CM SERVICE RSLTʱ���ɷ��𻺴��SMSҵ��
  3.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  5.��    ��   :2015��02��23��
    ��    ��   :j00174725
    �޸�����   :for DTS2015012303754
*******************************************************************************/
VOS_VOID Mm_ComFollowOnProc(
                        VOS_VOID
                        )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT8                           ucCmSvsType;
    VOS_UINT8                           ucPdType;
    NAS_MM_CONN_CTRL_ENUM_UINT8         i;

    /* �ֲ�������ʼ�� */
    ucCmSvsType = 0xFF;
    ucPdType    = 0xFF;
    i           = MM_CONN_CTRL_CC;

    /* �л���ĺϷ���CCҵ��Ĵ��� */
    if (  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {                                                                           /* �еȴ���CC��������Ҫ������MM����         */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;             /* ��¼�յ���������ʱ��״̬                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {                                                                       /* ��������                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* ���CM SERVICE REQUEST�ṹ��             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_FALSE;                                                     /* ��������                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE);
        }
        else
        {                                                                       /* ��������                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* ���CM SERVICE REQUEST�ṹ��             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_TRUE;                                                      /* ��������                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                        /* �����෢�ͽ���MM���ӵ�����               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                                        /* ��¼���ڽ�����MM����                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;                /* ��¼���ڽ�����MM���ӵ�PD                 */
        g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION;     /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_T3230);                                          /* ����TIMER3230                            */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* ������ڻ����MM���ӽ�������ı�־       */

        /* ֪ͨMMC��ǰCSҵ���Ѿ����� */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        /* ����CSҵ������״̬ */
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

        return;
    }

    /* �л���Ĳ��Ϸ���CCҵ��Ĵ��� */
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        /* �еȴ���CCҪ������MM����,TI���Ϸ�      */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);   /* ֪ͨCC����ʧ��  */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* ������ڻ����MM���ӽ�������ı�־       */

    }

    /* ѭ������CM����ҵ�� */
    for ( i = 0 ; i < MM_CONN_CTRL_BUTT; i++ )
    {
        if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg )
        {
            if (  ( MM_CONST_NUM_7 <  g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId)
               && ( MM_CONST_NUM_15 > g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId) )
            {
                if ( MM_CONN_CTRL_SS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SS_ACT;
                    ucPdType    = MM_IE_PD_NON_CALL_RLT_SS_MSG;
                }
                else if ( MM_CONN_CTRL_SMS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SMS;
                    ucPdType    = MM_IE_PD_SMS_MSG;
                }
                else
                {
                    /* ��SS/SMS��Ϣ�����쳣���� */
                    break;
                }


                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;         /* ��¼�յ���������ʱ��״̬                 */
                Mm_ComFillInCMSncReq(ucCmSvsType,
                    MM_FALSE, &CmSvcReq);                                           /* ���CM SERVICE REQUEST�ṹ��             */
                Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* �����෢�ͽ���MM���ӵ�����               */

                g_MmGlobalInfo.ConnCtrlInfo[i].ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId;                                        /* ��¼���ڽ�����MM����                     */
                g_MmGlobalInfo.ucMMConnEstingPD = ucPdType;                         /* ��¼���ڽ�����MM���ӵ�PD                 */
                g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION; /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
                Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */

                /* ������ڻ����MM���ӽ�������ı�־ */
                g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

                /* ֪ͨMMC��ǰCSҵ���Ѿ����� */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

                /* ����CSҵ������״̬ */
                NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

                /* ����CM ������� */
                return;
            }

            /* �л���ķǷ���CMҵ��Ĵ��� */
            if ( MM_CONN_CTRL_SS == i )
            {
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
            }
            else if ( MM_CONN_CTRL_SMS == i )
            {
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[i].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* ֪ͨSMS����ʧ��                          */
            }
            else
            {
            }

            /* ������ڻ����MM���ӽ�������ı�־ */
            g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

        }

    }

    /* �����ǰû�л�����߻������ϢTI�Ƿ��������״̬Ǩ�� */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;        /* ������е�״̬                           */
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM��������                               */
    g_MmGlobalInfo.ucPreState   = LOCATION_UPDATING_INITIATED;              /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    Mm_TimerStart(MM_TIMER_T3240);

    return;
}

/*******************************************************************************
  MODULE   : Mm_ComChkAttDelay
  FUNCTION : ����Ƿ��б�����ATTACH
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_ComChkAttDelay( )
{
    if ( MM_TRUE == g_MmGlobalInfo.ucAttDelay )
    {
        if ( ( MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState )
            && ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
            )
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        g_MmGlobalInfo.ucAttDelay = MM_FALSE;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_LU_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: LU_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     3.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_LU_PROC(VOS_VOID)
{
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_LU_PROC:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }
    }
    else
    {
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                     /* ����ԭ��ֵ�Ĵ���                         */
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_GMM_ATTACH_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmAttachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* ����ԭ��ֵ�Ĵ���                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: GMM_RAU_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmRauCauseHandle(g_MmGlobalInfo.usCauseVal);                 /* ����ԭ��ֵ�Ĵ���                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_GMM_SR_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* �ο�4.5.1.1 */
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmSrCauseHandle(g_MmGlobalInfo.usCauseVal);                  /* ����ԭ��ֵ�Ĵ���                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_NET_DETACH_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��2��4��
       ��    ��   : w00176964
       �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     3.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     4.��    ��   : 2013��9��12��
       ��    ��   : w00242748
       �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                    ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                    G��ԭС��ʱ��LAU
     5.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
     6.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC(VOS_VOID)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComNetDetachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* ����ԭ��ֵ�Ĵ���                         */
        break;
    case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_MM_CONN_PROC����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
    1.  ŷ����   2009.06.11  �°�����
    2.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
   3.��    ��   : 201112��16��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�DTS2011111403722,����ģʽI CSע��ʧ��#4ʱ,û�з���ע��,����CSҵ�񲻿���
   4.��    ��   : 2012��10��29��
     ��    ��   : z00161729
     �޸�����   : DTS2012083102536:֧��cc�����ؽ�
   5.��    ��   : 2013��2��4��
     ��    ��   : w00176964
     �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
   6.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   7.��    ��   :2013��9��12��
     ��    ��   :z00161729
      �޸�����  :DTS2013082903019:֧��ss�ط�����
   8.��    ��   :2014��9��24��
     ��    ��   :s00217060
     �޸�����   :for cs_err_log
************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC(VOS_VOID)
{
    VOS_UINT8                           ucPsSimStatus;

    ucPsSimStatus = NAS_MML_GetSimPsRegStatus();

    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaAfterWaitForNwkCmd);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

        /* ��ǰCS��Ч��LAIû�н�ֹ */
        if ( (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (( MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
           || ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )))
        {
            /*
            24.008 4.5.1.1 CM SERVICE REJECT Process: If cause value #4
            is received, If subsequently the RR connection is released
            or aborted, this will force the mobile station to initiate
            a normal location updating.
            */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
            if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
             && (VOS_TRUE == ucPsSimStatus)
             && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
            {                                                               /* �ж��Ƿ�ΪA+Iģʽ                        */
                /* MM�յ�CM Service Reject��Ϣʱ�Ѿ�֪ͨGMM,GMM���յ�
                CM_SERVICE_IND��Ϣָʾ��CS����ʱ���� COMBINED_RALAU_WITH_IMSI_ATTACH*/
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
        else
        {
            /* �ͷŵ�ǰ���� */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            /* ת�����ӽ���ǰ��״̬ */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_MM_NET_ABORT����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        switch ( g_MmGlobalInfo.ucMmServiceState )
        {
        case MM_NORMAL_SERVICE:
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            break;
        case MM_LIMITED_SERVICE:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            break;
        case MM_NO_IMSI:
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        default:
            break;
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH
 *  FUNCTION : Mm_ComProcCauseProcess���������Ӷ�: MM_IMSI_DETACH����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH(VOS_VOID)
{
    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    return;
}

/*******************************************************************************
  MODULE   : Mm_ComProcCauseProcess
  FUNCTION : �������̺�ԭ��ֵ�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2004.04.01  �°�����,MM_PT_����_BUG_014 ��Ӧ

     2.��    ��   : 2006��4��14��
       ��    ��   : liuyang id:48197
       �޸�����   : ���ⵥ�ţ�A32D03031
     3.��    ��   : 2007��06��01��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥA32D10964�޸�
     4.��    ��   : 2007��07��10��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥA32D11966
     5.��    ��   : 2008��08��1��
       ��    ��   : luojian id:00107747
       �޸�����   : �������ⵥAT2D04486/AT2D04822
     6.��    ��   : 2008��09��03��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
     7.��    ��   : 2009��02��21��
       ��    ��   : l65478
       �޸�����   : AT2D09308,�յ�SR�ܾ��������ԭ��ֵ6��û�и��·���״̬�Ϳ��е��ļ���Ϣ
     8.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_ComProcCauseProcess( )
{
    switch ( g_MmGlobalInfo.ucProc )
    {
    case MM_NULL_PROC:
        break;
    case MM_LU_PROC:
        Mm_ComProcCauseProcess_Handling_LU_PROC();
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC();
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC();
        break;
    case MM_COMB_ATTACH_PROC:
        break;
    case MM_COMB_RAU_PROC:
        break;
    case MM_GMM_SR_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC();
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC();
        break;
    case MM_AUTH_FAIL_PROC:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case MM_MM_CONN_PROC:
        Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC();
        break;
    case MM_MM_NET_ABORT:
        Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT();
        break;
    case MM_IMSI_DETACH:
        Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH();
        break;
    case MM_MM_MS_AUTH_FAIL_PROC:

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is ",g_MmGlobalInfo.ucState);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComProcCauseProcess:WARNING: ucProc Abnormal");
        break;
    }
    Mm_ComProcCauseClear();
}

/*******************************************************************************
  MODULE   : Mm_ComDelLai
  FUNCTION : ɾ��LAI�Ĺ�������
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2004.04.12  �°�����,MM_CHK_BUG_021 ��Ӧ
     2.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/

VOS_VOID Mm_ComDelLai()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    pstCsSuccLai->aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCsSuccLai->aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;
}

/*******************************************************************************
  MODULE   : Mm_ComProcCauseClear
  FUNCTION : ���ԭ��ֵ������
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1. ��־��   2004.04.26 �¹�����
*******************************************************************************/

VOS_VOID Mm_ComProcCauseClear()
{
    g_MmGlobalInfo.ucProc       = MM_NULL_PROC;                                 /* ��������                                 */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NULL_PROC \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: MmServiceState is MM_NULL_PROC");
    g_MmGlobalInfo.usCauseVal   = NAS_MML_REG_FAIL_CAUSE_NULL;                            /* ��¼ԭ��ֵ                               */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL");
}

/*******************************************************************************
  MODULE   : Mm_ComChkLu
  FUNCTION : �������LU����
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1. ��־��   2004.05.21 �¹�����
  2. s46746   2006.07.27 �������ⵥA32D03975�޸�
  3.��    ��   : 2009��8��18��
    ��    ��   : ŷ���� 00132663
    �޸�����   : AT2D13774,���������������з�����ϵͳ��ѡ��W->G,NMOII->NMOI��LAI�ı䣬
                 ����RAU�ɹ���δ���𻺴��CSҵ��
  4.��    ��   : 2009��8��25��
    ��    ��   : ŷ���� 00132663
    �޸�����   : AT2D14050,��NAS R6Э���������ԡ�פ����ϵͳ��Ϣ�ı䣬ָʾDSAC PS��BAR��
                 ������ͨ�绰,ͨ���ڼ�T3312��ʱ���ͷź����˴����������LAU��
  5.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2011��03��24��
    ��    ��   : ��־�� C00173809
    �޸�����   : ���ⵥ�ţ�DTS2011031803983, ��ϵͳ�л�������12С��,����LAU
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����

  8.��    ��   : 2012��09��21��
    ��    ��   : z00161729
    �޸�����  : DTS2012090706407:����lau accept��Я����ϵͳ��Ϣ�в�ͬ��non broadcast laiʱ��Ҫ����lau
  9.��    ��   : 2012��10��27��
    ��    ��   : s000217060
    �޸�����  : DTS2012041605494:RRC���Ӵ��ڣ�����ϵͳ��Ϣ����������LAU
  10.��    ��   : 2013��1��9��
    ��    ��   : l00167671
    �޸�����  : DTS2012112803062:��绰�����д�NMOI GС���л���NMOII WС�����л���ԭGС����������LAU
 11.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 12.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 13.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : DTS2013041602825:CSFB���ӽ���ʧ�ܺ�û�з���LU
*******************************************************************************/
VOS_UINT8    Mm_ComChkLu( )
{
    VOS_UINT8                           ucRet = MM_FALSE;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;


    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    if (VOS_TRUE != pstConnStatus->ucRrcStatusFlg)
    {
        return MM_FALSE;
    }

    ucRet = NAS_MM_ProcessLuAfterCsConnectNotExist();

    return ucRet;
}

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

/*******************************************************************************
  Module:   Mm_TimerPause
  Function: MMʹ�ö�ʱ����ͣ
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.25  �°�����
*******************************************************************************/
VOS_VOID Mm_TimerPause( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        {
            if ( MM_TIMER_RUNNING == gstMmTimer[i].ucTimerStatus )
            {
                if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* ��ͣʧ�ܣ��Ѿ���ͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_PAUSE;
            }
        }
    }
    else
    {
        if ( MM_TIMER_RUNNING == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* ��timer�Ѿ�����                          */

            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer) )
            {                                                                   /* ��ͣʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_PAUSE;                /* ��Timer��������־                        */
        }
    }
}

/*******************************************************************************
  Module:   Mm_TimerResume
  Function: MMʹ�ö�ʱ���ָ�
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.25  �°�����
*******************************************************************************/
VOS_VOID Mm_TimerResume( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        {
            if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus )
            {




                if( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[i].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[i].ulTimerLen,         /* ʱ��                                     */
                                           (VOS_UINT32)i,            /* ��Ϣ���е�ID                             */
                                           gstMmTimer[i].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[i].ucMode          /* ��Ϣ���ȼ�                               */
                                           ))
                {                                                               /* �ָ�ʧ�ܣ��Ѿ��ָ���Timer������          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_RUNNING;
            }
        }
    }
    else
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* ��timer�Ѿ�����                          */






            if ( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* ʱ��                                     */
                                           (VOS_UINT32)ucTimerId,            /* ��Ϣ���е�ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           ) )
            {                                                                   /* ��ͣʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* ��Timer��������־                        */
        }
    }
}

/*******************************************************************************
  Module:   Mm_ComT3212
  Function: ����T3212��ʱ��
  Input:    VOS_UINT8  ucT3212Timer     ���뵥λ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.25  �°�����
      2.  s46746     2006.08.02  �������ⵥA32D03686�޸�
      3.  ��    ��   : 2012��1��30��
          ��    ��   : l00130025
          �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
      4.��    ��   : 2013��5��20��
        ��    ��   : s00217060
        �޸�����   : coverity��foritfy�޸�
      5.��    ��   : 2014��6��22��
        ��    ��   : z00234330
        �޸�����   : coverity��foritfy�޸�
*******************************************************************************/

VOS_VOID Mm_ComT3212(VOS_UINT32  ulT3212Timer)
{
    VOS_UINT32                          ulTemp;
    VOS_UINT32                          ulTemp1;
    VOS_UINT32                          ulTempRemain;

    /* Modified by z00234330 for PCLINT����, 2014-06-20, begin */
    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_STATE_NULL:
    case MM_IDLE_NO_CELL_AVAILABLE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_PLMN_SEARCH:
    case MM_IDLE_PLMN_SEARCH_NORMAL_SERVICE:

        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212ʱ���ĸ�ֵ                          */

        break;

    /* Modified by z00234330 for PCLINT����, 2014-06-20, end */

    default:
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212ʱ���ĸ�ֵ                          */

        if ( MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
        {                                                                       /* ���T3212����������                      */
            ulTemp1 = ulT3212Timer;


            ulTempRemain = MM_CONST_NUM_0;

            if (VOS_NULL_PTR != gstMmTimer[MM_TIMER_T3212].hTimer)
            {
                /* hTimer Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ,��Ϊ��ʱ����ȡ��ʣ�೤�� */
                if (VOS_OK != VOS_GetRelTmRemainTime(&(gstMmTimer[MM_TIMER_T3212].hTimer), &ulTempRemain))
                {
                    ulTempRemain = MM_CONST_NUM_0;
                }
            }

            ulTemp = ulTempRemain * MM_TIMER_TICK;


            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_T3212, &gstMmTimer[MM_TIMER_T3212].hTimer ) )
            {                                                                   /* ��ͣʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER STOP FAILURE!");
            }

            if ( MM_CONST_NUM_0 == ( ulTemp%ulTemp1 ) )
            {
                ulTemp = 1000;
            }
            else
            {
                ulTemp = (VOS_UINT32)ulTemp%ulTemp1;
            }
            if (VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[MM_TIMER_T3212].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           ulTemp,         /* ʱ��                                     */
                                           MM_TIMER_T3212,            /* ��Ϣ���е�ID                             */
                                           gstMmTimer[MM_TIMER_T3212].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[MM_TIMER_T3212].ucMode          /* ��Ϣ���ȼ�                               */
                                           ) )
            {                                                                   /* ����ʧ�ܣ��Ѿ��ָ���Timer������          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER START FAILURE!");
            }


        }
        else
        {
            ulTemp1 = ulT3212Timer;

            /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, begin */
            /* ������� */
            VOS_SetSeed(VOS_GetTick());

            NAS_MM_SetNetworkT3212RandLen(VOS_Rand(ulTemp1));

            /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, end */
        }
        break;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MM_QryTimerStatus
 ��������  : ��ѯָ����MM��ʱ����״̬�Լ�ʣ��ʱ��
 �������  : ucTimerId  - ��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : pusLeftLen - ��ʱ����ʣ��ʱ��
 �� �� ֵ  : NAS_MMC_TIMER_STATUS_ENUM_U8:��ʱ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��26��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
*****************************************************************************/
VOS_UINT32  NAS_MM_QryTimerStatus(VOS_UINT8 ucTimerId)
{

    if ( MM_TIMER_STOP  != gstMmTimer[ucTimerId].ucTimerStatus )
    {
        return MM_TIMER_RUNNING;
    }
    else
    {
        return MM_TIMER_STOP;
    }

}

/*******************************************************************************
  Module:   Mm_TimerStart
  Function: MMʹ�ö�ʱ������
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.25  �°�����
*******************************************************************************/
VOS_VOID Mm_TimerStart( VOS_UINT8   ucTimerId )
{
    VOS_UINT32 ulResult;

    if ( MM_TIMER_STOP ==  gstMmTimer[ucTimerId].ucTimerStatus )
    {
        if ( MM_TIMER_T3212 == ucTimerId )
        {                                                                       /* ���ΪT3212                              */
            if ( MM_CONST_NUM_0 != gstMmTimer[ucTimerId].ulTimerLen )
            {
                if ( MM_CONST_NUM_0 != NAS_MM_GetNetworkT3212RandLen())
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           NAS_MM_GetNetworkT3212RandLen(),         /* ʱ��                                     */
                                           MM_TIMER_T3212,            /* ��Ϣ���е�ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           );                                   /* ����֧����Ϣ�Ķ�ʱ��                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* ����ʧ��                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);
                }
                else
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* ʱ��                                     */
                                           MM_TIMER_T3212,            /* ��Ϣ���е�ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           );                                                /* ����֧����Ϣ�Ķ�ʱ��                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* ����ʧ��                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                }

                gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;          /* ��Timer��������־                        */
                /*WUEPS_TRACE(MM_LOG_LEVEL_6,"\nMM StartTimer: %d\r",ucTimerId);*/
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
            }
        }
        else
        {
            if (MM_TIMER_PROTECT_SIGNALLING  == ucTimerId)
            {
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_G_SIGNALLING_VALUE;
                }
                else
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;
                }
            }
            ulResult = Mm_StartRelTimer(  &gstMmTimer[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* ʱ��                                     */
                                           (VOS_UINT32)ucTimerId,                       /* ��Ϣ���е�ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           );                                             /* ����֧����Ϣ�Ķ�ʱ��                     */
            if ( VOS_OK != ulResult )                        /* ����ʧ��                                 */
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                return;
            }
            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* ��Timer��������־                        */
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
        }
    }

}
/*****************************************************************************
 �� �� ��  : NAS_MM_IsTimerIdInTimerList
 ��������  : �ж�ĳ����ʱ���Ƿ��ڶ�ʱ��������
 �������  : ucTimerId   �ض���ʱ��
             ucTimerNum  ��ʱ������
             pucTimer    ��ʱ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��ʾ�ڸ�������
             VOS_FALSE ��ʾ���ڸ�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��2��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_TimerStopExceptSpecialTimers
 ��������  : MMģ��ֹͣ���г��ض���ʱ��������ж�ʱ��
 �������  : ucTimerNum  ��ʱ������
             pucTimer    ��ʱ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��2��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��16��
    ��    ��   : j00174725
    �޸�����   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;

    /* Modified by w00176964 for V3R360_eCall��Ŀ, 2014-5-19, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by w00176964 for V3R360_eCall��Ŀ, 2014-5-19, end */
    {
        if ( VOS_TRUE == NAS_MM_IsTimerIdInTimerList(i, ucTimerNum, pucTimer) )
        {
            continue;
        }


        if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
            Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
            {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            if (MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE == i)
            {
                NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);
            }

            gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
        }
    }
}


/*******************************************************************************
  Module:   Mm_TimerStop
  Function: MMʹ�ö�ʱ��ֹͣ
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.25  �°�����
      24. ��    ��   : 2014��5��28��
          ��    ��   : z00234330
          �޸�����   : covertity�޸�
      24. ��    ��   : 2015��10��16��
          ��    ��   : j00174725
          �޸�����   : DTS2015101603066
*******************************************************************************/
VOS_VOID Mm_TimerStop( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* ֱ�ӽ�CSFB �ı�����ʱ��״̬��Ϊstop */
        NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        {
            if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
            {
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;
                /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
                /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
            }
        }
    }
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    else if ( ucTimerId < MM_TIMER_MAX )
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    {
        if ( MM_TIMER_STOP != gstMmTimer[ucTimerId].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer))
            {                                                                   /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_STOP;
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", ucTimerId);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER ID ERROR!");
    }

}
/*******************************************************************************
  MODULE   : Mm_ComAuthMsRej
  FUNCTION : ��MS��ܾ���Ȩ�Ĺ�������
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.27 �¹�����
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_ComAuthMsRej()
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);


    Mm_SndRrRelReq(RRC_CELL_BARRED);
    switch(g_MmGlobalInfo.ucState)
    {
    case WAIT_FOR_OUTGOING_MM_CONNECTION:
        Mm_TimerStart(MM_TIMER_T3230);
        break;
    case MM_CONNECTION_ACTIVE:
    case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    case WAIT_FOR_NETWORK_COMMAND:
        break;
    case LOCATION_UPDATING_INITIATED:
        Mm_TimerStart(MM_TIMER_T3210);
        break;
    case LOCATION_UPDATE_REJECTED:
        break;
    case IMSI_DETACH_INITIATED:
        Mm_TimerStart(MM_TIMER_T3220);
        break;
    case PROCESS_CM_SERVICE_PROMPT:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthMsRej:WARNING: g_MmGlobalInfo.ucState Abnormal");
        break;
    }
}

/*******************************************************************************
  MODULE   : Mm_ComTempIdJudge
  FUNCTION : �ж���ʱID�Ƿ�仯�Ĺ�������
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : MM_TRUE  �仯
             MM_FALSE ���仯
  NOTE     :
  HISTORY  :
  1.  ��־��   2005.01.06 �¹�����
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/

VOS_UINT8 Mm_ComTempIdJudge()
{
    VOS_UINT8 ucRet = MM_TRUE;

    if ( ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) && */
                                & MM_MS_ID_TMSI_PRESENT ) ) &&
         ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) ) */
                                & MM_MS_ID_TMSI_PRESENT ) ) )
    {
        if ( 0 == VOS_MemCmp(NAS_MML_GetUeIdTmsi(), g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi, NAS_MML_MAX_TMSI_LEN))
        {
            ucRet = MM_FALSE;
        }

    }
    return ucRet;
}
/*******************************************************************************
  MODULE   : Mm_Com_UsimAuthenticationCnfChgFormat
  FUNCTION : USIM_AUTHENTICATION_CNF��ʽת��
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.02.03 �¹�����
     2.  ��־��2005.02.03 ָ������޸�Ϊ�����ʽ

     3.��    ��  : 2013��7��22��
       ��    ��  : y00245242
       �޸�����  : VoIP�����������µ�USIM�ӿ�

     4.��    ��  : 2013��8��12��
       ��    ��  : y00245242
       �޸�����  : �Ż�����
     5.��    ��   : 2014��4��175��
       ��    ��   : s00246516
       �޸�����   : DTS2014041700472:ʹ��2G SIM����PAD��̬�ϳ��ּ�Ȩ������ܾ�
*******************************************************************************/
VOS_VOID Mm_Com_UsimAuthenticationCnfChgFormat(
                               USIMM_AUTHENTICATION_CNF_STRU *pUsimMsg
                               )
{
    VOS_UINT8                           i = 0;
    VOS_UINT8*                          pPointer;
    VOS_UINT8                           ucCause;
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, begin */
    USIMM_TELECOM_AUTH_CNF_STRU        *pstTELECnf = VOS_NULL_PTR;

    pstTELECnf = &(pUsimMsg->uCnfData.stTELECnf);

    /* UMTS AUTH SUCCESS or GSM AUTH SUCCESS */
    if ((USIMM_AUTH_UMTS_SUCCESS == pUsimMsg->enResult)
     || (USIMM_AUTH_GSM_SUCCESS == pUsimMsg->enResult))
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_SUCCESS;

        pPointer = pstTELECnf->aucAuthRes;

        if (pPointer[0] <= 4)
        {
            for ( i = 0; i < pPointer[0]; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }
            for ( ;i < 4; i++ )
            {
                g_AgentUsimAuthCnf.aucResponse[i] = 0xFF;
            }

            g_AgentUsimAuthCnf.ucExtRspLength = 0x0;
        }
        else
        {
            for ( i = 0; i < 4; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }

            if ( pPointer[0] > 16 )
            {
                g_AgentUsimAuthCnf.ucExtRspLength = 12;
            }
            else
            {
                g_AgentUsimAuthCnf.ucExtRspLength = pPointer[0] - 4;
            }

            for (i=0; i<g_AgentUsimAuthCnf.ucExtRspLength; i++)
            {
                g_AgentUsimAuthCnf.aucExtResponse[i] = pPointer[i+5];
            }
        }

        if (MM_ZERO == pstTELECnf->aucGsmKc[0]) /* ��Ȩ��������� KC */
        {
            g_AgentUsimAuthCnf.ucKcLength = 0;
        }
        else /* ��Ȩ������� KC, ��ȡ KC ֵ */
        {
            for (i=0; i<8; i++)
            {
                /* skip the first length byte */
                g_AgentUsimAuthCnf.aucKc[i] = pstTELECnf->aucGsmKc[i+1];
            }

            /* get KC length from the first byte */
            g_AgentUsimAuthCnf.ucKcLength   = pstTELECnf->aucGsmKc[0];
        }

        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-12, begin */
        for (i=0; i<16; i++)
        {
            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucCipheringKey[i] = pstTELECnf->aucCK[i+1];

            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucIntegrityKey[i] = pstTELECnf->aucIK[i+1];
        }
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-12, end */
    }
    else if (USIMM_AUTH_MAC_FAILURE == pUsimMsg->enResult)
    {
        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_MAC_CODE;
        ucCause = NAS_OM_MM_CAUSE_MAC_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE);
    }
    else if (USIMM_AUTH_SYNC_FAILURE == pUsimMsg->enResult)
    {
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-12, begin */
        g_AgentUsimAuthCnf.ucFailParaLength = 14;

        pPointer = pstTELECnf->aucAuts;
        if ( pstTELECnf->aucAuts[0] > 14 )
        {
            for ( i = 0; i < g_AgentUsimAuthCnf.ucFailParaLength; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
        }
        else
        {
            for ( i = 0; i < pstTELECnf->aucAuts[0]; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
            if ( pstTELECnf->aucAuts[0] < 14 )
            {
                for ( ;i < 14; i++ )
                {
                    g_AgentUsimAuthCnf.aucFailPara[i] = 0xFF;
                }
            }
        }
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-12, end */

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_SQN;
        ucCause = NAS_OM_MM_CAUSE_SYNCH_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE);
    }
    else if (USIMM_AUTH_GSM_OTHER_FAILURE == pUsimMsg->enResult) /* GSM AUTH FAILURE */
    {
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_GAS_AUTH_FAIL;
        ucCause = NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Com_UsimAuthenticationCnfChgFormat:WARNING: ucResult Abnormal");
        /* WUEPS_ASSERT(0); */
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_AUTH_FAIL_UNKNOWN;
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE);
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
        return ;
    }

    if(AGENT_AUTH_RST_FAILURE == g_AgentUsimAuthCnf.ucCheckRst)
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
    }
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, end */
}

/*******************************************************************************
  MODULE   : Mm_ComNetModeChange
  FUNCTION : ����ģʽ�仯����
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746 2005.07.27 create
     2.  x51137 A32D08115 2007/01/03
     3.��    ��   : 2010��12��01��
       ��    ��   : z00161729
       �޸�����  : DTS2010111903590:LAI��RAI��CELL��δ��ֻ������ģʽ�����ı䣬UE����RAU��LAU����˲���

     4.��    ��   : 2011��8��15��
       ��    ��   : zhoujun 40661
       �޸�����   : δ����LAUʱ����Ҫ�ϱ������̸�MMCģ��
     5.��    ��   : 2011��12��23��
       ��    ��   : w00167002
       �޸�����   : DTS2011111901055:�������ϱ�ԭ��ֵ��NAS_MML_REG_FAIL_CAUSE_NULL
                    �޸�ΪNAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                    �޸�ԭ��:��ON PLMN״̬���յ��˼�������Ϣ����ԭ��ֵС��
                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE������ܷ���������
     6.��    ��   : 2012��02��29��
       ��    ��   : l00130025
       �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
     7.��    ��   : 2012��03��17��
       ��    ��   : s46746
       �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����

     8.��    ��   : 2012��05��22��
       ��    ��   : z40661
       �޸�����   : DTS2012052105040:�ص�ԭС��,MM״̬δǨ�Ƶ���������
     9.��    ��   : 2012��08��21��
       ��    ��   : l65478
       �޸�����   : DTS2012082003615:����������3212��ʱ�ؽ�������û�з���LU
    10.��    ��   : 2012��11��07��
       ��    ��   : t00212959
       �޸�����   : DTS2011110100336,�������Ⱥ��к���LAU
    11.��    ��   : 2012��11��17��
       ��    ��   : l65478
       �޸�����   : DTS2012111508506,������������״̬��MMû������T3212
    12.��    ��   : 2013��07��05��
       ��    ��   : l65478
       �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ
    13.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
    14.��    ��   : 2014��9��17��
       ��    ��   : w00167002
       �޸�����   : DTS2014091001010:��С��A(II)��ע��ɹ���ָ����С��B(I)����13��
                    ANYCELLפ����С��B�ϣ���ָ����С��A(II��,û�з���CS���ע�ᡣ
    15.��    ��   : 2014��9��17��
       ��    ��   : w00167002
       �޸�����   : DTS2015010504216:��GSM�£�CS ONLY,����LAU������ģʽI<->II��
                    ����ģʽ�任����ͬLAC������Ҫ����LAU.
    16.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
*******************************************************************************/
VOS_VOID Mm_ComNetModeChange()
{
    VOS_UINT8                               ucProcessLu;

    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    ucProcessLu     = MM_TRUE;

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        if ( MM_TRUE
         == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
        {
            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            return;
        }

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        {
            ucProcessLu = MM_FALSE;   /*�յ�ϵͳ��Ϣֻ��С��������ģʽ�ı����跢��LU*/


            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);



            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
             if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
               && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
               && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
             {

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
             }

            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        }
    }
    else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        {
            ucProcessLu = MM_FALSE;   /*�յ�ϵͳ��Ϣֻ��С��������ģʽ�ı����跢��LU*/

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


        }
    }
    else
    {
    }

    if (MM_TRUE == ucProcessLu)
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

    }

}

/*******************************************************************************
  Module   : MM_Update_Revision_Level
  Function : ���¿տ���Ϣ�е�ClassMark IE �� revision level����
  Input    : classmark �ĵ�һ���ֽ�
  Output   : ��
  NOTE     : ��
  Return   : �ޡ�
  History  :
    1. ŷ����  2009.06.19  �¹�����
*******************************************************************************/
VOS_VOID MM_Update_Revision_Level(VOS_UINT8 *pucClassMark)
{
    VOS_INT8                    cVersion;
    VOS_UINT8                   ucRevisionLevel;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    /* R99��ǰ�汾���ϱ� revision level Ϊ GSM PHASE 2*/
    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_GSM_PH2;
    }
    else
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }

    *pucClassMark &= 0x9f;
    *pucClassMark |= (VOS_UINT8)(ucRevisionLevel << 5);

    return;
}

/*******************************************************************************
  Module   : MM_Fill_IE_ClassMark1
  Function : ��д�տ���Ϣ�е�ClassMark1 IE (V)
  Input    : VOS_VOID *pAddr  ��дClassMark1 IE�ĵ�ַ
  Output   : ��
  NOTE     : ��
  Return   : �ޡ�
  History  :
    1. ŷ����  2009.05.10  �¹�����
    2. ��    ��   : 2010��09��07��
       ��    ��   : w00167002
       �޸�����   : ���ⵥ�ţ�DTS2010090101367,RRC CONN setup cmp��Ϣ��Class mark2 ��д���ݲ���ȷ
    3. ��    ��   : 2011��07��14��
       ��    ��   : z00161729
       �޸�����   : V7R1 phase IIȫ�ֱ��������޸�
    4.��    ��   : 2013��4��7��
      ��    ��   : z00161729
      �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
    5.��    ��   : 2014��06��04��
      ��    ��   : s00217060
      �޸�����   : ��֧��GSMʱ��classmark1�е�ES IND => 0, A5/1 => 1
*******************************************************************************/
VOS_VOID MM_Fill_IE_ClassMark1(
                               VOS_UINT8 *pucClassMark1                           /* ��дClassMark1 IE���׵�ַ                */
                              )
{
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
    GSM_BAND_SET_UN                     unSysCfgSetGsmBand;
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

    VOS_UINT8                           ucBandNum;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand  = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstCurrBand     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;

    enCurrNetRat    = NAS_MML_GetCurrNetRatType();
    pstMsCapability = NAS_MML_GetMsCapability();
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    pstCurrBand     = NAS_MML_GetCurrBandInfo();
    *pucClassMark1 = pstMsCapability->ucClassmark1;

    NAS_MML_Update_Revision_Level(pucClassMark1);

    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_GSM))
    {

        /* W only */
        /* bi8 ES IND => 0, A5/1 => 1, RF power capability => 111 */
        *pucClassMark1 &= 0xE0;
        *pucClassMark1 |= 0x0F;
    }
    else
    {
        /*��ȡ��ǰ��С������Ƶ��*/
        unSysCfgSetGsmBand.ulBand = pstCurrBand->unGsmBand.ulBand;
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;
        }

        /*���ݵ�ǰפ����Ƶ����дRF power capability*/

        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
        if ((VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1800)
         || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1900))
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
        {
           /*power class 1*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS1;
        }
        else /* ����Ƶ�� */
        {
            /*power class 4*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS4;
        }

        /* �����ǰ����פ����W��,���û�����Ϊ��Ƶ�εĴ��� */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            /* ��ȡ�û����õĿ���С����פ����Ƶ�� */
            NAS_MML_GetSupportBandNum(unSysCfgSetGsmBand.ulBand, &ucBandNum);

            /*���֧�ֶ�Ƶ�λ��߲�֧���κ�Ƶ�Σ�����RF power capability => 111*/
            if ((ucBandNum > 1) || (0 == ucBandNum))
            {
                *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_MASK;
            }
        }
    }
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetSupportBandNum
 ��������  : �����������ulBand���ж��ò����������ж��ٸ�bitֵΪ1��
             �˺����������жϵ�ǰ����Ƶ���Ƿ�Ϊ��Ƶ�Ρ�
 �������  : VOS_UINT32 ulBand
 �������  : VOS_UINT8 &ucBandNum������ȡ��ulBand�е�bitֵΪ1�ĸ�������Ƶ�θ���
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��26��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��5��
    ��    ��   : w00176964
    �޸�����   : DTS201212345678:����BAND6,BAND19��֧��

*****************************************************************************/
VOS_VOID NAS_MM_GetSupportBandNum(VOS_UINT32 ulBand, VOS_UINT8 *pucBandNum)
{
    /* ucIndicator����������λָʾ */
    VOS_UINT8                           ucIndicator;

    /* ucTotalLen��ʾ��������usBand����bitλ�� */
    VOS_UINT8                           ucTotalLen;

    /* ucBandNum������¼bitֵΪ1�ĸ���������Ϊ�����ķ���ֵ */
    *pucBandNum = 0;
    ucIndicator = 0;
    ucTotalLen  = sizeof(ulBand) * 8;

    /* ͨ��ѭ����λ����ulBand�е�bitֵΪ1���ܸ����������浽ucBandNum�� */
    while (ucIndicator < ucTotalLen)
    {
        if ((ulBand>>ucIndicator) & 0x01)
        {
            (*pucBandNum)++;
        }

        ucIndicator++;
    }

    return;
}

/*******************************************************************************
  Module   : MM_Fill_IE_ClassMark2
  Function : ��д�տ���Ϣ�е�ClassMark2 IE (V)
  Input    : VOS_VOID *pAddr  ��дClassMark2 IE�ĵ�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.05.10  �¹�����
    2. ��    ��   : 2010��09��07��
       ��    ��   : w00167002
       �޸�����   : ���ⵥ�ţ�DTS2010090101367,RRC CONN setup cmp��Ϣ��Class mark2 ��д���ݲ���ȷ
   3. ��    ��   : 2010��11��1��
      ��    ��   : ŷ����
      �޸�����  : ���ⵥ��DTS2010102903975:RRC conn setup cmp��Ϣ��classmark2��RF power������ֵ����
   4. ��    ��   : 2010��12��22��
      ��    ��   : z00161729
      �޸�����  : DTS2010120900138:ֻ֧��900PƵ����פ��900P����£�classmark2��FCӦ���ϱ�Ϊ0
   5.��    ��   : 2011��07��14��
      ��    ��   : z00161729
      �޸�����   : V7R1 phase IIȫ�ֱ��������޸�,�滻classmark2
   6. ��    ��   : 2011��09��14��
      ��    ��   : f00179208
      �޸�����  : DTS2011062803354:CM Service Request��Ϣ��A53��Ϣ�������
   7. ��    ��   : 2012��11��06��
      ��    ��   : t00212959
      �޸�����  : DTS2012101005815:��֧��G�Ͳ���дGSM����
   8. ��    ��   : 2012��11��06��
      ��    ��   : t00212959
      �޸�����   : DTS2013022703646:��дClassMark2 IE��MML��ɣ��Ա�L����
*******************************************************************************/
VOS_VOID MM_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2                           /* ��дClassMark2 IE���׵�ַ                */
)
{
    NAS_MML_Fill_IE_ClassMark2(pClassMark2);

    return;
}

/*******************************************************************************
  MODULE   : MM_ComGetChanMode
  FUNCTION : GSM�����£�ת���ŵ�ģʽ
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746 2006.11.06 create for A32D06442
     2.��    ��  : 2008��12��2��
       ��    ��  : s62952
       �޸�����  : �������ⵥA32D07110�޸�

     3.��    ��   : 2012��2��9��
       ��    ��   : z40661
       �޸�����   : ֧��AMR-WB
*******************************************************************************/
MMCC_CHANNEL_MODE_ENUM_U32 MM_ComGetChanMode(NAS_RR_CHANNEL_MODE_ENUM_U8 enChanMode)
{
    MMCC_CHANNEL_MODE_ENUM_U32   enMmCcChanMode;

    switch(enChanMode)
    {
    case RR_CHAN_MOD_SINGAL_ONLY:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_FR:
        enMmCcChanMode = MMCC_CHAN_MOD_FR;
        break;
    case RR_CHAN_MOD_EFR:
        enMmCcChanMode = MMCC_CHAN_MOD_EFR;
        break;
    case RR_CHAN_MOD_AFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMR;
        break;
    case RR_CHAN_MOD_CSD_2400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_2400;
        break;
    case RR_CHAN_MOD_CSD_4800:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_4800;
        break;
    case RR_CHAN_MOD_CSD_9600:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_9600;
        break;
    case RR_NAS_DATA_CSD_14400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_14400;
        break;
    case RR_CHAN_MOD_HR:
        enMmCcChanMode = MMCC_CHAN_MOD_HR;
        break;
    case RR_CHAN_MOD_AHR:
        enMmCcChanMode = MMCC_CHAN_MOD_AHR;
        break;
    case RR_CHAN_MOD_H24:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_H48:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;

    case RR_CHAN_MOD_WFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMRWB;
        break;

    default :
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                            "MM_ComGetChanMode:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    }

    return enMmCcChanMode;
}

/*******************************************************************************
  MODULE   : Mm_ComSetMmState
  FUNCTION : �趨MM״̬
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.��    ��  : 2009��2��10��
       ��    ��  :
       �޸�����  :
     2.��    ��   : 2009��03��12��
       ��    ��   : ouyangfei id:00132663
       �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
     3.��    ��   : 2010��07��29��
       ��    ��   : l65478
       �޸�����   : ���ⵥDTS2010070502239,�����ó�PS only�󣬷���CS���У�Ȼ�����ó�CS ONLY��MMû�з���ע��
     4.��    ��   : 2010��08��21��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�DTS2010080502037��ע��״̬�ı�ͨ��MM IDLE״̬����
     5.��    ��   : 2012��9��07��
       ��    ��   : l00171473
       �޸�����   : DTS2012081701006, ���GMM״̬�Ŀ�ά�ɲ���Ϣ
     6.��    ��   : 2013��05��08��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     7.��    ��   : 2014��04��29��
       ��    ��   : y00245242
       �޸�����   : eCall��Ŀ�޸�
     8.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
     9.��    ��   : 2015��6��01��
       ��    ��   : j00174725
       �޸�����   : DTS2015053000044
    10.��    ��   : 2015��10��16��
       ��    ��   : j00174725
       �޸�����   : DTS2015101603066
    11.��    ��   : 2016��03��08��
       ��    ��   : l00356716
       �޸�����   : NAS���������Ż�
*******************************************************************************/
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
VOS_VOID Mm_ComSetMmState(NAS_MM_STATE_ENUM_UINT8 ulState)
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
{


#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MM_NotifySessionAccordingStateChg(g_MmGlobalInfo.ucState, ulState);
#endif

    if (( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (MM_IDLE_NORMAL_SERVICE == ulState))
    {
        g_MmGlobalInfo.ucState = MM_IDLE_LIMITED_SERVICE;
        g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComSetMmState:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
    else
    {
        g_MmGlobalInfo.ucState = ulState;
    }

    NAS_MM_LogMmStateInfo(g_MmGlobalInfo.ucState);

    switch(ulState)
    {
        case MM_STATE_NULL:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_IDLE_NO_IMSI:
        case MM_IDLE_NO_CELL_AVAILABLE:
            /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, begin */

            /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, end */
            break;

        case MM_CONNECTION_ACTIVE:
            /* ֹͣ��ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

            /*�յ����е�ʱ������FR*/
            if (MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
            {
                NAS_MM_SndTransactionStatusNotify(RRMM_TRANSACTION_CONNECTION_EST_SUCC);
            }
            NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);


            NAS_MM_ClearErrorLogInfo();


            break;

        default:
            break;
    }


    return;
}

/*****************************************************************************
 �� �� ��  : MM_LocalEndAllCalls
 ��������  : �����ͷ����еĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��02��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MM_LocalEndAllCalls(VOS_VOID)
{
    Mm_RcvRrmmRelInd();
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    return;
}
/*******************************************************************************
  MODULE   : Mm_GetServiceStatus
  FUNCTION : ��ȡ��ǰ�ķ���״̬��ԭ��ֵ
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.��    ��  : 2009��1��16��
       ��    ��  :
       �޸�����  :
*******************************************************************************/
VOS_VOID Mm_GetServiceStatus(VOS_UINT32 *pulCsServiceStatus, VOS_UINT32 *pulCsCause)
{
    *pulCsServiceStatus = g_MmGlobalInfo.ucMmServiceState;
    *pulCsCause = g_MmGlobalInfo.usCauseVal;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayDetach
 *  FUNCTION : PS ONLY�£�CSҵ����������Detach
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  s46746        09-06-23    �°�����
     2.��    ��   : 2010��07��29��
       ��    ��   : l65478
       �޸�����   : ���ⵥDTS2010070502239,�����ó�PS only�󣬷���CS���У�Ȼ�����ó�CS ONLY��MMû�з���ע��
     3.��    ��   : 2011��03��01��
       ��    ��   : A00165503
       �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                    ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
     6.��    ��   : 2012��03��03��
       ��    ��   : s62952
       �޸�����   : BalongV300R002 Build�Ż���Ŀ
     7.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     8.��    ��   : 2014��05��21��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ:PS ONLYҲ��Ҫ֧��ecall�Ļغ�,��˲���CS��detach
     9.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
     10.��    ��   : 2015��6��16��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayDetach()
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-21, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;

    enCallMode   = NAS_MML_GetCallMode();
#endif
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
#if (FEATURE_ON == FEATURE_ECALL)
     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-21, end */
    {
        Mm_TimerStop(MM_TIMER_T3212);

        if (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
        {
            /*Detach CS*/
            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)))
            {
                Mm_SndMmcDeRegisterInit();
            }
            else if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* ��������TIMER                            */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            }
            else
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
        }
        else if ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
              || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                   "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

        }
        else
        {
        }

        /*����attach not allow ��־*/
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComIsCsServExist
 *  FUNCTION : �жϵ�ǰCS���Ƿ���ҵ�����,����SS,SMS,CC
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_BOOL
 *  NOTE     :
 *  HISTORY  :
 *     1.  z40661        09-07-22    �°����� AT2D12429
       2.��    ��   : 2012��09��01��
         ��    ��   : s46746
         �޸�����  : DTS2012090405619:DCM�ⳡ����,����RAU��������ӦѰ��������abort
 ************************************************************************/
VOS_UINT32 Mm_ComJudgeCsServExist(VOS_VOID)
{
    VOS_UINT32                          ulRet = MM_CS_SERV_NONE_EXIST;

    if(  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {
            ulRet = MM_CS_SERV_EMERGENCY_CALL_EXIST;
        }
        else
        {
            ulRet = MM_CS_SERV_NORMAL_CALL_EXIST;
        }
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SS_EXIST;
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SMS_EXIST;
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        ulRet = MM_CS_SERV_MT_EXIST;
    }
    else
    {
        ;
    }

    return ulRet;
}




/*****************************************************************************
 �� �� ��  : NAS_MM_IsExistBufferService
 ��������  : �жϵ�ǰ�Ƿ�����л����ҵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��8��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsExistBufferService(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MM_GetSignalingStatus
 ��������  : �жϵ�ǰ�Ƿ��������HPLMN����
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��10��10��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��03��20��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D17070,������ָֹ������ʱ��MMC����û�з�������

*****************************************************************************/
VOS_UINT8  MM_GetSignalingStatus(VOS_VOID)
{
    /* ��ΪMMC��MM������������Ϣ��֪ͨ�ǲ����첽��Ϣ�������ڷ���PLMN����ǰ��Ҫ�ж�MM�ĵ�ǰ״̬��
    ��ע�����ȥע�������,������������ */
    if((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else if (VOS_TRUE == NAS_MM_IsExistBufferService())
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else
    {
        return MMC_MM_SIGNALING_STATUS_ABSENT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_CheckIfMmIsEstablishRRConnection
 ��������  : �жϵ�ǰMM�Ƿ����ڽ���
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  NAS_MM_CheckIfMmIsEstablishRRConnection()
{
    /* ��ΪMMC��MM������������Ϣ��֪ͨ�ǲ����첽��Ϣ�������ڷ���PLMN����ǰ��Ҫ�ж�MM�ĵ�ǰ״̬��
    ��ע�����ȥע�������,������������ */
    if( (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* �������� */

/*****************************************************************************
 �� �� ��  : NAS_MM_RetryCurrentProcedureCheck
 ��������  : �ж��Ƿ���Ҫ���·���ǰ����
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��26��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MM_RetryCurrentProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.4.4.9 f1/4.5.1.2 a1:
      a.1) RR connection failure in Iu mode (i.e. RRC connection release) with,
      for example, cause "Normal", "User inactivity" or "Directed signalling
      connection re-establishment" (see 3GPP TS 25.331 [32c] and 3GPP TS 44.118
      [111])
      The MM connection establishment procedure shall be initiated again, if
      the following conditions apply:
      i) The original MM connection establishment was initiated over an existing
      RRC connection; and
      ii) No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS) mess-
      ages relating to the CS signalling connection (e.g. CS authentication
      procedures, see subclause 4.3.2), were received after the CM SERVICE REQU-
      EST message was transmitted.
      NOTE 1:  The RRC connection release cause that triggers the re-initiation
      of the MM connection establishment procedure is implementation specific.*/

    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (   (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            && (VOS_TRUE == g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn)
            && (VOS_FALSE
                    == g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg)
            && (g_MmGlobalInfo.ucProc
                    == g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc))
        {
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT           == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T314_EXPIRED            == ulRelCause) )
            {
                ucRst = VOS_TRUE;
            }
        }
    }

    /* �ж���Ϻ����MM��·���Ʊ��� */
    NAS_MM_ClearMmLinkCtrlStru();

    return ucRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsRrRelCauseNeedRetryLau
 ��������  : ͨ�������ͷ�ԭ���ж��Ƿ���Ҫ���·���Lau
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��28��
    ��    ��   : w00167002
    �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
*****************************************************************************/
VOS_UINT8 NAS_MM_IsRrRelCauseNeedRetryLau(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;  /* [false alarm]:ucRst��Ϊ��ʼ��ֵ */

    switch ( ulRelCause )
    {
        case RRC_REL_CAUSE_RR_UNSPEC :
        case RRC_REL_CAUSE_NAS_DATA_ABSENT :
        case RRC_REL_CAUSE_RRC_ERROR :
        case RRC_REL_CAUSE_RL_FAILURE :
        case RRC_REL_CAUSE_OTHER_REASON :
        case RRC_REL_CAUSE_NO_RF :
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            ucRst = VOS_FALSE;
            break;

        default:
            ucRst = VOS_TRUE;
            break;
    }

    return ucRst;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_RetryMmConnectionProc
 ��������  : ���·���ǰ��MM CONNECTION����
 �������  : VOS_UINT8                           ucMMConnEstingPD
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RetryMmConnectionProc(
    VOS_UINT8                           ucMMConnEstingPD
)
{
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl;

    switch (ucMMConnEstingPD)
    {
        case MM_IE_PD_CALL_CONTROL:
            ucMmConnCtrl = MM_CONN_CTRL_CC;
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SS;
            break;
        case MM_IE_PD_SMS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SMS;
            break;
        default:
            ucMmConnCtrl = MM_CONN_CTRL_BUTT;
            NAS_WARNING_LOG1(WUEPS_PID_MM, "NAS_MM_RetryMmConnectionProc: unexpected ucMMConnEstingPD received: ", ucMMConnEstingPD);
            break;
    }

    if (MM_CONN_CTRL_BUTT != ucMmConnCtrl)
    {
        NAS_MM_EstMmConnection(ucMmConnCtrl);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetPDFromConnCtrlEnum
 ��������  : ����NAS_MM_CONN_CTRL_ENUMö�����ͻ�ȡ��Ӧ��MMConnEstingPD
 �������  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 �������  : UINT8                               *pucMMConnEstingPD
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_GetPDFromConnCtrlEnum(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucMMConnEstingPD
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            *pucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;
            break;
        case MM_CONN_CTRL_SS:
            *pucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
            break;
        case MM_CONN_CTRL_SMS:
            *pucMMConnEstingPD = MM_IE_PD_SMS_MSG;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_GetPDFromConnCtrlEnum: unexpected ucMmConnCtrl.");
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_EstMmConnection
 ��������  : ������MM CONNECTION
 �������  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��1��27��
   ��    ��   : o00132663
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������

*****************************************************************************/
VOS_VOID NAS_MM_EstMmConnection(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize;
    VOS_UINT8                           *pucCmSvcReq;
    VOS_UINT8                           ucCMSvcType;
    VOS_UINT32                          ulRrcEstCause;

    /* ������Ϣ�������ӽ������������������ѡ�����LU�ı䣬��LU��������Խ����ش� */
    NAS_MM_UpdateConnCtrlInfo(ucMmConnCtrl);

    NAS_MM_GetCMSvcType(ucMmConnCtrl, &ucCMSvcType);

    /* ���CM SERVICE REQUEST�ṹ��             */
    Mm_ComFillInCMSncReq(ucCMSvcType, MM_FALSE, &stCmSvcReq);

    /* ���CM SERVICE REQUEST ��Ϣ              */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&stCmSvcReq, &usMsgSize);
    if (VOS_NULL_PTR == pucCmSvcReq)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;
    }
    else
    {
        NAS_MM_GetRrcEstCause(ucMmConnCtrl, &ulRrcEstCause);

        Mm_SndRrEstReq(ulRrcEstCause, MM_FALSE, usMsgSize, pucCmSvcReq);

        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
    }

    NAS_MM_GetPDFromConnCtrlEnum(ucMmConnCtrl, &g_MmGlobalInfo.ucMMConnEstingPD);

    /* ��������TIMER                            */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsCcServiceNeedTriggerPlmnSearchNoRf
 ��������  : mm�յ�ccҵ���Ƿ���Ҫ֪ͨmmc��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��09��
    ��    ��   : c00318887
    �޸�����   : for Ԥ��Ƶ�������Ż�

*****************************************************************************/
VOS_UINT32 NAS_MM_IsCcServiceNeedTriggerPlmnSearch(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* ��������ʱ��Ҫ�������� */
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        return VOS_TRUE;
    }

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    /* ��ͨ�����ҿ���Чno rfʱ��Ҫ�������� */
    if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
     && (VOS_TRUE == ucSimCsRegStatus)
     && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType))
    {
        return VOS_TRUE;
    }
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateConnCtrlInfo
 ��������  : ����MM Connection������Ϣ
 �������  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateConnCtrlInfo(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ucFlg = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucRat = NAS_MML_GetCurrNetRatType();
    NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = g_MmCcEstReq.ulCallPri;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = g_MmCcEstReq.ulCallType;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallMode
                = g_MmCcEstReq.ulCallMode;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmCcEstReq.ulTransactionId;

            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_TRUE;
            }
            break;

        case MM_CONN_CTRL_SS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSsEstReq.ulTi;

            break;

        case MM_CONN_CTRL_SMS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetCMSvcType
 ��������  : ��ȡ��ǰ���е�MM CONNECTION���̵�CM Service ����
 �������  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
 �������  : VOS_UINT8                           *pucCmSrvType
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_GetCMSvcType(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucCmSrvType
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_MO_CALL_EST;
            }
            else
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_EMG_CALL_EST;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SS_ACT;
            break;

        case MM_CONN_CTRL_SMS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SMS;
            break;

        default:
            *pucCmSrvType = 0;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetRrcEstCause
 ��������  : ��ȡ����RRC���ӵ�ԭ��ֵ
 �������  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
 �������  : VOS_UINT32                          *pulRrcEstCause
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_GetRrcEstCause(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT32                          *pulRrcEstCause
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            }
            else
            {
                *pulRrcEstCause = RRC_EST_CAUSE_EMERGENCY_CALL;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;

        case MM_CONN_CTRL_SMS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;
            break;

        default:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateMmLinkCtrlStru
 ��������  : ����MM�����ͷſ��ƽṹ
 �������  : NAS_MM_COM_PROCEDURE_ENUM_UINT8     ucCurrentProc
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��3��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е�ȫ�ֱ���
*****************************************************************************/
VOS_VOID NAS_MM_UpdateMmLinkCtrlStru(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = g_MmGlobalInfo.ucProc;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    /* ��鵱ǰ�����Ƿ����ѽ�����RRC�����Ϸ��� */
    if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    }
    else
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ClearMmLinkCtrlStru
 ��������  : ���MM��·���ƹ�����ر���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��9��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ClearMmLinkCtrlStru( VOS_VOID )
{
    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = MM_NULL_PROC;
    g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ClearConnCtrlInfo.g_MmGlobalInfo
 ��������  : ���MM ConnCtrlInfoȫ�ֱ����ı�־λ
 �������  : VOS_UINT8 ucMMConnEstingPD - ��ǰ������ҵ������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��5��15��
    ��    ��   : w00167002
    �޸�����   : DTS2013051408623:����CS BUFFER STATUSʱ����ϰ������ֱ�Ӹ���
                 ���治���ڴ��ڷ���NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE)��
                 �޸�Ϊ����NAS_MM_UpdateCsServiceBufferStatusFlg���������»����
                 ҵ��״̬��

*****************************************************************************/
VOS_VOID NAS_MM_ClearConnCtrlInfo(VOS_UINT8 ucMMConnEstingPD)
{
    if(MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else
    {
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/* Modified by z00161729 for DCM�����������������, 2012-9-5, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ClearConnCtrlInfoExcEmgCall
 ��������  : ���MM ConnCtrlInfoȫ�ֱ����ı�־λ,�������в����
 �������  : VOS_UINT8 ucMMConnEstingPD - ��ǰ������ҵ������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��4��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ClearConnCtrlInfoExcEmgCall(VOS_UINT8 ucMMConnEstingPD)
{
    if ((MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
     && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}
/* Modified by z00161729 for DCM�����������������, 2012-9-5, end */

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcEstCnfSuccessCauseAtState12
 ��������  : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬�£��յ�RRMM_EST_CNF(�ɹ�)�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��23��
    ��    ��   : w00167002
    �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                  �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                  T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
  3.��    ��   : 2014��03��04��
    ��    ��   : z00161729
    �޸�����   : DTS2014022800234:����mm�յ�paging������csҵ���������Ӵ��ڣ�����ѯ^usersrvstateʱ������csҵ��syscfgex����ʧ�ܻظ�����csҵ�񣬲�һ��
  4.��    ��   :2015��3��13��
    ��    ��   :n00269697
    �޸�����   :CHR �Ż���Ŀ
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfSuccessCauseAtState12(VOS_VOID)
{
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* �Ƿ�֧��cs����ҵ�������ͨ������vpҵ��VOS_TRUE:֧��cs����ҵ��VOS_FALSE:��֧��cs����ҵ��*/

    ulIsTestCard          = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    if ( (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI))
    {
        Mm_TimerStart(MM_TIMER_T3230);
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION");
    }
    else
    {
        /* ������Ѱ����������ӽ���                 */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");

        NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

        if ( (VOS_TRUE  == ulIsTestCard)
          && (VOS_FALSE == ucSupportCsServiceFlg) )
        {
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
        }
        else
        {
            /*A32D12629==>�ڴ��ڼ���ܷ���Ƶ���ض��壬ʱ��Ϊ50�룬������Ӷ�ʱ������*/
            gstMmTimer[MM_TIMER_T3240].ulTimerLen += 50000;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen -= 50000;
        }
        /*<==A32D12629*/
    }

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_InformCmLayerEstFail
 ��������  : ֪ͨ�ϲ�Ӧ��ģʽ������ʧ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_InformCmLayerEstFail(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        /* CC�����RR���ӵĽ���, ֪ͨCC����ʧ��             */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                        enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        /* SS�����RR���ӵĽ��� ��֪ͨSS,MM���ӽ���ʧ��      */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        /* SMS�����RR���ӵĽ��� ,֪ͨSMS,MM���ӽ���ʧ��      */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else
    {
        /* û�����ڽ�����MM���ӣ�������             */
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcEstCnfOtherFailCauseAtState12
 ��������  : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬�£��յ�RRMM_EST_CNF(ʧ��,���ض�ԭ��ֵ)�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : DTS2013041602825:CSFB���ӽ���ʧ�ܺ�û�з���LU
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  5.��    ��   :2015��3��10��
    ��    ��   :n00269697
    �޸�����   :CHR�Ż���Ŀ��ɾ��CHR����ļ�¼��CS PAGING FAIL
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfOtherFailCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    VOS_UINT8               ucTiValidFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_InformCmLayerEstFail(ulResult);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_ProcEstCnfOtherFailCauseAtState12:NORMAL: ucState = ",
                    g_MmGlobalInfo.ucState);

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    /* ��Ϊ����Mm_ComChkLu���Ƿ�ǰ������̬���ж�,���������ӽ���ʧ��ʱ,
       ����ֱ�ӵ��ô˺���,��Ҫ����NAS_MM_CheckLuAfterCsConnectRelease���д��� */
    if ( MM_FALSE == NAS_MM_ProcessLuAfterCsConnectNotExist() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            /* ɾ��CHR����ļ�¼��CS PAGING FAIL */
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );

        Mm_ComCheckDelayDetach();
    }
    else
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else
        {
            /* ɾ��CHR����ļ�¼��CS PAGING FAIL */
            ;
        }
    }

    if ( g_T3211Flag )
    {
        Mm_TimerStart(MM_TIMER_T3211);
        g_T3211Flag = 0;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ProcEstCnfCauseAtState12
 ��������  : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬�£��յ�RRMM_EST_CNF��Ĵ���
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult - �������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : ɾ��С����ֹҵ����,��ϵͳ��Ϣ��AC INFO CHANGE��Ϣ��������

  5.��    ��   : 2013��8��22��
    ��    ��   : w00167002
    �޸�����   : DTS2013081604476:w��ѡ��G�º󣬱�����ָ�ɾܾ���GAS����T3122
                  ��ʱ���������û�����绰��NAS����LAU,GAS����T3122���У�ֱ�ӻظ�
                  ����ʧ�ܡ�MM������T3211,�����ֳ����£�NAS����Ҫ����T3211��ʱ����
  6.��    ��   : 2013��4��1��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�RRC_EST_RJ_NO_RF�Ĵ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    switch (ulResult)
    {
        case RRC_EST_SUCCESS:
        case RRC_EST_PRESENT:
            NAS_MM_ProcEstCnfSuccessCauseAtState12();
            break;
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        case RRC_EST_RJ_SNW:
        case RRC_EST_RJ_NO_RF:                                                     /* RR Connection failed because of no rf */
        case RRC_EST_RJ_T3122_RUNNING:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_OTHER_ACCESS_BARRED:
            /* ��Ҫ�������ޣ����ñ�־λ */
            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_PAGING_ACCESS_BARRED:
            /* ��Ҫ�������ޣ����ñ�־λ */
            NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_CELL_BAR:
            /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-18, begin */
            /* �ǽ������в���������ע���Ѱ����� */
            if (MMCC_EMERGENCY_CALL !=  g_MmCcEstReq.ulCallType)
            /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-18, end */
            {
                /* �������ޣ����ñ�־λ */
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
            }

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: ulResult Abnormal");
            break;
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeFullNameForNetworkIe
 ��������  : ����Full Name for Network IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
     VOS_UINT8     - *pucLongNetWorkNameExist : IE��Ч��־
 �� �� ֵ  : MM_DECODE_RESULT_ENUM_U32 - ��ϢIE�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2013010809507���������ϱ�����
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFullNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucLongNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;

        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
                if (NAS_MML_MAX_OPER_LONG_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_LONG_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeShortNameForNetworkIe
 ��������  : ����Short Name for Network IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
     VOS_UINT8     - *pucShortNetWorkNameExist : IE��Ч��־
 �� �� ֵ  : MM_DECODE_RESULT_ENUM_U32 - ��ϢIE�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2013010809507���������ϱ�����
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeShortNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucShortNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                if (NAS_MML_MAX_OPER_SHORT_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeLocalTimeZoneIe
 ��������  : ����Local Time Zone IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
 �� �� ֵ  :
     MM_DECODE_RESULT_ENUM_U32 - �������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalTimeZoneIe:WARNING: Local Time Zone Value ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe
 ��������  : ����Universal Time And Local Time Zone IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
 �� �� ֵ  :
     MM_DECODE_RESULT_ENUM_U32 - ��ϢIE�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��7��20��
    ��    ��   : ŷ����
    �޸�����   : DTS2010072001259����IE���ʧ��ʱ�����Ը���Ϣ�������ٸ�����
                 �ظ�MM STATUS��Ϣ
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimAndTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe:WARNING: Universal Time and Zone value error!");
        }
        usIndex = usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeLocalizedServiceAreaIe
 ��������  : ����Localize Service Area IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
 �� �� ֵ  : MM_DECODE_RESULT_ENUM_U32 - ��ϢIE�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalizedServiceAreaIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if (usIeLen > MM_IE_LSA_IDENTITY_VALUE_MAX_LEN)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkLsaIdtfr( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ))
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DecodeNetworkDaylightSavingTimeIe
 ��������  : ����Network Daylight Saving Time IE
 �������  :
     VOS_UINT8     - *pucRcvMsg  : ��Ϣָ��
     VOS_UINT16    - usMsgSize,  : ��Ϣ����
     VOS_UINT16    - *pusIndex,  : ��ǰ������Ϣλ��
 �������  :
     VOS_UINT8     - *pucEventId : �¼�ID
 �� �� ֵ  : MM_DECODE_RESULT_ENUM_U32 - ��ϢIE�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeNetworkDaylightSavingTimeIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];
        if ( MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_VALUE_LEN !=  usIeLen)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }

        if ( MM_FALSE == MM_IeChkDayLightSavTim( &pucRcvMsg[usIndex + 1]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsInRegisterProcedure
 ��������  : �жϵ�ǰ�Ƿ���ע�������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��10��10��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MM_IsInRegisterProcedure(VOS_VOID)
{
    /* �жϵ�ǰ�Ƿ���ע������� */
    if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_NeedSendEPlmnConnFail
 ��������  : �ж�CS�����ͷ��Ƿ���Ҫ����EPLMN�������
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��3��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL NAS_MM_NeedSendEPlmnConnFail()
{
    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
      && (1 == g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsPLmnIdInEplmnList
 ��������  : �жϵ�ǰPLMN ID�Ƿ���EPLMN��RPLMN��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��11��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MM_IsPLmnIdInEplmnList (
    MM_PLMN_ID_STRU                    *pstPlmnId
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList    =   NAS_MML_GetEquPlmnList();
    for ( i = 0 ; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if ( ( pstPlmnId->ulMcc == pstEplmnList->astEquPlmnAddr[i].ulMcc)
          && ( pstPlmnId->ulMnc == pstEplmnList->astEquPlmnAddr[i].ulMnc))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertToMmcServiceStatus
 ��������  : ��MM�ķ���״̬ת��ΪMMC�ķ���״̬
 �������  : VOS_UINT8                           ucMmServiceStatus
             MMCMM_LU_RESULT_IND_STRU           *pMmcLuRstInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��15��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToMmcServiceStatus(
    VOS_UINT8                           ucMmServiceStatus,
    VOS_UINT32                         *pCsServiceStatus
)
{
    switch(ucMmServiceStatus)
    {
        case MM_NORMAL_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NORMAL_SERVICE;
            break;
        case MM_LIMITED_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_NO_IMSI:
            *pCsServiceStatus = MM_COM_SRVST_NO_IMSI;
            break;
        case MM_NO_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NO_SERVICE;
            break;
        case MM_LIMIT_REGION_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            *pCsServiceStatus = MM_COM_SRVST_NO_CHANGE;
            break;
        case MM_DETACHED:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_DISABLE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_HandleGmmCauseValAsLuAccept
 ��������  : MMλ�ø��³ɹ������GMM attach/rauʧ��ԭ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��7��
    ��    ��   : 12
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_HandleGmmCauseValAsLuAccept()
{
    if ((MM_GMM_ATTACH_PROC == g_MmGlobalInfo.ucProc)
     || (MM_GMM_RAU_PROC == g_MmGlobalInfo.ucProc))
    {
        if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW  == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal))
        {
            Mm_ComProcCauseClear();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateCsServiceConnStatusFlg
 ��������  : ���ݵ�ǰ����״̬����CS���ҵ�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��3��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCsServiceConnStatusFlg(VOS_VOID)
{
    if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

    if ( ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateCsServiceBufferStatusFlg
 ��������  : ����CS�򻺴�ҵ���Ƿ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��3��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCsServiceBufferStatusFlg(VOS_VOID)
{
    if ( ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetLikeBFlg
 ��������  : ����LIKE B��־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��3��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_SetLikeBFlg(VOS_VOID)
{
    if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ��ȫ����                  */
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_WriteRplmnWithRatNvim
 ��������  : дNV: en_NV_Item_RPlmnWithRat
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID NAS_MM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU    stRplmn;

    stRplmn.ucLastRplmnRat          = (VOS_UINT8)pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if(NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsGURplmnChanged
 ��������  : �ж�lau�ɹ���RPLMN�Ƿ�ı�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE:RPLMN�ı�
             VOS_FALSE:RPLMNδ�ı�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��08��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulGRplmnCompareRslt;
    VOS_UINT32                          ulWRplmnCompareRslt;

    /* Ĭ��RPlmn�ȽϽ��δ�����ı� */
    ulGRplmnCompareRslt = VOS_TRUE;
    ulWRplmnCompareRslt = VOS_TRUE;

    /* ���ڻ�ȡRPLMN�Ķ���������Ϣ */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* �ж�ȫ�ֱ����е�LastRPLMN�Ľ��뼼���Ƿ����ı� */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        /* RPlmn��Ϣ�����˸ı䣬����VOS_TRUE */
        return VOS_TRUE;
    }

    /* �ж�ȫ�ֱ����е�˫RPLMN�Ƿ�֧�� */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stGRplmnInNV);

        ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stWRplmnInNV);
    }
    else
    {
        /* ֧��˫RPLMN, ��ֻ�ж϶�Ӧ���뼼����RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stGRplmnInNV);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stWRplmnInNV);
        }
        else
        {
            ;
        }
    }

    /* RPlmn�ȽϽ����VOS_FALSE��ʾ�����˸ı� */
    if ((VOS_FALSE == ulGRplmnCompareRslt)
     || (VOS_FALSE == ulWRplmnCompareRslt))
    {
        /* RPlmn��Ϣ�����˸ı䣬����VOS_TRUE */
        return VOS_TRUE;
    }

    /* RPlmn��Ϣδ�����ı䣬����VOS_FALSE */
    return VOS_FALSE;

}



/*****************************************************************************
 �� �� ��  : NAS_MM_GenerateEPlmnInfo
 ��������  : ��RPlmn���뵽����Я����EPlmn�б��У�
              ��EPLMN�б���ɾ����Ч ����ֹ�Ͳ��������ε�����
 �������  : ulLauAcceptPlmnNum:lau accept�д���EPLMN����
              pHandlingPlmnList:lau accept�д���EPLMN��Ϣ
 �������  : pstEquPlmnInfo:MML�����EPLMN��Ϣ
 �� �� ֵ  : VOS_TRUE:EPLMN�ı�
              VOS_FALSE:EPLMNδ�ı�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_GenerateEPlmnInfo(
    VOS_UINT32                          ulLauAcceptPlmnNum,
    MM_PLMN_ID_STRU                    *pstLauAcceptPlmnList,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId       = VOS_NULL_PTR;

    /* ��������Eplmn����������15�� */
    if (ulLauAcceptPlmnNum > NAS_MML_MAX_NETWORK_EQUPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_GenerateEPlmnInfo:NETWORK EPlmn NUMBER > 15");
        ulLauAcceptPlmnNum = NAS_MML_MAX_NETWORK_EQUPLMN_NUM;
    }

    /* ����ӵ�ǰפ����plmn��Ϣ��EPlmn�б��� */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;
    pstEquPlmnInfo->ucEquPlmnNum = 1;

    /* ��������EPlmn��EPLMN��Ϣ�ӵ�һ��λ�ÿ�ʼ��¼ */
    for ( i = 0; i < ulLauAcceptPlmnNum; i++ )
    {
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMcc = pstLauAcceptPlmnList[i].ulMcc;
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMnc = pstLauAcceptPlmnList[i].ulMnc;
        pstEquPlmnInfo->ucEquPlmnNum += 1;
    }

    /* ��EPLMN�б���ɾ����Ч ����ֹ�Ͳ��������ε����� */
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);

    return ;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn
 ��������  : ��MML��ʽ��PlmnIDת��ΪNvim��Eplmn
              23002f(MML�ĸ�ʽ Mcc:0x000302,Mnc:0x0f0200)-->2,3,0,0,2,f
 �������  : pstPlmnId: MML��PLMN ID
 �������  : pstNvimPlmnId: NvimEPlmn��ʽ
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��03��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* ת��MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* ת��MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertMmlEquListToNvimEquPlmnList
 ��������  : ��MML��ʽ��Eplmn�б�ת��ΪNvim��Eplmn�б�
 �������  : pstMmlEPlmnList: MML��EplmnList
 �������  : pstNvimEPlmnList:Nvim��ʽ��EPlmnList
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��03��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsInNvEplmnList
 ��������  : �ж�PLMN ID�Ƿ���NV�е�EPLMN LIST�б���
 �������  : pstPlmnId:��Ҫ�жϵ�PLMN ID
             ucPlmnNum:PLMN ID����
             pstPlmnIdList:PLMN ID�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID��NV�е�EPLMN LIST�б���
             VOS_FALSE : PLMN ID����NV�е�EPLMN LIST�б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
    1.��    ��   : 2012��03��15��
      ��    ��   : l00130025
      �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_UINT32 NAS_MM_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNvimEPlmnListEqual
 ��������  : �ж�2��NVIM_EQUIVALENT_PLMN_LIST_STRU�Ƿ���ͬ
 �������  : pstNvimEPlmnList1,pstNvimEPlmnList2���Ƚϵ�2��NvimPlmnList
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : 2��EplmnList��ͬ
              VOS_FALSE : 2��EplmnList��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
    1.��    ��   : 2012��03��15��
      ��    ��   : l00130025
      �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn��������0,��Rplmn��ͬʱ��EplmnList����ͬ */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
                                                 1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* ����Eplmnû�н������������ظ����ݣ���Ҫ�Ա�2���б����ȷ����ͬ */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
                                                 pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_DeleteEPlmnList
 ��������  : ���EPLMN�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_MM_DeleteEPlmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList = NAS_MML_GetEquPlmnList();

    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* ���NV�б����EPLMN */
    NAS_MM_WriteEplmnNvim( pstEPlmnList );

    /*����ǰ�������Eplmn�б�*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_WriteEplmnNvim
 ��������  : ��Eplmn���µ�NV��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_MM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
)
{

    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;

    ulUpdateNvFlag  = VOS_FALSE;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MM,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_MM,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_MM_ConvertMmlEquListToNvimEquPlmnList(pstEplmnAddr,
                                              pstNewNvEquPlmnList);

    /* ��ȡNV��EPLMN��Ϣ */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)) )
    {
        if (VOS_FALSE == NAS_MM_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                     pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_MM, pstOldNvEquPlmnList);

}

/*****************************************************************************
�� �� ��  : NAS_MM_UpdateEquPlmnInfo
��������  : �ж��Ƿ���Ҫ��ʼ��EPLMN��Ϣ
�������  : ulCause :LUʧ�ܵ�ԭ��ֵ
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��  : 2011��10��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��03��15��
  ��    ��   : l00130025
  �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_MM_UpdateEquPlmnInfo(
    VOS_UINT32                          ulCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* ���LAUʧ�ܣ���Ҫ�ж��Ƿ�ɾ��EPLMN */
    switch (ulCause)
    {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            NAS_MM_DeleteEPlmnList();

            break;

        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        case NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM:
        case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        case NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT:

            break;

        default:
           /* ����ԭ��ֵ�����LAU attempt acounter����Roam broker����ע��ʧ�ܵĴ�������Ҫ���EPLMN */
           if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
            || (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= MM_CONST_NUM_4)
            || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                NAS_MM_DeleteEPlmnList();

            }
           break;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_CsSimValid
 ��������  : �ṩ������Ϣģ���ȡCS SIM���Ƿ���Ч
 �������  : ��
 �������  : VOS_BOOL *pbCsSimValids
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : ��ϰ��/s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid)
{
    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {
        *pbCsSimValid = VOS_TRUE;
    }
    else
    {
        *pbCsSimValid = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_CsCellBar
 ��������  : �ṩ������Ϣģ���ȡUEפ��С��CS���Ƿ�BAR
 �������  : ��
 �������  : VOS_BOOL *pCsCellBar  CS���Ƿ�BAR
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : ��ϰ��/s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  3.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
*****************************************************************************/
VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar)
{
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
    {
        *pbCsCellBar = VOS_TRUE;
    }
    else
    {
        *pbCsCellBar = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetLauUptNeededCsSrvStatus
 ��������  : ��ȡMM_IDLE_LOCATION_UPDATE_NEEDED״̬ʱCS�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 CS�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_MM_GetLauUptNeededCsSrvStatus(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* ��ǰLAI���ϴ�ע��ɹ�LAI��ͬ���Ҹ���״̬ΪU1 */
    if((VOS_FALSE == NAS_MML_IsCsLaiChanged())
    && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
    && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        return MM_COM_SRVST_LIMITED_SERVICE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated
 ��������  : MM_IDLE_LOCATION_UPDATE_NEEDED U1 ״̬ʱCSע������ޱ�Ϊ�����޵Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��

*****************************************************************************/
VOS_VOID  NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated()
{
    /* ���LAI����,����״̬ΪU1 */
    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* ����LU����                               */
            Mm_ComLuOnly();
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* ���÷���״̬                             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
    else
    {
        /* ��ǰ���ϵ翪�� */
        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* ����LU����                               */
            Mm_ComLuOnly();                                                     /* ����LU REQ                               */
        }
        else if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* ����LU����                               */
            Mm_ComLuOnly();                                                     /* ����LU REQ                               */
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* ���÷���״̬                             */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
}
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated
 ��������  : MM_IDLE_LOCATION_UPDATE_NEEDED ��U״̬ʱCSע������ޱ�Ϊ������,����ģʽII�Ĵ���
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

  3.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.sunxibo�߶�T3212��ʱ��ʱ����Ϊ0�ŷ���LAU.

*****************************************************************************/
VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)                                 /* �տ�����λ�������䣬Ҳ����ע�� */
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����                               */
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
        return;
    }


    /* �ڷ�U1״̬��������ע�ᶨʱ��û������ʱ,Ҫ����һ��LU���� */
    if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
     && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
     && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        }

        Mm_ComLuOnly();
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                /* ���÷���״̬                             */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCsAcChgRegisterNetModeII
 ��������  : MM_IDLE_LOCATION_UPDATE_NEEDED CSע������ޱ�Ϊ������
             ����ģʽII�µĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeII(VOS_VOID)
{
    /* LAI�����ı� */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        Mm_TimerStop(MM_TIMER_T3213);
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����                               */
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
    }
    else
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            /* ��ǰCS UPDATE״̬ΪU1 */
            NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated();
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated();
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar
 ��������  : ҵ������У�CS BAR TO UNBAR����MM״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 CS�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��7��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*****************************************************************************/
VOS_VOID NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucStaOfRcvXXEstReq)
    {
        return;
    }

    /* ��ǰCS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* �û����ò�֧��CS */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* ��ǰ�����ڽ�ֹ�б��� */
    if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* ��ǰCS ATTACH״̬��LAIû�иı䣬����״̬ΪU1 */
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, begin */
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, end */
     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
     && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_NORMAL_SERVICE;
    }
    else
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MM_ProcEccNumList_RcvSysinfo
 ��������  : MM�յ�ϵͳ��Ϣ�󣬶Խ������б�Ĵ���
 �������  : pSysInfoInd ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��5��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��04��03��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.CurLai�滻��MML�е�
  3.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_ProcEccNumList_RcvSysinfo(
    VOS_UINT32                          ulMcc
)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     EmcNumLst;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId        = VOS_NULL_PTR;

    pstCurPlmnId  = NAS_MML_GetCurrCampPlmnId();

    pstEmergencyNumList = NAS_MML_GetEmergencyNumList();

    /* ��Ϣ�а������������б�֮ǰ�洢�˽������б�,�������ͬһ�����ҵ�mcc��ɾ��֮ǰ�洢�Ľ��������б�
    24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6��4.7.3.1.3��4.7.5.1.3��������:
    The emergency number(s) received in the Emergency Number List IE are valid only
    in networks with in.the same MCCcountry as in  the cell on which this IE
    is received.*/
    if (VOS_FALSE == NAS_MML_ComparePlmnMcc(ulMcc, pstCurPlmnId->ulMcc))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    {                                                                       /* ��С����MCC���ϴ�פ��С����MCC��ͬ       */
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, pstEmergencyNumList->ulMcc))
        {
            Mm_SndCcEmergencyNumberList(pstEmergencyNumList);               /* ֪ͨCC���������� */
        }
        else
        {
            EmcNumLst.ulMcc             = ulMcc;
            EmcNumLst.ucEmergencyNumber = 0;

            PS_MEM_SET(EmcNumLst.aucEmergencyList, 0xFF, NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS);
            Mm_SndCcEmergencyNumberList(&EmcNumLst);                            /* ֪ͨCC������������Ч                     */
        }
    }

    return;
}


#if (FEATURE_LTE == FEATURE_ON)

/*****************************************************************************
 �� �� ��  : NAS_MM_IsLInterSysGuLauNeededLaiNoChange
 ��������  : �ж�L��ϵͳ��GU��LAIû�ı��Ƿ�Ҳ��Ҫ����LAU
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��ҪLAU
              VOS_FALSE:����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��21��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��05��21��
    ��    ��   : z40661
    �޸�����   : DTS2012052308001:��L��ѡ��G�󷴸�����LAU
  3.��    ��   : 2013��12��14��
    ��    ��   : f00261443
    �޸�����   : Volte_PhaseIII:���UE֧��IMS����ʹLaiû�б仯����ǿ��Lau�ĵ�nv��򿪣�����Ҫ����LAU
  4.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
  5.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
VOS_UINT32  NAS_MM_IsLauNeededLaiNoChange_LInterSys(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;

    VOS_UINT8                                               ucLauForceFlg;
    VOS_UINT8                                               ucImsVoiceAvailFlg;

    enLteCsServiceCfg   = NAS_MML_GetLteCsServiceCfg();

    /**
     * ������Ǵ� L ��ϵͳ�任 �򲻽��к����ж�
     */
    if (NAS_MML_NET_RAT_TYPE_LTE != g_MmGlobalInfo.enPreRatType)
    {
        return VOS_FALSE;
    }

    /* ���CSҵ������ΪSMS over SGs������TIN����Ϊ"GUTI" */
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && ((NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)))
    {
        return VOS_TRUE;
    }

    /**
     * �������������UE֧��IMS����ȡNv��������ѡ����CS ONLY)
     * �ҿ��ƴ�L��GU�¼�ʹLAIû�иı�Ҳ��Ҫ����LAU��Nv��򿪣�
     * ֻҪ��CSFB��������Ҫ����LAU
     */
    /**
     * VDF�ı���Ҫ��֧��IMS voice���ն��ڴ�L��ϵͳ�任��GU������������һ��LAU,ԭ�����£�
     * The LTE terminal supporting Voice over IMS (GSMA IR.92),
     * shall always issue a Location Update following a RAT change.
     * With terminal in IDLE mode a LAU is performed.
     * If a call is initiated under CS network,
     * all the procedures currently in use today shall be applicable.
     * For example, when a terminal that initially registers on 2G roams into LTE coverage,
     * then roams back into 2G under the same LAC that it previously registered,
     * will it always send a LU towards the MSC.
     */

    ucLauForceFlg = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    ucImsVoiceAvailFlg = NAS_MML_GetImsVoiceAvailFlg();

    if ((VOS_TRUE == ucLauForceFlg)
     && (VOS_TRUE == ucImsVoiceAvailFlg))
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
     && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg))
    {
        return VOS_TRUE;
    }

    /* 23122_CR0122R1_(Rel-8)_C1-083459 23122 4.5.2�½���������:
    -The MS detects that it has entered a registration area that has the same identity
    as the one stored in the MS, while being in the ROAMING NOT ALLOWED update state,
    and the LAI or the PLMN identity is not contained in any of the lists of "forbidden LAs for roaming",
    "forbidden LAs for regional provision of service", "forbidden PLMNs for GPRS service"
    or "forbidden PLMNs" respectively. */
    if (NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    /* TS 24301 5.5.3.3.6�½���������:
     * 3)otherwise, the abnormal cases specified in subclause 5.5.3.2.6 apply with the following modification.
     *   If the tracking area updating attempt counter is incremented according to subclause 5.5.3.2.6 the next actions depend on
     *   the value of the tracking area updating attempt counter.
     *   - If the tracking area updating attempt counter is less than 5, the UE shall set the update status to U2 NOT UPDATED,
     *     but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
     *
     * TS 23122 4.5.2�½���������:
     * - the MS changes cell while the update status is "NOT UPDATED";(for MS capable of GPRS and non-GPRS services when at least
     *   one of both update statuses is "NOT UPDATED")
     */

    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsT3412ExpiredNeedRegist
 ��������  : T3412��ʱ����ģʽII�Ƿ���ҪLAU
 �������  : enLteCsServiceCfg - UE֧�ֵ�cs ҵ������
             enTinType         - TIN����
             enT3412Status     - T3412��ʱ��״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����ע��
             VOS_FALSE - ����Ҫ����ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
)
{
     /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((NAS_MML_TIMER_EXP == enT3412Status)
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsT3423StatusChangeNeedRegist
 ��������  : T3423������ʱ��ʱ����ģʽII�Ƿ���ҪLAU
 �������  : enLteCsServiceCfg - UE֧�ֵ�cs ҵ������
             enTinType         - TIN����
             enT3423Status     - T3423��ʱ��״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����ע��
             VOS_FALSE - ����Ҫ����ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
)
{
      /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
       The normal location updating procedure shall also be started when the MS,
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       enters a GERAN or UTRAN cell in network operation mode II or III and the
       E-UTRAN deactivate ISR timer T3423 has expired.

       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       -   when the MS enters a GERAN or UTRAN cell in network operation mode II
       or III and the E-UTRAN deactivate ISR timer T3423 is running.
    */
    if (((NAS_MML_TIMER_START == enT3423Status)
      || (NAS_MML_TIMER_EXP == enT3423Status))
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_WriteTinInfoNvim
 ��������  : ����TIN INFO�����ݵ�NVIM
 �������  : enTinType - TIN����
             pucImsi   - IMSI
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��15��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  NAS_MM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU              stTinInfo;
    /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, end */

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    if (pstRplmnCfgInfo->enTinType != enTinType)
    {
        /* �ȸ���MML�Ĳ��� */
        pstRplmnCfgInfo->enTinType  = enTinType;
        PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

        /* �ٸ���NVIM�еĲ��� */
        stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
        PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
        PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

        /* ������NVIM�� */
        if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                               &stTinInfo,
                               sizeof(stTinInfo)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteTinInfoNvim:Write NV Failed");
        }

        /* ��ά�ɲ⣬����Ϣ */
        NAS_MM_LogTinTypeInfo(enTinType);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LogTinTypeInfo
 ��������  : MM ����TIN����ʱ��Ҫ����Ϣ������trace��
 �������  : enTinType - TIN����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��17��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_MM_LOG_TIN_INFO_STRU           *pstTinTypeInfo = VOS_NULL_PTR;

    pstTinTypeInfo = (NAS_MM_LOG_TIN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                             sizeof(NAS_MM_LOG_TIN_INFO_STRU));

    if ( VOS_NULL_PTR == pstTinTypeInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogTinTypeInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstTinTypeInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_TIN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstTinTypeInfo->stMsgHeader.ulMsgName       = NAS_MM_LOG_TIN_TYPE_INFO_IND;

    pstTinTypeInfo->enTinType = enTinType;

    DIAG_TraceReport(pstTinTypeInfo);

    PS_MEM_FREE(WUEPS_PID_MM, pstTinTypeInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedDeactiveIsrLauInit
 ��������  : LAU����ʱ�Ƿ���Ҫȥ����ISR
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫȥ����ISR
             VOS_FALSE - ����Ҫȥ����ISR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��29��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedDeactiveIsrLauInit(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;
    VOS_INT8                                                cVersion;


    cVersion       = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();

    /* 24008_CR1902R1_(Rel-11)_C1-113481-c1-113200-tin 24008 4.4.4.1��������:
    If the mobile station is configured to use CS fallback and SMS over SGs, or SMS over SGs only,
    and TIN indicates "RAT-related TMSI" the mobile station shall set the TIN to "P-TMSI"
    unless the mobile station had already received the EMM cause #18 during a combined
    attach procedure (see subclause 5.5.1.3.4.3 of 3GPP TS 24.301 [120]) or a combined
    tracking area updating procedure (see subclause 5.5.3.3.4.3 of 3GPP TS 24.301 [120])
    on the same PLMN, but not disabled the E-UTRAN capability.*/
    enTinType         = NAS_MML_GetTinType();
    enLteCsServiceCfg = NAS_MML_GetLteCsServiceCfg();

    if (((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
       || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
     && (cVersion >= PS_PTL_VER_R11))
    {
        if ((VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapStatus)
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapStatus))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedDeactiveIsrAfterLau
 ��������  : LAU�������Ƿ���Ҫȥ����ISR
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫȥ����ISR
             VOS_FALSE - ����Ҫȥ����ISR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��15��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedDeactiveIsrAfterLau(VOS_VOID)
{
    VOS_UINT32                                             ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                             ulT3412StatusChgNeedRegFlg;

    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function����ȥ����ISR������
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
     || (VOS_TRUE == ulT3412StatusChgNeedRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvSysInfoSurpportLte_PreProc
 ��������  : ֧��LTEʱ���յ�ϵͳ��Ϣ��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - Ԥ�������
             VOS_FALSE - Ԥ����δ���,����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��4��5��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��06��08��
   ��    ��   : l65478
    �޸�����   : DTS2012060708776:����L��ע��ʧ��#7��������GU��LU���ʹ���
 3.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 4.��    ��   : 2012��12��28��
   ��    ��   : t00212959
   �޸�����   : DTS2012122607665:L������ʱ�����������
 5.��    ��   : 2013��7��25��
   ��    ��   : w00242748
   �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                rau req�д�follow on��־,����ȷЭ������
 6.��    ��   : 2014��4��18��
   ��    ��   : w00176964
   �޸�����   : V3R3C60_eCall��Ŀ����:��Ԥ������ֹͣ�ȴ�ϵͳ��Ϣ��ʱ�����߼��Ƶ����˴�
*****************************************************************************/
VOS_UINT32 NAS_MM_RcvSysInfoSurpportLte_PreProc(VOS_VOID)
{
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
    /* ������ʱ������ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    }

    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* ��¼״̬ΪCSFB MT���յ�ϵͳ��Ϣ */
        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MM_RcvSysInfo_CSFB();

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg() )
    {
        /* CSFB���̴�L��ϵͳ�任��GU,����ģʽII,LAIδ�ı�ʱ����ҵ��
           ��¼��Ҫ��ҵ���������LAU */
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* ���CSҵ������ΪSMS over SGs��CSFB�Ͷ��Ŷ�֧�֣�����TIN����Ϊ"GUTI"
       3GPP 24008 4.4.1:
       indicating to the network that the MS, configured to use CS fallback and
       SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell
       in NMO II or III, after intersystem change from S1 mode to Iu
       or A/Gb mode, the TIN indicates "GUTI" and the location area of
       the current cell is the same as the stored location area; */

    if (VOS_TRUE == NAS_MM_IsLauNeededLaiNoChange_LInterSys())
    {
        /* ����LAU���� �н������Ƚ��н�����*/
        enLauType = NAS_MM_GetLuType();
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);



        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* 3GPP 24.008��4.4.1   Location updating procedure�½�����:
       The normal location updating procedure shall also be started if
       the MS is configured to use CS fallback and SMS over SGs,
       or SMS over SGs only, and the TIN indicates "RAT-related TMSI",
       when the MS enters a GERAN or UTRAN cell in network operation
       mode II or III and the E-UTRAN deactivate ISR timer T3423 is running.
       The normal location updating procedure shall also be started when
       the MS, configured to use CS fallback and SMS over SGs, or SMS over
       SGs only, enters a GERAN or UTRAN cell in network operation mode
       II or III and the E-UTRAN deactivate ISR timer T3423 has expired*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        /* ����LAU���� �н������Ƚ��н�����*/
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);


        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif
/*****************************************************************************
 �� �� ��  : NAS_MM_GetLuType
 ��������  : ����LU����
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��08��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��27��
    ��    ��   : t00212959
    �޸�����   : DTS2012122607665
*****************************************************************************/
VOS_UINT8 NAS_MM_GetLuType(VOS_VOID)
{
    if ( VOS_TRUE == NAS_MML_IsCsLaiChanged() )
    {
        return MM_IE_LUT_NORMAL_LU;
    }
    else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (MM_TRUE     == g_MmGlobalInfo.ucPowerOnFlg)
         && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
    {
        return MM_IE_LUT_IMSI_ATTACH;
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        return MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        return MM_IE_LUT_NORMAL_LU;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LogMmStateInfo
 ��������  : ��MM��״̬
 �������  : ucMmState: MM�ĵ�ǰ״̬
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��21��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��04��29��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature �޸�

*****************************************************************************/
VOS_VOID  NAS_MM_LogMmStateInfo(
    NAS_MM_STATE_ENUM_UINT8             ucMmState
)
{
    NAS_MM_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_STATE_INFO_IND;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    pstMsg->enMmState                   = ucMmState;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_IsCcTiValid
 ��������  : �ж�cc��transaction id�Ƿ�Ϸ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - TI�Ϸ�
             VOS_FALSE - TI�Ƿ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��18��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���,��Ȧ���Ӷ�

*****************************************************************************/
VOS_UINT32 NAS_MM_IsCcTiValid(VOS_VOID)
{
    if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
      ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Modified by z00161729 for DCM�����������������, 2012-8-20, end */

/* Modified by z00161729 for DCM�����������������, 2012-8-23, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcBufferedEmgCallBeforeLau_RcvSysinfo
 ��������  : �յ�ϵͳ��Ϣ��Ҫ��lauǰ�ж��Ƿ��л���Ľ������У��������laiδ�ı�
             �����������У����н���������lau�����lai�ı���lai�ı�����lau nv��
             �رգ��Ƚ��н������к��н���������lau
 �������  : ulLaiChangeFlag - lai�Ƿ�ı��־
             ulLuType        - Lau������
 �������  : ��
 �� �� ֵ  : VOS_TRUE -
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��22��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���, ��Ȧ���Ӷ�
  2.��    ��   : 2012��10��25��
    ��    ��   : z00161729
    �޸�����   : DTS2012102305986:csfb��gu access barС���޷������������
  3.��    ��   : 2012��11��09��
    ��    ��   : t00212959
    �޸�����   : DTS2012110810521:���������жϲ�׼ȷ
  4.��    ��   : 2012��12��22��
    ��    ��   : l65478
    �޸�����   : DTS2012122103936 �����������ʱMM״̬Ǩ�ƴ���
  5.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                rau req�д�follow on��־,����ȷЭ������
*****************************************************************************/
VOS_VOID NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(
    VOS_UINT32                          ulLaiChangeFlag,
    VOS_UINT8                           ucLuType
)
{
    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT32                          ulCsRestrictRegFlg;

    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulCsRestrictRegFlg             = NAS_MML_GetCsRestrictRegisterFlg();
    ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

    if (VOS_FALSE == ulLaiChangeFlag)
    {
        /* LAIδ�ı��Ҵ��ڻ���Ľ����������Ƚ��н������У����н���������lau */
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif

            /* ����ֹCS����LAI���ı�ʱ���������ͷź���Ҫ����LU */
            if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
             || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
            {
                if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                 && ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)))
                {
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
                }
            }
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* ��¼�յ���������ʱ��״̬                 */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, begin */
            /* �������е�ʱ��,�ȴ�����LAU���ϱ�ע����,��������delay��LAU����
               �������е�ʱ��,�����ϱ�������ע��ɹ� */
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, end */

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            return;
        }

        /* �޻���Ľ�������ֱ�ӽ���lau */
        g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
        Mm_ComLuOnly();
        return;
    }

    /* ���ڻ���Ľ�������lai�ı��Ƚ��н������н���������lau nv���� */
    if (((VOS_FALSE == ulCsfbEmgCallLaiChgLauFirstFlg)
      || ((VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg)
       && (VOS_TRUE == ulCsRestrictRegFlg)))
     && (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg))
    {
#if (FEATURE_LTE == FEATURE_ON)
         /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
        NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif
        /* ����ֹCS����LAI���ı�ʱ���������ͷź���Ҫ����LU */
        if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
        {
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
        }
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* ��¼�յ���������ʱ��״̬                 */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, begin */
        /* �������е�ʱ��,�ȴ�����LAU���ϱ�ע����,��������delay��LAU����
           �������е�ʱ��,�����ϱ�������ע��ɹ� */
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, end */

        Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

        return;
    }

    /* �޻���Ľ�������ֱ�ӽ���lau */
    g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
    Mm_ComLuOnly();
    return;
}
/* Modified by z00161729 for DCM�����������������, 2012-8-23, end */


/*****************************************************************************
 �� �� ��  : NAS_MM_IsCsEnableLau
 ��������  : �ж�CS���ܷ����LAU
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��7��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MM_IsCsEnableLau( VOS_VOID )
{

    /* CS��Ŀ���Ч,����Ҫ���� */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus()  )
    {
        return VOS_FALSE;
    }

    /* CS������aTTach,����Ҫ���� */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* CS���������,����Ҫ���� */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return VOS_FALSE;
    }

    /* ��ǰ�ǽ�ֹ����,����Ҫ���� */
    if ((MMCMM_NO_FORBIDDEN !=g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    /* T3211��ʱ������,����Ҫ���� */
    if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedLauCsSigRel
 ��������  : ����ģʽ��ͬʱ���ж��Ƿ���ҪLAU
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��27��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : DTS2013041602825:CSFB���ӽ���ʧ�ܺ�û�з���LU
  3.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                 �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                 rau req�д�follow on��־,����ȷЭ������
  4.��    ��   : 2014��05��07��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MM_IsNeedLauCsSigRel( VOS_VOID )
{
    /* ���ô˺���ǰ,�����Ҫ�ж���������״̬,��Ҫ�ɵ��ô˺������ϼ�������֤ */

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, begin */
    if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, end */
      && ((MM_TRUE == g_MmGlobalInfo.ucConnRcvSysFlg)
       || (VOS_TRUE == g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg)) )
    {
        return VOS_TRUE;
    }

#if (FEATURE_LTE == FEATURE_ON)

    if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_MM_IsAbleRecover_EstCnfFailResult
 ��������  : �жϽ����ظ���est cnfʧ��ԭ��ֵ�Ƿ���Ҫ�ɻָ����ɻָ���Ҫcc/ss/sms�ط�
 �������  : enEstResult - �����ظ���est cnfʧ��ԭ��ֵ
 �������  : VOS_TRUE  - ����ʧ��ԭ��ֵ�ɻָ�����Ҫ��������/����ҵ��/�����ط�
             VOS_FALSE - ����ʧ��ԭ��ֵ��ʱ���ɻָ�������Ҫ��������/����ҵ��/�����ط�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��8��22��
    ��    ��   : w00167002
    �޸�����   : DTS2013081604476:w��ѡ��G�º󣬱�����ָ�ɾܾ���GAS����T3122
                  ��ʱ���������û�����绰��NAS����LAU,GAS����T3122���У�ֱ�ӻظ�
                  ����ʧ�ܡ�MM������T3211,�����ֳ����£�NAS����Ҫ����T3211��ʱ����
  3.��    ��   :2013��9��15��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32  NAS_MM_IsAbleRecover_EstCnfFailResult(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstResult
)
{
    /* RRC_EST_RJ_CELL_BAR���ɻָ� */
    if ((RRC_EST_IMMEDIATE_ASSIGN_REJECT == enEstResult)
     || (RRC_EST_ACCESS_BARRED           == enEstResult)
     || (RRC_EST_OTHER_ACCESS_BARRED     == enEstResult)
     || (RRC_EST_RJ_T3122_RUNNING        == enEstResult)
     || (RRC_EST_RJ_CELL_BAR             == enEstResult))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedCmServiceRetry_RelIndResult
 ��������  : �жϽ����ظ���rel indʧ��ԭ��ֵ�Ƿ���Ҫ��������/����ҵ��/�����ط�
 �������  : enRelCause - �����ظ���rel indʧ��ԭ��ֵ
 �������  : VOS_TRUE  - ��Ҫ��������/����ҵ��/�����ط�
             VOS_FALSE - ����Ҫ��������/����ҵ��/�����ط�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   :2013��9��15��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����

*****************************************************************************/
VOS_UINT32  NAS_MM_IsNeedCmServiceRetry_RelIndResult(
    RRC_REL_CAUSE_ENUM_UINT32           enRelCause
)
{
    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd
 ��������  : MM�յ�RelInd������ʧ�ܣ�����С��4�εĳ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���, ��Ȧ���Ӷ�
  2.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  4.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
*****************************************************************************/
VOS_VOID NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(
    RRC_REL_CAUSE_ENUM_UINT32                   enRelCauses
)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    VOS_UINT8                                               ucGsmEstConnFailFlg = MM_FALSE;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (RRC_REL_CAUSE_CONN_FAIL   == enRelCauses))
    {
        ucGsmEstConnFailFlg = MM_TRUE;
    }

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
      && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
    {                                                                   /* ���LAI����,�Ҹ���״̬ΪU1��ʱ��         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd:INFO: MmServiceState is MM_NORMAL_SERVICE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* ��MMC����MMCMM_LU_RESULT_IND             */

        }

        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
        g_T3211Flag = 1;
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
        }
        else
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
    }

}


/*****************************************************************************
 �� �� ��  : NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd
 ��������  : MM�յ�RelInd������ʧ�ܣ���MMC����RR����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���, ��Ȧ���Ӷ�
*****************************************************************************/
VOS_VOID NAS_MM_SndMmcRrConn_RcvRelInd(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;

    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR���Ӳ�����                             */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
    }
    else
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

}





/*****************************************************************************
 �� �� ��  : NAS_MM_LocalDetach_MmInterRatChange
 ��������  : MM�ڹ���״̬�յ�detach��Ϣ�Ĵ���
 �������  : VOS_VOID* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��15��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 4.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach_MmInterRatChange(VOS_VOID)
{
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* ֪ͨGMM��ǰCS���ѱ���DETACH��ʱ���� */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                           /* ����MM��Ϣ                               */

    /* ���÷���״̬ΪDETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* ����ȫ�ֱ�����CS����б���detach����Ҫ����ɾ�� */
    if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
      && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucSuspendPreState ) )
    {
        NAS_MM_InitCcoFallbackCtx();
    }

    /* ����mmǨ����״̬,3212�ڹ���״̬δֹͣ,��ʱ��Ҫֹͣ */
    Mm_TimerStop(MM_TIMER_T3212);

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucSuspendPreState)
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucPreState = MM_IDLE_NO_IMSI;
    }
    else
    {
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LocalDetach_MmNoImsi
 ��������  : MM���޿�ʱ�򱾵�ȥע��ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach_MmNoImsi(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* ����ȥע��ͨ�ò��� */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* ֪ͨGMM��ǰCS���ѱ���DETACH��ʱ���� */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* �������ɹ���ֱ�ӱ���DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* ���÷���״̬ΪDETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* ֪ͨMMC��ǰ����Ч */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    /* �����ǰ���������ӣ����ͷ����� */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LocalDetach
 ��������  : MM����ȥע��ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmTimerProtectCsDetachExpired(VOS_VOID)
{
    NAS_MM_LocalDetach();

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_LocalDetach
 ��������  : MM����ȥע��ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��9��12��
    ��    ��   : z00161729
    �޸�����   : DTS2013082903019:֧��ss�ط�����
  3.��    ��   : 2014��04��30��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulMmState;

    pstConnStatus = NAS_MML_GetConnStatus();
    ulMmState     = Mm_GetState();

    /* ����״̬���� */
    switch ( ulMmState )
    {
        case MM_INTER_RAT_CHANGE :

            /* ��ϵͳʱ��ı���ȥע�ᴦ���������ֱ�ӷ��� */
            NAS_MM_LocalDetach_MmInterRatChange();
            return;

        case MM_IDLE_NO_IMSI :

            /* NO IMSI�ı���ȥע�ᴦ���������ֱ�ӷ��� */
            NAS_MM_LocalDetach_MmNoImsi();
            return;

        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case MM_IDLE_ECALL_INACTIVE:

            NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive();
            return;
#endif
        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, end */

        /* ������״̬Ǩ�ƵĴ��� */
        case MM_STATE_NULL :
            break;

        default:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            break;
    }

    /* ����ȥע��ͨ�ò��� */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* ֪ͨGMM��ǰCS���ѱ���DETACH��ʱ���� */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* �������ɹ���ֱ�ӱ���DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* ���÷���״̬ΪDETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* ֪ͨMMC��ǰ������֧�� */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    /* �����ǰ���������ӣ����ͷ����� */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_StartDetachProtectingTimer
 ��������  : ����MM��Detach��Ϣ�ı�����ʱ��
 �������  : MMCMM_DETACH_REQ_STRU              *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��13��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID NAS_MM_StartDetachProtectingTimer(
    MMCMM_DETACH_REQ_STRU              *pstMsg
)
{
    /* Detach���̱�����ʱ��ʱ�� */
    VOS_UINT32                          ulDetachTimerVal;

    /* MM��CS��Detach������ʱ������״̬ */
    VOS_UINT32                          ulCsDetachTimerStatus;

    if (MMC_MM_DETACH_REASON_USER_DETACH == pstMsg->enDetachReason)
    {
        /* �û�������DETACH��ʱ��: 90s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* �����ǰ��SYSCFG������򴥷���DETACH,�����ñ�����ʱ����ʱ��Ϊ26s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }

    /* ��ȡMM��Detach������ʱ������״̬ */
    ulCsDetachTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_CS_DETACH);

    /* ���MM��CS��Detach������ʱ�������У�������CS��Detach������ʱ�� */
    if ( MM_TIMER_RUNNING == ulCsDetachTimerStatus )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartDetachProtectingTimer:WARN:TIMER HAS BEEN STARTED ALREADY");
        Mm_TimerStop(MM_TIMER_PROTECT_CS_DETACH);
    }

    /* ����MM��CS��Detach������ʱ��ʱ�� */
    gstMmTimer[MM_TIMER_PROTECT_CS_DETACH].ulTimerLen = ulDetachTimerVal;

    /* ����MM��CS��detach������ʱ�� */
    Mm_TimerStart(MM_TIMER_PROTECT_CS_DETACH);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer
 ��������  : �յ�������RRMM_EST_CNF��Ϣʱ����ǰ����CS��DETACH��־�Ĵ���
 �������  : RRMM_EST_CNF_STRU              *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��6��24��
    ��    ��   : w00167002
    �޸�����   : ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF
  3.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  4.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(
    RRMM_EST_CNF_STRU                  *pRrcEstCnf
)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer: Release all MM connection");
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    /* �����ǰ�����ɹ������л����û������IMSI detach������ֱ�ӷ���ȥע�� */
    if ( (RRC_EST_SUCCESS == pRrcEstCnf->ulResult)
      || (RRC_EST_PRESENT == pRrcEstCnf->ulResult))
    {

        /* ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;             /* �������������Ѵ���                       */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                        /* RR���ӽ����ɹ�                           */

        /* ��д��Ϣ,����IMSI detach��Ϣ */
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);

        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);
        Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */


        return;
    }

    /* MM���б���DETACH */
    NAS_MM_LocalDetach();

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedGmmProcUserDetach
 ��������  : �����б��Ƿ���GMM�������û������CS/CS+PS��detach
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE          -- ����ҪGMM���д����û������CS/CS+PS��detach
             VOS_TRUE           -- ��ҪGMM���д����û������CS/CS+PS��detach
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedGmmProcUserDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* ��ȡ��ǰ��������Ϣ */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* ������ģʽI�£�����GMM�����û������detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS��׼��ע�ᣬ����GMM�����û������detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS��ע�����ޣ�����GMM�����û������detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS ����Ч������GMM�����û������detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* ��ǰС���Ƿ�֧��GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* ��ǰС���Ƿ���FORB GPRS PLMN���� */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM�Ѵ���ATTACHED״̬������ǰGS�ӿڲ����� */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* �����û������CS���DETACH������GMM���д��� */
    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsLauNeeded_NetModeChange
 ��������  : �����б��Ƿ���GMM�������û������CS/CS+PS��detach
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE          -- ����ҪLAU
             VOS_TRUE           -- ��ҪLAU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��7��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsLauNeeded_NetModeChange(VOS_VOID)
{
    /* LAI�ı䣬��Ҫ����LAU */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        return VOS_TRUE;
    }

    /* LAI/RAC��û�ı� */
    if (g_MmGlobalInfo.MsCsInfo.ucOldRac == NAS_MML_GetCurrCampRac())
    {
        return VOS_FALSE;
    }

    /* ����W������ע�ᵫPS ONLY�ɹ�����ģʽ�ı�ΪII��Ҳ��ҪLAU */
    if ( (MM_ATT_NEED  == g_MmGlobalInfo.ucAttFlg)
      && (MM_TRUE      == g_MmGlobalInfo.ucPowerOnFlg) )
    {
        return VOS_TRUE;
    }

    /* I->II, GS�ڴ��ڣ���ҪLAU */
    if ( (VOS_FALSE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
      && (VOS_TRUE  == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg) )
    {
        return VOS_TRUE;
    }

    /* ��������Ҫ����LAU  */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_IsEmergencyCallEndTrigLau
 ��������  : ���������ͷź󣬼���Ƿ�������Ҫ����LAU
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE          -- ����Ҫ��������LAU
             VOS_TRUE           -- ��Ҫ��������LAU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 CSδע���£�������ʱ�û��·�ATTACH,�����ͷţ���ǰ��PSҵ����Ҫ����LAU��
  2.��    ��   : 2013��8��28��
    ��    ��   : l65478
    �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU

*****************************************************************************/
VOS_UINT32 NAS_MM_IsEmergencyCallEndTrigLau(VOS_VOID)
{
    VOS_UINT8                           ucEmergencyServiceFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM��CS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/
    VOS_UINT8                           ucRestrictRegister;                     /*�Ƿ�����ע�� */

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo         = VOS_NULL_PTR;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstCampInfo           = NAS_MML_GetCurrCampPlmnInfo();
    ucEmergencyServiceFlg = NAS_MML_GetCsEmergencyServiceFlg();
    ucCsAttachAllowFlg    = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus      = NAS_MML_GetSimCsRegStatus();
    ucRestrictRegister    = NAS_MML_GetCsRestrictRegisterFlg();

    /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
       �ж������ǰ��PSҵ����Ҫ����LAU */
    if ( (VOS_TRUE            == pstConnStatus->ucRrcStatusFlg)
      && (VOS_TRUE            == ucEmergencyServiceFlg)
      && (MM_STATUS_DETACHED  == g_MmSubLyrShare.MmShare.ucCsAttachState)
      && (VOS_TRUE            == ucCsAttachAllowFlg)
      && (VOS_TRUE            == ucSimCsRegStatus)
      && (VOS_FALSE           == ucRestrictRegister)
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3211].ucTimerStatus )
      && (NAS_MML_NET_MODE_II  == pstCampInfo->enNetworkMode)
      && ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
       || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_RelEstingMmConn
 ��������  : �ͷŵ�ǰ���ڽ�����MM���ӵ�TI
 �������  : ulRelCause         -- �ͷ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 Mm_Cell_S9_E33��Ȧ���Ӷȡ�
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RelEstingMmConn(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
        NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(ulRelCause);

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);            /* ֪ͨCC,MM���ӽ���ʧ��                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* ������ڽ�����MM���ӵı�־               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {                                                                   /* ��SS���ڽ�����MM����                     */
        Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* ������ڽ�����MM���ӵı�־               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {                                                                   /* ��SMS���ڽ�����MM����                    */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);                                          /* ֪ͨSS,MM���ӽ���ʧ��                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* ������ڽ�����MM���ӵı�־               */
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_RelBufferedServiceEstReq
 ��������  : �ͷ�MM��ǰ�����CSҵ��������
 �������  : ulRelCause         -- �ͷ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 Mm_Cell_S14_E33��Ȧ���Ӷȡ�
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RelBufferedServiceEstReq(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                           /* �еȴ���CC��������Ҫ������MM����         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg
            = MM_FALSE;

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);                          /* ֪ͨCC����ʧ��                           */
    }
    if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
    {                                                                           /* �еȴ���SMS��������Ҫ������MM����         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                RcvXXEstReq.ucFlg = MM_FALSE;
        Mm_SndSmsRelInd(
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
            .RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg )
    {                                                                           /* �еȴ���SS��������Ҫ������MM����         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg = MM_FALSE;

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall
 ��������  : �ͷ�MM��ǰ����ĳ��������е�CSҵ��������
 �������  : ulRelCause         -- �ͷ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}



/*****************************************************************************
 �� �� ��  : NAS_MM_NotifyBufferedServiceRRConnNotExist
 ��������  : �л���CSҵ��ʱ��֪ͨMMC/GMM��ǰRR���Ӳ�����
 �������  : ulRelCause         -- �ͷ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE          -- �ͷ�ʧ��
             VOS_TRUE           -- �ͷųɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 Mm_Cell_S10_E33��Ȧ���Ӷȡ�

*****************************************************************************/
VOS_UINT32 NAS_MM_NotifyBufferedServiceRRConnNotExist(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg;

    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                  .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if ( MM_FALSE == ucTiValidFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedNormLu
 ��������  : �ж��Ƿ���Ҫ��MM�Լ���LAU
 �������  :
 �������  :
 �� �� ֵ  : VOS_FALSE          ����Ҫ
             VOS_TRUE           ��Ҫ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��19��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : DTS2013041602825:CSFB���ӽ���ʧ�ܺ�û�з���LU
*****************************************************************************/
VOS_UINT32 NAS_MM_IsDisableGprsCombineAttach(VOS_VOID)
{

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* ��ȡ��ǰ��������Ϣ */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;

    /* CS��ע�����ޣ�MM����Ҫ��LAU */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }


    /* ������ģʽI�£�MM��Ҫ�Լ���LAU */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_TRUE;
    }

    /* PS��׼��ע�ᣬMM��Ҫ�Լ���LAU */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_TRUE;
    }

    /* PS��ע�����ޣ�MM��Ҫ�Լ���LAU */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_TRUE;
    }

    /* PS ����Ч������GMM�����û������detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_TRUE;
    }

    /* ��ǰС���Ƿ�֧��GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_TRUE;
    }

    /* ��ǰС���Ƿ���FORB GPRS PLMN���� */
    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_RestartT3240_WaitForNetworkCommand
 ��������  : WaitForNetworkCommand״̬����T3240
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RestartT3240_WaitForNetworkCommand(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* �Ƿ�֧��cs����ҵ�������ͨ������vpҵ��VOS_TRUE:֧��cs����ҵ��VOS_FALSE:��֧��cs����ҵ��*/
    VOS_UINT8                           ucCsServiceConnStatusFlg;

    pstConnStatus            = NAS_MML_GetConnStatus();
    ulIsTestCard             = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg    = NAS_MML_GetSupportCsServiceFLg();
    ucCsServiceConnStatusFlg = pstConnStatus->ucCsServiceConnStatusFlg;

    /* ͣT3240 */
    Mm_TimerStop( MM_TIMER_T3240 );

    /* ��ǰ���Կ�����ǰ����Ϊ��֧��CSҵ�񣬵�ǰ��CSҵ��������T3240���ֵ */
    if ( (VOS_TRUE  == ulIsTestCard)
      && (VOS_FALSE == ucSupportCsServiceFlg)
      && (VOS_TRUE  == ucCsServiceConnStatusFlg) )
    {
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
        Mm_TimerStart( MM_TIMER_T3240 );
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    }
    else
    {
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* ����T3240                                  */
    }

}
/*****************************************************************************
 �� �� ��  : NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending
 ��������  : MM״̬�ָ�����ǰ״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending(VOS_VOID)
{
    VOS_UINT8                           ucPreMmState;

    ucPreMmState  = g_MmGlobalInfo.ucPreState;

    /* CS����Ч��״̬Ǩ�� */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        return;
    }

    /* CS��׼��ע���״̬Ǩ�� */
    if ( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* ��ǰ��ֹע���״̬Ǩ�� */
    if ( (MMCMM_NO_FORBIDDEN            != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
      && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* CS�����޵�״̬Ǩ�� */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        return;
    }

    /* MM��ǰ��MM_IDLE_NORMAL_SERVICE״̬������µ�ǰ״̬ΪMM_IDLE_NORMAL_SERVICE */
    if ( MM_IDLE_NORMAL_SERVICE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        return;
    }

    /* MM��ǰ��MM_IDLE_ATTEMPTING_TO_UPDATE״̬������µ�ǰ״̬ΪMM_IDLE_ATTEMPTING_TO_UPDATE */
    if ( MM_IDLE_ATTEMPTING_TO_UPDATE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        return;
    }

    /* ͳһǨ�Ƶ�MM_IDLE_ATTEMPTING_TO_UPDATE״̬ */
    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

}



/*****************************************************************************
 �� �� ��  : NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject
 ��������  : LAUʱ������ָ�ɱ��ܣ�����������ͨCC���У�����Ҫ�ز�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2013��12��9��
    ��    ��   :w00242748
    �޸�����   :DTS2013120502018:MMģ�鷢�͸�SMS����Ϣ�ı���ԭ��ֵ���ԣ��޸�
                �ú���Ϊ�ж��Ƿ���ڻ����CS Service
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject()
{
    /* ���ݻ���ҵ������ͣ���ȡ��Ӧ�ĺ���ָ���Լ�TransActionId */
    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
      && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType) )
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_
 ��������  : �����ͷ�����ģʽI�´���LAU����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI( VOS_VOID )
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac )
    {                                                               /* RACΪ0�ĳ���                             */
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComChkLu:INFO: MmLikeB is MM_TRUE");
        if ( ( MMCMM_NO_FORBIDDEN !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
            ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            if ( MMCMM_FORBIDDEN_PLMN
                == (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            }
            else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                    & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

                 Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
                 /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

                Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
            }
        }
        else
        {
           g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
           Mm_ComLuOnly();                                          /* LU REQ                                   */
           ucRet = MM_TRUE;
        }
    }

    return ucRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode
 ��������  : �����ͷ���������ģʽ�´���LAU����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode( VOS_VOID )
{                                                                   /* ��A+Iģʽ                                */
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( ( MMCMM_NO_FORBIDDEN !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
        ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
    {                                                               /* ���û��CS���ֹ����Ϣ                   */
        if ( MMCMM_FORBIDDEN_PLMN == ( MMCMM_FORBIDDEN_PLMN &
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
        Mm_ComLuOnly();                                             /* ����LU REQ                               */
        ucRet = MM_TRUE;
    }

    return ucRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire
 ��������  : �����ͷ�����T3212��ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(
    VOS_UINT8                           ucPsRestrictionFlg
)
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
        ucRet = MM_TRUE;

        if((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
            && (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* ����LU����                               */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* ����LU����                               */
        }

        Mm_ComLuOnly();                                                     /* ����LU REQ                               */
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
        ucRet = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* ����LU����                               */
        Mm_ComLuOnly();                                                     /* ����LU REQ                               */
        break;
    default:
        break;
    }

    return ucRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist
 ��������  : �����ͷ�,rrc���Ӵ��ڵĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist( VOS_VOID )
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        ucFlg = MM_TRUE;
        break;
    default:
        break;
    }
    if ( MM_TRUE == ucFlg )
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
        {                                                                   /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI();
        }
        else
        {
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode();
        }
    }

    return ucRet;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_ProcessLuAfterCsConnectNotExist
 ��������  : CS�����ͷŻ������ӽ���ʧ�ܺ�,����Ƿ���LU
 �������  : ��
 �������  : ��
 �� �� ֵ  : MM_FALSE: ����Ҫ����LU����
             MM_TRUE:  ��Ҫ����LU����
 ���ú���  : ���ô˺���ǰ,�ɵ��ú��������Ƿ���Ҫ�ж�RRC�����Ƿ����;
             ����:�����CSFB->GU,ҵ�����ӽ���ʧ�ܺ�Ҫ����LU,����Ҫ�ж�RRC״̬;
                  �����CSҵ�������,CS�����ͷź�Ҫ����LU,��Ҫ�ж�RRC״̬
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��12��11��
    ��    ��   : z00234330
    �޸�����   : dts2013121106833,��Ȧ���Ӷ�

*****************************************************************************/
VOS_UINT8 NAS_MM_ProcessLuAfterCsConnectNotExist(VOS_VOID)
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();


    if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
    {
        if ( ( MMCMM_FORBIDDEN_PLMN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_ROAM == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ))
        {
            return ucRet;
        }

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        switch ( g_MmGlobalInfo.ucState )
        {
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LIMITED_SERVICE:
            ucFlg = MM_TRUE;
            break;
        default:
            break;
        }
        if  ( MM_NET_MODE_II == g_MmGlobalInfo.ucNtMod )
        {
            if (MM_TRUE == ucFlg)
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
                ucRet = MM_TRUE;
                return ucRet;
            }
        }
    }

    if (VOS_TRUE == NAS_MM_IsNeedLauCsSigRel())
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist();
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(ucPsRestrictionFlg);
    }
    else
    {

    }

    return ucRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LogAuthInfo
 ��������  : ��MM�������ļ�Ȩ��Ϣ
 �������  : VOS_VOID
 �������  : ucRcvOpId    : ��Ϣ�н��ܵ���OPID
             ucExpectOpId : MM������OPID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��21��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
)
{
    NAS_MM_LOG_AUTH_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_AUTH_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogAuthInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_AUTH_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_AUTH_INFO_IND;
    pstMsg->ucExpectOpId                = ucExpectOpId;
    pstMsg->ucRcvOpId                   = ucRcvOpId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_LogMmCtxInfo
 ��������  : ��MM��ȫ�ֱ���ֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_LogMmCtxInfo(VOS_VOID)
{
    MMOM_LOG_CTX_INFO_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMOM_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(MMOM_LOG_CTX_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(MMOM_LOG_CTX_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMOM_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_CTX_INFO_IND;

    pstMsg->stMmGlobalInfo.ConnCtrlInfo_CC_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SMS_RcvXXEstReq_ucFlg = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SS_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.enPreRatType                       = g_MmGlobalInfo.enPreRatType;
    pstMsg->stMmGlobalInfo.LuInfo_ucT3212ExpiredFlg           = g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg;
    pstMsg->stMmGlobalInfo.MsCsInfo_ucOldRac                  = g_MmGlobalInfo.MsCsInfo.ucOldRac;
    pstMsg->stMmGlobalInfo.stDetachInfo_enDetachType          = g_MmGlobalInfo.stDetachInfo.enDetachType;
    pstMsg->stMmGlobalInfo.ucAttFlg                           = g_MmGlobalInfo.ucAttFlg;
    pstMsg->stMmGlobalInfo.ucLikeB                            = g_MmGlobalInfo.ucLikeB;
    pstMsg->stMmGlobalInfo.ucMmServiceState                   = g_MmGlobalInfo.ucMmServiceState;
    pstMsg->stMmGlobalInfo.ucNotCampONPreState                = g_MmGlobalInfo.ucNotCampONPreState;
    pstMsg->stMmGlobalInfo.ucNtMod                            = g_MmGlobalInfo.ucNtMod;
    pstMsg->stMmGlobalInfo.ucPowerOnFlg                       = g_MmGlobalInfo.ucPowerOnFlg;
    pstMsg->stMmGlobalInfo.ucPreState                         = g_MmGlobalInfo.ucPreState;
    pstMsg->stMmGlobalInfo.usRac                              = g_MmGlobalInfo.usRac;

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_GetCallMode();
#else
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_CALL_MODE_BUTT;
#endif
    pstMsg->stMmlCtxInfo.enCsfbServiceStatus                  = NAS_MML_GetCsfbServiceStatus();
    pstMsg->stMmlCtxInfo.enCsUpdateStatus                     = NAS_MML_GetCsUpdateStatus();
    pstMsg->stMmlCtxInfo.enT3423Status                        = NAS_MML_GetT3423Status();
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo, NAS_MM_GetAttemptUpdateLaiInfo(), sizeof(pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCsLastSuccLai, NAS_MML_GetCsLastSuccLai(), sizeof(pstMsg->stMmlCtxInfo.stCsLastSuccLai));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCurrCampLai, NAS_MML_GetCurrCampLai(), sizeof(pstMsg->stMmlCtxInfo.stCurrCampLai));
    pstMsg->stMmlCtxInfo.ucCsSecurityCksn                     = NAS_MML_GetSimCsSecurityCksn();
    pstMsg->stMmlCtxInfo.ucImsVoiceAvailFlg                   = NAS_MML_GetImsVoiceAvailFlg();
    pstMsg->stMmlCtxInfo.ucImsVoiceInterSysLauEnableFlg       = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    pstMsg->stMmlCtxInfo.ucStaOfRcvXXEstReqCsfb               = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

    pstMsg->stMmTimerInfo.ucT3211TimerStatus                  = gstMmTimer[MM_TIMER_T3211].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3212TimerStatus                  = gstMmTimer[MM_TIMER_T3212].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3213TimerStatus                  = gstMmTimer[MM_TIMER_T3213].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3242TimerStatus                  = gstMmTimer[MM_TIMER_T3242].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3243TimerStatus                  = gstMmTimer[MM_TIMER_T3243].ucTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MM_GetEstCnfResult
 ��������  : ��ȡMMģ�齨��ʧ��ԭ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : est cnfʧ��ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
RRC_NAS_EST_RESULT_ENUM_UINT32 NAS_MM_GetEstCnfResult(VOS_VOID)
{
    return g_MmGlobalInfo.enEstCnfResult;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetEstCnfResult
 ��������  : ����MMģ�齨��ʧ��ԭ��ֵ
 �������  : est cnfʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstCnfResult)
{
    g_MmGlobalInfo.enEstCnfResult = enEstCnfResult;
}


/* Added by n00355355 for �����ؽ�, 2015-9-29, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_GetTransactionEnqSenderPid
 ��������  : ��ȡMM TransactionEnq��Ϣ��SenderPid
 �������  : ��
 �������  : ��
 �� �� ֵ  : TransactionEnq��Ϣ��SenderPid
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��29��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetTransactionEnqSenderPid(VOS_VOID)
{
    return g_MmGlobalInfo.ulTransactionEnqSenderPid;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetTransactionEnqSenderPid
 ��������  : ����MM TransactionEnq��Ϣ��SenderPid
 �������  : est cnfʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
  1.��    ��   : 2015��9��29��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetTransactionEnqSenderPid(
    VOS_UINT32                          ulSenderPid
)
{
    g_MmGlobalInfo.ulTransactionEnqSenderPid = ulSenderPid;

    return;
}

/* Added by n00355355 for �����ؽ�, 2015-9-29, end */

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf
 ��������  : �յ�lau�������ӽ���ж��Ƿ���Ҫ�������cs detach��Ϣ
 �������  : enEstCnfResult - �������
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ
             VOS_FALSE:����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult
)
{
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4�½�����:If a RR connection
        exists and the ATT flag indicates that no detach procedure is required,
        the MM sublayer will release locally any ongoing MM connections before
        releasing the RR connection. If a MM specific procedure is active,
        the release of the RR connection may be delayed until the MM specific
        procedure is complete. lau�����������ͷ�ʱ��������detach,���lau����ʧ����������detach */
    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        if ((RRC_EST_SUCCESS != enEstCnfResult)
         && (RRC_EST_PRESENT !=enEstCnfResult))
        {
            return VOS_TRUE;
        }

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ClearAuthInfo
 ��������  : �����Ȩ�����Ϣ
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��21��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_ClearAuthInfo(VOS_VOID)
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause   = MM_AUTHEN_NO_CAUSE;

    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_DIFFER;

    /* 24.008 4.3.2.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3218, if running, shall be stopped:
    -   if the mobile station enters the MM state MM IDLE or NULL.
    */
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();

    if (MM_RCV_AUTH_CNF_FLG == (MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    }

    if ((VOS_TRUE == NAS_MML_GetNwIgnoreAuthFailCfg())
     && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3216].ucTimerStatus))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ClearAuthInfo: Clear CKSN and Stop T3216");
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        Mm_TimerStop(MM_TIMER_T3216);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired
 ��������  : ����CSFB��Я��CSMT��־��ʱ����ʱ�������FLG��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��28��
    ��    ��   : w00167002
    �޸�����   : csmt modify
  3.��    ��   : 2015��6��01��
    ��    ��   : j00174725
    �޸�����   : DTS2015053000044
  4.��    ��   : 2015��10��16��
    ��    ��   : j00174725
    �޸�����   : DTS2015101603066
  5.��    ��   : 2016��2��2��
    ��    ��   : z00359541
    �޸�����   : DTS2016011809099:����Ҫ����CSFB ABORT��Ϣ���״̬�����յ�PLMN SERACH IND��Ϣʱ����
*****************************************************************************/
VOS_VOID NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRcvPid;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    ulRet            = VOS_ERR;
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);


    if (MM_INTER_RAT_CHANGE == Mm_GetState())
    {
        if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
          && (NAS_MML_NET_RAT_TYPE_LTE             == enCurrNetRatType) )
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            /* ֪ͨL CSFB ������ֹ */
            NAS_MM_SndLmmCsfbServiceAbortNotify();
        }
    }

    /* ֪ͨ�����TRANSACTION״̬ */
    ulRet = NAS_MM_GetRrcPidFromCurrRatType(&ulRcvPid);
    if (VOS_OK == ulRet)
    {
        NAS_MM_SndRrcTransactionStatusNotify(ulRcvPid, RRMM_TRANSACTION_FAIL);
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

#if (FEATURE_ON == FEATURE_PTM)
    /* ���CS�������Ӳ����ڣ����¼CSFB MT�쳣 */
    if (VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
    {
        NAS_MM_CsfbMtFailRecord();
    }
#endif

    /* ���MMC��������ʱҵ�������֪ͨMMCֹͣ��GU�����´�LTE��ʼ����;���MMC����ON PLMN�������ȼ����뼼��BG�Ѷ�ʱ�� */
    NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);

    return;
}



/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired
 ��������  : MM��HO���̻�ȡCS��ȫ�����ĳ�ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired(VOS_VOID)
{
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
    {
        /* ��MMC�ظ�����rsp */
        NAS_MM_SndMmcSuspendRsp();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetSrvccFlg
 ��������  : ��ȡMMģ����SRVCC���̱��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_GetSrvccFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucSrvccFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetSrvccFlg
 ��������  : ����MMģ����SRVCC���̱��
 �������  : ucFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetSrvccFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucSrvccFlg = ucFlg;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */

/*****************************************************************************
 �� �� ��  : NAS_MM_GetRcvSrvccCallInfoFlg
 ��������  : ��ȡMMģ����SRVCC�����յ�CCͬ��CALLINFO���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_GetRcvSrvccCallInfoFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucRcvSrvccCallInfoFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetRcvSrvccCallInfoFlg
 ��������  : ����MMģ����SRVCC�����յ�CCͬ��CALLINFO���
 �������  : ucFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetRcvSrvccCallInfoFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucRcvSrvccCallInfoFlg = ucFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertToLmmSrvccStatus
 ��������  : ��MM��SRVCC״̬ת��ΪLMM�ĸ�ʽ
 �������  : enSrvccStatus---MM��ʽ��SRVCC״̬
 �������  : penMmlSrvccStatus--LMM��ʽ��SRVCC״̬
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToLmmSrvccStatus(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus,
    MM_LMM_SRVCC_STATUS_ENUM_UINT32    *penMmlSrvccStatus
)
{
    switch(enSrvccStatus)
    {
        case NAS_MMCC_SRVCC_STATUS_START:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_START;
            break;
        case NAS_MMCC_SRVCC_STATUS_SUCCESS:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_SUCC;
            break;
        case NAS_MMCC_SRVCC_STATUS_FAIL:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_FAIL;
            break;
        default:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedSetCsmtFlg
 ��������  : �ж��Ƿ���ҪЯ��CSMT��־
 �������  : ��
 �������  : VOS_TRUE :��ҪЯ��CSMT
             VOS_FALSE:����ҪЯ��CSMT
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��25��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��5��
    ��    ��   : b00269685
    �޸�����   : csmt�޸�
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedSetCsmtFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsfbMtFlg;

    ucCsfbMtFlg = NAS_MM_GetCsfbMtLauFlg();

    /* ����CSMT��־������ҪЯ��CSMT��־ */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
      || (VOS_TRUE                             == ucCsfbMtFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedSetCsmoFlg
 ��������  : �ж��Ƿ���ҪЯ��CSMO��־
 �������  : ��
 �������  : VOS_TRUE :��ҪЯ��CSMO
             VOS_FALSE:����ҪЯ��CSMO
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��25��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��9��
    ��    ��   : z00359541
    �޸�����   : DTS2015111402223:����С���Ƿ�֧��CSMO��ʶ
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedSetCsmoFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucCellNotSupportCsmoFlg;
    VOS_UINT8                           ucCsfbMoSetupFlg;

    ucCsmoSupportedFlg      = NAS_MML_GetCsmoSupportedFlg();
    ucCellNotSupportCsmoFlg = NAS_MML_GetCellNotSupportCsmoFlg();
    ucCsfbMoSetupFlg        = NAS_MML_GetCsfbMoSetupFlg();

    NAS_NORMAL_LOG3(WUEPS_PID_MM,
        "NAS_MM_IsNeedSetCsmoFlg: ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg",
        ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg);

    /* ��ǰ����֧��CSMO���ҵ�ǰ����CSMOҵ�� */
    if ((VOS_TRUE == ucCsmoSupportedFlg)
     && (VOS_FALSE == ucCellNotSupportCsmoFlg)
     && (VOS_TRUE == ucCsfbMoSetupFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_IsNeedSetCsmoFlg: Need to set CSMO");
        return VOS_TRUE;
    }

    /* ����Я��CSMO ��־ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_SetCsfbAdditionalUpdateParameters
 ��������  : ����AdditionalUpdateParameters
 �������  : pusMsgSize  :��ǰ��Ϣ�ĳ���
             pucSndMsg   : ������Ϣ��ַ
 �������  : pusMsgSize  :��ǰ��Ϣ�ĳ���
             pucSndMsg   : ������Ϣ��ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetCsfbAdditionalUpdateParameters(
    VOS_UINT8                           ucCsmtFlg,
    VOS_UINT8                           ucCsmoFlg,
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx       = *pusMsgSize;

    /* ͬʱЯ��CSMT/CSMO��־ */
    if ( (VOS_TRUE == ucCsmtFlg)
      && (VOS_TRUE == ucCsmoFlg) )
    {
        /* ����CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* ����CS fallback mobile originating call */
        pucSndMsg[usIdx]    |= MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* ����ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* ��Ϣ�������� */
        (*pusMsgSize) ++;

        return;
    }

    /* Я��CSMT��־ */
    if (VOS_TRUE == ucCsmtFlg)
    {
        /* ����CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* ����ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* ��Ϣ�������� */
        (*pusMsgSize) ++;

        return;
    }

    /* Я��CSMO��־ */
    if (VOS_TRUE == ucCsmoFlg)
    {
        /* ����CS fallback mobile originating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* ����ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* ��Ϣ�������� */
        (*pusMsgSize) ++;

        return;
    }

    /* ����ҪЯ��CSMT/CSMO��־ */
    return;
}



#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq
 ��������  : �ж��Ƿ���Ҫ��lau�����з�װMS network feature support IE
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq(VOS_VOID)
{
    VOS_UINT8                          ucIsNeedSetCsmoFlg;
    VOS_UINT8                          ucIsNeedSetCsmtFlg;

    ucIsNeedSetCsmoFlg = NAS_MM_IsNeedSetCsmoFlg();
    ucIsNeedSetCsmtFlg = NAS_MM_IsNeedSetCsmtFlg();


    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15�½���������:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    if ((PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
     && (VOS_FALSE == ucIsNeedSetCsmoFlg)
     && (VOS_FALSE == ucIsNeedSetCsmtFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetMsNetworkFeatureSupportIE
 ��������  : ����MS network feature support IE
 �������  : pusMsgSize  :��ǰ��Ϣ�ĳ���
             pucSndMsg   : ������Ϣ��ַ
 �������  : pusMsgSize  :��ǰ��Ϣ�ĳ���
             pucSndMsg   : ������Ϣ��ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_SetMsNetworkFeatureSupportIE(
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx  = *pusMsgSize;

    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15�½���������:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    pucSndMsg[usIdx]    = MM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN;

    /* ����MS NETWORK FEATURE SUPPORT IEI */
    pucSndMsg[usIdx]    |= MM_IEI_MS_NETWORK_FEATURE_SUPPORT;

    /* ��Ϣ�������� */
    (*pusMsgSize) ++;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetCsfbMtLauFlg
 ��������  : ��ȡMMģ����CsfbMtLau���̱��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_GetCsfbMtLauFlg(VOS_VOID)
{
    return g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetCsfbMtLauFlg
 ��������  : ����MMģ����CsfbMtLau���̱��
 �������  : ucFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_SetCsfbMtLauFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg = ucFlg;
}






/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */

/*****************************************************************************
 �� �� ��  : Mm_IsMultiSrvCollisionAllow
 ��������  : ��ҵ���ͻ�������̣��������
             1. ������ͬ����MO�����ͻ����
             2. һ��MT����ʱ������һ��MOҵ������ʱ��ͻ����

 �������  : ucMmConnCtrl -- ��ǰ�����ҵ������

 �������  : ��


 �� �� ֵ  : VOS_TRUE  -- ��ǰҵ����������
             VOS_FALSE -- ��ǰҵ����������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��2��21��
    ��    ��   : y00245242
    �޸�����   : ��dts201412901179���������ú����д���
*****************************************************************************/
VOS_UINT32 Mm_IsMultiSrvCollisionAllow(NAS_MM_CONN_CTRL_ENUM_UINT8  ucMmConnCtrl)
{
    if ((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_OUTGOING_MM_CONNECTION      == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_NETWORK_COMMAND             == g_MmGlobalInfo.ucState))
    {
        /* ��ǰ��һ������ҵ�����ڽ��� */
        if (MM_MT_PAGING == g_MmGlobalInfo.ucPagingType)
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                /* ��ǰ�������ΪGSM���ܾ���ǰ��MO����ҵ������ԭ��: GSMҵ��������ҵ�����ӽ����׶Σ�
                 * �޷�֪����ǰ��ҵ������
                 */
                if (MM_CONN_CTRL_CC == ucMmConnCtrl)
                {
                    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_IsMultiSrvCollisionAllow: retrun FALSE under GSM");
                    return VOS_FALSE;
                }

                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_IsMultiSrvCollisionAllow: retrun TRUE under GSM");
                return VOS_TRUE;
            }
            else
            {
                if ((MM_CONN_CTRL_CC                                 == ucMmConnCtrl)
                 && (RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL          == g_MmGlobalInfo.ucPagingCause))
                {
                    /* �����ǰMOҵ������Ϊ����ҵ����MTҵ������Ҳ�Ǻ��У��ܾ���ǰ��MOҵ�� */
                    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_IsMultiSrvCollisionAllow: retrun FALSE when there have MT call under UMTS");
                    return VOS_FALSE;
                }
                else
                {
                    /* ��������,����ǰҵ���� */
                    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_IsMultiSrvCollisionAllow: retrun TRUE under UMTS");
                    return VOS_TRUE;
                }
            }
        }

        /* ������Ϊ�˹�ܶ��MOҵ������ͬʱ����ʱ�Ĵ�������
         *
         * ע: δ���߰汾�����Կ��Ǹ���T3246��ʱ����ʽ������(Ref: section 4.5.1.1/4.5.1.2
         *     in 24.008 version 10.6.1)
         */
        if (WAIT_FOR_NETWORK_COMMAND != g_MmGlobalInfo.ucState)
        {
            if ((MM_IE_PD_NON_CALL_RLT_SS_MSG == g_MmGlobalInfo.ucMMConnEstingPD)
             && (MM_CONN_CTRL_CC              == ucMmConnCtrl))
            {
                /* ��ǰһ��MO SSҵ���������ڽ���������յ�����ҵ�����󣬾ܾ���ǰ����ҵ������ */
                return VOS_FALSE;
            }
            else if ((MM_IE_PD_CALL_CONTROL   == g_MmGlobalInfo.ucMMConnEstingPD)
                  && (MM_CONN_CTRL_SS         == ucMmConnCtrl))
            {
                /* ��ǰһ��MO ����ҵ���������ڽ���������յ�����ҵ�����󣬾ܾ���ǰ����ҵ������ */
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }
        }
    }

    NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_IsMultiSrvCollisionAllow: retrun TRUE when in MM state", g_MmGlobalInfo.ucState);

    return VOS_TRUE;
}



/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow
 ��������  : CS������attachʱ��MMCת����MM��ϵͳ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    if ((VOS_TRUE           == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I      == g_MmGlobalInfo.ucNtMod)
     && (MM_UNSUPPORT_GPRS  == g_MmGlobalInfo.usRac))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);


    Mm_DealWithBuffMsg();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsCsForbidden
 ��������  : �ж�ϵͳ��ϢָʾCS���Ƿ�forbidden
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰϵͳ��ϢָʾCS��forbidden
             VOS_FALSE:��ǰϵͳ��ϢָʾCS���forbidden
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_IsCsForbidden( VOS_VOID )
{
    if ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsCsNotSupport
 ��������  : �ж�ϵͳ��ϢָʾCS���Ƿ�֧��
 �������  : ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰϵͳ��ϢָʾCS��֧��
             VOS_FALSE:��ǰϵͳ��ϢָʾCS��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��11��
    ��    ��   : b00269685
    �޸�����   : ����ota �� sys
*****************************************************************************/
VOS_UINT8 NAS_MM_IsCsNotSupport(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;                    /* ������յ�����Ϣ����ָ��                 */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;                                                      /* ��Ϣת��                                */

        if ((0 == pstWSysInfoInd->ucCsInfoSize)
         && (MMC_MM_SYS_INFO_TYPE_SYS == pstWSysInfoInd->enSysInfoType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict
 ��������  : CS����ע��ʱ��MMCת����MM��ϵͳ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict( VOS_VOID )
{
    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3211);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertMmlLaiFormatToMMFormat
 ��������  : ��MML��ʽ��LAI��Ϣת����MM��ʽ��LAI��Ϣ
 �������  : pstSrcLai------------MML��ʽ��LAI��Ϣ
 �������  : pstDstLai------------MM��ʽ��LAI��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlLaiFormatToMMFormat(
    NAS_MML_LAI_STRU                   *pstSrcLai,
    MM_LAI_STRU                        *pstDstLai
)
{
    pstDstLai->PlmnId.ulMcc = pstSrcLai->stPlmnId.ulMcc;
    pstDstLai->PlmnId.ulMnc = pstSrcLai->stPlmnId.ulMnc;

    pstDstLai->ulLac        = (pstSrcLai->aucLac[0]<< 8) & 0xFF00;
    pstDstLai->ulLac        |= pstSrcLai->aucLac[1];

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_CheckMmcMmSysInfoIE
 ��������  : ���MMCת����MM��ϵͳ��Ϣ�Ϸ���
 �������  : MMCת����MM��ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:ϵͳ��Ϣ���ͨ��
             VOS_FALSE:ϵͳ��Ϣ��鲻ͨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_CheckMmcMmSysInfoIE(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstGSysInfoInd = VOS_NULL_PTR;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pstGSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

        /* �ж��Ƿ�Ϊ GSM ��ϵͳ��Ϣָʾ��Ϣ */
        if (MMCMM_GSM_SYS_INFO_IND != pstGSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

        /* �ж��Ƿ�Ϊ WCDMA ��ϵͳ��Ϣָʾ��Ϣ */
        if (MMCMM_SYS_INFO_IND != pstWSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        if ((MM_CONST_NUM_8 < pstWSysInfoInd->ucCnCommonSize)
         || (MM_CONST_NUM_8 < pstWSysInfoInd->ucCsInfoSize))
        {                                                                           /* ��Ϣ�е�ȡֵ���Ϸ�                       */
            return VOS_FALSE;                                                       /* ������Ϣ���ʧ��                         */
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateT3212Value_RcvLauAccept
 ��������  : ����T3212��ʱ��ʱ��
 �������  : ucTimerName     - ��ʱ������
             ucMsgTimerValue - ��Ϣ�ж�ʱ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_UpdateT3212Value_RcvLauAccept(
    VOS_UINT8                            ucMsgTimerValue
)
{
    VOS_UINT8                            ucTimerUnit;                                                   /* ������ʱ�����洢ʱ����λ                 */
    VOS_UINT8                            ucTimerValue;                                                   /* ������ʱ�����洢ʱ��                     */

    ucTimerUnit     = 0;
    ucTimerValue    = 0;
    ucTimerUnit     = (VOS_UINT8)(ucMsgTimerValue >> NAS_MML_OCTET_MOVE_FIVE_BITS);
    ucTimerValue    = (VOS_UINT8)(ucMsgTimerValue & NAS_MML_OCTET_LOW_FIVE_BITS);

    /* 24008 10.5.163a�½���������:
    GPRS Timer 3 value (octet 3)
    Bits 5 to 1 represent the binary coded timer value.
    Bits 6 to 8 defines the timer value unit for the GPRS timer as follows:
    Bits
    8 7 6
    0 0 0 value is incremented in multiples of 10 minutes
    0 0 1 value is incremented in multiples of 1 hour
    0 1 0 value is incremented in multiples of 10 hours
    0 1 1 value is incremented in multiples of 2 seconds
    1 0 0 value is incremented in multiples of 30 seconds
    1 0 1 value is incremented in multiples of 1 minute
    1 1 1 value indicates that the timer is deactivated.

    Other values shall be interpreted as multiples of 1 hour in this version of the protocol.
    */
    switch (ucTimerUnit)
    {
        case 0:
            /* 10���� */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 1000);
            break;

        case 1:
            /* 1Сʱ */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;

        case 2:
            /* 10Сʱ */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 60 * 1000);
            break;

        case 3:
            /* 2�� */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 2 * 1000);
            break;

        case 4:
            /* 30�� */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 30 * 1000);
            break;

        case 5:
            /* 1���� */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 1000);
            break;

        case 7:
            /* timer is deactivated */
            NAS_MM_SetNetworkAllocT3212Len(0);
            break;

        default:
            /* 1Сʱ */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo
 ��������  : �յ�guϵͳ��Ϣ�Ƿ���Ҫ����T3212��ʱ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ��Ҫ����
             VOS_TRUE - ����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo(VOS_VOID)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstNetWorkInfo             = NAS_MML_GetNetworkInfo();

    /* ���Э��汾С��R11,������Ҫ����ϵͳ��Ϣ����T3212��ʱ��ʱ�� */
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }

    /* ���֮ǰ�·�T3212��ʱ��ʱ����������뼼���뵱ǰפ������Ľ��뼼����ͬ��������Ҫ����T3212ʱ�� */
    if (pstAllocT3212ValueLaiInfo->enCampPlmnNetRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ���֮ǰ�·�T3212��ʱ��ʱ���������뵱ǰפ��������lai��ͬ���򷵻���Ҫ����T3212ʱ�� */
    if (VOS_FALSE == NAS_MML_CompareLai(&pstNetWorkInfo->stCampPlmnInfo.stLai, pstAllocT3212ValueLaiInfo))
    {
        return VOS_TRUE;
    }

    /* ֮ǰ�·�T3212ʱ��������lai�뵱ǰפ������lai��ͬ����֮ǰ���粻��ͨ��lau accept�·��ģ��򷵻���Ҫ����T3212ʱ�� */
    if (NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST != NAS_MM_GetNetworkT3212ValueType())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateT3212Value_RcvGuSysInfo
 ��������  : �յ�GU�µ�ϵͳ��Ϣ����T3212��ʱ��
 �������  : ucLRTimerT3212-------GU��ϵͳ��Ϣ��Я����T3212ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_UpdateT3212Value_RcvGuSysInfo(
    VOS_UINT8                           ucLRTimerT3212
)
{
    VOS_UINT32                          ulT3212Value;

    /* ���յ�����Ϣ�ṹ�л�ȡ�µ� T3212 ��ʱ���� */
    ulT3212Value    = ucLRTimerT3212 * MM_T3212_UNIT_TRANSFORM;     /* 6����->���� */

    if (ulT3212Value > MM_TIMER_T3212_MAX_VALUE)
    {
        ulT3212Value = MM_TIMER_T3212_MAX_VALUE;
    }

    /* �Զ�ʱ���ȷ������� */
    if ((MM_CONST_NUM_0 == ulT3212Value)
     || (MM_CONST_NUM_0 == gstMmTimer[MM_TIMER_T3212].ulTimerLen))                /* Ϊ�� */
    {
        /* ���� T3212 ��ʱ����Ϊ��Чֵ */
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Value;
        Mm_TimerStop(MM_TIMER_T3212);
    }
    else /* ����ֵ */
    {
        if (gstMmTimer[MM_TIMER_T3212].ulTimerLen != ulT3212Value)
        {
            Mm_ComT3212(ulT3212Value);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateNetModeInfo_RcvGuSysInfo
 ��������  : �յ�GU�µ�ϵͳ��Ϣ��������ģʽ��Ϣ
 �������  : ucNetworkOperationMode-------GU��ϵͳ��Ϣ��Я��������ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(
    VOS_UINT8                           ucNetworkOperationMode
)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if (ucNetworkOperationMode < MM_CONST_NUM_4)
        {
            /* ����ģʽ��Ϣ��Ч */
            if (MM_CONST_NUM_0 != ucNetworkOperationMode)
            {
                /* ��ȡ ucNewNtMod ֵ */
                g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;
            }
            else
            {
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_II;
            }
        }
    }
    else
    {
        g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;

        /* �����ǰ�����类bar����ôֱ��ˢ��һ������ģʽ*/
        if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        {
             g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        }
    }

    /* �����ǰ����ģʽδ֪,����Ϊ�»�ȡ����ģʽ */
    if (MM_CONST_NUM_0 == g_MmGlobalInfo.ucNtMod)
    {
        g_MmGlobalInfo.ucNtMod      = g_MmGlobalInfo.ucNewNtMod;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateNetworkInfo_GasSysInfo
 ��������  : ����GSM�µ�ϵͳ��Ϣ
 �������  : pRcvMsg-------ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetworkInfo_GasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstSysInfoInd     = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    g_MmGlobalInfo.ucSysInfoFlg             = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg  = pstSysInfoInd->ulForbiddenFlg;

    /* �յ�ϵͳ��ϢĬ��С��ID���ı� */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    /* ����������б� */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->stPlmnId.ulMcc);

    if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
    {
        NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

        pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
        pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
        pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
        pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
        pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
        NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
    }

    /* Ĭ���յ�ϵͳ��Ϣ����attach */
    g_MmGlobalInfo.ucAttFlg         = MM_ATT_NEED;

    /* ������Ϣ�� Att ���ݣ�����ȫ�� Att ��־ */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
    {
        g_MmGlobalInfo.ucAttFlg     = MM_ATT_NOT_NEED;
    }

    /* GPRS��֧�� */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucGprsSupportInd)
    {
        g_MmGlobalInfo.usRac            = MM_UNSUPPORT_GPRS;
        g_MmGlobalInfo.ucNtMod          = MM_NET_MODE_INVALID;
        g_MmGlobalInfo.ucNewNtMod       = MM_NET_MODE_INVALID;
    }
    else
    {
        /* RAI�����ı� */
        if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
         || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
        {
            if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
            {
                g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                Mm_TimerStop( MM_TIMER_T3211 );
                Mm_TimerStop( MM_TIMER_T3212 );
            }

            /* ���� LikeB ��־ */
            g_MmGlobalInfo.ucLikeB = MM_FALSE;
        }

        g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

        NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

        ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
        ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
         && ((VOS_FALSE    == ucSimPsRegStatus)
          || (VOS_FALSE    == ucPsAttachAllow)))
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
        }
    }

    /* �յ�G�µ�ϵͳ��ϢĬ��NSD MODΪR99�� */
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    if (GRRMM_MSC_RELEASE98_OR_OLDER == pstSysInfoInd->ucMsrRelease)
    {
        g_stMmNsd.ucNsdMod = MM_NSD_MOD_R98_OR_OLDER;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateNetworkInfo_WasSysInfo
 ��������  : ����WRR�µ�ϵͳ��Ϣ
 �������  : pRcvMsg-------ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��11��
    ��    ��   : b00269685
    �޸�����   : ����ota �� sys
  3.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetworkInfo_WasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoInd = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

    if (RRC_NAS_SYS_MSK_CS_DRX == (RRC_NAS_SYS_MSK_CS_DRX & pstSysInfoInd->ulMask))
    {
        g_MmGlobalInfo.MsCsInfo.ucCsDrxLen = (VOS_UINT8)pstSysInfoInd->ulCsDrxLength;
    }

    if (RRC_NAS_SYS_MSK_CSPS_INFO == (RRC_NAS_SYS_MSK_CSPS_INFO & pstSysInfoInd->ulMask))
    {
        /* W��PS��֧�� */
        if (0 == pstSysInfoInd->ucPsInfoSize)
        {
            if (MMC_MM_SYS_INFO_TYPE_SYS == pstSysInfoInd->enSysInfoType)
            {
                g_MmGlobalInfo.usRac      = MM_UNSUPPORT_GPRS;
                g_MmGlobalInfo.ucNtMod    = MM_NET_MODE_INVALID;
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_INVALID;
            }
        }
        else
        {
            /* RAI�����ı� */
            if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
             || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
            {
                if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
                {
                    g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                    Mm_TimerStop( MM_TIMER_T3211 );
                    Mm_TimerStop( MM_TIMER_T3212 );
                }

                g_MmGlobalInfo.ucLikeB = MM_FALSE;
            }

            g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

            /* ��������ģʽ��Ϣ */
            NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

            ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
            ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
             && ((VOS_FALSE    == ucSimPsRegStatus)
              || (VOS_FALSE    == ucPsAttachAllow)))
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
            }
        }

        if (0 != pstSysInfoInd->ucCsInfoSize)
        {
            if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
            {
                NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

                pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
                pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
                pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
                pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
                pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
                NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
            }

            /* �յ�ϵͳ��ϢĬ������attach */
            g_MmGlobalInfo.ucAttFlg = MM_ATT_NEED;

            if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
            {
                g_MmGlobalInfo.ucAttFlg = MM_ATT_NOT_NEED;
            }
        }
    }

    /* ����������б� */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->PlmnId.ulMcc);

    g_MmGlobalInfo.ucSysInfoFlg = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg = pstSysInfoInd->ulForbiddenFlg;

    /* �յ�ϵͳ��ϢĬ��С��ID���ı� */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId     = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedClearAttemptCounter
 ��������  : �ж��Ƿ���Ҫ���attempt counter
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ���attemp counter
             VOS_FALSE:����Ҫ���attempt counter
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedClearAttemptCounter( VOS_VOID )
{
    /* ����24.008 4.4.4.5 The attempt counter is reset when:
        in case of service state ATTEMPTING to UPDATE��
        a MS detects that a new location area is entered */
    if ((MM_IDLE_PLMN_SEARCH           == g_MmGlobalInfo.ucState)
     && ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucPreState)
      || (MM_IDLE_NO_CELL_AVAILABLE    == g_MmGlobalInfo.ucPreState)))
    {
        if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SndMmcForbidenRslt
 ��������  : ��ǰ�����fobidenʱ��MMC����ע����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��14��
   ��    ��   : l00167671 �޿���
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_SndMmcForbidenRslt(VOS_VOID)
{
    if (MMCMM_FORBIDDEN_PLMN == (MMCMM_FORBIDDEN_PLMN & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                MM_MMC_LU_RESULT_FAILURE,
                NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
    }
    else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
            MM_MMC_LU_RESULT_FAILURE,
            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MM_IsClassAAndNmoIMode
 ��������  : �жϵ�ǰ�ն�ΪAģʽ,פ������ΪNMO1
 �������  : ucCurNtMod-----��ǰפ�����������ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰ��ΪA+Iģʽ
             VOS_FALSE:��ǰ����A+Iģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_IsClassAAndNmoIMode(
    VOS_UINT8                               ucCurNtMod
)
{
    if ((VOS_TRUE      == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == ucCurNtMod)
     && (MM_FALSE      == g_MmGlobalInfo.ucLikeB))
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}




/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, end */


/*****************************************************************************
 �� �� ��  : NAS_MM_GetAttemptUpdateLaiInfo
 ��������  : ��ȡATTEMPT UPDATEʱ��LAI��Ϣ
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : MM_LAI_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
MM_LAI_STRU *NAS_MM_GetAttemptUpdateLaiInfo(VOS_VOID)
{
    return &(g_MmGlobalInfo.MsCsInfo.stAttemptToUpdateLai);
}

/*****************************************************************************
 �� �� ��  : NAS_MM_InitLaiInfo
 ��������  : ��ʼ��MM��LAI��Ϣ
 �������  : pstLai
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_InitLaiInfo(
    MM_LAI_STRU                        *pstLai
)
{
    pstLai->PlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstLai->PlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstLai->ulLac        = MM_INVALID_LAI;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsSameLaiInfo
 ��������  : �ж�MM��LAI��Ϣ�Ƿ�ı�
 �������  : pstCurrLai
             pstOldLai
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_IsSameLaiInfo(
    MM_LAI_STRU                        *pstCurrLai,
    MM_LAI_STRU                        *pstOldLai
)
{
    if ( pstCurrLai->PlmnId.ulMcc != pstOldLai->PlmnId.ulMcc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->PlmnId.ulMnc != pstOldLai->PlmnId.ulMnc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->ulLac != pstOldLai->ulLac)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MM_LocationUpdateAttemptCounter
 ��������  : Location UpdateʱAttempt Counter�Ĵ���
 �������  : ulMmCause:ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��12��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*****************************************************************************/
VOS_VOID NAS_MM_LocationUpdateAttemptCounter(
    VOS_UINT32                          ulMmCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;
    MM_LAI_STRU                                *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                           *pstCampLaiInfo  = VOS_NULL_PTR;

    /* ������1 */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */


        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* ��U2״̬�����浱ǰ��LAI��Ϣ */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
        NAS_MM_UpdateEquPlmnInfo(ulMmCause);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    ulMmCause);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 ulMmCause);

        /* ��U2�Ĺ������� */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212�Ƚ���ֹͣ                                */

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateLauRetryFlg_RcvRelInd
 ��������  : �յ�rel_indʱ����LauRetryFlg��ʶ
 �������  : ulMmCause:ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��12��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_UpdateLauRetryFlg_RcvRelInd(
    RRMM_REL_IND_STRU                  *pRrcRelInd
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();

    /* ucLuAttmptCnt�Ǽ�1֮��Ĵ��� */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
        }
    }
    else
    {
        if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetNetworkT3212ValueType
 ��������  : ��ȡ�����·�T3212ʱ��ֵ��Դ���Ǵ�ϵͳ��Ϣ�л�ȡ���Ǵ�lau accept
             ��Per Ms T3212 IE�л�ȡ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8 NAS_MM_GetNetworkT3212ValueType(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetNetworkT3212ValueType
 ��������  : ���������·�T3212ʱ��ֵ��Դ���Ǵ�ϵͳ��Ϣ�л�ȡ���Ǵ�lau accept
             ��Per Ms T3212 IE�л�ȡ
 �������  : enT3212ValueType - �����·�T3212ʱ��ֵ��Դ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MM_SetNetworkT3212ValueType(
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType
)
{
    g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType = enT3212ValueType;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetAllocT3212ValueLaiInfo
 ��������  : ��ȡ�·�t3212��ʱ��ʱ����LAI��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �·�t3212��ʱ��ʱ����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
NAS_MML_LAI_STRU *NAS_MM_GetAllocT3212ValueLaiInfo(VOS_VOID)
{
    return (&g_MmGlobalInfo.stT3212Info.stAllocT3212ValueLaiInfo);
}



/*****************************************************************************
 �� �� ��  : NAS_MM_GetNetworkAllocT3212Len
 ��������  : ��ȡT3212����ʱ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_GetNetworkAllocT3212Len(VOS_VOID)
{
    return gstMmTimer[MM_TIMER_T3212].ulTimerLen;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetNetworkAllocT3212Len
 ��������  : ���õ�ǰ������T3212����ʱ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_SetNetworkAllocT3212Len(
    VOS_UINT32                          ulNetworkAllocT3212Len
)
{
    gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulNetworkAllocT3212Len;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_LogT3212Info
 ��������  : ��MM��������T3212��Ϣ
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��21��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID  NAS_MM_LogT3212Info(VOS_VOID)
{
    NAS_MM_LOG_T3212_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();

    pstMsg = (NAS_MM_LOG_T3212_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogT3212Info:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_T3212_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_T3212_INFO_IND;

    /* NV�ж��Ƶ�T3212��Ϣ */
    PS_MEM_CPY( &(pstMsg->stMmlT3212NvCfgInfo), NAS_MML_GetT3212TimerInfo(), sizeof(NAS_MML_T3212_TIMER_INFO_CONFIG_STRU));

    /* ��ǰʹ��NV��T3212ʱ���ļ��� */
    pstMsg->ulT3212Count                = NAS_MM_GetT3212StartCount();

    /* ��������T3212��ʱ��ʱ�� */
    pstMsg->ulNetworkT3212Len           = NAS_MM_GetNetworkAllocT3212Len();

    /* ��������T3212��ʱ��ʱ�� */
    pstMsg->ulNetworkRandT3212Len       = NAS_MM_GetNetworkT3212RandLen();

    PS_MEM_CPY(&pstMsg->stAllocT3212ValueLaiInfo, pstAllocT3212ValueLaiInfo, sizeof(pstMsg->stAllocT3212ValueLaiInfo));
    pstMsg->enT3212ValueType = NAS_MM_GetNetworkT3212ValueType();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_Start3212Timer
 ��������  : MM����T3212��ʱ��
 �������  : T3212��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��20��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_StartT3212Timer(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    VOS_UINT32                          ulCurrT3212Len;
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8    enCurrT3212LenType;
    VOS_UINT32                          ulResult;

    enCurrT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* �����ǰT3212��ʱ������ֹͣ״̬������Ҫ���� */
    if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
    {
        return;
    }

    /* ��ά�ɲ⹴T3212�����Ϣ�� */
    NAS_MM_LogT3212Info();

    /* ������T3212ʱ����Ҫ����ʱ��: NV���õ�ʱ������ԭ�е�ʱ�� */
    ulCurrT3212Len = NAS_MM_GetT3212StartSceneTimerLen(enT3212StartScene, &enCurrT3212LenType);

    /* �����ǰ��T3212ʱ��Ϊ0������Ҫ���� */
    if (0 == ulCurrT3212Len)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: Currt3212 TIMER LEN IS ZERO !");

        return;
    }

    /* ����T3212  Mm_TimerStart(MM_TIMER_T3212); */
    ulResult = Mm_StartRelTimer(
                               &gstMmTimer[MM_TIMER_T3212].hTimer,              /* ���TIMER ID�ĵ�ַ */
                               WUEPS_PID_MM,
                               ulCurrT3212Len,                                  /* ʱ�� */
                               MM_TIMER_T3212,                                  /* ��Ϣ���е�ID */
                               gstMmTimer[MM_TIMER_T3212].ulParam,              /* ��Ϣ��ַ */
                               gstMmTimer[MM_TIMER_T3212].ucMode                /* ��Ϣ���ȼ� */
                               );                                               /* ����֧����Ϣ�Ķ�ʱ�� */

    /* ����ʧ�ܣ����˳� */
    if ( VOS_OK != ulResult )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: TIMER CREATE FAILURE!");
        return;
    }

    /* ���õ�ǰ��ʱ�����б�־ */
    gstMmTimer[MM_TIMER_T3212].ucTimerStatus = MM_TIMER_RUNNING;

    if (NAS_MM_T3212_LEN_TYPE_NV_DEFINED == enCurrT3212LenType)
    {
        /* �����ǰ��Ҫ��NV�еĶ�ʱ��ʱ������T3212�����ۼƼ�1 */
        NAS_MM_IncreaseT3212Counter();
    }
    else if (NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN == enCurrT3212LenType)
    {
        /* ��ʼ��ȫ�ֱ�����ֵ */
        NAS_MM_SetNetworkT3212RandLen(0);
    }
    else
    {
    }

    /* T3212��������������T3212���� */
    if (NAS_MM_T3212_START_SCENE_NORMAL_START == enT3212StartScene)
    {
        NAS_MM_InitT3212Counter();
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_IncreaseT3212Counter
 ��������  : ���ӵ�ǰT3212����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_IncreaseT3212Counter(VOS_VOID)
{
    /* �ﵽ���ֵ�Ͳ�����  */
    if (g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount >= NAS_MM_T3212_START_SCENE_COUNTER_MAX_VALUE )
    {
        return;
    }

    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount++;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_InitT3212Counter
 ��������  : ���� T3212����Ϊ0
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_InitT3212Counter(VOS_VOID)
{
    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetT3212StartCount
 ��������  : ��ȡT3212����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulT3212StartCount
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartCount(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetNetworkT3212RandLen
 ��������  : ��ȡT3212����ʱ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_GetNetworkT3212RandLen(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SetNetworkT3212RandLen
 ��������  : ���õ�ǰ������T3212����ʱ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_SetNetworkT3212RandLen(
    VOS_UINT32                          ulCurrT3212Len
)
{
    g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen = ulCurrT3212Len;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedUseTheNvimT3212TimerLen
 ��������  : �ж��Ƿ�ʹ��NV�����õ�T3212��ʱ��ʱ��
 �������  : enT3212StartScene:��������
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ��NV�е�ʱ��
             VOS_FALSE:����Ҫ��NV�е�ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��20��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedUseTheNvimT3212TimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceneCtrlBitIndex;
    VOS_UINT32                                              ulT3212StartCount;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulT3212StartSceneCtrlBitIndex   = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* �жϵ�ǰ�ǲ��Կ�������Ҫ��NVIM�����õ�T3212��ʱ��ʱ��ֵ */
    if (VOS_TRUE == USIMM_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* NVδ����ʱ����ʹ��NVIM�е�ֵ  */
    if (VOS_FALSE == pstT3212Info->ulT3212NvActiveFlg)
    {
        return VOS_FALSE;
    }

    /* �жϵ�ǰT3212ʧ�ܵ�COUNTER�Ѿ������ڶ��׶��ˣ�����Ҫ��NVIM�л�ȡT3212��ʱ����ʱ�� */
    if (ulT3212StartCount >= (pstT3212Info->ulT3212Phase1Count + pstT3212Info->ulT3212Phase2Count))
    {
        return VOS_FALSE;
    }

    /* �ӱ��л�ȡ��ǰ������Ӧ�Ŀ���BIT���� */
    ulT3212StartSceneCtrlBitIndex = NAS_MM_MapT3212StartSceneToCtrlBitIndex(enT3212StartScene);

    /* �жϵ�ǰT3212��������NVIM�����Ƿ�ʹ�ܣ�TRUEΪʹ�ܣ�FALSEΪ��ʹ�� */
    if (VOS_TRUE == NAS_MM_GetT3212StartSceneCtrlBitIndexValue(ulT3212StartSceneCtrlBitIndex))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_MapT3212StartSceneToCtrlBitIndex
 ��������  : ����T3212��������������ȡ���ñ���
 �������  : ulMmCause:ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��20��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_MapT3212StartSceneToCtrlBitIndex(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MM_T3212_START_SCENE_CFG_TBL_STRU                  *pstT3212StartSceanCtrlTblPtr = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceanCtrlBitIndex;
    VOS_UINT32                                              i;

    pstT3212StartSceanCtrlTblPtr = NAS_MM_GET_T3212_START_SCENE_CFG_TBL_PTR();

    /* Ĭ��Ϊ�Ƿ�INDEX */
    ulT3212StartSceanCtrlBitIndex = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* �ӱ��л�ȡ��ǰ������Ӧ�Ŀ���BIT���� */
    for (i = 0; i < NAS_MM_GET_T3212_START_SCENE_CFG_TBL_SIZE(); i++)
    {
        /* �������ñ�,��ȡ��ǰ�����Ŀ���BITλ���� */
        if (enT3212StartScene == pstT3212StartSceanCtrlTblPtr[i].enT3212StartScene)
        {
            ulT3212StartSceanCtrlBitIndex = pstT3212StartSceanCtrlTblPtr[i].ulT3212StartSceneCtrlBitIndex;

            break;
        }
    }

    return ulT3212StartSceanCtrlBitIndex;

}


/*****************************************************************************
 �� �� ��  : NAS_MM_GetT3212StartSceneCtrlBitIndexValue
 ��������  : ����T3212��������������ȡ���ñ���
 �������  : ulMmCause:ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��20��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartSceneCtrlBitIndexValue(
    VOS_UINT32                          ulT3212StartSceneCtrlBitIndex
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;

    pstT3212Info = NAS_MML_GetT3212TimerInfo();

    /* ��ǰ�����Ƿ� */
    if (ulT3212StartSceneCtrlBitIndex >= NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX)
    {
        return VOS_FALSE;
    }

    /* ʹ�ÿ����ֽ�1:bit0~bit31 */
    if (ulT3212StartSceneCtrlBitIndex <= NAS_MML_T3212_START_SCEAN_MASK1_MAX_BIT_INDEX)
    {
        /* ����NV���Ƿ�ʹ��BITֵΪ1��ʹ�ܣ�Ϊ0��ʹ�� */
        if (NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE == ((pstT3212Info->ulT3212StartSceneCtrlBitMask >> ulT3212StartSceneCtrlBitIndex) & NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE))
        {
            return VOS_TRUE;
        }
    }
    else
    {
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetT3212StartSceneTimerLen
 ��������  : ��ȡT3212��ʱ��ʱ��
 �������  : enT3212StartScene:T3212��ʱ����������
 �������  : penT3212LenType
 �� �� ֵ  : VOS_UINT32: T3212����ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartSceneTimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene,
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8                       *penT3212LenType
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartCount;
    VOS_UINT32                                              ulNetworkAllocT3212Len;
    VOS_UINT32                                              ulNetworkT3212RandLen;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulNetworkAllocT3212Len          = NAS_MM_GetNetworkAllocT3212Len();
    ulNetworkT3212RandLen           = NAS_MM_GetNetworkT3212RandLen();
    *penT3212LenType                = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* �жϵ�ǰ�Ƿ��NV�л�ȡ���õ�T3212��ʱ��ʱ�� */
    if (VOS_TRUE == NAS_MM_IsNeedUseTheNvimT3212TimerLen(enT3212StartScene))
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NV_DEFINED;

        /* ���T3212ʧ�ܴ���С�ڵ�һ�׶Σ���ʹ�õ�һ�׶ε�ʱ���������õڶ��׶ε�ʱ�� */
        if (ulT3212StartCount < pstT3212Info->ulT3212Phase1Count)
        {
            return pstT3212Info->ulT3212Phase1TimeLen;
        }

        return pstT3212Info->ulT3212Phase2TimeLen;
    }

    /* ȡ��������T3212 RAND��ʱ��ʱ��  */
    if ( (MM_CONST_NUM_0 != ulNetworkT3212RandLen)
      && (MM_CONST_NUM_0 != ulNetworkAllocT3212Len) )
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN;

        /* ��������·��µ�T3212ʱ������ǰT3212û�������У���ȡ�����������·�ʱ�������ֵ */
        return ulNetworkT3212RandLen;
    }

    /* ȡ�����·���T3212ʱ�� */
    return ulNetworkAllocT3212Len;
}

#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertCsfbServiceStatusToRrcSessionType
 ��������  : ��CSFB����״̬ת������Ӧ��Session����
             (������øú���ʱ�����CSFB����״̬ʹ��)
 �������  : enCsfbServiceStatus:CSFB����
 �������  : penRrcSessionType  :��ӦRrc��Session����

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8                        *penRrcSessionType
)
{
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_CSFB;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCsfbServiceStatusChange
 ��������  : ����CSFB��ǣ�CSFB��ǴӴ��ڸ��³ɲ�����ʱ����Ҫ�ͷ�������Դ
 �������  : enCurStatus   :��ǰ��CSFB��־     ----- BUTT����NOT_EXIST����
             enTargetStatus:��Ҫ���µ�CSFB��־ ----- BUTT����NOT_EXIST����
             (��ò�Ҫʹ��BUTTֵ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��9��16��
   ��    ��   : f00179208
   �޸�����   : cs_err_log��Ŀ����쳣��¼
*****************************************************************************/
VOS_VOID NAS_MM_ProcCsfbServiceStatusChange(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCurStatus,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enTargetStatus
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;


    /* �������BUTTֵ��Ĭ����Ϊ�����ڣ�һ���ֹ����BUTT */
    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enCurStatus )
    {
        enCurStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enTargetStatus )
    {
        enTargetStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    /* CSFB��־���޵��У�����������Դ֪ͨ */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enTargetStatus, &enRrcSessionType);

        /* �ͷ�������Դ */
        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    /* CSFB��־���е��ޣ������ͷ���Դ֪ͨ */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enCurStatus, &enRrcSessionType);

        /* �ͷ�������Դ */
        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }
#endif

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertRrcRelCauseToMmCcRelCause
 ��������  : ��RRC RELԭ��ֵת����MM��CC��ԭ��ֵ
 �������  : RRC_REL_CAUSE_ENUM_UINT32     :RRC RELԭ��ֵ
 �������  : ��
 �� �� ֵ  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM��CC��ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��20��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertRrcRelCauseToMmCcRelCause(
    RRC_REL_CAUSE_ENUM_UINT32           enRrcRelCause
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astRrcToMmCcRelCause) / sizeof(g_astRrcToMmCcRelCause[0])); i++)
    {
        if (enRrcRelCause == g_astRrcToMmCcRelCause[i].enRrcRelCause)
        {
            enRelCause = g_astRrcToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertEstCnfRsltToMmCcRelCause
 ��������  : ��EST_CNF���ת����MM��CC��ԭ��ֵ
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32:RRC RELԭ��ֵ
 �������  : ��
 �� �� ֵ  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM��CC��ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��20��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertEstCnfRsltToMmCcRelCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32     enEstCnfRslt
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astEstRsltToMmCcRelCause) / sizeof(g_astEstRsltToMmCcRelCause[0])); i++)
    {
        if (enEstCnfRslt == g_astEstRsltToMmCcRelCause[i].enEstRslt)
        {
            enRelCause = g_astEstRsltToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertLauEstCnfRsltToT3212StartScean
 ��������  : ��LAU��EST_CNF���ת��������T3212�ĳ���
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32:enEstCnfRsltԭ��ֵ
 �������  : ��
 �� �� ֵ  : NAS_MM_T3212_START_SCENE_ENUM_UINT32:T3212��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��20��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MM_T3212_START_SCENE_ENUM_UINT32 NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfRslt
)
{
    VOS_UINT32                                              i;
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene;

    enT3212StartScene  = NAS_MM_T3212_START_SCENE_BUTT;

    for (i = 0; i < (sizeof(g_astLauEstCnfRsltToT3212StartScene) / sizeof(g_astLauEstCnfRsltToT3212StartScene[0])); i++)
    {
        if (enEstCnfRslt == g_astLauEstCnfRsltToT3212StartScene[i].enEstRslt)
        {
            enT3212StartScene = g_astLauEstCnfRsltToT3212StartScene[i].enT3212StartScene;
            break;
        }
    }

    return enT3212StartScene;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause
 ��������  : ��CSFBʧ�ܽ��ת����MM��CC��ԭ��ֵ
 �������  : LMM_MM_CSFB_SERVICE_END_IND_STRU:CSFB�����쳣��ֹ�ṹ��
 �������  : ��
 �� �� ֵ  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM��CC��ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��07��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstCsfbEndInd
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT;

    /* CSFB service rej */
    if (MM_LMM_CSFB_SERVICE_RSLT_CN_REJ == pstCsfbEndInd->enCsfbSrvRslt)
    {
        enRelCause  = (pstCsfbEndInd->ulCnCause) + NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN;
    }
    /* ����ΪCSFB LMM Error */
    else
    {
        for (i = 0; i < (sizeof(g_astCsfbRsltToMmCcRelCause) / sizeof(g_astCsfbRsltToMmCcRelCause[0])); i++)
        {
            if (pstCsfbEndInd->enCsfbSrvRslt    == g_astCsfbRsltToMmCcRelCause[i].enCsfbRslt)
            {
                enRelCause = g_astCsfbRsltToMmCcRelCause[i].enMmCcRelCause;
            }
        }
    }

    return enRelCause;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_IsGsmOnlyEstCnfRslt
 ��������  : �ж��ǲ���ֻ��GSM�²��е�EST_CNFԭ��ֵ
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsGsmOnlyEstCnfRslt(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT == ulResult)
     || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == ulResult)
     || (RRC_EST_RJ_RA_FAIL == ulResult)
     || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO == ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsHoBetweenGU
 ��������  : �ж��Ƿ���GU֮����л�����
 �������  : enSrcRatType:��ϵͳǰ�Ľ��뼼��
             enDestRatType:��ϵͳ��Ľ�����뼼��
             enSuspendCause:����ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��GU֮����л����� VOS_FALSE:����GU֮����л�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��13��
   ��    ��   : s00217060
   �޸�����   : ��������

*****************************************************************************/
VOS_UINT8 NAS_MM_IsHoBetweenGU(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRatType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
 {
    /* ��ϵͳʧ�ܣ�����FALSE */
    if (enSrcRatType == enDestRatType)
    {
        return VOS_FALSE;
    }

    /* ��ϵͳǰ��Ľ��뼼����LTE������FALSE */
#if (FEATURE_ON == FEATURE_LTE)
    if ( (NAS_MML_NET_RAT_TYPE_LTE == enSrcRatType)
      || (NAS_MML_NET_RAT_TYPE_LTE == enDestRatType) )
    {
        return VOS_FALSE;
    }
#endif

    /* ����ԭ��ֵ����handover������FALSE */
    if (MMC_SUSPEND_CAUSE_HANDOVER != enSuspendCause)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_StartHoWaitSysInfoTimer
 ��������  : HOʱ���ȴ�ϵͳ��Ϣ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��18��
   ��    ��   : s00217060
   �޸�����   : ��������

*****************************************************************************/
VOS_VOID NAS_MM_StartHoWaitSysInfoTimer(
    VOS_UINT8                           ucTimerId
)
{
    /* ��ʱ����ͣ����,��ʱ��ʱ����NV���� */
    Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

    /* ����HO��ϵͳ��Ϣ�Ķ�ʱ�� */
    Mm_TimerStart(ucTimerId);

    return;
}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : NAS_MM_RecordCsPagingFail_WaitForRrConnection
 ��������  : ���Լ�¼Cs Paging Fail
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult   - �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��10��
   ��    ��   : n00269697
   �޸�����   : ��������

*****************************************************************************/
VOS_VOID NAS_MM_RecordCsPagingFail_WaitForRrConnection(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    /* ���������RRC_EST_SUCCESS����RRC_EST_PRESENT������Ҫ��¼ */
    if ((RRC_EST_SUCCESS == ulResult)
     || (RRC_EST_PRESENT == ulResult))
    {
        return;
    }

    /* �����CSFB MT�Ĺ���������Ҫ��¼CS PAGING FAIL */
    if (NAS_ERR_LOG_CSFB_MT_STATE_NULL != NAS_MML_GetCsfbMtCurrState())
    {
        return;
    }

    if ((MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
    {
        /* CS PAGING��·����ʧ�ܵ��쳣��¼ */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_FAIL);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ParseErrLogCsPagingInfo
 ��������  : ���ϲ㴫�ݹ����Ĳ����洢ȫ�ֱ���
 �������  : VOS_VOID            *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ParseErrLogCsPagingInfo(
    VOS_VOID                           *pRcvMsg
)
{
    RRMM_PAGING_IND_STRU               *pstWPagingMsg = VOS_NULL_PTR;
    GRRMM_PAGING_IND_ST                *pstGPagingMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_NULL_PTR == pRcvMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_ParseErrLogCsPagingInfo(): parameter is NULL pointer.");
        return;
    }

    enRatType = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        pstGPagingMsg = (GRRMM_PAGING_IND_ST *)pRcvMsg;

        NAS_MML_SetErrLogGMsIdType(pstGPagingMsg->ucMSIDType);
        NAS_MML_SetErrLogGPagingType(pstGPagingMsg->ucPagingType);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
    {
        pstWPagingMsg = (RRMM_PAGING_IND_STRU *)pRcvMsg;

        NAS_MML_SetErrLogWCnDomainId(pstWPagingMsg->ulCnDomainId);
        NAS_MML_SetErrLogWPagingType(pstWPagingMsg->ulPagingType);
        NAS_MML_SetErrLogWPagingCause(pstWPagingMsg->ulPagingCause);
        NAS_MML_SetErrLogWPagingUeId(pstWPagingMsg->ulPagingUeId);
    }
    else
    {
        ;
    }

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_RecordErrorLogInfo
 ��������  : ��¼������Ϣ
 �������  : enState        ---  ����״̬
             ulCause        ---  ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_RecordErrorLogInfo(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState,
    VOS_UINT32                          ulCause
)
{
    VOS_UINT32                          ulTimerStatus;
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;

    ulTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    /* �����CSFB MT�������У����¼��ص�CSFB MT����Ϣ */
    if ((MM_TIMER_RUNNING                                       == ulTimerStatus)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT     == enBaseState)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == enBaseState))
    {
        enCsfbMtState = NAS_MNTN_ConvertBaseStateToCsfbMtState(enBaseState);

        NAS_MM_FillCsfbMtInfo(enCsfbMtState, ulCause);
    }

    /* ��Ҫ��¼����ҵ�񳡾�����Ϣ����ӵ����� */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ClearErrorLogInfo
 ��������  : ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ClearErrorLogInfo(VOS_VOID)
{
    NAS_MML_InitCsfbMtInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_FillCsfbMtInfo
 ��������  : ���CSFB MT�Ĺ��̵���Ϣ
 �������  : enCsfbMtState  ---  ����״̬
             ulCause        ---  ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_FillCsfbMtInfo(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState,
    VOS_UINT32                          ulCause
)
{
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU       *pstCsfbMtInfo   = VOS_NULL_PTR;
    NAS_MNTN_POSITION_INFO_STRU            *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU    *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                              ulPositionNum;
    VOS_UINT32                              ulStateNum;

    pstCsfbMtInfo       = NAS_MML_GetCsfbMtInfoAddr();

    /* ���Ƕ�Ӧ��״̬���򲻼�¼��Ϣ */
    if (enCsfbMtState > NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT)
    {
        return;
    }

    NAS_MML_SetCsfbMtCurrState(enCsfbMtState);

    ulPositionNum = NAS_MML_GetCsfbMtRecordPositionNum();
    ulStateNum    = NAS_MML_GetCsfbMtRecordStateNum();

    /* �յ�LMM��paging ind״̬����Ҫ����ǰL��λ������Ϣ��¼������
       �յ�ϵͳ��Ϣ��״̬����Ҫ������ص�λ������Ϣ��
       ������¼����������Ͳ��ټ�¼ */
    if ((NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED     == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED    == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED   == enCsfbMtState))
    {
        if (ulPositionNum < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM)
        {
            pstPositionInfo = &(pstCsfbMtInfo->astPositionInfo[ulPositionNum]);

            NAS_MNTN_OutputPositionInfo(pstPositionInfo);
        }

        NAS_MML_AddCsfbMtRecordPositionNum();
    }

    /* ������Ӧ��״̬��Ϣ��������¼����������Ͳ��ټ�¼ */
    if (ulStateNum < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM)
    {
        pstStateInfo = &(pstCsfbMtInfo->astStateInfo[ulStateNum]);
        pstStateInfo->enCsfbMtState = enCsfbMtState;
        pstStateInfo->ulMmState     = Mm_GetState();
        pstStateInfo->ulCause       = ulCause;
        pstStateInfo->ulTick        = VOS_GetTick();
    }

    NAS_MML_AddCsfbMtRecordStateNum();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetRrcPidFromCurrRatType
 ��������  : ��ȡ��ǰ����ģʽ�Ľ����PID
 �������  : VOS_UNT
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��06��01��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetRrcPidFromCurrRatType(
    VOS_UINT32                         *pulPid
)
{
    VOS_UINT32                          ulRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    /* ��ʼ�� */
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    switch(enCurrNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *pulPid = UEPS_PID_GAS;
            ulRet   = VOS_OK;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *pulPid = WUEPS_PID_WRR;
            ulRet   = VOS_OK;
            break;

        default:
            ulRet   = VOS_ERR;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsLauRejNeedRetry
 ��������  : LAUע�ᱻ��ʱ���Ƿ���Ҫ��������ע��
 �������  : VOS_UINT8                           ucCause
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MM_IsLauRejNeedRetry(
    VOS_UINT8                           ucCause
)
{
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     *pstLauRejCfg = VOS_NULL_PTR;
    VOS_UINT8                                               ucIsCurCauseInNvCauseList;
    VOS_UINT32                                              i;

    pstLauRejCfg                = NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo();
    ucIsCurCauseInNvCauseList   = VOS_FALSE;

    /* ���Կ�ʱ��Ҫ�������� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_TRUE;
    }

    /* ���ҵ�ǰԭ��ֵ�Ƿ���NV���õ�ԭ��ֵ�б��� */
    for (i=0; i < pstLauRejCfg->ucLauRejCauseNum; i++)
    {
        if (ucCause == pstLauRejCfg->aucLauRejCause[i])
        {
            ucIsCurCauseInNvCauseList   = VOS_TRUE;
            break;
        }
    }


    /* ���ҵ�����ʱ������ԭ��ֵ��NV�б��У����ҳ��Դ����Ѿ��ﵽNV�����õĴ���������Ҫ�������� */
    if ((VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_TRUE == ucIsCurCauseInNvCauseList)
     && (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= pstLauRejCfg->ucLauRejTimes))
    {
        return VOS_FALSE;
    }

    /* ������������类�ܲ���Ҫ���Ե�NV�������Ҫ�ٳ��� */
    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertCallStatusToTransactionStatus
 ��������  : ��CALL STATUS�еõ�transaction״̬
 �������  : RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertCallStatusToTransactionStatus(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateCallStatus_RcvCcEstReq
 ��������  : �յ�MMCC_EST_REQʱ����call status��־
 �������  : MMCC_EST_REQ_STRU                   *pstEstReq
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCallStatus_RcvCcEstReq(
    MMCC_EST_REQ_STRU                   *pstEstReq
)
{
    /* ��һ�η������(�����ز�ʱ),��Ĭ��Ϊgu�µĺ��У�
       ��������Ƿ���LMM�ģ��ڸ�LMM����csfb startʱ����¸ñ�־
    */

    if (VOS_FALSE == pstEstReq->ucRedialFlg)
    {

        NAS_NORMAL_LOG(WUEPS_PID_MM,
        "NAS_MM_UpdateCallStatus_RcvCcEstReq: Not Redail call, Set CellNotSupportCsmoFlg to FALSE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_FALSE);

        if (MMCC_EMERGENCY_CALL == pstEstReq->ulCallType)
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_START);
        }
        else
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_START);
        }

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateCallStatus_RcvCallStatusNty
 ��������  : �յ����н���״̬ʱ������MML�е�call status
 �������  : MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCallStatus_RcvCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enOldMoCallStatus;

    enOldMoCallStatus   = NAS_MML_GetMoCallStatus();

    /* �������б�־ */
    switch (enOldMoCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_UpdateSsStatus_RcvSsStatusNty
 ��������  : �յ�MMSS_STATUS_NTYʱ����ss status
 �������  : MMSS_STATUS_ENUM_UINT8              enSsStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_UpdateSsStatus_RcvSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
)
{

    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enOldMoSsStatus;

    enOldMoSsStatus = NAS_MML_GetMoSsStatus();

    /* ����MO��־ */
    switch (enOldMoSsStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertSsStatusToTransactionStatus
 ��������  : ��SS STATUS�еõ�transaction״̬
 �������  : RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertSsStatusToTransactionStatus(
    MMSS_STATUS_ENUM_UINT8              enSsStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedLauFirst_CsfbMoEmcExist
 ��������  : CSFB MO����������ʱ���Ƿ���Ҫ����LAU
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedLauFirst_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* ������������ʱ��CSFB MO EMC��Ҫ����LAU���ٴ��������:
        1. ��������csfb��gu��LAI�ı��Ƚ���lau��NV���
        2. LAI�����仯
        3. CS������
    */

    if ((VOS_TRUE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
     && (VOS_TRUE == ulLaiChangeFlag)
     && (VOS_FALSE == ulCsRestrictRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist
 ��������  : CSFB MO EMC����ʱ��MM�ϱ�cs��ע��״̬�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* ������CSFB��GU,��Ҫ��LAUʱ�����ϱ�CS��ע��״̬����ע�����ʱ�ϱ���ʵ��ע��״̬ */
    if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
    {
        return;
    }

    /* CS������ֱ���ϱ�ע����Ϊaccess bar */
    if (VOS_TRUE == ulCsRestrictRegFlg)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    }
    /* LAIδ�����ı�ʱ��update status״̬��updated������ֱ�ӱ�ע��ɹ�����Ϊ��LAI��last succ lai */
    else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
          && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (VOS_FALSE == ulLaiChangeFlag))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

    }
    /* NV��Ƶ��µĲ���LAU���ϱ�ע����Ϊ��ϵͳ�ɹ���MMC�ᱨ֮ǰ��CS�����״̬��ע��״̬ */
    else if (VOS_FALSE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);

    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ProcT3213AttemptCounter
 ��������  : GSM��T3213����ʱ�����LAI�ı䣬������T3213 Attempt Counter
 �������  : ulT3213Status: T3213����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcT3213AttemptCounter(
    VOS_UINT32                          ulT3213Status
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT32                          ucIsCampLaiChange;

    enCurrNetRat = NAS_MML_GetCurrNetRatType();
    ucIsCampLaiChange = NAS_MML_IsCampLaiInfoChanged();

    /* GSM��T3213����ʱ�����LAI�ı䣬����Lau��MM��״̬��ΪWAIT_FOR_RR_CONNECTION_LOCATION_UPDATING����ʱ����T3213 Attempt Counter */
    if ((NAS_MML_NET_RAT_TYPE_GSM                 == enCurrNetRat)
     && (VOS_TRUE                                 == ucIsCampLaiChange)
     && (MM_TIMER_RUNNING                         == ulT3213Status)
     && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcLuAttemptCounter
 ��������  : ���ݽ������������ Lu Attempt Counter
 �������  : enEstResult: �������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcLuAttemptCounter(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstResult)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT8                           ucTrigLauOnceFlg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode           = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurrNetRat              = NAS_MML_GetCurrNetRatType();
    ucTrigLauOnceFlg          = NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
     && (VOS_TRUE == ucTrigLauOnceFlg)
     && (MM_CONST_NUM_5 == g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt))
    {
        if ((RRC_EST_RANDOM_ACCESS_REJECT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }

        if ((RRC_EST_RJ_TIME_OUT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }
    }

    /* NO_RFʱ���ۼ� */
    if (RRC_EST_RJ_NO_RF != enEstResult)
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ComProcPsRandomAccessFailCnt
 ��������  : W������RAU/Attach����ʧ�ܣ�MM����ԭ��ֵ������ȫ�ֱ���ucPsEstCnfFailCnt
 �������  : enRegFailCause: ����ʧ��ԭ��ֵ
             ulRegCounter  : RAU/Attach Attempt Counter
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MM_ComProcPsRandomAccessFailCnt(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause,
    VOS_UINT32                          ulRegAttemptCounter
)
{
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT != enRegFailCause)
        {
            g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
        }
        else
        {
            /* RAI�ı�ʱ��GMMģ�������Rau/Attach Attempt Counter����ʱҲ��Ҫ����ucPsEstCnfFailCnt
            *  ���ǣ����õ�ʱ��û��֪ͨMMģ�飬֮����Rau/Attach���������ʧ����ulRegCounterΪ1��
            *  ��ʱ��ͬ������ȫ�ֱ���ucPsEstCnfFailCnt��ֵΪ1
            */
            if (MM_CONST_NUM_1 == ulRegAttemptCounter)
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = MM_CONST_NUM_1;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt++;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcLauEstCnfNoRf
 ��������  : ����ʧ��ԭ��ֵ no_rf�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��23��
   ��    ��   : j00174725
   �޸�����   : DTS2015060105317(LAU ����ʧ��ԭ��NO_RFʱ������Ҫ֪ͨMMC)
*****************************************************************************/
VOS_VOID NAS_MM_ProcLauEstCnfNoRf(VOS_VOID)
{
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    }

    NAS_MM_ProcLuAttemptCounter(RRC_EST_RJ_NO_RF);

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
            && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* ���LAI����,�Ҹ���״̬ΪU1��ʱ��         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);  /* ��MMC����MMCMM_LU_RESULT_IND             */

            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */
            g_T3211Flag = 1;
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();

            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* ��U2״̬�����浱ǰ��LAI��Ϣ */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        /* ��U2�Ĺ������� */
        Mm_ComToU2Handle();

        NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(RRC_EST_RJ_NO_RF));
    }

    if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
    {
         Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                          /* RR���Ӳ�����                             */

         NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertToMmlSessionType
 ��������  : ��MM��Session type ת��MML������
 �������  :
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��27��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
)
{
    switch(enMmSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SMS;
            break;

        default:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetMmCmRelCause
 ��������  : ����MM��ǰ״̬��ȡMMCM RELԭ��ֵ
 �������  :
 �������  :
 �� �� ֵ  : ��CM��REL IND��Ϣ��ҪЯ����ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��19��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_GetMmCmRelCause(VOS_VOID)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    switch(g_MmGlobalInfo.ucState)
    {
        case IMSI_DETACH_PENDING:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_PLMN_SEARCH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK;
            break;

        case MM_IDLE_ATTEMPTING_TO_UPDATE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case LOCATION_UPDATING_PENDING:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case MM_WAIT_FOR_ATTACH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case MM_INTER_RAT_CHANGE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE;
            break;

        case MM_IDLE_LIMITED_SERVICE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE;
            break;

        case MM_STATE_NULL:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_NO_IMSI:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_NO_CELL_AVAILABLE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE;
            break;

        case WAIT_FOR_RR_CONNECTION_IMSI_DETACH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case IMSI_DETACH_INITIATED:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        default:
            enRelCause = (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT;
            break;
    }

    return enRelCause;
}

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

