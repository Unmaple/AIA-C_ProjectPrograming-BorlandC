#include"public.h"
#include"welcome.h"
#include"image.h"

/*****************************************
lgfunc.c
COPYRIGHT:	lixin
FUNCTION:	start with this first screen
ABSTRACT:	
DATE:2023/3/9
*******************************************/


void welcome_page(void)
{
	setfillstyle(1,WHITE);//��䱳��ɫΪ��ɫ
	floodfill(50,50,WHITE);
	
	show_dbm(155,1,"..\\photo\\logo1.dbm");
	setlinestyle(0,0,3);//���ÿ��Ϊ3��ʵ��
	setcolor(DARKGRAY);//�������ɫΪ��ɫ
	line(0,320,640,320);	//�ֽ���

	setfillstyle(1,GREEN);
	bar(140,350,530,410);	//��ӭ
	puthz(150,380-16 ,"�ݶ��������ģ����ϵͳ", 32, 34, WHITE);

	setfillstyle(1, LIGHTGRAY);//��Ȩ��������
	bar(0,458,640,480);
	setcolor(WHITE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(1,0,3);
	outtextxy(400, 450+3, " by zmj and lx");
	
	delay(2500);
}
