#ifndef _SELECT_H_
#define _SELECT_H_

int page_select(struct user *U,int mode);
void draw_select();
void lightcircle_rackselect(int flag);
void lightcircle_inventerselect(int num);
void inputnum(struct user *user);
void selectfile(struct user *user);
int check_select(struct user *user) ;

#endif