#include <microM.h>
#define obstaclePinL 3
#define obstaclePinC 4
#define obstaclePinR 5
#define off 0
const int obstacleOnOffPin = 13;
int obstacleReadings [3];
int obstacleReadingOffsets [3];
int sensorAverage = 0;
int i;
int forwardSpeedL = 85;
int forwardSpeedR = 83;
int reverseSpeedL = -145;
int reverseSpeedR = -150;

int danger = 10;

void turn()
{
  microM.Motors(forwardSpeedL,off,0,0);
  readSensor();
  if (obstacleReadings[0] > danger or obstacleReadings[1] > danger or obstacleReadings[2])
  { 
    turn();
  }
}
void goForward()
{
  microM.Motors(forwardSpeedL, forwardSpeedR, 0, 0);
}

void setup ()
{
  microM.Setup ();
  pinMode (obstacleOnOffPin, OUTPUT);
  Serial.begin (192000);
  delay (3000);
  initSensorReadings();
}
void loop ()
{
  readSensor();
  if (obstacleReadings [0] > danger or obstacleReadings[1] > danger or obstacleReadings[2] > danger)
  {
    turn();
  } else {
    goForward();
  }
}






