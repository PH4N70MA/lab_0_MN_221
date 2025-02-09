#include <Arduino.h>

#define LED_PIN 13
#define BUTTON_PIN 2
#define DEBOUNDE_DELAY 150

void setup(void) 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop(void) 
{

  //satatic-se foloseste pentru ca intrarea in functie sa nu se redefineasca la fiecare apelare a functiei
  static uint32_t nextTime = 0;

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    if(millis() >= nextTime)
    {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
    nextTime = millis() + DEBOUNDE_DELAY;
  }
}