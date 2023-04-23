
#include"mimage.h"
#include"d3room.h"
#include"MZFK.h"
#include"MyMath.h"
//#include<stdlib.h>

/*****************************************
D3ROOM.c
COPYRIGHT:  Zengmingjie
FUNCTION:   Making3DModels and transfer into different view port
DATE:       2023/2/28-4/1(Debug and Reinforcement)
Available code lines:ZMJ-about680lines
******************************************/
;//不加会报declaration error,不理解

static struct D3FullVectorMap OriMap;//OutputMap;

//利用给出的坐标R,θ,φ计算出转换矩阵（视角仍需在合适方向上），
//即P = Pfai · Pxita，Pfai为围绕竖直轴旋转的变换矩阵，Pxita为沿xy方向上的俯仰变换（也是旋转变换）矩阵
//在电路理论课上推导出来的仿射坐标转换公式
//0303mark下一步增加平移矩阵（可能矩阵需要升维成4阶），以及透视变换矩阵，均仅需点乘，亦可手算出来后在此处填入公式
int GenerateTransformMatrix(struct TransformMatrix *pTM,int Xita, int Fai, double Radius)//这个函数生成的是一个先旋转再俯仰的时候变换的矩阵
{
	pTM->P[0][0] = Radius*COS(Xita)*COS(Fai);
	pTM->P[0][1] = Radius*SIN(Xita);
	pTM->P[0][2] = -(Radius*COS(Xita)*SIN(Fai));
	pTM->P[0][3] = 0;

	pTM->P[1][0] = -(Radius*SIN(Xita)*COS(Fai));
	pTM->P[1][1] = Radius*COS(Xita);
	pTM->P[1][2] = Radius*SIN(Xita)*SIN(Fai);
	pTM->P[1][3] = 0;

	pTM->P[2][0] = Radius*SIN(Fai);
	pTM->P[2][1] = 0;
	pTM->P[2][2] = Radius*COS(Fai);
	pTM->P[2][3] = 0;

	pTM->P[3][3] = 0;
	pTM->P[3][3] = 0;
	pTM->P[3][3] = 0;
	pTM->P[3][3] = 1;

	return 0;
}

int GenerateAnotherTransformMatrix(struct TransformMatrix *pTM,int Xita, int Fai)//这个函数生成的是一个先俯仰再旋转的时候变换的矩阵
{
	pTM->P[0][0] = COS(Fai)*COS(Xita);
	pTM->P[0][1] = (COS(Fai)*SIN(Xita));
	pTM->P[0][2] = -SIN(Fai);
	pTM->P[0][3] = 0;

	pTM->P[1][0] = -SIN(Xita);
	pTM->P[1][1] = COS(Xita);
	pTM->P[1][2] = 0;
	pTM->P[1][3] = 0;

	pTM->P[2][0] = COS(Xita)*SIN(Fai);
	pTM->P[2][1] = SIN(Xita)*SIN(Fai);
	pTM->P[2][2] = COS(Fai);
	pTM->P[2][3] = 0;

	pTM->P[3][3] = 0;
	pTM->P[3][3] = 0;
	pTM->P[3][3] = 0;
	pTM->P[3][3] = 1;

	return 0;
}

struct D3DOT DotTransfer(const struct TransformMatrix TM,const struct D3DOT D,double Perspective)//return TM · D
{
	static struct D3DOT result;
	result.x = TM.P[0][0]*D.x+TM.P[0][1]*D.y+TM.P[0][2]*D.z+TM.P[0][3]*1;
	result.y = TM.P[1][0]*D.x+TM.P[1][1]*D.y+TM.P[1][2]*D.z+TM.P[1][3]*1;
	result.z = TM.P[2][0]*D.x+TM.P[2][1]*D.y+TM.P[2][2]*D.z+TM.P[2][3]*1;
	//此处为透视变换
	//result.x = -result.x*Perspective / (result.z - Perspective);
	result.y = -result.y*Perspective / (result.x - Perspective);
	result.z = -result.z*Perspective / (result.x - Perspective);
	//第四维一般提供的是常数
	return result;
}

struct D3DOT DotTransferWithoutPers(const struct TransformMatrix TM,const struct D3DOT D)//return TM · D
{
	static struct D3DOT result;
	result.x = TM.P[0][0]*D.x+TM.P[0][1]*D.y+TM.P[0][2]*D.z+TM.P[0][3]*1;
	result.y = TM.P[1][0]*D.x+TM.P[1][1]*D.y+TM.P[1][2]*D.z+TM.P[1][3]*1;
	result.z = TM.P[2][0]*D.x+TM.P[2][1]*D.y+TM.P[2][2]*D.z+TM.P[2][3]*1;
	//第四维一般提供的是常数
	return result;
}

int D3FullVectorMapDotTransform(struct TransformMatrix TM,double Perspective)//此处pResult记得开好数组
{
	int i;
	for(i = 0; i < OriMap.DotNum;i++)
	{
		OriMap.TredDOTS[i] = DotTransfer(TM,OriMap.DOTS[i],Perspective);
	}
	return 0;
}

int CreateShadow(int TriangleOrder, float X0, float Z0, int FloorHeight)
{
	int SOrder = OriMap.ShadowTriangleNum;
	int DOrder = OriMap.DotNum;
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][0]], X0, Z0,
			  &(OriMap.DOTS[DOrder+0]) , FloorHeight);
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][1]], X0, Z0,
			  &(OriMap.DOTS[DOrder+1]) , FloorHeight);
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][2]], X0, Z0,
			  &(OriMap.DOTS[DOrder+2]) , FloorHeight);
			  
	OriMap.ShadowTriangle[SOrder][0] = DOrder+0;
	OriMap.ShadowTriangle[SOrder][1] = DOrder+1;
	OriMap.ShadowTriangle[SOrder][2] = DOrder+2;

	OriMap.ShadowTriangleNum ++;
	OriMap.DotNum += 3;
	return 0;
}

//请注意，由于使用同一个阴影数组，在循环中请一定要在CreateShadow后调用
int CreateBackShadow(int TriangleOrder, float X0, float Z0, int FloorHeight)
{
	int SOrder = OriMap.ShadowTriangleNum + OriMap.ShadowBackTriangleNum;
	int DOrder = OriMap.DotNum;
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][0]], X0, Z0,
			  &(OriMap.DOTS[DOrder+0]) , FloorHeight);
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][1]], X0, Z0,
			  &(OriMap.DOTS[DOrder+1]) , FloorHeight);
	DotShadow(OriMap.DOTS[OriMap.triangles[TriangleOrder][2]], X0, Z0,
			  &(OriMap.DOTS[DOrder+2]) , FloorHeight);
			  
	OriMap.ShadowTriangle[SOrder][0] = DOrder+0;
	OriMap.ShadowTriangle[SOrder][1] = DOrder+1;
	OriMap.ShadowTriangle[SOrder][2] = DOrder+2;

	OriMap.ShadowBackTriangleNum ++;
	OriMap.DotNum += 3;
	return 0;
}

int DotShadow(const struct D3DOT D, float X0, float Z0, struct D3DOT *result, int FloorHeight)//return TM · D
{
	static double Temp;
	Temp = FloorHeight - D.y;
	result->x = D.x + Temp * X0;
	result->y = FloorHeight;
	result->z = D.z + Temp * Z0;
	return 0;
}

int ShadowReset()
{
	OriMap.DotNum -= 3*OriMap.ShadowTriangleNum + 3* OriMap.ShadowBackTriangleNum;
	OriMap.ShadowTriangleNum = 0;
	OriMap.ShadowBackTriangleNum = 0;
	return 0;
}

int QueueReset()
{
	OriMap.TriangleQueuePos = 0;
	return 0;
}

int QueueLength()
{
	return OriMap.TriangleNum;
}

int push(unsigned int TriangleOrder)
{
	if(OriMap.TriangleQueuePos >= OriMap.TriangleNum)
	{
		printf("PUSHING_ERROR!");
		delay(2000);
		exit(1);
	}
	if(TriangleOrder >= OriMap.TriangleNum)
	{
		printf("%d %dPUSHING_Parameter_ERROR!",TriangleOrder,OriMap.TriangleNum);
		delay(2000);
		exit(1);
	}	
	OriMap.TriangleRenderQueue[OriMap.TriangleQueuePos] = TriangleOrder;
	OriMap.TriangleQueuePos ++;
	return 0;
}

int isTriangleSeen(int TriOrder)
{
	static int y1,y2,y3,z1,z2,z3;
	z1 = OriMap.TredDOTS[OriMap.triangles[TriOrder][0]].z;
	z2 = OriMap.TredDOTS[OriMap.triangles[TriOrder][1]].z;
	z3 = OriMap.TredDOTS[OriMap.triangles[TriOrder][2]].z;
	y1 = OriMap.TredDOTS[OriMap.triangles[TriOrder][0]].y;
	y2 = OriMap.TredDOTS[OriMap.triangles[TriOrder][1]].y;
	y3 = OriMap.TredDOTS[OriMap.triangles[TriOrder][2]].y;
	return (float)(z2-z1)*(float)(y3-y1) - (float)(y2-y1)*(float)(z3-z1)>0;
}

int drawD3FullVectorMap()
{
	static int i,y1,y2,y3,z1,z2,z3;
	if(OriMap.TriangleQueuePos != OriMap.TriangleNum)
	{
		printf("Order_ERROR!\n");
		printf("%d %d",OriMap.TriangleQueuePos,OriMap.TriangleNum);
		delay(2000);
		exit(1);
	}
	//画个地板
	for(i = 0; i < PRECUBE;i++)
	{
		z1 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][0]].z;
		z2 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][1]].z;
		z3 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][2]].z;
		y1 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][0]].y;
		y2 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][1]].y;
		y3 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][2]].y;
		if((float)(z2-z1)*(float)(y3-y1) - (float)(y2-y1)*(float)(z3-z1) > 0)
		{
			MRTriangle(z1+320,240-y1,z2+320,240-y2,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][0]);
			MROutLine(z1+320,240-y1,z2+320,240-y2,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][1]);
			MROutLine(z1+320,240-y1,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][2]);
			MROutLine(z2+320,240-y2,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][3]);
		}
	}
	//画几根电线
	for(i = 0; i < OriMap.LineNum;i++)
	{
		MROutLine(OriMap.TredDOTS[OriMap.lines[i][0]].z+320,240-OriMap.TredDOTS[OriMap.lines[i][0]].y,
				  OriMap.TredDOTS[OriMap.lines[i][1]].z+320,240-OriMap.TredDOTS[OriMap.lines[i][1]].y,
				  OriMap.lineColor[i]);
	}
	//下面可画阴影
	for(i = 0; i < OriMap.ShadowTriangleNum;i++)
	{
		z1 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][0]].z;
		z2 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][1]].z;
		z3 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][2]].z;
		y1 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][0]].y;
		y2 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][1]].y;
		y3 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][2]].y;
		//if((float)(z2-z1)*(float)(y3-y1) - (float)(y2-y1)*(float)(z3-z1) > 0)
		{
			MRShadowTriangle(z1+320,240-y1,z2+320,240-y2,z3+320,240-y3,0,OriMap.ShadowType);
		}
	}
	//下面可画三角形
	for(i = PRECUBE; i < OriMap.TriangleNum;i++)
	{
		z1 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][0]].z;
		z2 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][1]].z;
		z3 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][2]].z;
		y1 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][0]].y;
		y2 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][1]].y;
		y3 = OriMap.TredDOTS[OriMap.triangles[OriMap.TriangleRenderQueue[i]][2]].y;
		if((float)(z2-z1)*(float)(y3-y1) - (float)(y2-y1)*(float)(z3-z1) > 0)
		{
			MRTriangle(z1+320,240-y1,z2+320,240-y2,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][0]);
			MROutLine(z1+320,240-y1,z2+320,240-y2,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][1]);
			MROutLine(z1+320,240-y1,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][2]);
			MROutLine(z2+320,240-y2,z3+320,240-y3,OriMap.TriangleColor[OriMap.TriangleRenderQueue[i]][3]);
		}
	}
	
	for(i = OriMap.ShadowTriangleNum; i < OriMap.ShadowTriangleNum + OriMap.ShadowBackTriangleNum;i++)
	{
		z1 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][0]].z;
		z2 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][1]].z;
		z3 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][2]].z;
		y1 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][0]].y;
		y2 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][1]].y;
		y3 = OriMap.TredDOTS[OriMap.ShadowTriangle[i][2]].y;
		//if((float)(z2-z1)*(float)(y3-y1) - (float)(y2-y1)*(float)(z3-z1) > 0)
		{
			MRShadowTriangle(z1+320,240-y1,z2+320,240-y2,z3+320,240-y3,0,1);
		}
	}

	// MZFI(240,0,OriMap.DotNum < 600? 15 : 10,OriMap.DotNum);
	// MZFI(240,30,OriMap.LineNum < 500? 15 : 10,OriMap.LineNum);
	// MZFI(240,45,OriMap.WireNum < 200? 15 : 10,OriMap.WireNum);
	// MZFI(240,60,OriMap.TriangleNum < 400? 15 : 10,OriMap.TriangleNum);
	// MZFI(240,75,15,OriMap.TriangleQueuePos);
	// MZFI(240,90,OriMap.ShadowTriangleNum < 50? 15 : 10,OriMap.ShadowTriangleNum);
	// MZFI(240,105,15,OriMap.ShadowBackTriangleNum);
	// MZFI(300,0,15,sizeof(struct D3FullVectorMap));
	return 0;
}

int ClrOriMap()
{
	OriMap.DotNum = 0;
	OriMap.LineNum = 0;
	OriMap.WireNum = 0;
	OriMap.TriangleNum = 0; 
	OriMap.ShadowTriangleNum = 0;
	OriMap.TriangleQueuePos = 0;
	OriMap.ShadowBackTriangleNum = 0;
	OriMap.ShadowType = 0;
	return 0;
}

int DeleteLastCube()
{
	OriMap.DotNum -=8;
	OriMap.LineNum = 0;
	OriMap.TriangleNum -= 12;//12
	return 0;
}

int DeleteLastParallelogram()
{
	OriMap.DotNum -=4;
	OriMap.LineNum = 0;
	OriMap.TriangleNum -= 2;//12
	return 0;
}

int AddParallelogram(const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,const int y3,const int z3,unsigned int EdgeColor,unsigned int InnerColor)
{
	unsigned int DotOrder,TriangleOrder;
	
	DotOrder = OriMap.DotNum;
	TriangleOrder  = OriMap.TriangleNum;
	OriMap.DOTS[DotOrder + 0].x = x1;
	OriMap.DOTS[DotOrder + 0].y = y1;
	OriMap.DOTS[DotOrder + 0].z = z1;
	OriMap.DOTS[DotOrder + 1].x = x2;
	OriMap.DOTS[DotOrder + 1].y = y2;
	OriMap.DOTS[DotOrder + 1].z = z2;
	OriMap.DOTS[DotOrder + 2].x = x3;
	OriMap.DOTS[DotOrder + 2].y = y3;
	OriMap.DOTS[DotOrder + 2].z = z3;
	OriMap.DOTS[DotOrder + 3].x = x2+x3-x1;
	OriMap.DOTS[DotOrder + 3].y = y2+y3-y1;
	OriMap.DOTS[DotOrder + 3].z = z2+z3-z1;
	
	OriMap.triangles[TriangleOrder + 0][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + 0][1] = DotOrder + 1;
	OriMap.triangles[TriangleOrder + 0][2] = DotOrder + 2;
	OriMap.TriangleColor[TriangleOrder + 0][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 0][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 0][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 0][3] = InnerColor;
	OriMap.triangles[TriangleOrder + 1][0] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 1][1] = DotOrder + 1;
	OriMap.triangles[TriangleOrder + 1][2] = DotOrder + 3;
	OriMap.TriangleColor[TriangleOrder + 1][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 1][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 1][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 1][3] = EdgeColor;
	
	
	OriMap.DotNum += 4;
	OriMap.TriangleNum += 2;
	return 0;
}

int AddCube(const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,
		const int y3,const int z3,const int x4,const int y4,const int z4,unsigned int EdgeColor,unsigned int InnerColor)
{
	unsigned int DotOrder,TriangleOrder;
	
	DotOrder = OriMap.DotNum;
	TriangleOrder  = OriMap.TriangleNum;
	
	OriMap.DOTS[DotOrder + 0].x = x1;
	OriMap.DOTS[DotOrder + 0].y = y1;
	OriMap.DOTS[DotOrder + 0].z = z1;
	OriMap.DOTS[DotOrder + 1].x = x2;
	OriMap.DOTS[DotOrder + 1].y = y2;
	OriMap.DOTS[DotOrder + 1].z = z2;
	OriMap.DOTS[DotOrder + 2].x = x3;
	OriMap.DOTS[DotOrder + 2].y = y3;
	OriMap.DOTS[DotOrder + 2].z = z3;
	OriMap.DOTS[DotOrder + 3].x = x2+x3-x1;
	OriMap.DOTS[DotOrder + 3].y = y2+y3-y1;
	OriMap.DOTS[DotOrder + 3].z = z2+z3-z1;
	OriMap.DOTS[DotOrder + 4].x = x4;
	OriMap.DOTS[DotOrder + 4].y = y4;
	OriMap.DOTS[DotOrder + 4].z = z4;
	OriMap.DOTS[DotOrder + 5].x = x2+x4-x1;
	OriMap.DOTS[DotOrder + 5].y = y2+y4-y1;
	OriMap.DOTS[DotOrder + 5].z = z2+z4-z1;
	OriMap.DOTS[DotOrder + 6].x = x3+x4-x1;
	OriMap.DOTS[DotOrder + 6].y = y3+y4-y1;
	OriMap.DOTS[DotOrder + 6].z = z3+z4-z1;
	OriMap.DOTS[DotOrder + 7].x = x2+x3-x1+x4-x1;
	OriMap.DOTS[DotOrder + 7].y = y2+y3-y1+y4-y1;
	OriMap.DOTS[DotOrder + 7].z = z2+z3-z1+z4-z1;
	
	OriMap.triangles[TriangleOrder + 0][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + 0][1] = DotOrder + 1;
	OriMap.triangles[TriangleOrder + 0][2] = DotOrder + 2;
	OriMap.TriangleColor[TriangleOrder + 0][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 0][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 0][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 0][3] = InnerColor;
	OriMap.triangles[TriangleOrder + 1][0] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 1][1] = DotOrder + 1;
	OriMap.triangles[TriangleOrder + 1][2] = DotOrder + 3;
	OriMap.TriangleColor[TriangleOrder + 1][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 1][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 1][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 1][3] = EdgeColor;//顶上的矩形

	OriMap.triangles[TriangleOrder + 2][0] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 2][1] = DotOrder + 3;
	OriMap.triangles[TriangleOrder + 2][2] = DotOrder + 7;
	OriMap.TriangleColor[TriangleOrder + 2][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 2][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 2][2] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 2][3] = EdgeColor;
	OriMap.triangles[TriangleOrder + 3][0] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 3][1] = DotOrder + 7;
	OriMap.triangles[TriangleOrder + 3][2] = DotOrder + 6;
	OriMap.TriangleColor[TriangleOrder + 3][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 3][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 3][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 3][3] = EdgeColor;//右侧的矩形

	OriMap.triangles[TriangleOrder + 4][0] = DotOrder + 1;
	OriMap.triangles[TriangleOrder + 4][1] = DotOrder + 5;
	OriMap.triangles[TriangleOrder + 4][2] = DotOrder + 3;
	OriMap.TriangleColor[TriangleOrder + 4][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 4][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 4][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 4][3] = InnerColor;
	OriMap.triangles[TriangleOrder + 5][0] = DotOrder + 3;
	OriMap.triangles[TriangleOrder + 5][1] = DotOrder + 5;
	OriMap.triangles[TriangleOrder + 5][2] = DotOrder + 7;
	OriMap.TriangleColor[TriangleOrder + 5][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 5][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 5][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 5][3] = EdgeColor;//前侧的矩形

	OriMap.triangles[TriangleOrder + 6][0] = DotOrder + 4;
	OriMap.triangles[TriangleOrder + 6][1] = DotOrder + 6;
	OriMap.triangles[TriangleOrder + 6][2] = DotOrder + 5;
	OriMap.TriangleColor[TriangleOrder + 6][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 6][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 6][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 6][3] = InnerColor;
	OriMap.triangles[TriangleOrder + 7][0]= DotOrder + 5;
	OriMap.triangles[TriangleOrder + 7][1] = DotOrder + 6;
	OriMap.triangles[TriangleOrder + 7][2] = DotOrder + 7;
	OriMap.TriangleColor[TriangleOrder + 7][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 7][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 7][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 7][3] = EdgeColor;//底下的矩形


	OriMap.triangles[TriangleOrder + 8][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + 8][1] = DotOrder + 5;
	OriMap.triangles[TriangleOrder + 8][2] = DotOrder + 1;
	OriMap.TriangleColor[TriangleOrder + 8][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 8][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 8][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 8][3] = EdgeColor;
	OriMap.triangles[TriangleOrder + 9][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + 9][1] = DotOrder + 4;
	OriMap.triangles[TriangleOrder + 9][2] = DotOrder + 5;
	OriMap.TriangleColor[TriangleOrder + 9][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 9][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 9][2] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 9][3] = EdgeColor;//左侧的矩形

	OriMap.triangles[TriangleOrder + 10][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + 10][1] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 10][2] = DotOrder + 4;
	OriMap.TriangleColor[TriangleOrder + 10][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 10][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 10][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 10][3] = InnerColor;
	OriMap.triangles[TriangleOrder + 11][0] = DotOrder + 2;
	OriMap.triangles[TriangleOrder + 11][1] = DotOrder + 6;
	OriMap.triangles[TriangleOrder + 11][2] = DotOrder + 4;
	OriMap.TriangleColor[TriangleOrder + 11][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 11][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + 11][2] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + 11][3] = EdgeColor;//后侧的矩形
	
	
	OriMap.DotNum += 8;
	OriMap.TriangleNum += 12;
	return 0;
}

int AddCylinder(const int x1,const int y1,const int z1,const int height, const unsigned int EdgeNum, const int Radius,unsigned int EdgeColor,unsigned int InnerColor)
{
	unsigned int DotOrder,TriangleOrder;
	int i = 0;
	DotOrder = OriMap.DotNum;
	TriangleOrder  = OriMap.TriangleNum;
	if(EdgeNum > 30)
	{
		printf("Don't take so much edgeNum to this poor BC!");
		delay(2000);
		exit();
	}
	OriMap.DOTS[DotOrder + 0].x = x1;
	OriMap.DOTS[DotOrder + 0].y = y1;
	OriMap.DOTS[DotOrder + 0].z = z1;
	for(i = 1; i < EdgeNum+1;i ++)
	{
		OriMap.DOTS[DotOrder + i].x = x1 + Radius*COS(360.0/EdgeNum*(i-1));//360.0/EdgeNum*(i-1)360.0/EdgeNum*(i-1)
		OriMap.DOTS[DotOrder + i].y = y1;
		OriMap.DOTS[DotOrder + i].z = z1 + Radius*SIN(360.0/EdgeNum*(i-1));
	}
	OriMap.DOTS[DotOrder + EdgeNum + 1].x = x1;
	OriMap.DOTS[DotOrder + EdgeNum + 1].y = y1 + height;
	OriMap.DOTS[DotOrder + EdgeNum + 1].z = z1;
	for(i = EdgeNum + 2; i < 2 * EdgeNum+2;i ++)
	{
		OriMap.DOTS[DotOrder + i].x = x1 + Radius*COS(360.0/EdgeNum*(i-EdgeNum + 2));//360.0/EdgeNum*(i-EdgeNum + 2)
		OriMap.DOTS[DotOrder + i].y = y1 + height;
		OriMap.DOTS[DotOrder + i].z = z1 + Radius*SIN(360.0/EdgeNum*(i-EdgeNum + 2));
	}
	OriMap.DotNum += 2*EdgeNum + 2;
	for(i = 0; i < EdgeNum-1; i ++)
	{
		OriMap.triangles[TriangleOrder + i*4 + 0][0] = DotOrder + 0;
		OriMap.triangles[TriangleOrder + i*4 + 0][1] = DotOrder + i+1;
		OriMap.triangles[TriangleOrder + i*4 + 0][2] = DotOrder + i+1 + 1;
		OriMap.TriangleColor[TriangleOrder + i*4 + 0][0] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 0][1] = EdgeColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 0][2] = EdgeColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 0][3] = InnerColor;
		OriMap.triangles[TriangleOrder + i*4 + 1][0] = DotOrder + EdgeNum + 1;
		OriMap.triangles[TriangleOrder + i*4 + 1][1] = DotOrder + EdgeNum + i+1 + 2;
		OriMap.triangles[TriangleOrder + i*4 + 1][2] = DotOrder + EdgeNum + i+1 + 1;
		OriMap.TriangleColor[TriangleOrder + i*4 + 1][0] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 1][1] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 1][2] = EdgeColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 1][3] = EdgeColor;//顶上的矩形
		OriMap.triangles[TriangleOrder + i*4 + 2][0] = DotOrder + i+1;
		OriMap.triangles[TriangleOrder + i*4 + 2][1] = DotOrder + EdgeNum + i+1 + 1;
		OriMap.triangles[TriangleOrder + i*4 + 2][2] = DotOrder + EdgeNum + i+1 + 2;
		OriMap.TriangleColor[TriangleOrder + i*4 + 2][0] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 2][1] = EdgeColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 2][2] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 2][3] = EdgeColor;
		OriMap.triangles[TriangleOrder + i*4 + 3][0] = DotOrder + i+1;
		OriMap.triangles[TriangleOrder + i*4 + 3][1] = DotOrder + EdgeNum + i+1 + 2;
		OriMap.triangles[TriangleOrder + i*4 + 3][2] = DotOrder + i+1 + 1;
		OriMap.TriangleColor[TriangleOrder + i*4 + 3][0] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 3][1] = InnerColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 3][2] = EdgeColor;
		OriMap.TriangleColor[TriangleOrder + i*4 + 3][3] = EdgeColor;//右侧的矩形
	}
	i = EdgeNum-1;
	
	OriMap.triangles[TriangleOrder + i*4 + 0][0] = DotOrder + 0;
	OriMap.triangles[TriangleOrder + i*4 + 0][1] = DotOrder + i+1;
	OriMap.triangles[TriangleOrder + i*4 + 0][2] = DotOrder + i+1 + 1 - EdgeNum;
	OriMap.TriangleColor[TriangleOrder + i*4 + 0][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 0][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 0][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 0][3] = InnerColor;
	OriMap.triangles[TriangleOrder + i*4 + 1][0] = DotOrder + EdgeNum + 1;
	OriMap.triangles[TriangleOrder + i*4 + 1][1] = DotOrder + EdgeNum + i+1 + 2 - EdgeNum;
	OriMap.triangles[TriangleOrder + i*4 + 1][2] = DotOrder + EdgeNum + i+1 + 1;
	OriMap.TriangleColor[TriangleOrder + i*4 + 1][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 1][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 1][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 1][3] = EdgeColor;//顶上的矩形
	OriMap.triangles[TriangleOrder + i*4 + 2][0] = DotOrder + i+1;
	OriMap.triangles[TriangleOrder + i*4 + 2][1] = DotOrder + EdgeNum + i+1 + 1;
	OriMap.triangles[TriangleOrder + i*4 + 2][2] = DotOrder + EdgeNum + i+1 + 2 - EdgeNum;
	OriMap.TriangleColor[TriangleOrder + i*4 + 2][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 2][1] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 2][2] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 2][3] = EdgeColor;
	OriMap.triangles[TriangleOrder + i*4 + 3][0] = DotOrder + i+1;
	OriMap.triangles[TriangleOrder + i*4 + 3][1] = DotOrder + EdgeNum + i+1 + 2 - EdgeNum;
	OriMap.triangles[TriangleOrder + i*4 + 3][2] = DotOrder + i+1 + 1 - EdgeNum;
	OriMap.TriangleColor[TriangleOrder + i*4 + 3][0] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 3][1] = InnerColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 3][2] = EdgeColor;
	OriMap.TriangleColor[TriangleOrder + i*4 + 3][3] = EdgeColor;//右侧的矩形
	
	OriMap.TriangleNum += 4*EdgeNum;
	return 0;
	
}

int EditCube(const int BeginDotOrder, const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,
		const int y3,const int z3,const int x4,const int y4,const int z4)
{
	unsigned int DotOrder;//,TriangleOrder
	
	DotOrder = BeginDotOrder;
	//TriangleOrder  = OriMap.TriangleNum;
	
	OriMap.DOTS[DotOrder + 0].x = x1;
	OriMap.DOTS[DotOrder + 0].y = y1;
	OriMap.DOTS[DotOrder + 0].z = z1;
	OriMap.DOTS[DotOrder + 1].x = x2;
	OriMap.DOTS[DotOrder + 1].y = y2;
	OriMap.DOTS[DotOrder + 1].z = z2;
	OriMap.DOTS[DotOrder + 2].x = x3;
	OriMap.DOTS[DotOrder + 2].y = y3;
	OriMap.DOTS[DotOrder + 2].z = z3;
	OriMap.DOTS[DotOrder + 3].x = x2+x3-x1;
	OriMap.DOTS[DotOrder + 3].y = y2+y3-y1;
	OriMap.DOTS[DotOrder + 3].z = z2+z3-z1;
	OriMap.DOTS[DotOrder + 4].x = x4;
	OriMap.DOTS[DotOrder + 4].y = y4;
	OriMap.DOTS[DotOrder + 4].z = z4;
	OriMap.DOTS[DotOrder + 5].x = x2+x4-x1;
	OriMap.DOTS[DotOrder + 5].y = y2+y4-y1;
	OriMap.DOTS[DotOrder + 5].z = z2+z4-z1;
	OriMap.DOTS[DotOrder + 6].x = x3+x4-x1;
	OriMap.DOTS[DotOrder + 6].y = y3+y4-y1;
	OriMap.DOTS[DotOrder + 6].z = z3+z4-z1;
	OriMap.DOTS[DotOrder + 7].x = x2+x3-x1+x4-x1;
	OriMap.DOTS[DotOrder + 7].y = y2+y3-y1+y4-y1;
	OriMap.DOTS[DotOrder + 7].z = z2+z3-z1+z4-z1;
	return 0;
}

int D3MR()
{
	return MR();//仅做封装
}

//clrWires 为重置
//newWire 为设置（两点均更新）
//linkWire 为沿用上一个点进行设置
//mode 3 为更新颜色
int clrWires()
{
	//别清了关pageEmu的时候统一清完平常别生成
	return 0;
}

int newWire(const int x1,const int z1,const int x2,const int z2, int FloorHeight)
{
	OriMap.DOTS[OriMap.DotNum + 0].x = x1;
	OriMap.DOTS[OriMap.DotNum + 0].y = FloorHeight;
	OriMap.DOTS[OriMap.DotNum + 0].z = z1;
	OriMap.DOTS[OriMap.DotNum + 1].x = x2;
	OriMap.DOTS[OriMap.DotNum + 1].y = FloorHeight;
	OriMap.DOTS[OriMap.DotNum + 1].z = z2;
	OriMap.lines[OriMap.LineNum][0] = OriMap.DotNum+0;
	OriMap.lines[OriMap.LineNum][1] = OriMap.DotNum+1;
	
	OriMap.WireNum ++;
	OriMap.LineNum ++;
	OriMap.DotNum += 2;
	return 0;
}

int linkWires(const int x1,const int z1, int FloorHeight)
{
	OriMap.DOTS[OriMap.DotNum + 0].x = x1;
	OriMap.DOTS[OriMap.DotNum + 0].y = FloorHeight;
	OriMap.DOTS[OriMap.DotNum + 0].z = z1;
	OriMap.lines[OriMap.LineNum][0] = OriMap.DotNum-1;
	OriMap.lines[OriMap.LineNum][1] = OriMap.DotNum+0;
	OriMap.WireNum ++;
	OriMap.LineNum ++;
	OriMap.DotNum ++;
	return 0;
}

int ColorWires(int BlingStrength, int BlingNow)
{
	int i;
	const int BlingSize = 16;//此处改循环长度
	for(i = 0; i < OriMap.WireNum;i ++)
	{
		OriMap.lineColor[i] = ((BlingNow + i) % BlingSize < BlingStrength)?14:0;
	}
	return 0;
}

void ShadowType(int type)
{
	OriMap.ShadowType = type;
}

int ReturnIOrderX(int i)
{
	return OriMap.TredDOTS[i].x;
}

int ReturnIOrderY(int i)
{
	return OriMap.TredDOTS[i].y;
}

int ReturnIOrderZ(int i)
{
	return OriMap.TredDOTS[i].z;
}

