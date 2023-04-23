#include"public.h"
#include"pdata.h"
#include"date.h"
#include"diagram.h"

//根据实际情况 武汉最高辐射量约在7月，春季太阳辐射量略大于秋季
//河北邯郸太阳最高辐射量大约在6月，秋季太阳辐射量略大于春季
//单位面积太阳辐射吸收量固定<平单轴<双轴

void TODAYPOWER(int DIQU,struct user *U,int month,float tODAYPOWER[26])
{
	//struct EP Result;	
	int i=0;
	//float weather=0.0;
	//static float tODAYPOWER[26];
	//float WEATHER[3]={0.3,0.75,1.0};//雨天，阴天，晴天
	float HA[26]={0.0};
	float HAD[24][24]={ {0,0,0,0,0,0,0,67,306.1,663.1,850,1001,932,838.6,437.5,285,183.6,45,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,156,423.3,780.5,950.8,960.3,886,826.6,767.5,450.2,299.3,114.4,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,145,423.1,800.2,986.4,1004.6,966.8,920.5,780.6,436.9,305.3,111.2,0,0,0,0,0,0},
						{0,0,0,0,0,0,37,237.2,488.6,817.2,1064.3,1189.6,1302.5,1103.8,1012.3,873.2,302.6,195.2,0,0,0,0,0,0},
						{0,0,0,0,0,0,199.3,421.6,700.2,1023.4,1289.2,1289.2,1289.2,1216.3,1125.4,987.2,365,250,0,0,0,0,0,0},
						{0,0,0,0,0,0,134.7,425.3,721.9,1008.3,1275.3,1300.4,1345.3,1223.9,1126.3,1002,375.1,249.1,0,0,0,0,0,0},
						{0,0,0,0,0,70.2,149,524.3,1230.1,1294.8,1247.2,1300.2,1184.3,976.5,702.2,654.9,540.3,208.6,36,0,0,0,0,0},
						{0,0,0,0,0,156.3,209.3,723.5,1269.2,1300.5,1356.2,1425.7,1196.9,1102.6,896.2,756.1,670.1,236.3,149,0,0,0,0,0},
						{0,0,0,0,0,178,213.5,895,1256.2,1354.2,1429.7,1489.2,1207.3,1103.2,876.9,784.2,750.1,301.3,124.6,0,0,0,0,0},
						{0,0,0,0,0,23,330.5,852,789.2,860.3,988,905.3,965.3,969.2,745.3,453.2,200.7,68.2,0,0,0,0,0,0},
						{0,0,0,0,0,75,462.2,813,865.2,876.2,956.4,945.2,1000.2,954.3,850.2,561.7,301.4,100.2,0,0,0,0,0,0},
						{0,0,0,0,0,69,425.3,824.3,845.2,905.3,1075.2,935.3,1124.2,968.4,861.2,542.3,298.1,103.5,0,0,0,0,0,0},
						{0.0,0.0,0.0,0.0,0.0,0.0,0.0,88.2,450.4,695.4,1023.5,1156.4,1089.7,894.6,546.8,456.3,254.2,100.3,0,0,0,0,0,0},
						{0.0,0.0,0.0,0.0,0.0,0.0,0.0,102.5,567.1,785.3,1056.2,1115.3,1089.3,974.1,756.2,564.2,300.1,141.5,0,0,0,0,0,0},
						{0.0,0.0,0.0,0.0,0.0,0.0,0.,101.6,584.3,765.2,1075.3,1223.9,1110.3,1000.8,764.9,602.1,302.3,152.4,0,0,0,0,0,0},
						{0,0,0,0,0,0,56.1,256.7,700.3,925.3,1156.8,1356.4,1362.4,1307.3,945.3,782.9,402.8,210,0,0,0,0,0,0},
						{0,0,0,0,0,0,123.1,385.2,845.3,1007.3,1257.7,1475.3,1562.3,1356.3,1078.3,800.3,675.3,287.3,0,0,0,0,0,0},
						{0,0,0,0,0,0,112.6,387.2,856.3,1045.2,1245.3,1485.3,1675.2,1405.3,1000.3,826.6,702.1,298.3,0,0,0,0,0,0},
						{0,0,0,0,0,120.3,356.1,800.6,1045.3,1245.2,1448.4,1756.3,1544.3,1233.3,1045.3,890.6,441.1,245.5,50,0,0,0,0,0},
						{0,0,0,0,0,201.6,405.3,945.3,1145.8,1356.3,1565.2,1746.6,1604.2,1334.2,1156.2,968.2,500.2,300.9,145.2,0,0,0,0,0},
						{0,0,0,0,0,203.6,423.3,986.2,1212.3,1403.2,1602.3,1856.2,1640.3,1325.2,1174.3,1000,503.2,293.1,136.3,0,0,0,0,0},
						{0,0,0,0,0,10,78.3,230.3,754.3,956.2,1123.2,1396.2,1601.2,1302.2,989,765.3,502.3,225.3,12.6,0,0,0,0,0},
						{0,0,0,0,0,50.2,302.1,522.3,865,1145.3,1254.7,1403.5,1403.4,1367.2,1000.2,845.2,485.3,300.1,68.3,0,0,0,0,0},
						{0,0,0,0,0,52.3,309.6,536.2,842.6,1478.8,1265.7,1459.3,1425.3,1356.2,1045.3,865.3,456.1,306.4,65.2,0,0,0,0,0}};
	int num=0;
	float k1=0.98;//光伏发电系统可用率
	float Inventer_efficiency=0.0;//逆变器的转换效率
	//num=(float)(*U).Ban_num;
	num=U->Ban_num;//组件数目
	
	if(U->Inventer_type==0)
	{
		Inventer_efficiency=0.984;
	}
	else if (U->Inventer_type==1)
	{
		Inventer_efficiency=0.983;
	}
	
	{
		int ROW = ((DIQU+1)%2)*12 + (((((DIQU+1)%2)+month)%12)/3)*3+U->Rack_type;
		if(ROW < 24 && ROW >= 0)
		{
			for(i=0;i<24;i++)
			{
				HA[i]=HAD[ROW][i];
			}
		}	
	}
	/* switch(DIQU)
	{
		case 1://武汉
		if(month==12||month==1||month==2)//冬季的数据
		{
			 // weather=random_weather(0,1);
			if(U->Rack_type==0)
			{
				float HA1[]={0,0,0,0,0,0,0,67,306.1,663.1,850,1001,932,838.6,437.5,285,183.6,45,0,0,0,0,0,0};
				// 已经进行过处理的数据，得出的是对应一个组件获得的辐射量
				for(i=0;i<24;i++)
				{
					HA[i]=HA1[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA2[]={0,0,0,0,0,0,0,156,423.3,780.5,950.8,960.3,886,826.6,767.5,450.2,299.3,114.4,0,0,0,0,0,0};
				for(i=0;i<24;i++)
					{
						HA[i]=HA2[i];
					}
			}
			else if(U->Rack_type==2)
			{
				float HA3[]={0,0,0,0,0,0,0,145,423.1,800.2,986.4,1004.6,966.8,920.5,780.6,436.9,305.3,111.2,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA3[i];
				}
			} 
			
		}
		if(month==3||month==4||month==5)//春季的数据
		{
			//weather=random_weather(1,1);
			if(U->Rack_type==0)
			{
				float HA4[]={0,0,0,0,0,0,37,237.2,488.6,817.2,1064.3,1189.6,1302.5,1103.8,1012.3,873.2,302.6,195.2,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA4[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA5[]={0,0,0,0,0,0,199.3,421.6,700.2,1023.4,1289.2,1289.2,1289.2,1216.3,1125.4,987.2,365,250,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA5[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA6[]={0,0,0,0,0,0,134.7,425.3,721.9,1008.3,1275.3,1300.4,1345.3,1223.9,1126.3,1002,375.1,249.1,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA6[i];
				}
			}
		}
		if(month==6||month==7||month==8)//夏季的数据
		{
			//weather=random_weather(2,1);
			if(U->Rack_type==0)
			{
				float HA7[]={0,0,0,0,0,70.2,149,524.3,1230.1,1294.8,1247.2,1300.2,1184.3,976.5,702.2,654.9,540.3,208.6,36,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA7[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA8[]={0,0,0,0,0,156.3,209.3,723.5,1269.2,1300.5,1356.2,1425.7,1196.9,1102.6,896.2,756.1,670.1,236.3,149,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA8[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA9[]={0,0,0,0,0,178,213.5,895,1256.2,1354.2,1429.7,1489.2,1207.3,1103.2,876.9,784.2,750.1,301.3,124.6,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA9[i];
				}
			}
		}
		if(month==9||month==10||month==11)//秋季的数据
		{
			//weather=random_weather(3,1);
			if(U->Rack_type==0)
			{
				float HA10[]={0,0,0,0,0,23,330.5,852,789.2,860.3,988,905.3,965.3,969.2,745.3,453.2,200.7,68.2,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA10[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA11[]={0,0,0,0,0,75,462.2,813,865.2,876.2,956.4,945.2,1000.2,954.3,850.2,561.7,301.4,100.2,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA11[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA12[]={0,0,0,0,0,69,425.3,824.3,845.2,905.3,1075.2,935.3,1124.2,968.4,861.2,542.3,298.1,103.5,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA12[i];
				}
			}
		}
		break;
		
		case 2://河北邯郸
		if(month==11||month==12||month==1)//冬季的数据
		{
			//weather=random_weather(0,2);
			if(U->Rack_type==0)
			{
				float HA13[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,88.2,450.4,695.4,1023.5,1156.4,1089.7,894.6,546.8,456.3,254.2,100.3,0,0,0,0,0,0};
				for(i=0;i<24;i++)
					{
						HA[i]=HA13[i];
					}
			}
			else if (U->Rack_type==1)
			{
				float HA14[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,102.5,567.1,785.3,1056.2,1115.3,1089.3,974.1,756.2,564.2,300.1,141.5,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA14[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA15[]={0.0,0.0,0.0,0.0,0.0,0.0,0.,101.6,584.3,765.2,1075.3,1223.9,1110.3,1000.8,764.9,602.1,302.3,152.4,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA15[i];
				}
			}
		}
		if(month==2||month==3||month==4)//春季的数据
		{
			//weather=random_weather(1,2);
			if(U->Rack_type==0)
			{
				float HA16[]={0,0,0,0,0,0,56.1,256.7,700.3,925.3,1156.8,1356.4,1362.4,1307.3,945.3,782.9,402.8,210,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA16[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA17[]={0,0,0,0,0,0,123.1,385.2,845.3,1007.3,1257.7,1475.3,1562.3,1356.3,1078.3,800.3,675.3,287.3,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA17[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA18[]={0,0,0,0,0,0,112.6,387.2,856.3,1045.2,1245.3,1485.3,1675.2,1405.3,1000.3,826.6,702.1,298.3,0,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA18[i];
				}
			}
		}
		if(month==5||month==6||month==7)//夏季的数据
		{
			//weather=random_weather(2,2);
			if(U->Rack_type==0)
			{
				float HA19[]={0,0,0,0,0,120.3,356.1,800.6,1045.3,1245.2,1448.4,1756.3,1544.3,1233.3,1045.3,890.6,441.1,245.5,50,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA19[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA20[]={0,0,0,0,0,201.6,405.3,945.3,1145.8,1356.3,1565.2,1746.6,1604.2,1334.2,1156.2,968.2,500.2,300.9,145.2,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA20[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA21[]={0,0,0,0,0,203.6,423.3,986.2,1212.3,1403.2,1602.3,1856.2,1640.3,1325.2,1174.3,1000,503.2,293.1,136.3,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA21[i];
				}
			}
		}
		if(month==8||month==9||month==10)//秋季的数据
		{
			//ssweather=random_weather(3,2);
			if(U->Rack_type==0)
			{
				float HA22[]={0,0,0,0,0,10,78.3,230.3,754.3,956.2,1123.2,1396.2,1601.2,1302.2,989,765.3,502.3,225.3,12.6,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA22[i];
				}
			}
			else if (U->Rack_type==1)
			{
				float HA23[]={0,0,0,0,0,50.2,302.1,522.3,865,1145.3,1254.7,1403.5,1403.4,1367.2,1000.2,845.2,485.3,300.1,68.3,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA23[i];
				}
			}
			else if(U->Rack_type==2)
			{
				float HA24[]={0,0,0,0,0,52.3,309.6,536.2,842.6,1478.8,1265.7,1459.3,1425.3,1356.2,1045.3,865.3,456.1,306.4,65.2,0,0,0,0,0};
				for(i=0;i<24;i++)
				{
					HA[i]=HA24[i];
				}
			}
		}
		break;
	} */

		for(i=0;i<24;i++)
		{
			tODAYPOWER[i]=HA[i]*num*k1*Inventer_efficiency;
		}
		
	
/* 	closegraph();
	printf("Unum%d\n",U->Ban_num);
	getchar(); 
	printf("WEATHER%f\n",WEATHER[0]);
	printf("WEATHER%f\n",WEATHER[1]);
	printf("WEATHER%f\n",WEATHER[2]);
	printf("k1%f\n",k1);
	printf("Inventer_efficiency%f\n",Inventer_efficiency);
	
	for(i=0;i<24;i++)
	{
		//printf("%f\n",tODAYPOWER[i]);
	}printf("pU%p\n",U); */
	
	return ;
}

void real_TODAYPOWER(struct user *U,int year,int month,int day,int DIQU,float RTODAYPOWER[26],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i;
	//struct WeatherYearData WYDATA[10];
	float data1[26],data2[26];
	float randnum;
	//float weather=0.0;
	//static float tODAYPOWER[26];
	float WEATHER[3]={0.3,0.75,1.0};//雨天，阴天，晴天
	TODAYPOWER(DIQU,U,month,data1);
	randnum=RNUM[year-2023].RANDNUM[month][day];

	//weather = WEATHER[WYDATA[year-2023].DATA[month][day]];
	/*  closegraph();
	for(i = 1; i <= 12;i ++)
	{
		 for(j = 1; j <= 31; j ++)
		 {
			 printf("%f ",WYDATA[2024-2023].DATA[i][j]);
			 //printf("%f ",RNUM[2024-2023].RANDNUM[i][j]);
		 }
	}
	 delay(3000);
	getchar(); */
	if(month!=1||month!=12)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,(month-1),data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,(month+1),data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
	}
	
	else if(month==1)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,12,data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,(month+1),data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
	}
	
	else if(month==12)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,(month-1),data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,1,data2);
			for(i=0;i<24;i++)
			{
				RTODAYPOWER[i]=randnum*(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];//(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[WYDATA[year-2023].DATA[month][day]];
			}
		}
	}

}

float today_weather(int year,int month,int day,struct WeatherYearData WYDATA[10])
{
	float WEATHER[3]={0.3,0.75,1.0};
	float weather;
	weather=WEATHER[WYDATA[year-2023].DATA[month][day]];

	return weather;
}
	
float* real_timePOWER(struct user *U,struct DATE DATE,int DIQU,int weather,float timepower[26])
{
	int i,BANNum;
	int month,day;
	float data1[26]={0},data2[26]={0};
	//float timepower[26]={0};
	float WEATHER[3]={0.3,0.75,1.0};//雨天，阴天，晴天
	//year=DATE.year;year,
	month=DATE.month;
	day=DATE.day;
	BANNum = U->Ban_num;
	TODAYPOWER(1,U,4,data1);
	/* closegraph();
	printf("%f\n",timepower[time-1]);printf("%f\n",data1[2]);printf("%d",month);
	//printf("Inventer_efficiency%f\n",Inventer_efficiency);
	printf("Unum%d\n",U->Ban_num);
	getchar(); */
	if(month!=1||month!=12)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,(month-1),data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,(month+1),data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
	}
	
	else if(month==1)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,12,data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,(month+1),data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
	}
	
	else if(month==12)
	{
		if(day<=15)
		{
			TODAYPOWER(DIQU,U,(month-1),data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((15+day)*data1[i]+(15-day)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
		else if(day>15)
		{
			TODAYPOWER(DIQU,U,1,data2);
			for(i=0;i<24;i++)
			{
				timepower[i]=(((30-day+15)*data1[i]+(day-15)*data2[i])/30.0)*WEATHER[weather]/(float)BANNum;
			}
		}
	}
	/* closegraph();
for(i=10;i<13;i++)
{
	printf("%f",timepower[i]);
	
}getchar();  */ 
	return timepower;
}
	
float MONTHPOWER(int DIQU,struct user *U,int month)
{
	float HA = 0.0;
	int num=0,ROW;
	float k1=0.98;//光伏发电系统可用率
	float Inventer_efficiency=0.0;//逆变器的转换效率
	float HAD[24] = {5608.9,6614.9,6880.6,8623.5,10156.0,10187.6,10118.6,11447.9,11963.4,8150.2,8761.2,8977.3,
					 6755.8,7451.8,7683.1,9462.3,10853.7,11039.7,12222.3,13375.2,13759.5,9946.4,11012.8,11464.3};
	num=U->Ban_num;//组件数目
	
	if(U->Inventer_type==0)
	{
		Inventer_efficiency=0.984;
	}
	else if (U->Inventer_type==1)
	{
		Inventer_efficiency=0.983;
	}
	ROW = ((DIQU+1)%2)*12 + (((((DIQU+1)%2)+month)%12)/3)*3+U->Rack_type;
	if(ROW < 24 && ROW >= 0)
		HA = HAD[ROW];
	/* switch(DIQU)
	{
		case 1://武汉
		if(month==12||month==1||month==2)//冬季的数据
		{
			if(U->Rack_type==0)
			{
				HA=5608.9;
			}
			else if (U->Rack_type==1)
			{
				HA=6614.9;
			}
			else if(U->Rack_type==2)
			{
				HA=6880.6;
			}
		}
		
		else if(month==3||month==4||month==5)//春季的数据
		{
			if(U->Rack_type==0)
			{
				HA=8623.5;
			}
			else if (U->Rack_type==1)
			{
				HA=10156.0;
			}
			else if(U->Rack_type==2)
			{
				HA=10187.6;
			}
		}
		
		else if(month==6||month==7||month==8)//夏季的数据
		{
			if(U->Rack_type==0)
			{
				HA=10118.6;
			}
			else if (U->Rack_type==1)
			{
				HA=11447.9;
			}
			else if(U->Rack_type==2)
			{
				HA=11963.4;
			}
		}
		
		else if(month==9||month==10||month==11)//秋季的数据
		{
			if(U->Rack_type==0)
			{
				HA=8150.2;
			}
			else if (U->Rack_type==1)
			{
				HA=8761.2;
			}
			else if(U->Rack_type==2)
			{
				HA=8977.3;
			}
		}
		break;
		
		case 2:	
		if(month==11||month==12||month==1)//冬季的数据
		{
			if(U->Rack_type==0)
			{
				HA=5608.9;
			}
			else if (U->Rack_type==1)
			{
				HA=6614.9;
			}
			else if(U->Rack_type==2)
			{
				HA=6880.6;
			}
		}
		
		else if(month==2||month==3||month==4)//春季的数据
		{
			if(U->Rack_type==0)
			{
				HA=8623.5;
			}
			else if (U->Rack_type==1)
			{
				HA=10156;
			}
			else if(U->Rack_type==2)
			{
				HA=10187.6;
			}
		}
		
		else if(month==5||month==6||month==7)//夏季的数据
		{
			if(U->Rack_type==0)
			{
				HA=10118.6;
			}
			else if (U->Rack_type==1)
			{
				HA=11447.9;
			}
			else if(U->Rack_type==2)
			{
				HA=11963.4;
			}
		}
		
		else if(month==8||month==9||month==10)//秋季的数据
		{
			if(U->Rack_type==0)
			{
				HA=8150.2;
			}
			else if (U->Rack_type==1)
			{
				HA=8761.2;
			}
			else if(U->Rack_type==2)
			{
				HA=8977.3;
			}
		}
		break;
	}	 */
    return HA*num*k1*Inventer_efficiency;
}

void real_MONTHPOWER(struct user *U,int year,int month,int DIQU,float RMONTHPOWER[31+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i;
	float data3,data4;
	float WEATHER[3]={0.3,0.75,1.0};
	float randnum;
	data3=MONTHPOWER(DIQU,U,month);
	randnum=RNUM[year-2023].RANDNUM[month][i+1];
	for(i=0;i<15;i++)
	{
		if(month!=1)
		{
			data4=MONTHPOWER(DIQU,U,month-1);
		}
		else if(month==1)
		{
			data4=MONTHPOWER(DIQU,U,12);
		}
		RMONTHPOWER[i]=randnum*(((i+1+15)*data3+(15-(i+1))*data4)/30)*WEATHER[WYDATA[year-2023].DATA[month][i+1]];
	}
		
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
	{
		for(i=15;i<31;i++)
		{
			if(month!=12)
			{
				data4=MONTHPOWER(DIQU,U,month+1);
			}
			else if(month==12)
			{
				data4=MONTHPOWER(DIQU,U,1);
			}
			RMONTHPOWER[i]=randnum*((( 45-(i+1))*data3+((i+1)-15)*data4)/30)*WEATHER[WYDATA[year-2023].DATA[month][i+1]];
		}
	}
		
	else if(month==4||month==6||month==9||month==11)
	{
		for(i=15;i<30;i++)
		{
			data4=MONTHPOWER(DIQU,U,month+1);
			RMONTHPOWER[i]=randnum*((( 45-(i+1))*data3+((i+1)-15)*data4)/30)*WEATHER[WYDATA[year-2023].DATA[month][i+1]];
		}
	}
		
	else if(month==2)
	{
		if(year!=2024)
		{
			for(i=15;i<28;i++)
			{
				data4=MONTHPOWER(DIQU,U,month+1);
				RMONTHPOWER[i]=randnum*((( 45-(i+1))*data3+((i+1)-15)*data4)/30)*WEATHER[WYDATA[year-2023].DATA[month][i+1]];
			}
		}
		else if(year==2024)
		{
			for(i=15;i<29;i++)
			{
				data4=MONTHPOWER(DIQU,U,month+1);
				RMONTHPOWER[i]=randnum*((( 45-(i+1))*data3+((i+1)-15)*data4)/30)*WEATHER[WYDATA[year-2023].DATA[month][i+1]];
			}
		}
	}
/* closegraph();
for(i=0;i<30;i++)
{
	
	printf("%f",RMONTHPOWER[i]);
}getchar(); 
 */
	return;
}

void YEARPOWER(struct user *U,int DIQU,int year,float YEARPOWER[12+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i,j;
	float a[32];
	//YEARPOWER[12]={0};
	for(i=0;i<12;i++)
	{
		YEARPOWER[i]=0;
		real_MONTHPOWER(U,year,i+1,DIQU,a,WYDATA,RNUM);
		for(j=0;j<month_days (i+1,year);j++)
		{
			YEARPOWER[i]+=a[j];
		}
/* 	 closegraph();
        printf("%f",YEARPOWER[i]);
		getchar();  */
		
	}
/* 		for(j=0;j<31;j++)
		{
			YEARPOWER[i]=YEARPOWER[i]+a[j];
		}
	} *///该方法会出界
	/* 	if(i==0||i==2||i==4||i==6||i==7||i==9||i==11)
		{
			for(j=0;j<31;j++)
			{
				YEARPOWER[i]=YEARPOWER[i]+a[j];
			}
		}
		else if(i==3||i==5||i==8||i==10)
		{
			for(j=0;j<30;j++)
			{
				YEARPOWER[i]=YEARPOWER[i]+a[j];
			}
		}
		else if (i==1)
		{
			if(year==2024)
			{
				for(j=0;j<29;j++)
				{
					YEARPOWER[i]=YEARPOWER[i]+a[j];
				}
			}
			else if(year!=2024)
			{
				for(j=0;j<28;j++)
				{
					YEARPOWER[i]=YEARPOWER[i]+a[j];
				}
			}
		}
	}
 */
	return ;
} 

void LIFEPOWER(struct user *U,int DIQU,float LIFEPOWER[5+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i=0,j=0;
	float a[12+1];
	for(i=0;i<5;i++)
	{
		LIFEPOWER[i]=0;
		YEARPOWER(U,DIQU,i+2023,a,WYDATA,RNUM);
		for(j=0;j<12;j++)
		{	 //closegraph();
			LIFEPOWER[i]+=a[j];
			//printf("%f\n",a[j]);
		}
	 	
       // printf("%f\n",LIFEPOWER[i]);
		//getchar();
	}
	return ;
}

float TOTALPOWER(struct user *U,struct RandNum RNUM[10],struct WeatherYearData WHWYDATA[10],struct WeatherYearData HDWYDATA[10])
{
	float a[6],b[6];
	int i;
	float sum1=0,sum2=0,sum=0;
	
	LIFEPOWER(U,1,a,WHWYDATA,RNUM);
	LIFEPOWER(U,2,b,HDWYDATA,RNUM);
	for(i=0;i<5;i++)
	{
		sum1+=a[i];
		sum2+=b[i];
	}
	sum=(sum1+sum2)/2;
	/* closegraph();
	printf("%f",sum);
	getchar(); */
	return sum;
}
	
void SEASONPOWER(struct user *U,int year,int DIQU,float SEASONPOWER[4+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i =0;
	float a[12+1];
	YEARPOWER(U,DIQU,year,a,WYDATA,RNUM);
	for (i=0;i<4;i++)
	{
		SEASONPOWER[i]=0;
	}
	switch(DIQU)//武汉	
	{
		case 1:
		SEASONPOWER[0]=a[2]+a[3]+a[4];
		SEASONPOWER[1]=a[5]+a[6]+a[7];
		SEASONPOWER[2]=a[8]+a[9]+a[10];
		SEASONPOWER[3]=a[0]+a[1]+a[11];
		break;
	
		case 2://邯郸
		SEASONPOWER[0]=a[1]+a[2]+a[3];
		SEASONPOWER[1]=a[4]+a[5]+a[6];
		SEASONPOWER[2]=a[7]+a[8]+a[9];
		SEASONPOWER[3]=a[10]+a[11]+a[0];
		break;
	}
	/* closegraph();
	printf("%f",a[1]);
	printf("%f",SEASONPOWER[1]);
	getchar(); */
	return ;
}
	
void TBRATE(struct user *U,int year,int DIQU,float TBRATE[4+1],struct WeatherYearData WYDATA[10],struct RandNum RNUM[10])
{
	int i;
	float a[5]={0},b[5]={0};
	SEASONPOWER(U,year,DIQU,a,WYDATA,RNUM);
	if(year==2023)
	{
		TBRATE[0]=0.48;
	}
	else 
	{
		SEASONPOWER(U,year-1,DIQU,b,WYDATA,RNUM);
		TBRATE[0]=(a[0]-b[3])/b[3];
	}
	for(i=1;i<4;i++)
	{
		TBRATE[i]=(a[i]-a[i-1])/a[i-1];
	}
	/* closegraph();
	printf("%f",TBRATE[0]);
	printf("%f",TBRATE[1]);
	printf("%f",TBRATE[2]);
	printf("%f",TBRATE[3]);
	getchar();  */ 
	return;
}
		
	
int random_weather(int season,int DIQU)
{
	double result;
	float RATE1[3][4]={{0.0,0.0,0.0,0.0},{0.2,0.3,0.1,0.3},{0.7,0.6,0.4,0.6}};//四个季节三种天气发生的概率
	float RATE2[3][4]={{0.0,0.0,0.0,0.0},{0.3,0.2,0.1,0.2},{0.6,0.5,0.4,0.5}};//四个季节三种天气发生的概率
	//大量测试并结合实际天气情况给出的分布比例
	result=(float)rand()/RAND_MAX; 
	//srand((unsigned)time( NULL ) );
	switch(DIQU)
	{
		case 1://武汉	
			
			if(result>RATE1[2][season])
			{
				return 2;
			}
			else if(result>RATE1[1][season])
			{
				return 1;
			}
			else if(result>RATE1[0][season])
			{
				return 0;
			}
			return -1;
		//break;
			
		case 2://河北邯郸
			
			if(result>RATE2[2][season])
			{
				return 2;
			}
			else if(result>RATE2[1][season])
			{
				return 1;
			}
			else if(result>RATE2[0][season])
			{
				return 0;
			}
			return -1;
		//break;
	}
	return -1;
}

int setWYDATA(struct WeatherYearData *pDATA,int DIQU)
{
	int i,j;
	static int seed = 0;
	if(seed == 0)
	{
		srand((unsigned)time( NULL ) );
		seed = 1;
	}
	//closegraph();
	for(i = 1; i <= 12;i ++)
	{
		for(j = 1; j <= 31; j ++)
		{
			if(i<=11)
			{
				pDATA->DATA[i][j] = random_weather(i/3,DIQU);//这里是否合理？i=1起步
			}
			else if(i==12)
			{
				pDATA->DATA[12][j] = random_weather(0,DIQU);
			}
			//printf("%d",pDATA->DATA[i][j]);
		}
	}
	///delay(3000);
	//getchar();
	return 0;
} 

int setRANDNUM(struct RandNum *pRANDNUM)
{
	int i,j;
	static int seed = 0;
	if(seed == 0)
	{
		srand((unsigned)time( NULL ) );
		seed = 1;
	}

	for(i = 1; i <= 12;i ++)
	{
		for(j = 1; j <= 31; j ++)
		{
			pRANDNUM->RANDNUM[i][j]=( ((float)rand() / RAND_MAX)*0.1)+1;
		//printf("%f",(( ((float)rand() / RAND_MAX)*0.1)+1));
		}
	}
	///delay(3000);
	//getchar();
	return 0;
}