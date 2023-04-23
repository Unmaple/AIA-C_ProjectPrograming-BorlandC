#include "public.h"
#include"main.h"
#include"data.h"
#include"mimage.h"
#include"mmouse.h"
#include"MZFK.h"
//#include"kairo.h"
#include"image.h"
#include"string.h"
#include"pageEmu.h"

void main(void)
{
	int page = 0;
	int i;
	struct user U;
	int graphdriver = VGA;
    int	graphmode = VGAHI;
	static struct WeatherYearData WHWYDATA[5];
	static struct WeatherYearData HDWYDATA[5];//สýื้
	static struct RandNum RNUM[10];

	initgraph(&graphdriver,&graphmode,"c:\\borlandc\\bgi");
	
	setWYDATA(WHWYDATA+0,1);
	setWYDATA(WHWYDATA+1,1);
	setWYDATA(WHWYDATA+2,1);
	setWYDATA(WHWYDATA+3,1);//&(WYDATA[i])
	setWYDATA(WHWYDATA+4,1);
	setWYDATA(HDWYDATA+0,2);
	setWYDATA(HDWYDATA+1,2);
	setWYDATA(HDWYDATA+2,2);
	setWYDATA(HDWYDATA+3,2);//&(WYDATA[i])
	setWYDATA(HDWYDATA+4,2);
	setRANDNUM(RNUM+0);
	setRANDNUM(RNUM+1);
	setRANDNUM(RNUM+2);
	setRANDNUM(RNUM+3);
	setRANDNUM(RNUM+4);
	//U->Rack_type=-1;
	//U->Ban_num=1;
	//U->Inventer_type=-1;
	MZFKinit();
	welcome_page();
	mouseinit();

	while(1)
	{
		switch(page)
		{
			case 0:
				page=page_select(&U,0);
				break;
			
			case 1:
				page=page_history(&U);
				break;
			
			case 2:
				page = page_select(&U,1);
				break;
			
			case 3:
				page=page_diagram(&U,WHWYDATA,HDWYDATA,RNUM);
				break;
			
			case 4:
				page=page_dz(&U);
				break;
			
			case 5:
				page=page_chart(&U,WHWYDATA,HDWYDATA,RNUM);
				break;
			
			case 6:
				page = pageEmu(U,WHWYDATA,HDWYDATA);
				break;
			case 7:
				page=page_YearOnYear(&U,WHWYDATA,HDWYDATA,RNUM);
				break;
			
			case 8:
				page=page_chain(&U,WHWYDATA,HDWYDATA,RNUM);
				break;
			
			case 9:
				page=page_device(&U,1);
				break;
				
			case 20:
			case 21:
				page=page_about(page-19,&U,WHWYDATA,HDWYDATA,RNUM);
				break;
			
			case 11:
				page = page_view(U.Rack_type);
				break;
			
			case 12:
				closegraph();
				delay(100);
				exit(0);
				break;
			default:
				closegraph();
				printf("pageError!");
				delay(2000);
				exit(0);
				return 0;
		}
	}
}
	
	