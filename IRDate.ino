#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "IRDate.h"

IRDate ir;

const char *ssid     = "reza";
const char *password = "@pi#3.14!!";

String getTime(uint32_t,double);
String getDate(uint32_t,double);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org",0, 60000);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.update();
  if(timeClient.getEpochTime()<100){
    delay(1000);
    Serial.println("No access to NTP pool.");
    while(1);
  }
}

uint32_t previousTime=0;
void loop() {
  if((millis()-previousTime)>1000){
    previousTime=millis();
    Serial.println(ir.timeFormat(timeClient.getEpochTime()));
    Serial.println(ir.dateFormat(timeClient.getEpochTime()));
    Serial.println(timeClient.getEpochTime());
    Serial.println();    
  }
}
