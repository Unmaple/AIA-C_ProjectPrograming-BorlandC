#include"public.h"
#include"view.h"
#include"button.h"
#include"mmouse.h"
#include"BCNtc.h"

#define SUNBANMAX 18
#define LSUNBANMAX 14
#define PSUNBANMAX 16

int setBCButtonPos(struct BCButton *pBCB,int x,int y)
{
	pBCB->x1 = x;
	pBCB->y1 = y;
	pBCB->x2 = x+60;
	pBCB->y2 = y+60;
	return 0;
}

int setLogicButton(struct BCButton aBCB[])
{
	int i;
	for(i=0;i<7;i++)
	{
		setBCButtonPos(aBCB+2*i,130+70*i,140);
		setBCButtonPos(aBCB+2*i+1,130+70*i,280);
	}
	return 0;
}

int PsetBCButtonPos(struct BCButton *pBCB,int x,int y)
{
	
	pBCB->x1 = x+10;
	pBCB->y1 = y-10;
	pBCB->x2 = x+80;
	pBCB->y2 = y+60;
	return 0;
}

int XsetBCButtonPos(struct BCButton *pBCB,int x,int y)
{
	pBCB->x1 = x;
	pBCB->y1 = y;
	pBCB->x2 = x+70;
	pBCB->y2 = y+70;
	return 0;
}

int setPhysicButton(struct BCButton aBCB[])
{
	int i;
	PsetBCButtonPos(aBCB+0,200,143);
	PsetBCButtonPos(aBCB+1,200+22,143+84);
	PsetBCButtonPos(aBCB+2,200+22*2,143+84*2);
	PsetBCButtonPos(aBCB+3,290,120);
	PsetBCButtonPos(aBCB+4,290+22,120+84);
	PsetBCButtonPos(aBCB+5,290+22*2,120+84*2);
	PsetBCButtonPos(aBCB+6,70,190);
	PsetBCButtonPos(aBCB+7,40,290);
	PsetBCButtonPos(aBCB+8,130,360);
	PsetBCButtonPos(aBCB+9,270,143+84*3);
	XsetBCButtonPos(aBCB+10,530,110);
	XsetBCButtonPos(aBCB+11,530-90,110);
	XsetBCButtonPos(aBCB+12,530,110+90);
	XsetBCButtonPos(aBCB+13,530,110+90*2);
	XsetBCButtonPos(aBCB+14,530,110+90*3);
	XsetBCButtonPos(aBCB+15,440,110+90*3);
	return 0;
}

int page_view(int type)
{
	int page=11,i,j,BANNOW = 0,mode = 0;
	int draw=0;
	struct BCButton BItems[SUNBANMAX];
	struct BCWindow WItems;
	if(type == 1)
	{
		strcpy(WItems.Lines[1],"平单轴太阳能板");
		strcpy(WItems.Lines[5],  "PDZ-450W-P");
	}
	else if(type == 2)
	{
		strcpy(WItems.Lines[1],"双轴太阳能板");
		strcpy(WItems.Lines[5],  "SZ-400W-P");
	}
	else
	{
		strcpy(WItems.Lines[1],"固定太阳能板");
		strcpy(WItems.Lines[5], "GD-500W-P");
	}
	strcpy(WItems.Lines[0],  "名称");
	//strcpy(WItems.Lines[1],  "哈哈嗨");//上方已定义
	strcpy(WItems.Lines[2],  "SN:");
	strcpy(WItems.Lines[3],  "******075701");
	strcpy(WItems.Lines[4],  "型号");
	strcpy(WItems.Lines[6],  "当前功率");
	strcpy(WItems.Lines[7],  "345.24W");
	strcpy(WItems.Lines[8],  "倾角");
	strcpy(WItems.Lines[9],  "12.3");
	strcpy(WItems.Lines[10],  "方位角");
	strcpy(WItems.Lines[11],  "23.4");
	strcpy(WItems.Lines[12],  "Hello!");
	strcpy(WItems.Lines[13],  "哈哈嗨");
	WItems.LineNum = 12;
	WItems.on = 0;
	
	for(j = 0; j < SUNBANMAX; j ++)
	{
		if(type == 1)
		{
			strcpy(BItems[j].Lines,"平单轴太阳能板");
		}
		else if(type == 2)
		{
			strcpy(BItems[j].Lines,"双轴太阳能板");
		}
		else
		{
			strcpy(BItems[j].Lines,"固定太阳能板");
		}
		
		BItems[j].x1 = 500;
		BItems[j].y1 = 50;
		BItems[j].x2 = 580;
		BItems[j].y2 = 100;
		BItems[j].EdgeColor = 2;
		BItems[j].InnerColor = 15;
		BItems[j].ZIHAO = 16;
		
	}
	
	clrmous(MouseX, MouseY);
	cleardevice();
	draw_button();//
	
	mode = 2;
	draw_view();
	logical_view();
	setLogicButton(BItems);
	// for(j = 0; j < LSUNBANMAX; j ++)
	// {
		// BCRenderButton(BItems[j]);
	// }
	//BCRender(WItems);
	BANNOW = LSUNBANMAX;
	
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while(page==11)
	{
		newmouse(&MouseX,&MouseY,&press);
		
		if(WItems.on == 1)
		{
			if(BCDetect(&WItems) == 1)
			{
				draw = mode;
				delay(100);
			}
		}
		else if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2
		||mouse_press(290-26*4-10,40,290,80)==2
		||mouse_press(350,40,350+26*4+10,80)==2)
		{
			MouseS=1;
		}
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
		else if (mouse_press(290-26*4-10,40,290,80)==1)//物理视图
		{
			draw=1;
			mode = 1;
			lightbutton_select(13);
			recoverbutton_select(13);
		}
		else if (mouse_press(350,40,350+26*4+10,80)==1)//逻辑视图
		{
			draw=2;
			mode = 2;
			lightbutton_select(14);
			recoverbutton_select(14);
		}
		else if(mouse_press(20,5,40,25)==1)//返回
		{
			page=4;
			delay(100);
			return page;
		}
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			delay(100);
			return page;
		}
		else
		{
			for(i = 0; i < BANNOW; i ++)
			{
				if(BCDetectButton(BItems[i]) == 1)
				{
					WItems.on = 1;
					clrmous(MouseX, MouseY);
					BCRender(WItems);
					save_bk_mou(MouseX,MouseY);
					drawmous(MouseX,MouseY);
					delay(130);
					break;
				}
			}
		}
		
		if(draw==1||draw==2)
		{
			switch(draw)
			{
				case 1:
				clrmous(MouseX, MouseY);
				physical_view();
				setPhysicButton(BItems);
				// for(j = 0; j < PSUNBANMAX; j ++)
				// {
					// BCRenderButton(BItems[j]);
				// }
				save_bk_mou(MouseX,MouseY);
				drawmous(MouseX,MouseY);
				BANNOW = PSUNBANMAX;
				draw=0;
				delay(130);
				break;
				
				case 2:
				logical_view();
				setLogicButton(BItems);
				// for(j = 0; j < LSUNBANMAX; j ++)
				// {
					// BCRenderButton(BItems[j]);
				// }
				save_bk_mou(MouseX,MouseY);
				drawmous(MouseX,MouseY);
				BANNOW = LSUNBANMAX;
				draw=0;
				delay(130);
				break;
			}
		}
		
	}
	return 12;
}

void physical_view()
{
	int i;
	setfillstyle(1,WHITE);
	bar(0,96,640,480);
	
	cir_bar(20, 380, 100, 460, CYAN);
	setcolor(RED);
	setlinestyle(0,0,3);
	line(30,410,45,410);
	line(30,420,36,420);
	line(39,420,45,420);
	settextstyle(1,0,3);
	settextjustify(0, 2);
	outtextxy(50,405,"/");
	settextstyle(1,0,4);
	outtextxy(70,405,"~");
	
	setcolor(BLUE);
	lxrectangle(200,143);
	lxrectangle(200+22,143+84);
	lxrectangle(200+22*2,143+84*2);
	lxrectangle(290,120);
	lxrectangle(290+22,120+84);
	lxrectangle(290+22*2,120+84*2);
	lxrectangle(70,190);
	lxrectangle(40,290);
	lxrectangle(130,360);
	lxrectangle(270,143+84*3);
	setfillstyle(1,BLUE);
	bar(530,110,600,180);
	bar(530-90,110,600-90,180);
	bar(530,110+90,600,180+90);
	bar(530,110+90*2,600,180+90*2);
	bar(530,110+90*3,600,180+90*3);
	bar(440,110+90*3,510,180+90*3);
	lxline(200,143);
	lxline(200+22,143+84);
	lxline(200+22*2,143+84*2);
	lxline(290,120);
	lxline(290+22,120+84);
	lxline(290+22*2,120+84*2);
	lxline(70,190);
	lxline(40,290);
	lxline(130,360);
	lxline(270,143+84*3);
	for(i=0;i<4;i++)
	{
		line(530,110+35+90*i,600,110+35+90*i);
		line(530+35,110+90*i,530+35,180+90*i);
	}
	line(530-90,110+35,600-90,110+35);
	line(530-90+35,110,530-90+35,180);
	line(530-90,110+35+90*3,510,110+90*3+35);
	line(530-90+35,110+90*3,530-90+35,180+90*3);
	/* line(200,140,230,370);
	line(200,140,330,120);
	line(330,120,360,350);
	line(230,370,360,350);
	setfillstyle(1,BLUE);
	floodfill(300,280,BLUE); */
	//line(200,140,230,370);
}

void logical_view()
{
	int i;
	setfillstyle(1,WHITE);
	bar(0,96,640,600);
	
	cir_bar(20, 200, 100, 280, CYAN);
	setcolor(RED);
	setlinestyle(0,0,3);
	line(30,230,45,230);
	line(30,240,36,240);
	line(39,240,45,240);
	settextstyle(1,0,3);
	settextjustify(0, 2);
	outtextxy(50,225,"/");
	settextstyle(1,0,4);
	outtextxy(70,225,"~");
	setcolor(DARKGRAY);
	line(60,200,60,170);
	line(60,170,130,170);
	line(60,280,60,310);
	line(60,310,130,310);
	setfillstyle(1,BLUE);
	setcolor(WHITE);
	for(i=0;i<7;i++)
	{
		bar(130+70*i,140,190+70*i,200);
		line(130+70*i,170,190+10+70*i,170);
		line(160+70*i,140,160+70*i,200);
		bar(130+70*i,280,190+70*i,340);
		line(130+70*i,310,190+10+70*i,310);
		line(160+70*i,280,160+70*i,340);
	}
	setcolor(DARKGRAY);
	for(i=0;i<6;i++)
	{
		line(190+70*i,170,190+10+70*i,170);
		line(190+70*i,310,190+10+70*i,310);
	}
}

int lxrectangle(int x1,int y1)
{
	line(x1,y1,x1+20,y1+70);
	line(x1,y1,x1+70,y1-20);
	line(x1+20,y1+70,x1+90,y1+50);
	line(x1+70,y1-20,x1+90,y1+50);
	setfillstyle(1,BLUE);
	floodfill(x1+10,y1+10,BLUE);
	
	return 0;
}

int lxline(int x1,int y1)
{
	setcolor(WHITE);
	setlinestyle(0,0,3);
	line(x1+10,y1+35,x1+80,y1+15);
	line(x1+35,y1-10,x1+55,y1+60);
	
	return 0;
}

void draw_view()
{
	setbkcolor(WHITE);
	setfillstyle(1,RED);
	bar(290-26*4-10,40,290,80);
	puthz(290-26*4-5,40+6,"物理视图",24,26,WHITE);
	bar(350,40,350+26*4+10,80);
	puthz(350+5,40+6,"逻辑视图",24,26,WHITE);
}