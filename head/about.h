#ifndef_ABOUT_H
#define_ABOUT_H

int page_about(int mode,struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void draw_about1();
void draw_about2(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void recoverbutton_about(int flag);
void lightbutton_about();

#endif