/******************************************************************************

                  ��Ȩ���� (C), 2013-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaSndUphy.c
  �� �� ��   : ����
  ��    ��   : l00198894
  ��������   : 2015��6��15��
  ����޸�   :
  ��������   : MMAģ�鷢�͵�UPHY����Ϣ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��15��
    ��    ��   : l00198894
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafMmaSndUphy.h"
#include "MmaUphyInterface.h"

#include "PsTypeDef.h"
#include "TafLog.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_UPHY_C

/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndUphyPowerOnReq
 ��������  : MMA֪ͨUPHY��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndUphyPowerOnReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_ON_REQ_STRU         *pstPowerOn = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_ON_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerOn  = (MMA_UPHY_POWER_ON_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOn)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerOn + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerOn->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOn->usMsgID                 = ID_MMA_UPHY_POWER_ON_REQ;
    pstPowerOn->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOn))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Snd Msg Failed!");
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndUphyPowerOffReq
 ��������  : MMA֪ͨUPHY�ػ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndUphyPowerOffReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_OFF_REQ_STRU        *pstPowerOff = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerOff  = (MMA_UPHY_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOff)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerOff + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerOff->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOff->usMsgID                 = ID_MMA_UPHY_POWER_OFF_REQ;
    pstPowerOff->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOff))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Snd Msg Failed!");
    }

    return;

}





#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif







