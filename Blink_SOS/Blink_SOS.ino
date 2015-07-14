/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin ledPin. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

int ledPin=13;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);
}
void shortBlinks()
{
  for (int i = 0; i<3; i++)
  {
  digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(ledPin, HIGH);    // turn the LED off by making the voltage LOW
  delay(500); 
  }
}
void longBlinks()
{
  for (int i = 0; i<3; i++)
  {
  digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(ledPin, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000); 
  }
}

// the loop function runs over and over again forever
void loop() {
  shortBlinks();
  longBlinks();
  shortBlinks();
  delay(1000);
}

