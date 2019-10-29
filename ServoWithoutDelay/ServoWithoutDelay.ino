//------------------------------------------------------------
struct ServoStruct
{
  int pin;
  int currentPosition;
  int timer;
  int onTime;
  bool on;
  //------------------------------------------------------------
  void turn(int position)
  {
    bool direction = (position < currentPosition);
    int onTime = map(abs(position - currentPosition), 0, 1, 0, 480);
    bool weAreMeantToMove = (millis() - timer < onTime) && (this->currentPosition != position);
    if (weAreMeantToMove)
    {
      if (millis() - timer > onTime)
      {
        currentPosition += position;
        stop();
      }
      move(direction);
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
ServoStruct servo = {9, 0, 0, 0, false};
//------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
}
//------------------------------------------------------------
void loop()
{
  servo.turn(2);
}

//------------------------------------------------------------
