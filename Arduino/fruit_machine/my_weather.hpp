#ifndef __MY_WEATHER_H
#define __MY_WEATHER_H

#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

#include "my_weather_config.hpp"
#define NO_TEMP -275

inline double temperature = NO_TEMP;

double getTemperature();

#endif
