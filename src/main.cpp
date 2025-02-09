#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define LED_PIN 13
#define BUTTON_PIN 2
#define DEBOUNDE_DELAY 150
#define BAUD_RATE 9600
#define IMPUT_SIZE 10

String strData = "";
bool recievedFlag = false;

void reciveData(void);
void dataPrecess(void);
void buttonPrecess(void);
int sputc(char __c, FILE *__f);
int sputs(const char* __str);
int sgetc(FILE *__f);


void setup(void) 
{
  Serial.begin(BAUD_RATE);
  fdevopen(&sputc, &sgetc);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  printf("%s\n","Hello, World from Arduino!");
}

void loop(void) 
{
  //Button press
  buttonPrecess();
  
  //Serial communication
  reciveData();
  dataPrecess();
  
}

void buttonPrecess(void)
{
  static uint32_t nextTime = 0;

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    if(millis() >= nextTime)
    {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      nextTime = millis() + DEBOUNDE_DELAY;
    }
  }
}

void reciveData(void)
{
  while (Serial.available() > 0) {        
    strData += (char)sgetc(stdin);       
    recievedFlag = true;                   
    delay(2);                             
  }
}

void dataPrecess(void)
{
  if (recievedFlag) 
  {
    char command[IMPUT_SIZE];
    strData.toCharArray(command, IMPUT_SIZE);

    if (strcmp(command, "led on") == 0) 
    {
      digitalWrite(LED_PIN, HIGH);
      printf("%s\n","LED is ON");
    } 
    else if (strcmp(command, "led off") == 0) 
    {
      digitalWrite(LED_PIN, LOW);
      printf("%s\n","LED is OFF");
    } 
    else 
    {
      printf("%s\n","Unknown command");
    }
    strData = ""; 
    recievedFlag = false;  
  }
}

int sputc(char __c, FILE *__f)
{
  if(__f == stderr)
  {
    Serial.write(__c);
  }
  else 
  {
    Serial.write(__c);
  }
  return __c;
}

int sputs(const char* __str)
{
  for(int i = 0; i < (int)strlen(__str); i++)
  {
    sputc(__str[i], stdout);
  }
  return 0;
}

int sgetc(FILE *__f)
{
  return Serial.read();
}