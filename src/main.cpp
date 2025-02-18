#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define LED_PIN 13
#define BUTTON_PIN 2
#define DEBOUNDE_DELAY 150
#define BAUD_RATE 9600
#define IMPUT_SIZE 10

void buttonPrecess(void);


void setup(void) 
{
  Serial.begin(BAUD_RATE);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop(void) 
{
  //Button press
  buttonPrecess();
  
}

void buttonPrecess(void)
{
  static uint32_t nextTime = 0;
  static bool lastState = false;

  if(millis() >= nextTime)
  {
    if (!digitalRead(BUTTON_PIN) & !lastState & ((millis() - nextTime) > DEBOUNDE_DELAY))
    {
      lastState = true;
      nextTime = millis() + DEBOUNDE_DELAY;
    }
    if (digitalRead(BUTTON_PIN) & lastState & ((millis() - nextTime) > DEBOUNDE_DELAY))
    {
      lastState = false;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      nextTime = millis() + DEBOUNDE_DELAY;
    }
  }
}
