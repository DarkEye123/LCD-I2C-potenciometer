/**
 * Simple experiment using lcd & potenciometer
**/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DEAD_ZONE 5
int direction = 0;

void scrollDisplay(int new_direction)
{
  if (new_direction - direction > DEAD_ZONE)
  {
    lcd.scrollDisplayLeft();
  }
  else if (new_direction - direction < -DEAD_ZONE)
  {
    lcd.scrollDisplayRight();
  }
}

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
  pinMode(A0, INPUT);
  lcd.clear();
  direction = analogRead(A0);
}

unsigned int counter = 0;
void loop()
{
  // when characters arrive over the serial port...
  int new_direction = analogRead(A0);
  delay(100);
  scrollDisplay(new_direction);
  direction = new_direction;

  if (Serial.available())
  {
    // wait a bit for the entire message to arrive
    delay(100);
    while (Serial.available() > 0)
    {
      String x = Serial.readString();
      Serial.println(x);
      for (char c : x)
      {
        lcd.print(c);
        delay(100);
      }
      lcd.setCursor(0, counter % 2);
    }
    counter++;
  }
}