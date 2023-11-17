//Clock using the Arduino Nano with 16x2 lcd screen

#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
RtcDS3231<TwoWire> rtc(Wire);
RtcDateTime dt;
BigNumbers_I2C big_num(&lcd);

unsigned int hour;
unsigned int minute;
unsigned int seconds;

byte x = 0;
byte y = 0;
unsigned int number_of_digits = 0;
char *ptr;

void setup(){
  initialize();  
  //setTime();
}
void initialize()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  rtc.Begin();
  big_num.begin();
}

void loop() {   
  dt = rtc.GetDateTime();  
  hour = getHour(dt.Hour());
  minute = dt.Minute();
  seconds = dt.Second();
  
  if((hour == 1 || hour == 10) && minute == 0 && seconds == 0){
   clearScreen();
  }

  if(hour > 9){
    x = 0;
    number_of_digits = 2;
  }
  else{
    x = 2;
    number_of_digits = 1;
  }

  lcd.setCursor(0,0);
  big_num.displayLargeInt(hour,x,y,number_of_digits,false);

  lcd.setCursor(6,0);
  lcd.print('.');
  lcd.setCursor(6,1);
  lcd.print('.');
  lcd.setCursor(7,0);

  x = 7;
  y = 0;
  number_of_digits = 2;

  big_num.displayLargeInt(minute,x,y,number_of_digits,true);
  lcd.setCursor(14,1);
  
  get_ampm(dt.Hour());
  lcd.print(ptr);
}

//Call this once to set time - not needed after this unless time is no longer consistent or 3v battery dies.
void setTime()
{
  //parameters: year,month,day,hour(military),minutes,seconds
  RtcDateTime dt = RtcDateTime(2021,05,06,20,44,0);
  rtc.SetDateTime(dt);
}

//clears the screen in the locations where the hour digit(s) are drawn to the lcd
void clearScreen()
{
   //clear the first row (x,y)
  big_num.clearLargeNumber(2,0);
  big_num.clearLargeNumber(3,0);
  big_num.clearLargeNumber(4,0); 
  big_num.clearLargeNumber(5,0);
  
  //clear the second row (x,y)
  big_num.clearLargeNumber(2,1);
  big_num.clearLargeNumber(3,1);
  big_num.clearLargeNumber(4,1); 
  big_num.clearLargeNumber(5,1); 
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
