/*****************************************
Mimage.c
COPYRIGHT:  Zengmingjie
FUNCTION:   store basic graphics elements and render them
DATE:       2023/2/23-3/11(Debug and Reinforcement)
Available code lines:ZMJ-about900lines
******************************************/

#include <graphics.h>
#include <dos.h>
#include <string.h>
#include<stdio.h>
//#include<math.h>
#include"a1.h"
#include"a2.h"
#include"a3.h"
#include"a4.h"
#include"MZFK.h"
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define abs(x) ((x) > 0 ? (x) : (-x))
#include"mimage.h"

//此处为在2.23解决内存限制问题的制作人曾明杰
//现在将之前所有Render系列函数重写，命名为MR开始的函数，意为MemoryRender
//显存位置为ai.c，共4个源文件，此外的均需重置
//0228更新新函数，核心用户为需要大量渲染外围矢量图的D3ROOM.c：MROutLine，注意格式转换。
//0228份bug检修：MRLine中前置渲染函数并未return，浪费计算资源，留下数据溢出隐患。
//且上述定义min，max时并未添加括号，在for循环每轮判断中优先级错误并连续崩溃。目前上述define定义"函数"已添加括号避免后续优先级问题。
//0301将几乎所有形参加上了const限定，并增添绘制三角形的函数
//3.11增加阴影系列函数和调色板系列函数


;//不加会报declaration error,不理解
int MR()//从缓存绘制入显存，其中38400 = 640*480/8，memcpy真好用&&颜色面应该没写错，csdn里的
{
	//指向显存的指针
    const char far *videoBuffer = (char far *)0xA0000000L;

    //把颜色拆成4位bit，分4次写到显存里
	outportb(0x3c4,2);//好像是告诉硬件要向显存写入数据
	outportb(0x3c5,1 << 0);//蓝色面
	memcpy(videoBuffer, a1, 38400l);//把缓冲写到显存里,以下同

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 1);//绿色面
	memcpy(videoBuffer, a2, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 2);//红色面
	memcpy(videoBuffer, a3, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 3);//高亮面
	memcpy(videoBuffer, a4, 38400l);
	
	outportb(0x3c5,0xf);//恢复设置 ，0314添加，应可以避免重复检测
	return 0;
}


int ClrMR()//更新界面，本版本速度极快
{
	//清空缓冲，就是把缓冲全设为0x00，此处为将背景设置为0010，即绿色
	memset(a1, 0x00, 38400l);
	memset(a2, 0xff, 38400l);
	memset(a3, 0x00, 38400l);
	memset(a4, 0x00, 38400l);
	return 0;
}
int MRBk(const unsigned Color)//更新界面，本版本速度极快
{
	//清空缓冲，就是把缓冲设为Color
	if((Color & (1 << 0)) != 0)
	{
		memset(a1, 0xff, 38400l);//将所有像素设为1
	}
	else
	{
		memset(a1, 0x00, 38400l);//否则将所有像素设为0
	}
	//以下功能同上，仅颜色面不同
	if((Color & (1 << 1)) != 0)
	{
		memset(a2, 0xff, 38400l);
	}
	else
	{
		memset(a2, 0x00, 38400l);
	}
	if((Color & (1 << 2)) != 0)
	{
		memset(a3, 0xff, 38400l);
	}
	else
	{
		memset(a3, 0x00, 38400l);
	}
	if((Color & (1 << 3)) != 0)
	{
		memset(a4, 0xff, 38400l);
	}
	else
	{
		memset(a4, 0x00, 38400l);
	}
	return 0;
}

int MRPixel(const unsigned int x,const unsigned int y,const unsigned char Color)	//基础像素输出，下称其为像素版本
{	
	const long elm = x/8+y * 80L;//element order
	const int bite = x%8;
	char temp;
	if(x > 639U ||y > 479U)//多长以上建议使用L？
	{
		return 1;
	}
	temp = a1[elm];	
	//如果颜色的第一位为1
	if((Color & (1 << 0)) != 0)
	{
		//将该像素设为1
		temp = temp | (1 << (7 - bite));
	}
	else
	{
		//否则将该像素设为0
		temp = temp & (~(1 << (7 - bite)));
	}
	//将该像素放回a1数组
	a1[elm] = temp;
	//以下代码同上
	temp = a2[elm];	
	if((Color & (1 << 1)) != 0)
	{
		temp = temp | (1 << (7 - bite));
	}
	else
	{
		temp = temp & (~(1 << (7 - bite)));
	}
	a2[elm] = temp;

	temp = a3[elm];	
	if((Color & (1 << 2)) != 0)
	{
		temp = temp | (1 << (7 - bite));
	}
	else
	{
		temp = temp & (~(1 << (7 - bite)));
	}
	a3[elm] = temp;

	temp = a4[elm];	
	if((Color & (1 << 3)) != 0)
	{
		temp = temp | (1 << (7 - bite));
	}
	else
	{
		temp = temp & (~(1 << (7 - bite)));
	}
	a4[elm] = temp;

	return 0;
}

static int MR8_1Bar(const unsigned int x,const unsigned int y,const unsigned char Color)//速度较像素版更快，控制像素更多，推荐优先使用
{
	const long elm = x/8+y * 80L;//element order
	if(x > 639U ||y > 479U)//多长以上建议使用L？
	{
		return 1;
	}
	//如果颜色的第一位为1
	if((Color & (1 << 0)) != 0)
	{
		//将该像素设为1
		a1[elm] = 0xFF;
	}
	else
	{
		//否则将该像素设为0
		a1[elm] = 0x00;
	}
	//以下同上
	
	if((Color & (1 << 1)) != 0)
	{
		a2[elm] = 0xFF;
	}
	else
	{
		a2[elm] = 0x00;
	}

	if((Color & (1 << 2)) != 0)
	{
		a3[elm] = 0xFF;
	}
	else
	{
		a3[elm] = 0x00;
	}

	if((Color & (1 << 3)) != 0)
	{
		a4[elm] = 0xFF;
	}
	else
	{
		a4[elm] = 0x00;
	}

	return 0;
}

//此函数相对与像素版本有约8倍加速效果，鼓励使用本函数绘图
//0303mark 此函数已引发两次大规模渲染bug，就算是大面积绘图也建议经过Safe版本的检测
static int MRHorizonLine(const unsigned int x1,const unsigned int x2,const unsigned int y,const unsigned char Color)//x1<=x2
{
	unsigned int i;
	if(x2 < x1)
		return 1;//减少出现bug几率
	
	if(x1/8 == x2/8)
	{
		for(i = x1; i <= x2;i ++)
		{
			MRPixel(i,y,Color);
		}
		return 0;
	}
	for(i = x1;i< (x1&0xFFF8)+8;i++)
	{
		MRPixel(i,y,Color);
	}
	for(i = (x1&0xFFF8)+8;i< (x2&0xFFF8);i+=8)
	{
		MR8_1Bar(i,y,Color);//0303mark此处若需加速可使用memset
	}
	for(i = x2&0xFFF8;i<= x2;i++)
	{
		MRPixel(i,y,Color);
	}
	return 0;
}

int MRSafeHorizonLine(const int x1,const int x2,const int y,const char Color)//随意输入x1，x2，y不必担心越界（即为楼上的检测）
{
	if(y <=479 && y >= 0 && min(x1,x2) < 639 && max(x1,x2) >=0)
	{
		return MRHorizonLine(max(min(x1,x2),0),min(max(x1,x2),639),y,Color);
	}
	else
	{
		return -1;
	}
	
}

//请注意，相对于像素版本，此函数并无加速作用。与之对比，水平横线加速效果约为8倍。
int MRVerticalLine(const unsigned int x,const unsigned int y1,const unsigned int y2,const unsigned char Color)//y1<=y2
{
	unsigned int i;
	if(y1 > y2)
		return 1;
	for(i = max(y1,0);i<= min(y2,479);i++)
	{
		MRPixel(x,i,Color);
	}
	return 0;
}

//若需要使用粗垂直线或粗水平线，请使用Bar函数

int MRBar(const unsigned int x1,const unsigned int x2,const unsigned int y1,const unsigned int y2,const unsigned char Color)//y1<=y2
{
	unsigned int j,xmin,xmax,ymin,ymax;
	xmin = min(x1,x2);
	xmax = max(x1,x2);
	ymin = min(y1,y2);
	ymax = max(y1,y2);
	for(j = ymin;j<= ymax;j++)
	{
		MRSafeHorizonLine(xmin,xmax,j,Color);
	}
	return 0;
}

//请注意，相对于像素版本，此函数并无加速作用。与之对比，水平横线加速效果约为8倍。
int MRRect(const unsigned int x1,const unsigned int x2,const unsigned int y1,const unsigned int y2,const unsigned char Color)//y1<=y2
{
	unsigned int i,j,xmin,xmax,ymin,ymax;
	xmin = min(x1,x2);
	xmax = max(x1,x2);
	ymin = min(y1,y2);
	ymax = max(y1,y2);
	MRSafeHorizonLine(xmin,xmax,y1,Color);
	MRSafeHorizonLine(xmin,xmax,y2,Color);
	MRVerticalLine(x1,ymin,ymax,Color);
	MRVerticalLine(x2,ymin,ymax,Color);
	return 0;
}

//此函数在0303更新为Bresenham算法，不推荐用于3D显示，因为仅Pixel和8_1Bar处有检测，速度较慢甚至可能出bug，建议用于屏幕内绘图。
int MRLine(const int x1,const int y1,const int x2,const int y2,const unsigned char Color)
{
	int i;
	int dx = abs((x2 - x1)), dy = abs((y2 - y1));
	if(x1 == x2)//画竖直线
	{
		return MRVerticalLine(x1,min(y1,y2),max(y1,y2),Color);
	}
	if(y1 == y2)//画水平线
	{
		return MRSafeHorizonLine(x1,x2,y1,Color);
	}
	if(dx == dy)//画dx与dy相等的斜线
	{
		if(x1 < x2 && y1 < y2)
		{
			for(i = 0;i<=dx;i++)
				MRPixel(x1+i,y1+i,Color);
		}
		else if(x1 < x2 && y1 > y2)
		{
			for(i = 0;i<=dx;i++)
				MRPixel(x1+i,y1-i,Color);
		}
		else if(x1 > x2 && y1 < y2)
		{
			for(i = 0;i<=dx;i++)
				MRPixel(x2+i,y2-i,Color);
		}
		else
		{
			for(i = 0;i<=dx;i++)
				MRPixel(x2+i,y2+i,Color);
		}
	}
	else if(dx > dy)//调用对应的bresenham算法函数画斜线
	{
		MRBresenHamLineX(x1,y1,x2,y2,Color);
	}
	else
	{
		MRBresenHamLineY(x1,y1,x2,y2,Color);
	}
		
	return 0;
}

int MRBresenHamLineX(const int x1,const int y1,int x2,const int y2,const char Color)//此函数在0303更新为Bresenham算法,此处斜率绝对值小于1
{
	int dx = abs((x2 - x1)), dy = abs((y2 - y1));
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x,y,operator;
	//determine which endpoint to use as start position;
	if(x1>x2)
	{
		x = x2;
		y = y2;
		x2 = x1;
		if(y1>y2)
			operator = 0;
		else
			operator = 1;
	}
	else
	{
		x = x1;
		y = y1;
		if(y1<y2)
			operator = 0;
		else
			operator = 1;
	}
	MRPixel(x,y,Color);
	if(operator == 0)
	{
	while(x < x2)
		{
			x++;
			if(p < 0)
				p += twoDy;
			else
			{
				y ++;
				p += twoDyMinusDx;
			}
			MRPixel(x,y,Color);
		}
	}
	else
	{
	while(x < x2)
		{
			x++;
			if(p < 0)
				p += twoDy;
			else
			{
				y --;
				p += twoDyMinusDx;
			}
			MRPixel(x,y,Color);
		}
	}
	
	return 0;
}

int MRBresenHamLineY(const int x1,const int y1,const int x2,int y2,const unsigned char Color)//此函数在0303更新为Bresenham算法,此处斜率绝对值大于1
{
	int dx = abs((x2 - x1)), dy = abs((y2 - y1));
	int p = 2 * dx - dy;
	int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
	int x,y,operator;
	//determine which endpoint to use as start position;
	if(y1>y2)
	{
		x = x2;
		y = y2;
		y2 = y1;
		if(x1>x2)
			operator = 0;
		else
			operator = 1;
	}
	else
	{
		x = x1;
		y = y1;	
		if(x1<x2)
			operator = 0;
		else
			operator = 1;
	}
	MRPixel(x,y,Color);
	if(operator == 0)
	{
		while(y < y2)
		{
			y++;
			if(p < 0)
				p += twoDx;
			else
			{
				x ++;
				p += twoDxMinusDy;
			}
			MRPixel(x,y,Color);
		}
	}
	else
	{
		while(y < y2)
		{
			y++;
			if(p < 0)
				p += twoDx;
			else
			{
				x --;
				p += twoDxMinusDy;
			}
			MRPixel(x,y,Color);
		}
	}
	return 0;
}

int MROutLine(const int x1,const int y1,const int x2,const int y2,const unsigned char Color)
{
	int i,j,w,h;
	double step;
	if(x1 > x2)
	{
		return MROutLine(x2,y2,x1,y1,Color);
	}
	if(y1 == y2)
	{
		if(y1>=0 && y1 < 480)
			{
				return MRSafeHorizonLine(x1,x2,y1,Color);
			}
		else
			{
				return 1;
			}
	}
//以下需参考BPix222编写斜线函数，暂时来说仅需要1像素宽版本
//此后w>=0,h!=0
	w = x2-x1;
	h = y2-y1;

	if(h > 0)
	{
		if(w > h)
		{
			step = h/(double)w;
			for(i = max(0,-x1);i<=min(w,639-x1);i++)
			{
				MRPixel(x1+i,y1+(unsigned int)(i*step+0.5),Color);
			}
		}

		else
		{
			step = w/(double)h;
			for(j = max(0,-y1);j<=min(h,479-y1);j++)
			{
				MRPixel(x1+(unsigned int)(j*step+0.5),y1+j,Color);
			}
		}
	}
	else
	{
		if(w > -h)
		{
			step = (-h)/(double)w;
			for(i = max(0,-x1);i<=min(w,639-x1);i++)
			{
				MRPixel(x1+i,y1-(unsigned int)(i*step+0.5),Color);
			}
		}
		else
		{
			step = w/(double)(-h);
			for(j = max(0,y1-479);j<=min(-h,y1);j++)
			{
				MRPixel(x1+(unsigned int)(j*step+0.5),y1-j,Color);
			}
		}
	}
	
	return 0;
	
}

int MRHorizonTriangle(const int x1,const int y1,const int x2,const int x3,const int y2,const unsigned char Color,const char type)//x2<=x3含检测
{

	int i,j,w1,w2,h;
	static double step1,step2;
	
	if(x2 > x3)
	{
		return MRHorizonTriangle(x1,y1,x3,x2,y2,Color,type);
	}//以下x2<=x3
	
	if(y1 == y2)
	{
		return MRSafeHorizonLine(min(min(x1,x2),x3),max(max(x1,x2),x3),y1,Color);
	}
	if(x2 == x3)
	{
		return MROutLine(x1,y1,x2,y2,Color);
	}
//此后h!=0

	w1 = x2-x1;
	w2 = x3-x1;
	h = y2-y1;
	if(type != 2)
	{
		if(h > 0)
		{
			step1 = (double)w1/(double)h;
			step2 = (double)w2/(double)h;
			
			for(j = max(0,-y1);j<=min(479-y1,h);j++)
			{

				MRHorizonShadowLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1+j,Color,type);
			}
		}
		else
		{
			step1 = (double)w1/(double)(-h);
			step2 = (double)w2/(double)(-h);
			
			for(j = max(0,y1-479);j<=min(-h,y1);j++)
			{
				MRHorizonShadowLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1-j,Color,type);
			}
		}
	}
	else
	{
		if(h > 0)
		{
			step1 = (double)w1/(double)h;
			step2 = (double)w2/(double)h;
			
			for(j = max(0,-y1);j<=min(479-y1,h);j++)
			{
				MRSafeHorizonLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1+j,Color);
			}
		}
		else
		{
			step1 = (double)w1/(double)(-h);
			step2 = (double)w2/(double)(-h);
			
			for(j = max(0,y1-479);j<=min(-h,y1);j++)
			{
				MRSafeHorizonLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1-j,Color);
			}
			
		}
	}
	return 0;
}
	
int MRTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color)//仅含检测
{
	if(y1 == y2)
	{
		return MRHorizonTriangle(x3,y3,x1,x2,y1,Color,2);
	}
	if(y2 == y3)
	{
		return MRHorizonTriangle(x1,y1,x2,x3,y2,Color,2);
	}
	if(y1 == y3)
	{
		return MRHorizonTriangle(x2,y2,x1,x3,y1,Color,2);
	}
	if(y1 > y2)
	{
		return MRTriangle(x2,y2,x1,y1,x3,y3,Color);
	}
	//以下y1<y2
	if(y2 < y3)
	{
		return MRRealTriangle(x1,y1,x2,y2,x3,y3,Color,2);
	}
	//以下y1<y2,y2>y3
	if(y1 < y3)
	{
		return MRRealTriangle(x1,y1,x3,y3,x2,y2,Color,2);
	}
	else
	{
		return MRRealTriangle(x3,y3,x1,y1,x2,y2,Color,2);
	}
	return -1;
}

int MRShadowTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type)//仅含检测
{
	if(y1 == y2)
	{
		return MRHorizonTriangle(x3,y3,x1,x2,y1,Color,type);
	}
	if(y2 == y3)
	{
		return MRHorizonTriangle(x1,y1,x2,x3,y2,Color,type);
	}
	if(y1 == y3)
	{
		return MRHorizonTriangle(x2,y2,x1,x3,y1,Color,type);
	}
	if(y1 > y2)
	{
		return MRShadowTriangle(x2,y2,x1,y1,x3,y3,Color,type);
	}
	//以下y1<y2
	if(y2 < y3)
	{
		return MRRealTriangle(x1,y1,x2,y2,x3,y3,Color,type);
	}
	//以下y1<y2,y2>y3
	if(y1 < y3)
	{
		return MRRealTriangle(x1,y1,x3,y3,x2,y2,Color,type);
	}
	else
	{
		return MRRealTriangle(x3,y3,x1,y1,x2,y2,Color,type);
	}
	return -1;
}

static int MRRealTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type)//y1<y2<y3不含检测,使用safeLine不必担心越界,type 2为实心，01为虚影
{
	int j;
	static double step1,step2,step3;//delta;//delta用于判断中间的点在左侧还是右侧

	const int w1 = (int)x2-(int)x1;
	const int w2 = (int)x3-(int)x1;
	const int w3 = (int)x3-(int)x2;
	const int h1 = (int)y2-(int)y1;
	const int h2 = (int)y3-(int)y1;
	const int h3 = (int)y3-(int)y2;//h均正
	step1 = w1/(double)h1;
	step2 = w2/(double)h2;
	step3 = w3/(double)h3;
	if(type != 2)
	{
		if(step1 > step2)//中间点在右侧
		{
			for(j = max(0,-y1);j<=min(479-y1,h1);j++)
			{
				MRHorizonShadowLine(x1+(int)(j*step2+0.5),x1+(int)(j*step1+0.5),y1+j,Color,type);
			}
			for(j = max(h1,-y1);j<=min(479-y1,h2);j++)
			{
				MRHorizonShadowLine(x1+(int)(j*step2+0.5),x2+(int)((j-h1)*step3+0.5),y1+j,Color,type);
			}
		}
		else
		{
			for(j = max(0,-y1);j<=min(479-y1,h1);j++)
			{
				MRHorizonShadowLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1+j,Color,type);
			}
			for(j = max(h1,-y1);j<=min(479-y1,h2);j++)
			{
				MRHorizonShadowLine(x2+(int)((j-h1)*step3+0.5),x1+(int)(j*step2+0.5),y1+j,Color,type);
			}
		}	
	}
	else
	{
		if(step1 > step2)//中间点在右侧
		{
			for(j = max(0,-y1);j<=min(479-y1,h1);j++)
			{
				MRSafeHorizonLine(x1+(int)(j*step2+0.5),x1+(int)(j*step1+0.5),y1+j,Color);
			}
			for(j = max(h1,-y1);j<=min(479-y1,h2);j++)
			{
				MRSafeHorizonLine(x1+(int)(j*step2+0.5),x2+(int)((j-h1)*step3+0.5),y1+j,Color);
			}
		}
		else
		{
			for(j = max(0,-y1);j<=min(479-y1,h1);j++)
			{
				MRSafeHorizonLine(x1+(int)(j*step1+0.5),x1+(int)(j*step2+0.5),y1+j,Color);
			}
			for(j = max(h1,-y1);j<=min(479-y1,h2);j++)
			{
				MRSafeHorizonLine(x2+(int)((j-h1)*step3+0.5),x1+(int)(j*step2+0.5),y1+j,Color);
			}
		}	
	}
	return 0;
}

int MRdbm(const int x,const int y,const char *dbm)	//输入dbmp的路径,在(x,y)输出图片(x需为8的倍数)
{					
	int ImageW,ImageH,n,i,j;
	long hangsize,per;
	FILE * fdbm;
	
	if((fdbm=fopen(dbm,"rb"))==NULL)
	{
		printf("%s",dbm);
		getchar();
		printf("Open Error!");
		return 1;
	}
	fread(&ImageW,sizeof(int),1,fdbm);
	fread(&ImageH,sizeof(int),1,fdbm);
	hangsize=(ImageW-1)/8;
	per = x/8+y*80;
	if((ImageH+y)>480)	ImageH=480-y; 	//VGAHI  640*480 
	for(i=0;i<ImageH;i++)//
	{
		//for(n=8;n>=1;n>>=1)	//从第三位颜色平面写到第0
		fread(a4+per,hangsize,1,fdbm);
		fseek(fdbm,1,SEEK_CUR);
		fread(a3+per,hangsize,1,fdbm);
		fseek(fdbm,1,SEEK_CUR);
		fread(a2+per,hangsize,1,fdbm);
		fseek(fdbm,1,SEEK_CUR);
		fread(a1+per,hangsize,1,fdbm);
		fseek(fdbm,1,SEEK_CUR);
	   //	fseek(fdbm,hangsize*2,SEEK_CUR);
		per+=80;
	}
	fclose(fdbm);
	return 0;
}

static int MR8_1Shadow(const unsigned int x,const unsigned int y,const unsigned char Color,const char ShadowType)//shadowtype = 0 时为每四个两个，为1时为每四格一个
{
	const long elm = x/8+y * 80L;//element order
	char figure;
	if(ShadowType)
	{
		if(y%2)
		{
			return 1;
		}
		figure = 0x55;
	}
	else
	{
		figure = y%2? 0X55 : 0xAA;
	}
	if(x > 639U ||y > 479U)//多长以上建议使用L？
	{
		return 1;
	}
	//printf("p");	
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
	//以下同上
	
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

static int MRHorizonShadowLine(const int x1,const int x2,const int y,const unsigned char Color,const char ShadowType)//随意输入x1，x2，y不必担心越界（即为楼下的检测）
{
	if(y <=479 && y >= 0 && min(x1,x2) < 639 && max(x1,x2) >=0)
	{
		return MRRealHorizonShadowLine(max(min(x1,x2),0),min(max(x1,x2),639),y,Color,ShadowType);
	}
	else
	{
		return -1;
	}
}

static int MRRealHorizonShadowLine(const int x1,const int x2,const int y,const unsigned char Color,const char ShadowType)//x1<=x2
{
	unsigned int i;
	if(x2 < x1)
		return 1;//减少出现bug几率
	if(ShadowType == 1 && y%2 == 1)
	{
		return 1;
	}
	if(x1/8 == x2/8)
	{
		for(i = x1; i <= x2;i ++)
		{
			if((ShadowType + y+i)%2 == 1)
			{
				MRPixel(i,y,Color);
			}
		}
		return 0;
	}
	for(i = x1;i< (x1&0xFFF8)+8;i++)
	{
		if((ShadowType + y+i)%2 == 1)
		{
			MRPixel(i,y,Color);
		}
	}
	for(i = (x1&0xFFF8)+8;i< (x2&0xFFF8);i+=8)
	{
		MR8_1Shadow(i,y,Color,ShadowType);//0303mark此处若需加速可使用memset
	}
	for(i = x2&0xFFF8;i<= x2;i++)
	{
		if((ShadowType + y+i)%2 == 1)
		{
			MRPixel(i,y,Color);
		}
	}
	return 0;
}

//此函数为0311曾明杰引用古典贴图库image.c的函数，不计入代码量
static void set_color(int color_no,int red,int green,int blue)	//指定颜色编号，修改其对应的rgb值 
{
	if(color_no<16)
	{
		_AX=0x1007;	//选择10H显示中断中的第7号功能
		_BL=color_no;
		geninterrupt(0x10);
		color_no=_BH; 
	}
	else
		color_no = 0xff;	//将屏幕边缘色指向调色板255 
		
	//修改调色板寄存器 
	_DH=red;
	_CH=green;
	_CL=blue;
	_BX=color_no;
	_AX=0x1010;
	geninterrupt(0x10);
	
	//处理屏幕边缘颜色 
	if(color_no==0xff)
	{
		_BH=0xff;
		_AX=0x1001;
		geninterrupt(0x10);
	} 
}

int SetColor(struct SetOfColor S)
{
	int i;
	for(i = 0; i < 16; i ++)
	{
		set_color(i,S.Red[i],S.Green[i],S.Blue[i]);
	}
	return 0;
}