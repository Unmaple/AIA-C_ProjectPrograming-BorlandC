#include"public.h"
#include"history.h"
#include"button.h"

/*****************************************
history.c
COPYRIGHT: 	li xin
FUNCTION:  
DATE:2023/3/23
******************************************/

int page_history(struct user *U)
{
	int page=1;
	int i = 0;
    int j = 0;
	int length=0;
	char NumBuffer[100]={0};
	FILE *fp=NULL;
	
	clrmous(MouseX, MouseY);
	cleardevice();
	delay(100);
	draw_button();
	

	if ((fp = fopen("..\\data\\User.dat", "rb+")) == NULL)
	{
		closegraph();
		printf("the file in history.c cannot be opened%\n");
		delay(1000);
		exit(1);
	}
	
	fseek(fp, 0, 2);
	length = ftell(fp) / sizeof(struct user);
	if(length > 8)
	{
		i = length - 8;
	}
	else
	{
		i = 0;
	}
	for (; i < length; i++)
	{
		//if ((U = (struct user*)malloc(sizeof(struct user))) == NULL)
		//{
		//	printf("no enough memory");
		//	exit(1);
		//}
		//delay(100);
		
		fseek(fp, i * sizeof(struct user), 0);
		fread(U, sizeof(struct user), 1, fp);
		

		settextstyle(1,0,2);
		settextjustify(0, 2);
		cir_bar(20, 35 + 50 * j, 620, 35+ 50 * (j +1.1), CYAN);
		
		puthz(25+10,50+50*j,"支架类型",16,18,LIGHTBLUE);
		switch(U->Rack_type)
		{
			case 0:
			puthz(115,45+50*j,"固定支架",24,22,CYAN);
			break;
			
			case 1:
			puthz(115,45+50*j,"平单轴支架",24,22,CYAN);
			break;
			
			case 2:
			puthz(115,45+50*j,"双轴支架",24,22,CYAN);
			break;
		}
		puthz(245,50+50*j,"组件数目",16,18,LIGHTBLUE);
		itoa(U->Ban_num,NumBuffer,10);
		setcolor(DARKGRAY);
		outtextxy(325,45+50*j,NumBuffer);
		puthz(385,50+50*j,"逆变器类型",16,18,LIGHTBLUE);
		switch(U->Inventer_type)
		{
			case 0:
			puthz(480,45+50*j,"集中式逆变器",24,22,RED);
			break;
			
			case 1:
			puthz(480,45+50*j,"集散式逆变器",24,22,RED);
			break;
			
		}
		j++;
	}
	
	save_bk_mou(MouseX,MouseY);
	drawmous(MouseX,MouseY);
	
	while(page==1)
	{
		newmouse(&MouseX,&MouseY,&press);
		
		if(mouse_press(600,5,620,25)==2
		||mouse_press(20,5,40,25)==2)
		{
			MouseS=1;
		}
		
		else if(mouse_press(0,0,640,480)==2)
		{
			MouseS=0;
		}
	/**
		for(j=7;j<=0;j--)
		{
			for(i=length-1;i<=length-8;i--)
			{
				if (mouse_press(20, 35 + 50 * j, 620, 35+ 50 * (j +1.1))==1)
				{
					fseek(fp, i * sizeof(struct user), 0);
					fread(U, sizeof(struct user), 1, fp);
					page =2;
					//TODO:read N order User

					//END_OF_TODO
					fclose(fp);
					return page;
				}
			}
		}
	**/
		else if(mouse_press(20, 35  , 620, 35+ 50 * 1.1)==1)
		{
			if(length > 8)
			{
				i = length - 8;
			}
			else
			{
				i = 0;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *1, 620, 35+ 50 * (1+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+1;
			}
			else
			{
				i = 1;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *2, 620, 35+ 50 * (2+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+2;
			}
			else
			{
				i = 2;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *3, 620, 35+ 50 * (3+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+3;
			}
			else
			{
				i = 3;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50*4, 620, 35+ 50 * (4+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+4;
			}
			else
			{
				i = 4;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *5, 620, 35+ 50 * (5+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+5;
			}
			else
			{
				i = 5;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *6, 620, 35+ 50 * (6+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+6;
			}
			else
			{
				i = 6;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20, 35 + 50 *1, 620, 35+ 50 * (7+1.1))==1)
		{
			if(length > 8)
			{
				i = length - 8+7;
			}
			else
			{
				i = 7;
			}
			fseek(fp, i * sizeof(struct user), 0);
			fread(U, sizeof(struct user), 1, fp);
			fclose(fp);
			page =2;
			
			return page;
		}
		
		else if(mouse_press(20,5,40,25)==1)
		{
			page=0;
			return page;
		}
		
		else if(mouse_press(600,5,620,25) == 1)
		{
			page = 12;
			return page;
		}
	}
	return 0;
}

