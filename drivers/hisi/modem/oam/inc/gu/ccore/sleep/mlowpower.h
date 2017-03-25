/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mlowpower.h
  �� �� ��   : ����
  ��    ��   : s00207770
  ��������   : 2015��8��15��
  ����޸�   :
  ��������   : mlowpower.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��15��
    ��    ��   : s00207770
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MLOWPOWER_H__
#define __MLOWPOWER_H__

#include "vos.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : SLEEP_MODE_INFO_STRU
 �ṹ˵��  : GUģ��ǰϵͳ״̬
*****************************************************************************/
typedef struct
{
    VOS_INT                             (*bbe16_enable_operator)(BSP_DSP_TYPE_E edsptype);
    VOS_INT                             (*bbe16_disable_operator)(BSP_DSP_TYPE_E edsptype);
    VOS_INT                             (*bbe16_pwrup_operator)(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
    VOS_INT                             (*bbe16_pwrdown_operator)(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
    VOS_UINT32                          ulVoteMap;
    VOS_UINT32                          ulState;
    VOS_SPINLOCK                        spinlock;
    VOS_UINT32                          aulEnableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulActualEnableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulEnableSlice[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulDisableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulActualDisableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulDisableSlice[VOS_RATMODE_BUTT];
} MLP_BBE16_OPERATOR_INFO_STRU;

typedef struct
{
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16Load;                        /* BBE16������� */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16RunStop;                     /* BBE16����/ֹͣ */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16SysCtrl;                     /* BBE16�⸴λ/��λ */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16SysClock;                    /* BBE16ʱ�Ӵ�/�ر� */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16RestoreBackup;               /* BBE16����ָ�/���� */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16WaitRestoreBackup;           /* BBE16�ȴ�����ָ�/���� */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16PowerCtrl;                   /* BBE16�ϵ�/�µ� */
} MLP_BBE16_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID mlp_dsp_init(VOS_VOID);
VOS_UINT32 mlp_dsp_load( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_run( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_stop( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_unreset( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_reset( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_enable_clock( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_disable_clock( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_restore( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_backup( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_wait_restore( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_wait_backup( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_pwrup( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId );
VOS_UINT32 mlp_dsp_pwrdown( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId );
VOS_VOID mlp_show_counter(VOS_VOID);





#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mlowpoer.h */
