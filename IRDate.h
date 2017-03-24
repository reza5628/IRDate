#define UTC 0
#define IR 3.5
#define DLST_ON  1//day liagt saving time on
#define DLST_OFF 0//day liagt saving time off

#ifndef IRDate_h
#define IRDate_h
#include <Arduino.h>
#include <string.h>
class IRDate{
private:
  const uint32_t irEpoch=38361600;//unix time in 1350/01/01
  const float TimeZone=+3.5;
  const bool DLST_status=DLST_ON;
  float LocalTimeZone=+3.5;
  uint32_t SysTime;
  uint32_t IRTime;
  
  uint8_t Hour;
  uint8_t Minute;
  uint8_t Second;
  
  uint8_t LeapYears=0;
  bool LeapYearFlag=0;
  uint16_t Year;
  uint8_t Moon;
  uint8_t Day;
  uint32_t LastDays;//last days of the year
  uint8_t DaysInMon[12]={31,31,31,31,31,31,30,30,30,30,30,29};
  String WeekDays[7]={"SHANBE","1_SHANBE","2_SHANBE","3_SHANBE","4_SHANBE","5_SHANBE","JOMEH"};
  uint8_t DayOfWeek;
public:
  IRDate(float,bool);
  IRDate();
  void irTime();              //convert refrence time 1970-01-01 to 1350-01-01
  uint8_t second(uint32_t);   //convert epoch time to ir second
  void second();
  uint8_t minute(uint32_t);   //convert epoch time to ir minute
  void minute();
  uint8_t hour(uint32_t);     //convert epoch time to ir hour
  void hour();
  uint16_t year(uint32_t);    //convert epoch time to ir year
  void year();
  uint8_t moon(uint32_t);     //convert epoch time to ir moon
  void moon();
  uint8_t day(uint32_t);      //convert epoch time to ir day
  void day();
  void lastDays();
  void dayOfWeek();
  uint8_t dayOfWeek(uint32_t);
  
  void DaylightSavingTimeAutoAdust();
  bool DaylightSavingTimeDetect(uint8_t,uint8_t,uint8_t);

  String timeFormat(uint32_t sysTime);
  String dateFormat(uint32_t sysTime);

  uint32_t jalaliToEpoch(uint16_t,uint16_t,uint16_t,uint8_t,uint8_t,uint8_t,float,bool);
  uint32_t jalaliToEpoch(uint16_t,uint16_t,uint16_t,uint8_t,uint8_t,uint8_t,float);
  uint32_t jalaliToEpoch(uint16_t,uint16_t,uint16_t,uint8_t,uint8_t,uint8_t);
  uint32_t jalaliToEpoch(String,String,float,bool);
  uint32_t jalaliToEpoch(String,String,float);
  uint32_t jalaliToEpoch(String,String);
  int stringtoint(String&,int,int);
};
#endif
