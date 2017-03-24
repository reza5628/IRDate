#include "IRDate.h"

void IRDate::irTime(){
  IRTime=SysTime-irEpoch;
  IRTime+=(uint32_t)(TimeZone*60*60);
}

void IRDate::second(){
    Second=(IRTime%60);
}
uint8_t IRDate::second(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  second();
  return Second;
}

void IRDate::minute(){
  Minute=((IRTime%(60*60))/60);
}

uint8_t IRDate::minute(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  minute();
  return Minute;
}

void IRDate::hour(){
  Hour=((IRTime%(60*60*24))/(60*60));
}

uint8_t IRDate::hour(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  hour();
  return Hour;
}
//------------------------------------------
//------------------------------------------
void IRDate::year(){
  LeapYears=0;
  LeapYearFlage=0;
  Year=0;
  uint32_t y=0;
  while(1){
    y+=365*24*60*60;
    if(y>=IRTime){break;}
    Year++;
    
    y+=366*24*60*60;LeapYears++; //1351 is leap year
    if(y>=IRTime){LeapYearFlage=1;break;}
    Year++;
    
    y+=365*24*60*60;
    if(y>=IRTime){break;}
    Year++;
    
    y+=365*24*60*60;
    if(y>=IRTime){break;}
    Year++;
  }
  Year+=1350;
}

uint16_t IRDate::year(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  year();
  return Year;
}

void IRDate::moon(){
  year();
  DaysInMon[12-1]=LeapYearFlage?30:29;
  lastDays();
    for(int i=0,temp=0;i<12;i++){
    temp+=DaysInMon[i];
    if(temp>=LastDays){
      Moon=i+1;
      break;
    }
  }  
}

uint8_t IRDate::moon(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  moon();
  return Moon;
}

void IRDate::lastDays(){
  LastDays=(!LeapYearFlage)?((Year-1350)*365+LeapYears):((Year-1350)*365+LeapYears-1);
  LastDays=(IRTime-LastDays*24*60*60)/(24*60*60)+1;
}

void IRDate::day(){
  moon();
  uint32_t d=LastDays;
  for(int i=0;i<(Moon-1);i++){
    d-=DaysInMon[i];
  }
  Day=d;
}

uint8_t IRDate::day(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  day();
  return Day;
}

uint8_t IRDate::dayOfWeek(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  dayOfWeek();
  return DayOfWeek;
}

void IRDate::dayOfWeek(){
  DayOfWeek=((IRTime+(1*24*60*60))%(7*24*60*60))/(24*60*60);  
}
//*****************************
void IRDate::DaylightSavingTimeAutoAdust(){
  TimeZone=3.5;
  day();
  hour();

  if(Moon==1&&Day>1){
    TimeZone+=1;
    return;
  }
  if(Moon>1&&Moon<6){
    TimeZone+=1;
    return;
  }
  if(Moon==6&Day<30){
    TimeZone+=1;
    return;
  }
  if(Moon==6&&Day==30&&Hour<23){
    TimeZone+=1;
    return;    
  }
}
//*******************************
//------------------------------
String IRDate::timeFormat(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  second();
  minute();
  hour();  
  char Time[]="HH:MM:SS";
  sprintf(Time,"%02d:%02d:%02d",Hour,Minute,Second);
  return String(Time);  
}
//------------------------------
String IRDate::dateFormat(uint32_t sysTime){
  SysTime=sysTime;
  irTime();
  DaylightSavingTimeAutoAdust();
  day();
  dayOfWeek();
  char date[]="YYYY,MM,DD";
  String weekDays[7]={"SHANBE","1_SHANBE","2_SHANBE","3_SHANBE","4_SHANBE","5_SHANBE","joume"};
  sprintf(date,"%04d,%02d,%02d",Year,Moon,Day);
  return String(date)+"  "+weekDays[DayOfWeek];
}

