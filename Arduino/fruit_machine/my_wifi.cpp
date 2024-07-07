#include "my_wifi.hpp"


void wifiConnectStatus(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Wifi not connected, connecting now.");
    int tries = 0;
    while ((WiFi.status() != WL_CONNECTED) && (tries < 60))
    {
      delay(500);
      Serial.print(".");
      if( tries%5 < 2){
        display.showNumberDec(tries, true);
      } else {
        display.setSegments(wof,4,0);
      }
      tries++;
    }
    Serial.println("");

    if(WiFi.status() == WL_CONNECTED){
      display.setSegments(won,4,0);
      Serial.println("success!");
      Serial.print("IP Address is: ");
      Serial.println(WiFi.localIP());
    }
    getTemperature();
  }
}

void wifiSetup(){
  int tries=0;
  WiFi.begin(SSID, SSID_PASSWORD);
  wifiConnectStatus();
}
