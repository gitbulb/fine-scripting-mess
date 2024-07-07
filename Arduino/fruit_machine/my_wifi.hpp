#ifndef __MY_WIFI_H
#define __MY_WIFI_H

#include <ESP8266WiFi.h>
#include "my_wifi_credentials.hpp"
#include "my_display.hpp"
#include "my_weather.hpp"

void wifiConnectStatus();
void wifiSetup();

#endif
