#define OUTPUT_DEBUG 1
#define OUTPUT_VALUE ANALOG_SWITCH

#define LAYER_COUNT 8
#define COLUMN_COUNT 64

byte TempCube[COLUMN_COUNT];
byte Cube[COLUMN_COUNT];

void CubeSave()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    Cube[i] = TempCube[i];
  }
}

bool CubeChanged()
{
  byte i;
  for (i = 0; i < 64; i++)
  {
    if(TempCube[i] != Cube[i])
    {
      return true;
    }
  }
  return false;
}

void CubeSet(int column, int value)
{
    TempCube[column] = value;
}

void CubePrint()
{
  if (CubeChanged())
  {
    CubeSave();
    
    Serial.write(0xf2);
    Serial.write(Cube, COLUMN_COUNT);
    
    if (OUTPUT_DEBUG)
    {
      int valRead = analogRead(OUTPUT_VALUE);
      char sVal[5];
      itoa(valRead, sVal, 10);
      Serial.write(sVal);
      Serial.write("|\n");
    }
  }
}
