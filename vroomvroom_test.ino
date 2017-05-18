#define BRAKEVCC 0 //defines all the ints for wheel rotation
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

void setup() {
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

}

void loop() {
  //CORRECT
  motorGo(0, CCW, 110);
  motorGo(1, CW, 110);
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
  // new chassis is CCW and CW
  Serial.println("Going forward!");
  motorGo(0, CCW, 110);
  motorGo(1, CW, 110);  
  
}

void reverse() { //drives motors in reverse
  Serial.println("Going backward!");
  motorGo(0, CW, 110);
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
