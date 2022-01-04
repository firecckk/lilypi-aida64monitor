#include "mod/WIFI.h"
#include "mod/OTA.h"
#include "mod/Aida.h"
#include "sys/Sys_task.h"
#include "ttgo.h"
#include "lv.h"

bool ota_on = true;

void ota_once();
void aida_repeat();
void lv_update();

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  sys_task_init();

  wifi_setup();

  ota_setup();

  ttgo_setup();
  
  lv_create();

  sys_task_run_once( ota_once, millis() + 10000);
  sys_task_run_repeat( []() {aida_repeat(); lv_update();}, 1000);
  //sys_task_run_repeat( []() {  Serial.print("cpu freq:");Serial.println(aida_get_cpu_freq());Serial.print("cpu usage:");Serial.println(aida_get_cpu_usage());Serial.print("ram usage:");Serial.println(aida_get_ram_usage());}, 1000);
}

void loop() {
  if(ota_on) ota_loop();

  sys_task_handle();

  ttgo_loop();

  //delay(5);
}

void lv_update() {
  lv_set_cpu_usage(aida_get_cpu_usage());
  lv_set_ram_usage(aida_get_ram_usage());
}

void ota_once() {
  ota_end();ota_on=false;Serial.println("ota closed.");
}

void aida_repeat() {
  aida_update();
  Serial.println("aida loop");
}