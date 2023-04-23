#include"public.h"
#include"diagram.h"
#include"chart.h"
#include"pdata.h"
#include"data.h"
#include"date.h"
#include"button.h"
#include"ftoa.h"
#include"device.h"

/*****************************************
diagram.c
COPYRIGHT:	lixin
FUNCTION:	power generation diagram
ABSTRACT:
		
DATE:2023/3/13
******************************************/

//struct WeatherYearData WYDATA[10];


/*********************************************
FUNCTION:power_diagram
DESCRIPTION：发电量统计总面板
INPUT:
RETURN:无
***********************************************/

int page_diagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	int page=3;
	int i=0;
	float j=0;
	//float a=0;//尝试
	int n=0;//,dx=0
	int DIQU=0;
	int mode=0,draw = 0;
	int LIFE=0,YEAR=0,MONTH=0,DAY=0;
	int flag=0;
	char str[32] = {0};
	int x;
	//int month=4;
	struct DATE powerDATE={2023,4,22};
	static float Time[26],Day[32],Month[13],Year[6];
	
	clrmous(MouseX, MouseY);
	cleardevice();
	setbkcolor(WHITE);
	draw_diagram();
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	//power_daydiagram();
	while (page==3)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(100+20,40+10,200,100-10)==2
		||mouse_press(200+30,40+10,310,100-10)==2
		||mouse_press(310+30,40+10,420,100-10)==2
		||mouse_press(420+30,40+10,600,100-10)==2
		||mouse_press(610,5,630,25) == 2
		||mouse_press(15,100,85,140) == 2
		||mouse_press(15,160,85,200) == 2
		||mouse_press(15,270,85,310) == 2
		||mouse_press(15,330,85,370) == 2
		||mouse_press(15,390,85,430)==2
		||mouse_press(0,0,180,40)==2
		||mouse_press(0,0,600,40)==2)
		{
			MouseS=1;
		}
		else if(mouse_press(150,140,620,450)==2)
		{
			MouseS=3;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
		
		if(mode == 1)
		{
			int change = 0;
			
			//delay(300);
			if(mouse_press(120,110,130,130)==1)//减少年份
			{
				if(powerDATE.year > 2023)
				{
					powerDATE.year --;
				}
				change = 1;
			}
			
			if(mouse_press(225,110,235,130)==1)//增加年份
			{
				if(powerDATE.year<2023+4)
				{
					powerDATE.year ++;
				}
				change = 1;
			}
			
			if(mouse_press(280,110,290,130)==1)//减少月份
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
			
			if(mouse_press(345,110,355,130)==1)//增加月份
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
			if(mouse_press(390,110,400,130)==1)//减少天数
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
			if(mouse_press(460,110,470,130)==1)//增加天数
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
			
			//若修改的年月使日期不可用,规范化它
			if(powerDATE.day > month_days(powerDATE.month,powerDATE.year))
			{
				powerDATE.day = month_days(powerDATE.month, powerDATE.year);
				//change==1;
			}
			
			if(change == 1)
			{
				show_date1(powerDATE);
				draw = 1;
				delay(120);
			}
			setcolor(LIGHTRED);
			settextstyle(2, 0, 5);//三倍笔划字体，水平输出
			settextjustify(0, 2);//输出左对齐，顶部对齐
			// for(i=0;i<=n-1;i++)
			// {
				// x=20*i+153;
				// if(mouse_press(x,120,x+dx,450)==2)
				// { 
					// my_ftoa(Time[i],4,str);
					
					// outtextxy(100+5,100+5,str);
				// }
			// }
			n=24;//24个时刻
			//dx=9+2;
			j=20;
			x = 153;
			puthz(490,112,"发电量",16,16,DARKGRAY);
			if(mouse_press(x,120,x+j*(n-1),450)==2)
			{ 
				static int LastMouseX = 0;
				if(MouseX != LastMouseX)
				{
					i = (MouseX-x+10)/j;
					if(i >= 0 && i < n)
					{
						my_ftoa(Time[i],4,str);
						//my_itoa(i+1,str,10);
						setfillstyle(1,WHITE);
						bar(550,110,640,130);
						outtextxy(550,112,str);
					}
					else
					{
						outtextxy(100+5,100+5,"error");
					}
					LastMouseX = MouseX;
				}
			}		
		}
		
		else if (mode==2)       
		{
			int change=0;
			if(mouse_press(205,110,215,130)==1)//减少年份
			{
				if(powerDATE.year > 2023)    
				{
					powerDATE.year --;
				}
				change = 2;
				
			}
			
			if(mouse_press(320,110,330,120)==1)//增加年份
			{
				if(powerDATE.year<2023+4)
				{
					powerDATE.year ++;
				}
				change = 2;
			}
			
			if(mouse_press(365,110,375,130)==1)//减少月份
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
				change = 2;
				
			}
			
			if(mouse_press(430,110,440,130)==1)//增加月份
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
				change = 2;
			}
			
			if(change==2)
			{
				show_date2(powerDATE);
				draw=2;
				delay(120);
			}
			setcolor(LIGHTRED);
			settextstyle(2, 0, 5);//三倍笔划字体，水平输出
			settextjustify(0, 2);//输出左对齐，顶部对齐
			puthz(460,112,"发电量",16,16,DARKGRAY);
			//dx=9+1;
			x=158;
			if(month_days (powerDATE.month, powerDATE.year)==31)
			{
				n=31;
				j=15;
			}
			else if(month_days (powerDATE.month, powerDATE.year)==30)
			{
				n=30;
				x=158;
				j=15.5;
			}
			else if(month_days (powerDATE.month, powerDATE.year)==28)
			{
				n=28;
				j=16;
			}
			else if(month_days (powerDATE.month, powerDATE.year)==29)
			{
				n=29;
				j=15.5;
			}
			if(mouse_press(x,120,x+j*(n-1),450)==2)
			{ 
				static int LastMouseX = 0;
				if(MouseX != LastMouseX)
				{
					i = (MouseX-x+10)/j;
					if(i >= 0 && i < n)
					{
						my_ftoa(Day[i],4,str);
						setfillstyle(1,WHITE);
						bar(530,110,640,130);
						outtextxy(530,112,str);
					}
					else
					{
						outtextxy(100+5,100+5,"error");
					}
					LastMouseX = MouseX;
				}
			}		
		}
		
		else if(mode==3)
		{
			int change=0;
			if(mouse_press(270-5,110-3,280+5,130+3)==1)//减少年份
			{
				if(powerDATE.year > 2023)
				{
					powerDATE.year --;
				}
				change = 3;
				
			}
			
			if(mouse_press(430-5,110-3,440+5,130+3)==1)//增加年份
			{
				if(powerDATE.year<2023+4)
				{
					powerDATE.year ++;
				}
				change = 3;
			}
			
			if(change==3)
			{
				show_date3(powerDATE);
				draw=3;
				delay(120);
			}
			setcolor(LIGHTRED);
			settextstyle(2, 0, 5);//三倍笔划字体，水平输出
			settextjustify(0, 2);//输出左对齐，顶部对齐
			puthz(460,112,"发电量",16,16,DARKGRAY);
			j=40;
			n=12;
			x=156;
			//dx=20;
			if(mouse_press(x,120,x+j*(n-1),450)==2)
			{ 
				static int LastMouseX = 0;
				if(MouseX != LastMouseX)
				{
					i = (MouseX-x+10)/j;
					if(i >= 0 && i < n)
					{
						my_ftoa(Month[i],4,str);
						setfillstyle(1,WHITE);
						bar(530,110,640,130);
						outtextxy(530,112,str);
					}
					else
					{
						outtextxy(100+5,100+5,"error");
					}
					LastMouseX = MouseX;
				}
			}		
		}
		else if(mode==4)
		{
			setcolor(LIGHTRED);
			settextstyle(2, 0, 7);//三倍笔划字体，水平输出
			settextjustify(0, 2);//输出左对齐，顶部对齐
			puthz(240,110,"发电量",24,26,DARKGRAY);
			j=92;
			n=5;
			x=180;
			//dx=40;
			if(mouse_press(x,120,x+j*(n-1),450)==2)
			{ 
				static int LastMouseX = 0;
				if(MouseX != LastMouseX)
				{
					i = (MouseX-x+10)/j;
					if(i >= 0 && i < n)
					{
						my_ftoa(Year[i],4,str);
						//my_itoa(i+1,str,10);
						setfillstyle(1,WHITE);
						bar(360,101,600,130);
						outtextxy(360,112,str);
					}
					else
					{
						outtextxy(100+5,100+5,"error");
					}
					LastMouseX = MouseX;
				}
			}	
		}			
			
		
		if(mouse_press(100+20,40+10,200,100-10) == 1)//日框点击中
		{
			powerDATE.year=2023;
			powerDATE.month=4;
			powerDATE.day=22;
			show_date1(powerDATE);
			lightbutton_select(1);
			recoverbutton_select(1);
			mode=1;
			draw = 1;
			LIFE=0;
			YEAR=0;
			MONTH=0;
			DAY=1;
			continue;
		}
		else if (mouse_press(200+30,40+10,310,100-10)==1)//月框点击中
		{
			powerDATE.year=2023;
			powerDATE.month=4;
			show_date2(powerDATE);
			lightbutton_select(2);
			recoverbutton_select(2);
			mode=2;
			draw = 2;
			LIFE=0;
			YEAR=0;
			MONTH=1;
			DAY=0;
			continue;
		}
		else if(mouse_press(310+30,40+10,420,100-10)==1)//年框点击中
		{
			powerDATE.year=2023;
			show_date3(powerDATE);
			lightbutton_select(3);
			recoverbutton_select(3);
			mode=3;
			draw = 3;
			LIFE=0;
			YEAR=1;
			MONTH=0;
			DAY=0;
			continue;
		}
		else if(mouse_press(420+30,40+10,600,100-10)==1)//生命期框点击中
		{
			setlinestyle(0,0,3);
			setfillstyle(1,WHITE);
			bar(105,100+1,639,130+1);
			lightbutton_select(4);
			recoverbutton_select(4);
			draw=4;
			mode=4;
			LIFE = 1;
			YEAR=0;
			MONTH=0;
			DAY=0;
			continue;
		}
		else if(mouse_press(15,100,85,140)==1)//武汉点击中
		{
			lightbutton_select(5);
			recoverbutton_select(5);
			DIQU=1;//武汉
			flag=1;
			continue;
		}
		else if(mouse_press(15,160,85,200)==1)//邯郸点击中
		{
			lightbutton_select(6);
			recoverbutton_select(6);
			DIQU=2;//邯郸
			flag=2;
			continue;
		}
		else if(mouse_press(610,5,630,25) == 1)//退出
		{
			page = 12;
			delay(100);
			return page;
		}
		else if(mouse_press(180,0,320,40)==1)//电站信息
		{
			page = 4;
			delay(100);
			return page;
		}
		else if(mouse_press(15,390,85,430)==1)//功率
		{
			page=5;
			delay(100);
			return page;
		}
		else if(mouse_press(15,270,85,310)==1)//同比
		{
			page=7;
			delay(100);
			return page;
		}
		else if(mouse_press(15,330,85,370)==1)//环比
		{
			page=8;
			delay(100);
			return page;
		}
		else if (mouse_press(320,0,460,40)==1)//设备管理
		{
			page=page_device(U,1);
			delay(100);
			return page;
		}
		else if (mouse_press(460,0,600,40)==1)//关于我们
		{
			page=20;
			delay(100);
			return page;
		}
		else if(mouse_press(0,0,180,40)==1)//日照变化图
		{
			page=6;
			delay(100);
			return page;
		}
		
		/**
		if(mode!=0)
		{
			if(mode==1)
			{
				power_daydiagram();
				mode=0;
				break;
			}
			continue;
		}
		**/
		
		if(DIQU==1&&(draw==1||draw==2||draw==3||draw==4))
		{
			switch(draw)
			{
				case 1:
				power_daydiagram(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				//real_timePOWER(U,powerDATE,0,1,20);//用于测试
				draw=0;
				break;
				
				case 2:
				if(powerDATE.month==1||powerDATE.month==3||powerDATE.month==5||powerDATE.month==7||powerDATE.month==8
					||powerDATE.month==10||powerDATE.month==12)
				{
					power_monthdiagram1(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
				}
				else if(powerDATE.month==4||powerDATE.month==6||powerDATE.month==9||powerDATE.month==11)	
				{
					power_monthdiagram2(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
				}
				if(powerDATE.year!=2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram3(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
					}
				}
				else if(powerDATE.year==2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram4(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
					}
				}
				draw=0;
				break;
				
				case 3:
				 power_yeardiagram(Month,1,U,pWHDATA,powerDATE,pRANDNUM);
				 draw=0;
				 break;
				 
				 
				case 4:
				  power_lifetimediagram(Year,1,U,pWHDATA,pRANDNUM);
				  draw=0;
				 break;
				 
				 default :
				 break; 
			}
			continue;
		}
		
		else if (DIQU==2&&(draw==1||draw==2||draw==3||draw==4))
		{
			switch(draw)
			{
				case 1:
				power_daydiagram(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				draw=0;
				break;
				
				case 2:
				if(powerDATE.month==1||powerDATE.month==3||powerDATE.month==5||powerDATE.month==7||powerDATE.month==8
					||powerDATE.month==10||powerDATE.month==12)
				{
					power_monthdiagram1(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
				}
				else if(powerDATE.month==4||powerDATE.month==6||powerDATE.month==9||powerDATE.month==11)	
				{
					power_monthdiagram2(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
				}
				if(powerDATE.year!=2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram3(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
					}
				}
				else if(powerDATE.year==2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram4(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
					}
				}
				draw=0;
				break;
				
				case 3:
				 power_yeardiagram(Month,2,U,pHDDATA,powerDATE,pRANDNUM);
				 draw=0;
				 break;
				 
				case 4:
				 power_lifetimediagram(Year,2,U,pHDDATA,pRANDNUM);
				 draw=0;
				 break;
				 
				 default :
				 break;
			}
			continue;
		}
		
		if(LIFE==1&&(flag==1||flag==2))
		{
			switch(flag)
			{
				case 1:
				power_lifetimediagram(Year,1,U,pWHDATA,pRANDNUM);
				flag=0;
				break;
				
				case 2:
				power_lifetimediagram(Year,2,U,pHDDATA,pRANDNUM);
				flag=0;
				break;
			}
			continue;
		}
		
		if(YEAR==1&&(flag==1||flag==2))
		{
			switch(flag)
			{
				case 1:
				power_yeardiagram(Month,1,U,pWHDATA,powerDATE,pRANDNUM);
				flag=0;
				break;
				
				case 2:
				power_yeardiagram(Month,2,U,pHDDATA,powerDATE,pRANDNUM);
				flag=0;
				break;
			}
			continue;
		}
		
		if(MONTH==1&&(flag==1||flag==2))
		{
			switch(flag)
			{
				case 1:
				if(powerDATE.month==1||powerDATE.month==3||powerDATE.month==5||powerDATE.month==7||powerDATE.month==8
					||powerDATE.month==10||powerDATE.month==12)
				{
					power_monthdiagram1(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
				}
				else if(powerDATE.month==4||powerDATE.month==6||powerDATE.month==9||powerDATE.month==11)	
				{
					power_monthdiagram2(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
				}
				if(powerDATE.year!=2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram3(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
					}
				}
				else if(powerDATE.year==2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram4(Day,1,U,pWHDATA,powerDATE,pRANDNUM);
					}
				}
				flag=0;
				break;
				
				case 2:
				if(powerDATE.month==1||powerDATE.month==3||powerDATE.month==5||powerDATE.month==7||powerDATE.month==8
					||powerDATE.month==10||powerDATE.month==12)
				{
					power_monthdiagram1(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
				}
				else if(powerDATE.month==4||powerDATE.month==6||powerDATE.month==9||powerDATE.month==11)	
				{
					power_monthdiagram2(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
				}
				if(powerDATE.year!=2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram3(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
					}
				}
				else if(powerDATE.year==2024)
				{
					if(powerDATE.month==2)
					{
						power_monthdiagram4(Day,2,U,pHDDATA,powerDATE,pRANDNUM);
					}
				}
				flag=0;
				break;
			}
			continue;
		}
		
		if(DAY==1&&(flag==1||flag==2))
		{
			switch(flag)
			{
				case 1:
				power_daydiagram(Time,1,U,pWHDATA,powerDATE,pRANDNUM);
				flag=0;
				break;
				
				case 2:
				power_daydiagram(Time,2,U,pHDDATA,powerDATE,pRANDNUM);
				flag=0;
				break;
			}
			continue;
		}
	}
	return 12;
}
	
void power_daydiagram(float a[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x,dy;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	int n=24;//24个时间点
	int dx=9,y=450;
	char *time[]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24"};
	int year,month,day;
	float weather;
	year=DATE.year;
	month=DATE.month;
	day=DATE.day;
	 
	//float a[25]={0,0,0,0,0,0,0.59,1.91,3.61,4.25,4.01,5.69,6.31,4.56,2.93,0.95,0.13};//更改
	//char *p[]={"0","2","4","6","8","10"};//更改2
	// U->Inventer_type=0;
	// U->Ban_num = 100;
	// U->Inventer_type = 0;
	//TODAYPOWER(1,U,10,b);
	real_TODAYPOWER(U,year,month,day,DIQU,a,pDATA,pRANDNUM);
	weather=today_weather(year,month,day,pDATA);
	/* closegraph();
	 for(i=0;i<24;i++)
	{
		printf("%d\n",*(a+i));
	} 
	printf("%d\n",sizeof(a));
	getchar();  */
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	//setviewport(120,100,630,470,1);
	settextstyle(2,0,3);
	for(i=0;i<=n-1;i++)
	{
		x=20*i+153;
		dy=(*(a+i))/(U->Ban_num)*0.15;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(146,140,624,450);
	for(i=157;i<=620;i=i+20)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,time[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		//i++;
	}
	settextstyle(0,1,1);
	outtextxy(130,140,"power production");
	puthz(155,150,"天气",16,18,CYAN);
	settextstyle(1, 0, 2);
	setcolor(CYAN);
	outtextxy(195,150-6,":");//weather==1.0
	if(weather > (1.0-1e-4)&&weather < (1.0+1e-4))//weather > (1.0-1e-4)&&weather < (1.0+1e-4)
	{
		puthz(205,150,"晴",16,18,CYAN);
	}
	else if (weather > (0.75-1e-4)&&weather < (0.75+1e-4))
	{
		puthz(205,150,"阴",16,18,CYAN);
	}
	else if(weather > (0.3-1e-4)&&weather < (0.3+1e-4))
	{
		puthz(205,150,"雨",16,18,CYAN);
	}
}

void power_monthdiagram1(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)//31天
{
	int i=0,j=0,x,dy;   
	int n=31;///31天
	int dx=9,y=450;
	char *day[]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
	//float a[32];//需要更改
	int year,month;
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	year=DATE.year;
	month=DATE.month;
	real_MONTHPOWER(U,year,month,DIQU,a,pDATA,pRANDNUM);
	   
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(i=0;i<=n-1;i++)
	{
		x=15*i+158;
		dy=(*(a+i))/(U->Ban_num)*0.021;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=163;i<=620;i=i+15)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,day[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130,140,"power production");
}

void power_monthdiagram2(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)//30天
{
	float i=0.0,x;
	int m,j=0,dy;   
	int n=30;///30天
	int dx=9,y=450;
	char *day[]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"};
	//float a[32];//需要更改
	int year,month;
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	year=DATE.year;
	month=DATE.month;
	real_MONTHPOWER(U,year,month,DIQU,a,pDATA,pRANDNUM);
	
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(m=0;m<=n-1;m++)
	{
		x=15.5*m+158;
		dy=(*(a+m))/(U->Ban_num)*0.021;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=163.0;i<=620.0;i=i+15.5)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,day[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130+1,140,"power production");
}

void power_monthdiagram3(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	float i=0.0,x;
	int m,j=0,dy;   
	int n=28;///28天
	int dx=9,y=450;
	char *day[]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28"};
	//float a[32];//需要更改
	int year,month;
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	year=DATE.year;
	month=DATE.month;
	real_MONTHPOWER(U,year,month,DIQU,a,pDATA,pRANDNUM);
	
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(m=0;m<=n-1;m++)
	{
		x=16.5*m+158;
		dy=(*(a+m))/(U->Ban_num)*0.021;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=163.0;i<=620.0;i=i+16.5)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,day[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130+1,140,"power production");
}

void power_monthdiagram4(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)//29天
{
	int i=0,j=0,x,dy;   
	int n=29;///29天
	int dx=9,y=450;
	char *day[]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29"};
	//float a[32];//需要更改
	int year,month;
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	year=DATE.year;
	month=DATE.month;
	real_MONTHPOWER(U,year,month,DIQU,a,pDATA,pRANDNUM);
	
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(i=0;i<=n-1;i++)
	{
		x=16*i+158;
		dy=(*(a+i))/(U->Ban_num)*0.021;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=163;i<=620.0;i=i+16)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,day[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130+1,140,"power production");
}

void power_yeardiagram(float a[13],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x,dy;  
	int n=12;//12个月
	int dx=20,y=450;
	char *month[]={"1","2","3","4","5","6","7","8","9","10","11","12"};
	//float a[13];//需要更改
	int year;
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	year=DATE.year;
	YEARPOWER(U,DIQU,year,a,pDATA,pRANDNUM);
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(i=0;i<=n-1;i++)
	{
		x=40*i+156;
		dy=(*(a+i))/(U->Ban_num)*0.00075;
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=165;i<=620;i=i+40)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,month[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130+1,140,"power production");

}

void power_lifetimediagram(float a[6],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct RandNum *pRANDNUM)
{
	int i=0,j=0,x,dy;  
	int n=5;///5年
	int dx=40,y=450;
	char *year[]={"2023","2024","2025","2026","2027"};
	//float a[6];//需要更改
	//char *p[]={"0","2","4","6","8","10"};//需要更改
	LIFEPOWER(U,DIQU,a,pDATA,pRANDNUM);
	setfillstyle(1,WHITE);
	bar(105,130+1,639,480);
	setcolor(DARKGRAY);
	setlinestyle(0, 0, 1);
	settextstyle(2,0,3);
	for(i=0;i<=n-1;i++)
	{
		x=92*i+180;
		dy=(*(a+i))/(U->Ban_num)*0.00009;//zhuyi
		setfillstyle(1,GREEN);
		bar(x,y,x+dx,y-dy);
	}
	setcolor(DARKGRAY);
	rectangle(150,140,620,450);
	for(i=200;i<=620.0;i=i+92)
	{
		line(i,450,i,460);
		outtextxy(i-4,460+2,year[j]);
		j++;
	}
	i=0;
	for(j=0;j<=200;j=j+40)
	{
		//line(145,450-1.4*j,150,450-1.4*j);
		setlinestyle(1,0,1);
		line(150,450-1.4*j,620,450-1.4*j);
		//outtextxy(135,450-1.4*j,p[i]);
		i++;
	}
	settextstyle(0,1,1);
	outtextxy(130,140,"power production");
}

		
void draw_diagram()
{
	int i,j;
	/* float x=4.5600;
	char str[50];
	setcolor(DARKGRAY);
	settextstyle(0,0,3);
	my_ftoa(x,4,str);//中间填1234 
	outtextxy(100,100,str);*/
	setbkcolor(WHITE);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(1,40,639,40);
	line(1,0,1,480);
	line(1, 479, 639, 479);
	line(100,40,100,479);
	line(100,100,639,100);
	setcolor(BLUE);
	setlinestyle(0,0,3);
	rectangle(610,5,630,25);
	line(610,5,630,25);
	line(630, 5, 610, 25);
	
	//画顶端选择栏
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(0, HORIZ_DIR, 1);
	puthz(5,4,"日照变化图",32,34,BLUE);
	line(180,0,180,40);
	puthz(180+2,4,"电站概况",32,34,BLUE);
	line(320,0,320,40);
	puthz(320+2,4,"设备管理",32,34,BLUE);
	line(460,0,460,40);
	puthz(460+2,4,"关于我们",32,34,BLUE);
	line(600,0,600,40);
	
	//画日月年生命期选择界面
	setlinestyle(0,0,3);
	//setfillstyle(1,GREEN);
	rectangle(100+20,40+10,200,100-10);
	puthz(120+25,50+5,"日",32,34,GREEN);
	rectangle(200+30,40+10,310,100-10);
	puthz(230+25,50+5,"月",32,34,GREEN);
	rectangle(310+30,40+10,420,100-10);
	puthz(340+25,50+5,"年",32,34,GREEN);
	rectangle(420+30,40+10,600,100-10);
	puthz(450+25,50+5,"生命期",32,34,GREEN);
	
	//画左侧信息栏
	setcolor(DARKGRAY);
	puthz(8,60,"选择地区",24,22,LIGHTGRAY);
	rectangle(15,100,85,140);
	puthz(15+2,100+2,"武汉",32,34,DARKGRAY);
	rectangle(15,160,85,200);
	puthz(15+2,160+2,"邯郸",32,34,DARKGRAY);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(1,215,100,215);
	setfillstyle(1,LIGHTGREEN);
	puthz(8,230,"切换模式",24,22,LIGHTGRAY);
	bar(15,270,85,310);
	puthz(15+2,270+2,"同比",32,34,GREEN);
	setfillstyle(1,LIGHTCYAN);
	bar(15,330,85,370);
	puthz(15+2,330+2,"环比",32,34,CYAN);
	setfillstyle(1,BLUE);
	bar(15,390,85,430);
	puthz(15+2,390,"功率",32,34,LIGHTBLUE);
}

static int show_date1(DATE date)//显示年月日
{
	char YearBuffer[10],MonthBuffer[4],DayBuffer[4];
	setlinestyle(0,0,3);
	setfillstyle(1,WHITE);
	bar(105,100+1,639,130+1);
	setcolor(RED);
	line(130,110,120,120);
	line(120,120,130,130);
	line(225,110,235,120);
	line(235,120,225,130);
	
	line(290,110,280,120);
	line(280,120,290,130);
	line(345,110,355,120);
	line(355,120,345,130);
	
	line(400,110,390,120);
	line(390,120,400,130);
	line(460,110,470,120);
	line(470,120,460,130);
	itoa(date.year,YearBuffer,10);
	itoa(date.month,MonthBuffer,10);
	itoa(date.day,DayBuffer,10);
	
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(153,110-3,YearBuffer);
	outtextxy(310,110-3,MonthBuffer);
	outtextxy(420,110-3,DayBuffer);
	return 0;
}

static int show_date2(DATE date)//显示年月
{
	char YearBuffer[10],MonthBuffer[4];
	setlinestyle(0,0,3);
	setfillstyle(1,WHITE);
	bar(105,100+1,639,130+1);
	setcolor(RED);
	line(215,110,205,120);
	line(205,120,215,130);
	line(320,110,330,120);
	line(330,120,320,130);
	
	line(375,110,365,120);
	line(365,120,375,130);
	line(430,110,440,120);
	line(440,120,430,130);
	
	itoa(date.year,YearBuffer,10);
	itoa(date.month,MonthBuffer,10);
	
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(245,110-3,YearBuffer);
	outtextxy(390,110-3,MonthBuffer);
	return 0;
}

static int show_date3(DATE date)
{
	char YearBuffer[10];
	setlinestyle(0,0,3);
	setfillstyle(1,WHITE);
	bar(105,100+1,639,130+1);
	setcolor(RED);
	line(280,110,270,120);
	line(270,120,280,130);
	line(430,110,440,120);
	line(440,120,430,130);
	
	itoa(date.year,YearBuffer,10);
		
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(330,110-3,YearBuffer);
	return 0;
}