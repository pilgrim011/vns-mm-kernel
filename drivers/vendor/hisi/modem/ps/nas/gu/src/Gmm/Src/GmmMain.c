/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmMain.c
  Description   : GMM TASK���������ڻ�����Ϣ�ַ�������Դ�ļ�
  Function List :
              GmmMsgProc
              Gmm_AbortCurrentService
              Gmm_BufSmDataReqMsg
              GMM_ComCheckIntegrityProtection
              GMM_ComCheckRauIntegrityProtection
              Gmm_ComCmpLai
              Gmm_ComForbiddenList
              Gmm_ComNetModeChange
              Gmm_ComNetModeChangeGsm
              Gmm_ComPlmnSearchInit
              Gmm_ComReset
              Gmm_ComServiceSts
              Gmm_ComStaChg
              Gmm_ComUnrealProc
              Gmm_ComVariantInit
              Gmm_DealWithBuffAfterProc
              Gmm_DealWithBuffInProc
              GMM_GetCurServiceStatus
              Gmm_GetGprsState
              Gmm_GetState
              Gmm_GmmStatusMsgMake
              Gmm_HoldBufferFree
              Gmm_MsgDistribute
              GMM_PrintState
              Gmm_RcvAcInfoChangeInd
              Gmm_RcvCmServReq_DeregAtmpToAtch
              Gmm_RcvCmServReq_RegAtmpToUpdt
              Gmm_RcvGmmStatusMsg
              Gmm_RcvLLCInform
              Gmm_RcvMmcAuthenticationFailureInd
              Gmm_RcvMmcCmServiceInd
              Gmm_RcvMmcCmServiceInd_InProc
              Gmm_RcvMmcCmServiceInd_RegNmlServ
              Gmm_RcvMmcCmServiceRejectInd
              Gmm_RcvMmcCoverageLostInd
              Gmm_RcvMmcGmmModeChangeReq
              Gmm_RcvMmcPlmnSearchInitiated
              Gmm_RcvMmcPlmnUserSelReq
              Gmm_RcvMmcRegisterInitiation
              Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch
              Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
              Gmm_RcvMmcRegisterInitiation_ServReqInit
              Gmm_RcvMmcStartReq
              Gmm_RcvMmcSysInfoInd
              Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch
              Gmm_RcvMmcSysInfoInd_DeregInit
              Gmm_RcvMmcSysInfoInd_DeregNmlServ
              Gmm_RcvMmcSysInfoInd_RauInit
              Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt
              Gmm_RcvMmcSysInfoInd_RegInit
              Gmm_RcvMmcSysInfoInd_RegNmlServ
              Gmm_RcvMmcSysInfoInd_RegNoCell
              Gmm_RcvMmcSysInfoInd_RegUpdtNeed
              Gmm_RcvMmcSysInfoInd_ServReqInit
              Gmm_RcvMmcSysInfoInd_SuspWaitSys
              Gmm_RcvRrmmDataInd
              Gmm_RcvRrmmEstCnf
              Gmm_RcvRrmmEstCnf_DeregInit
              Gmm_RcvRrmmEstCnf_DeregNmlServ
              Gmm_RcvRrmmEstCnf_RauInit
              Gmm_RcvRrmmEstCnf_RegImsiDtchInit
              Gmm_RcvRrmmEstCnf_RegInit
              Gmm_RcvRrmmEstCnf_ServReqInit
              Gmm_RcvRrmmRelInd
              Gmm_RcvRrmmRelInd_DeregInit
              Gmm_RcvRrmmRelInd_DeregNmlServ
              Gmm_RcvRrmmRelInd_RauInit
              Gmm_RcvRrmmRelInd_RegImsiDtchInit
              Gmm_RcvRrmmRelInd_RegInit
              Gmm_RcvRrmmRelInd_RegNmlServ
              Gmm_RcvRrmmRelInd_ServReqInit
              Gmm_RcvSmDataReq
              Gmm_RcvSmDataReq_DeregInit
              Gmm_RcvSmDataReq_RegNmlServ
              Gmm_RcvSmPdpStatusInd
              Gmm_RcvTcDataReq
              Gmm_RcvTcTestReq
              Gmm_TaskInit
              GRM_Inform_Gmm
              WuepsGmmPidInit

  History       :
    1.  ��־��  2003.12.05  �¹�����
    2.  l40632  2005.10.19  ��ӡȫ�����ݽṹ ���ⵥA32D00636
    3.��    ��   : 2006��2��17��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01287����ӡ����
    4.  s46746  2006-03-15  �������ⵥA32D02388�޸�
    5.  s46746  2006-03-18  �������ⵥA32D02141�޸�

    6.��    ��   : 2006��3��24��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                   �����RR����ԭ�����
    7.  s46746  2006-03-27  �������ⵥA32D02387�޸�
    8.  s46746  2006-04-03  �������ⵥA32D01509�޸�

    9.��    ��   : 2006��4��19��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D03208
    10.x51137 2006/4/21 A32D03244
    11. l40632  2006-04-24  �������ⵥA32D03344�޸�
    12. s46746  2006-05-08  �������ⵥA32D03487�޸�
    13. l40632  2006-05-19  �������ⵥA32D03888�޸�
    14. l40632 2006-05-29 �������ⵥA32D03821�޸�
    15. l40632 2006-06-19 �������ⵥA32D04282�޸�
    16.  s46746  2006-06-16  �������ⵥA32D03581�޸�
    17.��    ��   : 2006��9��9��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D05604
    18.��    ��   : 2006��9��9��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D05653
    19.��    ��   : 2006��9��23��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D06377
    20.��    ��   : 2006��10��9��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D05744
    21.x51137 2006/11/3 A32D06511
    22.��    ��   : 2006��11��1��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D06572
    23.��    ��   : 2006��11��2��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D06406
    24.��    ��   : 2006��11��6��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D06867
    25.��    ��   : 2006��11��20��
       ��    ��   : s46746
       �޸�����   : �������������ⵥ�ţ�A32D07433
    26.��    ��   : 2006��12��07��
       ��    ��   : s46746
       �޸�����   : �������������ⵥ�ţ�A32D07799
    27.��    ��   : 2007��1��10��
       ��    ��   : x51137
       �޸�����   : A32D08279
    28.��    ��   : 2007��01��04��
       ��    ��   : luojian,id:60022475
       �޸�����   : �������ⵥ�ţ�A32D06408
    29.��    ��   : 2007��03��20��
       ��    ��   : x51137
       �޸�����   : A32D09192
    30.��    ��   : 2007��3��22��
       ��    ��   : liurui id:40632
       �޸�����   : �������ⵥ�ţ�A32D09593
    31.��    ��   : 2007��3��30��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D09854
    32.��    ��   : 2007��4��2��
       ��    ��   : x51137
       �޸�����   : A32D09789
    33.��    ��   : 2007��4��5��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D10023
    34.��    ��   : 2007��4��26��
       ��    ��   : liurui id:40632
       �޸�����   : �������ⵥ�ţ�A32D10052
    35.��    ��   : 2007��6��9��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D11579
    36.��    ��   : 2007��06��22��
       ��    ��   : l60022475
       �޸�����   : �������ⵥ��: A32D11911
    37.��    ��   : 2007��06��29��
       ��    ��   : l65478
       �޸�����   : �������ⵥ��: A32D11896
    38.��    ��   : 2007��07��02��
       ��    ��   : l65478
       �޸�����   : �������ⵥ��: A32D10052
    39.��    ��   : 2007��07��05��
        ��    ��   : Li Jilin
        �޸�����   : A32D11950
    40.��    ��   : 2007��07��10��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥA32D11966
    41.��    ��   : 2007��7��14��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D12438
    42.��    ��   : 2007��07��11��
       ��    ��   : hanlufeng 41410
       �޸�����   : �������ⵥ�ţ�A32D12294
    43.��    ��   : 2007��07��10��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D12268
    44.��    ��   : 2007��07��11��
       ��    ��   : hanlufeng 41410
       �޸�����   : �������ⵥ�ţ�A32D11966
    45.��    ��   : 2007��08��08��
       ��    ��   : l65478
       �޸�����   : �������ⵥ�ţ�A32D12663
    46.��    ��   : 2007��08��14��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D12689,
                    GMM_REGISTERED_IMSI_DETACH_INITIATED״̬��ӦPDP��������
    47.��    ��   : 2007��8��28��
       ��    ��   : l60022475
       �޸�����   : ���ⵥ�ţ�A32D12744,��ʼ��GMM Timer���
    48.��    ��   : 2007��09��03��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�AT2D01459
    49.��    ��   : 2007��09��10��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D12829
    50.��    ��   : 2007��9��27��
       ��    ��   : s46746
       �޸�����   : ������Ч��Ϣ��RRMM_NAS_INFO_CHANGE��Ϣ���õ�
    51.��    ��   : 2007��10��10��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D12948
    52.��    ��   : 2007��10��13��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13060
    53.��    ��   : 2007��10��26��
       ��    ��   : l39007
       �޸�����   : A32D13207  Gmm_RcvMmcSysInfoInd������ָ��W����ʱ���GMM����
                    ���ӱ�־�Ĵ���
    54.��    ��   : 2007-10-26
       ��    ��   : hanlufeng
       �޸�����   : A32D13172
    55.��    ��   : 2007��11��16��
       ��    ��   : hanlufeng 41410
       �޸�����   : A32D12187
    56.��    ��   : 2007��11��20��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13510,������״ָ̬ʾ�����P/TMSI
    57.��    ��   : 2007��11��22��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13475,�޸���ϵͳ�ı��ָ�ɵ�old TLLI�Ϳ���������ԿΪȫ0����
    58.��    ��   : 2007��12��04��
       ��    ��   : s46746
       �޸�����   : 1.GMMģ�����ATTACH��RAUʱ�������ʱ����������������
                      �ᵼ��LLC��ATTACH��RAU�ӳٷ��ͣ�ʹ��ATTACH��RAUʱ�������
                    2.GMM�ڽ���RAU����ʱ�����DRX�������ı䣬����������Ϣ��
                      ��DRX������������SGSN��RAUʱ�����ܵ������಻ʶ��UE��DR
                      X������  ʹ��RAU���ܳɹ���
    59.��    ��   : 2007��12��08��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13826,�յ�REL_IND��������йػ���Ϣ��Ҫ����
    60.��    ��   : 2007��12��11��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13845,����������MMC����������ϵͳ��ͬPLMN
                    ����
    61.��    ��   : 2007��12��15��
       ��    ��   : l00107747
       �޸�����   : ���ⵥ��:A32D13897
    62.��    ��   : 2007��12��18��
       ��    ��   : s46746
       �޸�����   : ���ⵥA32D13913��GMM�ڽ��м�Ȩ�����У����rand��ͬ��Ҳ��Ҫָ
                    ʾ��2�����㷨����Կ
    63.��    ��   : 2007��12��18��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13917,GMM����SM����͵�ǰ���ܴ�����Ҫ������Ҫ������
                    ���������ڴ�����
    64.��    ��   : 2007��12��20��
       ��    ��   : s46746
       �޸�����   : 2G3�л���W��RAU�����йҶϵ绰��RAU ACCEPT��Ϣ���յ���
                    ��RAU COMPLETE��Ϣδ���;ͽ�������RAU
    65.��    ��   : 2007��12��21��
       ��    ��   : l00107747
       �޸�����   : ���ⵥA32D13950,W֧��CS&PS,G�²�֧��PS���л���Wģʽ��GMMû�з�������RAU
    66.��    ��   : 2007��12��21��
       ��    ��   : l00107747
       �޸�����   : ���ⵥ��:A32D13951
    67.��    ��   : 2007��12��28��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
    68.��    ��   : 2008��3��17��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:AT2D02570,NAS B005�汾�����������
    69.��    ��   : 2008��7��2��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
    70.��    ��   : 2008��7��18��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ�ţ�AT2D03887,�޸�CS��Ч���������ģʽ�������
    71.��    ��   : 2008��7��24��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237,
                      ATTEMPT TO UPDATE/ATTACH ״̬��CM������
    72.��    ��   : 2008��7��28��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:AT2D03915,�޸�����RAU����,CS����Ѿ�����LAU�ɹ�����Ҫ
                    ����with IMSI Attach��RAU
    73.��    ��   : 2008��08��1��
       ��    ��   : luojian id:00107747
       �޸�����   : �������ⵥAT2D04486/AT2D04822,�޸�CM��������ܾ�ԭ��ֵΪ#4,
                    RR�����ͷź���,���� 24.008 4.5.1.1,4.2.2.3
    74.��    ��   : 2008��08��1��
       ��    ��   : luojian id:00107747
       �޸�����   : �������ⵥAT2D04837/AT2D04947,���� 24.008 4.1.1.1����L3��Ϣͳһ���������Լ��
    75.��    ��   : 2008��08��25��
       ��    ��   : ouyangfei id:00132663
       �޸�����   : �������ⵥ�ţ�AT2D04509,��������Ҫ�ĸ澯��
    76.��    ��   : 2008��9��18��
       ��    ��   : ouyangfei 00132663
       �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
    77.��    ��   : 2008��9��23��
       ��    ��   : o00132663
       �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
    78.��    ��   : 2008��9��26��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D05431
    79.��    ��   : 2008��10��20��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D06272
    80.��    ��   : 2008��10��20��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D06271
    81.��    ��   : 2008��10��30��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D06422
    82.��    ��   : 2008��11��03��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D06493
    83.��    ��   : 2008��12��3��
       ��    ��   : ouyangfei id:00132663
       �޸�����   : �������ⵥ�ţ�AT2D07165,��W�����RR���ӽ��������ж���������WRR��RRMM_REL_REQ��
    84.��    ��   : 2008��12��08��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D06899:MS Detach�������յ��ײ��ͷţ�
                    ��ʱ��ΪDetach�ɹ�������û�н�ȫ����
                    g_MmSubLyrShare.MmcShare.ucPsAttachFlg��ΪMMC_ATTACH_NOT_ALLOW
    85.��    ��   : 2008��12��26��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D07892:2Gģʽ�������û�ģʽA����B��
                    ��SDT�����в�ѯNAS MM������Ue Operation Mode
                    ��ʾΪUE_OPERATE_MODE_A
    86.��    ��   : 2009��01��15��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
    88.��    ��   : 2009��02��13��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ��:AT2D08906,��TA ��֤�����ⳡ����-HK��smartone UEû�д���attach״̬,�ͷ�����ҵ������.
    90.��    ��   : 2009��2��19��
       ��    ��   : o00132663
       �޸�����  : ���ⵥ��:AT2D09274,��GCF���ԡ�����12.4.1.3ʧ�ܣ�RAC�ı�ʱ��û�з���RAU��
    91.��    ��   : 2009��02��24��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D09321,MM��WRR�·���NAS_INFO_CHANGE_REQ TMSI��
                    �� plmnȫ F��ʹWAS����ʧ�ܣ�RRC���ӽ���ʧ�ܡ�
    92.��    ��   : 2009��03��12��
       ��    ��   : ouyangfei id:00132663
       �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
    93.��    ��   : 2009��03��21��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ��:AT2D09534,��ϵͳ�л���Ľ���ʧ�ܹ����йػ���Gmm/MM�Թػ���Ϣû�д�����������AT^CPAM��ʱ������Ӧ
    94.��    ��   : 2009��3��31��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ�ţ�AT2D10231/AT2D10624 ��RABM�����յ�Dsflowrpt�����ϱ���
                    ��PDP�����W�¶������漰 W->G->W���л�ʱ���������ָܻ�
    95.��    ��   : 2009��04��06��
       ��    ��   : l00130025
       �޸�����   : �������ⵥ�ţ�AT2D10790/AT2D10804��Gmm����VOS_RestartRelTimerʱ�������ָ�룬���µ��帴λ
    96.��    ��   : 2009��4��9��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:AT2D10867,��ϵͳ�ı��δ��ɵ�Detach����û�м���
    97.��    ��   : 2009��4��22��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D11234,RRC�����ͷţ�ԭ��ֵΪ"Directed Signalling
                    Connection Re-Establishment"��֮���ϱ�ϵͳ��Ϣ�ı䣬����ģʽ
                    ��I��ΪII������Rau������ԭ����д����Registration��������
                    Call Re-Establishment��������Э��Ҫ��
    98.��    ��   : 2009��5��5��
       ��    ��   : s62952
       �޸�����   : AT2D11639
    99.��    ��   : 2009��5��5��
       ��    ��   : x00115505
       �޸�����   : AT2D11784,����ATģʽ��A��CGʱ������imsi detach���̣�
                    �յ�detach accept��δ�ͷ���·��ֱ�ӷ���pdp���UE�յ�pdp
                    ������ܺ�����ظ�����pdp��������
   100.��    ��   : 2009��5��8��
       ��    ��   : x00115505
       �޸�����   : AT2D11792,ִ��GCF��������8.2.2.50ʱ����GMM����ʱ����Ӧpaging��Ϣ��������ʧ�ܡ�
   101.��    ��   : 2009��5��12��
       ��    ��   : x00115505
       �޸�����   : AT2D11814,2G��PPP����ʧ��
   102.��    ��   : 2009��6��30��
       ��    ��   : x00115505
       �޸�����   : AT2D12552,W��ѡ����֧��GPRS��GSMС������PS���ţ�TAFû���ж�
                    ��ǰ״̬�Ƿ�Ӧ�÷�����Ȼ���͸ö���
   103.��    ��   : 2009��7��2��
       ��    ��   : l60609
       �޸�����   : AT2D12314,��CMU�Զ��������յ�Ѱ�����ݣ���δ����R5��·
   104.��    ��   : 2009��7��7��
       ��    ��   : l60609
       �޸�����   : AT2D12732,����CGCLASSΪAȻ������ΪCG�������쳣
   105.��    ��   : 2009��7��22��
       ��    ��   : x00115505
       �޸�����   : AT2D13182,SM��ͬһ��NSAPI��������������PDP��������
   106.��    ��   : 2009��7��23��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�AT2D12878��GSM��HPLMN����ʱ���յ�GPRSѰ����PDP����(W��PDP������ͬ����)������Ҫ�ܼ�ʱ��Ӧ
   107.��    ��   : 2009��7��31��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�AT2D13446��GMM�ڽ���Detach��������ѡ����Ҫ��������RAU���̣�����ͷŽ���㣬
                    ����Deregister״̬δ��¼��־g_GmmGlobalCtrl.ucRaiChgRelFlg�����½��յ��ͷ�ָʾ�������ֽ�����Detach����
   108.��    ��   : 2009��8��3��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�AT2D13469������GCF����12.9.7c��PDP����ʱService Req���ܣ�
                    �ϲ�û��������ֹ�ù��̣�֮��פ����������С�����ٴη�����PDP����������Ϣ����������ʧ��
   109.��    ��   : 2009��8��22��
       ��    ��   : l60609
       �޸�����   : �������ⵥ�ţ�AT2D13782��G��ģ����ע��ɹ�������W��ģ����ʧ�ܣ������û�G��ģ��RAI����
                    PDP����ʧ��
   110.��    ��   : 2009��08��24��
       ��    ��   : x00115505
       �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
   111.��    ��   : 2009��08��29��
       ��    ��   : s46746
       �޸�����   : AT2D14108,GMMģ������ϵͳ��ѡ״̬���յ�ϵͳ��Ϣ�����С������ֹ��û�и��·���״̬
   112.��    ��   : 2009��9��7��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�AT2D14311������������GMM��������ʱ�Ƚ����������ͷţ��ᵼ�·���״̬��ʱ����ΪNormal service
   113.��    ��   : 2009��09��12��
       ��    ��   : s46746
       �޸�����   : ���ⵥ�ţ�AT2D14432,HPLMN��ʱ������ϵͳ��ѡ�����г�ʱû����������HPLMN����
   114.��    ��   : 2009��09��19��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ�ţ�AT2D14251,Service Requset�����У������·�ȥ���GMMֱ�Ӷ���
   115.��    ��   : 2009��09��22��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ�ţ�AT2D14627,��W������ģʽI��G������ģʽII��û�з���Rau
   116.��    ��   : 2009��09��25��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2d14773,�ػ�ʱ��SDT�п�ά�ɲ⹦�ܲ�ѯIMSIΪ��
   117.��    ��   : 2009��09��30��
       ��    ��   : x00115505
       �޸�����   : AT2D14857,פ����FPLMN�ϣ�GMM������״̬�޸�ΪGU3��
   118.��    ��   : 2009��10��22��
       ��    ��   : x00115505
       �޸�����   : AT2D15174,PDPȥ����ʧ��
   119.��    ��   : 2009��10��31��
       ��    ��   : x00115505
       �޸�����   : AT2D15076,��PSע�ᣬPS���ŷ����������ͷţ�ת��CS����
   120.��    ��   : 2009��11��3��
       ��    ��   : s46746
       �޸�����   : AT2D15367,��������޷�����������������У�NAS������ҵ����ʧ�ܻ�ı��״̬
   121.��    ��   : 2009��12��7��
       ��    ��   : s46746
       �޸�����   : ���ⵥ�ţ�AT2D15718,CS LAUʧ���Ĵ������޸�ΪCS LAUʧ���Ĵ�PS RAU/ATTACHʧ����κ�����
   122.��    ��   : 2009��12��17��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:GCF����8.1.2.3��8.1.2.9����ʧ��
   123.��    ��   : 2010��04��21��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D17739,�����ض�������������Ҫ��һ��
   125.��    ��   : 2010��6��17��
       ��    ��   : s46746
       �޸�����   : DTS2010061500077,�޿����������������쳣
*******************************************************************************/
#include "GmmInc.h"
#include "psprimitive.h"
#include "GmmCasGlobal.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasCommDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "GmmLmmInterface.h"
#include "NasGmmProcLResult.h"
#endif
#include "GmmMmInterface.h"
#include "NasMmcSndOm.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUsimmApi.h"

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_MAIN_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

NAS_GMM_CTRL_STATUS_ENUM_UINT8  gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

/*lint -save -e958 */

/*******************************************************************************
  Module:      GMM_ReportN2MOtaMsg
  Function:    ��trace�й�ȡGMM�Ŀտ���Ϣ
  Input:       NAS_MSG_STRU*   pNasMsg     SM�տ���Ϣ
  NOTE:
  Return:      VOS_VOID
  History:
      1. ³��    2009.07.11   �¹�����
*******************************************************************************/
VOS_VOID GMM_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportN2MOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_ACCEPT;
            break;

        case GMM_MSG_ATTACH_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REJECT;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ_BY_NET;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT;
            break;

        case GMM_MSG_RAU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_ACCEPT;
            break;

        case GMM_MSG_RAU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REJECT;
            break;

        case GMM_MSG_SERVICE_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_ACC;
            break;

        case GMM_MSG_SERVICE_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REJ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REQ;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REJ;
            break;

        case GMM_MSG_IDENTITY_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_REQUEST;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS;
            break;

        case GMM_MSG_GMM_INFORMATION:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_INFORMATION;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*������GMMģ��Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8 *)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__


/*****************************************************************************
 �� �� ��  : NAS_GMM_SetGmmSigFunc
 ��������  : ����GMM��g_GmmImportFunc�ĺ���ָ��,Gģ��ʹ�ø�ָ�룬ֱ������ΪW�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��1��
    ��    ��   : l00130025
    �޸�����   : �طŵ����������ָ���ָ���ַ����

*****************************************************************************/
VOS_VOID  NAS_GMM_SetGmmSigFunc(VOS_VOID)
{
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RestoreContextData
 ��������  : �ָ�GMMȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��04��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��1��
    ��    ��   : l00130025
    �޸�����   : �طŵ����������ָ���ָ���ַ����
  3.��    ��   : 2011��11��30��
    ��    ��   : z00161729
    �޸�����   : pc�ط�ѹ�������޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;
    VOS_UINT32                                               ulMsgAddrForSm;

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                  + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                  + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                  + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                  + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                  + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                  + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                  + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                  + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                  + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                  + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                  + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                  + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* gucGmmInitStateĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gucGmmInitState;
    ulDestLen   = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmInterRatCellReselectĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulDestLen   = sizeof(g_GmmInterRatCellReselect);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmCasGlobalCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulDestLen   = sizeof(GMM_CAS_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmSuspendCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulDestLen   = sizeof(GMM_SUSPEND_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmGlobalCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulDestLen   = sizeof(GMM_GLOBAL_CTRL_STRU);

    /*GTR����ʱGMM�����SM�������ݰ�Ϊ��ַ������ʵ�ʻط�ʱSM���������ַ��ͬ�����Բ���Ҫ�ָ��õ�ַ��*/
    ulMsgAddrForSm = g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = ulMsgAddrForSm;
    pucSrc += (ulItemCount);

    /* g_GmmTimerMngĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmTimerMng;
    ulDestLen   = sizeof(GMM_TIMER_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAttachCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulDestLen   = sizeof(GMM_ATTACH_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmRauCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulDestLen   = sizeof(GMM_RAU_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDownLinkNpduBakeĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulDestLen   = sizeof(GMM_DOWNLINK_NPDU_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDetachCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulDestLen   = sizeof(GMM_DETACH_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAuthenCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulDestLen   = sizeof(GMM_AUTHEN_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmReqCnfMngĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulDestLen   = sizeof(GMM_REQ_CNF_MNG_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmServiceCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulDestLen   = sizeof(GMM_SR_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RestoreContextData - data is restored.");

    NAS_GMM_SetGmmSigFunc();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_SndOutsideContextData
 ��������  : ��GMM�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��03��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��30��
    ��    ��   : z00161729
    �޸�����   : ����pc�ط�ѹ������

*****************************************************************************/
VOS_VOID NAS_GMM_SndOutsideContextData()
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_GMM, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM,"NAS_GMM_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* ��ȡbuf��β��ַ�����ڼ���ʣ��ռ�*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;
    pucDest   = pstPcreplayCompressCtx->aucData;

    /* ԭʼ���ݴ�С */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* ѹ��gucGmmInitState*/
    pucSrc      = (VOS_UINT8 *)&gucGmmInitState;
    ulItemCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmInterRatCellReselect */
    pucSrc      = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulItemCount = sizeof(g_GmmInterRatCellReselect);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��gstGmmCasGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulItemCount = sizeof(GMM_CAS_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��gstGmmSuspendCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulItemCount = sizeof(GMM_SUSPEND_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulItemCount = sizeof(GMM_GLOBAL_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmTimerMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmTimerMng;
    ulItemCount = sizeof(GMM_TIMER_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmAttachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulItemCount = sizeof(GMM_ATTACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmRauCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulItemCount = sizeof(GMM_RAU_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmDownLinkNpduBake */
    pucSrc      = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulItemCount = sizeof(GMM_DOWNLINK_NPDU_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmDetachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulItemCount = sizeof(GMM_DETACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);


    /* ѹ��g_GmmAuthenCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulItemCount = sizeof(GMM_AUTHEN_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmReqCnfMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulItemCount = sizeof(GMM_REQ_CNF_MNG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmServiceCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulItemCount = sizeof(GMM_SR_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_MsgProcAtStatusNull
 ��������  : GMMģ�����״̬ΪNULLʱ����Ϣ������
 �������  : MsgCB *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_MsgProcAtStatusNull(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_ADMIN == pMsgHeader->ulSenderPid)
     && (WUEPS_START_REQ == pMsgHeader->ulMsgName))
    {
        #ifdef __PS_WIN32_RECUR__
        Gmm_TaskInit();
        #endif

        gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_MsgProcAtStatusStartup
 ��������  : GMMģ�����״̬ΪStartupʱ����Ϣ������
 �������  : struct MsgCB *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ

*****************************************************************************/
VOS_VOID NAS_GMM_MsgProcAtStatusStartup(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsgHeader->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_TaskInit();
        Gmm_RcvMmcStartReq();
        gucGmmInitState = NAS_GMM_CTRL_STATUS_INSERVICE;

        #ifndef __PS_WIN32_RECUR__


        if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
        {
            NAS_GMM_SndOutsideContextData();
        }

        #endif
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusStartup:Receive message at state NAS_GMM_CTRL_STATUS_STARTUP.");

        if ((WUEPS_PID_SM == pMsgHeader->ulSenderPid)
            && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_STARTUP);
        }
        else if ((WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
            && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {

        }
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, begin */
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmCsConnectInd_PreProc
 ��������  : �յ�MM����������ָʾ��Ϣ��Ԥ����
 �������  : pstRcvMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��10��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_PreProc(
    VOS_VOID                           *pstRcvMsg                               /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* ����ԭ������ָ��                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* ǿ������ת��                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;                         /* ��CSͨ����Ϊ��                           */
    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;
    }
    else
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                        /* ��CSͨ����Ϊ��                           */
    }

    return;                                                                     /* ����                                     */
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, end */


/*****************************************************************************
 �� �� ��  : NAS_GMM_MsgProcAtStatusInService
 ��������  : GMMģ�����״̬ΪINSERVICEʱ����Ϣ����
 �������  : struct MsgCB *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��20��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��12��21��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ��:DTS2010121800152,GMM�ػ��ز�����״̬����
  3.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��10��21��
    ��    ��   : h44270
    �޸�����   : V7R1 FAST DORMANCY���ԣ���������RABM��Ϣ�Ĵ���
  5.��    ��   : 2013��7��11��
    ��    ��   : M00217266
    �޸�����   : GMM״̬��ѯ����������
  6.��    ��   : 2013��10��29��
     ��    ��  : W00176964
     �޸�����  : VoLTE_PhaseII ��Ŀ�޸�:����MM������ָʾ��ϢԤ����
  7.��    ��   : 2014��05��22��
    ��    ��   : W00242748
    �޸�����   : DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS
  8.��    ��   : 2015��09��23��
    ��    ��   : c00318887
    �޸�����   : DTS2015082604451:�޸�DSDS���
*****************************************************************************/
VOS_UINT8 NAS_GMM_MsgProcAtStatusInService(
    struct MsgCB                        *pMsg
)
{
    VOS_UINT8                           ucFollowOn;
    REL_TIMER_MSG                       *pTimerMsg;
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_RcvMmcStartReq();
        return VOS_TRUE;
    }

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, begin */
    if ((WUEPS_PID_MM         == pMsg->ulSenderPid)
     && (MMGMM_CS_CONNECT_IND == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvMmCsConnectInd_PreProc(pMsg);
    }
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, end */

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
    && (MMCGMM_DETACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcDetachReq_PreProc((MMCGMM_DETACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SMS == pMsg->ulSenderPid)
    {
        if (GMMSMS_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsBeginSessionNotify_PreProc((GMMSMS_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSMS_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsEndSessionNotify_PreProc((GMMSMS_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SM == pMsg->ulSenderPid)
    {
        if (GMMSM_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmBeginSessionNotify_PreProc((GMMSM_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSM_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmEndSessionNotify_PreProc((GMMSM_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;

        }
    }

    if ((WUEPS_PID_RABM == pMsg->ulSenderPid)
    && (ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvRabmMmlProcStatusQryReq((struct MsgCB *)pMsg);
        return VOS_TRUE;
    }

    if (RRMM_GMM_PROC_ENQ == pMsgHeader->ulMsgName)
    {
        if ( (WUEPS_PID_WRR == pMsgHeader->ulSenderPid)
          || (UEPS_PID_GAS == pMsgHeader->ulSenderPid) )
        {
            NAS_GMM_SndRrmmGmmProcAns();
        }

        return VOS_TRUE;
    }

    GMM_CasMsgProc(pMsg, &ucFollowOn);

    if (VOS_FALSE == ucFollowOn)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;

        Gmm_RcvTimerExpired((VOS_UINT8)pTimerMsg->ulName);
    }
    else if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    {
        if (WUEPS_RESET_REQ == pMsgHeader->ulMsgName)
        {
            gucGmmInitState = NAS_GMM_CTRL_STATUS_NULL;
        }
    }
    else
    {
        if (WUEPS_PID_GMM == pMsgHeader->ulReceiverPid)
        {
            Gmm_MsgDistribute((VOS_VOID*)pMsg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusInService: The message is not GMM message.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}
/*******************************************************************************
  Module   : GmmMsgProc
  Function : GMM TASK��ں���
  Input    : MsgCB* pMsg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2005.01.25  �¹�����
    2. ��    ��   : 2007��10��24��
       ��    ��   : l65478
       �޸�����   : A32D13102

  2.��    ��   : 2014��3��22��
    ��    ��   : z00234330
    �޸�����   : dts2014032202060���ӿ�ν�ɲ⣬gmmû�յ�һ����Ϣ�������Ϣ
*******************************************************************************/
VOS_VOID GmmMsgProc(
    struct MsgCB*                       pMsg
)
{
    VOS_UINT8                ucResult;

#ifdef __PS_WIN32_RECUR__
    if ((WUEPS_PID_GMM == pMsg->ulSenderPid)
     && (WUEPS_PID_GMM == pMsg->ulReceiverPid))
    {
        NAS_GMM_RestoreContextData(pMsg);
    }
#endif


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    switch (gucGmmInitState)
    {
        case NAS_GMM_CTRL_STATUS_NULL:
            NAS_GMM_MsgProcAtStatusNull(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_STARTUP:
            NAS_GMM_MsgProcAtStatusStartup(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_INSERVICE:
            ucResult = NAS_GMM_MsgProcAtStatusInService(pMsg);
            if (VOS_FALSE == ucResult)
            {
                return;
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GmmMsgProc:WARNING: gucGmmInitState is Abnormal!");
            break;
    }
/*
#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
*/
    return;
}

/*****************************************************************************
 �� �� ��  : Gmm_MsgDistribute_GMM_TC_ACTIVE
 ��������  : TC״̬�µ���Ϣ����
 �������  : VOS_VOID *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��06��14��
    ��    ��   : ŷ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2012��5��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012051501127, ����TC״̬��, W2Gʱδ֪ͨGPHY.
  4.��    ��   : 2013��6��7��
    ��    ��   : w00167002
    �޸�����   : SVLTE:�յ�DETACH��Ϣ������ȥע��
*****************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_GMM_TC_ACTIVE(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    MMCGMM_DETACH_REQ_STRU             *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq  = (MMCGMM_DETACH_REQ_STRU *)pRcvMsg;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if ((WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT,RABM,SM or SMS is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_DATA_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_PAGING_IND != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg except RRMM_REL_IND,RRMM_DATA_IND is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
           &&(MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    else if ( (WUEPS_PID_MMC     == pNasMsgHeader->ulSenderPid)
           && (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName) )
    {
        /* �жϵȴ�Detach��־�Ƿ���ڣ������������detach */
        if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
        {
            Gmm_MsInitNormalDetach(pstDetachReq->enDetachType);
        }

        /* ��ǰDETACH��Ϣ����Ҫ�ٽ��д��� */
        ucRst = GMM_FALSE;
    }
    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = NAS_Gmm_IsValidMmcMsg_GmmTcActive(pRcvMsg);
    }
    else
    {
    }
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: GMM is in GMM_TC_ACTIVE");


    /* �յ������PS�������ͷ���Ϣʱ��֪ͨTC�����ͷ� */
    if ( (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
      && (RRMM_REL_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }

    /* ��MMC�յ�COVERAGE LOST��Ϣʱ��֪ͨTC�����ͷ� */
    if ( (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
      && (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }


    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_GMM_NULL
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: GMM_NULL״̬�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��  : 2012��08��24��
       ��    ��  : m00217266
       �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
     3.��    ��   : 2012��11��24��
       ��    ��   : z60575
       �޸�����   : DTS2012112003432������ģʽ�����޸�

     3.��    ��   : 2013��6��20��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:GMM NULL״̬����MMC��Ϣ
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_GMM_NULL(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
    {
        if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
    {
        if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_NULL);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
    {
        if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {
        }
        ucRst = GMM_FALSE;
    }

    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = Gmm_MsgDistribute_ProcMmcMsg_GmmNull(pRcvMsg);
    }
    else if(WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT or RRC is Abnormal when GMM is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_TC == pNasMsgHeader->ulSenderPid)
        && (TCGMM_TEST_REQ != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive TCGMM_TEST_REQ Msg is Abnormal when  is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else
    {
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_SpecProc_Handling
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: SpecProc�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��  : 2012��08��24��
       ��    ��  : m00217266
       �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_SpecProc_Handling(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc)
    {
        if (WUEPS_PID_MMC != pNasMsgHeader->ulSenderPid)
        {
            if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
                && (RRMM_REL_IND == pNasMsgHeader->ulMsgName))
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
            }
            else
            {
                ucRst = GMM_FALSE;
            }
        }
    }

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {
        if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        {
            if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        {
            if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else
            {
            }
            ucRst = GMM_FALSE;
        }
        else if((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
            || (WUEPS_PID_TC == pNasMsgHeader->ulSenderPid))
        {
            if (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName)
            {

                /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
                if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                         & GMM_WAIT_PS_ATTACH))
                {
                    NAS_GMM_SndMmcAttachCnf();
                }
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
            }

            ucRst = GMM_FALSE;
        }
        else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
            && (RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
            && (RRMM_REL_IND != pNasMsgHeader->ulMsgName))
        {
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_Rat_Handling
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: ��ͬ���뼼������Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_Rat_Handling(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G����ģʽ */
        /* ������WRRC��Ϣ��SMS��Ϣ */
        if (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
        else if (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        {
            if ((RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
                && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
                && (RRMM_INTER_RAT_HANDOVER_INFO_CNF != pNasMsgHeader->ulMsgName))
            {
                ucRst = GMM_FALSE;
            }
        }
        else
        {
        }
    }
    else
    {/* 3G����ģʽ */
        /* ������GAS��Ϣ��LLC��Ϣ */
        if (UEPS_PID_LL == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_USIM
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: USIM��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_USIM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case USIMM_AUTHENTICATION_CNF:
        Gmm_RcvAgentUsimAuthenticationCnf(pRcvMsg);                         /* AGENT_USIM_AUTHENTICATION_CNF���մ���    */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from USIM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RRCF
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: RRCF��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RRCF(
    VOS_VOID                            *pRcvMsg
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
    case RRMM_PAGING_IND:
        Gmm_RcvRrmmPagingInd(pRcvMsg);
        break;
    case RRMM_EST_CNF:
        Gmm_RcvRrmmEstCnf(pRcvMsg);
        break;
    case RRMM_DATA_IND:
        Gmm_RcvRrmmDataInd(pRcvMsg);
        break;
    case RRMM_REL_IND:
        Gmm_RcvRrmmRelInd(pRcvMsg);
        break;
    case RRMM_SECURITY_IND:
        Gmm_RcvRrmmSecurityInd(pRcvMsg);
        break;
    case RRMM_INTER_RAT_HANDOVER_INFO_CNF:
        NAS_GMM_RcvInterRatHandoverInfoCnf(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RRC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RABM
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: RABM��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2015��7��9��
       ��    ��   : z00161729
       �޸�����   : DTS2015071505434:rau��attach���󲻴�follow on������ظ�attach accept��rau accept��Я��follow on proceed��ʶ��gmm��Ҫ
                �����ж����ps rab���ڻ����rabm�ؽ���smҵ�������cds���ڻ�������������T3340����������t3340���������������
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RABM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_RABM_GMM_REESTABLISH_REQ:
        Gmm_RcvRabmReestablishReq(pRcvMsg);                                 /* GMMRABM_REESTABLISH_REQ���մ���          */
        break;
    case ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP:
        NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(pRcvMsg);
        break;
    case ID_RABM_GMM_RAB_REL_IND:
        Gmm_RcvRabRelInd();                                                 /* RAB�ͷ�ָʾ���մ���                      */
        break;

    case ID_RABM_GMM_RAB_SETUP_IND:
        NAS_GMM_RcvRabmRabSetupInd((GMMRABM_RAB_SETUP_IND_STRU *)pRcvMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RABM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_MMC
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: MMC��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2011��10��27��
        ��    ��   : s46746
        �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     3. ��    ��   : 2011��12��29��
        ��    ��   : l00130025
        �޸�����   : DTS2011082201679/DTS2011121504358,�л�ģʽ�����˺�W/G��ע��״̬û����NASͬ��
     4. ��    ��   : 2012��02��29��
        ��    ��   : l00130025
        �޸�����   : DTS2012022206186:������RAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
     5. ��    ��   : 2012��03��02��
        ��    ��   : l00130025
        �޸�����   : DTS2012022102014:L->G->L->G��û�����·���TLLI,����G��RAU������ImplicityDetached
      6.��    ��   : 2012��3��17��
        ��    ��   : w00176964
        �޸�����   : DTS2012031308021:[GCF����]L2U��ѡ,Я��RAU request��������Ϣ
                     �е�RAU�����Լ�PTMSI���ʹ���
     7. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     8. ��    ��   : 2012��3��20��
        ��    ��   : z00161729
        �޸�����   : ISR ����
     9. ��    ��   : 2012��10��16��
        ��    ��   : z00161729
        �޸�����   : DTS2012101503609,����ģʽII��L��ϵͳ��G,raiδ�ı�isrδ�����rau��
                     ԭ���һ��ϵͳ��Ϣ���治����gstGmmSuspendCtrl.ucPreRat��Ϊg��lau����gprs
                     resume���յ�ϵͳ��Ϣ���жϲ�������ϵͳ��raiδ�ı���Ϊ����rau
    10. ��    ��   : 2015��2��5��
        ��    ��   : s00217060
        �޸�����   : VOLTE SWITCH�޸�
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_MMC(
    VOS_VOID                            *pRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case MMCGMM_SYS_INFO_IND:
        Gmm_RcvMmcSysInfoInd(pRcvMsg);                                      /* MMCGMM_SYS_INFO_IND���մ���              */

        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_WRR);


        /* �����ʱGMM��Ҫ��ȡLMM�İ�ȫ������,���ܻ�������ʱ��,��ʱ������Ӧ����ʱ�����
           ���յ�LMM�İ�ȫ�����ĵĻظ����߶�ʱ����ʱ������� */
        if ( VOS_FALSE == NAS_GMM_GetLmmSecInfoFlg())
        {
            /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
            gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_WCDMA;

            g_GmmInterRatCellReselect = 0;
        }


        break;
    case MMCGMM_COVERAGE_LOST_IND:
        Gmm_RcvMmcCoverageLostInd();                                        /* MMCGMM_COVERAGE_LOST_IND���մ���         */
        break;
    case MMCGMM_POWER_OFF_REQ:
        Gmm_RcvMmcPowerOffReq(pRcvMsg);                                     /* MMCGMM_POWER_OFF_REQ���մ���             */
        break;

    case MMCGMM_PLMN_SEARCH_INITIATED:
        Gmm_RcvMmcPlmnSearchInitiated();                                    /* MMCGMM_PLMN_SEARCH_INITIATED���մ���     */
        break;
    case MMCGMM_START_REQ:
        Gmm_RcvMmcStartReq();                                               /* MMCGMM_START_REQ���մ���                 */
        break;
    case MMCGMM_PLMN_USER_SEL_REQ:
        Gmm_RcvMmcPlmnUserSelReq();                                         /* MMCGMM_PLMN_USER_SEL_REQ���մ���         */
        break;
    case MMCGMM_DETACH_REQ:
        Gmm_RcvMmcDetachReq(pRcvMsg);                                       /* MMCGMM_DETACH_REQ���մ���                */
        break;
    case MMCGMM_MODE_CHANGE_REQ:
        Gmm_RcvMmcGmmModeChangeReq(pRcvMsg);                                /* MMCGMM_MODE_CHANGE_REQ���մ���           */
        break;
    case MMCGMM_ATTACH_REQ:
        Gmm_RcvMmcGmmAttachReq(pRcvMsg);                                    /* MMCGMM_ATTACH_REQ���մ���                */
        break;
    case MMCGMM_GSM_SYS_INFO_IND:
        GMM_RcvGasSysInfoInd(pRcvMsg);



        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_GAS);


        break;
    case MMCGMM_SUSPEND_IND:
        GMM_RcvMmcSuspendInd(pRcvMsg);
        break;
    case MMCGMM_RESUME_IND:
        GMM_RcvMmcResumeInd(pRcvMsg);
        break;
    case MMCGMM_REL_REQ:
        GMM_RcvMmcRelReq(pRcvMsg);
        break;
    case MMCGMM_W_AC_INFO_CHANGE_IND:
        NAS_GMM_RcvMmcWasAcInfoChgInd((NAS_MSG_STRU *)pRcvMsg);
        break;
#if (FEATURE_ON == FEATURE_LTE)
    case MMCGMM_LTE_SYS_INFO_IND:
        NAS_GMM_RcvMmcLteSysInfoInd((MMC_GMM_LTE_SYS_INFO_IND_STRU*)pRcvMsg);
        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_LTE;
        break;

    case MMCGMM_LMM_ATTACH_IND:
        NAS_GMM_RcvLmmAttachResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_TAU_RESULT_IND:
        NAS_GMM_RcvLmmTauResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MT_DETACH_IND:
        NAS_GMM_RcvLmmMtDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_SERVICE_RESULT_IND:
        NAS_GMM_RcvLmmServiceResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MO_DETACH_IND:
        NAS_GMM_RcvLmmMoDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_LOCAL_DETACH_IND:
        NAS_GMM_RcvLmmLocalDetachInd((struct MsgCB*)pRcvMsg);
        break;


    case MMCGMM_LMM_STATUS_IND:
        NAS_GMM_RcvMmcLmmStatusInd((MMCGMM_LMM_STATUS_IND_STRU*)pRcvMsg);
        break;

    case MMCGMM_LMM_TIMER_STATE_NOTIFY:
        NAS_GMM_RcvLmmTimerStateNotify((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_EMERGENCY_NUM_LIST_IND:
        NAS_GMM_RcvMmcEmergencyNumList((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY:
        NAS_GMM_RcvMmcVoiceDomainChangeNotify((struct MsgCB*)pRcvMsg);
        break;
#endif

    default :
        NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pNasMsgHeader->ulMsgName);
        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmAbortReq
 ��������  : ��ϢGMMSM_ABORT_REQ�Ľ��մ���
 �������  : ��������PDP״̬����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : �����ɺ�����PS Project�����Ӷ���Abort��Ϣ�Ĵ���
******************************************************************************/
VOS_VOID NAS_GMM_RcvSmAbortReq(
    VOS_VOID                            *pRcvMsg)
{
    NAS_GMM_ClearBufferedSmDataReq();
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SM
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: SM��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��9��14��
   ��    ��   : h44270
   �޸�����   : modify for PS Project,���Ӷ���Abort��Ϣ�Ĵ���
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case GMMSM_ESTABLISH_REQ:
        Gmm_RcvSmEstablishReq(pRcvMsg);                                     /* GMMSM_ESTABLISH_REQ���մ���              */
        break;
    case GMMSM_DATA_REQ:
        Gmm_RcvSmDataReq(pRcvMsg);                                          /* GMMSM_DATA_REQ���մ���                   */
        break;
    case GMMSM_PDP_STATUS_IND:
        Gmm_RcvSmPdpStatusInd(pRcvMsg);                                     /* GMMSM_PDP_STATUS_IND���մ���             */
        break;
    case GMMSM_PDP_DEACTIVATED_IND:
        NAS_GMM_RcvSmPdpDeactivatedInd(pRcvMsg);
        break;

    case GMMSM_ABORT_REQ:
        NAS_GMM_RcvSmAbortReq(pRcvMsg);
        break;

    case GMMSM_PDP_MODIFY_IND:
        NAS_GMM_RcvSmPdpModifyInd(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SMS
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: SMS��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SMS(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case PMMSMS_EST_REQ:
        Gmm_RcvSmsEstReq(pRcvMsg);                                          /* PMMSMS_EST_REQ���մ���                   */
        break;
    case PMMSMS_UNITDATA_REQ:
        Gmm_RcvSmsUnitdataReq(pRcvMsg);                                     /* GMMSM_DATA_REQ���մ���                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SMS is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_LL
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: LL��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
    1.ŷ����   2009.06.11  �°�����
    2.��    ��   : 2015��4��7��
      ��    ��   : wx270776
      �޸�����   : ���ⵥ��:DTS2015040701865�����ͨ�ػ��Ż������Ӷ�ID_LL_UNITDATA_CNF����Ϣ����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_LL(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_LL_GMM_STATUS_IND:                                                  /* �ϱ�LLC״̬��Ϣ */
        GMM_CasCellS0E45(pRcvMsg);
        break;
    case ID_LL_UNITDATA_IND:                                                    /* ֱ���������� */
        GMM_RcvLlcDataInd(pRcvMsg);
        break;

    case ID_LL_UNITDATA_CNF:                                                    /* ֱ���������� */
        NAS_GMM_RcvLlcDataCnf(pRcvMsg);
        break;

    case ID_LL_DATA_INFORM :
        Gmm_RcvLLCInform(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from LLC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_TC
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: TC��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_TC(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case TCGMM_DATA_REQ:
        Gmm_RcvTcDataReq(pRcvMsg);                                          /* TCGMM_DATA_REQ���մ���                   */
        break;
    case TCGMM_TEST_REQ:
        Gmm_RcvTcTestReq(pRcvMsg);                                          /* TCGMM_TEST_REQ���մ���                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from TC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_GAS
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: GAS��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��    : 2009��9��03��
   ��    ��    : l65478
   �޸�����    : created AT2D14239,detach��ɺ�,�ٴη���ATTATCH REQʱ,GASʹ�þɵ�TLLI������TBF��������,û�м�ʱʹ���µ�TLLI,����MS��������ά����TLLI��һ��,�Ӷ�����GAS��ΪTLLI��ƥ�䶪���˽�������TBF��ָ������,���յ�������ʧ��
 3.��    ��   : 2011��7��12��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����������Ϣԭ�����֪���Ƿ�G��GPRS����ɹ�
************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_GAS(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
        case GRRMM_PAGING_IND:                                                  /* GASѰ������ */
            GMM_RcvGasPagingInd(pRcvMsg);
            break;
        case RRMM_GPRS_SUSPENSION_IND:                                          /* GAS GPRS����ָʾ */
            GMM_RcvGasSuspensionInd(pRcvMsg);
            break;
        case RRMM_GPRS_RESUME_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasGprsResumeInd(pRcvMsg);
            break;
        case RRMM_CELL_RESELECT_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvCellReselectInd(pRcvMsg);
            break;
        case GRRGMM_TBF_REL_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasTbfRleInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasRadioAccessCapa(pRcvMsg);
            break;

        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-22, begin */
        case RRMM_CLASSMARK_CHANGE_IND:
            GMM_RcvGasClassMarkChangeInd(pRcvMsg);
            break;
        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-22, end */

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasTdsRadioAccessCapa(pRcvMsg);
            break;

        case GRRGMM_GPRS_ACCESS_RESULT_IND:
            NAS_GMM_RcvGprsAccessResultInd(pRcvMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from GAS is ignored");
            break;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvLmmReselSecInfoCnf
 ��������  : �յ�LMM����ѡ��ȫ��������������Ӧ����
             �����µ��ñ���ֹ��SYS_INFO��Ϣ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : luokaihui /00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
  3.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031308021:[GCF����]L2U��ѡ,Я��RAU request��������Ϣ
                 �е�RAU�����Լ�PTMSI���ʹ���
  4.��    ��   : 2012��3��21��
    ��    ��   : z40661
    �޸�����   : DTS2011110201060:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ
  5.��    ��   : 2014��4��24��
    ��    ��   : s00217060
    �޸�����   : ��Lģ��ȡӳ��İ�ȫ������֮��֪ͨGUģ
  6.��    ��   : 2014��10��30��
    ��    ��   : s00217060
    �޸�����   : ��Lģ��ȡ��ȫ�����ĺ������ǰ״̬����ATTACH_INIT��RAU_INIT������attach/rau req
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmReselSecInfoCnf(
    VOS_VOID                             *pRcvMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU     *pstMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8       enCurrRat;

    pstMsg = (LMM_GMM_RESEL_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInReselect((struct MsgCB *)pstMsg);

    enCurrRat   = NAS_MML_GetCurrNetRatType();

    /* ��Lģ��ȡӳ��İ�ȫ������֮��֪ͨGUģ */
    if (NAS_MML_NET_RAT_TYPE_WCDMA  == enCurrRat)
    {
        NAS_GMM_SndWasInfoChangeReq(RRC_NAS_MASK_MAPPED_SECURITY_KEY);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM  == enCurrRat)
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_MAPPED_SECURITY_KEY);
    }
    else
    {
    }

    /* ��Lģ��ȡ��ȫ�����ĺ������ǰ״̬����ATTACH_INIT��RAU_INIT������attach/rau req
       ��Ӧ����Ϊ:LTE���Ʒ�����available timer,��ѡ��GU������available timer��ʱ����������
       GMM״̬����ΪPLMN_SRCH,������RAU���̳�ͻ */
    if ( (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
        {
            Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        }
        else
        {
            Gmm_SndAttachReq();
        }

        /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
        gstGmmSuspendCtrl.ucPreRat = enCurrRat;
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;


    gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);

}
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvLmmHoSecInfoCnf
 ��������  : �յ�LMM����ѡ��ȫ��������������Ӧ����
             �����µ��ñ���ֹ��SYS_INFO��Ϣ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : luokaihui /00167671
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����:��������л�ȡ��L�İ�ȫ�����ĺ���MMC�ظ�������
  3.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmHoSecInfoCnf(
    VOS_VOID                            *pRcvMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU       *pstMsg;

    pstMsg = (LMM_GMM_HO_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver((struct MsgCB *)pstMsg);

    /* �����ʱ��GMM�Ĺ���״̬�����ҹ�����ΪLTE������MMC�ظ�����ظ� */
    if ( (NAS_MML_NET_RAT_TYPE_LTE      == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE  == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }
}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-12, begin */
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-12, end */

/*****************************************************************************
 �� �� ��  : Gmm_MsgDistribute_From_Lmm
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��14��
    ��    ��   : luokaihui /00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��12��
    ��    ��   : y00245242
    �޸�����   : ���Ӵ���LTE����ҵ�����������ϱ�
*****************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_Lmm(
    VOS_VOID *pRcvMsg
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
        case ID_LMM_GMM_RESEL_SECU_INFO_CNF:
            NAS_GMM_RcvLmmReselSecInfoCnf(pRcvMsg);
            break;

        case ID_LMM_GMM_HO_SECU_INFO_CNF:
            NAS_GMM_RcvLmmHoSecInfoCnf(pRcvMsg);
            break;

        /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-12, begin */
        /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-12, end */
        default :
            break;
    }

    return;
}

#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcMtcRrcAreaLostInd
 ��������  : ��������Mtc��rrc�ٶ�����Ϣ
 �������  : pstRcvMsg - ����Mtc����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��8��
   ��    ��   : z00161729
   �޸�����   : dts2014010202583
*****************************************************************************/
VOS_VOID NAS_GMM_ProcMtcRrcAreaLostInd(VOS_VOID  *pstRcvMsg)
{

    /* svlte���Կ���ʱps��modem0Ǩ�Ƶ�modem1������ȫ�ֱ���������gmm�յ�
       detach ps����ֱ�ӽ��б���detach�Լ���ʱ�� */
    NAS_MML_SetPsLocalDetachFlag(VOS_TRUE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcMtcMsg
 ��������  : ��������Mtc��Ϣ�ķַ�����
 �������  : pstRcvMsg - ����Mtc����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ProcMtcMsg(VOS_VOID  *pstRcvMsg)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;

    switch (pstNasMsgHeader->ulMsgName)
    {
        case ID_MTC_GMM_RRC_AREA_LOST_IND:
            NAS_GMM_ProcMtcRrcAreaLostInd(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_ProcMtcMsg: The Msg from MTC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

#endif



/*****************************************************************************
 �� �� ��  : Gmm_MsgDistribute_From_MM
 ��������  : ��������MM��Ϣ�ķַ�����
 �������  : pstRcvMsg:����MM����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_MM(
    VOS_VOID                           *pstRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pstNasMsgHeader->ulMsgName)
    {
        case MMGMM_LU_RESULT_IND:
            NAS_GMM_ProcMmLuResult(pstRcvMsg);
            break;

        case MMGMM_CS_CONNECT_IND:
            NAS_GMM_RcvMmCsConnectInd(pstRcvMsg);                               /* MMGMM_CS_CONNECT_IND���մ���            */
            break;
        case MMGMM_CM_SERVICE_REJECT_IND:
            NAS_GMM_RcvMmCmServiceRejectInd(pstRcvMsg);                         /* MMGMM_CM_SERVICE_REJECT_IND���մ���     */
            break;

        case MMGMM_AUTHENTICATON_FAILURE_IND:
            NAS_GMM_RcvMmAuthenticationFailureInd();                            /* MMCGMM_AUTHENTICATON_FAILURE_IND���մ��� */
            break;

        case MMGMM_REGISTER_INITIATION:
            Gmm_RcvMmRegisterInitiation(pstRcvMsg);                              /* MMCGMM_REGISTER_INITIATION���մ���       */
            break;

        case MMGMM_CS_LOCAL_DETACH_IND:
            NAS_Gmm_RcvMmCsLocalDetachInd(pstRcvMsg);                           /* MMGMM_CS_LOCAL_DETACH_IND���մ��� */
            break;


        case MMGMM_T3211_TIMER_EXPIRED_NOTIFY:
            NAS_Gmm_RcvMmT3211ExpiredNotify(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_MsgDistribute
  Function : GMM TASK��Ϣ�ַ�����
  Input    : VOS_VOID *pRcvMsg  ������Ϣʹ�õ�ͷ��ַ����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.  ��־��  2003.12.09  �¹�����
  2. x51137   2006/4/21 A32D03244
  3. ��    ��   : 2006��11��2��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D06406
  4. ��    ��   : 2007��01��04��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D06408
  5. ��    ��   : 2007��03��20��
     ��    ��   : x51137
     �޸�����   : A32D09192
  6. ��    ��   : 2008��7��23��
     ��    ��   : luojian id:107747
     �޸�����   : �������ⵥ��AT2D04627/AT2D04237
  7.��    ��   : 2009��01��15��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
  8.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  9.��    ��   : 2013��12��8��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
*******************************************************************************/
VOS_VOID Gmm_MsgDistribute(
    VOS_VOID                            *pRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */
    if (WUEPS_PID_GMM != pNasMsgHeader->ulReceiverPid)
    {                                                                           /* ulDestTskId����GMM                       */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive PID is not GMM.");
        return;
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_TC_ACTIVE(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_NULL(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    ucRst = Gmm_MsgDistribute_SpecProc_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    ucRst = Gmm_MsgDistribute_Rat_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    switch (pNasMsgHeader->ulSenderPid)
    {                                                                           /* ����message class�ַ���Ϣ                */
    case WUEPS_PID_USIM:                                                        /* AGENT���͸�GMM                           */
        Gmm_MsgDistribute_From_USIM(pRcvMsg);
        break;

    case WUEPS_PID_WRR:                                                        /* RRC���͸�GMM                             */
        Gmm_MsgDistribute_From_RRCF(pRcvMsg);
        break;

    case WUEPS_PID_RABM:                                                        /* RABM���͸�GMM                            */
        Gmm_MsgDistribute_From_RABM(pRcvMsg);
        break;

    case WUEPS_PID_MMC:                                                         /* MMC���͸�GMM                             */
        Gmm_MsgDistribute_From_MMC(pRcvMsg);
        break;

    case WUEPS_PID_MM:                                                         /* SMS���͸�GMM                             */
        Gmm_MsgDistribute_From_MM(pRcvMsg);
        break;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    case UEPS_PID_MTC:
        NAS_GMM_ProcMtcMsg(pRcvMsg);
        break;
#endif

    case WUEPS_PID_SM:                                                          /* SM���͸�GMM                              */
        Gmm_MsgDistribute_From_SM(pRcvMsg);
        break;

    case WUEPS_PID_SMS:                                                         /* SMS���͸�GMM                             */
        Gmm_MsgDistribute_From_SMS(pRcvMsg);
        break;

    case WUEPS_PID_TC:                                                        /* TC���͸�GMM                              */
        Gmm_MsgDistribute_From_TC(pRcvMsg);
        break;

    case UEPS_PID_LL:                                                           /* LLC���͸�GMM */
        Gmm_MsgDistribute_From_LL(pRcvMsg);
        break;

    case UEPS_PID_GAS:                                                          /* GRR���͸�GMM */
        Gmm_MsgDistribute_From_GAS(pRcvMsg);
        break;

#if   (FEATURE_ON == FEATURE_LTE)
    case PS_PID_MM:                                                          /* GRR���͸�GMM */
        Gmm_MsgDistribute_From_Lmm(pRcvMsg);
        break;
#endif

    default :
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive Message from unexpected PID, PID : ", pNasMsgHeader->ulSenderPid);
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_ComVariantInit
  Function : GMM TASKȫ�ֱ����ĳ��ڻ�����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2.��    ��   : 2009��5��9��
      ��    ��   : l00130025
      �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
    3.��    ��   : 2009��7��23��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��:AT2D13173,GMM���յ�ϵͳ��Ϣ�󣬸�MMC������NO SERVICE������MMC������������ʱ��
    4.��    ��   : 2009��9��16��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��:AT2D13861,RAUʧ��֪ͨOM�ڵ�ԭ��ֵ���� ��Ӧ����rr��connect fail
    5.��    ��   : 2010��10��05��
      ��    ��   : o00132663
      �޸�����   : DTS2010100500115����������RAC��ʼֵ
    6.��    ��   : 2011��10��11��
      ��    ��   : f00179208
      �޸�����   : DTS2011101001459�������ġ�GSMģʽ�£�����㲥ϵͳ��Ϣ13��
                   E5��ר��̬�ص�IDLE̬����ȡ������ϵͳ��Ϣ���˲�һ��
    7.��    ��   : 2012��8��10��
      ��    ��   : L00171473
      �޸�����   : DTS2012082204471, TQE����
    8.��    ��   : 2012��8��15��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
    9.��    ��   : 2012��9��03��
      ��    ��   : w00176964
      �޸�����   : GUTL PhaseII:����TDS��RAC��������
   10.��    ��   : 2012��9��25��
      ��    ��   : h00216089
      �޸�����   : DTS2012090304976:����������Detach(re-attach not required)��MM��ʱ����ʱ����LU��
                     LU�������յ�ϵͳ��ϢGMM�����ٷ���Attach
   11.��    ��   : 2012��12��13��
      ��    ��   : L00171473
      �޸�����   : DTS2012121802573, TQE����
   12.��    ��   : 2014��01��13��
      ��    ��   : l65478
      �޸�����   : DTS2013102508485, �ĵ�PDPȥ�����UE�����ͷ���RRC����
   13.��    ��   : 2014��6��17��
      ��    ��   : s00217060
      �޸�����   : DTS2014061003286:3311��ʱ����ʱ��־��ʼ��
   14.��    ��   : 2015��1��15��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
   15.��    ��   : 2015��2��12��
      ��    ��   : s00217060
      �޸�����   : VOLTE SWITCH�޸�
   16.��    ��   : 2015��6��15��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_ComVariantInit(VOS_VOID)
{
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usNonDrxTimerLen;
    VOS_UINT8                           aucDefaultRac[] = {0x15, 0x17, 0x73, 0x43, 0x2b, 0x25, 0x96, 0x62, 0x00,
                                                           0x42, 0x68, 0x8b, 0x19, 0x88, 0x01, 0x0b, 0xa2,
                                                           0x8c, 0x66, 0x20, 0x04, 0x00};
    NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU    stRelConnAfterPdpDeact;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulLength;

    NAS_MML_PLMN_WITH_RAT_STRU                  stPlmnWithRat;

    stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;


    usNonDrxTimerLen = 0;

    /* ��GMM��ȫ�ֱ������ڻ�Ϊ0 */
    Gmm_MemSet(&g_GmmGlobalCtrl, 0, sizeof(GMM_GLOBAL_CTRL_STRU));
    Gmm_MemSet(&g_GmmReqCnfMng,  0, sizeof(GMM_REQ_CNF_MNG_STRU));
    Gmm_MemSet(&g_GmmAttachCtrl, 0, sizeof(GMM_ATTACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmRauCtrl,    0, sizeof(GMM_RAU_CTRL_STRU));
    Gmm_MemSet(&g_GmmDetachCtrl, 0, sizeof(GMM_DETACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmAuthenCtrl, 0, sizeof(GMM_AUTHEN_CTRL_STRU));
    Gmm_MemSet(&g_GmmServiceCtrl,0, sizeof(GMM_SR_CTRL_STRU));
    Gmm_MemSet(&g_MmSubLyrShare.GmmShare, 0, sizeof(GMM_SHARE_STRU));
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    g_GmmTimerMng.ulTimerRunMask             = 0;
    g_GmmTimerMng.ulTimerSusMask             = 0;
    g_GmmTimerMng.ulTimerValMask             = 0;
    g_GmmTimerMng.ulTimerRunMaskEx           = 0;
    g_GmmTimerMng.ulTimerSusMaskEx           = 0;
    g_GmmTimerMng.ulTimerValMaskEx           = 0;    
    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    GMM_InitCasGlobalVariable();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);

    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg  = GMM_SUPPORT_INFORMATION_MSG;

    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */

    /* ��GASά����NV���ж�ȡnonDRXTimerֵ */
    if(NV_OK != NV_Read (en_NV_Item_GPRS_Non_Drx_Timer_Length, &usNonDrxTimerLen, sizeof(VOS_UINT16)))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_ComVariantInit():en_NV_Item_GPRS_Non_Drx_Timer_Length Error");
        usNonDrxTimerLen = 0;
    }

    NAS_MML_SetNonDrxTimer((VOS_UINT8)usNonDrxTimerLen);



    g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = VOS_FALSE;
    PS_MEM_SET(&stRelConnAfterPdpDeact, 0x00, sizeof(NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU));

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT, &ulLength);
    if (ulLength > sizeof(stRelConnAfterPdpDeact))
    {
        return;
    }
    ulResult = NV_Read(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT,
                       &stRelConnAfterPdpDeact,
                       ulLength);

    /* �ǲ��Կ������ó�nvֵ */
    if ((VOS_FALSE == NAS_USIMMAPI_IsTestCard())
     && (NV_OK == ulResult))
    {
        g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = stRelConnAfterPdpDeact.ucRelFlg;
    }

    /*���ｫ��¼�ϴ�attach��RAU�Ƿ�Я��Drx�����ı���enLatestAttachOrRauContainDrx ��ʼ��*/
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */

    g_GmmGlobalCtrl.ucSuspendProc                = GMM_FALSE;
    g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult   = RRC_NAS_EST_RESULT_BUTT;
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;

    g_GmmInterRatCellReselect = 0;
    g_GmmGlobalCtrl.ucEventCause = GMM_EVENT_CAUSE_INVALID;
    /* ��ʼ��Ϊû���յ�����detach��Ϣ */
    g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_FALSE;

    g_GmmGlobalCtrl.ucIsNeedStartT3340PdpExist = VOS_FALSE;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* Ĭ��֧��L���� */
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs     = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */
    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq          = NAS_MML_GetVoiceDomainPreference();
#endif

    /* ��RAC����ʼֵ */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, aucDefaultRac, ucLen);

    /* ��RAC����ʼֵ */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, aucDefaultRac, ucLen);

    /* ��ʼ��3311��ʱ��δ��ʱ */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    return;
}

/*******************************************************************************
  Module   : Gmm_TaskInit
  Function : GMM TASK��ʱ��������AS API����ָ��ĳ��ڻ�����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2. ��    ��   : 2006��11��6��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D06867
    3. ��    ��   : 2006��12��07��
       ��    ��   : s46746
       �޸�����   : �������������ⵥ�ţ�A32D07799
    4. ��    ��   : 2007��3��30��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D09854
    5. ��    ��   : 2007��8��28��
       ��    ��   : l60022475
       �޸�����   : ���ⵥ�ţ�A32D12744,��ʼ��GMM Timer���
    6. ��    ��   : 2010��01��03��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ�ţ�xxxx,NAS R7Э��������������PS ���������ͷŶ�ʱ��T3340
     7.��    ��   : 2011��10��11��
       ��    ��   : l00171473
       �޸�����   : V7R1 phase II,TC���ص���, �����ӳ���MMC�ظ�SUSPEND_RSP��ʱ��
     8.��    ��   : 2011��12��2��
       ��    ��   : s46746
       �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
     9.��    ��   : 2011��12��29��
       ��    ��   : l00130025
       �޸�����   : DTS2011082201679/DTS2011121504358,�л�ģʽ�����˺�W/G��ע��״̬û����NASͬ��
    10.��    ��   : 2012��3��21��
       ��    ��   : z40661
       �޸�����   : DTS2011110201060:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ
     11.��    ��   : 2012��3��7��
        ��    ��   : z00161729
        �޸�����   : ISR�޸�
     12.��    ��   : 2012��4��17��
        ��    ��   : z00161729
        �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
    11.��    ��   : 2012��5��15��
       ��    ��   : l00130025
       �޸�����   : DTS2012041002516: ���RadioCapa�ı䴥��RAU�ӳ�ʱ��
    12.��    ��   : 2012��08��24��
       ��    ��   : m00217266
       �޸�����   : ɾ��GMM_ClearErrCode��PS��������ϱ���Ŀ��
    13.��    ��   : 2012��8��15��
       ��    ��   : z00161729
       �޸�����   : DCM������������������޸�
    14.��    ��   : 2012��10��12��
       ��    ��   : w00176964
       �޸�����   : DTS2012091400694:Gģ�ػ���
    15.��    ��   : 2013��01��4��
       ��    ��   : w00176964
       �޸�����   : DTS2012122509167:GCF WЭ������7.1.5.6ʧ��(�ػ�detachʱ������5S�����罨��6S�Ż�)
    16.��    ��   : 2013��6��5��
       ��    ��   : w00242748
       �޸�����   : svlte��usim�ӿڵ���
    17.��    ��   : 2014��12��25��
       ��    ��   : w00167002
       �޸�����   : DTS2014122201960:��L��SRVCC HO��G��HO��W,RABM�����ؽ�����������
                    ����RAU�������յ�ϵͳ��Ϣ���ٴη���RAU,��������REL����·������
                    �������޸�Ϊ��HO������������ʱ����ϵͳ��Ϣ��
    18.��    ��   : 2015��7��2��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_TaskInit(VOS_VOID)
{
    VOS_UINT8 i;

    Gmm_MemSet(&g_GmmTimerMng, 0, sizeof(GMM_TIMER_STRU));

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3310].ulTimerVal = GMM_TIMER_T3310_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3311].ulTimerVal = GMM_TIMER_T3311_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = GMM_TIMER_T3312_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3316].ulTimerVal = GMM_TIMER_T3316_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3317].ulTimerVal = GMM_TIMER_T3317_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3318].ulTimerVal = GMM_TIMER_T3318_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3319].ulTimerVal = GMM_TIMER_T3319_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3320].ulTimerVal = GMM_TIMER_T3320_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3321].ulTimerVal = GMM_TIMER_T3321_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3330].ulTimerVal = GMM_TIMER_T3330_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_1S   ].ulTimerVal = GMM_TIMER_1S_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_POWER_OFF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;

    /* GCF����,�ػ�detach��ʱ��ʱ��Ϊ8S */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_GCF_POWER_OFF_VALUE;
    }

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT].ulTimerVal
            = GMM_TIMER_PROTECT_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_FOR_SIGNALING].ulTimerVal
            = GMM_TIMER_PROTECT_FOR_SIGNALING_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_SUSPENDED].ulTimerVal
            = GMM_TIMER_SUSPENDED_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_RAU_RSP].ulTimerVal
            = GMM_TIMER_RAU_RSP_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_OLD_TLLI].ulTimerVal
            = GMM_TIMER_PROTECT_OLD_TLLI_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF].ulTimerVal = GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF].ulTimerVal = GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerVal    = GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_CONNECT_REL].ulTimerVal    = GMM_TIMER_WAIT_CONNECT_REL_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_TC_DELAY_SUSPEND_RSP].ulTimerVal = GMM_TIMER_TC_DELAY_SUSPEND_RSP_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3323].ulTimerVal = GMM_TIMER_T3323_VALUE;


    /* GMM HO��GU���ϵͳ��Ϣ��ʱ�� */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_HO_WAIT_SYSINFO].ulTimerVal = GMM_TIMER_WAIT_SYSINFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU].ulTimerVal = GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU_VALUE;


    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO].ulTimerVal = GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO_VALUE;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU].ulTimerVal = GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_PS_SMS_CONN_REL].ulTimerVal    = GMM_TIMER_DELAY_PS_SMS_CONN_REL_VALUE;
    
    for (i = 0; i < GMM_TIMER_NUM; i++)
    {
        g_GmmTimerMng.aTimerInf[i].ucMode = VOS_RELTIMER_NOLOOP;
        g_GmmTimerMng.aTimerInf[i].hTimer = VOS_NULL_PTR;
    }
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;

    Gmm_MemSet(&gstGmmSuspendCtrl, 0x0, sizeof(GMM_SUSPEND_CTRL_STRU));

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_NET_RAT_TYPE_WCDMA;
    gstGmmSuspendCtrl.ucRauCause                  = GMM_RAU_FOR_NORMAL;
    gstGmmSuspendCtrl.ucT3312State                = GMM_T3312_NOT_TIMEOUT;
    gstGmmSuspendCtrl.ucNetModeChange             = GMM_FALSE;
    gstGmmSuspendCtrl.ucPowerOff                  = GMM_POWER_OFF_NOT_RCV;

    gstGmmSuspendCtrl.ucGetLteSecContext          = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif

    Gmm_ComVariantInit();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_MakeDetachMsg
 ��������  : ����DETACH��Ϣ
 �������  : ��������PDP״̬����Ϣ
 �������  : ��
 �� �� ֵ  : �³����ɵ�MMCGMM_DETACH_REQ_STRU�ṹ��ָ�룬��DETACH��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��29��
    ��    ��   : l00167671/�޿���
    �޸�����   : �½����������ⵥ�ţ�DTS2010100802035,CS ONLYģʽȥע��Ĵ���
*****************************************************************************/
MMCGMM_DETACH_REQ_STRU* NAS_GMM_MakeDetachMsg( VOS_UINT32  ulDetachCause )
{

    MMCGMM_DETACH_REQ_STRU* pSndMsg = VOS_NULL_PTR;                                     /* ����ԭ������ָ��                         */

    /*������Ϣ  */
    pSndMsg = (MMCGMM_DETACH_REQ_STRU*)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

    if ( VOS_NULL_PTR == pSndMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mmc_SndGmmDetachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_NULL_PTR;                                                                 /* ����                                     */
    }

    Gmm_MemSet(pSndMsg, 0x00, sizeof(MMCGMM_DETACH_REQ_STRU));

    pSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pSndMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���                             */
    pSndMsg->MsgHeader.ulMsgName   = MMCGMM_DETACH_REQ;                         /* ��д��Ϣ����                             */

    pSndMsg->enDetachType          = ulDetachCause;

    return pSndMsg;

}
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmPdpModifyInd
 ��������  : ����GMMSM_PDP_MODIFY_IND��Ϣ
 �������  : pRcvMsg - GMMSM_PDP_MODIFY_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��27��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmPdpModifyInd(VOS_VOID *pRcvMsg)
{
#if (FEATURE_LTE == FEATURE_ON)
    GMMSM_PDP_MODIFY_IND_STRU          *pSmPdpModifyInd;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enCurrTinType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT8                           ucNsapi;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pSmPdpModifyInd = (GMMSM_PDP_MODIFY_IND_STRU *)pRcvMsg;
    ucNsapi         =  pSmPdpModifyInd->ucNsapi;
    enCurrTinType   =  NAS_MML_GetTinType();
    enCurrRatType   =  NAS_MML_GetCurrNetRatType();
    pstRplmnCfgInfo =  NAS_MML_GetRplmnCfg();

    /* 3GPP 24008 6.3  Coordination between SM and GMM for supporting ISR�½�������
       This subclause applies to a MS with its TIN set as "RAT related TMSI" for which ISR is activated.
       The MS shall change its TIN to "P-TMSI" to deactivate ISR:
       -   upon modification of any PDP context which was activated before the ISR is activated in the MS
    */
    if ((VOS_TRUE == NAS_MML_IsPsBearerExistBeforeIsrAct(ucNsapi))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enCurrTinType)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrRatType))
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmPdpDeactivatedInd
 ��������  : ��ϢGMMSM_PDP_DEACTIVATED_IND�Ľ��մ���,����������PSȥע��
 �������  : ��������PDP״̬����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��10��
    ��    ��   : LUOKAIHUI/l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��10��22��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ:DTS2010102003076,E5 GCF����Ҫ��pdp�����ȥ����ﵽ��������,�������û��Ӧ�������ͷ���·
  3.��    ��   : 2010��10��29��
    ��    ��   : l00167671/�޿���
    �޸�����   : ���ⵥ�ţ�DTS2010100802035,CS ONLYģʽȥע��Ĵ���
  4.��    ��   : 2010��11��23��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2010112304706����ѡ�����жϿ����ź��ٴβ���ʧ��
  5.��    ��   : 2011��02��21��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ��DTS2011021900432:GMM��GMM_SERVICE_REQUEST_INITIATED״̬�յ�sm pdpȥ����
                 ָʾδ��T3340�ͷ�RRC����,����RRC��ʱ��δ�ͷ�,Ӱ��BG��������
  6.��    ��   : 2011��3��2��
    ��    ��   : z00161729
    �޸�����   : DTS2010071601574:RAU��������յ�rau accept��Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ�ڼ�,
                 cs only��������detach����,��RAU�����ٷ���

  7.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е����Ӵ���״̬
  8.��    ��   : 2011��8��12��
    ��    ��   : l65478
    �޸�����   : DTS2011081001476:ӡ���ⳡ����,�޷�����G->W
  9.��    ��   : 2011��12��23��
    ��    ��   : s46746
    �޸�����   : DTS2011122007386:PDP��ȥ�����,PS�����־δ���
  10.��    ��   : 2012��3��31��
     ��    ��   : z00161729
     �޸�����   : ֧��ISR�޸�

  11.��    ��   : 2012��10��17��
    ��    ��   : z40661
    �޸�����   : DTS2012092004258:PDPȥ����,����T3340��ʱ������GCFЭ��Ҫ���ش�����Ϊ3�Σ���Ҫ����15s
                 ��ʱ����

  12.��    ��   : 2012��11��17��
     ��    ��   : w00167002
     �޸�����   : DTS2012111409855:����ǰ�л�����Ϣ,���ͷŵ�����TD���ڲ�list��ʱ������û�����PDP���
                   ��ʱ��ȻulMsgHoldMskΪ�գ����Ի�����PS SERVICE��ʶ��������Ҫ�����.
                   ���򣬻Ὣ�˱�ʶά���ò���ȷ�������ڲ�LIST������ʱ��һֱ��ͣ��
  13.��    ��   : 2013��3��30��
     ��    ��   : l00167671
     �޸�����   : �����ϱ�AT�������������C��
  14.��    ��   : 2013��8��7��
     ��    ��   : w00167002
     �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                  �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                  ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                  ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
   15.��    ��   : 2014��01��13��
      ��    ��   : l65478
      �޸�����   : DTS2013102508485, �ĵ�PDPȥ�����UE�����ͷ���RRC����
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmPdpDeactivatedInd(VOS_VOID *pRcvMsg)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pSmPdpStatusInd;
    MMCGMM_DETACH_REQ_STRU             *ptr;
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurRat;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();

    pstConnStatus   = NAS_MML_GetConnStatus();

    pSmPdpStatusInd = (GMMSM_PDP_DEACTIVATED_IND_STRU *)pRcvMsg;

    /* û�ж���ʱ,���follow on��־ */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }


    /* ����ǰ�л�����Ϣ,���ͷŵ�����TD���ڲ�list��ʱ������û�����PDP���
       ��ʱ��ȻulMsgHoldMskΪ�գ����Ի�����PS SERVICE��ʶ��������Ҫ����� */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvSmPdpDeactivatedInd(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        /* pSmPdpStatusInd->ulPdpContextStatus�н��õ��˵�ʮ��λ */
        if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
        {
            /* �Ѿ�û�м����PDP */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "NAS_GMM_RcvSmPdpDeactivatedInd:Normal: Service is CS ONLY,Detach PS");

            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

            /* ����GMM״̬��ȥע�ỹ��������ȥע�� */
            if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
             || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
            {
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

				/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
                ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);
				/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                if (VOS_NULL_PTR == ptr)
                {
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                    return;
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
            }
            else if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
            {
                Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                && (GMM_RRC_RRMM_EST_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                {                                                               /* �����������ڽ�����������                 */
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

					 /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
                    ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);
					 /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                    if (VOS_NULL_PTR == ptr)
                    {
                        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                        return;
                    }
                    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
                }
                else
                {
                    Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
                }
            }
            else if ((GMM_REGISTERED_PLMN_SEARCH== g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
            {   /* ���ؽ�GMM״̬Ǩ��δע��״̬,����ǳ���������LL�Ѿ�������,��������ʱ��t3312δ��ʱ
                   �Ƿ���Ҫ����DETACH,����*/
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
                NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );


                /* ֪ͨGMM��ǰPS��DETACH��� */
                NAS_GMM_SndMmGprsDetachComplete();

                Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);

                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    Gmm_TimerStop(GMM_TIMER_T3314);
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

                    /* default 44s */
                    gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                }
            }
            else
            {
            }
        }
    }


    /* W��PDPȥ������GMM������������״̬��GMM_SERVICE_REQUEST_INITIATED��û�ж���ҵ��ʱ��Ҫ��T3340,
       �ȴ�RRC��·�ͷ�,�ڼ��յ���PDP��������GMM�������PDPȥ������·�ͷź��ٷ��� */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
     && (VOS_TRUE == g_GmmGlobalCtrl.ucRelConnAfterPdpDeact))
    {
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || ((GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
          && (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)))
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_WAIT_REL_PS_SIGNAL_VALUE;
            Gmm_TimerStart(GMM_TIMER_T3340);
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
        }
    }

    if ((VOS_FALSE == pstConnStatus->ucPsTbfStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_SndMmcTBFRelInd();
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
    {
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (NAS_MML_NET_RAT_TYPE_LTE != enCurRat))
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);

            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvSmPdpStatusInd
  Function : ԭ��GMMSM_PDP_STATUS_IND�Ľ��մ���
  Input    : VOS_VOID *pRcvMsg  ������Ϣʹ�õ�ͷ��ַ����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2. ��    ��   : 2009��05��05��
       ��    ��   : s62952
       �޸�����   : AT2D11639
    3. ��    ��   : 2009��06��30��
       ��    ��   : l65478
       �޸�����   : ���ⵥ��AT2D12655,�������LLC�������͵Ĵ���
    4. ��    ��   : 2009��06��30��
       ��    ��   : l65478
       �޸�����   : ���ⵥ��AT2D12677,�����жϣ���W�²���LL�������������Ϣ
    5. ��    ��   : 2010��11��23��
       ��    ��   : A00165503
       �޸�����   : ���ⵥ��: DTS2010112304706����ѡ�����жϿ����ź��ٴβ���ʧ��

    6. ��    ��   : 2011��8��9��
       ��    ��   : l00167671
       �޸�����   : ���ⵥ��DTS2011080502405 PDP STATUSά�����󣬵�����RAUʱIE��д����
    7. ��    ��   : 2012��10��18��
       ��    ��   : s00217060
       �޸�����   : DTS2012071702125:ucPdpStatusFlg��־ά������
    8.��    ��   : 2012��12��13��
      ��    ��   : L00171473
      �޸�����   : DTS2012121802573, TQE����
    9.��    ��   : 2012��3��15��
      ��    ��   : l65478
      �޸�����   : DTS2013120300990:��PDP��������з���RAU,��һ��PDP����ʧ��
   10.��    ��   : 2014��12��06��
      ��    ��   : A00165503
      �޸�����   : DTS2014120207400: ����ȥ������PDP, ���಻�ͷ�RRC����
   11.��    ��   : 2015��07��20��
      ��    ��   : zwx247453
      �޸�����   : 3 modem tas
*******************************************************************************/
VOS_VOID Gmm_RcvSmPdpStatusInd(
                           VOS_VOID *pRcvMsg                                    /* ������Ϣʹ�õ�ͷ��ַ����                 */
                           )
{
    GMMSM_PDP_STATUS_IND_STRU          *pSmPdpStatusInd;                        /* ����GMMSM_PDP_STATUS_IND_STRU����ָ��    */
    VOS_UINT8                           ucPrePdpStatusFlg;                      /* ԭ���Ƿ���ڼ����PDP context��־        */
    VOS_UINT8                           ucCurPdpStatusFlg;                      /* ��ǰ�Ƿ���ڼ����PDP context��־        */
    NAS_MML_PS_BEARER_CONTEXT_STRU      stPsBearCtx;
    VOS_UINT32                          i;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();


    PS_MEM_SET(&stPsBearCtx, 0x00, sizeof(stPsBearCtx));

    ucCurPdpStatusFlg = MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST;

    pSmPdpStatusInd = (GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg;                     /* �õ���Ϣָ��                             */

    ucPrePdpStatusFlg = pstConnStatus->ucPdpStatusFlg;

    /* ������Ϣ��pdp״̬����MML��ȫ�ֱ��� g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        stPsBearCtx.enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        stPsBearCtx.ucPsActPending   = VOS_FALSE;
        stPsBearCtx.ucPsDeactPending = VOS_FALSE;

        if (GMMSM_PDP_STATE_ACTIVE == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;

            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
            }
        }
        else if (GMMSM_PDP_STATE_ACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsActPending  = VOS_TRUE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else if (GMMSM_PDP_STATE_INACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsDeactPending = VOS_TRUE;
            ucCurPdpStatusFlg            = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else
        {
        }

        /* פ����L,��L����pdp״̬ */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetPsBearerCtx((VOS_UINT8)(i + NAS_MML_MIN_NSAPI), &stPsBearCtx);
        }
        /* LTE��ʱ,ֻ��Ҫ����״̬ΪPENDING��PDP״̬ */
        else
        {
            NAS_Gmm_ClearPendingPdpStatus();
        }

    }

    if ( MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;
    }
    else
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_TRUE;
    }

    if (ucPrePdpStatusFlg != pstConnStatus->ucPdpStatusFlg)
    {                                                                           /* PDP CONTEXT״̬�仯                      */
        Gmm_SndMmcPdpStatusInd(ucCurPdpStatusFlg);                              /* ֪ͨMMC���µ�PDP CONTEXT״̬             */
    }

    /* PDPȥ�����֪ͨLL��GRM���������û������������� */
    if(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmBeginSessionNotify
 ��������  : ��gmm��sm�ӿ��е�session typeת��Ϊgmm��gu������session type
 �������  : enGmmSmSessionType  - gmm��sm�ӿ��е�session type
 �������  : pucRrcSessionType   - gmm��gu������session type
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ConvertSmSessionTypeToRrc(
    GMMSM_SESSION_TYPE_ENUM_UINT8       enGmmSmSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmSessionType)
    {
        case GMMSM_SESSION_TYPE_CONVERSAT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case GMMSM_SESSION_TYPE_STREAM_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case GMMSM_SESSION_TYPE_INTERACT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case GMMSM_SESSION_TYPE_BACKGROUND_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmBeginSessionNotify_PreProc
 ��������  : �յ�sm��begin session��Ϣ�Ĵ���
 �������  : pstBeginSessionMsg  - �յ�sm begin session��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��23��
    ��    ��   : c00318887
    �޸�����   : DTS2015082604451:�޸�DSDS���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmBeginSessionNotify_PreProc(
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif     

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_START);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmEndSessionNotify_PreProc
 ��������  : �յ�sm��end session��Ϣ�Ĵ���
 �������  : pstEndSessionMsg  - �յ�sm end session��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��23��
    ��    ��   : c00318887
    �޸�����   : DTS2015082604451:�޸�DSDS���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmEndSessionNotify_PreProc(
    GMMSM_END_SESSION_NOTIFY_STRU      *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif 

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_FINISH);

    return;
}



/*******************************************************************************
  Module   : Gmm_ComPlmnSearchInit
  Function : ����PLMN����ʱGMM�����ڲ������ĳ�ʼ��
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��    ��   : 2007��07��05��
      ��    ��   : L65478
      �޸�����   : created
    2.��    ��   : 2008��7��2��
      ��    ��   : l00107747
      �޸�����   : �������ⵥ�ţ�AT2D03900
    3.��    ��   : 2011��3��12��
      ��    ��   : z00161729
      �޸�����   : �������ⵥ�ţ�DTS2011022400350����δע��ʱpdp������ָ������pdp����ʧ��
    4.��    ��   : 2011��07��13��
      ��    ��   : w00166186
      �޸�����   : V7R1 PHASE II ATTACH/DETACH����
    5.��    ��   : 2011��04��14��
      ��    ��   : ŷ����
      �޸�����   : DTS2011041202700,��PS����Ч��״̬��Ǩ�����޷��񣬵���Ӧ�ò�ѯSYSINFO
                   ʱ��ʾ����Ч��
    6.��    ��   : 2011��03��24��
      ��    ��   : ŷ����
      �޸�����   : ���ⵥ��:DTS2011032400460��פ���ɹ����û�ָ������������������
                   ����פ����T3312��ʱ��MM�����˲�������LAU
    7.��    ��   : 2011��11��18��
      ��    ��   : w00167002
      �޸�����   : DTS2011110300229:G��CSonlyʱ��������CSʧ��3�κ��û�����ATTACH��
                   ʧ��4�˺��û���RPlmn��������PS���ע�ᡣ��GMM suspend״̬��
                   �յ���������󣬽�GMM״̬Ǩ�Ƶ�����״̬��
    8.��    ��   : 2013��8��7��
      ��    ��   : w00167002
      �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
    9.��    ��   : 2013��10��05��
      ��    ��   : l65478
      �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
    10.��    ��   : 2015��1��26��
       ��    ��   : z00161729
       �޸�����   : AT&T ֧��DAM�����޸�
   11.��    ��   : 2016��3��1��
      ��    ��   : z00359541
      �޸�����   : DTS2016022908722: ��������ʱ��ͣT3302��ʱ��
*******************************************************************************/
VOS_VOID Gmm_ComPlmnSearchInit()
{
    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {
        /* ��ǰ��ΪPS����Ч */
        if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);                        /* ����״̬�Ĺ�������                       */
            if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
            {
                Gmm_TimerStop(GMM_TIMER_T3311);

            }
        }
    }
    else if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM != g_GmmGlobalCtrl.ucPlmnSrchPreSta))
    {                                                                           /* REGISTERED״̬���ҷ�������               */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);                              /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);

    }

    else if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }


        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {   /*ֻ���û������detach���̲Ż����GMM_DEREGISTERED_INITIATED*/
        /*����Ҫ�жϵ�ǰdetach����*/
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }
        else
        {

        }

        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        if (GMM_MSG_HOLD_FOR_RAU
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {                                                                       /* ����б�����RAUԭ��                      */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);   /* ��ȡRAUԭ���ַ                          */
        }
        Gmm_ComCnfHandle();
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        Gmm_ComCnfHandle();
    }
    else if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_SUSPENDED);

        g_GmmRauCtrl.ucNpduCnt = 0x0;
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        else
        {
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                           GMM_RABM_IMMEDIATELY_RAU);
#endif

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        GMM_BufferMsgDump();

        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }
    else if ( GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState )
    {
        /* ǩ������״̬ */
        if ( (0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
          || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
        }

        /* GSM�µ�ϵͳ��Ϣ��ʼ�� */
        NAS_GMM_FreeGsmSysInfo();

        /* �������ݵĴ��� */
        GMM_BufferMsgResume();
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* �����еȴ�cnf                            */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �����ǰ����                             */
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* ��������Ĺ���                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* �����¼��CSͨ��������                   */

}


/*******************************************************************************
  Module   : Gmm_RcvMmcPlmnUserSelReq
  Function : �յ�ԭ��MMCGMM_PLMN_USER_SEL_REQ�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��  ��  2003.12.10  �¹�����
  2. ��    ��   : 2006��12��5��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�A32D10052
  3. ��    ��   : 2007��09��03��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�AT2D01459
  4. ��    ��   : 2007��10��16��
     ��    ��   : l65478
     �޸�����   : �������ⵥ�ţ�A32D11957
  5. ��    ��   : 2011��07��13��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  6.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPlmnUserSelReq(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_VOID            *pAddr;

    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ж��Ƿ����������                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                   /* �ͷ�����                                 */
    }

    if (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    Gmm_ComPlmnSearchInit();

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* �õ���Ϣͷ                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* ���P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */
            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC����MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* ����״̬�Ĺ�������                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);                /* ��SIM�������ڱ�־                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* ���IMSI����MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* ���P_TMSI����MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;      /* ���P_TMSI_SIGNATURE����MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                 /* ֪ͨRRC NAS����Ϣ�仯                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */

    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : GMM_ComCheckRauIntegrityProtection
 ��������  : RAU Accept��Ϣ�����Լ��
 �������  : VOS_UINT8 *pucMsgContent
             VOS_UINT16  usMsgLen
 �������  : ��
 �� �� ֵ  : GMM_TRUE--RAU ACCEPT��Ϣ�����Լ��ͨ��
             GMM_FALSE--RAU ACCEPT��Ϣ�����Լ�鲻ͨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2008��8��4��
   ��    ��   : luojian id:107747
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��1��18��
   ��    ��   : o00132663
   �޸�����   : DTS2011011803318,������RAU�������������Ա�����RAU ACCEPT�з������µ�P-TMSI����ϢӦ�ñ�����
 3.��    ��   : 2011��3��3��
   ��    ��   : z00161729
   �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
 4.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 5. ��    ��   : 2012��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                 ��������rau
*****************************************************************************/
VOS_UINT32 GMM_ComCheckRauIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                                VOS_UINT32  ulMsgLen)
{
    GMM_RAI_STRU                        stRauRai;
    VOS_UINT8                           aucRauPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT8                           ucPtmsiAvail;
    VOS_UINT32                          ulIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*ROUTING AREA UPDATE ACCEPT (at periodic routing area update with no
        change of routing area or temporary identity)*/
        if (GMM_FALSE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            return GMM_FALSE;
        }

        /* ��ȡ RAU ACCEPT��Ϣ RAI����*/
        Gmm_FillRaiForRcv(&stRauRai, &pucMsgContent[4]);

        ucPtmsiAvail = GMM_FALSE;
        PS_MEM_SET(aucRauPtmsi, 0x00, NAS_MML_MAX_PTMSI_LEN);

        /* ��ȡ RAU ACCEPT��Ϣ PTMSI����*/
        for (ulIeCount=10; ulIeCount < ulMsgLen; ulIeCount++ )
        {
            if (GMM_IEI_P_TMSI_SIGNATURE == pucMsgContent[ulIeCount])
            {
                /* P-TMSI signatureΪ4���ֽڣ��˴���3��Forѭ���ټ�1 */
                ulIeCount += 3;
                continue;
            }

            if (GMM_IEI_ALLOCATED_PTMSI == pucMsgContent[ulIeCount])
            {
                if ( GMM_MOBILE_ID_TMSI_PTMSI == (pucMsgContent[ulIeCount+2] & 0x07) )
                {
                    ucPtmsiAvail = GMM_TRUE;
                    PS_MEM_CPY(aucRauPtmsi, &pucMsgContent[ulIeCount+3], NAS_MML_MAX_PTMSI_LEN);
                }
                break;
            }
        }

        /* ���RAIû�з����ı� */
        if (GMM_TRUE == Gmm_Com_CmpRai(&stRauRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
        {
            /* û�з���PTMSI */
            if (GMM_FALSE == ucPtmsiAvail)
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            /* �����PTMSI����ǰ��ͬ */
            else if ( 0 == VOS_MemCmp(aucRauPtmsi,NAS_MML_GetUeIdPtmsi(),NAS_MML_MAX_PTMSI_LEN) )
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}

/*****************************************************************************
 �� �� ��  : GMM_ComCheckIntegrityProtection
 ��������  : �����Լ��
 �������  : VOS_UINT8 *pucMsgContent
             VOS_UINT16  usMsgLen
 �������  : ��
 �� �� ֵ  : GMM_TRUE -- �����Լ��ͨ��
             GMM_FALSE -- �����Լ�鲻ͨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��8��4��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��3��3��
    ��    ��   : z00161729
    �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
  3.��    ��   : 2013��11��18��
    ��    ��   : w00167002
    �޸�����   : DTS2013112006986:������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                 TD�²�����SMC���̡�
*****************************************************************************/
VOS_UINT32 GMM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                            VOS_UINT32  ulMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* ���ٽ���ģʽ���ڲ���ģʽ�������������Լ�� */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return GMM_TRUE;
    }

    /* �����Լ���������UMTS���� */


    /* �����Լ���������UMTS���� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }

    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())

    {
        return GMM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (GMM_PD_GMM == ucPD)
        {
            ucMsgType = pucMsgContent[1];
            switch (ucMsgType)
            {
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                case GMM_MSG_IDENTITY_REQUEST:
                case GMM_MSG_ATTACH_REJECT:
                case GMM_MSG_RAU_REJECT:
                case GMM_MSG_SERVICE_REJECT:
                    ulIntegrityCheckResult = GMM_TRUE;
                    break;
                case GMM_MSG_RAU_ACCEPT:
                    ulIntegrityCheckResult =
                     GMM_ComCheckRauIntegrityProtection(pucMsgContent,ulMsgLen);
                    break;

                case GMM_MSG_DETACH_ACCEPT:
                    /* DETACH ACCEPT (for non power-off) */
                    if ((GMM_GPRS_DETACH_POWEROFF != g_GmmGlobalCtrl.ucSpecProc)
                      && (GMM_COMBINED_DETACH_POWEROFF !=
                                            g_GmmGlobalCtrl.ucSpecProc))
                    {
                        ulIntegrityCheckResult = GMM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if (GMM_PD_RSV_FOR_TEST == ucPD)
        {
            ulIntegrityCheckResult = GMM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg
 ��������  : �Ƿ���Ҫ����ptmsi�ط�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��5��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg (VOS_VOID)
{
    /* 24008 4.7.5.1.5 �½���������:
    Routing area updating and P-TMSI reallocation procedure collision
    - If the MS receives a P-TMSI REALLOCATION C0MMAND message before the routing area
    updating procedure has been completed, the P-TMSI reallocation procedure shall
    be aborted and the routing area updating procedure shall be progressed.*/
    if (NAS_GMM_SPEC_PROC_TYPE_RAU == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
    {
        return VOS_FALSE;
    }

    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4�½���������:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. detach���������detach ���Ͳ�Ϊimsi detach�򲻴��� */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcStatusMsg
 ��������  : �Ƿ���Ҫ����gmm status��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��5��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcStatusMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4�½���������:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach���������detach ���Ͳ�Ϊimsi detach�򲻴��� */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcGmmInfoMsg
 ��������  : �Ƿ���Ҫ����gmm infomation��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��5��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcGmmInfoMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4�½���������:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach���������detach ���Ͳ�Ϊimsi detach�򲻴��� */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



/*******************************************************************************
  Module   : Gmm_RcvRrmmDataInd
  Function : RRMM_DATA_IND���մ���
  Input    : VOS_VOID *pRcvMsg  ������Ϣʹ�õ�ͷ��ַ����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.  ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��12��5��
      ��    ��   : luojian 60022475
      �޸�����   : Maps3000�ӿ��޸�
    3.��    ��  : 2007��12��21��
      ��    ��  : l00107747
      �޸�����  : ���ⵥ��:A32D13951
    4.��    ��   : 2009��09��25��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:AT2D14675,RAU/Attach�����У�list����ʧ��
    5. ��    ��   : 2010��10��16��
       ��    ��   : o00132663
       �޸�����   : DTS2010101401399:�յ�С����ѡ������Ϣ��GMM֪ͨLL�����CM�����������
    6. ��    ��   : 2011��05��11��
       ��    ��   : f00179208
       �޸�����   : DTS2011051003575:GģGCF����:44.2.3.2.5-1ʧ�ܡ�
                    RAU���ܺ��������������������²�2û�н�RLC ACK���͵���������������ط���RAU Reject
    7.��    ��  : 2013��03��13��
      ��    ��  : z00214637
      �޸�����  : BodySAR��Ŀ
    8.��    ��   : 2013��3��30��
      ��    ��   : l00167671
      �޸�����   : �����ϱ�AT�������������C��
    9.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmDataInd(
                        VOS_VOID *pRcvMsg                                       /* ������Ϣʹ�õ�ͷ��ַ����                 */
                        )
{
    RRMM_DATA_IND_FOR_PCLINT_STRU  *pRrmmDataInd;
    NAS_MSG_FOR_PCLINT_STRU        *pNasMsg;
    NAS_MSG_STRU                   *pGmmStatus;

    pRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pRcvMsg;                    /* �õ���Ϣ���׵�ַ                         */
    if ( RRC_NAS_CS_DOMAIN == pRrmmDataInd->ulCnDomainId )
    {                                                                           /* �������Ϣ                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: CS data is received in RRMM_DATA_IND");
        return;
    }
    if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��ǰû������                             */
        if (GMM_FALSE == GMM_IsCasGsmMode())
        {                                                                       /*3G�������ǰû�����ֱ�ӷ��ء�2G���������ӱ�־ʼ����Ч */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Signalling connection is not existed");
            return;
        }
    }

    pNasMsg = &pRrmmDataInd->RcvNasMsg;                                         /* �õ�NAS��Ϣ�ṹ�ĵ�ַ                    */
    if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        && (GMM_PD_RSV_FOR_TEST != (pNasMsg->aucNasMsg[0] & 0x0F)))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: In TC_ACTIVE, other NT message than TC is omitted");
        Gmm_MemFree(pRcvMsg);                                                   /* �ͷŽ��յ�����Ϣ�ڴ�                     */
        return;
    }

    if (2 > pNasMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ����                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Message from NT is too short");
        return;
    }

    if (GMM_FALSE == GMM_ComCheckIntegrityProtection(pNasMsg->aucNasMsg, pNasMsg->ulNasMsgSize))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Integrity Check Fail");
    }
    else
    {

        /* �յ��˴���������NAS����Ϣ */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch (pNasMsg->aucNasMsg[0] & 0x0F)
        {                                                                       /* ����Protocol discriminator�ַ�           */
        case GMM_PD_GMM:
            if (0 != ( pNasMsg->aucNasMsg[0] & 0xF0))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: NT message is invalid");
                return;
            }

            GMM_ReportN2MOtaMsg((NAS_MSG_STRU *)pNasMsg);


            switch (pNasMsg->aucNasMsg[1])
            {                                                                   /* ����Message type�ַ�                     */
            case GMM_MSG_ATTACH_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* 2G�����£�֪ͨGAS��GMM������ɣ�GRR��ֹͣnon_DRX״̬ */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }

                Gmm_RcvAttachAcceptMsg(pNasMsg);                                /* �տ���ϢAttach accept�Ľ��մ���          */
                break;
            case GMM_MSG_ATTACH_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {/* 2G�����£�֪ͨGAS��GMM������ɣ�GRR��ֹͣnon_DRX״̬ */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvAttachRejectMsg(pNasMsg);                                /* �տ���ϢAttach reject�Ľ��մ���          */
                break;
            case GMM_MSG_DETACH_REQUEST:
                if(GMM_TRUE == GMM_IsCasGsmMode())
                {
                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvDetachRequestMsg(pNasMsg);                               /* �տ���ϢDetach request�Ľ��մ���         */
                break;
            case GMM_MSG_DETACH_ACCEPT:
                Gmm_RcvDetachAcceptMsg(pNasMsg);                                /* �տ���ϢDetach accept�Ľ��մ���          */
                break;
            case GMM_MSG_RAU_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateAcceptMsg(pNasMsg);                     /* �տ���ϢRouting area update accept�Ľ��� */
                break;
            case GMM_MSG_RAU_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

                    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateRejectMsg(pNasMsg);                     /* �տ���ϢRouting area update reject�Ľ��� */
                break;
            case GMM_MSG_SERVICE_ACCEPT:
                Gmm_RcvServiceAcceptMsg(pNasMsg);                               /* �տ���ϢService Accept�Ľ��մ���         */
                break;
            case GMM_MSG_SERVICE_REJECT:
                Gmm_RcvServiceRejectMsg(pNasMsg);                               /* �տ���ϢService Reject�Ľ��մ���         */
                break;
            case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
                if (VOS_TRUE == NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg())
                {
                    Gmm_RcvPtmsiReallocationCommandMsg(pNasMsg);                /* �տ���ϢP-TMSI reallocation command����  */
                }
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                Gmm_RcvAuthenAndCipherRequestMsg(pNasMsg);                      /* Authentication and ciphering request���� */
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                Gmm_RcvAuthenAndCipherRejectMsg(pNasMsg);                       /* Authentication and ciphering reject����  */
                break;
            case GMM_MSG_IDENTITY_REQUEST:
                Gmm_RcvIdentityRequestMsg(pNasMsg);                             /* �տ���ϢIdentity request�Ľ��մ���       */
                break;
            case GMM_MSG_GMM_STATUS:
                if (VOS_TRUE == NAS_GMM_IsNeedProcStatusMsg())
                {
                    Gmm_RcvGmmStatusMsg(pNasMsg);                               /* �տ���ϢGMM Status�Ľ��մ��� */
                }
                break;
            case GMM_MSG_GMM_INFORMATION:
                if (VOS_TRUE == NAS_GMM_IsNeedProcGmmInfoMsg())
                {
                    Gmm_RcvGmmInformationMsg(pNasMsg);                          /* �տ���ϢGMM Information�Ľ��մ��� */
                }
                break;
            default :
                pGmmStatus = Gmm_GmmStatusMsgMake(
                    NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: The MsgType is Abnormal");
                break;
            }
            break;

        case GMM_PD_SM:
            Gmm_SndSmDataInd(pNasMsg);                                          /* ԭ��GMMSM_DATA_IND�ķ��ʹ���             */
            break;

        case GMM_PD_SMS:
            if (GMM_NULL_PROCEDURE == g_GmmGlobalCtrl.ucSpecProc)
            {
                Gmm_SndSmsUnitdataInd(pNasMsg);                                 /* ԭ��PMMSMS_UNITDATA_IND�ķ��ʹ���        */
            }
            break;

        case GMM_PD_RSV_FOR_TEST:
            Gmm_SndTcDataInd(pNasMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Protocol discriminator is Error");
            break;
        }
    }

    return;
}

/*******************************************************************************
  Module   : GMM_RcvMmcRelReq
  Function : �յ�ԭ��MMCGMM_REL_REQ�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��    ��   : 2008��12��7��
     ��    ��   : l00130025
     �޸�����   : �������ⵥ�ţ�AT2D07018,�����Ӵ���ʱSYSCFG����ʱ�����
  2. ��    ��   : 2009��10��3��
     ��    ��   : l00130025
     �޸�����   : �������ⵥ�ţ�AT2D14890,W����ģʽI��,CS detach������SYSCFGʧ��
  3. ��    ��   : 2010��10��11��
     ��    ��   : z00161729
     �޸�����   : ���ⵥ��DTS2010100900058:GMM�յ�MMC��REL_REQ��Ϣʱ��Ҫ���attch/RAU������,��Ϊ���attach/RAU
                     ����������������,MMC�ᷢ��list����,���²���Ӧ�û����ֶ���������
  4. ��    ��   : 2011��7��11��
     ��    ��   : sunxibo 46746
     �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
  5. ��    ��   : 2011��7��14��
     ��    ��   : zhoujun 40661
     �޸�����   : ����MML_CTX�е����Ӵ���״̬
  6. ��    ��   : 2011��11��14��
     ��    ��   : w00167002
     �޸�����   : ������ע�ᱻָ���Ѵ�ϣ�MMC��GMM�������������ͷ����󣬴�ʱ��Ҫ
                   ��¼��ǰ��GMM״̬����ָ���ѵ������BG�ѳ���ע��ʱ��������ͬʱ��
                   �����ϴγɹ�ע������粻һ��ʱ��Ҳ��Ҫ����·�������¡�
  7. ��    ��   : 2012��11��7��
     ��    ��   : s00217060
     �޸�����   : DTS2012060507813: GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ�����
                   GMM������㷢���ͷ����������ͷź��·�SYSCFG
  8. ��    ��   : 2013��06��27��
     ��    ��   : l65478
     �޸�����   : DTS2013062406563:EMO�Ŀ���OOSʱû��פ����SBM������
*******************************************************************************/
VOS_VOID GMM_RcvMmcRelReq(
    VOS_VOID                           *pMsg                                    /* ��Ϣָ��                                 */
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ�����
       GMM������㷢���ͷ����������ͷź��·�SYSCFG */

    /* ֪ͨWRR�ͷ�����.��״̬������״̬ʱ,˵��ԭ���Ѿ�֪ͨ�������ͷ�,����Ҫ�ظ�֪ͨ */
    if (((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
        case GMM_REGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegInit();
            break;
        case GMM_DEREGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_DeregInit();
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_GMM_RcvMmcRelReq_RauInit();
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegImsiDtchInit();
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo();
            break;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            break;
        default:
            break;
    }

    if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {                                                                           /* ��ǰ���ڷ�ע��״̬                       */
        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }
    else
    {                                                                           /* ��ǰ����ע��״̬                         */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    /* �����û��棬��֤���ݲ����·� */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcRelReq_RegInit
 ��������  : ����ע������н��յ�MMCģ����ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2. ��    ��   : 2014��06��12��
    ��    ��   : s00217060
    �޸�����   : DTS2014061003286:TD2G��ѡ��G��RAU�����У��û�ָ����TD�����磬���粻��Ӧ����ҵ��accept

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RegInit()
{
    /* ֹͣע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3310);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }


    /* �յ�MMC��rel req,��Ϊע��ʧ�ܣ�����ע��ʧ�ܵĴ�����RauInit״̬ʱ�յ�rel_ind�Ĵ������� */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);             /* ����attach attempt counter�Ĵ���         */

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���fallowon��־                         */

    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);



    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcRelReq_DeregInit
 ��������  : ����ȥע������н��յ�MMCģ����ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1. ��    ��   : 2011��7��11��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
 2. ��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
 3. ��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_DeregInit()
{
    /* ֹͣȥע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_RR_REL);

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_DeregInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcRelReq_RauInit
 ��������  : ����·�������¹����н��յ�MMCģ����ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��06��12��
   ��    ��   : s00217060
   �޸�����   : DTS2014061003286:TD2G��ѡ��G��RAU�����У��û�ָ����TD�����磬���粻��Ӧ����ҵ��accept

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RauInit()
{

    /* ֹͣ·���������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3330);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* �յ�MMC��rel req,��Ϊע��ʧ�ܣ�����ע��ʧ�ܵĴ�����RauInit״̬ʱ�յ�rel_ind�Ĵ������� */

    /* �����Ա�����־��ΪDEACTIVE */
    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* ���RAU��LU��־ */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    /* ������ڼ�Ȩ��������ȴ���־ */
    NAS_GMM_ClearAuthInfo();


    /* ������ڽ���������ȴ���־ */
    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ���Ӧ��־                           */
    }

    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* ����RAU attempt counter�Ĵ���            */

    /* free֮ǰ�����ϵͳ��Ϣ */
    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();


    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcRelReq_RegImsiDtchInit
 ��������  : ����IMSIȥע������н��յ�MMCģ����ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RegImsiDtchInit()
{
    /* ֹͣȥע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_RegImsiDtchInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo
 ��������  : ������ϵͳ��ѡ�ȴ�ϵͳ��Ϣ�����н��յ�MMCģ����ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo()
{
    /*��ϵͳ�ı�ʱ֪ͨRABM*/
    g_GmmRauCtrl.ucNpduCnt = 0x0;
    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
}


/*******************************************************************************
  Module   : Gmm_RcvMmcCoverageLostInd
  Function : �յ�ԭ��MMCGMM_COVERAGE_LOST_IND�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.08  �¹�����
  2. ��    ��   : 2007��6��9��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D11579,���CS Service Exit��־
  3. ��    ��   : 2008��12��3��
     ��    ��   : ouyangfei id:00132663
     �޸�����   : �������ⵥ�ţ�AT2D07165,��W�����RR���ӽ��������ж���������WRR��RRMM_REL_REQ��
  4.��    ��   : 2009��01��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D07971,������״̬���ϱ��Ľ��뼼������
  5.��    ��   : 2009��03��12��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
  6. ��    ��   : 2009��05��23��
     ��    ��   : L65478
     �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
  7.��    ��   : 2009��08��13��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D13662,3G���ϱ���out of coverage�����ǻ�����ϱ�PS_Service
  8.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�
  9.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 10.��    ��   : 2011��7��28��
    ��    ��   : sunxibo 46746
    �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 11.��    ��   : 2011��04��14��
    ��    ��   : ŷ����
    �޸�����   : DTS2011041202700,��PS����Ч��״̬��Ǩ�����޷��񣬵���Ӧ�ò�ѯSYSINFO
                   ʱ��ʾ����Ч��
 12.��    ��   : 2011��11��22��
    ��    ��   : w00166186
    �޸�����   : DTS2011112101648,OOS�ȴ�ϵͳ��Ϣ��ʱ���������ӱ�־û����������º���AVAILABLE
                 ��ʱ����ʱ��û�з�������
 13.��    ��   : 2011��12��26��
    ��    ��   : w00166186
    �޸�����   : DTS2011122305611,was����̬�ϱ�AREA_LOSTû����������
 14.��    ��   : 2012��05��04��
    ��    ��   : l65478
    �޸�����   : DTS2012042802989,�ڳ�������ʱ����˻����SM��Ϣ,
                   �ؽ���������PDP������
 15.��    ��   : 2011��12��28��
    ��    ��  : l00167671
    �޸�����  : �޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
                 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
                 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
                 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
 16.��    ��   : 2013��07��23��
    ��    ��   : l65478
    �޸�����   : DTS2013071809030,MMC�յ�RRMM_SUSPEND_REL_CNF��û�����̴������SYSCFG
 17.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
 18.��    ��   : 2013��10��05��
    ��    ��   : l65478
    �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
 19.��    ��   : 2015��1��12��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI�޸�
  20.��    ��   : 2015��6��5��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvMmcCoverageLostInd(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_VOID            *pAddr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* ����ʱ, ָʾRABM��ǰϵͳģʽ, ������RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* ��GSMģʽ�£����������������ʱ��Ҫ����LLC����ֹ�û�������������� */
    if(GMM_TRUE == GMM_IsCasGsmMode())
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE;
        }
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    g_GmmGlobalCtrl.ucCvrgAreaLostFlg     = GMM_TRUE;
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg   = GMM_FALSE;
    g_GmmGlobalCtrl.ucCipherStartFlg      = GMM_FALSE;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ֹͣT3310                                */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ֹͣT3317                                */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ֹͣT3321                                */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ֹͣT3330                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* ֹͣT3340                                */

    if (GMM_TIMER_PROTECT_FOR_SIGNALING_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_PROTECT_FOR_SIGNALING_FLG))

    {                                                                           /* ����Timer�Ƿ�������,��                   */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);                         /* ͣ����Timer                              */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ�cnf                                */
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���T3311������                          */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ֹͣT3311                                */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* �ָ����б������Timer                    */
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvCoverLost_RegInit();
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvCoverLost_DeregInit();
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvCoverLost_RauInit();
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvCoverLost_ServReqInit();
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_RcvCoverLost_RegNmlServ();
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvCoverLost_RegImsiDtchInit();
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvCoverLost_SuspendWaitForSys();
        break;
    default:
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* PS ����Ч��״̬��Ǩ�� */
    if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {                                                                       /* ��ǰ���ڷ�ע��״̬                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                  /* ����״̬�Ĺ�������                       */
        }
        else
        {                                                                       /* ��ǰ����ע��״̬                         */
            Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);                    /* ����״̬�Ĺ�������                       */
        }
    }

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* �õ���Ϣͷ                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* ���P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */
            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC����MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* ����״̬�Ĺ�������                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
            NAS_MML_SetSimPresentStatus(VOS_FALSE);                             /* ��SIM�������ڱ�־                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* ���IMSI����MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* ���P_TMSI����MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;/* ���P_TMSI_SIGNATURE����MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                /* ֪ͨRRC NAS����Ϣ�仯                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */

        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;
        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                             /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }

    Gmm_FreeBufferMsgWithoutSm();

    g_GmmReqCnfMng.ucCnfMask            = 0;                                    /* �����еȴ�cnf                            */
    g_GmmGlobalCtrl.ucSpecProc          = GMM_NULL_PROCEDURE;                   /* �����ǰ����                             */
    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_NULL_PROCEDURE;                   /* ��������Ĺ���                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* �����¼��CSͨ��������                   */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcCoverageLostInd:INFO: specific procedure ended");

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcPlmnSearchInitiated
  Function : �յ�ԭ��MMCGMM_PLMN_SEARCH_INITIATED�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��    ��   : 2007��4��26��
       ��    ��   : liurui id:40632
       �޸�����   : �������ⵥ�ţ�A32D10052
    3. ��    ��   : 2007��07��02��
       ��    ��   : l65478
       �޸�����   : �������ⵥ�ţ�A32D10052
    4. ��    ��   : 2007��10��16��
       ��    ��   : l65478
       �޸�����   : �������ⵥ�ţ�A32D11957
     5.��    ��   : 2010��12��23��
       ��    ��   : s46746
       �޸�����   : DTS2010122305821:GPRS���������и����ȼ���ʱ����ʱ�ᷢ��ָ������
    6. ��    ��   : 2010��12��24��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
    7. ��    ��   : 2011��7��28��
       ��    ��   : sunxibo 46746
       �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
    8. ��    ��   : 2011��12��8��
       ��    ��   : s46746
       �޸�����   : ���ⵥ�ţ�DTS2011111603445,���յ�ϵͳ��Ϣ���Ҳ�2�Ѿ�ָ�ɺ���ָܻ�RABM
    9. ��    ��   : 2011��12��7��
       ��    ��   : w00176964
       �޸�����   : RRC��������
    10.��    ��   : 2011��12��28��
       ��    ��  : l00167671
       �޸�����  : �޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
                 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
                 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
                 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
     11.��    ��   : 2015��6��5��
        ��    ��   : z00161729
        �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPlmnSearchInitiated(VOS_VOID)
{

    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;                          /* ����ϵͳ��Ϣ��Ч�ı�־                   */

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);
    }
    else
    {
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬ΪNULL״̬                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPlmnSearchInitiated:WARNING: GMM state is VOS_NULL_PTR(Gmm_RcvMmcPlmnSearchInitiated)");
        return;
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    if ((GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
        }
        else
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
        }

        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);

        Gmm_ComPlmnSearchInit();
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcStartReq
  Function : �յ�ԭ��MMCGMM_START_REQ�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��־��  2004.10.27  CK��IK�洢�ṹ���

 3.��    ��   : 2011��7��12��
   ��    ��   : zhoujun 40661
   �޸�����   : SIM�����ݱ�����MML�У�ɾ��GMM��Ҫ���µ�����
 4.��    ��   : 2012��2��22��
   ��    ��   : w00199382
   �޸�����   : B060��Ŀ��ֲ������
 5.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
 6.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcStartReq(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucTmpTmsi;
    VOS_UINT32                          ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsiSig;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;
#endif

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* ��ǰפ����������뼼�� */

    enNetRatType = NAS_MML_GetCurrNetRatType();

    Gmm_ComReset();                                                             /* ����reset�������� */

    GMM_CasChangSysMode(enNetRatType);


#if (FEATURE_ON == FEATURE_LTE)

    /* ��¼����ʱ��MS Radio Capability��Ӧ�Ľ��뼼���б� */
    PS_MEM_CPY(&(g_GmmGlobalCtrl.UeInfo.stRadioCpbRelatedRatList),
               NAS_MML_GetMsPrioRatList(),
               sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
#endif


    /* ��ǰ��Ȼ֧��UMTS��Ȩ */
    g_GmmAuthenCtrl.ucUmtsAuthFlg           = GMM_UMTS_AUTHEN_SUPPORTED;

    /* ��ǰ��Ȼ֧��GMM INFORMATION */
    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg = GMM_SUPPORT_INFORMATION_MSG;

    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    enCallMode = NAS_MML_GetCallMode();
#endif

    /* ���õ�ǰPS���Ƿ���Ч */
    if ((VOS_TRUE == NAS_MML_GetSimPresentStatus())
#if (FEATURE_ON == FEATURE_ECALL)
     /* ����3GPP 24.008 section 4.7:
     * 1. An eCall only mobile station shall not perform a normal or combined GPRS attach procedure.
     * 2. An eCall only mobile station shall not perform any kind of GPRS detach procedure.
     * 3. An eCall only mobile station shall not perform a normal or combined routing area updating procedure.
     * �����GMM��������PS sim��Ч��ʹ����GMM����NO_IMSI״̬
     */

     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
    {
        NAS_MML_SetSimPsRegStatus(VOS_TRUE);
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_IMSI;
    }
    else
    {
        NAS_MML_SetSimPsRegStatus(VOS_FALSE);
        Gmm_SndMmcStartCnf();
        return;
    }

    /* ���ݵ�ǰ�洢��TMSI�Ƿ���Ч���趨�Ƿ����PTMSI */
    ulInvalidCnt = 0;
    pucTmpTmsi = NAS_MML_GetUeIdPtmsi();
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (GMM_PTMSI_INVALID == pucTmpTmsi[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI ��Ч                              */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }
    else
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;
    }

    ulInvalidCnt = 0;
    pucTmpTmsiSig = NAS_MML_GetUeIdPtmsiSignature();

    ulInvalidCnt = 0;
    for (i=0; i<NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        if (GMM_PTMSI_SIGNATURE_INVALID == pucTmpTmsiSig[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI signature��Ч                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

    }
    else
    {                                                                           /* P-TMSI signature��Ч                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* ������Ӧ���ڱ�ʶ                         */
    }


    /* Ϊ�˷�ֹʹ�ò��ԺŶαܹ�IMSI�ļ�飬ʹ���ܹ�ʹ��TMSI����ע�ᣬ��Ҫ
       ���з��������ж�����NV��������£�����Ŷ�TMSI��Ϊ��Ч
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdPtmisInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }


    Gmm_SndMmcStartCnf();

    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckSimStatusAffectAttach
 ��������  : ���ATTACH���ͺ�USIM״̬�ĳ�ͻ
 �������  : MMCGMM_ATTACH_REQ_STRU              *pstAttachReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��5��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckSimStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS����Ч��MMC_GMM_ATTACH_TYPE_GPRS_IMSI����ת��ΪMMC_GMM_ATTACH_TYPE_GPRS */
    if ( ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
      && ( VOS_TRUE != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: CS USIM is invalid.");

        if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* USIM PS����Ч��ֱ�ӻظ�ATTACH CNF */
    if ( ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
      && ( VOS_TRUE                 != pstUsimStatus->ucSimPsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM,"NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: PS USIM is invalid.");

        NAS_GMM_SndMmcAttachCnf();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ModifyAttachType
 ��������  : �޸�attach����
 �������  : MMCGMM_ATTACH_REQ_STRU              *pstAttachReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��5��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_ModifyAttachType(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        /* ������ģʽI���յ�CS ATTACH��GMM������ */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType)
        {
            return VOS_TRUE;
        }

        /* ������ģʽI���յ�CS+PS ATTACH����ΪGPRS ATTACH */
        if (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_IsAttachRepeated
 ��������  : ���ATTACH��ͻ
 �������  : VOS_UINT32 enAttachType
             VOS_UINT32 ulOpID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��13��
   ��    ��   : W00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* ֮ǰ����PS ATTACH �յ�PS ATTACH������OPID��ֱ�ӷ��� */
    if ( ( GMM_WAIT_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType ) )
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    /* ֮ǰ����CS ATTACH �յ�CS ATTACH��ֱ�ӷ��� */
    if ( ( GMM_WAIT_CS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType ) )
    {
        return VOS_TRUE;
    }

    if ( GMM_WAIT_CS_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
    {
        /* ֮ǰ����PS ATTACH �յ�CS+PS ATTACH���յ�PS ATTACH����OPID */
        if (MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*******************************************************************************
 �� �� ��  : NAS_GMM_IsDetachNotAcceptNeedAttach
 ��������  : ��detachû�����ʱ���յ�Attach����ʱ�Ƿ���Ҫ����attach
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:detachû�����ʱ����Ҫattach��
             VOS_FALSE:����Ҫ����attach��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��5��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��6��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE��Ŀ�޸�
*******************************************************************************/
VOS_UINT32 NAS_GMM_IsDetachNotAcceptNeedAttach(VOS_VOID)
{
    if (GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            NAS_GMM_SndMmGprsDetachComplete();

            NAS_GMM_SndMmcDetachCnf();
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType &=~GMM_WAIT_PS_DETACH;


        /* GMMֹͣPS���DETACH������ʱ�� */
        Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_IsAttachDetachConflicted
 ��������  : ���ATTACH��֮ǰ��DETACH�Ƿ��ͻ
 �������  : VOS_UINT32 ulAttachType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��5��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��5��
   ��    ��   : t00212959
   �޸�����   :DTS2013030407991
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAttachDetachConflicted(VOS_UINT32 ulAttachType)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* ֮ǰ������DETACH���� */
    if ( GMM_WAIT_NULL_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        return VOS_FALSE;
    }

    /* A+Iģʽ */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* ����ģʽI��,��DETACH����,ֱ�ӻظ�CNF */
        if ( MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType
                                        & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
            {
                return VOS_FALSE;
            }

            NAS_GMM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }

    /* ��A+Iģʽ */
    if ( ( ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType )
        && (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_PS_DETACH ) ) )
      || ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
    {
        if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
        {
            return VOS_FALSE;
        }

        NAS_GMM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* IMSI ATTACH��֮ǰ���г�ͻ */
    if ( (MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType )
        && (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_CS_DETACH ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckSigConnStatusAffectAttach
 ��������  : ������������Ƿ�Ӱ��ATTACH
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��29��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
 2. ��    ��   : 2013��6��18��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2013061406222,����RAUʱӦ���ж� CS��ҵ��״̬

*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckSigConnStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    /* ����Ƿ���ר�����̴��� */
    if((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
    && ( MMC_MM_ATTACH_TYPE_GPRS == pstAttachReq->enAttachType )
    && (GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg))
    {
        return VOS_TRUE;
    }

    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckAttachStatus
 ��������  : ���ATTACH״̬
 �������  : MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��13��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��6��
   ��    ��   : t00212959
   �޸�����   : DTS2013030407991
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckAttachStatus(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_TRUE;

    if ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
    {                                                                           /* Ҫ��ATTACH PS��                          */
        NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_TRUE;

        /* GMM����ע��״̬��ֱ�ӻظ�PS CNF */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta )
         && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
        {                                                                       /* PS���Ѿ�ATTACH                           */
            NAS_GMM_SndMmcAttachCnf();

            if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_IMSI;
                ulRet                      = VOS_FALSE;
            }
        }
        else
        {                                                                       /* PS��û��ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_PS_ATTACH;
            g_GmmGlobalCtrl.stAttachInfo.ulOpid        = pstAttachReq->ulOpid;
            ulRet = VOS_FALSE;
        }
    }

    if ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
    {                                                                           /* Ҫ��ATTACH CS��                          */
        /* CS ����ATTACHED״̬���޸�GPRS_IMSI����ΪGPRS ATTACH */
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {                                                                       /* CS���Ѿ�ATTACH                           */
            ulRet = VOS_TRUE;

            /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
            if ( NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType  = MMC_GMM_ATTACH_TYPE_GPRS;
                ulRet                       = VOS_FALSE;
            }
			/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

        }
        else
        {                                                                       /* CS��û��ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_CS_ATTACH;
            ulRet                                      = VOS_FALSE;
        }
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcAttachReq_PreProc
 ��������  : GMM�յ�ATTACH��Ԥ����
 �������  : MMCMM_ATTACH_REQ_STRU *pstmsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��16��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2011111402583,opidֵ���󣬵���AT����

*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcAttachReq_PreProc(
    MMCGMM_ATTACH_REQ_STRU             *pstmsg
)
{
    /* �ж��Ƿ���Ҫ�������Ϣ����Ч��Ϣ���������� */
    if ((MMC_MM_ATTACH_TYPE_IMSI      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pstmsg->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return VOS_TRUE;
    }


    if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = pstmsg->ulOpid;
    }


    /* ����Ƿ���ҵ����� */
    if (VOS_TRUE == NAS_GMM_CheckSigConnStatusAffectAttach(pstmsg))
    {
        if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
        {
            NAS_GMM_SndMmcAttachCnf();
        }

        return VOS_TRUE;
    }

    /* ���ATTACH�����Ƿ��SIM��״̬��ͻ */
    if ( VOS_TRUE == NAS_GMM_CheckSimStatusAffectAttach(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* ��������ģʽ����ATTACH���� */
    if ( VOS_TRUE == NAS_GMM_ModifyAttachType(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* ����Ƿ��֮ǰ����DETACH�г�ͻ */
    if ( VOS_TRUE == NAS_GMM_IsAttachDetachConflicted(pstmsg->enAttachType) )
    {
        return VOS_TRUE;
    }

    /* ���֮ǰ����ATTACH */
    if ( VOS_TRUE == NAS_GMM_IsAttachRepeated(pstmsg->enAttachType, pstmsg->ulOpid) )
    {
        return VOS_TRUE;
    }

    /* ���ע����� */
    if ( VOS_TRUE == NAS_GMM_CheckAttachStatus(pstmsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckNeedBuffDetach
 ��������  : ����Ƿ���Ҫ����DETACH
 �������  : MMCMM_DETACH_REQ_STRU *pstmsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��13��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��16��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2011111402583,opidֵ���󣬵���AT����

  3.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:�Ѿ���DETACH���̽���ʱ������ģʽI�»���DETACH��Ϣ��
                 ���ӶԻ���ȥע����Ϣ�Ķ�ʱ��������
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckNeedBuffDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    MMCGMM_DETACH_REQ_STRU             *pstDetach;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        /* �Ѿ���DETACH���̽���ʱ������ģʽI�»���DETACH��Ϣ */
        if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
          && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode) )
        {
            pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
            if ( VOS_NULL_PTR == pstDetach )
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_CheckNeedBuffDetach:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                  return VOS_TRUE;
            }

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* ��ԭ�ﻺ���־                           */
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

            Gmm_MemCpy(pstDetach, pstmsg, sizeof(MMCGMM_DETACH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstDetach;       /* ����ԭ��                                 */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcPsDetach
 ��������  : GMM����pS DETACH
 �������  : VOS_UINT32 ulOpID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��15��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��16��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:DTS2011111402583,opidֵ���󣬵���AT����

  3.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��ǰPDP����ʱ�������SYSCFG���õ�PSȥע�ᣬҲ����
                 PSȥע�ᡣ
  4.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��������޸ģ���Ԥ�����յ�DETACHʱ�򣬾�����DETACH��
                 ������ʱ�����ڻظ�MMC��detach CNFʱ��ֹͣ������ʱ����
                 �޸ĺ�����Ρ�
  5.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/

VOS_UINT32 NAS_GMM_ProcPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_FALSE;


    g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());



    g_GmmGlobalCtrl.stAttachInfo.enAttachType &=~GMM_WAIT_PS_ATTACH;
    g_GmmGlobalCtrl.stDetachInfo.enDetachType |= GMM_WAIT_PS_DETACH;

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsDetach
 ��������  : GMM����CS DETACH
 �������  : VOS_UINT32 ulOpID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��15��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��23��
    ��    ��   : w00166186
    �޸�����   : ���ⵥ��:DTS2012041805421,L�¿�������GU������ģʽI IMSI DETACH���ɹ�

  3.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:����ģʽI��CS��ǰ��ҵ�����Ӵ��ڣ�������syscfg����
                 �����detach cs������
                 ����ע���ʱ�򣬴���CS���DETACH
                 �����ж�GMM����CS���DETACH��Ϣ
*****************************************************************************/
VOS_UINT32 NAS_GMM_ProcCsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    /* ������ģʽI�£�������ֱ�ӷ��� */

    if (VOS_FALSE == NAS_GMM_IsNeedProcUserCsDetach())
    {
        return VOS_TRUE;
    }
    else
    {
        /* CS����ATTACHED״̬������־λ, ����ֱ�ӻظ�DETACH CNF*/
        if ( (MM_STATUS_ATTACHED                  == g_MmSubLyrShare.MmShare.ucCsAttachState)
          || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_INITIATED            == g_GmmGlobalCtrl.ucState) )
        {
            if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
            {
                /*  ����ģʽI�£�CS��ǰ��ҵ�����Ӵ��ڣ�syscfg���������detach cs��������ֱ�ӷ��� */
                if (VOS_TRUE == g_GmmDetachCtrl.ucSysCfgDetachFlg)
                {
                    return VOS_TRUE;
                }
            }

            g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
            g_GmmGlobalCtrl.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsPsDetach
 ��������  : GMM����CS+PS���͵�DETACH
 �������  : VOS_UINT32 ulOpID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���


  2.��    ��   : 2013��6��11��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��������޸ģ���Ԥ�����յ�DETACHʱ�򣬾�����DETACH��
                 ������ʱ�����ڻظ�MMC��detach CNFʱ��ֹͣ������ʱ����
                 �޸ĺ�����Ρ�
  3.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/

VOS_UINT32 NAS_GMM_ProcCsPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    /* ������ģʽI��,ֻ����PS�ı�־λ */
    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~GMM_WAIT_PS_ATTACH;
        g_GmmGlobalCtrl.stDetachInfo.enDetachType |=  GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid        = pstmsg->ulOpid;
    }
    else
    {
        /* ���ATTACH�ȴ���־ */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

        /* CS����ATTACHED״̬������־λ */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_CS_DETACH;
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid           = pstmsg->ulOpid;
    }

    g_GmmGlobalCtrl.ucUserPsAttachFlag = VOS_FALSE;

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcDetachReq_PreProc
 ��������  : GMM�յ�MMC DETACH��Ԥ����
 �������  : MMCMM_ATTACH_REQ_STRU *pstmsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��13��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��6��11��
   ��    ��   : w00167002
   �޸�����   : V9R1_SVLTE:��������޸ģ���Ԥ�����յ�DETACHʱ�򣬾�����DETACH��
                 ������ʱ�����ڻظ�MMC��detach CNFʱ��ֹͣ������ʱ����
                 �޸ĺ�����Ρ�
 3.��    ��   : 2015��4��15��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcDetachReq_PreProc(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    /* ����Detach���̱�����ʱ�� */
    NAS_GMM_StartDetachProtectingTimer(pstmsg);

    /* �ж��Ƿ���Ҫ����DETACH */
    if ( VOS_TRUE == NAS_GMM_CheckNeedBuffDetach(pstmsg) )
    {
        return VOS_TRUE;
    }


    if ( (MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH == pstmsg->enDetachReason)
      || (MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE  == pstmsg->enDetachReason) )
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_TRUE;
    }
    else
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;
    }

    /*  ����DETACH���ͷֱ��� */
    switch ( pstmsg->enDetachType )
    {
        case MMC_GMM_PS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;

        case MMC_GMM_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        case MMC_GMM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        default:
            GMM_LOG_WARN("NAS_GMM_RcvMmcDetachReq_PreProc:DETACH TYPE INVALID!");
            return VOS_TRUE;
     }


    return VOS_FALSE;
}

/*******************************************************************************
  Module   : Gmm_ComReset
  Function : GMM Reset�Ĺ�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��  : 2012��08��24��
      ��    ��  : m00217266
      �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
*******************************************************************************/
VOS_VOID Gmm_ComReset(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* ͣ����Timer                              */
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ��Ҫ��SM����Ӧ                           */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GMM_RESET);/* ֪ͨSM GMMע��ʧ��                       */

        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS�ڵȴ���Ӧ                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {                                                                           /* GMM��ǰ״̬ΪATTACHED                    */
        GMM_CasFsmStateChangeTo(GMM_NULL);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_ComReset:NORMAL: STATUS IS GMM_NULL");

        Gmm_SndSmStatusInd();                                                   /* ����ԭ��GMMSM_STATUS_IND                 */
    }
    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��Ҫ��RABM����Ӧ                         */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(failure)     */
    }
    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��PS������                               */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                                    /* �ͷ�����                                 */
    }
    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */
    Gmm_ComVariantInit();                                                       /* GMM��ʼ��                                */

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_DealWithBuffInProc
  Function : �յ�RRMM_EST_CNF���buffer�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : GMM_FALSE    û�л���
             GMM_TRUE     �л���
  History  :
    1. ��־��  2003.12.08  �¹�����
  2.��    ��   : 2012��5��21��
   ��    ��   : l65478
   �޸�����   : DTS2012052101009:��RAU�����з���DETACH,GMMû�д���
*******************************************************************************/
VOS_UINT8 Gmm_DealWithBuffInProc(VOS_VOID)
{
    VOS_VOID               *pAddr;                                              /* ����ָ��                                 */
    VOS_UINT8               ucRet;                                              /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ����ֵ��ʼ��ΪFALSE                      */

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* ��ȡpower offԭ���ַ                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        NAS_GMM_FreeBufferCmMsg();
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }
    else
    {
    }
    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_DealWithBuffAfterProc
  Function : ���̽������buffer�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��³��  2007.11.16  A32D12187 ���ӶԻ���Ĵ������緢�͵�SM��Ϣ�Ĵ���
    3.��    ��   : 2007��12��18��
      ��    ��   : l00107747
      �޸�����   : �������ⵥ�ţ�GMM����SM����͵�ǰ���ܴ�����Ҫ������Ҫ������
                   ���������ڴ�����
    4.��    ��   : 2011��12��23��
      ��    ��   : s46746
      �޸�����   : DTS2011122007386:PDP��ȥ�����,PS�����־δ���
*******************************************************************************/
VOS_VOID Gmm_DealWithBuffAfterProc(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMSM_DATA_REQ_STRU                 *ptr;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ��������־                             */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*����ַ���Ϣ*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*�ͷű����RAMB��Ϣ*/
        Gmm_MemFree(pMsg);

        /*�ַ������Service��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*�ͷ���������ڴ�*/
        Gmm_MemFree(pRabmReEst);
    }

    if (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* ��������־                             */
        Gmm_MsgDistribute((VOS_VOID *)(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS)); /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;

    }

    /* ����SM��Ϣ��GMM������̬����Ҫ���λ��棬��һ�λ���ȵ�GMM����
    *  ��������̬�Ŵ�����ʱ�ȷ������������Ϣ��Ҫ�ڶ��λ���
    *  �ȵ���ȫģʽ��ɺ��ٴ����������λ���ʹ��ͬһ������¼��Ϣ��ַ��
    *  ���ÿ�δ���ʱ������������ռ䣬��ʱ�ͷ�ԭ����ռ䡣
    */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        /*�������SM��Ϣ�ı�־*/
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

        if (VOS_NULL_PTR == pMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: GMM MSG HOLD FOR SM PTR IS NULL.");
            return;
        }
        /*���뻺����Ϣ���ڴ�*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
                   + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
        }
        if (VOS_NULL_PTR == ptr)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        /*����Ϣ�ݴ浽������ڴ���*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
                + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_DealWithBuffAfterProc(): Process cached SM Data Req");
        /*�ͷű����SM��Ϣ*/
        Gmm_MemFree(pMsg);
        /*�ַ������SM��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(ptr));
        /*�ͷ���������ڴ�*/
        Gmm_MemFree(ptr);
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_HoldBufferFree
  Function : ������buffer�����е���Ϣ�ͷŵĴ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.01.04  �¹�����
    2.��    ��   : 2007��12��18��
      ��    ��   : l00107747
      �޸�����   : �������ⵥ��:AA32D13917,GMM����SM����͵�ǰ���ܴ�����Ҫ������Ҫ������
                   ���������ڴ�����
    3.��    ��   : 2009��03��21��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:AT2D09534,��ϵͳ�л���Ľ���ʧ�ܹ����йػ���Gmm/MM�Թػ���Ϣû�д�����������AT^CPAM��ʱ������Ӧ
    4.��    ��   : 2011��12��23��
      ��    ��   : s46746
      �޸�����   : DTS2011122007386:PDP��ȥ�����,PS�����־δ���
*******************************************************************************/
VOS_VOID Gmm_HoldBufferFree(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ��������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* ����б�����SmDataReqԭ��                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_HoldBufferFree(): Clear cached SM Data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* ��ȡSmDataReqԭ���ַ                    */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmCmServiceRejectInd
 ��������  : �յ�ԭ��MMGMM_CM_SERVICE_REJECT_IND�Ĵ���
 �������  : pstmsg:MMGMM_CM_SERVICE_REJECT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCmServiceRejectInd(
    VOS_VOID                           *pstMsg
)
{
    MMGMM_CM_SERVICE_REJECT_IND_STRU   *pstMmServRejInd;                      /* ����ָ��                                 */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceRejectInd:WARNING: It is not A+I(Gmm_RcvMmcCmServiceRejectInd)");
        return;
    }

    pstMmServRejInd = (MMGMM_CM_SERVICE_REJECT_IND_STRU *)pstMsg;                 /* ��ʼ��ָ��                               */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == pstMmServRejInd->enCause)
    {                                                                           /* ԭ��ֵΪ#4                               */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_TRUE;                               /* ����MmcCmServiceRejectInd#4����RAU�ı�־ */
    }

    return;
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd_InProc
  Function : RAU/SR�������յ�ԭ��MMGMM_CS_CONNECT_IND�Ĵ���
  Input    : VOS_VOID       *pMsg        ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2012��12��5��
      ��    ��   : t00212959
      �޸�����   : DTS2012120504420:CSFB��rau��#10�ܾ���ATTACH�ɹ���CS����������RAU
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_InProc(
    VOS_VOID                           *pstMsg                               /* ԭ��ָ��                                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstTmpMsg;

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ����ΪRAU                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ����ΪATTACH                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
        return;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* �����������ڽ�����������                 */
        pstTmpMsg = (MMGMM_CS_CONNECT_IND_STRU *)Gmm_MemMalloc(sizeof(MMGMM_CS_CONNECT_IND_STRU));
        if (VOS_NULL_PTR == pstTmpMsg)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcCmServiceInd_InProc:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(pstTmpMsg, pstMsg, sizeof(MMGMM_CS_CONNECT_IND_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)pstTmpMsg;              /* ������ԭ��                               */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* �ñ�����־                               */
    }
    else
    {                                                                           /* �������û�������һ�û������             */
        if (GMM_TIMER_T3317_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3317_FLG))
        {                                                                       /* ���T3317������                          */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* ͣT3317                                  */
        }
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                               /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ִ��RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd_RegNmlServ
  Function : ��GMM_REGISTERED_NORMAL_SERVICE״̬���յ�
             ԭ��MMGMM_CM_SERVICE_IND�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2008��08��1��
      ��    ��   : luojian id:00107747
      �޸�����   : �������ⵥAT2D04486/AT2D04822
    3.��    ��   : 2012��4��17��
      ��    ��   : z00161729
      �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
    4.��    ��   : 2012��9��17��
      ��    ��   : l65478
      �޸�����  : DTS2012091204262��������������RAU
    5.��    ��   : 2012��10��30��
      ��    ��   : s00217060
      �޸�����  : DTS2012050301830������ RRC���Ӵ���ʱ,����������RAU;������յ�ϵͳ��Ϣ����������RAU
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_RegNmlServ(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState )
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }

    /* CSҵ�������GS���������ڣ�RRC���ڣ�������������RAU��������ϱ�ϵͳ��Ϣ���ٷ�������rau*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRatType)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvMmCsConnectInd_RrcConnExist();
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* ���CS����RAU�ı�־                      */
    }
    else
    {
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRcvRrmmEstCnfMsgValid
 ��������  : ��Gmm_RcvRrmmEstCnf����Ȧ���Ӷȣ��жϽ��յ���rrmm est cnf��Ϣ�Ƿ�Ϸ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: �Ϸ�
             VOS_FALSE: ���Ϸ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��13��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRcvRrmmEstCnfMsgValid(
    RRMM_EST_CNF_STRU                  *pRrmmEstCnf
)
{
    if (RRC_NAS_PS_DOMAIN != pRrmmEstCnf->ulCnDomainId)
    {                                                                           /* �ж���PS����Ϣ,��                        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: It is not PS domain(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }
    if (GMM_RRC_RRMM_EST_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ж��Ƿ����ڵȸ���Ӧ,��                  */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected");
        return VOS_FALSE;
    }
    if (g_GmmReqCnfMng.ucRrmmEstOpid != pRrmmEstCnf->ulOpId)
    {                                                                           /* OP ID�����                              */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected(OPID is not same)");
        return VOS_FALSE;
    }

    if (RRC_EST_ESTING == pRrmmEstCnf->ulResult)
    {                                                                           /* ���Ϊ���ڽ�                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: The result is invalid(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf
  Function : �յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��2��17��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01287����ӡ����

    3.��    ��   : 2011��7��14��
      ��    ��   : zhoujun 40661
      �޸�����   : ����PS�����Ӵ��ڱ�־λ

    4.��    ��   : 2011��04��20��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�DTS2011040804149����V3R1C31B027����RAU��PS ONLY�£�PMM_IDLE̬W2G��ѡ�󣬷���pingδ����RAU���̣��޷���������
    5.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
    6.��    ��   : 2012��03��12��
      ��    ��   : z00161729
      �޸�����   : ֧��ISR�޸�
    7.��    ��   : 2012��7��14��
      ��    ��   : l65478
      �޸�����   : DTS2012071303294�����ӽ���ʧ��ʱû��������ӱ�־
    8.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
    9.��    ��   : 2013��4��10��
      ��    ��   : y00176023
      �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�RRC_EST_RJ_NO_RF�Ĵ���
    10.��    ��   : 2014��9��18��
       ��    ��   : z00161729
       �޸�����   : DTS2014091705885:l csfb��w����ģʽI��С����λ�����ı�lau��rau�������ʧ�ܣ�ҵ��ʧ�ܣ�T3311ʧ�ܷ�������rau�ɹ����ֶ෢��һ������rau

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf(
                       VOS_VOID *pMsg                                           /* ԭ��ָ��                                 */
                       )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* ����ָ��                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    if (VOS_FALSE == NAS_GMM_IsRcvRrmmEstCnfMsgValid(pRrEstCnf))
    {
        return;
    }

    if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
    {                                                                           /* ���Ϊ�Ѿ�����                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result of RRMM_EST_CNF is unexpected");
    }

    switch(pRrEstCnf->ulResult)
    {
    case RRC_EST_RJ_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_EST_OTHER_ACCESS_BARRED:
        g_GmmGlobalCtrl.ucRelCause =
                    RR_REL_CAUSE_ACCESS_BARRED_CAUSE_ACCESS_CLASS_CONTROL;
        break;
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_NO_RF:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        break;

    case RRC_EST_RJ_SNW:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RRC_SNW;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result item of RRMM_EST_CNF Msg is SUCCESS");
        break;

    }

    g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                      /* ��ȴ���Ӧ��־                           */

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* ������ɹ�                             */
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* �������־λ                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: PS signatual exist");
        if (GMM_TIMER_T3312_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {                                                                       /* ���T3312������                          */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);         /* ֪ͨMMC PS���������Ӵ���                 */

#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        /* 24.008, 4.4.4.9, case f1, CR1099 update:
           W�¸���GMM��·���ƽṹ��������RRC��·״̬ */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            /* ���յ�RRMM_RESUME_INDʱ,û��ֹͣT3314,��Ϊ�˱���CCOʧ�ܻ���
               �������յ����ӽ����ɹ�ʱ��Ҫֹͣ�˶�ʱ�� */
            Gmm_TimerStop(GMM_TIMER_T3314);

            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

            NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

            gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

        }

    }
    else
    {
        /* ��·����ʧ�ܣ����GMM��·���Ʊ��� */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_GMM_ClearGmmLinkCtrlStru();
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
    }


    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_RegInit(pRrEstCnf);                                   /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_DeregInit(pRrEstCnf);                                 /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmEstCnf_RauInit(pRrEstCnf);                                   /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmEstCnf_ServReqInit(pRrEstCnf);                               /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmEstCnf_DeregNmlServ(pRrEstCnf);                              /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmEstCnf_RegImsiDtchInit(pRrEstCnf);                           /* ���ø�״̬�µĴ���                       */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmEstCnf:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RegInit
  Function : ��GMM-REGISTERED-INITIATED״̬���յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2008��7��2��
    ��    ��   : l00107747
    �޸�����   : �������ⵥ�ţ�AT2D03900
  3.��    ��   : 2010��01��04��
    ��    ��   : w00166186
    �޸�����   : ���ⵥ��:DTS2010122004132 W CS ONLY PDP��������ض���G,PDP����ʧ��
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  6.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  7.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RegInit(
                               VOS_VOID *pMsg                                   /* ԭ��ָ��                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* ����ָ��                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ����Ϣ����                               */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3310);                                        /* ��T3310                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);                          /* ����״̬�Ĺ�������                       */
        enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_ATTACH_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��ǰ����Ϊcombined attach                */
            NAS_GMM_SndMmCombinedAttachRejected(enCause);       /* ����MMCGMM_COMBINED_ATTACH_REJECTED      */
        }
        else
        {                                                                       /* ��ǰ����Ϊnormal attach                  */
            NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                            enCause);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND         */
        }


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        &enCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN
                        );

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);      /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_AttachAttemptCounter(enCause);                                      /* ����attach attempt counter�Ĵ���         */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* ������ڽ��е�specific���̱�־           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_DeregInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�ԭ��RRMM_EST_CNF�Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. ��    ��   : 2008��9��18��
     ��    ��   : ouyangfei 00132663
     �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM�������Ӧ�ñ����棬��GMM���̽����ٷ���
  3.��    ��   : 2010��12��03��
    ��    ��   : w00166186
    �޸�����   : DTS2010112403161 ��������������
  4.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.

  7.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_DeregInit(
                                 VOS_VOID *pMsg                                 /* ԭ��ָ��                                 */
                                 )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_DeregInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );         /* ����PS���ֹע���־                     */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                      GMM_MMC_ACTION_RESULT_FAILURE,
                                      NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_DeregInit:INFO: specific procedure ended");
    }
    return;
}

  /*******************************************************************************

  Module   : Gmm_RcvRrmmEstCnfAccessBar_RauInit
  Function : ��RauInit״̬�½���ʧ��ԭ��ΪAccess Barred�Ĵ������˴����װΪ������
             Ϊ�˽���ԭ�����ĸ��Ӷ�
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/

VOS_VOID Gmm_RcvRrmmEstCnfAccessBar_RauInit( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);                            /* ����״̬�Ĺ�������                       */
    Gmm_ComCnfHandle();
    enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* �����ǰ������combined RAU               */
        NAS_GMM_SndMmCombinedRauRejected(enCause);          /* ����MMCGMM_COMBINED_ATTACH_REJECTED      */
    }
    else
    {                                                                       /* �����ǰ������normal RAU                 */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND         */
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnfAccessBar_RauInit:INFO: specific procedure ended");

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RauInit
  Function : ��GMM-ROUTING-AREA-UPDATING-INITIATED״̬��
             �յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
  3.��    ��   : 2010��11��22��
    ��    ��   : h44270
    �޸�����   : �������ⵥ�ţ�DTS2010111700109��С����bar������£�״̬����ȷ������MM״̬���ԣ�û�з���LAU
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����

  6.��    ��   : 2013��6��5��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��Э���п��������ǰ��RAU�����У��յ�IMSI detach�����ȴ���RAU;
                 �����Detach�����У��������µ�·���������ȴ���RAU.����Э���������ж�UE�Ķ���
                 Ϊ:��RAU�����У�����յ�DETACH���򻺴�Detach����RAU�����󣬴������Detach��
  7.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RauInit(
                               VOS_VOID *pMsg                                   /* ԭ��ָ��                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* ����ָ��                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;
    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_RauFailureInterSys();
        }
    }
    else
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }
    }


    /* ��RAU�����У�������Detach */
    if (0 != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & ~GMM_MSG_HOLD_FOR_DETACH) )
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RauInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3330);                                        /* ��T3330                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        /* Ϊ���ͺ������Ӷȣ�������Access bar�Ĵ����װΪ���µĺ��� */
        Gmm_RcvRrmmEstCnfAccessBar_RauInit();
    }
    else
    {
        /* TS24.008
        4.7.5.1.5 Abnormal cases in the MS
        g) Routing area updating and detach procedure collision
        GPRS detach containing detach type"re-attach required" or "re-attach not required":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be aborted and the GPRS detach procedure shall be
        progressed. If the DETACH REQUEST message contains detach type "re-attach not required" and GMM
        cause #2 "IMSI unknown in HLR", the MS will follow the procedure as described below for the detach type
        "IMSI detach".
        GPRS detach containing detach type "IMSI detach":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be progressed, i.e. the DETACH REQUEST message
        shall be ignored.


            4.7.4.1.4 Abnormal cases in the MS

            f) Change of cell into a new routing area
        If a cell change into a new routing area occurs before a DETACH ACCEPT message has been received, the
        GPRS detach procedure shall be aborted and re-initiated after successfully performing a routing area updating
        procedure. If the detach procedure is performed due to the removal of the SIM/USIM the MS shall abort the
        detach procedure and enter the state GMM-DEREGISTERED. */

        /* �������ӽ���ʧ��                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_RoutingAreaUpdateAttemptCounter(enCause);                           /* ����RAU attempt counter�Ĵ���            */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);


        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬���յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
  3.��    ��   : 2009��3��11��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D09927�����PS�򲻿��ã��ظ�SM SERVICE REJ����ֹ��ǰ���󣬱���SM����ʱ����
                 �ظ���������
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӳ��ű��ܶ���
  6.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�GMM_SndSmServiceRej�ӿڣ����ԭ��ֵ


  7.��    ��   : 2015��1��14��
    ��    ��   : w00167002
    �޸�����   : DTS2015010509687:DSDS�Ż�,��ҵ����ʧ��NO RF����ҪSM���´���PDP
                 �������֪ͨWAS��������Դ��ռ��
                 ��NORMAL SERVICEʱ���յ�NO RF relʱ��ͨ��REL IND֪ͨSM��ǰ��Ҫ���´���PDP
                 �������֪ͨWAS��������Դ��ռ��
  8.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_ServReqInit(
                                   VOS_VOID *pMsg                               /* ԭ��ָ��                                 */
                                   )
{
    VOS_UINT32           ulCause;                                               /* ����ֲ�����                             */
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_ServReqInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3317);                                        /* ��T3317                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        if (RRC_EST_OTHER_ACCESS_BARRED == pRrEstCnf->ulResult)
        {                                                                       /* ��������                                 */
            ulCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

            /* ��ǰ��SM����� Service Request����, ��SM �ظ� Service Rej ��Ϣ�����ͷ��ϲ�Ӧ�á� */
            if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
                && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
            {
                GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

                g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
            }
        }
        else
        {
            ulCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
        }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmEstCnf_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

        /* �˴����ϱ�����״̬����Ϊ���������Ѿ������޷���ĵƣ�����ϱ�����ĵ�״̬ */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
        Gmm_ComCnfHandle();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        {                                                                       /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* ���ڱ������T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* �ָ�T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* ���ڱ������T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* �ָ�T3302                                */
            }
            else
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);                                /* ��T3312                                  */
            }
        }
        else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* ���ڱ������T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* �ָ�T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* ���ڱ������T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* �ָ�T3302                                */
            }
            else
            {
            }
        }
        else
        {
        }

        if ((VOS_TRUE == NAS_MML_GetDailRejectCfg())
         && (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == ulCause))
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_RRC_EST_FAIL);
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }


        /* �����ǰ��NO RF�Ľ���ʧ�ܣ���֪ͨSM��Ҫ���·���PDP���� */
        else if ( (GMM_FALSE         == GMM_IsCasGsmMode())
          && (RRC_EST_RJ_NO_RF  == pRrEstCnf->ulResult) )
        {
            Gmm_SndSmRelInd();
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }
        else
        {

        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulCause);                             /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulCause);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ulCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_ServReqInit:INFO: specific procedure ended");
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_DeregNmlServ
  Function : ��GMM-DEREGISTERED.NORMAL-SERVICE״̬���յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2. x51137 2007/4/2 A32D09789
    3.��    ��   : 2009��5��9��
      ��    ��   : l00130025
      �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_DeregNmlServ(
                                    VOS_VOID *pMsg                              /* ԭ��ָ��                                 */
                                    )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* ����ָ��                                 */
    NAS_MSG_STRU           *pNasMsg;                                            /* ����ָ��                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����Ϊpower off����                  */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* ����RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* �������ӽ���ʧ��                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSIM���γ���detach����          */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* ����RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* �������ӽ���ʧ��                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RegImsiDtchInit
  Function : ��GMM-REGISTERED.IMSI-DETACH-INITIATED״̬��
             �յ�ԭ��RRMM_EST_CNF �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. ��    ��   : 2008��9��18��
     ��    ��   : ouyangfei 00132663
     �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
  3. ��    ��   : 2011��07��13��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RegImsiDtchInit(
                                       VOS_VOID *pMsg                               /* ԭ��ָ��                                 */
                                       )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
     || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬�Ĺ�������                       */
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
        }
        g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;          /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:INFO: specific procedure ended");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd
  Function : �յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : VOS_VOID     *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2. ��    ��   : 2007��12��08��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13826
    3. ��    ��   : 2008��9��18��
       ��    ��   : ouyangfei 00132663
       �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
    4. ��    ��   : 2009��03��31��
       ��    ��   : L65478
       �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����

    5.��    ��   : 2011��7��14��
      ��    ��   : zhoujun 40661
      �޸�����   : ����MML_CTX�е����Ӵ���״̬
    6.��    ��   : 2011��12��15��
      ��    ��   : W00166186
      �޸�����   : DTS20111205018756,�����ϴ�ʱ������û�о��������Ա�����3312��ʱ��ʱ����Ч
                   ������Э��淶
    7.��    ��   : 2012��3��07��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
    8.��    ��   : 2012��6��13��
      ��    ��   : l00130025
      �޸�����   : DTS2012061302495:RB�ؽ�������С����ѡ,RAI�仯ʱ,��·�ͷź�û��֪ͨRABM�ͷš������޷�����
    9.��    ��   : 2012��08��18��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�DTS2012081506413:NMOI��PS detach��,MM������ע��
   10.��    ��   : 2011��12��28��
      ��    ��  : l00167671
      �޸�����  : �޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
				 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
				 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
				 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
   11. ��    ��   : 2013��8��2��
       ��    ��  : z00234330
       �޸�����  :stk��Ŀ�޸�
   12.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
   13.��    ��  :2014��07��09��
      ��    ��  :s00217060
      �޸�����  :DTS2014070205755:�Ƚ����est_cnfʱ�յ�rel_ind,�ӳ�15s�ٷ�attach
   14.��    ��  :2014��07��28��
      ��    ��  :b00269685
      �޸�����  :DTS2014072802678:�Ƚ����est_cnfʱ�յ�rel_ind,ֹͣ������ʱ��
   15.��    ��   : 2015��1��15��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
   16.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd(
                       VOS_VOID *pMsg                                           /* ԭ��ָ��                                 */
                       )
{
    VOS_VOID                *pAddr;
    RRMM_REL_IND_STRU       *pRrRelInd;                                         /* ����ָ��                                 */

    pRrRelInd = (RRMM_REL_IND_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    /* �������PS��ģ�GMM���������� */
    /* ����������¼���״̬�ȴ�est_cnf������rel causeΪRRC_REL_CAUSE_NAS_DATA_ABSENT������������:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */
    if (VOS_FALSE == NAS_GMM_IsNeedProcRelInd(pRrRelInd))
    {
        return;
    }



    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* �����Ȩ���ȫ�ֱ��� */
    NAS_GMM_ClearAuthInfo();

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3319);                                             /* ֹͣT3319                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* ֹͣT3340                                */
        
    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       


    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ���Ӧ��־                           */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    /* ��������йػ��¼����յ�REL_INDʱ��Ҫ���� */
    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO:DEAL HOLD_POWEROFF_MSG");
        Gmm_TimerStop( GMM_TIMER_PROTECT_FOR_SIGNALING );
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* ��ȡpower offԭ���ַ                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        Gmm_MsgDistribute( pAddr );                                             /* ��������Ϣ�ַ�                           */
        Gmm_MemFree( pAddr );
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        return;
    }

    switch(pRrRelInd->ulRelCause)
    {
    case RRC_REL_CAUSE_RR_NORM_EVENT:
    case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
    case RRC_REL_CAUSE_T315_EXPIRED:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
        break;
    case RRC_REL_CAUSE_RR_UNSPEC:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_REL_CAUSE_RR_PRE_EMPT_REL:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_PRE_EMPTIVE_RELEASE;
        break;
    case RRC_REL_CAUSE_RR_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_REL_CAUSE_RR_RE_EST_REJ:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RE_ESTABLISH_REJ;
        break;
    case RRC_REL_CAUSE_RR_USER_INACT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_USER_INACTIVITY;
        break;
    case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:
        g_GmmGlobalCtrl.ucRelCause =
                 RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT;
        break;
    case RRC_REL_CAUSE_NAS_REL_ABSENT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_UNEXIST_CONNECTION;
        break;
    case RRC_REL_CAUSE_NAS_REL_SUCCESS:
    case RRC_REL_CAUSE_NAS_ABORT:
    case RRC_REL_CAUSE_NAS_STOP_SETUP:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_NORMAL;
        break;
    default:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: The Relase Cause is default");
        break;

    }

    g_GmmGlobalCtrl.ucCipherStartFlg = GMM_FALSE;

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;         /* 2G���������ӱ�־ʼ����Ч */
        }
        else
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;        /* 3G���������ӱ�־��� */
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucTcPreSta)
        {
            g_GmmGlobalCtrl.ucTcPreSta = GMM_REGISTERED_NORMAL_SERVICE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucServPreSta = GMM_NULL;
        }
        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucTcPreSta)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
            Gmm_TimerPauseForTc(GMM_TIMER_T3312);                               /* ����T3312                                */
        }
        return;
    }

    if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
        &&(GMM_MSG_HOLD_FOR_SMS == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)) )
    {   /* ��ǰ�л���� SMS ��Ϣ,�ҵ�ǰ������������,���𻺴��SMS���� */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: Buffered SMS Request will be handled.");
    }
    else
    {
        if (!((GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            && (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)))
        {

            if (GMM_MSG_HOLD_FOR_SMS
                ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
            {
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL_PTR;

                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }

            /* Added by z00234330 for V9R1 STK����, 2013/07/11, begin */

            /* GCF34.4.8.1���Բ�ͨ����������G�·�����ʱ���յ�T3314��ʱ���˴�֪ͨSMS�ͷ� */
            if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType() )
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                      /* ����PMMSMS_ERROR_IND                     */
            }

            /* Added by z00234330 for V9R1 STK����, 2013/07/11, end */
        }
    }

    /* GMM�յ������������ͷ�ָʾ��RABMҲһ�����յ������������ͷ�ָʾ��RABM
       �յ��ͷ�ָʾ�����ֹ��ǰ��RAB�ؽ����̣���ʱGMM��û�б�Ҫ��������RABM��
       �ؽ���Ϣ��;��ʱWRR����û���ؽ�RB,��ҪGMM֪ͨRABM ����ʧ��*/
    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);               /* ������buffer�����е���Ϣ�ͷ�             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL_PTR;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }
    if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        &&(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProcHold))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 2G���������ӱ�־ʼ����Ч */
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;                                /* 3G���������ӱ�־��� */
        /* W�����RRC����״̬ */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        if (RRC_RRC_CONN_STATUS_ABSENT == pRrRelInd->ulRrcConnStatus)
        {
            NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
        }
    }

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");

    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        if (VOS_TRUE == NAS_GMM_ProcSavedWasSysInfo())
        {
            NAS_GMM_FreeWasSysInfo();
            return;
        }
    }
    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_RegInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_DeregInit(pRrRelInd);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmRelInd_RauInit(pRrRelInd);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmRelInd_ServReqInit(pRrRelInd);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvRrmmRelInd_RegNmlServ(pRrRelInd);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmRelInd_RegImsiDtchInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmRelInd_DeregNmlServ();
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvRrmmRelInd_PlmnSearch();
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmRelInd:WARNING: g_GmmGlobalCtrl.ucState is WRong");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        break;
    }

    /* W�£���·�ͷź����GMM��·���Ʊ��� */
    if (VOS_FALSE == GMM_IsCasGsmMode())
    {
        NAS_GMM_ClearGmmLinkCtrlStru();
    }

    /* �������ͷź�����������PS DETACH��Ϣ,����PS detach */
    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* ��������Ϣ�ַ�                           */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ��������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();
    return;
}

/*******************************************************************************
Module   : Gmm_RcvRrmmRelInd_DeregNmlServ
Function : ��GMM-DEREGISTERED-NORMAL-SERVICE״̬���յ�ԭ��RRMM_REL_IND �Ĵ���
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. ��־��  2005.02.22  �¹�����
2.��    ��   : 2009��5��9��
  ��    ��   : l00130025
  �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
3.��    ��   : 2011��07��13��
  ��    ��   : w00166186
  �޸�����   : V7R1 PHASE II ATTACH/DETACH����
4.��    ��   : 2011��7��27��
  ��    ��   : h44270
  �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
5.��    ��   : 2011��11��8��
  ��    ��   : s46746
  �޸�����   : V7R1 PhaseII�׶ν���ػ�������
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_DeregNmlServ(VOS_VOID)
{

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����Ϊpower off����                  */
        Gmm_TimerStop(GMM_TIMER_1S);                                            /* ͣ5s����Timer                            */

        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_GMM_SndMmGprsDetachComplete();
        }

        Gmm_ComStaChg(GMM_NULL);
        Gmm_SndMmcPowerOffCnf();                                                /* ����MMCGMM_POWER_OFF_CNF                 */
        /*Gmm_TimerDistroy();*/                                                     /* ��������Timer                            */
        Gmm_ComVariantInit();                                                   /* ���ȫ�ֱ���                             */
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSIM���γ���detach����          */
        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        Gmm_TimerStop(GMM_TIMER_1S);                                            /* ͣ5s����Timer                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregNmlServ:INFO: specific procedure ended");
    }

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegInit
  Function : ��GMM-REGISTERED-INITIATED״̬���յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2010��01��04��
      ��    ��   : w00166186
      �޸�����   : ���ⵥ��:DTS2010122004132 W CS ONLY PDP��������ض���G,PDP����ʧ��
    3.��    ��   : 2012��12��6��
      ��    ��   : t00212959
      �޸�����   : ���ⵥ��:DTS2012120704835 ���RAU��־Ӧ����Returnǰ
    4.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    /* ����Ƿ���Ҫ���·���Attach ����*/
    ucRst = NAS_GMM_RetryAttachProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Attach���� */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���attach���� */
            g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    g_GmmAttachCtrl.ucRetryFlg = GMM_TRUE;                                      /* ���û�С��������attach��־               */


    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                        /* ����attach attempt counter�Ĵ���         */


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                         /* ������ڽ��е�specific���̱�־           */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegInit:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���fallowon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_DeregInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2.��    ��   : 2006��3��24��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                 �����RR����ԭ�����
  3.��    ��   : 2010��12��03��
    ��    ��   : w00166186
    �޸�����   : DTS2010112403161 ��������������
  4.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

  8.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_DeregInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    if (VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ����Ƿ���Ҫ���·���Detach ���� */
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Detach���� */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���Detach���� */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /*���յ���Detach Accept��Ϣ��֮ǰδע��ɹ�*/
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregInit:INFO: specific procedure ended");

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RauInit
  Function : ��GMM-ROUTING-AREA-UPDATING-INITIATED״̬��
             �յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : RRMM_REL_IND_STRU *pRrRelInd  RRMM_REL_IND_STRU����ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��3��24��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                   �����RR����ԭ�����
    3.��    ��   : 2009��01��15��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
    4.��    ��   : 2012��12��6��
      ��    ��   : t00212959
      �޸�����   : ���ⵥ��:DTS2012120704835 CSFB��һ��LAURAU���ͷŵ���ʧ�ܺ�����CSFB��෢RAU
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RauInit(
                               RRMM_REL_IND_STRU *pRrRelInd                     /* RRMM_REL_IND_STRU����ָ��                */
                               )
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {
        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        return;
    }

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* ����Ƿ���Ҫ���·���RAU ����*/
    ucRst = NAS_GMM_RetryRauProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���RAU���� */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���RAU���� */
            g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /* RAU�������յ�SM���󣬱����棬���RAUʧ�ܣ��жϵ�ǰ�Ƿ���SM�������������SM����REL��Ϣ */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_MSG_HOLD_FOR_SM ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause) ))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RauInit(): RAU fail, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    g_GmmRauCtrl.ucRetryFlg = GMM_TRUE;                                     /* ���û�С����Ҫ����RAU��־                */
    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);         /* ����RAU attempt counter�Ĵ���            */


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬���յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��3��24��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                   �����RR����ԭ�����
    3.��    ��   : 2009��08��13��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�AT2D13662,3G���ϱ���out of coverage�����ǻ�����ϱ�PS_Service
    4.��    ��   : 2010��09��27��
      ��    ��   : z00161729
      �޸�����   : ���ⵥ�ţ�AT2D19560
    5.��    ��   : 2011��09��6��
      ��    ��   : s46746
      �޸�����   : ͬ��V3R1�汾���ⵥDTS2011072005340
    6.��    ��   : 2012��02��16��
      ��    ��   : L65478
      �޸�����   : ���ⵥ��;DTS2012021602026,GCF����ʧ��,PDP�������ܾ������������·�����PDP��������
    7.��    ��   : 2012��3��17��
      ��    ��   : w00176964
      �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӳ��ű��ܶ���
    8.��    ��  : 2012��08��24��
      ��    ��  : m00217266
      �޸�����  : �޸Ľӿ�GMM_SndSmServiceRej�����ԭ��ֵ
    9.��    ��  : 2013��06��5��
      ��    ��  : w00242748
      �޸�����  : svlte��usim�ӿڵ���

    10.��    ��   : 2015��1��14��
       ��    ��   : w00167002
       �޸�����   : DTS2015010509687:DSDS�Ż�,��ҵ����ʧ��NO RF����ҪSM���´���PDP
                 �������֪ͨWAS��������Դ��ռ��
                 ��NORMAL SERVICEʱ���յ�NO RF relʱ��ͨ��REL IND֪ͨSM��ǰ��Ҫ���´���PDP
                 �������֪ͨWAS��������Դ��ռ��

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_ServReqInit(
                                   RRMM_REL_IND_STRU *pRrRelInd
                                   )
{
    VOS_UINT8                           ucRst;
    NAS_MSG_STRU                       *pServiceReqMsg;
    VOS_UINT8                           ucDellRejectEnableFlg;
    VOS_UINT32                          ulIsTestCardFlg;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* ��ȡ���ű��ܶ����Ƿ�ʹ�� */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    Gmm_TimerStop(GMM_TIMER_T3317);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* ����Ƿ���Ҫ���·���SR����*/
    ucRst = NAS_GMM_RetrySrProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���SR���� */
            pServiceReqMsg = Gmm_ServiceRequestMsgMake();

            if (VOS_NULL_PTR != pServiceReqMsg)
            {
                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause,
                                  GMM_RRC_IDNNS_UNKNOWN,
                                  pServiceReqMsg);

                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

                /* ��ʱPS���������Ѿ��ͷ�,��˹���Ӧ����idle̬��������ҵ������ */
                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ��,����g_GmmGlobalCtrl.MsgHold�еĻ��棬
                ���·���SR���� */
            Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */
            g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_TRUE;

        }
        return;
    }

    if (((RRC_REL_CAUSE_RR_NORM_EVENT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_RR_USER_INACT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_T315_EXPIRED        == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_NO_RF               == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        Gmm_SndSmRelInd();
    }

    if (VOS_TRUE == ucDellRejectEnableFlg)
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                         /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID *)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

    Gmm_ComCnfHandle();

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
        }
    }
    else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }
    }
    else
    {
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* Directed signalling connection           *
                                                                                 * re-establishment                         */
    }
    else
    {                                                                           /* ����ԭ��                                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_ServReqInit:INFO: specific procedure ended");
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegNmlServ
  Function : ��GMM-REGISTERED.NORMAL-SERVICE״̬���յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : VOS_VOID    *pRrRelInd       ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��3��24��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                   �����RR����ԭ�����
    3.��    ��   : 2007��11��1��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�A32D13307���ͷ�ԭ��ֵ#5��û���ͷŻ���
    4.��    ��   : 2009��01��15��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
    5.��    ��   : 2011��7��26��
      ��    ��   : l00130025
      �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
    6.��    ��   : 2012��02��16��
      ��    ��   : L65478
      �޸�����   : ���ⵥ��;DTS2012021602026,GCF����ʧ��,PDP�������ܾ������������·�����PDP��������
    7.��    ��   : 2013��6��5��
      ��    ��   : w00242748
      �޸�����   : SVLTE��USIM�ӿڵ���
    8.��    ��   : 2014��7��28��
      ��    ��   : b00269685
      �޸�����   : DTS2014072802678:ע��ɹ�������T3340�ȴ������ͷţ��յ�SM�ļ�������
                   ���л��棬�˺��������յ�WRR�����ͷţ�����Ҫ֪ͨSM�����ͷ�
    9.��    ��   : 2015��1��14��
      ��    ��   : w00167002
      �޸�����   : DTS2015010509687:DSDS�Ż�,��ҵ����ʧ��NO RF����ҪSM���´���PDP
                 �������֪ͨWAS��������Դ��ռ��
                 ��NORMAL SERVICEʱ���յ�NO RF relʱ��ͨ��REL IND֪ͨSM��ǰ��Ҫ���´���PDP
                 �������֪ͨWAS��������Դ��ռ��
    10.��    ��   : 2015��8��13��
       ��    ��   : l00289540
       �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegNmlServ(
                                  RRMM_REL_IND_STRU *pRrRelInd                  /* ��Ϣָ��                                 */
                                  )
{
    VOS_UINT32                          ulIsTestCardFlg;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* ����ע������У��յ�SM�ļ�������ע��ɹ���������ԭ��·�Ͻ��������󷢸�
        ���࣬��·���ͷţ���ʱ��Ҫ֪ͨSM��·�ͷ���Ϣ,�����·��� */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_NO_RF             == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (GMM_MSG_HOLD_FOR_SM
            != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SM)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RegNmlServ(): Connection release, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* ���RRC�ͷ�ԭ��ΪDirected signalling con
                                                                                 * nection re-establishment                 */
        /* ������״̬�£�ֻ�п����л����SR��Ϣ�����Դ˴�ֻ��Ҫ���SR */
        if(GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStart(GMM_TIMER_T3312);

        return;
    }
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);                                            /* ��T3312                                  */

    if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauSuccessInterSys();
    }

    if(GMM_FALSE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        /* ��ǰREL����Ҫ����RAU�����Դ���������� */
        NAS_GMM_HandleDelayedEvent();
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegImsiDtchInit
  Function : ��GMM-REGISTERED.IMSI-DETACH-INITIATED״̬��
             �յ�ԭ��RRMM_REL_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2.��    ��   : 2006��3��24��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                 �����RR����ԭ�����
  3.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegImsiDtchInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;
    VOS_UINT8                           ucRst;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ����Ƿ���Ҫ���·���Detach ����*/
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Detach���� */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���Detach���� */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬�Ĺ�������                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* ���������                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegImsiDtchInit:INFO: specific procedure ended");

}

/*****************************************************************************
 �� �� ��  : Gmm_RcvRrmmRelInd_PlmnSearch
 ��������  : ����״̬���յ������ͷ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_PlmnSearch()
{
    Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
    2.��    ��  : 2012��08��24��
      ��    ��  : m00217266
      �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ��Ҫ�ϱ���SM                             */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_RRC_EST_FAIL);        /* ֪ͨSM GMMע��ʧ��                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_DeregInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. s46746  2009.8.19  �¹�����
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��1��24��
    ��    ��   : w00176964
    �޸�����   : DTS2013012408469:detach�����ж���ֱ�ӽ��б���detach
  4.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
  5.��    ��   : 2013��10��05��
    ��    ��   : l65478
    �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_DeregInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if ( VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    /* detach��Ǵ��ڶ���ʱֱ�ӻظ�detach��� */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcRauHoldProcedure_RcvCoverLost
 ��������  : ·�������¹����г����������Ի���Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2014��5��31��
    ��    ��  : s00246516
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_ProcRauHoldProcedure_RcvCoverLost(VOS_VOID)
{

    /* MMC�ڷ���Coverage lost�����д���Detach��Attach��� */
    switch (g_GmmGlobalCtrl.ucSpecProcHold)
    {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;

        case GMM_DETACH_COMBINED:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                NAS_GMM_SndMmGprsDetachComplete();
            }
            break;

        case GMM_DETACH_WITH_IMSI:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        default:
            break;
    }

    g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                                 /* ���followon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* ������ڽ��е�specific���̱�־           */

    return;
}


/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RauInit
  Function : ��GMM-RAU-INITIATED״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
    2. ��    ��   : 2012��7��17��
       ��    ��   : z00161729
       �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                    ��������rau
    3. ��    ��   : 2013��3��30��
       ��    ��   : l00167671
       �޸�����   : �����ϱ�AT�������������C��
    4. ��    ��   : 2014��05��31��
       ��    ��   : s00246516
       �޸�����   : ·�������¹����г�������������л����Detach��û�лظ�
    5. ��    ��   : 2015��2��6��
       ��    ��   : h00313353
       �޸�����   : USIMM���ӿڵ���
    6.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RauInit()
{
    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    pstLastSuccRai      = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stRai.Lai.PlmnId);
    stRai.Lai.aucLac[0] = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1] = pstLastSuccRai->stLai.aucLac[1];
    stRai.ucRac         = pstLastSuccRai->ucRac;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    g_GmmRauCtrl.ucRauAttmptCnt++;                                              /* RAU Attempt Counter��1                   */

    if (5 > g_GmmRauCtrl.ucRauAttmptCnt)
    {                                                                           /* ucRauAttmptCntС��5                      */
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ((GMM_TRUE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
         && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
        {                                                                       /* RAI����Ҹ���״̬��GU1                   */
        }
        else
        {                                                                       /* RAI����Ȼ��߸���״̬����GU1             */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        Gmm_TimerStart(GMM_TIMER_T3311);
    }
    else
    {                                                                           /* ucRauAttmptCnt���ڵ���5                  */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* �ø���״̬ΪGU2                          */

        /* ��U2״̬�����浱ǰ��RAI��Ϣ */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;                             /* ���̽��������3312�����־               */
        g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x�½���������:
        The MS shall apply this value in the routing area registered by the MS, until a new value is received.
        The default value of this timer is used in the following cases:
        -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
        -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
        -   the MS does not have a stored value for this timer; or
        -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
        ע��ʧ�ܴ�5�Σ����ϴ��·�t3302��ʱ��ʱ��������ͬ��ǰפ�����粻ͬ������뼼����ͬ����t3302ʹ��Ĭ��ֵ��*/
        if (VOS_TRUE == NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax())
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }

        Gmm_TimerStart(GMM_TIMER_T3302);

    }

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_GMM_ProcRauHoldProcedure_RcvCoverLost();

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_BufferMsgDump();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_ServReqInit()
{
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSR_DATA                        */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucServPreSta)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucServPreSta))
    {                                                                           /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegNmlServ
  Function : ��GMM-REGISTER-NORMAL-SERVICE״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegNmlServ()
{
    if ((GMM_TRUE == GMM_IsCasGsmMode())
     || (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        return;
    }
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegImsiDtchInit
  Function : ��GMM-REGISTER-IMSI-DETACH-INIT״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegImsiDtchInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_SuspendWaitForSys
  Function : ��GMM-SUSPEND-WAIT-FOR-SYSINFO״̬���յ�ԭ��MMCGMM_COVERAGE_LOST_IND �Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. s46746  2009.8.19  �¹�����
    2.��    ��   : 2014��12��25��
      ��    ��   : w00167002
      �޸�����   : DTS2014122201960:��L��SRVCC HO��G��HO��W,RABM�����ؽ�����������
                   ����RAU�������յ�ϵͳ��Ϣ���ٴη���RAU,��������REL����·������
                   �������޸�Ϊ��HO������������ʱ����ϵͳ��Ϣ��
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_SuspendWaitForSys()
{
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmRauCtrl.ucNpduCnt = 0x0;
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }
    else
    {
#if 0
        GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                       GMM_RABM_IMMEDIATELY_RAU);
#endif

        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }

    GMM_BufferMsgDump();
}

/*******************************************************************************
  Module   : Gmm_RcvSmDataReq
  Function : ԭ��GMMSM_DATA_REQ�Ľ��մ���
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2.��    ��   : 2007��08��14��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D12689
    3.��    ��   : 2007��11��13��
      ��    ��   : hanlufeng 41410
      �޸�����   : �������ⵥ�ţ�A32D12187
    4.��    ��   : 2007��12��18��
      ��    ��   : l00107747
      �޸�����   : �������ⵥ�ţ�A32D13917,GMM����SM����͵�ǰ���ܴ�����Ҫ������Ҫ������
                   ���������ڴ�����
    5.��    ��   : 2008��7��23��
      ��    ��   : luojian id:107747
      �޸�����   : �������ⵥ��AT2D04627/AT2D04237

    6.��    ��   : 2010��4��13��
      ��    ��   : o00132663
      �޸�����   : AT2D18275, GMM�����˲�������PDPȥ����
    7.��    ��   : 2011��05��12��
      ��    ��   : h44270
      �޸�����   : �������ⵥ�ţ�DTS2011051104889�����������󣬽��뵽��֧��GPRSС��������ѡ��ԭ��ע���С�������񲻿���
    8.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
    8.��    ��   : 2012��05��12��
      ��    ��   : l65478
      �޸�����   : �������ⵥ�ţ�DTS2012041707074,��RAU�������յ�����PDPȥ����,ȥ���������Ϣ�޷���������
    9.��    ��  : 2012��08��24��
      ��    ��  : m00217266
      �޸�����  : �޸�GMM_SndSmServiceRej�ӿڣ����ԭ��ֵ
    10.��    ��   : 2012��8��15��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
   11.��    ��   : 2012��12��11��
      ��    ��   : w00176964
      �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
   12.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���

   13.��    ��   : 2014��11��19��
      ��    ��   : w00167002
      �޸�����   : DTS2014111803732:���յ�����ʱ�򣬼���PDP����û�еȵ�SMC��ֱ��
                   ������PS PDP����޸�Ϊ���棬��SMC�󴥷�PDP���
*******************************************************************************/
VOS_VOID Gmm_RcvSmDataReq(
                      VOS_VOID       *pMsg                                          /* ָ��ԭ���ָ��                           */
                      )
{
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
     && (VOS_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {/* ��ǰPS��������ޣ��ظ�SMʧ�� */
        GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        return;
    }

    NAS_GMM_ClearBufferedSmDataReq();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬���в�ͬ����                     */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM_DEREGISTERED_INITIATED״̬           */
        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        NAS_GMM_ProcSmDataReq_RAUInit(pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:

        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {
            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg); /* ���� RRMM_DATA_REQ                       */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
                Gmm_BufSmDataReqMsg(pMsg);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
            Gmm_BufSmDataReqMsg(pMsg);
        }
        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
        Gmm_BufSmDataReqMsg(pMsg);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PDPACT);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PDPACT;
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
        }
        else if (g_GmmGlobalCtrl.SysInfo.ucForbMask != MMCGMM_GSM_NO_FORBIDDEN)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_FORBID_LA);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
        {
            /* �������������´��� */
            Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        }
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;                                                                     /* ����                                     */
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo
 ��������  : ��SUSPEND WAIT FOR SYSINFO״̬���յ�SM��Ϣ�Ĵ���
 �������  : pMsg        - �յ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��26��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2014122201960:��SUSPEND WAIT FOR SYSINFOʱ�������ʱ����
                ���У��������ϵͳ��Ϣ��
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }

    /* �ڴ�G�л���Wʱ,��Ҫ���ȷ���RAU�ָ�PS,Ȼ�������SM��Ϣ */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        Gmm_BufSmDataReqMsg(pMsg);

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* �����ϵͳ��Ϣ��ʱ�������У����·�RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_BufferSmDataReq
  Function : ����SM������DATA_REQ��Ϣ
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2010.01.07  �¹�����
*******************************************************************************/
VOS_VOID Gmm_BufferSmDataReq(VOS_VOID       *pMsg)
{
    GMMSM_DATA_REQ_STRU      *pGmmSmDataReq;                                         /* GMMSM_DATA_REQ_STRU����ָ��              */
    GMMSM_DATA_REQ_STRU      *ptr;

    pGmmSmDataReq = (GMMSM_DATA_REQ_STRU *)pMsg;

    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq_DeregInit:WARNING: VOS_NULL_PTR pointer in Gmm_RcvSmDataReq_DeregInit");
          return;
    }
    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4));
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;               /* ����SM��Ϣ                               */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk  |= GMM_MSG_HOLD_FOR_SM;           /* ��SM��Ϣ�����־                         */

    return;
}
/*****************************************************************************
 �� �� ��  : Gmm_RcvCmServReq_RegAtmpToUpdt
 ��������  : GMM_REGISTERED_ATTEMPTING_TO_UPDATE״̬���յ�CM��������Ĵ���

 3gpp 24.008 4.2.5.1.4 : GMM-REGISTERED ATTEMPTING-TO-UPDATE:
    The MS shall use request from CM layers to trigger the combined routing area
 update procedure, if the network operates in network operation mode I.
 Depending on which of the timers T3311 or T3302 is running the MS shall stop
 the relevant timer and act as if the stopped timer has expired.

 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��23��
    ��    ��   : luojian id:107747
    �޸�����   : �������ⵥ��AT2D04627/AT2D04237,�����ɺ���,
  2.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID Gmm_RcvCmServReq_RegAtmpToUpdt(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    GMM_LOG_INFO("Gmm_RcvSmDataReq_RegAtmpToUpdt.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH״̬�£���ǰ�汾��֧��SMS������PS�������� */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }
    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_DATA_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* ֹͣTimer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* ֹͣTimer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*����RAU����*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        /*����SM��Ϣ*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ulEstCause = ((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause;
        return;
    }

    GMM_SndSmServiceRej(GMM_SM_CAUSE_PS_DETACH);
    return;
}

/*****************************************************************************
 �� �� ��  : Gmm_RcvCmServReq_DeregAtmpToAtch
 ��������  : GMM_REGISTERED_ATTEMPTING_TO_UPDATE״̬���յ�CM��������Ĵ���
 3gpp 24.008 4.2.4.2.2 : GMM-DEREGISTERED ATTEMPTING-TO-ATTACH:
    use requests from CM layers to trigger the combined GPRS attach procedure,
 if the network operates in network operation mode I. Depending on which of the
 timers T3311 or T3302 is running the MS shall stop the elevant timer and act
 as if the stopped timer has expired..

 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��23��
    ��    ��   : luojian id:107747
    �޸�����   : �������ⵥ��AT2D04627/AT2D04237,�����ɺ���,
  2.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  3.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID Gmm_RcvCmServReq_DeregAtmpToAtch(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;


    GMM_LOG_INFO("Gmm_RcvCmServReq_DeregAtmpToAtch.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH״̬�£���ǰ�汾��֧��SMS������PS�������� */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }

    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
        MS is in substate ATTEMPTING-TO-ATTACH and
            - expiry of timer T3302;
            - a new routing area is entered; or
            - an attach is triggered by CM sublayer requests.
        */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        /* �ø�SM��EST_CNF��־ΪTRUE */
        g_GmmAttachCtrl.ucSmCnfFlg        = GMM_TRUE;

        /* ����follow on ��־ */
        g_GmmGlobalCtrl.ucFollowOnFlg     = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        /* ֹͣTimer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* ֹͣTimer3311 */
        Gmm_TimerStop(GMM_TIMER_T3311);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

        /*����ATTACH����*/
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        return;
    }

    Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetGmmSmDataReqMsgType
 ��������  : ��ȡSM����GMM��DATA_REQ��Ϣ�е���Ϣ����
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2010��11��08��
    ��    ��  : z00161729
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetGmmSmDataReqMsgType(NAS_MSG_STRU *pstMsg)
{
    VOS_UINT8                           ucMsgType;

    if (0x70 == (pstMsg->aucNasMsg[0] & 0x70))
    {
        /* ������չTIʱ,��Ϣ����ȡ��aucNasMsg[2] */
        ucMsgType  = pstMsg->aucNasMsg[2];
    }
    else
    {
        /* ��ȡ��Ϣ����ȡ��aucNasMsg[1] */
        ucMsgType  = pstMsg->aucNasMsg[1];
    }

    return ucMsgType;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running
 ��������  : T3340�����ڼ��յ�sm��data req������Ϣ�����ж��ǻ��滹�Ƿ�������
 �������  : enMsgType - SM��GMMͨ��GMMSM_DATA_REQ����ʱ�������Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ��sm data req���󷢸�����
             VOS_FALSE - ����Ҫ��sm data req���󷢸����绺��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2014��10��22��
    ��    ��  : z00161729
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32                      enMsgType
)
{
    if ((SM_STATUS == enMsgType)
     || (SM_MOD_PDP_CONTEXT_ACC_M2N == enMsgType)
     || (SM_DEACT_PDP_CONTEXT_ACC == enMsgType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*******************************************************************************
  Module   : Gmm_RcvSmDataReq_RegNmlServ
  Function : REGISTERED_NORMAL_SERVICE״̬��ԭ��GMMSM_DATA_REQ�Ľ��մ���
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2.��    ��   : 2006��2��17��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01287����ӡ����
    3.��    ��   : 2007��11��16��
      ��    ��   : hanlufeng 41410
      �޸�����   : ���ⵥ�ţ�A32D12187
    4.��    ��   : 2009��07��23��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��:AT2D13173,û���жϽ���ģʽ����G�·�����SR
    5.��    ��   : 2010��11��06��
      ��    ��   : z00161729
      �޸�����   : ���ⵥ��:DTS2010110600919:GCF 11.3.1/11.3.2��ͨ��,ȥ�����GMM����T3340�ȴ���·�ͷ�,
                   �յ�����modify pdp����,sm��status��Ϣ,GMM����δ��������,����GCFʧ��
    6.��    ��   : 2010��11��09��
      ��    ��   : w00166186
      �޸�����   : ���ⵥ��:DTS2010110900902,  ���Ӷ�REL_IND CAUSEֵΪ
                   RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT�Ĵ���
    7.��    ��   : 2011��3��2��
      ��    ��   : z00161729
      �޸�����   : DTS2010071601574:RAU��������յ�rau accept��Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ�ڼ�,
                   ����sm����,��RAU�����ٷ���
    8.��    ��   : 2011��3��3��
      ��    ��   : z00161729
      �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
    9.��    ��   : 2012��4��20��
      ��    ��   : l65478
      �޸�����   : DTS2012041707566:BVT����ʱ,�ڷ���PDPȥ����ǰGMM�����ͷ�����������
   10.��    ��   : 2013��2��06��
      ��    ��   : w00176964
      �޸�����   : DTS2013020601874:G2W CS�����л�������,�绰�ҶϺ�GPRS RESUME FAILURE,
                   �û�����PS����,G���ڽ�����ѡ����ʱ��һ�����ŷ���ʧ��
   11.��    ��   : 2013��11��18��
      ��    ��   : w00167002
      �޸�����   : DTS2013112006986:������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                   TD�²�����SMC���̡�
   12.��    ��   : 2014��10��23��
      ��    ��   : z00161729
      �޸�����   : DTS2014102403468:rau accept����û�д�follow on proceed����Ҫ����T3340��T3340�����ڼ�����յ�����pdp modify�����ȥ����������Ҫ�����ظ�
*******************************************************************************/
VOS_VOID Gmm_RcvSmDataReq_RegNmlServ(
                                 VOS_VOID       *pMsg                           /* ָ��ԭ���ָ��                           */
)
{
    NAS_MSG_STRU                       *pNasMsg;                                /* ����ָ��                                 */
    VOS_UINT32                          ulEstCause;                             /* RRC���ӽ���ԭ��                          */
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32  ucMsgType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT8                           ucIsUtranSmcNeeded;

    ucIsUtranSmcNeeded = NAS_UTRANCTRL_IsUtranPsSmcNeeded();

    enCurRat  = NAS_MML_GetCurrNetRatType();
    pNasMsg   = VOS_NULL_PTR;                                                     /* ��ʼ��ָ��                               */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        Gmm_BufferSmDataReq(pMsg);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && (!((NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender !=
                                    enCurRat))))
    {                                                                           /* ��ǰ����������                           */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            /* RESUME FAIL ��Ҫ��RAUʱ���Ȼ���SM����Ϣ��RAU���ٽ��д���*/
            if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
            {
                Gmm_BufSmDataReqMsg(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */
            }
        }


        /* FDD/TDD�յ������Ա�������TDD�²���Ҫ�����Ա�����Ҳ���Է���ҵ�� */
        else if ( ( (VOS_TRUE                              == ucIsUtranSmcNeeded)
                  && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
               || ( (NAS_MML_NET_RAT_TYPE_WCDMA            == enCurRat)
                 && (VOS_FALSE                             == ucIsUtranSmcNeeded) ) )

        {
            /*�ж�T3340 �Ƿ����� */
            if ((VOS_FALSE == NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(ucMsgType))
             && (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG)))
            {
                Gmm_BufferSmDataReq(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */
            }
        }
        else
        {
            /*�����Ա���δ�򿪣��軺��SM��Ϣ��
              ͨ��service request���Դ������Ա���
              ��GMM_SERVICE_REQUEST_INITIATED״̬��,
              �յ�RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_RCV)��Ϣ���������Ա�����־λ
              �յ�RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_CMPL)��Ϣ���������SM��Ϣ*/
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* �洢��ǰ������                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

            Gmm_BufSmDataReqMsg(pMsg);
            /*Service request*/
            pNasMsg = Gmm_ServiceRequestMsgMake();                          /* ����make����                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

            Gmm_TimerStop(GMM_TIMER_T3340);
        }
    }
    else if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        GMM_LOG_INFO("Gmm_RcvSmDataReq_RegNmlServ:Inter System change, Exec select RAU.");

        /*GMM_BufferMsgReceive(pMsg);*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    /* �����ǰGMM�ڽ����ӵĹ���������RAI�ı������Ҫ���ͷ����ڽ��������ӣ�
       ��ô�����ڵȴ������������ͷ�ָʾ�Լ������ͷ�ָʾ֮���ϱ���ϵͳ��Ϣ
       �������յ����ϲ�������Ҫ����*/
    else if ((GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
          || (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause))
    {
        if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }
        Gmm_BufSmDataReqMsg(pMsg);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        /* RESUME ��Ҫ��RAUʱ���Ȼ���SM����Ϣ��RAU���ٽ��д���*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            Gmm_BufSmDataReqMsg(pMsg);
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */

            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        }
    }
    else
    {                                                                           /* ��ǰû����������                         */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* Timer3302��������                        */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* ����Timer3302                            */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* Timer3311��������                        */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* ����Timer3311                            */
        }
        else
        {
        }
        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* �洢��ǰ������                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

        /*����SM��Ϣ*/
        Gmm_BufSmDataReqMsg(pMsg);

        pNasMsg = Gmm_ServiceRequestMsgMake();                                  /* ����service request��������              */

        switch (((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause)
        {                                                                       /* ת��ԭ��ֵ                               */
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ():INFO: The RRC Connection Setup Cause is GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL");
            ulEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
        }

        g_GmmGlobalCtrl.ulEstCause = ulEstCause;
        Gmm_SndRrmmEstReq(ulEstCause, GMM_RRC_IDNNS_UNKNOWN, pNasMsg);          /* ����service request(signalling)          */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REQ,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegInit
  Function : ��GMM_REGISTERED_INITIATED��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.11  �¹�����
  2.��    ��   : 2006��2��17��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�A32D01287
  3.��    ��   : 2008��7��2��
    ��    ��   : l00107747
    �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegInit(
                                  VOS_VOID    *pMsg,                                /* ��Ϣָ��                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ��ʼ��ָ��                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);       /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LAû��,������A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (VOS_TRUE == g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg))
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* ���GMM���ܽ���RAUʱ����Ҫ����MM��LU���� */
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregInit
  Function : ��GMM-DEREGISTERED.NORMAL-SERVICE��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2. ��    ��   : 2006��11��1��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D06572
    3. ��    ��   : 2011��07��13��
       ��    ��   : w00166186
       �޸�����   : V7R1 PHASE II ATTACH/DETACH����
    4.��    ��   : 2013��10��05��
      ��    ��   : l65478
      �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregInit(
                                    VOS_VOID    *pMsg,                              /* ��Ϣָ��                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI�仯��־                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length�仯��־                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI�仯��־                              */
                                    )
{
    VOS_UINT8                           ucDetachType;
    MMCGMM_SYS_INFO_IND_STRU            *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ��ʼ��ָ��                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();

            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if (((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    {                                                                           /* RA�ı����DRX�ı�                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        ucDetachType = NAS_GMM_GetDetachTypeFromProcName(g_GmmDetachCtrl.ucDetachProc);
        if (GMM_INVALID_DETACH_TYPE != ucDetachType)
        {
            Gmm_MsInitNormalDetach(ucDetachType);
        }
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RauInit
  Function : ��GMM-ROUTING_AREA_UPDATING_INITIATED��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2. ��    ��   : 2008��7��2��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
    3. ��    ��   : 2011��4��6��
       ��    ��   : c00173809
       �޸�����   : �������ⵥ�ţ�DTS2011032900575,NMO1������RAU������NMO1��֧��
                    GPRS��С���У�T3312��ʱû�з���������LAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RauInit(
                                  VOS_VOID    *pMsg,                                /* ��Ϣָ��                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        /* ��ǰפ����λ������֮ǰפ����λ����LAIû�ı�,����������ģʽI,����T3312��ʱ */
        if ((GMM_FALSE == ucLaiChgFlg)
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                        /* ֪ͨMM����LU                             */
            }
            else
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RauInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_RauInit(): call Gmm_ComCnfHandle to clear msg buffer");

        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
             == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        ||(VOS_TRUE == g_GmmRauCtrl.ucRetryRauForRelCtrlFlg))
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* ����״̬��ΪGU2                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
    }
    else
    {
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_ServReqInit
  Function : ��GMM-ROUTING_AREA_UPDATING_INITIATED��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2.��    ��   : 2011��11��8��
      ��    ��   : s46746
      �޸�����   : V7R1 PhaseII�׶ν���ػ�������
    3.��    ��   : 2012��1��18��
      ��    ��   : s46746
      �޸�����   : ���ⵥ�ţ�DTS2012011601544,����ģʽI ����ע���PS�ɹ�,�������к�CSָʾ��������
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_ServReqInit(
                                      VOS_VOID    *pMsg,                            /* ��Ϣָ��                                 */
                                      VOS_UINT8   ucRaiChgFlg,                      /* RAI�仯��־                              */
                                      VOS_UINT8   ucDrxLengthChgFlg,                /* DRX length�仯��־                       */
                                      VOS_UINT8   ucLaiChgFlg                       /* LAI�仯��־                              */
                                      )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_ComCnfHandle();
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_ServReqInit:INFO: specific procedure ended");
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA�ı����DRX�ı�                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }

        if (GMM_TRUE == ucRaiChgFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* �������жϵ�SR����                       */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregNmlServ
  Function : ��GMM_DEREGISTERED_NORMAL_SERVICE��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.11  �¹�����
  2.��    ��   : 2010��9��9��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�DTS2010082301847�������ȼ��б�����ʱ��CS ONLY����Ȼ��Ҫ�ܴ���PS Attach
  3.��    ��   : 2010��12��24��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2011��07��29��
    ��    ��   : L65478
    �޸�����   : �������ⵥ�ţ�DTS2011072503161,CS ONLY����ѡ������,����PDP����
  7.��    ��   : 2011��04��02��
    ��    ��   : x00180552
    �޸�����   : �������ⵥ�ţ�DTS2011040600327,CS ONLY����פ����,����PDP����
  8.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�NAS_GMM_CnfSmNotAttach�ӿڣ����ԭ��ֵ
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2016��1��27��
    ��    ��   : z00359541
    �޸�����   : DTS2016012302336:����RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ����Ҫ�ܷ���ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregNmlServ(
                                       VOS_VOID    *pMsg,                           /* ��Ϣָ��                                 */
                                       VOS_UINT8   ucLaiChgFlg                      /* LAI�仯��־                              */
                                       )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* ����״̬�Ĺ�������                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        /* ��ʱ�����л����SMע��������Ϣ */
        GMM_BufferMsgResume();
        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* ǰһ��С��Ҳ��֧��GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);
    }
    else
    {                                                                           /* С���ı�                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch
  Function : ��GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.11  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  2.��    ��   : 2011��05��13��
    ��    ��   : h44270
    �޸�����   : �������ⵥ�ţ�DTS2011051203553����ATTACH�����з�����ѡ����ϵͳRAi��ͬʱ��GMM״̬����ȷ������ҵ�񲻿���
  3.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
  4.��    ��   : 2011��11��15��
    ��    ��   : w00166186
    �޸�����   : DTS201111402055,����ģʽI�±�17��ԭ��ֵ�ܾ�5�κ�MM��ͣ�ķ���ע��
  5.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  7.��    ��   : 2013��9��29��
    ��    ��   : w00242748
    �޸�����   : DTS2013092302598:�ֶ�������L�³ɹ�פ����CSFB��W�£�λ�����仯��LAU/RAU����ʧ��(5��)��
                 ������ԭС����������������RAUʧ�ܣ�MM����LAUʧ�ܣ���ѭ����MM ATTEMPT COUNTER��������
  8.��    ��   : 2014��04��08��
    ��    ��   : s00217060
    �޸�����   : DTS2014040901544:PS��ע�ᱻ��#111,�������T3302��ʱ��ʱ��Ϊ0�������ͷ����յ�ϵͳ��Ϣʱ��UEһֱ����ATTACH
  9.��    ��   : 2016��1��27��
    ��    ��   : z00359541
    �޸�����   : DTS2016012302336:����RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ����Ҫ�ܷ���ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(
                                          VOS_VOID    *pMsg,                        /* ��Ϣָ��                                 */
                                          VOS_UINT8   ucRaiChgFlg,                  /* RAI�仯��־                              */
                                          VOS_UINT8   ucDrxLengthChgFlg,            /* DRX length�仯��־                       */
                                          VOS_UINT8   ucLaiChgFlg                   /* LAI�仯��־                              */
                                          )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if ((GMM_TRUE == ucRaiChgFlg)
        &&  (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask))
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter��0                */
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */


        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter��0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* ��С����Ҫ����attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* ����Attach                               */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }
        else
        {
            /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
            else
            {


                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();
                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }
        }
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegNmlServ
  Function : ��GMM-REGISTERED.NORMAL-SERVICE��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.11  �¹�����
  2.��    ��   : 2007��1��26��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D08577
  3.��    ��   : 2007��3��22��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D09593
  4.��    ��   : 2007��4��5��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D10023
  5.��    ��   : 2007��07��10��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥA32D11966
  7.��    ��   : 2007��7��14��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D12438
  8.��    ��   : 2008��12��31��
    ��    ��   : l65478
    �޸�����   : �������ⵥ�ţ�AT2D07251 RAUʱ�����������Ҫ���ͣ���λfollow on��־
  9.��    ��   : 2009��3��31��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D10231/AT2D10624 ��RABM�����յ�Dsflowrpt�����ϱ���
                 ��PDP�����W�¶������漰 W->G->W���л�ʱ���������ָܻ�
  10.��    ��   : 2009��8��19��
     ��    ��   : o00132663
     �޸�����   : ���ⵥ�ţ�AT2D13895, ��NAS R6Э���������ԡ�פ����ϵͳ��Ϣ�ı䣬ָʾDSAC CS��BAR��
                  ֮����Ȼ���Բ�����ͨ�绰
  11.��    ��   : 2010��8��14��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�DTS2010081400611��GMM����פ��FPLMN���û�ָ������FPLMN������RAU����
  12.��    ��   : 2010��10��05��
     ��    ��   : o00132663
     �޸�����   : ���ⵥ�ţ�DTS2010093000943��GCF12.4.1.5��GMM 5��RAUʧ�ܷ����������ػ�ԭС����
                  ��Ӧ�÷���RAU.
  13.��    ��   : 2010��11��16��
     ��    ��   : z00161729
     �޸�����  : ���ⵥDTS2010111502913������ģʽI+A,������������RAU�����н�����Ӧ��������RAU
  15. ��    ��   : 2010��12��24��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
  16.��    ��   : 2011��7��14��
     ��    ��   : h44270
     �޸�����   : V7R1 PhaseII�׶ε�����ע������
  17. ��    ��   : 2011��05��31��
      ��    ��   : c00173809
      �޸�����   : �������ⵥ�ţ�DTS2011051902988��GMM����״̬��,ָ���ѵ�֮ǰ��ͬRAI,LAI��С��ʱ,û��RAU.
  18. ��    ��   : 2011��08��12��
      ��    ��   : c00173809
      �޸�����   : �������ⵥ�ţ�DTS2011071802663��BVT����ʧ�ܣ���PDP�����У�������Ȼ�����פ��������С�����ٻص�
                    ԭ��С������RAU��
  19. ��    ��   : 2011��04��20��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�DTS2011040804149����V3R1C31B027����RAU��PS ONLY�£�PMM_IDLE̬W2G��ѡ�󣬷���pingδ����RAU���̣��޷���������
  20. ��    ��   : 2011��03��18��
      ��    ��   : c00173809
      �޸�����   : �������ⵥ�ţ�DTS2011031603952��CS����Ч������ģʽI,GMM��������RAU
  21. ��    ��   : 2011��11��19��
      ��    ��   : zhoujun 40661
      �޸�����   : DTS2011111700165,����ģʽI��,GMM�ص�ԭС��,δ��֪ͨMM������������
  22. ��    ��   : 2011��12��23��
      ��    ��   : w00167002
      �޸�����   : DTS2011111901055:�������ϱ�ԭ��ֵ��NAS_MML_REG_FAIL_CAUSE_NULL
                    �޸�ΪNAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                    �޸�ԭ��:��ON PLMN״̬���յ��˼�������Ϣ����ԭ��ֵС��
                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE������ܷ���������
  23. ��    ��   : 2012��1��18��
      ��    ��   : s46746
      �޸�����   : ���ⵥ�ţ�DTS2012011601544,����ģʽI ����ע���PS�ɹ�,�������к�CSָʾ��������
  24. ��    ��   : 2012��2��14��
      ��    ��   : w00176964
      �޸�����   : ���ⵥ�ţ�DTS2012021005606:UE��Uģ����RAU����Ӧ,T3311�����ڼ��ش�RAU
  25. ��    ��   : 2012��3��28��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�DTS2012032002585:��W->L->Wʱ���ص�W��û�з���RAU
  26. ��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
  27. ��    ��   : 2012��8��13��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
  28. ��    ��   : 2013��6��18��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�DTS2013061406222,����RAUʱӦ���ж� CS��ҵ��״̬
  29. ��    ��   : 2013��5��22��
      ��    ��   : w00167002
      �޸�����   : DTS2013051408623:��W��46007��PSע��ʧ��5�Σ�������L�µ�46002
                    ��ע��ɹ����û�����绰ͨ��������ʽ���䵽W�µ�46002�����ϣ�
                    GMM����RAUʧ�ܺ�û���ٳ���RAU.
                    ԭ��:��46007������ע��ʧ��5�κ���䵽W�µ�46002�Ϻ�û��
                    ����ATTEMPT COUNTER����.
  30.��    ��   : 2013��7��19��
     ��    ��   : w00167002
     �޸�����   : DTS2013071900239:W������ģʽI,����ע��PS only�ɹ���CSʧ��ԭ��
                    #17,����ģʽ��I--->II,��ʱ��Ӧ��������ATTACH.
                    �����ʱ��Ȼ������ģʽI,���û�����ΪPS ONLY,��Ҳ���÷���
                    ����ATTACH.
  31.��    ��   : 2013��08��16��
     ��    ��   : l65478
     �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���
  31.��    ��   : 2013��9��29��
     ��    ��   : w00242748
     �޸�����   : DTS2013092302598:�ֶ�������L�³ɹ�פ����CSFB��W�£�λ�����仯��LAU/RAU����ʧ��(5��)��
                  ������ԭС����������������RAUʧ�ܣ�MM����LAUʧ�ܣ���ѭ����MM ATTEMPT COUNTER��������
  32.��    ��   : 2013��11��1��
     ��    ��   : z00161729
     �޸�����  : DTS2013110103529:L�ؽ���gu��ISR����λ����δ�ı䣬gmmδ����rau
  33.��    ��   : 2014��04��08��
     ��    ��   : s00217060
     �޸�����   : DTS2014040901544:PS��ע�ᱻ��#111,�������T3302��ʱ��ʱ��Ϊ0�������ͷ����յ�ϵͳ��Ϣʱ��UEһֱ����ATTACH
  34.��    ��   : 2014��06��17��
     ��    ��   : s00217060
     �޸�����   : DTS2014061003286:GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ����������
  35.��    ��   : 2015��2��12��
     ��    ��   : s00217060
     �޸�����   : VOLTE SWITCH�޸ģ�voice domain�仯ʱ��Ҫ��RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNmlServ(
                                     VOS_VOID    *pMsg,                             /* ��Ϣָ��                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI�仯��־                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length�仯��־                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI�仯��־                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
    VOS_UINT32                          ulIsAModeAndNetworkIFlg;
    /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();
    /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������ʱ���Ƿ�Ϊ0���жϣ�UE��һֱ����ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* ��·�ͷź���Ҫ���·���Service Request���� */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* ����RAU����                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* ����RAU����                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311��������ʱ�ŷ���RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            /* <==A32D12438 */
            /*
            ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
            GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
            ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
            ��Ҫ��ǰ�汻�жϵ����̽�����
            */
            else if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                Gmm_RoutingAreaUpdateHandleFollowOn();
            }
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W������ݲ�֧�������½��յ�Ѱ��*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
    }

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    else
    {
        /*
        ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
        GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
        ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
        ��Ҫ��ǰ�汻�жϵ����̽�����
        */

        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            if (VOS_FALSE == ucCsRestrictionFlg)
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }
            else
            {
                NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                   /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */

            }
        }


        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        /* ԭ��T3312��ʱ����suspend wait for sysinfo״̬�����,��ΪL handover to W,
           ״̬Ǩ����register normal service״̬,������Ҫ�ڴ�״̬�´���T3312��ʱ */
        if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
        }
    }
    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  �� �� ��  : NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch
  ��������  : GMM_REGISTERED_PLMN_SEARCH�յ�ϵͳ��Ϣ�Ĵ���
  �������  : VOS_VOID   *pMsg                     ��Ϣָ��
              VOS_UINT8   ucRaiChgFlg              RAI�仯��־
              VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
              VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2014��06��12��
     ��    ��   : s00217060
     �޸�����   : �����ɺ���
   2.��    ��   : 2014��08��02��
     ��    ��   : s00217060
     �޸�����   : DTS2014073105516:REGISTERED_PLMN_SRCH״̬T3311��ʱ��֮���յ�ϵͳ��Ϣ�����������ģʽI,��Ҫ������ע��
   3.��    ��   : 2015��2��12��
     ��    ��   : s00217060
     �޸�����   : VOLTE SWITCH�޸ģ�voice domain�仯ʱ��Ҫ��RAU
   4.��    ��   : 2016��1��27��
     ��    ��   : z00359541
     �޸�����   : DTS2016012302336:����RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ����Ҫ�ܷ���ע��
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(
                                     VOS_VOID    *pMsg,                             /* ��Ϣָ��                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI�仯��־                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length�仯��־                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI�仯��־                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_TRUE == ucRaiChgFlg)
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* ����ATTEMPT TO UPDATE����REGISTERED_NO_CELL_AVAILABLE״̬����
               �������յ�ϵͳ��Ϣ����Ҫ���ATTEMPT COUNTER */
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    /* RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ��RAI������ҪͣT3311��ʱ��������ע�� */
    else if ((VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
          && (GMM_FALSE == ucRaiChgFlg)
          && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch: User NW Srch, need to stop T3311 and send RAU Req");
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������ʱ���Ƿ�Ϊ0���жϣ�UE��һֱ����ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
    {
        NAS_GMM_IsrActiveRaiNoChg_InterSys();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* ��·�ͷź���Ҫ���·���Service Request���� */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */

    /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* ����RAU����                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* ����RAU����                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311��������ʱ�ŷ���RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
            /* <==A32D12438 */
            /*
            ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
            GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
            ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
            ��Ҫ��ǰ�汻�жϵ����̽�����
            */
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W������ݲ�֧�������½��յ�Ѱ��*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }
    else
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

        /* T3311δ��ʱ���������̴��� */
        else if (GMM_FALSE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                if (GMM_FALSE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;


                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }



                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                        Gmm_RoutingAreaUpdateHandleFollowOn();
                    }
                }
            }
            else if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                /*
                3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
                reset when the MS is in substate ATTEMPTING-TO-UPDATE and
                    - a new routing area is entered;
                    - expiry of timer T3302; or
                    - at request from registration function.
                */
                g_GmmRauCtrl.ucRauAttmptCnt = 0;

                /* ֹͣTimer3302 */
                Gmm_TimerStop(GMM_TIMER_T3302);

                /* ֹͣTimer3311*/
                Gmm_TimerStop(GMM_TIMER_T3311);

                /* ����RAU���� */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                if ((GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
                 || (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG)))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }

            }

            if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
            {
                /*W������ݲ�֧�������½��յ�Ѱ��*/
            }
            else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
            {
                Gmm_DealWithBuffAfterProc();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
        /* T3311��ʱ��REGISTERED_PLMN_SRCH״̬��Ҫ����RAU */
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegUpdtNeed
  Function : ��GMM-REGISTERED.UPDATE-NEEDED��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.11  �¹�����
 2.��    ��   : 2011��7��14��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3.��    ��   : 2011��06��09��
   ��    ��   : c00173809
   �޸�����   : �������ⵥ�ţ�DTS2011060705224��GMM��LIMITED SERVICE״̬�£�I+Aģʽ�յ���֧��
                    GPRS��ͬLAI��С��ʱ��������LAU��
 4.��    ��   : 2011��08��12��
   ��    ��   : c00173809
   �޸�����   : �������ⵥ�ţ�DTS2011071802663��BVT����ʧ�ܣ���PDP�����У�������Ȼ�����פ��������С�����ٻص�
                   ԭ��С������RAU��
 5.��    ��   : 2011��05��10��
   ��    ��   : c00173809
   �޸�����   : �������ⵥ�ţ�DTS2011050402447����ͬra/la��֧��GPRS��ѡ����֧��GPRS��С��,����ѡ��ԭ��С��Ҫ������RAU
 6.��    ��   : 2012��2��15��
   ��    ��   : w00166186
   �޸�����   : CSFB&PPAC&ETWS&ISR ����
 7.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 8.��    ��   : 2015��2��12��
   ��    ��   : s00217060
   �޸�����   : VOLTE SWITCH�޸ģ�voice domain�仯ʱ��Ҫ��RAU
 9.��    ��   : 2016��1��27��
   ��    ��   : z00359541
   �޸�����   : DTS2016012302336:����RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ����Ҫ�ܷ���ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegUpdtNeed(
                                        VOS_VOID    *pMsg,                          /* ��Ϣָ��                                 */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI�仯��־                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                    ucCsRestrictionFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */

        /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else
    {                                                                           /* С���ı�                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
        {
            ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

            if (!((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)))
            {                                                                   /* ��A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                  || (VOS_TRUE == ucCsRestrictionFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
            }
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
        }

    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt
  Function : ��GMM-REGISTERED.ATTEMPTING-TO-UPDATE��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
  4.��    ��   : 2011��11��15��
    ��    ��   : w00166186
    �޸�����   : DTS201111402055,����ģʽI�±�17��ԭ��ֵ�ܾ�5�κ�MM��ͣ�ķ���ע��
  5.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ

  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  7.��    ��   : 2013��9��29��
    ��    ��   : w00242748
    �޸�����   : DTS2013092302598:�ֶ�������L�³ɹ�פ����CSFB��W�£�λ�����仯��LAU/RAU����ʧ��(5��)��
                 ������ԭС����������������RAUʧ�ܣ�MM����LAUʧ�ܣ���ѭ����MM ATTEMPT COUNTER��������
  8.��    ��   : 2016��1��27��
    ��    ��   : z00359541
    �޸�����   : DTS2016012302336:����RAU���û�ָ���Ѵ�ϣ������ѵ�ͬһ����Ҫ�ܷ���ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(
                                        VOS_VOID    *pMsg,                          /* ��Ϣָ��                                 */
                                        VOS_UINT8   ucRaiChgFlg,                    /* RAI�仯��־                              */
                                        VOS_UINT8   ucDrxLengthChgFlg,              /* DRX length�仯��־                       */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI�仯��־                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* ��С����Ҫ����RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegNoCell
  Function : ��GMM-REGISTERED.NO-CELL-AVAILABLE״̬��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucDrxLengthChgFlg        DRX length�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.10  �¹�����
  2.��    ��   : 2007��05��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D10713
  3.��    ��   : 2009��3��31��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D10231/AT2D10624 ��RABM�����յ�Dsflowrpt�����ϱ���
                 ��PDP�����W�¶������漰 W->G->W���л�ʱ���������ָܻ�
  4.��    ��   : 2009��7��23��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��: AT2D13173�����������������̽��л����SM��Ϣ�Ĵ���
  5.��    ��   : 2009��8��19��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D13895, ��NAS R6Э���������ԡ�פ����ϵͳ��Ϣ�ı䣬ָʾDSAC CS��BAR��
                 ֮����Ȼ���Բ�����ͨ�绰
  6.��    ��   : 2009��8��25��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D14050, CS��ͨ��ʱT3312��ʱӦ����������RAU
  7.��    ��   : 2010��8��14��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2010081400611��GMM����פ��FPLMN���û�ָ������FPLMN������RAU����
  8.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  9.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 10.��    ��   : 2011��05��12��
    ��    ��   : h44270
    �޸�����   : �������ⵥ�ţ�DTS2011051104889�����������󣬽��뵽��֧��GPRSС��������ѡ��ԭ��ע���С�������񲻿���
 11.��    ��   : 2011��04��20��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�DTS2011040804149����V3R1C31B027����RAU��PS ONLY�£�PMM_IDLE̬W2G��ѡ�󣬷���pingδ����RAU���̣��޷���������
 12.��    ��   : 2012��3��28��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2012032002585:��W->L->Wʱ���ص�W��û�з���RAU
 13.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
 14.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
 15.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 16.��    ��   : 2013��11��1��
    ��    ��   : z00161729
    �޸�����   : DTS2013110103529:L�ؽ���gu��ISR����λ����δ�ı䣬gmmδ����rau
 17.��    ��   : 2014��06��17��
    ��    ��   : s00217060
    �޸�����   : DTS2014061003286:�յ�ϵͳ��Ϣʱ���T3311��ʱ����RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNoCell(
                                    VOS_VOID    *pMsg,                              /* ��Ϣָ��                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI�仯��־                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length�仯��־                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI�仯��־                              */
                                    )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictionFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucSimCsRegStatus        = NAS_MML_GetSimCsRegStatus();

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* ֪ͨMM����LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
           || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
#if (FEATURE_ON == FEATURE_LTE)
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
           && (NAS_MML_TIN_TYPE_GUTI != enTinType))
#else
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg))
#endif
    {                                                                           /* �ص�ԭ����RA����DRX����û�иı�          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* ��������ʱT3312δ���                    */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED
                == NAS_MML_GetPsUpdateStatus())
            {                                                                   /* ����״̬��GU1                            */

                /* T3311��ʱ��REGISTERED_PLMN_SRCH״̬��Ҫ����RAU */
                if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* ���ü����̱�־                           */

                    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
                     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
                     || (VOS_TRUE == ucCsRestrictionFlg))
                    {                                                               /* ��A+I                                    */
                        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }

                        /* ���֮ǰ����������T3312��ʱ��������T3323,���ؽ�����������ҪֹͣT3323*/
                        Gmm_TimerStop(GMM_TIMER_T3323);
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* ����T3312                                */
                        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                        /* ��MMC����PSע���� */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                                     NAS_MML_REG_FAIL_CAUSE_NULL);

                        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                    }
                    else
                    {                                                               /* A+I                                      */
                        if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
                        {                                                           /* ����״̬��U1,����Gs�����Ѵ���            */
                            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                            {
                                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                            }
#endif
                            Gmm_TimerStart(GMM_TIMER_T3312);                        /* ����T3312                                */
                            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                            {                                                       /* ��Ҫ��SM��EST_CNF                        */
                                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM�ؽ����ɹ�����Ӧ                     */
                            }


                            /* ��MMC����PSע���� */
                            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                            if (VOS_TRUE == ucCsAttachAllow)
                            {                                                       /* CS������ע��                             */
                                NAS_GMM_SndMmCombinedRauInitiation();
                                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                               NAS_MML_REG_FAIL_CAUSE_NULL,
                                                               VOS_NULL_PTR,
                                                               VOS_NULL_PTR);                                      /* ���� MMCGMM_COMBINED_RAU_ACCEPTED        */

                                /*����RAU������ */
                                if(5<=g_GmmRauCtrl.ucRauAttmptCnt)
                                {
                                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                                }
                            }
                            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                        }
                        else
                        {                                                           /* ����״̬����U1,����Gs�����Ѿ��Ƴ�                           */
                            if ((VOS_TRUE != ucSimCsRegStatus)
                             || (VOS_FALSE == ucCsAttachAllow))
                            {                                                       /* sim��Ч����CS������ע��                */
                                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                                {
                                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                                }
#endif
                                Gmm_TimerStart(GMM_TIMER_T3312);                    /* ����T3312                                */
                                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                                {                                                   /* ��Ҫ��SM��EST_CNF                        */
                                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM�ؽ����ɹ�����Ӧ                     */
                                }
                                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                                /* ��MMC����PSע���� */
                                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                            }
                            else
                            {
                                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_UPDATING_TYPE_INVALID);                     /* ����RAU                                  */
                            }
                        }
                    }
                }
            }
            else
            {                                                                   /* ����״̬����GU1                          */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* ����RAU                                  */
            }

            if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            {
                if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                }
                if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    Gmm_DealWithBuffAfterProc();
                    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
                }
            }
        }
        else
        {                                                                       /* ��������ʱT3312���                      */
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* �������������־                         */
            if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
             || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* ��A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (VOS_TRUE == ucCsRestrictionFlg)
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {/* A+I ģʽ����CS�� BAR, ���� ��ǰ CS ͨ���� */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
            }
        }
    }
    else
    {                                                                           /* RA�ı����DRX�����仯                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* ���T3312������                        */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* ��A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU����                              */
        }
    }

    return;                                                                     /* ����                                     */
}


/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_SuspWaitSys
  Function : ��GMM-SUSPENDED-WAIT-FOR-SYSINFO��MMCGMM_SYS_INFO_IND�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
             VOS_UINT8   ucRaiChgFlg              RAI�仯��־
             VOS_UINT8   ucLaiChgFlg              LAI�仯��־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �¹�����
  2.��    ��   : 2006��10��9��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D05744
  3.��    ��   : 2011��2��14��
    ��    ��   : o00132663
    �޸�����   : ���ⵥDTS2010122401824��G->W��ѡ��δ����������RAU.
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 6. ��    ��   : 2011��5��16��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011050905176,��֧��GPRS��С����ϵͳ��ѡ����֧��GPRS��
                    С��,�쳣ֹͣ��T3312��ʱ��.
 7. ��    ��   : 2011��05��16��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ�DTS2011051005812������ģʽI,��ͬRAI,T3312��ʱʱ,��֧��GPRS��3GС����ѡ����֧��GPRS��2GС������ѡ��ԭ����3GС��,������RAU.
 8. ��    ��   : 2011��07��30��
    ��    ��   : f00179208
    �޸�����   : �������ⵥ�ţ�DTS2011072901080����V3R1C31B112W��ģ GCF/PTCRB��֤ Э����ԡ�˫ģ����6.2.2.3ʧ��
 9. ��    ��   : 2011��04��25��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ�DTS2011042205602����ͬRAI��,�Ӳ�֧��GPRS��2GС����ѡ��֧��GPRS��3GС��,����RAU.
10. ��    ��   : 2011��04��26��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ�DTS2011042502289����RAU��������ϵͳ��ѡ����ͬRAI��С������PS�޷��ṩ����.
11. ��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
12. ��    ��   : 2012��1��18��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2012011601544,����ģʽI ����ע���PS�ɹ�,�������к�CSָʾ��������
13. ��    ��   : 2012��03��20��
    ��    ��   : l00130025
    �޸�����   : DTS2012030105247,NASֻ������ʵ�ʷ����Ȩʱ,֪ͨW SecurityKey�������������WAS���ö�Ӧ�ӿڻ�ȡ
14. ��    ��   : 2012��3��14��
    ��    ��   : z00161729
    �޸�����   : ֧��ISR�޸�
15. ��    ��   : 2012��5��21��
    ��    ��   : l00171473
    �޸�����   : DTS2012051501480, w->L->w��������, �ص�w��Ӧ��GMM״̬�ָ�ΪGMM_REGISTERED_NO_CELL_AVAILABLE
16. ��    ��   : 2012��8��18��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
17. ��    ��   : 2012��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2012073106360:ISR����CSFB�ض����CCO��GU,idle̬λ��������������RAU
18. ��    ��   : 2012��09��08��
    ��    ��   : l65478
    �޸�����   : DTS012090302087,L->GUʱ,RAIû�иı�ʱ,GMM������RAU
19 .��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
20. ��    ��   : 2013��08��07��
    ��    ��   : l65478
    �޸�����   : �޸����ⵥDTS2013080502397,����ѡ��G�½���LU��,Ȼ��GASָʾ�ض���Wԭ����С��ʱ�����Gs�ڲ�����,��Ҫ��������RAU
21.��    ��   : 2013��9��29��
    ��    ��   : w00242748
    �޸�����   : DTS2013092302598:�ֶ�������L�³ɹ�פ����CSFB��W�£�λ�����仯��LAU/RAU����ʧ��(5��)��
                 ������ԭС����������������RAUʧ�ܣ�MM����LAUʧ�ܣ���ѭ����MM ATTEMPT COUNTER��������
22.��    ��   : 2015��2��12��
   ��    ��   : s00217060
   �޸�����   : VOLTE SWITCH�޸ģ�voice domain�仯ʱ��Ҫ��RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_SuspWaitSys(VOS_VOID* pRcvMsg,VOS_UINT8 ucRaiChgFlg,VOS_UINT8 ucLaiChgFlg)
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_VOID                           *pAddr;
    VOS_UINT8                           ucCsAttachAllow;

    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                           ucCsRestrictFlg;
    GMM_RAI_STRU                        stRai;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();

    pstConnStatus             = NAS_MML_GetConnStatus();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                             /* ǿ������ת��                             */

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* ��дLAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* ��дPLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        GMM_LOG_INFO("Gmm_RcvMmcSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* ͣ����Timer                              */

        /*��ϵͳ�ı�ʱ֪ͨRABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }

        /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */


        /*��ϵͳ�ı�ʱ֪ͨRABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {/* �µ�RA,��������ģʽ��� */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;

        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else                                                                        /* RA ��ͬ */
    {
        /* reference to 23.401 10.5.1.3 L->GU handoverʱ,RAI���ı䲻��Ҫ����RAU; TINָʾΪGUTIʱ��Ҫ����RAU */






        if ((((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
           || (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
          && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
#if (FEATURE_ON == FEATURE_LTE)
         || (NAS_MML_TIN_TYPE_GUTI == enTinType)
#endif
         )

        {

            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */

        }
        else if (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
        {
            /*��ϵͳ�ı�ʱ֪ͨRABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W,G�²�֧��GPRS,��W�º�,���RAI���ı�,���µ�����GMM_REGISTERED_UPDATE_NEEDED
               ״̬�½��յ�ϵͳ��Ϣ�Ĵ�����. */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState)
             || (GMM_ROUTING_AREA_UPDATING_INITIATED== gstGmmSuspendCtrl.ucPreState))
            {
                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);
            }
#if (FEATURE_ON == FEATURE_LTE)
                /* L��ѡ��G,·����δ�ı䣬ISR���������RAUʱ��Ҫ����״̬��
                  ����Ϊregister no cell available�������޷���ҵ�� */
            else if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
#endif
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
                }
                else
                {
                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    }
                    GMM_BufferMsgResume();
                }
            }
        }
        /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ���Ҫ��������ע�� */
        else if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ucCsAttachAllow)
              && (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
              && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
            /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ���Ҫ��������ע�� */
            if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
             && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

#endif
        else
        {
            /*��ϵͳ�ı�ʱ֪ͨRABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W, G�½����ֹ���߲�֧��GPRS����W�º����RAC���ı䣬���µ�����GMM_REGISTERED_UPDATE_NEEDED
               ״̬�µ�ϵͳ��Ϣ������ */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE == gstGmmSuspendCtrl.ucPreState))
            {

                if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
                }

                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);

                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

            }
            else
            {
                /* ������ģʽI�£�Gs�ڲ�����,���ҽ��벻����ʱ,��Ҫ�������ϵ�RAU�ؽ�Gs�� */
                /* PS access bar�Ѿ���Ԥ�������ж�,���Դ˴������ж�PS�����ֹ */
                if ((VOS_FALSE                            == Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai)))
                 && (VOS_TRUE                             == ucCsAttachAllow)
                 && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE                             == ucSimCsRegStatus)
                 && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_FALSE                            == ucCsRestrictFlg))
                {
                    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
                    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                    return;
                }

                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

#if (FEATURE_ON == FEATURE_LTE)
                /* L��ѡ��G,·����δ�ı䣬ISR���������RAUʱ��Ҫ����״̬��
                  ����Ϊregister no cell available�������޷���ҵ�� */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                 && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
                else
#endif
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                }


                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    switch (g_GmmGlobalCtrl.ucSpecProcHold)
                    {                                                               /* ������specific����                       */
                    case GMM_SERVICE_REQUEST_DATA_IDLE:
                    case GMM_SERVICE_REQUEST_DATA_CONN:
                        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                        break;
                    case GMM_SERVICE_REQUEST_SIGNALLING:
                        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
                        {
                            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);              /* ����PMMSMS_ERROR_IND                     */
                        }
                        if (GMM_MSG_HOLD_FOR_SM
                            ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                                    GMM_MSG_HOLD_FOR_SM))
                        {                                                           /* ����б�����SmDataReqԭ��                */
                            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_SuspWaitSys(): Clear cached SM data Req");

                            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &=
                                ~GMM_MSG_HOLD_FOR_SM;                               /* ���������־                             */
                            pAddr =
                                (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm; /* ��ȡSmDataReqԭ���ַ                    */
                            Gmm_MemFree(pAddr);                                     /* �ͷű����SM��Ϣ                         */
                        }
                        break;
                    default:
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:INFO: No Hold Procedure");
                        break;
                    }
                    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
                }
            }
        }
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_ComCmpLai
  Function : LAI�ıȽ�
  Input    : GMM_LAI_STRU   *pMsg       ָ��LAI��ָ��
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ��־��  2003.12.10  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_ComCmpLai(
                    GMM_LAI_STRU *pMsg                                          /* ָ��LAI��ָ��                            */
                    )
{
    VOS_UINT8 ucRet;                                                                /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ��ʼ��                                   */

    if (GMM_TRUE == Gmm_Com_CmpPlmnid(&pMsg->PlmnId))
    {                                                                           /* PLMN��ͬ                                 */
        if ((pMsg->aucLac[0]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0])
            &&(pMsg->aucLac[1]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1]))
        {                                                                       /* LAC��ͬ                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;                                                               /* ����                                     */
}

/***********************************************************************
  Module   : NAS_GMM_RcvMmAuthenticationFailureInd
  Function : ԭ��MMGMM_AUTHENTICATON_FAILURE_IND�Ľ��մ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.11  �°�����
  2.��    ��   : 2006��9��9��
    ��    ��   : sunxibo id:46746
    �޸�����   : �������ⵥ�ţ�A32D05604
  3.��    ��   : 2008��7��2��
    ��    ��   : l00107747
    �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��4��20��
    ��    ��   : l00130025
    �޸�����   : DTS2012031502528��GMM GPRS Suspension״̬û�д���LuRsltInd��
                 W->G Rej 11->WԭС��ʱ,û����Attach�����º���SMҵ��ʧ��
  6.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  7.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  8.��    ��   : 2013��10��05��
    ��    ��   : l65478
    �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��

  9.��    ��   : 2013��12��09��
    ��    ��   : z00234330
    �޸�����   : DTS2013120907910:MM��Ȩ������ܾ���,gmm״̬�������⡣
************************************************************************/
VOS_VOID NAS_GMM_RcvMmAuthenticationFailureInd(VOS_VOID)
{
    VOS_UINT8                           ucGmmPreState;
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
        case GMM_REGISTERED_INITIATED:
        case GMM_DEREGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NO_IMSI:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_UPDATE_NEEDED:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_REGISTERED_PLMN_SEARCH:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
            g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                       /* ��Ҫ��SM����Ӧ                           */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_FAIL); /* ֪ͨSM GMMע��ʧ��                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
            }
            if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            {                                                                       /* SMS�ڵȴ���Ӧ                            */
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                          /* ����PMMSMS_ERROR_IND                     */
                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }
            if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                       /* ��Ҫ��RABM����Ӧ                         */
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ����GMMRABM_REESTABLISH_CNF(failure)     */
            }
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ����                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcAuthenticationFailureInd:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */

            Gmm_HoldBufferFree();                                                   /* ���������Ϣ                             */

            gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_IMSI;
            ucGmmPreState = g_GmmGlobalCtrl.ucState;
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */

            if (GMM_REGISTERED_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                                      NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }

            else if (GMM_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);                                /* ����״̬�Ĺ�������                       */
            }
            else if (GMM_SUSPENDED_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);                                /* ����״̬�Ĺ�������                       */
            }
            else
            {
            }

            /* �����ر�־ */
            NAS_GMM_ClearIMSIOfUeID();

            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* ����״̬����ΪGU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOC INFO                  */
            break;                                                                  /* ����                                     */

        case GMM_NULL:
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* ����״̬����ΪGU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOC INFO                  */

        default:                                                                    /* �������                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcAuthenticationFailureInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;                                                                  /* ����                                     */
    }
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd
  Function : ԭ��MMCGMM_CM_SERVICE_IND�Ľ��մ���
  Input    : VOS_VOID  * pRcvMsg                ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.11  �°�����
     2.��    ��   : 2006��2��17��
       ��    ��   : liuyang id:48197
       �޸�����   : ���ⵥ�ţ�A32D01287����ӡ����
     3.��    ��   : 2008��08��1��
       ��    ��   : luojian id:00107747
       �޸�����   : �������ⵥAT2D04486/AT2D04822
     4.��    ��   : 2010��11��1��
       ��    ��   : z00161729
       �޸�����  : ���ⵥDTS2010111502913:ͨ��������,T3312��ʱ,GMM����period_updating RAU�ɹ�,���н������ַ���combined ralau with imsi attach,��˲��ᷢ��
     5.��    ��   : 2012��12��5��
       ��    ��   : t00212959
       �޸�����   : DTS2012120504420:CSFB��rau��#10�ܾ���ATTACH�ɹ���CS����������RAU
     6.��    ��   : 2011��12��28��
       ��    ��   : l00167671
       �޸�����   : �޸����ⵥDTS2012122001075,���ⵥ��������:
                    PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
                    �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
                    ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
                    ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
     7.��    ��   : 2013��2��4��
       ��    ��   : w00176964
       �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     8.��    ��   : 2013��10��29��
       ��    ��   : w00176964
       �޸�����   : VoLTE_PhaseII ��Ŀ�޸�:MM�Ƿ���ҵ������е��߼����ڸ���Ϣ��Ԥ������
     9.��    ��   : 2015��1��5��
       ��    ��   : z00161729
       �޸�����   : AT&T ֧��DAM�����޸�
******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd(
    VOS_VOID                           *pstRcvMsg                               /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* ����ԭ������ָ��                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* ǿ������ת��                             */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, begin */
    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {

    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        NAS_GMM_FreeGsmSysInfo();
    }
    else
    {
        NAS_GMM_ProcSavedGsmSysInfo();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        NAS_GMM_FreeWasSysInfo();
    }
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-29, end */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I     != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcCmServiceInd:NORMAL: It is not A+I(Gmm_RcvMmcCmServiceInd)");
        return;
    }

    if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
    {                                                                           /* ���CS����ͨ����                         */
        /* g_GmmRauCtrl.ucCsSpringRauFlg��ʶ�Ƿ�ΪCS������RAU��
           ֻ����CM SERVICE REJECTԭ��ֵΪ4ʱ��
           g_GmmRauCtrl.ucCsSpringRauFlg��ΪTRUE��
        */
        /*CSFB������RAU��#10�ܣ���Attach��״̬ΪGMM_ATTACH_NORMAL*/
        if( ( GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg )
            || ((VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
             || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))))
        {                                                                       /* CS����RAU                                */
             switch (g_GmmGlobalCtrl.ucState)
             {                                                                  /* ����״̬�ַ�                             */
             case GMM_REGISTERED_INITIATED:
             case GMM_ROUTING_AREA_UPDATING_INITIATED:
             case GMM_SERVICE_REQUEST_INITIATED:
                 NAS_GMM_RcvMmCsConnectInd_InProc(pstRcvMsg);                   /* ����RAU/SR�����еĴ���                   */
                 break;
             case GMM_REGISTERED_NORMAL_SERVICE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                 NAS_GMM_RcvMmCsConnectInd_RegNmlServ();                        /* ���ø�״̬�µĴ���                       */
                 break;
             default:
                 PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
                 break;
             }
             g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific ���̱�־          */
        }

        /*CSFB������RAU��#10�ܣ���Attach��״̬ΪGMM_ATTACH_NORMAL*/
        if (((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
          || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;           /* �����ǰ���е�specific ���̱�־          */
        }
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_Compare_Plmnid
  Function : �Ƚ�����PLMN ID �Ƿ���ͬ
  Input    : GMM_PLMN_ID_STRU *pPlmnId1
             GMM_PLMN_ID_STRU *pPlmnId2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE   ��ͬ
             GMM_FALSE  ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Plmnid(GMM_PLMN_ID_STRU *pPlmnId1,
                             GMM_PLMN_ID_STRU *pPlmnId2 )
{
    VOS_UINT8           i;                                                      /* ������ʱ����                             */

    for (i=0; i<3; i++)
    {                                                                           /* ��MCC�������ж�                          */
        if (pPlmnId1->aucMccDigit[i] != pPlmnId2->aucMccDigit[i])
        {                                                                       /* MCC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    if (pPlmnId1->ucMncCnt != pPlmnId2->ucMncCnt)
    {                                                                           /* MNC��������ͬ                            */
        return GMM_FALSE;                                                       /* ����GMM_FALSE                            */
    }

    for (i=0; i<pPlmnId1->ucMncCnt; i++)
    {                                                                           /* ��MNC�������ж�                          */
        if (pPlmnId1->aucMncDigit[i] != pPlmnId2->aucMncDigit[i])
        {                                                                       /* MNC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* ����GMM_TRUE                             */
}

/*******************************************************************************
  Module   : Gmm_Compare_Lai
  Function : LAI�ıȽ�
  Input    : GMM_LAI_STRU   *pLAI1
             GMM_LAI_STRU   *pLAI2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Lai(GMM_LAI_STRU *pLAI1,
                          GMM_LAI_STRU *pLAI2)
{
    VOS_UINT8 ucRet;                                                            /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ��ʼ��                                   */

    if (GMM_TRUE == Gmm_Compare_Plmnid(&pLAI1->PlmnId, &pLAI2->PlmnId))
    {                                                                           /* PLMN��ͬ                                 */
        if (  (pLAI1->aucLac[0] == pLAI2->aucLac[0])
            &&(pLAI1->aucLac[1] == pLAI2->aucLac[1]))
        {                                                                       /* LAC��ͬ                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Com_CmpRai
  Function : RAI�ıȽ�
  Input    : GMM_RAI_STRU   *pRAI1
             GMM_RAI_STRU   *pRAI2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Rai(GMM_RAI_STRU  *pRAI1,
                          GMM_RAI_STRU  *pRAI2)
{
    VOS_UINT8 ucRet = GMM_FALSE;                                                /* ���巵��ֵ                               */

    if (GMM_TRUE == Gmm_Compare_Lai(&pRAI1->Lai, &pRAI2->Lai))
    {                                                                           /* LAIһ��                                  */
        if (pRAI1->ucRac == pRAI2->ucRac)
        {                                                                       /* RACһ��                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Get_Location_info
  Function : ��ȡС����Ϣ��������
  Input    : VOS_VOID  * pRai1               С����Ϣ 1
             VOS_VOID  * pRai2               С����Ϣ 2
  Output   : VOS_UINT8 * pucLaiChgFlg        LAI�Ƿ�ı��־
             VOS_UINT8 * pucRaiChgFlg        RAI�Ƿ�ı��־
  NOTE     : ��
  Return   : ��
  History  :
     1. ŷ����  2009.02.11  �°�����
                ���ⵥ�ţ�AT2D08906��smartone UEû�д���attach״̬, �ͷ�����ҵ������
     2. ��    ��   : 2012��3��22��
        ��    ��   : z00161729
        �޸�����   : ֧��ISR�����޸�
     3. ��    ��   : 2012��7��17��
        ��    ��   : z00161729
        �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                     ��������rau
     4. ��    ��   : 2012��7��17��
        ��    ��   : z00161729
        �޸�����   : DTS2012073106360:ISR����CSFB�ض����CCO��GU,idle̬λ��������������RAU
     5. ��    ��   : 2012��09��08��
        ��    ��   : l65478
        �޸�����   : DTS012090302087,L->GUʱ,RAIû�иı�ʱ,GMM������RAU
     6.��    ��   : 2015��1��5��
       ��    ��   : z00161729
       �޸�����   : AT&T ֧��DAM�����޸�
     7. ��    ��   : 2016��3��2��
        ��    ��   : z00359541
        �޸�����   : DTS2016022908722: ��T3302��ʱ���Ĵ�����DAM����Ҫ�󱣳�һ��
******************************************************************************/
 VOS_VOID Gmm_Get_Location_Change_info(
    GMM_RAI_STRU                       *pRai1,
    GMM_RAI_STRU                       *pRai2,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg,
    VOS_UINT8                           ucNetMod
)
{
    VOS_UINT32                          ulT3302Status;

    ulT3302Status                = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    if (GMM_FALSE == Gmm_Compare_Rai(pRai1, pRai2))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        *pucRaiChgFlg = GMM_TRUE;
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Get_Location_Change_info, Gmm_Compare_Rai:rai not change");
        *pucRaiChgFlg = GMM_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
    {
        /* 3GPP 23401 4.3.5.6   Idle mode signalling reduction function:
           The Idle mode Signalling Reduction (ISR) function provides a
           mechanism to limit signalling during inter-RAT cell-reselection
           in idle mode (ECM-IDLE, PMM-IDLE, GPRS STANDBY states).
        */
        /* AT&T LTE-BTR-1-1824��LTE-BTR-1-1826��LTE-BTR-1-1828����Ҫ��
           GMM��GU��attach����Ӧ�򱻾ܴ�����������T3302��ʱ����������ϵͳ
           ��������L�º�����ֹͣ��L��ע��ʧ������disable lte������GU������
           ��ԭʧ��С��ʱ����T3302��ʱ������ps attach */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != NAS_MML_GetTinType())
         && (VOS_FALSE == ulT3302Status))

        {
            *pucRaiChgFlg = GMM_TRUE;
        }

        /* �������ģʽI,��L��ϵͳ��GU,��Ҫ�ж�CS ��LAI�Ƿ�ı䣬����ı���Ҫ��������rau */
        if (GMM_TRUE == NAS_GMM_IsCsLaiChangeNeedRegister(ucNetMod))
        {
            *pucRaiChgFlg = GMM_TRUE;
        }
    }

#endif

    if (GMM_FALSE == Gmm_Compare_Lai(&(pRai1->Lai), &(pRai2->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        *pucLaiChgFlg = GMM_TRUE;
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Get_Location_Change_info: LAI not Change");
        *pucLaiChgFlg = GMM_FALSE;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_PS_BAR
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: PS BAR�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
    3. ��    ��   : 2012��12��11��
       ��    ��   : w00176964
       �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
     4.��    ��   : 2013��2��4��
       ��    ��   : w00176964
       �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_PS_BAR(
    VOS_UINT8                           ucLaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (GMM_FALSE == ucLaiChgFlg))
        {
            if ( ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState ))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }

        }

        if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
        {

            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            return ucRst;
        }
        else if(GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            ucRst = GMM_FALSE;
        }
        else if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0)))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            ucRst = GMM_FALSE;
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
            ucRst = GMM_FALSE;
        }

        /* �����ǰҵ�����ޣ���������� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            Gmm_ComCnfHandle();
            GMM_BufferMsgDump();
        }
        else
        {
            GMM_BufferMsgResume();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoIndRelEstingLink
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: ucRaiChgFlg�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
    2. ��    ��   : 2010��10��28��
       ��    ��   : h44270
       �޸�����   : ���ⵥDTS2010091401278,����ģʽ�ı��û�з���PDP�ؽ����޸ĺ�����
    3. ��    ��   : 2010��10��28��
       ��    ��   : h44270
       �޸�����   : ���ⵥDTS2011071503390,��ʼפ����LAI1,��ѡ��LAI2,��ע�������
                    ����ѡ��LAI1��,MM������ע��,GMMû�з���ע��
    4. ��    ��   : 2013��03��07��
       ��    ��   : l00167671
       �޸�����   : ���ⵥDTS2013030502525,��RAI1����RAU�������ӳɹ�֮ǰ·���������RAI2
                          δ����RAU
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoIndRelEstingLink(VOS_VOID)
{
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340���������У�����·�ͷź��ٴ���ϵͳ��Ϣ */
        g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
        ucRst = GMM_FALSE;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                       /* �����������ڽ�����������                 */
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {                                                                   /* GMM_REGISTERED_INITIATED״̬             */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* ����ȴ�CNF��־                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific����               */
            ucRst = GMM_FALSE;
        }
        else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);*/

            /* GMM�ĸ���״̬��U1ʱ,GMMΪ��������;����GMMǨ�Ƶ�ATT-TO-UPDATE������3311���г��� */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                g_GmmGlobalCtrl.SysInfo.Rai = stGmmRai;
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                Gmm_TimerStart(GMM_TIMER_T3311);
            }
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* ����ȴ�CNF��־                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific����               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;          /* ����ȴ�CNF��־                          */

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;            /* �����ǰ���е�specific����               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: pRaiTemp�ĸ�ֵ
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(GMM_RAI_STRU         *pRaiTemp,
                                            VOS_VOID             *pRcvMsg
                                            )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */

    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* �õ�ԭ��ָ��                             */

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo��Ϊ��                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                          /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);                   /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);                  /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                          /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);                   /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);                  /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */
        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
              pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];               /* RAC                                      */
          }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_PreProcess_Handling
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: ��Ϣ�ַ�ǰ��Ԥ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2009��08��01��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��AT2D13412, ����GMM��������RAU�ؽ�Gs�����ĳ���������PS��ע����ж�������
     3.��    ��   : 2011��03��1��
       ��    ��   : w00176964
       �޸�����   : ���ⵥ�ţ�DTS2011022503955, [���������-�������Ż�˫ģ]�����ѿ���ָ���ѹ����У�����
                    �û��б��������ػ��Ȳ�����ֹͣ�������RPLMN�ɹ�������ǰС����ֹ��֧��CS/PS���������
                    ������δ����������Ҫ�ȴ���ʱ����ʱ�����쳣����
     4.��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
     5.��    ��   : 2012��8��14��
       ��    ��   : t00212959
       �޸�����   : DCM�����������������
     6.��    ��   : 2013��2��4��
       ��    ��   : w00176964
       �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     7.��    ��   : 2013��6��18��
       ��    ��   : l65478
       �޸�����   : ���ⵥ�ţ�DTS2013061406222,����RAUʱӦ���ж� CS��ҵ��״̬
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_PreProcess_Handling(VOS_UINT8                    ucNetMod,
                                                   VOS_UINT8                    ucRaiChgFlg,
                                                   MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                                   VOS_UINT8                   *pucDrxLengthChgFlg
                                                )
{
    VOS_UINT8                           ucRst = GMM_TRUE;
    VOS_UINT8                           ucCsChanged2UnBarFlg;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */
    if (GMM_TRUE == *pucDrxLengthChgFlg)
    {                                                                           /* ϵͳ��Ϣ�д���DRX length��Ϣ             */
        /* Modified by t00212959 for DCM�����������������, 2012-8-16, begin */
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* �洢DRX LENGTH                           */
        /* Modified by t00212959 for DCM�����������������, 2012-8-16, end */

        *pucDrxLengthChgFlg = GMM_FALSE;
    }

    ucCsChanged2UnBarFlg            =   pSysInfoInd->ucCsChanged2UnBarFlg;
    ucCsRestrictionFlg              =   NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg              =   NAS_MML_GetPsRestrictRegisterFlg();
    gstGmmCasGlobalCtrl.ucSysRauFlg = ucRaiChgFlg;
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    else
    {
        /* PS��ע�ᣬCS���bar����bar, ��Gs����δ����,��ʱGMM��Ҫ��������RAU�ؽ�Gs������ */
        if (   (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            && (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            && (VOS_TRUE == ucCsAttachAllow)
            && (VOS_TRUE == ucPsAttachAllow)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            if ( (VOS_FALSE == ucPsRestrictionFlg)
              && (VOS_FALSE == ucCsRestrictionFlg)
              && (VOS_TRUE == ucCsChanged2UnBarFlg)
              && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
              && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                ucRst = GMM_FALSE;
            }
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_CSPS_INFO
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: CSPS_INFO�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_CSPS_INFO(MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                        VOS_UINT8                   *pucNetMod
                                            )
{
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
        if (0 != pSysInfoInd->ulPsInfoSize)
        {
            if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
            {
                *pucNetMod = GMM_NET_MODE_I;
            }
            else
            {
                *pucNetMod = GMM_NET_MODE_II;
            }
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is supported");
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* ���õ�ǰС����֧��GPRS��־                */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
        }
    }
    else
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* ���õ�ǰС����֧��GPRS��־                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: ucNetModeChange����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1. ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2010��10��28��
        ��    ��   : h44270
        �޸�����   : ���ⵥDTS2010091401278,����ģʽ�ı��û�з���PDP�ؽ����޸ĺ�����
     3. ��    ��   : 2010��12��01��
        ��    ��   : z00161729
        �޸�����  : DTS2010111903590:LAI��RAI��CELL��δ��ֻ������ģʽ�����ı䣬UE����RAU��LAU����˲���
     4. ��    ��   : 2012��03��17��
        ��    ��   : s46746
        �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
(
    VOS_UINT8                           ucNetMod,
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfoInd,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        if ((GMM_TRUE == *pucLaiChgFlg)
         || (GMM_TRUE == *pucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
                && (0x10 != g_GmmGlobalCtrl.ucState))
            {                                                                       /* �û�ģʽΪA,�����Ѿ�ע��                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {/* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                     && (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                    {
                        (VOS_VOID)Gmm_RcvMmcSysInfoIndRelEstingLink();
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                    else
                    {
                        /* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                        /* ͬϵͳ��С��ϵͳ��Ϣ���� */
                        Gmm_ComNetModeChange(pSysInfoInd);                              /* ��������ģʽ�任�Ĺ�������               */
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                }
            }
        }
        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_State_Distribute
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: ��Ϣ��״̬����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2009��07��23��
        ��    ��   : L65478
        �޸�����  : ���ⵥ��:AT2D13173,GMM���յ�ϵͳ��Ϣ�󣬸�MMC������NO SERVICE������MMC������������ʱ��
    3. ��    ��   : 2010��12��24��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
    4. ��    ��   : 2011��10��31��
       ��    ��   : w00166186
       �޸�����   : �б��ѹ��̣�GMMû���ϱ�ϵͳ��Ϣ�������б���ʧ��
    5. ��    ��   : 2014��06��15��
       ��    ��   : s00217060
       �޸�����   : DTS2014061003286:TD2G��ѡ��G��RAU�����У��û�ָ����TD�����磬���粻��Ӧ����ҵ��accept
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_State_Distribute(
                                  VOS_VOID    *pRcvMsg,                                 /* ��Ϣָ��                                 */
                                  VOS_UINT8    ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8    ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8    ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = ucRaiChgFlg;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg = ucDrxLengthChgFlg;

    /* ��ԭ��MMCGMM_SYS_INFO_IND����״̬�ַ� */
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvMmcSysInfoInd_RegInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvMmcSysInfoInd_DeregInit(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvMmcSysInfoInd_RauInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvMmcSysInfoInd_ServReqInit(pRcvMsg,
                                         ucRaiChgFlg,
                                         ucDrxLengthChgFlg,
                                         ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvMmcSysInfoInd_DeregNmlServ(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(pRcvMsg,
                                             ucRaiChgFlg,
                                             ucDrxLengthChgFlg,
                                             ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:

        Gmm_RcvMmcSysInfoInd_RegNmlServ(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;

    case GMM_REGISTERED_PLMN_SEARCH:

        NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_REGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcSysInfoInd_RegUpdtNeed(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(pRcvMsg,
                                           ucRaiChgFlg,
                                           ucDrxLengthChgFlg,
                                           ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvMmcSysInfoInd_SuspWaitSys(pRcvMsg,ucRaiChgFlg,ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_IMSI:
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd
  Function : ԭ��MMCGMM_SYS_INFO_IND�Ľ��մ���
  Input    : VOS_VOID *pRcvMsg  ������Ϣʹ�õ�ͷ��ַ����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2.��    ��   : 2006��9��9��
      ��    ��   : sunxibo id:46746
      �޸�����   : �������ⵥ�ţ�A32D05653
    3.��    ��   : 2006��10��9��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D05744
    4.��    ��   : 2006��11��20��
      ��    ��   : s46746
      �޸�����   : �������������ⵥ�ţ�A32D07433
    5.��    ��   : 2007��1��26��
      ��    ��   : liurui id:40632
      �޸�����   : �������ⵥ�ţ�A32D08577
    6.��    ��   : 2007��03��20��
      ��    ��   : x51137
      �޸�����   : A32D09192
    6.��    ��   : 2007��06��22��
      ��    ��   : l60022475
      �޸�����   : A32D11911
    7.��    ��   : 2007��10��26��
      ��    ��   : l39007
      �޸�����   : A32D13207
    8.��    ��   : 2007-10-26
      ��    ��   : hanlufeng
      �޸�����   : A32D13172
    9.��    ��   : 2007��12��15��
      ��    ��   : l00107747
      �޸�����   : ���ⵥ��:A32D13897
   10.��    ��   : 2009��01��15��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
   11.��    ��   : 2009��03��18��
      ��    ��   : l65478
      �޸�����   : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
   12.��    ��   : 2009��9��03��
      ��    ��   : l65478
      �޸�����   : created AT2D14239,detach��ɺ�,�ٴη���ATTATCH REQʱ,GASʹ�þɵ�TLLI������TBF��������,û�м�ʱʹ���µ�TLLI,����MS��������ά����TLLI��һ��,�Ӷ�����GAS��ΪTLLI��ƥ�䶪���˽�������TBF��ָ������,���յ�������ʧ��
   13.��    ��   : 2010��8��14��
      ��    ��   : s46746
      �޸�����   : DTS2010073001405,G2W��ϵͳ��ѡ�󣬲����2����ȥָ�ɶ��ǹ����2
   14.��    ��   : 2010��10��28��
      ��    ��   : h44270
      �޸�����   : ���ⵥDTS2010091401278,����ģʽ�ı��û�з���PDP�ؽ����޸ĺ�����
   15.��    ��   : 2011��02��21��
      ��    ��   : w00176964
      �޸�����   : ���ⵥ��: DTS2011021102016. [V3C02B020][BG��]BG�ѳɹ���ָ����ʧ�ܺ󣬻��򱣻���ʱ����ʱ
                   �ٴ�����BG��
   16.��    ��   : 2011��03��1��
      ��    ��   : w00176964
      �޸�����   : ���ⵥ�ţ�DTS2011022503955, [���������-�������Ż�˫ģ]�����ѿ���ָ���ѹ����У�����
                   �û��б��������ػ��Ȳ�����ֹͣ�������RPLMN�ɹ�������ǰС����ֹ��֧��CS/PS���������
                   ������δ����������Ҫ�ȴ���ʱ����ʱ�����쳣����
   17.��    ��   : 2011��7��13��
      ��    ��   : w00176964
      �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�
   18.��    ��   : 2011��7��13��
      ��    ��   : l00130025
      �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
   19.��    ��   : 2011��5��20��
      ��    ��   : f00179208
      �޸�����   : �������ⵥ�ţ�DTS20110517005731,����������T3212��ʱ��ԭ��С����NMO1��
                   UE�ظ��Ǻ��С����֧��GPRS��ͬLA��û����������LAU
   20.��    ��   : 2011��4��6��
      ��    ��   : c00173809
      �޸�����   : �������ⵥ�ţ�DTS2011032900575,NMO1������RAU������NMO1��֧��
                   GPRS��С���У�T3312��ʱû�з���������LAU
   21.��    ��   : 2011��12��2��
      ��    ��   : s46746
      �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
   22.��    ��   : 2012��03��20��
      ��    ��   : l00130025
      �޸�����   : DTS2012030105247,NASֻ������ʵ�ʷ����Ȩʱ,֪ͨW SecurityKey�������������WAS���ö�Ӧ�ӿڻ�ȡ
   23.��    ��   : 2012��4��17��
      ��    ��   : z00161729
      �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
   24.��    ��   : 2012��7��17��
      ��    ��   : z00161729
      �޸�����  : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                    ��������rau
   25.��    ��   : 2012��8��14��
      ��    ��   : t00212959
      �޸�����   : DCM�����������������
   26.��    ��   : 2011��12��28��
      ��    ��  : l00167671
      �޸�����  : �޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
                 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
                 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
                 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
   27.��    ��   : 2013��6��11��
      ��    ��   : z00234330
      �޸�����   : DTS2013061152841,��bar��С������bar��С��,GMM֪ͨwrr������Ϣ����Я����plmn idΪ0
   28.��    ��   : 2014��1��26��
      ��    ��   : w00242748
      �޸�����   : DTS2014011800247:����GMM��ACC BARʱ��GMM��MMC���͵�PS��ע��ԭ��ֵ
   29.��    ��   : 2014��10��22��
      ��    ��   : z00161729
      �޸�����   : DTS2014102109190:��gmm��mm��ȫ�ֱ��������ӿ�ά�ɲ���Ϣ
   30.��    ��   : 2014��12��25��
      ��    ��   : w00167002
      �޸�����   : DTS2014122201960:��L��SRVCC HO��G��HO��W,RABM�����ؽ�����������
                   ����RAU�������յ�ϵͳ��Ϣ���ٴη���RAU,��������REL����·������
                   �������޸�Ϊ��HO������������ʱ����ϵͳ��Ϣ��
   31.��    ��   : 2015��1��15��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
   32.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd(
                          VOS_VOID *pRcvMsg                                     /* ������Ϣʹ�õ�ͷ��ַ����                 */
                          )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucDrxLengthChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod = g_GmmGlobalCtrl.ucNetMod;
    VOS_UINT32                   ulNewCellId;
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    VOS_UINT8                           ucSimPsRegStatus;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();
    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* �õ�ԭ��ָ��                             */

    NAS_GMM_LogGmmCtxInfo();

    Gmm_SndSmSysInfoInd(MMCGMM_SGSN_RELEASE99_ONWARDS);

    /* �յ�Wģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, ���ָ�RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_FALSE,
                                VOS_TRUE);

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_FALSE;

    NAS_GMM_SuspendLlcForInterSys();

    g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;

    Gmm_RcvMmcSysInfoInd_CSPS_INFO(pSysInfoInd, &ucNetMod);

    /* ��Ǩ��Wģʽ���ǣ���Ҫ�������ָ���־����Ϊ��ָ�����ʱ��Ҫʹ�ô˱�־ */
    if(NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
    {
        gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;

        NAS_GMM_SndMmcCipherInfoInd();
    }
    /* ֮ǰ���쳣�ͷ�,�յ�ϵͳ��Ϣ����������־ */
    if (RR_REL_CAUSE_ABORT_RR_NORMAL == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd:ERROR: Alloc mem fail.");
        return;
    }

    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pRcvMsg);

    /*�����յ�ϵͳ��Ϣ��G��ѡ��W���������Ҫ�����ԭ�����Ӵ��ڱ��
 */
    /*�˴�������Ҫ��С����BAR�Ĵ���֮ǰ����ΪС����BAR�᷵��
 */
    if((NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
       &&((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
          ||(GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)))
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);
        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);
#if (FEATURE_ON == FEATURE_LTE)
        /* L�¶�����������GU����Ҫ�ж������ISR����󼤻��pdp�����ģ���Ҫȥ����ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
#endif
    }

    /* ��ѡ��PS��BARRED��С��,������ģʽI,����T3312��ʱ */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend�������յ�T3312��ʱ����PS barred,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ( (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
               && (GMM_NET_MODE_I == ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;

    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    Gmm_Get_Location_Change_info(pRaiTemp, &stOldRai, &ucLaiChgFlg, &ucRaiChgFlg, ucNetMod);

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoInd->ulForbiddenMask) )
    {
        ucRst = Gmm_RcvMmcSysInfoInd_PS_BAR(ucLaiChgFlg);
        if(GMM_FALSE == ucRst)
        {
            g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
            g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            Gmm_MemFree(pRaiTemp);
            return;
        }
    }


    ulNewCellId = pSysInfoInd->ulCellId;

    g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;

    if (ulNewCellId != g_GmmGlobalCtrl.SysInfo.ulCellId)
    {
        g_GmmGlobalCtrl.SysInfo.ulCellId = ulNewCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_TRUE;
    }




    if (MMC_GMM_SYS_MSK_PS_DRX ==(pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PS_DRX))
    {
        /* Modified by t00212959 for DCM�����������������, 2012-8-16, begin */
        /* ϵͳ��Ϣ�д���DRX length��Ϣ             */
        if (NAS_MML_GetWSysInfoDrxLen() != (VOS_UINT8)pSysInfoInd->ulPsDrxLength)
        {                                                                       /* DRX LENGTH�ı�                           */
            ucDrxLengthChgFlg = GMM_TRUE;                                       /* ����DRX length�仯��־                   */
        }
        /* Modified by t00212959 for DCM�����������������, 2012-8-16, end */
    }

    if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı����DRX�ı�                        */
        ucRst = Gmm_RcvMmcSysInfoIndRelEstingLink();
        if(GMM_FALSE == ucRst)
        {
            NAS_GMM_SaveWasSysInfo(pSysInfoInd);
            Gmm_MemFree(pRaiTemp);
            return;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling(ucNetMod, pSysInfoInd, &ucLaiChgFlg, &ucRaiChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    }
    else
    {
        /*  suspend�������յ�T3312��ʱ����GPRS NOT SUPPORT,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_PreProcess_Handling(ucNetMod, ucRaiChgFlg, pSysInfoInd, &ucDrxLengthChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }

    Gmm_RcvMmcSysInfoInd_State_Distribute(pRcvMsg,
                                          ucRaiChgFlg,
                                          ucDrxLengthChgFlg,
                                          ucLaiChgFlg);

    Gmm_MemFree(pRaiTemp);

    /* ��·�ͷſ���: �յ�ϵͳ��Ϣ���ڴ�����Ϻ���������̵�Retry��־ */
    g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_FALSE;
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_FALSE;
    g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcLteSysInfoInd
 ��������  : ����ID_MMC_GMM_LTE_SYS_INFO_INDԭ��
 �������  : MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��26��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�
  3.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
  4.��    ��   : 2012��10��25��
    ��    ��   : t00212959
    �޸�����   : DTS2012102403382,GU��L��,����ͷ�ԭ��ֵ,�����ֻص�GU������RAU
  5.��    ��   : 2015��11��4��
    ��    ��   : c00318887
    �޸�����   : DTS2015110401863: w������rabm�ؽ�����L�󣬱�����ʧ��
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcLteSysInfoInd(
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    /* ��Ǩ��Lģʽ�£���Ҫ�������ָ���־����Ϊ��ָ�����ʱ��Ҫʹ�ô˱�־ */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
    gstGmmCasGlobalCtrl.ucGprsCipher       = VOS_FALSE;

    gstGmmSuspendCtrl.ucGetLteSecContext   = VOS_FALSE;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* �յ�Lģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, ������RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* ����ͷ�ԭ��ֵ */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;  

}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcLmmStatusInd
 ��������  : ����MMCGMM_LMM_STATUS_INDԭ��
 �������  : MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��: 2012��03��02��
    ��    ��: l00130025
    �޸�����: DTS2012022102014:L->G->L->G��û�����·���TLLI,����G��RAU������ImplicityDetached
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcLmmStatusInd(
    MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
)
{
    switch (pstLmmStatusInd->ulConnState)
    {
    case MMC_LMM_CONN_ESTING:
    case MMC_LMM_CONNECTED_SIG:
    case MMC_LMM_CONNECTED_DATA:

        gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_LTE;

        break;

    default:
        NAS_INFO_LOG1(WUEPS_PID_GMM, "pstLmmStatusInd->ulConnState =",pstLmmStatusInd->ulConnState);
        break;

    }

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsCsLaiChangeNeedRegister
 ��������  : ����ģʽI,CS��LAI�ı��Ƿ���Ҫ��������ע��
 �������  : ucNetMod - ����ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE-��Ҫ
             VOS_FALSE-����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��: 2012��07��18��
   ��    ��: z00161729
   �޸�����: DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
             ��������rau

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsCsLaiChangeNeedRegister(
    VOS_UINT8                           ucNetMod
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          ucMsMode;
    VOS_UINT8                           ucCsSimRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    ucMsMode           = NAS_MML_GetMsMode();
    ucCsSimRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
     && (GMM_NET_MODE_I == ucNetMod)
     && (NAS_MML_MS_MODE_PS_CS == ucMsMode)
     && (VOS_TRUE == ucCsSimRegStatus)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucCsAttachAllowFlg))
    {
        return GMM_TRUE;
    }

    return GMM_FALSE;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_GMM_StopReadyTimer_DeregStat
 ��������  : ���Gmm״̬,��Deregister״̬,ֹͣReadyTimer,֪ͨ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��14��
   ��    ��   : l00130025
   �޸�����   : ���ⵥDTS2011091906272,Dereg״̬��û��ֹͣReadyTimer

 2.��    ��   : 2013��08��16��
   ��    ��   : l65478
   �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
*****************************************************************************/
VOS_VOID NAS_GMM_StopReadyTimer_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SetIdleSrvState_DeregStats
 ��������  : ���Gmm״̬,��Deregister״̬,������״̬�޸�ΪIdle,֪ͨGAS
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��14��
   ��    ��   : l00130025
   �޸�����   : ���ⵥDTS2011091906272,Dereg״̬��û�н��뵽Idle̬

*****************************************************************************/
VOS_VOID NAS_GMM_SetIdleSrvState_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        if (GMM_AGB_GPRS_IDLE != gstGmmCasGlobalCtrl.GmmSrvState)
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
             NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

}

/*******************************************************************************
Module   : Gmm_ComStaChg
Function : Ǩ���INITIATED״̬�Ĺ�������
Input    : VOS_UINT8 ucState Ǩ��״̬
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. ��־��  2003.12.18  �¹�����
2. ��    ��   : 2006��9��9��
   ��    ��   : sunxibo id:46746
   �޸�����   : �������ⵥ�ţ�A32D05604
3. ��    ��   : 2009��07��23��
   ��    ��   : L65478
   �޸�����  : ���ⵥ��:AT2D13173,GMM���յ�ϵͳ��Ϣ�󣬸�MMC������NO SERVICE������MMC������������ʱ��
4.��    ��   : 2011��7��25��
  ��    ��   : h44270
  �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
5.��    ��   : 2011��12��14��
  ��    ��   : l00130025
  �޸�����   : ���ⵥDTS2011091906272,Dereg״̬��û�н��뵽Idle̬,û��ֹͣReadyTimer
6.��    ��   : 2012��2��18��
  ��    ��   : w00181244
  �޸�����   : ���ⵥDTS2012021305344,cgreg���ϱ����⣬��������״̬�ϱ���ע��״̬�ϱ���˳��
7.��    ��   : 2012��3��28��
  ��    ��   : z00161729
  �޸�����   : ISR�޸�
8.��    ��   : 2012��9��07��
  ��    ��   : l00171473
  �޸�����   : DTS2012081701006, ���GMM״̬�Ŀ�ά�ɲ���Ϣ
9.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
10.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
11.��    ��   : 2014��05��22��
   ��    ��   : W00242748
   �޸�����   : DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS
12.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Gmm_ComStaChg(VOS_UINT8 ucState)
{

    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucState);
    }
    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucState);
#endif

    g_GmmGlobalCtrl.ucState = ucState;                                          /* ����ҪǨ���״̬                         */

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_PrintState();

    Gmm_SndSmStatusInd();

    Gmm_SndSmsServiceStatusInd();

    if(VOS_TRUE == g_GmmGlobalCtrl.ucNeedChgServiceStatus)
    {
        Gmm_Com_ServiceStatus_Handle();                                         /* ֪ͨMMC����״̬                          */
    }
    /* 3GPP 24.008 4.7.2.2�½�������
      If the periodic routeing area update timer expires and the MS is in state
      GMM-REGISTERED.NO-CELL-AVAILABLE, the MS shall start the GERAN/UTRAN Deactivate
      ISR timer T3323. The MS shall initiate the routeing area updating procedure
      and stop the timer T3323 when the MS enters the state GMM-REGISTERED.NORMAL-SERVICE
      before timer T3323 expires. */

    if (GMM_REGISTERED_NORMAL_SERVICE == ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }


    if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ״̬Ǩ��GMM_DEREGISTERED_NO_IMSI         */
        if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
        {                                                                       /* sim����Ч                                */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;
        }
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_TimerStop(GMM_TIMER_T3319);                                         /* ֹͣ3319                                 */
    }


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


}

/*******************************************************************************
  Module   : Gmm_RcvMmRegisterInitiation
  Function : ԭ��MMGMM_REGISTER_INITIATION�Ľ��մ���
  Input    : VOS_VOID *pMsg  ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmRegisterInitiation(
    VOS_VOID                           *pMsg                                    /* ָ����Ϣ��ָ��                           */
)
{
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
    {                                                                           /* A+I                                      */
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* ���ò�ͬ״̬�µĴ���                     */
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_RcvMmcRegisterInitiation_ServReqInit(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch();
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcRegisterInitiation:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
        }
    }
    else
    {
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_ServReqInit
  Function : ��GMM_SERVICE_REQUEST_INITIATED״̬��
             �յ�ԭ��MMCGMM_REGISTER_INITIATION�Ĵ���
  Input    : VOS_VOID *pMsg  ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
    3. ��    ��   : 2010��11��24��
       ��    ��   : ��ë 00166186
       �޸�����   : �������ⵥ��DTS2010112205253,DEFAULT��֧���Ի����ҵ������жϣ������ڴ�й©

*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_ServReqInit(
                                              VOS_VOID *pMsg                        /* ָ����Ϣ��ָ��                           */
                                              )
{
    MMCGMM_REGISTER_INITIATION_STRU   *ptr;

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* �����������ڽ�����������                 */
        ptr = (MMCGMM_REGISTER_INITIATION_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_REGISTER_INITIATION_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcRegisterInitiation_ServReqInit:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_REGISTER_INITIATION_STRU));

        if (GMM_MSG_HOLD_FOR_RAU ==
            (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* ����Ϣ������־                           */

        return;
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask
            &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                          /* ���ԭ��ȴ���־                         */
    }
    g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;                /* �������жϵ�SR����                       */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                                   /* ����follow on��־                        */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);                   /* ����RAU                                  */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch
  Function : ��GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH״̬��
             �յ�ԭ��MMCGMM_REGISTER_INITIATION�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
    2.��    ��   : 2008��7��23��
      ��    ��   : luojian id:107747
      �޸�����   : �������ⵥ��AT2D04627/AT2D04237
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */
    /*
    3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
    MS is in substate ATTEMPTING-TO-ATTACH and
        - expiry of timer T3302;
        - a new routing area is entered; or
        - an attach is triggered by CM sublayer requests.
    */
    if ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState )
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
    }
    Gmm_AttachInitiate(GMM_ATTACH_COMBINED);                                                       /* ����attach                               */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
  Function : ��GMM_REGISTERED_NORMAL_SERVICE/ATTEMPTING_TO_UPDATE_MM/
             ATTEMPTING_TO_UPDATE״̬���յ�ԭ��MMCGMM_REGISTER_INITIATION�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */
    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter ��0                  */
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

    return;
}

/*******************************************************************************
  Module   : Gmm_ComUnrealProc
  Function : �����̵������жϴ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : VOS_UINT8   ucGmmAction   ����������
  History  :
    1. ��־��  2004.03.16  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_ComUnrealProc(VOS_VOID)
{
    VOS_UINT8       ucGmmAction = 0;                                                /* ����ֲ�����                             */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucGmmAction = GMM_ATTACH_NORMAL;
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        ucGmmAction = GMM_RAU_NORMAL;
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        {
            ucGmmAction = GMM_ATTACH_NORMAL;
        }
        else
        {
            ucGmmAction = GMM_RAU_NORMAL;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComUnrealProc:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return ucGmmAction;
}
/*******************************************************************************
  Module   : Gmm_ComGetFollowOnFlg
  Function : ��ȡGmm��FollowOn��־
  Input    : ��
  Output   : FollowOn��־
  NOTE     : ��
  Return   : VOS_UINT8   Gmm��FollowOn��־
  History  :
        1.  ��    ��   : 2008��11��15��
            ��    ��   : l00130025
            �޸�����   : ���ⵥ�ţ�AT2D06602,���GSMģʽ�¶�MMC������Ϣ�Ĵ���
*******************************************************************************/
VOS_UINT8 Gmm_ComGetFollowOnFlg(VOS_VOID)
{
    return  g_GmmGlobalCtrl.ucFollowOnFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ExistBufferService
 ��������  : �ж�gmm�Ƿ��л���ҵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ�л���ҵ��
             VOS_FALSE  ��ʾû�л���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��2��25��
    ��    ��   : z00161729
    �޸�����   : DTS2011021604439:cs only����bg�ѳɹ�����ָ���ѹ����з�������ʧ��

*****************************************************************************/
VOS_BOOL NAS_GMM_IsExistBufferService(VOS_VOID)
{
    if ((GMM_MSG_HOLD_FOR_SM == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     || (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_PAGING == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        return  VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_GMM_IsFollowOnPend() )
    {
        return  VOS_TRUE;
    }

    /* �����ж��Ƿ������� */

    return  VOS_FALSE;

}
/*******************************************************************************
  Module   : Gmm_ComForbiddenList
  Function : ���ϱ�ϵͳ��Ϣ��forbidden�б�Ĵ���
  Input    : VOS_UINT32   ulForbiddenMask    ����forbidden�б������
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.17  �¹�����
    2. ��־��  2005.02.21  MM_MT_BUG_003��Ӧ
    3. ��    ��   : 2008��12��15��
       ��    ��   : l00130025
       �޸�����  : ���ⵥ��:AT2D07408,Gmm״̬�ж�

    4.��    ��   : 2010��11��27��
      ��    ��   : zhoujun /40661
      �޸�����   : ��������������GMM����������,ɾ��GMM������
*******************************************************************************/
VOS_VOID Gmm_ComForbiddenList(
                          VOS_UINT32   ulForbiddenMask                               /* ����forbidden�б������                  */
                          )
{
    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ȴ������                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ���ԭ��ȴ���־                         */
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* ����״̬�Ĺ�������                       */
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* ����״̬�Ĺ�������                       */
    }

    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;                          /* ���������̱�־                           */
    g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComForbiddenList:INFO: specific procedure ended");
    return;
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_NotSupportGprs_Handling
  Function : Gmm_ComNetModeChange �����Ӷ�: ��֧��GPRS�Ĵ���
  Input    : VOS_UINT8   ucNetMod
             VOS_UINT8   ucLaiChgFlg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.ŷ���� 2009.06.11  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013081400197,T3314��ʱ��,������ֹ��ǰ��ע�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_NotSupportGprs_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucLaiChgFlg)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    g_GmmReqCnfMng.ucCnfMask = 0;

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */
    Gmm_ComCnfHandle();
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_NotSupportGprs_Handling:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
        return;
    }

    if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
    }

    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
    }

    if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* ͣT3312                                  */
    }

    else
    {
        if (GMM_TRUE == ucLaiChgFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }

        else
        {
            if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                == g_GmmGlobalCtrl.ucState)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* ͣT3312                                  */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }

            else
            {
                if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);                                /* ��T3312                                  */
                }
            }
        }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_I2II_Handling
  Function : Gmm_ComNetModeChange �����Ӷ�: ����ģʽ I => II �Ĵ���
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.11  �¹�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_I2II_Handling(
                                                  VOS_UINT8 ucNetMod,
                                                  VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /*
        Imsi Detach�����д�����ģʽI�䵽����ģʽII����ֹ��Detach����Ϊ
        �˴�Detachʧ�ܡ���Ϊ�仯������ģʽII��PS�򲻿��ܷ���Imsi Detach
        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        /*
        Combined GPRS/IMSI Detach����������ģʽ��I�仯��II��
        ��¼���жϵ�����ΪPs Detach����Ϊ����ģʽII�²��ܷ���
        Combined GPRS/IMSI Detach.
        */
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_DETACH_NORMAL;                     /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* ͣT3310                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_I2II_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_II2I_Handling
  Function : Gmm_ComNetModeChange �����Ӷ�: ����ģʽ II => I �Ĵ���
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.ŷ���� 2009.06.11  �¹�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2013��7��19��
    ��    ��   : w00167002
    �޸�����   : DTS2013071900239:W������ģʽI,����ע��PS only�ɹ���CSʧ��ԭ��
                    #17,����ģʽ��I--->II,��ʱ��Ӧ��������ATTACH.
                    �����ʱ��Ȼ������ģʽI,���û�����ΪPS ONLY,��Ҳ���÷���
                    ����ATTACH.
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_II2I_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */



        /* ����CS��ֹע��ʱ�򣬲�������ATTACH */
        if ( VOS_FALSE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(
                                        GMM_COMBINED_RALAU_WITH_IMSI_ATTACH
                                          );
        }
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* ͣT3310                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_II2I_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Fill_Rai
  Function : Gmm_ComNetModeChange �����Ӷ�: ��ָ��pRaiTemp��ֵ
  Input    : GMM_RAI_STRU                *pRaiTemp,
             MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.11  �¹�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Fill_Rai(
                          GMM_RAI_STRU                *pRaiTemp,
                          MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
                          )
{
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo��Ϊ��                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                      /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);               /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);              /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                      /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);               /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);              /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */

        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }

    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
            pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];             /* RAC                                      */
          }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange
  Function : ��������ģʽ�任�Ĺ�������
  Input    : VOS_VOID  *pMsg                    ָ����Ϣ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.17  �¹�����
    2.��    ��   : 2008��7��18��
      ��    ��   : luojian 00107747
      �޸�����   : �������ⵥ�ţ�AT2D03887
    3.��    ��   : 2010��8��14��
      ��    ��   : ŷ����
      �޸�����   : DTS2010081203473,�仯С����RAUʧ�ܺ���������T3302��������T-
                   3311��ʱ��
    4. ��    ��   : 2012��7��17��
       ��    ��   : z00161729
       �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                    ��������rau
     5.��    ��   : 2012��8��14��
       ��    ��   : t00212959
       �޸�����   : DCM�����������������
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange(VOS_VOID  *pMsg)
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp    = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: alloc rai temp memory fail.");
        return;
    }

    Gmm_ComNetModeChange_Fill_Rai(pRaiTemp, pSysInfoInd);

    if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
    {
        ucNetMod = GMM_NET_MODE_I;
    }
    else
    {
        ucNetMod = GMM_NET_MODE_II;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, ucNetMod))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    /* Modified by t00212959 for DCM�����������������, 2012-8-16, begin */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* �洢DRX LENGTH                           */
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-16, end */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_ComNetModeChange_NotSupportGprs_Handling(ucNetMod, ucLaiChgFlg);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* ����ģʽ��� I->II                       */
        Gmm_ComNetModeChange_Netmode_I2II_Handling(ucNetMod, ucRaiChgFlg);
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        Gmm_ComNetModeChange_Netmode_II2I_Handling(ucNetMod, ucRaiChgFlg);
    }

    Gmm_MemFree(pRaiTemp);
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange
  Function : ��������ģʽ�任�Ĺ�������
  Input    : VOS_VOID  *pMsg                    ָ����Ϣ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��       2004.03.17  �¹�����
  2.��    ��   : 2010��8��14��
    ��    ��   : ŷ����
    �޸�����   : DTS2010081203473,�仯С����RAUʧ�ܺ���������T3302��������T-
                 3311��ʱ��
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4. ��    ��   : 2012��7��17��
     ��    ��   : z00161729
     �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                  ��������rau
  5.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
  6.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013081400197,T3314��ʱ��,������ֹ��ǰ��ע�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChangeGsm(VOS_VOID  *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfoInd;
    VOS_UINT8                           ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                           ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                       *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                           ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST         *ptr;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    if (((GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* ���ڽ�����                               */
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* ����Ϣ������־                           */
        return;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;                /* �洢��Ϣ�׵�ַ�� ulMsgAddrForAttach      */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;        /* ����Ϣ������־                           */
        return;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
          return;
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* ��дRAC */
    pRaiTemp->ucRac = pSysInfoInd->ucRac;
    /* ��дLAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfoInd->usLac;       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfoInd->usLac >> 8);
    /* ��дPLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMcc & 0x0F);             /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 8) & 0x0F);      /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 16) & 0x0F);     /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMnc & 0x0F);             /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 8) & 0x0F);      /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 16) & 0x0F);     /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                       /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                  /* MNC Degit count                          */
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, pSysInfoInd->ucNetworkOperationMode))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    ucNetMod = pSysInfoInd->ucNetworkOperationMode;

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenFlg;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    /* Modified by t00212959 for DCM�����������������, 2012-8-16, begin */
    /* G��ϵͳ��Ϣ����DRX LENGTH ��ɾ��*/
    /* Modified by t00212959 for DCM�����������������, 2012-8-16, end */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        if (GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChangeGsm:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
            Gmm_MemFree(pRaiTemp);
            return;
        }
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* ����״̬�Ĺ�������                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* ����״̬�Ĺ�������                       */
        }
        if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }
        else
        {
            if (GMM_TRUE == ucLaiChgFlg)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* ͣT3312                                  */
            }
            else
            {
                if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                    == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);                             /* ͣT3312                                  */

                    NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
                }
                else
                {
                    if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                    {
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* ��T3312                                  */
                    }
                }
            }
        }
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* ����ģʽ��� I->II                       */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
            return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */

        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* ����ģʽGSM I�ı䵽����ģʽGSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* ����ģʽGSM II�ı䵽����ģʽGSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_I == ucNetMod))
    {/* ����ģʽGSM III�ı䵽����ģʽGSM I */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_II == ucNetMod))
    {/* ����ģʽGSM III�ı䵽����ģʽGSM II */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    Gmm_MemFree(pRaiTemp);
    return;
}


/*******************************************************************************
  Module   : Gmm_RcvMmcGmmModeChangeReq
  Function : �յ�ԭ��MMCGMM_MODE_CHANGE_REQ�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.11  �¹�����
  2.��    ��   : 2006��9��23��
    ��    ��   : sunxibo id:46746
    �޸�����   : �������ⵥ�ţ�A32D06377
  3.��    ��   : 2007��1��10��
    ��    ��   : x51137
    �޸�����   : A32D08279
  4.��    ��   : 2009��01��20��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2012��11��02��
    ��    ��   : l65478
    �޸�����   : DTS2012110104636:�ڽ�ֹPLMN�Ͻ�����ATTACH
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmModeChangeReq(
    VOS_VOID                           *pMsg                                   /* ��Ϣָ��                                 */
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU        *pModeChg;                                   /* ����ָ��                                 */

    pModeChg = (MMCGMM_MODE_CHANGE_REQ_STRU *)pMsg;                             /* ��ʼ��ָ��                               */

    switch (pModeChg->enMsMode)
    {                                                                           /* �û�ģʽ                                 */
    case NAS_MML_MS_MODE_NULL:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS��ע�ᱻ��ֹ                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* ״̬Ǩ�Ƶ�GMM_NULL                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    case NAS_MML_MS_MODE_PS_CS:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM״̬ΪNULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS��ǰפ����С����                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM������                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM��Ч                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM��Ч                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }
                }
            }
            else
            {                                                                   /* û��С��פ��                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* ״̬Ǩ��                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_PS_ONLY:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM״̬ΪNULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS��ǰפ����С����                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM������                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM��Ч                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM��Ч                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }

                }
            }
            else
            {                                                                   /* û��С��פ��                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* ״̬Ǩ��                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_CS_ONLY:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS��ע�ᱻ��ֹ                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* ״̬Ǩ�Ƶ�GMM_NULL                       */
            if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: The MsMode is Abnormal");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_GmmStatusMsgMake
  Function : GMM STATUS��Ϣ������
  Input    : VOS_UINT8    ucRejectCause                     ����ԭ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pGmmStatus  ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
    1. ��־��  2004.04.14  �¹�����
*******************************************************************************/
NAS_MSG_STRU *Gmm_GmmStatusMsgMake(
                                   VOS_UINT8    ucRejectCause                       /* ����ԭ��                                 */
                                   )
{
    NAS_MSG_STRU *pGmmStatus = VOS_NULL_PTR;                                            /* ָ��NAS_MSG_STRU�ṹ��ָ�����           */

    pGmmStatus = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));           /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pGmmStatus)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_GmmStatusMsgMake:ERROR: Alloc mem fail.");
        return pGmmStatus;
    }
    Gmm_MemSet(pGmmStatus, 0, sizeof(NAS_MSG_STRU));                            /* �ڴ�ռ���0                              */

    /* ��д�տ���Ϣ����             */
    pGmmStatus->ulNasMsgSize = GMM_MSG_LEN_GMM_STATUS;                          /* ��д�տ���Ϣ����                         */
    pGmmStatus->aucNasMsg[0] = GMM_PD_GMM;                                      /* ��дProtocol discriminator               */
    pGmmStatus->aucNasMsg[1] = GMM_MSG_GMM_STATUS;                              /* ��дAttach complete message identity     */
    pGmmStatus->aucNasMsg[2] = ucRejectCause;                                   /* ��дGMM cause                            */

    return pGmmStatus;
}

/*******************************************************************************
  Module   : Gmm_RcvTcTestReq
  Function : �յ�TCGMM_TEST_REQԭ��Ĵ���
  Input    : VOS_VOID *pMsg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.06.18  �¹�����
    2. ��    ��   : 2009��02��09��
       ��    ��   : l65478
       �޸�����   : �������ⵥ�ţ�AT2D08422������TCʱ��T3317��Ҫ����ֹͣ
    3. ��    ��   : 2011��10��11��
       ��    ��   : l00171473
       �޸�����   : V7R1 phase II, TC���ص�����ά��PS TCҵ����ڱ�־
*******************************************************************************/
VOS_VOID Gmm_RcvTcTestReq(
    VOS_VOID                           *pMsg                                    /* ָ��ԭ���ָ��                           */
)
{
    TCGMM_TEST_REQ_STRU                *pTcTestReq = VOS_NULL_PTR;              /* ����ԭ������ָ��                         */

    pTcTestReq = (TCGMM_TEST_REQ_STRU *)pMsg;                                   /* ǿ������ת��                             */

    if (TC_RB_TEST_ACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC����                                   */
        g_GmmGlobalCtrl.ucTcPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_TC_ACTIVE);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS GMM_TC_ACTIVE");

        Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
        Gmm_TimerPauseForTc(GMM_TIMER_ALL);                                     /* �������������е�Timer                    */


        /* ����PS TCҵ����ڣ��Կ���MMC�����������Ȼ��
           ͨ��PS����TC����ʱ����������PSҵ����ڣ������ڴ˴�����PS TCҵ����ڡ�

           ͨ��CS����TC���أ��յ�������PAGING��Ϣʱ����������CSҵ����ڣ���
           TC���ؽ���ʱ�����ٵ�������CSҵ����ڡ� */

        NAS_MML_SetPsTcServiceFlg(VOS_TRUE);

    }
    else if (TC_RB_TEST_DEACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TCȥ����                                 */
        GMM_CasFsmStateChangeTo(g_GmmGlobalCtrl.ucTcPreSta);

        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS ",g_GmmGlobalCtrl.ucState);

        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* �ָ����б������Timer                    */


        /* ����PS TCҵ�񲻴��� */
        NAS_MML_SetPsTcServiceFlg(VOS_FALSE);


    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_RcvTcDataReq
  Function : �յ�TCGMM_DATA_REQԭ��Ĵ���
  Input    : VOS_VOID *pMsg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.06.18  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvTcDataReq(
                      VOS_VOID *pMsg                                            /* ָ��ԭ���ָ��                           */
                      )
{

    TCGMM_DATA_REQ_STRU           *pTcDataReq;                                  /* ����ԭ������ָ��                         */
    NAS_MSG_STRU                  *pTcMsg;

    if (GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬����GMM_TC_ACTIVE                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvTcDataReq:WARNING: TCGMM_DATA_REQ is unexpected");
        return;
    }
    pTcDataReq = (TCGMM_DATA_REQ_STRU *)pMsg;                                   /* ǿ������ת��                             */

    pTcMsg = (NAS_MSG_STRU *)(&pTcDataReq->SendTcMsg);

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH, pTcMsg);              /* ���� RRMM_DATA_REQ                       */
    }
    return;
}
/*******************************************************************************
Module   : Gmm_RcvGmmStatusMsg
Function : �յ�GMM STATUS��Ϣ�Ĵ���
Input    : NAS_MSG_STRU *pMsg
Output   : ��
NOTE     : ��
Return   : ��
History  :
    1. ��־��  2005.01.25  �¹�����(for agent)
*******************************************************************************/
VOS_VOID Gmm_RcvGmmStatusMsg(
                                          NAS_MSG_FOR_PCLINT_STRU *pMsg
                                         )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_GMM_STATUS > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvGmmStatusMsg:WARNING: The length of GMM STATUS is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    return;
}
/* ��������ɾ�� */

/*******************************************************************************
  Module   : GRM_Inform_Gmm
  Function : GRM inform GMM that a data be send on user plan
  Input    : none
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. x51137  2006.07.21  Init
	2.��    ��   : 2013��7��8��
      ��    ��   : z00161729
      �޸�����  : DTS2013062008818:g�¿�������С���ʳ�������״̬���˳������Ϣ����״̬��״̬Ǩ״̬ʱ�������⣬
                    ��������״̬���˳������Ϣδ����mmc״̬�쳣
      3.��    ��   : 2013��8��27��
      ��    ��   : l00208543
      �޸�����  :  DTS2013082608600
*******************************************************************************/
VOS_VOID GRM_Inform_Gmm()
{
    LL_DATA_INFORM_MSG                 *pMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == gstGmmCasGlobalCtrl.ucLastDataSender))
    {
        /* ״̬���ԣ����������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
         && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
        {
            return;
        }

        /* ready timer��ʱ��ʱ��Ϊ0�����������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            return;
        }

        /* ready timer��ʱ��ʱ��Ϊ0xffffffff����Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* TC״̬t3314����������Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* ��TC״̬t3314����������Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            Gmm_TimerStart(GMM_TIMER_T3314);

            return;
        }
    }

    pMsg = (LL_DATA_INFORM_MSG *)PS_ALLOC_MSG(UEPS_PID_LL,
                  sizeof(LL_DATA_INFORM_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* ��Ϣͷ�̶��Ĳ��� */
    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = UEPS_PID_LL;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_GMM;

    /* ��д��Ϣ���Ͳ��� */
    pMsg->ulMsgName = ID_LL_DATA_INFORM;

    ulRet = PS_SEND_MSG(UEPS_PID_LL, pMsg);

    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_SendMsg()");
    }


    return;
}
/******************************************************************************
 * �������� �� WuepsGmmPidInit
 * �������� �� WUEPS GMM PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsGmmPidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}

/*******************************************************************************
  Module   : Gmm_RcvLLCInform
  Function : �յ�ID_LL_DATA_INFORMԭ��Ĵ���
  Input    : VOS_VOID *pMsg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. x51137  2006.07.21  Init
    2. ��    ��   : 2009��04��06��
       ��    ��   : l00130025
       �޸�����   : �������ⵥ�ţ�AT2D10790/AT2D10804��Gmm����VOS_RestartRelTimerʱ�������ָ�룬���µ��帴λ
     3.��    ��   : 2010��12��23��
       ��    ��   : s46746
       �޸�����   : DTS2010122305821:GPRS���������и����ȼ���ʱ����ʱ�ᷢ��ָ������
     4.��    ��   : 2011��12��14��
       ��    ��   : l00130025
       �޸�����   : ���ⵥDTS2011091906272,Dereg״̬��û�н��뵽Idle̬,û��ֹͣReadyTimer
     5.��    ��   : 2013��8��27��
       ��    ��   : l00208543
       �޸�����  :  DTS2013082608600

     6.��    ��   : 2014��9��5��
       ��    ��   : w00167002
       �޸�����   : GCF.9.2.3.1.6 ʧ���޸ģ����յ� GAS��PAGING INDʱ������T3314����
                    �յ�LL�·������ݲ�������
*******************************************************************************/
VOS_VOID Gmm_RcvLLCInform( VOS_VOID *pMsg )
{
    /* ����GSMģʽ��PS�����ҵ������ڽ���ע�� */
    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_GSM;


    if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        return;
    }


    if (0 != gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        /*A32D12829==>*/
        if (0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
            {
                /* ��������T3314��ֹͣT3312 */
                if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
                {
                    Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
                }
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
                if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    Gmm_TimerStop(GMM_TIMER_T3323);
                }
#endif
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
            return;
        }
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
        if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        {
            if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {
                Gmm_TimerStart(GMM_TIMER_T3314);
                Gmm_TimerPauseForTc(GMM_TIMER_T3314);                               /* ����T3312                                */
            }
        }
        else
        {
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {                                                                           /* ��timer�Ѿ�����                          */
               if(VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
               {

                   Gmm_TimerStop(GMM_TIMER_T3314);
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
               else
               {
                   g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3314);         /* ��Timer��������־                        */
                   g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
            }
            else
            {
                /*<==A32D12829*/
                g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                Gmm_TimerStart(GMM_TIMER_T3314);
            }

        }
        if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
        {

            /* ��������T3314��ֹͣT3312 */
            if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
            {
                Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                 NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            }
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
            if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                Gmm_TimerStop(GMM_TIMER_T3323);
            }
#endif
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_PrintState
 Description    : ��ӡGMM״̬
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-10-17
    Author      : Roger Leo
    Modification: created
*****************************************************************************/
VOS_VOID GMM_PrintState(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            GMM_LOG_INFO("GMM State is GMM_NULL.");
            break;
        case GMM_REGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_INITIATED.");
            break;
        case GMM_DEREGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_INITIATED.");
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_ROUTING_AREA_UPDATING_INITIATED.");
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_SERVICE_REQUEST_INITIATED.");
            break;
        case GMM_TC_ACTIVE:
            GMM_LOG_INFO("GMM State is GMM_TC_ACTIVE.");
            break;
        case GMM_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_GPRS_SUSPENSION.");
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTACH_NEEDED.");
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH.");
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_PLMN_SEARCH.");
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_IMSI.");
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_UPDATE_NEEDED.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE.");
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_PLMN_SEARCH.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM.");
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_IMSI_DETACH_INITIATED.");
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_NORMAL_SERVICE.");
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_GPRS_SUSPENSION.");
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_WAIT_FOR_SYSINFO.");
            break;
        default:
            GMM_LOG_WARN("GMM State is Error.");
            break;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_GetCurServiceStatus
 Description    : �õ�GMM�ĵ�ǰ�ķ���״̬
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-06-29
    Author      : l65478
    Modification: created
  2.Date        : 2007-08-08
    Author      : l65478
    Modification: modified for A32D12663
  3.��    ��   : 2009��01��15��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
  4.��    ��   : 2009��03��21��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D09534,��ϵͳ�л���Ľ���ʧ�ܹ����йػ���Gmm/MM�Թػ���Ϣû�д�����������AT^CPAM��ʱ������Ӧ
*****************************************************************************/
VOS_UINT8 GMM_GetSignalingStatus(VOS_VOID)
{
    VOS_UINT8      ucResult = MMC_GMM_SIGNALING_STATUS_ABSENT;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        ucResult = MMC_GMM_SIGNALING_STATUS_PRESENT;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: ucResult is ",(VOS_INT32)ucResult);

    return ucResult;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRegisteredOrRegistering
 ��������  : �жϵ�ǰGMM�Ƿ���ע�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��16��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegisteredOrRegistering(VOS_VOID)
{
    if (  (GMM_REGISTERED_NORMAL_SERVICE            == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_INITIATED                == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED     == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE     == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED           == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Prototype      : GMM_IsServiceExist
 Description    : Gmm��ǰ�Ƿ���ҵ�����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-11-17
    Author      : l00130025
    Modification: created
  2.��    ��   : 2012��3��6��
    ��    ��   : z00161729
    �޸�����   : ֧��ISR�����޸�
*****************************************************************************/
VOS_UINT32 GMM_IsServiceExist(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if((VOS_TRUE == NAS_MML_IsPsBearerExist())
    || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ulResult = GMM_TRUE;
    }
    else
    {
        ulResult = GMM_FALSE;
    }
    return ulResult;
}

/*****************************************************************************
 Prototype      : NAS_GMM_GetSignalingStatusInGsm
 Description    : ��ǰ�Ƿ���ܴ���TBF
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.��    ��   : 2009��09��25��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D14675,RAU/Attach�����У�list����ʧ��
*****************************************************************************/
VOS_UINT32 NAS_GMM_GetSignalingStatusInGsm(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (( ( VOS_TRUE == NAS_MML_GetPsTbfStatusFlg() )
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: ucResult is ",(VOS_INT32)ulResult);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : Gmm_BufSmDataReqMsg
 ��������  : GMM��ǰ״̬�޷�����SM����Ϣʱ,���л���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2007��11��16��
    ��    ��   : hanlufeng 41410
    �޸�����   : �����ɺ���
  2.��    ��   : 2007��12��18��
    ��    ��   : l00107747
    �޸�����   : �������ⵥ�ţ�A32D13917,GMM����SM����͵�ǰ���ܴ�����Ҫ������Ҫ������
                 ���������ڴ�����
*****************************************************************************/
VOS_VOID Gmm_BufSmDataReqMsg( VOS_VOID *pMsg )
{
    GMMSM_DATA_REQ_STRU                 *ptr;

    /*���뻺����Ϣ���ڴ�*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_RcvSmDataReq_RegNmlServ:WARNING: Gmm_MemMalloc fail !! ");
          return;
    }

    /*����Ϣ�ݴ浽������ڴ���*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
    }
    /*�÷���ֻ�������µ�һ����Ϣ,����ǰ�л�����Ϣ,���ͷŵ�*/
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SM;

    return;
}
/*****************************************************************************
 �� �� ��  : Gmm_ComCnfHandle
 ��������  : Rau��Service����ʧ��֮�󣬶Ի�����Ϣ��Follow On��־�����ϲ�ظ�
             ��Ӧ�Ĺ�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   :
  2.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
  3.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2012��09��12��
    ��    ��   : Z40661
    �޸�����   : DTS2012081608654
  5.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
  6.��    ��   : 2013��10��05��
    ��    ��   : l65478
    �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
*****************************************************************************/
VOS_VOID Gmm_ComCnfHandle(VOS_VOID)
{
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSR_DATA                        */
        if (RR_REL_CAUSE_RRC_SNW == g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_OOS);                 /* ֪ͨRABM���                             */
        }
        else
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        }
    }


    if ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
     || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
    {

        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        NAS_GMM_SndMmcMmDetachInfo();
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_ComCnfHandle(): Clear cached SM data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL;
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;

        case GMM_DETACH_COMBINED:
        case GMM_DETACH_NORMAL:
        case GMM_DETACH_WITH_IMSI:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
                NAS_GMM_SndMmGprsDetachComplete();
            }

            break;

        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }
}
/*****************************************************************************
 �� �� ��  : Gmm_GetState
 ��������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Gmm_GetState()
{
    return g_GmmGlobalCtrl.ucState;
}
/*****************************************************************************
 �� �� ��  : Gmm_GetGprsState
 ��������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Gmm_GetGprsState()
{
    VOS_UINT32  ulGprsState;
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState&0xf0))
            ||(GMM_NULL == g_GmmGlobalCtrl.ucState))
        {
            ulGprsState = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            ulGprsState = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            ulGprsState = GMM_IU_PMM_IDLE;
        }
    }
    else
    {
        ulGprsState = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    return ulGprsState;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_NetMod
 *  FUNCTION : Gmm_FillNasMmInfo���������Ӷ�: NetMod�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  ŷ����   2009.06.11  �°�����
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_NetMod(NAS_OM_MM_IND_STRU       *pMsg)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_1;
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_2;
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_3;
    }
    else
    {
        pMsg->enNetMode = NET_OPERATE_MODE_BUTT;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FillNasGmmState
 ��������  : ���Gmm State��Substate ��Ϣ
 �������  : ��
 �������  : �����ɺ��Gmm State��Substate ��Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��3��4��
   ��    ��   : o00132663
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��23��
   ��    ��   : zhoujun 40661
   �޸�����   : �޸����Ʒ��ϱ�̹淶

 3.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ����GMM����״̬��д

 4.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ

*****************************************************************************/
VOS_VOID NAS_GMM_FillNasGmmState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    pstMsg->enGmmSubState = GMM_SUB_STATE_BUTT;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            pstMsg->enGmmState = STATE_GMM_NULL;
            break;
        case GMM_REGISTERED_INITIATED:
            pstMsg->enGmmState = REGISTERED_INITIATED;
            break;
        case GMM_DEREGISTERED_INITIATED:
            pstMsg->enGmmState = DEREGISTERED_INITIATED;
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            pstMsg->enGmmState = ROUTING_AREA_UPDATING_INITIATED;
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            pstMsg->enGmmState = SERVICE_REQUEST_INITIATED;
            break;
        case GMM_TC_ACTIVE:
            pstMsg->enGmmState = TC_ACTIVE;
            break;
        case GMM_GPRS_SUSPENSION:
            pstMsg->enGmmState = GPRS_SUSPENSION;
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NORMAL_SERVICE;
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_LIMITED_SERVICE;
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTACH_NEEDED;
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTEMPTING_TO_ATTACH;
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_PLMN_SEARCH;
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_IMSI;
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NORMAL_SERVICE;
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_LIMITED_SERVICE;
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_UPDATE_NEEDED;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE;
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_PLMN_SEARCH;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE_MM;
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_IMSI_DETACH_INITIATED;
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            pstMsg->enGmmState = SUSPENDED_NORMAL_SERVICE;
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            pstMsg->enGmmState = SUSPENDED_GPRS_SUSPENSION;
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            pstMsg->enGmmState = SUSPENDED_WAIT_FOR_SYSINFO;
            break;
        default:
            pstMsg->enGmmState = GMM_STATE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_FillNasMmInfo:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    NAS_GMM_FillNasGmmGprsState(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FillNasGmmGprsState
 ��������  : ���Gmm GPRS State��Ϣ
 �������  : ��
 �������  : �����ɺ��Gmm GPRS State��Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ��������
*****************************************************************************/
VOS_VOID NAS_GMM_FillNasGmmGprsState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    pstMsg->enGmmGprsState              = NAS_OM_GMM_GPRS_STATE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        switch(gstGmmCasGlobalCtrl.GmmSrvState)
        {
            case GMM_AGB_GPRS_IDLE:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_IDLE;
                break;
            case GMM_AGB_GPRS_STANDBY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_STANDBY;
                break;
            case GMM_AGB_GPRS_READY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_READY;
                break;
            default:
                break;
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_ucUpdateSta
 *  FUNCTION : Gmm_FillNasMmInfo���������Ӷ�: ucUpdateSta�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  ŷ����   2009.06.11  �°�����
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_ucUpdateSta(NAS_OM_MM_IND_STRU     *pMsg)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    switch (NAS_MML_GetPsUpdateStatus())
    {
    case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU1;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU2;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
    case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU3;
        break;
    default:
        pMsg->enGmmUpdateStatus = GMM_UPDATE_STATUS_BUTT;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_FillNasMmInfo:WARNING: PsUpdateStatus is Error");
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    return;
}

/*******************************************************************************
Module   : Gmm_FillNasMmInfo
Function :
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :

  1.��    ��   : 2008��9��01��
    ��    ��   :
    �޸�����   :
*******************************************************************************/

/***********************************************************************
 *  MODULE   : Gmm_Com_ServiceStatus_Handle
 *  FUNCTION : ��õ�ǰ����״̬�Ĺ�������
 *  INPUT    : ��
 *  OUTPUT   : ��
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : ��
 *  HISTORY  :
 *     1.     2009.02.10  �°�����
       2.��    ��   : 2009��03��12��
         ��    ��   : ouyangfei id:00132663
         �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
       3.��    ��   : 2011��08��12��
         ��    ��   : z00161729
         �޸�����   : V7R1 PHASE II ST�޸�
       4.��    ��   : 2014��4��3��
         ��    ��   : s00261364
         �޸�����   : V3R360_eCall��Ŀ
 ************************************************************************/
VOS_VOID Gmm_Com_ServiceStatus_Handle(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {         /* ����״̬��Ҫ�ϱ�����״̬    */
    case GMM_NULL:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, begin */

        /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, end */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        break;

    default:
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_ServiceStatus_Handle:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return;
}
/***********************************************************************
 *  MODULE   : Gmm_ComServiceSts
 *  FUNCTION : ��õ�ǰ����״̬�Ĺ�������
 *  INPUT    : ��
 *  OUTPUT   : ��
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : ��
 *  HISTORY  :
 *     1.     2009.02.10  �°�����
       2.��    ��   : 2009��03��12��
         ��    ��   : ouyangfei id:00132663
         �޸�����   : ���ⵥAT2D09683,����ʱ��GMM�ϱ�����״̬�쳣����MMCû�з���������
       3.��    ��   : 2009��08��13��
         ��    ��   : l65478
         �޸�����   : ���ⵥ�ţ�AT2D13662,3G���ϱ���out of coverage�����ǻ�����ϱ�PS_Service
       4.��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
 ************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 Gmm_ComServiceSts(VOS_VOID)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8       ucServiceSts = MM_COM_SRVST_NO_CHANGE;                     /* ������ʱ����                             */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�÷���״̬                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucServiceSts = MM_COM_SRVST_NORMAL_SERVICE;
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        ucServiceSts = NAS_GMM_GetRegUptNeededPsSrvStatus();
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;

        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
        }
        break;

    case GMM_DEREGISTERED_NO_IMSI:
        ucServiceSts = MM_COM_SRVST_NO_IMSI;
        break;

    case GMM_NULL:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        ucServiceSts = MM_COM_SRVST_NO_SERVICE;
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        if (5 == g_GmmRauCtrl.ucRauAttmptCnt)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;
        }
        else
        {
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        }
        break;
    default:
        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComServiceSts:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucServiceSts;
}
/*******************************************************************************
 *  MODULE   : Gmm_GetServiceStatusForSms
 *  FUNCTION : ��õ�ǰ����״̬�Ĺ�������
 *  INPUT    : ��
 *  OUTPUT   : ��
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : ��
 *  HISTORY  :
 *     1.     2009.06.30    x00115505    �°�����
 ******************************************************************************/
VOS_UINT32 Gmm_GetServiceStatusForSms(VOS_VOID)
{
    GMM_STATE_TYPE_UINT8    ucState;
    VOS_UINT32              ulServiceSts = GMM_SMS_NO_SERVICE;                  /* ������ʱ����                             */

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    switch (ucState)
    {                                                                           /* ����״̬�÷���״̬                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        ulServiceSts = GMM_SMS_NORMAL_SERVICE;
        break;
    default:
        break;
    }

    return ulServiceSts;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvInterRatHandoverInfoCnf
 ��������  : �յ�WRR��RRMM_INTER_RAT_HANDOVER_INFO_CNF��Ϣ����
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��17��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  3.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  4.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�޸�

*****************************************************************************/
VOS_VOID NAS_GMM_RcvInterRatHandoverInfoCnf(VOS_VOID *pMsg)
{
    RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU   *pRrmmInterRatInfoMsg = VOS_NULL_PTR;
    NAS_MSG_STRU                            *pSendNasMsg = VOS_NULL_PTR;

    pRrmmInterRatInfoMsg = (RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU *)pMsg;

    Gmm_TimerStop(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg   = VOS_TRUE;
    g_GmmInterRatInfoCtrl.ucDataLen                 = (VOS_UINT8)pRrmmInterRatInfoMsg->usDataLen;

    if (0 == pRrmmInterRatInfoMsg->usDataLen)
    {
        /* WRR����InterRatHandoverʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Msg Len is 0.");
    }
    else
    {
        /* InterRatHandoverInfo ��Ϣ���浽ȫ�ֱ����� */
        PS_MEM_CPY(g_GmmInterRatInfoCtrl.aucData, pRrmmInterRatInfoMsg->aucData, g_GmmInterRatInfoCtrl.ucDataLen);
    }

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH��������SM������,֪ͨSM GMMע��ɹ�,����ucSmCnfFlg��־ */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* �ظ�����Attach Complete ��Ϣ */
        pSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* ����Ҫ�ȴ�RABM�Ļظ���Ϣ�������Ѿ��յ�RABM�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsInHandoverProcedure
 ��������  : �жϵ�ǰGMM�Ƿ�����ѡ�����л������У�����ǣ����ܽ���BG����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��23��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInHandoverProcedure(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;

    if ((GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsInHandoverProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsInRegisterProcedure
 ��������  : �жϵ�ǰ�Ƿ���ע�������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��10��10��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  1.��    ��   : 2012��8��3��
    ��    ��   : z60575
    �޸�����   : DTS2012080301265, ����״̬�ж�
*****************************************************************************/
VOS_UINT32  NAS_GMM_IsInRegisterProcedure(VOS_VOID)
{
    /* �жϵ�ǰ�Ƿ���ע������� */
    if((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_CnfSmNotAttach
 ��������  : GMM Deregister״̬�����ȼ��б�����ʱ���յ�SM��������פ������-
             GMM�޷�����Attachʱ�ظ�SMģ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��23��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
   2.��    ��  : 2012��08��24��
   ��    ��    : m00217266
   �޸�����    : ���enCause��Σ��ϱ�ע��ɹ���ʧ��ԭ��ֵ

*****************************************************************************/
VOS_VOID NAS_GMM_CnfSmNotAttach(
    GMM_SM_CAUSE_ENUM_UINT16            enCause                                 /* ע��ʧ��ԭ��ֵ */
)
{
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, enCause);
        g_GmmAttachCtrl.ucSmCnfFlg            = GMM_FALSE;
        g_GmmGlobalCtrl.ucFollowOnFlg         = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsInRegOrDeregProcedure
 ��������  : �ж�GMM��ǰ�Ƿ���ע�����ȥע�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ��ע�������
             VOS_FALSE : ����ע�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��28��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInRegOrDeregProcedure(VOS_VOID)
{
    VOS_UINT8      ucResult;

    ucResult = VOS_FALSE;

    /* WCDMAģʽ�£����ڽ���ע��/ȥע�ᣬ������ҵ�������ʱ����Ϊ�������ӣ�
      GSMģʽ�£���TBF����ʱ����Ϊ�������� */
    if ( (GMM_REGISTERED_INITIATED             == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_INITIATED           == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ucResult = VOS_TRUE;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_GMM, "NAS_GMM_IsInRegisterOrDeregisterProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucResult;
}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_IsInServiceProcedure
 ��������  : �ж�GMM��ǰ�Ƿ��ڷ���ҵ��Ĺ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��31��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_Gmm_IsInServiceProcedure(VOS_VOID)
{
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetGmmRegStateForInterPLmnList
 ��������  : ��ȡGMM��״̬�Ƿ��ܷ����б�����,��Ҫ����MM�����б�����ʱ�����ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK:���Է����б�����
              VOS_ERR:���ܷ����б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��21��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetGmmRegStateForInterPLmnList( VOS_VOID )
{
    VOS_UINT8                           ucTimerId;
    VOS_BOOL                            bTimerRunning;
    VOS_UINT32                          ulTimerRunMask;

    /* С����bar����� */
    if ( ( GMM_DEREGISTERED_ATTACH_NEEDED        == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_UPDATE_NEEDED          == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    ucTimerId   = GMM_TIMER_T3302;

    ulTimerRunMask = g_GmmTimerMng.ulTimerRunMask;

    /*lint -e701*/
    if (0 != ( ulTimerRunMask & ( 0x00000001 << ucTimerId )))
    /*lint +e701*/
    {
        bTimerRunning = VOS_TRUE;
    }
    else
    {
        bTimerRunning = VOS_FALSE;
    }

    if ( VOS_FALSE == bTimerRunning )
    {
        return VOS_ERR;
    }


    if ( ( GMM_REGISTERED_ATTEMPTING_TO_UPDATE   == g_GmmGlobalCtrl.ucState)
      || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    if ( ( GMM_DEREGISTERED_NO_IMSI   == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertPlmnIdToMmcFormat
 ��������  : ��GMM��PLMNID��ʽת��ΪMMC��ʽ��
 �������  : pstGmmPlmnId:GMM��PLMN ID��ʽ
 �������  : pstMmcPlmnId:MMC��PLMN ID��ʽ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToMmcFormat(
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId
)
{

    pstMmcPlmnId->ulMcc = pstGmmPlmnId->aucMccDigit[0]
                        | (pstGmmPlmnId->aucMccDigit[1] << 8)
                        | (pstGmmPlmnId->aucMccDigit[2] << 16);

    pstMmcPlmnId->ulMnc = pstGmmPlmnId->aucMncDigit[0]
                        | (pstGmmPlmnId->aucMncDigit[1] << 8)
                        | (pstGmmPlmnId->aucMncDigit[2] << 16);
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertPlmnIdToMmcFormat
 ��������  : ��GMM��PLMNID��ʽת��ΪMMC��ʽ��
 �������  : pstMmcPlmnId:
 �������  : pstGmmPlmnId
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToGmmFormat(
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId,
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId
)
{
    pstGmmPlmnId->aucMccDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMcc & 0x0F);

    pstGmmPlmnId->aucMccDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 8) & 0x0F);

    pstGmmPlmnId->aucMccDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 16) & 0x0F);

    pstGmmPlmnId->ucMncCnt = 3;

    pstGmmPlmnId->aucMncDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMnc & 0x0F);

    pstGmmPlmnId->aucMncDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 8) & 0x0F);

    pstGmmPlmnId->aucMncDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 16) & 0x0F);

    if (GMM_PLMNID_MNC3_INVALID == pstGmmPlmnId->aucMncDigit[2])
    {
        pstGmmPlmnId->ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

}




/*****************************************************************************
 �� �� ��  : NAS_GMM_IsDeregisterState
 ��������  : �ж�״̬�Ƿ�ΪGMMδע��״̬
 �������  : ucState
 �������  : ��
 �� �� ֵ  : VOS_TRUE:δע��
             VOS_FALSE:��ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��21��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsDeregisterState(
    GMM_STATE_TYPE_UINT8                ucState
)
{
    if ((GMM_REGISTERED_INITIATED == ucState)
     || (GMM_DEREGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_DEREGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_DEREGISTERED_ATTACH_NEEDED == ucState)
     || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_DEREGISTERED_PLMN_SEARCH == ucState)
     || (GMM_DEREGISTERED_NO_IMSI == ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : Gmm_FreeBufferMsgWithoutSm
 ��������  : �ͷŲ�����SM��Ϣ������������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��04��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Gmm_FreeBufferMsgWithoutSm(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ��������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsAcChgRegisterNetRaiChg
 ��������  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded�յ�WasAcInfoChgInd�Ĵ���,RAI�ı�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸�����  : �����ɺ���
  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiChg()
{
    g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* ���T3312������                        */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                       /* ��A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
    }
    else
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU����                              */
    }
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChgT3312Expire
 ��������  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded�յ�WasAcInfoChgInd�Ĵ���,RAI�ı�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire()
{
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* ��A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
          || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChgT3312NotExpire
 ��������  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded�յ�WasAcInfoChgInd�Ĵ���,RAI���ı�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
  2.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  3.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire()
{
    VOS_UINT8                           ucCsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    /* ��ǰPS����״̬ΪU1 */
    if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /* ������ģʽI�Ĵ��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
         || (VOS_TRUE != ucCsAttachAllow)
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
        else
        {
            /* CS����״̬ΪU1����Gs���Ӵ��� */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                }

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
            else                                                                /* CS����״̬����U1,����Gs�����Ѿ��Ƴ� */
            {
                /* sim��Ч����CS������ע�� */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                    }

                    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);                     /* ����RAU                                  */
                }
            }
        }
    }
    else
    {
        /* ����״̬����GU1,����RAU */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChg
 ��������  : GMM��GMM_REGISTERED_UPDATE_NEEDED״̬�յ�WasAcInfoChgInd,RAIû�иı�ʱ�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg()
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /* T3312��ʱ��־�����ڡ�*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire();
    }
    else
    {
        /* T3312��ʱ��־���ڡ�*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire();
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_PostAcInfoChgInd
 ��������  : �յ�MMCת����WasAcInfoChgInd�ĺ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
*****************************************************************************/
VOS_VOID NAS_GMM_ComProcAcInfoChgInd(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* ��ѡ��PS��BARRED��С��,������ģʽI,����T3312��ʱ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
    }
    /* ��ǰҵ�����ޣ������ҵ�񻺴� */
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
    {
        /* ������� */
        Gmm_ComCnfHandle();
        GMM_BufferMsgDump();
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegInit
 ��������  : ��DEREG״̬�յ�MMCת����WasAcInfoChgInd�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* PS ע��Ӳ����޵����� */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState)
        {
            /* ����ģʽI */
            if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        /* ���õ�ǰPS����״̬Ϊ���Ʒ��� */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimit
 ��������  : REG LIMIT SERVICE״̬�յ�MMCת����WasAcInfoChgInd�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    /* PS ע������ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        /* Ǩ�Ƶ�ǰGMM״̬��GMM_REGISTERED_UPDATE_NEEDED */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded
 ��������  : GMM_DEREGISTERED_ATTACH_NEEDED״̬�յ�MMCת����WasAcInfoChgInd�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���

  2.��    ��   : 2013��6��11��
    ��    ��   : z00234330
    �޸�����   : DTS2013061152841,��bar��С������bar��С��,GMM֪ͨwrr������Ϣ����Я����plmn idΪ0
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS ע������޵������� */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucSysValidFlg       = GMM_TRUE;
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }

        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);

        /* PS����Ч */
        if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
        {                                                                           /* ԭ��SIM��Ч                              */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
            return;
        }

        /* ��ǰ�û����ò�֧��PSע�� */
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* ����״̬�Ĺ�������                       */

            GMM_BufferMsgResume();
            return;
        }

        /* ��ǰ���粻֧��GPRS�����������ڽ�ֹ�б� */
        if ((GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
         || (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask))
        {                                                                           /* ��֧��GPRS                               */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        }
        else
        {                                                                           /* С���ı�                                 */
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }


}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ
 ��������  : GMM ��REG��������״̬�յ�MMCת����WasAcInfoChgInd�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    VOS_UINT8                           ucCsAttachAllow;                        /* CS���Ƿ�����ע��,VOS_TRUE:����CS��ע��,VOS_FALSE:������CS��ע�� */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();
    ucCsAttachAllow     = NAS_MML_GetCsAttachAllowFlg();

    /* PS ע�᲻���޵����� */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* ֪ͨMM����LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
            }
            else
            {
                 /* ֪ͨMM����LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
    }
    else
    {
        /* ����ģʽI,�ֻ�ģʽA,CS����Ч,Gs���ӱ�־�����ڣ��ҵ�ǰCS������ڣ�
        CSע������ޱ�Ϊ������ʱ��Ҫ��������ע�� */
        if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
         && (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
         && (VOS_TRUE == ucCsAttachAllow)
         && (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
         && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded
 ��������  : ��GMM_REGISTERED_UPDATE_NEEDED״̬�յ�MMCת����WasAcInfoChgInd�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : w00166186
    �޸����� : �����ɺ���
  2.��    ��   : 2013��6��11��
    ��    ��   : z00234330
    �޸�����   : DTS2013061152841,��bar��С������bar��С��,GMM֪ͨwrr������Ϣ����Я����plmn idΪ0
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS ע������޵������� */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }
        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);
        if (VOS_FALSE ==  NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* ��ǰ���粻֧��GPRS */
        else if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* ��ǰ�����ڽ�ֹ�б� */
        else if (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        }
        else if (VOS_FALSE == NAS_MML_IsRaiChanged())
        {
            /* RAIû�иı� */
            NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg();
        }
        else
        {
            /* RAI�ı� */
            NAS_GMM_ProcPsAcChgRegisterNetRaiChg();
        }
    }

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcWasAcInfoChgInd
 ��������  : �յ�MMCת��RRMM_W_INFO_CHANGE_IND
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2012��2��15��
    ��    ��  : W00166186
    �޸����� : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd(
    NAS_MSG_STRU                       *pstMsg
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    /* ��ԭ��RRMM_W_INFO_CHANGE_IND����״̬�ַ� */
    switch (g_GmmGlobalCtrl.ucState)
    {
        /* DEREG״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(pstAcInfoChangeInd);
            break;
        case GMM_DEREGISTERED_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            break;

        /* REG LIMITED SERVICE״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(pstAcInfoChangeInd);
            break;

        /* GMM_DEREGISTERED_ATTACH_NEEDED״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(pstAcInfoChangeInd);
            break;

        /* REG NORMAL״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(pstAcInfoChangeInd);
            break;

        /* GMM_REGISTERED_UPDATE_NEEDED״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_UPDATE_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(pstAcInfoChangeInd);
            break;
        default :
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
            break;
    }

    NAS_GMM_ComProcAcInfoChgInd(pstAcInfoChangeInd);

}
/*****************************************************************************
 �� �� ��  : NAS_GMM_GetRegUptNeededPsSrvStatus
 ��������  : ��ȡMM_IDLE_LOCATION_UPDATE_NEEDED״̬ʱCS�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 PS�����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_GMM_GetRegUptNeededPsSrvStatus()
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* �����ǰRAI���ϴγɹ�ע���RAI��ͬ��UPDATE״̬ΪU1��OTHER������Ϊ�������񣬷���Ϊ���Ʒ��� */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
            return MM_COM_SRVST_LIMITED_SERVICE_REGION;
        }
        else
        {
            return MM_COM_SRVST_LIMITED_SERVICE;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcSmDataReq_RAUInit
 ��������  : ��RAU�������յ�SM��Ϣ�Ĵ���
 �������  : VOS_VOID                           *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��04��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ProcSmDataReq_RAUInit(
    VOS_VOID                           *pSmDataReqMsg
)
{
    VOS_UINT8                           ucMsgType;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_GMM_ProcSmDataReq_RAUInit:NORMAL:Gmm receive SM Data Req.");

    /* ��ȥ������ܻ���SM STATUS��Ϣ,������ʱ���̷�������,û������ʱ����;
       ���򻺴���Ϣ */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
    if ((SM_DEACT_PDP_CONTEXT_ACC == ucMsgType)
     || (SM_STATUS                == ucMsgType))
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
        }
    }
    else
    {
        Gmm_BufSmDataReqMsg(pSmDataReqMsg);
    }
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_Gmm_IsPtmsiMappedFromGuti
 ��������  : �жϵ�ǰPTMSI�Ƿ���GUTIת������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��17��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_Gmm_IsPtmsiMappedFromGuti(VOS_VOID)
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* �ж�GUPTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
     && (VOS_OK == ulGetGutiRst) )
    {
        return VOS_TRUE;
    }

    if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
     && (VOS_FALSE == ulLocalPtmsiFlg)
     && (VOS_OK == ulGetGutiRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
#endif



/*****************************************************************************
 �� �� ��  : NAS_GMM_FreeBufferCmMsg
 ��������  : �ͷŻ����CM��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��22��
    ��    ��   : l5478
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_GMM_FreeBufferCmMsg(VOS_VOID)
{
    VOS_VOID                           *pAddr;                                              /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* ����б�����SmDataReqԭ��                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_FreeBufferCmMsg(): Clear cached SM data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* ��ȡSmDataReqԭ���ַ                    */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }
}

/* Modified by z00161729 for DCM�����������������, 2012-8-30, begin */
/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedEnableLte_AttachPs
 ��������  : Attach PS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��08��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 4.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч
    (3)USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* �����SIM��������ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-30, end */

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttachType
 ��������  : ��ȡattach ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : attach ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��09��16��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���DTS2012091707434
 2.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

*****************************************************************************/
VOS_UINT8 NAS_GMM_GetAttachType(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictRegister;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* ps������attach��������ע�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return GMM_NULL_PROCEDURE;
    }

    /* ����CS��������ʱ������NORMAL ATTACH */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* ����ģʽI, ��PS�򵥶�ע��ɹ����յ�ϵͳ��Ϣ����Ҫ�ٴδ���COMBINED ATTACH */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_ATTACH_NORMAL);
        }

        return GMM_ATTACH_NORMAL;
    }

    if (((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
      || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)))
    {
        return GMM_ATTACH_NORMAL;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {                                                                       /* CS���Ѿ�ע��                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
                return GMM_ATTACH_NORMAL_CS_TRANS;
            }

            return GMM_ATTACH_WHILE_IMSI_ATTACHED;
        }

        if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
         || (VOS_TRUE == ucCsRestrictRegister))
        {
            /* CS��ATTACH����ֹ */
            return GMM_ATTACH_NORMAL;
        }

        /* CS��ATTACHû����ֹ */
        if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {
            /* CS����ͨ����*/
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            return GMM_ATTACH_NORMAL_CS_TRANS;
        }

        /* CS����ͨ���� */
        return  GMM_ATTACH_COMBINED;

    }

    return GMM_ATTACH_NORMAL;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmCsConnectInd_RrcConnExist
 ��������  : RRC���Ӵ���ʱ���յ�MM��CsConnectInd�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��7��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��30��
    ��    ��   : s00217060
    �޸�����   : DTS2012050301830:�޸ĺ��������յ�MM��CsConnectIndʱ,���RRC���Ӵ���,��������RAU��
                 ����,�յ�������ϱ���ϵͳ��Ϣ����������RAU.
  3.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_RrcConnExist(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucPsRestrictRegFlg;

    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictRegFlg = NAS_MML_GetPsRestrictRegisterFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    enCurrNetRatType   = NAS_MML_GetCurrNetRatType();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucSimCsRegStatus)
     && (VOS_FALSE == ucPsRestrictRegFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FreeWasSysInfo
 ��������  : �ͷŻ���GSMϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��28��
   ��    ��  : l00167671
   �޸�����  : �����ɺ������޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
				 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
				 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
				 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
*****************************************************************************/
VOS_VOID NAS_GMM_FreeWasSysInfo(VOS_VOID)
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return;
    }

    /* ���������־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* ������buffer�����е���Ϣ�ͷ� */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SaveWasSysInfo
 ��������  : ����W��ϵͳ��Ϣ
 �������  : pstGsmSysInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��28��
   ��    ��  : l00167671
   �޸�����  : �����ɺ������޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
				 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
				 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
				 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
*****************************************************************************/
VOS_VOID NAS_GMM_SaveWasSysInfo(
    MMCGMM_SYS_INFO_IND_STRU         *pstSysInfo
)
{
    MMCGMM_SYS_INFO_IND_STRU         *pstHoldSysInfo = VOS_NULL_PTR;

    NAS_GMM_FreeWasSysInfo();

    pstHoldSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHoldSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveWasSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* �û����־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* ����ϵͳ��Ϣ */
    Gmm_MemCpy(pstHoldSysInfo, pstSysInfo, sizeof(MMCGMM_SYS_INFO_IND_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = (VOS_UINT32)pstHoldSysInfo;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcSavedWasSysInfo
 ��������  : ������GSMϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��28��
   ��    ��  : l00167671
   �޸�����  : �����ɺ������޸����ⵥDTS2012122001075,���ⵥ��������:
                 PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
				 �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
				 ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
				 ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
*****************************************************************************/
VOS_UINT32 NAS_GMM_ProcSavedWasSysInfo()
{
    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : Gmm_MsgDistribute_ProcMmcMsg_GmmNull
 ��������  : GMM��GmmNULL״̬����MMC��Ϣ
 �������  : pMsg        - �յ���Ϣ
 �������  : ��
 �� �� ֵ  : GMM_TRUE    - ��ǰ��Ϣ��������
             MM_TRUE     - ��ǰ��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_ProcMmcMsg_GmmNull(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* �õ���Ϣͷ                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_MODE_CHANGE_REQ :
            break;

        case MMCGMM_PLMN_SEARCH_INITIATED :
            break;

        case MMCGMM_SYS_INFO_IND :
            break;

        case MMCGMM_GSM_SYS_INFO_IND :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        /* ������Ϣ��Ϊ�쳣��Ϣ */
        case MMCGMM_DETACH_REQ :
            NAS_GMM_SndMmcDetachCnf();
            ucRst = GMM_FALSE;

            break;

        case MMCGMM_ATTACH_REQ :
            NAS_GMM_SndMmcAttachCnf();
            ucRst = GMM_FALSE;

            break;

        default:
            ucRst = GMM_FALSE;
            break;
    }

    return ucRst;
}



/*****************************************************************************
 �� �� ��  : NAS_Gmm_IsValidMmcMsg_GmmTcActive
 ��������  : GMM��GmmTcActive״̬�ж�MMC��Ϣ�Ƿ�Ƿ�
 �������  : pMsg        - �յ���Ϣ
 �������  : ��
 �� �� ֵ  : GMM_TRUE    - ��ǰ��Ϣ�ͷ������Ժ�����������
             MM_TRUE     - ��ǰ��Ϣ�Ƿ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_Gmm_IsValidMmcMsg_GmmTcActive(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* �õ���Ϣͷ                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        case MMCGMM_SUSPEND_IND :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_ATTACH_REQ :
            break;

        /* ������Ϊ��Ϣ�Ƿ��������� */
        default:
            ucRst = GMM_FALSE;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_Gmm_IsInvalidMmcMsg_GmmTcActive:WARN:INVALID MSG");
            break;
    }

    return ucRst;
}


/*****************************************************************************
 �� �� ��  : NAS_Gmm_ClearPendingPdpStatus
 ��������  : �������PENDING״̬��PDP STATUS
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��06��
    ��    ��   : A00165503
    �޸�����   : DTS2014120207400: ����ȥ������PDP, ���಻�ͷ�RRC����
*****************************************************************************/
VOS_VOID NAS_Gmm_ClearPendingPdpStatus(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearCtx;
    VOS_UINT32                          i;

    pstPsBearCtx = NAS_MML_GetPsBearerCtx();

    /* ������Ϣ��pdp״̬����MML��ȫ�ֱ��� g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (VOS_TRUE == pstPsBearCtx[i].ucPsActPending)
        {
            pstPsBearCtx[i].ucPsActPending = VOS_FALSE;
        }

        if (VOS_TRUE == pstPsBearCtx[i].ucPsDeactPending)
        {
            pstPsBearCtx[i].ucPsDeactPending = VOS_FALSE;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ClearAuthInfo
 ��������  : �����Ȩ�����Ϣ
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��09��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_ClearAuthInfo(VOS_VOID)
{
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;

    /* 24.008 4.7.7.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3316, if running, shall be stopped:
    -   if the mobile station enters the GMM states GMM-DEREGISTERED or GMM-NULL.
    */
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��"RES���ڱ�־ "��Ϊ0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* ��"RAND���ڱ�־ "��Ϊ0                   */
    Gmm_TimerStop(GMM_TIMER_T3316);

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG == (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG & g_GmmReqCnfMng.ucCnfMask))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
        Gmm_TimerStop(GMM_TIMER_PROTECT);
    }


    return;
}

/*lint -restore */

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcRelInd
 ��������  : ����Ƿ���Ҫ����rel_ind��Ϣ
 �������  : RRMM_REL_IND_STRU:������rel_ind��Ϣ
 �������  : VOS_VOID
 �� �� ֵ  : VOS_TRUE:��Ҫ��������rel_ind��Ϣ
             VOS_FALSE:����Ҫ��������rel_ind��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��09��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_IsNeedProcRelInd(
    RRMM_REL_IND_STRU       *pstRrRelInd
)
{

    /* �������PS��,GMM����Ҫ���� */
    if (RRC_NAS_PS_DOMAIN != pstRrRelInd->ulCnDomainId)
    {
        return VOS_FALSE;
    }


    /* ����������¼���״̬�ȴ�est_cnf������rel causeΪRRC_REL_CAUSE_NAS_DATA_ABSENT������������:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */

    /* ���GMMû�ڵȽ�����est_cnf����Ҫ�������� */
    if (GMM_RRC_RRMM_EST_CNF_FLG !=
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        return VOS_TRUE;
    }

    /* ���rel cause����RRC_REL_CAUSE_NAS_DATA_ABSENT����Ҫ�������� */
    if (RRC_REL_CAUSE_NAS_DATA_ABSENT != pstRrRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    /* ״̬����init״̬����Ҫ�������� */
    if ( (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension
 ��������  : ��GMM_GPRS_SUSPENSION/GMM_SUSPENDED_GPRS_SUSPENSION״̬�յ�MMC��Ϣ��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : s00217060
   �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;

    pstNasMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if (MMCGMM_SUSPEND_IND == pstNasMsgHeader->ulMsgName)
    {
        GMM_LOG_INFO("NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension:Receive MMCGMM_SUSPEND_IND in GMM_GPRS_SUSPENSION state.");
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if (MMCGMM_POWER_OFF_REQ == pstNasMsgHeader->ulMsgName)
    {
        GMM_BufferMsgDump();
        Gmm_TimerStop(GMM_TIMER_ALL);
        Gmm_TimerStart(GMM_TIMER_1S);
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;
        g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;
        return VOS_TRUE;
    }
    else if ( MMCGMM_PLMN_SEARCH_INITIATED == pstNasMsgHeader->ulMsgName )
    {
        /* ���к���Ĵ���Ǩ�Ƶ�����״̬ */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if ( MMCGMM_DETACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        /* ���к���Ĵ���Ǩ�Ƶ�����״̬ */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }


    /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
       ������פ��������������Attach */
    else if ( MMCGMM_ATTACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }

    else if (( MMCGMM_GSM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName )
          || ( MMCGMM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName ) )
    {
        /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ��,����ϵͳ��Ϣ */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);
    }
    else
    {
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcVoiceDomainChangeNotify
 ��������  : GMM�յ�MMC��MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY��Ϣ�Ĵ���
 �������  : pRcvMsg:��Ϣ
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��09��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcVoiceDomainChangeNotify(
    struct MsgCB                       *pRcvMsg
)
{
    /* ���Э���½�:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    VOS_INT8                            cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain���ϴη���ע��ʱ����ͬ������Ҫ����RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* ��ǰ�Ѿ�����ʱ���������� */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU))
    {
        Gmm_TimerStop(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        return;
    }

    /* �������CSҵ����ֱ�ӷ��� */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* ������ڷ���CSҵ����������ʱ����ҵ����ʧ��������ʱ������RAU��
       ҵ����ɹ���ʱ����ʱʱ��ֱ�ӷ��� */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
