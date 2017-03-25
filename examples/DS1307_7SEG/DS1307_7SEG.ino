
#include <Wire.h>
#include <RTClib.h>
#include <IRDate.h>
#include <Arduino.h>
#include <TM1637Display.h>

#define TIMEZONE +4.5 //because the now date is 1396/01/02 and My computer is the time difference with utc 4.5 hours
#define UPLAUD_DELAY 12
#define led 16
#define RTC_CLK 14
#define RTC_DIO 10
#define SG_CLK 5
#define SG_DIO 4

IRDate ir(IR,DLST_ON);//(time zone , DaylightSavingTime ON or OFF)

TM1637Display display(SG_CLK, SG_DIO);

const uint32_t differenceTime=(long)(TIMEZONE*60*60)-UPLAUD_DELAY;
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
  display.setBrightness(7);
}
bool flag=0;
void loop(){
  DateTime now = RTC.now();
  Serial.print("uinx: ");
  Serial.println(now.unixtime()-differenceTime);
  Serial.print("time: ");
  Serial.println(ir.timeFormat(now.unixtime()-differenceTime));
  Serial.print("date: ");
  Serial.println(ir.dateFormat(now.unixtime()-differenceTime));
  Serial.println();
  int HH=ir.hour(now.unixtime()-differenceTime);
  int MM=ir.minute(now.unixtime()-differenceTime);
  display.showNumberDecEx(HH*100+MM,(0x80>>(flag)),1);
  flag=!flag;
  delay(1000); 
}
