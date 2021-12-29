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

#define SIMILARITY 3

enum Slider
{
  pos_left, pos_center, pos_right  
};

enum Button
{
  none,
  left, right, forward, backward, 
  up, down,
  switch_down, 
  win_left_down_1, win_left_down_2, win_left_up_1, win_left_up_2, 
  win_right_down_1, win_right_down_2, win_right_up_1, win_right_up_2
};

Button button = none;
Slider slider = pos_center;

void SetupInput()
{
  pinMode(ANALOG_ARROW, INPUT);
  pinMode(ANALOG_SWITCH, INPUT);
  pinMode(ANALOG_WINDOW_LEFT, INPUT);
  pinMode(ANALOG_WINDOW_RIGHT, INPUT);
}

void CheckButtons()
{
  int valArrow = analogRead(ANALOG_ARROW);
  int valWindowRight = analogRead(ANALOG_WINDOW_RIGHT);
  int valWindowLeft = analogRead(ANALOG_WINDOW_LEFT);
  int valSwitch = analogRead(ANALOG_SWITCH);
  
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

bool ValueSimilar(int val, int val2)
{
  return val <= val2 + SIMILARITY && val >= val2 - SIMILARITY;
}
