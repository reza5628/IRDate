#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <IRDate.h>

IRDate ir(IR,DLST_ON);//(time zone , DaylightSavingTime ON or OFF)

const char *ssid     = "****";
const char *password = "****";

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
  if((millis()-previousTime)>999){
    previousTime=millis();
    Serial.println(ir.timeFormat(timeClient.getEpochTime()));
    Serial.println(ir.dateFormat(timeClient.getEpochTime()));
    Serial.println(timeClient.getEpochTime());
    Serial.println();
  }
}
