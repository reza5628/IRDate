
#include "IRDate.h"

IRDate::IRDate(double TimeZone=3.5,bool DLST_status=DLST_ON):TimeZone(TimeZone),DLST_status(DLST_status) {}

void IRDate::irTime(){
  IRTime=SysTime-irEpoch;
  IRTime+=(uint32_t)(LocalTimeZone*60*60);
}

void IRDate::second(){
    Second=(IRTime%60);
}
uint8_t IRDate::second(uint32_t sysTime){
  SysTime=sysTime;
  DaylightSavingTimeAutoAdust();
  second();
  return Second;
}

void IRDate::minute(){
  Minute=((IRTime%(60*60))/60);
}

uint8_t IRDate::minute(uint32_t sysTime){
  SysTime=sysTime;
  DaylightSavingTimeAutoAdust();
  minute();
  return Minute;
}

void IRDate::hour(){
  Hour=((IRTime%(60*60*24))/(60*60));
}

uint8_t IRDate::hour(uint32_t sysTime){
  SysTime=sysTime;
  DaylightSavingTimeAutoAdust();
  hour();
  return Hour;
}
//------------------------------------------
//------------------------------------------
void IRDate::year(){
  LeapYears=0;
  LeapYearFlag=0;
  Year=0;
  uint32_t y=0;
  while(1){
    y+=365*24*60*60;
    if(y>=IRTime){break;}
    Year++;
    
    y+=366*24*60*60;LeapYears++; //1351 is leap year
    if(y>=IRTime){LeapYearFlag=1;break;}
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
  DaylightSavingTimeAutoAdust();
  year();
  return Year;
}

void IRDate::moon(){
  year();
  DaysInMon[12-1]=LeapYearFlag?30:29;
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
  DaylightSavingTimeAutoAdust();
  moon();
  return Moon;
}

void IRDate::lastDays(){
  LastDays=(!LeapYearFlag)?((Year-1350)*365+LeapYears):((Year-1350)*365+LeapYears-1);
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
  DaylightSavingTimeAutoAdust();
  day();
  return Day;
}

uint8_t IRDate::dayOfWeek(uint32_t sysTime){
  SysTime=sysTime;
  DaylightSavingTimeAutoAdust();
  dayOfWeek();
  return DayOfWeek;
}

void IRDate::dayOfWeek(){
  DayOfWeek=((IRTime+(1*24*60*60))%(7*24*60*60))/(24*60*60);  
}
//*****************************
void IRDate::DaylightSavingTimeAutoAdust(){
  LocalTimeZone=TimeZone;
  irTime();
  if(DLST_status==DLST_OFF)
  return;
  
  day();
  hour();

  if(Moon==1&&Day>1){
    LocalTimeZone+=1;
    irTime();
    return;
  }
  if(Moon>1&&Moon<6){
    LocalTimeZone+=1;
    irTime();
    return;
  }
  if(Moon==6&Day<30){
    LocalTimeZone+=1;
    irTime();
    return;
  }
  if(Moon==6&&Day==30&&Hour<23){
    LocalTimeZone+=1;
    irTime();
    return;    
  }
}
//*******************************
//------------------------------
String IRDate::timeFormat(uint32_t sysTime){
  SysTime=sysTime;
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
  DaylightSavingTimeAutoAdust();
  day();
  dayOfWeek();
  char date[]="YYYY,MM,DD";
  String weekDays[7]={"SHANBE","1_SHANBE","2_SHANBE","3_SHANBE","4_SHANBE","5_SHANBE","JOMEH"};
  sprintf(date,"%04d,%02d,%02d",Year,Moon,Day);
  return String(date)+"  "+weekDays[DayOfWeek];
}

//----------------------------------------------
uint32_t IRDate::jalaliToEpoch(uint16_t YY,uint16_t MM,uint16_t DD,uint8_t hh,uint8_t mm,uint8_t ss,double time_zone){
  uint32_t epoch;
  int leapYearCount=(((YY-1)-(1351-4)))/4;
  bool leapYearFlag=((YY-(1351-4))%4==0)?1:0;
  epoch=(YY-1350)*365+leapYearCount;
  int temp=DaysInMon[12-1];
  DaysInMon[12-1]=leapYearFlag?30:29;
  for(int i=1;i<MM;i++){
    DD+=DaysInMon[i-1];
  }
  epoch+=DD-1;
  epoch*=24;
  epoch+=hh;
  epoch*=60;
  epoch+=mm;
  epoch*=60;
  epoch+=ss;
  epoch+=irEpoch;
  time_zone*=60*60;
  DaysInMon[12-1]=temp;
  return (epoch-(uint32_t)time_zone);
}
uint32_t IRDate::jalaliToEpoch(uint16_t YY,uint16_t MM,uint16_t DD,uint8_t hh,uint8_t mm,uint8_t ss){
  return jalaliToEpoch( YY, MM, DD, hh, mm,ss ,0);
}
uint32_t IRDate::jalaliToEpoch(String date="YYYY/MM/DD",String time="hh:mm:ss"){
  uint16_t YY=stringtoint(date,0,3);
  uint8_t MM=stringtoint(date,5,6);
  uint8_t DD=stringtoint(date,8,9);
  uint8_t hh=stringtoint(time,0,1);
  uint8_t mm=stringtoint(time,3,4);
  uint8_t ss=stringtoint(time,6,7);
  return jalaliToEpoch(YY,MM,DD,hh,mm,ss);
}
int IRDate::stringtoint(String &str,int start,int end){
  String temp="";
  for(int i=start;i<=end;i++){
    temp+=str[i];
  }
  return temp.toInt();
}

