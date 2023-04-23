#include"public.h"
#include"chart.h"
#include"diagram.h"
#include"pdata.h"
#include"date.h"
#include"data.h"
#include"ftoa.h"

int page_chart(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	int page=5;
	int i = 0;
	//int change = 0;dx,
	int mode=0,flag=0,draw = 0;
	int DIQU;
	int x=0,n=0,j=0;
	char str[32]={0};
	static float Time[26];
	struct DATE powerDATE={2023,4,22};
	
	clrmous(MouseX, MouseY);
	cleardevice();
	delay(100);
	draw_chart();
	show_date4(powerDATE);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);
		//ColorWires(100,200,100,200,3,i,10);
		//i ++;
		if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2
		||mouse_press(550,190,620,230)==2
		||mouse_press(550,260,620,300)==2
		||mouse_press(540,355,630+3,395+3)==2
		||mouse_press(160,15-2,170,35-2)==2
		||mouse_press(275,15-2,285,35-2)==2
		||mouse_press(320,15-2,330,35-2)==2
		||mouse_press(385,15-2,395,35-2)==2
		||mouse_press(430,15-2,440,35-2)==2
		||mouse_press(495,15-2,505,35-2)==2)
		{
			MouseS=1;
		}
		else if(mouse_press(30,60,530,450)==2)
		{
			MouseS=3;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
		if(mode==1||mode==2)
		{
			int change=0;
			if(mouse_press(160,15-2,170,35-2)==1)//减少年份
			{
				if(powerDATE.year > 2023)
				{
					powerDATE.year --;
				}
				change = 1;
			}
			
			if(mouse_press(275,15-2,285,35-2)==1)//增加年份
			{
				if(powerDATE.year<2023+4)
				{
					powerDATE.year ++;
				}
				change = 1;
			}
			
			if(mouse_press(320,15-2,330,35-2)==1)//减少月份
			{
				if(powerDATE.month<=1)
				{
					powerDATE.month=12;
					if(powerDATE.year > 2023)
					{
						powerDATE.year --;
					}
				}
				else 
				{
					powerDATE.month--;
				}
				change = 1;
			}
			
			if(mouse_press(385,15-2,395,35-2)==1)//增加月份
			{
				if(powerDATE.month >=12)
				{
					powerDATE.month=1;
					if(powerDATE.year<2023+4)
					{
						powerDATE.year ++;
					}
				}
				else
				{
					powerDATE.month++;
				}
				change = 1;
			}
			
			if(mouse_press(430,15-2,440,35-2)==1)//减少天数
			{
				if(powerDATE.day<=1)
				{
					if(powerDATE.month<=1)
					{
						powerDATE.month=12;
						if(powerDATE.year > 2023)
						{
							powerDATE.year --;
						}
					}
					else 
					{
						powerDATE.month--;
					}
					powerDATE.day = month_days(powerDATE.month, powerDATE.year);
				}
				else
				{
					powerDATE.day--;
				}
				change = 1;	
			}
			if(mouse_press(495,15-2,505,35-2)==1)//增加天数
			{
				if(powerDATE.day >= month_days(powerDATE.month, powerDATE.year))
				{
					if(powerDATE.month >= 12)
					{
						powerDATE.month = 1;
						if(powerDATE.year < 2023+4)
						{
							powerDATE.year ++;
						}
					}
					else
					{
						powerDATE.month ++;
					}
					
					powerDATE.day = 1;
				}
				else
				{
					powerDATE.day ++;
				}
				change = 1;
			}
			if(powerDATE.day > month_days(powerDATE.month,powerDATE.year))
			{
				powerDATE.day = month_days(powerDATE.month, powerDATE.year);
				//change=1;
			}
			
			if(change == 1)
			{
				show_date4(powerDATE);
				draw = 1;
				delay(100);
			}
			x=40;
			n=24;
			j=20;
			//dx=10;
			settextstyle(2, 0, 5);//三倍笔划字体，水平输出
			settextjustify(0, 2);//输出左对齐，顶部对齐
			if(mouse_press(x,60,x+j*(n-1),450)==2)
			{ 
				static int LastMouseX = 0;
				if(MouseX != LastMouseX)
				{
					i = (MouseX-x+10)/j;
					if(i >= 0 && i < n)
					{
						my_ftoa(Time[i],4,str);
						setfillstyle(1,WHITE);
						bar(535,100,640,130);
						outtextxy(540,110,str);
					}
					else
					{
						outtextxy(100+5,100+5,"error");
					}
					LastMouseX = MouseX;
				}
			}		
		}
		
		if(mouse_press(550,190,620,230)==1)//武汉
		{
			lightbutton_chart(1);
			recoverbuttom_chart(2);
			if(mode != 0)
			{
				draw = 1;
			}
			flag=1;
			DIQU=1;
			continue;
		}
		else if (mouse_press(550,260,620,300)==1)//邯郸
		{
			// setfillstyle(1,WHITE);
			// bar(540,250,630,310);
			lightbutton_chart(2);
			recoverbuttom_chart(1);
			if(mode != 0)
			{
				draw = 1;
			}
			flag=2;
			DIQU=2;
			continue;
		}
		else if (mouse_press(550,350,620,390)==1)//显示发电量
		{
			lightbutton_chart(3);
			recoverbuttom_chart(4);
			if(flag != 0)
			{
				draw = 1;
			}
			mode=1;
			continue;
		}
		else if (mouse_press(545,410,625,450)==1)//不显示发电量
		{
			lightbutton_chart(4);
			recoverbuttom_chart(3);
			if(flag != 0)
			{
				draw = 1;
			}
			mode=2;
			continue;
		}
		
		else if(mouse_press(20,5,40,25)==1)
		{
			page=3;
			delay(130);
			return page;
		}
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			delay(130);
			return page;
		}
		if(draw&&DIQU==1)
		{
			switch(mode)
			{
				case 1:
				diagram_chart(Time,DIQU,U,pWHDATA,powerDATE,pRANDNUM);
				break;
				
				case 2:
				power_chart(Time,DIQU,U,pWHDATA,powerDATE,pRANDNUM);
				break;
			}
			draw = 0;
		}
		if(draw&&DIQU==2)
		{
			switch(mode)
			{
				case 1:
				diagram_chart(Time,DIQU,U,pHDDATA,powerDATE,pRANDNUM);
				break;
				
				case 2:
				power_chart(Time,DIQU,U,pHDDATA,powerDATE,pRANDNUM);
				break;
			}
			draw = 0;
		}
		// if(DIQU==1&&draw)
		// {
			// switch(draw)
			// {
				// case 1:
				// diagram_chart(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				// draw=0;
				// draw = 0;
				// break;
				
				// case 2:
				// power_chart(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				// draw=0;
				// draw = 0;
				// break;
			// }
			// continue;
		// }
		
		// else if(DIQU==2&&draw)
		// {
			// switch(draw)
			// {
				// case 1:
				// diagram_chart(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				// draw=0;
				// draw = 0;
				// break;
				
				// case 2:
				// power_chart(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				// draw=0;
				// draw = 0;
				// break;
			// }
			// continue;
		// }
		
		// else if(show==1&&draw)
		// {
			// switch(flag)
			// {
				// case 1:
				// diagram_chart(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				// flag=0;
				// draw = 0;
				// break;
				
				// case 2:
				// diagram_chart(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				// flag=0;
				// draw = 0;
				// break;
			// }
			// continue;
		// }
		
		// else if(unshow==1&&draw)
		// {
			// switch(flag)
			// {
				// case 1:
				// power_chart(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				// flag=0;
				// draw = 0;
				// break;
				
				// case 2:
				// power_chart(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				// flag=0;
				// draw = 0;
				// break;
			// }
			// continue;
		// }
	}	
}
	
void power_chart(float b[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i,j=0,x,dy;
	int n=24,y=450;
	char *time[]={"00:00","02:00","04:00","06:00","08:00","10:00","12:00","14:00","16:00","18:00","20:00","22:00","24:00"};
	//char *p[]={"0","1","2","3","4","5"};//更改
	//float b[26];//更改
	int year,month,day;
	float weather;
	settextstyle(2, 0, 5);//小笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	year=DATE.year;
	month=DATE.month;
	day=DATE.day;
	real_TODAYPOWER(U,year,month,day,DIQU,b,pDATA,pRANDNUM);
	weather=today_weather(year,month,day,pDATA);
	//real_TODAYPOWER(U,2023,12,15,1,b);
	/* closegraph();
	for(i=0;i<24;i++)
	{
		printf("%f\n",b[i]);
	}printf("%p\n",b);
	getchar();  */
	setfillstyle(1,WHITE);
	bar(1,40,530,600);
	setbkcolor(WHITE);
	setcolor(LIGHTGRAY);
	setlinestyle(0, 0, 3);
	moveto(40,y);//zhuyi
	for(i=0;i<=n;i++)
	{
		x=i*20+40;
		dy=(*(b+i))/(U->Ban_num)*0.18;//zhuyi
		setcolor(GREEN);
		lineto(x,y-dy);
		setcolor(GREEN);
		setlinestyle(0,0,3);
		circle(x,y-dy,3);
		moveto(x,y-dy);
	}
	setlinestyle(0,0,1);
	setcolor(DARKGRAY);
	rectangle(30,60,530,450);
	for(i=40;i<=520;i=i+40)
	{
		line(i,440,i,450);
		outtextxy(i-6,450+4,time[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		line(30,450-1.6*j,520,450-1.6*j);
		setlinestyle(1,0,1);
	}
	settextstyle(2,1,5);
	outtextxy(10,40,"power");
	puthz(40,70,"天气",16,18,BLUE);
	settextstyle(1, 0, 2);
	setcolor(BLUE);
	outtextxy(80,70-6,":");
	if(weather > (1.0-1e-4)&&weather < (1.0+1e-4))
	{
		puthz(90,70,"晴",16,18,BLUE);
	}
	else if (weather > (0.75-1e-4)&&weather < (0.75+1e-4))
	{
		puthz(90,70,"阴",16,18,BLUE);
	}
	else if(weather > (0.3-1e-4)&&weather < (0.3+1e-4))
	{
		puthz(90,70,"雨",16,18,BLUE);
	}
}

void diagram_chart(float b[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x,dy;
	int n=24;
	int dx=10,y=450;
	char *time[]={"00:00","02:00","04:00","06:00","08:00","10:00","12:00","14:00","16:00","18:00","20:00","22:00","24:00"};
	//float b[26];//更改
	int year,month,day;
	float weather;
	settextstyle(2, 0, 5);//小笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	year=DATE.year;
	month=DATE.month;
	day=DATE.day;
	real_TODAYPOWER(U,year,month,day,DIQU,b,pDATA,pRANDNUM);
	weather=today_weather(year,month,day,pDATA);
	setfillstyle(1,WHITE);
	bar(1,40,530,600);
	setbkcolor(WHITE);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 3);
	moveto(40,y);//zhuyi
	for(i=0;i<n;i++)
	{
		x=i*20+40;
		if(*(b+i)==0)
		{
			dy=0;
		}
		else 
		{
			dy=(*(b+i))/(U->Ban_num)*0.18+3;//zhuyi
		}
		setcolor(LIGHTCYAN);
		setlinestyle(0,0,3);
		lineto(x,y-dy);
		setcolor(RED);
		//setlinestyle(0,0,1);
		circle(x,y-dy,3);
		moveto(x,y-dy);
	}
	setlinestyle(0,0,3);
	setcolor(LIGHTCYAN);
	lineto(520,450);
	//setlinestyle(0,0,1);
	setcolor(RED);
	circle(520,450,3);
	for(i=0;i<=n-1;i++)
	{
		x=i*20+35;
		dy=(*(b+i))/(U->Ban_num)*0.18;
		setfillstyle(1,CYAN);
		bar(x,y,x+dx,y-dy);
	}
	setlinestyle(0,0,1);
	setcolor(DARKGRAY);
	rectangle(30,60,530,450);
	for(i=40;i<=520;i=i+40)
	{
		line(i,440,i,450);
		outtextxy(i-6,450+4,time[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		line(30,450-1.6*j,520,450-1.6*j);
		setlinestyle(1,0,1);
		line(30,450-1.6*j,520,450-1.6*j);
		i++;
	}
	settextstyle(2,1,5);
	outtextxy(10,40,"power");
	puthz(40,70,"天气",16,18,BLUE);
	settextstyle(1, 0, 2);
	setcolor(BLUE);
	outtextxy(80,70-6,":");
	if(weather==1.0)
	{
		puthz(90,70,"晴",16,18,BLUE);
	}
	else if (weather==0.75)
	{
		puthz(90,70,"阴",16,18,BLUE);
	}
	else if(weather==0.3)
	{
		puthz(90,70,"雨",16,18,BLUE);
	}
}

static int show_date4(DATE date)
{
	char YearBuffer[10],MonthBuffer[4],DayBuffer[4];
	setfillstyle(1,WHITE);
	bar(150,10,510,40);
	setlinestyle(0,0,3);
	setcolor(RED);
	line(170,15-2,160,25-2);
	line(160,25-2,170,35-2);
	line(275,15-2,285,25-2);
	line(285,25-2,275,35-2);
	
	line(330,15-2,320,25-2);
	line(320,25-2,330,35-2);
	line(385,15-2,395,25-2);
	line(395,25-2,385,35-2);
	
	line(440,15-2,430,25-2);
	line(430,25-2,440,35-2);
	line(495,15-2,505,25-2);
	line(505,25-2,495,35-2);

	itoa(date.year,YearBuffer,10);
	itoa(date.month,MonthBuffer,10);
	itoa(date.day,DayBuffer,10);
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(200,15-3-2,YearBuffer);
	outtextxy(345,15-3-2,MonthBuffer);
	outtextxy(455,15-3-2,DayBuffer);
	return 0;
}

void draw_chart()
{
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
	
	puthz(540,70,"当前功率",24,22,LIGHTGRAY);
	puthz(540,150,"选择地区",24,22,LIGHTGRAY);
	setfillstyle(1,LIGHTGREEN);
	bar(550,190,620,230);
	puthz(550+2,190+2,"武汉",32,34,GREEN);
	bar(550,260,620,300);
	puthz(550+2,260+2,"邯郸",32,34,GREEN);
	puthz(540,320,"显示发电量",16,18,DARKGRAY);
	setfillstyle(1,LIGHTRED);
	bar(550,350,620,390);
	puthz(550+2,350+2,"显示",32,34,RED);
	bar(545,410,625,450);
	puthz(540+4,410+8,"不显示",24,26,RED);
	
}

void lightbutton_chart(int flag)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch(flag)
	{
		case 1:
		setfillstyle(1,WHITE);
		bar(540,180,630,240+3);
		setfillstyle(1,GREEN);
		bar(550+3,190+3,620+3,230+3);
		puthz(550+2+3,190+2+3,"武汉",32,34,WHITE);
		break;
		
		case 2:
		setfillstyle(1,WHITE);
		bar(540,250,630,310);
		setfillstyle(1,GREEN);
		bar(550+3,260+3,620+3,300+3);
		puthz(550+2+3,260+2+3,"邯郸",32,34,WHITE);
		break;
		
		case 3:
		setfillstyle(1,WHITE);
		bar(550,350,620,390);
		setfillstyle(1,RED);
		bar(550+3,350+3,620+3,390+3);
		puthz(550+5,350+5,"显示",32,34,WHITE);
		break;
		
		case 4:
		setfillstyle(1,WHITE);
		bar(545,410,625,450);
		setfillstyle(1,RED);
		bar(545+3,410+3,625+3,450+3);
		puthz(545+7,410+12,"不显示",24,26,WHITE);
		break;
		
	}
}

void recoverbuttom_chart(int flag)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch(flag)
	{
		case 1:
		setfillstyle(1,WHITE);
		bar(540,180,630,240+3);
		setfillstyle(1,LIGHTGREEN);
		bar(550,190,620,230);
		puthz(550+2,190+2,"武汉",32,34,GREEN);
		break;
		
		case 2:
		setfillstyle(1,WHITE);
		bar(540,250,630,310);
		setfillstyle(1,LIGHTGREEN);
		bar(550,260,620,300);
		puthz(550+2,260+2,"邯郸",32,34,GREEN);
		break;
		
		case 3:
		setfillstyle(1,WHITE);
		bar(550+3,350+3,620+3,390+3);
		setfillstyle(1,LIGHTRED);
		bar(550,350,620,390);
		puthz(550+2,350+2,"显示",32,34,RED);
		break;
		
		case 4:
		setfillstyle(1,WHITE);
		bar(545+3,410+3,625+3,450+3);
		setfillstyle(1,LIGHTRED);
		bar(545,410,625,450);
		puthz(540+4,410+8,"不显示",24,26,RED);
	}
}
		
		