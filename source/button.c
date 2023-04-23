#include"public.h"
#include"button.h"

void lightbutton_select(int flag)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch(flag)
	{ 
		case 1:
		setfillstyle(1,GREEN);
		bar(100+20,40+10,200,100-10);
		puthz(120+25,50+5,"日",32,34,WHITE);
		break;
		
		case 2:
		setfillstyle(1,GREEN);
		bar(200+30,40+10,310,100-10);
		puthz(230+25,50+5,"月",32,34,WHITE);
		break;
		
		case 3:
		setfillstyle(1,GREEN);
		bar(310+30,40+10,420,100-10);
		puthz(340+25,50+5,"年",32,34,WHITE);
		break;
		
		case 4:
		setfillstyle(1,GREEN);
		bar(420+30,40+10,600,100-10);
		puthz(450+25,50+5,"生命期",32,34,WHITE);
		break;
		
		case 5:
		setfillstyle(1,DARKGRAY);
		bar(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,WHITE);
		break;
		
		case 6:
		setfillstyle(1,DARKGRAY);
		bar(15,160,85,200);
		puthz(15+2,160+2,"邯郸",32,34,WHITE);
		break;
		
		case 7:
		setfillstyle(1,LIGHTCYAN);
		bar(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,CYAN);
		break;
		
		case 8:
		setfillstyle(1,LIGHTCYAN);
		bar(15,220,85,260);
		puthz(15+2,220+2,"邯郸",32,34,CYAN);
		break;
		
		case 9:
		setfillstyle(1,LIGHTCYAN);
		bar(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,CYAN);
		break;
		
		case 10:
		setfillstyle(1,BLUE);
		bar(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,LIGHTBLUE);
		break;
		
		case 11:
		setfillstyle(1,BLUE);
		bar(15,220,85,260);
		puthz(15+2,220+2,"邯郸",32,34,LIGHTBLUE);
		break;
		
		case 12:
		setfillstyle(1,BLUE);
		bar(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,LIGHTBLUE);
		break;
		
		case 13:
		setfillstyle(1,LIGHTRED);
		bar(290-26*4-10-5,40-5,290+5,80+5);
		setfillstyle(1,RED);
		bar(290-26*4-10,40,290,80);
		puthz(290-26*4-5,40+6,"物理视图",24,26,WHITE);
		break;
		
		case 14:
		setfillstyle(1,LIGHTRED);
		bar(350-5,40-5,350+26*4+10+5,80+5);
		setfillstyle(1,RED);
		bar(350,40,350+26*4+10,80);
		puthz(350+5,40+6,"逻辑视图",24,26,WHITE);
		break;
	}
}
	
void recoverbutton_select(int num)
{
	clrmous(MouseX, MouseY);
	setfillstyle(1,WHITE);
	setlinestyle(0,0,3);
	switch(num)
	{
		case 1:
		bar(200+30,40+10,310,100-10);
		puthz(230+25,50+5,"月",32,34,GREEN);
		bar(310+30,40+10,420,100-10);
		puthz(340+25,50+5,"年",32,34,GREEN);
		bar(420+30,40+10,600,100-10);
		puthz(450+25,50+5,"生命期",32,34,GREEN);
		break;

		case 2:
		bar(100+20,40+10,200,100-10);
		puthz(120+25,50+5,"日",32,34,GREEN);
		bar(310+30,40+10,420,100-10);
		puthz(340+25,50+5,"年",32,34,GREEN);
		bar(420+30,40+10,600,100-10);
		puthz(450+25,50+5,"生命期",32,34,GREEN);
		break;

		case 3:
		bar(100+20,40+10,200,100-10);
		puthz(120+25,50+5,"日",32,34,GREEN);
		bar(200+30,40+10,310,100-10);
		puthz(230+25,50+5,"月",32,34,GREEN);
		bar(420+30,40+10,600,100-10);
		puthz(450+25,50+5,"生命期",32,34,GREEN);
		break;
	
		case 4:
		bar(100+20,40+10,200,100-10);
		puthz(120+25,50+5,"日",32,34,GREEN);
		bar(200+30,40+10,310,100-10);
		puthz(230+25,50+5,"月",32,34,GREEN);
		bar(310+30,40+10,420,100-10);
		puthz(340+25,50+5,"年",32,34,GREEN);
		break;
		
		case 5:
		setfillstyle(1,WHITE);
		bar(15,160,85,200);
		setcolor(DARKGRAY);
		rectangle(15,160,85,200);
		puthz(15+2,160+2,"邯郸",32,34,DARKGRAY);
		break;
		
		case 6:
		setfillstyle(1,WHITE);
		bar(15,100,85,140);
		setcolor(DARKGRAY);
		rectangle(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,DARKGRAY);
		break;
		
		case 7:
		setfillstyle(1,WHITE);
		bar(15,220,85,260);
		bar(15,340,85,380);
		setcolor(CYAN);
		setlinestyle(0,0,3);
		rectangle(15,220,85,260);
		puthz(15+2,220+2,"邯郸",32,34,DARKGRAY);
		rectangle(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,DARKGRAY);
		break;
		
		case 8:
		setfillstyle(1,WHITE);
		bar(15,100,85,140);
		bar(15,340,85,380);
		setcolor(CYAN);
		setlinestyle(0,0,3);
		rectangle(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,DARKGRAY);
		rectangle(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,DARKGRAY);
		break;
		
		case 9:
		setfillstyle(1,WHITE);
		bar(15,100,85,140);
		bar(15,220,85,260);
		setcolor(CYAN);
		setlinestyle(0,0,3);
		rectangle(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,DARKGRAY);
		rectangle(15,220,85,260);
		puthz(15+2,220+2,"邯郸",32,34,DARKGRAY);
		break;
		
		case 10:
		setfillstyle(1,WHITE);
		bar(15,220,85,260);
		bar(15,340,85,380);
		rectangle(15,220,85,260);
		setcolor(DARKGRAY);
		setlinestyle(0,0,3);
		puthz(15+2,220+2,"邯郸",32,34,BLUE);
		rectangle(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,BLUE);
		break;
		
		case 11:
		setfillstyle(1,WHITE);
		bar(15,100,85,140);
		bar(15,340,85,380);
		setcolor(DARKGRAY);
		setlinestyle(0,0,3);
		rectangle(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,BLUE);
		rectangle(15,340,85,380);
		puthz(15+2,340+2,"两地",32,34,BLUE);
		break;
		
		case 12:
		setfillstyle(1,WHITE);
		bar(15,100,85,140);
		bar(15,220,85,260);
		setcolor(DARKGRAY);
		setlinestyle(0,0,3);
		rectangle(15,100,85,140);
		puthz(15+2,100+2,"武汉",32,34,BLUE);
		rectangle(15,220,85,260);
		puthz(15+2,220+2,"邯郸",32,34,BLUE);
		break;
		
		case 13:
		setfillstyle(1,WHITE);
		bar(350-5,40-5,350+26*4+10+5,80+5);
		setfillstyle(1,LIGHTRED);
		bar(350,40,350+26*4+10,80);
		puthz(350+5,40+6,"逻辑视图",24,26,DARKGRAY);
		break;
		
		case 14:
		setfillstyle(1,WHITE);
		bar(290-26*4-10-5,40-5,290+5,80+5);
		setfillstyle(1,LIGHTRED);
		bar(290-26*4-10,40,290,80);
		puthz(290-26*4-5,40+6,"物理视图",24,26,DARKGRAY);
		break;
	}
}	

void draw_button()
{
	setcolor(BLUE);
	setbkcolor(WHITE);
	setlinestyle(0,0,3);
	rectangle(600,5,620,25);
	line(600,5,620,25);
	line(620, 5, 600, 25);
	rectangle(20,5,40,25);
	line(20,15,40,15);
	line(20,15,25,10);
	line(20,15,25,20);
}