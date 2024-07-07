#include "my_weather.hpp"
double getTemperature() {

    // https://api.openweathermap.org/data/2.5/weather?units=metric&lat=52.2042184&lon=5.4249618&appid=750b4f2e6efecb7d5c581a2539dc5384

    WiFiClient client;
    HTTPClient http;

    String url = ("http://api.openweathermap.org/data/2.5/weather?units="  UNITS  "&lat="  LATITUDE  "&lon="  LONGITUDE  "&appid="  OPENWEATHERMAPAPIKEY );
   Serial.println(url);
    http.begin(client, url);

    int httpCode = http.GET();
    if (httpCode > 0) {
       Serial.print("httpCode: "); Serial.println(httpCode);
        String payload = http.getString();
       Serial.print("payload: "); Serial.println(payload);

        JSONVar myObject = JSON.parse(payload); //JSON object

        if (JSON.typeof(myObject) == "undefined") {
            Serial.println("Parsing input failed!");
            Serial.println(myObject);
            return NO_TEMP;
        }
        temperature = myObject["main"]["temp"];
        return temperature;
    }
    else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpCode);
        return NO_TEMP;
    }

    http.end();
}
