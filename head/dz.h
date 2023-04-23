#ifndef _DZ_H_
#define _DZ_H_

int page_dz(struct user *U);
int color_wires(int x1, int x2,int y1, int y2,int BlingStrength, int BlingNow,int division);
int Blline(int x1,int y1, int x2, int y2);
void draw_parabola(int x1, int y1, int x2, int y2, int a) ;
int LXColorParabola(int x1,int y1, int x2, int y2, int a,int BlingStrength);
void drawTower(int x, int y);
void drawTransformer(int x, int y);
void draw_dz(struct user *U);

#endif