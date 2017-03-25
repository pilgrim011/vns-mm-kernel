/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : PPpp_task.c
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : PPP D/E/F����������
  �����б�   :
*
*       1.                PPP_A11TaskProc
*       2.                PPP_AAATaskProc
*       3.                PPP_COMPRESSTaskProc
*       4.                PPP_FATaskProc
*       5.                PPP_GTPCTaskProc
*       6.                PPP_L2TPTaskProc
*       7.                PPP_LAPTaskProc
*       8.                PPP_NEGOTaskProc
*       9.                PPP_PcrfcTaskProc
*       10.               PPP_TaskEntry
*       11.               PPP_TIMERTaskProc
*

  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_TASK_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPP_QueueInit
 ��������  : ��������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_QueueInit(  )
{
    VOS_UINT32                      ulResult = VOS_OK;
    PTM_QUEUE_INFO_S                stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = PPP_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulPPPTaskId;


    g_ulPppTaskTrace = 10;

    /* ������ʱ����Ϣ���� */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN * 4;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "3PTM");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulPppTimeQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPP_QueueInit: Create TIMER Que error 0x%x!", ulResult);
        return VOS_ERR;
    }

    /* �����ڲ����� */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_INNER;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN;
    stQueInfo.ulEvent       = PPP_INNERMSG_NOTIFY_PPP_EVENTBIT;
    VOS_sprintf(stQueInfo.szQueName, "PPPIN");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulPppInnerMsgQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG2("PTM_CreateQueue %s fail, return = 0x%x", stQueInfo.szQueName, ulResult);
        return ulResult;
    }

    /*================����ΪPPP���յĹ������====================*/
    /* ��������LAP����Ϣ���� */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_LAP;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN;
    stQueInfo.ulEvent       = PPP_LAP_NOTIFY_PPP_EVENTBIT;
    VOS_sprintf(stQueInfo.szQueName, "SC%02lu_PPP_QUE", PPP_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (VOS_UINT32 *)&g_pstPppLAPNotifyQueID);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

     /* ��������DDU����Ϣ���� */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = PPP_MSG_TYPE_DDU;
    stQueInfo.ulQueLen      = PPP_MAXQUELEN ;
    stQueInfo.ulEvent       = 0;                /* ����д�¼� */
    VOS_sprintf(stQueInfo.szQueName, "S%luPP", PPP_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (VOS_UINT32 *)&g_pstPppNegoQueID);
    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_QueueInit: Create DDU Que error 0x%x!",ulResult);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_TaskInit
 ��������  : D/E��PPP�����ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_TaskInit(  )
{
    VOS_UINT32                      ulRet = VOS_OK;

    /* ��ʼ��������� */
    g_stPppCompInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_PPPT);
    g_stPppCompInfo.ullSelfSgId  = PSM_Inf_GetSelfSGID();
    g_stPppCompInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(PPP_SELF_CSI);
    g_stPppCompInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(PPP_SELF_CSI);
    g_stPppCompInfo.ulHandle     = MID_PPPC;



    /* ��һ�׶γ�ʼ�� */
    /*lint -e746*/
    ulRet = PPP_CompInit1();
    /*lint +e746*/
    if (VOS_OK != ulRet)
    {

        PPPC_WARNING_LOG1("[ppp]PPP_TaskInit: PPP_CompInit1 error %lu!",ulRet);
        return VOS_ERR;
    }

    /*Add by chenmin00265046, ά����Ϣ��ʼ��*/
    PPP_ClearCnt();

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_TaskEntry
 ��������  : D/E��PPPģ�����������
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_TaskEntry(VOID)
{
    VOS_UINT32                  ulRet = VOS_OK;


    /* ��������*/
    ulRet = PPP_QueueInit();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_QueueInit error %lu!",ulRet);
        return VOS_ERR;
    }

    /* �ڶ��׶γ�ʼ�� */
    /*lint -e746*/
    ulRet = PPP_CompInit2();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_CompInit2 error %lu!",ulRet);
        return VOS_ERR;
    }

    /* �����׶γ�ʼ�� */
    ulRet = PPP_CompInit3();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("[ppp]PPP_TaskEntry: PPP_CompInit3 error %lu!",ulRet);
        return VOS_ERR;
    }

    PPP_SubBoardInit();




    /* ������ */
    /* ����coverity���������������������� */
#if 0
    // coverity[no_escape][loop_top][loop_bottom]
    for(;;)
    {
        ulEvRcv = 0x0;

        /* ���¼���Ϣ */
        if (VOS_OK == VOS_Ev_Read(VOS_TIMER_EVENT
                                   | PPP_AAA_EVENTBIT
                                   | PPP_COMPRESS_MSG_EVENTBIT
                                   | PPP_A11_NOTIFY_PPP_EVENTBIT
                                   | PPP_LAP_NOTIFY_PPP_EVENTBIT
                                   | PPP_L2TP_NOTIFY_PPP_EVENTBIT
                                   | DIAM_AUTH_PPP_EVENT
                                   | PPP_INNERMSG_NOTIFY_PPP_EVENTBIT,
                                   &ulEvRcv,
                                   (VOS_EV_ANY | VOS_NO_WAIT), 0))/*����¼�λ*/
        {

            /* ����ʱ���¼� */
            if (ulEvRcv & VOS_TIMER_EVENT)
            {
                PPP_TIMERTaskProc();
            }

            /* ����A11�¼� */
            if (ulEvRcv & PPP_A11_NOTIFY_PPP_EVENTBIT)
            {
                PPP_A11TaskProc();
            }
             ///TODO:luofang����ѹ���¼�

            /* ����AAA�¼� */
            if (ulEvRcv & PPP_AAA_EVENTBIT)
            {
                PPP_AAATaskProc();
            }

            /* ����DIAM AAA�¼� */
            if (ulEvRcv & DIAM_AUTH_PPP_EVENT)
            {
                PPP_DiamAAATaskProc();
            }

            /* ����LAP�¼� */
            if (ulEvRcv & PPP_LAP_NOTIFY_PPP_EVENTBIT)
            {
                PPP_LAPTaskProc();
            }

             /* ����L2TP�¼� */
            if (ulEvRcv & PPP_L2TP_NOTIFY_PPP_EVENTBIT)
            {
                PPP_L2TPTaskProc();
            }

            if (ulEvRcv & PPP_INNERMSG_NOTIFY_PPP_EVENTBIT)
            {
               /* �����ڲ���Ϣ */
                PPP_InnerMsgProc();
            }
        }

        /* ����Э���¼� */
        PPP_NEGOTaskProc();
        /*lint +e746*/
        VOS_T_Delay(10); /* �ͷ�CPU */
    }
#endif
    return VOS_OK;
}
#if 0
/*****************************************************************************
 �� �� ��  : PPP_InnerMsgProc
 ��������  : sd�����ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : y00225787
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_InnerMsgProc()
{
    VOS_UINT32 aulMsg[4] = {0};
    UCHAR *pucMsg = VOS_NULL_PTR;
    VOS_UINT32 ulFlowControl = 0;

    while (VOS_OK == VOS_Que_Read(g_ulPppInnerMsgQueID, aulMsg, VOS_NO_WAIT, 0))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1366);
        pucMsg = (UCHAR*)aulMsg[1];

        if ( VOS_NULL_PTR != pucMsg )
        {
            /*�ַ��ڲ���Ϣ*/
            PPP_DispatchInnerMsg(pucMsg);
            PGP_RTDistributeFreeMsg(pucMsg);
        }

        PPP_DBG_OK_CNT(PPP_PHOK_1367);

        ulFlowControl++;
        if(PPP_FLOWCONTROL_MAX < ulFlowControl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_INNERMSG_NOTIFY_PPP_EVENTBIT);
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_DispatchInnerMsg
 ��������  : ppp�ַ��ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : y00225787
    �޸�����   : �����ɺ���

*****************************************************************************/

VOID PPP_DispatchInnerMsg(UCHAR *pucMsg)
{
    if ( VOS_NULL_PTR == pucMsg )
    {
        return;
    }
#if 0
    switch (RTD_GET_MSGCODE(pucMsg))
    {
        case PPP_INNER_MSG_CODE_RENEGO :
             PPP_InnerRengeoMsgProc(pucMsg);
             break;

        default:
            break;
    }
#endif
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_InnerRengeoMsgProc
 ��������  : ppp�����ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : y00225787
    �޸�����   : �����ɺ���

*****************************************************************************/

VOID PPP_InnerRengeoMsgProc(UCHAR *pucMsg)
{
    VOS_UINT32  ulSelfCpuId = DVM_SELF_CPUID;

    PPP_DBG_OK_CNT(PPP_PHOK_1368);
    if ( VOS_NULL_PTR == pucMsg )
    {
        return;
    }

    if ((PPP_CPU_ONLINE == g_ulPppSubBordStat[0])
        && (PPP_CPU_ONLINE == g_ulPppSubBordStat[1]))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
            "\r\n [ppp]PPP_ReNegoCompressTask: Subboard is restored! SelfCpuId = [%d]"
            ,ulSelfCpuId);
         g_ulReNegoTaskId = 0;
         return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1369);
    PPP_ReNegoCompressTask(pucMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_TIMERTaskProc
 ��������  : PPP�Ĵ���TIMER�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_TIMERTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر��� */
    VOS_UINT32 ulRetMsg[4] = {0};

    while (VOS_OK == VOS_Que_Read(g_ulPppTimeQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1370);
        if (ulRetMsg[2] != VOS_NULL_PTR)
        {
            ((VOID (*) (VOID *))(ulRetMsg[2]))((VOID*)(ulRetMsg[3]));
        }

        if (++ulFlowControl >= g_ulPPPTimerFlowctrl)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1371);
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, VOS_TIMER_EVENT);
            break;
        }
    }
    return;
}


/*****************************************************************************
 �� �� ��  : PPP_A11TaskProc
 ��������  : PPP�Ĵ���A11�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_A11TaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر���  */
    VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulRetMsg[4] = {0};

    while (VOS_OK == VOS_Que_Read(g_ulPppA11NotifyQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
       pMsg = (VOID *)ulRetMsg[1];
       if (VOS_NULL_PTR == pMsg)
       {
           VOS_DBGASSERT(0);
           continue;
       }

       PPP_A11MsgProc(pMsg);
       PGP_RTDistributeFreeMsg(pMsg);

       if (++ulFlowControl >= g_ulPPPA11Flowctrl)
       {
           (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_A11_NOTIFY_PPP_EVENTBIT);
           break;
       }
    }
   return;
}

/*****************************************************************************
 �� �� ��  : PPP_DiamAAATaskProc
 ��������  : PPP�Ĵ���diam AAA�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_DiamAAATaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر��� */
    VOS_UINT32 ulRetMsg[4] = {0};
    VOID *pMsg = VOS_NULL_PTR;

    while (VOS_OK == VOS_Que_Read(g_ulPppDiamAaaQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        pMsg = (DIAM_AUTHRSP_S *)ulRetMsg[1];
        PPP_DBG_OK_CNT(PPP_PHOK_1372);

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        PPP_EAP_ReceiveDiamAAAResult((DIAM_AUTHRSP_S *)pMsg);
#endif
        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= g_ulPPPAAAFlowctrl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, DIAM_AUTH_PPP_EVENT);
            break;
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_AAATaskProc
 ��������  : PPP�Ĵ���AAA�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_AAATaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر��� */
    VOS_UINT32 ulRetMsg[4] = {0};
    VOID *pMsg = VOS_NULL_PTR;

    while (VOS_OK == VOS_Que_Read(g_ulPppAaaQueID, ulRetMsg, VOS_NO_WAIT, 0))
    {
        pMsg = (AAA_AUTHRSP_S *)ulRetMsg[1];
        PPP_DBG_OK_CNT(PPP_PHOK_1373);

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        PPP_AAAMsgProc((AAA_AUTHRSP_S *)pMsg);
        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= g_ulPPPAAAFlowctrl)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_AAA_EVENTBIT);
            break;
        }
    }
    return;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : PPP_NEGOTaskProc
 ��������  : PPP�Ĵ���NEGO�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_NEGOTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر��� */
    VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgCode = 0;
    VOS_UINT32 ulRet = VOS_OK;

     while (VOS_OK == VOS_MCReadQue(g_pstPppNegoQueID,
                                    &pMsg,
                                    &ulMsgCode,
                                    VOS_MCQUEUE_NO_WAIT,
                                    0))
     {
         if (VOS_NULL_PTR == pMsg)
         {
             VOS_DBGASSERT(0);
             continue;
         }

         PPP_DBG_OK_CNT(PPP_PHOK_1374);
         ulRet = PPP_NegoMsgProc((UCHAR *)pMsg);
         if (VOS_OK != ulRet)
         {
             PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_NegoMsgProc error: %lu!",ulRet);
             continue;
         }

         if (++ulFlowControl >= g_ulPPPNegoFlowctrl)
         {
             (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_NEGO_EVENTBIT);
             break;
         }
     }
     return;
}
#endif

#if 0
/*****************************************************************************
 �� �� ��  : PPP_L2TPTaskProc
 ��������  : PPP�Ĵ���L2TP�¼��ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_L2TPTaskProc()
{
    VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر���  */
    VOS_VOID *pMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgCode = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_L2TPTaskProc: enter!");

    while (VOS_OK == VOS_MCReadQue(g_pstL2TPPppNotifyQueID,
                                   &pMsg,
                                   &ulMsgCode,
                                   VOS_MCQUEUE_NO_WAIT,
                                   0))
    {

        if (VOS_NULL_PTR == pMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        PPP_DBG_OK_CNT(PPP_PHOK_1375);
        /* PPP_L2tpMsgProc(pMsg, RTD_GET_MSGCODE(pMsg)); */

        PGP_RTDistributeFreeMsg(pMsg);

        if (++ulFlowControl >= 25)
        {
            (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_L2TP_NOTIFY_PPP_EVENTBIT);
            break;
        }
    }
    return;
}
#endif
#if 0
/*****************************************************************************
�� �� ��  : PPP_LAPTaskProc
��������  : PPP�Ĵ���LAP�¼��ĺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��9��24��
��    ��   : �淽
�޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_LAPTaskProc()
{
      VOS_UINT32 ulFlowControl = 0; /* ���岢��ʼ�����ر���  */
      VOID *pMsg = VOS_NULL_PTR;
      VOS_UINT32 ulMsgCode = 0;

      while (VOS_OK == VOS_MCReadQue(g_pstPppLAPNotifyQueID,
                                   &pMsg,
                                   &ulMsgCode,
                                   VOS_MCQUEUE_NO_WAIT,
                                   0))
      {
          if (VOS_NULL_PTR == pMsg)
          {
              VOS_DBGASSERT(0);
              continue;
          }

          PPP_DBG_OK_CNT(PPP_PHOK_1376);

          /* (VOID)PDN_LapMsgProc((USM_LAP2_MSG_S *)pMsg); */

          PGP_RTDistributeFreeMsg(pMsg);

          if (++ulFlowControl >= g_ulPPPLapFlowctrl)
          {
              (VOID)VOS_Ev_Write(g_ulPPPTaskId, PPP_LAP_NOTIFY_PPP_EVENTBIT);
              break;
          }
      }

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : PPP_SubBoardInit
 ��������  : �ӿ�״̬�����ʼ��
 �������  :
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_SubBoardInit(VOS_VOID)
{

    return;
}

#if 0
/*****************************************************************************
 �� �� ��  : PPP_ReNegoCompressTask
 ��������  : ������ѹ���û�������Э��
 �������  : ��
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  PPP_ReNegoCompressTask(UCHAR *pucMsg)
{
    VOS_UINT32 ulFlowCtr1 = 0;
    VOS_UINT32 ulFlowCtr2 = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    PPPRENOGOINFO* pstPppRenegoInfo = VOS_NULL_PTR;
    PPP_INNER_MSG_S *pstPppInnerMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMemSize = 0;
    VOS_UINT32 ulRenegoIndex = 0;

    pstPppInnerMsg = (PPP_INNER_MSG_S *)pucMsg;
    ulRenegoIndex = pstPppInnerMsg->ulCurRenegoIndex ;

    for(; ulRenegoIndex <= PPP_MAX_USER_NUM; ulRenegoIndex++ )
    {
        /* �������� */
        ulFlowCtr1++;
        if ((1000 <= ulFlowCtr1) || (3 <= ulFlowCtr2))
        {
            ulFlowCtr1 = 0;
            ulFlowCtr2 = 0;
            PPP_DBG_OK_CNT(PPP_PHOK_1377);
            PPP_SendInnerMsg(ulRenegoIndex);
            break;
        }

        pstPppInfo = &g_astPppPool[ulRenegoIndex];
        if(PPP_CB_STATE_USED != pstPppInfo->usState)
        {
            continue;
        }

        /* �����ѹ���û�����ѹ���ӿ�״̬����λ���������Э�� */
        if (((MAX_DMPU_NUM > pstPppInfo->ucDmpuId)
                && (PPP_CPU_ONLINE != g_ulPppSubBordStat[pstPppInfo->ucDmpuId]))
            &&((VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
                || ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
                &&(((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stGotOptions.neg_vj))))
        {
                pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
                pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1378);

                /* BEGIN: M by h50774 for DTS2010090901800,���Windows��Bug����֧��VJѹ����Э��Ϊ��ѹ��, 2010/9/13 */
                /*lint -e746*/
                if ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
                    &&(((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stGotOptions.neg_vj)
                    && (VOS_OK != PPP_CheckVjLimit()))
                /*lint +e746*/
                {
                     PPP_ERROR_COUNTER(PPP_ERROR_COUNTER024);
                     PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CMPRESS_RENEGO_FAIL);
                     PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

                     PPP_DBG_ERR_CNT(PPP_PHERR_668);
                     ulFlowCtr2++;
                     continue;
                }

                //(VOID)PPP_NodeDelete(ulRenegoIndex);
                (VOID)PPP_NodeAdd(ulRenegoIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

                pstPppInfo->bReNego = 1;
                if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                {

                    ulMemSize = sizeof(PPPRENOGOINFO);
                    pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(ulMemSize);

                }

                if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                {
                     PPP_DBG_OK_CNT(PPP_PHOK_1379);
                     continue;
                }

                pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
                PPP_MemSet((VOID*)pstPppRenegoInfo, 0, sizeof(PPPRENOGOINFO));
                if (VOS_NULL_PTR != pstIpcpInfo )
                {
                    pstPppRenegoInfo->ucIpcpFlag = 1;
                    (VOID)VOS_MemCpy((VOID*)&(pstPppRenegoInfo->stIpcpOptions),
                                (VOID*)&(pstIpcpInfo->stGotOptions),
                                sizeof(PPP_IPCP_OPTION_S));
                }

                if ((VOS_NULL_PTR != pstCcpInfo) && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
                {
                    pstPppRenegoInfo->ucCcpFlag = 1;
                    (VOID)VOS_MemCpy((VOID*)&(pstPppRenegoInfo->stCcpOptions),
                                (VOID*)&(pstCcpInfo->stGotOptions),
                                sizeof(PPP_CCP_options_S));
                }

                PPP_INNER_COUNTER(PPP_INNER_COUTNER_019);
                PPP_Core_ReceiveEventFromShell(pstPppInfo, PPPISLRENEGO, VOS_NULL_PTR);

                /* ���ӿ���DPEID��Ϊ��Ч��������Э��ʱ����ѡ */
                pstPppInfo->ucDmpuId = 0xFF;
                pstPppInfo->ucDpeId = 0xFF;

                ulFlowCtr2++;
        }
    }

    g_ulReNegoTaskId = 0;
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : PPP_SubBoardDown
 ��������  : �ӿ�״̬���ϴ���
 �������  :
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_SubBoardDown(VOS_VOID)
{
    if (CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        return;
    }

    /* ��ʱˢ��ѹ����Դ��Ϣ */
    /*lint -e746*/
    PPP_CompRescSyn();
    /*lint +e746*/

    if (0 != g_ulReNegoTaskId)
    {
        PPPC_INFO_LOG1("[ppp]PPP_SubBoardDown: task is already running, g_ulReNegoTaskId = [%d]", g_ulReNegoTaskId);
        return;
    }

    PPP_SendInnerMsg(1);

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
