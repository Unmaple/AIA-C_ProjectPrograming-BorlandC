/****
LIXIN Notice .c
***/

#include <graphics.h>
#include <dos.h>
#include <string.h>
#include<stdio.h>
#include"mimage.h"
#include"MZFK.h"
#include"mmouse.h"
#include"hz.h"


//MARK 0226BUG修复：.h文件中声明与.c实现中不同导致类型转换错误
//MARK 0226ERROR，斜线多次崩溃，目前观测到原因为计算中的步长中间量被修改为0，
//未知是否为所有浮点数同时崩溃
//经测试，并非所有浮点数存储位置均崩溃，亦非所有浮点数运算位置均崩溃，但直线运动的表现形式与sin，cos遇到的bug如出一辙，猜测为同一原因

#define WindowX 100
#define WindowY 100
#define WindowWidth 400
#define WindowHeight 300
;//不加会报declaration error,不理解
struct BCWindow //全是ascii字符串
{
	char Lines[18][80];
	int LineNum;
	int on;
};

struct BCButton //ZIHAO非8时为汉字
{
	char Lines[80];
	unsigned int x1;
	unsigned int y1;
	unsigned int x2;
	unsigned int y2;
	unsigned char EdgeColor;
	unsigned char InnerColor;
	unsigned char ZIHAO;
	
};

int BCRender(struct BCWindow W)
{
	int i;
	if(W.on == 0)
		return 1;
	setfillstyle(1,15);
	bar(WindowX, WindowY, WindowX+ WindowWidth, WindowY + WindowHeight);
	setcolor(DARKGRAY);
	rectangle(WindowX, WindowY, WindowX+ WindowWidth, WindowY + WindowHeight);
	settextstyle(0,0,1);
	for(i = 0; i < W.LineNum;i++)
	{
		if((W.Lines[i][0])<='~'&&(W.Lines[i][0])>=' ')//检测本字符串中是中文还是英文
		{
			
			//MZFS(WindowX+10, WindowY + 20 + 20*i,0,W.Lines[i]);
			outtextxy(WindowX+10, WindowY + 20 + 20*i,W.Lines[i]);
		}
		else
		{
			puthz(WindowX+10, WindowY + 20 + 20*i,W.Lines[i],16,16,DARKGRAY);
		}
	}
	setcolor(8);
	bar(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20);
	setcolor(DARKGRAY);
	rectangle(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20);
	setcolor(12);
	line(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth,WindowY + 20);
	line(WindowX+ WindowWidth-20, WindowY + 20, WindowX+ WindowWidth,WindowY);
	return 0;
}

int BCRenderButton(struct BCButton B)
{
	int i;

	setfillstyle(1,12);
	//bar(500, 50, 580, 125);
	bar(B.x1, B.y1, B.x2, B.y2);
	setcolor(0);
	rectangle(B.x1, B.y1, B.x2, B.y2);
	//MRBar(B.x1, B.x2, B.y1, B.y2,B.InnerColor);
	
	//MRRect(B.x1, B.x2, B.y1, B.y2,B.EdgeColor);
	if(B.ZIHAO == 8)
	{
		settextstyle(0,0,1);
		//MZFS(B.x1+5, B.y1+5,0,B.Lines);
		outtextxy(B.x1+5, B.y1+5,B.Lines);
	}
	else
	{
		puthz(B.x1+5, B.y1+5,B.Lines,B.ZIHAO,B.ZIHAO+3,0);
	}
	

	return 0;
}

int BCDetect(struct BCWindow *W)
{
	if(W->on == 0)
		return -1;
	if(mouse_press(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20)==2)
	{
		MouseS=1;
		return 2;
	}

	else if(mouse_press(0,0,640,480)==2)
	{
		MouseS=0;
	}

	if(mouse_press(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20)==1)//start
	{
		MouseS=0;
		W->on = 0;
		return 1;
	}

	return 0;
}

int BCDetectButton(struct BCButton B)
{
	if(mouse_press(B.x1,  B.y1,B.x2, B.y2)==2)
	{
		MouseS=1;
		return 2;
	}

//	else if(mouse_press(0,0,640,480)==2)
//	{
//		MouseS=0;
//	}

	if(mouse_press(B.x1,  B.y1,B.x2, B.y2)==1)//start
	{
		MouseS=0;
		return 1;
	}

	return 0;
}
