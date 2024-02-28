//Digital clock built with Arduino Nano, DS3231 RTC, and 16x2 LCD
//Displays the Date and Time and Temperature

#include <Wire.h>
#include <RtcDS3231.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> 

hd44780_I2Cexp lcd;
RtcDS3231<TwoWire> rtc(Wire);

char *ptr;

void setup(){
  initialize();  
  //setTime();
}

void initialize()
{
  lcd.begin(16,2);
  lcd.backlight();
  rtc.Begin();
}

void loop() {   
  printDate();
  printTime();
  printTemperature();
}

void setTime(){
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  rtc.SetDateTime(compiled);
}

void printDate(){
  RtcDateTime dt = rtc.GetDateTime(); 
  char dateString[20];

  snprintf_P(dateString, 
          countof(dateString),
          PSTR("%02u/%02u/%04u"),
          dt.Month(),
          dt.Day(),
          dt.Year());

  lcd.setCursor(0,0);
  lcd.print(dateString);
}

void printTime(){
  RtcDateTime dt = rtc.GetDateTime(); 
  
  unsigned int hour = getHour(dt.Hour());
  unsigned int minute = dt.Minute();
  unsigned seconds = dt.Second();

  //clears the screen when going from a double digit hour to a single digit hour or vice versa
  if((hour == 1 || hour == 10) && minute == 0 && seconds == 0){
   lcd.clear();
  }

  //print time
  lcd.setCursor(0,1);
  lcd.print(hour);
  lcd.print(':');
  if(minute == 0){
    lcd.print("00"); 
  }else if (minute < 10){
    lcd.print("0");
    lcd.print(minute);
  }else{
    lcd.print(minute);
  }
  
  //print am/pm
  if(hour < 10){
    lcd.setCursor(5,1);
  }else{
    lcd.setCursor(6,1);
  }
  
  get_ampm(dt.Hour());
  lcd.print(ptr);
}

void printTemperature(){
  RtcTemperature temp = rtc.GetTemperature();
  lcd.setCursor(12,1);
  lcd.print(round((temp.AsFloatDegC() *9/5)+32));
  lcd.setCursor(14,1);
  lcd.print((char)223);
  lcd.print('F');
}

//converts military time to standard format
int getHour(unsigned hour)
{
  if(hour > 12) return(hour-12);
  else if(hour == 0) return 12;
  else return hour;
}

//determines whether it's am or pm based on the military time. 
void get_ampm(unsigned short hour){
  if(hour < 12) ptr = "AM";
  else ptr = "PM";
}
