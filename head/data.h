#ifndef _DATA_H_
#define _DATA_H_

struct daypower
{
	float Dpower[50];//实际48个
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

struct inverter//逆变器
{
	float totalgeneration;
	char temperature[10];//逆变器内部温度
	char outputmode[4];//输出方式
	char powerfactor;//功率因数
	char insulation_resistance;//绝缘抗阻值
};

struct user
{
	int Rack_type;//支架类型(0为固定，1为平单轴，2为双轴）
	int Ban_num;//组件数目
	int Inventer_type;//逆变器类型（0为集中式逆变器，1为集散式逆变器）
	
};
	
#endif