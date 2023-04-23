#ifndef MIMAGE
#define MIMAGE
;
int MR();
int ClrMR();
int MRBk(unsigned Color);
int MRPixel(const unsigned int x,const unsigned int y,const unsigned char Color);
int MR8_1Bar(const unsigned int x,const unsigned int y,const unsigned char Color);
int MRHorizonLine(const unsigned int x1,const unsigned int x2,const unsigned int y,const unsigned char Color);
int MRSafeHorizonLine(const int x1,const int x2,const int y,const char Color);
int MRVerticalLine(const unsigned int x,const unsigned int y1,const unsigned int y2,const unsigned char Color);
int MRRect(const unsigned int x1,const unsigned int x2,const unsigned int y1,const unsigned int y2,const unsigned char Color);
int MRBar(const unsigned int x1,const unsigned int x2,const unsigned int y1,const unsigned int y2,const unsigned char Color);
int MRLine(const int x1,const int y1,const int x2,const int y2,const unsigned char Color);
int MRBresenHamLineX(const int x1,const int y1,int x2,const int y2,const char Color);//此函数在0303更新为Bresenham算法,此处斜率绝对值小于1
int MRBresenHamLineY(const int x1,const int y1,const int x2,int y2,const unsigned char Color);//此函数在0303更新为Bresenham算法,此处斜率绝对值大于1
int MROutLine(const int x1,const int y1,const int x2,const int y2,const unsigned char Color);
int MRHorizonTriangle(const int x1,const int y1,const int x2,const int x3,const int y2,const unsigned char Color,const char type);//x2<=x3含检测
int MRTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color);
int MRRealTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type);
int MRdbm(const int x,const int y,const char *dbm);
static int MR8_1Shadow(const unsigned int x,const unsigned int y,const unsigned char Color,const char ShadowType);//shadowtype = 0 时为每四个两个，为1时为每四格一个
int MRHorizonShadowLine(const int x1,const int x2,const int y,const unsigned char Color,const char ShadowType);//x1<=x2
int MRRealHorizonShadowLine(const int x1,const int x2,const int y,const unsigned char Color,const char ShadowType);
int MRShadowTriangle(const int x1,const int y1,const int x2,const int y2,const int x3,const int y3,const unsigned char Color,const char type);//仅含检测
static void set_color(int color_no,int red,int green,int blue);	//指定颜色编号，修改其对应的rgb值 
int SetColor(struct SetOfColor S); 
struct SetOfColor
{
	int Red[16];
	int Green[16];
	int Blue[16];
};

extern char a1[38400];
extern char a2[38400];
extern char a3[38400];
extern char a4[38400];

#endif
