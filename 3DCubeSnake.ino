#define USE_TIMER_1     true
#include <TimerInterrupt.h>
#include <ISR_Timer.h>

#define REFRESH 10

void setup()
{
  SetupInput();

  byte i;
  delay(1000);
  Serial.begin(38400);
  for (i = 0; i < 70; i++)
  {
    Serial.write(0xAD);
  }
  ITimer1.init();
  ITimer1.setInterval(REFRESH, TimerFunction);
}

void loop()
{ 
  while (1)
  {
    Step();
  }
  while (1);
}

void TimerFunction()
{  
  CubePrint();    
  CheckButtons();
}
