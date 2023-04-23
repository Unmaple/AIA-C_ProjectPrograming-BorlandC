#ifndef D3ROOM
#define D3ROOM

#define PRECUBE 14
#define PRECUBEDOT 12
//#include"mimage.h"

;

struct D3DOT
{
	int x;
	int y;
	int z;	
};

struct D3FullVectorMap//此处可以考虑使用链表，以数组形式对矢量图输出方要求太高
{
	unsigned int DotNum;
	unsigned int LineNum;
	unsigned int TriangleNum;
	unsigned int TriangleQueuePos;
	unsigned int ShadowTriangleNum;
	unsigned int ShadowBackTriangleNum;
	unsigned int WireNum;
	unsigned int ShadowType;
	
	struct D3DOT DOTS[700];
	struct D3DOT TredDOTS[700];
	
	unsigned int lines[500][2];
	unsigned char lineColor[500];
	
	unsigned int triangles[500][3];
	
	unsigned char TriangleColor[500][4];//0为三角形自己的颜色，1为线01，2为线02，3为线12
	unsigned int TriangleRenderQueue[500];
	
	unsigned int ShadowTriangle[80][3];//点数据一起存DOTS里
	
	
	
};

struct TransformMatrix
{
	double P[4][4];

};


//double SIN(int Xita);
//double COS(int Xita);
int GenerateTransformMatrix(struct TransformMatrix *pTM,int Xita, int Fai, double Radius);//利用给出的坐标R,θ,φ计算出转换矩阵（视角仍需在合适方向上）
int GenerateAnotherTransformMatrix(struct TransformMatrix *pTM,int Xita, int Fai);//这个函数生成的是一个先俯仰再旋转的时候变换的矩阵
struct D3DOT DotTransfer(struct TransformMatrix TM,struct D3DOT D,double Perspective);//return TM · D
struct D3DOT DotTransferWithoutPers(const struct TransformMatrix TM,const struct D3DOT D);
//int D3VectorMapTransfer(struct TransformMatrix TM,double Perspective);//此处pResult记得开好数组
int D3FullVectorMapDotTransform(struct TransformMatrix TM,double Perspective);//此处pResult记得开好数组
int CreateShadow(int TriangleOrder,float X0, float Z0, int FloorHeight);
int DotShadow(const struct D3DOT D, float X0, float Z0, struct D3DOT *result, int FloorHeight);
//int D3FullVectorMapOthersTransform();
//int drawD3VectorMap();
int QueueReset();
int QueueLength();
int push(unsigned int TriangleOrder);
int isTriangleSeen(int TriOrder);
int drawD3FullVectorMap();
int ClrOriMap();
int DeleteLastCube();
int AddParallelogram(const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,const int y3,const int z3,unsigned int EdgeColor,unsigned int InnerColor);
int AddCube(const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,
		const int y3,const int z3,const int x4,const int y4,const int z4,unsigned int EdgeColor,unsigned int InnerColor);
int AddCylinder(const int x1,const int y1,const int z1,const int height, const unsigned int EdgeNum, const int Radius,unsigned int EdgeColor,unsigned int InnerColor);
int D3MR();
int EditCube(const int BeginDotOrder, const int x1,const int y1,const int z1,const int x2,const int y2,const int z2,const int x3,
		const int y3,const int z3,const int x4,const int y4,const int z4);
		
int clrWires();
int newWire(const int x1,const int z1,const int x2,const int z2, int FloorHeight);
int linkWires(const int x1,const int z1, int FloorHeight);
int ColorWires(int BlingStrength, int BlingNow);
void ShadowType(int type);
int ReturnIOrderX(int i);
int ReturnIOrderY(int i);
int ReturnIOrderZ(int i);
//extern struct D3FullVectorMap OriMap,OutputMap;

#endif