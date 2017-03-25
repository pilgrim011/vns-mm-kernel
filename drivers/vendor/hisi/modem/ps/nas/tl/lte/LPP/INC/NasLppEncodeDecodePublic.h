


#ifndef __NASLPPENCODEDECODEPUBLIC_H__
#define __NASLPPENCODEDECODEPUBLIC_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
#include    "PsCommonDef.h"
#include    "LPsOm.h"
#include    "NasLppPublic.h"




/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_LPP_SLCT        (1)
#define NAS_LPP_NO_SLCT     (0)
#define NAS_LPP_TRUE        (TRUE)
#define NAS_LPP_FALSE       (FALSE)
//#define NAS_LPP_DECODE_FAIL (1)
//#define NAS_LPP_DECODE_SUCC (0)
//#define NAS_LPP_ENCODE_SUCC (0)
//#define NAS_LPP_ENCODE_FAIL (1)


/*Encode define start*/
#define NAS_LPP_GNSS_SUPPORT_LIST_MIN       (1)
#define NAS_LPP_GNSS_SUPPORT_LIST_MAX       (16)
#define NAS_LPP_GNSS_IDS_MIN                (1)
#define NAS_LPP_GNSS_IDS_MAX                (16)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MIN     (1)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MAX     (16)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MIN       (1)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MAX       (8)
#define NAS_LPP_SBASID_MAX                      (3)
#define NAS_LPP_CLOCK_MODEL_MIN                 (1)
#define NAS_LPP_CLOCK_MODEL_MAX                 (8)
#define NAS_LPP_ORBIT_MODEL_MIN                 (1)
#define NAS_LPP_ORBIT_MODEL_MAX                 (8)
#define NAS_LPP_ALMANAC_MODEL_MIN               (1)
#define NAS_LPP_ALMANAC_MODEL_MAX               (8)
#define NAS_LPP_UTC_MODEL_MIN                   (1)
#define NAS_LPP_UTC_MODEL_MAX                   (8)
#define NAS_LPP_EXT_ENUMERATED_BUTT             (0XFF)
/*Encode define end*/

/*Encode define start*/

/*Encode define end*/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


enum NAS_LPP_TO_OM_MSG_ENUM
{
    NAS_LPP_TO_OM_MSG_BASE = 0,
    NAS_LPP_TO_OM_MSG_ASN_FAIL = NAS_LPP_TO_OM_MSG_BASE + 0X01,
};

enum NAS_LPP_DECODE_CAUSE_ENUM
{
    NAS_LPP_DECODE_SUCC = 0,                                    /*�ɹ�*/
    NAS_LPP_DECODE_FAIL,                                        /*ʧ��*/
    /*��������*/
    NAS_LPP_DECODE_NULL_PTR,                                    /*��ָ�룬��������õ�,�ϸ������ϣ����벻�����п�ָ��*/
    /*MsgHeaderError��ӳ�䵽LPP error�տ��е�ͷ����*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*��Ϣͷֵ����ȷ*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*��Ϣͷ�����������һ������������չ���������н�һ��ϸ��*/
    /*IncorrectError��ӳ�䵽LPP error����ȷֵ�Ĵ���*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*����ֵ����ȷ*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*ö��ֵ����ȷ*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING���͵Ĵ��� ����*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*�ṹ���������Ч���ȳ���*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*�ṹ������չ����,����ö����չ��ĳ���̫����������65535*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*�ַ��ͱ������Ȳ���ȷ*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choiceֵ������Χ*/

    /*MsgBodyError��ӳ�䵽LPP error��Ϣ�����*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*����չ�Ľṹ�壬�б�ѡ����չ�����û��ѡ��*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*������ܳ��ȸ�����֮����ܳ��Ȳ�ƥ��*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*ĳһ��ԪΪ��ѡ��Ԫ������ĳЩ�������Ǳ�ѡ��Ԫû�д�����*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH,  /*��չ��L+V��ֵ��ƥ��*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*��ĳЩ�����У�ĳЩ��Ԫ��ֵһ�����ԣ�����Ҳ����Ϣ�����*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOO_SHORT,                    /*��Ϣ��̫��*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*��Ϣ���Ͳ�����*/
    /*EpuduError, ӳ�䵽LPP error�е�epdu����*/
    NAS_LPP_DECODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU��ֵ�������*/
    /*Undefined, ӳ�䵽LPP error�е�undefined����*/
    NAS_LPP_DECODE_MSG_UNDEFINED_ERROR,                         /*�����������״̬֮���״̬*/

    NAS_LPP_DECODE_MSG_ERROR_BUTT
};
typedef VOS_UINT32  NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32;

enum NAS_LPP_ENCODE_CAUSE_ENUM
{
    NAS_LPP_ENCODE_SUCC = 0,                                    /*�ɹ�*/
    NAS_LPP_ENCODE_FAIL,                                        /*ʧ��*/
    /*��������*/
    NAS_LPP_ENCODE_NULL_PTR,                                    /*��ָ�룬��������õ�,�ϸ������ϣ����벻�����п�ָ��*/
    /*MsgHeaderError��ӳ�䵽LPP error�տ��е�ͷ����*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*��Ϣͷֵ����ȷ*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*��Ϣͷ�����������һ������������չ���������н�һ��ϸ��*/
    /*IncorrectError��ӳ�䵽LPP error����ȷֵ�Ĵ���*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*����ֵ����ȷ*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*ö��ֵ����ȷ*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_VALUE_ERROR,          /*ѡ����ֵ����ȷ*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING���͵Ĵ��� ����*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*�ṹ���������Ч���ȳ���*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*�ṹ������չ����,����ö����չ��ĳ���̫����������65535*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*�ַ��ͱ������Ȳ���ȷ*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choiceֵ������Χ*/

    /*MsgBodyError��ӳ�䵽LPP error��Ϣ�����*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*����չ�Ľṹ�壬�б�ѡ����չ�����û��ѡ��*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*������ܳ��ȸ�����֮����ܳ��Ȳ�ƥ��*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*ĳһ��ԪΪ��ѡ��Ԫ������ĳЩ�������Ǳ�ѡ��Ԫû�д�����*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*��ĳЩ�����У�ĳЩ��Ԫ��ֵһ�����ԣ�����Ҳ����Ϣ�����*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*��Ϣ���Ͳ�����*/
    /*EpuduError, ӳ�䵽LPP error�е�epdu����*/
    NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU��ֵ����*/
    /*Undefined, ӳ�䵽LPP error�е�undefined����*/
    NAS_LPP_ENCODE_MSG_UNDEFINED_ERROR,                         /*�����������״̬֮���״̬*/

    NAS_LPP_ENCODE_MSG_ERROR_BUTT
};
typedef VOS_UINT16  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16;

enum LPP_ENCODE_ERR_STR_ENUM
{
    LPP_ENCODE_ERR_STR_TRANSATION_ID = 0,
    LPP_ENCODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_ENCODE_ERR_STR_ACKNOWLEGMENT,
    LPP_ENCODE_ERR_STR_PROVIDE_CAPABILITIES,
    LPP_ENCODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_ENUM_UINT32;

enum LPP_DECODE_ERR_STR_ENUM
{
    LPP_DECODE_ERR_STR_TRANSATION_ID = 0,
    LPP_DECODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_DECODE_ERR_STR_ACKNOWLEGMENT,
    LPP_DECODE_ERR_STR_REQ_CAPABILITIES,
    LPP_DECODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_UINT32;

enum LPP_ENCODE_DECODE_ERR_ENUM
{
    LPP_ENCODE_DECODE_ERR_VALUE_OUT_OF_RANGE = 0, /*��ʾ������ʱ��ֵ������Χ*/
    LPP_ENCODE_DECODE_ERR_PROTOCOL_MISMATCH,      /*��ʾЭ��汾��һ��*/
    LPP_DECODE_DECODE_ERR_MSG_EXCEED_TOTOL_LEN,   /*��ʾ�ܳ��ȳ���*/
    LPP_ENCODE_DECODE_ERR_NULL_POINTER,           /*��ʾ��ο�ָ��*/
    LPP_DECODE_DECODE_ERR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_DECODE_ERR_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*********************************************************************
�ṹ����: LPP_DEBUG_INFO_STRU
�ṹ����: LPPģ���ά�ɲ���Ϣ�ṹ
��    ��: lifuxin 00253982 2015-5-6 ����
*********************************************************************/
typedef struct
{
    LPP_ENCODE_DECODE_ERR_ENUM_UINT32       enEncodeDecodeErrType;      /*��ʾ��������*/
    VOS_UINT8                               aucAbortIeName[16];         /*�쳣IE����*/
    VOS_UINT32                              ulMinValue;                 /*ȡֵ���½�*/
    VOS_UINT32                              ulMaxValue;                 /*ȡֵ���Ͻ�*/
    VOS_UINT32                              ulLineNo;                   /*����ʱ����к�*/
    VOS_UINT32                              ulErrPos;                   /*���ֽ������ʱ�̵�λ��*/
    VOS_UINT32                              ulErrByte;
    VOS_UINT8                               ucProtocolVersionOfCn;      /*�����Э��汾*/
    VOS_UINT8                               ucExtIeNum;                 /*�������չ��Ԫ�ļ���*/
    VOS_UINT8                               aucRsv[2];
    VOS_UINT32                              aulRsv[10];                 /*��������ں�����չ*/
} LPP_DEBUG_INFO_STRU;


/*Lģʹ��*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}PS_HEADER_STRU;

/*Lģʹ��
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[2];
}LHPA_MSG_HEADER_STRU;*/






/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_EncodeBitSteam(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      *pulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);
extern VOS_VOID NAS_LPP_SetBitStreamFromStream(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      ulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);


extern VOS_UINT32 NAS_LPP_GetParamFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      ulPos,
                                            VOS_UINT8       usLen);
extern VOS_UINT32 NAS_LPP_GetDataFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      *ulPos,
                                            VOS_UINT8       usLen);

extern VOS_UINT32 NAS_LPP_GetLongDataFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT8       usLen,
                                                VOS_UINT64      *pllDestData);
extern VOS_UINT32 NAS_LPP_GetLongBitFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT16       usLen,
                                                VOS_UINT8      *pllDestData);

extern VOS_UINT16 NAS_LPP_EncodeExtBit(
                        VOS_UINT16      *pBitPos,
                        VOS_UINT8       *pEncodeOutMsg);
extern VOS_VOID NAS_LPP_EncodeBitsLess8(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       ucSource);

extern VOS_UINT32  NAS_LPP_DecodeExtIeWithPartValid(
                        VOS_UINT8                               *pDecodeBitStream,
                        VOS_UINT32                              *pCurrentBitPos,
                        VOS_UINT32                              ulInvalidExtIeLen);

extern VOS_UINT32  NAS_LPP_Decode_ExtChoiceCellId(
                                    VOS_UINT8                       *pDecodeBitStream,
                                    VOS_UINT32                      *pCurrentBitPos,
                                    VOS_UINT8                       ucLen,
                                    VOS_UINT32                      *pExtChoiceValue);

extern VOS_VOID NAS_LPP_EncodeEncodeLongData(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT32      ulSource);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif











































