

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"

#include "ATCmdProc.h"
#include "AtDeviceCmd.h"
#include "AtCheckFunc.h"
#include "mdrv.h"
#include "AtCmdMsgProc.h"

#include "phyoaminterface.h"

#include "AtInputProc.h"

#include "AtTestParaCmd.h"


//DTS2012041801532 w00182550 NV��һ�� start in 2012-04-12
#if(FEATURE_ON == FEATURE_LTE)
#include "LNvCommon.h"
#include "RrcNvInterface.h"
#include "msp_nvim.h"
#endif
/* DTS2012041801532 w00182550 NV��һ�� start in 2012-04-12 */

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

#if (FEATURE_ON==FEATURE_LTE)
#include "at_lte_common.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_DEVICECMD_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* �������ޱ�־�궨��˵��
#define CMD_TBL_E5_IS_LOCKED        (0x00000001)     ����E5�������Ƶ�����
#define CMD_TBL_PIN_IS_LOCKED       (0x00000002)     ����PIN���������Ƶ�����
#define CMD_TBL_IS_E5_DOCK          (0x00000004)     E5 DOCK����
#define CMD_TBL_CLAC_IS_INVISIBLE   (0x00000008)     +CLAC�����в������ʾ������
*/

VOS_UINT32                 g_ulNVRD = 0;
VOS_UINT32                 g_ulNVWR = 0;

AT_PAR_CMD_ELEMENT_STRU g_astAtDeviceCmdTbl[] = {
    {AT_CMD_GTIMER,
    AT_SetGTimerPara,    AT_NOT_SET_TIME,    AT_QryGTimerPara,      AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GTIMER",   (VOS_UINT8*)"(0-429496728)"},

    {AT_CMD_RSIM,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryRsimPara,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^RSIM",     VOS_NULL_PTR},

    {AT_CMD_PHYNUM,
    AT_SetPhyNumPara,    AT_NOT_SET_TIME,    AT_QryPhyNumPara,      AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHYNUM",   VOS_NULL_PTR},

    {AT_CMD_CSVER,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryCsVer,           AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CSVER",    VOS_NULL_PTR},

    {AT_CMD_QOS,
    At_SetQosPara,       AT_NOT_SET_TIME,    At_QryQosPara,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
   AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^QOS",      VOS_NULL_PTR},

    {AT_CMD_SDOMAIN,
    At_SetSDomainPara,   AT_NOT_SET_TIME,    At_QrySDomainPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SDOMAIN",  VOS_NULL_PTR},

    {AT_CMD_DPACAT,
    At_SetDpaCat,        AT_NOT_SET_TIME,    At_QryDpaCat,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DPACAT",   VOS_NULL_PTR},

    {AT_CMD_HSSPT,
    AT_SetHsspt  ,       AT_NOT_SET_TIME,    AT_QryHsspt,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HSSPT",    (VOS_UINT8*)"(0,1,2,6)"},

    {AT_CMD_PLATFORM,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryPlatForm,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PLATFORM", VOS_NULL_PTR},

    {AT_CMD_BSN,
    At_SetBsn,           AT_NOT_SET_TIME,    At_QryBsn,             AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^BSN",      VOS_NULL_PTR},

/* Modify by c00172979 for V7����ͬ��, 2012-04-13, Begin   */
#if ( FEATURE_ON == FEATURE_LTE )
/* Modify by c00172979 for V7����ͬ��, 2012-04-13, End   */
    {AT_CMD_SFM,
    At_SetSfm,          AT_SET_PARA_TIME,   At_QrySfm,            AT_NOT_SET_TIME,    VOS_NULL_PTR , AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SFM",     (VOS_UINT8*)"(0,1)"},
#endif

    {AT_CMD_TMODE,
    At_SetTModePara,     AT_SET_PARA_TIME,   At_QryTModePara,       AT_QRY_PARA_TIME ,  At_TestTmodePara , AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TMODE",    (VOS_UINT8*)"(0,1,2,3,4,11,12,13,14,15,16,17,18,19)"},

    /* DTS2012041801532 w00182550 NV��һ�� start in 2012-04-12 */
    {AT_CMD_FCHAN,
    At_SetFChanPara,     AT_SET_PARA_TIME,   At_QryFChanPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FCHAN_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FCHAN",    (VOS_UINT8*)"(0-7),(0-255),(0-65535)"},
    /* DTS2012041801532 w00182550 NV��һ�� end in 2012-04-12 */

    {AT_CMD_FTXON,
    At_SetFTxonPara,     AT_SET_PARA_TIME,   At_QryFTxonPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FTXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FTXON",    (VOS_UINT8*)"(0,1,2)"},

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
    {AT_CMD_FDAC,
    AT_SetFDac,          AT_SET_PARA_TIME,   AT_QryFDac,            AT_NOT_SET_TIME,    At_TestFdacPara , AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FDAC",     (VOS_UINT8*)"(0-65536)"},

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, End   */

    {AT_CMD_FRXON,
    At_SetFRxonPara,     AT_SET_PARA_TIME,   At_QryFRxonPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FRXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FRXON",    (VOS_UINT8*)"(0-1)"},

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
    {AT_CMD_FPA,
    At_SetFpaPara,       AT_SET_PARA_TIME,   At_QryFpaPara,         AT_NOT_SET_TIME,    VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FPA_OTHER_ERR  ,      CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPA",      (VOS_UINT8*)"(0-255)"},

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, End   */

    {AT_CMD_FLNA,
    At_SetFlnaPara,      AT_SET_PARA_TIME,   At_QryFlnaPara,        AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FLNA_OTHER_ERR  ,     CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FLNA",     (VOS_UINT8*)"(0-255)"},

    {AT_CMD_FRSSI,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryFrssiPara,       AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FRSSI",    VOS_NULL_PTR},

    {AT_CMD_MDATE,
    AT_SetMDatePara,     AT_NOT_SET_TIME,    AT_QryMDatePara,       AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^MDATE",    (VOS_UINT8*)"(@time)"},

    {AT_CMD_FACINFO,
    AT_SetFacInfoPara,   AT_NOT_SET_TIME,    AT_QryFacInfoPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FACINFO",  (VOS_UINT8*)"(0,1),(@valueInfo)"},


    {AT_CMD_SD,
    At_SetSD,            AT_NOT_SET_TIME,    At_QrySD,              AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_SD_CARD_OTHER_ERR ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SD",       (VOS_UINT8*)"(0-4),(0-429496728),(0-3)"},

    {AT_CMD_GPIOPL,
    At_SetGPIOPL,        AT_SET_PARA_TIME,   At_QryGPIOPL,          AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GPIOPL",   (VOS_UINT8*)"(@GPIOPL)"},

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
#if ( FEATURE_ON == FEATURE_LTE )
    /* DTS2012041801532 w00182550 NV��һ�� start in 2012-04-12 */
    {AT_CMD_GETEXBANDINFO,
    AT_SetExbandInfoPara,      AT_NOT_SET_TIME,  VOS_NULL_PTR,            AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GETEXBANDINFO",     (VOS_UINT8*)"(101-116)"},

    {AT_CMD_GETEXBANDTESTINFO,
    AT_SetExbandTestInfoPara,      AT_NOT_SET_TIME, VOS_NULL_PTR ,     AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GETEXBANDTESTINFO",      (VOS_UINT8*)"(101-116),(14,50,100,150,200)"},
    /* DTS2012041801532 w00182550 NV��һ�� end in 2012-04-12 */
    /* ����NV�ָ� */
    {AT_CMD_INFORRS,
    At_SetInfoRRS,       AT_SET_PARA_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^INFORRS",  VOS_NULL_PTR},
#endif
    /* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

#ifdef FEATURE_UPGRADE_TL
    {AT_CMD_INFORBU,
    atSetNVFactoryBack,  AT_SET_PARA_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^INFORBU",  VOS_NULL_PTR},
#else
    {AT_CMD_INFORBU,
    At_SetInfoRBU,       AT_SET_PARA_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^INFORBU",  VOS_NULL_PTR},
#endif

    {AT_CMD_DATALOCK,
    At_SetDataLock,      AT_SET_PARA_TIME,   At_QryDataLock,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DATALOCK", (VOS_UINT8*)"(@nlockCode)"},

    {AT_CMD_VERSION,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryVersion,         AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^VERSION",  VOS_NULL_PTR},



    {AT_CMD_SIMLOCK,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QrySimLockPlmnInfo, AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCK",  VOS_NULL_PTR},

    {AT_CMD_MAXLCK_TIMES,
    At_SetMaxLockTimes,  AT_SET_PARA_TIME,   At_QryMaxLockTimes,    AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^MAXLCKTMS",(VOS_UINT8*)"(0-429496728)"},

    {AT_CMD_CALLSRV,
    At_SetCallSrvPara,   AT_NOT_SET_TIME,    At_QryCallSrvPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CALLSRV",  (VOS_UINT8*)"(0,1)"},

    {AT_CMD_CSDFLT,
    At_SetCsdfltPara,    AT_NOT_SET_TIME,    At_QryCsdfltPara,      AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR,                       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CSDFLT",   (VOS_UINT8*)"(0,1)"},

    {AT_CMD_SECUBOOTFEATURE,
    VOS_NULL_PTR,    AT_NOT_SET_TIME,    At_QrySecuBootFeaturePara, AT_NOT_SET_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECUBOOTFEATURE",  (VOS_UINT8*)"(0,1)"},

    {AT_CMD_SECUBOOT,
    At_SetSecuBootPara,  AT_SET_PARA_TIME,    At_QrySecuBootPara,    AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECUBOOT", (VOS_UINT8*)"(0,1)"},

    {AT_CMD_TMMI,
    AT_SetTmmiPara,      AT_NOT_SET_TIME,    AT_QryTmmiPara,        AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TMMI",  (VOS_UINT8*)"(0,1)"},

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
    /* V7R1Ҫ��ʹ��"=?"��ѯ���ʹ��״̬ */
    {AT_CMD_TCHRENABLE,
    AT_SetChrgEnablePara,AT_NOT_SET_TIME,    AT_QryChrgEnablePara,  AT_NOT_SET_TIME,   AT_TestChrgEnablePara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TCHRENABLE",(VOS_UINT8*)"(0,1,4)"},
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/

    {AT_CMD_TCHRINFO,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryChrgInfoPara,    AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TCHRINFO",VOS_NULL_PTR},

    {AT_CMD_TSCREEN,
    AT_SetTestScreenPara,AT_NOT_SET_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TSCREEN",  (VOS_UINT8*)"(0-255),(0-255)"},

    {AT_CMD_BATVOL,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryBatVolPara,      AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TBATVOLT",  VOS_NULL_PTR},

    {AT_CMD_WUPWD,
    AT_SetWebPwdPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WUPWD",  (VOS_UINT8*)"(0,1),(@WUPWD)"},

    {AT_CMD_PRODTYPE,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryProdTypePara,    AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PRODTYPE",  VOS_NULL_PTR},

    {AT_CMD_FEATURE,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryFeaturePara,     AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SFEATURE",  VOS_NULL_PTR},

    {AT_CMD_PRODNAME,
    AT_SetProdNamePara,  AT_NOT_SET_TIME,    AT_QryProdNamePara,    AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PRODNAME",  (VOS_UINT8*)"(@ProductName)"},

    {AT_CMD_FWAVE,
    AT_SetFwavePara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FWAVE",  (VOS_UINT8*)"(0-7),(0-65535)"},

    {AT_CMD_EQVER,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryEqverPara,       AT_NOT_SET_TIME,   VOS_NULL_PTR,     AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^EQVER",  VOS_NULL_PTR},

    {AT_CMD_WIENABLE,
    AT_SetWiFiEnablePara, AT_NOT_SET_TIME, AT_QryWiFiEnablePara, AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIENABLE",(VOS_UINT8*)"(0,1,2)"},

    {AT_CMD_WIMODE,
    AT_SetWiFiModePara,   AT_NOT_SET_TIME, AT_QryWiFiModePara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIMODE",  (VOS_UINT8*)"(0,1,2,3,4)"},

    {AT_CMD_WIBAND,
    AT_SetWiFiBandPara,   AT_NOT_SET_TIME, AT_QryWiFiBandPara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIBAND",  (VOS_UINT8*)"(0,1)"},

    {AT_CMD_WIFREQ,
    AT_SetWiFiFreqPara,   AT_NOT_SET_TIME, AT_QryWiFiFreqPara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIFREQ",  (VOS_UINT8*)"(0-65535),(@offset)"},

    {AT_CMD_WIRATE,
    AT_SetWiFiRatePara,   AT_NOT_SET_TIME, AT_QryWiFiRatePara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIDATARATE",  (VOS_UINT8*)"(0-65535)"},

    /* Modified by L00171473 for DTS2012020106679,AT WT��λ 2012-01-17  Begin */
    {AT_CMD_WIPOW,
    AT_SetWiFiPowerPara,  AT_NOT_SET_TIME, AT_QryWiFiPowerPara,  AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIPOW",    (VOS_UINT8*)"(0-65535)"},
    /* Modified by L00171473 for DTS2012020106679,AT WT��λ 2012-01-17  End */

    {AT_CMD_WITX,
    AT_SetWiFiTxPara,     AT_NOT_SET_TIME, AT_QryWiFiTxPara,     AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WITX",     (VOS_UINT8*)"(0,1)"},

    {AT_CMD_WIRX,
    AT_SetWiFiRxPara,     AT_NOT_SET_TIME, AT_QryWiFiRxPara,     AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIRX",     (VOS_UINT8*)"(0,1),(@smac),(@dmac)"},

    {AT_CMD_WIRPCKG,
    AT_SetWiFiPacketPara, AT_NOT_SET_TIME, AT_QryWiFiPacketPara, AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIRPCKG",  (VOS_UINT8*)"(0)"},

    {AT_CMD_SSID,
    AT_SetWiFiSsidPara,   AT_NOT_SET_TIME, AT_QryWiFiSsidPara,   AT_NOT_SET_TIME, AT_TestSsidPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SSID",  (VOS_UINT8*)"(0-3),(@SSID)"},

    {AT_CMD_WIKEY,
    AT_SetWiFiKeyPara,    AT_NOT_SET_TIME, AT_QryWiFiKeyPara,    AT_NOT_SET_TIME, AT_TestWikeyPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIKEY",  (VOS_UINT8*)"(0-3),(@WIKEY)"},

    {AT_CMD_WILOG,
    AT_SetWiFiLogPara,    AT_NOT_SET_TIME, AT_QryWiFiLogPara,    AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WILOG",  (VOS_UINT8*)"(0,1),(@content)"},

    {AT_CMD_WIINFO,
    AT_SetWifiInfoPara,   AT_NOT_SET_TIME, VOS_NULL_PTR,         AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIINFO",  (VOS_UINT8*)"(0,1),(0,1)"},

    {AT_CMD_WIPARANGE,
    AT_SetWifiPaRangePara, AT_NOT_SET_TIME, AT_QryWifiPaRangePara, AT_NOT_SET_TIME, AT_TestWifiPaRangePara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIPARANGE",  (VOS_UINT8*)"(@gainmode)"},

    {AT_CMD_NVRD,
    AT_SetNVReadPara,     AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVRD",(VOS_UINT8*)"(0-65535)"},

    {AT_CMD_NVWR,
    AT_SetNVWritePara,    AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWR",(VOS_UINT8*)"(0-65535),(0-2048),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data)"},
    /* Added by ��ӳ��/f62575 for AT Project, SIM��������־ȷ��, 2011/11/15, begin */
	/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */

    {AT_CMD_NVWRPART,
    AT_SetNVWRPartPara,       AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWRPART",(VOS_UINT8*)"(0-65535),(0-2048),(0-2048),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data)"},


    {AT_CMD_CURC,
    At_SetCurcPara,      AT_NOT_SET_TIME,     At_QryCurcPara,     AT_QRY_PARA_TIME, VOS_NULL_PTR,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CURC", (VOS_UINT8*)"(0-2)"},
	/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
    /* Added by ��ӳ��/f62575 for AT Project, SIM��������־ȷ��, 2011/11/15, end */

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, Begin   */

    {AT_CMD_SN,
    At_SetSnPara,        AT_NOT_SET_TIME,    VOS_NULL_PTR,           AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_DEVICE_OTHER_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SN",       VOS_NULL_PTR},

    /* Modify by w00199382 for V7����ͬ��, 2012-04-07, End   */

    {AT_CMD_TBAT,
    AT_SetTbatPara,     AT_SET_PARA_TIME,   AT_QryTbatPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TBAT",    (VOS_UINT8 *)"(0,1),(0,1),(0-65535),(0-65535)"},

    {AT_CMD_PSTANDBY,
    AT_SetPstandbyPara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^PSTANDBY",    (VOS_UINT8 *)"(0-65535),(0-65535)"},

    {AT_CMD_WIWEP,
    AT_SetWiwepPara,        AT_SET_PARA_TIME,   AT_QryWiwepPara,  AT_QRY_PARA_TIME,  AT_TestWiwepPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^WIWEP",    (VOS_UINT8 *)"(0-3),(@wifikey),(0-3)"},

    {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"},

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
    {AT_CMD_TSELRF,
    AT_SetTseLrfPara,        AT_SET_PARA_TIME,   AT_QryTseLrfPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TSELRF",    (VOS_UINT8 *)"(0-255),(0-255)"},
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/

    {AT_CMD_HUK,
    AT_SetHukPara,              AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HUK",         (VOS_UINT8 *)"(@huk)"},

    {AT_CMD_FACAUTHPUBKEY,
    VOS_NULL_PTR,               AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FACAUTHPUBKEY",       (VOS_UINT8 *)"(@Pubkey)"},

    {AT_CMD_IDENTIFYSTART,
    AT_SetIdentifyStartPara,    AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^IDENTIFYSTART",       (VOS_UINT8 *)"(@Rsa)"},

    {AT_CMD_IDENTIFYEND,
    AT_SetIdentifyEndPara,      AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^IDENTIFYEND",       VOS_NULL_PTR},

    {AT_CMD_SIMLOCKDATAWRITE,
    VOS_NULL_PTR,               AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKDATAWRITE",    (VOS_UINT8 *)"(@SimlockData)"},

    {AT_CMD_PHONESIMLOCKINFO,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryPhoneSimlockInfoPara, AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHONESIMLOCKINFO",    VOS_NULL_PTR},

    {AT_CMD_SIMLOCKDATAREAD,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QrySimlockDataReadPara,  AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKDATAREAD",     VOS_NULL_PTR},

    {AT_CMD_PHONEPHYNUM,
    AT_SetPhonePhynumPara,  AT_SET_PARA_TIME,    AT_QryPhonePhynumPara,  AT_QRY_PARA_TIME,   AT_TestHsicCmdPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHONEPHYNUM",         (VOS_UINT8 *)"(@type),(@Phynum)"},

    {AT_CMD_PORTCTRLTMP,
    AT_SetPortCtrlTmpPara,          AT_SET_PARA_TIME,   AT_QryPortCtrlTmpPara,  AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PORTCTRLTMP",    (VOS_UINT8 *)"(@password)"},

    {AT_CMD_PORTATTRIBSET,
    AT_SetPortAttribSetPara,          AT_SET_PARA_TIME,   AT_QryPortAttribSetPara,  AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PORTATTRIBSET",    (VOS_UINT8 *)"(0,1),(@password)"},

    {AT_CMD_SIMLOCKUNLOCK,
    AT_SetSimlockUnlockPara, AT_SET_PARA_TIME,  VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_TestSimlockUnlockPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKUNLOCK",    (VOS_UINT8 *)"(\"NET\",\"NETSUB\",\"SP\"),(pwd)"},

    {AT_CMD_FPLLSTATUS,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryFPllStatusPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPLLSTATUS",     (VOS_UINT8 *)"(0,1),(0,1)"},

    {AT_CMD_FPOWDET,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryFpowdetTPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPOWDET",     VOS_NULL_PTR},

    {AT_CMD_NVWRSECCTRL,
    AT_SetNvwrSecCtrlPara,  AT_SET_PARA_TIME,   AT_QryNvwrSecCtrlPara,  AT_NOT_SET_TIME,   At_CmdTestProcOK,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWRSECCTRL",   (VOS_UINT8*)"(0-2),(@SecString)"},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {AT_CMD_MEID,
    AT_SetMeidPara,    AT_SET_PARA_TIME,    AT_QryMeidPara,    AT_SET_PARA_TIME,    VOS_NULL_PTR,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,    AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8 *)"^MEID",   (VOS_UINT8*)"(@number)"},
#endif

    {AT_CMD_MIPIWR,
    AT_SetMipiWrPara,  AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^MIPIWR",  (TAF_UINT8*)"(0-9),(0-15),(0-255),(0-65535),(0-3)"},/*mode, slave_id,  address, data,channel*/

   {AT_CMD_MIPIRD,
    AT_SetMipiRdPara,  AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^MIPIRD",  (TAF_UINT8*)"(0-9),(0-1),(0-15),(0-255)"},

   {AT_CMD_SSIWR,
    AT_SetSSIWrPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_QRY_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SSIWR",  (TAF_UINT8*)"(0-9),(0-1),(0-255),(0-65535)"}, /*mode, channel, address, data*/

    {AT_CMD_SSIRD,
    AT_SetSSIRdPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_QRY_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SSIRD",  (TAF_UINT8*)"(0-9),(0-1),(0-255)"},/*mode, channel, address*/



    {AT_CMD_SECURESTATE,
    AT_SetSecureStatePara,   AT_NOT_SET_TIME,   AT_QrySecureStatePara,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECURESTATE", (VOS_UINT8*)"(0-2)"},

    {AT_CMD_KCE,
    AT_SetKcePara,   AT_NOT_SET_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^KCE", (VOS_UINT8*)"(@KceString)"},

    {AT_CMD_SOCID,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,   AT_QrySocidPara,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SOCID", (VOS_UINT8*)"(@SocidString)"}

};


/* ʾ��: ^CMDX �����ǲ���E5���뱣���������+CLAC�о���������ʱ����ʾ����һ�������ǲ���˫���ŵ��ַ���,
        �ڶ��������Ǵ�˫���ŵ��ַ����������������������Ͳ���

   !!!!!!!!!!!ע��: param1��param2��ʾ����ʵ�ʶ�������ʱӦ��������ļ��(����߽���Ч��)!!!!!!!!!!!!!

    {AT_CMD_CMDX,
    At_SetCmdxPara, AT_SET_PARA_TIME, At_QryCmdxPara, AT_QRY_PARA_TIME, At_TestCmdxPara, AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_E5_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE,
    (VOS_UINT8*)"^CMDX", (VOS_UINT8*)"(@param1),(param2),(0-255)"},
*/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : At_TestTmodePara
 ��������  : TMODE���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_TestTmodePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "%s: %d",
                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                  g_stAtDevCmdCtrl.ucCurrentTMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 �� �� ��  : At_TestFdacPara
 ��������  : FDAC���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_TestFdacPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength  = 0;

    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: (0-2047)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: (0-1023)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 �� �� ��  : At_RegisterDeviceCmdTable
 ��������  : ע��װ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��21��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_RegisterDeviceCmdTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtDeviceCmdTbl, sizeof(g_astAtDeviceCmdTbl)/sizeof(g_astAtDeviceCmdTbl[0]));
}


/*****************************************************************************
 �� �� ��  : AT_TestSsidPara
 ��������  : SSID��������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��17��
    ��    ��   : z60575
    �޸�����   : MULTI_SSID�޸�
*****************************************************************************/
VOS_UINT32 AT_TestSsidPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    AT_WIFI_MAX_SSID_NUM);
    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestWikeyPara
 ��������  : WIKEY��������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestWikeyPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    AT_WIFI_KEY_NUM);
    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SetTbatPara
 ��������  : ^TBAT��������
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��FEATURE_CHARGE��

*****************************************************************************/
VOS_UINT32 AT_SetTbatPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_LTE)
    return atSetTBATPara(ucIndex);

#else
    AT_TBAT_OPERATION_DIRECTION_ENUM_UINT32 enTbatOperdirection;
    AT_TBAT_BATTERY_ADC_INFO_STRU           stAdcInfo;
    VOS_UINT32                              ulRet;

    /* ������Ч�Լ�� */
    /* ^TBAT���������������ٴ�2������: �������ͺͷ��� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ^TBAT������������������:
       ���ֵ�ص�ѹ���ò���������3.7V��Ӧ��HKADCֵ��4.2V��Ӧ��HKADCֵ
       ���ֵ�ص�ѹ��ѯ������<value1>��<value2>����
      */

    /* V3R2-��֧�ֵ��ģ���ѹ */
    if (AT_TBAT_BATTERY_ANALOG_VOLTAGE == gastAtParaList[0].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    enTbatOperdirection = gastAtParaList[1].ulParaValue;
    if (AT_TBAT_READ_FROM_UUT == enTbatOperdirection)
    {
        if (2 != gucAtParaIndex)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        if ((4 != gucAtParaIndex)
         || (0 == gastAtParaList[2].usParaLen)
         || (0 == gastAtParaList[3].usParaLen))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    if (AT_TBAT_READ_FROM_UUT == enTbatOperdirection)
    {
        /* ���õ���ӿڻ�ȡ������ֵ�ѹ */
        if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                 gastAtClientTab[ucIndex].opId,
                                                 DRV_AGENT_HKADC_GET_REQ,
                                                 VOS_NULL_PTR,
                                                 0,
                                                 I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBAT_SET;     /*���õ�ǰ����ģʽ */
            return AT_WAIT_ASYNC_RETURN;                                                       /* �ȴ��첽�¼����� */
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* д���������У׼�õ�NV��90 en_NV_Item_BATTERY_ADC */
        stAdcInfo.usMinAdc = (VOS_UINT16)gastAtParaList[2].ulParaValue;
        stAdcInfo.usMaxAdc = (VOS_UINT16)gastAtParaList[3].ulParaValue;
        ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_BATTERY_ADC, &stAdcInfo, sizeof(stAdcInfo));
        if (NV_OK != ulRet)
        {
             AT_WARN_LOG("AT_SetTbatPara: Fail to write NV en_NV_Item_BATTERY_ADC.");
             return AT_ERROR;
        }

        return AT_OK;
    }
#endif
    /*
    ���ݲ�����ͬ������������:
    1.  ֧���û�����AT^TBAT=1,0��ȡ��ص�ѹ����ֵ��
    ���õ���/OM�ӿڻ�ȡ�������ֵ
    2.  ֧���û�����AT^TBAT=1,1,<value1>,<value2>���õ�ص�ѹ����ֵ�����ڵ��У׼��
    дУ׼��ѹ��NVID 90(en_NV_Item_BATTERY_ADC)���˴������ʴ�ȷ�ϣ�
    en_NV_Item_BATTERY_ADC�м�¼������������ֵ����AT�����һ�����������ӳ��
    3.4V ��ѹ��Ӧ��ADCֵ
    4.2V ��ѹ��Ӧ��ADCֵ
    */
}

/*****************************************************************************
 �� �� ��  : AT_QryTbatPara
 ��������  : ^TBAT��ѯ������ڻ�ȡ��صİ�װ��ʽ
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_QryTbatPara(VOS_UINT8 ucIndex)
{
    /*
    ���õ���ӿڻ�ȡ��ذ�װ��ʽ:
    <mount type> ��ذ�װ��ʽ
    0 �޵��
    1 �ɸ������
    2 ����һ�廯���
    */
    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               DRV_AGENT_TBAT_QRY_REQ,
                                               VOS_NULL_PTR,
                                               0,
                                               I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBAT_QRY;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                                              /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SetPstandbyPara
 ��������  : ���õ�����뵽����״̬��
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��2��21��
    ��    ��   : w00199382
    �޸�����   : B060��Ŀ���ӵ�����ؽӿڵ���
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ :ɾ�����Ժ�
  4.��    ��   : 2012��04��13��
    ��    ��   : f62575
    �޸�����   : V7����ͬ��: ɾ��WIFI_POWER_SHUTDOWN��oledPwrOff��DRV_PWRCTRL_USB_LOWPOWER_ENTER�ĵ��ã�
                        �滻ΪDRV_PWRCTRL_STANDBYSTATEACPU (BSP_PWRCTRL_StandbyStateAcpu)
  5.��    ��   : 2014��2��14��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:���ػ���������
*****************************************************************************/
VOS_UINT32 AT_SetPstandbyPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_PSTANDBY_REQ_STRU         stPstandbyInfo;

#ifdef FEATURE_UPGRADE_TL

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */

#endif

    /* ^PSTANDBY�����������ҽ���2������: �������״̬��ʱ�䳤�Ⱥ͵���������״̬���л�ʱ�� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (2 != gucAtParaIndex))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    At_FormatResultData(ucIndex, AT_OK); /*��Ҫ�Ȼظ�OK*/

    /*��֤�������ݷ������*/
    VOS_TaskDelay(10);

    /*
    ���õ����OM�ӿ�ʹ����������״̬:
    ACPU����ɵĲ�����
    1���µ�WIFI
    2��LED�µ�
    3��USB PowerOff

    ����Ϣ��C�ˣ�ָʾCCPU����ɵĲ�����
    1��ͨ��ģ���µ�
    2���ض�ʱ��
    3�����ж�
    4�����õ���ӿڽ�����˯
    */
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    stPstandbyInfo.ulStandbyTime = gastAtParaList[0].ulParaValue;
    stPstandbyInfo.ulSwitchTime   = gastAtParaList[1].ulParaValue;

    DRV_PWRCTRL_STANDBYSTATEACPU(stPstandbyInfo.ulStandbyTime, stPstandbyInfo.ulSwitchTime);

    /*������Ϣ��c��*/
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                           gastAtClientTab[ucIndex].opId,
                           DRV_AGENT_PSTANDBY_SET_REQ,
                           &stPstandbyInfo,
                           sizeof(stPstandbyInfo),
                           I0_WUEPS_PID_DRV_AGENT))
    {
        AT_ERR_LOG("AT_SetPstandbyPara: AT_FillAndSndAppReqMsg fail.");
    }

    /* V7R2���ùػ�����͹����������� */
#ifdef FEATURE_UPGRADE_TL

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
    stPhoneModePara.PhMode = TAF_PH_MODE_MINI;

    if (VOS_TRUE == TAF_MMA_PhoneModeSetReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPhoneModePara))
    {
        /* Modified by zwx247453 for pc����ת3650, 2015-08-24, begin */
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_PSTANDBY_SET;
        /* Modified by zwx247453 for pc����ת3650, 2015-08-24, end */

        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */
#endif

    return AT_SUCCESS;
}

/* DTS2012041801532 w00182550 NV��һ�� start in 2012-04-12 */
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32 AT_SetExbandInfoPara(VOS_UINT8 ucIndex)
{
    LTE_COMM_NON_STANDARD_BAND_COMM_STRU stLpsNonstandBand = {0};
    VOS_UINT32 ulRet  = AT_OK;
    VOS_UINT32 ulNvId = 0;

    /* 1��AT���������Ƿ���ȷ */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2�����������Ƿ����Ҫ�� */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulNvId = gastAtParaList[0].ulParaValue -LTE_COMM_NONSTANDARD_BAND_BEGIN  + EN_NV_ID_BANDNon1_BAND_INFO  ;
    if((ulNvId < EN_NV_ID_BANDNon1_BAND_INFO )||(ulNvId > EN_NV_ID_BANDNon16_BAND_INFO))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = NVM_Read(ulNvId, (VOS_VOID*) &stLpsNonstandBand, sizeof(LTE_COMM_NON_STANDARD_BAND_COMM_STRU));
     if(  NV_OK != ulRet)
     {
        (VOS_VOID)vos_printf("read non stand band nv fail,ulNvId = %d,ulRet = %d!\n",ulNvId,ulRet);
        return AT_ERROR;
     }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:BANDNO:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.ucBandID);


    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                     "%s:DUPLEX:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.enBandMode);

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:FREQ:%d,%d,%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUlFreqInfo.usFLow,
                                                    stLpsNonstandBand.stUlFreqInfo.usFHigh,
                                                    stLpsNonstandBand.stDlFreqInfo.usFLow,
                                                    stLpsNonstandBand.stDlFreqInfo.usFHigh
                                                 );

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:CHANNUM:%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUlFreqInfo.usRangOfNLow,
                                                    stLpsNonstandBand.stDlFreqInfo.usRangOfNLow);

     return AT_OK;
}

VOS_UINT32 AT_SetExbandTestInfoPara(VOS_UINT8 ucIndex)
{
    LTE_COMM_NON_STANDARD_BAND_COMM_STRU stLpsNonstandBand = {0};
    VOS_UINT32 ulRet  = AT_OK;
    VOS_UINT32 ulNvId = 0,ulArrayID=0 ,i=0;

    VOS_UINT32 BandWidthArray[BAND_WIDTH_NUMS]= {14,30,50,100,150,200};

    /* 1��AT���������Ƿ���ȷ */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2�����������Ƿ����Ҫ�� */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulNvId = gastAtParaList[0].ulParaValue -LTE_COMM_NONSTANDARD_BAND_BEGIN  + EN_NV_ID_BANDNon1_BAND_INFO  ;

    if((ulNvId  < EN_NV_ID_BANDNon1_BAND_INFO ) ||(ulNvId > EN_NV_ID_BANDNon16_BAND_INFO))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = NVM_Read(ulNvId, (VOS_VOID*) &stLpsNonstandBand, sizeof(LTE_COMM_NON_STANDARD_BAND_COMM_STRU));

    if(  NV_OK != ulRet)
    {
        (VOS_VOID)vos_printf("read non stand band nv fail,ulRet = %d!\n",ulRet);
        return AT_ERROR;
    }

    ulArrayID = BandWidthArray[BAND_WIDTH_NUMS -1];

    for(i = 0 ; i < BAND_WIDTH_NUMS; i++)
    {
        if( BandWidthArray[i] == gastAtParaList[1].ulParaValue)
        {
            ulArrayID = i;
            break;
        }
    }

    gstAtSendData.usBufLen = 0 ;

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                     "%s:FREQS:%d,%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[0],
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[1],
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[2]);

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:MAXPOWTOLERANCE:%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUePowerClassInfo.sPowerToleranceHigh,
                                                    stLpsNonstandBand.stUePowerClassInfo.sPowerToleranceLow
                                                 );

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:REFSENSPOW:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stLpsNonstandBand.stTestInfo[ulArrayID].sRxRefSensPower);
      return AT_OK;
}
#endif
/* DTS2012041801532 w00182550 NV��һ�� end in 2012-04-12 */

/*****************************************************************************
 �� �� ��  : AT_WriteWiWep
 ��������  : дWIFI KEY��NV��
 �������  : VOS_UINT32                          ulIndex        WIFI KEY��NV���е�����
             VOS_UINT32                          ulWiWepLen     WIFI KEY����
             VOS_UINT8                           aucWiWep[]     WIFI KEY����
             AT_WIFI_SEC_STRU                   *pstWifiSecInfo WIFI KEY����NV�����ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��6��
    ��    ��   : l60609
    �޸�����   : DTS20120033007015:����NV50012�Ľṹ���ֽڶ���
*****************************************************************************/
VOS_UINT32 AT_WriteWiWep(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           aucWiWep[],
    VOS_UINT16                          usWiWepLen,
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo,
    VOS_UINT8                           ucGroup
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                          *paucWifiWepKey;

    /* ��Ϊ���޸�en_NV_Item_WIFI_KEY�е�WIFI KEY���������Ҫ�Ȼ�ȡȫ��NVֵ��Ȼ������޸Ĳ��� */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_WriteWiWep: Fail to read en_NV_Item_WIFI_KEY.");
        return AT_ERROR;
    }

    /* ����index��ȡNV�б�������� */
    paucWifiWepKey = ((0 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey1[ucGroup] :
                      ((1 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey2[ucGroup] :
                      ((2 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey3[ucGroup] : pstWifiSecInfo->aucWifiWepKey4[ucGroup])));

    /* �ж��µ�WIFI KEY��NV�м�¼���Ƿ�һ�� */
    for (ulLoop = 0; ulLoop < AT_NV_WLKEY_LEN; ulLoop++)
    {
        if (paucWifiWepKey[ulLoop] != aucWiWep[ulLoop])
        {
            break;
        }
    }

    /* �ж��µ�WIFI KEY��NV�м�¼��һ����ֱ�ӷ��ز������*/
    if (AT_NV_WLKEY_LEN == ulLoop)
    {
        return AT_OK;
    }

    /* �������ݵ�NV��en_NV_Item_WIFI_KEY */
    PS_MEM_SET(paucWifiWepKey, 0, AT_NV_WLKEY_LEN);

    PS_MEM_CPY(paucWifiWepKey, aucWiWep, usWiWepLen);

    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
         AT_WARN_LOG("AT_WriteWiWep: Fail to write NV en_NV_Item_WIFI_KEY.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetWiwepPara
 ��������  : ����ָ��INDEX��WiFi WEP��WIFI��KEY������
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��6��
    ��    ��   : l60609
    �޸�����   : DTS20120033007015:����NV50012�Ľṹ���ֽڶ���

  3.��    ��   : 2012��9��17��
    ��    ��   : z60575
    �޸�����   : MULTI_SSID�޸�
*****************************************************************************/
VOS_UINT32 AT_SetWiwepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucGroup;
    VOS_UINT32                          ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ����������: ���ҽ���< index >��< content >�������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (0 == gastAtParaList[2].usParaLen))
    {
        return AT_ERROR;
    }

    /* WIFI key ������DATALOCK���� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }

    /* < index >������0-3��Χ�ڣ�< content >����С��NV_WLKEY_LEN */
    ulIndex = gastAtParaList[0].ulParaValue;
    if (ulIndex > AT_WIWEP_CARD_WIFI_KEY_TOTAL)
    {
        return AT_ERROR;
    }

    if (gastAtParaList[1].usParaLen > AT_NV_WLKEY_LEN)
    {
        return AT_ERROR;
    }

    ucGroup = (VOS_UINT8)gastAtParaList[2].ulParaValue;

    if (ucGroup >= AT_WIFI_MAX_SSID_NUM)
    {
        return AT_ERROR;
    }

    /* ��װWIFI KEY��NV�ṹ���������ݵ�NV��en_NV_Item_WIFI_KEY */
    pstWifiSecInfo = (TAF_AT_MULTI_WIFI_SEC_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                  sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (VOS_NULL_PTR == pstWifiSecInfo)
    {
        return AT_ERROR;
    }

    ulRet = AT_WriteWiWep(ulIndex,
                          gastAtParaList[1].aucPara,
                          gastAtParaList[1].usParaLen,
                          pstWifiSecInfo,
                          ucGroup);

    PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : AT_QryWiwepPara
 ��������  : WIFI KEY��Ϣ��ѯ
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��6��
    ��    ��   : l60609
    �޸�����   : DTS20120033007015:����NV50012�Ľṹ���ֽڶ���
  3.��    ��   : 2012��9��17��
    ��    ��   : z60575
    �޸�����   : MULTI_SSID�޸�
*****************************************************************************/
VOS_UINT32 AT_QryWiwepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo;
    VOS_UINT8                           aucWifiWepKey[AT_NV_WLKEY_LEN + 1];
    VOS_UINT8                           aucWepKeyLen1[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen2[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen3[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen4[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           ucWepKeyNum;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* Ϊ��ȡWIFI KEY�����ڴ棬��NV��en_NV_Item_WIFI_KEY��ȡWIFI KEY��Ϣ */
    pstWifiSecInfo = (TAF_AT_MULTI_WIFI_SEC_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                      sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (VOS_NULL_PTR == pstWifiSecInfo)
    {
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryWiwepPara: Fail to read en_NV_Item_WIFI_KEY.");
        PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);
        return AT_ERROR;
    }

    ucWepKeyNum = 0;
    PS_MEM_SET(aucWepKeyLen1, 0, sizeof(aucWepKeyLen1));
    PS_MEM_SET(aucWepKeyLen2, 0, sizeof(aucWepKeyLen2));
    PS_MEM_SET(aucWepKeyLen3, 0, sizeof(aucWepKeyLen3));
    PS_MEM_SET(aucWepKeyLen4, 0, sizeof(aucWepKeyLen4));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        /* KEY1��Ӧ��NV���ձ�ʾKEY1��Ч */
        aucWepKeyLen1[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey1[ulLoop]);
        if (0 != aucWepKeyLen1[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen2[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey2[ulLoop]);
        if (0 != aucWepKeyLen2[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen3[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey3[ulLoop]);
        if (0 != aucWepKeyLen3[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen4[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey4[ulLoop]);
        if (0 != aucWepKeyLen4[ulLoop])
        {
            ucWepKeyNum++;
        }
    }

    /* δ����ʱ����Ҫ�����Ѷ���0�� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        ucWepKeyNum = 0;
        PS_MEM_SET(aucWepKeyLen1, 0, sizeof(aucWepKeyLen1));
        PS_MEM_SET(aucWepKeyLen2, 0, sizeof(aucWepKeyLen2));
        PS_MEM_SET(aucWepKeyLen3, 0, sizeof(aucWepKeyLen3));
        PS_MEM_SET(aucWepKeyLen4, 0, sizeof(aucWepKeyLen4));
    }

    /*
    ���㹤λ�Խ�Ҫ����Ҫ�����λ֧�ֵ�ȫ����20��WiFi WEP��WIFI��KEY��
    ��ӡ���鵥��֧�ֵ�WIFI KEY��Ϣ
    ���16��^WIWEP: <index>,�빤λҪ���20����WiFi WEP��WIFI��KEY��һ�£�
    */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s:%d%s",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     ucWepKeyNum,
                                     gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucWepKeyLen1[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey1[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              0,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen2[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey2[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              1,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen3[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey3[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              2,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen4[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey4[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              3,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength - (VOS_UINT16)VOS_StrLen((VOS_CHAR *)gaucAtCrLf);

    PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestWiwepPara
 ��������  : WIWEP�Ĳ�����������λ֧�ֵ�WIFI KEY����
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestWiwepPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   AT_WIWEP_TOOLS_WIFI_KEY_TOTAL);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestWifiPaRangePara
 ��������  : AT^WIPARANGE���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��02��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucWifiMode;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ��ʼ�� */
    ucWifiMode                          = (VOS_UINT8)WIFI_GET_PA_MODE();

    /* ��ѯ����֧�ֵ�ģʽ�����ֻ֧��PAģʽ��û��NO PAģʽ����ֻ����h���ɣ��������ģʽ��֧�֣��򷵻�h,l��*/
    if (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "h");
    }
    else if (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "l");
    }
    else if (AT_WIFI_MODE_PA_NOPA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "h,l");
    }
    else
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_GetTseLrfLoadDspInfo
 ��������  : ^TSELRF�����Ƿ񴥷�LOAD DSP
 �������  : AT_TSELRF_PATH_ENUM_UINT32          enPath     ��Ƶͨ·���
             VOS_BOOL                           *pbLoadDsp  �Ƿ񴥷�LOAD DSP
                     VOS_FALSE                              ������LOAD DSP����
                     VOS_TRUE                               ����LOAD DSP����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��01��16��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(load mode �޸�)

*****************************************************************************/
VOS_VOID AT_GetTseLrfLoadDspInfo(
    AT_TSELRF_PATH_ENUM_UINT32          enPath,
    VOS_BOOL                           *pbLoadDsp,
    DRV_AGENT_TSELRF_SET_REQ_STRU      *pstTseLrf
)
{
    /* ^TSELRF�������õ���Ƶͨ·���ΪGSM�ҵ�ǰ�Ѿ�LOAD�˸�ͨ·������LOAD */
    if (AT_TSELRF_PATH_GSM == enPath)
    {
        if ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
         && (VOS_TRUE == g_stAtDevCmdCtrl.bDspLoadFlag))
        {
            *pbLoadDsp = VOS_FALSE;
        }
        else
        {
            pstTseLrf->ucLoadDspMode     = VOS_RATMODE_GSM;
            pstTseLrf->ucDeviceRatMode   = AT_RAT_MODE_GSM;
            *pbLoadDsp                   = VOS_TRUE;
        }
        return;
    }

    /* ^TSELRF�������õ���Ƶͨ·���ΪWCDMA�����ҵ�ǰ�Ѿ�LOAD�˸�ͨ·������LOAD */
    if (AT_TSELRF_PATH_WCDMA_PRI == enPath)
    {
        if (((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
          || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
         && (VOS_TRUE == g_stAtDevCmdCtrl.bDspLoadFlag))
        {
            *pbLoadDsp = VOS_FALSE;
        }
        else
        {
            pstTseLrf->ucLoadDspMode     = VOS_RATMODE_WCDMA;
            pstTseLrf->ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
            *pbLoadDsp                   = VOS_TRUE;
        }
        return;
    }

    *pbLoadDsp = VOS_FALSE;

    AT_WARN_LOG("AT_GetTseLrfLoadDspInfo: enPath only support GSM or WCDMA primary.");

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetTseLrfPara
 ��������  : ^TSELRF�����ò���
 �������  : VOS_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ����ִ�н���ɹ�����Ӧ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��21��
    ��    ��   : f62575
    �޸�����   : V7����ͬ��: ����PATH��������
  3.��    ��   : 2012��05��04��
    ��    ��   : f62575
    �޸�����   : DTS2012040600347��֧������ּ���򿪽��ջ�����װ������
  4.��    ��   : 2012��05��05��
    ��    ��   : f62575
    �޸�����   : DTS2012050502003�����V7�汾AT^TSELRF=1��������Ӧ����

*****************************************************************************/
VOS_UINT32 AT_SetTseLrfPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;
    VOS_BOOL                            bLoadDsp;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
#if (FEATURE_ON == FEATURE_LTE)
    if ((AT_TSELRF_PATH_WCDMA_PRI!=gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_WCDMA_DIV!=gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_GSM !=gastAtParaList[0].ulParaValue))
    {
        return atSetTselrfPara(ucIndex);
    }
#endif
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_TSELRF_PATH_TD == gastAtParaList[0].ulParaValue)
    {
        return atSetTselrfPara(ucIndex);
    }

#endif
    /* ����������Ҫ�� */
    if ((1 != gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    if (AT_TSELRF_PATH_WIFI == gastAtParaList[0].ulParaValue)
    {
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if ( BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
        {
            /*WIFIδEnableֱ�ӷ���ʧ��*/
            if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
            {
                return AT_ERROR;
            }

            g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WIFI;

            return AT_OK;
        }
        else
        {
            return AT_ERROR;
        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_ERROR;
    }

    /* �򿪷ּ�������FRXON֮�󣬲ο�RXDIVʵ�� */
    if (AT_TSELRF_PATH_WCDMA_DIV == gastAtParaList[0].ulParaValue)
    {
        if (DRV_AGENT_DSP_RF_SWITCH_ON != g_stAtDevCmdCtrl.ucRxOnOff)
        {
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
            return AT_OK;
        }

        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON))
        {
            return AT_ERROR;
        }

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TSELRF_SET;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }

    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    if ((AT_TSELRF_PATH_GSM != gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_WCDMA_PRI != gastAtParaList[0].ulParaValue))
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    /* �˴��ж��Ƿ���Ҫ���¼���DSP: ��Ҫ������C�˼���DSP������ֱ�ӷ���OK */
    AT_GetTseLrfLoadDspInfo(gastAtParaList[0].ulParaValue, &bLoadDsp, &stTseLrf);
    if (VOS_TRUE == bLoadDsp)
    {
        if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                   gastAtClientTab[ucIndex].opId,
                                                   DRV_AGENT_TSELRF_SET_REQ,
                                                   &stTseLrf,
                                                   sizeof(stTseLrf),
                                                   I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TSELRF_SET;             /*���õ�ǰ����ģʽ */
            return AT_WAIT_ASYNC_RETURN;                                           /* �ȴ��첽�¼����� */
        }
        else
        {
            return AT_ERROR;
        }
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_QryTseLrfPara
 ��������  : ��ѯ�����������ص���֧�ֵ����������ÿ�����������ʾ��ÿ��<path>
             ����ֻ��ʾһ�У�
             ������˵����֧��2��WIFI���ߣ�����ʾΪ��^TSELRF: 7,0,1��
 �������  : VOS_UINT8 ucIndex �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ����ִ�н���ɹ�����Ӧ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_QryTseLrfPara(VOS_UINT8 ucIndex)
{

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
#if(FEATURE_LTE == FEATURE_ON)
    return atQryTselrfPara(ucIndex);
#else
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_TSELRF_PATH_TOTAL,
                                      gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s:%d%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_TSELRF_PATH_GSM,
                                      gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s:%d%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_TSELRF_PATH_WCDMA_PRI,
                                      gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s:%d%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_TSELRF_PATH_WCDMA_DIV,
                                      gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_TSELRF_PATH_WIFI);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif

}

/*****************************************************************************
 �� �� ��  : AT_SetCmdlenPara
 ��������  : ��֪����PCһ���������͵��ַ�������PC��������һ�η��͵��ַ�����
             ����������֧��SIMLOCK���ݵķֶη��ͣ�BALONG�޴����󣬽�����OK��֤��
             λ��һ����������ִ��
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetCmdlenPara(VOS_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (2 != gucAtParaIndex))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[0].ulParaValue > (AT_COM_BUFF_LEN - sizeof("AT")))
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_QryCmdlenPara
 ��������  : ��ѯ����������ֱ�ӽ���AT�����ַ��������Լ�����ͨ��ATһ�����
             ������Ӧ���ַ����������ַ�������������AT�������ַ���
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_QryCmdlenPara(VOS_UINT8 ucIndex)
{
    /*
      �������������ֱ�ӽ���AT�����ַ�����(AT_CMD_MAX_LEN - sizeof("AT"))��
      ���ַ�������������AT�������ַ����Լ�����ͨ��ATһ����������Ӧ���ַ�������
      BALONG��Ʒ��Ӧ�ַ������ȿ��Է�
      ����ϱ���û�����ֵ�����λ�Ը�ֵ�޴����˴����һ���ϱ������ֵAT_CMD_MAX_LEN��
    */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (AT_COM_BUFF_LEN - VOS_StrLen("AT")),
                                                    AT_CMD_MAX_LEN);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_UpdateMacPara
 ��������  : ����MAC��ַ��NV
             �Ƿ�֧��2��MAC��ȷ�ϣ�
 �������  : VOS_UINT8                           aucMac[]   MAC��ַ�ַ����׵�ַ
             VOS_UINT16                          usMacLength    MAC��ַ�ַ�������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             �����ɹ�������AT_OK
             ����ų��Ȳ��Ϸ�����AT_PHYNUM_LENGTH_ERR
             MT�ڲ����󣬷���AT_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_UpdateMacPara(
    VOS_UINT8                           aucMac[],
    VOS_UINT16                          usMacLength
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulWifiGlobalMacOffset;
    VOS_UINT32                          ulPhyNumMacOffset;
    VOS_UINT8                           aucWifiGlobalMac[AT_MAC_ADDR_LEN];

    /* MAC��ַ���ȼ��: ����12λ */
    if (AT_PHYNUM_MAC_LEN != usMacLength)
    {
        return AT_PHYNUM_LENGTH_ERR;
    }

    /* MAC��ַ��ʽƥ��: 7AFEE22111E4=>7A:FE:E2:21:11:E4*/
    ulWifiGlobalMacOffset = 0;
    ulPhyNumMacOffset     = 0;
    for (ulLoop = 0; ulLoop < (AT_PHYNUM_MAC_COLON_NUM + 1); ulLoop++)
    {
        PS_MEM_CPY(&aucWifiGlobalMac[ulWifiGlobalMacOffset],
                   &aucMac[ulPhyNumMacOffset],
                   AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulWifiGlobalMacOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulPhyNumMacOffset     += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        aucWifiGlobalMac[ulWifiGlobalMacOffset] = ':';
        ulWifiGlobalMacOffset++;
    }

    aucWifiGlobalMac[AT_PHYNUM_MAC_LEN + AT_PHYNUM_MAC_COLON_NUM] = '\0';

    /* ����MAC��ַ��NV */
    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucWifiGlobalMac, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
         AT_WARN_LOG("AT_UpdateMacPara: Fail to write NV.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetTmodeAutoPowerOff
 ��������  : �Զ��ػ���װ�������E5��Ʒ��̬֧�֣�������Ʒ��̬����ERROR
             ����Ҫ����֪ͨ�û�AT������ִ�У�������ߵ�ʱЧ����
             �û�ͨ�����˿��Ƿ���ʧ��ȷ�������Ƿ���ȷִ��
 �������  : VOS_UINT8 ucIndex      �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2014��2��14��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:���ػ���������
*****************************************************************************/
VOS_UINT32 AT_SetTmodeAutoPowerOff(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhModeSet;
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */

    VOS_UINT8                             *pucSystemAppConfig;


    PS_MEM_SET(&stPhModeSet, 0x00, sizeof(TAF_PH_OP_MODE_STRU));

    pucSystemAppConfig                    = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* ����Ϣ��C��֪ͨ�ػ����µ� */
        /* ��֪ͨ�û�AT������ִ�У��û�ͨ�����˿��Ƿ���ʧ��ȷ�������Ƿ���ȷִ��
           ������ִ����ɺ����µ磬����ȴ��첽����
        */

        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
        stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;

        if (VOS_TRUE == TAF_MMA_PhoneModeSetReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPhModeSet))
        {
            return AT_OK;
        }
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */
        else
        {
            return AT_ERROR;
        }

    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    return AT_ERROR;

}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */

/*****************************************************************************
 �� �� ��  : AT_SDParamErrCode
 ��������  : SD����������󷵻ش�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��19��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SDParamErrCode(VOS_VOID)
{
    if(0 == g_stATParseCmd.ucParaCheckIndex)
    {
        return AT_SD_CARD_OPRT_NOT_ALLOWED;
    }
    else if(1 == g_stATParseCmd.ucParaCheckIndex)
    {
        return AT_SD_CARD_ADDR_ERR;
    }
    else
    {
        return AT_SD_CARD_OTHER_ERR;
    }
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

/*****************************************************************************
 �� �� ��  : AT_GetSpecificPort
 ��������  : ��ȡָ�����͵Ķ˿�
 �������  : VOS_UINT8                           ucPortType �˿�����
 �������  : VOS_UINT32                         *pulPortPos �˿���NV���е�ƫ��
             VOS_UINT32                         *pulPortNum NV���еĶ˿�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_GetSpecificPort(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           aucRewindPortStyle[],
    VOS_UINT32                         *pulPortPos,
    VOS_UINT32                         *pulPortNum
)
{
    VOS_UINT32                          ulLoop;

    *pulPortPos = AT_DEV_NONE;
    for (ulLoop = 0; ulLoop < AT_SETPORT_PARA_MAX_LEN; ulLoop++)
    {
        if (0 == aucRewindPortStyle[ulLoop])
        {
            break;
        }

        /* �˿�ֵΪucPortType����ʾ�ҵ�ָ���˿ڣ���¼ulLoopΪ�˿���NV���е�ƫ�� */
        if (ucPortType == aucRewindPortStyle[ulLoop])
        {
            *pulPortPos = ulLoop;
        }
    }

    /* �˿�ֵΪ0�򵽴�ѭ�����ޣ�ulLoop��Ϊ����Ķ˿����� */
    *pulPortNum = ulLoop;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ExistSpecificPort
 ��������  : �Ƿ����ָ�����͵Ķ˿�
 �������  : VOS_UINT8              ucPortType �˿�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32             VOS_TRUE    ����ָ�����͵Ķ˿�
                                    VOS_FALSE ������ָ�����͵Ķ˿�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 AT_ExistSpecificPort(VOS_UINT8 ucPortType)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ��NV��en_NV_Item_Huawei_Dynamic_PID_Type��ȡ��ǰ�Ķ˿�״̬ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_WARN_LOG("AT_ExistSpecificPort: Read NV fail!");
        return VOS_FALSE;
    }

    /* �ж�DIAG�˿��Ƿ��Ѿ���: �Ѿ�����ֱ�ӷ���AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* ��ѯNV��en_NV_Item_Huawei_Dynamic_PID_Type���Ƿ��Ѿ�����DIAG�� */
        AT_GetSpecificPort(ucPortType,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE != ulPortPos)
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : AT_OpenDiagPort
 ��������  : ��DIAG�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 AT_OpenDiagPort(VOS_VOID)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ��NV��en_NV_Item_Huawei_Dynamic_PID_Type��ȡ��ǰ�Ķ˿�״̬ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_WARN_LOG("AT_OpenDiagPort: Read NV fail!");
        return AT_ERROR;
    }

    /* �ж�DIAG�˿��Ƿ��Ѿ���: �Ѿ�����ֱ�ӷ���AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* ��ѯNV��en_NV_Item_Huawei_Dynamic_PID_Type���Ƿ��Ѿ�����DIAG�� */
        AT_GetSpecificPort(AT_DEV_DIAG,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE != ulPortPos)
        {
            return AT_OK;
        }

    }
    else
    {
        AT_WARN_LOG("AT_OpenDiagPort: en_NV_Item_Huawei_Dynamic_PID_Type is inactive!");
        return AT_OK;
    }

    /* DIAG�˿ڲ���Ȩ��δ��ȡ: ֱ�ӷ���AT_OK */
    if (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag)
    {
        return AT_OK;
    }

    /* ׷��DIAG�˿ڵ��л���˿ڼ� */
    if (AT_SETPORT_PARA_MAX_LEN == ulPortNum)
    {
        return AT_OK;
    }

    stDynamicPidType.aucRewindPortStyle[ulPortNum] = AT_DEV_DIAG;

    /* ���¶˿ڼ������ݵ�NV��en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_OpenDiagPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_CloseDiagPort
 ��������  : �ر�DIAG�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32             ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 AT_CloseDiagPort(VOS_VOID)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;
    VOS_UINT32                          ulLoop;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ��NV��en_NV_Item_Huawei_Dynamic_PID_Type��ȡ��ǰ�Ķ˿�״̬ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseDiagPort: Read NV fail!");
        return AT_ERROR;
    }

    /* �ж�DIAG�˿��Ƿ��Ѿ���: �Ѿ�����ֱ�ӷ���AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* ��ѯNV��en_NV_Item_Huawei_Dynamic_PID_Type���Ƿ��Ѿ�����DIAG�� */
        AT_GetSpecificPort(AT_DEV_DIAG,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE == ulPortPos)
        {
            return AT_OK;
        }
    }
    else
    {
        return AT_OK;
    }

    /* DIAG�˿ڲ���Ȩ��δ��ȡ: ֱ�ӷ���AT_OK */
    if (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag)
    {
        return AT_OK;
    }

    /* ɾ��NV���е�DIAG�˿� */
    stDynamicPidType.aucRewindPortStyle[ulPortPos] = 0;
    ulPortNum--;
    for (ulLoop = ulPortPos; ulLoop < ulPortNum; ulLoop++)
    {
        stDynamicPidType.aucRewindPortStyle[ulLoop] = stDynamicPidType.aucRewindPortStyle[ulLoop + 1UL];
    }
    stDynamicPidType.aucRewindPortStyle[ulPortNum] = 0;

    /* �˿��쳣���ݱ���: �л�����豸��̬�У���һ���豸����ΪMASS�豸(0xa1,0xa2) */
    if (0 != ulPortNum)
    {
        if ((AT_DEV_CDROM == stDynamicPidType.aucRewindPortStyle[0])
         || (AT_DEV_SD == stDynamicPidType.aucRewindPortStyle[0]))
        {
            return AT_OK;
        }
    }

    /* ���¶˿ڼ������ݵ�NV��en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseDiagPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_ExistSpecificPortChange
 ��������  : �Ƿ����ָ�����͵Ķ˿ڱ��Ȩ��
 �������  : VOS_UINT8                           ucPortType �˿�����
             VOS_UINT8                           aucOldRewindPortStyle[]���ǰ�Ķ˿ڼ���
             VOS_UINT8                           aucNewRewindPortStyle[]�����Ķ˿ڼ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32             VOS_TRUE    ����ָ�����͵Ķ˿ڱ��
                                    VOS_FALSE ������ָ�����͵Ķ˿ڱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 AT_ExistSpecificPortChange(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
)
{
    VOS_UINT32                          ulOldPortPos;
    VOS_UINT32                          ulNewPortPos;
    VOS_UINT32                          ulPortNum;


    ulOldPortPos = 0;
    ulNewPortPos = 0;
    ulPortNum    = 0;

    AT_GetSpecificPort(ucPortType, aucOldRewindPortStyle, &ulOldPortPos, &ulPortNum);
    AT_GetSpecificPort(ucPortType, aucNewRewindPortStyle, &ulNewPortPos, &ulPortNum);

    /* ����һ��ָ���˿� */
    if ((AT_DEV_NONE == ulOldPortPos)
     && (AT_DEV_NONE != ulNewPortPos))
    {
        return VOS_TRUE;
    }

    /* ɾ��һ��ָ���˿� */
    if ((AT_DEV_NONE != ulOldPortPos)
     && (AT_DEV_NONE == ulNewPortPos))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : AT_CheckSetPortRight
 ��������  : �Ƿ����ָ�����͵Ķ˿ڱ��
 �������  : VOS_UINT8                           aucOldRewindPortStyle[]���ǰ�Ķ˿ڼ���
             VOS_UINT8                           aucNewRewindPortStyle[]�����Ķ˿ڼ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32             AT_OK       Ȩ�޼��ͨ��
                                    AT_ERROR    Ȩ�޼�鲻ͨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckSetPortRight(
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
)
{
    VOS_UINT32                          ulRet;

    ulRet = AT_ExistSpecificPortChange(AT_DEV_DIAG,
                                       aucOldRewindPortStyle,
                                       aucNewRewindPortStyle);

    if ((VOS_TRUE == ulRet)
     && (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SetHsspt
 ��������  : ����RRC�汾��Ϣ,�����Ĳ��������Լ����ڸ�ģ����.
 �������  : ucIndex    - �û�����
 �������  : ��
 �� �� ֵ  : ���س�����Ϣ��OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetHsspt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_DPAUPA_ERROR;
    }

    /* ����Ƿ������ݱ���,δ���ʱ���س�����Ϣ:ErrCode:0 */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    ucRRCVer = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ����дNV�ӿں���: AT_WriteRrcVerToNV,���ز������ */
    if (VOS_OK == AT_WriteRrcVerToNV(ucRRCVer))
    {
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_SetHsspt:WARNING:Write NV failed!");
        return AT_DPAUPA_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_QryHsspt
 ��������  : ��ѯRRC�汾��Ϣ
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : ���س�����Ϣ��OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_QryHsspt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    ulResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (VOS_OK == ulResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_TestHsicCmdPara
 ��������  : HSICͨ����������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��19��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������
  2.��    ��   : 2012��8��13��
    ��    ��   : l60609
    �޸�����   : MUX:����MUXͨ���Ĵ���
*****************************************************************************/
VOS_UINT32 AT_TestHsicCmdPara(VOS_UINT8 ucIndex)
{
    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    return AT_OK;
}

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : At_TestTdsScalibPara
 ��������  : ^SCALIB�����������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��30��
    ��    ��   : z00212940
    �޸�����   : TDS��������

*****************************************************************************/
VOS_UINT32 At_TestTdsScalibPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                           usLength;

    usLength = 0;
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s:%s", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        AT_TDS_SCALIB_TEST_STR);
    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : AT_TestSimlockUnlockPara
 ��������  : ^SIMLOCKUNLOCK�����������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : STK�������Լ�DCM���󿪷���Ŀ�����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestSimlockUnlockPara( VOS_UINT8 ucIndex )
{
    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (\"NET\",\"NETSUB\",\"SP\")",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_String2Hex
 ��������  : ����ַ���ת16����������
 �������  : nptr [in/out] ������ַ�������ָ��
             usLen [in] ������ַ�������
 �������  : pRtn [in/out] ���ַ���ת����������ֵ
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
*****************************************************************************/
VOS_UINT32 AT_String2Hex( VOS_UINT8 *nptr,VOS_UINT16 usLen, VOS_UINT32 *pRtn)
{
    VOS_UINT32                          c     = 0;         /* current Char */
    VOS_UINT32                          total = 0;         /* current total */
    VOS_UINT8                           Length = 0;        /* current Length */

    c = (VOS_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else if( (c  >= 'a') && (c  <= 'f') )
        {
            c  = c  - 'a' + 10;
        }
        else if( (c  >= 'A') && (c  <= 'F') )
        {
            c  = c  - 'A' + 10;
        }
        else
        {
            return VOS_ERR;
        }

        if(total > 0x0FFFFFFF)              /* ������ת */
        {
            return VOS_ERR;
        }
        else
        {
            total = (total << 4) + c;       /* accumulate digit */
            c = (VOS_UINT32)(*(nptr++));    /* get next Char */
        }
    }
     /* return result, negated if necessary */
    *pRtn = total;
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_NVWRGetParaInfo
 ��������  : ��ȡ���������Ϣ
 �������  : *pucPara  :
             *pucValue :
             **pucParaDst

 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
*****************************************************************************/
VOS_UINT32 AT_NVWRGetItemValue( VOS_UINT8 *pucPara,  VOS_UINT8 *pucValue,  VOS_UINT8 **pucParaDst)
{
    VOS_UINT32                          ulTmp = 0;
    VOS_UINT8                          *pucStart = pucPara;
    VOS_UINT16                          usLen = 0;
    VOS_UINT8                          *pucEnd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ���õĵط���֤pucPara,pucValue,pucParaDst��ΪNULL */

    /* ֱ����һ������' '���ַ� */
    while(' ' == *pucStart)
    {
        pucStart++;
    }

    if(' ' == *(pucStart+1))
    {
        usLen = 1;
        pucEnd = pucStart+2;
    }
    else if(' ' == *(pucStart+2))
    {
        usLen = 2;
        pucEnd = pucStart+3;
    }
    else
    {
        return VOS_ERR;
    }

    ulRet = AT_String2Hex(pucStart, usLen, &ulTmp);
    if((VOS_OK != ulRet) || (ulTmp > 0xff))
    {
        return VOS_ERR;
    }

    *pucValue = (VOS_UINT8)ulTmp;
    *pucParaDst = pucEnd;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_NVWRGetParaInfo
 ��������  : ^NVWRITE�������
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
*****************************************************************************/
VOS_UINT32 AT_NVWRGetParaInfo( AT_PARSE_PARA_TYPE_STRU * pstPara, VOS_UINT8 * pu8Data, VOS_UINT32 * pulLen)
{
    VOS_UINT32                          ulNum = 0;
    VOS_UINT8                          *pu8Start   = VOS_NULL_PTR;
    VOS_UINT8                          *pu8ParaTmp = VOS_NULL_PTR;
    VOS_UINT16                          usLen = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          i = 0;

    /* ���õĵط���֤pstPara,pu8Data��ΪNULL */

    pu8Start = pstPara->aucPara;
    usLen= pstPara->usParaLen;

    if(usLen < AT_PARA_MAX_LEN)
    {
        pstPara->aucPara[usLen] = ' ';
    }
    else
    {
        return VOS_ERR;
    }

    ulNum = 0;
    for(i = 0; i < usLen; )
    {
        ulRet = AT_NVWRGetItemValue(pu8Start, (pu8Data+ulNum), &pu8ParaTmp);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            return ulRet;
        }

        ulNum++;

        /* ���128�� */
        /*MAX_NV_NUM_PER_PARA */
        if(ulNum == 128)
        {
            break;
        }

        if(pu8ParaTmp >= (pu8Start+usLen))
        {
            break;
        }

        i += (VOS_UINT16)(pu8ParaTmp - pu8Start);
        pu8Start = pu8ParaTmp;
    }

    *pulLen = ulNum;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetNVReadPara
 ��������  : ^NVREAD�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
*****************************************************************************/
VOS_UINT32 AT_SetNVReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvId  = 0;
    VOS_UINT32                          ulNvLen = 0;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          i       = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    VOS_UINT32                          ulRet;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        g_ulNVRD = 1;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        g_ulNVRD = 2;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        g_ulNVRD = 3;
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        usNvId = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    }

    ulRet = NV_GetLength(usNvId, &ulNvLen);

    if(VOS_OK != ulRet)
    {
        g_ulNVRD = 4;
        return AT_ERROR;
    }

    /* ���ȴ���128��ֻȡǰ128���ֽ�*/
    pucData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, ulNvLen);
    if(VOS_NULL_PTR == pucData)
    {
        g_ulNVRD = 5;
        return AT_ERROR;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVReadPara:Get modem id fail");

        PS_MEM_FREE(WUEPS_PID_AT, pucData);

        g_ulNVWR =8;
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(enModemId, usNvId, (VOS_VOID*)pucData, ulNvLen);

    if(VOS_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);

        g_ulNVRD = 6;
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr,
        "^NVRD: %d,", ulNvLen);

    for(i = 0; i < ulNvLen; i++)
    {
        if(0 == i)
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,"%02X", pucData[i]);
        }
        else
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen," %02X", pucData[i]);
        }
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucData);
    g_ulNVRD = 7;
    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetNVReadPara
 ��������  : ^NVWRITE�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
  2.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : NVWR���ȫ����
*****************************************************************************/
VOS_UINT32 AT_SetNVWritePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvId = 0;
    VOS_UINT16                          usNvTotleLen = 0;
    VOS_UINT32                          ulNvLen = 0; /* VOS_UINT16 -> VOS_UINT32 */
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulNvNum = 0; /* VOS_UINT16 -> VOS_UINT32 */
    VOS_UINT8                           au8Data[128] = {0};/* MAX_NV_NUM_PER_PARA */
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulRet;

    gstAtSendData.usBufLen = 0;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        g_ulNVWR =1;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (0 == gastAtParaList[2].usParaLen))
    {
        g_ulNVWR =2;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usNvId = (VOS_UINT16)gastAtParaList[0].ulParaValue;

    if (VOS_TRUE != AT_IsNVWRAllowedNvId(usNvId))
    {
        g_ulNVWR = 10;
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    (VOS_VOID)vos_printf("\n atSetNVWRPara usNvId = %d\n",usNvId);

    usNvTotleLen = (VOS_UINT16)gastAtParaList[1].ulParaValue;
    (VOS_VOID)vos_printf("\n atSetNVWRPara usNvTotleLen = %d\n",usNvTotleLen);

    pucData = PS_MEM_ALLOC(WUEPS_PID_AT, usNvTotleLen);
    if(VOS_NULL_PTR == pucData)
    {
        g_ulNVWR =3;
        return AT_ERROR;
    }

    i = 0;
    while(0 != gastAtParaList[2UL + i].usParaLen)
    {
        ulRet = AT_NVWRGetParaInfo((AT_PARSE_PARA_TYPE_STRU*)(&(gastAtParaList[2UL + i])), au8Data, &ulNvNum);

        if(VOS_OK != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =4;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ��������ĳ��ȴ���128���򷵻�ʧ�� */
        /*MAX_NV_NUM_PER_PARA */
        if(ulNvNum > 128)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =5;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ����ۼӵĲ������������ܳ��� */
        if((ulNvLen+ulNvNum) > usNvTotleLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =6;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        PS_MEM_CPY((pucData + ulNvLen), au8Data, ulNvNum);

        ulNvLen += ulNvNum;
        i++;

        if(i >= (AT_MAX_PARA_NUMBER-2))
        {
            break;
        }
    }

    /* ����ۼӵĲ����������ܳ��Ȳ���� */
    if(ulNvLen != usNvTotleLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =7;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVWritePara:Get modem id fail");
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =8;
        return AT_ERROR;
    }

    ulRet = NV_WriteEx(enModemId, usNvId, (VOS_VOID*)pucData, usNvTotleLen);

    if(VOS_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =9;

        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucData);
    g_ulNVWR =10;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SetNVWRPartPara
 ��������  : ^NVWRLEN���������
 �������  : VOS_UINT8 ucClientId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : s00318873
    �޸�����   : �����ɺ��� for DTS2015042202710

  2.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : NVWR���ȫ����

*****************************************************************************/
VOS_UINT32 AT_SetNVWRPartPara(VOS_UINT8 ucClientId)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usNVID;
    VOS_UINT32                          ulNVWrTotleLen;
    VOS_UINT32                          ulNVLen;
    VOS_UINT16                          usNVWrLen;
    VOS_UINT8                          *pucNvWrData = VOS_NULL_PTR;
    VOS_UINT32                          ulNVNum;
    VOS_UINT32                          i;
    VOS_UINT8                           aucData[128];
    VOS_UINT16                          usOffset;
    MODEM_ID_ENUM_UINT16                enModemId;

    i                       = 0;
    ulNVLen                 = 0;
    gstAtSendData.usBufLen  = 0;
    ulNVWrTotleLen          = 0;
    PS_MEM_SET(aucData,0,sizeof(aucData));

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if( (0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (0 == gastAtParaList[2].usParaLen)
     || (0 == gastAtParaList[3].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usNVID       = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    usOffset     = (VOS_UINT16)gastAtParaList[1].ulParaValue;
    usNVWrLen    = (VOS_UINT16)gastAtParaList[2].ulParaValue;

    if (VOS_TRUE != AT_IsNVWRAllowedNvId(usNVID))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    /* check param#3 usNVWrLen */
    if (usNVWrLen == 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* get NV length */
    ulRet        = NV_GetLength(usNVID, &ulNVWrTotleLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* check param#2 usOffset */
    if(((VOS_UINT32)usOffset > (ulNVWrTotleLen - 1)) || ((VOS_UINT32)(usOffset + usNVWrLen) > ulNVWrTotleLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pucNvWrData = PS_MEM_ALLOC(WUEPS_PID_AT, usNVWrLen);
    if(NULL == pucNvWrData)
    {
        return AT_ERROR;
    }

    /* get NV value form param#4\5\...\#16 */
    while(0 != gastAtParaList[3UL + i].usParaLen)
    {
        ulRet = AT_NVWRGetParaInfo((AT_PARSE_PARA_TYPE_STRU*)(&(gastAtParaList[3UL + i])), aucData, (VOS_UINT32 *)&ulNVNum);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(ulNVNum > 128)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if((ulNVLen+ulNVNum) > usNVWrLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        PS_MEM_CPY(((VOS_UINT8*)pucNvWrData + ulNVLen), (VOS_UINT8*)aucData, ulNVNum);

        ulNVLen += ulNVNum;
        i++;

        if(i >= (AT_MAX_PARA_NUMBER - 3))
        {
            break;
        }

    }

    /* check all the nv value have the exact length by param#3 */
    if(ulNVLen != usNVWrLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = AT_GetModemIdFromClient(ucClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVWritePara:Get modem id fail");
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    if (enModemId >= MODEM_ID_BUTT)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    ulRet = NV_WritePartEx(enModemId, usNVID, usOffset, (VOS_VOID*)pucNvWrData, usNVWrLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : AT_GetNvRdDebug
 ��������  : ��ʾNV��д������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��28��
    ��    ��   : d00212987
    �޸�����   : ��ֲ����ԭ��AT �����дNV����
*****************************************************************************/
VOS_VOID AT_GetNvRdDebug(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n g_ulNVRD=0x%x \n",g_ulNVRD);
    (VOS_VOID)vos_printf("\n g_ulNVWR=0x%x \n",g_ulNVWR);
}

/*****************************************************************************
 �� �� ��  : AT_QryFPllStatusPara
 ��������  : ��ѯG��W PLL״̬
 �������  : ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��29��
    ��    ��   : L00256032
    �޸�����   : Added for PLL status query
*****************************************************************************/
VOS_UINT32 AT_QryFPllStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulReceiverPid;
    AT_PHY_RF_PLL_STATUS_REQ_STRU      *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMsgId;
#if (FEATURE_ON==FEATURE_LTE)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
            ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFPllStatusPara(ucIndex);
    }
#endif
    /*�жϵ�ǰ����ģʽ��ֻ֧��G/W*/
    if (AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        ulReceiverPid = DSP_PID_WPHY;
        usMsgId       = ID_AT_WPHY_RF_PLL_STATUS_REQ;
    }
    else if ( (AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
            ||(AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode) )
    {
        ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
        usMsgId       = ID_AT_GPHY_RF_PLL_STATUS_REQ;
    }

    else
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ����AT_PHY_RF_PLL_STATUS_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_PHY_RF_PLL_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_PHY_RF_PLL_STATUS_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_QryFPllStatusPara: Alloc msg fail!");
        return AT_ERROR;
    }

    /* �����Ϣ */
    pstMsg->ulReceiverPid = ulReceiverPid;
    pstMsg->usMsgID       = usMsgId;
    pstMsg->usRsv1        = 0;
    pstMsg->usDspBand     = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->usRsv2        = 0;

    /* ���ӦPHY������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_QryFPllStatusPara: Send msg fail!");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPLLSTATUS_QRY;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    /* ������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : At_RfPllStatusCnfProc
 ��������  : AT����GPHY/WPHY�ظ���PLL״̬��ѯ��Ӧ��Ϣ
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��29��
    ��    ��   : L00256032
    �޸�����   : Added for PLL status query
*****************************************************************************/
VOS_VOID At_RfPllStatusCnfProc(PHY_AT_RF_PLL_STATUS_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ��ȡ���ر�����û����� */
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_FPLLSTATUS_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RfPllStatusCnfProc: CmdCurrentOpt is not AT_CMD_FPLLSTATUS_QRY!");
        return;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d,%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstMsg->usTxStatus,
                                       pstMsg->usRxStatus);

    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, AT_OK);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_QryFpowdetTPara
 ��������  : ���Ĵ���PDEGֵ
 �������  : ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : d00212987
    �޸�����   : Added for PDEA status query
*****************************************************************************/
VOS_UINT32 AT_QryFpowdetTPara(VOS_UINT8 ucIndex)
{
    AT_PHY_POWER_DET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

    /*�жϵ�ǰ����ģʽ��ֻ֧��W*/
    if (AT_RAT_MODE_WCDMA != g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ����AT_PHY_POWER_DET_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_PHY_POWER_DET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_PHY_POWER_DET_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_QryFpowdetTPara: Alloc msg fail!");
        return AT_ERROR;
    }

    /* �����Ϣ */
    pstMsg->ulReceiverPid = DSP_PID_WPHY;
    pstMsg->usMsgID       = ID_AT_WPHY_POWER_DET_REQ;
    pstMsg->usRsv         = 0;

    /* ���ӦPHY������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_QryFpowdetTPara: Send msg fail!");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPOWDET_QRY;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    /* ������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : At_RfFPOWDETCnfProc
 ��������  : AT����WPHY�ظ������ļĴ���PDEGֵ
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : d00212987
    �޸�����   : Added for PDEA status query
*****************************************************************************/
VOS_VOID At_RfFpowdetTCnfProc(PHY_AT_POWER_DET_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ��ȡ���ر�����û����� */
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_FPOWDET_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RfFPOWDETCnfProc: CmdCurrentOpt is not AT_CMD_FPOWDET_QRY!");
        return;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* Ӧ�����Ҫ���������ֵΪ0x7FFF��Ϊ��Чֵ�����ѯ�߷���ERROR */
    if(0x7FFF == pstMsg->sPowerDet)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstMsg->sPowerDet);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetNvwrSecCtrlPara
 ��������  : ^NVWRSECCTRL�����������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AT_SetNvwrSecCtrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_MTA_NVWRSECCTRL_SET_REQ_STRU     stNvwrSecCtrl;
    VOS_UINT16                          usLength;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stNvwrSecCtrl, 0x00, sizeof(stNvwrSecCtrl));

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ��������������� */
    if (AT_NVWRSECCTRL_PARA_SECTYPE_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ð�ȫ�������� */
    stNvwrSecCtrl.ucSecType = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ���ַ�������ת��Ϊ���� */
    usLength = gastAtParaList[1].usParaLen;
    if ( (2 == gucAtParaIndex)
      && (AT_RSA_CIPHERTEXT_PARA_LEN == usLength) )
    {
        if ( (AT_SUCCESS == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &usLength))
          && (AT_RSA_CIPHERTEXT_LEN == usLength) )
        {
            stNvwrSecCtrl.ucSecStrFlg = VOS_TRUE;
            PS_MEM_CPY(stNvwrSecCtrl.aucSecString, gastAtParaList[1].aucPara, AT_RSA_CIPHERTEXT_LEN);
        }
    }

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_NVWRSECCTRL_SET_REQ,
                                      &stNvwrSecCtrl,
                                      sizeof(stNvwrSecCtrl),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetNvwrSecCtrlPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVWRSECCTRL_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaNvwrSecCtrlSetCnf
 ��������  : ATģ���յ�MTAģ����Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AT_RcvMtaNvwrSecCtrlSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_RESULT_CNF_STRU             *pstResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstResult       = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NVWRSECCTRL_SET */
    if (AT_CMD_NVWRSECCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstResult->enResult)
    {
        /* �ɹ������OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* ʧ�ܣ����ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_QryNvwrSecCtrlPara
 ��������  : ^NWSECCTRL��ѯ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AT_QryNvwrSecCtrlPara(VOS_UINT8 ucIndex)
{
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    VOS_UINT32                          ulResult;

    /* ������ʼ�� */
    ulResult = AT_ERROR;
    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));

    /* �޸İ�ȫ����NV */
    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvwrSecCtrlNV.ucSecType);
    }

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : AT_IsNVWRAllowedNvId
 ��������  : �ж�����^NVWR��^NVWREX�ܷ��޸Ĵ�NV_ID
 �������  : usNvId
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- �����޸�
             VOS_FLASE  -- �������޸�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_BOOL AT_IsNVWRAllowedNvId(VOS_UINT16 usNvId)
{
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBlackListNum;

    /* ������ʼ�� */
    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));

    /* ��ȡ��ȫ����NV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        AT_ERR_LOG("AT_IsNVWRAllowedNvId: NV_ReadEx fail!");
        return VOS_FALSE;
    }

    switch (stNvwrSecCtrlNV.ucSecType)
    {
        case AT_NVWR_SEC_TYPE_OFF:
            return VOS_TRUE;

        case AT_NVWR_SEC_TYPE_ON:
            return VOS_FALSE;

        case AT_NVWR_SEC_TYPE_BLACKLIST:
            ucBlackListNum = (stNvwrSecCtrlNV.ucBlackListNum <= TAF_NV_BLACK_LIST_MAX_NUM) ?
                             stNvwrSecCtrlNV.ucBlackListNum : TAF_NV_BLACK_LIST_MAX_NUM;
            for (ucLoop = 0; ucLoop < ucBlackListNum; ucLoop++)
            {
                if (usNvId == stNvwrSecCtrlNV.ausBlackList[ucLoop])
                {
                    return VOS_FALSE;
                }
            }
            return VOS_TRUE;

        default:
            AT_ERR_LOG1("AT_IsNVWRAllowedNvId: Error SecType:", stNvwrSecCtrlNV.ucSecType);
            break;
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  :AT_AsciiToHex
��������  :ת���ַ�����ʽ
�������  :

�������  :��
�� �� ֵ  :VOS_OK    :ʧ��
           VOS_ERR   :�ɹ�

�޶���¼  :
1. ��    ��   : 2015��07��23��
   ��    ��   : z00316370
   �޸�����   : Creat
*****************************************************************************/

VOS_UINT32 AT_AsciiToHex(
    VOS_UINT8                          *pucSrc,
    VOS_UINT8                          *pucDst
)
{

    if (( *pucSrc >= '0') && (*pucSrc <= '9')) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - '0');
    }
    else if ( (*pucSrc >= 'a') && (*pucSrc <= 'f') ) /* the number is a-f */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - 'a') + 0x0a;
    }
    else if ( (*pucSrc >= 'A') && (*pucSrc <= 'F') ) /* the number is A-F */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - 'A') + 0x0a;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :AT_AsciiToHexCode
��������  :ת���ַ�����ʽ������,"1234"->0x3412
�������  :

�������  :��
�� �� ֵ  :VOS_OK    :ʧ��
           VOS_ERR   :�ɹ�

�޶���¼  :
1. ��    ��   : 2015��7��23��
   ��    ��   : z00316370
   �޸�����   : Creat
*****************************************************************************/

VOS_UINT32 AT_AsciiToHexCode_Revers(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDst
)
{
    VOS_INT16                           sLoop1;
    VOS_UINT16                          usLoop2;
    VOS_UINT8                           ucTemp1;
    VOS_UINT8                           ucTemp2;
    VOS_UINT32                          ulRslt;

    sLoop1 = (VOS_INT16)(usDataLen - 1);
    for (usLoop2 = 0; sLoop1 >= 0; sLoop1--, usLoop2++)
    {
        ulRslt = AT_AsciiToHex(&(pucSrc[sLoop1]), &ucTemp1);
        if (VOS_ERR == ulRslt)
        {
            return VOS_ERR;
        }

        sLoop1--;

        ulRslt = AT_AsciiToHex(&(pucSrc[sLoop1]), &ucTemp2);
        if (VOS_ERR == ulRslt)
        {
            return VOS_ERR;
        }

        pucDst[usLoop2] = (VOS_UINT8)((ucTemp2 << 4) | ucTemp1);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_Hex2Ascii
 ��������  : ��ʮ�����������ַ���ת����ASCII���ʾ�������ַ���,����,0x3412 --> "1234"
 �������  : VOS_UINT8  aucHex[]ʮ���������ַ����׵�ַ
             VOS_UINT32 ulLength      ʮ���������ַ�������
 �������  : VOS_UINT8  aucAscii[]    ASCII���ʾ�������ַ����׵�ַ
 �� �� ֵ  : VOS_UINT32 ת�����: VOS_OKת���ɹ���VOS_ERRת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_Hex2Ascii_Revers(
    VOS_UINT8                           aucHex[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_INT32                           lLoopSrc;
    VOS_UINT32                          ulLoopDest;
    VOS_UINT8                           ucTemp;

    lLoopSrc = (VOS_INT32)(ulLength - 1);
    for (ulLoopDest = 0; lLoopSrc >= 0; lLoopSrc--, ulLoopDest++)
    {
        ucTemp = (aucHex[lLoopSrc]>>4) & 0x0F;
        if (ucTemp < 10)
        {
            /* 0~9 */
            aucAscii[ulLoopDest] = ucTemp + 0x30;
        }
        else if ((ucTemp >= 0x0a)
             && ((ucTemp <= 0x0f)))
        {
            /* a~f */
            aucAscii[ulLoopDest] = ucTemp + 0x37;
        }
        else
        {
            return VOS_ERR;
        }

        ulLoopDest++;
        ucTemp = aucHex[lLoopSrc] & 0x0F;
        if (ucTemp < 10)
        {
            /* 0~9 */
            aucAscii[ulLoopDest] = ucTemp + 0x30;
        }
        else if ((ucTemp >= 0x0a)
             && ((ucTemp <= 0x0f)))
        {
            /* a~f */
            aucAscii[ulLoopDest] = ucTemp + 0x37;
        }
        else
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : AT_SetMeidPara
 ��������  : �����޸�MEID,�����ʽ%MEID=<meid number>
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : AT_OK - �ɹ�
             AT_DEVICE_OTHER_ERROR�� AT_DATA_UNLOCK_ERROR - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetMeidPara(VOS_UINT8 ucIndex)
{
    AT_MTA_MEID_SET_REQ_STRU            stMeIdReq;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stMeIdReq, 0x00, sizeof(NV_MEID_STRU));

    /* ����״̬��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������Ϊ1�����ַ������Ȳ�Ϊ14 */
    if ((1 != gucAtParaIndex)
     || (14 != gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRslt = AT_AsciiToHexCode_Revers(gastAtParaList[0].aucPara,
                                      gastAtParaList[0].usParaLen,
                                      stMeIdReq.aucMeid);

    if (VOS_OK != ulRslt)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRslt = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_MEID_SET_REQ,
                                    &stMeIdReq,
                                    sizeof(stMeIdReq),
                                    I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MEID_SET;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("AT_SetMeidPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

}

/*****************************************************************************
 �� �� ��  : AT_QryMeidPara
 ��������  : AT%MEID��ѯMEID
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��17��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_QryMeidPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������Ϣ*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MEID_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MEID_QRY;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("AT_QryMeidPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaMeidSetCnf
 ��������  : ID_MTA_AT_MEID_SET_CNF��Ϣ������,^MEID���ý��
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��23��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMeidSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_RESULT_CNF_STRU             *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf       = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMeidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMeidSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_MEID_SET */
    if (AT_CMD_MEID_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMeidSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MEID����� */
    gstAtSendData.usBufLen = 0;

    switch (pstSetCnf->enResult)
    {
        case MTA_AT_RESULT_INCORRECT_PARAMETERS:
            ulRslt = AT_DEVICE_INVALID_PARAMETERS;
            break;

        case MTA_AT_RESULT_DEVICE_SEC_NV_ERROR:
            ulRslt = AT_DEVICE_NV_WRITE_FAIL_UNKNOWN;
            break;

        case MTA_AT_RESULT_NO_ERROR:
            ulRslt = AT_OK;
            break;

        default:
            ulRslt = AT_ERROR;
            break;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaMeidQryCnf
 ��������  : ID_MTA_AT_MEID_QRY_CNF��Ϣ������,^MEID���ý��
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMeidQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_MEID_QRY_CNF_STRU           *pstQryCnf;
    VOS_UINT8                           ucIndex;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    VOS_UINT8                           aucMeId[2*MEID_NV_DATA_LEN_NEW + 1];
    VOS_UINT8                           aucpEsn[2*PESN_NV_DATA_LEN + 1];
    VOS_UINT8                           aucpUimID[2*UIMID_DATA_LEN + 1];

    PS_MEM_SET(&stMeId, 0x00, sizeof(NV_MEID_STRU));
    PS_MEM_SET(&stPEsn, 0x00, sizeof(NV_PESN_STRU));
    PS_MEM_SET(aucMeId, 0, sizeof(VOS_UINT8));

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstQryCnf       = (MTA_AT_MEID_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_MEID_QRY */
    if (AT_CMD_MEID_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MEID����� */
    gstAtSendData.usBufLen = 0;

    /* ��ȡen_NV_Item_MEID */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MEID, &stMeId, sizeof(NV_MEID_STRU)))
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf:Read en_NV_Item_MEID Nvim Failed");
        return AT_DEVICE_NV_READ_FAILURE;
    }

    /* ��ȡen_NV_Item_PESN */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PESN, &stPEsn, sizeof(NV_PESN_STRU)))
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf:Read en_NV_Item_PESN Nvim Failed");
        return AT_DEVICE_NV_READ_FAILURE;
    }

    /* ��ȡUIMIDʧ�� */
    if (pstQryCnf->enResult != MTA_AT_RESULT_NO_ERROR)
    {
        AT_WARN_LOG("AT_RcvMtaMeidQryCnf:Read UIMID Failed");
    }

    AT_Hex2Ascii_Revers(&(pstQryCnf->aucEFRUIMID[1]), UIMID_DATA_LEN, aucpUimID);
    aucpUimID[2*UIMID_DATA_LEN] = '\0';

    AT_Hex2Ascii_Revers(&(stPEsn.aucPEsn[0]), PESN_NV_DATA_LEN, aucpEsn);
    aucpEsn[2*PESN_NV_DATA_LEN] = '\0';

    AT_Hex2Ascii_Revers(&(stMeId.aucMeID[0]), MEID_NV_DATA_LEN_NEW, aucMeId);
    aucMeId[2*MEID_NV_DATA_LEN_NEW] = '\0';

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %s,%s,%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucMeId,
                                                    aucpEsn,
                                                    aucpUimID);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

