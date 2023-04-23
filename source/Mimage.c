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

//�˴�Ϊ��2.23����ڴ����������������������
//���ڽ�֮ǰ����Renderϵ�к�����д������ΪMR��ʼ�ĺ�������ΪMemoryRender
//�Դ�λ��Ϊai.c����4��Դ�ļ�������ľ�������
//0228�����º����������û�Ϊ��Ҫ������Ⱦ��Χʸ��ͼ��D3ROOM.c��MROutLine��ע���ʽת����
//0228��bug���ޣ�MRLine��ǰ����Ⱦ������δreturn���˷Ѽ�����Դ�������������������
//����������min��maxʱ��δ������ţ���forѭ��ÿ���ж������ȼ���������������Ŀǰ����define����"����"��������ű���������ȼ����⡣
//0301�����������βμ�����const�޶�����������������εĺ���
//3.11������Ӱϵ�к����͵�ɫ��ϵ�к���


;//���ӻᱨdeclaration error,�����
int MR()//�ӻ���������Դ棬����38400 = 640*480/8��memcpy�����&&��ɫ��Ӧ��ûд��csdn���
{
	//ָ���Դ��ָ��
    const char far *videoBuffer = (char far *)0xA0000000L;

    //����ɫ���4λbit����4��д���Դ���
	outportb(0x3c4,2);//�����Ǹ���Ӳ��Ҫ���Դ�д������
	outportb(0x3c5,1 << 0);//��ɫ��
	memcpy(videoBuffer, a1, 38400l);//�ѻ���д���Դ���,����ͬ

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 1);//��ɫ��
	memcpy(videoBuffer, a2, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 2);//��ɫ��
	memcpy(videoBuffer, a3, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 3);//������
	memcpy(videoBuffer, a4, 38400l);
	
	outportb(0x3c5,0xf);//�ָ����� ��0314��ӣ�Ӧ���Ա����ظ����
	return 0;
}


int ClrMR()//���½��棬���汾�ٶȼ���
{
	//��ջ��壬���ǰѻ���ȫ��Ϊ0x00���˴�Ϊ����������Ϊ0010������ɫ
	memset(a1, 0x00, 38400l);
	memset(a2, 0xff, 38400l);
	memset(a3, 0x00, 38400l);
	memset(a4, 0x00, 38400l);
	return 0;
}
int MRBk(const unsigned Color)//���½��棬���汾�ٶȼ���
{
	//��ջ��壬���ǰѻ�����ΪColor
	if((Color & (1 << 0)) != 0)
	{
		memset(a1, 0xff, 38400l);//������������Ϊ1
	}
	else
	{
		memset(a1, 0x00, 38400l);//��������������Ϊ0
	}
	//���¹���ͬ�ϣ�����ɫ�治ͬ
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

int MRPixel(const unsigned int x,const unsigned int y,const unsigned char Color)	//��������������³���Ϊ���ذ汾
{	
	const long elm = x/8+y * 80L;//element order
	const int bite = x%8;
	char temp;
	if(x > 639U ||y > 479U)//�೤���Ͻ���ʹ��L��
	{
		return 1;
	}
	temp = a1[elm];	
	//�����ɫ�ĵ�һλΪ1
	if((Color & (1 << 0)) != 0)
	{
		//����������Ϊ1
		temp = temp | (1 << (7 - bite));
	}
	else
	{
		//���򽫸�������Ϊ0
		temp = temp & (~(1 << (7 - bite)));
	}
	//�������طŻ�a1����
	a1[elm] = temp;
	//���´���ͬ��
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

static int MR8_1Bar(const unsigned int x,const unsigned int y,const unsigned char Color)//�ٶȽ����ذ���죬�������ظ��࣬�Ƽ�����ʹ��
{
	const long elm = x/8+y * 80L;//element order
	if(x > 639U ||y > 479U)//�೤���Ͻ���ʹ��L��
	{
		return 1;
	}
	//�����ɫ�ĵ�һλΪ1
	if((Color & (1 << 0)) != 0)
	{
		//����������Ϊ1
		a1[elm] = 0xFF;
	}
	else
	{
		//���򽫸�������Ϊ0
		a1[elm] = 0x00;
	}
	//����ͬ��
	
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

//�˺�����������ذ汾��Լ8������Ч��������ʹ�ñ�������ͼ
//0303mark �˺������������δ��ģ��Ⱦbug�������Ǵ������ͼҲ���龭��Safe�汾�ļ��
static int MRHorizonLine(const unsigned int x1,const unsigned int x2,const unsigned int y,const unsigned char Color)//x1<=x2
{
	unsigned int i;
	if(x2 < x1)
		return 1;//���ٳ���bug����
	
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
		MR8_1Bar(i,y,Color);//0303mark�˴�������ٿ�ʹ��memset
	}
	for(i = x2&0xFFF8;i<= x2;i++)
	{
		MRPixel(i,y,Color);
	}
	return 0;
}

int MRSafeHorizonLine(const int x1,const int x2,const int y,const char Color)//��������x1��x2��y���ص���Խ�磨��Ϊ¥�ϵļ�⣩
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

//��ע�⣬��������ذ汾���˺������޼������á���֮�Աȣ�ˮƽ���߼���Ч��ԼΪ8����
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

//����Ҫʹ�ôִ�ֱ�߻��ˮƽ�ߣ���ʹ��Bar����

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

//��ע�⣬��������ذ汾���˺������޼������á���֮�Աȣ�ˮƽ���߼���Ч��ԼΪ8����
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

//�˺�����0303����ΪBresenham�㷨�����Ƽ�����3D��ʾ����Ϊ��Pixel��8_1Bar���м�⣬�ٶȽ����������ܳ�bug������������Ļ�ڻ�ͼ��
int MRLine(const int x1,const int y1,const int x2,const int y2,const unsigned char Color)
{
	int i;
	int dx = abs((x2 - x1)), dy = abs((y2 - y1));
	if(x1 == x2)//����ֱ��
	{
		return MRVerticalLine(x1,min(y1,y2),max(y1,y2),Color);
	}
	if(y1 == y2)//��ˮƽ��
	{
		return MRSafeHorizonLine(x1,x2,y1,Color);
	}
	if(dx == dy)//��dx��dy��ȵ�б��
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
	else if(dx > dy)//���ö�Ӧ��bresenham�㷨������б��
	{
		MRBresenHamLineX(x1,y1,x2,y2,Color);
	}
	else
	{
		MRBresenHamLineY(x1,y1,x2,y2,Color);
	}
		
	return 0;
}

int MRBresenHamLineX(const int x1,const int y1,int x2,const int y2,const char Color)//�˺�����0303����ΪBresenham�㷨,�˴�б�ʾ���ֵС��1
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

int MRBresenHamLineY(const int x1,const int y1,const int x2,int y2,const unsigned char Color)//�˺�����0303����ΪBresenham�㷨,�˴�б�ʾ���ֵ����1
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
//������ο�BPix222��дб�ߺ�������ʱ��˵����Ҫ1���ؿ�汾
//�˺�w>=0,h!=0
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

int MRHorizonTriangle(const int x1,const int y1,const int x2,const int x3,const int y2,const unsigned char Color,const char type)//x2<=x3�����
{

	int i,j,w1,w2,h;
	static double step1,step2;
	
	if(x2 > x3)
	{
		return MRHorizonTriangle(x1,y1,x3,x2,y2,Color,type);
	}//����x2<=x3
	
	if(y1 == y2)
	{
		return MRSafeHorizonLine(min(min(x1,x2),x3),max(max(x1,x2),x3),y1,Color);
	}
	if(x2 == x3)
	{
		return MROutLine(x1,y1,x2,y2,Color);
	}
//�˺�h!=0

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
	
int MRTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color)//�������
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
	//����y1<y2
	if(y2 < y3)
	{
		return MRRealTriangle(x1,y1,x2,y2,x3,y3,Color,2);
	}
	//����y1<y2,y2>y3
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

int MRShadowTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type)//�������
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
	//����y1<y2
	if(y2 < y3)
	{
		return MRRealTriangle(x1,y1,x2,y2,x3,y3,Color,type);
	}
	//����y1<y2,y2>y3
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

static int MRRealTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type)//y1<y2<y3�������,ʹ��safeLine���ص���Խ��,type 2Ϊʵ�ģ�01Ϊ��Ӱ
{
	int j;
	static double step1,step2,step3;//delta;//delta�����ж��м�ĵ�����໹���Ҳ�

	const int w1 = (int)x2-(int)x1;
	const int w2 = (int)x3-(int)x1;
	const int w3 = (int)x3-(int)x2;
	const int h1 = (int)y2-(int)y1;
	const int h2 = (int)y3-(int)y1;
	const int h3 = (int)y3-(int)y2;//h����
	step1 = w1/(double)h1;
	step2 = w2/(double)h2;
	step3 = w3/(double)h3;
	if(type != 2)
	{
		if(step1 > step2)//�м�����Ҳ�
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
		if(step1 > step2)//�м�����Ҳ�
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

int MRdbm(const int x,const int y,const char *dbm)	//����dbmp��·��,��(x,y)���ͼƬ(x��Ϊ8�ı���)
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
		//for(n=8;n>=1;n>>=1)	//�ӵ���λ��ɫƽ��д����0
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

static int MR8_1Shadow(const unsigned int x,const unsigned int y,const unsigned char Color,const char ShadowType)//shadowtype = 0 ʱΪÿ�ĸ�������Ϊ1ʱΪÿ�ĸ�һ��
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
	if(x > 639U ||y > 479U)//�೤���Ͻ���ʹ��L��
	{
		return 1;
	}
	//printf("p");	
	//�����ɫ�ĵ�һλΪ1
	if((Color & (1 << 0)) != 0)
	{
		//����������Ϊ1
		a1[elm] = a1[elm] | (~figure);
	}
	else
	{
		//���򽫸�������Ϊ0
		a1[elm] = a1[elm] & figure;
	}
	//����ͬ��
	
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

static int MRHorizonShadowLine(const int x1,const int x2,const int y,const unsigned char Color,const char ShadowType)//��������x1��x2��y���ص���Խ�磨��Ϊ¥�µļ�⣩
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
		return 1;//���ٳ���bug����
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
		MR8_1Shadow(i,y,Color,ShadowType);//0303mark�˴�������ٿ�ʹ��memset
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

//�˺���Ϊ0311���������ùŵ���ͼ��image.c�ĺ����������������
static void set_color(int color_no,int red,int green,int blue)	//ָ����ɫ��ţ��޸����Ӧ��rgbֵ 
{
	if(color_no<16)
	{
		_AX=0x1007;	//ѡ��10H��ʾ�ж��еĵ�7�Ź���
		_BL=color_no;
		geninterrupt(0x10);
		color_no=_BH; 
	}
	else
		color_no = 0xff;	//����Ļ��Եɫָ���ɫ��255 
		
	//�޸ĵ�ɫ��Ĵ��� 
	_DH=red;
	_CH=green;
	_CL=blue;
	_BX=color_no;
	_AX=0x1010;
	geninterrupt(0x10);
	
	//������Ļ��Ե��ɫ 
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