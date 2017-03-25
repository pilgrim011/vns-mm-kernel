/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tft_context.h
  �� �� ��   : ����
  ��    ��   : h50774
  ��������   : 2012��12��29��
  ����޸�   :
  ��������   : tft_context.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��29��
    ��    ��   : h50774
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TFT_CONTEXT_H__
#define __TFT_CONTEXT_H__


#define SDB_MAX_PF_PER_TFT                4

typedef DPE_FILTER_CONTENT_S    SDB_PACKET_FILTER_S;

typedef struct tagPF_INFO
{
    VOS_UINT32     ulA10Index;
    UCHAR     ucFlowID;       /* IP Flow ID: pdnId(4bit) + flowid(4bit)   */
    UCHAR     bDirection:1,   /* PF Direction */
              bActive:1,      /* Used by NP */
              FlowPriority:4,
              bUsedFlag:1,
              bHasPfInfo:1;  /*��ʾ�Ƿ�ò����ڴ��Ƿ�д����PF��Ϣ*/
    UCHAR ucResv[2];                /* �ֽڶ��� */
    SDB_PACKET_FILTER_S stPacketFileter;
}VOS_PACKED SDB_PF_INFO_S;

typedef struct tagSDB_PDSN_TFT_CONTEXT
{
    VOS_UINT32   ulTftIndex;
    VOS_UINT32   ulPdnIndex;
    UCHAR   ucPFNumbers;   /*��ʵ����packet filter����Ŀ ���۸�filter�Ƿ��Ѿ�ʹ��  �����Ҫ�����HSGW */
    UCHAR   ucBindNumbers;
    UCHAR   ucResv[2];                /* �ֽڶ��� */
    SDB_PF_INFO_S  stTFT_Info[SDB_MAX_PF_PER_TFT];      /* Flow's TFT */

    /*****************************************/
    /*�����ֶ�����ά���򲹶�******************/
    UCHAR aucPatchReserve[4];
}VOS_PACKED SDB_PDSN_TFT_CONTEXT_S;


#endif /* __TFT_CONTEXT_H__ */
