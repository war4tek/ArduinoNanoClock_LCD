/*
  The circuit:
 * LCD RS pin 4 to Nano pin 12
 * LCD E pin 6 to Nano pin 10
 * LCD D4 pin 11 to Nano pin 5
 * LCD D5 pin 12 to Nano pin 4
 * LCD D6 pin 13 to Nano pin 3
 * LCD D7 pin 14 to Nano pin 2
 * LCD R/W pin 5 to ground
 * LCD VSS pin 1 to ground
 * LCD LEDK pin 16 to ground
 * LCD VCC pin 2 to +5V
 * 10K potentiometers:
 * ends to +5V and ground
 * wiper to LCD VO pin 3 contrast
 * wiper to LCD LEDA pin 15 brightness
 * Relay:
 * +5V (NC) or GND (NO) to Nano pin 8
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

int inPin = 8;   // input connected to digital pin 8
int val = 0;     // variable to store the read value

void setup() {
  pinMode(inPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" THE GARAGE DOOR");
}

void loop() {
  lcd.setCursor(2, 1);
  val = digitalRead(inPin);   // read the input pin
  if (val < 1)
  {
    lcd.print(" IS  < OPEN > ");
  }
  else
  {
    lcd.print(" IS CLOSED    ");
  }
}
