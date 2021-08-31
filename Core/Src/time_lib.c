/*
EPOCH to human readable time and date converter for microcontrollers (PIC, AVR, Arduino, STM32)
Current EPOCH time can be found at https://www.epochconverter.com/
The code can be suitably modified to suit your requirements. I have extensively
tested this code with valid inputs. If you have any questions or if you find a bug, please contact me. 
Author: Siddharth Singh <sidsingh78@gmail.com>
Ver:1.0
Date: June 15, 2017 

Adopted 28.08.2021 for MCU by Naladchik
*/

#include "time_lib.h"

void epoch_to_datetime(uint32_t epoch, TypeDateTime* dt)
{		
		static uint8_t month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		const unsigned char week_days[7] = {4,5,6,0,1,2,3};
		//Thu=4, Fri=5, Sat=6, Sun=0, Mon=1, Tue=2, Wed=3
		uint32_t temp_days; 
   //---------------------------- Calculations -------------------------------------
    dt->leap_days = 0; 
    dt->leap_year_ind = 0;
    
    // Add or substract time zone here. 
    epoch+=10800 ; //GMT +3:00 = +10800 seconds 
    
      dt->ntp_second = epoch%60;
      epoch /= 60;
      dt->ntp_minute = epoch%60;
      epoch /= 60;
      dt->ntp_hour  = epoch%24;
      epoch /= 24;
        
      dt->days_since_epoch = epoch;      //number of days since epoch
      dt->ntp_week_day = week_days[dt->days_since_epoch % 7];  //Calculating WeekDay
      
      dt->ntp_year = 1970 + (dt->days_since_epoch / 365); // ball parking year, may not be accurate!
 
      int i;
      for (i = 1972; i < dt->ntp_year; i+=4)      // Calculating number of leap days since epoch/1970
         if(((i%4==0) && (i%100!=0)) || (i%400==0)) dt->leap_days++;
            
      dt->ntp_year = 1970 + ((dt->days_since_epoch - dt->leap_days) / 365); // Calculating accurate current year by (days_since_epoch - extra leap days)
      dt->day_of_year = ((dt->days_since_epoch - dt->leap_days) % 365) + 1;
  
   
      if(((dt->ntp_year % 4==0) && (dt->ntp_year % 100!=0)) || (dt->ntp_year % 400==0))  
       {
         month_days[1]=29;     //February = 29 days for leap years
         dt->leap_year_ind = 1;    //if current year is leap, set indicator to 1 
        }
            else month_days[1]=28; //February = 28 days for non-leap years 
   
            temp_days=0;
   
    for (dt->ntp_month=0 ; dt->ntp_month <= 11 ; dt->ntp_month++) //calculating current Month
       {
           if (dt->day_of_year <= temp_days) break; 
           temp_days = temp_days + month_days[dt->ntp_month];
        }
    
    temp_days = temp_days - month_days[dt->ntp_month-1]; //calculating current Date
    dt->ntp_date = dt->day_of_year - temp_days;
}
