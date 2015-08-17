/*
This program normalizes the accelerometer values and computes the orientation of the accelerometer in terms
 of roll and pitch angles.  
 */


#include <microM.h>

void setup()
{ 
  microM.Setup();                        // this must be called first in your setup function

  // impact detection variableshttp://www.farnell.com/datasheets/682873.pdf
  microM.sensitivity=50;                 
  microM.devibrate=50;                   

  Serial.begin(9600);                    // initialize serial monitor
}

void impactDetected()
{
  // don't do anything for now.
}

void printOrientationValues()
{
  // First dimension x=0, y=1, z=2
  // 2nd dim min and max
  static int lastValue[3]={
    0          };
  static int adjustedValue[3]={
    0          };

  // Offset values 
  const int zeroOffset[3]={
    495, 565, 427          };

  // convert voltage to g's,  The scale factor is the force of gravity when the axis is oriented
  // along the gravitational force vector.
  const int scale=256;
  const int changeThreshold=10;

  // only update the last value if it is sufficiently different from the last measurement.
  if (abs(lastValue[0] - microM.xaxis) > changeThreshold || 
    abs(lastValue[1] - microM.yaxis) > changeThreshold || 
    abs(lastValue[2] - microM.zaxis) > changeThreshold)
  {
    lastValue[0] = microM.xaxis;
    lastValue[1] = microM.yaxis;
    lastValue[2] = microM.zaxis;
    int i;
    for (i = 0; i < 3; i++)
    {
      // adjust the measured value so that zero is really zero
      if (i != 0)
      {
        Serial.print(" ");
      }
      Serial.print(lastValue[i]-zeroOffset[i]); // print raw accelerometer value
    }    
    Serial.println();
  } 

}

void loop()
{
  // Measure the impact.  If there is impact, we don't want to measure angles since the angles will not
  // be accurate.  
  microM.Impact();                       // function must be called at least once every 2mS to work accurately
  if(microM.magnitude>0)                 // display results of impact
  {
    impactDetected();
    microM.magnitude=0;                  // prevents display repeating the same values
  } 
  else
  {
    printOrientationValues();
  }
}


