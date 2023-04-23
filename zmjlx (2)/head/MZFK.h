
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include<stdio.h>
#include"mimage.h"
//#define min(x, y) x < y ? x : y
//#define max(x, y) x > y ? x : y
#define ZfkCap 96//从32到127应该是够了，先写字母
//#include <conio.h>
//#define TrBlock 10

//此处为在2.23解决内存限制问题的制作人曾明杰
//现在将之前所有Render系列函数重写，命名为MR开始的函数，意为MemoryRender
//显存位置为ai.c，共4个源文件，此外的均需重置
//本文件仅用于显示8*8大小字符，考虑到边缘留空，所有字符应以7*7为基本大小设计。

//以下本应写在头文件下
/*****
int MZFKinit();
int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure);
int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
*****/
;
extern unsigned char STORAGE[ZfkCap][8];
;
int MZFKinit();

int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure);//速度较像素版更快，控制像素更多，推荐优先使用

int  MZFtest(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
int  MZFS(unsigned int x,unsigned int y,unsigned char Color,unsigned char* S);
int  MZFI(unsigned int x,unsigned int y,unsigned char Color,int i)
