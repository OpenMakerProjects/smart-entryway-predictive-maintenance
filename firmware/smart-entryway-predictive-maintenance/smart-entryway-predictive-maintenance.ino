#include <Arduino.h>
#include "../maintenance.h"
#include <cstring>
Maintenance monitor; uint32_t printed=0; char line[16];size_t used=0;
void setup(){pinMode(2,INPUT_PULLUP);pinMode(5,OUTPUT);pinMode(6,OUTPUT);pinMode(9,OUTPUT);analogReadResolution(10);Serial.begin(115200);}
void loop(){
 uint32_t now=millis();monitor.update(now,digitalRead(2)==HIGH,analogRead(A0));
 while(Serial.available()){char c=Serial.read();if(c=='\n'){line[used]=0;if(!strcmp(line,"RESET")){Serial.println(monitor.reset()?"reset accepted":"reset denied: close door");}used=0;}else if(c!='\r'){if(used<sizeof(line)-1)line[used++]=c;else used=0;}}
 const char* s=monitor.state(now);
 analogWrite(5,!strcmp(s,"invalid")?180:(!strcmp(s,"service")?160:0));
 analogWrite(6,!strcmp(s,"healthy")?120:(!strcmp(s,"service")?70:0));
 analogWrite(9,!strcmp(s,"dark")?120:0);
 if(uint32_t(now-printed)>=2000){printed=now;Serial.print("{\"ms\":");Serial.print(now);Serial.print(",\"open\":");Serial.print(monitor.open?"true":"false");Serial.print(",\"cycles\":");Serial.print(monitor.cycles);Serial.print(",\"light_adc\":");Serial.print(monitor.light);Serial.print(",\"state\":\"");Serial.print(s);Serial.println("\"}");}
 delay(10);
}
