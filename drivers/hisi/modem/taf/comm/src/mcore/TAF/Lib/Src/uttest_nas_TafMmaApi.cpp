#include "gtest/gtest.h"
#include "llt_mockcpp.h"


#include "uttest_nas_TafMmaApi.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

//˵��������������gtest+�������׺Ͳ����������ֲ�����Ϊ��
//      ������ú�gtest��ͬ�Ĺؼ��֣����ⲻ��Ҫ���鷳
//      gtest�ṩ EXPECT �� ASSERT ����,���庬����Կ���Ƭ�����׺궼��һһ��Ӧ�ģ�������EXPECTΪ��

//1���ȶԲ������� EXPECT_TRUE��EXPECT_FALSE/ASSERT_TRUE
//2���Ƚ����� EXPECT_EQ EXPECT_NE
//3���Ƚ��ַ��� EXPECT_STREQ
//4������ʧ�������Ϣ ADD_FAILUREd
//5�����óɹ���ʧ�� SUCCEED FAIL
//6���Զ����ʽ EXPECT_PRED_FORMAT3
//7�����������������TRUE EXPECT_PRED1
//8�������ͱȽ� EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9�����ͼ�� StaticAssertTypeEq
//10������3�ֲ��Լ����¼�
//11����ȡ������������ test_case_name()
//12���Ƚ��쳣 EXPECT_THROW
//13���ṹ�����ͱȽ�ASSERT_SAME_DATA ASSERT_SAME_MEMORY

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*****************************************************************************
����     : TAF_MMA_PlmnPlmnUserSelSetReq
�������� : �û�ָ������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : c00173809
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_PlmnPlmnUserSelSetReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_PlmnPlmnUserSelSetReq_001
������������      : ��Ӫ�����ֳ���Ϊ0
Ԥ�ڽ��          : ���ز�������
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  :   c00173809
  �޸����� : �½�CASE

2.��   ��  : 2015-3-24
  ��   ��  : f00279542
  �޸����� : TAF_MMA_PlmnPlmnUserSelSetReq�滻TAF_PhonePlmnUserSel
*******************************************************************/
TEST_F(Test_TAF_MMA_PlmnPlmnUserSelSetReq,Test_TAF_MMA_PlmnPlmnUserSelSetReq_001)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, begin */
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    TAF_PLMN_USER_SEL_STRU              stPlmnUserSel;
    VOS_UINT32                          ulReslut;

    stPlmnUserSel.enAccessMode = TAF_PH_RA_GSM;
    stPlmnUserSel.ucFormatType = AT_COPS_NUMERIC_TYPE;
    stPlmnUserSel.usOperNameLen = 0;
    ClientId             = 0;
    OpId                 = 0;

    ulReslut = TAF_MMA_PlmnSpecialSelReq(ClientId, OpId, &stPlmnUserSel);
    EXPECT_EQ(VOS_TRUE, ulReslut);

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, end */

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_PlmnPlmnUserSelSetReq_002
������������      : ��Ӫ�����ֳ���Ϊ0������APP_REQ_MSGʧ��
Ԥ�ڽ��          : ���ز�������
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  :   c00173809
  �޸����� : �½�CASE

2.��   ��  : 2015-3-24
  ��   ��  : f00279542
  �޸����� : TAF_MMA_PlmnPlmnUserSelSetReq�滻TAF_PhonePlmnUserSel
*******************************************************************/
TEST_F(Test_TAF_MMA_PlmnPlmnUserSelSetReq,Test_TAF_MMA_PlmnPlmnUserSelSetReq_002)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, begin */
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    TAF_PLMN_USER_SEL_STRU              stPlmnUserSel;

    stPlmnUserSel.enAccessMode = TAF_PH_RA_GSM;
    stPlmnUserSel.ucFormatType = AT_COPS_NUMERIC_TYPE;
    stPlmnUserSel.usOperNameLen = 0;
    ClientId             = 0;
    OpId                 = 0;

    /* MOCKER���� */
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_APS_FAIL));

    EXPECT_EQ(VOS_FALSE, TAF_MMA_PlmnSpecialSelReq(ClientId, OpId, &stPlmnUserSel));

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, end */

    GlobalMockObject::verify();
}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-07, Begin */
/*****************************************************************************
����     : Test_TAF_MMA_PhoneModeSetReq
�������� : �ֻ�ģʽ���ýӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
��   ��  : s00246516
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_PhoneModeSetReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_PhoneModeSetReq_001
������������      : ģʽ���ò���Ϊ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_PhoneModeSetReq,Test_TAF_MMA_PhoneModeSetReq_001)
{

    /* MOCKER���� */

    /* ���ñ��⺯��  */
    TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_PhoneModeSetReq_002
������������      : ����ģʽ����������Ϣ�ڴ�ʧ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_PhoneModeSetReq,Test_TAF_MMA_PhoneModeSetReq_002)
{

    // ��������
    TAF_MMA_PHONE_MODE_PARA_STRU            stPhoneModePara;

    // ������ʼ��
    PS_MEM_SET(&stPhoneModePara, 0, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));

    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;

    /* MOCKER���� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ���ñ��⺯��  */
    TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stPhoneModePara);


    GlobalMockObject::verify();
}


/*****************************************************************************
����     : Test_TAF_MMA_SysCfgReq
�������� : �ֻ�ϵͳ���ýӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
��   ��  : s00246516
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_SetSysCfgReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_SysCfgReq_001
������������      : ����pstSysCfgParaΪ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_SetSysCfgReq,Test_TAF_MMA_SetSysCfgReq_001)
{

    /* MOCKER���� */

    /* ���ñ��⺯��  */
    TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_SysCfgReq_002
������������      : ����SetSysCfgReq��Ϣ�ڴ�ʧ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_SetSysCfgReq,Test_TAF_MMA_SetSysCfgReq_002)
{
    // ��������
    TAF_MMA_SYS_CFG_PARA_STRU            stSysCfgPara;

    // ������ʼ��
    // ������ʼ��
    PS_MEM_SET(&stSysCfgPara, 0, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    stSysCfgPara.enRoam                    = TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON;
    stSysCfgPara.enSrvDomain               = TAF_MMA_SERVICE_DOMAIN_PS;
    stSysCfgPara.enUserPrio                = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    stSysCfgPara.stRatOrder.ucRatOrderNum  = 1;
    stSysCfgPara.stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;

    /* MOCKER���� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ���ñ��⺯��  */
    TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stSysCfgPara);


    GlobalMockObject::verify();
}


/*****************************************************************************
����     : Test_TAF_MMA_AcqBestNetworkReq
�������� : ��ȡ����ӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
��   ��  : s00246516
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_AcqBestNetworkReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_AcqBestNetworkReq_001
������������      : ����pstAcqParaΪ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_AcqBestNetworkReq,Test_TAF_MMA_AcqBestNetworkReq_001)
{

    /* MOCKER���� */

    /* ���ñ��⺯��  */
    TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_AcqBestNetworkReq_002
������������      : ����AcqBestNetworkReq��Ϣ�ڴ�ʧ��
Ԥ�ڽ��          : ����VOS_TRUE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_AcqBestNetworkReq,Test_TAF_MMA_AcqBestNetworkReq_002)
{

    // ��������
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;

    // ������ʼ��
    // ������ʼ��
    PS_MEM_SET(&stAcqPara, 0, sizeof(TAF_MMA_ACQ_PARA_STRU));

    stAcqPara.enAcqReason      = TAF_MMA_ACQ_REASON_POWER_UP;

    /* MOCKER���� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ���ñ��⺯��  */
    TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stAcqPara);

    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_TAF_MMA_RegReq
�������� : ע������ӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
��   ��  : s00246516
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_RegReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_RegReq_001
������������      : ע�����Ϊ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_RegReq,Test_TAF_MMA_RegReq_001)
{

    /* MOCKER���� */

    /* ���ñ��⺯��  */
    TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);


    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_RegReq_002
������������      : ����ע����Ϣ�ڴ�ʧ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_RegReq,Test_TAF_MMA_RegReq_002)
{

    // ��������
    TAF_MMA_REG_PARA_STRU               stRegPara;

    // ������ʼ��
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));

    stRegPara.bitOpPrioClass      = 1;

    /* MOCKER���� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ���ñ��⺯��  */
    TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stRegPara);

    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_TAF_MMA_PowerSaveReq
�������� : Power Save�ӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
��   ��  : s00246516
�޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_PowerSaveReq: public ::testing::Test
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

/* Added by b00269685 for L-C��������Ŀ, 2014-2-25, begin */
/*******************************************************************
�����������      : Test_TAF_MMA_PowerSaveReq_001
������������      : �����Ƿ�
Ԥ�ڽ��          : ��������Ϣ������VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
��   ��  :   b00269685
�޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_001)
{

    /* MOCKER���� */
    MOCKER(Ps_SendMsg)
        .expects(never());

    /* ���ú�������NULL���� */
    TAF_MMA_PowerSaveReq(0, 0, 0, NULL);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_PowerSaveReq_002
������������      : ����PowerSaveReq�ڴ�ʧ��
Ԥ�ڽ��          : ��������Ϣ������VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
��   ��  :   b00269685
�޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_002)
{
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;

    /* MOCKER���� */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* ���ñ��⺯��  */
    TAF_MMA_PowerSaveReq(0, 0, 0, &stPowerSavePara);

    GlobalMockObject::reset();
    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_PowerSaveReq_003
������������      : ����powersavereq��Ϣʧ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-25
  ��   ��  : s00261364
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_PowerSaveReq, Test_TAF_MMA_PowerSaveReq_003)
{
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;

    PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));

    /* MOCKER���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* ���ñ��⺯��  */
    TAF_MMA_PowerSaveReq(0, 0, 0, &stPowerSavePara);

    GlobalMockObject::verify();
}

/* Added by b00269685 for L-C��������Ŀ, 2014-2-25, end */

/*****************************************************************************
����     : Test_TAF_MMA_DetachReq
�������� : Detach�ӿ�
�޸���ʷ :
1.��   ��  : 2014-02-07
  ��   ��  : s00246516
  �޸����� : ��������
*****************************************************************************/
class Test_TAF_MMA_DetachReq: public ::testing::Test
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
�����������      : Test_TAF_MMA_DetachReq_001
������������      : Detach����Ϊ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-07
  ��   ��  :   s00246516
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_001)
{

    /* MOCKER���� */
    MOCKER(Ps_SendMsg)
        .expects(never());

    /* ���ú�������NULL���� */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, VOS_NULL_PTR);


    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_DetachReq_002
������������      : ����DetachReq�ڴ�ʧ��
Ԥ�ڽ��          : ����VOS_FALSE
�޸���ʷ     :
1.��   ��  : 2014-02-07
  ��   ��  :   s00246516
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_002)
{

    TAF_MMA_DETACH_PARA_STRU        stDetachPara;

    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* MOCKER���� */
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(Ps_SendMsg)
        .expects(never());

    /* ���ñ��⺯��  */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDetachPara);

    GlobalMockObject::verify();
}

/*******************************************************************
�����������      : Test_TAF_MMA_DetachReq_003
������������      : ����powersavereq��Ϣʧ��
Ԥ�ڽ��          : ����VOS_TRUE
�޸���ʷ     :
1.��   ��  : 2014-02-07
  ��   ��  :   s00246516
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_TAF_MMA_DetachReq,Test_TAF_MMA_DetachReq_003)
{

    TAF_MMA_DETACH_PARA_STRU        stDetachPara;

    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* MOCKER���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* ���ñ��⺯��  */
    TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDetachPara);

    GlobalMockObject::verify();
}




/* Added by s00246516 for L-C��������Ŀ, 2014-02-07, End */
