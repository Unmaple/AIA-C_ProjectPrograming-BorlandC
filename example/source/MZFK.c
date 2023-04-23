/*****************************************
MZFK.c
COPYRIGHT:  Zengmingjie
FUNCTION:   Output ASCII letters to MR-series' buffer
DATE:       2023/2/25-3/1(Debug and Reinforcement)
Available code lines:ZMJ-about130lines
******************************************/
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include"mimage.h"
#include"MyMath.h"
#define ZfkCap 96//��32��127Ӧ���ǹ��ˣ���д��ĸ

//�˴�Ϊ��2.23����ڴ����������������������
//���ڽ�֮ǰ����Renderϵ�к�����д������ΪMR��ʼ�ĺ�������ΪMemoryRender
//�Դ�λ��Ϊai.c����4��Դ�ļ�������ľ�������
//���ļ���������ʾ8*8��С�ַ������ǵ���Ե���գ������ַ�Ӧ��7*7Ϊ������С��ơ�
//2023.2.25,�����Զ���2209�ĳ��ο�ͬѧ����д���˱����Ӧ���ַ����ļ���һ����8��768�ĵ�ɫbmp��
//�ش���л��

//���±�Ӧд��ͷ�ļ���
;
static unsigned char STORAGE[ZfkCap][8];
int MZFKinit()
{
	//char *s = "C:\\test\\data\\ZFK.bmp";�˴��Ǿ���·��
	char *s = "..\\data\\ZFK.bmp";
	FILE *fp;
	unsigned int k;
	unsigned int i, j, bit,m;
	unsigned char temp[4];
	if ((fp = fopen(s, "rb")) == NULL)
	{
		printf("Cannot open MZFK data file!");
		getchar();
		return 1;
	}
	fseek(fp, 0x3E, 0);
	for(i = 0; i < ZfkCap; i ++)
	{
		for(j = 0; j < 8;j ++)
		{

			fread(temp,1,4,fp);
			STORAGE[i][7-j] = temp[0];
		}
	}
	fclose(fp);
	return 0;
}

static int MR8_1Group(unsigned int x,unsigned int y,unsigned char Color,unsigned char figure)//�ٶȽ����ذ���죬�������ظ��࣬�Ƽ�����ʹ��
{
	long elm = x/8+y * 80L;//element order	
	if(x > 639U ||y > 479U)//�೤���Ͻ���ʹ��L��
	{
		return 1;
	}
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
	//����ͬ
	
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

int  MZF(unsigned int x,unsigned int y,unsigned char Color,unsigned char C)
{
	int i,j;
	//setcolor(15); // ���û�ͼ��ɫΪ��ɫ
    for (i = 0; i < 8; i++) 
	{
        MR8_1Group(x,y+i,Color,STORAGE[C-32][i]);
    }
	return 0;
}

int  MZFS(unsigned int x,unsigned int y,unsigned char Color,unsigned char* S)
{
	int i,j;
	//setcolor(15); // ���û�ͼ��ɫΪ��ɫ
    for (i = 0; i < 80 && *S != '\0'; i++) 
	{
		for (j = 0; j < 8; j++) 
		{
        		MR8_1Group(x+8*i,y+j,Color,STORAGE[*S-32][j]);
		}
        S++;
      }
	return 0;
}


int  MZFI(unsigned int x,unsigned int y,unsigned char Color,int i)
{
	char S[16];
	itoa(i,S,10);
	return MZFS(x,y,Color,S);
}

