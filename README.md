# IRDate
convet epoch time to jalali time and date.

#include <IRDate>
IRDate ir   or  IRDate(time zone , DLTS_ON/SLTS_OFF) DTLS->DayLightTimeSaving

int second=second(unix time); 

int minute=minute(unix time); 

int hour=hour(unix time); 

int year=year(unix time); 

int moon=moon(unix time); 

int day=day(unix time); 

int dow=dayOfWeek(unix time);


String time=timeFormat(unix time);

String date=dateFormat(unix time);


convert jalali date to unix time :

unix=jalaliToEpoch("1395/02/02","20:30:00");

unix=jalaliToEpoch(1395,02,02,20,30,00);
