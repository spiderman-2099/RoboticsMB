
#include <microM.h>   // Use the microM library for motor control, IR command

enum SensorPosition {
  SenseLeft=0, 
  SenseCenter=1,
  SenseRight=2,
}; 
const int numSensors=3;
//
// Sensing pins
//
const int sensePin[3]={5,4,3};  // array containing the pin numbers
// for right,center, and left

const int senseOnOffPin=1;

int sensorInput[3]={0}; // sensor inputs

int counter=0;
const int numSamples=20;

// collect multiple samples for each sensor
unsigned int sensorSamples[numSensors][numSamples]={0};

const int DISTANCE_CLOSE=0;
const int DISTANCE_MEDIUM=1;
const int DISTANCE_FAR=2;

void setup()
{
  microM.Setup(); // set up the library
  pinMode(senseOnOffPin,OUTPUT); // set up sensor on/off pin
  Serial.begin(19200); // set the serial port speed.
  digitalWrite(senseOnOffPin, HIGH);  // Turn on the sensor
}

/**
 * average the last "numSample" samples
 **/
void computeSampleAverage(unsigned int *averagedSamples)
{
  int sampleIndex=counter % numSamples;

  // collect raw data into sample array
  for (int i = 0; i < numSensors; i++)
  {
    sensorSamples[i][sampleIndex]=analogRead(sensePin[i]);
    ;
    averagedSamples[i]=0; // clear the computed average
    for (int j=0; j < numSamples; j++)
    {
      // compute average samples for the sensor
      averagedSamples[i] += sensorSamples[i][j];
    }
    averagedSamples[i]=averagedSamples[i]/numSamples;
  }
  counter++;
}

void applyThresholds(unsigned int *averageInput, int *normalizedValues)
{
  const int zeroOffset[numSensors]={140, 120, 120};
  const int closeThreshold[numSensors]={400,400,400};
  const int farThreshold[numSensors]={100, 99, 70};
  const int mediumThreshold[numSensors]={200,200,200};
  
  for (int i = 0; i < numSensors; i++)
  {
    normalizedValues[i]=averageInput[i] - zeroOffset[i];
    if (normalizedValues[i] > closeThreshold[i])
    {
      normalizedValues[i] = DISTANCE_CLOSE;
    } else if (normalizedValues[i] > mediumThreshold[i])
    {
      normalizedValues[i] = DISTANCE_MEDIUM;
    } else
    {
      normalizedValues[i] = DISTANCE_FAR;
    }
    
  }
}

/**
 * Determine whether or not the values changed
 **/
bool valuesChanged(int *values)
{
  bool changed=false;
  static int lastValues[numSensors]={0,0,0};
  for (int i =0; i < numSensors; i++)
  {
     if (values[i] != lastValues[i])
     {
       changed=true;
       lastValues[i]=values[i]; // set the last value
     }
  }
  return changed;
}

void loop()
{
  unsigned int averageInput[numSensors]={0};
  int normalizedValues[numSensors]={0};
  
  computeSampleAverage(averageInput);

  applyThresholds(averageInput, normalizedValues);

  if (valuesChanged(normalizedValues))
  {
    for (int i = 0; i < numSensors; i++)
    {
      Serial.print(normalizedValues[i]);
      Serial.print(" ");
    }
    Serial.println();
  } 
}


