#ifndef IMAGE_H
#define IMAGE_H


//������룬�����������
;
int bmp_convert(char *bmp,char *dbm);	//�� *.bmp ��Ϊ *.dbm,�ַ���bmp��Ϊbmp���ڵ�ַ����dbmpΪ�����ַ
int show_dbm(int x,int y,char *dbm);	//����dbmp��·��,��(x,y)���ͼƬ(x��Ϊ8�ı���)
void cir_bar(int x1,int y1,int x2,int y2,int color);	//��ָ��λ�û���һ��Բ�Ǿ��ο� 
void movetopage(int x1, int y1, int x2, int y2,int page1 ,int page2);
void set_color(int color_no,int red,int green,int blue); //ָ����ɫ��ţ��޸����Ӧ��rgbֵ 

/*��Ϊ�û���д��֧�ֿ��Ѱַ�����ݴ��亯�������ԡ�VGAҳ��ͼ�������ƶ�������������ʾЧ���е�Ӧ�á�һ��*/
int quick_move1(int Start,int End,int Size);	//StartΪԭ���׵�ַ��EndΪĿ��λ���׵�ַ 
int quick_move2(int Start,int End,int Size);	//StartΪԭ���׵�ַ��EndΪĿ��λ���׵�ַ 
 
void close_display();		//�ر���Ļ��ʾ
void open_display();		//����Ļ��ʾ
 
#endif
