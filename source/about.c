#include"public.h"
#include"about.h"
#include"image.h"
#include"date.h"
#include"pdata.h"
#include"ftoa.h"

int page_about(int mode,struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	int page=10;
	int flag=0;
	int num=0;
	clrmous(MouseX,MouseY);	
	cleardevice();
	draw_about1();
	recoverbutton_about(1);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while(page==10)
	{
		newmouse(&MouseX,&MouseY,&press);
		
		if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2)
		{
			MouseS=1;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
		
		if (MouseX > 290 && MouseX < 350 && MouseY > 430 && MouseY < 463)//切换
		{
			if (mouse_press(290, 430, 350, 463) == 2)//未点击
			{
				MouseS = 1;
				if (flag == 0)//防止被重复标亮
				{
					lightbutton_about();
					flag = 1;
				}
				continue;
			}

			if (mouse_press(290, 430, 350, 463) == 1)
			{
				MouseS = 0;
				lightbutton_about();
				num = (num + 1) % 2;
				switch (num)
				{
					case 0:
						draw_about1();//显示关于
						break;
					case 1:
						draw_about2(U,pWHDATA,pHDDATA,pRANDNUM);
						break;
				}
				continue;
			}
		}
		if (flag != 0)
		{
			MouseS = 0;
			recoverbutton_about(flag);
			flag = 0;
		}
		if(mouse_press(20,5,40,25)==1)
		{
			if(mode==1)
			{
				page=3;
				delay(100);
			}
			else if(mode==2)
			{
				page=4;
				delay(100);
			}
			return page;
		}
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			return page;
		}
	}
	return 12;
}

void draw_about1()
{
	delay(100);
	cleardevice();
	setbkcolor(BLACK);

	setfillstyle(1,WHITE);
	setlinestyle(0,0,3);
	rectangle(600,5,620,25);
	line(600,5,620,25);
	line(620, 5, 600, 25);
	rectangle(20,5,40,25);
	line(20,15,40,15);
	line(20,15,25,10);
	line(20,15,25,20);
	
	puthz(15,40,"开发人员",16,18,WHITE);
	setcolor(WHITE);
	settextstyle(1, 0, 2);
	settextjustify(0, 2);//输出左对齐，顶部对齐
	outtextxy(93,40-5,":");
	puthz(100,40,"华中科技大学人工智能与自动化学院",16,18,WHITE);
	puthz(100,65,"智实",16,18,GREEN);
	setcolor(GREEN);
	settextstyle(2, 0, 7);
	outtextxy(145,65-5,"2201");
	puthz(200,65,"班",16,18,GREEN);
	puthz(250,65,"曾明杰",16,18,YELLOW);
	setcolor(YELLOW);
	outtextxy(313,65-5,"&");
	puthz(330,65,"李欣",16,18,YELLOW);
	puthz(15,90,"测试人员",16,18,WHITE);
	settextstyle(1, 0, 2);
	setcolor(WHITE);
	outtextxy(93,90-5,":");
	puthz(100,90,"华中科技大学人工智能与自动化学院",16,18,WHITE);
	outtextxy(397,85,"C");
	puthz(420,90,"语言教授与副教授",16,18,WHITE);
	puthz(15,115,"更新日期",16,18,WHITE);
	outtextxy(93,115-5,":");
	settextstyle(2, 0, 7);
	setcolor(CYAN);
	outtextxy(100,115-5,"2023/04/18");
	puthz(15,140,"大小",16,18,WHITE);
	setcolor(WHITE);
	settextstyle(1, 0, 2);
	outtextxy(52,140-5,":");
	setcolor(RED);
	settextstyle(2, 0, 7);
	outtextxy(62,140-5,"236 BM");
	setcolor(LIGHTCYAN);
	outtextxy(15,165,"VERSION: 2.1.7");
	setcolor(WHITE);
	puthz(70,210,"此软件为入门级产品",16,18,WHITE);
	outtextxy(235,210-5,",");
	puthz(245,210,"对电脑配置要求较低",16,18,WHITE);
	setlinestyle(0,0,1);
	circle(412,225,2);
	puthz(70,240,"此软件的开发目的为",16,18,WHITE);
	outtextxy(235,240-5,",");
	puthz(245,240,"模拟屋顶光伏发电",16,18,WHITE);
	outtextxy(395,240-5,",");
	puthz(405,240,"让电厂工作人员或感兴趣",16,18,WHITE);
	puthz(35,265,"人群更好得感受光伏发电的意义",16,18,WHITE);
	outtextxy(290,265-5,",");
	puthz(300,265,"进一步投入生产生活",16,18,WHITE);
	outtextxy(465,265-5,",");
	puthz(475,265,"响应时代呼唤",16,18,WHITE);
	outtextxy(590,265-5,",");
	puthz(35,290,"实现光伏平价与碳中和全球化",16,18,WHITE);
	outtextxy(268,290-5,",");
	puthz(280,290,"绿色生活",16,18,WHITE);
	circle(355,305-2,2);
	puthz(370,290,"如果有任何问题",16,18,WHITE);
	outtextxy(500,290-5,",");
	puthz(510,290,"可向开发者",16,18,WHITE);
	puthz(35,315,"反馈",16,18,WHITE);
	outtextxy(75,315-5,",");
	puthz(85,315,"开发者将进一步修改和完善",16,18,WHITE);
	circle(305,330-2,2);
	puthz(70 ,345, "最后，我们想感谢", 16, 18, WHITE);
	settextstyle(1, 0, 2);
	outtextxy(70+18*8+5, 345-5, "C");
	puthz(70 + 18 *9+10, 345, "语言课程设计的所有老师、助教，以及帮助过", 16, 18, WHITE);
	puthz(35, 370, "我们的同学。软件依旧有很多不足或者是可更新优化的地方。希望我们", 16, 18, WHITE);
	puthz(35, 395, "能一直热爱",16, 18, WHITE);
	outtextxy(35 + 18 * 5+5, 395-5, "C");
	puthz(35 + 18*6+10, 395, "语言和编程设计，在软件开发方面走的更远。", 16, 18, WHITE);

}
void draw_about2(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM)
{
	float sum;
	float coal,carbon,tree;
	char CoalBuffer[30],CarbonBuffer[30],TreeBuffer[30];
	delay(100);
	cleardevice();
	setbkcolor(BLACK);
	//bmp_convert("C:\\test\\photo\\green.bmp","C:\\test\\photo\\green.dbm");
	show_dbm(0,30,"..\\photo\\green.dbm");
	setcolor(LIGHTGRAY);
	setfillstyle(1,WHITE);
	bar(0,0,640,30);
	bar(0,30,10,328);
	bar(620,30,640,330);
	bar(0,330,640,480);
	setlinestyle(0,0,3);
	cir_bar(45,98,208,310,BLUE);
	cir_bar(208+25,98,208*2-20,310,BLUE);
	cir_bar(208*2-20+25+2,98,208*3-20*2+3,310,BLUE);
	
	sum=TOTALPOWER(U,pRANDNUM,pWHDATA,pHDDATA);
	coal=sum/123;
	carbon=sum/12700;
	tree=carbon*100/5;
	my_ftoa(coal,4,CoalBuffer);
	my_ftoa(carbon,2,CarbonBuffer);
	my_ftoa(tree,4,TreeBuffer);
	/* closegraph();
	printf("%f\n",coal);
	printf("%f\n",carbon);
	printf("%f\n",tree);
	getchar(); */
	bar(100,200,190,260);
	bar(260,200,390,260);
	bar(480,200,580,260);
	settextstyle(2,0,6);
	setcolor(RED);
	outtextxy(70,223,CoalBuffer);
	outtextxy(250,223,CarbonBuffer);
	outtextxy(440,223,TreeBuffer);
	puthz(175,220,"吨",24,26,RED);
	puthz(340,220,"万吨",24,26,RED);
	puthz(550,220,"棵",24,26,RED);
	
	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	rectangle(600,5,620,25);
	line(600,5,620,25);
	line(620, 5, 600, 25);
	rectangle(20,5,40,25);
	line(20,15,40,15);
	line(20,15,25,10);
	line(20,15,25,20);
	
	settextjustify(0, 2);
	settextstyle(3, 0, 4);
	setcolor(RED);
	outtextxy(125, 330, "  HUST:");
	settextjustify(0,2);
	settextstyle(2, 0, 8);
	setcolor(LIGHTRED);
	outtextxy(215, 340, "     SCHOOL OF");
	setcolor(GREEN);
	outtextxy(50, 375, "ARTIFICIAL INTELLIGENCE AND AUTOMATION");
	
}

void recoverbutton_about(int flag)//About按钮恢复
{
	clrmous(MouseX, MouseY);

	switch (flag)
	{
		case 1:
			setfillstyle(1, BLUE);
			bar(290, 430, 350, 463);
			puthz(296, 430+5, "切换", 24, 26, WHITE);
			break;
	}
}

void lightbutton_about()//About按钮点亮
{
	clrmous(MouseX, MouseY);
	delay(10);
	setcolor(WHITE);
	setlinestyle(0, 0, 1);
	setfillstyle(1, LIGHTBLUE);
	bar(290, 430, 350, 463);
	rectangle(290, 430, 350, 463);	//画边框
	puthz(296, 430+5, "切换", 24, 26, BLUE);
}