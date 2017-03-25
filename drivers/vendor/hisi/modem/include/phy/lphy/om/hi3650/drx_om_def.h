/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drx_om_def.h
  �� �� ��   : ����
  ��    ��   : zhangning(49144)
  ��������   : 2011��11��1��
  ����޸�   :
  ��������   : ����DRX OM��Ҫ�ϱ��Ľṹ��,���ļ����ջύ����HiStudioʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��11��1��
    ��    ��   : zhangning(49144)
    �޸�����   : �����ļ�
--------------------------------------------------------------------------------
  2.��    ��   : 2012��07��12��
     ��    ��   : zhangning
     �޸�����   : DTS2012071204333 ����������λ��Ϣ���޸ķ����жϴ�λ��
******************************************************************************/

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __DRX_OM_DEF_H__
#define __DRX_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



typedef enum
{
     LPHY_DEBUG_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DEBUG, 0x1),

}LPHY_DEBUG_DRX_ENUM;

typedef enum
{
     LPHY_ERR_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_ERROR, 0x1),

}LPHY_ERR_DRX_ENUM;



typedef struct
{
    UINT32 ulAllResetCnt;
    UINT32 ulInitPowUpCnt;
    UINT32 ulLpcResetCnt;
    UINT32 ulTaskLoopCnt[16];
    UINT32 ulWakeResumeFunc;
    //UINT32 ulWakeTimer;
    //UINT32 ulSlwwpTimer;
    //UINT32 ulMeasResult;

    UINT32 ulTaskInfo;
    UINT32 ulDrxCurStatus;
    UINT32 epc[4];
    UINT32 eps[4];
	UINT32 ulExcLoc;
	UINT16 usExcID;
    UINT16 usSysFrame;
    UINT16 usSubFrame;
    UINT16 usMeasCalcCnt;
    UINT16 usWakeCnt;
    UINT16 usSleepCnt;
    UINT16 usCdrxSleepCnt;
    UINT16 usCdrxWakeCnt;
    //UINT16 usWakeValid;
    UINT16 usSlaveWakeUpCnt;
    UINT16 usSlaveSleepCnt;
    UINT16 usCdrxOnlyRfSleepCnt;
    UINT16 usCdrxOnlyRfWakeCnt;
    UINT16 usRsvd[6];
}DRX_DEBUG_STRU;

typedef enum
{
    LPHY_REQ_DRX_PRINT_INFO            =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x0),
    LPHY_DT_DRX_STATUS_INFO_REQ        =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x100),
    LPHY_DT_DRX_STATUS_INFO_REQ_DT,

}LPHY_DT_DRX_REQ_ENUM;

typedef enum
{
     LPHY_DT_DRX_STATUS_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_SG, 0x1),
    LPHY_DT_DRX_STATUS_INFO_IND_DT                = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DT, 0x1),

    LPHY_LPC_DVFS_STATUS_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x1),
    LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND              = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x2),
    LPHY_LPC_NOTSLEEP_INFO_IND                    = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x3),
    LPHY_LPC_DSDS_RF_ON_INFO_IND                  = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x4),
    LPHY_LPC_DSDS_RF_OFF_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x5),
    LPHY_LPC_PRESYNC_START_INFO_IND               = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x6),
    LPHY_LPC_PRESYNC_END_INFO_IND                 = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x7),
    LPHY_LPC_TASK_LOG_INFO_IND                    = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x8),
    LPHY_LPC_WAKE_INFO_IND                        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x9),
    LPHY_LPC_ULRF_PAON_INFO_IND                   = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0xa),
    LPHY_LPC_ULRF_PAOFF_INFO_IND                  = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0xb),

    LPHY_LPC_CDRX_STATUS_START_INFO_IND           = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x10),/*Begin,��ֹ��Endǰ�����µĶ���*/
    LPHY_LPC_CDRX_INACTIVE_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x10),        //��ǰ��֡��ʼactive
    LPHY_LPC_CDRX_ACTIVE_START_INFO_IND           = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x11),/*End,��ֹ��Begin������µĶ���*/

    LPHY_LPC_DLRF_IDLE_STATUS_INFO_IND            = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x20), /*Begin,��ֹ��Endǰ�����µĶ���*/
    LPHY_LPC_PCELL_DLRF_IDLE_START_INFO_IND       = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x20),         //PCELL��һ��֡��ʼRF_IDLE
    LPHY_LPC_SCELL_DLRF_IDLE_START_INFO_IND       = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x21),
    LPHY_LPC_SCELL2_DLRF_IDLE_START_INFO_IND      = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x22),
    LPHY_LPC_SCELL3_DLRF_IDLE_START_INFO_IND      = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x23),
    LPHY_LPC_DLRF_ON_STATUS_INFO_IND              = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x24),
    LPHY_LPC_PCELL_DLRF_ON_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x24),         //PCELL��һ��֡��ʼRF_ON
    LPHY_LPC_SCELL_DLRF_ON_START_INFO_IND         = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x25),
    LPHY_LPC_SCELL2_DLRF_ON_START_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x26),
    LPHY_LPC_SCELL3_DLRF_ON_START_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_TRACE, 0x27)  /*End,��ֹ��Begin������µĶ���*/


}LPHY_DT_DRX_IND_ENUM;
typedef UINT32 LPHY_DT_DRX_IND_ENUM_UINT32;

typedef enum
{
    DRX_TIMER_INACTIVE = 0,
    DRX_TIMER_ACTIVE
}DRX_TIMER_STATUS_ENUM;

typedef UINT16 DRX_TIMER_STATUS_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    OM_REQ_ENABLE_ENUM_UINT16   enLpcReport;
} LPHY_DT_DRX_STATUS_INFO_REQ_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enHighPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enLowPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enMidPrintEn;
    UINT16                      usRsv;
} LPHY_REQ_DRX_PRINT_INFO_REQ_STRU;


typedef struct
{
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRttTimer[15];
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRetranTimer[15];
} DRX_DL_HARQ_TIMER_INFO_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    UINT16  usDrxCycleType;
    UINT16  usActiveState;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;
    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    DRX_TIMER_STATUS_ENUM_UINT16  enShortTimer;
    UINT16                        usRsv;
    DRX_DL_HARQ_TIMER_INFO_STRU   astDlHarqTimer[4];

} LPHY_DT_DRX_STATUS_INFO_IND_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT__
{
    UINT16  usSFN;
    UINT16  usSubFn;

    UINT16  usDrxCycleType;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;

    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    UINT16                        usRsv;


} LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT;

typedef struct __LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //����ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //����ʱ��ϵͳ֡��
    UINT16 usReqCnt;                  //�ۼ��������
    UINT8  ucBbpVoltaReq;             //����BBP��ѹ״̬��0Ϊ��ѹ��1Ϊ��ѹ
    UINT8  ucDspVoltaReq;             //����BBE16��ѹ״̬��0Ϊ��ѹ��1Ϊ��ѹ
}LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU;

typedef struct __LPHY_LPC_DVFS_STATUS_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //״̬�仯ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //״̬�仯ʱ��ϵͳ֡��
    UINT8  ucBbpVolta;                //BBP��ѹ״̬��0Ϊ��ѹ��1Ϊ��ѹ
    UINT8  ucDspVolta;                //BBE16��ѹ״̬��0Ϊ��ѹ��1Ϊ��ѹ
    UINT8  ucDspClkStatus;            //BBE16��ʱ��Ƶ��״̬,0,�ͣ�1,��
    UINT8  ucPdtClkStatus;            //BBP PDT��ʱ��Ƶ��״̬,0,�ͣ�1,��
    UINT8  ucPdfClkStatus;            //BBP PDF��ʱ��Ƶ��״̬,0,�ͣ�1,��
    UINT8  ucTdlClkStatus;            //BBP TDL��ʱ��Ƶ��״̬,0,�ͣ�1,��
    UINT16 usRsv;
    UINT32 ulDspClkSelStatus;         //BBE16�ĸ�ģ���Ƶ����״̬
    UINT32 aulLPdtClkSelStatus;       //PDT�ĸ�ģ���Ƶ����״̬
    UINT32 aulLPdfClkSelStatus;       //PDF�ĸ�ģ���Ƶ����״̬
    UINT32 aulLTdlClkSelStatus;       //PDL�ĸ�ģ���Ƶ����״̬
}LPHY_LPC_DVFS_STATUS_INFO_IND_STRU;

typedef struct __LPHY_LPC_DVFS_INFO_STRU__
{
    LPHY_LPC_DVFS_VOLTA_REQ_INFO_IND_STRU stVoltaReqInfo;   //��ѹ����״̬
    LPHY_LPC_DVFS_STATUS_INFO_IND_STRU    stDvfsStatusInfo; //��Ƶ��ѹ�仯״̬
}LPHY_LPC_DVFS_INFO_STRU;

typedef struct __LPHY_LPC_NOTSLEEP_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usCdrxValid;               //��ǰ״̬ΪCDRX
    UINT16 usIdrxValid;               //��ǰ״̬ΪIDLE
    UINT32 ulNotSleepReason;          //���ܽ���˯�ߵ�ԭ��
    UINT32 ulCurrentTaskStatus;       //��ǰ����״̬
}LPHY_LPC_NOTSLEEP_INFO_IND_STRU;

typedef struct __LPHY_LPC_PRESYNC_START_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usPresyncDlCnt;            //Ԥͬ��������֡����
    UINT16 usRsv;                     //�������ֽڶ���
}LPHY_LPC_PRESYNC_START_INFO_IND_STRU;

typedef struct __LPHY_LPC_TASK_LOG_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usCdrxValid;               //��ǰ״̬ΪCDRX
    UINT16 usIdrxValid;               //��ǰ״̬ΪIDLE
    UINT16 usTaskId;                  //��ǰ״̬ΪIDLE
    UINT16 usLogStatus;               //0:log out, 1: log in
}LPHY_LPC_TASK_LOG_INFO_IND_STRU;

/*x00312156, DSP Wake��Ϣ�ϱ��ṹ�壬�����lpc.h�Ľṹ��LPC_DEBUG_CNT_STRU����һ��*/
typedef struct __LPHY_LPC_WAKE_INFO_IND_STRU__
{
    UINT32 ulAllResetCnt;
    UINT32 ulInitPowUpCnt;
    UINT32 ulLpcResetCnt;
    UINT32 ulTaskLoopCnt;
    UINT32 ulLpcSnoozeCnt;
    UINT16 enDspSleepMode;
    UINT16 enLpcIratMode;
    UINT16 enLpcMainState;
    UINT16 enLpcSubState;
    UINT16 usMasterFlag;
    UINT16 usFuncIdxCnt;
    UINT32 ulLastWakeupStartSlice;
    UINT32 ulLastWakeupEndSlice;
    UINT32 ulLastWakeStep;
    UINT32 ulLastWakeStepSlice;
    UINT32 ulLastResumeIpcSlice;
    UINT32 ulLastSleepIpcSlice;
    UINT32 ulSleepIpcCnt;
    UINT32 ulWakeIpcCnt;
    UINT16 enLpcWakeType;
    UINT16 usRsv;
}LPHY_LPC_WAKE_INFO_IND_STRU;  //LPC_DEBUG_CNT_STRU


typedef struct __LPHY_LPC_DRX_OM_TIME_INFO_IND_STRU__
{
    UINT16 usSysFn;                   //�ϱ�ʱ��ϵͳ֡��
    UINT16 usSubFn;                   //�ϱ�ʱ��ϵͳ֡��
}LPHY_LPC_DRX_OM_TIME_INFO_IND_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRX_OM_DEF_H__ */

