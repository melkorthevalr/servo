//--------------------------------------------------------------------------------------------------

void moveServoDegrees(int degrees, int setOnTime, int interval)
{
  if (speedMode)
  {
    int twentyMilliMicros = 20000;
    //    int onTime = map(degrees, 0, 360, 1000, 2000);
    int onTime = setOnTime;
    int offTime = twentyMilliMicros - onTime;
    Serial.print("time elapsed = "); Serial.println(timeElapsed);
    unsigned long loopStart = millis();
    while ((timeElapsed - loopStart) < interval)
    {
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(onTime); // Duration of the pusle in microseconds
      digitalWrite(servoPin, LOW);
      delayMicroseconds(offTime);
    }
  }
  else
  {
    int onTime = map(degrees, 0, 360, 0, 255);
    analogWrite(servoPin, onTime);
  }
}
//--------------------------------------------------------------------------------------------------
void stopServo()
{
  analogWrite(servoPin, 0);
}


void moveServo(int duty, int time, bool direction = false)
{
  duty = direction ? 255 - duty : duty;
  analogWrite(servoPin, duty);
  delay(time);
  analogWrite(servoPin, 0);
}


void moveServoSet(int servo, int duty, int time, bool direction)
{
  duty = direction ? 255 - duty : duty;
  analogWrite(servo, duty);
  delay(time);
  analogWrite(servo, 0);
}

void calibrateServo()
{
  Serial.println(degreesToMilliSeconds(180, 1));
  moveServo(1, degreesToMilliSeconds(180, 1), false);
  moveServo(0, 2000);
  moveServo(1, degreesToMilliSeconds(180, 1), true);
  moveServo(0, 2000);
  moveServo(1, degreesToMilliSeconds(180, 1), false);
  moveServo(0, 2000);
  moveServo(1, degreesToMilliSeconds(180, 1), false);
  while (true);
}
//--------------------------------------------------------------------------------------------------

int microSecondsToDegree(int micros, int duty)
{

}

int milliSecondsToDegree(int millis, int duty)
{
}
//--------------------------------------------------------------------------------------------------

int degreesToMicroSeconds(int degrees, int duty)
{
  return 100;
}

int degreesToMilliSeconds(int degrees, int duty)
{
  return ((fullTurnMillis * degrees) / 360);

}
//--------------------------------------------------------------------------------------------------
