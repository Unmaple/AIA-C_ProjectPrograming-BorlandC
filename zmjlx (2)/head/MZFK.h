
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include<stdio.h>
#include"mimage.h"
//#define min(x, y) x < y ? x : y
//#define max(x, y) x > y ? x : y
#define ZfkCap 96//��32��127Ӧ���ǹ��ˣ���д��ĸ
//#include <conio.h>
//#define TrBlock 10

//�˴�Ϊ��2.23����ڴ����������������������
//���ڽ�֮ǰ����Renderϵ�к�����д������ΪMR��ʼ�ĺ�������ΪMemoryRender
//�Դ�λ��Ϊai.c����4��Դ�ļ�������ľ�������
//���ļ���������ʾ8*8��С�ַ������ǵ���Ե���գ������ַ�Ӧ��7*7Ϊ������С��ơ�

//���±�Ӧд��ͷ�ļ���
/*****
int MZFKinit();
int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure);
int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
*****/
;
extern unsigned char STORAGE[ZfkCap][8];
;
int MZFKinit();

int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure);//�ٶȽ����ذ���죬�������ظ��࣬�Ƽ�����ʹ��

int  MZFtest(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C);
int  MZFS(unsigned int x,unsigned int y,unsigned char Color,unsigned char* S);
int  MZFI(unsigned int x,unsigned int y,unsigned char Color,int i)
