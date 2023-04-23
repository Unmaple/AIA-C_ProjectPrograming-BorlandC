#ifndef _CHART_H_
#define _CHART_H_

int page_chart(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void draw_chart();
void power_chart(float b[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void diagram_chart(float b[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void lightbutton_chart(int flag);
void recoverbuttom_chart(int flag);

#endif