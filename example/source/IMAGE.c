/***********************

该图像转换及输出函数，要求输入的图片分辨率在640*480之内
（对VGAHI的阉割版）
有问题您再Q我：1105674202 

***********************/
#include <stdio.h>
#include <dos.h>
#include "image.h"
#include <graphics.h>
#include <conio.h>


int bmp_convert(char *bmp,char *dbm)	//将 *.bmp 变为 *.dbm,字符串bmp中为bmp所在地址，字dbmp为输出地址
{
//	static int color[16]={0,4,2,6,1,5,3,7,8,12,10,14,9,13,11,15}; 上win下ps 
	static int color[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//索引与bc内颜色序号对应转换（建议用win画图转化）
	unsigned char dbmline[640],bmpline[640],pixel[8],Vbyte;
	int ImageW,ImageH,i,j,k,n,now,bmpcom,gg ;
	long hangsize;
	FILE *fbmp,*fdbm;
	union {
		unsigned char val;
		struct {
			unsigned cl:4;
			unsigned ch:4;
		}color;	//用位域储存颜色信息，分拆颜色信息 
	}MyColor;
	if((fbmp=fopen(bmp,"rb"))==NULL)
	{
		printf("%s\n",bmp);
		printf("Open bmp error!");
		return 1;
	}
	fseek(fbmp,18,SEEK_SET);	//bmp图像的宽高在文件头18字节后
	fread(&gg,4,1,fbmp);
   //	fread(&ImageW,4,1,fbmp);
	fread(&ImageH,4,1,fbmp);
	ImageW=gg;
 //	ImageH*=2;
  //	printf("%d ",ImageW);
  //	printf("%d",ImageH);
	if(ImageW==0||ImageH==0||ImageW>640||ImageH>480)
	{
		printf("The image is too large!Please input image below 640*480.");
		fclose(fbmp);
		return 1;
	}
	if((fdbm=fopen(dbm,"wb"))==NULL)
	{
		printf("Creat \"%s\" error!",dbm);
		return 1;
	}
	bmpcom=(ImageW-1)/8+1;	//行处理单元数
	hangsize=bmpcom*4;	//每行字节数（DIB数据要求每行字节为4整数倍，已计算补零）
	fwrite(&ImageW,sizeof(int),1,fdbm);
	fwrite(&ImageH,sizeof(int),1,fdbm);
	fseek(fbmp,-hangsize,SEEK_END);
	for(i=0;i<ImageH;i++)
	{
		now=0;
		fread(bmpline,hangsize,1,fbmp);
		fseek(fbmp,-hangsize*2,SEEK_CUR);
		for(n=3;n>=0;n--)	//每行拆成四个位面的数据输出
	  // for(n=0;n<=3;n++)
		{
			for(j=0;j<bmpcom;j++)
			{
				Vbyte=0;
				for(k=0;k<4;k++)
				{
					MyColor.val=bmpline[j*4+k];
					pixel[k*2]=color[MyColor.color.ch];
					pixel[k*2+1]=color[MyColor.color.cl];
				}
				for(k=0;k<8;k++)
				{
					Vbyte+=(pixel[k]>>n&1)<<(7-k);
				}
				dbmline[now++]=Vbyte;
			}
		}
		fwrite(dbmline,hangsize,1,fdbm);
	}
	fclose(fdbm);
	fclose(fbmp);
	return 0;
}

int show_dbm(int x,int y,char *dbm)	//输入dbmp的路径,在(x,y)输出图片(x需为8的倍数)
{					
	int ImageW,ImageH,n,i,j;
	long hangsize;
	FILE * fdbm;
	char far * per;
	
	per=(char far *)0xA0000000L;

	
//	_VideoBusy=YES;			//hanenv系统内的显示寄存器保护变量 
	
	if((fdbm=fopen(dbm,"rb"))==NULL)
	{
		char ch;
		printf("%s",dbm);
		ch = getchar();
		printf("Open Error!");
		return 1;
	}
	fread(&ImageW,sizeof(int),1,fdbm);
	fread(&ImageH,sizeof(int),1,fdbm);
  //	printf("%d %d",ImageW,ImageH);
	hangsize=(ImageW-1)/8;
	per=per+x/8+y*80;
	if((ImageH+y)>480)	ImageH=480-y; 	//VGAHI  640*480 
	for(i=0;i<ImageH;i++)//
	{
		for(n=8;n>=1;n>>=1)	//从第三位颜色平面写到第0
		{
			outportb(0x3c4,2);
			outportb(0x3c5,n);
			fread(per,hangsize,1,fdbm);
			fseek(fdbm,1,SEEK_CUR);
		}
	   //	fseek(fdbm,hangsize*2,SEEK_CUR);
		per+=80;
	}
	fclose(fdbm);
	
//	_VideoBusy=NO;	
	
	outportb(0x3c5,0xf);
	return 0;
}

void cir_bar(int x1,int y1,int x2,int y2,int color)	//在指定位置画出一个圆角矩形框 
{
	int w=x2-x1,h=y2-y1;
	setcolor(color);
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    ellipse(5+x1,10+y1,90,180,5,10);
    line(0+x1,10+y1,0+x1,10+h-20+y1);
    ellipse(5+x1,10+h-20+y1,180,270,5,10);
    line(5+x1,0+y1,5+w-10+x1,0+y1);
    ellipse(5+w-10+x1+1,10+y1,0,90,5,10);
    line(w+x1,10+y1,w+x1,y2-10);
    ellipse(w-5+x1+1,10+h-20+y1,270,360,5,10);
    line(5+x1,h+y1,5+w-10+x1,h+y1);
}

void movetopage(int x1, int y1, int x2, int y2,int page1 ,int page2)	//显示页间局部图像数据传输，输入左上角坐标及右上角坐标，从page1移动到page2
{	
	int per1, per2;
	int hangsize = (x2 - x1) / 8;
	int high = y2 - y1 + 1;
	register int i, p1, p2;
	if (page1 == 0)
	{
		per2 = 0xA0000000L;
		per1 = 0xA8000000L;
	}
	else
	{
		per1 = 0xA0000000L;
		per2 = 0xA8000000L;
	}
	
	

	per1 = per1 + (x1) / 8 + (y1 ) * 80;
	per2 = per2 + (x1) / 8 + (y1 ) * 80;
	for (i = 0; i <high; i++)		//传输视频图像 
	{
		for (p1 = 8, p2 = 3; p1 >= 1; p1 >>= 1, p2--)	//从第三位颜色平面写到第0
		{
			outportb(0x3c4, 2);		//颜色位面写寄存器 
			outportb(0x3c5, p1);
			outportb(0x3ce, 4);		//颜色位面读寄存器 
			outportb(0x3cf, p2);
			if (page1 == 0)
			{
				quick_move_2(per2, per1, hangsize);
			}
			else
			{
				quick_move_1(per2, per1, hangsize);
			}
		}
		per1 += 80;
		per2 += 80;
	}
	outportb(0x3cf,0);		//恢复设置 
	outportb(0x3c5,0xf);
	page1 = page2++;// 胡言乱语消warning
}

void set_color(int color_no,int red,int green,int blue)	//指定颜色编号，修改其对应的rgb值 
{
	if(color_no<16)
	{
		_AX=0x1007;	//选择10H显示中断中的第7号功能
		_BL=color_no;
		geninterrupt(0x10);
		color_no=_BH; 
	}
	else
		color_no = 0xff;	//将屏幕边缘色指向调色板255 
		
	//修改调色板寄存器 
	_DH=red;
	_CH=green;
	_CL=blue;
	_BX=color_no;
	_AX=0x1010;
	geninterrupt(0x10);
	
	//处理屏幕边缘颜色
	if(color_no==0xff)
	{
		_BH=0xff;
		_AX=0x1001;
		geninterrupt(0x10);
	} 
}

/*此为用汇编编写的支持跨段寻址的数据传输函数，来自《VGA页面图形数据移动技术在特殊显示效果中的应用》一文*/
int quick_move_1(int Start,int End,int Size)	//Start为原处首地址，End为目标位置首地址 	(1 to 0)
{
	asm{
		push es
		push ds
		push di
		push si
		push ax
		push cx
		push dx
		mov ax,0a800h
		mov ds,ax
		mov ax,Start
		mov si,ax
		mov ax,0a000h
		mov es,ax
		mov ax,End
		mov di,ax
		mov cx,Size
		rep movsb
		pop dx
		pop cx
		pop ax
		pop si
		pop di
		pop ds
		pop es
	}
	return 0;
}

int quick_move_2(int Start,int End,int Size)	//Start为原处首地址，End为目标位置首地址 	(0 to 1)
{
	asm{
		push es
		push ds
		push di
		push si
		push ax
		push cx
		push dx
		mov ax,0a000h
		mov ds,ax
		mov ax,Start
		mov si,ax
		mov ax,0a800h
		mov es,ax
		mov ax,End
		mov di,ax
		mov cx,Size
		rep movsb
		pop dx
		pop cx
		pop ax
		pop si
		pop di
		pop ds
		pop es
	}
	return 0;
}

void close_display()	//关闭屏幕显示
{
	_BL=0x32;
	_AH=0x12;
	_AL=0x01;
	geninterrupt(0x10);
}

void open_display()		//打开屏幕显示
{
	_BL=0x32;
	_AH=0x12;
	_AL=0x00;
	geninterrupt(0x10);
} 
