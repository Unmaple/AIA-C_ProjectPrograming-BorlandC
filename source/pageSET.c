#include"public.h"
#include"device.h"
#include"select.h"
#include"button.h"

int page_device(struct user *U,int mode)
{
	int page=9;
	int flag=0;
	
	clrmous(MouseX, MouseY);
	cleardevice();
	draw_button();//
	recoverbutton_device(1);
	devide(U);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while(page==9)
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
		if (MouseX > 265 && MouseX < 375 && MouseY > 425 && MouseY < 465)//�����豸
		{
			if (mouse_press(265, 425, 375, 465) == 2)//δ���
			{
				MouseS = 1;
				if (flag == 0)//��ֹ���ظ�����
				{
					lightbutton_device();
					flag = 1;
				}
				continue;
			}
			if (mouse_press(265, 425, 375, 465) == 1)
			{
				MouseS = 0;
				lightbutton_device();
				page=2;
				delay(100);
				return page;
			}
		}
		if (flag != 0)
		{
			MouseS = 0;
			recoverbutton_device(flag);
			flag = 0;
		}
		if(mouse_press(20,5,40,25)==1)//����
		{
			if(mode==1)
			{
				page=3;
				delay(100);
				return page;
			}
			else if (mode==2)
			{
				page=4;
				delay(100);
				return page;
			}
		}
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			return page;
		}
		
	}
	return 12;
}

void recoverbutton_device(int flag)
{
	clrmous(MouseX, MouseY);

	switch (flag)
	{
		case 1:
			setfillstyle(1, BLUE);
			bar(265, 425, 375, 465);
			puthz(265+4, 425+7, "�����豸", 24, 26, WHITE);
			break;
	}
}

void lightbutton_device()//device��ť����
{
	clrmous(MouseX, MouseY);
	delay(10);
	setcolor(LIGHTGRAY);
	setlinestyle(0, 0, 1);
	setfillstyle(1, LIGHTBLUE);
	bar(265, 425, 375, 465);
	rectangle(265, 425, 375, 465);	//���߿�
	puthz(265+4, 425+7, "�����豸", 24, 26,  BLUE);
}

void devide(struct user *U)
{
	int i;
	setbkcolor(WHITE);
	cir_bar(20, 40, 620, 168, CYAN);
	setcolor(BLUE);
	settextstyle(1,0,3);
	settextjustify(0, 2);
	outtextxy(20+9,40+2,"******10L1037220");
	puthz(20+4,72,"��վ����",24,26,LIGHTGRAY);
	setcolor(LIGHTGRAY);
	outtextxy(24*5+15,68,":");
	setcolor(RED);
	outtextxy(24*5+20,68,"AIA");
	puthz(24*7+12,72,"�������ϵͳ",24,26,DARKGRAY);
	
	setcolor(LIGHTGRAY);
	outtextxy(20+7,100,"SN");
	puthz(55,102,"��",24,26,LIGHTGRAY);
	setcolor(DARKGRAY);
	outtextxy(100,102,"******10L10372201");
	setcolor(LIGHTGRAY);
	outtextxy(80,100,":  ");
	puthz(20+4,136,"�豸����",24,26,LIGHTGRAY);
	outtextxy(140,133,": ");
	puthz(150,136,"ͨ��ģ��",24,26,DARKGRAY);
	
	cir_bar(20, 180+10, 620, 400, CYAN);
	setcolor(BLUE);
	outtextxy(20+9,190+2,"**");
	puthz(50,190+5,"�����",24,26,BLUE);
	setcolor(LIGHTGRAY);
	outtextxy(20+7,220,"SN :  ");
	outtextxy(130,253,":  ");//�豸����
	outtextxy(162,287,":  ");
	outtextxy(130,322," :  ");
	outtextxy(162,357,":  ");
	setcolor(DARKGRAY);
	outtextxy(100,220,"******103736");
	puthz(20+4,255,"�豸����",24,26,LIGHTGRAY);
	if(U->Inventer_type==0)
	{
		puthz(140,258,"����ʽ�����",24,26,DARKGRAY);
	}
	else if(U->Inventer_type==1)
	{
		puthz(140,258,"��ɢʽ�����",24,26,DARKGRAY);
	}
	puthz(20+7,290,"�����״̬",24,26,LIGHTGRAY);
	puthz(172,290,"����",24,26,DARKGRAY);
	puthz(20+7,325,"�й�����",24,26,LIGHTGRAY);
	outtextxy(140,322,"  12.56 KW");
	puthz(20+7,360,"�ʱ���Ч��",24,26,LIGHTGRAY);
	outtextxy(172,357," 2033/01/01");
}