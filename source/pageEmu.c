/*****************************************
Mimage.c
COPYRIGHT:  Zengmingjie
FUNCTION:   store basic graphics elements and render them
DATE:       2023/2/23-4/13(Debug and Reinforcement)
Available code lines:ZMJ-about1320lines
******************************************/
/******************
已使用的三角形序号：
0-1 地板
2-25 ： 太阳能板，其中2-13是支架，15为板顶
26-49 ： 太阳能板，其中前12是支架，39为板顶
50-73 ： 太阳能板，其中前12是支架，63为板顶
74-97 ： 太阳能板，其中前12是支架，39为板顶
98-121 ： 太阳能板，其中前12是支架，63为板顶
已使用的点序号
0-3 地板
4-83 ： 太阳能板
84-?-1: 电线所属的点
?-？+ 59：阴影所属的点

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

;//需要一个教程功能（或界面）(0406已完成)

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
//0415TODO:需要添加地区切换                                  DONE
//0415TODO:添加iStep切换（倍速）记得step一定要是能过0和270的 DONE
//0415TODO:添加根据地区和月份切换太阳高度角                  DONE
//武汉30.5N，邯郸36.5N
//0415TODO:按键检测(while(kbhit()))                          DONE
//0415TODO:电线倍速效果修复                                  DONE
//0415TODO:天气数据修复                                      DONE
//0415TODO:平单轴倾角数据修复                                DONE

int pageEmu(struct user U,struct WeatherYearData WHWYDATA[],struct WeatherYearData HDWYDATA[])//需要添加地图，太阳能板类型作为参数,BANTYPE 0为固定式，1为平单轴，2为双轴，BANNUM确定板子个数，预计应该是1~10左右
{
	int i,j,k, height, width,Fai = 270,Xita = -30,exit = 0, PAUSE = 0,
		BANPos,ElectricStrength = 1,ShowName = 0,WEATHER = 0,WINDOW = -1,   //0雨天1阴天2晴天
		StellarHeightAngle = 90-53, CameraMode = 0,ChangeWeather = 0, DIQU = 1, iSpeed = 0;//CameraMode 0为自由视角，1为太阳视角，2为板子视角
		//临时废弃,CLOUDON = 0 test = 10.0/2.0,
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
	//我们假设WYDATA和RANDNUM都初始化好了
	struct BANS EmuBans;
	setbkcolor(0);//需要检查
	//
	//菜单部分按钮UI界面初始化
	strcpy(B1.Lines,"退出");
	B1.x1 = 500;
	B1.y1 = 50;
	B1.x2 = 560;
	B1.y2 = 85;
	B1.EdgeColor = 2;
	B1.InnerColor = 15;
	B1.ZIHAO = 24;
	strcpy(BName.Lines,"显示名字");
	BName.x1 = 500;
	BName.y1 = 95;
	BName.x2 = 625;
	BName.y2 = 130;
	BName.EdgeColor = 2;
	BName.InnerColor = 15;
	BName.ZIHAO = 24;
	strcpy(BPause.Lines,"暂停");
	BPause.x1 = 500;
	BPause.y1 = 10;
	BPause.x2 = 570;
	BPause.y2 = 45;
	BPause.EdgeColor = 2;
	BPause.InnerColor = 15;
	BPause.ZIHAO = 24;
	strcpy(BChart.Lines,"图表");
	BChart.x1 = 570;
	BChart.y1 = 50;
	BChart.x2 = 630;
	BChart.y2 = 85;
	BChart.EdgeColor = 2;
	BChart.InnerColor = 15;
	BChart.ZIHAO = 24;
	strcpy(BCamera.Lines,"自由摄像机");
	BCamera.x1 = 500;
	BCamera.y1 = 140;
	BCamera.x2 = 630;
	BCamera.y2 = 165;
	BCamera.EdgeColor = 2;
	BCamera.InnerColor = 15;
	BCamera.ZIHAO = 16;
	strcpy(BWeather.Lines,"晴");
	BWeather.x1 = 570;
	BWeather.y1 = 175;
	BWeather.x2 = 630;
	BWeather.y2 = 205;
	BWeather.EdgeColor = 2;
	BWeather.InnerColor = 15;
	BWeather.ZIHAO = 24;
	strcpy(BDiqu.Lines,"武汉");
	BDiqu.x1 = 500;
	BDiqu.y1 = 175;
	BDiqu.x2 = 560;
	BDiqu.y2 = 205;
	BDiqu.EdgeColor = 2;
	BDiqu.InnerColor = 15;
	BDiqu.ZIHAO = 24;
	//日期修改UI初始化
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
	//板子初始化（在接入队友页面后可消失
	EmuBans.SUNBANNUM = max(1,min(U.Ban_num,12));//需要<=12，否则会超出地板范围
	for(j = 0; j < EmuBans.SUNBANNUM; j ++)
	{
		EmuBans.SunBanBuffer[j].Tx = j%6;
		EmuBans.SunBanBuffer[j].Tz = j/6;
		EmuBans.SunBanBuffer[j].Type = U.Rack_type;
	}

	//对象悬浮名字初始化
	for(j = 0; j < EmuBans.SUNBANNUM; j ++)
	{
		if(EmuBans.SunBanBuffer[j].Type == 1)
		{
			strcpy(BItems[j].Lines,"平单轴太阳能板");
			strcpy(WItems[j].Lines[1],"平单轴太阳能板");
			strcpy(WItems[j].Lines[5],  "PDZ-450W-P");
		}
		else if(EmuBans.SunBanBuffer[j].Type == 2)
		{
			strcpy(BItems[j].Lines,"双轴太阳能板");
			strcpy(WItems[j].Lines[1],"双轴太阳能板");
			strcpy(WItems[j].Lines[5],  "SZ-400W-P");
		}
		else
		{
			strcpy(BItems[j].Lines,"固定太阳能板");
			strcpy(WItems[j].Lines[1],"固定太阳能板");
			strcpy(WItems[j].Lines[5], "GD-500W-P");
		}
		
		BItems[j].x1 = 500;
		BItems[j].y1 = 50;
		BItems[j].x2 = 580;
		BItems[j].y2 = 100;
		BItems[j].EdgeColor = 2;
		BItems[j].InnerColor = 15;
		BItems[j].ZIHAO = 16;
		strcpy(WItems[j].Lines[0],  "名称");
		//strcpy(WItems[j].Lines[1],  "哈哈嗨");//上方已定义
		strcpy(WItems[j].Lines[2],  "SN:");
		strcpy(WItems[j].Lines[3],  "******075701");
		strcpy(WItems[j].Lines[4],  "型号");
		strcpy(WItems[j].Lines[6],  "当前功率");
		strcpy(WItems[j].Lines[7],  "345.24W");
		strcpy(WItems[j].Lines[8],  "倾角");
		strcpy(WItems[j].Lines[9],  "12.3");
		strcpy(WItems[j].Lines[10],  "方位角");
		strcpy(WItems[j].Lines[11],  "23.4");
		strcpy(WItems[j].Lines[12],  "Hello!");
		strcpy(WItems[j].Lines[13],  "哈哈嗨");
		WItems[j].LineNum = 12;
		WItems[j].on = 0;
	}
	j = EmuBans.SUNBANNUM;
	strcpy(BItems[j].Lines,"控制器");
	BItems[j].x1 = 500;
	BItems[j].y1 = 50;
	BItems[j].x2 = 580;
	BItems[j].y2 = 100;
	BItems[j].EdgeColor = 2;
	BItems[j].InnerColor = 15;
	BItems[j].ZIHAO = 16;
	strcpy(WItems[j].Lines[0],  "名称");
	strcpy(WItems[j].Lines[1],  "光伏控制器");
	strcpy(WItems[j].Lines[2],  "SN:");
	strcpy(WItems[j].Lines[3],  "114514");
	strcpy(WItems[j].Lines[4],  "型号");
	strcpy(WItems[j].Lines[5],  "30A40A50A60A");//来源http://www.sdywpower.com/product/595.html
	strcpy(WItems[j].Lines[6],  "功能");
	strcpy(WItems[j].Lines[7],  "控制多路太阳能电池方阵对蓄电池充电");
	strcpy(WItems[j].Lines[8],  "以及蓄电池给太阳能逆变器负载供电");
	strcpy(WItems[j].Lines[9],  "目前有效总太阳能板数");
	{
		char sBANNUM[10];
		my_itoa(U.Ban_num,sBANNUM,10);
		strcpy(WItems[j].Lines[10],  sBANNUM);
	}
	strcpy(WItems[j].Lines[11],  "目前有效总发电量");
	//此行每循环修改
	WItems[j].LineNum = 13;
	WItems[j].on = 0;
	j = EmuBans.SUNBANNUM + 1;
	strcpy(BItems[j].Lines,"蓄电池组");
	BItems[j].x1 = 500;
	BItems[j].y1 = 50;
	BItems[j].x2 = 580;
	BItems[j].y2 = 100;
	BItems[j].EdgeColor = 2;
	BItems[j].InnerColor = 15;
	BItems[j].ZIHAO = 16;
	strcpy(WItems[j].Lines[0],  "名称");
	strcpy(WItems[j].Lines[1],  "蓄电池组");
	strcpy(WItems[j].Lines[2],  "SN:");
	strcpy(WItems[j].Lines[3],  "1919810");
	strcpy(WItems[j].Lines[4],  "型号");
	strcpy(WItems[j].Lines[5],  "6-CNJ-250");
	//来源https://isite.baidu.com/site/wjz2kt4w/7a740000-2d31-49cd-95f6-2c5ab2fc07c0?fid=nH01PHbvn1DLnjDkPW63Pjb1PjIxnWcdg1D&ch=4&bd_vid=10865824235531637379&bd_bxst=EiaKs3DQ0agrkcO900DD0aZuS6AwFb00000000J43oxtYrld4e5m00000000000BnDRswbDdPjI7fYR4wjF7PYDvnH6zP1Iaf1IarRwKfY7tna0Lrjn4njD1wW-7n1n1wRPAwjR3nHcvnD7AnWF7nHc4rUu6ws-MRGwU0f000PUpyis50000rxUT3L60000f0ZnKj_zoYxHDLQiBkPzd4e5mPnzoYxHDLQiBkPzd4e5msQHNYopo12hd4qiYQnHl1SEiJogD12EwqnHTYrld4e5mVo1HYaD00nO4Df6
	strcpy(WItems[j].Lines[6],  "功能");
	strcpy(WItems[j].Lines[7],  "临时储存电能");
	strcpy(WItems[j].Lines[8],  "调整输出功率使输出稳定");
	WItems[j].LineNum = 9;
	WItems[j].on = 0;
	
	//教程相关UI
	strcpy(BTutorial.Lines,"教程");
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
	strcpy(WTutorial.Lines[6],  "按教程可再次观看此教程");
	strcpy(WTutorial.Lines[7],  "按摄像机可切换摄像机模式");
	strcpy(WTutorial.Lines[8],  "预设一观察太阳用预设摄像机且最佳效果在邯郸冬天");
	strcpy(WTutorial.Lines[9],  "预设二观察光伏板用预设摄像机");
	strcpy(WTutorial.Lines[10],  "预设摄像机模式时使用键盘操作");
	strcpy(WTutorial.Lines[11],  "将回到自由摄像机模式");
	strcpy(WTutorial.Lines[12],  "按晴阴雨强制转换天气");
	strcpy(WTutorial.Lines[13],  "按左侧箭头可调整日期一按暂停可暂停");
	WTutorial.LineNum = 14;
	WTutorial.on = 1;//TODO 最终改成1
	//UI界面初始化结束
	
	MouseS = 0;
	ClrOriMap();
	
	//此处地形应当根据来源数据变化；
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
	//这个位置得找机会改，也可以直接每帧重置
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
		//修改对象
		GenerateTransformMatrix(&TM,Xita,Fai,Zoom);//根据提供的视角数据计算坐标转换矩阵
		BANPos = EditBANS(EmuBans,i);//根据时间修改板子姿态参数（就是修改板子的位置）
		SetColorTable(WEATHER,i,&ChangeWeather); //根据天气设置颜色表
		//设置渲染顺序
		QueueReset();
		SetRenderQueue(Fai,EmuBans.SUNBANNUM,Xita);//此处可以检测视线是否可以看到板的上平面以确定显示顺序
		SetElectricStrength(i,&ElectricStrength);//根据时间设置电流流量绘制
		//绘制对象
		DrawStellarAndShadow(i,TM,Zoom,WEATHER,EmuBans, StellarHeightAngle);//绘制天体和阴影
		ColorWires(ElectricStrength, i);//可以在此处改电线传递时的黄色部分占比
		D3FullVectorMapDotTransform(TM,CAMERAPOS);//这个-1000是转换后坐标的摄像机距离原点的位置，会决定透视的效果
		//0304因为透视等3d效果中并没有做截断，倘若1000不够大可能出现有对象在摄像机后面
		//并被绘制入的情况，需要检测，或限制zoom的大小和对象的大小
		drawD3FullVectorMap();
		DrawWeatherEffect(WEATHER, PAUSE);//绘制天气效果
		
		//画每个对象上面的名字OR介绍
		if(ShowName)
		{
			for(j = 0; j < EmuBans.SUNBANNUM; j ++)//此处returnOrder里面是点序号，需要详细计算位置
			{
				BItems[j].x1 = 320+ReturnIOrderZ(j*16+PRECUBEDOT)-68;
				//对于位置不定的按钮，需要做切割（可见部分判别等算法），notice.c里面的MRBar需要修改
				//或修改MRBar实现，或更新MRBar检测，或在Notice.c中完成检测+ReturnIOrderY(j*24+2)+ReturnIOrderZ(j*24+2)
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
		
		//画按钮们
		RenderButton(B1);
		RenderButton(BName);
		RenderButton(BPause);
		RenderButton(BTutorial);
		RenderButton(BChart);
		RenderButton(BCamera);
		RenderButton(BDiqu);
		if(WEATHER == 0)
		{
			strcpy(BWeather.Lines,"晴");
		}
		else if(WEATHER == 1)
		{
			strcpy(BWeather.Lines,"阴");
		}
		else
		{
			strcpy(BWeather.Lines,"雨");
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
		
		//画窗口
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
					strcpy(WItems[WINDOW].Lines[11], "不可用");
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
					strcpy(WItems[WINDOW].Lines[11], "不可用");
					strcpy(WItems[WINDOW].Lines[9], "不可用");
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
				//光伏控制器，显示当前总功率
				my_ftoa(DayPowerBuffer[((i+90)%360)/15] * U.Ban_num,2,sPower);
				strcpy(WItems[WINDOW].Lines[12],  sPower);
				//ENDOFTODO
				;
			}
			else if(WINDOW == EmuBans.SUNBANNUM + 1)
			{
				//TODO;
				//蓄电池组，显示当前蓄电总量？
				//ENDOFTODO
				;
			}
			
			Render(WItems[WINDOW]);
		}
		Render(WTutorial);
		
		ShadowReset();//重置阴影
		
		
		//以下为用户操作的检测
		MRnewmouse(&MouseX,&MouseY,&press);
		if(WINDOW != -1)//若开了窗口则仅作窗口的检测
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
		else//若没开窗口，则检测键盘和按钮
		{
			int buttonActionExist = 0;
			//检测按键
			if(checkKeyboard(&Fai, &Xita, &Zoom, &exit))
			{
				CameraMode = 0;
				strcpy(BCamera.Lines,"自由摄像机");
				flushKeyboardBuffer();//此函数慎用，易bug
			}
			//重置MouseS
			if(mouse_press(0,0,640,480)==2)
			{
				MouseS=0;
			}
			
			//MRnewmouse(&MouseX,&MouseY,&press);
			
			
			//检测是否按下按钮
			//检测是否按下退出
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
					strcpy(BCamera.Lines,"自由摄像机");
				}
				else if(CameraMode == 1)
				{
					strcpy(BCamera.Lines,"太阳摄像机");
				}
				else
				{
					strcpy(BCamera.Lines,"光伏摄像机");
				}
				delay(40);
				
			}
			
			if(DetectButton(BDiqu) == 1)
			{
				buttonActionExist = 1;
				DIQU = (DIQU+1)%2;
				if(DIQU == 1)
				{
					strcpy(BDiqu.Lines,"武汉");
				}
				else
				{
					strcpy(BDiqu.Lines,"邯郸");
				}
				//切地区后更新WEATHER, StellarHeightAngle, DayPowerBuffer
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
					strcpy(BWeather.Lines,"晴");
				}
				else if(WEATHER == 1)
				{
					strcpy(BWeather.Lines,"阴");
				}
				else
				{
					strcpy(BWeather.Lines,"雨");
				}
				ChangeWeather = 1;
				//需要修改 DayPowerBuffer 的值（重新生成）
				real_timePOWER(&U,CurrentDate,DIQU,2-WEATHER,DayPowerBuffer);
				delay(40);
				
			}
			
			//检测是否按下是否显示名字的切换按钮
			if(DetectButton(BName) == 1)
			{
				buttonActionExist = 1;
				if(ShowName == 1)
				{
					ShowName = 0;
					strcpy(BName.Lines,"显示名字");
				}
				else
				{
					ShowName = 1;
					strcpy(BName.Lines,"隐藏名字");
				}
			}
			
			//检测是否按下暂停
			if(DetectButton(BPause) == 1)
			{
				buttonActionExist = 1;
				if(PAUSE == 1)
				{
					PAUSE = 0;
					strcpy(BPause.Lines,"暂停");
				}
				else
				{
					PAUSE = 1;
					strcpy(BPause.Lines,"继续");
				}
			}
			//不统一判断的原因是此三按钮与上述按钮逻辑上并列，并不好用if判断
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
			//若在显示名字状态下，检测是否按下名字TAG
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
			
			
			
			
			
			//检测是否按下日期快进OR快退
			if(EditDate(BDate,&CurrentDate))
			{
				ChangeWeather = 1;
				//切日期后更新WEATHER, StellarHeightAngle, DayPowerBuffer
				EditPower(&WEATHER, &StellarHeightAngle, DIQU, CurrentDate, DayPowerBuffer, U,WHWYDATA,HDWYDATA);
			}
		}
		
		//若非自由模式，修改摄像机
		if(CameraMode == 1)
		{
			SunCamera(i,&Fai, &Xita, &Zoom, StellarHeightAngle);
		}
		else if(CameraMode == 2)
		{
			BanCamera(i,&Fai, &Xita, &Zoom);
		}
		
		if(i == 270)//0点时切日期
		{
			NextDate(&CurrentDate);
			//切日期后更新WEATHER, StellarHeightAngle, DayPowerBuffer
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
	
	for(i = 0; i < Bans.SUNBANNUM; i ++)//type为0则不需要编辑
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
				xOFFSET-2,145-SpotHeight,zOFFSET-BANCHANG,12,0);//支架

		AddCube(xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
				,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+BANCHANG
				,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
				,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-BANCHANG,12,1);//太阳能板
	}
	else
	{
		AddCube(xOFFSET-2,BANY-3-SpotHeight,zOFFSET-DOUBLEZHUCHANG,
				xOFFSET-2,BANY-3-SpotHeight,zOFFSET+DOUBLEZHUCHANG,
				xOFFSET+2,BANY-3-SpotHeight,zOFFSET-DOUBLEZHUCHANG,
				xOFFSET-2,145-SpotHeight,zOFFSET-DOUBLEZHUCHANG,12,0);//支架

		AddCube(xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG
				,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+DOUBLEBANCHANG
				,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG
				,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-DOUBLEBANCHANG,12,1);//太阳能板
	}

	return 0;
}

static int EditBAN(int Tx, int Tz,int Order,int BANPos)
{
	int xOFFSET = BANStartX+BANJIANJUX*Tx, zOFFSET = BANStartZ+Tz*BANJIANJUZ;
	EditCube(8+PRECUBEDOT+16*Order,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
						,xOFFSET-BANKUAN*COS(BANPos),BANY-BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET+BANCHANG
						,xOFFSET+BANKUAN*COS(BANPos),BANY+BANKUAN*SIN(BANPos)-SpotHeight,zOFFSET-BANCHANG
						,xOFFSET-BANKUAN*COS(BANPos)+BANHOU*SIN(BANPos),BANY-BANKUAN*SIN(BANPos)-BANHOU*COS(BANPos)-SpotHeight,zOFFSET-BANCHANG);//太阳能板
	return 0;
}

/*****************************
FUNCTION: EditDoubleBan
DESCRIPTION: 画可以双轴旋转的太阳能板
INPUT: 相对坐标Tx,Ty,板子对象的序号，旋转角，俯仰角；
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
						,xOFFSET+TD4.x,BANY+TD4.y-SpotHeight,zOFFSET+TD4.z);//太阳能板
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
	if(i == 0)//以下是根据时间设置电流流量绘制
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

static int SetRenderQueue(int Fai,int TotalBanNum,int Xita)//此处仍需修改，应当以EmuBans为参数，而不是限定仅12个太阳能板
{
	int i,j;
	if(Xita>0)
	{
		SetObjects(Fai,TotalBanNum);
		for(i = 0+2; i < 12+2; i ++)
		{
			push(i);
		}
		push(0);//地板
		push(1);
	}
	else
	{
		push(0);//地板
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
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//含配电箱
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//含圆柱
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
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//含圆柱
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//含配电箱
			{
				push(j);
			}
		}
	}
	else
	{
		if(Fai<= 180)
		{
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//含配电箱
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//含圆柱
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
			for(j = PRECUBE+24*TotalBanNum + 12; j < PRECUBE+24*TotalBanNum + 12 + 20*4; j ++)//含圆柱
			{
				push(j);
			}
			for(j = PRECUBE+24*TotalBanNum; j < PRECUBE+24*TotalBanNum + 12 ; j ++)//含配电箱
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
	if(i == 0 || (*ChangeWeather == 1 && i < 180 && i >= 0))//以下是根据天气设置颜色表
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
		//以下用于创作阴影的三角形分别为太阳能板顶三角形，太阳能板基座三角形
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
	//绘制天气效果
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
	if(DetectButton(BDate[0]) == 1)//尝试减少年份
	{
		if(CurrentDate->year > 2023)
		{
			CurrentDate->year --;
		}
	}
	else if(DetectButton(BDate[1]) == 1)//尝试增加年份
	{
		if(CurrentDate->year < 2027)
		{
			CurrentDate->year ++;
		}
	}
	else if(DetectButton(BDate[2]) == 1)//尝试减少月份
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
	else if(DetectButton(BDate[3]) == 1)//尝试增加月份
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
	else if(DetectButton(BDate[4]) == 1)//尝试减少日期
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
	else if(DetectButton(BDate[5]) == 1)//尝试增加日期
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
	//若修改的年月使日期不可用,规范化它
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
		}                  //键盘接入部分
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
	while(kbhit())//此处极易卡死，慎用
	{
		ch=getch();
	}
	return 1;
}

int SunCamera(int i, int *pFai, int *pXita, double *pZoom,int StellarHeightAngle)//通过i计算出需要的camera位置以更好地观察太阳
{
	//最好添加 StellarHeightAngle作为参数
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

int BanCamera(int i, int *pFai, int *pXita, double *pZoom)//通过i计算出需要的camera位置以更好地绕圈观察太阳能板
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
	pdate->day = date1.day;   //将date1赋值给date2
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
	return 90 - BasicDIQU[(DIQU+1)%2] + BasicMonthlyHeight[(month+11) % 12];//DIQU==1时为武汉
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
				