//activates the servo library
#include <Servo.h>

//gives our servo a name
Servo servo1;

int pos = 0; //variable to store the servo position
 
const int trigPin = 12;
const int echoPin = 13;
 
void setup() {
  
  // initialize serial communication:
  Serial.begin(9600);
  
  //sets the pin to output and attaches servo to it
  pinMode(1, OUTPUT);
  servo1.attach(3); //attach the servo on pin 3 (orange pin)

  //attach red pin to 5V and brown pin to GND
}

 
void loop()
{
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  //vars for calculations
  }
 { long duration, inches, cm;
 
  //send out the pulse from sensor, should be 10+ ms
  //setting to LOW before the HIGH makes signal cleaner
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  //reads the pulse that's come back
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //print out data
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //wait before starting over
  //can be as long as you want depending on how frequently the data is needed
  delay(100);
}
 
long microsecondsToInches(long microseconds)
{
  //calculation comes from Parallax's datasheet
  
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;


  {
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
{
  long duration, inches, cm;
 
  //send out the pulse from sensor, should be 10+ ms
  //setting to LOW before the HIGH makes signal cleaner
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  //reads the pulse that's come back
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //print out data
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //wait before starting over
  //can be as long as you want depending on how frequently the data is needed
  delay(100);
}
 
long microsecondsToInches(long microseconds)
{
  //calculation comes from Parallax's datasheet
  
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds);
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
 }
  }
