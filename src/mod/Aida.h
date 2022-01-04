#include <Arduino.h>
#include <WiFi.h>

bool aida_connect();
void aida_update();
uint16_t aida_get_cpu_freq();
uint16_t aida_get_cpu_usage();
uint16_t aida_get_ram_usage();