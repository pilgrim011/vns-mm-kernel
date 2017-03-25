#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "AppVcApi.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "ATCmdProc.h"

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

#define    THIS_FILE_ID        PS_FILE_ID_VC_API_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*****************************************************************************
����     : Test_APP_VC_SetVoiceVolume
�������� : APP_VC_SetVoiceVolume UT������
�޸���ʷ     :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : ��������
*****************************************************************************/
class Test_APP_VC_SetVoiceVolume: public ::testing::Test
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
�����������      : Test_APP_VC_SetVoiceVolume_001
������������      : ����Ϣ���͵�modem0��PID
Ԥ�ڽ��          : ��������VOS_OK
�޸���ʷ          :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoiceVolume,Test_APP_VC_SetVoiceVolume_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;
    VOS_UINT8                           ucVoiceVolume;

    enClientId = AT_CLIENT_TAB_APP_INDEX;
    enOpId = 1;
    ucVoiceVolume = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    APP_VC_SetVoiceVolume(enClientId, enOpId,ucVoiceVolume);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_APP_VC_GetVoiceVolume
�������� : APP_VC_GetVoiceVolume UT������
�޸���ʷ     :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : ��������
*****************************************************************************/
class Test_APP_VC_GetVoiceVolume: public ::testing::Test
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
�����������      : Test_APP_VC_GetVoiceVolume_001
������������      : ����Ϣ���͵�modem0��PID
Ԥ�ڽ��          : ��������VOS_OK
�޸���ʷ          :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceVolume,Test_APP_VC_GetVoiceVolume_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;

    enClientId = AT_CLIENT_TAB_APP_INDEX;
    enOpId = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    APP_VC_GetVoiceVolume(enClientId, enOpId);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_APP_VC_SetVoiceMode
�������� : APP_VC_SetVoiceMode UT������
�޸���ʷ     :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : ��������
*****************************************************************************/
class Test_APP_VC_SetVoiceMode: public ::testing::Test
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
�����������      : Test_APP_VC_SetVoiceMode_001
������������      : ����Ϣ���͵�modem0��PID
Ԥ�ڽ��          : ��������VOS_OK
�޸���ʷ          :
1.��   ��  : 2012-12-26
  ��   ��  : l00227485
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoiceMode,Test_APP_VC_SetVoiceMode_001)
{
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   enOpId;
    VOS_UINT8                           ucVoiceMode;

    enClientId = AT_CLIENT_ID_APP;
    enOpId = 1;
    ucVoiceMode = 1;

    APP_VC_SetVoiceMode(enClientId, enOpId, ucVoiceMode, I0_WUEPS_PID_VC);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_APP_VC_SetVoicePort
�������� : APP_VC_SetVoicePort������UT������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : f00179208
�޸����� : ��������
*****************************************************************************/
class Test_APP_VC_SetVoicePort: public ::testing::Test
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
�����������      : Test_APP_VC_SetVoicePort_001
������������      : �ڴ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // ������ʼ��
    ClientId                            = 0;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // ���ñ��⺯��
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_SetVoicePort_002
������������      : ������Ϣ��modem0��PIDʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // ������ʼ��
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_SetVoicePort_003
������������      : ������Ϣ��modem0��PID�ɹ�
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetVoicePort,Test_APP_VC_SetVoicePort_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;

    // ������ʼ��
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    ucVoicePort                         = 1;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRst = APP_VC_SetVoicePort(ClientId, OpId, ucVoicePort);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*****************************************************************************
����     : Test_APP_VC_GetVoiceMode
�������� : APP_VC_GetVoiceMode������UT������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : f00179208
�޸����� : ��������
*****************************************************************************/
class Test_APP_VC_GetVoiceMode: public ::testing::Test
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
�����������      : Test_APP_VC_GetVoiceMode_001
������������      : �ڴ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            = 0;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_GetVoiceMode_002
������������      : ������Ϣ��modem0��PIDʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            =AT_CLIENT_ID_APP;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_GetVoiceMode_003
������������      : ������Ϣ��modem0��PID�ɹ�
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoiceMode,Test_APP_VC_GetVoiceMode_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoiceMode(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*****************************************************************************
����     : Test_APP_VC_GetVoicePort
�������� : APP_VC_GetVoicePort������UT������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : f00179208
�޸����� : ��������
*****************************************************************************/
class Test_APP_VC_GetVoicePort: public ::testing::Test
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
�����������      : Test_APP_VC_GetVoicePort_001
������������      : �ڴ����ʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            = 0;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)0));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_GetVoicePort_002
������������      : ������Ϣ��modem0��PIDʧ��
Ԥ�ڽ��          : ����VOS_ERR
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*******************************************************************
�����������      : Test_APP_VC_GetVoicePort_003
������������      : ������Ϣ��modem0��PID�ɹ�
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetVoicePort,Test_APP_VC_GetVoicePort_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    MN_CLIENT_ID_T                      ClientId;
    MN_OPERATION_ID_T                   OpId;

    // ������ʼ��
    ClientId                            = AT_CLIENT_ID_APP;
    OpId                                = 0;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(ClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRst = APP_VC_GetVoicePort(ClientId, OpId);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

/*****************************************************************************
����     : Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode
�������� : APP_VC_AppVcVoiceMode2VcPhyVoiceMode������UT������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : f00179208
�޸����� : ��������
*****************************************************************************/
class Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode: public ::testing::Test
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
�����������      : Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode_001
������������      : ö�ٸ�������ģʽ��ת����ȷ
Ԥ�ڽ��          : ���ض�Ӧ��ö��
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode,Test_APP_VC_AppVcVoiceMode2VcPhyVoiceMode_001)
{
    // ��������

    // ���������
    ASSERT_EQ(VC_PHY_DEVICE_MODE_PCVOICE,       APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_PCVOICE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_EARPHONE,      APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_EARPHONE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_HANDSET,       APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_HANDSET));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_HANDS_FREE,    APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_HANDS_FREE));
    ASSERT_EQ(VC_PHY_DEVICE_MODE_BUTT,          APP_VC_AppVcVoiceMode2VcPhyVoiceMode(APP_VC_VOICE_MODE_BUTT));

}

/*****************************************************************************
����     : Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode
�������� : APP_VC_VcPhyVoiceMode2AppVcVoiceMode������UT������
�޸���ʷ :
1.��   ��  : 2011-10-13
��   ��  : f00179208
�޸����� : ��������
*****************************************************************************/
class Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode: public ::testing::Test
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
�����������      : Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode_001
������������      : ö�ٸ�������ģʽ��ת����ȷ
Ԥ�ڽ��          : ���ض�Ӧ��ö��
�޸���ʷ     :
1.��   ��  : 2011-10-13
  ��   ��  : f00179208
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode,Test_APP_VC_VcPhyVoiceMode2AppVcVoiceMode_001)
{
    // ��������

    // ���������
    ASSERT_EQ(APP_VC_VOICE_MODE_PCVOICE,       APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_PCVOICE));
    ASSERT_EQ(APP_VC_VOICE_MODE_EARPHONE,      APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_EARPHONE));
    ASSERT_EQ(APP_VC_VOICE_MODE_HANDSET,       APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_HANDSET));
    ASSERT_EQ(APP_VC_VOICE_MODE_HANDS_FREE,    APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_HANDS_FREE));
    ASSERT_EQ(APP_VC_VOICE_MODE_BUTT,          APP_VC_VcPhyVoiceMode2AppVcVoiceMode(VC_PHY_DEVICE_MODE_BLUETOOTH));

}

/*****************************************************************************
����     : Test_APP_VC_GetMuteStatus
�������� : Test_APP_VC_GetMuteStatus UT������
�޸���ʷ :
1.��   ��  : 2013-01-07
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_APP_VC_GetMuteStatus: public ::testing::Test
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
�����������      : Test_APP_VC_GetMuteStatus_001
������������      : ����Ϣͷ���͵�modem0��PID
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ          :
1.��   ��  : 2013-01-07
  ��   ��  : z00220246
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_GetMuteStatus, Test_APP_VC_GetMuteStatus_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    usClientId = AT_CLIENT_TAB_APP_INDEX;
    ucOpId = 1;
    pstAtClientCtx = AT_GetClientCtxAddr(usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;


    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(usClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(VOS_OK, APP_VC_GetMuteStatus(usClientId, ucOpId));
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

/*****************************************************************************
����     : Test_APP_VC_SetMuteStatus
�������� : Test_APP_VC_SetMuteStatus UT������
�޸���ʷ :
1.��   ��  : 2013-01-07
  ��   ��  : z00220246
  �޸����� : ��������
*****************************************************************************/
class Test_APP_VC_SetMuteStatus: public ::testing::Test
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
�����������      : Test_APP_VC_SetMuteStatus_001
������������      : ����Ϣͷ���͵�modem0��PID
Ԥ�ڽ��          : ����VOS_OK
�޸���ʷ          :
1.��   ��  : 2013-01-07
  ��   ��  : z00220246
  �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_APP_VC_SetMuteStatus, Test_APP_VC_SetMuteStatus_001)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    usClientId = AT_CLIENT_TAB_APP_INDEX;
    ucOpId = 1;
    enMuteStatus = 1;
    pstAtClientCtx = AT_GetClientCtxAddr(usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(usClientId),eq(I0_WUEPS_PID_VC))
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(VOS_OK, APP_VC_SetMuteStatus(usClientId, ucOpId,enMuteStatus));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

