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
		
		if (MouseX > 290 && MouseX < 350 && MouseY > 430 && MouseY < 463)//�л�
		{
			if (mouse_press(290, 430, 350, 463) == 2)//δ���
			{
				MouseS = 1;
				if (flag == 0)//��ֹ���ظ�����
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
						draw_about1();//��ʾ����
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
	
	puthz(15,40,"������Ա",16,18,WHITE);
	setcolor(WHITE);
	settextstyle(1, 0, 2);
	settextjustify(0, 2);//�������룬��������
	outtextxy(93,40-5,":");
	puthz(100,40,"���пƼ���ѧ�˹��������Զ���ѧԺ",16,18,WHITE);
	puthz(100,65,"��ʵ",16,18,GREEN);
	setcolor(GREEN);
	settextstyle(2, 0, 7);
	outtextxy(145,65-5,"2201");
	puthz(200,65,"��",16,18,GREEN);
	puthz(250,65,"������",16,18,YELLOW);
	setcolor(YELLOW);
	outtextxy(313,65-5,"&");
	puthz(330,65,"����",16,18,YELLOW);
	puthz(15,90,"������Ա",16,18,WHITE);
	settextstyle(1, 0, 2);
	setcolor(WHITE);
	outtextxy(93,90-5,":");
	puthz(100,90,"���пƼ���ѧ�˹��������Զ���ѧԺ",16,18,WHITE);
	outtextxy(397,85,"C");
	puthz(420,90,"���Խ����븱����",16,18,WHITE);
	puthz(15,115,"��������",16,18,WHITE);
	outtextxy(93,115-5,":");
	settextstyle(2, 0, 7);
	setcolor(CYAN);
	outtextxy(100,115-5,"2023/04/18");
	puthz(15,140,"��С",16,18,WHITE);
	setcolor(WHITE);
	settextstyle(1, 0, 2);
	outtextxy(52,140-5,":");
	setcolor(RED);
	settextstyle(2, 0, 7);
	outtextxy(62,140-5,"236 BM");
	setcolor(LIGHTCYAN);
	outtextxy(15,165,"VERSION: 2.1.7");
	setcolor(WHITE);
	puthz(70,210,"�����Ϊ���ż���Ʒ",16,18,WHITE);
	outtextxy(235,210-5,",");
	puthz(245,210,"�Ե�������Ҫ��ϵ�",16,18,WHITE);
	setlinestyle(0,0,1);
	circle(412,225,2);
	puthz(70,240,"������Ŀ���Ŀ��Ϊ",16,18,WHITE);
	outtextxy(235,240-5,",");
	puthz(245,240,"ģ���ݶ��������",16,18,WHITE);
	outtextxy(395,240-5,",");
	puthz(405,240,"�õ糧������Ա�����Ȥ",16,18,WHITE);
	puthz(35,265,"��Ⱥ���õø��ܹ�����������",16,18,WHITE);
	outtextxy(290,265-5,",");
	puthz(300,265,"��һ��Ͷ����������",16,18,WHITE);
	outtextxy(465,265-5,",");
	puthz(475,265,"��Ӧʱ������",16,18,WHITE);
	outtextxy(590,265-5,",");
	puthz(35,290,"ʵ�ֹ��ƽ����̼�к�ȫ��",16,18,WHITE);
	outtextxy(268,290-5,",");
	puthz(280,290,"��ɫ����",16,18,WHITE);
	circle(355,305-2,2);
	puthz(370,290,"������κ�����",16,18,WHITE);
	outtextxy(500,290-5,",");
	puthz(510,290,"���򿪷���",16,18,WHITE);
	puthz(35,315,"����",16,18,WHITE);
	outtextxy(75,315-5,",");
	puthz(85,315,"�����߽���һ���޸ĺ�����",16,18,WHITE);
	circle(305,330-2,2);
	puthz(70 ,345, "����������л", 16, 18, WHITE);
	settextstyle(1, 0, 2);
	outtextxy(70+18*8+5, 345-5, "C");
	puthz(70 + 18 *9+10, 345, "���Կγ���Ƶ�������ʦ�����̣��Լ�������", 16, 18, WHITE);
	puthz(35, 370, "���ǵ�ͬѧ����������кܶ಻������ǿɸ����Ż��ĵط���ϣ������", 16, 18, WHITE);
	puthz(35, 395, "��һֱ�Ȱ�",16, 18, WHITE);
	outtextxy(35 + 18 * 5+5, 395-5, "C");
	puthz(35 + 18*6+10, 395, "���Ժͱ����ƣ���������������ߵĸ�Զ��", 16, 18, WHITE);

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
	puthz(175,220,"��",24,26,RED);
	puthz(340,220,"���",24,26,RED);
	puthz(550,220,"��",24,26,RED);
	
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

void recoverbutton_about(int flag)//About��ť�ָ�
{
	clrmous(MouseX, MouseY);

	switch (flag)
	{
		case 1:
			setfillstyle(1, BLUE);
			bar(290, 430, 350, 463);
			puthz(296, 430+5, "�л�", 24, 26, WHITE);
			break;
	}
}

void lightbutton_about()//About��ť����
{
	clrmous(MouseX, MouseY);
	delay(10);
	setcolor(WHITE);
	setlinestyle(0, 0, 1);
	setfillstyle(1, LIGHTBLUE);
	bar(290, 430, 350, 463);
	rectangle(290, 430, 350, 463);	//���߿�
	puthz(296, 430+5, "�л�", 24, 26, BLUE);
}