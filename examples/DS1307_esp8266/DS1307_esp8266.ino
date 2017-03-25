#include <Wire.h>
#include <RTClib.h>
#include <IRDate.h>
#define TIMEZONE +4.5 //because the now date is 1396/01/02 and My computer is the time difference with utc 4.5 hours
#define UPLAUD_DELAY 10
const uint32_t differenceTime=(long)(TIMEZONE*60*60)-UPLAUD_DELAY;

IRDate ir(IR,DLST_ON);//(time zone , DaylightSavingTime ON or OFF)

RTC_DS1307 RTC;
void setup () {
  Serial.begin(115200);
//Wire.begin();       //for arduino uno,nano
  Wire.begin(12,14);  
  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void loop(){
  DateTime now = RTC.now();
  Serial.print("uinx: ");
  Serial.println(now.unixtime()-differenceTime);
  Serial.print("time: ");
  Serial.println(ir.timeFormat(now.unixtime()-differenceTime));
  Serial.print("date: ");
  Serial.println(ir.dateFormat(now.unixtime()-differenceTime));
  Serial.println();
delay(1000); 
}
