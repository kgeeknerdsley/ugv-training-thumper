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
