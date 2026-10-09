#pragma once
#include <cstdint>
#include <limits>
struct Maintenance {
 bool initialized=false, candidate=false, open=false; uint32_t changed=0, opened=0, cycles=0; int light=0;
 void update(uint32_t now,bool rawOpen,int adc) {
  light=adc;
  if(!initialized){initialized=true; candidate=open=rawOpen; changed=opened=now; return;}
  if(rawOpen!=candidate){candidate=rawOpen;changed=now;}
  if(candidate!=open && uint32_t(now-changed)>=50){
   open=candidate; if(open){opened=now;if(cycles<std::numeric_limits<uint32_t>::max())++cycles;}
  }
 }
 bool warning(uint32_t now)const{return cycles>=1000 || (open && uint32_t(now-opened)>=30000);}
 bool reset(){if(!initialized||open)return false;cycles=0;return true;}
 const char* state(uint32_t now)const {if(light<0||light>1023)return "invalid";if(warning(now))return "service";return light<150?"dark":"healthy";}
};
