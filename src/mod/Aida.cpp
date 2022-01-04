#include "Aida.h"
//https://blog.csdn.net/weixin_42487906/article/details/119990801

const char *host = "192.168.31.247";
const int port = 80;

WiFiClient client;

uint16_t cpu_frequency = 0;
uint16_t cpu_usage = 0;
uint16_t ram_usage = 0;

bool aida_connect()
{
    if (!client.connect(host, port))
    {
        // error
        return false;
    }
    return true;
}

uint16_t substring(String str, String begin_with, String end_with) {
    int16_t dataStart = 0;
    int16_t dataEnd = 0;
    String dataStr;

    dataStart = str.indexOf(begin_with) + begin_with.length();
    dataEnd = str.indexOf(end_with, dataStart);
    dataStr = str.substring(dataStart, dataEnd);
    dataStr.trim();
    //Serial.println(dataStr);
    return dataStr.toInt();
}

void aida_fetch()
{
    String getUrl = "/sse";
    client.print(String("GET ") + getUrl + " HTTP/1.1\r\nConetnt-Type=application/json;charset=utf-8\r\n" + "Host: " + host + "\r\n" + "User-Agent=ESP32\r\nConnection: close\r\n\r\n");

    char endOfHeaders[] = "\n\n";
    if (!client.find(endOfHeaders))
    {
        // not ok
        // no response or invalid
        Serial.println("invalid response");
        return;
    }

    String line = client.readStringUntil('\n');
    //Serial.println(line);

    cpu_frequency = substring(line, "CPU Clock", "MHz");
    cpu_usage = substring(line, "CPU Utilization", "%");
    ram_usage = substring(line, "Memory Utilization", "%");

}

bool aida_connected = false;
void aida_update()
{
    if (!aida_connected && aida_connect())
    {
        Serial.println("aida connect success");
        aida_connected = true;
    }
    else
    {
        aida_fetch();
    }
}

uint16_t aida_get_cpu_freq()
{
    return cpu_frequency;
}

uint16_t aida_get_cpu_usage() {
    return cpu_usage;
}

uint16_t aida_get_ram_usage() {
    return ram_usage;
}