#include"public.h"
#include"hb.h"
#include"diagram.h"
#include"pdata.h"
#include"date.h"
#include"data.h"
#include"button.h"
#include"ftoa.h"

//因实际年与年，月与月，日与日之间发电量的差异并不大
//故考虑不同季度之间的增长率与发电量变化
//同时 考虑武汉和邯郸两个地方的气候差异
//武汉的季度和邯郸的季度所对应的月份各不相同

int page_chain(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	int page=8;
	int mode=0,draw=0;
	int n,j,x,dx;
	struct DATE powerDATE={2023,4,22};
	
	clrmous(MouseX,MouseY);
	cleardevice();
	delay(100);
	draw_HB(powerDATE);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	//HB_diagram(1,U,pWHDATA,powerDATE,pRANDNUM);
	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);

		if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2
		||mouse_press(290,20,300,40)==2
		||mouse_press(480,20,490,40)==2)
		{
			MouseS=1;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
		else if(mouse_press(110,70,620,450)==2)
		{
			MouseS=3;
		}
		if(mode==1||mode==2||mode==3)
		{
			int change=0;
			if(mouse_press(290,20,300,40)==1)//减少年份
			{
				if(powerDATE.year > 2023)
				{
					powerDATE.year --;
				}
				else if(powerDATE.year==2027)
				{
					powerDATE.year=2023;
				}
				change = 1;
			}
			
			if(mouse_press(480,20,490,40)==1)//增加年份
			{
				if(powerDATE.year<2023+4)
				{
					powerDATE.year ++;
				}
				else if (powerDATE.year==2027)
				{
					powerDATE.year=2023;
				}
				change = 1;
				
			}
			
			if(change == 1)
			{
				show_date6(powerDATE);
				switch(mode)
				{
					case 1:
					draw=1;
					break;
					
					case 2:
					draw=2;
					break;
					
					case 3:
					draw=3;
					break;
				}
				delay(120);
			}
			
		}
		
		if (mouse_press(15,100,85,140)==1)//武汉
		{
			lightbutton_select(10);
			recoverbutton_select(10);
			mode=1;
			draw=1;
			continue;
		}
		else if (mouse_press(15,220,85,260)==1)//邯郸
		{
			lightbutton_select(11);
			recoverbutton_select(11);
			mode=2;
			draw=2;
			continue;
		}
		else if (mouse_press(15,340,85,380)==1)//同时
		{
			lightbutton_select(12);
			recoverbutton_select(12);
			mode=3;
			draw=3;
			continue;
		}
		
		if(draw!=0)
		{
			switch(draw)
			{
				case 1:
				HB_diagram(1,U,pWHDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
				
				case 2:
				HB_diagram(2,U,pHDDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
				
				case 3:
				HB_Ddiagram(U,pWHDATA,pHDDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
			}
			continue;
		}
		
		if(mouse_press(20,5,40,25)==1)
		{
			page=3;
			delay(100);
			return page;
		}
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			delay(100);
			return page;
		}
	}
}
	
void HB_diagram(int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x; 
	float dy=0;
	int year;
	int n=4;//四个季度
	float a[5],b[5];
	int dx=50,y=450;
	char str[30];
	//char *season[]={,"第二季度","第三季度","第四季度"};
	year=DATE.year;
	SEASONPOWER(U,year,DIQU,a,pDATA,pRANDNUM);
	TBRATE(U,year,DIQU,b,pDATA,pRANDNUM);
	// closegraph();
	// printf("%f ",b[0]);
	// printf("%f ",b[1]);
	// printf("%f ",b[2]);
	// printf("%f",b[3]);
	// getchar();
	setfillstyle(1,WHITE);
	bar(110,70,640,450);
	if(DIQU==1)
	{
		setfillstyle(1,DARKGRAY);
	}
	else if (DIQU==2)
	{
		setfillstyle(1,LIGHTGRAY);
	}
	for(i=0;i<=n-1;i++)
	{
		x=125*i+165;
		dy=(*(a+i))/(U->Ban_num)*0.00032;
		bar(x,y,x+dx,y-dy);
	}
	
	
	/* closegraph();
	printf("%f",a[1]);
	getchar();  */
	if(DIQU==1)
	{
		setcolor(RED);
	}
	else if (DIQU==2)
	{
		setcolor(LIGHTRED);
	}
	y=258;
	setlinestyle(0, 0, 3);
	moveto(190,y-(*(b+0))*200);
	circle(190,y-(*(b+0))*200,3);
	
	for(i=1;i<n;i++)
	{
		x=125*i+190;
		if(*(b+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(b+i))*200;//zhuyi
		}
		
		setlinestyle(0,0,3);
		lineto(x,y-dy);
		circle(x,y-dy,3);
		moveto(x,y-dy);
	}
	settextstyle(1, 0, 3);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	//y=300-(*(b+0))*200;
	if(DIQU==1)
	{
		setcolor(LIGHTMAGENTA);
	}
	else if (DIQU==2)
	{
		setcolor(LIGHTBLUE);
	}
	my_ftoa(b[0],4,str);
	//outtextxy(190-35,y-30,str);
	for(i=0;i<n;i++)
	{//b[i]
		my_ftoa(b[i],4,str);
		x=125*i+190;
		if(*(b+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(b+i))*200;//zhuyi
		}
		outtextxy(x-35,y-dy-35,str);
		//y=y-dy;
	}
	
	setlinestyle(0, 0, 1);
	setcolor(DARKGRAY);
	rectangle(110,70,620,450);
	i=0;
	for(i=190;i<=600.0;i=i+125)
	{
		line(i,450,i,460);
	}
	puthz(190-33,460-3,"第一季度",16,18,DARKGRAY);
	puthz(190-33+125,460-3,"第二季度",16,18,DARKGRAY);
	puthz(190-33+125*2,460-3,"第三季度",16,18,DARKGRAY);
	puthz(190-33+125*3,460-3,"第四季度",16,18,DARKGRAY);
	
	
	for(j=0;j<=200;j=j+40)
	{
		setlinestyle(1,0,1);
		line(110,450-1.6*j,620,450-1.6*j);
	}
}

void HB_Ddiagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x; 
	float dy=0;
	int year;
	int n=4;//四个季度
	float a[5]={0},b[5]={0},c[5]={0},d[5]={0};
	int dx=24,y=450;
	char str[30];
	year=DATE.year;
	SEASONPOWER(U,year,1,a,pWHDATA,pRANDNUM);
	SEASONPOWER(U,year,2,b,pHDDATA,pRANDNUM);
	TBRATE(U,year,1,c,pWHDATA,pRANDNUM);
	TBRATE(U,year,2,d,pHDDATA,pRANDNUM);
	setfillstyle(1,WHITE);
	bar(110,70,640,450);
	for(i=0;i<=n-1;i++)
	{
		x=125*i+165;
		dy=(*(a+i))/(U->Ban_num)*0.00032;
		setfillstyle(1,DARKGRAY);
		bar(x,y,x+dx,y-dy);
	}

	for(i=0;i<=n-1;i++)
	{
		x=125*i+191;
		dy=(*(b+i))/(U->Ban_num)*0.00032;
		setfillstyle(1,LIGHTGRAY);
		bar(x,y,x+dx,y-dy);
	}
	
	y=258;
	setlinestyle(0, 0, 3);
	setcolor(RED);
	moveto(165+12,y-(*(c+0))*200);
	circle(165+12,y-(*(c+0))*200,3);
	for(i=1;i<n;i++)
	{
		x=125*i+165+12;
		if(*(c+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(c+i))*200;//zhuyi
		}
		
		setlinestyle(0,0,3);
		lineto(x,y-dy);
		circle(x,y-dy,3);
		moveto(x,y-dy);
		//y=y-dy;
	}
	
	y=258+50;
	setlinestyle(0, 0, 3);
	setcolor(LIGHTRED);
	moveto(191+12,y-(*(d+0))*200);
	circle(191+12,y-(*(d+0))*200,3);
	for(j=1;j<n;j++)
	{
		x=125*j+191+12;
		if(*(d+j)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(d+j))*200;//zhuyi
		}
		
		setlinestyle(0,0,3);
		lineto(x,y-dy);
		circle(x,y-dy,3);
		moveto(x,y-dy);
		//y=y-dy;
	}
	
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	y=258;
	setcolor(LIGHTMAGENTA);
	my_ftoa(c[0],4,str);
	//outtextxy(190-70,y-30,str);
	for(i=0;i<n;i++)
	{
		my_ftoa(c[i],4,str);
		x=125*i+190;
		if(*(b+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(c+i))*200;//zhuyi
		}
		outtextxy(x-80,y-dy-30,str);
		//y=y-dy;
	}
	
	y=258+50;
	setcolor(LIGHTBLUE);
	my_ftoa(d[0],4,str);
	//outtextxy(190,y+20,str);
	for(i=0;i<n;i++)
	{
		my_ftoa(d[i],4,str);
		x=125*i+190;
		if(*(b+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(d+i))*200;//zhuyi
		}
		outtextxy(x-13,y-dy+20,str);
		//y=y-dy;
	}
	
	setlinestyle(0, 0, 1);
	setcolor(DARKGRAY);
	rectangle(110,70,620,450);
	i=0;
	for(i=190;i<=600.0;i=i+125)
	{
		line(i,450,i,460);
	}
	puthz(190-33,460-3,"第一季度",16,18,DARKGRAY);
	puthz(190-33+125,460-3,"第二季度",16,18,DARKGRAY);
	puthz(190-33+125*2,460-3,"第三季度",16,18,DARKGRAY);
	puthz(190-33+125*3,460-3,"第四季度",16,18,DARKGRAY);
	
	for(j=0;j<=200;j=j+40)
	{
		setlinestyle(1,0,1);
		line(110,450-1.6*j,620,450-1.6*j);
	}
}

void draw_HB(DATE date)
{
	char YearBuffer[10];
	setbkcolor(WHITE);
	setcolor(BLUE);
	setlinestyle(0,0,3);
	rectangle(600,5,620,25);
	line(600,5,620,25);
	line(620, 5, 600, 25);
	rectangle(20,5,40,25);
	line(20,15,40,15);
	line(20,15,25,10);
	line(20,15,25,20);
	
	setcolor(GREEN);
	puthz(100,20-3,"切换年份",24,26,CYAN);
	line(300,20,290,30);
	line(290,30,300,40);
	line(480,20,490,30);
	line(490,30,480,40);
	itoa(date.year,YearBuffer,10);
	settextstyle(1, 0, 3);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(365,20-6,YearBuffer);
	
	setcolor(DARKGRAY);
	setlinestyle(0,0,3);
	rectangle(15,100,85,140);
	puthz(15+2,100+2,"武汉",32,34,BLUE);
	rectangle(15,220,85,260);
	puthz(15+2,220+2,"邯郸",32,34,BLUE);
	rectangle(15,340,85,380);
	puthz(15+2,340+2,"两地",32,34,BLUE);
	setfillstyle(1,DARKGRAY);
	bar(15,400,30,415);
	setcolor(RED);
	line(40,406,60,406);
	puthz(70,400+2,"武汉",16,18,DARKGRAY);
	setfillstyle(1,LIGHTGRAY);
	bar(15,425,30,440);
	setcolor(LIGHTRED);
	line(40,431,60,431);
	puthz(70,425+2,"邯郸",16,18,LIGHTGRAY);
}
	
static int show_date6(DATE date)
{
	char YearBuffer[10];
	setfillstyle(1,WHITE);
	bar(300,20,500,40);
	setcolor(GREEN);
	setlinestyle(0,0,3);
	line(300,20,290,30);
	line(290,30,300,40);
	line(480,20,490,30);
	line(490,30,480,40);
	
	itoa(date.year,YearBuffer,10);
	
	settextstyle(1, 0, 3);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(365,20-6,YearBuffer);
	return 0;
}