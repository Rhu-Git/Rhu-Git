//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Graph.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LCD5110 myGLCD(3,4,5,6,7);

extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t dot[];
extern uint8_t dot_inv[];

char hours[3] = {0};
char minutes[3] = {0};
char seconds[3] = {0};
char days[3] = {0};
char months[3] = {0};
char years[5] = {0};

char daysOfWeek[7][12] =
{
  "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};

char monthsOfYear[12][12] =
{
  "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

void setup()
{
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2018, 3, 30, 23, 10, 10));//(YYYY, MM, DD, HH, MM, SS)
  myGLCD.InitLCD();
  //myGLCD.invert(true);

  //Mid Line
  myGLCD.drawLine(0, 27, 84, 27);
  myGLCD.drawLine(0, 26, 84, 26);
}

void loop()
{
  DateTime now = rtc.now();
  //Time
  //Hours
  myGLCD.setFont(BigNumbers);
  sprintf(hours, "%02d", ((now.hour()%12)==0) ? (12) : (now.hour()%12));
  myGLCD.print(/*"88"*/hours, 0, 0);
  //Minutes
  sprintf(minutes, "%02d", now.minute());
  myGLCD.print(/*"88"*/minutes, 40, 0);
  //Seconds
  myGLCD.setFont(SmallFont);
  sprintf(seconds, "%02d", now.second());
  myGLCD.print(/*"88"*/seconds, 70, 4);
  /*if(now.hour() > 12)
  myGLCD.print("PM", 70, 14);
  else
  myGLCD.print("AM", 70, 14);*/
  (now.hour()>=12) ? myGLCD.print("PM", 70, 14) : myGLCD.print("AM", 70, 14);

  //Second dots
  if(now.second()%2)
  {
    myGLCD.drawBitmap(32, 5, dot, 4, 4);
    myGLCD.drawBitmap(32, 16, dot, 4, 4);
  }
  else
  {
    myGLCD.drawBitmap(32, 5, dot_inv, 4, 4);
    myGLCD.drawBitmap(32, 16, dot_inv, 4, 4);
  }

  //Day of week
  myGLCD.print(daysOfWeek[now.dayOfTheWeek()]/*"888"*/, 8, 34);
  myGLCD.drawRect(7, 32, 27, 42);

  //Date
  sprintf(days, "%02d", now.day());
  sprintf(years, "%4d", now.year());
  myGLCD.setFont(MediumNumbers);
  myGLCD.print(days/*"88"*/, 34, 29);
  myGLCD.setFont(SmallFont);
  myGLCD.print(monthsOfYear[now.month() - 1], 58, 30);
  myGLCD.print(years, 58, 39);
  
  myGLCD.update();
}
