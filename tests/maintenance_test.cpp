#include "../firmware/maintenance.h"
#include <cassert>
#include <cstring>
#include <iostream>
int main(){
 Maintenance m;m.update(0,false,500);m.update(1,true,500);m.update(40,false,500);m.update(100,true,500);m.update(149,true,500);assert(m.cycles==0);m.update(150,true,500);assert(m.open&&m.cycles==1);
 assert(!m.warning(30149));assert(m.warning(30150));assert(!m.reset());
 m.update(31000,false,100);m.update(31050,false,100);assert(!m.open&&m.reset());assert(!strcmp(m.state(31050),"dark"));
 m.cycles=999;m.update(32000,true,500);m.update(32050,true,500);assert(m.cycles==1000&&m.warning(32050));
 m.cycles=UINT32_MAX;m.update(33000,false,500);m.update(33050,false,500);m.update(34000,true,500);m.update(34050,true,500);assert(m.cycles==UINT32_MAX);
 Maintenance w;w.update(UINT32_MAX-100,false,500);w.update(UINT32_MAX-50,true,500);w.update(0,true,500);assert(w.cycles==1);assert(w.warning(30000));
 w.light=1024;assert(!strcmp(w.state(0),"invalid"));Maintenance boot;boot.update(20,true,500);assert(boot.cycles==0&&boot.warning(30020));assert(!boot.reset());
 std::cout<<"debounce, cycle threshold, long-open, reset, saturation, boot-open and timer wrap passed\n";
}
