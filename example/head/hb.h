#ifndef _HB_H_
#define _HB_H_

int page_chain(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void HB_diagram(int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void HB_Ddiagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void draw_HB(DATE date);
static int show_date6(DATE date);

#endif
