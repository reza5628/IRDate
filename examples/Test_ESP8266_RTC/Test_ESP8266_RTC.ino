
#include <Wire.h>
#include <RTClib.h>
#include <IRDate.h>
#define TIMEZONE +4.5 //because the now date is 1396/01/02 and My computer is the time difference with utc 4.5 hours
IRDate ir;
RTC_DS1307 RTC;
void setup () {
//Wire.begin();       //for arduino uno,nano
  Wire.begin(12,14);  // Inicia el puerto I2C
  RTC.begin();        // Inicia la comunicación con el RTC
  delay(500);
  RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  delay(1000);
  Serial.begin(115200); // Establece la velocidad de datos del puerto serie
}
void loop(){
DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

Serial.println(now.unixtime()-(long)(TIMEZONE*60*60));
Serial.println(ir.timeFormat(now.unixtime()-(long)(TIMEZONE*60*60)));
Serial.println(ir.dateFormat(now.unixtime()-(long)(TIMEZONE*60*60)));
Serial.println();
delay(1000); // La información se actualiza cada 1 seg.
}
