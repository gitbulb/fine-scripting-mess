#include "my_time.hpp"
struct tm readTime(){
  time_t now;                         // this are the seconds since Epoch (1970) - UTC
  struct tm tm;
  time(&now);                       // read the current time
  localtime_r(&now, &tm);           // update the structure tm with the current time
  return tm;
}


// void showNTPTime() {
//   time(&now);                       // read the current time
//   localtime_r(&now, &tm);           // update the structure tm with the current time
//   Serial.print("year:");
//   Serial.print(tm.tm_year + 1900);  // years since 1900
//   Serial.print("\tmonth:");
//   Serial.print(tm.tm_mon + 1);      // January = 0 (!)
//   Serial.print("\tday:");
//   Serial.print(tm.tm_mday);         // day of month
//   Serial.print("\thour:");
//   Serial.print(tm.tm_hour);         // hours since midnight  0-23
//   Serial.print("\tmin:");
//   Serial.print(tm.tm_min);          // minutes after the hour  0-59
//   Serial.print("\tsec:");
//   Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
//   Serial.print("\twday");
//   Serial.print(tm.tm_wday);         // days since Sunday 0-6
//   if (tm.tm_isdst == 1)             // Daylight Saving Time flag
//     Serial.print("\tDST");
//   else
//     Serial.print("\tstandard");
//   Serial.println();
// }
