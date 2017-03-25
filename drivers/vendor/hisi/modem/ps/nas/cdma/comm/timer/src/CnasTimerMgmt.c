/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasTimerMgmt.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��28��
  ��������   : NAS CDMA��ʱ�������ܺ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��28��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CnasTimerMgmt.h"
#include "CnasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_TIMER_MGMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CNAS_TIMER_CTX_STRU                     g_astCnasTimerCtx[CNAS_MAX_TIMER_RUNNING_NUM];

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_GetTimerCtxAddr
 ��������  : ��ȡtimer�������׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����timer�������׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetTimerCtxAddr(VOS_VOID)
{
    return (&g_astCnasTimerCtx[0]);
}

/*****************************************************************************
 �� �� ��  : CNAS_InitTimerCtx
 ��������  : timer ������table��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��05��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_InitTimerCtx(VOS_VOID)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;

        pstTimerCtx++;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_GetAFreeTimerCtx
 ��������  : ��ȡһ�����е�CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����timer�����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetAFreeTimerCtx(VOS_VOID)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((VOS_NULL_PTR           == pstTimerCtx->pTimerHandle)
         && (CNAS_TIMER_STATUS_STOP == pstTimerCtx->enTimerStatus))
        {
            /* �ҵ�һ�����е�timer CTX, ����ѭ�� */
            return pstTimerCtx;
        }

        pstTimerCtx++;
    }

    /* û���ҵ������ؿ�ָ�� */
    return (VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : CNAS_GetSpecifiedTimerCtx
 ��������  : ��ȡָ��timer��CTX, ���ָ��timer ID��CTX�����ҵ������ص�ǰCTX��ַ��
             ���򷵻�ΪNULL
 �������  : ulPid     -- ����timer��PID����
             ulTimerId -- timer��ʶ
             ulPara    -- ��ʱ��������ʶ
 �������  : ��
 �� �� ֵ  : ����ָ��timer�����ĵ�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_TIMER_CTX_STRU* CNAS_GetSpecifiedTimerCtx(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulPara
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    /* ����timer ID�Ƿ���timer ctx���� */
    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((ulPid                     == pstTimerCtx->ulPid)
         && (ulTimerId                 == pstTimerCtx->ulTimerId)
         && (ulPara                    == pstTimerCtx->ulParam)
         && (CNAS_TIMER_STATUS_RUNNING == pstTimerCtx->enTimerStatus))
        {
            /* ���ҳɹ������ص�ǰ��ctx��ַ */
            return pstTimerCtx;
        }

        pstTimerCtx++;
    }

    /* ����ʧ�ܣ����ؿ�ָ�� */

    return (VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : CNAS_StartTimer
 ��������  : CNAS��ʱ������
 �������  : ulPid        -- ����timer��PIDģ��
             pstTimerInfo -- timer��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

 1.��    ��   : 2015��07��25��
   ��    ��   : y00245242
   �޸�����   : ����ʱ��Ϊ0�ı���
*****************************************************************************/
VOS_VOID CNAS_StartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* ָ���� */
    if ((VOS_NULL_PTR == pstTimerInfo)
     || (0            == pstTimerInfo->ulTimerLen))
    {
        /* ��ӡ������Ϣ */
        CNAS_ERROR_LOG(ulPid, "CNAS_StartTimer: pstTimerInfo is NULL or PARAM is invalid!");

        return;
    }

    /* ��鵱ǰ�Ķ�ʱ���Ƿ���CTX���� */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, pstTimerInfo->ulTimerId, pstTimerInfo->ulParam);


    if (VOS_NULL_PTR != pstTimerCtx)
    {
        /* ��ӡ������Ϣ, ��ǰtimer������ */
        CNAS_ERROR_LOG1(ulPid, "CNAS_StartTimer: ulTimerId is already running!", pstTimerInfo->ulTimerId);

        return;
    }

    /* ��ȡһ�����еĶ�ʱ��CTX */
    pstTimerCtx = CNAS_GetAFreeTimerCtx();

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* timer CTX����������ӡ������Ϣ�� */
        CNAS_ERROR_LOG(ulPid, "CNAS_StartTimer: timer ctx table is full!");

        return;
    }

    if (VOS_OK != VOS_StartRelTimer(&(pstTimerCtx->pTimerHandle),
                                    ulPid,
                                    pstTimerInfo->ulTimerLen,
                                    pstTimerInfo->ulTimerId,
                                    pstTimerInfo->ulParam,
                                    VOS_RELTIMER_NOLOOP,
                                    pstTimerInfo->ulTimerPrecision))
    {
        /* ������ʱ��ʧ�ܣ���ӡ������Ϣ */
        CNAS_ERROR_LOG1(ulPid, "CNAS_StartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

        return;
    }

    /* ���涨ʱ������Ϣ���ö�ʱ��CTX�� */
    pstTimerCtx->ulTimerId = pstTimerInfo->ulTimerId;
    pstTimerCtx->ulPid     = ulPid;
    pstTimerCtx->ulParam   = pstTimerInfo->ulParam;

    /* ���ö�ʱ��״̬Ϊrunning״̬ */
    pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_RUNNING;

    /* ���timer������Ϣ */
    stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
    stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
    stMntnTimerInfo.ulTimerLen = pstTimerInfo->ulTimerLen;
    stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_START;
    CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_RestartTimer
 ��������  : ������ʱ��������ʱ����������ʱ����ֹͣ�ö�ʱ������������ʱ�������
             ��ʱ��δ���У�ֱ�������ö�ʱ��
 �������  : ulPid        -- ����timer��PIDģ��
             pstTimerInfo -- timer��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_RestartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* ָ���� */
    if (VOS_NULL_PTR == pstTimerInfo)
    {
        /* ��ӡ������Ϣ */
        CNAS_ERROR_LOG(ulPid, "CNAS_RestartTimer: pstTimerInfo is NULL!");

        return;
    }

    /* ��鵱ǰ�Ķ�ʱ���Ƿ���CTX���� */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, pstTimerInfo->ulTimerId, pstTimerInfo->ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* CTX�����޵�ǰ��ʱ����¼����ȡһ�����еĶ�ʱ��CTX */
        pstTimerCtx = CNAS_GetAFreeTimerCtx();

        if (VOS_NULL_PTR == pstTimerCtx)
        {
            /* timer CTX����������ӡ������Ϣ�� */
            CNAS_ERROR_LOG(ulPid, "CNAS_RestartTimer: timer ctx table is full!");

            return;
        }
    }

    if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
    {
        /* ��ǰtimer�������У���ֹͣ�� */
        if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
        {
            /* ֹͣ��ʱ��ʧ�ܣ���ӡ������Ϣ */
            CNAS_ERROR_LOG1(ulPid, "CNAS_RestartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

            return;
        }

        /* ���timer CTX��Ϣ */
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;

        /* ���timerֹͣ��Ϣ */
        stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
        stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
        stMntnTimerInfo.ulTimerLen = 0;
        stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
        CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
    }

    /* ������ʱ�� */
    if (VOS_OK != VOS_StartRelTimer(&(pstTimerCtx->pTimerHandle),
                                    ulPid,
                                    pstTimerInfo->ulTimerLen,
                                    pstTimerInfo->ulTimerId,
                                    pstTimerInfo->ulParam,
                                    VOS_RELTIMER_NOLOOP,
                                    pstTimerInfo->ulTimerPrecision))
    {
        /* ������ʱ��ʧ�ܣ���ӡ������Ϣ */
        CNAS_ERROR_LOG1(ulPid, "CNAS_RestartTimer: start timer is failure!", pstTimerInfo->ulTimerId);

        return;
    }

    /* ���涨ʱ������Ϣ���ö�ʱ��CTX�� */
    pstTimerCtx->ulTimerId = pstTimerInfo->ulTimerId;
    pstTimerCtx->ulPid     = ulPid;
    pstTimerCtx->ulParam   = pstTimerInfo->ulParam;

    /* ���ö�ʱ��״̬Ϊrunning״̬ */
    pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_RUNNING;

    /* ���timer������Ϣ */
    stMntnTimerInfo.ulParam    = pstTimerInfo->ulParam;
    stMntnTimerInfo.ulTimerId  = pstTimerInfo->ulTimerId;
    stMntnTimerInfo.ulTimerLen = pstTimerInfo->ulTimerLen;
    stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_START;
    CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_StopTimer
 ��������  : CNASֹͣ��ʱ��
 �������  : ulPid        -- ����timer��PIDģ��
             pstTimerInfo -- timer��Ϣָ��
             ulPara       -- ��ʱ��������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_StopTimer(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    /* ��鵱ǰ�Ķ�ʱ���Ƿ���CTX���� */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR != pstTimerCtx)
    {
        if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
        {
            /* ��ǰtimer�������У���ֹͣ�� */
            if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
            {
                /* ֹͣ��ʱ��ʧ�ܣ���ӡ������Ϣ */
                CNAS_ERROR_LOG1(ulPid, "CNAS_StopTimer: start timer is failure!", ulTimerId);

                return;
            }


        }

        /* ���timerֹͣ��Ϣ */
        stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
        stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
        stMntnTimerInfo.ulTimerLen = 0;
        stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
        CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);

        /* ���timer���е�CTX��Ϣ */
        pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
        pstTimerCtx->ulParam       = 0;
        pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
        pstTimerCtx->ulTimerId     = 0;
        pstTimerCtx->ulPid         = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_StopAllTimerWithSpecifiedPid
 ��������  : ָֹͣ��PID�����ж�ʱ��
 �������  : ulPid        -- ����timer��PIDģ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_StopAllTimerWithSpecifiedPid(
    VOS_UINT32                          ulPid
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((CNAS_TIMER_STATUS_RUNNING == pstTimerCtx->enTimerStatus)
         && (ulPid                     == pstTimerCtx->ulPid))
        {
            /* ����ʱ���ľ��Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
            if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
            {
                /* ��ǰtimer�������У���ֹͣ�� */
                if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
                {
                    /* ֹͣ��ʱ��ʧ�ܣ���ӡ������Ϣ */
                    CNAS_ERROR_LOG1(ulPid, "CNAS_StopTimer: start timer is failure!", pstTimerCtx->ulTimerId);

                    pstTimerCtx++;

                    continue;
                }

                /* ���timerֹͣ��Ϣ */
                stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
                stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
                stMntnTimerInfo.ulTimerLen = 0;
                stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
                CNAS_MNTN_TraceTimerMsg(ulPid, &stMntnTimerInfo);
            }

            /* ���timer���е�CTX��Ϣ */
            pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
            pstTimerCtx->ulParam       = 0;
            pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
            pstTimerCtx->ulTimerId     = 0;
            pstTimerCtx->ulPid         = 0;
        }

        pstTimerCtx++;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_GetSpecifiedTimerStatus
 ��������  : CNASֹͣ��ʱ��
 �������  : ulPid     -- ����timer��PIDģ��
             ucTimerId -- timer��ʶ
 �������  : ��
 �� �� ֵ  : CNAS_TIMER_STATUS_STOP    -- timer��ֹͣ״̬
             CNAS_TIMER_STATUS_RUNNING -- timer������״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_TIMER_STATUS_ENUM_UINT8 CNAS_GetSpecifiedTimerStatus(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;

    /* ��鵱ǰ�Ķ�ʱ���Ƿ���CTX���� */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        return CNAS_TIMER_STATUS_STOP;
    }

    return pstTimerCtx->enTimerStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_GetSpecifiedTimerRemainLen
 ��������  : ��ȡָ����ʱ��ʣ�೤��
 �������  : ulPid     -- ����timer��PIDģ��
             ucTimerId -- timer��ʶ
 �������  : ��
 �� �� ֵ  : ����ʣ�ඨʱ��ʱ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_GetSpecifiedTimerRemainLen(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen  = 0;

    /* ��鵱ǰ�Ķ�ʱ���Ƿ���CTX���� */
    pstTimerCtx = CNAS_GetSpecifiedTimerCtx(ulPid, ulTimerId, ulParam);

    if (VOS_NULL_PTR == pstTimerCtx)
    {
        /* û���ҵ��ö�ʱ�������س���Ϊ0 */
        return ulTimerLen;
    }

    /* �����ʱ�����Ϊ�գ�������ʱ����ͣ���Ѿ����� */
    if (VOS_NULL_PTR == pstTimerCtx->pTimerHandle)
    {
        /* ��ʱ���Ѿ�ֹͣ��ʱ�����ض�ʱ������Ϊ0 */
        return ulTimerLen;
    }

    /* ��ȡ��ʱ������ */
    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerCtx->pTimerHandle), &ulTimerLen))
    {
        /* ��ȡ��ʱ��ʣ��ʱ��ʧ�ܣ���ӡ������Ϣ */
        CNAS_ERROR_LOG1(ulPid, "CNAS_GetSpecifiedTimerRemainLen: get remained length is failure!",
                        pstTimerCtx->ulTimerId);

        /* ��ȡʧ�ܣ�����Ϊ0 */
        return 0;
    }

    /* ת��timerʱ��Ϊ���� */
    return (ulTimerLen * CNAS_TIMER_TICK);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



