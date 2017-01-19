/* final_autonomous_code.ino
 *  
 *  Master Code for Kitty's obstacle avoidance
 * Written by Kevin Worsley, Jason Kim
 * Drives until an obstacle is detected, tries to turn out of its way, repeat ad infinitum.
 * Blue LED on Kitty's body will light up when the bot is moving forward, will turn off when turning
 *  - Basically an OK indicator to move
 * 
 * Motor setup code and function goMotor() credit to Sparkfun's example code for the Monster Motor Shield
 * Ultrasonic calculations credit to Parallax datasheets
 * Some servo code from Arduino's Sweep tutorial
 * 
 * UGV Apprentice Team, Winter Q 2017
 */
 
#include <Servo.h> //includes servo library

#define BRAKEVCC 0 //defines all the ints for wheel rotation
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

Servo myservo; //enables our servo

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

const int trigPin = 12; //pins for the ultrasonic
const int echoPin = 13;

int duration, inches, cm; //variables! yay!
int distance;
int pos;

bool lefts = true; //flags to see if the left and right directions are safe
bool rights = true;

void setup()
{
  Serial.begin(9600); //everything getting set up, basically
  
   pinMode(trigPin, OUTPUT); //sets up ultrasonic pins to work
   pinMode(echoPin, INPUT);

  // Initialize digital pins as outputs for motors
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize brakes for motors
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }

  pinMode(10, OUTPUT); //sets up the little blue LED

  myservo.attach(3); //gets the servo ready to go
}

void loop(){

  distance = testDistance(); //checks the distance and prints it to serial monitor
  Serial.println(distance);
  
  if(distance <= 0) { //resets bogus data from the ultrasonic to something usable
    distance = 37;
  }

/*Note on the driving algorithm
 * 
 * Kitty checks two flags to see which directions are safe, and then moves accordingly.
 * Each possibility has a preprogrammed move set to get her unstuck. Probably.
 * She doesn't like walls at shallow angles, but it's 10:00pm and I want to go to bed so we'll work on this after demo day.
 * TODO: add another ultrasonic for better coverage?
 * TODO: perhaps put the ultrasonic on a constant sweep so it's always cognizant of its area
 */

  if(distance <= 36) {
    lefts = true; //assigns everything to true to reset from its last run
    rights = true;
    
    digitalWrite(10, LOW); //turns off the forward light cause it ain't going forward
    brake();
    delay(700);

    for (pos = 90; pos <= 180; pos += 2) { //everybody look left
      myservo.write(pos);              
      delay(20);                       
    }

    myservo.detach(); //leaves the servo in its position

    distance = testDistance(); //tests the left distance

    if(distance <= 36) { //makes the safety decision for left
      Serial.println("Left side is not safe!");
      lefts = false;
    }

    delay(500);

    myservo.attach(3); //gets the servo ready to go to sweep

    for (pos = 180; pos >= 0; pos -= 2) { //sweeps to the right, gets in position for right safety test
      myservo.attach(3);
      myservo.write(pos);              
      delay(20);                       
    }
    
    myservo.detach();  //same deal as before, waits, tests, then makes decision
    
    distance = testDistance();

    if(distance <= 36) {
      Serial.println("The right isn't safe!");
      rights = false;
    }

    delay(500);

    myservo.attach(3);

    for (pos = 0; pos <= 90; pos += 2) { //resets eyes back to the front
      myservo.attach(3);
      myservo.write(pos);
      delay(20);  
  }

    //OK IS TRUE
    //UNSAFE IS FALSE
    if(lefts && rights) { //if all clear, usual turn left then go
      left();
      delay(800);
      brake();
      delay(700);
    } else if(lefts == true && rights == false) { //if right obstructed, turn left
      left();
      delay(800);
      brake();
      delay(700);
    } else if(lefts == false && rights == true) { //if left obstructed, turn right
      right();
      delay(800);
      brake();
      delay(800); 
    } else if(lefts == false && rights == false) { //if both sides obstructed, back up more than usual and turn left
      reverse();
      delay(1000);
      brake();
      delay(700);
      left();
      delay(600);
    }
  }
  
  digitalWrite(10, HIGH); //lights the "moving forward" led indicator
  forward();
  
  delay(100);
}

void brake() { //full stop to motors
  Serial.println("Stopping!");
  motorGo(0, 0, 110);
  motorGo(1, 0, 110);
}
void left() { //turns motors left
  Serial.println("Left turning");
  motorGo(0, CCW, 110);
  motorGo(1, CCW, 110);
}

void right() { //turns motors right
  Serial.print("Right turning");
  motorGo(0, CW, 110);
  motorGo(1, CW, 110);
}

void forward() { //drives motors forwards
  Serial.println("Going forward!");
  motorGo(0, CW, 110);
  motorGo(1, CCW, 110);
}

void reverse() { //drives motors in reverse
  Serial.println("Going backward!");
  motorGo(0, CCW, 110);
  motorGo(1, CW, 110);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) //Sparkfun's code to get the motors to run
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

int testDistance() { //algorithm to check distance and spit out an integer value
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

long microsecondsToInches(long microseconds) { //math.
  //calculation comes from Parallax's datasheet
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds) { //also math.
  return microseconds / 29 / 2;
}
