#ifndef SM_ALGORITHM_HEADER_2008_10_
#define SM_ALGORITHM_HEADER_2008_10_

// ----------------------------------------------------------------
// ��������
#define SKEY_LEN			(128/8)	// �ԳƼ��ܵ���Կ���ȣ��ֽڵ�λ
#define BLOCK_LEN_BYTE		(128/8)	// ���鳤��128 bit
#define BLOCK_LEN_BIT		128


#ifndef SERVER_VER_		// �������汾��ʹ��
	#define ECC_KEY_LEN			(192/8)	// �ֽڵ�λ��32�ֽڣ�192 bit ECC
#endif	// SERVER_VER_


/*
	�൱���ǵ���g_loisNoise.Do();
*/
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
int NoiseDo();



/**************** �����ӽ��ܳ�ʼ������ ****************************
   ������
   [IN]init_key������/���ܵ���Կָ�룬����ָ�򳤶�ΪSKEY_LEN�Ļ�����
   [IN]outgoing_call����ʾ�����ܻ����ն��Ƿ������У�1Ϊ���У�0Ϊ���С�

   ����ֵ��
   ����ֵΪ0��ʾ��ʼ���ɹ�
******************************************************************/

int init_voice(const unsigned char *init_key,
		unsigned long outgoing_call);





/**************** �������ܺ��� ************************************
   ������
   [IN] input_data��������������������ݵ�ָ�룻
   [OUT]output_data��������������ܺ�������ݵ�ָ�룻
   [IN] input_len��������������������ݵĳ��ȣ���bitΪ��λ��
   [OUT]output_len��������������ܺ����ݵĳ��ȣ���bitΪ��λ��

   ����ֵ��
   ����ֵΪ0��ʾ���ܳɹ�
******************************************************************/

int encrypt_voice(const unsigned char *input_data,
		unsigned char *output_data,
		unsigned long input_len,
		unsigned long *output_len);





/**************** �������ܺ��� ************************************
   ������
   [IN] input_data��������������������ݵ�ָ�룻
   [OUT]output_data��������������ܺ�������ݵ�ָ�룻
   [IN] input_len��������������������ݵĳ��ȣ���bitΪ��λ��
   [OUT]output_len��������������ܺ����ݵĳ��ȣ���bitΪ��λ��

   ����ֵ��
   ����ֵΪ0��ʾ���ܳɹ�
******************************************************************/

int decrypt_voice(const unsigned char *input_data,
		unsigned char *output_data,
		unsigned long input_len,
		unsigned long *output_len);




#ifndef SERVER_VER_		// �������汾��ʹ��

/**************** ECC��ʼ������ ***********************************
   ���ܣ�
   ��ʼ��ECC��������ϵͳ��ʼ��ʱ����һ�Σ����Ԥ����
   ����ֵ��
   ��ʼ���ɹ�����1�����򷵻�0
******************************************************************/

int ECC_Init(void);





/**************** ECC��˽Կ�����ɺ��� *****************************
   ������
   [OUT]priv_key��˽Կ�ռ�ĵ�ַ���ÿռ���ڵ���ECC_KEY_LEN�ֽڣ����ʱ�ÿռ��ڴ洢˽Կ��
   [OUT]pub_key����Կ����ĵ�ַ���ÿռ�Ӧ�ô��ڵ���(2*ECC_KEY_LEN+1)���ֽڣ����ʱ�ÿռ��ڴ洢��Կ

   ����ֵ��
   �ɹ�����1�����򷵻�0
******************************************************************/

int ecc192_genkey(unsigned char *priv_key,
		unsigned char *pub_key);





/**************** ECC��Կ���ܺ��� *********************************
   ���ܣ�
   ʹ�ù�Կ�������ݣ�����KMC��Կ�Դ�������KMC����Ϣ���м��ܣ�

   ������
   [OUT]pout��������Ŀռ�ĵ�ַ
   [IN] lenout�����Ļ������ĳ���
   [IN] pin�����Ŀռ�ĵ�ַ
   [IN] len�����ĵĳ���
   [IN] pub_key����Կ

   ����ֵ��
   �ɹ�ʱ�������ĵĳ��ȣ�ʧ��ʱ���ظ���
******************************************************************/

int ecc192_encrypt(unsigned char * pout,
		int lenout,
		const unsigned char * pin,
		int len,
		const unsigned char * pub_key);





/**************** ECC˽Կ���ܺ��� *********************************
   ���ܣ�
   ʹ��˽Կ���ܣ������ն���ʱ˽Կ������KMC����Ϣ���н��ܻ�ûỰ��ԿKs��

   ������
   [OUT]pout��������Ŀռ�ĵ�ַ
   [IN] lenout, ���Ļ������ĳ���
   [IN] pin�����Ŀռ�ĵ�ַ
   [IN] len�����ĵĳ���
   [IN] priv_key��˽Կ��ַ

   ����ֵ��
   �ɹ�ʱ�������ĵĳ��ȣ�ʧ��ʱ���ظ���
******************************************************************/

int ecc192_decrypt(unsigned char * pout,
		int lenout,
		const unsigned char * pin,
		int len,
		const unsigned char * priv_key);





/**************** ECC��Կǩ����֤���� *****************************

   ���ܣ�
   ʹ�ù�Կ��֤ǩ��������KMC��Կ��������KMC����Ϣ����ǩ����֤��

   ������
   [IN]pub _key����Կ�ռ��ַ
   [IN]in������֤ǩ�����ݵĵ�ַ
   [IN]in_len������֤ǩ�����ݵĳ���
   [IN]sign��ǩ��ֵ
   [IN]sign_len��ǩ��ֵ�ĳ���

   ����ֵ��
   �ɹ�ʱ����1��ʧ��ʱ����0��
******************************************************************/

int ecc192_verify(const unsigned char * pub_key,
		const unsigned char * in,
		int in_len,
		const unsigned char * sign,
		int sign_len);


#endif // SERVER_VER_�������汾��ʹ��

#ifdef __cplusplus
#if __cplusplus
		}
#endif
#endif

#endif // SM_ALGORITHM_HEADER_2008_10_