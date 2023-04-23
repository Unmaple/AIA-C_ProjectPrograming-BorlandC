#ifndef _NOTICE_H_
#define _NOTICE_H_

struct Window //全是ascii字符串
{
	char Lines[14][80];
	int LineNum;
	int on;
};

struct Button //ZIHAO非8时为汉字
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

int Render(struct Window W);
int RenderButton(struct Button B);
int Detect(struct Window *W);
int DetectButton(struct Button B);
#endif