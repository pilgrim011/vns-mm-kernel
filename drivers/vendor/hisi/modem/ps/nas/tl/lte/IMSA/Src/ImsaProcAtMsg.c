/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcAtMsg.c
  Description     : ��C�ļ�������IMSAģ�鴦��AT�����ʵ��
  History           :
     1.leili 00132387      2013-10-12  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "ImsaProcAtMsg.h"
#include    "ImsaEntity.h"
#include    "ImsaPublic.h"
#include    "ImsaServiceManagement.h"
#include    "ImsaConnManagement.h"
#include    "ImsaImsAdaption.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IMSAPROCATMSG_C
#define    THIS_NAS_FILE_ID    NAS_FILE_ID_IMSAPROCATMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
extern VOS_VOID IMSA_SndMsgAtCiregSetCnf (VOS_UINT8 ucOpId, VOS_UINT16 usClientId,VOS_UINT32 ulRslt);
extern VOS_VOID IMSA_SndMsgAtCiregQryCnf
(
    VOS_UINT8 ucOpId,
    VOS_UINT16 usClientId,
    VOS_UINT32 ulRegInfo
);
extern VOS_VOID IMSA_SndMsgAtCirepSetCnf (VOS_UINT8 ucOpId, VOS_UINT16 usClientId, VOS_UINT32 ulRslt);
extern VOS_VOID IMSA_SndMsgAtCirepQryCnf
(
    VOS_UINT8 ucOpId,
    VOS_UINT16 usClientId,
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops
);


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_ProcMsgCiregSetReq
 Discription    : �յ�ID_AT_IMSA_CIREG_SET_REQ��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgCiregSetReq (const AT_IMSA_CIREG_SET_REQ_STRU *pstCiregSetReq)
{
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_ProcMsgCiregSetReq is entered! ");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsgCiregSetReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstCiregSetReq)
    {
        IMSA_WARN_LOG("IMSA_ProcMsgCiregSetReq: Input is null! ");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsgCiregSetReq_ENUM, LNAS_NULL_PTR);
        return;
    }

    pstImsaAtControl = IMSA_GetAtControlAddress();

    if (AT_IMSA_IMS_REG_STATE_REPROT_BUTT <= pstCiregSetReq->enCireg )
    {
        ulRslt = VOS_ERR;
    }
    else
    {
        /*�����Ƿ������ϱ�����*/
        pstImsaAtControl->enCireg = pstCiregSetReq->enCireg;

        ulRslt = VOS_OK;
    }

    /* ��AT���ͻظ���Ϣ*/
    IMSA_SndMsgAtCiregSetCnf(pstCiregSetReq->ucOpId,pstCiregSetReq->usClientId,ulRslt);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCiregSetCnf
 Discription    : ����ID_AT_IMSA_CIREG_SET_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCiregSetCnf (VOS_UINT8 ucOpId, VOS_UINT16 usClientId,VOS_UINT32 ulRslt)
{

    IMSA_AT_CIREG_SET_CNF_STRU          *pstCiregSetCnf;

    /*������Ϣ�ռ�*/
    pstCiregSetCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREG_SET_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCiregSetCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCiregSetCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCiregSetCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCiregSetCnf),
                    IMSA_GET_MSG_LENGTH(pstCiregSetCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCiregSetCnf));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCiregSetCnf,ID_IMSA_AT_CIREG_SET_CNF);

    /*��д��Ϣ����*/
    pstCiregSetCnf->ucOpId = ucOpId;
    pstCiregSetCnf->usClientId = usClientId;
    pstCiregSetCnf->ulResult = ulRslt;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCiregSetCnf);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCireguInd
 Discription    : ����ID_AT_IMSA_CIREGU_IND��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCireguInd (VOS_UINT32 ulRegInfo)
{
    IMSA_AT_CIREGU_IND_STRU             *pstCireguInd;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    if (AT_IMSA_IMS_REG_STATE_DISABLE_REPORT == pstImsaAtControl->enCireg)
    {
        IMSA_INFO_LOG("IMSA_SndMsgAtCireguInd: NOT SEND CIREGU IND MSG!");
        TLPS_PRINT2LAYER_INFO(IMSA_SndMsgAtCireguInd_ENUM, 1);
        return;
    }

    /*������Ϣ�ռ�*/
    pstCireguInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREGU_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCireguInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCireguInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_INFO(IMSA_SndMsgAtCireguInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCireguInd),
                    IMSA_GET_MSG_LENGTH(pstCireguInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCireguInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCireguInd,ID_IMSA_AT_CIREGU_IND);

    /*��д��Ϣ����*/
    pstCireguInd->ucOpId = 0;
    pstCireguInd->usClientId = 0x3fff;

    pstCireguInd->ulRegInfo = ulRegInfo;

    if (AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT == pstImsaAtControl->enCireg)
    {
        pstCireguInd->bitOpExtInfo = VOS_TRUE;
        pstCireguInd->ulExtInfo = 0;
    }

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCireguInd);
    return;
}


/*****************************************************************************
 Function Name  : IMSA_ProcMsgCiregQryReq
 Discription    : �յ�ID_AT_IMSA_CIREG_QRY_REQ��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgCiregQryReq (const AT_IMSA_CIREG_QRY_REQ_STRU *pstCiregQryReq)
{
    VOS_UINT32                          ulRegInfo;

    IMSA_INFO_LOG("IMSA_ProcMsgCiregQryReq is entered! ");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsgCiregQryReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstCiregQryReq)
    {
        IMSA_WARN_LOG("IMSA_ProcMsgCiregQryReq: Input is null! ");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsgCiregQryReq_ENUM, LNAS_NULL_PTR);
        return;
    }

    ulRegInfo = IMSA_SRV_GetAtRegStatusFromSrvStatus(IMSA_SRV_GetNormalSrvStatus());


    /* ��AT���ͻظ���Ϣ*/
    IMSA_SndMsgAtCiregQryCnf(pstCiregQryReq->ucOpId,pstCiregQryReq->usClientId,ulRegInfo);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCiregQryCnf
 Discription    : ����ID_AT_IMSA_CIREG_QRY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCiregQryCnf
(
    VOS_UINT8 ucOpId,
    VOS_UINT16 usClientId,
    VOS_UINT32 ulRegInfo
)
{
    IMSA_AT_CIREG_QRY_CNF_STRU          *pstCiregQryCnf;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    /*������Ϣ�ռ�*/
    pstCiregQryCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCiregQryCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCiregQryCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCiregQryCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCiregQryCnf),
                    IMSA_GET_MSG_LENGTH(pstCiregQryCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCiregQryCnf));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCiregQryCnf,ID_IMSA_AT_CIREG_QRY_CNF);

    /*��д��Ϣ����*/
    pstCiregQryCnf->ucOpId = ucOpId;
    pstCiregQryCnf->usClientId = usClientId;

    pstCiregQryCnf->ulRegInfo = ulRegInfo;

    if (AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT == pstImsaAtControl->enCireg)
    {
        pstCiregQryCnf->bitOpExtInfo = VOS_TRUE;
        pstCiregQryCnf->ulExtInfo = 0;
    }
    pstCiregQryCnf->enCireg = pstImsaAtControl->enCireg;
    pstCiregQryCnf->ulResult = VOS_OK;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCiregQryCnf);
    return;
}


/*****************************************************************************
 Function Name  : IMSA_ProcMsgCirepSetReq
 Discription    : �յ�ID_AT_IMSA_CIREP_SET_REQ��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgCirepSetReq (const AT_IMSA_CIREP_SET_REQ_STRU *pstCirepSetReq)
{
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;
    VOS_UINT32                          ulRslt;

    IMSA_WARN_LOG("IMSA_ProcMsgCirepSetReq is entered! ");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsgCirepSetReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstCirepSetReq)
    {
        IMSA_WARN_LOG("IMSA_ProcMsgCirepSetReq: Input is null! ");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsgCirepSetReq_ENUM, LNAS_NULL_PTR);
        return;
    }

    pstImsaAtControl = IMSA_GetAtControlAddress();

    if (AT_IMSA_IMSVOPS_CAPABILITY_BUTT <= pstCirepSetReq->enReport)
    {
        ulRslt = VOS_ERR;
    }
    else
    {
        /*�����Ƿ������ϱ�����*/
        pstImsaAtControl->enReport = pstCirepSetReq->enReport;
        ulRslt = VOS_OK;
    }

    /* ��AT���ͻظ���Ϣ*/
    IMSA_SndMsgAtCirepSetCnf(pstCirepSetReq->ucOpId,pstCirepSetReq->usClientId,ulRslt);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCirepSetCnf
 Discription    : ����ID_AT_IMSA_CIREG_SET_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCirepSetCnf (VOS_UINT8 ucOpId, VOS_UINT16 usClientId, VOS_UINT32 ulRslt)
{
    IMSA_AT_CIREP_SET_CNF_STRU          *pstCirepSetCnf;

    /*������Ϣ�ռ�*/
    pstCirepSetCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREP_SET_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCirepSetCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCirepSetCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCirepSetCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCirepSetCnf),
                    IMSA_GET_MSG_LENGTH(pstCirepSetCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCirepSetCnf));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCirepSetCnf,ID_IMSA_AT_CIREP_SET_CNF);

    /*��д��Ϣ����*/
    pstCirepSetCnf->ucOpId = ucOpId;
    pstCirepSetCnf->usClientId = usClientId;
    pstCirepSetCnf->ulResult = ulRslt;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCirepSetCnf);
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCirephInd
 Discription    : ����ID_AT_IMSA_CIREPH_IND��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCirephInd (AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32   enHandover)
{
    IMSA_AT_CIREPH_IND_STRU             *pstCirephInd;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    if (AT_IMSA_CIREP_REPORT_DISENABLE == pstImsaAtControl->enReport)
    {
        IMSA_INFO_LOG("IMSA_SndMsgAtCirephInd: NOT SEND CIREPH IND MSG!");
        TLPS_PRINT2LAYER_INFO(IMSA_SndMsgAtCirephInd_ENUM, 1);
        return;
    }

    /*������Ϣ�ռ�*/
    pstCirephInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREPH_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCirephInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCirephInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCirephInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCirephInd),
                    IMSA_GET_MSG_LENGTH(pstCirephInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCirephInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCirephInd,ID_IMSA_AT_CIREPH_IND);

    /*��д��Ϣ����*/
    pstCirephInd->ucOpId = 0;
    pstCirephInd->usClientId = 0x3fff;


    pstCirephInd->enHandover = enHandover;


    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCirephInd);
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCirepiInd
 Discription    : ����ID_AT_IMSA_CIREPI_IND��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCirepiInd (AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops)
{
    IMSA_AT_CIREPI_IND_STRU             *pstCirepiInd;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    if (AT_IMSA_CIREP_REPORT_DISENABLE == pstImsaAtControl->enReport)
    {
        IMSA_INFO_LOG("IMSA_SndMsgAtCirepiInd: NOT SEND CIREPH IND MSG!");
        TLPS_PRINT2LAYER_INFO(IMSA_SndMsgAtCirepiInd_ENUM, 1);
        return;
    }

    /*������Ϣ�ռ�*/
    pstCirepiInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREPI_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCirepiInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCirephInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCirepiInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCirepiInd),
                    IMSA_GET_MSG_LENGTH(pstCirepiInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCirepiInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCirepiInd,ID_IMSA_AT_CIREPI_IND);


    /*��д��Ϣ����*/
    pstCirepiInd->ucOpId = 0;
    pstCirepiInd->usClientId = 0x3fff;


    pstCirepiInd->enImsvops = enImsvops;


    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCirepiInd);
    return;
}


/*****************************************************************************
 Function Name  : IMSA_ProcMsgCirepQryReq
 Discription    : �յ�ID_AT_IMSA_CIREG_QRY_REQ��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgCirepQryReq (const AT_IMSA_CIREP_QRY_REQ_STRU *pstCiregQryReq)
{
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops;

    IMSA_INFO_LOG("IMSA_ProcMsgCirepQryReq is entered! ");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsgCirepQryReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstCiregQryReq)
    {
        IMSA_WARN_LOG("IMSA_ProcMsgCirepQryReq: Input is null! ");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsgCirepQryReq_ENUM, LNAS_NULL_PTR);
        return;
    }

    enImsvops = IMSA_GetNwImsVoiceCap();

    if (AT_IMSA_IMSVOPS_CAPABILITY_BUTT == enImsvops)
    {
        enImsvops = AT_IMSA_NW_NOT_SUPORT_IMSVOPS;
    }

    /* ��AT���ͻظ���Ϣ*/
    IMSA_SndMsgAtCirepQryCnf(pstCiregQryReq->ucOpId,pstCiregQryReq->usClientId,enImsvops);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgVolteImpuQryReq
 Discription    : �յ�ID_AT_IMSA_VOLTEIMPU_QRY_REQ��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181      2013-12-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgVolteImpuQryReq(const AT_IMSA_VOLTEIMPU_QRY_REQ_STRU *pstVolteImpuQryReq)
{
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    IMSA_INFO_LOG("IMSA_ProcMsgVolteImpuQryReq is entered! ");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsgVolteImpuQryReq_ENUM, LNAS_ENTRY);

    /* ��Ҫ����CLENT ID��OPID�����ڻظ�ʱʹ�� */
    pstImsaAtControl->usClientId = pstVolteImpuQryReq->usClientId;
    pstImsaAtControl->ucOpId = pstVolteImpuQryReq->ucOpId;

    /* ��IMSA���Ͳ�ѯ���� */
    IMSA_SendImsVolteImpuQryReq();
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgQryVolteImpuCnf()
 Description    : IMS�ظ�IMPU��ѯ�¼��Ĵ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181       2013-12-19  Draft Enact
*****************************************************************************/
/*lint -e818*/
/*lint -e830*/
VOS_VOID IMSA_SndMsgAtQryVolteImpuCnf
(
    VOS_UINT32 ulResult,
    VOS_UINT32 ulImpuLen,
    VOS_CHAR *pucImpu
)
{
    IMSA_AT_VOLTEIMPU_QRY_CNF_STRU          *pstVolteImpuQryCnf;

    IMSA_AT_CONTROL_STRU                    *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    /*������Ϣ�ռ�*/
    pstVolteImpuQryCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_VOLTEIMPU_QRY_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstVolteImpuQryCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtQryVolteImpuCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtQryVolteImpuCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstVolteImpuQryCnf),
                    IMSA_GET_MSG_LENGTH(pstVolteImpuQryCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstVolteImpuQryCnf));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstVolteImpuQryCnf,ID_IMSA_AT_VOLTEIMPU_QRY_CNF);

    /*��д��Ϣ����*/
    pstVolteImpuQryCnf->ucOpId = pstImsaAtControl->ucOpId;
    pstVolteImpuQryCnf->usClientId = pstImsaAtControl->usClientId;

    pstVolteImpuQryCnf->ulResult = ulResult;

    pstVolteImpuQryCnf->ulImpuLen = ulImpuLen;

    if (VOS_NULL_PTR != pucImpu)
    {
        IMSA_UtilStrNCpy(pstVolteImpuQryCnf->aucImpu, pucImpu, AT_IMSA_IMPU_MAX_LENGTH);
    }

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstVolteImpuQryCnf);

    return;
}
/*lint +e830*/
/*lint +e818*/


/*****************************************************************************
 Function Name  : IMSA_SndMsgAtCirepQryCnf
 Discription    : ����ID_AT_IMSA_CIREP_QRY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. leili 00132387      2013-10-12  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtCirepQryCnf
(
    VOS_UINT8 ucOpId,
    VOS_UINT16 usClientId,
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops
)
{
    IMSA_AT_CIREP_QRY_CNF_STRU          *pstCirepQryCnf;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    /*������Ϣ�ռ�*/
    pstCirepQryCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCirepQryCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtCirepQryCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtCirepQryCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstCirepQryCnf),
                    IMSA_GET_MSG_LENGTH(pstCirepQryCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstCirepQryCnf));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstCirepQryCnf,ID_IMSA_AT_CIREP_QRY_CNF);


    /*��д��Ϣ����*/
    pstCirepQryCnf->ucOpId = ucOpId;
    pstCirepQryCnf->usClientId = usClientId;
    pstCirepQryCnf->enReport = pstImsaAtControl->enReport;
    pstCirepQryCnf->enImsvops = enImsvops;
    pstCirepQryCnf->ulResult = VOS_OK;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstCirepQryCnf);
    return;
}
/*lint +e961*/
/*****************************************************************************
 Function Name  : IMSA_SndMsgAtPdpActInd
 Discription    : ����ID_IMSA_AT_VT_PDP_ACTIVATE_IND��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2014-08-04  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtPdpActInd (const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo)
{
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU    *pstPdpActInd;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};


    /*������Ϣ�ռ�*/
    pstPdpActInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_VT_PDP_ACTIVATE_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstPdpActInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtPdpActInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtPdpActInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstPdpActInd),
                    IMSA_GET_MSG_LENGTH(pstPdpActInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstPdpActInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstPdpActInd,ID_IMSA_AT_VT_PDP_ACTIVATE_IND);


    /*��д��Ϣ����*/
    pstPdpActInd->ucOpId = 0;
    pstPdpActInd->usClientId = 0x3fff;

    pstPdpActInd->stPdpAddr.enPdpType = pstPdpInfo->stPdpAddr.enIpType;

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV4��ַ */
        IMSA_MEM_CPY_S( pstPdpActInd->stPdpAddr.aucIpv4Addr,
                        IMSA_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpAddr.aucIpV4Addr,
                        IMSA_IPV4_ADDR_LEN);

        /* ����IPV4 DNS��ַ */
        pstPdpActInd->stIpv4Dns.bitOpPrimDnsAddr = pstPdpInfo->stPdpIpv4Dns.bitOpPriDns;
        IMSA_MEM_CPY_S( pstPdpActInd->stIpv4Dns.aucPrimDnsAddr,
                        TAF_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpIpv4Dns.aucPriDns,
                        IMSA_IPV4_ADDR_LEN);

        pstPdpActInd->stIpv4Dns.bitOpSecDnsAddr = pstPdpInfo->stPdpIpv4Dns.bitOpSecDns;
        IMSA_MEM_CPY_S( pstPdpActInd->stIpv4Dns.aucSecDnsAddr,
                        TAF_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpIpv4Dns.aucSecDns,
                        IMSA_IPV4_ADDR_LEN);
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            /* ����IPV6��ַ */
            IMSA_MEM_CPY_S( pstPdpActInd->stPdpAddr.aucIpv6Addr,
                            TAF_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN);

            /* ����IPV6 DNS��ַ */
            pstPdpActInd->stIpv6Dns.bitOpPrimDnsAddr = pstPdpInfo->stPdpIpv6Dns.bitOpPriDns;
            IMSA_MEM_CPY_S( pstPdpActInd->stIpv6Dns.aucPrimDnsAddr,
                            TAF_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucPriDns,
                            IMSA_IPV6_ADDR_LEN);

            pstPdpActInd->stIpv6Dns.bitOpSecDnsAddr = pstPdpInfo->stPdpIpv6Dns.bitOpSecDns;
            IMSA_MEM_CPY_S( pstPdpActInd->stIpv6Dns.aucSecDnsAddr,
                            TAF_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucSecDns,
                            IMSA_IPV6_ADDR_LEN);
        }
    }


    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstPdpActInd);
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SndMsgAtPdpDeactInd
 Discription    : ����ID_IMSA_AT_VT_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2014-08-04  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtPdpDeactInd (TAF_PDP_TYPE_ENUM_UINT8             enPdpType)
{
    IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU    *pstPdpDeactInd;
    /*VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};*/


    /*������Ϣ�ռ�*/
    pstPdpDeactInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstPdpDeactInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsgAtPdpDeactInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsgAtPdpDeactInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstPdpDeactInd),
                    IMSA_GET_MSG_LENGTH(pstPdpDeactInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstPdpDeactInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstPdpDeactInd,ID_IMSA_AT_VT_PDP_DEACTIVATE_IND);


    /*��д��Ϣ����*/
    pstPdpDeactInd->ucOpId = 0;
    pstPdpDeactInd->usClientId = 0x3fff;

    pstPdpDeactInd->enPdpType = enPdpType;



    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstPdpDeactInd);
    return;
}


/*****************************************************************************
 Function Name  : IMSA_SndMsgAtMtStatusInd
 Discription    : ����ID_IMSA_AT_MT_STATES_IND��Ϣ�Ĵ���
 Input          : ulCallId    ����id
                  mtStates    ����״̬�� 0�յ�INVITE, 1���йҶ�
                  pMoNumber   ���к���
 Output         : None
 Return         : None
 History:
      1. mengchao 00277840  2015-03-18  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SndMsgAtMtStatusInd(const IMSA_MT_STATUS_REPORT_STRU    *pstMtReport)
{
    IMSA_AT_MT_STATES_IND_STRU        *pstMtStatusInd = VOS_NULL_PTR;

    pstMtStatusInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_AT_MT_STATES_IND_STRU));

    if (VOS_NULL_PTR == pstMtStatusInd)
    {
        IMSA_ERR_LOG("IMSA_SndMsgAtMtStatusInd:ERROR:Alloc Msg fail!");
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMtStatusInd),
                    IMSA_GET_MSG_LENGTH(pstMtStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMtStatusInd));

    IMSA_WRITE_AT_MSG_MSG_HEAD(pstMtStatusInd, ID_IMSA_AT_MT_STATES_IND);

    pstMtStatusInd->ucOpId = 0;
    pstMtStatusInd->usClientId = 0x3fff;
    pstMtStatusInd->ulCauseCode = pstMtReport->ulCauseCode;
    pstMtStatusInd->ucMtStatus = pstMtReport->enMtStatus;
    IMSA_UtilStrNCpy((VOS_CHAR*)pstMtStatusInd->aucAsciiCallNum, pstMtReport->acNumber, IMSA_CALL_NUMBER_MAX_NUM);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstMtStatusInd);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcAtMsg.c */




