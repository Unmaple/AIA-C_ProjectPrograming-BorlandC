/*****************************************
MZFK.c
COPYRIGHT:  Zengmingjie
FUNCTION:   Output ASCII letters to MR-series' buffer
DATE:       2023/2/25-3/1(Debug and Reinforcement)
Available code lines:ZMJ-about130lines
******************************************/
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include"mimage.h"
#include"MyMath.h"
#define ZfkCap 96//从32到127应该是够了，先写字母

//此处为在2.23解决内存限制问题的制作人曾明杰
//现在将之前所有Render系列函数重写，命名为MR开始的函数，意为MemoryRender
//显存位置为ai.c，共4个源文件，此外的均需重置
//本文件仅用于显示8*8大小字符，考虑到边缘留空，所有字符应以7*7为基本大小设计。
//2023.2.25,来自自动化2209的陈鑫楷同学帮助写作了本库对应的字符库文件（一个宽8高768的单色bmp）
//特此鸣谢！

//以下本应写在头文件下
;
static unsigned char STORAGE[ZfkCap][8];
int MZFKinit()
{
	//char *s = "C:\\test\\data\\ZFK.bmp";此处是绝对路径
	char *s = "..\\data\\ZFK.bmp";
	FILE *fp;
	unsigned int k;
	unsigned int i, j, bit,m;
	unsigned char temp[4];
	if ((fp = fopen(s, "rb")) == NULL)
	{
		printf("Cannot open MZFK data file!");
		getchar();
		return 1;
	}
	fseek(fp, 0x3E, 0);
	for(i = 0; i < ZfkCap; i ++)
	{
		for(j = 0; j < 8;j ++)
		{

			fread(temp,1,4,fp);
			STORAGE[i][7-j] = temp[0];
		}
	}
	fclose(fp);
	return 0;
}

static int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure)//速度较像素版更快，控制像素更多，推荐优先使用
{
	long elm = x/8+y * 80L;//element order	
	if(x > 639U ||y > 479U)//多长以上建议使用L？
	{
		return 1;
	}
	//如果颜色的第一位为1
	
	if((Color & (1 << 0)) != 0)
	{
		//将该像素设为1
		a1[elm] = a1[elm] | (~figure);
	}
	else
	{
		//否则将该像素设为0
		a1[elm] = a1[elm] & figure;
	}
	//以下同
	
	if((Color & (1 << 1)) != 0)
	{
		a2[elm] = a2[elm] | (~figure);
	}
	else
	{
		a2[elm] = a2[elm] & figure;
	}

	if((Color & (1 << 2)) != 0)
	{
		a3[elm] = a3[elm] | (~figure);
	}
	else
	{
		a3[elm] = a3[elm] & figure;
	}

	if((Color & (1 << 3)) != 0)
	{
		a4[elm] = a4[elm] | (~figure);
	}
	else
	{
		a4[elm] = a4[elm] & figure;
	}
	return 0;
}

int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C)
{
	int i,j;
	//setcolor(15); // 设置绘图颜色为白色
    for (i = 0; i < 8; i++) 
	{
        MR8_1Group(x,y+i,Color,STORAGE[C-32][i]);
    }
	return 0;
}

int  MZFS(unsigned int x,unsigned int y,unsigned char Color,unsigned char* S)
{
	int i,j;
	//setcolor(15); // 设置绘图颜色为白色
    for (i = 0; i < 80 && *S != '\0'; i++) 
	{
		for (j = 0; j < 8; j++) 
		{
        		MR8_1Group(x+8*i,y+j,Color,STORAGE[*S-32][j]);
		}
        S++;
      }
	return 0;
}


int  MZFI(unsigned int x,unsigned int y,unsigned char Color,int i)
{
	char S[16];
	itoa(i,S,10);
	return MZFS(x,y,Color,S);
}

