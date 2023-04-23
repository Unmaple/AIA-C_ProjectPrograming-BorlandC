#ifndef _DIAGRAM_H_
#define _DIAGRAM_H_

int page_diagram(struct user *U,struct WeatherYearData *pWHDATA,struct WeatherYearData *pHDDATA ,struct RandNum *pRANDNUM);
void power_daydiagram(float a[26],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_monthdiagram1(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_monthdiagram2(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_monthdiagram3(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_monthdiagram4(float a[32],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_yeardiagram(float a[13],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct DATE DATE,struct RandNum *pRANDNUM);
void power_lifetimediagram(float a[6],int DIQU,struct user *U,struct WeatherYearData *pDATA,struct RandNum *pRANDNUM);
void draw_diagram();
static int show_date1(DATE date);
static int show_date2(DATE date);
static int show_date3(DATE date);

#endif