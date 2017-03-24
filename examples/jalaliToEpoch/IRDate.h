#define UTC 0
#define IR 3.5
#define DLST_ON  1
#define DLST_OFF 0

#ifndef IRDate_h
#define IRDate_h
#include <Arduino.h>
#include <string.h>
class IRDate{
private:
  const uint32_t irEpoch=38361600;// 1350-01-01
  double TimeZone;
  double LocalTimeZone;
  bool DLST_status;
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
  uint32_t LastDays;
  uint8_t DaysInMon[12]={31,31,31,31,31,31,30,30,30,30,30,29};
  uint8_t DayOfWeek;
public:
  IRDate(double,bool);
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

  String timeFormat(uint32_t sysTime);
  String dateFormat(uint32_t sysTime);

  uint32_t jalaliToEpoch(uint16_t,uint16_t,uint16_t,uint8_t,uint8_t,uint8_t,double);
  uint32_t jalaliToEpoch(uint16_t,uint16_t,uint16_t,uint8_t,uint8_t,uint8_t );
  uint32_t jalaliToEpoch(String,String);
  int stringtoint(String&,int,int);
};
#endif
