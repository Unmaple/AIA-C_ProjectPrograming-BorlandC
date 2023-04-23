#include"public.h"
#include"select.h"
#include"data.h"

/******************************************************
select.c
COPYRIGHT: lx
FUNCTION:  select project
ABSTRACT:
		
DATE: 2023/3/21
******************************************************/

int page_select(struct user *U,int mode)
{	
	int page = 0;
	//struct user UserData;
	//struct user *U = &UserData;//(struct user *)malloc(sizeof(struct user));
	int flag = 0;
	
	if(mode == 0)
	{
		U->Rack_type=-1;
		U->Ban_num=1;
		U->Inventer_type=-1;
	}
    
	clrmous(MouseX,MouseY);	
	cleardevice();
	draw_select(U);
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while (page==0||page==2)
	{
		newmouse(&MouseX,&MouseY,&press);
		if(mouse_press(175-2,95-2,185+2,105+2)==2
		||mouse_press(380-2,95-2,390+2,105+2)==2
		||mouse_press(555-2,95-2,565+2,105+2)==2
		||mouse_press(245-2,285-2,255+2,295+2) == 2
		||mouse_press(485-2,285-2,495+2,295+2)==2
		||mouse_press(120-10,360-10,260+10,400+10)==2
		||mouse_press(560,25,580,45) == 2
		||mouse_press(380-10,360-10,520+10,400+10)==2)
		{
			MouseS=1;
		}
		else if (mouse_press(30,185,230,185+22)==2)
		{
			MouseS=2;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
	
		else if(mouse_press(175-2,95-2,185+2,105+2) == 1)
		{
			lightcircle_rackselect(1);
			U->Rack_type=0;
			continue;
		}
		else if (mouse_press(380-2,95-2,390+2,105+2)==1)
		{
			lightcircle_rackselect(2);
			U->Rack_type=1;
			continue;
		}
		else if(mouse_press(555-2,95-2,565+2,105+2)==1)
		{
			lightcircle_rackselect(3);
			U->Rack_type=2;
			continue;
		}
		else if(mouse_press(245-2,285-2,255+2,295+2) == 1)
		{
			lightcircle_inventerselect(1);
			U->Inventer_type=0;
			continue;
		}
		else if (mouse_press(485-2,285-2,495+2,295+2)==1)
		{
			lightcircle_inventerselect(2);
			U->Inventer_type=1;
			continue;
		}
		else if(mouse_press(30,185,230,185+22)==1)
		{
			inputnum(U);
			continue;
		}
	
	
		if(mouse_press(120-10,360-10,260+10,400+10)==1)
		{
			flag=check_select(U);
			delay(100);
			if(flag==2)
			{
				selectfile(U);
				page=3;//目前还不确定
			}
			return page;
		}
	
		else if(mouse_press(380-10,360-10,520+10,400+10)==1)
		{
			page=1;
			return page;
		}
		
		else if(mouse_press(560,25,580,45) == 1)
		{
			page = 12;
			return page;
		}
	}
	return 12;
}

void draw_select(struct user *U)
{
	int i,j;
	char NumBuffer[20]={0};
	setbkcolor(GREEN);
	setfillstyle(1,WHITE);
	bar(20,20,600,440);
	
	setcolor(DARKGRAY);
	for(i=0;i<=20;i++)
	{
		line(20+i,440+i,600+i,440+i);
		line(600+i,20+i,600+i,440+i);
	}
	puthz(25,35,"支架类型",32,34,LIGHTGRAY);
	setfillstyle(1,GREEN);
	setlinestyle(0,0,3);
	
	setcolor(DARKGRAY);
	bar(30,80,170,120);
	puthz(30+2,80+2,"固定支架",32,34,WHITE);
	bar(200,80,375,120);
	puthz(200+2,80+2,"平单轴支架",32,34,WHITE);
	bar(405,80,550,120);
	puthz(405+2,80+2,"双轴支架",32,34,WHITE);
	if(U->Rack_type==-1)
	{
		setcolor(DARKGRAY);
		circle(180,100,5);
		circle(385,100,5);
		circle(560,100,5);
	}
	
	else if(U->Rack_type==0)//0为固定，1为平单轴，2为双轴
	{
		setcolor(LIGHTCYAN);
		circle(180,100,5);
		setcolor(DARKGRAY);
		circle(385,100,5);
		circle(560,100,5);
	}
	
	else if(U->Rack_type==1)
	{
		setcolor(LIGHTCYAN);
		circle(385,100,5);
		setcolor(DARKGRAY);
		circle(180,100,5);
		circle(560,100,5);
	}	
	
	else if(U->Rack_type==2)
	{
		setcolor(LIGHTCYAN);
		circle(560,100,5);
		setcolor(DARKGRAY);
		circle(180,100,5);
		circle(385,100,5);
	}

	setcolor(DARKGRAY);
	puthz(25,140,"组件数目",32,34,LIGHTGRAY);
	puthz(190,140+10,"范围是十到六百五",16,18,BLUE);
	bar(30,185,230,185+22);
	
	if(U->Ban_num!=1)
	{
		itoa(U->Ban_num,NumBuffer,10);
		setcolor(DARKGRAY);
		outtextxy(30+ 2, 185 - 2,NumBuffer);
	}
	
	puthz(25,225,"逆变器类型",32,34,LIGHTGRAY);
	bar(30,270,240,310);
	puthz(30+2,270+2,"集中式逆变器",32,34,WHITE);
	bar(270,270,480,310);
	puthz(270+2,270+2,"集散式逆变器",32,34,WHITE);
	
	if(U->Inventer_type==-1)
	{
		setcolor(DARKGRAY);
		circle(250,290,5);
		circle(490,290,5);
	}
	
	else if(U->Inventer_type==0)//0为集中式逆变器，1为集散式逆变器
	{
		setcolor(LIGHTRED);
		circle(250,290,5);
		setcolor(DARKGRAY);
		circle(490,290,5);
	}
	
	else if(U->Inventer_type==1)
	{
		setcolor(LIGHTRED);
		circle(490,290,5);
		setcolor(DARKGRAY);
		circle(250,290,5);
	}
	
	setfillstyle(1,LIGHTCYAN);
	bar(120-10,360-10,260+10,400+10);
	puthz(120,360,"进入模拟",32,34,DARKGRAY);
	
    bar(380-10,360-10,520+10,400+10);
	puthz(380,360,"历史记录",32,34,DARKGRAY);
	
	setcolor(BLUE);
	rectangle(560,25,580,45);
	line(560,25,580,45);
	line(580,25,560,45);
	
}

void lightcircle_rackselect(int flag)
{
	clrmous(MouseX,MouseY);
	delay(10);
	setlinestyle(0,0,3);
	
	switch(flag)
	{ 
		case 1:
		setcolor(LIGHTCYAN);
		circle(180,100,5);
		setcolor(DARKGRAY);
		circle(385,100,5);
		circle(560,100,5);
		break;
		
		case 2:
		setcolor(LIGHTCYAN);
		circle(385,100,5);
		setcolor(DARKGRAY);
		circle(180,100,5);
		circle(560,100,5);
		break;
		
		case 3:
		setcolor(LIGHTCYAN);
		circle(560,100,5);
		setcolor(DARKGRAY);
		circle(180,100,5);
		circle(385,100,5);
		break;
	}
	
}

void lightcircle_inventerselect(int num)
{
	clrmous(MouseX,MouseY);
	delay(10);
	setlinestyle(0,0,3);
	
	switch(num)
	{
		case 1:
		setcolor(LIGHTRED);
		circle(250,290,5);
		setcolor(DARKGRAY);
		circle(490,290,5);
		break;
		
		case 2:
		setcolor(LIGHTRED);
		circle(490,290,5);
		setcolor(DARKGRAY);
		circle(250,290,5);
		break;
	}
}

void inputnum(struct user *U)
{
	int i=0;
	char t;
	char a[2];
	char NumBuffer[20]={0};
	clrmous(MouseX, MouseY);
	setcolor(BLUE);
	setfillstyle(1, LIGHTGRAY);
	bar(30,185,230,185+22);
	settextstyle(1, 0, 2);//三倍笔划字体，水平输出
	settextjustify(0, 2);//输出左对齐，顶部对齐
	while (1)
	{
		t = bioskey(0);
		if (i < 4)
		{
			if (t != '\n'
				&& t != '\r'
				&& t != ' ')
			{
				if (t != '\b')
				{
					NumBuffer[i] = t;
					a[0] = t;
					a[1] = '\0';
					NumBuffer[i + 1] = '\0';
					outtextxy(2 + 30 + i * 10, 185 - 2, a);
					i++;
				}
				else if (t == '\b' && i > 0)
				{
					bar(30 + i * 10 - 8, 185 , 30 + i * 10 + 4, 185 + 22);
					i--;
					NumBuffer[i] = '\0';
				}
			}
			else
			{
				setfillstyle(1, LIGHTGRAY);
				break;
			}
		}
		
		else if (i >= 4)
		{
			if (t != '\n'
				&& t != '\r'
				&& t != ' '
				&& t != 033)
			{
				if (t == '\b' && i > 0)
				{
					bar(30 + i * 10 - 8, 185 , 30 + i * 10 + 4, 185 + 22);
					i--;
					NumBuffer[i] = '\0';
				}
			}
			else
			{
				setfillstyle(1, LIGHTGRAY);
				break;
			}
		}
	}
	U->Ban_num=atoi(NumBuffer);
	clrmous(MouseX, MouseY);
	setfillstyle(1, GREEN);
	bar(30,185,230,185+22);
	outtextxy(30+ 2, 185 - 2, NumBuffer);
}
	
void selectfile(struct user *U)
{
	FILE *fp = NULL;

	if ((fp = fopen("..\\data\\User.dat", "rb+")) == NULL)
	{
		closegraph();
		printf("the file in select.c cannot be opened%\n");
		delay(1000);
		exit(1);
	}
	
	fseek(fp, 0, 2); //以文件尾为基准
	fwrite(U, sizeof(struct user), 1, fp);
	
	//if (U != NULL)
	//{
	//	free(U);
	//	U = NULL;
	//}

	if (fclose(fp) != 0)
	{
		printf("\n the file in select.c cannot close data.");
		delay(3000);
		exit(1);
	}
}

int check_select(struct user *U) 
{
	int t=0;
	
	if(U->Rack_type!=0&&U->Rack_type!=1&&U->Rack_type!=2)
	{
		puthz(410,140,"请做出选择",16,16,RED);
		delay(1000);
		setfillstyle(1,WHITE);
		bar(410,140,600,140+20);
		return 0;
	}
	
	else
	{
		t++;
	}
	
	if(U->Ban_num>650||U->Ban_num<10)
	{
		puthz(250,185,"请输入正确的组件数目",16,16,RED);
		delay(1000);
		setfillstyle(1,WHITE);
		bar(250,185,600,185+20);
		return 0;
	}
	
	else
	{
		t++;
	}
	
	if(U->Inventer_type!=0&&U->Inventer_type!=1)
	{
		puthz(400,320,"请做出选择",16,16,RED);
		delay(1000);
		setfillstyle(1,WHITE);
		bar(400,320,600,320+20);
		return 0;
	}
	
	return t;
}

