#include "my_display.hpp"
#include "my_wifi.hpp"
#include "my_weather.hpp"
#include "my_time.hpp"

/*
 * Display a countdown (/up)
 */
void displayCounter( bool reset , bool reverse ) {
  static int i = 0;
  int displayNum;

  if (reset)
  {
    i=0;
  } else {
    EVERY_N_MILLISECONDS(50){


      if( reverse ) {
        i = int((i*0.97) -1 );
        i = i<0 ? 9999 : i;
      } else {
        i = (int((i+1) * 1.05) % 10000);
      }

      display.setBrightness(7);
      display.showNumberDec(i, true);
    }
  }
}

void displayResetStatics(){
  displayCounter(true);
}

void showBrightness(){
  static int k = 0;
  EVERY_N_MILLISECONDS(500){
    k = (k+1) % 8;
    display.setBrightness(k);
    display.setSegments(data);
  }
}

void showLocations(uint8_t bpm){
  static uint8_t prev_pos = -1;

  uint8_t pos = beatsin8(bpm,  0, 4, 0, 0);
  if( pos > 3) pos = 3;
  pos = 3 - pos;
  // prev_pos = pos;
  if(pos != prev_pos){
    prev_pos = pos;
    display.clear();
    display.showNumberDec(pos, false, 1, pos);
  }
}

void showTemp(){
  int displayTemperature = (int)temperature;
  static int lastCheck = -10;


  EVERY_N_MINUTES(10){
    Serial.println("Get temp...");
    displayTemperature = (int)getTemperature();
  }

  if(displayTemperature == NO_TEMP){
    displayTemperature = (int)getTemperature();
  }

  if(displayTemperature == NO_TEMP) {
      display.setSegments(na, 2, 0);
  } else {
    display.showNumberDec(displayTemperature, false, 2, 0);
  }
  display.setSegments(celsius, 2, 2);

}

void showTime(){
  EVERY_N_MILLISECONDS(1000){
    struct tm currentTime = readTime(); // read the current time

    uint8_t dot = seconds16()%2 == 0 ? 0b01000000 : 0b00000000; // Display double dots every other second
    display.showNumberDecEx((currentTime.tm_hour * 100) + currentTime.tm_min, dot, true);
  }
}

void showText(){
  static int textNum = 0;

  EVERY_N_MILLISECONDS(1000){
    textNum = (textNum + 1) % 6;
    // display.setSegments(blank,4,0);
    switch (textNum)
    {

    case 0:
      display.setSegments(data,4,0);
      break;

    case 1:
      display.setSegments(blank,4,0);
      break;

    case 2:
      display.setSegments(wof,4,0);
      break;

    case 3:
      display.setSegments(won,4,0);
      break;

    case 4:
      display.setSegments(done,4,0);
      break;

    case 5:
      display.setSegments(celsius,2,2);
      break;

    default:
      break;
    }

  }
}
