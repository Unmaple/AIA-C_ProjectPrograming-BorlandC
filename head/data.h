#ifndef _DATA_H_
#define _DATA_H_

struct daypower
{
	float Dpower[50];//ʵ��48��
	float Dgeneration[25];
	float totalDgeneration;
};

struct monthpower
{
	float Mgeneration[32];
	float totalMgeneration;
};

struct yearpower
{
	float Ypower[13];
	float totalYgeneration[];
};

struct inverter//�����
{
	float totalgeneration;
	char temperature[10];//������ڲ��¶�
	char outputmode[4];//�����ʽ
	char powerfactor;//��������
	char insulation_resistance;//��Ե����ֵ
};

struct user
{
	int Rack_type;//֧������(0Ϊ�̶���1Ϊƽ���ᣬ2Ϊ˫�ᣩ
	int Ban_num;//�����Ŀ
	int Inventer_type;//��������ͣ�0Ϊ����ʽ�������1Ϊ��ɢʽ�������
	
};
	
#endif