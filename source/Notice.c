/*****************************************
Notice.c
COPYRIGHT:  Zengmingjie
FUNCTION:   store basic graphics elements and render them
DATE:       2023/3/?-4/13(Debug and Reinforcement)
Available code lines:ZMJ-about110lines
******************************************/
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include<stdio.h>
#include"mimage.h"
#include"MZFK.h"
#include"mmouse.h"
#include"Notice.h"
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

int Render(struct Window W)
{
	int i;
	if(W.on == 0)
		return 1;
	MRBar(WindowX, WindowX+ WindowWidth, WindowY, WindowY + WindowHeight,15);
	MRRect(WindowX, WindowX+ WindowWidth, WindowY, WindowY + WindowHeight,0);
	for(i = 0; i < W.LineNum;i++)
	{
		if((W.Lines[i][0])<='~'&&(W.Lines[i][0])>=' ')//检测本字符串中是中文还是英文
		{
			MZFS(WindowX+10, WindowY + 20 + 20*i,0,W.Lines[i]);
		}
		else
		{
			MRputhz(WindowX+10, WindowY + 20 + 20*i,W.Lines[i],16,16,0);
		}
	}
	MRBar(WindowX+ WindowWidth-20, WindowX+ WindowWidth, WindowY, WindowY + 20,7);
	MRRect(WindowX+ WindowWidth-20, WindowX+ WindowWidth, WindowY, WindowY + 20,0);
	MRLine(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth,WindowY + 20,12);
	MRLine(WindowX+ WindowWidth-20, WindowY + 20, WindowX+ WindowWidth,WindowY,12);
	return 0;
}

int RenderButton(struct Button B)
{
	int i, z1, z2, z3, z4, y1, y2, y3, y4;
	z1 = B.x1;
	z2 = B.x1;
	z3 = B.x2;
	z4 = B.x2;
	y1 = B.y1;
	y2 = B.y2;
	y3 = B.y1;
	y4 = B.y2;
	MRTriangle(z1,y1,z2,y2,z3,y3,B.InnerColor);
	MRTriangle(z2,y2,z3,y3,z4,y4,B.InnerColor);
	MROutLine(z1,y1,z2,y2,B.EdgeColor);
	MROutLine(z1,y1,z3,y3,B.EdgeColor);
	MROutLine(z2,y2,z4,y4,B.EdgeColor);
	MROutLine(z3,y3,z4,y4,B.EdgeColor);
	if(B.ZIHAO == 8)
	{
		MZFS(B.x1+5, B.y1+5,0,B.Lines);
	}
	else
	{
		MRputhz(B.x1+5, B.y1+5,B.Lines,B.ZIHAO,B.ZIHAO+3,0);
	}
	return 0;
}

int Detect(struct Window *W)
{
	if(W->on == 0)
		return 1;
	if(mouse_press(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20)==2)
	{
		MouseS=1;
	}

	else if(mouse_press(0,0,640,480)==2)
	{
		MouseS=0;
	}

	if(mouse_press(WindowX+ WindowWidth-20, WindowY, WindowX+ WindowWidth, WindowY + 20)==1)//start
	{
		MouseS=0;
		W->on = 0;
		return 2;
	}
	return 0;
}

int DetectButton(struct Button B)
{
	if(mouse_press(B.x1,  B.y1,B.x2, B.y2)==2)
	{
		MouseS=1;
	}
	if(mouse_press(B.x1,  B.y1,B.x2, B.y2)==1)//start
	{
		MouseS=0;
		return 1;
	}
	return 0;
}
