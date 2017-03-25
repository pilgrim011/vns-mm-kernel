/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicProcMsg.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#if 0

/*****************************************************************************
2 ��������
*****************************************************************************/


/*****************************************************************************
2 ����ʵ��
*****************************************************************************/


/*****************************************************************************
����       : Test_RNIC_RcvAtIpv4PdpActInd
��������   : RNIC_RcvAtIpv4PdpActInd UT������
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtIpv4PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4PdpActInd_001
������������      : modem0,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV4_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ���ű�����ʱ��ֹͣ�����ŶϿ���ʱ��δ����,PDP��������IPV4Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* ֹͣ���ŶϿ���ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* �������ű�����ʱ�� */


	MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* ��ȡ���ű�����ʱ����״̬ */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4PdpActInd_002
������������      : modem1,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV4_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ���ű�����ʱ��ֹͣ�����ŶϿ���ʱ��δ����,PDP��������IPV4Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 72;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* ֹͣ���ŶϿ���ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* �������ű�����ʱ�� */


	MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(ucNewBabId), any());

    MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* ��ȡ���ű�����ʱ����״̬ */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4PdpActInd_003
������������      : ��ǰΪ���貦��ģʽ,��PDP����ɹ���RNIC�յ�AT��ϢID_AT_RNIC_IPV4_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ���ŶϿ���ʱ�����������ű�����ʱ��ֹͣ,PDP��������IPV4Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ���貦��ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* ֹͣ���ŶϿ���ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* �������ű�����ʱ�� */

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* ��ȡ���ű�����ʱ����״̬ */

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4PdpActInd_004
������������      : ���RabIDʧ��
Ԥ�ڽ��          : ���ش���
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ���貦��ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 8;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4PdpActInd_005
������������      : �洢rabid��Ӧ����ʧ��
Ԥ�ڽ��          : ���ش���
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4PdpActInd, Test_RNIC_RcvAtIpv4PdpActInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ���貦��ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    stAtRnicIpv4PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4PdpActInd.enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;
    stAtRnicIpv4PdpActInd.ucRabId         = 4;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvAtIpv6PdpActInd
��������   : RNIC_RcvAtIpv6PdpActInd UT������
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtIpv6PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_001
������������      : modem0,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
    pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
	    .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));


    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);


     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_002
������������      : modem1,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 76;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
		.with(eq(ucNewBabId), any());

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_003
������������      : ��ǰΪ���貦��ģʽ,RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-12
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_004
������������      : ��ǰΪ���貦��ģʽ,��IPV4 PDP����ɹ���RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2012-12-12
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* IPV4 �Ѽ��� */
	VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv6PdpActInd);

	pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_005
������������      : ���RabIDʧ��
Ԥ�ڽ��          : ���ش���
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 12;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

    /* IPV4 �Ѽ��� */
	VOS_MemSet(&stAtRnicIpv4PdpActInd, 0, sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4PdpActInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv6PdpActInd_006
������������      : �洢rabid��Ӧ����ʧ��
Ԥ�ڽ��          : ���ش���
�޸���ʷ   :
1.��   ��  : 2012-12-11
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv6PdpActInd, Test_RNIC_RcvAtIpv6PdpActInd_006)
{
   RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV6_PDP_ACT_IND_STRU       stAtRnicIpv6PdpActInd;
	AT_RNIC_IPV4_PDP_ACT_IND_STRU       stAtRnicIpv4PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV6_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv6PdpActInd.enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;
    stAtRnicIpv6PdpActInd.ucRabId         = 4;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

	MOCKER(ADS_DL_RegDlDataCallback).expects(never());
    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvAtIpv4v6PdpActInd
��������   : RNIC_RcvAtIpv4v6PdpActInd UT������
�޸���ʷ   :
1.��   ��  : 2012-12-12
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtIpv4v6PdpActInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4v6PdpActInd_001
������������      : modem0,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV4V6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(stAtRnicIpv4v6PdpActInd.ucRabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4v6PdpActInd_002
������������      : modem1,��ǰΪ�ֶ�����ģʽ��RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
Ԥ�ڽ��          : ��������ͳ�ƶ�ʱ��, PDP��������IPV4V6Ϊ�Ѽ���״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	VOS_UINT8                           ucNewBabId;

	ucNewBabId = 74;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_1;

    /* ֹͣ����ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);

    MOCKER(ADS_DL_RegDlDataCallback)
        .expects(exactly(1))
        .with(eq(ucNewBabId), any());
	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);

     /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4v6PdpActInd_003
������������      : modem����
Ԥ�ڽ��          : ʧ��
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 10;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_BUTT;

    MOCKER(ADS_DL_RegDlDataCallback).expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtIpv4v6PdpActInd_004
������������      : rabid���ڷ�Χ��
Ԥ�ڽ��          : ʧ��
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtIpv4v6PdpActInd, Test_RNIC_RcvAtIpv4v6PdpActInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU     stAtRnicIpv4v6PdpActInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    pstDialModeCtx = RNIC_GetDialModeAddr();
    pstDialModeCtx->enDialMode = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialModeCtx->ulIdleTime = AT_APP_IDLE_TIME;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicIpv4v6PdpActInd, 0, sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    stAtRnicIpv4v6PdpActInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicIpv4v6PdpActInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicIpv4v6PdpActInd.enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;
    stAtRnicIpv4v6PdpActInd.ucRabId         = 17;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicIpv4v6PdpActInd.ucRmNetId);
	pstSpecNetCardCtx->enModemId = MODEM_ID_0;

    MOCKER(ADS_DL_RegDlDataCallback).expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicIpv4v6PdpActInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
/*****************************************************************************
����       : Test_RNIC_RcvAtPdpDeactInd
��������   : RNIC_RcvAtPdpDeactInd UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtPdpDeactInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};


/*******************************************************************
�����������      : Test_RNIC_RcvAtPdpDeactInd_001
������������      : IPV4����״̬, IPV6����״̬���յ�AT�·���IPV4ȥ������Ϣ
Ԥ�ڽ��          : ���ŶϿ���ʱ��ֹͣ�� ����ͳ�ƶ�ʱ��δֹͣ,PDP��������IPV4Ϊȥ����״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_001)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4PdpInfo.ucRabId    = 11;
     /* IPV4�Ѽ��� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6�Ѽ��� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* �������ŶϿ���ʱ�� */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdpDeactInd_002
������������      : IPV4����״̬��IPV6����״̬���յ�AT�·���IPV6ȥ������Ϣ
Ԥ�ڽ��          : �Ͽ����Ŷ�ʱ��δֹͣ������ͳ�ƶ�ʱ��δֹͣ, PDP��������IPV6Ϊȥ����״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_002)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv6PdpInfo.ucRabId    = 11;
     /* IPV4�Ѽ��� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6�Ѽ��� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* �������ŶϿ���ʱ�� */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(2))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdpDeactInd_003
������������      : IPV4δ����״̬��IPV6δ����״̬��IPV4V6����״̬���յ�AT�·���IPV4V6ȥ������Ϣ
Ԥ�ڽ��          : ����ͳ�ƶ�ʱ��ֹͣ, PDP��������IPV4V6Ϊȥ����״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_003)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4v6PdpInfo.ucRabId    = 11;
     /* IPV4δ���� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6δ���� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6�Ѽ��� */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* ֹͣ���ŶϿ���ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdpDeactInd_004
������������      : IPV4δ����״̬��IPV6δ����״̬��IPV4V6δ����״̬���յ�AT�·���ȥ������Ϣ
Ԥ�ڽ��          : ���ŶϿ���ʱ��ֹͣ, ����ͳ�ƶ�ʱ��ֹͣ����Ϊȥ����״̬
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_004)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 11;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4v6PdpInfo.ucRabId    = 11;
     /* IPV4δ���� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6δ���� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6�Ѽ��� */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StopTimer(TI_RNIC_DSFLOW_STATS_0);
    /* ֹͣ���ŶϿ���ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdpDeactInd_005
������������      : IPV4����״̬, IPV6����״̬���յ�AT�·���IPV4ȥ������Ϣ,���rabid��Ӧ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdpDeactInd, Test_RNIC_RcvAtPdpDeactInd_005)
{
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus1;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus2;
    AT_RNIC_PDP_DEACT_IND_STRU          stAtRnicPdpDectInd;
    RNIC_DIAL_MODE_STRU                *pstDialModeCtx = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stAtRnicPdpDectInd, 0, sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    stAtRnicPdpDectInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicPdpDectInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicPdpDectInd.enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;
    stAtRnicPdpDectInd.ucRabId         = 4;

     pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);
     pstPdpAddr->stIpv4PdpInfo.ucRabId    = 4;
     /* IPV4�Ѽ��� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6�Ѽ��� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
    /* �������ŶϿ���ʱ�� */
    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

	MOCKER(V_GetRelTmRemainTime)
		.expects(exactly(1))
		.will(returnValue(VOS_OK));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicPdpDectInd);

    pstPdpAddr = RNIC_GetPdpCtxAddr(stAtRnicPdpDectInd.ucRmNetId);

    /* ��ȡ����ͳ�ƶ�ʱ����״̬ */
    enTimerStatus1 = RNIC_GetTimerStatus(TI_RNIC_DSFLOW_STATS_0);
    /* ��ȡ���ŶϿ���ʱ����״̬ */
    enTimerStatus2 = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTimerStatus1);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTimerStatus2);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvAtMtuChangeInd
��������   : RNIC_RcvAtMtuChangeInd UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtMtuChangeInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};


/*******************************************************************
�����������      : Test_RNIC_RcvAtMtuChangeInd_001
������������      : MTUֵ�����ı��AT������ָʾ��Ϣ
Ԥ�ڽ��          : �ı��Ӧ������Ϣ��MTUֵ
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtMtuChangeInd, Test_RNIC_RcvAtMtuChangeInd_001)
{
	AT_RNIC_MTU_CHANGE_IND_STRU         stAtRnicMtuChangeInd;
	RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
	RNIC_NETCARD_DEV_INFO_STRU         *pstNetDevInfo;
	RNIC_NETCARD_DEV_INFO_STRU          stPrv;
	struct net_device                   stNetDev;

	/* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
	VOS_MemSet(&stAtRnicMtuChangeInd, 0, sizeof(AT_RNIC_MTU_CHANGE_IND_STRU));
	stAtRnicMtuChangeInd.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicMtuChangeInd.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicMtuChangeInd.enMsgId         = ID_AT_RNIC_MTU_CHANGE_IND;
	stAtRnicMtuChangeInd.ulMtuValue		 = 100;

	pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(stAtRnicMtuChangeInd.ucRmNetId);

	pstSpecNetCardCtx->pstNetDevInfo = &stPrv;

    pstNetDevInfo = pstSpecNetCardCtx->pstNetDevInfo;
	pstNetDevInfo->pstNetDev = &stNetDev;

	RNIC_ProcMsg((MsgBlock *)&stAtRnicMtuChangeInd);

    EXPECT_EQ(100, pstSpecNetCardCtx->pstNetDevInfo->pstNetDev->mtu);
}


/*****************************************************************************
����       : Test_RNIC_RcvAtDsflowInd
��������   : RNIC_RcvAtDsflowInd UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtDsflowInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtDsflowInd_001
������������      : �ڴ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_001)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;

    /* ����ID_AT_RNIC_DIAL_MODE_IND��Ϣ */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.aucRsv[0]       = 0;

    /* ��Ϣ�ڴ����ʧ�� */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtDsflowInd_002
������������      : PDPδ���������£���Ϣ���ͳɹ�
Ԥ�ڽ��          : �ϱ�������Ϊ0
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_002)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����ID_AT_RNIC_DSFLOW_IND��Ϣ */
    stAtRnicDsflowInd.ulSenderPid        = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid      = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId            = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.enRnicRmNetId      = RNIC_RM_NET_ID_0;
    stAtRnicDsflowInd.clientId           = 1;
    stAtRnicDsflowInd.aucRsv[0]          = 0;

    /* ��Ҫƥ���ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                 = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid               = WUEPS_PID_AT;
    stSndMsg.enMsgId                     = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                    = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 0;
    stSndMsg.stRnicDataRate.ulDLDataRate = 0;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4δ���� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV6δ���� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6�Ѽ��� */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg ����ID_RNIC_AT_DSFLOW_RSP��Ϣ*/
     MOCKER(Ps_SendMsg)
         .expects(exactly(1))
         .with(any(), any(), eq(ACPU_PID_RNIC), any());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtDsflowInd_003
������������      : PDP���������£���Ϣ���ͳɹ�
Ԥ�ڽ��          : �ϱ�������Ϊ��ǰ������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_003)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    stAtRnicDsflowInd.aucRsv[0]       = 0;

    /* ����ID_AT_RNIC_DSFLOW_IND��Ϣ */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;

    /* ��Ҫƥ���ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid              = WUEPS_PID_AT;
    stSndMsg.enMsgId                    = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                   = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 100;
    stSndMsg.stRnicDataRate.ulDLDataRate = 50;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4���� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6δ���� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6�Ѽ��� */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg ����ID_RNIC_AT_DSFLOW_RSP��Ϣ*/
     MOCKER(Ps_SendMsg)
         .expects(exactly(1))
         .with(any(), any(), eq(ACPU_PID_RNIC), any());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtDsflowInd_004
������������      : PDP���������£���Ϣ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDsflowInd, Test_RNIC_RcvAtDsflowInd_004)
{
    AT_RNIC_DSFLOW_IND_STRU             stAtRnicDsflowInd;
    RNIC_AT_DSFLOW_RSP_STRU             stSndMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����ID_AT_RNIC_DSFLOW_IND��Ϣ */
    stAtRnicDsflowInd.ulSenderPid     = WUEPS_PID_AT;
    stAtRnicDsflowInd.ulReceiverPid   = ACPU_PID_RNIC;
    stAtRnicDsflowInd.enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    stAtRnicDsflowInd.clientId        = 1;
    stAtRnicDsflowInd.aucRsv[0]       = 0;
    stAtRnicDsflowInd.enRnicRmNetId   = RNIC_RM_NET_ID_0;

    /* ��Ҫƥ���ID_RNIC_AT_DSFLOW_RSP */
    stSndMsg.ulSenderPid                = ACPU_PID_RNIC;
    stSndMsg.ulReceiverPid              = WUEPS_PID_AT;
    stSndMsg.enMsgId                    = ID_RNIC_AT_DSFLOW_RSP;
    stSndMsg.clientId                   = 1;
    stSndMsg.stRnicDataRate.ulDLDataRate = 100;
    stSndMsg.stRnicDataRate.ulDLDataRate = 50;

    RNIC_SetCurrentDlRate(100, ucIndex);
    RNIC_SetCurrentUlRate(50, ucIndex);

     pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
     /* IPV4���� */
     pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
     /* IPV6δ���� */
     pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
     /* IPV4V6�Ѽ��� */
     pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* VOS_SendMsg ����ID_RNIC_AT_DSFLOW_RSP��Ϣ*/
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stAtRnicDsflowInd);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvAtDialModeReq
��������   : RNIC_RcvAtDialModeReq UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtDialModeReq: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtDialModeReq_001
������������      :
Ԥ�ڽ��          :
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_001)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* ����AT_RNIC_DIAL_MODE_REQ��Ϣ */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	/* ��Ϣ�ڴ����ʧ�� */
	MOCKER(V_AllocMsg)
        .stubs()
		.will(returnValue(VOS_NULL_PTR));

	MOCKER(Ps_SendMsg)
		.expects(never());

	/* ������Ϣ��ں��� */
	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* ������ʱ, ��Ҫ����������λ�ü������ */
	GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtDialModeReq_002
������������      :
Ԥ�ڽ��          :
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_002)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* ����AT_RNIC_DIAL_MODE_REQ��Ϣ */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	pstDialMode                         = RNIC_GetDialModeAddr();

	/* VOS_SendMsg ����ID_RNIC_AT_DSFLOW_RSP��Ϣ*/
	MOCKER(Ps_SendMsg)
		.expects(exactly(1))
		.with(any(), any(), eq(ACPU_PID_RNIC), any());

	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* ������ʱ, ��Ҫ����������λ�ü������ */
	GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtDialModeReq_003
������������      :
Ԥ�ڽ��          :
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtDialModeReq, Test_RNIC_RcvAtDialModeReq_003)
{
	AT_RNIC_DIAL_MODE_REQ_STRU          stAtRnicDialModeReq;
	RNIC_AT_DIAL_MODE_CNF_STRU          stSndMsg;
	RNIC_DIAL_MODE_STRU                *pstDialMode;

	/* ����AT_RNIC_DIAL_MODE_REQ��Ϣ */
	VOS_MemSet(&stAtRnicDialModeReq, 0, sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
	stAtRnicDialModeReq.ulSenderPid     = WUEPS_PID_AT;
	stAtRnicDialModeReq.ulReceiverPid   = ACPU_PID_RNIC;
	stAtRnicDialModeReq.enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
	stAtRnicDialModeReq.clientId        = 1;

	pstDialMode                         = RNIC_GetDialModeAddr();

	/* VOS_SendMsg ����ID_AT_RNIC_DIAL_MODE_REQ��Ϣ*/
	MOCKER(Ps_SendMsg)
        .stubs()
		.will(returnValue(VOS_ERR));

	/* ������Ϣ��ں��� */
	RNIC_ProcMsg((MsgBlock *)&stAtRnicDialModeReq);

	/* ������ʱ, ��Ҫ����������λ�ü������ */
	GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvTiDsflowStatsExpired
��������   : RNIC_RcvTiDsflowStatsExpired UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvTiDsflowStatsExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvTiDsflowStatsExpired_001
������������      : PDPδ���RNIC�յ���ʱ����ʱ��Ϣ��ϢTI_RNIC_APP_DSFLOW�Ĵ���
Ԥ�ڽ��          : �������ʵ�ȫ�ֱ�����û��ֵ������ͳ��Byte�����
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDsflowStatsExpired, Test_RNIC_RcvTiDsflowStatsExpired_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DSFLOW_STATS_0;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndBytes = 0;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes = 0;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6�Ѽ��� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTiDsflowStatsExpired_002
������������      : PDP����ʱ��RNIC�յ���ʱ����ʱ��Ϣ��ϢTI_RNIC_APP_DSFLOW�Ĵ���
Ԥ�ڽ��          : �������ʵ�ȫ�ֱ�������ֵ,����ͳ��Byte�����
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDsflowStatsExpired, Test_RNIC_RcvTiDsflowStatsExpired_002)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName    = TI_RNIC_DSFLOW_STATS_0;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndBytes = 50;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes = 200;
    pstUlCtx->stULDataStats.ulULTotalSndBytes  = 12345;
    pstDlCtx->stDLDataStats.ulDLTotalRcvBytes  = 54321;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6�Ѽ��� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(25, pstUlCtx->stULDataStats.ulULCurDataRate);
    EXPECT_EQ(100, pstDlCtx->stDLDataStats.ulDLCurDataRate);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndBytes);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes);
    EXPECT_EQ(12345, pstUlCtx->stULDataStats.ulULTotalSndBytes);
    EXPECT_EQ(54321, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvTiDemandDialDisconnectExpired
��������   : RNIC_RcvTiDemandDialDisconnectExpired UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvTiDemandDialDisconnectExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialDisconnectExpired_001
������������      : �ֶ�����ģʽ�¡�RNIC�յ���ʱ����ʱ��Ϣ��ϢTI_RNIC_APP_DEMAND_DIAL_DOWN�Ĵ���
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_MANUAL;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6δ���� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialDisconnectExpired_002
������������      : ���貦��ģʽ�£���ǰ���û����������û����ӡ�
Ԥ�ڽ��          : �Ͽ����Ŷ�ʱ������������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_002)
{
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6δ���� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;


    RNIC_IncTiDialDownExpCount();

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, ulCount);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialDisconnectExpired_003
������������      : ���貦��ģʽ�£���ǰ���û����������û����ӡ�
Ԥ�ڽ��          : �Ͽ����Ŷ�ʱ������������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_003)
{
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6δ���� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, ulCount);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialDisconnectExpired_004
������������      : ���貦��ģʽ�£���ǰ���û����������û����ӣ���ʱ����ʱ�Ѵﵽ��ͳ�ƵĴ���
Ԥ�ڽ��          : �Ͽ����Ŷ�ʱ�����������ӣ� ֪ͨӦ�ò���
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_004)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;
	pstDialMode->enEventReportFlag      = RNIC_ALLOW_EVENT_REPORT;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6�Ѽ��� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();
    for (i = 1; i < (AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN); i++)
    {
        RNIC_IncTiDialDownExpCount();
    }

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ((AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN), ulCount);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialDisconnectExpired_005
������������      : ֪ͨӦ�öϿ�����ʧ��
Ԥ�ڽ��          : �Ͽ�����ʧ�ܼ���������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialDisconnectExpired, Test_RNIC_RcvTiDemandDialDisconnectExpired_005)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCount;
    REL_TIMER_MSG                       stTimeMsg;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_DEMAND_CONNECT;
    pstDialMode->ulIdleTime             = AT_APP_IDLE_TIME;
	pstDialMode->enEventReportFlag      = RNIC_ALLOW_EVENT_REPORT;

    /* ��ȡ�����������ĵ�ַ */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstUlCtx->stULDataStats.ulULPeriodSndPkts  = 1;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts  = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    /* IPV4���� */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV6δ���� */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* IPV4V6�Ѽ��� */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;

    RNIC_ClearTiDialDownExpCount();
    for (i = 1; i < (AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN); i++)
    {
        RNIC_IncTiDialDownExpCount();
    }

    MOCKER(drv_get_local_usr_connect_status)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));
	MOCKER(RNIC_SendDialEvent)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    ulCount = RNIC_GetTiDialDownExpCount();
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);

    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ((AT_APP_IDLE_TIME * TI_RNIC_UNIT / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN), ulCount);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_RNIC_RcvTiDemandDialProtectExpired
�������� : Test_RNIC_RcvTiDemandDialProtectExpired UT������
�޸���ʷ     :
1.��   ��  : 2012-06-06
  ��   ��  : A00165503
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvTiDemandDialProtectExpired: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvTiDemandDialProtectExpired_001
������������      : ֹͣ���貦�ű�����ʱ��
Ԥ�ڽ��          : ֹͣ���貦�ű�����ʱ��
�޸���ʷ     :
1.��   ��  : 2012-06-06
  ��   ��  : A00165503
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvTiDemandDialProtectExpired, Test_RNIC_RcvTiDemandDialProtectExpired_001)
{
    //��������
    REL_TIMER_MSG                       stTimeMsg;

    //������ʼ��
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid   = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid = ACPU_PID_RNIC;
    stTimeMsg.ulName        = TI_RNIC_DEMAND_DIAL_PROTECT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    //ִ�м��
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_RcvAtMsg
��������   : RNIC_RcvAtMsg UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtMsg_001
������������      : �յ�����Ϣû����Ҫ�����
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg, Test_RNIC_ProcMsg_001)
{
    MSG_HEADER_STRU                     stMsgHeader;

    /* ����ID_AT_RNIC_IPV4_PDP_ACT_IND��Ϣ */
    VOS_MemSet(&stMsgHeader, 0, sizeof(MSG_HEADER_STRU));
    stMsgHeader.ulSenderPid     = WUEPS_PID_AT;
    stMsgHeader.ulReceiverPid   = ACPU_PID_RNIC;
    stMsgHeader.ulMsgName      = ID_RNIC_AT_MSG_ID_ENUM_BUTT;


    MOCKER(RNIC_RcvAtIpv4PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtIpv6PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtIpv4v6PdpActInd)
        .expects(never());

    MOCKER(RNIC_RcvAtPdpDeactInd)
        .expects(never());

    MOCKER(RNIC_RcvAtDsflowInd)
        .expects(never());

    MOCKER(RNIC_RcvAtMtuChangeInd)
        .expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg((MsgBlock *)&stMsgHeader);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtMsg_002
������������      : �յ�AT PDN������Ϣ
Ԥ�ڽ��          : ����PDN���÷ַ�������
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg,Test_RNIC_RcvAtMsg_002)
{
    /*��������*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;


    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnCfgInd,0x00,sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;

    /*������׮*/
    MOCKER(RNIC_RcvAtPdnInfoCfgInd)
        .expects(exactly(1));

    /*���ñ��⺯�� */
    RNIC_RcvAtMsg((MsgBlock *)&stRnicPdnCfgInd);

    /* �����֤*/

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtMsg_003
������������      : �յ�AT PDN�ͷ���Ϣ
Ԥ�ڽ��          : ����PDN�����ͷŷַ�������
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtMsg,Test_RNIC_RcvAtMsg_003)
{
    /*��������*/
    AT_RNIC_PDN_INFO_REL_IND_STRU     	stRnicPdnCfgRel;


    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnCfgRel,0x00,sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnCfgRel.enMsgId = ID_AT_RNIC_PDN_INFO_REL_IND;

    /*������׮*/
    MOCKER(RNIC_RcvAtPdnInfoRelInd)
        .expects(exactly(1));

    /*���ñ��⺯�� */
    RNIC_RcvAtMsg((MsgBlock *)&stRnicPdnCfgRel);

    /* �����֤*/

    GlobalMockObject::verify();
}


/*****************************************************************************
����       : Test_RNIC_RcvTimerMsg
��������   : RNIC_RcvTimerMsg UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvTimerMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvTimerMsg_001
������������      : �յ��Ķ�ʱ����Ϣû����Ҫ�����
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTimerMsg, Test_RNIC_RcvTimerMsg_001)
{
    REL_TIMER_MSG                       stTimeMsg;
    VOS_UINT32                          ulRst;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_TIMER_BUTT;

    MOCKER(RNIC_RcvTiDsflowStatsExpired)
        .expects(never());

    MOCKER(RNIC_RcvTiDemandDialProtectExpired)
        .expects(never());

    MOCKER(RNIC_RcvTiDemandDialDisconnectExpired)
        .expects(never());


    /* ������Ϣ��ں��� */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    EXPECT_EQ(VOS_OK, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvTimerMsg_002
������������      : �յ��Ķ�ʱ����Ϣ������������ֵΪERR
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_RcvTimerMsg, Test_RNIC_RcvTimerMsg_002)
{
	 REL_TIMER_MSG                       stTimeMsg;
     VOS_UINT32                          ulRst;

    /* ����REL_TIMER_MSG��Ϣ */
    VOS_MemSet(&stTimeMsg, 0, sizeof(REL_TIMER_MSG));
    stTimeMsg.ulSenderPid                = VOS_PID_TIMER;
    stTimeMsg.ulReceiverPid              = ACPU_PID_RNIC;
    stTimeMsg.ulName                     = TI_RNIC_DSFLOW_STATS_0;

	MOCKER(RNIC_RcvTiDsflowStatsExpired)
        .stubs()
        .will(returnValue(VOS_ERR));
    /* ������Ϣ��ں��� */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stTimeMsg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}

/*****************************************************************************
����       : Test_RNIC_ProcMsg
��������   : RNIC_ProcMsg UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_ProcMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_ProcMsg_001
������������      : �յ�����ϢΪ��ʱ
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcMsg, Test_RNIC_ProcMsg_001)
{
    MsgBlock                     *pstMsgBlock = VOS_NULL_PTR;

    MOCKER(RNIC_RcvAtMsg)
        .expects(never());

    MOCKER(RNIC_RcvTimerMsg)
        .expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg(pstMsgBlock);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_ProcMsg_002
������������      : �յ�����Ϣû�ж�Ӧ��PIDʱ
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : f00179208
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_ProcMsg, Test_RNIC_ProcMsg_002)
{
    MsgBlock                            stMsgBlock;

    VOS_MemSet(&stMsgBlock, 0, sizeof(MsgBlock));
    stMsgBlock.ulSenderPid                = ACPU_PID_ADS_UL;
    stMsgBlock.ulReceiverPid              = ACPU_PID_RNIC;

    MOCKER(RNIC_RcvAtMsg)
        .expects(never());

    MOCKER(RNIC_RcvTimerMsg)
        .expects(never());

    /* ������Ϣ��ں��� */
    RNIC_ProcMsg(&stMsgBlock);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_GetDsflowTimerIdByNetId
��������   : RNIC_GetDsflowTimerIdByNetId UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_GetDsflowTimerIdByNetId: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
�����������      : Test_RNIC_GetDsflowTimerIdByNetId_001
������������      : ����ID�ֱ�Ϊ1,2,3,4
Ԥ�ڽ��          : ����ͳ�ƶ�ʱ��Ϊ1,2,3,4
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_GetDsflowTimerIdByNetId, Test_RNIC_GetDsflowTimerIdByNetId_001)
{
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID1;
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID2;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID3;
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID4;
#endif
	RNIC_TIMER_ID_ENUM_UINT16 enTimerID5;

    enTimerID1 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_1);
	enTimerID2 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	enTimerID3 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_3);
	enTimerID4 = RNIC_GetDsflowTimerIdByNetId(RNIC_RM_NET_ID_4);
#endif
	enTimerID5 = RNIC_GetDsflowTimerIdByNetId(RNIC_RMNET_ID_BUTT);

	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1,enTimerID1);
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2,enTimerID2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_3,enTimerID3);
	EXPECT_EQ(TI_RNIC_DSFLOW_STATS_4,enTimerID4);
#endif
	EXPECT_EQ(TI_RNIC_TIMER_BUTT,enTimerID5);
    /* ������ʱ, ��Ҫ����������λ������� */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_GetNetIdByTimerId
��������   : RNIC_GetNetIdByTimerId UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_GetNetIdByTimerId: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
�����������      : Test_RNIC_GetNetIdByTimerId_001
������������      : ����ͳ�ƶ�ʱ��Ϊ1,2,3,4
Ԥ�ڽ��          : �����ֱ�Ϊ1,2,3,4
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_GetNetIdByTimerId, Test_RNIC_GetNetIdByTimerId_001)
{
	VOS_UINT8 ucRmNedId1;
	VOS_UINT8 ucRmNedId2;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	VOS_UINT8 ucRmNedId3;
	VOS_UINT8 ucRmNedId4;
#endif

    ucRmNedId1 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_1);
	ucRmNedId2 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	ucRmNedId3 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_3);
	ucRmNedId4 = RNIC_GetNetIdByTimerId(TI_RNIC_DSFLOW_STATS_4);
#endif

	EXPECT_EQ(RNIC_RM_NET_ID_1,ucRmNedId1);
	EXPECT_EQ(RNIC_RM_NET_ID_2,ucRmNedId2);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
	EXPECT_EQ(RNIC_RM_NET_ID_3,ucRmNedId3);
	EXPECT_EQ(RNIC_RM_NET_ID_4,ucRmNedId4);
#endif
    /* ������ʱ, ��Ҫ����������λ������� */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_BuildRabIdByModemId
��������   : RNIC_BuildRabIdByModemId UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_BuildRabIdByModemId: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
�����������      : Test_RNIC_BuildRabIdByModemId_001
������������      : modemID�Ȳ�Ϊ0Ҳ��Ϊ1
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_BuildRabIdByModemId, Test_RNIC_BuildRabIdByModemId_001)
{
	VOS_UINT8 ucRabId = 6;
	VOS_UINT32 ulRst;

	ulRst = RNIC_BuildRabIdByModemId(MODEM_ID_BUTT,ucRabId,&ucRabId);

	EXPECT_EQ(VOS_ERR,ulRst);
    /* ������ʱ, ��Ҫ����������λ������� */
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_SaveNetIdByRabId
��������   : RNIC_SaveNetIdByRabId UT������
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_SaveNetIdByRabId: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};

/*******************************************************************
�����������      : Test_RNIC_SaveNetIdByRabId_001
������������      : RABID������5-15
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ   :
1.��   ��  : 2011-12-10
  ��   ��  : z00220246
  �޸����� : �½�CASE

*******************************************************************/
TEST_F(Test_RNIC_SaveNetIdByRabId, Test_RNIC_SaveNetIdByRabId_001)
{
	VOS_UINT8  ucRabId = 4;
    VOS_UINT32 ulRst;
	ulRst = RNIC_SaveNetIdByRabId(MODEM_ID_0,ucRabId,RNIC_RM_NET_ID_1);

  //��EXPECT_EQ(VOS_ERR,ulRst);
    /* ������ʱ, ��Ҫ����������λ������� */
    GlobalMockObject::verify();
}


/*****************************************************************************
����       : Test_RNIC_RcvCcpuResetStartInd
��������   : RNIC_RcvCcpuResetStartInd UT������
�޸���ʷ   :
1.��   ��  : 2013-04-19
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvCcpuResetStartInd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvCcpuResetStartInd_001
������������      : �յ�ID_CCPU_RNIC_RESET_START_IND
Ԥ�ڽ��          : ����VOS_ERROR
�޸���ʷ   :
1.��   ��  : 2013-04-19
  ��   ��  : f00179208
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvCcpuResetStartInd, Test_RNIC_RcvCcpuResetStartInd_001)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* ������ʼ�� */

    /* ����ID_CCPU_RNIC_RESET_START_IND��Ϣ */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_CCPU_RESET_START_IND;

    /* ׮���� */
    MOCKER(RNIC_StopAllTimer)
        .expects(exactly(1));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*****************************************************************************
����       : Test_RNIC_RcvRnicMsg
��������   : RNIC_RcvRnicMsg UT������
�޸���ʷ   :
1.��   ��  : 2013-04-19
  ��   ��  : f00179208
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvRnicMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvRnicMsg_001
������������      : �յ�ID_CCPU_RNIC_RESET_END_IND
Ԥ�ڽ��          : ����VOS_ERROR
�޸���ʷ   :
1.��   ��  : 2013-04-19
  ��   ��  : f00179208
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicMsg, Test_RNIC_RcvRnicMsg_001)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* ������ʼ�� */

    /* ����ID_CCPU_RNIC_RESET_START_IND��Ϣ */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_CCPU_RESET_END_IND;

    /* ׮���� */
    MOCKER(RNIC_StopAllTimer)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicMsg_002
������������      : �յ�ID_RNIC_RESET_MSG_ID_ENUM_BUTT
Ԥ�ڽ��          : ����VOS_ERROR
�޸���ʷ   :
1.��   ��  : 2013-04-19
  ��   ��  : f00179208
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicMsg, Test_RNIC_RcvRnicMsg_002)
{
    VOS_UINT32                          ulRst;
    RNIC_CCPU_RESET_IND_STRU            stResetInd;

    /* ������ʼ�� */

    /* ����ID_CCPU_RNIC_RESET_START_IND��Ϣ */
    VOS_MemSet(&stResetInd, 0, sizeof(RNIC_CCPU_RESET_IND_STRU));
    stResetInd.ulSenderPid     = ACPU_PID_RNIC;
    stResetInd.ulReceiverPid   = ACPU_PID_RNIC;
    stResetInd.enMsgId         = ID_RNIC_RNIC_MSG_ID_BUTT;

    /* ׮���� */
    MOCKER(RNIC_StopAllTimer)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_ProcMsg((MsgBlock *)&stResetInd);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*****************************************************************************
����     : Test_RNIC_RcvAtPdnInfoCfgInd
�������� : RNIC_RcvAtPdnInfoCfgInd UT������
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtPdnInfoCfgInd: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoCfgInd_001
������������      : ����ModemId����RABIDʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_001)
{
    /*��������*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU      	stRnicPdnCfgInd;
    VOS_UINT32                          ulRslt;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;

    /*������׮*/
    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    /*���ñ��⺯�� */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* �����֤*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoCfgInd_002
������������      : �洢RABID��Ӧ������ID
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_002)
{
    /*��������*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU      	stRnicPdnCfgInd;
    VOS_UINT32                          ulRslt;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId = 16;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* �����֤*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoCfgInd_003
������������      : �յ�IPV4���͵�PDN������Ϣ
Ԥ�ڽ��          : ����IPV4 PDN��Ϣ������VOS_OK
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_003)
{
    /*��������*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    stFilterIpAddr.bitOpIpv4Addr        = VOS_TRUE;

    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = 5;
    stRnicPdnCfgInd.bitOpIpv4PdnInfo    = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnCfgInd.ucRmNetId);

    /*������׮*/
    MOCKER(ADS_DL_RegFilterDataCallback)
        .stubs()
        .with(any(),mirror(&stFilterIpAddr, sizeof(stFilterIpAddr)),any());

    /*���ñ��⺯�� */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* �����֤*/
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoCfgInd_004
������������      : �յ�IPV6���͵�PDN������Ϣ
Ԥ�ڽ��          : ����IPV6 PDN��Ϣ������VOS_OK
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoCfgInd,Test_RNIC_RcvAtPdnInfoCfgInd_004)
{
    /*��������*/
    AT_RNIC_PDN_INFO_CFG_IND_STRU       stRnicPdnCfgInd;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stFilterIpAddr, 0x00, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    stFilterIpAddr.bitOpIpv6Addr        = VOS_TRUE;

    PS_MEM_SET(&stRnicPdnCfgInd, 0x00, sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));
    stRnicPdnCfgInd.enMsgId             = ID_AT_RNIC_PDN_INFO_CFG_IND;
    stRnicPdnCfgInd.ucRabId             = 5;
    stRnicPdnCfgInd.bitOpIpv6PdnInfo    = 1;

    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnCfgInd.ucRmNetId);

    /*������׮*/
    MOCKER(ADS_DL_RegFilterDataCallback)
        .stubs()
        .with(any(),mirror(&stFilterIpAddr, sizeof(stFilterIpAddr)),any());

    /*���ñ��⺯�� */
    ulRslt = RNIC_RcvAtPdnInfoCfgInd((MsgBlock *)&stRnicPdnCfgInd);

    /* �����֤*/
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_RNIC_RcvAtPdnInfoRelInd
�������� : RNIC_RcvAtPdnInfoRelInd UT������
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvAtPdnInfoRelInd: public ::testing::Test
{
public:

    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoRelInd_001
������������      : һ������ʱ���յ�IPV4\IPV6���͵�PDN������Ϣ
Ԥ�ڽ��          : ����ע��״̬�����IPV4\IPv6 PDN��Ϣ
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_001)
{
    /*��������*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*ȫ�ֱ�����ʼ��*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*������׮*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*���ñ��⺯�� */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* �����֤*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoRelInd_002
������������      : һ������ʱ���յ�IPV4V6���͵�PDN������Ϣ
Ԥ�ڽ��          : ����ע��״̬�����IPV4V6 PDN��Ϣ
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_002)
{
    /*��������*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*ȫ�ֱ�����ʼ��*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*������׮*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*���ñ��⺯�� */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* �����֤*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoRelInd_003
������������      : �������ʱ���յ�IPV4���͵�PDN������Ϣ
Ԥ�ڽ��          : ����ע��״̬�����IPV4 PDN��Ϣ
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_003)
{
    /*��������*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*ȫ�ֱ�����ʼ��*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 6;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*������׮*/
    MOCKER(RNIC_StopTimer)
        .expects(never());

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(exactly(1));

    /*���ñ��⺯�� */
    RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* �����֤*/
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvAtPdnInfoRelInd_004
������������      : �յ�PDN������Ϣ�����RABID��Ӧ������IDʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2013-06-19
  ��   ��  : z00214637
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_RNIC_RcvAtPdnInfoRelInd,Test_RNIC_RcvAtPdnInfoRelInd_004)
{
    /*��������*/
    AT_RNIC_PDN_INFO_REL_IND_STRU       stRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT32                          ulRslt;

    /*���ر�����ʼ��*/
    PS_MEM_SET(&stRnicPdnRelInd, 0x00, sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));
    stRnicPdnRelInd.enMsgId             = ID_AT_RNIC_PDN_INFO_REL_IND;
    stRnicPdnRelInd.ucRabId             = 5;

    /*ȫ�ֱ�����ʼ��*/
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr = RNIC_GetPdpCtxAddr(stRnicPdnRelInd.ucRmNetId);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 5;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;

    /*������׮*/
    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    MOCKER(RNIC_SaveNetIdByRabId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(ADS_DL_DeregFilterDataCallback)
        .expects(never());

    /*���ñ��⺯�� */
    ulRslt = RNIC_RcvAtPdnInfoRelInd((MsgBlock *)&stRnicPdnRelInd);

    /* �����֤*/
    EXPECT_EQ(VOS_ERR, ulRslt);

    GlobalMockObject::verify();
}

/* Added by m00217266 for L-C��������Ŀ, 2014-2-7, begin */
/*****************************************************************************
����       : Test_RNIC_RcvRnicRmnetConfigReq
��������   : RNIC_RcvRnicRmnetConfigReq UT������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_RcvRnicRmnetConfigReq: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_001
������������      : �����ڲ�modem��ipv4��������up
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* ipv4���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

        /* ipv6���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* ipv6ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* ipv4ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    }
    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_002
������������      : �����ڲ�modem��ipv6��������up
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_002)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_0, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* ipv4v6ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_0;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_003
������������      : �����ⲿmodem��ipv4��������up
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_003)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv6���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(2, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv4ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(2, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv6ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_004
������������      : �����ⲿmodem��ipv6��������up
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_004)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
#endif

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_005
������������      : �����ڲ�modem��ipv4��������down
Ԥ�ڽ��          : ���ipv4������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_005)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ipv4ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_006
������������      : �����ڲ�modem��ipv6��������down
Ԥ�ڽ��          : ���ipv6������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_006)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ipv6���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    /* ipv6ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_007
������������      : �����ⲿmodem��ipv4��������down
Ԥ�ڽ��          : ���ipv4������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_007)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_008
������������      : �����ⲿmodem��ipv6��������down
Ԥ�ڽ��          : ���ipv6������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_008)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_009
������������      : �����ڲ�modem�л�����modem��ipv4����PDP����(�״�modem�л�)
Ԥ�ڽ��          : ����������ֻ������modem�ļ�����Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_009)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

    /* ����1ipv6���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 6;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    /* ����2ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 7;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_2;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    /* handover */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����2������ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_010
������������      : �����ڲ�modem�л�����modem��ipv6����PDP����(�ڶ���modem�л�)
Ԥ�ڽ��          : ����������ֻ������modem�ļ�����Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_010)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* ����1ipv4���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));

        /* ����1ipv6���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        /* ��һ��handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* �ڶ���handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ipv4v6ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(2));
    }

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_011
������������      : �����ⲿmodem�л�����modem��ipv4����PDP����(�״�modem�л�)
Ԥ�ڽ��          : ����������ֻ������modem�ļ�����Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_011)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_PDP_CTX_STRU                  *pstRmnet2PdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstRmnet2SpecNetCardCtx;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);
    pstRmnet2PdpAddr                    = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_2);
    pstRmnet2SpecNetCardCtx             = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_2);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����1ipv6���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����2ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 7;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_2;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    /* ��һ��handover */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����2������ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstRmnet2SpecNetCardCtx->enModemType);
    EXPECT_EQ(7, pstRmnet2PdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstRmnet2PdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_2, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 7));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_012
������������      : �����ⲿmodem�л�����modem��ipv6����PDP����(�ڶ���modem�л�)
Ԥ�ڽ��          : ����������ֻ������modem�ļ�����Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_012)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    for (i = 0; i < 10; i++)
    {
        /* ����1ipv4���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ����1ipv6���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ��һ��handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* �ڶ���handover */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ����1 ipv4ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ����1 ipv6ȥ���� */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_013
������������      : handover����ѹ������
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_013)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����1ipv6���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    for (i = 0; i < 10; i++)
    {
        /* ��һ����modem handover ��modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 5;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));

        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* �ڶ�����modem handover ��modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 0;
        stRmnetConfigReq.ucRabId        = 6;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(6, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* ��һ����modem handover ��modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 1;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

        /* �ڶ�����modem handover ��modem */
        stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
        stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
        stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
        stRmnetConfigReq.ucPdnId        = 2;
        stRmnetConfigReq.ucRabId        = 0;
        stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
        stRmnetConfigReq.usModemId      = MODEM_ID_0;

        /* �������� */
        RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

        /* ����ƥ�� */
        EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
        EXPECT_EQ(2, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
        EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
        EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
        EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));
    }

    /* ����1 ipv4ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 2;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(1, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    /* ����1 ipv6ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 6));
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_014
������������      : handover���������ipv4���������쳣rabid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_014)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 4;                /* ��Чrabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_015
������������      : handover���������ipv6���������쳣rabid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_015)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 4;                /* ��Чrabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_016
������������      : handover���������ipv4v6���������쳣rabid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_016)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 4;                /* ��Чrabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_OUTSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(1, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_017
������������      : handover���������ipv4v6���������쳣pdnid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_017)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = 21;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;                /* ��Чrabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_018
������������      : handover���������ipv6���������쳣pdnid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_018)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 21;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;                /* ��Чrabid */

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_019
������������      : handover���������ipv4���������쳣pdnid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_019)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 21;       /* ��Чpdnid */
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_020
������������      : handover���������ipv4���������쳣pdnid��Ӧ����idʧ��
Ԥ�ڽ��          : ���������Ĺ�������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_020)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 21;       /* ��Чpdnid */
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_PDN_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_SWITCH;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(5, pstPdpAddr->stIpv4PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_ACTIVE, pstPdpAddr->stIpv4PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RM_NET_ID_1, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_021
������������      : �ⲿmodem����ʱ���յ�IPV4V6����ȥ���ȥ����ɹ�
Ԥ�ڽ��          : ȥ����ɹ�
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_021)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_OUTSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = 1;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4v6ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 1;
    stRmnetConfigReq.ucRabId        = 0;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    MOCKER(RNIC_SaveNetIdByPdnId)
        .will(returnValue(VOS_ERR));

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
#endif
/*******************************************************************
�����������      : Test_RNIC_RcvRnicRmnetConfigReq_022
������������      : �ڲ�modem����ʱ���յ�IPV4V6����ȥ���ȥ����ɹ�
Ԥ�ڽ��          : ȥ����ɹ�
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_RcvRnicRmnetConfigReq, Test_RNIC_RcvRnicRmnetConfigReq_022)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU          stRmnetConfigReq;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           i;

    pstPdpAddr                          = RNIC_GetPdpCtxAddr(RNIC_RM_NET_ID_1);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_1);

    /* ȫ�ֱ�����ʼ�� */
    pstSpecNetCardCtx->enModemType            = RNIC_MODEM_TYPE_INSIDE;
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucPdnId       = RNIC_PDN_ID_INVALID;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId       = 5;

    stRmnetConfigReq.ulSenderCpuId            = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulSenderPid              = ACPU_PID_RNIC;
    stRmnetConfigReq.ulReceiverCpuId          = VOS_LOCAL_CPUID;
    stRmnetConfigReq.ulReceiverPid            = ACPU_PID_RNIC;
    stRmnetConfigReq.enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* ����1ipv4v6ȥ���� */
    stRmnetConfigReq.enIpType       = RNIC_IP_TYPE_IPV4V6;
    stRmnetConfigReq.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stRmnetConfigReq.enRmnetStatus  = RNIC_RMNET_STATUS_DOWN;
    stRmnetConfigReq.ucPdnId        = 0;
    stRmnetConfigReq.ucRabId        = 5;
    stRmnetConfigReq.ucRmNetId      = RNIC_RM_NET_ID_1;
    stRmnetConfigReq.usModemId      = MODEM_ID_0;

    MOCKER(RNIC_SaveNetIdByRabId)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* �������� */
    RNIC_ProcMsg((MsgBlock *)&stRmnetConfigReq);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_MODEM_TYPE_INSIDE, pstSpecNetCardCtx->enModemType);
    EXPECT_EQ(RNIC_RAB_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucRabId);
    EXPECT_EQ(RNIC_PDN_ID_INVALID, pstPdpAddr->stIpv4v6PdpInfo.ucPdnId);
    EXPECT_EQ(RNIC_PDP_REG_STATUS_DEACTIVE, pstPdpAddr->stIpv4v6PdpInfo.enRegStatus);
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_MODEM_ID(MODEM_ID_0, 5));
    EXPECT_EQ(RNIC_RMNET_ID_BUTT, RNIC_GET_RM_NET_ID_BY_PDN_ID(1));

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



/* ���串���� */
/*****************************************************************************
����       : Test_RNIC_ProcInsideModemIpv4ActInd
��������   : RNIC_ProcInsideModemIpv4ActInd UT������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_ProcInsideModemIpv4ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_ProcInsideModemIpv4ActInd_001
������������      : �����ڲ�modem������rabidʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv4ActInd, Test_RNIC_ProcInsideModemIpv4ActInd_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId  = RNIC_RM_NET_ID_0;
    stPdpStatusInd.usModemId  = RNIC_MODEM_TYPE_INSIDE;

    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_SaveNetIdByRabId)
        .expects(never());

    RNIC_ProcInsideModemIpv4ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_ProcInsideModemIpv4ActInd_002
������������      : �����ڲ�modem����������idʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv4ActInd, Test_RNIC_ProcInsideModemIpv4ActInd_002)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucRabId   = 4;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcInsideModemIpv4ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_ProcInsideModemIpv6ActInd
��������   : RNIC_ProcInsideModemIpv6ActInd UT������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_ProcInsideModemIpv6ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_ProcInsideModemIpv6ActInd_001
������������      : �����ڲ�modem������rabidʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv6ActInd, Test_RNIC_ProcInsideModemIpv6ActInd_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId  = RNIC_RM_NET_ID_0;
    stPdpStatusInd.usModemId  = RNIC_MODEM_TYPE_INSIDE;

    MOCKER(RNIC_BuildRabIdByModemId)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_SaveNetIdByRabId)
        .expects(never());

    RNIC_ProcInsideModemIpv6ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_RNIC_ProcInsideModemIpv6ActInd_002
������������      : �����ڲ�modem����������idʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcInsideModemIpv6ActInd, Test_RNIC_ProcInsideModemIpv6ActInd_002)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucRabId   = 4;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcInsideModemIpv6ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
����       : Test_RNIC_ProcOutsideModemIpv6ActInd
��������   : RNIC_ProcOutsideModemIpv6ActInd UT������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_ProcOutsideModemIpv6ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_ProcOutsideModemIpv6ActInd_001
������������      : �����ڲ�modem������rabidʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcOutsideModemIpv6ActInd, Test_RNIC_ProcOutsideModemIpv6ActInd_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucPdnId   = 21;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcOutsideModemIpv6ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����       : Test_RNIC_ProcOutsideModemIpv4ActInd
��������   : RNIC_ProcOutsideModemIpv4ActInd UT������
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������
*****************************************************************************/
class Test_RNIC_ProcOutsideModemIpv4ActInd: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
    void TearDown()
    {
        /* ��ʼ��RNIC��������Ϣ */
        pstRnicCtx = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);
    }
};

/*******************************************************************
�����������      : Test_RNIC_ProcOutsideModemIpv4ActInd_001
������������      : �����ڲ�modem������rabidʧ��
Ԥ�ڽ��          : ����������������Ϣ
�޸���ʷ   :
1.��   ��  : 2014-02-07
  ��   ��  : m00217266
  �޸����� : ��������

*******************************************************************/
TEST_F(Test_RNIC_ProcOutsideModemIpv4ActInd, Test_RNIC_ProcOutsideModemIpv4ActInd_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_REQ_STRU         stPdpStatusInd;

    stPdpStatusInd.ucRmNetId = RNIC_RM_NET_ID_1;
    stPdpStatusInd.ucPdnId   = 21;

    MOCKER(RNIC_GetDsflowTimerIdByNetId)
        .expects(never());

    RNIC_ProcOutsideModemIpv4ActInd(&stPdpStatusInd);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/* ���串���� */
#endif
/* Added by m00217266 for L-C��������Ŀ, 2014-2-7, end */
#endif
