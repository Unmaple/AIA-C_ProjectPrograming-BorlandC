#include"public.h"
#include"dz.h"
#include"view.h"
#include"device.h"
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
//#define abs(x) (((x) > 0 )? (x) : (-x))
/*****************************************
station.c
COPYRIGHT:	lixin
FUNCTION:	power station
ABSTRACT:
		
DATE:2023/3/20
******************************************/
int page_dz(struct user *U)
{
	int page=4;
	//int num=0;
	const int Ty = 90;
	int x,y;
	clrmous(MouseX, MouseY);
	cleardevice();
	setbkcolor(WHITE);
	draw_dz(U);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while (page==4)
	{
		Blline(380,220,300,220);
		x = 200;
		y = 60;
		setcolor(LIGHTCYAN);
		Blline(x + 220, y + 0,x + 220, y + Ty-50);
		Blline(x + 430, y + 0, x + 220, y + 0);
		Blline(x + 430, y + 275, x + 430, y + 0);
		Blline(x + 360, y + 275, x + 430, y + 275);
		LXColorParabola(x + 280, y + 275, x + 360, y + 275,-20,20);
		LXColorParabola(410, 275,x + 280, y + 275,-20,20);
		
		Blline(x + 255, y + 7, x + 255, y + Ty-50);//可替换为bling闪线
		Blline(x + 420, y + 7, x + 255, y + 7);
		Blline(x + 420, y + 245, x + 420, y + 7);
		Blline(x + 375, y + 245, x + 420, y + 245);
		LXColorParabola(x + 265, y + 245, x + 375, y + 245,-20,20);
		LXColorParabola(410, 267,x + 265, y + 245,-20,20);
		
		Blline(x + 290, y + 15, x + 290, y + Ty-50);
		Blline(x + 410, y + 15, x + 290, y + 15);
		Blline(x + 410, y + 215, x + 410, y + 15);
		Blline(x + 360, y + 215, x + 410, y + 215);
		LXColorParabola(x + 280, y + 215, x + 360, y + 215,-20,20);
		LXColorParabola(410, 260,x + 280, y + 215,-20,20);
		x = 100;
		y = 260;
		setcolor(LIGHTCYAN);
		Blline(x + 220, y + Ty-50, x + 220, y + 0);
		Blline(x + 220, y + 0, x + 310, y + 0);
		
		Blline(x + 255, y + Ty-50, x + 255, y + 7);//可替换为bling闪线
		Blline(x + 255, y + 7, x + 310, y + 7);
		
		Blline(x + 290, y + Ty-50, x + 290, y + 15);
		Blline(x + 290, y + 15, x + 310, y + 15); 
		//LXColorParabola(400,100,100,200,-200,20);
		
		x = -20;
		y = 260;
		setcolor(LIGHTCYAN);
		Blline(x + 220, y + 0, x + 220, y + Ty-50);
		LXColorParabola(20+110,280-3,x + 220, y + 0,-20,20);
		LXColorParabola(0,280,20+110,280-3,-40,20);
		
		Blline(x + 255, y + 0, x + 255, y + Ty-50);//可替换为bling闪线
		LXColorParabola(20+126,310-3,x + 255, y + 0,-20,20);
		LXColorParabola(0,310,20+126,310-3,-40,20);
		
		Blline(x + 290, y + 0, x + 290, y + Ty-50);
		LXColorParabola(20+110,340-3,x + 290, y + 0,-20,20);
		LXColorParabola(0,340,20+110,340-3,-40,20);
		
		newmouse(&MouseX,&MouseY,&press);
		if(mouse_press(0,0,180,40)==2
		||mouse_press(180,0,250,40)==2
		||mouse_press(250,0,390,40)==2
		||mouse_press(390,0,530,40) == 2
		||mouse_press(530,0,600,40)==2
		// ||mouse_press(15,60,85,125)==2
		// ||mouse_press(15,150,85,215)==2
		// ||mouse_press(15,240,85,305) == 2
		// ||mouse_press(15,330,85,395)==2
		||mouse_press(610,5,630,25)==2)
		{
			MouseS=1;
		}
	
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
	
		else if(mouse_press(0,0,180,40) == 1)//日照变化图
		{
			page=6;
			delay(100);
			return page;
		}
		else if (mouse_press(180,0,250,40)==1)//统计
		{
			page=3;
			delay(100);
			return page;
		}
		else if(mouse_press(250,0,390,40)==1)//电站视图
		{
			page=11;
			delay(100);
			return page;
		}
		else if(mouse_press(390,0,530,40) == 1)//设备管理
		{
			page=page_device(U,2);
			delay(100);
			return page;
		}
		else if (mouse_press(530,0,600,40)==1)//关于
		{
			page=21;
			delay(100);
			return page;
		}
	/* 	else if(mouse_press(30,185,230,185+22)==1)
		{
			
		} */
	
	
		// if(mouse_press(120-10,360-10,260+10,400+10)==1)
		// {
			// page=11;
			// return page;
		// }
	
		// else if(mouse_press(380-10,360-10,520+10,400+10)==1)
		// {
			// page=1;
			// return page;
		// }
		
		else if(mouse_press(610,5,630,25) == 1)//退出
		{
			page = 12;
			return page;
		}
		delay(10);
	}
	return 12;
}

int color_wires(int x1, int x2,int y1, int y2,int BlingStrength, int BlingNow,int division)//blingbling
{
	int i;//,x1 = 100, x2 = 200, y1 = 100, y2 = 100
	float dx = (x2 - x1)/(float)division, dy = (y2 - y1)/(float)division;
	const int BlingSize = 10;//此处改循环长度
	for(i = 1; i <= division;i ++)
	{
		setcolor(((BlingNow + i) % BlingSize < BlingStrength)?YELLOW:DARKGRAY);
		setlinestyle(0,0,3);
		line(x1+ (i - 1)*dx,y1+ (i - 1)*dy,x1+ i*dx,y1+ i*dy);
	}
	return 0;
}

int Blline(int x1,int y1, int x2, int y2)//,int mode
{
	static int BlingNow = 0;
	static int count = 0;
	int dx;
	int dy;
	int length;
	dx = x2-x1;
	dy = y2-y1;
	length = max(max(dx,dy),max(-dx,-dy));//求最大值
	count ++;
	if(count >= 100)
	{
		BlingNow ++;
		count = 0;
	}
	//需要增加时间判断以确定是否++,需要查询时间函数time.h
	color_wires(x1, x2, y1, y2,2,BlingNow,length/15+10);//length/15+1
	return 0;
}

void draw_parabola(int x1, int y1, int x2, int y2, int a) 
{ 
   // 绘制抛物线 
   float x, y; 
   for (x = x1; x <= x2; x += 1) { 
      y = (float)a * ((float)(x - x1) * (float)(x - x2)) / ((float)(x1 - x2) * (float)(x1 - x2)) + y1 + (float)(y2-y1)*(float)(x-x1)/(float)(x2-x1); 
      putpixel(x, y, DARKGRAY); 
   } 
} 

int LXColorParabola(int x1,int y1, int x2, int y2, int a,int BlingStrength)//blingbling
{
	static int BlingNow = 0;
	static int count = 0;
	float x, y; 
	int i = 0;
	const int BlingSize = 100;//此处改循环长度
	count ++;
	if(count >= 1)
	{
		BlingNow ++;
		count = 0;
	}
	if(BlingNow >= 100)
	{	
		BlingNow -= 100;
	}// for(i = 1; i < division;i ++)
	// {
		// setcolor(((BlingNow + i) % BlingSize < BlingStrength)?YELLOW:DARKGRAY);
		// setlinestyle(0,0,3);
		// line(x1+ (i - 1)*dx,y1+ (i - 1)*dy,x1+ i*dx,y1+ i*dy);BlingStrength
	// }
	if(x2 > x1)
	{
		for (x = x1; x <= x2; x += 1,i ++) 
		{ 
			y = (float)a * ((float)(x - x1) * (float)(x - x2)) / ((float)(x1 - x2) * (float)(x1 - x2)) + y1 + (float)(y2-y1)*(float)(x-x1)/(float)(x2-x1); 
			putpixel(x, y, (((BlingNow + i) % BlingSize < BlingStrength)?YELLOW:DARKGRAY)); 
		} 
	}
	else
	{
		for (x = x1; x >= x2; x -= 1,i ++) 
		{ 
			y = (float)a * ((float)(x - x1) * (float)(x - x2)) / ((float)(x1 - x2) * (float)(x1 - x2)) + y1 + (float)(y2-y1)*(float)(x-x1)/(float)(x2-x1); 
			putpixel(x, y, (((BlingNow + i) % BlingSize < BlingStrength)?YELLOW:DARKGRAY)); 
		} 
	}
	
	return 0;
}

// 绘制高压线铁塔
void drawTower(int x, int y) 
{
    // 变压器主体
	
	// int x = 250; // 塔身左侧x坐标
    // int y = 50; // 塔身顶部y坐标
    //int width = 140; // 塔身宽度
   // int height = 200; // 塔身高度
	int dx = 0, dy = 0;
   
    setcolor(DARKGRAY);
    line(x + 30,y+10,x+110,y+10);
	rectangle(x + 55,y+10,x+85,y+40);
	line(x + 15,y+40,x+125,y+40);
	rectangle(x + 55,y+40,x+85,y+70);
	line(x + 30,y+70,x+110,y+70);
	//顶上三角形
	line(x + 55,y+10,x+70,y+0);
	line(x + 70,y+0,x+85,y+10);
	//下支撑架
	line(x + 55,y+70,x+22,y+200);
	line(x + 85,y+70,x+118,y+200);
	//斜梁0
	line(x + 55,y+70,x + 92,y+100);
	line(x + 48,y+100,x+85,y+70);
	//斜梁1
	line(x + 55,y+10,x+85,y+30);
	line(x + 55,y+30,x+85,y+10);
	//斜梁2
	line(x + 55,y+50,x+85,y+30);
	line(x + 55,y+30,x+85,y+50);
	//斜梁3
	line(x + 55,y+50,x+85,y+70);
	line(x + 55,y+70,x+85,y+50);
	//横梁1
	line(x + 48,y+100,x + 92,y+100);
	line(x + 41,y+130,x + 92,y+100);
	line(x + 48,y+100,x + 99,y+130);
	//横梁2
	line(x + 41,y+130,x + 99,y+130);
	line(x + 34,y+160,x + 99,y+130);
	line(x + 41,y+130,x + 106,y+160);
	//横梁3
	line(x + 34,y+160,x + 106,y+160);
	line(x+22,y+200,x+70,y+160);
	line(x+118,y+200,x+70,y+160);
	//小钩钩
	dx = 32;
	dy = 12;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
	//小钩钩
	dx = 108;
	dy = 12;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
	//小钩钩
	dx = 17;
	dy = 42;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
	//小钩钩
	dx = 123;
	dy = 42;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
	//小钩钩
	dx = 32;
	dy = 72;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
	//小钩钩;
	dx = 108;
	dy = 72;
	line(x+dx,y+dy,x+dx,y+dy+15);
	line(x+dx-3,y+dy+3,x+dx+3,y+dy+3);
	line(x+dx-3,y+dy+6,x+dx+3,y+dy+6);
	line(x+dx-3,y+dy+9,x+dx+3,y+dy+9);
	line(x+dx-3,y+dy+12,x+dx+3,y+dy+12);
  
}


// 绘制变压器
void drawTransformer(int x, int y) 
{
	int i,j;
	const int Ty = 90;
    // 变压器主体
    setcolor(BROWN);
    rectangle(x + 200, y + 100, x + 300, y + 150);
	rectangle(x + 225, y + 150, x + 275, y + 170);

    // 左侧电线杆
	y -=60;
    line(x + 200, y + 175, x + 180, y + 175);
    line(x + 180, y + 175, x + 180, y + 230);
    line(x + 180, y + 230, x + 190, y + 230);
    line(x + 190, y + 230, x + 190, y + 195);
    line(x + 190, y + 195, x + 200, y + 195);

    // 右侧电线杆
    line(x + 300, y + 175, x + 320, y + 175);
    line(x + 320, y + 175, x + 320, y + 230);
    line(x + 320, y + 230, x + 310, y + 230);
    line(x + 310, y + 230, x + 310, y + 195);
    line(x + 310, y + 195, x + 300, y + 195);

	y+=60;
    // 背后的铁架子
    line(x + 200, y + 100, x + 210, y + 80);
    line(x + 210, y + 80, x + 260, y + 80);
    line(x + 260, y + 80, x + 270, y + 100);
	setcolor(LIGHTBLUE);
	for(i = 0; i < 10; i ++)
	{
		ellipse(x + 220, y + Ty-5*i, 180, 360, 10, 7);
	}
    //arc(x + 235, y + Ty-5*10, 0, 360, 15);
	ellipse(x + 220, y + Ty-5*10, 0, 360, 10, 7);


	for(i = 0; i < 10; i ++)
	{
		ellipse(x + 255, y + Ty-5*i, 180, 360, 10, 7);
	}
    //arc(x + 235, y + Ty-5*10, 0, 360, 15);
	ellipse(x + 255, y + Ty-5*10, 0, 360, 10, 7);
    // 顶部的线圈
    //ellipse(x + 280, y + 40, 0, 360, 15, 10);
    //arc(x + 300, y + 105, 180, 360, 25);
   // arc(x + 300, y + 135, 0, 180, 25);
	for(i = 0; i < 10; i ++)
	{
		//arc(x + 280, y + Ty-5*i, 180, 360, 15);
		ellipse(x + 290, y + Ty-5*i, 180, 360, 10, 7);
	}
	//arc(x + 280, y + Ty-5*10, 0, 360, 15);
	ellipse(x + 290, y + Ty-5*10, 0, 360, 10, 7);
	setcolor(DARKGRAY);
	
}

void draw_dz(struct user *U)
{
	int reletiveX,relativeY,i,j;
	const int Ty = 90;
	int x,y;
	int ret;
	char NormalBuffer[20]={0};
	char DownBuffer[20]={0};
	int normal;
	/* srand((unsigned int)time(NULL));
	if(U->Ban_num<200)
	{
		ret=rand()%3;//（n-m+1）+m 为m-n的随机数
	}
	else if(U->Ban_num>=200)
	{
		ret = rand() % 11;//生成0-10的随机数
	} */
	normal=(U->Ban_num)*0.98;
	ret=(U->Ban_num)-normal;
	itoa(normal,NormalBuffer,10);
	itoa(ret,DownBuffer,10);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(1,40,639,40);
	line(1,0,1,480);
	line(1, 479, 639, 479);
	//line(100,40,100,479);
	setcolor(BLUE);
	setlinestyle(0,0,3);
	rectangle(610,5,630,25);
	line(610,5,630,25);
	line(630, 5, 610, 25);//右上角叉叉
	
	//画顶端信息栏
	settextjustify(0,2);
	settextstyle(0,0, 1);
	//0,0,180,40
	puthz(5,4,"日照变化图",32,34,BLUE);
	line(180,0,180,40);
	//180,0,250,40
	puthz(180+2,4,"统计",32,34,BLUE);
	line(250,0,250,40);
	//250,0,390,40
	puthz(250+2,4,"电站视图",32,34,BLUE);
	line(390,0,390,40);
	//390,0,530,40
	puthz(390+2,4,"设备管理",32,34,BLUE);
	line(530,0,530,40);
	//530,0,600,40
	puthz(530+2,4,"关于",32,34,BLUE);
	line(600,0,600,40);
	
	//画左端信息栏
	setfillstyle(1,LIGHTGRAY);
	// bar(15,60,85,125);
	//puthz(15+2,60+2,"全部",32,32,DARKGRAY);
	bar(45,60,115,125);
	puthz(45+2,60+2,"正常",32,32,DARKGRAY);
	bar(45,150,115,215);
	puthz(45+2,150+2,"故障",32,32,DARKGRAY);
	settextstyle(1,0,3);
	setcolor(WHITE);
	if(normal<100)
	{
		outtextxy(70,90+4,NormalBuffer);
	}
	else if(normal>=100)
	{
		outtextxy(60,90+4,NormalBuffer);
	}
	setcolor(RED);
	if(ret<10)
	{
		outtextxy(75,180+4,DownBuffer);
	}
	else if(ret>=10)
	{
		outtextxy(65,180+4,DownBuffer);
	}
	
	// bar(15,330,85,395);
	// puthz(15+2,330+2,"断连",32,32,DARKGRAY);
	
	// setfillstyle(SOLID_FILL, GREEN);
	// bar(100,50,635,475);
	// delay(1000);
	// 绘制太阳能板
	{
		 // 存储太阳能板的位置和尺寸
		int panel_x = 200;
		int panel_y = 150;
		int panel_width = 100;
		int panel_height = 20;
		
		int support_x = panel_x;
		int support_y = panel_y + panel_height;
		int support_width = panel_width;
		int support_height = 50;
		setcolor(BLUE);
		line(panel_x, panel_y, panel_x + panel_width, panel_y);
		line(panel_x + panel_width, panel_y, panel_x + panel_width, panel_y + panel_height);
		line(panel_x + panel_width, panel_y + panel_height, panel_x, panel_y + panel_height);
		line(panel_x, panel_y + panel_height, panel_x, panel_y);
		// 绘制支架
		setcolor(DARKGRAY);
		line(support_x + support_width/2-5, support_y, support_x + support_width/2-5, support_y + support_height);
		line(support_x, support_y + support_height, support_x + support_width, support_y + support_height);
		line(support_x + support_width/2+5, support_y + support_height, support_x + support_width/2+5, support_y);
	}
	drawTower(450, 250); // 绘制高压线铁塔
	drawTower(20, 250); // 绘制高压线铁塔
	setcolor(LIGHTCYAN);
	line(300,220,380,220);//可替换为bling闪线
	x = 200;
	y = 60;
	drawTransformer(x,y);
	
	x = 200;
	y = 60;
	setcolor(LIGHTCYAN);
	Blline(x + 220, y + Ty-50, x + 220, y + 0);
    Blline(x + 220, y + 0, x + 310, y + 0);
	
	Blline(x + 255, y + Ty-50, x + 255, y + 7);//可替换为bling闪线
	Blline(x + 310, y + 7, x + 255, y + 7);
	
	Blline(x + 290, y + Ty-50, x + 290, y + 15);
    Blline(x + 290, y + 15, x + 310, y + 15);
	
	
	x = 100;
	y = 260;
	drawTransformer(x,y);
	x = 100;
	y = 260;
	setcolor(LIGHTCYAN);
	Blline(x + 220, y + Ty-50, x + 220, y + 0);
    Blline(x + 220, y + 0, x + 310, y + 0);
	
	Blline(x + 255, y + Ty-50, x + 255, y + 7);//可替换为bling闪线
	Blline(x + 310, y + 7, x + 255, y + 7);
	
	Blline(x + 290, y + Ty-50, x + 290, y + 15);
    Blline(x + 290, y + 15, x + 310, y + 15);
	
	x = -20;
	y = 260;
	drawTransformer(x,y);
	x = -20;
	y = 260;
	setcolor(LIGHTCYAN);
	Blline(x + 220, y + Ty-50, x + 220, y + 0);
    //Blline(x + 220, y + 0, x + 310, y + 0);
	
	Blline(x + 255, y + Ty-50, x + 255, y + 7);//可替换为bling闪线
	//Blline(x + 310, y + 7, x + 255, y + 7);
	
	Blline(x + 290, y + Ty-50, x + 290, y + 15);
   // Blline(x + 290, y + 15, x + 310, y + 15);
	
	//draw_parabola(100,200,400,100,-30);
   
}






