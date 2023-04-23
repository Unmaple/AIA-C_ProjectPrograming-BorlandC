#include"public.h"
#include"tb.h"
#include"diagram.h"
#include"pdata.h"
#include"date.h"
#include"data.h"
#include"button.h"

int page_YearOnYear(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	int page=7;
	int mode=0,draw=0;
	struct DATE powerDATE={2023,4,22};
	clrmous(MouseX,MouseY);
	cleardevice();
	delay(100);
	
	draw_TB(powerDATE);
	show_date5(powerDATE);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	//TB_diagram(1,U,pWHDATA,powerDATE,pRANDNUM);
	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);

		if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2
		||mouse_press(330,20,340,40)==2
		||mouse_press(460,20,470,40)==2
		||mouse_press(15,100,85,140)==2
		||mouse_press(15,220,85,260)==2
		||mouse_press(15,340,85,380)==2)
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
			if(mouse_press(330,20,340,40)==1)//减少月份
			{
				if(powerDATE.month<=1)
				{
					powerDATE.month=12;
				}
				else 
				{
					powerDATE.month--;
				}
				change = 1;
			}
			
			if(mouse_press(460,20,470,40)==1)//增加月份
			{
				if(powerDATE.month >=12)
				{
					powerDATE.month=1;
				}
				else
				{
					powerDATE.month++;
				}
				change = 1;
			}
			
			if(change == 1)
			{
				show_date5(powerDATE);
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
				delay(100);
			}
		}
			
		if (mouse_press(15,100,85,140)==1)//武汉
		{
			lightbutton_select(7);
			recoverbutton_select(7);
			draw=1;
			mode=1;
			continue;
		}
		else if (mouse_press(15,220,85,260)==1)//邯郸
		{
			lightbutton_select(8);
			recoverbutton_select(8);
			draw=2;
			mode=2;
			continue;
		}
		else if (mouse_press(15,340,85,380)==1)//同时
		{
			lightbutton_select(9);
			recoverbutton_select(9);
			draw=3;
			mode=3;
			continue;
		}
		if(draw!=0)
		{
			switch(draw)
			{
				case 1:
				TB_diagram(1,U,pWHDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
				
				case 2:
				TB_diagram(2,U,pHDDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
				
				case 3:
				TB_Ddiagram(U,pWHDATA,pHDDATA,powerDATE,pRANDNUM);
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
	return 12;
}

void TB_diagram(int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x; 
	int month;
	float dy[6]={0,0,0,0,0,0};
	int n=5;///5年
	int dx=42,y=450;
	char *year[]={"2023","2024","2025","2026","2027"};
	float a[13],b[13],c[13],d[13],e[13];
	char str1[30],str2[30],str3[30],str4[30],str5[30];
	month=DATE.month;
	YEARPOWER(U,DIQU,2023,a,pDATA,pRANDNUM);
	YEARPOWER(U,DIQU,2024,b,pDATA,pRANDNUM);
	YEARPOWER(U,DIQU,2025,c,pDATA,pRANDNUM);
	YEARPOWER(U,DIQU,2026,d,pDATA,pRANDNUM);
	YEARPOWER(U,DIQU,2027,e,pDATA,pRANDNUM);
	setfillstyle(1,WHITE);
	bar(110,70,640,450);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(1,0,1);
	dy[0]=(*(a+month-1))/(U->Ban_num)*0.0009;
	dy[1]=(*(b+month-1))/(U->Ban_num)*0.0009;
	dy[2]=(*(c+month-1))/(U->Ban_num)*0.0009;
	dy[3]=(*(d+month-1))/(U->Ban_num)*0.0009;
	dy[4]=(*(e+month-1))/(U->Ban_num)*0.0009;
	if (DIQU==1)
	{
		setfillstyle(1,LIGHTRED);
	}
	else if (DIQU==2)
	{
		setfillstyle(1,RED);
	}
	for(i=0;i<=n-1;i++)
	{
		x=95*i+155;
		bar(x,y,x+dx,y-dy[i]);
	}
	setcolor(DARKGRAY);
	rectangle(110,70,620,450);
	i=0;
	for(i=180;i<=620.0;i=i+95)
	{
		line(i,450,i,460);
		outtextxy(i-15,460-3,year[j]);
		j++;
	}
	for(j=0;j<=200;j=j+40)
	{
		setlinestyle(1,0,1);
		line(110,450-1.6*j,620,450-1.6*j);
	}
	
	settextstyle(1, 0, 1);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	setcolor(DARKGRAY);
	my_ftoa(*(a+month-1),4,str1);
	my_ftoa(*(b+month-1),4,str2);
	my_ftoa(*(c+month-1),4,str3);
	my_ftoa(*(d+month-1),4,str4);
	my_ftoa(*(e+month-1),4,str5);
	outtextxy(155-35,80,str1);
	outtextxy(155+95*1-35,110,str2);
	outtextxy(155+95*2-35,80,str3);
	outtextxy(155+95*3-35,110,str4);
	outtextxy(155+95*4-35,80,str5);
}

void TB_Ddiagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x; 
	int month;
	float dy[11];
	int n=5;///5年
	int dx=20,y=450;
	char *year[]={"2023","2024","2025","2026","2027"};
	float a1[13],b1[13],c1[13],d1[13],e1[13];
	float a2[13],b2[13],c2[13],d2[13],e2[13];
	char str[30];
	
	month=DATE.month;
	YEARPOWER(U,1,2023,a1,pWHDATA,pRANDNUM);
	YEARPOWER(U,1,2024,b1,pWHDATA,pRANDNUM);
	YEARPOWER(U,1,2025,c1,pWHDATA,pRANDNUM);
	YEARPOWER(U,1,2026,d1,pWHDATA,pRANDNUM);
	YEARPOWER(U,1,2027,e1,pWHDATA,pRANDNUM);
	YEARPOWER(U,2,2023,a2,pHDDATA,pRANDNUM);
	YEARPOWER(U,2,2024,b2,pHDDATA,pRANDNUM);
	YEARPOWER(U,2,2025,c2,pHDDATA,pRANDNUM);
	YEARPOWER(U,2,2026,d2,pHDDATA,pRANDNUM);
	YEARPOWER(U,2,2027,e2,pHDDATA,pRANDNUM);
	dy[0]=(*(a1+month-1))/(U->Ban_num)*0.0009;
	dy[1]=(*(b1+month-1))/(U->Ban_num)*0.0009;
	dy[2]=(*(c1+month-1))/(U->Ban_num)*0.0009;
	dy[3]=(*(d1+month-1))/(U->Ban_num)*0.0009;
	dy[4]=(*(e1+month-1))/(U->Ban_num)*0.0009;
	dy[5]=(*(a2+month-1))/(U->Ban_num)*0.0009;
	dy[6]=(*(b2+month-1))/(U->Ban_num)*0.0009;
	dy[7]=(*(c2+month-1))/(U->Ban_num)*0.0009;
	dy[8]=(*(d2+month-1))/(U->Ban_num)*0.0009;
	dy[9]=(*(e2+month-1))/(U->Ban_num)*0.0009;
	setfillstyle(1,WHITE);
	bar(110,70,620,450);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(1,0,1);
	for(i=0;i<=n-1;i++)
	{
		x=95*i+155;
		setfillstyle(1,LIGHTRED);
		bar(x,y,x+dx,y-dy[i]);
	}
	for(i=0;i<=n-1;i++)
	{
		x=95*i+178;
		setfillstyle(1,RED);
		bar(x,y,x+dx,y-dy[i+5]);
	}
	
	
	setlinestyle(0, 0, 1);
	settextstyle(1,0,1);
	setcolor(DARKGRAY);
	rectangle(110,70,620,450);
	i=0;
	for(i=180;i<=620.0;i=i+95)
	{
		line(i,450,i,460);
		outtextxy(i-15,460-3,year[j]);
		j++;
	}
	for(j=0;j<=200;j=j+40)
	{
		setlinestyle(1,0,1);
		line(110,450-1.6*j,620,450-1.6*j);
	}
}
	
void draw_TB(DATE date)
{
	char MonthBuffer[4];
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
	
	puthz(120,20-3,"切换月份",24,26,LIGHTBLUE);
	setlinestyle(0,0,3);
	setcolor(LIGHTBLUE);
	line(340,20,330,30);
	line(330,30,340,40);
	line(460,20,470,30);
	line(470,30,460,40);
	itoa(date.month,MonthBuffer,10);
	
	settextstyle(1, 0, 3);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(390,20-3,MonthBuffer);	
	
	setcolor(CYAN);
	setlinestyle(0,0,3);
	rectangle(15,100,85,140);
	puthz(15+2,100+2,"武汉",32,34,DARKGRAY);
	rectangle(15,220,85,260);
	puthz(15+2,220+2,"邯郸",32,34,DARKGRAY);
	rectangle(15,340,85,380);
	puthz(15+2,340+2,"两地",32,34,DARKGRAY);
	setfillstyle(1,LIGHTRED);
	bar(15,400,30,415);
	puthz(40,400+2,"武汉",16,18,LIGHTGRAY);
	setfillstyle(1,RED);
	bar(15,425,30,440);
	puthz(40,425+2,"邯郸",16,18,LIGHTGRAY);
}

static int show_date5(DATE date)
{
	char MonthBuffer[4];
	setfillstyle(1,WHITE);
	bar(300,20,460,40);
	setlinestyle(0,0,3);
	setcolor(LIGHTBLUE);
	line(340,20,330,30);
	line(330,30,340,40);
	line(460,20,470,30);
	line(470,30,460,40);
	
	itoa(date.month,MonthBuffer,10);
	
	settextstyle(1, 0, 3);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(390,20-3,MonthBuffer);	
	return 0;
}