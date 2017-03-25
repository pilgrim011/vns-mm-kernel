/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaMsgPrioCompare.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��7��22��
  ����޸�   :
  ��������   : TafMmaMsgPrioCompare.h��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��22��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafMmaMsgPrioCompare.h"
#include  "TafFsm.h"
#include  "Taf_Tafm_Remote.h"
#include  "TafOamInterface.h"
#include  "TafLog.h"
#include  "TafMmaSndInternalMsg.h"
#include  "TafMmaSndApp.h"

#include  "MmaMsccInterface.h"

#include "Taf_Status.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
 ȫ�ֱ�����    : g_astMmaMsgPrioCompareWithPhoneModeTbl
 ȫ�ֱ���˵��  : MMA phone mode ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2013��7��22��
   ��    ��   : w00176964
   �޸�����   : �½�

  2.��    ��   : 2014��2��19��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ�޸�
  3.��    ��   : 2015��3��13��
    ��    ��   : b00269685
    �޸�����   : �б����ϱ��ı�ӿ��޸�
*****************************************************************************/
TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithPhoneModeTbl[] =
{
    /* phone mode�������յ�OM��ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* Deleted by w00167002 for L-C��������Ŀ, 2014-2-19, begin */
    /* ģʽ��ѯ����Ҫ�Ƚ� */
    /* Deleted by w00167002 for L-C��������Ŀ, 2014-2-19, end */


    /* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

    /* phone mode�������յ�ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* phone mode�������յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode),

    /* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

    /* phone mode�������յ�TAF��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode),
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */

    /* phone mode�������յ�AT��list�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode),
#if (FEATURE_ON == FEATURE_CSG)
    /* phone mode�������յ�AT��csg list�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ),
                             TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode),

#endif
    /* phone mode�������յ�AT���û�ָ�������������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode),

    /* phone mode�������յ�AT��attach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithPhoneMode),

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, begin */

    /* phone mode�������յ�AT��detach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithPhoneMode),
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, end */

    /* phone mode�������յ�AT���Զ���ѡ�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode),
#if (FEATURE_ON == FEATURE_IMS)
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode),
#endif

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             TAF_MMA_CompareSTKRefreshWithPhoneMode),
};

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 ȫ�ֱ�����    : g_astMmaMsgPrioCompareWithImsSwitchTbl
 ȫ�ֱ���˵��  : MMA IMS SWITCH״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithImsSwitchTbl[] =
{
    /* IMS SWITCH�������յ�OM��ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch),

    /* IMS SWITCH�������յ�TAF��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT���û�ָ�������������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT��attach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT��detach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT���Զ���ѡ�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch),

    /* IMS SWITCH�������յ�TAF��IMS���ػ��������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch),


    /* IMS SWITCH�������յ�MSCC��PLMN RESEL�ظ�����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMA_PLMN_RESEL_CNF),
                             TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch),

};
#endif

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmaMsgPrioCompareWithSysCfgTbl
 ȫ�ֱ���˵��  : MMA SYS CFG ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2015��4��8��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithSysCfgTbl[] =
{
    /* ��SYS CFG�����У��յ�OAMģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�APP��ģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�CBT��ģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg),



    /* ��SYS CFG������, �յ�APP��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�MMA�ڲ����͵�ϵͳ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��ATTACH�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAttachReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��DETACH�����������Ϣ���ȼ��Ƚ�, ����L-C������ */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareDetachReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��PLMN RESEL�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_ComparePlmnReselReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��PLMN LIST�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_ComparePlmnListReqPrioWithSysCfg),
#if (FEATURE_ON == FEATURE_CSG)
    /* ��SYS CFG������, �յ�APP��CSG PLMN LIST�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ),
                             TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_ABORT_REQ),
                             TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg),
#endif

    /* ��SYS CFG������, �յ�APP��PLMN USER SEL�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_ABORT_REQ),
                             TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg),

    #if (FEATURE_ON == FEATURE_IMS)
    /* ��SYS CFG������, �յ�APP��ims switch�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg),
    #endif

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             TAF_MMA_CompareSTKRefreshWithSysCfg),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmaMsgCompareTbl
 ȫ�ֱ���˵��  : MMA״̬���ȽϺ�����
  1.��    ��   : 2013��7��22��
    ��    ��   : w00176964
    �޸�����   : �½�
  2.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
TAF_MMA_FSM_MSG_COMPARE_STRU g_astMmaMsgCompareTbl[] =
{
     /* phone mode ״̬���ȽϺ�����*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_PHONE_MODE,
                                 g_astMmaMsgPrioCompareWithPhoneModeTbl),

#if (FEATURE_ON == FEATURE_IMS)
    /* IMS SWITCH״̬���ȽϺ�����*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_IMS_SWITCH,
                                 g_astMmaMsgPrioCompareWithImsSwitchTbl),
#endif
     TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_SYS_CFG,
                                  g_astMmaMsgPrioCompareWithSysCfgTbl),
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode
 ��������  : ��MMA�յ���OM��ATģʽ������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��SYSCFG����������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode
 ��������  : ��MMA�յ���MMA���ڲ�usim��״̬�ı�ָʾ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��8��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��list ����������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��csg list ����������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#endif
/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��ָ�� ����������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtAttachPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��attach������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtDetachPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��detach������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode
 ��������  : ��MMA�յ���AT��������ѡ������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareSTKRefreshWithPhoneMode
 ��������  : ��MMA�յ���STK Refresh��Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��7��
    ��    ��   : h00313353
    �޸�����   : STK REFRESH

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareSTKRefreshWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode
 ��������  : ��MMA�յ���IMS SWITCH������Ϣ��phone mode״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch
 ��������  : ��MMA�յ���OM��ATģʽ������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��SYSCFG����������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch
 ��������  : ��MMA�յ���MMA���ڲ�usim��״̬�ı�ָʾ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnListReqPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��list ����������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��ָ�� ����������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtAttachPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��attach������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtDetachPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��detach������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch
 ��������  : ��MMA�յ���AT��������ѡ������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch
 ��������  : ��MMA�յ���TAF��IMS���ػ�������Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch
 ��������  : ��MMA�յ���MSCC��PLMN RESEL�ظ���Ϣ��IMS SWITCH״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#endif
/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg
 ��������  : ��MMA�յ���OM��ATģʽ������Ϣ��SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬������Ϊattach/detach�������յ�phone mode���ã��ɴ�ϵ�ǰ���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* �����ǰSYS CFG״̬������Ϊsystem cofigure setting�������յ�phone mode���ã�����phone mode */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* �����ϲ�Ӧ�÷�������ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg
 ��������  : ��MMA�յ��ڲ���USIM״̬�ı�ָʾ��SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬������Ϊattach/detach�������յ�usim״̬�ı䣬�ɴ�ϵ�ǰ���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* �����ǰSYS CFG״̬������Ϊsystem cofigure setting�������յ�usim״̬�ı䣬����usim��״̬�仯ָʾ */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* �����ϲ�Ӧ�÷�������ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��ϵͳ����������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ǰSYS CFG�����У��ܾ���ǰϵͳ�������� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareAttachReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��ATTACH������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareAttachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareDetachReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��DETACH������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareDetachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareSTKRefreshWithSysCfg
 ��������  : ��MMA�յ�STK Refresh��Ϣ��SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��7��
    ��    ��   : h00313353
    �޸�����   : STK Refresh

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareSTKRefreshWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePlmnReselReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��PLMN RESEL REQ������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePlmnReselReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��CSG PLMN LIST REQ������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��CSG LIST ABORT REQ������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstEntryMsgAddr = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT32                          ulPlmnListEvent;
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstPlmnListAbortMsg = VOS_NULL_PTR;

    pstPlmnListAbortMsg = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;

    ulPlmnListEvent = TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ);

    pstEntryMsgAddr = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstEntryMsgAddr->ucCacheMsgNum; i++)
    {
        if (ulPlmnListEvent == pstEntryMsgAddr->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            pstEntryMsgAddr->ucCacheMsgNum--;

            /* ���CSG LIST REQ�¼�, move�����к���Ļ�����Ϣ */
            PS_MEM_MOVE(&(pstEntryMsgAddr->astMsgQueue[i].stMsgEntry),
                        &(pstEntryMsgAddr->astMsgQueue[i+1].stMsgEntry),
                        sizeof(TAF_MMA_ENTRY_MSG_STRU) * (pstEntryMsgAddr->ucCacheMsgNum - i));

            /* ��Ϣ���������һ����Ϣ�����0 */
            PS_MEM_SET(&(pstEntryMsgAddr->astMsgQueue[pstEntryMsgAddr->ucCacheMsgNum].stMsgEntry),
                       0,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            break;
        }
    }

    /* �ϱ�AT��ǰ״̬�¼� */
    TAF_MMA_SndCsgListAbortCnf(&(pstPlmnListAbortMsg->stCtrl), TAF_ERR_NO_ERROR);

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* �Ѵ�����ϣ����Ը���Ϣ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePlmnListReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��PLMN LIST REQ������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePlmnListReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��PLMN_USER_SEL������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��PLMN ABORT REQ������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstEntryMsgAddr = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT32                          ulPlmnListEvent;
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU   *pstPlmnListAbortMsg = VOS_NULL_PTR;

    pstPlmnListAbortMsg = (TAF_MMA_PLMN_LIST_ABORT_REQ_STRU *)pstMsg;

    ulPlmnListEvent = TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ);

    pstEntryMsgAddr = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstEntryMsgAddr->ucCacheMsgNum; i++)
    {
        if (ulPlmnListEvent == pstEntryMsgAddr->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            pstEntryMsgAddr->ucCacheMsgNum--;

            /* ���PLMN LIST REQ�¼�, move�����к���Ļ�����Ϣ */
            PS_MEM_MOVE(&(pstEntryMsgAddr->astMsgQueue[i].stMsgEntry),
                        &(pstEntryMsgAddr->astMsgQueue[i+1].stMsgEntry),
                        sizeof(TAF_MMA_ENTRY_MSG_STRU) * (pstEntryMsgAddr->ucCacheMsgNum - i));

            /* ��Ϣ���������һ����Ϣ�����0 */
            PS_MEM_SET(&(pstEntryMsgAddr->astMsgQueue[pstEntryMsgAddr->ucCacheMsgNum].stMsgEntry),
                       0,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            break;
        }
    }

    /* �ϱ�AT��ǰ״̬�¼� */
    TAF_MMA_SndPlmnListAbortCnf(&(pstPlmnListAbortMsg->stCtrl), TAF_ERR_NO_ERROR);

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* �Ѵ�����ϣ����Ը���Ϣ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcessComparePrioRsltAbort
 ��������  : ������Ϣ���ȼ��ȽϽ��Ϊ��ֹ���̴���
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcessComparePrioRsltAbort(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    PS_MEM_SET(&stEntryMsg, 0, sizeof(TAF_MMA_ENTRY_MSG_STRU));

    /* ����л��棬����������е���Ϣ */
    while (VOS_TRUE ==TAF_MMA_GetNextCachedMsg(&stEntryMsg))
    {
        TAF_MMA_RejectAppRequest(stEntryMsg.ulEventType, (struct MsgCB *)stEntryMsg.aucEntryMsgBuffer);
    }

    /* ���浱ǰ���û����� */
    (VOS_VOID)TAF_MMA_SaveCacheMsgInMsgQueue(ulEventType, (VOS_VOID *) pstMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcessComparePrioRsltReject
 ��������  : ������Ϣ���ȼ��ȽϽ��Ϊ�ܾ����̴���
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcessComparePrioRsltReject(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_RejectAppRequest(ulEventType, pstMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RejectAppRequest
 ��������  : �ܾ���ǰ�û�����
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID TAF_MMA_RejectAppRequest(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;

    pstRcvMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
            /* ����attach confirm�ظ��ӿں��� */
            TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            /* ����detach confirm�ظ��ӿں��� */
            TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
            /* ����SYS CFG SET�ظ��ӿں��� */
            TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                    TAF_ERR_ERROR);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):
            TAF_MMA_SndPlmnAutoReselCnf(&(((TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;
#if (FEATURE_ON == FEATURE_CSG)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ):
            /* �ظ�csg�б�������� */
            TAF_MMA_ReportCsgListError(&(((TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)(pstRcvMsg))->stCtrl), TAF_ERR_PHONE_MSG_UNMATCH);
            break;
#endif

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
            {
                pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                                                     sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
                if (VOS_NULL_PTR != pstPlmnListCnfPara)
                {
                    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

                    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
                    pstPlmnListCnfPara->enPhoneError = TAF_ERR_PHONE_MSG_UNMATCH;

                    TAF_MMA_SndPlmnListCnf(&(((TAF_MMA_PLMN_LIST_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                           pstPlmnListCnfPara);

                    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);
                }
            }
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
            TAF_MMA_SndPlmnSpecialSelCnf(&(((TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):
             TAF_MMA_SndPhoneModeSetCnf(&(((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        ((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stPhoneModePara.PhMode,
                                        TAF_MMA_APP_OPER_RESULT_FAILURE,
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ):
             /* ���ϲ�ظ�ʧ�� */
            TAF_MMA_SndImsSwitchSetCnf(&(((TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_MMA_APP_OPER_RESULT_FAILURE,
                                         TAF_ERR_UNSPECIFIED_ERROR);
             break;
#endif

        default:
            /* unknown message, ignore it */
            break;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_FindMsgPrioCompareFun
 ��������  : ������Ϣ�ȽϺ���
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
             ulFsmEntryEventType    :״̬���������Ϣ
             enFsmId                :״̬����ID
 �������  : ��
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

TAF_MMA_MSG_COMPARE_FUNC  TAF_MMA_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astMmaMsgCompareTbl)/sizeof(TAF_MMA_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astMmaMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmaMsgCompareTbl[i];
            break;
        }
    }

    /* δ���ҵ���״̬���ıȽϺ�����,ֱ�ӷ��ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* ���Ҳ�ͬ�¼��ıȽϺ��� */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* δ�ҵ�������ֱ�ӷ��ؿ�ָ�� */
    return VOS_NULL_PTR;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_GetMsgComparePrio
 ��������  : ��ȡ��Ϣ���ȼ��ȽϺ�Ľ��
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
 �������  : pulAbortType:����ֵΪ���ʱ,���صĴ������
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_COMPARE_FUNC                    pfCompareFunc;
    TAF_MMA_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  ��ȡ��ǰ״̬����ID */
    enCurrFsmId         = TAF_MMA_GetCurrFsmId();

    if (TAF_MMA_FSM_BUTT <= enCurrFsmId)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "ERROR:FsmId Error");
    }

    /*  ��ȡ�ȽϺ��� TAF_MMA_FindMsgPrioCompareFun() */
    pfCompareFunc       = TAF_MMA_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* δ�ҵ�������,��Ĭ����Ϣ���� */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = TAF_MMA_ABORT_BUTT;
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ñȽϺ���,�������ȼ��ʹ������ */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg
 ��������  : ��MMA�յ�APP��ims switch������SYS CFG״̬�������ȼ����бȽ�
 �������  : ulEventType : ��Ϣ����
             pstMsg      : ��Ϣ����
 �������  : penAbortType: �������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

