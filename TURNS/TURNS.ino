//------------------------------------------------------------
struct ServoStruct
{
  int pin;
  int currentPosition;
  int timer;
  int onTime;
  bool on;
  bool moveLock;
  //------------------------------------------------------------
  void turn(int position)
  {
    if (this->currentPosition != position && !moveLock)
    {
      moveLock = true;
      timer = millis();
    }
    bool direction = (position < currentPosition);
    int onTime = map(abs(position - currentPosition), 0, 1, 0, 480);
    bool weAreMeantToMove = (this->currentPosition != position);

    if (weAreMeantToMove)
    {
      if (millis() - timer > onTime)
      {
        currentPosition += position;
        moveLock = false;
      }
      Serial.println("current postition: "); Serial.println( this->currentPosition );
      move(direction);
    }
    else
    {
      stop();
    }
  };
  //------------------------------------------------------------
  void move(bool direction)
  {
    int duty = direction ? 253 : 2;
    analogWrite(this->pin, duty);
  };
  //------------------------------------------------------------
  void stop()
  {
    analogWrite(this->pin, 255);
  };
  //------------------------------------------------------------
};
//------------------------------------------------------------
ServoStruct servo[]{
  {.pin = 10},
  {.pin = 9},
  {.pin = 11},
  {.pin = 6},
  {.pin = 5}
};
//------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
}
//------------------------------------------------------------
void loop()
{
//  int position = getNextDistance();
  servo[2].turn(10);
  servo[1].turn(10);
  servo[0].turn(-10);
  servo[3].turn(-10);
  servo[4].turn(-10);
  //  servo.move(false);
}

//------------------------------------------------------------
