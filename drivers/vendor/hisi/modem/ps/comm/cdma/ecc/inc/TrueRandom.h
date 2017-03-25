#ifndef _LOIS_TRUERANDOM_H
#define _LOIS_TRUERANDOM_H

//��ͷ�ļ�����C++�����������ã�������C����ʱ��Ӧ��ȥ��extern "C"ѡ�

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
//extern "C"   // C++ option, This line should be deleted when using with C compiler
//{
    /* ���ص�Ƶ���� */
    unsigned int cGetPower(void);
    /* ���ص�ص��� */
    unsigned int cGetBattery(void);
    /* ���س�ǿ */
    unsigned int cGetRSSI(void);
    /* ��������� */
    unsigned int cGetEcio(void);
    /* ����Pilot strength */
    unsigned int cGetPilotStrength(void);
    /* ����ʱ�� */
    unsigned int cGetTime(void);

    /* ��ȡһ�������
     *
     * ������
     * [OUT] pbOut�����ڻ�ȡ������Ļ�����
     * [IN] iLen��pbOut�������ĳ��ȣ���Ҫ��ȡ����������ֽڳ���
     *
     * ����ֵ��
     * ʵ�ʷ��ص�������ֽڳ���
    */
    int TrueRandom (unsigned char *pbOut, int iLen);
//}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif // #ifndef _LOIS_TRUERANDOM_H

