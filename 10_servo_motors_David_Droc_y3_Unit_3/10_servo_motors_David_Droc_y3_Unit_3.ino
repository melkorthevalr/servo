/*
   What is this?
   what does it do?
   whor wrote it?
   wehn?
   what do you need?
   what pins are used?
*/
//--------------------------------------------------------------------------------------------------
#include <elapsedMillis.h>
#include <NewPing.h>
//--------------------------------------------------------------------------------------------------
const bool speedMode = true;
const bool setupMode = false;
//--------------------------------------------------------------------------------------------------
const unsigned long fullTurnMillis = 360;
//--------------------------------------------------------------------------------------------------
#define TRIGGER_PIN  7
#define ECHO_PIN     2
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//--------------------------------------------------------------------------------------------------
elapsedMillis timeElapsed;
unsigned int interval ;
//--------------------------------------------------------------------------------------------------
//based on the distance value we have divided the ultrasonic sensor reading into 11 categories, to be able to work with them.
//consqeuntly whilst moving from mone postion to another the servo motor will have 11 postions.
//servoPosition -marks the current postion of the servo motor. Initially we assume that is in the middle

#define servoPin 9
const int servoCount = 5;
const int servoPinList[servoCount] =  {9, 10, 3, 5, 6};

int targetServoPosition; // positions the arduino has to move in that loop;
int currentServoPosition = 0; // current position for the servo motor;
//--------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}

void loop()
{
  Serial.println(currentServoPosition);
  int distance = 180;
  int mapDistance;
  if (distance != 0)
    mapDistance = map(distance, 0, 200, 1, 10) * 20;
  else
    mapDistance = 1;

  //associating to each reading a servo motor "step" (postion)

  if (mapDistance != 1)
    targetServoPosition = map(mapDistance, 20, 200, 0, 4500);
  else
    targetServoPosition = 50000;

  Serial.println(targetServoPosition);

  if ( currentServoPosition != targetServoPosition
       || currentServoPosition < 10000
       || currentServoPosition > 0)
  {
    bool direction = (currentServoPosition - targetServoPosition) < 0 ? true : false;
    interval = abs(currentServoPosition - targetServoPosition); // time for which the servo motor moves
    Serial.print("new interval = "); Serial.println(interval);
    if (!direction){
    Serial.print("direction = "); Serial.println(direction);
      moveServoDegrees(0, 1520, interval);
    }
    else
    Serial.print("direction = "); Serial.println(direction);
      moveServoDegrees(0, 1460, interval);
    currentServoPosition = targetServoPosition ; // saves the starting postion
    stopServo();
  }
  delay(4000);
}
