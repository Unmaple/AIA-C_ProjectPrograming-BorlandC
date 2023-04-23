#ifndef _BCNTC_H_
#define _BCNTC_H_
#include"mimage.h"
#include"MZFK.h"
#include"mmouse.h"
#include"hz.h"
;
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


int BCRender(struct BCWindow W);
int BCRenderButton(struct BCButton B);
int BCDetect(struct BCWindow *W);
int BCDetectButton(struct BCButton B);
#endif