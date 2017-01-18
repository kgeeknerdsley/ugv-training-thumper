/*  MonsterMoto Shield Example Sketch
  date: 5/24/11
  code by: Jim Lindblom
  hardware by: Nate Bernstein
  SparkFun Electronics
 
 License: CC-SA 3.0, feel free to use this code however you'd like.
 Please improve upon it! Let me know how you've made it better.
 
 This is really simple example code to get you some basic
 functionality with the MonsterMoto Shield. The MonsterMote uses
 two VNH2SP30 high-current full-bridge motor drivers.
 
 Use the motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) 
 function to get motors going in either CW, CCW, BRAKEVCC, or 
 BRAKEGND. Use motorOff(int motor) to turn a specific motor off.
 
 The motor variable in each function should be either a 0 or a 1.
 pwm in the motorGo function should be a value between 0 and 255.
 */

#include <Servo.h>

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

const int trigPin = 12;
const int echoPin = 13;

int duration, inches, cm;

int distance;



void setup()
{
  Serial.begin(9600);
  
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  // motorGo(0, CW, 1023);
  // motorGo(1, CCW, 1023);
}

// RIGHT: motor 0 CW, motor 1 CW
// LEFT: motor 0 CCW, motor 1 CCW
//FORWARD: motor 0 CW, motor 1 CCW
//BACKWARD: motor 0 CCW, motor 1 CW
void loop()
{
//  motorGo(0, CCW, 150);
//  motorGo(1, CW, 150);
//  delay(1000);

forward();
distance = testDistance();
Serial.println(distance);

if(distance <= 10) {
  brake();
  delay(1000);
  backward();
  delay(1000);
  brake();
  delay(1000);
  left();
  delay(1000);
  brake();
  delay(1000);
}




}

void brake() {
  motorGo(0, 0, 150);
  motorGo(1, 0, 150);
}
void left() {
  motorGo(0, CCW, 150);
  motorGo(1, CCW, 150);
}

void right() {
  motorGo(0, CW, 150);
  motorGo(1, CW, 150);
}

void forward() {
  motorGo(0, CW, 150);
  motorGo(1, CCW, 150);
  delay(1000);
}

void backward() {
  motorGo(0, CCW, 150);
  motorGo(1, CW, 150);
  delay(1000);
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

int testDistance() {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);

  return inches;
  delay(500);
}

long microsecondsToInches(long microseconds) {
  //calculation comes from Parallax's datasheet
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
