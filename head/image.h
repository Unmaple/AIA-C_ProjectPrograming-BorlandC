#ifndef IMAGE_H
#define IMAGE_H


//往届代码，不计入代码量
;
int bmp_convert(char *bmp,char *dbm);	//将 *.bmp 变为 *.dbm,字符串bmp中为bmp所在地址，字dbmp为输出地址
int show_dbm(int x,int y,char *dbm);	//输入dbmp的路径,在(x,y)输出图片(x需为8的倍数)
void cir_bar(int x1,int y1,int x2,int y2,int color);	//在指定位置画出一个圆角矩形框 
void movetopage(int x1, int y1, int x2, int y2,int page1 ,int page2);
void set_color(int color_no,int red,int green,int blue); //指定颜色编号，修改其对应的rgb值 

/*此为用汇编编写的支持跨段寻址的数据传输函数，来自《VGA页面图形数据移动技术在特殊显示效果中的应用》一文*/
int quick_move1(int Start,int End,int Size);	//Start为原处首地址，End为目标位置首地址 
int quick_move2(int Start,int End,int Size);	//Start为原处首地址，End为目标位置首地址 
 
void close_display();		//关闭屏幕显示
void open_display();		//打开屏幕显示
 
#endif
