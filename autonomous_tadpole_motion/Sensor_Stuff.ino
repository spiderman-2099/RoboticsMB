void initSensorReadings()
{
  digitalWrite(obstacleOnOffPin,HIGH);
  delay(5);
  obstacleReadings[0] =analogRead (obstaclePinL);
  obstacleReadings[1] =analogRead (obstaclePinC);
  obstacleReadings[2] =analogRead (obstaclePinR);
  digitalWrite (obstacleOnOffPin,LOW);

  sensorAverage=obstacleReadings[0]+obstacleReadings[1]+obstacleReadings[2]/3;
    for (i=0;i<3;i++);
}

void readSensor()
{
  digitalWrite (obstacleOnOffPin,HIGH);
  delay(5);
  obstacleReadings[0] =analogRead (obstaclePinL);
  obstacleReadings[1] =analogRead (obstaclePinC);
  obstacleReadings[2] =analogRead (obstaclePinR);
  digitalWrite (obstacleOnOffPin,LOW);
  for (i=0;i<3;i++)
  {
    obstacleReadings[i]=obstacleReadings[i]+obstacleReadingOffsets[i];
  }
}
void printSensorReadings()
{
Serial.println ("Fudged Sensor Readings");
  for (i=0;i<3;i++)
{
    Serial.print(obstacleReadings[i]);
    Serial.print("  ");
  }
  Serial.println();
  Serial.println();
} 
