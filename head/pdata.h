#ifndef _POWERDATA_H_
#define _POWERDATA_H_

void TODAYPOWER(int DIQU,struct user *U,int month,float tODAYPOWER[26]);
void real_TODAYPOWER(struct user *U,int year,int month,int day,int DIQU,float RTODAYPOWER[26],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
float today_weather(int year,int month,int day,struct WeatherYearData WYDATA[10]);
float* real_timePOWER(struct user *U,struct DATE DATE,int DIQU,int weather,float timepower[26]);
float MONTHPOWER(int DIQU,struct user *U,int month);
void real_MONTHPOWER(struct user *U,int year,int month,int DIQU,float RMONTHPOWER[31+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
void YEARPOWER(struct user *U,int DIQU,int year,float YEARPOWER[12+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
void LIFEPOWER(struct user *U,int DIQU,float LIFEPOWER[5+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
float TOTALPOWER(struct user *U,struct RandNum RNUM[10],struct WeatherYearData WHWYDATA[10],struct WeatherYearData HDWYDATA[10]);
void SEASONPOWER(struct user *U,int DIQU,int year,float SEASONPOWER[4+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
void TBRATE(struct user *U,int year,int DIQU,float TBRATE[4+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10]);
int random_weather(int season,int DIQU);
int setWYDATA(struct WeatherYearData *pDATA,int DIQU);
int setRANDNUM(struct RandNum *pRANDNUM);

#endif