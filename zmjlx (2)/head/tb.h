#ifndef _TB_H_
#define _TB_H_

int page_YearOnYear(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void TB_diagram(int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void TB_Ddiagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void draw_TB(DATE date);
static int show_date5(DATE date);

#endif