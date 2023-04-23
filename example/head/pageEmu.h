#ifndef PAGEEmu
#define PAGEEmu
;
#include"public.h"
#include"Notice.h"
/******
typedef struct DATE
{
         int year;
         int month;
         int day;
}DATE;

struct WeatherYearData
{
	unsigned char DATA[12+1][31+1];
};
****/

int pageEmu(struct user U,struct WeatherYearData WHWYDATA[],struct WeatherYearData HDWYDATA[]);
int PushBan(int TriStart, int BanUp);
int MAKESHADOWS(struct BANS Bans,struct D3DOT STELLAR);
int MakeShadow(int BanOrder,struct D3DOT STELLAR);
int LongWire(const int x1,const int z1,const int x2,const int z2, int FloorHeight, int division);
int AddBANS(struct BANS Bans);
int EditBANS(struct BANS Bans, int j);//,int BANPos
int AddBAN(struct SUNBAN Ban);
int EditBAN(int Tx, int Tz,int Order,int BANPos);
int EditDoubleBan(int Tx, int Tz,int Order,int Fai,int Xita);
int rainyEffect(int mode);
int SetElectricStrength(int i, int *pElectricStrength);
static int PushRelativeBan(int RelativeOrder);
int SetRenderQueue(int Fai,int TotalBanNum,int Xita);//此处仍需修改，应当以EmuBans为参数，而不是限定仅12个太阳能板
static int SetObjects(int Fai,int TotalBanNum);
int SetColorTable(int WEATHER,int i,int *ChangeWeather);
int DrawStellarAndShadow(int i, struct TransformMatrix TM, double Zoom, int WEATHER, struct BANS EmuBans, int StellarHeightAngle);
int DrawWeatherEffect(int WEATHER, int PAUSE);
int ShowDate(DATE date,int i);

int ReturnDate(int days,DATE *pdate);
int isrunyear (int year);
int month_days (int month, int year);

static int EditDate(struct Button BDate[6],struct DATE *CurrentDate);
static int NextDate(struct DATE *CurrentDate);
static int checkKeyboard(int *Fai, int *Xita, double *Zoom, int *exit);
int SunCamera(int i, int *pFai, int *pXita, double *pZoom,int StellarHeightAngle);
int BanCamera(int i, int *pFai, int *pXita, double *pZoom);
static int GetStellarHeightAngle(unsigned int DIQU,unsigned int month);
static int EditPower(int *pWEATHER,int *pStellarHeightAngle, int DIQU, DATE CurrentDate, float DayPowerBuffer[26],
					 struct user U,struct WeatherYearData WHWYDATA[],struct WeatherYearData HDWYDATA[]);

#endif
