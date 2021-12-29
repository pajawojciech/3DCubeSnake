#define USE_TIMER_1     true
#include <TimerInterrupt.h>
#include <ISR_Timer.h>

#define LAYER_COUNT 8
#define COLUMN_COUNT 64
byte pCube[COLUMN_COUNT];
bool CubeChanged = false;

#define ANALOG_ARROW A1
#define BTN_LEFT 18
#define BTN_RIGHT 33
#define BTN_FORWARD 8
#define BTN_BACKWARD 0

#define ANALOG_SWITCH A0
#define BTN_SWITCH_CENTER 33
#define BTN_SWITCH_DOWN 10
#define BTN_SWITCH_LEFT 0
#define BTN_SWITCH_RIGHT 9

#define ANALOG_WINDOW_LEFT A2
#define BTN_WIN_LEFT_DOWN1 35
#define BTN_WIN_LEFT_DOWN2 24
#define BTN_WIN_LEFT_UP1 10
#define BTN_WIN_LEFT_UP2 5

#define ANALOG_WINDOW_RIGHT A3
#define BTN_WIN_RIGHT_DOWN1 34
#define BTN_WIN_RIGHT_DOWN2 22
#define BTN_WIN_RIGHT_UP1 11
#define BTN_WIN_RIGHT_UP2 5

enum Button
{
  none,
  left, right, forward, backward, 
  up, down,
  switch_down, 
  win_left_down_1, win_left_down_2, win_left_up_1, win_left_up_2, 
  win_right_down_1, win_right_down_2, win_right_up_1, win_right_up_2
};

enum Slider
{
  pos_left, pos_center, pos_right  
};

#define SIMILARITY 3
#define REFRESH 10

Button button = none;
Slider slider = pos_center;
byte SnakeX = 0;
byte SnakeY = 0;
byte SnakeZ = 0;

void setup()
{
  pinMode(ANALOG_ARROW, INPUT);
  pinMode(ANALOG_SWITCH, INPUT);
  pinMode(ANALOG_WINDOW_LEFT, INPUT);
  pinMode(ANALOG_WINDOW_RIGHT, INPUT);

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
  byte j;
  
  while (1)
  {
    //DemoALL_OFF();
    //delay(1000);
    //DemoALL_ON();
    //delay(1000);
    
    CheckButtons();
    Print();
    
    if(slider == pos_center)
    {
      delay(300);
    }
    else if(slider == pos_left)
    {
      delay(700);
    }
    else if(slider == pos_right)
    {
      delay(150);
    }
  }
  for (j = 0; j < 70; j++)
  {
    Serial.write(0xED);
  }
  while (1);
}

void DemoALL_ON()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    SetCube(i, 0xff);
  }
}

void DemoALL_OFF()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    SetCube(i, 0x00);
  }
}

void CheckButtons()
{
  byte i;
  
  if (button == none)
  {
    DemoALL_OFF();
  }

  if (button == forward)
  {
    if(SnakeY < 7) SnakeY++;
  }

  else if (button == right)
  {
    if(SnakeX < 7) SnakeX++;
  }

  else if (button == left)
  {
    if(SnakeX > 0) SnakeX--;
  }

  else if (button == backward)
  {
    if(SnakeY > 0) SnakeY--;
  }

  else if (button == down)
  {
    if(SnakeZ > 0) SnakeZ--;  
  }
  
  else if(button == up)
  {
    if(SnakeZ < 7) SnakeZ++;
  }
}

void Print()
{
  DemoALL_OFF();
  int col = 63 - (SnakeX + SnakeY * 8);
  SetCube(col, 1 << SnakeZ);
}

void TimerFunction()
{
  int valArrow = analogRead(ANALOG_ARROW);
  int valWindowRight = analogRead(ANALOG_WINDOW_RIGHT);
  int valWindowLeft = analogRead(ANALOG_WINDOW_LEFT);
  int valSwitch = analogRead(ANALOG_SWITCH);
  
  if (CubeChanged)
  {
    Serial.write(0xf2);
    Serial.write(pCube, COLUMN_COUNT);
    CubeChanged = false;

    if (1)
    {
      int valRead = analogRead(ANALOG_SWITCH);
      char sVal[5];
      itoa(valRead, sVal, 10);
      Serial.write(sVal);
      Serial.write("xx \n");
    }
  }

  if (ValueSimilar(valArrow, BTN_FORWARD))
  {
    button = forward;
  }
  else if (ValueSimilar(valArrow, BTN_RIGHT))
  {
    button = right;
  }
  else if (ValueSimilar(valArrow, BTN_LEFT))
  {
    button = left;
  }
  else if (ValueSimilar(valArrow, BTN_BACKWARD))
  {
    button = backward;
  }

  else if (ValueSimilar(valWindowRight, BTN_WIN_RIGHT_DOWN1) || ValueSimilar(valWindowRight, BTN_WIN_RIGHT_DOWN2))
  {
    button = down;
  }
  
  else if (ValueSimilar(valWindowRight, BTN_WIN_RIGHT_UP1) || ValueSimilar(valWindowRight, BTN_WIN_RIGHT_UP2))
  {
    button = up;
  }

  if (ValueSimilar(valSwitch, BTN_SWITCH_CENTER))
  {
    slider = pos_center;
  }
  else if (ValueSimilar(valSwitch, BTN_SWITCH_LEFT))
  {
    slider = pos_left;
  }
  else if (ValueSimilar(valSwitch, BTN_SWITCH_RIGHT))
  {
    slider = pos_right;
  }
}

void SetCube(int column, int value)
{
  if (pCube[column] != value)
  {
    pCube[column] = value;
    CubeChanged = true;
  }
}

bool ValueSimilar(int val, int val2)
{
  return val <= val2 + SIMILARITY && val >= val2 - SIMILARITY;
}
