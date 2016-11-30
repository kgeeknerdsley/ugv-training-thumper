//Autonomy Basic:
//UGV can drive randomly and not hit walls

#include <Servo.h>

Servo servo1;

long inches;
long cm;
long duration;

int distance;

//pins for motor A
const int enA = 10;
const int in1 = 9;
const int in2 = 8;

//pins for motor B
const int enB = 5;
const int in3 = 7;
const int in4 = 6;

//pins for ultrasonic
const int trigPin = 12;
const int echoPin = 13;

//pin for servo
//const int 

void setup() {
  //startup serial for ultrasonic
  Serial.begin(9600);
  
  //set all motor pins to go
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {
  Serial.println("I'm moving forward!");
  distance = getDistance();
  Serial.println(distance);
  
  
  if(distance <= 10) {
    Serial.println("I'm stopping!");
    Serial.println("I'm backing up!");
    Serial.println("I'm rotating 45 degrees left!");
    delay(1000);
  }
  
  delay(1000);
 
  

}

void motorsStart() {
  //motor A startup
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  //motor B startup
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

//shuts down all the motors
void motorsStop() {
  //motor A shutdown
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//gets distance from obstacle, returns in cm
int getDistance() {
  pinMode(trigPin, LOW);
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
  
  return cm;
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
}
