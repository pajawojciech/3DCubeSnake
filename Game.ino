byte SnakeX = 0;
byte SnakeY = 0;
byte SnakeZ = 0;

void Step()
{
    MoveSnake();
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

void MoveSnake()
{
  if (button == none)
  {
    AllOff();
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

void AllON()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    CubeSet(i, 0xff);
  }
}

void AllOff()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    CubeSet(i, 0x00);
  }
}

void Print()
{
  AllOff();
  int col = 63 - (SnakeX + SnakeY * 8);
  CubeSet(col, 1 << SnakeZ);
}
