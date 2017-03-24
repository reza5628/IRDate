
#include "IRDate.h"
IRDate ir(IR,DLST_ON);//(time zone , DaylightSavingTime ON or OFF)


void setup(){
  Serial.begin(115200);

  Serial.println();
  Serial.print("unix time: ");
  Serial.println(ir.jalaliToEpoch(1396,1,3,1,25,32));
  Serial.print("unix time: ");
  Serial.println(ir.jalaliToEpoch("1396-01-03","01:25:32"));
  Serial.println();
}

void loop() {
  
}

