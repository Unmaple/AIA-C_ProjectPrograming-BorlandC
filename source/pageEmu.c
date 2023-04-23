/*****************************************
Mimage.c
COPYRIGHT:  Zengmingjie
FUNCTION:   store basic graphics elements and render them
DATE:       2023/2/23-4/13(Debug and Reinforcement)
Available code lines:ZMJ-about1320lines
******************************************/
/******************
��ʹ�õ���������ţ�
0-1 �ذ�
2-25 �� ̫���ܰ壬����2-13��֧�ܣ�15Ϊ�嶥
26-49 �� ̫���ܰ壬����ǰ12��֧�ܣ�39Ϊ�嶥
50-73 �� ̫���ܰ壬����ǰ12��֧�ܣ�63Ϊ�嶥
74-97 �� ̫���ܰ壬����ǰ12��֧�ܣ�39Ϊ�嶥
98-121 �� ̫���ܰ壬����ǰ12��֧�ܣ�63Ϊ�嶥
��ʹ�õĵ����
0-3 �ذ�
4-83 �� ̫���ܰ�
84-?-1: ���������ĵ�
?-��+ 59����Ӱ�����ĵ�

******************/		
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
//#include<math.h>
#include"mimage.h"
#include"mmouse.h"
#include"MZFK.h"
//#include<conio.h>
//#include"kairo.h"
#include"image.h"
#include"d3room.h"
#include"Notice.h"
#include"pageEmu.h"
//#include"math.h"
#include"MyMath.h" 
#include"ftoa.h"
#include"pdata.h"
//#include"string.h"
#define W 119
#define S 115
#define A 97
#define D 100
#define Z 122
#define X 120
#define Esc 27
#define STEP 2
// #define abs(x) ((x) > 0 ? (x) : (-x))
// #define min(x, y) (x < y ? x : y)
// #define max(x, y) (x > y ? x : y)

#define SpotHeight 150
#define BANStartX 500
#define BANStartZ -250
#define BANJIANJUX -180
#define BANJIANJUZ 500;
#define BANHOU 3
#define BANY 165
#define BANCHANG 200
#define BANKUAN 20
#define DOUBLEBANCHANG 60
#define DOUBLEZHUCHANG 6
#define CLOUDHEIGHT 500
#define SUNBANMAX 20

;//��Ҫһ���̳̹��ܣ�����棩(0406�����)

static struct SetOfColor ORICOLOR =  {{0x00,0x00,0x00,0x00, 0xA8,0xA8,0xA8,0xA8, 0x54,0x54,0x54,0x54, 0xFC,0xFC,0xFC,0xFC},
							         {0x00,0x00,0xA8,0xA8, 0x00,0x00,0x54,0xA8, 0x54,0x54,0xFC,0xFC, 0x54,0x54,0xFC,0xFC},
							         {0x00,0xA8,0x00,0xA8, 0x00,0xA8,0x00,0xA8, 0x54,0xFC,0x54,0xFC, 0x54,0xFC,0x54,0xFC}};
static struct SetOfColor CLOUDYCOLOR={{0x00,0x00,0x00,0x00, 0xA2,0xA2,0xA2,0xA2, 0x4F,0x4F,0x4F,0x8F, 0xF4,0xF4,0xF4,0xFC},
							         {0x00,0x00,0xA2,0xA2, 0x00,0x00,0x4E,0xA2, 0x4F,0x4F,0xF4,0xF4, 0x4F,0x4F,0xF4,0xFC},
							         {0x00,0xA2,0x00,0xA2, 0x00,0xA2,0x00,0xA2, 0x4F,0xF4,0x4F,0xF4, 0x4F,0xF4,0x4F,0xFC}};
static struct SetOfColor RAINYCOLOR ={{0x00,0x00,0x00,0x00, 0x9C,0x9C,0x9C,0x9C, 0x4A,0x4A,0x4A,0x4A, 0xE8,0xE8,0xE8,0xFC},
							         {0x00,0x00,0x9C,0x9C, 0x00,0x00,0x4A,0x9C, 0x4A,0x4A,0xE8,0xE8, 0x4A,0x4A,0xE8,0xFC},
							         {0x00,0x9C,0x00,0x9C, 0x00,0x9C,0x00,0x9C, 0x4A,0xE8,0x4A,0xE8, 0x4A,0xE8,0x4A,0xFC}};
static struct SetOfColor BLITZCOLOR= {{0x00,0x00,0x00,0x00, 0x98,0x98,0x94,0x98, 0x44,0x44,0x44,0x44, 0xDC,0xDC,0xDC,0xFC},
							         {0x00,0x00,0x98,0x98, 0x00,0x00,0x44,0x98, 0x44,0x44,0xDC,0xDC, 0x44,0x44,0xDC,0xFC},
							         {0x00,0x98,0x00,0x98, 0x00,0x98,0x00,0x98, 0x44,0xDC,0x44,0xDC, 0x44,0xDC,0x44,0xFC}};
static struct SetOfColor NIGHTCOLOR= {{0x00,0x00,0x00,0x00, 0x98,0x98,0x94,0x98, 0x44,0x44,0x44,0x44, 0xDC,0xDC,0xDC,0xFC},
							         {0x00,0x00,0x98,0x98, 0x00,0x00,0x44,0x98, 0x44,0x44,0xDC,0xDC, 0x44,0x44,0xDC,0xFC},
							         {0x00,0x98,0x00,0x98, 0x00,0x98,0x00,0x98, 0x44,0xDC,0x44,0xDC, 0x44,0xDC,0x44,0xFC}};

struct SUNBAN
{
	int Tx;
	int Tz;
	int Type;
};

struct BANS
{
	struct SUNBAN SunBanBuffer[SUNBANMAX];
	int SUNBANNUM;
};
							  


//struct WeatherYearData WYDATA[10];
//0415TODO:��Ҫ��ӵ����л�                                  DONE
//0415TODO:���iStep�л������٣��ǵ�stepһ��Ҫ���ܹ�0��270�� DONE
//0415TODO:��Ӹ��ݵ������·��л�̫���߶Ƚ�                  DONE
//�人30.5N������36.5N
//0415TODO:�������(while(kbhit()))                          DONE
//0415TODO:���߱���Ч���޸�                                  DONE
//0415TODO:���������޸�                                      DONE
//0415TODO:ƽ������������޸�                                DONE

int pageEmu(struct user U,struct WeatherYearData WHWYDATA[],struct WeatherYearData HDWYDATA[])//��Ҫ��ӵ�ͼ��̫���ܰ�������Ϊ����,BANTYPE 0Ϊ�̶�ʽ��1Ϊƽ���ᣬ2Ϊ˫�ᣬBANNUMȷ�����Ӹ�����Ԥ��Ӧ����1~10����
{
	int i,j,k, height, width,Fai = 270,Xita = -30,exit = 0, PAUSE = 0,
		BANPos,ElectricStrength = 1,ShowName = 0,WEATHER = 0,WINDOW = -1,   //0����1����2����
		StellarHeightAngle = 90-53, CameraMode = 0,ChangeWeather = 0, DIQU = 1, iSpeed = 0;//CameraMode 0Ϊ�����ӽǣ�1Ϊ̫���ӽǣ�2Ϊ�����ӽ�
		//��ʱ����,CLOUDON = 0 test = 10.0/2.0,
	const int  CAMERAPOS = -2000;
	struct Button B1, BName, BPause, BItems[SUNBANMAX + 4], 
		   BDate[6], BTutorial, BChart, BCamera, BWeather, BSpeed[3], BDiqu;
	struct Window WItems[SUNBANMAX + 4], WTutorial;
	double Zoom = 0.4,TempCos,TempSin;
	float DayPowerBuffer[26];
	struct TransformMatrix TM;
	//char ch;
	
	struct DATE CurrentDate = {2023,1,1};
	int days;
	//���Ǽ���WYDATA��RANDNUM����ʼ������
	struct BANS EmuBans;
	setbkcolor(0);//��Ҫ���
	//
	//�˵����ְ�ťUI�����ʼ��
	strcpy(B1.Lines,"�˳�");
	B1.x1 = 500;
	B1.y1 = 50;
	B1.x2 = 560;
	B1.y2 = 85;
	B1.EdgeColor = 2;
	B1.InnerColor = 15;
	B1.ZIHAO = 24;
	strcpy(BName.Lines,"��ʾ����");
	BName.x1 = 500;
	BName.y1 = 95;
	BName.x2 = 625;
	BName.y2 = 130;
	BName.EdgeColor = 2;
	BName.InnerColor = 15;
	BName.ZIHAO = 24;
	strcpy(BPause.Lines,"��ͣ");
	BPause.x1 = 500;
	BPause.y1 = 10;
	BPause.x2 = 570;
	BPause.y2 = 45;
	BPause.EdgeColor = 2;
	BPause.InnerColor = 15;
	BPause.ZIHAO = 24;
	strcpy(BChart.Lines,"ͼ��");
	BChart.x1 = 570;
	BChart.y1 = 50;
	BChart.x2 = 630;
	BChart.y2 = 85;
	BChart.EdgeColor = 2;
	BChart.InnerColor = 15;
	BChart.ZIHAO = 24;
	strcpy(BCamera.Lines,"���������");
	BCamera.x1 = 500;
	BCamera.y1 = 140;
	BCamera.x2 = 630;
	BCamera.y2 = 165;
	BCamera.EdgeColor = 2;
	BCamera.InnerColor = 15;
	BCamera.ZIHAO = 16;
	strcpy(BWeather.Lines,"��");
	BWeather.x1 = 570;
	BWeather.y1 = 175;
	BWeather.x2 = 630;
	BWeather.y2 = 205;
	BWeather.EdgeColor = 2;
	BWeather.InnerColor = 15;
	BWeather.ZIHAO = 24;
	strcpy(BDiqu.Lines,"�人");
	BDiqu.x1 = 500;
	BDiqu.y1 = 175;
	BDiqu.x2 = 560;
	BDiqu.y2 = 205;
	BDiqu.EdgeColor = 2;
	BDiqu.InnerColor = 15;
	BDiqu.ZIHAO = 24;
	//�����޸�UI��ʼ��
	for(j = 0; j < 6; j ++)
	{
		if(j%2 == 0)
		{
			strcpy(BDate[j].Lines,"<");
		}
		else
		{
			strcpy(BDate[j].Lines,">");
		}
		
		BDate[j].x1 = 20+24*j+24*(j/2);
		BDate[j].y1 = 25;
		BDate[j].x2 = 20+24*j+24*(j/2)+16;
		BDate[j].y2 = 40;
		BDate[j].EdgeColor = 2;
		BDate[j].InnerColor = 15;
		BDate[j].ZIHAO = 8;
	}
	strcpy(BSpeed[0].Lines,"1x");
	strcpy(BSpeed[1].Lines,"3x");
	strcpy(BSpeed[2].Lines,"5x");
	for(j = 0; j < 3; j ++)
	{
		BSpeed[j].x1 = 20+24*j;
		BSpeed[j].y1 = 65;
		BSpeed[j].x2 = 40+24*j;
		BSpeed[j].y2 = 80;
		BSpeed[j].EdgeColor = 2;
		BSpeed[j].InnerColor = 15;
		BSpeed[j].ZIHAO = 8;
	}
	BSpeed[0].InnerColor = 14;
	//���ӳ�ʼ�����ڽ������ҳ������ʧ
	EmuBans.SUNBANNUM = max(1,min(U.Ban_num,12));//��Ҫ<=12������ᳬ���ذ巶Χ
	for(j = 0; j < EmuBans.SUNBANNUM; j ++)
	{
		EmuBans.SunBanBuffer[j].Tx = j%6;
		EmuBans.SunBanBuffer[j].Tz = j/6;
		EmuBans.SunBanBuffer[j].Type = U.Rack_type;
	}

	//�����������ֳ�ʼ��
	for(j = 0; j < EmuBans.SUNBANNUM; j ++)
	{
		if(EmuBans.SunBanBuffer[j].Type == 1)
		{
			strcpy(BItems[j].Lines,"ƽ����̫���ܰ�");
			strcpy(WItems[j].Lines[1],"ƽ����̫���ܰ�");
			strcpy(WItems[j].Lines[5],  "PDZ-450W-P");
		}
		else if(EmuBans.SunBanBuffer[j].Type == 2)
		{
			strcpy(BItems[j].Lines,"˫��̫���ܰ�");
			strcpy(WItems[j].Lines[1],"˫��̫���ܰ�");
			strcpy(WItems[j].Lines[5],  "SZ-400W-P");
		}
		else
		{
			strcpy(BItems[j].Lines,"�̶�̫���ܰ�");
			strcpy(WItems[j].Lines[1],"�̶�̫���ܰ�");
			strcpy(WItems[j].Lines[5], "GD-500W-P");
		}
		
		BItems[j].x1 = 500;
		BItems[j].y1 = 50;
		BItems[j].x2 = 580;
		BItems[j].y2 = 100;
		BItems[j].EdgeColor = 2;
		BItems[j].InnerColor = 15;
		BItems[j].ZIHAO = 16;
		strcpy(WItems[j].Lines[0],  "����");
		//strcpy(WItems[j].Lines[1],  "������");//�Ϸ��Ѷ���
		strcpy(WItems[j].Lines[2],  "SN:");
		strcpy(WItems[j].Lines[3],  "******075701");
		strcpy(WItems[j].Lines[4],  "�ͺ�");
		strcpy(WItems[j].Lines[6],  "��ǰ����");
		strcpy(WItems[j].Lines[7],  "345.24W");
		strcpy(WItems[j].Lines[8],  "���");
		strcpy(WItems[j].Lines[9],  "12.3");
		strcpy(WItems[j].Lines[10],  "��λ��");
		strcpy(WItems[j].Lines[11],  "23.4");
		strcpy(WItems[j].Lines[12],  "Hello!");
		strcpy(WItems[j].Lines[13],  "������");
		WItems[j].LineNum = 12;
		WItems[j].on = 0;
	}
	j = EmuBans.SUNBANNUM;
	strcpy(BItems[j].Lines,"������");
	BItems[j].x1 = 500;
	BItems[j].y1 = 50;
	BItems[j].x2 = 580;
	BItems[j].y2 = 100;
	BItems[j].EdgeColor = 2;
	BItems[j].InnerColor = 15;
	BItems[j].ZIHAO = 16;
	strcpy(WItems[j].Lines[0],  "����");
	strcpy(WItems[j].Lines[1],  "���������");
	strcpy(WItems[j].Lines[2],  "SN:");
	strcpy(WItems[j].Lines[3],  "114514");
	strcpy(WItems[j].Lines[4],  "�ͺ�");
	strcpy(WItems[j].Lines[5],  "30A40A50A60A");//��Դhttp://www.sdywpower.com/product/595.html
	strcpy(WItems[j].Lines[6],  "����");
	strcpy(WItems[j].Lines[7],  "���ƶ�·̫���ܵ�ط�������س��");
	strcpy(WItems[j].Lines[8],  "�Լ����ظ�̫������������ع���");
	strcpy(WItems[j].Lines[9],  "Ŀǰ��Ч��̫���ܰ���");
	{
		char sBANNUM[10];
		my_itoa(U.Ban_num,sBANNUM,10);
		strcpy(WItems[j].Lines[10],  sBANNUM);
	}
	strcpy(WItems[j].Lines[11],  "Ŀǰ��Ч�ܷ�����");
	//����ÿѭ���޸�
	WItems[j].LineNum = 13;
	WItems[j].on = 0;
	j = EmuBans.SUNBANNUM + 1;
	strcpy(BItems[j].Lines,"������");
	BItems[j].x1 = 500;
	BItems[j].y1 = 50;
	BItems[j].x2 = 580;
	BItems[j].y2 = 100;
	BItems[j].EdgeColor = 2;
	BItems[j].InnerColor = 15;
	BItems[j].ZIHAO = 16;
	strcpy(WItems[j].Lines[0],  "����");
	strcpy(WItems[j].Lines[1],  "������");
	strcpy(WItems[j].Lines[2],  "SN:");
	strcpy(WItems[j].Lines[3],  "1919810");
	strcpy(WItems[j].Lines[4],  "�ͺ�");
	strcpy(WItems[j].Lines[5],  "6-CNJ-250");
	//��Դhttps://isite.baidu.com/site/wjz2kt4w/7a740000-2d31-49cd-95f6-2c5ab2fc07c0?fid=nH01PHbvn1DLnjDkPW63Pjb1PjIxnWcdg1D&ch=4&bd_vid=10865824235531637379&bd_bxst=EiaKs3DQ0agrkcO900DD0aZuS6AwFb00000000J43oxtYrld4e5m00000000000BnDRswbDdPjI7fYR4wjF7PYDvnH6zP1Iaf1IarRwKfY7tna0Lrjn4njD1wW-7n1n1wRPAwjR3nHcvnD7AnWF7nHc4rUu6ws-MRGwU0f000PUpyis50000rxUT3L60000f0ZnKj_zoYxHDLQiBkPzd4e5mPnzoYxHDLQiBkPzd4e5msQHNYopo12hd4qiYQnHl1SEiJogD12EwqnHTYrld4e5mVo1HYaD00nO4Df6
	strcpy(WItems[j].Lines[6],  "����");
	strcpy(WItems[j].Lines[7],  "��ʱ�������");
	strcpy(WItems[j].Lines[8],  "�����������ʹ����ȶ�");
	WItems[j].LineNum = 9;
	WItems[j].on = 0;
	
	//�̳����UI
	strcpy(BTutorial.Lines,"�̳�");
	BTutorial.x1 = 575;
	BTutorial.y1 = 10;
	BTutorial.x2 = 635;
	BTutorial.y2 = 45;
	BTutorial.EdgeColor = 2;
	BTutorial.InnerColor = 15;
	BTutorial.ZIHAO = 24;
	strcpy(WTutorial.Lines[0],  "W:Camera Upwards");
	strcpy(WTutorial.Lines[1],  "S:Camera Downwards");
	strcpy(WTutorial.Lines[2],  "A:Camera Leftwards");
	strcpy(WTutorial.Lines[3],  "D:Camera Rightwards");
	strcpy(WTutorial.Lines[4],  "Z:Camera Zoom In");
	strcpy(WTutorial.Lines[5],  "X:Camera Zoom Out");
	strcpy(WTutorial.Lines[6],  "���̳̿��ٴιۿ��˽̳�");
	strcpy(WTutorial.Lines[7],  "����������л������ģʽ");
	strcpy(WTutorial.Lines[8],  "Ԥ��һ�۲�̫����Ԥ������������Ч���ں�������");
	strcpy(WTutorial.Lines[9],  "Ԥ����۲�������Ԥ�������");
	strcpy(WTutorial.Lines[10],  "Ԥ�������ģʽʱʹ�ü��̲���");
	strcpy(WTutorial.Lines[11],  "���ص����������ģʽ");
	strcpy(WTutorial.Lines[12],  "��������ǿ��ת������");
	strcpy(WTutorial.Lines[13],  "������ͷ�ɵ�������һ����ͣ����ͣ");
	WTutorial.LineNum = 14;
	WTutorial.on = 1;//TODO ���ոĳ�1
	//UI�����ʼ������
	
	MouseS = 0;
	ClrOriMap();
	
	//�˴�����Ӧ��������Դ���ݱ仯��
	AddParallelogram(-1000,-SpotHeight,-1000,
	-1000,-SpotHeight,1000,
	1000,-SpotHeight,-1000,0,10);
	AddCube(-600,145-SpotHeight,-600,
			-600,145-SpotHeight,600,
			600,145-SpotHeight,-600,
			-600,-SpotHeight,-600,0,6);

	i = 300;	
	
	AddBANS(EmuBans);
	
	GenerateTransformMatrix(&TM,Xita,Fai,Zoom);
	//���λ�õ��һ���ģ�Ҳ����ֱ��ÿ֡����
	SetColor(ORICOLOR);
	if(DIQU == 1)
	{
		WEATHER = (5 - WHWYDATA[CurrentDate.year-2023].DATA[CurrentDate.month][CurrentDate.day])%3;
	}
	else
	{
		WEATHER = (5 - HDWYDATA[CurrentDate.year-2023].DATA[CurrentDate.month][CurrentDate.day])%3;
	}
	for(i = 150;exit == 0;)//
	{
		//�޸Ķ���
		GenerateTransformMatrix(&TM,Xita,Fai,Zoom);//�����ṩ���ӽ����ݼ�������ת������
		BANPos = EditBANS(EmuBans,i);//����ʱ���޸İ�����̬�����������޸İ��ӵ�λ�ã�
		SetColorTable(WEATHER,i,&ChangeWeather); //��������������ɫ��
		//������Ⱦ˳��
		QueueReset();
		SetRenderQueue(Fai,EmuBans.SUNBANNUM,Xita);//�˴����Լ�������Ƿ���Կ��������ƽ����ȷ����ʾ˳��
		SetElectricStrength(i,&ElectricStrength);//����ʱ�����õ�����������
		//���ƶ���
		DrawStellarAndShadow(i,TM,Zoom,WEATHER,EmuBans, StellarHeightAngle);//�����������Ӱ
		ColorWires(ElectricStrength, i);//�����ڴ˴��ĵ��ߴ���ʱ�Ļ�ɫ����ռ��
		D3FullVectorMapDotTransform(TM,CAMERAPOS);//���-1000��ת������������������ԭ���λ�ã������͸�ӵ�Ч��
		//0304��Ϊ͸�ӵ�3dЧ���в�û�����ضϣ�����1000��������ܳ����ж��������������
		//������������������Ҫ��⣬������zoom�Ĵ�С�Ͷ���Ĵ�С
		drawD3FullVectorMap();
		DrawWeatherEffect(WEATHER, PAUSE);//��������Ч��
		
		//��ÿ���������������OR����
		if(ShowName)
		{
			for(j = 0; j < EmuBans.SUNBANNUM; j ++)//�˴�returnOrder�����ǵ���ţ���Ҫ��ϸ����λ��
			{
				BItems[j].x1 = 320+ReturnIOrderZ(j*16+PRECUBEDOT)-68;
				//����λ�ò����İ�ť����Ҫ���и�ɼ������б���㷨����notice.c�����MRBar��Ҫ�޸�
				//���޸�MRBarʵ�֣������MRBar��⣬����Notice.c����ɼ��+ReturnIOrderY(j*24+2)+ReturnIOrderZ(j*24+2)
				BItems[j].y1 = 240-ReturnIOrderY(j*16+PRECUBEDOT)-20;
				BItems[j].x2 = BItems[j].x1+136;
				BItems[j].y2 = BItems[j].y1+23;
				RenderButton(BItems[j]);//ReturnIOrderY(j*24+2) + 30*j
			}
			j = EmuBans.SUNBANNUM;
			BItems[j].x1 = 320+ReturnIOrderZ(EmuBans.SUNBANNUM*16+PRECUBEDOT + 6)-68;
			BItems[j].y1 = 240-ReturnIOrderY(EmuBans.SUNBANNUM*16+PRECUBEDOT + 6)-20;
			BItems[j].x2 = BItems[j].x1+136;
			BItems[j].y2 = BItems[j].y1+23;
			RenderButton(BItems[j]);
			j = EmuBans.SUNBANNUM + 1;
			BItems[j].x1 = 320+ReturnIOrderZ(EmuBans.SUNBANNUM*16+PRECUBEDOT + 30)-68;
			BItems[j].y1 = 240-ReturnIOrderY(EmuBans.SUNBANNUM*16+PRECUBEDOT + 30)-20;
			BItems[j].x2 = BItems[j].x1+136;
			BItems[j].y2 = BItems[j].y1+23;
			RenderButton(BItems[j]);
		}
		
		//����ť��
		RenderButton(B1);
		RenderButton(BName);
		RenderButton(BPause);
		RenderButton(BTutorial);
		RenderButton(BChart);
		RenderButton(BCamera);
		RenderButton(BDiqu);
		if(WEATHER == 0)
		{
			strcpy(BWeather.Lines,"��");
		}
		else if(WEATHER == 1)
		{
			strcpy(BWeather.Lines,"��");
		}
		else
		{
			strcpy(BWeather.Lines,"��");
		}
		RenderButton(BWeather);
		
		for(j = 0; j < 6; j ++)
		{
			RenderButton(BDate[j]);
		}
		for(j = 0; j < 3; j ++)
		{
			RenderButton(BSpeed[j]);
		}
		ShowDate(CurrentDate,i);
		
		//������
		if(WINDOW != -1)
		{

			if(WINDOW < EmuBans.SUNBANNUM)
			{
				char FWJ[10], QJ[10],sPower[32];
				//float Power = 
				itoa(BANPos+90,FWJ,10);
				
				//30-((BANPos-180)<0?BANPos-180:180-BANPos)
				
				if(EmuBans.SunBanBuffer[j].Type == 1)
				{
					itoa(BANPos-180,QJ,10);
					strcpy(WItems[WINDOW].Lines[11], "������");
					strcpy(WItems[WINDOW].Lines[9], QJ);
				}
				else if(EmuBans.SunBanBuffer[j].Type == 2)
				{
					itoa(30-((BANPos-180)<0?BANPos-180:180-BANPos),QJ,10);
					strcpy(WItems[WINDOW].Lines[11], FWJ);
					strcpy(WItems[WINDOW].Lines[9], QJ);
				}
				else
				{
					strcpy(WItems[WINDOW].Lines[11], "������");
					strcpy(WItems[WINDOW].Lines[9], "������");
				}
				//TODO
				// sPower
				my_ftoa(DayPowerBuffer[((i+90)%360)/15],2,sPower);
				strcpy(WItems[WINDOW].Lines[7],sPower);
				//ENDOFTODO
			}
			else if(WINDOW == EmuBans.SUNBANNUM)
			{
				//TODO;
				char sPower[32];
				//�������������ʾ��ǰ�ܹ���
				my_ftoa(DayPowerBuffer[((i+90)%360)/15] * U.Ban_num,2,sPower);
				strcpy(WItems[WINDOW].Lines[12],  sPower);
				//ENDOFTODO
				;
			}
			else if(WINDOW == EmuBans.SUNBANNUM + 1)
			{
				//TODO;
				//�����飬��ʾ��ǰ���������
				//ENDOFTODO
				;
			}
			
			Render(WItems[WINDOW]);
		}
		Render(WTutorial);
		
		ShadowReset();//������Ӱ
		
		
		//����Ϊ�û������ļ��
		MRnewmouse(&MouseX,&MouseY,&press);
		if(WINDOW != -1)//�����˴�����������ڵļ��
		{
			if(Detect(&(WItems[WINDOW])) == 2)
			{
				WINDOW = -1;
			}
		}
		else if(WTutorial.on == 1)
		{
			//MRnewmouse(&MouseX,&MouseY,&press);
			Detect(&(WTutorial));
		}
		else//��û�����ڣ�������̺Ͱ�ť
		{
			int buttonActionExist = 0;
			//��ⰴ��
			if(checkKeyboard(&Fai, &Xita, &Zoom, &exit))
			{
				CameraMode = 0;
				strcpy(BCamera.Lines,"���������");
				flushKeyboardBuffer();//�˺������ã���bug
			}
			//����MouseS
			if(mouse_press(0,0,640,480)==2)
			{
				MouseS=0;
			}
			
			//MRnewmouse(&MouseX,&MouseY,&press);
			
			
			//����Ƿ��°�ť
			//����Ƿ����˳�
			if(DetectButton(B1) == 1)
			{
				buttonActionExist = 1;
				exit = 12;
			}
			
			if(DetectButton(BChart) == 1)
			{
				buttonActionExist = 1;
				exit = 3;
			}
			
			if(DetectButton(BCamera) == 1)
			{
				buttonActionExist = 1;
				CameraMode = (CameraMode+1)%3;
				if(CameraMode == 0)
				{
					strcpy(BCamera.Lines,"���������");
				}
				else if(CameraMode == 1)
				{
					strcpy(BCamera.Lines,"̫�������");
				}
				else
				{
					strcpy(BCamera.Lines,"��������");
				}
				delay(40);
				
			}
			
			if(DetectButton(BDiqu) == 1)
			{
				buttonActionExist = 1;
				DIQU = (DIQU+1)%2;
				if(DIQU == 1)
				{
					strcpy(BDiqu.Lines,"�人");
				}
				else
				{
					strcpy(BDiqu.Lines,"����");
				}
				//�е��������WEATHER, StellarHeightAngle, DayPowerBuffer
				EditPower(&WEATHER, &StellarHeightAngle, DIQU, CurrentDate, DayPowerBuffer, U,WHWYDATA,HDWYDATA);
				delay(40);
				
			}
			
			if(DetectButton(BTutorial) == 1)
			{
				buttonActionExist = 1;
				WTutorial.on = 1;
			}
			
			if(DetectButton(BWeather) == 1)
			{
				buttonActionExist = 1;
				WEATHER = (WEATHER+1)%3;
				if(WEATHER == 0)
				{
					strcpy(BWeather.Lines,"��");
				}
				else if(WEATHER == 1)
				{
					strcpy(BWeather.Lines,"��");
				}
				else
				{
					strcpy(BWeather.Lines,"��");
				}
				ChangeWeather = 1;
				//��Ҫ�޸� DayPowerBuffer ��ֵ���������ɣ�
				real_timePOWER(&U,CurrentDate,DIQU,2-WEATHER,DayPowerBuffer);
				delay(40);
				
			}
			
			//����Ƿ����Ƿ���ʾ���ֵ��л���ť
			if(DetectButton(BName) == 1)
			{
				buttonActionExist = 1;
				if(ShowName == 1)
				{
					ShowName = 0;
					strcpy(BName.Lines,"��ʾ����");
				}
				else
				{
					ShowName = 1;
					strcpy(BName.Lines,"��������");
				}
			}
			
			//����Ƿ�����ͣ
			if(DetectButton(BPause) == 1)
			{
				buttonActionExist = 1;
				if(PAUSE == 1)
				{
					PAUSE = 0;
					strcpy(BPause.Lines,"��ͣ");
				}
				else
				{
					PAUSE = 1;
					strcpy(BPause.Lines,"����");
				}
			}
			//��ͳһ�жϵ�ԭ���Ǵ�����ť��������ť�߼��ϲ��У���������if�ж�
			// if(DetectButton(BSpeed[0]) == 1)
			// {
				// buttonActionExist = 1;
				// BSpeed[iSpeed].InnerColor = 15;
				// iSpeed = 0;
				// BSpeed[iSpeed].InnerColor = 14;
			// }
			// if(DetectButton(BSpeed[1]) == 1)
			// {
				// buttonActionExist = 1;
				// BSpeed[iSpeed].InnerColor = 15;
				// iSpeed = 1;
				// BSpeed[iSpeed].InnerColor = 14;
			// }
			// if(DetectButton(BSpeed[2]) == 1)
			// {
				// buttonActionExist = 1;
				// BSpeed[iSpeed].InnerColor = 15;
				// iSpeed = 2;
				// BSpeed[iSpeed].InnerColor = 14;
			// }
			for(j = 0; j < 3; j ++)
			{
				if(DetectButton(BSpeed[j]) == 1)
				{
					buttonActionExist = 1;
					BSpeed[iSpeed].InnerColor = 15;
					iSpeed = j;
					BSpeed[iSpeed].InnerColor = 14;
					break;
				}
			}
			//������ʾ����״̬�£�����Ƿ�������TAG
			if(ShowName == 1&&buttonActionExist == 0)
			{
				for(j = EmuBans.SUNBANNUM + 2 - 1; j >= 0 ; j --)
				{
					if(DetectButton(BItems[j]) == 1)
					{
						buttonActionExist = 1;
						WItems[j].on = 1;
						WINDOW = j;
						break;
					}
				}
			}
			
			
			
			
			
			//����Ƿ������ڿ��OR����
			if(EditDate(BDate,&CurrentDate))
			{
				ChangeWeather = 1;
				//�����ں����WEATHER, StellarHeightAngle, DayPowerBuffer
				EditPower(&WEATHER, &StellarHeightAngle, DIQU, CurrentDate, DayPowerBuffer, U,WHWYDATA,HDWYDATA);
			}
		}
		
		//��������ģʽ���޸������
		if(CameraMode == 1)
		{
			SunCamera(i,&Fai, &Xita, &Zoom, StellarHeightAngle);
		}
		else if(CameraMode == 2)
		{
			BanCamera(i,&Fai, &Xita, &Zoom);
		}
		
		if(i == 270)//0��ʱ������
		{
			NextDate(&CurrentDate);
			//�����ں����WEATHER, StellarHeightAngle, DayPowerBuffer
			EditPower(&WEATHER, &StellarHeightAngle, DIQU, CurrentDate, DayPowerBuffer, U,WHWYDATA,HDWYDATA);
		}
		
		// MZFI(240,120,15,MouseX);
		// MZFI(240,150,15,MouseY);
		// MZFI(240,165,12,EmuBans.SUNBANNUM);
		D3MR();
		
		delay(40);
		if(PAUSE == 0)
		{
			if(iSpeed == 0)
			{
				i++;
			}
			else if(iSpeed == 1)
			{
				i += 3;
				i = i - (i % 3);
			}
			else
			{
				i += 5;
				i = i - (i % 5);
			}
			
			i = i%360;
		}
	}
	SetColor(ORICOLOR);
	return exit;//return to BC;
}

static int PushBan(int TriStart, int BanUp)
{
	int j;
	if(BanUp != 0)
	{
		for(j = TriStart; j < TriStart+12; j ++)
		{
			push(j);
		}
		for(j = TriStart+12; j < TriStart+24; j ++)
		{
			push(j);
		}
	}
	else
	{
		for(j = TriStart+12; j < TriStart+24; j ++)
		{
			push(j);
		}
		for(j = TriStart; j < TriStart+12; j ++)
		{
			push(j);
		}
	}
	return 0;
}

static int MAKESHADOWS(struct BANS Bans,struct D3DOT STELLAR)
{
	int i;
	for(i = 0; i < Bans.SUNBANNUM; i ++)
	{
		MakeShadow(i,STELLAR);
	}
	return 0;
}
static int MakeShadow(int BanOrder,struct D3DOT STELLAR)
{
	CreateShadow(12+PRECUBE+24*BanOrder,STELLAR.x / ((double)STELLAR.y +50),
					STELLAR.z / ((double)STELLAR.y +50),145-SpotHeight);
	CreateShadow(13+PRECUBE+24*BanOrder,STELLAR.x / ((double)STELLAR.y +50),
					STELLAR.z / ((double)STELLAR.y +50),145-SpotHeight);
	CreateShadow(2+PRECUBE+24*BanOrder,STELLAR.x / ((double)STELLAR.y +50),
					STELLAR.z / ((double)STELLAR.y +50),145-SpotHeight);
	CreateShadow(3+PRECUBE+24*BanOrder,STELLAR.x / ((double)STELLAR.y +50),
					STELLAR.z / ((double)STELLAR.y +50),145-SpotHeight);
	return 0;
}

static int LongWire(const int x1,const int z1,const int x2,const int z2, int FloorHeight, int division)
{
	int i;
	int xOffset = x2 - x1;
	int zOffset = z2 - z1;
	newWire(x1,z1,x1 + (float)xOffset/(float)division,z1 + (float)zOffset/(float)division, FloorHeight);
	for(i = 2; i <= division; i ++)
	{
		linkWires(x1 + (float)xOffset*(float)i/(float)division,z1 + (float)zOffset*(float)i/(float)division, FloorHeight);
	}
	return 0;
}

static int AddBANS(struct BANS Bans)
{
	int i;
	int height = 100;
	int width = 60;
	for(i = 0; i < Bans.SUNBANNUM; i ++)
	{
		AddBAN(Bans.SunBanBuffer[i]);
	}
	AddCube(-450,145-SpotHeight,width/2,
			-500,145-SpotHeight,width/2,
			-450,145-SpotHeight,-width/2,
			-450,145-SpotHeight+height,width/2,12,8);
	AddCylinder(-540,0,100,100,20,60,12,2);		
	LongWire(-600,0,BANStartX,0, 145-SpotHeight, (BANStartX - (-300) )/ 20);
	for(i = 0; i < Bans.SUNBANNUM; i ++)
	{
		int xOFFSET = BANStartX+BANJIANJUX*Bans.SunBanBuffer[i].Tx, zOFFSET = BANStartZ+Bans.SunBanBuffer[i].Tz*BANJIANJUZ;
		LongWire(xOFFSET,0,xOFFSET,zOFFSET,145-SpotHeight, 10);
	}
	return 0;
}

static int EditBANS(struct BANS Bans, int j)//,int BANPos
{
	int i, BANPos;
	if(j >= 60 && j <= 120)
	{
		BANPos = j+90;
	}
	else
	{
		BANPos = 120-((j+240)%360)/5+90;
	}
	
	for(i = 0; i < Bans.SUNBANNUM; i ++)//typeΪ0����Ҫ�༭
	{
		if(Bans.SunBanBuffer[i].Type == 1)
		{
			EditBAN(Bans.SunBanBuffer[i].Tx,Bans.SunBanBuffer[i].Tz,i,BANPos);
		}
		
		if(Bans.SunBanBuffer[i].Type == 2)
		{
			EditDoubleBan(Bans.SunBanBuffer[i].Tx,Bans.SunBanBuffer[i].Tz,i,
						  BANPos+90,-30+((BANPos-180)<0?BANPos-180:180-BANPos));//360-BANPos+((BANPos-90)<0?BANPos:180-BANPos)
		}
	}
	return BANPos;
}

static int AddBAN(struct SUNBAN Ban)
{
	const int BANPos = 180;
	int xOFFSET = BANStartX+BANJIANJUX*Ban.Tx, zOFFSET = BANStartZ+Ban.Tz*BANJIANJUZ;
	;
	if(Ban.Type != 2)
	{
		AddCube(xOFFSET-2,BANY-3-SpotHeight,zOFFSET-BANCHANG,
				xOFFSET-2,BANY-3-SpotHeight,zOFFSET+BANCHANG,
				xOFFSET+2,BANY-3-SpotHeight,zOFFSET-BANCHANG,
				xOFFSET-2,145-SpotHeight,zOFFSET-BANCHANG,12,0);//֧��

		AddCube(xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
				,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+BANCHANG
				,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
				,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-BANCHANG,12,1);//̫���ܰ�
	}
	else
	{
		AddCube(xOFFSET-2,BANY-3-SpotHeight,zOFFSET-DOUBLEZHUCHANG,
				xOFFSET-2,BANY-3-SpotHeight,zOFFSET+DOUBLEZHUCHANG,
				xOFFSET+2,BANY-3-SpotHeight,zOFFSET-DOUBLEZHUCHANG,
				xOFFSET-2,145-SpotHeight,zOFFSET-DOUBLEZHUCHANG,12,0);//֧��

		AddCube(xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG
				,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+DOUBLEBANCHANG
				,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG
				,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG,12,1);//̫���ܰ�
	}

	return 0;
}

static int EditBAN(int Tx, int Tz,int Order,int BANPos)
{
	int xOFFSET = BANStartX+BANJIANJUX*Tx, zOFFSET = BANStartZ+Tz*BANJIANJUZ;
	EditCube(8+PRECUBEDOT+16*Order,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
						,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+BANCHANG
						,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
						,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-BANCHANG);//̫���ܰ�
	return 0;
}

/*****************************
FUNCTION: EditDoubleBan
DESCRIPTION: ������˫����ת��̫���ܰ�
INPUT: �������Tx,Ty,���Ӷ������ţ���ת�ǣ������ǣ�
RETURN: 0
******************************/
static int EditDoubleBan(int Tx, int Tz,int Order,int Fai,int Xita)
{
	static struct D3DOT D1,D2,D3,D4,TD1,TD2,TD3,TD4;
	static struct TransformMatrix TMDouble;
	int xOFFSET = BANStartX+BANJIANJUX*Tx, zOFFSET = BANStartZ+Tz*BANJIANJUZ;
	
	GenerateAnotherTransformMatrix(&TMDouble,Xita,Fai);
	D1.x = +BANKUAN;
	D1.y = 0;
	D1.z = -DOUBLEBANCHANG;
	D2.x = +BANKUAN;
	D2.y = 0;
	D2.z = +DOUBLEBANCHANG;
	D3.x = -BANKUAN;
	D3.y = 0;
	D3.z = -DOUBLEBANCHANG;
	D4.x = +BANKUAN;
	D4.y = +BANHOU;
	D4.z = -DOUBLEBANCHANG;
	
	TD1 = DotTransferWithoutPers(TMDouble,D1);
	TD2 = DotTransferWithoutPers(TMDouble,D2);
	TD3 = DotTransferWithoutPers(TMDouble,D3);
	TD4 = DotTransferWithoutPers(TMDouble,D4);
	
	EditCube(8+PRECUBEDOT+16*Order,xOFFSET+TD1.x,BANY+TD1.y-SpotHeight,zOFFSET+TD1.z
						,xOFFSET+TD2.x,BANY+TD2.y-SpotHeight,zOFFSET+TD2.z
						,xOFFSET+TD3.x,BANY+TD3.y-SpotHeight,zOFFSET+TD3.z
						,xOFFSET+TD4.x,BANY+TD4.y-SpotHeight,zOFFSET+TD4.z);//̫���ܰ�
	return 0;
}

static int rainyEffect(int mode)
{
	static int time = 0;
	unsigned int i, j;
	if(mode == 0)
	{
		time++;
		time = time%30000;
	}
	
	for(i = 0,j = 0; i < 100; i ++)
	{
		j = j*j + i * 101;
		MRVerticalLine(i*6,(j+30*time)%480,(j+30*time+20)%480,1);
	}
	return 0;
}

static int SetElectricStrength(int i, int *pElectricStrength)
{
	if(i == 0)//�����Ǹ���ʱ�����õ�����������
	{
		*pElectricStrength = 2;
	}
	else if(i == 30)
	{
		*pElectricStrength = 4;
	}
	else if(i == 60)
	{
		*pElectricStrength = 6;
	}
	else if(i == 75)
	{
		*pElectricStrength = 8;
	}
	else if(i == 105)
	{
		*pElectricStrength = 6;
	}
	else if(i == 120)
	{
		*pElectricStrength = 4;
	}
	else if(i == 150)
	{
		*pElectricStrength = 2;
	}
	else if(i == 180)
	{
		*pElectricStrength = 0;
	}
	return 0;
}

static int PushRelativeBan(int RelativeOrder)
{
	return PushBan(PRECUBE+24*RelativeOrder,!isTriangleSeen(PRECUBE+13+24*RelativeOrder));
}

static int SetRenderQueue(int Fai,int TotalBanNum,int Xita)//�˴������޸ģ�Ӧ����EmuBansΪ�������������޶���12��̫���ܰ�
{
	int i,j;
	if(Xita>0)
	{
		SetObjects(Fai,TotalBanNum);
		for(i = 0+2; i < 12+2; i ++)
		{
			push(i);
		}
		push(0);//�ذ�
		push(1);
	}
	else
	{
		push(0);//�ذ�
		push(1);
		for(i = 0+2; i < 12+2; i ++)
		{
			push(i);
		}
		SetObjects(Fai,TotalBanNum);
	}
	
	return 0;
}

static int SetObjects(int Fai,int TotalBanNum)
{
	int i,j;
	if(Fai <= 90 || Fai >= 270)
	{
		if(Fai<= 90)
		{
			for(i = 0; i < min(6,TotalBanNum); i ++)
			{
				PushRelativeBan(i);
			}
			for(i = 6; i < TotalBanNum; i ++)
			{
				PushRelativeBan(i);
			}
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//�������
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//��Բ��
			{
				push(j);
			}
		}
		else
		{
			for(i = 6; i < TotalBanNum; i ++)
			{
				PushRelativeBan(i);
			}
			for(i = 0; i < min(6,TotalBanNum); i ++)
			{
				PushRelativeBan(i);
			}
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//��Բ��
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//�������
			{
				push(j);
			}
		}
	}
	else
	{
		if(Fai<= 180)
		{
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//�������
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//��Բ��
			{
				push(j);
			}
			for(i = min(6,TotalBanNum)-1; i >= 0; i --)
			{
				PushRelativeBan(i);
			}
			for(i = TotalBanNum-1; i >= 6; i --)
			{
				PushRelativeBan(i);
			}
			
		}
		else
		{
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//��Բ��
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//�������
			{
				push(j);
			}
			for(i = TotalBanNum-1; i >= 6; i --)
			{
				PushRelativeBan(i);
			}
			for(i = min(6,TotalBanNum)-1; i >= 0; i --)
			{
				PushRelativeBan(i);
			}
		}
	}
	return 0;
}

static int SetColorTable(int WEATHER,int i,int *ChangeWeather)
{
	if(i == 0 || (*ChangeWeather == 1 && i < 180 && i >= 0))//�����Ǹ�������������ɫ��
	{
		if(WEATHER == 0)
		{
			ShadowType(0);
			SetColor(ORICOLOR);
		}
		else if(WEATHER == 1)
		{
			SetColor(CLOUDYCOLOR);
			ShadowType(1);
		}
		else if(WEATHER == 2)
		{
			SetColor(RAINYCOLOR);
			
		}
		else
		{
			SetColor(BLITZCOLOR);
		}
		*ChangeWeather = 0;
	}
	else if(i == 180|| (*ChangeWeather == 1 && i >= 180 && i < 360))
	{
		SetColor(NIGHTCOLOR);
		*ChangeWeather = 0;
	}
	return 0;
}

static int DrawStellarAndShadow(int i, struct TransformMatrix TM, double Zoom, int WEATHER, struct BANS EmuBans, int StellarHeightAngle)
{
	struct D3DOT  STELLAR, TSTELLAR;
	if(i >= 0 && i <= 180)
	{
		MRBk(11);
		//
		STELLAR.x = 1000*SIN(StellarHeightAngle)*COS(i);
		STELLAR.y = 1000*SIN(StellarHeightAngle)*SIN(i);
		STELLAR.z = 1000*COS(StellarHeightAngle);
		TSTELLAR = DotTransferWithoutPers(TM,STELLAR);
		if(TSTELLAR.x > 0)
		{
			int const height = 50*Zoom;
			int i;
			for(i =  - height; i <  height; i ++)
			{
				MRSafeHorizonLine(TSTELLAR.z+320 - sqrt((double)height*height - (double)i*i),
								  TSTELLAR.z+320 + sqrt((double)height*height - (double)i*i),
								  240-TSTELLAR.y + i, 14);
			}
		}
		//�������ڴ�����Ӱ�������ηֱ�Ϊ̫���ܰ嶥�����Σ�̫���ܰ����������
		if(WEATHER <= 1)
		{
			MAKESHADOWS(EmuBans,STELLAR);
		}
	}
	else
	{
		MRBk(3);
		STELLAR.x = 1000*SIN(StellarHeightAngle)*COS(i-180);
		STELLAR.y = 1000*SIN(StellarHeightAngle)*SIN(i-180);
		STELLAR.z = 1000*COS(StellarHeightAngle);
		TSTELLAR = DotTransferWithoutPers(TM,STELLAR);
		if(TSTELLAR.x > 0)
		{
			int const height = 50*Zoom;
			int i;
			for(i =  - height; i <  height; i ++)
			{
				MRSafeHorizonLine(TSTELLAR.z+320 - sqrt((double)height*height - (double)i*i),
								  TSTELLAR.z+320 + sqrt((double)height*height - (double)i*i),
								  240-TSTELLAR.y + i, 15);
			}
		}
	}
	return 0;
}

static int DrawWeatherEffect(int WEATHER, int PAUSE)
{
	//��������Ч��
	if(WEATHER == 1)
	{
		;
	}
	else if(WEATHER == 2)
	{
		rainyEffect(PAUSE);
	}
	else
	{
		;
	}
	return 0;
}

static int ShowDate(DATE date,int i)
{
	//DATE date;
	i = (i+90)%360;
	MRBar(5,200,5,20,15);
	MZFS(15,10,0,"YEAR:");
	MZFI(55,10,0,date.year);
	MZFS(95,10,0,"MONTH:");
	MZFI(140,10,0,date.month);
	MZFS(155,10,0,"DAY:");
	MZFI(185,10,0,date.day);
	
	MRBar(5,100,45,60,15);
	MZFS(10,50,0,"TIME:");
	MZFI(55,50,0,i/15);
	MZFS(70,50,0,":");
	MZFI(85,50,0,(i%15) * 4);
	return 0;
}

static int EditDate(struct Button BDate[6],struct DATE *CurrentDate)
{
	if(DetectButton(BDate[0]) == 1)//���Լ������
	{
		if(CurrentDate->year > 2023)
		{
			CurrentDate->year --;
		}
	}
	else if(DetectButton(BDate[1]) == 1)//�����������
	{
		if(CurrentDate->year < 2027)
		{
			CurrentDate->year ++;
		}
	}
	else if(DetectButton(BDate[2]) == 1)//���Լ����·�
	{
		if(CurrentDate->month > 1)
		{
			CurrentDate->month --;
		}
		else
		{
			CurrentDate->month = 12;
			if(CurrentDate->year > 2023)
			{
				CurrentDate->year --;
			}
		}
	}
	else if(DetectButton(BDate[3]) == 1)//���������·�
	{
		if(CurrentDate->month == 12)
		{
			CurrentDate->month = 1;
			if(CurrentDate->year < 2027)
			{
				CurrentDate->year ++;
			}
		}
		else
		{
			CurrentDate->month ++;
		}
	}
	else if(DetectButton(BDate[4]) == 1)//���Լ�������
	{
		if(CurrentDate->day == 1)
		{
			if(CurrentDate->month == 1)
			{
				CurrentDate->month = 12;
				if(CurrentDate->year > 2023)
				{
					CurrentDate->year --;
				}
			}
			else
			{
				CurrentDate->month --;
			}
			
			CurrentDate->day = month_days(CurrentDate->month, CurrentDate->year);
		}
		else
		{
			CurrentDate->day --;
		}
	}
	else if(DetectButton(BDate[5]) == 1)//������������
	{
		if(CurrentDate->day == month_days(CurrentDate->month, CurrentDate->year))
		{
			if(CurrentDate->month == 12)
			{
				CurrentDate->month = 1;
				if(CurrentDate->year < 2027)
				{
					CurrentDate->year ++;
				}
			}
			else
			{
				CurrentDate->month ++;
			}
			
			CurrentDate->day = 1;
		}
		else
		{
			CurrentDate->day ++;
		}
	}
	else
	{
		return 0;
	}
	//���޸ĵ�����ʹ���ڲ�����,�淶����
	if(CurrentDate->day > month_days(CurrentDate->month, CurrentDate->year))
	{
		CurrentDate->day = month_days(CurrentDate->month, CurrentDate->year);
	}
	return 1;
}

static int NextDate(struct DATE *CurrentDate)
{
	if(CurrentDate->day == month_days(CurrentDate->month, CurrentDate->year))
	{
		if(CurrentDate->month == 12)
		{
			CurrentDate->month = 1;
			if(CurrentDate->year < 2027)
			{
				CurrentDate->year ++;
			}
		}
		else
		{
			CurrentDate->month ++;
		}
		
		CurrentDate->day = 1;
	}
	else
	{
		CurrentDate->day ++;
	}
	return 0;
}

static int checkKeyboard(int *Fai, int *Xita, double *Zoom, int *exit)
{
	char ch;
	if(kbhit())
	{
		ch=getch();
		switch(ch)
		{
			case A:
				if((*Fai)>0)
				{
					(*Fai)--;
				}
				else
				{
					(*Fai) += 359;
				}
			 break;
		 
			case D:
			  if((*Fai)<360)
				{
					(*Fai)++;
				}
				else
				{
					(*Fai) -= 359;
				}
			  break;

			case W:
				if((*Xita)>-90)
				{
					(*Xita)--;
				}
			 break;
		 
			case Z:
				if((*Zoom)<1.8)
				{
					(*Zoom) *= 1.1;
				}
			 break;
		 
			case X:
			  if((*Zoom)>0.2)
				{
					(*Zoom) /= 1.1;
				}
			  break;
		  
			case S:
			  if((*Xita)<90)
				{
					(*Xita)++;
				}
			  break;
			
			case Esc:
			  *exit = 12;
			 break;
		  
		default:
		  //*exit = 12;	
			break;
		}                  //���̽��벿��
	}
	else
	{
		return 0;
	}
	return 1;
}

static int flushKeyboardBuffer()
{
	char ch;
	while(kbhit())//�˴����׿���������
	{
		ch=getch();
	}
	return 1;
}

int SunCamera(int i, int *pFai, int *pXita, double *pZoom,int StellarHeightAngle)//ͨ��i�������Ҫ��cameraλ���Ը��õع۲�̫��
{
	//������ StellarHeightAngle��Ϊ����
	int MaxCameraAngle = StellarHeightAngle - 20;
	i = i % 180;
	*pZoom = 0.4;
	if(i >= 0 && i <= 30)
	{
		*pFai = 270+i;
		*pXita = -2;
	}
	else if(i > 30 && i <= 75)
	{
		*pFai = 300-(i-30)/2;
		*pXita = -2+(int)((i-30)/45.0*MaxCameraAngle);
	}
	else if(i > 75 && i <= 105)
	{
		*pFai = 270-(i-90)/2;
		*pXita = -2+MaxCameraAngle;
	}
	else if(i > 105 && i <= 150)
	{
		*pFai = 240+(150-i)/2;
		*pXita = -2+(int)((150-i)/45.0*MaxCameraAngle);
	}
	else
	{
		*pFai = 270-(180-i);
		*pXita = -2;
	}
	return 0;
	
}

int BanCamera(int i, int *pFai, int *pXita, double *pZoom)//ͨ��i�������Ҫ��cameraλ���Ը��õ���Ȧ�۲�̫���ܰ�
{
	*pFai = i;
	*pXita = -10;
	*pZoom = 1.0;
	return 0;
	
}

static int ReturnDate(int days,DATE *pdate)
{
	DATE date1;
	DATE date2;
	date1.year = 2023;
	date1.month = 1;
	date1.day = 1;
	pdate->year = date1.year;
	pdate->month = date1.month;
	pdate->day = date1.day;   //��date1��ֵ��date2
	while (days)
	{
		days--;
		if (pdate->day != month_days (pdate->month, pdate->year))
		{
			pdate->day++;
		}
		else
		{
			if (pdate->month != 12)
			{
				pdate->month++;
				pdate->day = 1;
			}
			else
			{
				pdate->year++;
				pdate->month = 1;
				pdate->day = 1;
			}
		}
	}
	return 0;
}

static int isrunyear (int year)
{
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
		return 1;
	else
		return 0;
}

static int month_days (int month, int year)
{
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return isrunyear (year) ? 29 : 28;
		default:
			return -1;
	}
}

static int GetStellarHeightAngle(unsigned int DIQU,unsigned int month)
{
	static int BasicMonthlyHeight[13] = {-23,-20,-12,0,12,20,23,20,12,0,-12,-20,0};
	static int BasicDIQU[2] ={30,36};
	return 90 - BasicDIQU[(DIQU+1)%2] + BasicMonthlyHeight[(month+11) % 12];//DIQU==1ʱΪ�人
}

static int EditPower(int *pWEATHER,int *pStellarHeightAngle, int DIQU, DATE CurrentDate, float DayPowerBuffer[26],
					 struct user U,struct WeatherYearData WHWYDATA[],struct WeatherYearData HDWYDATA[])
{
	if(DIQU == 1)
	{
		*pWEATHER = (5 - WHWYDATA[CurrentDate.year-2023].DATA[CurrentDate.month][CurrentDate.day])%3;
		*pStellarHeightAngle = GetStellarHeightAngle(DIQU,CurrentDate.month);
	}
	else
	{
		*pWEATHER = (5 - HDWYDATA[CurrentDate.year-2023].DATA[CurrentDate.month][CurrentDate.day])%3;
		*pStellarHeightAngle = GetStellarHeightAngle(DIQU,CurrentDate.month);
	}
	real_timePOWER(&U,CurrentDate,DIQU,2-*pWEATHER,DayPowerBuffer);
	return 0;
}
				