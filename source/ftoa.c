#include"public.h"
#include"ftoa.h"

char* my_itoa(int value,char *str,int radix)  
{  
    int sign = 0;  
    //char *s = str;   
   char ps[32];
   int i=1,j=0;   
    memset(ps,0,32);  
   
    if(value < 0)  
    {  
        sign = -1;  
       value = -value;  
	   }  
   do  
   {  
       if(value%radix>9)  
           ps[i] = value%radix +'0'+7;  
       else   
           ps[i] = value%radix +'0';  
       i++;  
	   }while((value/=radix)>0);  
	   if(sign<0)  
		   ps[i] = '-';  
    else  
        i--;  
    for(j=i;j>=0;j--)  
    {  
        str[i-j] = ps[j];  
   }  
    return str;  
}  

char* my_ltoa(long value,char *str)  
{  
    long sign = 0;  
    //char *s = str;   
    char ps[32];
    int i=1,j=0;   
    memset(ps,0,32);  
   
    if(value < 0)  
    {  
        sign = -1;  
       value = -value;  
	   }  
    do  
    {  
       // if(value%10>9)  
           // ps[i] = value%10 +'0'+7;  
       // else   
       ps[i] = value%10 +'0';  
       i++;  
	}while((value/=10)>0);  
	if(sign<0)  
		ps[i] = '-';  
    else  
        i--;  
    for(j=i;j>=0;j--)  
    {  
        str[i-j] = ps[j];  
    }  
    return str;  
} 

char *my_ftoa(double number,int ndigit,char *buf)  
{  
    int i;
    long int_part;  
    double float_part;  
    char str_int[32];  
    char str_float[32];  
    memset(str_int,0,32);  
    memset(str_float,0,32);  
	if(number >= 0)
	{
		int_part = (long)number;  
		float_part = number - int_part;  
		// 整数部分处理   
		my_ltoa(int_part,str_int);  
		// 小数部分处理   
		if(ndigit>0)  
	    {  
		   float_part =fabs( pow(10,ndigit)*float_part);  
			my_ltoa((long)float_part,str_float);  
		}  
		i = strlen(str_int);  
		str_int[i] = '.';      
		strcat(str_int,str_float);  
		strcpy(buf,str_int); 
	}
	else
	{
		number = -number;
		int_part = (long)number;  
		float_part = number - int_part;  
		// 整数部分处理   
		my_ltoa(int_part,str_int);  
		// 小数部分处理   
		if(ndigit>0)  
	    {  
		   float_part =fabs( pow(10,ndigit)*float_part);  
			my_ltoa((long)float_part,str_float);  
		}  
		i = strlen(str_int);  
		str_int[i] = '.';      
		strcat(str_int,str_float); 
		strcpy(buf,"-"); 
		strcat(buf,str_int); 
	}
     
    return buf;  
}  
