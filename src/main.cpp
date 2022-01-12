#include "mod/WIFI.h"
#include "mod/OTA.h"
#include "mod/Aida.h"
#include "sys/Sys_task.h"
#include "ttgo.h"
#include "lv.h"

bool ota_on = true;

void ota_once();
void lv_update();
void core0_task(void * args);

TaskHandle_t Task1;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  sys_task_init();

  wifi_setup();

  ota_setup();

  ttgo_setup();
  
  lv_create();

  sys_task_run_once( ota_once, millis() + 10000);
  sys_task_run_repeat( []() {
    aida_update(); 
    lv_update();}, 1000);
  //sys_task_run_repeat( []() {Serial.print("free heap:");Serial.println(ESP.getFreeHeap());}, 1000);
  //sys_task_run_repeat( []() {  Serial.print("cpu freq:");Serial.println(aida_get_cpu_freq());Serial.print("cpu usage:");Serial.println(aida_get_cpu_usage());Serial.print("ram usage:");Serial.println(aida_get_ram_usage());}, 1000);
  //xTaskCreate(core0_task, "core0", 2048, NULL, 5, NULL);
  xTaskCreatePinnedToCore(core0_task,"core0", 2048, NULL, 0, &Task1, 0);
}

void loop() {
  //time_start = millis();
  ttgo_loop();                
  //time_end = millis();
  //Serial.print("lv_loop: ");
  //Serial.print(time_end-time_start);
  //Serial.println("ms");

  delay(4);
}

void core0_task(void * args) {
  while(true) {
    if(ota_on) ota_loop();

    //int time_start = millis();
    sys_task_handle();
    //int time_end = millis();
    //Serial.print("sys_task: ");
    //Serial.print(time_end-time_start);
    //Serial.println("ms");
    delay(20);
    //Serial.print("loop() running on core ");
    //Serial.println(xPortGetCoreID());
  }
}

void lv_update() {
  lv_set_cpu_usage(aida_get_cpu_usage());
  lv_set_ram_usage(aida_get_ram_usage());
}

void ota_once() {
  ota_end();ota_on=false;
  Serial.println("ota closed.");
}